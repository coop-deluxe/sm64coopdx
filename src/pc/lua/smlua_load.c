#include <stdbool.h>
#include "smlua.h"

static int smlua_custom_load(lua_State *L) {
    size_t len;
    if (!lua_isstring(L, 1)) {
        lua_pushnil(L);
        lua_pushliteral(L, "load() expected string in argument 1");
        return 2;
    }

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
    }

    return 1;
}

void smlua_bind_custom_load() {
    lua_State *L = gLuaState;
    if (!L) { return; }
    // replace the global require function
    lua_pushcfunction(L, smlua_custom_load);
    lua_setglobal(L, "load");
}
