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

static struct ModFile* smlua_find_mod_file(const char* moduleName) {
    char relativeDir[SYS_MAX_PATH] = "";

    if (!gLuaActiveMod) {
        return NULL;
    }

    if (gLuaActiveModFile) {
        path_get_folder(gLuaActiveModFile->relativePath, relativeDir);
    }

    bool hasRelativeDir = strlen(relativeDir) > 0;

    struct ModFile* bestPick = NULL;
    int bestRelativeDepth = INT_MAX;
    int bestTotalDepth = INT_MAX;
    bool foundRelativeFile = false;

    char luaName[SYS_MAX_PATH] = "";
    char luacName[SYS_MAX_PATH] = "";
    snprintf(luaName, SYS_MAX_PATH, "%s.lua", moduleName);
    snprintf(luacName, SYS_MAX_PATH, "%s.luac", moduleName);

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
        if (!str_ends_with(file->relativePath, moduleName) && !str_ends_with(file->relativePath, luaName) && !str_ends_with(file->relativePath, luacName)) {
            continue;
        }

        // get total path depth
        int totalDepth = path_depth(file->relativePath);

        // make sure we never load the old-style lua files with require()
        if (totalDepth < 1) {
            continue;
        }

        // get relative path depth
        int relativeDepth = INT_MAX;
        if (hasRelativeDir && path_is_relative_to(file->relativePath, relativeDir)) {
            relativeDepth = path_depth(file->relativePath + strlen(relativeDir));
            foundRelativeFile = true;
        }

        // pick new best
        // relative files will always win against absolute files
        // other than that, shallower files will win
        if (relativeDepth < bestRelativeDepth || (!foundRelativeFile && totalDepth < bestTotalDepth)) {
            bestPick = file;
            bestRelativeDepth = relativeDepth;
            bestTotalDepth = totalDepth;
        }
    }

    return bestPick;
}

static int smlua_load_mod_file(lua_State* L, struct ModFile* file) {
    if (!file->cachedPath) {
        LOG_LUA("Lua 'require' error: module '%s' not found in mod files", file->relativePath);
        return LUA_ERRFILE;
    }

    FILE* f = f_open_r(file->cachedPath);
    if (!f) {
        LOG_LUA("Lua 'require' error: cannot open '%s': file not found", file->cachedPath);
        return LUA_ERRFILE;
    }

    // get file size
    f_seek(f, 0, SEEK_END);
    size_t length = f_tell(f);
    f_rewind(f);

    // allocate buffer
    void* buffer = calloc(length + 1, 1);
    if (!buffer) {
        f_close(f);
        f_delete(f);
        LOG_LUA("Lua 'require' error: cannot allocate buffer for '%s'", file->cachedPath);
        return LUA_ERRMEM;
    }

    // read file
    if (f_read(buffer, 1, length, f) < length) {
        free(buffer);
        f_close(f);
        f_delete(f);
        LOG_LUA("Lua 'require' error: cannot read '%s'", file->cachedPath);
        return LUA_ERRFILE;
    }

    f_close(f);
    f_delete(f);

    // load the buffer as lua code
    int result = luaL_loadbuffer(L, buffer, length, file->relativePath);
    free(buffer);

    return result;
}

static int smlua_custom_require(lua_State* L) {
    const char* moduleName = luaL_checkstring(L, 1);

    if (!gLuaActiveMod) {
        LOG_LUA("require() called outside of mod context");
        return 0;
    }

    // create registry key for this mod's loaded table
    char registryKey[SYS_MAX_PATH + 16] = "";
    snprintf(registryKey, sizeof(registryKey), "mod_loaded_%s", gLuaActiveMod->relativePath);

    // get or create the mod's loaded table
    lua_getfield(L, LUA_REGISTRYINDEX, registryKey);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setfield(L, LUA_REGISTRYINDEX, registryKey);
    }

    // find the file in mod files
    struct ModFile* file = smlua_find_mod_file(moduleName);
    if (!file) {
        LOG_LUA("module '%s' not found in mod files", moduleName)
        return 0;
    }

    // check if module is already loaded
    lua_getfield(L, -1, file->relativePath);
    if (!lua_isnil(L, -1)) {
        // module already loaded, return it
        return 1;
    }
    lua_pop(L, 1); // pop nil value

    // load the file
    int loadResult = smlua_load_mod_file(L, file);
    if (loadResult != LUA_OK) {
        return 0;
    }

    // get the mod's global table
    lua_getfield(L, LUA_REGISTRYINDEX, gLuaActiveMod->relativePath);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        LOG_LUA("mod environment not found")
        return 0;
    }
    lua_setupvalue(L, -2, 1); // set _ENV

    // cache the previous mod file
    struct ModFile* prevModFile = gLuaActiveModFile;

    // execute the loaded chunk
    gLuaActiveModFile = file;
    int callResult = smlua_pcall(L, 0, 1, 0);
    gLuaActiveModFile = prevModFile;

    if (callResult != LUA_OK) {
        return 0;
    }

    // if the module didn't return anything, use true
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_pushboolean(L, 1);
    }

    // store in loaded table
    lua_pushvalue(L, -1); // duplicate return value
    lua_setfield(L, -3, file->relativePath); // loaded[file->relativePath] = return_value

    // clean up stack
    lua_remove(L, -2);

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