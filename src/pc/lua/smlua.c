#include "smlua.h"

lua_State* gLuaState = NULL;

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

    smlua_bind_get_set();

    smlua_execfile("mods/constants.lua");
    smlua_execfile("mods/test.lua");
}

void smlua_call_hooks(enum LuaHookedEventType hookType) {
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

void smlua_call_hooks_param(enum LuaHookedEventType hookType, int param) {
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

void smlua_update(void) {
    smlua_call_hooks(HOOK_UPDATE);
}

void smlua_shutdown(void) {
    lua_State* L = gLuaState;
    lua_close(L);
}
