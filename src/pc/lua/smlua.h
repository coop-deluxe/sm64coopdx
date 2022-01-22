#ifndef SMLUA_H
#define SMLUA_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "types.h"

#include "smlua_cobject.h"
#include "smlua_utils.h"
#include "smlua_functions.h"
#include "smlua_functions_autogen.h"
#include "smlua_hooks.h"

#include "pc/debuglog.h"

#define LOG_LUA LOG_INFO

extern lua_State* gLuaState;

void smlua_init(void);
void smlua_update(void);
void smlua_shutdown(void);

#endif