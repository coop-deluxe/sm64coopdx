#include <stdbool.h>
#include "smlua.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/fs/fmem.h"

// table to track loaded modules per mod
static void smlua_init_mod_loaded_table(lua_State* L, const char* modPath) {
    // Create a unique registry key for this mod's loaded table
    char registryKey[SYS_MAX_PATH + 16];
    snprintf(registryKey, sizeof(registryKey), "mod_loaded_%s", modPath);

    lua_getfield(L, LUA_REGISTRYINDEX, registryKey);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_setfield(L, LUA_REGISTRYINDEX, registryKey);
    } else {
        lua_pop(L, 1);
    }
}

void smlua_get_mod_loaded_table(lua_State* L, struct Mod* mod) {   
    // create registry key for this mod's loaded table
    char registryKey[SYS_MAX_PATH + 16] = "";
    snprintf(registryKey, sizeof(registryKey), "mod_loaded_%s", mod->relativePath);

    // get or create the mod's loaded table
    lua_getfield(L, LUA_REGISTRYINDEX, registryKey);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setfield(L, LUA_REGISTRYINDEX, registryKey);
    }
}

bool smlua_get_cached_file(lua_State* L, struct Mod* mod, struct ModFile* file) {
    smlua_get_mod_loaded_table(L, mod);

    lua_getfield(L, -1, file->relativePath); // push loaded[file->relativePath]

    if (lua_isnil(L, -1)) {
        // not cached
        lua_pop(L, 2); // pop nil and loaded table
        return false;
    }

    // cached, remove loaded table and leave value on top
    lua_remove(L, -2);
    return true;
}

void smlua_cache_module_result(lua_State* L, struct Mod* mod, struct ModFile* file) {
    // push true if nothing returned
    if (lua_gettop(L) == 0 || lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_pushboolean(L, 1);
    }

    // get loaded table
    smlua_get_mod_loaded_table(L, mod);

    lua_pushvalue(L, -2); // duplicate result
    lua_setfield(L, -2, file->relativePath); // loaded[file->relativePath] = result
    lua_pop(L, 1); // pop loaded table
}

static struct ModFile* smlua_find_mod_file(const char* moduleName) {
    char basePath[SYS_MAX_PATH] = "";
    char absolutePath[SYS_MAX_PATH] = "";

    if (!gLuaActiveMod) {
        return NULL;
    }

    // get the directory of the current file
    if (gLuaActiveModFile) {
        path_get_folder(gLuaActiveModFile->relativePath, basePath);
    }

    // resolve moduleName to a path relative to mod root
    resolve_relative_path(basePath, moduleName, absolutePath);

    char luaName[SYS_MAX_PATH] = "";
    char luacName[SYS_MAX_PATH] = "";
    snprintf(luaName, SYS_MAX_PATH, "%s.lua", absolutePath);
    snprintf(luacName, SYS_MAX_PATH, "%s.luac", absolutePath);

    // since mods' relativePaths are relative to the mod's root, we can do a direct comparison
    for (int i = 0; i < gLuaActiveMod->fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];

        // don't consider the currently running file
        if (file == gLuaActiveModFile) {
            continue;
        }

        // only consider lua files
        if (!str_ends_with(file->relativePath, ".lua") && !str_ends_with(file->relativePath, ".luac")) {
            continue;
        }

        // check for match
        if (!strcmp(file->relativePath, luaName) || !strcmp(file->relativePath, luacName)) {
            return file;
        }
    }

    return NULL;
}

static int smlua_custom_require(lua_State* L) {
    const char* moduleName = luaL_checkstring(L, 1);

    struct Mod* activeMod = gLuaActiveMod;
    if (!activeMod) {
        LOG_LUA("require() called outside of mod context");
        return 0;
    }

    // find the file in mod files
    struct ModFile* file = smlua_find_mod_file(moduleName);
    if (!file) {
        LOG_LUA("module '%s' not found in mod files", moduleName);
        return 0;
    }

    // check cache first
    if (smlua_get_cached_file(L, activeMod, file)) {
        return 1;
    }

    // mark module as "loading" to prevent recursion
    smlua_get_mod_loaded_table(L, activeMod);
    lua_pushboolean(L, 1);
    lua_setfield(L, -2, file->relativePath);
    lua_pop(L, 1); // pop loaded table

    // cache the previous mod file
    struct ModFile* prevModFile = gLuaActiveModFile;

    // tag it as a loaded lua module
    file->isLoadedLuaModule = true;

    // load and execute
    gLuaActiveModFile = file;
    int rc = smlua_load_script(activeMod, file, activeMod->index, false);

    if (rc == LUA_OK) {
        smlua_cache_module_result(L, activeMod, file);
    }

    gLuaActiveModFile = prevModFile;

    return 1; // return the module value
}

void smlua_bind_custom_require(lua_State* L) {
    // replace the global require function
    lua_pushcfunction(L, smlua_custom_require);
    lua_setglobal(L, "require");
}

void smlua_init_require_system(void) {
    lua_State* L = gLuaState;
    if (!L) return;

    // initialize the custom require function
    smlua_bind_custom_require(L);

    // initialize loaded tables for each mod
    for (int i = 0; i < gActiveMods.entryCount; i++) {
        struct Mod* mod = gActiveMods.entries[i];
        smlua_init_mod_loaded_table(L, mod->relativePath);
    }
}