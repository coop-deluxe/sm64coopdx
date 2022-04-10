#include "smlua.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/crash_handler.h"
#include "pc/lua/utils/smlua_text_utils.h"

lua_State* gLuaState = NULL;
u8 gLuaInitializingScript = 0;
struct Mod* gLuaLoadingMod = NULL;
struct Mod* gLuaActiveMod = NULL;

static void smlua_exec_file(char* path) {
    lua_State* L = gLuaState;
    if (luaL_dofile(L, path) != LUA_OK) {
        LOG_LUA("Failed to load lua file '%s'.", path);
        puts(smlua_to_string(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

static void smlua_exec_str(char* str) {
    lua_State* L = gLuaState;
    if (luaL_dostring(L, str) != LUA_OK) {
        LOG_LUA("Failed to load lua string.");
        puts(smlua_to_string(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

static void smlua_load_script(struct Mod* mod, struct ModFile* file, u16 remoteIndex) {
    lua_State* L = gLuaState;

    char fullPath[SYS_MAX_PATH] = { 0 };
    if (!mod_file_full_path(fullPath, mod, file)) {
        LOG_ERROR("Failed to concat path: '%s' + '%s", mod->relativePath, file->relativePath);
        return;
    }

    gLuaInitializingScript = 1;
    if (luaL_loadfile(L, fullPath) != LUA_OK) {
        LOG_LUA("Failed to load lua script '%s'.", fullPath);
        puts(smlua_to_string(L, lua_gettop(L)));
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
    if (lua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK) {
        LOG_LUA("Failed to execute lua script '%s'.", fullPath);
        puts(smlua_to_string(L, lua_gettop(L)));
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
    //luaopen_debug(L);
    //luaopen_io(L);
    luaL_requiref(L, "math", luaopen_math, 1);
    //luaopen_os(L);
    //luaopen_package(L);
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
}

void smlua_shutdown(void) {
    smlua_text_utils_reset_all();
    smlua_cobject_allowlist_shutdown();
    smlua_cpointer_allowlist_shutdown();
    lua_State* L = gLuaState;
    if (L != NULL) {
        lua_close(L);
        gLuaState = NULL;
    }
}
