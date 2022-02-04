#ifndef SMLUA_HOOKS_H
#define SMLUA_HOOKS_H

#include <stdbool.h>

enum LuaHookedEventType {
    HOOK_UPDATE,
    HOOK_MARIO_UPDATE,
    HOOK_BEFORE_MARIO_UPDATE,
    HOOK_ON_SET_MARIO_ACTION,
    HOOK_BEFORE_PHYS_STEP,
    HOOK_ON_PVP_ATTACK,
    HOOK_ON_PLAYER_CONNECTED,
    HOOK_ON_PLAYER_DISCONNECTED,
    HOOK_MAX,
};

static char* LuaHookedEventTypeName[] = {
    "HOOK_UPDATE",
    "HOOK_MARIO_UPDATE",
    "HOOK_BEFORE_MARIO_UPDATE",
    "HOOK_ON_SET_MARIO_ACTION",
    "HOOK_BEFORE_PHYS_STEP",
    "HOOK_ON_PVP_ATTACK",
    "HOOK_ON_PLAYER_CONNECTED",
    "HOOK_ON_PLAYER_DISCONNECTED",
    "HOOK_MAX"
};

void smlua_call_event_hooks(enum LuaHookedEventType hookType);
void smlua_call_event_hooks_mario_param(enum LuaHookedEventType hookType, struct MarioState* m);
void smlua_call_event_hooks_mario_params(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2);

bool smlua_call_action_hook(struct MarioState* m, s32* returnValue);

bool smlua_call_chat_command_hook(char* command);
void smlua_display_chat_commands(void);

void smlua_bind_hooks(void);

#endif