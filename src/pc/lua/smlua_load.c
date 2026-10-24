#include <stdbool.h>
#include <string.h>
#include "smlua.h"

static void smlua_push_caller_env(lua_State *L) {
    lua_Debug ar;
    if (!lua_getstack(L, 1, &ar) || !lua_getinfo(L, "f", &ar)) {
        lua_pushnil(L);
        return;
    }

    const char *name;
    for (int i = 1; (name = lua_getupvalue(L, -1, i)) != NULL; i++) {
        if (strcmp(name, "_ENV") == 0) {
            lua_insert(L, -2);
            lua_pop(L, 1);
            return;
        }
        lua_pop(L, 1);
    }

    lua_pop(L, 1);
    lua_pushnil(L);
}

static int smlua_custom_load(lua_State *L) {
    if (!lua_isstring(L, 1)) {
        lua_pushnil(L);
        lua_pushliteral(L, "load() expected string in argument 1");
        return 2;
    }

    size_t len;
    const char *code = lua_tolstring(L, 1, &len);
    const char *chunkname = luaL_optstring(L, 2, "=(load)");

    int status = luaL_loadbufferx(L, code, len, chunkname, "t");

    if (status != LUA_OK) {
        lua_pushnil(L);
        lua_insert(L, -2);
        return 2;
    }

    if (lua_istable(L, 4)) {
        lua_pushvalue(L, 4);
        lua_setupvalue(L, -2, 1);
    } else {
        // fallback to the caller's environment
        smlua_push_caller_env(L);
        if (lua_istable(L, -1)) {
            lua_setupvalue(L, -2, 1);
        } else {
            lua_pop(L, 1);
        }
    }

    return 1;
}

void smlua_bind_custom_load() {
    lua_State *L = gLuaState;
    if (!L) { return; }
    // replace the global load function
    lua_pushcfunction(L, smlua_custom_load);
    lua_setglobal(L, "load");
}
