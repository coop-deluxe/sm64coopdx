#ifndef SMLUA_H
#define SMLUA_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdbool.h>
#include "types.h"

#include "smlua_cobject.h"
#include "smlua_cobject_allowlist.h"
#include "smlua_cobject_autogen.h"
#include "smlua_utils.h"
#include "smlua_functions.h"
#include "smlua_functions_autogen.h"
#include "smlua_hooks.h"
#include "smlua_sync_table.h"

#include "pc/debuglog.h"

#define LOG_LUA(...)  ( _debuglog_print_log("LUA ", __FILE__), printf(__VA_ARGS__), printf("\n") )

#ifdef DEVELOPMENT
#define LUA_STACK_CHECK_BEGIN() int __LUA_STACK_TOP = lua_gettop(gLuaState)
#define LUA_STACK_CHECK_END() if ((__LUA_STACK_TOP) != lua_gettop(gLuaState)) { smlua_dump_stack(); fflush(stdout); } assert((__LUA_STACK_TOP) == lua_gettop(gLuaState))
#else
#define LUA_STACK_CHECK_BEGIN()
#define LUA_STACK_CHECK_END()
#endif

extern lua_State* gLuaState;
extern u8 gLuaInitializingScript;

void smlua_init(void);
void smlua_update(void);
void smlua_shutdown(void);

#endif