#include "smlua.h"

#define MAX_HOOKED_REFERENCES 64

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    int count;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

int smlua_hook_event(lua_State* L) {
    if (L == NULL) { return 0; }
    u16 hookType = lua_tointeger(L, -2);
    if (hookType >= HOOK_MAX) {
        LOG_LUA("LUA: Hook Type: %d exceeds max!", hookType);
        return 0;
    }

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    if (hook->count >= MAX_HOOKED_REFERENCES) {
        LOG_LUA("LUA: Hook Type: %d exceeded maximum references!", hookType);
        return 0;
    }

    hook->reference[hook->count] = luaL_ref(L, LUA_REGISTRYINDEX);
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
        if (0 != lua_pcall(L, 0, 0, 0)) {
            LOG_LUA("LUA: Failed to call the callback: %s", lua_tostring(L, -1));
            continue;
        }
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
        if (0 != lua_pcall(L, 1, 0, 0)) {
            LOG_LUA("LUA: Failed to call the callback: %s", lua_tostring(L, -1));
            continue;
        }
    }
}

  ////////////////////
 // hooked actions //
////////////////////

struct LuaHookedMarioAction {
    u32 action;
    int reference;
};

#define MAX_HOOKED_ACTIONS 64

static struct LuaHookedMarioAction sHookedMarioActions[MAX_HOOKED_ACTIONS] = { 0 };
static int sHookedMarioActionsCount = 0;

int smlua_hook_mario_action(lua_State* L) {
    if (L == NULL) { return 0; }
    if (sHookedMarioActionsCount >= MAX_HOOKED_ACTIONS) {
        LOG_LUA("LUA: Hooked mario actions exceeded maximum references!");
        return 0;
    }

    struct LuaHookedMarioAction* hooked = &sHookedMarioActions[sHookedMarioActionsCount];
    hooked->action = lua_tointeger(L, -2);
    hooked->reference = luaL_ref(L, LUA_REGISTRYINDEX);

    sHookedMarioActionsCount++;
    return 1;
}

bool smlua_call_action_hook(struct MarioState* m, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        if (sHookedMarioActions[i].action == m->action) {
            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, sHookedMarioActions[i].reference);

            // push mario state
            lua_getglobal(L, "gMarioStates");
            lua_pushinteger(L, m->playerIndex);
            lua_gettable(L, -2);
            lua_remove(L, -2);
            
            // call the callback
            if (0 != lua_pcall(L, 1, 1, 0)) {
                LOG_LUA("LUA: Failed to call the callback: %s", lua_tostring(L, -1));
                continue;
            }

            // output the return value
            *returnValue = lua_tointeger(L, -1);
            lua_pop(L, 1);

            return true;
        }
    }

    return false;
}

  //////////
 // misc //
//////////

static void smlua_clear_hooks(void) {
    for (int i = 0; i < HOOK_MAX; i++) {
        for (int j = 0; j < sHookedEvents[i].count; j++) {
            sHookedEvents[i].reference[j] = 0;
        }
        sHookedEvents[i].count = 0;
    }

    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        sHookedMarioActions[i].action = 0;
        sHookedMarioActions[i].reference = 0;
    }
    sHookedMarioActionsCount = 0;
}

void smlua_bind_hooks(void) {
    lua_State* L = gLuaState;
    smlua_clear_hooks();

    smlua_bind_function(L, "hook_event", smlua_hook_event);
    smlua_bind_function(L, "hook_mario_action", smlua_hook_mario_action);

}
