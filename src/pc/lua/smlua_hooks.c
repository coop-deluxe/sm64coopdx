#include "smlua.h"
#include "behavior_commands.h"
#include "pc/mods/mod.h"
#include "src/game/object_list_processor.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/crash_handler.h"
#include "src/game/hud.h"
#include "pc/debug_context.h"

#if defined(DEVELOPMENT)
#include "../mods/mods.h"
#include "game/print.h"
#include "gfx_dimensions.h"

#define MAX_PROFILED_MODS 16
#define REFRESH_RATE 15

static struct {
    f64 start;
    f64 end;
    f64 sum;
    f64 disp;
} sLuaProfilerCounters[MAX_PROFILED_MODS];

static void lua_profiler_start_counter(struct Mod *mod) {
    for (s32 i = 0; i != MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); ++i) {
        if (gActiveMods.entries[i] == mod) {
            f64 freq = SDL_GetPerformanceFrequency();
            f64 curr = SDL_GetPerformanceCounter();
            sLuaProfilerCounters[i].start = curr / freq;
            return;
        }
    }
}

static void lua_profiler_stop_counter(struct Mod *mod) {
    for (s32 i = 0; i != MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); ++i) {
        if (gActiveMods.entries[i] == mod) {
            f64 freq = SDL_GetPerformanceFrequency();
            f64 curr = SDL_GetPerformanceCounter();
            sLuaProfilerCounters[i].end = curr / freq;
            sLuaProfilerCounters[i].sum += sLuaProfilerCounters[i].end - sLuaProfilerCounters[i].start;
            return;
        }
    }
}

void lua_profiler_update_counters() {
    if (gGlobalTimer % REFRESH_RATE == 0) {
        for (s32 i = 0; i != MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); ++i) {
            sLuaProfilerCounters[i].disp = sLuaProfilerCounters[i].sum / (f64) REFRESH_RATE;
            sLuaProfilerCounters[i].sum = 0;
        }
    }
    for (s32 i = 0, y = SCREEN_HEIGHT - 60; i != MIN(MAX_PROFILED_MODS, gActiveMods.entryCount); ++i, y -= 18) {
        const char *modName = gActiveMods.entries[i]->relativePath;
        s32 modCounterUs = (s32) (sLuaProfilerCounters[i].disp * 1000000.0);
        char text[256];
        snprintf(text, 256, "             %05d", modCounterUs);
        memcpy(text, modName, MIN(12, strlen(modName) - (gActiveMods.entries[i]->isDirectory ? 0 : 4)));
        for (s32 j = 0; j != 12; ++j) {
            char c = text[j];
            if (c >= 'a' && c <= 'z') c -= ('a' - 'A');
            if (c == 'J') c = 'I';
            if (c == 'Q') c = 'O';
            if (c == 'V') c = 'U';
            if (c == 'X') c = '*';
            if (c == 'Z') c = '2';
            if ((c < '0' || c > '9') && (c < 'A' || c > 'Z')) c = ' ';
            text[j] = c;
        }
        print_text(gfx_dimensions_rect_from_left_edge(4), y, text);
    }
}

#endif

#define MAX_HOOKED_REFERENCES 64
#define LUA_BEHAVIOR_FLAG (1 << 15)

static u64* sBehaviorOffset = &gPcDebug.bhvOffset;

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    struct Mod* mod[MAX_HOOKED_REFERENCES];
    int count;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

int smlua_call_hook(lua_State* L, int nargs, int nresults, int errfunc, struct Mod* activeMod) {
    struct Mod* prev = gLuaActiveMod;
    gLuaActiveMod = activeMod;
    gLuaLastHookMod = activeMod;
#if defined(DEVELOPMENT)
    extern bool configLuaProfiler;
    if (configLuaProfiler) {
        lua_profiler_start_counter(activeMod);
    }
#endif

    CTX_BEGIN(CTX_HOOK);
    int rc = smlua_pcall(L, nargs, nresults, errfunc);
    CTX_END(CTX_HOOK);

#if defined(DEVELOPMENT)
    if (configLuaProfiler) {
        lua_profiler_stop_counter(activeMod);
    }
#endif
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
        LOG_LUA_LINE("tried to hook undefined function to '%s'", LuaHookedEventTypeName[hookType]);
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

void smlua_call_event_hooks_with_reset_func(enum LuaHookedEventType hookType, void (*resetFunc)(void)) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the event_hook callback: %u", hookType);
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

void smlua_call_event_hooks_mario_params(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2) {
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

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i])) {
            LOG_LUA("Failed to call the callback: %u", hookType);
            continue;
        }
    }
}

void smlua_call_event_hooks_mario_params_ret_bool(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2, bool* returnValue) {
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
        smlua_push_object(L, LOT_OBJECT, obj);

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
        smlua_push_object(L, LOT_OBJECT, obj);

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

void smlua_call_event_hooks_object_param(enum LuaHookedEventType hookType, struct Object* obj) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push object
        smlua_push_object(L, LOT_OBJECT, obj);

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
        smlua_push_object(L, LOT_OBJECT, obj);
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
        smlua_push_object(L, LOT_CAMERA, c);
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

  ////////////////////
 // hooked actions //
////////////////////

struct LuaHookedMarioAction {
    u32 action;
    u32 interactionType;
    int actionHookRefs[ACTION_HOOK_MAX];
    struct Mod* mod;
};

#define MAX_HOOKED_ACTIONS 128

static struct LuaHookedMarioAction sHookedMarioActions[MAX_HOOKED_ACTIONS] = { 0 };
static int sHookedMarioActionsCount = 0;
u32 gLuaMarioActionIndex = 0;

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
        LOG_LUA_LINE("smlua_hook_mario_action received improper type '%d'", lua_type(L, 2));
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
    if (!gSmLuaConvertSuccess) { return 0; }

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
    int initReference;
    int loopReference;
    bool replace;
    bool luaBehavior;
    struct Mod* mod;
};

#define MAX_HOOKED_BEHAVIORS 256

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
    return behavior + *sBehaviorOffset;
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
        LOG_INFO("Registered custom behavior: %04hX - %s", customBehaviorId, bhvName);
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
    hooked->behavior = calloc(3, sizeof(BehaviorScript));
    hooked->behavior[0] = (BehaviorScript)BC_BB(0x00, objectList); // This is BEGIN(objectList)
    hooked->behavior[1] = (BehaviorScript)BC_B0H(0x39, customBehaviorId); // This is ID(customBehaviorId)
    hooked->behavior[2] = 0;
    hooked->behaviorId = customBehaviorId;
    hooked->overrideId = noOverrideId ? customBehaviorId : overrideBehaviorId;
    hooked->originalId = customBehaviorId; // For LUA behaviors. The only behavior id they have IS their custom one.
    hooked->originalBehavior = originalBehavior ? originalBehavior : hooked->behavior;
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
    LOG_INFO("Registered custom behavior: %04hX - %s", customBehaviorId, bhvName);

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
        smlua_push_object(L, LOT_OBJECT, object);

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

#define MAX_HOOKED_CHAT_COMMANDS 64

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
    if (!gSmLuaConvertSuccess) { return 0; }

    sHookedChatCommandsCount++;
    return 1;
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
        LOG_LUA_LINE("Tried to attach a non-table to hook_on_sync_table_change: %d", lua_type(L, syncTableIndex));
        return 0;
    }

    if (lua_type(L, funcIndex) != LUA_TFUNCTION) {
        LOG_LUA_LINE("Tried to attach a non-function to hook_on_sync_table_change: %d", lua_type(L, funcIndex));
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
    gLuaMarioActionIndex = 0;
}

void smlua_bind_hooks(void) {
    lua_State* L = gLuaState;
    smlua_clear_hooks();

    smlua_bind_function(L, "hook_event", smlua_hook_event);
    smlua_bind_function(L, "hook_mario_action", smlua_hook_mario_action);
    smlua_bind_function(L, "hook_chat_command", smlua_hook_chat_command);
    smlua_bind_function(L, "hook_on_sync_table_change", smlua_hook_on_sync_table_change);
    smlua_bind_function(L, "hook_behavior", smlua_hook_behavior);
}
