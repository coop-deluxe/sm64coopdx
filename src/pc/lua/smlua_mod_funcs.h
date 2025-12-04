#ifndef SMLUA_MOD_FUNCS_H
#define SMLUA_MOD_FUNCS_H

#include <lua.h>
#include <stdbool.h>

// Mod management functions
int smlua_func_mods_enable(lua_State *L);
int smlua_func_mods_disable(lua_State *L);
int smlua_func_mods_get_list(lua_State *L);
int smlua_func_network_reconnect(lua_State *L);

// Global flag to indicate that reconnection was requested by Lua
extern bool gReconnectRequested;

#endif
