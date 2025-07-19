#include "smlua.h"
#include "smlua_cobject.h"
#include "pc/mods/mods.h"
#include "pc/network/network.h"

// Mod management functions
int smlua_func_mods_enable(lua_State *L) {
    LUA_STACK_CHECK_BEGIN_NUM(0);

    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    const char* relativePath = smlua_to_string(L, 1);
    if (relativePath == NULL || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("mods_enable: invalid relativePath parameter");
        return 0;
    }

    mods_enable((char*)relativePath);

    LUA_STACK_CHECK_END();
    return 0;
}

int smlua_func_mods_disable(lua_State *L) {
    LUA_STACK_CHECK_BEGIN_NUM(0);

    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    const char* relativePath = smlua_to_string(L, 1);
    if (relativePath == NULL || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("mods_disable: invalid relativePath parameter");
        return 0;
    }

    mods_disable((char*)relativePath);

    LUA_STACK_CHECK_END();
    return 0;
}

// Function to list available mods
int smlua_func_mods_get_list(lua_State *L) {
    LUA_STACK_CHECK_BEGIN_NUM(1);

    // Create table for mods list
    lua_newtable(L);
    int modTable = lua_gettop(L);
    
    // Iterate through all local mods
    for (unsigned int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        
        // Push mod index as array index
        lua_pushinteger(L, i + 1);
        
        // Create table for this mod's properties
        lua_newtable(L);
        
        // Add mod properties
        lua_pushstring(L, "name");
        lua_pushstring(L, mod->name ? mod->name : "Unknown");
        lua_settable(L, -3);
        
        lua_pushstring(L, "relativePath");
        lua_pushstring(L, mod->relativePath);
        lua_settable(L, -3);
        
        lua_pushstring(L, "enabled");
        lua_pushboolean(L, mod->enabled);
        lua_settable(L, -3);
        
        if (mod->category) {
            lua_pushstring(L, "category");
            lua_pushstring(L, mod->category);
            lua_settable(L, -3);
        }
        
        if (mod->description) {
            lua_pushstring(L, "description");
            lua_pushstring(L, mod->description);
            lua_settable(L, -3);
        }
        
        // Add mod table to mods list
        lua_settable(L, modTable);
    }

    LUA_STACK_CHECK_END();
    return 1;  // Return the table
}

// Global flag to indicate that reconnection was requested by Lua
bool gReconnectRequested = false;

int smlua_func_network_reconnect(lua_State *L) {
    LUA_STACK_CHECK_BEGIN_NUM(0);

    if (!smlua_functions_valid_param_count(L, 0)) { return 0; }

    // Set flag instead of calling directly
    gReconnectRequested = true;

    LUA_STACK_CHECK_END();
    return 0;
}
