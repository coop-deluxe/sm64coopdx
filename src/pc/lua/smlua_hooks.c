#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "smlua.h"
#include "sm64.h"
#include "behavior_commands.h"
#include "pc/mods/mod.h"
#include "game/object_list_processor.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/crash_handler.h"
#include "game/hud.h"
#include "pc/debug_context.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"
#include "pc/network/socket/socket.h"
#include "pc/chat_commands.h"
#include "pc/pc_main.h"
#include "pc/djui/djui_lua_profiler.h"
#include "pc/djui/djui_panel.h"
#include "pc/configfile.h"
#include "pc/utils/misc.h"

#include "../mods/mods.h"
#include "game/print.h"
#include "gfx_dimensions.h"

#define MAX_HOOKED_REFERENCES 64
#define LUA_BEHAVIOR_FLAG (1 << 15)

u64* gBehaviorOffset = &gPcDebug.bhvOffset;

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    struct Mod* mod[MAX_HOOKED_REFERENCES];
    int count;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

int smlua_call_hook(lua_State* L, int nargs, int nresults, int errfunc, struct Mod* activeMod) {
    if (!gGameInited) { return 0; } // Don't call hooks while the game is booting

    struct Mod* prev = gLuaActiveMod;
    gLuaActiveMod = activeMod;
    gLuaLastHookMod = activeMod;
    gPcDebug.lastModRun = activeMod;

    lua_profiler_start_counter(activeMod);

    CTX_BEGIN(CTX_HOOK);
    int rc = smlua_pcall(L, nargs, nresults, errfunc);
    CTX_END(CTX_HOOK);

    lua_profiler_stop_counter(activeMod);

    gLuaActiveMod = prev;
    return rc;
}

int smlua_hook_event(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    u16 hookType = smlua_to_integer(L, -2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Invalid hook type given to hook_event(): %d", hookType);
        return 0;
    }

    if (hookType >= HOOK_MAX) {
        LOG_LUA_LINE("Hook Type: %d exceeds max!", hookType);
        return 0;
    }

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    if (hook->count >= MAX_HOOKED_REFERENCES) {
        LOG_LUA_LINE("Hook Type: %s exceeded maximum references!", LuaHookedEventTypeName[hookType]);
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Tried to hook undefined function to '%s'", LuaHookedEventTypeName[hookType]);
        return 0;
    }

    hook->reference[hook->count] = ref;
    hook->mod[hook->count] = gLuaActiveMod;
    hook->count++;

    return 1;
}

void smlua_call_event_hooks(enum LuaHookedEventType hookType) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the event_hook callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_on_hud_render(void (*resetFunc)(void)) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    if (resetFunc) { resetFunc(); }

    struct LuaHookedEvent* hook = &sHookedEvents[HOOK_ON_HUD_RENDER];
    for (int i = 0; i < hook->count; i++) {
        // support deprecated render behind hud
        if (hook->mod[i]->renderBehindHud) { continue; }

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the event_hook callback: %u", HOOK_ON_HUD_RENDER);
        }
        if (resetFunc) { resetFunc(); }
    }
}

void smlua_call_event_on_hud_render_behind(void (*resetFunc)(void)) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    if (resetFunc) { resetFunc(); }

    struct LuaHookedEvent* hook = &sHookedEvents[HOOK_ON_HUD_RENDER_BEHIND];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the event_hook callback: %u", HOOK_ON_HUD_RENDER_BEHIND);
        }
        if (resetFunc) { resetFunc(); }
    }

    // support deprecated render behind hud
    hook = &sHookedEvents[HOOK_ON_HUD_RENDER];
    for (int i = 0; i < hook->count; i++) {
        // support deprecated render behind hud
        if (!hook->mod[i]->renderBehindHud) { continue; }

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the event_hook callback: %u", HOOK_ON_HUD_RENDER);
        }
        if (resetFunc) { resetFunc(); }
    }

}

void smlua_call_event_hooks_bool_param(enum LuaHookedEventType hookType, bool value) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push value
        lua_pushboolean(L, value);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_bool_param_ret_bool(enum LuaHookedEventType hookType, bool value, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push value
        lua_pushboolean(L, value);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_mario_param(enum LuaHookedEventType hookType, struct MarioState* m) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_mario_param_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_mario_params(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2, u32 interaction) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m1->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m2->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push interaction
        lua_pushinteger(L, interaction);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_mario_params_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2, u32 interaction, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m1->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m2->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push interaction
        lua_pushinteger(L, interaction);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_interact_params(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType, bool interactValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push object
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push interact type
        lua_pushinteger(L, interactType);

        // push interact value
        lua_pushboolean(L, interactValue);

        // call the callback
        if (0 != smlua_call_hook(L, 4, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_interact_params_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push object
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push interact type
        lua_pushinteger(L, interactType);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_interact_params_no_ret(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push object
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push interact type
        lua_pushinteger(L, interactType);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_object_param(enum LuaHookedEventType hookType, struct Object* obj) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push object
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_object_model_param(enum LuaHookedEventType hookType, struct Object* obj, s32 modelID) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push params
        smlua_push_object(L, LOT_OBJECT, obj, NULL);
        lua_pushinteger(L, modelID);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

bool smlua_call_event_hooks_ret_int(enum LuaHookedEventType hookType, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
        }
        lua_settop(L, prevTop);
        return true;
    }
    return false;
}

void smlua_call_event_hooks_ret_bool(enum LuaHookedEventType hookType, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    *returnValue = true;

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN && *returnValue) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_network_player_param(enum LuaHookedEventType hookType, struct NetworkPlayer* np) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gNetworkPlayers");
        lua_pushinteger(L, np->localIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_set_camera_mode_params(enum LuaHookedEventType hookType, struct Camera *c, s16 mode, s16 frames, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    *returnValue = true;

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push params
        smlua_push_object(L, LOT_CAMERA, c, NULL);
        lua_pushinteger(L, mode);
        lua_pushinteger(L, frames);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN && *returnValue) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_int_params_ret_bool(enum LuaHookedEventType hookType, s16 param, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    *returnValue = true;

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push params
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_int_params_ret_int(enum LuaHookedEventType hookType, s32 param, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push params
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return;
        } else {
            lua_settop(L, prevTop);
        }
    }
}

void smlua_call_event_hooks_int_params_ret_string(enum LuaHookedEventType hookType, s32 param, char** returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push params
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TSTRING) {
            *returnValue = (char *)smlua_to_string(L, -1);
            lua_settop(L, prevTop);
            return;
        } else {
            lua_settop(L, prevTop);
        }
    }
}

void smlua_call_event_hooks_value_param(enum LuaHookedEventType hookType, int modIndex, int valueIndex) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        if (hook->mod[i]->index != modIndex) { continue; }
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push value
        lua_pushvalue(L, valueIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_on_play_sound(enum LuaHookedEventType hookType, s32 soundBits, f32* pos, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push sound bits
        lua_pushinteger(L, soundBits);

        // push vec3f
        lua_newtable(L);
        int valTableIndex = lua_gettop(L);

        lua_pushstring(L, "x");
        lua_pushnumber(L, pos[0]);
        lua_settable(L, valTableIndex);

        lua_pushstring(L, "y");
        lua_pushnumber(L, pos[1]);
        lua_settable(L, valTableIndex);

        lua_pushstring(L, "z");
        lua_pushnumber(L, pos[2]);
        lua_settable(L, valTableIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return;
        } else {
            lua_settop(L, prevTop);
        }
    }
}

void smlua_call_event_hooks_on_seq_load(enum LuaHookedEventType hookType, u32 player, u32 seqId, s32 loadAsync, s16* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);
        lua_pushinteger(L, player);
        lua_pushinteger(L, seqId);
        lua_pushinteger(L, loadAsync);

        // Call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // Output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return;
        } else {
            lua_settop(L, prevTop);
        }
    }
}

void smlua_call_event_hooks_use_act_select(enum LuaHookedEventType hookType, int value, bool* foundHook, bool* returnValue) {
    lua_State* L = gLuaState;
    *foundHook = false;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push value
        lua_pushinteger(L, value);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *foundHook = true;
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_on_chat_message(enum LuaHookedEventType hookType, struct MarioState* m, const char* message, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push the string
        lua_pushstring(L, message);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

bool smlua_call_event_hooks_mario_character_sound_param_ret_int(enum LuaHookedEventType hookType, struct MarioState* m, enum CharacterSound characterSound, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push character sound
        lua_pushinteger(L, characterSound);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        } else {
            lua_settop(L, prevTop);
        }
    }
    return false;
}

void smlua_call_event_hooks_mario_action_params_ret_int(enum LuaHookedEventType hookType, struct MarioState *m, u32 action, u32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push action
        lua_pushinteger(L, action);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

void smlua_call_event_hooks_mario_param_and_int_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m, s32 param, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push param
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -1);
        }
        lua_settop(L, prevTop);
    }
}

bool smlua_call_event_hooks_mario_param_and_int_ret_int(enum LuaHookedEventType hookType, struct MarioState* m, s32 param, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push param
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }
        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_mario_param_ret_float(enum LuaHookedEventType hookType, struct MarioState* m, f32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_number(L, -1);
        }
        lua_settop(L, prevTop);

        return true;
    }

    return false;
}

bool smlua_call_event_hooks_mario_param_and_int_and_int_ret_int(enum LuaHookedEventType hookType, struct MarioState* m, s32 param, u32 args, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push param
        lua_pushinteger(L, param);

        // push args
        lua_pushinteger(L, args);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return value
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *returnValue = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }
        lua_settop(L, prevTop);
    }
    return false;
}

void smlua_call_event_hooks_graph_node_object_and_int_param(enum LuaHookedEventType hookType, struct GraphNodeObject* node, s32 param) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push graph node object
        smlua_push_object(L, LOT_GRAPHNODEOBJECT, node, NULL);

        // push param
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_graph_node_and_int_param(enum LuaHookedEventType hookType, struct GraphNode* node, s16 matIndex) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push graph node
        smlua_push_object(L, LOT_GRAPHNODE, node, NULL);

        // push mat index
        lua_pushinteger(L, matIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

const char *smlua_call_event_hooks_int_ret_bool_and_string(enum LuaHookedEventType hookType, s32 param, bool* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return NULL; }
    *returnValue = true;
    const char *retString = NULL;

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push param
        lua_pushinteger(L, param);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 2, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }

        // output the return values
        if (lua_type(L, -2) == LUA_TBOOLEAN) {
            *returnValue = smlua_to_boolean(L, -2);
        }
        if (lua_type(L, -1) == LUA_TSTRING) {
            retString = smlua_to_string(L, -1);
            lua_settop(L, prevTop);
            return retString;
        }
        lua_settop(L, prevTop);
    }
    return NULL;
}

void smlua_call_event_hooks_string_param(enum LuaHookedEventType hookType, const char* string) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push string
        lua_pushstring(L, string);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

  ////////////////////
 // hooked actions //
////////////////////

struct LuaHookedMarioAction {
    u32 action;
    u32 interactionType;
    int actionHookRefs[ACTION_HOOK_MAX];
    struct Mod* mod;
};

#define MAX_HOOKED_ACTIONS (ACT_NUM_GROUPS * ACT_NUM_ACTIONS_PER_GROUP)

static struct LuaHookedMarioAction sHookedMarioActions[MAX_HOOKED_ACTIONS] = { 0 };
static int sHookedMarioActionsCount = 0;
u32 gLuaMarioActionIndex[ACT_NUM_GROUPS] = { 0 };

int smlua_hook_mario_action(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_range(L, 2, 3)) { return 0; }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_mario_action() can only be called on load.");
        return 0;
    }

    int paramCount = lua_gettop(L);

    if (sHookedMarioActionsCount >= MAX_HOOKED_ACTIONS) {
        LOG_LUA_LINE("Hooked mario actions exceeded maximum references!");
        return 0;
    }

    lua_Integer action = smlua_to_integer(L, 1);
    if (action == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook Action: tried to hook invalid action: %lld, %u", action, gSmLuaConvertSuccess);
        return 0;
    }

    int secondParamType = lua_type(L, 2);
    bool oldApi = secondParamType == LUA_TFUNCTION;

    if (!oldApi && secondParamType != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_hook_mario_action received improper type '%s'", luaL_typename(L, 2));
        return 0;
    }

    lua_Integer interactionType = 0;
    if (paramCount >= 3) {
        interactionType = smlua_to_integer(L, 3);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Hook Action: tried to hook invalid interactionType: %lld, %u", interactionType, gSmLuaConvertSuccess);
            return 0;
        }
    }
    interactionType |= (1 << 31); /* INT_LUA */

    struct LuaHookedMarioAction* hooked = &sHookedMarioActions[sHookedMarioActionsCount];

    // Support calling the function with just one function corresponding to the "every frame" hook instead of a full
    // table with all hooks
    if (oldApi) {
        for (int i = 0; i < ACTION_HOOK_MAX; i++) {
            hooked->actionHookRefs[i] = LUA_NOREF;
        }

        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);

        if (ref == -1) {
            LOG_LUA_LINE("Hook Action: %lld tried to hook undefined function", action);
            return 0;
        }

        hooked->actionHookRefs[ACTION_HOOK_EVERY_FRAME] = ref;
    }
    else {
        for (int i = 0; i < ACTION_HOOK_MAX; i++) {
            lua_pushstring(L, LuaActionHookTypeArgName[i]);

            if (lua_gettable(L, 2) == LUA_TNIL) {
                hooked->actionHookRefs[i] = LUA_NOREF;
            } else {
                int ref = luaL_ref(L, LUA_REGISTRYINDEX);

                if (ref == -1) {
                    LOG_LUA_LINE("Hook Action: %lld tried to hook undefined function", action);
                    return 0;
                }

                hooked->actionHookRefs[i] = ref;
            }
        }
    }

    hooked->action = action;
    hooked->interactionType = interactionType;
    hooked->mod = gLuaActiveMod;

    sHookedMarioActionsCount++;
    return 1;
}

bool smlua_call_action_hook(enum LuaActionHookType hookType, struct MarioState* m, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }

    //TODO GAG: Set up things such that O(n) check isn't performed on every action hook? Maybe in MarioState?
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        struct LuaHookedMarioAction* hook = &sHookedMarioActions[i];
        if (hook->action == m->action && hook->actionHookRefs[hookType] != LUA_NOREF) {
            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, hook->actionHookRefs[hookType]);

            // push mario state
            lua_getglobal(L, "gMarioStates");
            lua_pushinteger(L, m->playerIndex);
            lua_gettable(L, -2);
            lua_remove(L, -2);

            // call the callback
            if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod)) {
                LOG_LUA("Failed to call the action callback: %u", m->action);
                continue;
            }

            // output the return value
            *returnValue = false;
            if (lua_type(L, -1) == LUA_TBOOLEAN || lua_type(L, -1) == LUA_TNUMBER) {
                *returnValue = smlua_to_integer(L, -1);
            }
            lua_pop(L, 1);

            return true;
        }
    }

    return false;
}

u32 smlua_get_action_interaction_type(struct MarioState* m) {
    u32 interactionType = 0;
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        if (sHookedMarioActions[i].action == m->action) {
            interactionType |= sHookedMarioActions[i].interactionType;
        }
    }
    return interactionType;
}

  //////////////////////
 // hooked behaviors //
//////////////////////

struct LuaHookedBehavior {
    u32 behaviorId;
    u32 overrideId;
    u32 originalId;
    BehaviorScript *behavior;
    const BehaviorScript* originalBehavior;
    const char* bhvName;
    int initReference;
    int loopReference;
    bool replace;
    bool luaBehavior;
    struct Mod* mod;
};

#define MAX_HOOKED_BEHAVIORS 1024

static struct LuaHookedBehavior sHookedBehaviors[MAX_HOOKED_BEHAVIORS] = { 0 };
static int sHookedBehaviorsCount = 0;

enum BehaviorId smlua_get_original_behavior_id(const BehaviorScript* behavior) {
    enum BehaviorId id = get_id_from_behavior(behavior);
    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];
        if (hooked->behavior == behavior) {
            id = hooked->overrideId;
        }
    }
    return id;
}

const BehaviorScript* smlua_override_behavior(const BehaviorScript *behavior) {
    lua_State *L = gLuaState;
    if (L == NULL) { return behavior; }

    enum BehaviorId id = get_id_from_behavior(behavior);
    const BehaviorScript *hookedBehavior = smlua_get_hooked_behavior_from_id(id, false);
    if (hookedBehavior != NULL) { return hookedBehavior; }
    return behavior + *gBehaviorOffset;
}

const BehaviorScript* smlua_get_hooked_behavior_from_id(enum BehaviorId id, bool returnOriginal) {
    lua_State *L = gLuaState;
    if (L == NULL) { return NULL; }

    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];
        if (hooked->behaviorId != id && hooked->overrideId != id) { continue; }
        if (returnOriginal && !hooked->replace) { return hooked->originalBehavior; }
        return hooked->behavior;
    }
    return NULL;
}

bool smlua_is_behavior_hooked(const BehaviorScript *behavior) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    enum BehaviorId id = get_id_from_behavior(behavior);
    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior *hooked = &sHookedBehaviors[i];
        if (hooked->behaviorId != id && hooked->overrideId != id) { continue; }
        return hooked->luaBehavior;
    }

    return false;
}

const char* smlua_get_name_from_hooked_behavior_id(enum BehaviorId id) {
    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior *hooked = &sHookedBehaviors[i];
        if (hooked->behaviorId != id && hooked->overrideId != id) { continue; }
        return hooked->bhvName;
    }
    return NULL;
}

int smlua_hook_custom_bhv(BehaviorScript *bhvScript, const char *bhvName) {
    if (sHookedBehaviorsCount >= MAX_HOOKED_BEHAVIORS) {
        LOG_ERROR("Hooked behaviors exceeded maximum references!");
        return 0;
    }

    u32 originalBehaviorId = get_id_from_behavior(bhvScript);
    u8 newBehavior = originalBehaviorId >= id_bhv_max_count;

    struct LuaHookedBehavior *hooked = &sHookedBehaviors[sHookedBehaviorsCount];
    u16 customBehaviorId = (sHookedBehaviorsCount & 0xFFFF) | LUA_BEHAVIOR_FLAG;
    hooked->behavior = bhvScript;
    hooked->behavior[1] = (BehaviorScript)BC_B0H(0x39, customBehaviorId); // This is ID(customBehaviorId)
    hooked->behaviorId = customBehaviorId;
    hooked->overrideId = newBehavior ? customBehaviorId : originalBehaviorId;
    hooked->originalId = originalBehaviorId;
    hooked->originalBehavior = newBehavior ? bhvScript : get_behavior_from_id(originalBehaviorId);
    hooked->initReference = 0;
    hooked->loopReference = 0;
    hooked->replace = true;
    hooked->luaBehavior = false;
    hooked->mod = gLuaActiveMod;

    sHookedBehaviorsCount++;

    // We want to push the behavior into the global LUA state. So mods can access it.
    // It's also used for some things that would normally access a LUA behavior instead.
    lua_State* L = gLuaState;
    if (L != NULL) {
        lua_pushinteger(L, customBehaviorId);
        lua_setglobal(L, bhvName);
        LOG_INFO("Registered custom behavior: 0x%04hX - %s", customBehaviorId, bhvName);
    }

    return 1;
}

int smlua_hook_behavior(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_range(L, 5, 6)) { return 0; }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_behavior() can only be called on load.");
        return 0;
    }

    int paramCount = lua_gettop(L);

    if (sHookedBehaviorsCount >= MAX_HOOKED_BEHAVIORS) {
        LOG_LUA_LINE("Hooked behaviors exceeded maximum references!");
        return 0;
    }

    bool noOverrideId = (lua_type(L, 1) == LUA_TNIL);
    gSmLuaConvertSuccess = true;
    lua_Integer overrideBehaviorId = noOverrideId ? 0xFFFFFF : smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook behavior: tried to override invalid behavior: %lld, %u", overrideBehaviorId, gSmLuaConvertSuccess);
        return 0;
    }

    lua_Integer objectList = smlua_to_integer(L, 2);
    if (objectList <= 0 || objectList >= NUM_OBJ_LISTS || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook behavior: tried use invalid object list: %lld, %u", objectList, gSmLuaConvertSuccess);
        return 0;
    }

    bool replaceBehavior = smlua_to_boolean(L, 3);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook behavior: could not parse replaceBehavior");
        return 0;
    }
    const BehaviorScript* originalBehavior = noOverrideId ? NULL : get_behavior_from_id(overrideBehaviorId);
    if (originalBehavior == NULL) {
        replaceBehavior = true;
    }

    int initReference = 0;
    int initReferenceType = lua_type(L, 4);
    if (initReferenceType == LUA_TNIL) {
        // nothing
    } else if (initReferenceType == LUA_TFUNCTION) {
        // get reference
        lua_pushvalue(L, 4);
        initReference = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
        LOG_LUA_LINE("Hook behavior: tried to reference non-function for init");
        return 0;
    }

    int loopReference = 0;
    int loopReferenceType = lua_type(L, 5);
    if (loopReferenceType == LUA_TNIL) {
        // nothing
    } else if (loopReferenceType == LUA_TFUNCTION) {
        // get reference
        lua_pushvalue(L, 5);
        loopReference = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
        LOG_LUA_LINE("Hook behavior: tried to reference non-function for loop");
        return 0;
    }

    const char *bhvName = NULL;
    if (paramCount >= 6) {
        int bhvNameType = lua_type(L, 6);
        if (bhvNameType == LUA_TNIL) {
            // nothing
        } else if (bhvNameType == LUA_TSTRING) {
            bhvName = smlua_to_string(L, 6);
            if (!bhvName || !gSmLuaConvertSuccess) {
                LOG_LUA_LINE("Hook behavior: could not parse bhvName");
                return 0;
            }
        } else {
            LOG_LUA_LINE("Hook behavior: invalid type passed for argument bhvName: %u", bhvNameType);
            return 0;
        }
    }

    // If not provided, generate generic behavior name: bhv<ModName>Custom<Index>
    // - <ModName> is the mod name in CamelCase format, alphanumeric chars only
    // - <Index> is in 3-digit numeric format, ranged from 001 to 256
    // For example, the 4th unnamed behavior of the mod "my-great_MOD" will be named "bhvMyGreatMODCustom004"
    if (!bhvName) {
        static char sGenericBhvName[MOD_NAME_MAX_LENGTH + 16];
        s32 i = 3;
        snprintf(sGenericBhvName, 4, "bhv");
        for (char caps = TRUE, *c = gLuaLoadingMod->name; *c && i < MOD_NAME_MAX_LENGTH + 3; ++c) {
            if ('0' <= *c && *c <= '9') {
                sGenericBhvName[i++] = *c;
                caps = TRUE;
            } else if ('A' <= *c && *c <= 'Z') {
                sGenericBhvName[i++] = *c;
                caps = FALSE;
            } else if ('a' <= *c && *c <= 'z') {
                sGenericBhvName[i++] = *c + (caps ? 'A' - 'a' : 0);
                caps = FALSE;
            } else {
                caps = TRUE;
            }
        }
        snprintf(sGenericBhvName + i, 12, "Custom%03u", (u32) (gLuaLoadingMod->customBehaviorIndex++) + 1);
        bhvName = sGenericBhvName;
    }

    struct LuaHookedBehavior* hooked = &sHookedBehaviors[sHookedBehaviorsCount];
    u16 customBehaviorId = (sHookedBehaviorsCount & 0xFFFF) | LUA_BEHAVIOR_FLAG;
    hooked->behavior = calloc(4, sizeof(BehaviorScript));
    hooked->behavior[0] = (BehaviorScript)BC_BB(0x00, objectList); // This is BEGIN(objectList)
    hooked->behavior[1] = (BehaviorScript)BC_B0H(0x39, customBehaviorId); // This is ID(customBehaviorId)
    hooked->behavior[2] = (BehaviorScript)BC_B(0x0A); // This is BREAK()
    hooked->behavior[3] = (BehaviorScript)BC_B(0x0A); // This is BREAK()
    hooked->behaviorId = customBehaviorId;
    hooked->overrideId = noOverrideId ? customBehaviorId : overrideBehaviorId;
    hooked->originalId = customBehaviorId; // For LUA behaviors. The only behavior id they have IS their custom one.
    hooked->originalBehavior = originalBehavior ? originalBehavior : hooked->behavior;
    hooked->bhvName = bhvName;
    hooked->initReference = initReference;
    hooked->loopReference = loopReference;
    hooked->replace = replaceBehavior;
    hooked->luaBehavior = true;
    hooked->mod = gLuaActiveMod;

    sHookedBehaviorsCount++;

    // We want to push the behavior into the global LUA state. So mods can access it.
    // It's also used for some things that would normally access a LUA behavior instead.
    lua_pushinteger(L, customBehaviorId);
    lua_setglobal(L, bhvName);
    LOG_INFO("Registered custom behavior: 0x%04hX - %s", customBehaviorId, bhvName);

    // return behavior ID
    lua_pushinteger(L, customBehaviorId);

    return 1;
}

bool smlua_call_behavior_hook(const BehaviorScript** behavior, struct Object* object, bool before) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];

        // find behavior
        if (object->behavior != hooked->behavior) {
            continue;
        }

        // Figure out whether to run before or after
        if (before && !hooked->replace) {
            return false;
        }
        if (!before && hooked->replace) {
            return false;
        }

        // This behavior doesn't call it's LUA functions in this manner. It actually uses the normal behavior
        // system.
        if (!hooked->luaBehavior) {
            return false;
        }

        // retrieve and remember first run
        bool firstRun = (object->curBhvCommand == hooked->originalBehavior) || (object->curBhvCommand == hooked->behavior);
        if (firstRun && hooked->replace) { *behavior = &hooked->behavior[1]; }

        // get function and null check it
        int reference = firstRun ? hooked->initReference : hooked->loopReference;
        if (reference == 0) {
            return true;
        }

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, reference);

        // push object
        smlua_push_object(L, LOT_OBJECT, object, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hooked->mod)) {
            LOG_LUA("Failed to call the behavior callback: %u", hooked->behaviorId);
            return true;
        }

        return hooked->replace;
    }

    return false;
}


  /////////////////////////
 // hooked chat command //
/////////////////////////

struct LuaHookedChatCommand {
    char* command;
    char* description;
    int reference;
    struct Mod* mod;
};

#define MAX_HOOKED_CHAT_COMMANDS 512

static struct LuaHookedChatCommand sHookedChatCommands[MAX_HOOKED_CHAT_COMMANDS] = { 0 };
static int sHookedChatCommandsCount = 0;

int smlua_hook_chat_command(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_chat_command() can only be called on load.");
        return 0;
    }

    if (sHookedChatCommandsCount >= MAX_HOOKED_CHAT_COMMANDS) {
        LOG_LUA_LINE("Hooked chat command exceeded maximum references!");
        return 0;
    }

    const char* command = smlua_to_string(L, 1);
    if (command == NULL || strlen(command) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook chat command: tried to hook invalid command");
        return 0;
    }

    const char* description = smlua_to_string(L, 2);
    if (description == NULL || strlen(description) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook chat command: tried to hook invalid description");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook chat command: tried to hook undefined function '%s'", command);
        return 0;
    }

    struct LuaHookedChatCommand* hooked = &sHookedChatCommands[sHookedChatCommandsCount];
    hooked->command = strdup(command);
    hooked->description = strdup(description);
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;

    sHookedChatCommandsCount++;
    return 1;
}

int smlua_update_chat_command_description(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    const char* command = smlua_to_string(L, 1);
    if (command == NULL || strlen(command) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update chat command: tried to update invalid command");
        return 0;
    }

    const char* description = smlua_to_string(L, 2);
    if (description == NULL || strlen(description) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update chat command: tried to update invalid description");
        return 0;
    }

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        if (!strcmp(hook->command, command)) {
            if (hook->description) {
                free(hook->description);
            }
            hook->description = strdup(description);
            return 1;
        }
    }

    LOG_LUA_LINE("Update chat command: could not find command to update");
    return 0;
}

bool smlua_call_chat_command_hook(char* command) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        size_t commandLength = strlen(hook->command);
        for (size_t j = 0; j < commandLength; j++) {
            if (hook->command[j] != command[j + 1]) {
                goto NEXT_HOOK;
            }
        }

        char* params = &command[commandLength + 1];
        if (*params != '\0' && *params != ' ') {
            goto NEXT_HOOK;
        }
        if (*params == ' ') {
            params++;
        }

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference);

        // push parameter
        lua_pushstring(L, params);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod)) {
            LOG_LUA("Failed to call the chat command callback: %s", command);
            continue;
        }

        // output the return value
        bool returnValue = false;
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            returnValue = smlua_to_boolean(L, -1);
        }
        lua_pop(L, 1);

        if (!gSmLuaConvertSuccess) { return false; }

        return returnValue;

NEXT_HOOK:;
    }

    return false;
}

void smlua_display_chat_commands(void) {
    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        char msg[256] = { 0 };
        snprintf(msg, 256, "/%s %s", hook->command, hook->description);
        djui_chat_message_create(msg);
    }
}

bool is_valid_subcommand(const char* start, const char* end) {
    for (const char* ptr = start; ptr < end; ptr++) {
        if (isspace(*ptr) || *ptr == '\0') {
            return false;
        }
    }
    return true;
}

s32 sort_alphabetically(const void *a, const void *b) {
    const char* strA = *(const char**)a;
    const char* strB = *(const char**)b;

    s32 cmpResult = strcasecmp(strA, strB);

    if (cmpResult == 0) {
        return strcmp(strA, strB);
    }

    return cmpResult;
}

char** smlua_get_chat_player_list(void) {
    char* playerNames[MAX_PLAYERS] = { NULL };
    s32 playerCount = 0;

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) continue;

        bool isDuplicate = false;
        for (s32 j = 0; j < playerCount; j++) {
            if (strcmp(playerNames[j], np->name) == 0) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            playerNames[playerCount++] = np->name;
        }
    }

    qsort(playerNames, playerCount, sizeof(char*), sort_alphabetically);

    char** sortedPlayers = (char**) malloc((playerCount + 1) * sizeof(char*));
    for (s32 i = 0; i < playerCount; i++) {
        sortedPlayers[i] = strdup(playerNames[i]);
    }
    sortedPlayers[playerCount] = NULL;
    return sortedPlayers;
}

char** smlua_get_chat_maincommands_list(void) {
#if defined(DEVELOPMENT)
    s32 defaultCmdsCount = 11;
    static char* defaultCmds[] = {"players", "kick", "ban", "permban", "moderator", "help", "?", "warp", "lua", "luaf", NULL};
#else
    s32 defaultCmdsCount = 8;
    static char* defaultCmds[] = {"players", "kick", "ban", "permban", "moderator", "help", "?", NULL};
#endif
    s32 defaultCmdsCountNew = 0;
    for (s32 i = 0; i < defaultCmdsCount; i++) {
        if (defaultCmds[i] != NULL) {
            defaultCmdsCountNew++;
        } else if (gServerSettings.nametags && defaultCmds[i] == NULL) {
            defaultCmds[i] = "nametags";
            defaultCmdsCountNew++;
            break;
        }
    }
    char** commands = (char**) malloc((sHookedChatCommandsCount + defaultCmdsCountNew + 1) * sizeof(char*));
    for (s32 i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        commands[i] = strdup(hook->command);
    }
    for (s32 i = 0; i < defaultCmdsCount; i++) {
        if (defaultCmds[i] != NULL) {
            commands[sHookedChatCommandsCount + i] = strdup(defaultCmds[i]);
        }
    }
    commands[sHookedChatCommandsCount + defaultCmdsCountNew] = NULL;
    qsort(commands, sHookedChatCommandsCount + defaultCmdsCountNew, sizeof(char*), sort_alphabetically);
    return commands;
}

char** smlua_get_chat_subcommands_list(const char* maincommand) {
    if (gServerSettings.nametags && strcmp(maincommand, "nametags") == 0) {
        s32 count = 2;
        char** subcommands = (char**) malloc((count + 1) * sizeof(char*));
        subcommands[0] = strdup("show-tag");
        subcommands[1] = strdup("show-health");
        subcommands[2] = NULL;
        return subcommands;
    }

    for (s32 i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        if (strcmp(hook->command, maincommand) == 0) {
            char* noColorsDesc = str_remove_color_codes(hook->description);
            char* startSubcommands = strstr(noColorsDesc, "[");
            char* endSubcommands = strstr(noColorsDesc, "]");

            if (startSubcommands && endSubcommands && is_valid_subcommand(startSubcommands + 1, endSubcommands)) {
                *endSubcommands = '\0';
                char* subcommandsStr = strdup(startSubcommands + 1);

                s32 count = 1;
                for (s32 j = 0; subcommandsStr[j]; j++) {
                    if (subcommandsStr[j] == '|') count++;
                }

                char** subcommands = (char**) malloc((count + 1) * sizeof(char*));
                char* token = strtok(subcommandsStr, "|");
                s32 index = 0;
                while (token) {
                    subcommands[index++] = strdup(token);
                    token = strtok(NULL, "|");
                }
                subcommands[index] = NULL;

                qsort(subcommands, count, sizeof(char*), sort_alphabetically);

                free(noColorsDesc);
                free(subcommandsStr);
                return subcommands;
            }
            free(noColorsDesc);
        }
    }
    return NULL;
}

bool smlua_maincommand_exists(const char* maincommand) {
    char** commands = smlua_get_chat_maincommands_list();
    bool result = false;

    s32 i = 0;
    while (commands[i] != NULL) {
        if (strcmp(commands[i], maincommand) == 0) {
            result = true;
            break;
        }
        i++;
    }

    for (s32 j = 0; commands[j] != NULL; j++) {
        free(commands[j]);
    }
    free(commands);

    return result;
}

bool smlua_subcommand_exists(const char* maincommand, const char* subcommand) {
    char** subcommands = smlua_get_chat_subcommands_list(maincommand);

    if (subcommands == NULL) {
        return false;
    }

    bool result = false;
    s32 i = 0;
    while (subcommands[i] != NULL) {
        if (strcmp(subcommands[i], subcommand) == 0) {
            result = true;
            break;
        }
        i++;
    }

    for (s32 j = 0; subcommands[j] != NULL; j++) {
        free(subcommands[j]);
    }
    free(subcommands);

    return result;
}

  //////////////////////////////
 // hooked sync table change //
//////////////////////////////

int smlua_hook_on_sync_table_change(lua_State* L) {
    LUA_STACK_CHECK_BEGIN();
    if (L == NULL) { return 0; }
    if(!smlua_functions_valid_param_count(L, 4)) { return 0; }

    int syncTableIndex = 1;
    int keyIndex = 2;
    int tagIndex = 3;
    int funcIndex = 4;

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_on_sync_table_change() can only be called on load.");
        return 0;
    }

    if (lua_type(L, syncTableIndex) != LUA_TTABLE) {
        LOG_LUA_LINE("Tried to attach a non-table to hook_on_sync_table_change: %s", luaL_typename(L, syncTableIndex));
        return 0;
    }

    if (lua_type(L, funcIndex) != LUA_TFUNCTION) {
        LOG_LUA_LINE("Tried to attach a non-function to hook_on_sync_table_change: %s", luaL_typename(L, funcIndex));
        return 0;
    }

    // set hook's table
    lua_newtable(L);
    int valTableIndex = lua_gettop(L);

    lua_pushstring(L, "_func");
    lua_pushvalue(L, funcIndex);
    lua_settable(L, valTableIndex);

    lua_pushstring(L, "_tag");
    lua_pushvalue(L, tagIndex);
    lua_settable(L, valTableIndex);

    // get _hook_on_changed
    lua_pushstring(L, "_hook_on_changed");
    lua_rawget(L, syncTableIndex);
    int hookOnChangedIndex = lua_gettop(L);

    // attach
    lua_pushvalue(L, keyIndex);
    lua_pushvalue(L, valTableIndex);
    lua_settable(L, hookOnChangedIndex);

    // clean up
    lua_remove(L, hookOnChangedIndex);
    lua_remove(L, valTableIndex);

    LUA_STACK_CHECK_END();
    return 1;
}


  ////////////////////////////
 // hooked mod menu button //
////////////////////////////

struct LuaHookedModMenuElement gHookedModMenuElements[MAX_HOOKED_MOD_MENU_ELEMENTS] = { 0 };
int gHookedModMenuElementsCount = 0;

int smlua_hook_mod_menu_text(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_TEXT;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = 0;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = 0;
    hooked->mod = gLuaActiveMod;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_button(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_BUTTON;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = 0;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_checkbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    bool defaultValue = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_CHECKBOX;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = defaultValue;
    hooked->uintValue = 0;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_slider(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 5)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 defaultValue = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 sliderMin = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 sliderMax = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_SLIDER;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = defaultValue;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = sliderMin;
    hooked->sliderMax = sliderMax;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_inputbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 4)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    const char* defaultValue = smlua_to_string(L, 2);
    if (defaultValue == NULL || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 length = smlua_to_integer(L, 3);
    length = MIN(length, 256);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_INPUTBOX;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = 0;
    snprintf(hooked->stringValue, 256, "%s", defaultValue);
    hooked->length = length;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_update_mod_menu_element_name(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    const char* name = smlua_to_string(L, 2);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid name");
        return 0;
    }

    snprintf(gHookedModMenuElements[index].name, 64, "%s", name);
    return 1;
}

int smlua_update_mod_menu_element_checkbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    if (gHookedModMenuElements[index].element != MOD_MENU_ELEMENT_CHECKBOX) {
        LOG_LUA_LINE("Update mod menu element: element is not a checkbox.");
        return 0;
    }

    bool boolValue = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    gHookedModMenuElements[index].boolValue = boolValue;
    return 1;
}

int smlua_update_mod_menu_element_slider(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    if (gHookedModMenuElements[index].element != MOD_MENU_ELEMENT_SLIDER) {
        LOG_LUA_LINE("Update mod menu element: element is not a slider.");
        return 0;
    }

    u32 uintValue = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    gHookedModMenuElements[index].uintValue = uintValue;
    return 1;
}

int smlua_update_mod_menu_element_inputbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    if (gHookedModMenuElements[index].element != MOD_MENU_ELEMENT_INPUTBOX) {
        LOG_LUA_LINE("Update mod menu element: element is not an inputbox.");
        return 0;
    }

    const char* stringValue = smlua_to_string(L, 2);
    if (stringValue == NULL || strlen(stringValue) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element string");
        return 0;
    }

    snprintf(gHookedModMenuElements[index].stringValue, gHookedModMenuElements[index].length, "%s", stringValue);
    return 1;
}

void smlua_call_mod_menu_element_hook(struct LuaHookedModMenuElement* hooked, int index) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }

    // push the callback onto the stack
    lua_rawgeti(L, LUA_REGISTRYINDEX, hooked->reference);

    // push parameter
    u8 params = 2;
    lua_pushinteger(L, index);
    switch (hooked->element) {
        case MOD_MENU_ELEMENT_TEXT:
            params = 1;
        case MOD_MENU_ELEMENT_BUTTON:
            params = 1;
            break;
        case MOD_MENU_ELEMENT_CHECKBOX:
            lua_pushboolean(L, hooked->boolValue);
            break;
        case MOD_MENU_ELEMENT_SLIDER:
            lua_pushinteger(L, hooked->uintValue);
            break;
        case MOD_MENU_ELEMENT_INPUTBOX:
            lua_pushstring(L, hooked->stringValue);
            break;
        case MOD_MENU_ELEMENT_MAX:
            break;
    }

    // call the callback
    if (0 != smlua_call_hook(L, params, 1, 0, hooked->mod)) {
        LOG_LUA("Failed to call the mod menu element callback: %s", hooked->name);
        return;
    }
}


  //////////
 // misc //
//////////

void smlua_clear_hooks(void) {
    for (int i = 0; i < HOOK_MAX; i++) {
        struct LuaHookedEvent* hooked = &sHookedEvents[i];
        for (int j = 0; j < hooked->count; j++) {
            hooked->reference[j] = 0;
            hooked->mod[j] = NULL;
        }
        hooked->count = 0;
    }

    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        struct LuaHookedMarioAction* hooked = &sHookedMarioActions[i];
        hooked->action = 0;
        hooked->mod = NULL;
        memset(hooked->actionHookRefs, 0, sizeof(hooked->actionHookRefs));
    }
    sHookedMarioActionsCount = 0;

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hooked = &sHookedChatCommands[i];
        if (hooked->command != NULL) { free(hooked->command); }
        hooked->command = NULL;

        if (hooked->description != NULL) { free(sHookedChatCommands[i].description); }
        hooked->description = NULL;

        hooked->reference = 0;
        hooked->mod = NULL;
    }
    sHookedChatCommandsCount = 0;

    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        hooked->element = MOD_MENU_ELEMENT_TEXT;
        hooked->name[0] = '\0';
        hooked->boolValue = false;
        hooked->uintValue = 0;
        hooked->stringValue[0] = '\0';
        hooked->length = 0;
        hooked->sliderMin = 0;
        hooked->sliderMax = 0;
        hooked->reference = 0;
        hooked->mod = NULL;
    }
    gHookedModMenuElementsCount = 0;

    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];

        // If this is NULL. We can't do anything with it.
        if (hooked->behavior != NULL) {
            // If it's a LUA made behavior, The behavior is allocated so reset and free it.
            // Otherwise it's a DynOS behavior and it needs to have it's original id put back where it belongs.
            if (hooked->luaBehavior) {
                // Just free the allocated behavior.
                free(hooked->behavior);
            } else {
                hooked->behavior[1] = (BehaviorScript)BC_B0H(0x39, hooked->originalId); // This is ID(hooked->originalId)
            }
        }
        // Reset the variables.
        hooked->behaviorId = 0;
        hooked->overrideId = 0;
        hooked->originalId = 0;
        hooked->behavior = NULL;
        hooked->originalBehavior = NULL;
        hooked->initReference = 0;
        hooked->loopReference = 0;
        hooked->replace = false;
        hooked->luaBehavior = false;
        hooked->mod = NULL;
    }
    sHookedBehaviorsCount = 0;
    memset(gLuaMarioActionIndex, 0, sizeof(gLuaMarioActionIndex));
}

void smlua_bind_hooks(void) {
    lua_State* L = gLuaState;
    smlua_clear_hooks();

    smlua_bind_function(L, "hook_event", smlua_hook_event);
    smlua_bind_function(L, "hook_mario_action", smlua_hook_mario_action);
    smlua_bind_function(L, "hook_chat_command", smlua_hook_chat_command);
    smlua_bind_function(L, "hook_on_sync_table_change", smlua_hook_on_sync_table_change);
    smlua_bind_function(L, "hook_behavior", smlua_hook_behavior);
    smlua_bind_function(L, "hook_mod_menu_text", smlua_hook_mod_menu_text);
    smlua_bind_function(L, "hook_mod_menu_button", smlua_hook_mod_menu_button);
    smlua_bind_function(L, "hook_mod_menu_checkbox", smlua_hook_mod_menu_checkbox);
    smlua_bind_function(L, "hook_mod_menu_slider", smlua_hook_mod_menu_slider);
    smlua_bind_function(L, "hook_mod_menu_inputbox", smlua_hook_mod_menu_inputbox);
    smlua_bind_function(L, "update_chat_command_description", smlua_update_chat_command_description);
    smlua_bind_function(L, "update_mod_menu_element_name", smlua_update_mod_menu_element_name);
    smlua_bind_function(L, "update_mod_menu_element_checkbox", smlua_update_mod_menu_element_checkbox);
    smlua_bind_function(L, "update_mod_menu_element_slider", smlua_update_mod_menu_element_slider);
    smlua_bind_function(L, "update_mod_menu_element_inputbox", smlua_update_mod_menu_element_inputbox);
}
