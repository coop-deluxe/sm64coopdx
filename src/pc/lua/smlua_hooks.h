#ifndef SMLUA_HOOKS_H
#define SMLUA_HOOKS_H

#include <stdbool.h>
#include "include/behavior_table.h"

#include "smlua.h"
#include "pc/mods/mod.h"

// forward declare
struct Camera;

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
    HOOK_ALLOW_INTERACT,
    HOOK_ON_INTERACT,
    HOOK_ON_LEVEL_INIT,
    HOOK_ON_WARP,
    HOOK_ON_SYNC_VALID,
    HOOK_ON_OBJECT_UNLOAD,
    HOOK_ON_SYNC_OBJECT_UNLOAD,
    HOOK_ON_PAUSE_EXIT,
    HOOK_GET_STAR_COLLECTION_DIALOG,
    HOOK_ON_SET_CAMERA_MODE,
    HOOK_ON_OBJECT_RENDER,
    HOOK_ON_DEATH,
    HOOK_ON_PACKET_RECEIVE,
    HOOK_USE_ACT_SELECT,
    HOOK_ON_CHANGE_CAMERA_ANGLE,
    HOOK_ON_SCREEN_TRANSITION,
    HOOK_ALLOW_HAZARD_SURFACE,
    HOOK_ON_CHAT_MESSAGE,
    HOOK_OBJECT_SET_MODEL,
    HOOK_CHARACTER_SOUND,
    HOOK_BEFORE_SET_MARIO_ACTION,
    HOOK_JOINED_GAME,
    HOOK_ON_OBJECT_ANIM_UPDATE,
    HOOK_ON_DIALOG,
    HOOK_ON_EXIT,
    HOOK_DIALOG_SOUND,
    HOOK_ON_HUD_RENDER_BEHIND,
    HOOK_ON_COLLIDE_LEVEL_BOUNDS,
    HOOK_MIRROR_MARIO_RENDER,
    HOOK_OVERRIDE_PHYS_STEP_DEFACTO_SPEED,
    HOOK_ON_OBJECT_LOAD,
    HOOK_ON_PLAY_SOUND,
    HOOK_BEFORE_MARIO_HEALTH_UPDATE,
    HOOK_MAX,
};

static const char* LuaHookedEventTypeName[] = {
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
    "HOOK_ALLOW_INTERACT",
    "HOOK_ON_INTERACT",
    "HOOK_ON_LEVEL_INIT",
    "HOOK_ON_WARP",
    "HOOK_ON_SYNC_VALID",
    "HOOK_ON_OBJECT_UNLOAD",
    "HOOK_ON_SYNC_OBJECT_UNLOAD",
    "HOOK_ON_PAUSE_EXIT",
    "HOOK_GET_STAR_COLLECTION_DIALOG",
    "HOOK_ON_SET_CAMERA_MODE",
    "HOOK_ON_OBJECT_RENDER",
    "HOOK_ON_DEATH",
    "HOOK_ON_PACKET_RECEIVE",
    "HOOK_USE_ACT_SELECT",
    "HOOK_ON_CHANGE_CAMERA_ANGLE",
    "HOOK_ON_SCREEN_TRANSITION",
    "HOOK_ALLOW_HAZARD_SURFACE",
    "HOOK_ON_CHAT_MESSAGE",
    "HOOK_OBJECT_SET_MODEL",
    "HOOK_CHARACTER_SOUND",
    "HOOK_BEFORE_SET_MARIO_ACTION",
    "HOOK_JOINED_GAME",
    "HOOK_ON_OBJECT_ANIM_UPDATE",
    "HOOK_ON_DIALOG",
    "HOOK_ON_EXIT",
    "HOOK_DIALOG_SOUND",
    "HOOK_ON_HUD_RENDER_BEHIND",
    "HOOK_ON_COLLIDE_LEVEL_BOUNDS",
    "HOOK_MIRROR_MARIO_RENDER",
    "HOOK_OVERRIDE_PHYS_STEP_DEFACTO_SPEED",
    "HOOK_ON_OBJECT_LOAD",
    "HOOK_ON_PLAY_SOUND",
    "HOOK_BEFORE_MARIO_HEALTH_UPDATE",
    "HOOK_MAX"
};

enum LuaActionHookType {
    ACTION_HOOK_EVERY_FRAME,
    ACTION_HOOK_GRAVITY,
    ACTION_HOOK_MAX,
};

static const char* LuaActionHookTypeArgName[] = {
    "every_frame",
    "gravity",
    "max (dummy)",
};

extern u32 gLuaMarioActionIndex[];

int smlua_hook_custom_bhv(BehaviorScript *bhvScript, const char *bhvName);

void smlua_call_event_hooks(enum LuaHookedEventType hookType);
void smlua_call_event_on_hud_render(void (*resetFunc)(void));
void smlua_call_event_on_hud_render_behind(void (*resetFunc)(void));
void smlua_call_event_hooks_bool_param(enum LuaHookedEventType hookType, bool value);
void smlua_call_event_hooks_bool_param_ret_bool(enum LuaHookedEventType hookType, bool value, bool* returnValue);
void smlua_call_event_hooks_mario_param(enum LuaHookedEventType hookType, struct MarioState* m);
void smlua_call_event_hooks_mario_param_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m, bool* returnValue);
void smlua_call_event_hooks_mario_params(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2);
void smlua_call_event_hooks_mario_params_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2, bool* returnValue);
void smlua_call_event_hooks_interact_params(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType, bool interactValue);
void smlua_call_event_hooks_interact_params_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType, bool* returnValue);
void smlua_call_event_hooks_object_param(enum LuaHookedEventType hookType, struct Object* obj);
void smlua_call_event_hooks_object_model_param(enum LuaHookedEventType hookType, struct Object* obj, s32 modelID);
bool smlua_call_event_hooks_ret_int(enum LuaHookedEventType hookType, s32* returnValue);
void smlua_call_event_hooks_set_camera_mode_params(enum LuaHookedEventType hookType, struct Camera *c, s16 mode, s16 frames, bool* returnValue);
void smlua_call_event_hooks_int_params_ret_bool(enum LuaHookedEventType hookType, s16 param, bool* returnValue);
void smlua_call_event_hooks_int_params_ret_int(enum LuaHookedEventType hookType, s32 param, s32* returnValue);
void smlua_call_event_hooks_value_param(enum LuaHookedEventType hookType, int modIndex, int valueIndex);
void smlua_call_event_hooks_on_play_sound(enum LuaHookedEventType hookType, s32 soundBits, f32* pos, s32* returnValue);
void smlua_call_event_hooks_use_act_select(enum LuaHookedEventType hookType, int value, bool* foundHook, bool* returnValue);
void smlua_call_event_hooks_ret_bool(enum LuaHookedEventType hookType, bool* returnValue);
void smlua_call_event_hooks_on_chat_message(enum LuaHookedEventType hookType, struct MarioState* m, const char* message, bool* returnValue);
bool smlua_call_event_hooks_mario_character_sound_param_ret_int(enum LuaHookedEventType hookType, struct MarioState* m, enum CharacterSound characterSound, s32* returnValue);
void smlua_call_event_hooks_mario_action_params_ret_int(enum LuaHookedEventType hookType, struct MarioState *m, u32 action, u32* returnValue);
void smlua_call_event_hooks_mario_param_and_int_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m, s32 param, bool* returnValue);
bool smlua_call_event_hooks_mario_param_and_int_ret_int(enum LuaHookedEventType hookType, struct MarioState* m, s32 param, s32* returnValue);
bool smlua_call_event_hooks_mario_param_ret_float(enum LuaHookedEventType hookType, struct MarioState* m, f32* returnValue);
bool smlua_call_event_hooks_mario_param_and_int_and_int_ret_int(enum LuaHookedEventType hookType, struct MarioState* m, s32 param, u32 args, s32* returnValue);
void smlua_call_event_hooks_graph_node_object_and_int_param(enum LuaHookedEventType hookType, struct GraphNodeObject* node, s32 param);

enum BehaviorId smlua_get_original_behavior_id(const BehaviorScript* behavior);
const BehaviorScript* smlua_override_behavior(const BehaviorScript* behavior);
const BehaviorScript* smlua_get_hooked_behavior_from_id(enum BehaviorId id, bool returnOriginal);
bool smlua_is_behavior_hooked(const BehaviorScript *behavior);
bool smlua_call_behavior_hook(const BehaviorScript** behavior, struct Object* object, bool before);

int smlua_call_hook(lua_State* L, int nargs, int nresults, int errfunc, struct Mod* activeMod);
bool smlua_call_action_hook(enum LuaActionHookType hookType, struct MarioState* m, s32* returnValue);
u32 smlua_get_action_interaction_type(struct MarioState* m);

bool smlua_call_chat_command_hook(char* command);
void smlua_display_chat_commands(void);
char** smlua_get_chat_player_list(void);
char** smlua_get_chat_maincommands_list(void);
char** smlua_get_chat_subcommands_list(const char* maincommand);
bool smlua_maincommand_exists(const char* maincommand);
bool smlua_subcommand_exists(const char* maincommand, const char* subcommand);

void smlua_clear_hooks(void);
void smlua_bind_hooks(void);

#endif
