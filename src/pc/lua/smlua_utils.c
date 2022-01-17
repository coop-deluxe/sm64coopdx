#include "smlua.h"

void smlua_dump_stack(void) {
    lua_State* L = gLuaState;
    int top = lua_gettop(L);
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
}

void smlua_push_integer_field(int val, char* name) {
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
