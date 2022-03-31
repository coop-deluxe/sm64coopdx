#ifndef SMLUA_HOOKS_H
#define SMLUA_HOOKS_H

#include <stdbool.h>
#include "include/behavior_table.h"

enum LuaHookedEventType {
    HOOK_UPDATE,
    HOOK_MARIO_UPDATE,
    HOOK_BEFORE_MARIO_UPDATE,
    HOOK_ON_SET_MARIO_ACTION,
    HOOK_BEFORE_PHYS_STEP,
    HOOK_ALLOW_PVP_ATTACK,
    HOOK_ON_PVP_ATTACK,
    HOOK_ON_PLAYER_CONNECTED,
    HOOK_ON_PLAYER_DISCONNECTED,
    HOOK_ON_HUD_RENDER,
    HOOK_ON_INTERACT,
    HOOK_ON_LEVEL_INIT,
    HOOK_ON_WARP,
    HOOK_ON_SYNC_VALID,
    HOOK_ON_OBJECT_UNLOAD,
    HOOK_ON_SYNC_OBJECT_UNLOAD,
    HOOK_ON_PAUSE_EXIT,
    HOOK_MAX,
};

static char* LuaHookedEventTypeName[] = {
    "HOOK_UPDATE",
    "HOOK_MARIO_UPDATE",
    "HOOK_BEFORE_MARIO_UPDATE",
    "HOOK_ON_SET_MARIO_ACTION",
    "HOOK_BEFORE_PHYS_STEP",
    "HOOK_ALLOW_PVP_ATTACK",
    "HOOK_ON_PVP_ATTACK",
    "HOOK_ON_PLAYER_CONNECTED",
    "HOOK_ON_PLAYER_DISCONNECTED",
    "HOOK_ON_HUD_RENDER",
    "HOOK_ON_INTERACT",
    "HOOK_ON_LEVEL_INIT",
    "HOOK_ON_WARP",
    "HOOK_ON_SYNC_VALID",
    "HOOK_ON_OBJECT_UNLOAD",
    "HOOK_ON_SYNC_OBJECT_UNLOAD",
    "HOOK_ON_PAUSE_EXIT",
    "HOOK_MAX"
};

extern u32 gLuaMarioActionIndex;

void smlua_call_event_hooks(enum LuaHookedEventType hookType);
void smlua_call_event_hooks_bool_param(enum LuaHookedEventType hookType, bool value);
void smlua_call_event_hooks_bool_param_ret_bool(enum LuaHookedEventType hookType, bool value, bool* returnValue);
void smlua_call_event_hooks_mario_param(enum LuaHookedEventType hookType, struct MarioState* m);
void smlua_call_event_hooks_mario_params(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2);
void smlua_call_event_hooks_mario_params_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2, bool* returnValue);
void smlua_call_event_hooks_interact_params(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType, bool interactValue);
void smlua_call_event_hooks_object_param(enum LuaHookedEventType hookType, struct Object* obj);

enum BehaviorId smlua_get_original_behavior_id(const BehaviorScript* behavior);
const BehaviorScript* smlua_override_behavior(const BehaviorScript* behavior);
const BehaviorScript* get_lua_behavior_from_id(enum BehaviorId id, bool returnOriginal);
bool smlua_call_behavior_hook(const BehaviorScript** behavior, struct Object* object, bool before);

bool smlua_call_action_hook(struct MarioState* m, s32* returnValue);
u32 smlua_get_action_interaction_type(struct MarioState* m);

bool smlua_call_chat_command_hook(char* command);
void smlua_display_chat_commands(void);

void smlua_bind_hooks(void);

#endif
