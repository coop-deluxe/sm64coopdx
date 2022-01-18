#include "smlua.h"

void smlua_dump_stack(void) {
    lua_State* L = gLuaState;
    int top = lua_gettop(L);
    printf("--------------\n");
    for (int i = 1; i <= top; i++) {
        printf("%d\t%s\t", i, luaL_typename(L, i));
        switch (lua_type(L, i)) {
        case LUA_TNUMBER:
            printf("%g\n", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            printf("%s\n", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
            break;
        case LUA_TNIL:
            printf("%s\n", "nil");
            break;
        default:
            printf("%p\n", lua_topointer(L, i));
            break;
        }
    }
    printf("--------------\n");
}

void smlua_dump_globals(void) {
    lua_State* L = gLuaState;
    printf("--------------\n");
    lua_pushglobaltable(L);

    // table is in the stack at index 't'
    lua_pushnil(L);  // first key
    while (lua_next(L, -2) != 0) {
        // uses 'key' (at index -2) and 'value' (at index -1)
        if (lua_type(L, -2) == LUA_TSTRING) {
            printf("%s - %s\n",
                lua_tostring(L, -2),
                lua_typename(L, lua_type(L, -1)));
        } else {
            printf("%s - %s\n",
                lua_typename(L, lua_type(L, -2)),
                lua_typename(L, lua_type(L, -1)));
        }
        // removes 'value'; keeps 'key' for next iteration
        lua_pop(L, 1);
    }
    lua_pop(L, 1);                 // remove global table(-1)
    printf("--------------\n");
}

void smlua_push_integer_field(lua_Integer val, char* name) {
    int t = lua_gettop(gLuaState);
    lua_pushinteger(gLuaState, val);
    lua_setfield(gLuaState, t, name);
}

void smlua_push_number_field(float val, char* name) {
    int t = lua_gettop(gLuaState);
    lua_pushnumber(gLuaState, val);
    lua_setfield(gLuaState, t, name);
}

void smlua_get_u8_field(u8* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isinteger(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tointeger(gLuaState, -1);
    lua_pop(gLuaState, 1);
}

void smlua_get_u16_field(u16* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isinteger(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tointeger(gLuaState, -1);
    lua_pop(gLuaState, 1);
}

void smlua_get_u32_field(u32* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isinteger(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tointeger(gLuaState, -1);
    lua_pop(gLuaState, 1);
}

void smlua_get_s8_field(s8* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isinteger(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tointeger(gLuaState, -1);
    lua_pop(gLuaState, 1);
}

void smlua_get_s16_field(s16* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isinteger(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tointeger(gLuaState, -1);
    lua_pop(gLuaState, 1);
}

void smlua_get_s32_field(s32* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isinteger(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tointeger(gLuaState, -1);
    lua_pop(gLuaState, 1);
}

void smlua_get_number_field(float* val, char* name) {
    lua_getfield(gLuaState, -1, name);
    if (!lua_isnumber(gLuaState, -1)) {
        LOG_LUA("LUA: field '%s' isn't an integer.", name);
        return;
    }
    *val = lua_tonumber(gLuaState, -1);
    lua_pop(gLuaState, 1);
}
