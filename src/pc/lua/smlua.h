#ifndef SMLUA_H
#define SMLUA_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "types.h"

#include "smlua_cobject.h"
#include "smlua_utils.h"
#include "smlua_functions.h"

#include "pc/debuglog.h"

#define LOG_LUA LOG_INFO

enum LuaHookedEventType {
    HOOK_UPDATE,
    HOOK_MARIO_UPDATE,
    HOOK_MAX,
};

extern lua_State* gLuaState;

void smlua_call_event_hooks(enum LuaHookedEventType hookType);
void smlua_call_event_hooks_param(enum LuaHookedEventType hookType, int param);

bool smlua_call_action_hook(struct MarioState* m, s32* returnValue);

void smlua_init(void);
void smlua_update(void);
void smlua_shutdown(void);

#endif