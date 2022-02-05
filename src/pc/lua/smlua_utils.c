#include "smlua.h"

u8 gSmLuaConvertSuccess = false;

#define VEC3F_BUFFER_COUNT 64
static Vec3f sVec3fBuffer[VEC3F_BUFFER_COUNT] = { 0 };
static u8 sVec3fBufferIndex = 0;

#define VEC3S_BUFFER_COUNT 64
static Vec3s sVec3sBuffer[VEC3S_BUFFER_COUNT] = { 0 };
static u8 sVec3sBufferIndex = 0;

f32* smlua_get_vec3f_from_buffer(void) {
    if (sVec3fBufferIndex > VEC3F_BUFFER_COUNT) { sVec3fBufferIndex = 0; }
    return sVec3fBuffer[sVec3fBufferIndex++];
}

s16* smlua_get_vec3s_from_buffer(void) {
    if (sVec3sBufferIndex > VEC3S_BUFFER_COUNT) { sVec3sBufferIndex = 0; }
    return sVec3sBuffer[sVec3sBufferIndex++];
}

///////////////////////////////////////////////////////////////////////////////////////////

void smlua_bind_function(lua_State* L, const char* name, void* func) {
    lua_pushcfunction(L, func);
    lua_setglobal(L, name);
}


bool smlua_is_table_empty(int index) {
    lua_pushnil(gLuaState); // key
    if (lua_next(gLuaState, index)) {
        lua_pop(gLuaState, 2);
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////

bool smlua_to_boolean(lua_State* L, int index) {
    if (lua_type(L, index) != LUA_TBOOLEAN) {
        LOG_LUA("smlua_to_boolean received improper type '%d'", lua_type(L, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }
    return lua_toboolean(L, index) ? true : false;
}

lua_Integer smlua_to_integer(lua_State* L, int index) {
    if (lua_type(L, index) == LUA_TBOOLEAN) {
        gSmLuaConvertSuccess = true;
        return lua_toboolean(L, index) ? 1 : 0;
    } else if (lua_type(L, index) != LUA_TNUMBER) {
        LOG_LUA("smlua_to_integer received improper type '%d'", lua_type(L, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }
    gSmLuaConvertSuccess = true;
    lua_Integer val = lua_tointeger(L, index);
    return (val == 0) ? lua_tonumber(L, index) : val;
}

lua_Number smlua_to_number(lua_State* L, int index) {
    if (lua_type(L, index) != LUA_TNUMBER) {
        LOG_LUA("smlua_to_number received improper type '%d'", lua_type(L, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }
    gSmLuaConvertSuccess = true;
    return lua_tonumber(L, index);
}

const char* smlua_to_string(lua_State* L, int index) {
    if (lua_type(L, index) != LUA_TSTRING) {
        LOG_LUA("smlua_to_string received improper type '%d'", lua_type(L, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }
    gSmLuaConvertSuccess = true;
    return lua_tostring(L, index);
}

void* smlua_to_cobject(lua_State* L, int index, u16 lot) {
    if (lua_type(L, index) != LUA_TTABLE) {
        LOG_LUA("smlua_to_cobject received improper type '%d'", lua_type(L, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }

    // get LOT
    lua_getfield(L, index, "_lot");
    enum LuaObjectType objLot = smlua_to_integer(L, -1);
    lua_pop(L, 1);
    if (!gSmLuaConvertSuccess) { return NULL; }

    if (lot != objLot) {
        LOG_LUA("smlua_to_cobject received improper LOT. Expected '%d', received '%d'", lot, objLot);
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    // get pointer
    lua_getfield(L, index, "_pointer");
    void* pointer = (void*)smlua_to_integer(L, -1);
    lua_pop(L, 1);
    if (!gSmLuaConvertSuccess) { return NULL; }

    // check allowlist
    if (!smlua_cobject_allowlist_contains(lot, (u64)pointer)) {
        LOG_LUA("smlua_to_cobject received a pointer not in allow list. '%u', '%llu", lot, (u64)pointer);
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    if (pointer == NULL) {
        LOG_LUA("smlua_to_cobject received null pointer.");
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    gSmLuaConvertSuccess = true;
    return pointer;
}

struct LSTNetworkType smlua_to_lnt(lua_State* L, int index) {
    struct LSTNetworkType lnt = { 0 };
    int valueType = lua_type(L, index);

    if (valueType == LUA_TNUMBER) {
        lnt.type = LST_NETWORK_TYPE_INTEGER;
        lnt.value.integer = lua_tointeger(L, index);
        lnt.size = sizeof(u8) + sizeof(long long);

        if (lnt.value.integer == 0) {
            lnt.type = LST_NETWORK_TYPE_NUMBER;
            lnt.value.number = lua_tonumber(L, index);
            lnt.size = sizeof(u8) + sizeof(double);

            if (lnt.value.number == 0) {
                lnt.type = LST_NETWORK_TYPE_INTEGER;
                lnt.size = sizeof(u8) + sizeof(long long);
            }
        }
        gSmLuaConvertSuccess = true;
        return lnt;
    }

    if (valueType == LUA_TBOOLEAN) {
        lnt.type = LST_NETWORK_TYPE_BOOLEAN;
        lnt.value.boolean = lua_toboolean(L, index);
        lnt.size = sizeof(u8) + sizeof(u8);
        gSmLuaConvertSuccess = true;
        return lnt;
    }

    if (valueType == LUA_TSTRING) {
        lnt.type = LST_NETWORK_TYPE_STRING;
        lnt.value.string = (char*)lua_tostring(L, index);
        if (lnt.value.string == NULL || strlen(lnt.value.string) > 256) {
            LOG_LUA("smlua_to_lnt on invalid string value: '%s'", (lnt.value.string == NULL) ? "<null>" : lnt.value.string);
            smlua_logline();
            gSmLuaConvertSuccess = false;
            return lnt;
        }
        lnt.size = sizeof(u8) + sizeof(u16) + sizeof(u8) * strlen(lnt.value.string);
        gSmLuaConvertSuccess = true;
        return lnt;
    }

    if (valueType == LUA_TNIL) {
        lnt.type = LST_NETWORK_TYPE_NIL;
        lnt.size = sizeof(u8);
        gSmLuaConvertSuccess = true;
        return lnt;
    }

    LOG_LUA("smlua_to_lnt on invalid type: '%d'", valueType);
    smlua_logline();
    gSmLuaConvertSuccess = false;
    return lnt;
}

///////////////////////////////////////////////////////////////////////////////////////////

void smlua_push_object(lua_State* L, u16 lot, void* p) {
    if (p == NULL) {
        lua_pushnil(L);
        return;
    }
    // add to allowlist
    smlua_cobject_allowlist_add(lot, (u64)p);

    lua_newtable(L);
    int t = lua_gettop(L);
    smlua_push_integer_field(t, "_lot", lot);
    smlua_push_integer_field(t, "_pointer", (u64)p);
    lua_pushglobaltable(L);
    lua_getfield(gLuaState, -1, "_CObject");
    lua_setmetatable(L, -3);
    lua_pop(L, 1); // pop global table
}

void smlua_push_integer_field(int index, char* name, lua_Integer val) {
    lua_pushinteger(gLuaState, val);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_number_field(int index, char* name, lua_Number val) {
    lua_pushnumber(gLuaState, val);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_string_field(int index, char* name, const char* val) {
    lua_pushstring(gLuaState, val);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_nil_field(int index, char* name) {
    lua_pushnil(gLuaState);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_table_field(int index, char* name) {
    lua_newtable(gLuaState);
    lua_setfield(gLuaState, index, name);
}

///////////////////////////////////////////////////////////////////////////////////////////

void smlua_push_lnt(struct LSTNetworkType* lnt) {
    lua_State* L = gLuaState;
    switch (lnt->type) {
        case LST_NETWORK_TYPE_INTEGER:
            lua_pushinteger(L, lnt->value.integer);
            break;
        case LST_NETWORK_TYPE_NUMBER:
            lua_pushnumber(L, lnt->value.number);
            break;
        case LST_NETWORK_TYPE_BOOLEAN:
            lua_pushboolean(L, lnt->value.boolean);
            break;
        case LST_NETWORK_TYPE_STRING:
            lua_pushstring(L, lnt->value.string);
            break;
        case LST_NETWORK_TYPE_NIL:
            lua_pushnil(L);
            break;
        default: SOFT_ASSERT(false);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

lua_Integer smlua_get_integer_field(int index, char* name) {
    if (lua_type(gLuaState, index) != LUA_TTABLE) {
        LOG_LUA("smlua_get_integer_field received improper type '%d'", lua_type(gLuaState, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }
    lua_getfield(gLuaState, index, name);
    lua_Integer val = smlua_to_integer(gLuaState, -1);
    lua_pop(gLuaState, 1);
    return val;
}

lua_Number smlua_get_number_field(int index, char* name) {
    if (lua_type(gLuaState, index) != LUA_TTABLE) {
        LOG_LUA("smlua_get_number_field received improper type '%d'", lua_type(gLuaState, index));
        smlua_logline();
        gSmLuaConvertSuccess = false;
        return 0;
    }
    lua_getfield(gLuaState, index, name);
    lua_Number val = smlua_to_number(gLuaState, -1);
    lua_pop(gLuaState, 1);
    return val;
}

///////////////////////////////////////////////////////////////////////////////////////////

char* smlua_lnt_to_str(struct LSTNetworkType* lnt) {
    static char sLntStr[32] = "";
    switch (lnt->type) {
        case LST_NETWORK_TYPE_INTEGER:
            snprintf(sLntStr, 32, "%lld", lnt->value.integer);
            break;
        case LST_NETWORK_TYPE_NUMBER:
            snprintf(sLntStr, 32, "%f", lnt->value.number);
            break;
        case LST_NETWORK_TYPE_BOOLEAN:
            snprintf(sLntStr, 32, "%u", lnt->value.boolean);
            break;
        case LST_NETWORK_TYPE_STRING:
            snprintf(sLntStr, 32, "%s", lnt->value.string);
            break;
        case LST_NETWORK_TYPE_NIL:
            snprintf(sLntStr, 32, "<NIL>");
            break;
        default: SOFT_ASSERT_RETURN(false, "UNKNOWN");
    }
    return sLntStr;
}

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
        }
        else {
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

void smlua_dump_table(int index) {
    lua_State* L = gLuaState;
    printf("--------------\n");

    // table is in the stack at index 't'
    lua_pushnil(L);  // first key
    while (lua_next(L, index) != 0) {
        // uses 'key' (at index -2) and 'value' (at index -1)
        if (lua_type(L, -2) == LUA_TSTRING) {
            printf("%s - %s\n",
                lua_tostring(L, -2),
                lua_typename(L, lua_type(L, -1)));
        }
        else {
            printf("%s - %s\n",
                lua_typename(L, lua_type(L, -2)),
                lua_typename(L, lua_type(L, -1)));
        }
        // removes 'value'; keeps 'key' for next iteration
        lua_pop(L, 1);
    }
    printf("--------------\n");
}

void smlua_logline(void) {
    lua_State* L = gLuaState;
    lua_Debug info;
    int level = 0;
    while (lua_getstack(L, level, &info)) {
        lua_getinfo(L, "nSl", &info);
        LOG_INFO("  [%d] %s:%d -- %s [%s]",
            level, info.short_src, info.currentline,
            (info.name ? info.name : "<unknown>"), info.what);
        ++level;
    }
}