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

#define LUA_BOM_11 0x0000000000005678llu
#define LUA_BOM_19 0x4077280000000000llu

static bool smlua_check_binary_header(struct ModFile *file) {
    FILE *f = fopen(file->cachedPath, "rb");
    if (f) {

        // Read signature
        char signature[sizeof(LUA_SIGNATURE)] = {0};
        if (fread(signature, 1, sizeof(LUA_SIGNATURE) - 1, f) != sizeof(LUA_SIGNATURE) - 1) {
            LOG_LUA("Failed to load lua script '%s': File too short.", file->cachedPath);
            fclose(f);
            return false;
        }

        // Check signature
        if (strcmp(signature, LUA_SIGNATURE) != 0) {
            fclose(f);
            return true; // Not a binary lua
        }

        // Read version number
        u8 version;
        if (fread(&version, 1, 1, f) != 1) {
            LOG_LUA("Failed to load lua script '%s': File too short.", file->cachedPath);
            fclose(f);
            return false;
        }

        // Check version number
        u8 expectedVersion = strtoul(LUA_VERSION_MAJOR LUA_VERSION_MINOR, NULL, 16);
        if (version != expectedVersion) {
            LOG_LUA("Failed to load lua script '%s': Lua versions don't match (%X, expected %X).", file->cachedPath, version, expectedVersion);
            fclose(f);
            return false;
        }

        // Read the rest of the header
        u8 header[28];
        if (fread(header, 1, 28, f) != 28) {
            LOG_LUA("Failed to load lua script '%s': File too short.", file->cachedPath);
            fclose(f);
            return false;
        }

        // The following errors are silent (they're due to non-matching endianness/bitness and shouldn't prevent the rest of the mod from loading)

        // Check endianness
        u64 bom11 = *((u64 *) (header + 12));
        u64 bom19 = *((u64 *) (header + 20));
        if (bom11 != LUA_BOM_11) {
            LOG_ERROR("Failed to load lua script '%s': BOM at offset 0x11 don't match (%016llX, expected %016llX).", file->cachedPath, bom11, LUA_BOM_11);
            fclose(f);
            return false;
        }
        if (bom19 != LUA_BOM_19) {
            LOG_ERROR("Failed to load lua script '%s': BOM at offset 0x19 don't match (%016llX, expected %016llX).", file->cachedPath, bom19, LUA_BOM_19);
            fclose(f);
            return false;
        }

        // Check sizes
        u8 sizeOfCInteger = header[7];
        u8 sizeOfCPointer = header[8];
        u8 sizeOfCFloat = header[9];
        u8 sizeOfLuaInteger = header[10];
        u8 sizeOfLuaNumber = header[11];
        if (sizeOfCInteger != sizeof(int)) {
            LOG_ERROR("Failed to load lua script '%s': sizes of C Integer don't match (%d, expected %llu).", file->cachedPath, sizeOfCInteger, (long long unsigned)sizeof(int));
            fclose(f);
            return false;
        }
        if (sizeOfCPointer != sizeof(void *)) { // 4 for 32-bit architectures, 8 for 64-bit
            LOG_ERROR("Failed to load lua script '%s': sizes of C Pointer don't match (%d, expected %llu).", file->cachedPath, sizeOfCPointer, (long long unsigned)sizeof(void *));
            fclose(f);
            return false;
        }
        if (sizeOfCFloat != sizeof(float)) {
            LOG_ERROR("Failed to load lua script '%s': sizes of C Float don't match (%d, expected %llu).", file->cachedPath, sizeOfCFloat, (long long unsigned)sizeof(float));
            fclose(f);
            return false;
        }
        if (sizeOfLuaInteger != sizeof(LUA_INTEGER)) {
            LOG_ERROR("Failed to load lua script '%s': sizes of Lua Integer don't match (%d, expected %llu).", file->cachedPath, sizeOfLuaInteger, (long long unsigned)sizeof(LUA_INTEGER));
            fclose(f);
            return false;
        }
        if (sizeOfLuaNumber != sizeof(LUA_NUMBER)) {
            LOG_ERROR("Failed to load lua script '%s': sizes of Lua Number don't match (%d, expected %llu).", file->cachedPath, sizeOfLuaNumber, (long long unsigned)sizeof(LUA_NUMBER));
            fclose(f);
            return false;
        }

        // All's good
        LOG_INFO("Loading lua script '%s'", file->cachedPath);
        fclose(f);
        return true;
    }
    LOG_LUA("Failed to load lua script '%s': File not found.", file->cachedPath);
    return false;
}

static void smlua_load_script(struct Mod* mod, struct ModFile* file, u16 remoteIndex) {
    if (!smlua_check_binary_header(file)) return;

    lua_State* L = gLuaState;

    lua_settop(L, 0);

    gSmLuaConvertSuccess = true;
    gLuaInitializingScript = 1;
    LOG_INFO("Loading lua script '%s'", file->cachedPath);
    bool failed = (luaL_loadfile(L, file->cachedPath) != LUA_OK);

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

    // only run on success
    if (failed) {
        LOG_LUA("Failed to load lua script '%s'.", file->cachedPath);
        LOG_LUA("%s", smlua_to_string(L, lua_gettop(L)));
        gLuaInitializingScript = 0;
        return;
    }

    // run chunks
    LOG_INFO("Executing '%s'", file->relativePath);
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
    luaL_requiref(L, "package", luaopen_package, 1);
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
    /*lua_gc(L, LUA_GCSTEP, 1);
    lua_gc(L, LUA_GCSTOP, 0);*/

    // EDIT: uhh, it turns out that is not the case
    // if we only do incremental garbage collection,
    // eventually the garbage will build up so much
    // that the game slows to a crawl. Messing with
    // the GC setting is what caused Arena to get worse
    // over time.
    // The real fix would be to make smlua produce less
    // garbage.
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
