#include "smlua.h"
#include "game/hardcoded.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/crash_handler.h"
#include "pc/lua/utils/smlua_text_utils.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "pc/lua/utils/smlua_level_utils.h"
#include "pc/lua/utils/smlua_anim_utils.h"
#include "pc/djui/djui.h"

lua_State* gLuaState = NULL;
u8 gLuaInitializingScript = 0;
u8 gSmLuaSuppressErrors = 0;
struct Mod* gLuaLoadingMod = NULL;
struct Mod* gLuaActiveMod = NULL;
struct Mod* gLuaLastHookMod = NULL;

void smlua_mod_error(void) {
    struct Mod* mod = gLuaActiveMod;
    if (mod == NULL) { mod = gLuaLastHookMod; }
    if (mod == NULL) { return; }
    char txt[255] = { 0 };
    snprintf(txt, 254, "'%s' has script errors!", mod->name);
    djui_lua_error(txt);
}

int smlua_error_handler(UNUSED lua_State* L) {
    if (lua_type(L, -1) == LUA_TSTRING) {
        LOG_LUA("%s", lua_tostring(L, -1));
    }
    smlua_logline();
    return 0;
}

int smlua_pcall(lua_State* L, int nargs, int nresults, UNUSED int errfunc) {
    gSmLuaConvertSuccess = true;
    lua_pushcfunction(L, smlua_error_handler);
    int errorHandlerIndex = 1;
    lua_insert(L, errorHandlerIndex);
    int rc = lua_pcall(L, nargs, nresults, errorHandlerIndex);
    lua_remove(L, errorHandlerIndex);
    return rc;
}

void smlua_exec_file(char* path) {
    lua_State* L = gLuaState;
    if (luaL_dofile(L, path) != LUA_OK) {
        LOG_LUA("Failed to load lua file '%s'.", path);
        LOG_LUA("%s", smlua_to_string(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

void smlua_exec_str(char* str) {
    lua_State* L = gLuaState;
    if (luaL_dostring(L, str) != LUA_OK) {
        LOG_LUA("Failed to load lua string.");
        LOG_LUA("%s", smlua_to_string(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

static void smlua_load_script(struct Mod* mod, struct ModFile* file, u16 remoteIndex) {
    lua_State* L = gLuaState;

    lua_settop(L, 0);

    gSmLuaConvertSuccess = true;
    gLuaInitializingScript = 1;
    LOG_INFO("Loading lua script '%s'", file->cachedPath);
    if (luaL_loadfile(L, file->cachedPath) != LUA_OK) {
        LOG_LUA("Failed to load lua script '%s'.", file->cachedPath);
        LOG_LUA("%s", smlua_to_string(L, lua_gettop(L)));
        return;
    }

    // check if this is the first time this mod has been loaded
    lua_getfield(L, LUA_REGISTRYINDEX, mod->relativePath);
    bool firstInit = (lua_type(L, -1) == LUA_TNIL);
    lua_pop(L, 1);

    // create mod's "global" table
    if (firstInit) {
        lua_newtable(L); // create _ENV tables
        lua_newtable(L); // create metatable
        lua_getglobal(L, "_G"); // get global table

        // remove certain default functions
        lua_pushstring(L, "load");           lua_pushnil(L); lua_settable(L, -3);
        lua_pushstring(L, "loadfile");       lua_pushnil(L); lua_settable(L, -3);
        lua_pushstring(L, "loadstring");     lua_pushnil(L); lua_settable(L, -3);
        lua_pushstring(L, "collectgarbage"); lua_pushnil(L); lua_settable(L, -3);
        lua_pushstring(L, "dofile");         lua_pushnil(L); lua_settable(L, -3);

        // set global as the metatable
        lua_setfield(L, -2, "__index");
        lua_setmetatable(L, -2);

        // push to registry with path as name (must be unique)
        lua_setfield(L, LUA_REGISTRYINDEX, mod->relativePath);
    }

    // load mod's "global" table
    lua_getfield(L, LUA_REGISTRYINDEX, mod->relativePath);
    lua_setupvalue(L, 1, 1); // set upvalue (_ENV)

    // load per-file globals
    if (firstInit) {
        smlua_sync_table_init_globals(mod->relativePath, remoteIndex);
        smlua_cobject_init_per_file_globals(mod->relativePath);
    }

    // run chunks
    if (smlua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK) {
        LOG_LUA("Failed to execute lua script '%s'.", file->cachedPath);
        LOG_LUA("%s", smlua_to_string(L, lua_gettop(L)));
        smlua_dump_stack();
        gLuaInitializingScript = 0;
        return;
    }
    gLuaInitializingScript = 0;
}

void smlua_init(void) {
    smlua_shutdown();
    smlua_cobject_allowlist_init();
    smlua_cpointer_allowlist_init();

    gLuaState = luaL_newstate();
    lua_State* L = gLuaState;

    // load libraries
    luaopen_base(L);
    //luaopen_coroutine(L);
#if defined(DEVELOPMENT)
    luaL_requiref(L, "debug", luaopen_debug, 1);
    luaL_requiref(L, "io", luaopen_io, 1);
    luaL_requiref(L, "os", luaopen_os, 1);
    luaL_requiref(L, "package ", luaopen_package, 1);
#endif
    luaL_requiref(L, "math", luaopen_math, 1);
    luaL_requiref(L, "string", luaopen_string, 1);
    luaL_requiref(L, "table", luaopen_table, 1);
    //luaopen_utf8(L);

    smlua_bind_hooks();
    smlua_bind_cobject();
    smlua_bind_functions();
    smlua_bind_functions_autogen();
    smlua_bind_sync_table();

    extern char gSmluaConstants[];
    smlua_exec_str(gSmluaConstants);

    smlua_cobject_init_globals();

    // load scripts
    mods_size_enforce(&gActiveMods);
    LOG_INFO("Loading scripts:");
    for (int i = 0; i < gActiveMods.entryCount; i++) {
        struct Mod* mod = gActiveMods.entries[i];
        LOG_INFO("    %s", mod->relativePath);
        gLuaLoadingMod = mod;
        gLuaActiveMod = mod;
        gLuaLastHookMod = mod;
        gLuaLoadingMod->customBehaviorIndex = 0;
        gPcDebug.lastModRun = gLuaActiveMod;
        for (int j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            if (!str_ends_with(file->relativePath, ".lua")) {
                continue;
            }
            smlua_load_script(mod, file, i);
        }
        gLuaActiveMod = NULL;
        gLuaLoadingMod = NULL;
    }
}

void smlua_update(void) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    
    smlua_call_event_hooks(HOOK_UPDATE);
    // Collect our garbage after calling our hooks.
    // If we don't, Lag can quickly build up from our mods.
    lua_gc(L, LUA_GCCOLLECT, 0);
}

void smlua_shutdown(void) {
    hardcoded_reset_default_values();
    smlua_text_utils_reset_all();
    smlua_audio_utils_reset_all();
    audio_custom_shutdown();
    smlua_cobject_allowlist_shutdown();
    smlua_cpointer_allowlist_shutdown();
    smlua_clear_hooks();
    smlua_model_util_clear();
    smlua_level_util_reset();
    smlua_anim_util_reset();
    lua_State* L = gLuaState;
    if (L != NULL) {
        lua_close(L);
        gLuaState = NULL;
    }
    gLuaLoadingMod = NULL;
    gLuaActiveMod = NULL;
    gLuaLastHookMod = NULL;
}
