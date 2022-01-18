#include "smlua.h"

lua_State* gLuaState = NULL;

  ///////////////////
 // hooked events //
///////////////////

#define MAX_HOOKED_REFERENCES 64

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    int count;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

int smlua_hook_event(lua_State* L) {
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

void smlua_call_event_hooks_param(enum LuaHookedEventType hookType, int param) {
    lua_State* L = gLuaState;
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push the param
        lua_pushinteger(L, param);

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
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        if (sHookedMarioActions[i].action == m->action) {
            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, sHookedMarioActions[i].reference);

            // push param
            lua_pushinteger(L, m->playerIndex);
            
            // call the callback
            if (0 != lua_pcall(L, 1, 1, 0)) {
                LOG_LUA("LUA: Failed to call the callback: %s", lua_tostring(L, -1));
                continue;
            }

            // output the return value
            *returnValue = lua_tointeger(L, -1);
            lua_pop(L, 1);

            printf(">> action hook return: %d\n", *returnValue);
            fflush(stdout);
            return true;
        }
    }

    return false;
}

  //////////
 // main //
//////////

static void smlua_execfile(char* path) {
    lua_State* L = gLuaState;
    if (luaL_dofile(L, path) != LUA_OK) {
        LOG_LUA("LUA: Failed to load lua file.");
        puts(lua_tostring(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

void smlua_init(void) {
    gLuaState = luaL_newstate();
    lua_State* L = gLuaState;
    luaL_openlibs(L);

    lua_pushcfunction(L, smlua_hook_event);
    lua_setglobal(L, "hook_event");

    lua_pushcfunction(L, smlua_hook_mario_action);
    lua_setglobal(L, "hook_mario_action");

    smlua_bind_get_set();

    smlua_execfile("mods/constants.lua");
    smlua_execfile("mods/test.lua");
}

void smlua_update(void) {
    smlua_call_event_hooks(HOOK_UPDATE);
}

void smlua_shutdown(void) {
    lua_State* L = gLuaState;
    lua_close(L);

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
