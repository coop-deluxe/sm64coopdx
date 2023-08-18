#include "smlua.h"
#include "src/pc/mods/mods.h"
#include "audio/external.h"

u8 gSmLuaConvertSuccess = false;

#define VEC3F_BUFFER_COUNT 64
static Vec3f sVec3fBuffer[VEC3F_BUFFER_COUNT] = { 0 };
static u8 sVec3fBufferIndex = 0;

#define VEC3S_BUFFER_COUNT 64
static Vec3s sVec3sBuffer[VEC3S_BUFFER_COUNT] = { 0 };
static u8 sVec3sBufferIndex = 0;

#define VEC4F_BUFFER_COUNT 64
static Vec4f sVec4fBuffer[VEC4F_BUFFER_COUNT] = { 0 };
static u8 sVec4fBufferIndex = 0;

#define VEC4S_BUFFER_COUNT 64
static Vec4s sVec4sBuffer[VEC4S_BUFFER_COUNT] = { 0 };
static u8 sVec4sBufferIndex = 0;

#define COLOR_BUFFER_COUNT 64
static Color sColorBuffer[COLOR_BUFFER_COUNT] = { 0 };
static u8 sColorBufferIndex = 0;

f32* smlua_get_vec3f_from_buffer(void) {
    if (sVec3fBufferIndex >= VEC3F_BUFFER_COUNT) { sVec3fBufferIndex = 0; }
    return sVec3fBuffer[sVec3fBufferIndex++];
}

s16* smlua_get_vec3s_from_buffer(void) {
    if (sVec3sBufferIndex >= VEC3S_BUFFER_COUNT) { sVec3sBufferIndex = 0; }
    return sVec3sBuffer[sVec3sBufferIndex++];
}

f32* smlua_get_vec4f_from_buffer(void) {
    if (sVec4fBufferIndex >= VEC4F_BUFFER_COUNT) { sVec4fBufferIndex = 0; }
    return sVec4fBuffer[sVec4fBufferIndex++];
}

s16* smlua_get_vec4s_from_buffer(void) {
    if (sVec4sBufferIndex >= VEC4S_BUFFER_COUNT) { sVec4sBufferIndex = 0; }
    return sVec4sBuffer[sVec4sBufferIndex++];
}

u8* smlua_get_color_from_buffer(void) {
    if (sColorBufferIndex >= COLOR_BUFFER_COUNT) { sColorBufferIndex = 0; }
    return sColorBuffer[sColorBufferIndex++];
}

f32 *smlua_get_vec3f_for_play_sound(f32 *pos) {
    if (pos < (f32 *) sVec3fBuffer || pos >= (f32 *) (sVec3fBuffer + VEC3F_BUFFER_COUNT)) {
        return pos;
    }
    if (memcmp(pos, gGlobalSoundSource, sizeof(Vec3f)) == 0) {
        return gGlobalSoundSource;
    }
    for (s32 i = 0; i != MAX_PLAYERS; ++i) {
        if (gMarioStates[i].marioObj && memcmp(pos, gMarioStates[i].marioObj->header.gfx.cameraToObject, sizeof(Vec3f)) == 0) {
            return gMarioStates[i].marioObj->header.gfx.cameraToObject;
        }
    }
    return pos;
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
        LOG_LUA_LINE("smlua_to_boolean received improper type '%d'", lua_type(L, index));
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
        LOG_LUA_LINE("smlua_to_integer received improper type '%d'", lua_type(L, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }
    gSmLuaConvertSuccess = true;
    lua_Integer val = lua_tointeger(L, index);
    return (val == 0) ? lua_tonumber(L, index) : val;
}

lua_Number smlua_to_number(lua_State* L, int index) {
    if (lua_type(L, index) == LUA_TBOOLEAN) {
        gSmLuaConvertSuccess = true;
        return lua_toboolean(L, index) ? 1 : 0;
    } else if (lua_type(L, index) != LUA_TNUMBER) {
        LOG_LUA_LINE("smlua_to_number received improper type '%d'", lua_type(L, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }
    gSmLuaConvertSuccess = true;
    return lua_tonumber(L, index);
}

const char* smlua_to_string(lua_State* L, int index) {
    if (lua_type(L, index) != LUA_TSTRING) {
        LOG_LUA_LINE("smlua_to_string received improper type '%d'", lua_type(L, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }
    gSmLuaConvertSuccess = true;
    return lua_tostring(L, index);
}

LuaFunction smlua_to_lua_function(lua_State* L, int index) {
    if (lua_type(L, index) == LUA_TNIL) {
        return 0;
    }

    if (lua_type(L, index) != LUA_TFUNCTION) {
        LOG_LUA_LINE("smlua_to_lua_function received improper type '%d'", lua_type(L, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }

    gSmLuaConvertSuccess = true;
    lua_pushvalue(L, index);
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

bool smlua_is_cobject(lua_State* L, int index, u16 lot) {
    int top = lua_gettop(L);
    bool ret = true;

    s32 indexType = lua_type(L, index);
    if (indexType != LUA_TTABLE) {
        ret = false;
        goto result;
    }

    lua_getfield(L, index, "_lot");
    if (lua_type(L, -1) != LUA_TNUMBER) {
        ret = false;
        goto result;
    }

    enum LuaObjectType objLot = smlua_to_integer(L, -1);
    if (!gSmLuaConvertSuccess) {
        gSmLuaConvertSuccess = true;
        ret = false;
        goto result;
    }

    if (lot != objLot) {
        ret = false;
        goto result;
    }

result:
    lua_settop(L, top);
    return ret;
}

void* smlua_to_cobject(lua_State* L, int index, u16 lot) {
    s32 indexType = lua_type(L, index);
    if (indexType == LUA_TNIL) { return NULL; }
    if (indexType != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_to_cobject received improper type '%d'", lua_type(L, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }

    // get LOT
    lua_getfield(L, index, "_lot");
    enum LuaObjectType objLot = smlua_to_integer(L, -1);
    lua_pop(L, 1);
    if (!gSmLuaConvertSuccess) { return NULL; }

    if (lot != objLot) {
        LOG_LUA_LINE("smlua_to_cobject received improper LOT. Expected '%d', received '%d'", lot, objLot);
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    // get pointer
    lua_getfield(L, index, "_pointer");
    void* pointer = (void*)(intptr_t)smlua_to_integer(L, -1);
    lua_pop(L, 1);
    if (!gSmLuaConvertSuccess) { return NULL; }

    // check allowlist
    if (!smlua_cobject_allowlist_contains(lot, (u64)(intptr_t)pointer)) {
        LOG_LUA_LINE("smlua_to_cobject received a pointer not in allow list. '%u', '%llu", lot, (u64)(intptr_t)pointer);
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    if (pointer == NULL) {
        LOG_LUA_LINE("smlua_to_cobject received null pointer.");
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    gSmLuaConvertSuccess = true;
    return pointer;
}

void* smlua_to_cpointer(lua_State* L, int index, u16 lvt) {
    if (lua_type(L, index) == LUA_TNIL) {
        return NULL;
    }

    if (lua_type(L, index) != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_to_cpointer received improper type '%d'", lua_type(L, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }

    // get LVT
    lua_getfield(L, index, "_lvt");
    enum LuaObjectType objLvt = smlua_to_integer(L, -1);
    lua_pop(L, 1);
    if (!gSmLuaConvertSuccess) { return NULL; }

    if (lvt != objLvt) {
        LOG_LUA_LINE("smlua_to_cpointer received improper LVT. Expected '%d', received '%d'", lvt, objLvt);
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    // get pointer
    lua_getfield(L, index, "_pointer");
    void* pointer = (void*)(intptr_t)smlua_to_integer(L, -1);
    lua_pop(L, 1);
    if (!gSmLuaConvertSuccess) { return NULL; }

    if (!smlua_cpointer_allowlist_contains(lvt, (u64)(intptr_t)pointer)) {
        LOG_LUA_LINE("smlua_to_cpointer received a pointer not in allow list. '%u', '%llu", lvt, (u64)(intptr_t)pointer);
        gSmLuaConvertSuccess = false;
        return NULL;
    }

    if (pointer == NULL) {
        LOG_LUA_LINE("smlua_to_cpointer received null pointer.");
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
            LOG_LUA_LINE("smlua_to_lnt on invalid string value: '%s'", (lnt.value.string == NULL) ? "<null>" : lnt.value.string);
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

    LOG_LUA_LINE("smlua_to_lnt on invalid type: '%d'", valueType);
    gSmLuaConvertSuccess = false;
    return lnt;
}

///////////////////////////////////////////////////////////////////////////////////////////

bool packet_write_lnt(struct Packet* p, struct LSTNetworkType* lnt) {
    u8 lntType = lnt->type;
    packet_write(p, &lntType, sizeof(u8));

    switch (lnt->type) {
        case LST_NETWORK_TYPE_NUMBER: {
            f64 number = lnt->value.number;
            packet_write(p, &number, sizeof(f64));
            return true;
        }

        case LST_NETWORK_TYPE_INTEGER: {
            s64 integer = lnt->value.integer;
            packet_write(p, &integer, sizeof(s64));
            return true;
        }

        case LST_NETWORK_TYPE_BOOLEAN: {
            packet_write(p, &lnt->value.boolean, sizeof(u8));
            return true;
        }

        case LST_NETWORK_TYPE_STRING: {
            u16 valueLength = strlen(lnt->value.string);
            if (valueLength < 1 || valueLength > 256) {
                LOG_ERROR("attempted to send lua variable with invalid string length: %u", valueLength);
                return false;
            }
            packet_write(p, &valueLength, sizeof(u16));
            packet_write(p, lnt->value.string, valueLength * sizeof(u8));
            return true;
        }

        case LST_NETWORK_TYPE_NIL: {
            // no-op
            return true;
        }

        default:
            break;
    }

    LOG_ERROR("attempted to send lua variable with invalid lnt type: %d", lnt->type);
    return false;
}

bool packet_read_lnt(struct Packet* p, struct LSTNetworkType* lnt) {
    packet_read(p, &lnt->type, sizeof(u8));

    switch (lnt->type) {
        case LST_NETWORK_TYPE_NUMBER:
            packet_read(p, &lnt->value.number, sizeof(f64));
            return true;

        case LST_NETWORK_TYPE_INTEGER:
            packet_read(p, &lnt->value.integer, sizeof(s64));
            return true;

        case LST_NETWORK_TYPE_BOOLEAN:
            packet_read(p, &lnt->value.boolean, sizeof(u8));
            return true;

        case LST_NETWORK_TYPE_STRING: {
            u16 valueLength = 0;
            packet_read(p, &valueLength, sizeof(u16));
            if (valueLength < 1 || valueLength > 256) {
                LOG_ERROR("received lua variable with invalid value length: %d", valueLength);
                return false;
            }
            lnt->value.string = calloc(valueLength + 1, sizeof(char));
            packet_read(p, lnt->value.string, valueLength * sizeof(u8));
            return true;
        }

        case LST_NETWORK_TYPE_NIL:
            // no-op
            return true;

        default:
            break;
    }

    LOG_ERROR("received lua variable with invalid type: %d", lnt->type);
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////

void smlua_push_object(lua_State* L, u16 lot, void* p) {
    if (p == NULL) {
        lua_pushnil(L);
        return;
    }
    // add to allowlist
    smlua_cobject_allowlist_add(lot, (u64)(intptr_t)p);

    // get a cobject from a function
    lua_getglobal(L, "_NewCObject");  // Get the function by its global name
    lua_pushinteger(L, lot);
    lua_pushinteger(L, (u64)(intptr_t)p);

    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        LOG_ERROR("Error calling Lua function: %s\n", lua_tostring(L, -1));
    }
}

void smlua_push_pointer(lua_State* L, u16 lvt, void* p) {
    if (p == NULL) {
        lua_pushnil(L);
        return;
    }

    smlua_cpointer_allowlist_add(lvt, (u64)(intptr_t)p);

    // get a cpointer from a function
    lua_getglobal(L, "_NewCPointer");  // Get the function by its global name
    lua_pushinteger(L, lvt);
    lua_pushinteger(L, (u64)(intptr_t)p);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        LOG_ERROR("Error calling Lua function: %s\n", lua_tostring(L, -1));
    }
}

void smlua_push_integer_field(int index, const char* name, lua_Integer val) {
    lua_pushinteger(gLuaState, val);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_number_field(int index, const char* name, lua_Number val) {
    lua_pushnumber(gLuaState, val);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_string_field(int index, const char* name, const char* val) {
    lua_pushstring(gLuaState, val);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_nil_field(int index, const char* name) {
    lua_pushnil(gLuaState);
    lua_setfield(gLuaState, index, name);
}

void smlua_push_table_field(int index, const char* name) {
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

lua_Integer smlua_get_integer_field(int index, const char* name) {
    if (lua_type(gLuaState, index) != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_get_integer_field received improper type '%d'", lua_type(gLuaState, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }
    lua_getfield(gLuaState, index, name);
    lua_Integer val = smlua_to_integer(gLuaState, -1);
    lua_pop(gLuaState, 1);
    return val;
}

lua_Number smlua_get_number_field(int index, const char* name) {
    if (lua_type(gLuaState, index) != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_get_number_field received improper type '%d'", lua_type(gLuaState, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }
    lua_getfield(gLuaState, index, name);
    lua_Number val = smlua_to_number(gLuaState, -1);
    lua_pop(gLuaState, 1);
    return val;
}

LuaFunction smlua_get_function_field(int index, const char *name) {
    if (lua_type(gLuaState, index) != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_get_function_field received improper type '%d'", lua_type(gLuaState, index));
        gSmLuaConvertSuccess = false;
        return 0;
    }
    lua_getfield(gLuaState, index, name);
    LuaFunction val = smlua_to_lua_function(gLuaState, -1);
    lua_pop(gLuaState, 1);
    return val;
}

///////////////////////////////////////////////////////////////////////////////////////////

s64 smlua_get_integer_mod_variable(u16 modIndex, const char* variable) {
    lua_State* L = gLuaState;

    if (!gActiveMods.entries) {
        LOG_ERROR("Could not find mod list entries");
        return 0;
    }

    // figure out entry
    struct Mod* mod = gActiveMods.entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Could not find mod list entry for modIndex: %u", modIndex);
        return 0;
    }
    
    u8 prevSuppress = gSmLuaSuppressErrors;

    int prevTop = lua_gettop(L);
    lua_getglobal(L, "_G"); // get global table
    lua_getfield(L, LUA_REGISTRYINDEX, mod->relativePath); // get the file's "global" table
    gSmLuaSuppressErrors = true;
    s64 value = smlua_get_integer_field(-1, (char*)variable);
    lua_settop(L, prevTop);

    // return variable
    gSmLuaSuppressErrors = prevSuppress;
    return value;
}

s64 smlua_get_any_integer_mod_variable(const char* variable) {
    lua_State* L = gLuaState;
    u8 prevSuppress = gSmLuaSuppressErrors;

    s64 value = 0;
    for (s32 i = 0; i < gActiveMods.entryCount; i++) {
        // figure out entry
        struct Mod* mod = gActiveMods.entries[i];

        int prevTop = lua_gettop(L);
        lua_getglobal(L, "_G"); // get global table
        lua_getfield(L, LUA_REGISTRYINDEX, mod->relativePath); // get the file's "global" table
        gSmLuaSuppressErrors = true;
        value = smlua_get_integer_field(-1, (char*)variable);
        lua_settop(L, prevTop);

        if (gSmLuaConvertSuccess) {
            gSmLuaSuppressErrors = prevSuppress;
            return value;
        }
    }

    // return variable
    gSmLuaSuppressErrors = prevSuppress;
    return value;
}

LuaFunction smlua_get_function_mod_variable(u16 modIndex, const char *variable) {
    lua_State *L = gLuaState;

    // figure out entry
    struct Mod *mod = gActiveMods.entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Could not find mod list entry for modIndex: %u", modIndex);
        return 0;
    }
    
    u8 prevSuppress = gSmLuaSuppressErrors;

    int prevTop = lua_gettop(L);
    lua_getglobal(L, "_G"); // get global table
    lua_getfield(L, LUA_REGISTRYINDEX, mod->relativePath); // get the file's "global" table
    gSmLuaSuppressErrors = true;
    LuaFunction value = smlua_get_function_field(-1, (char *)variable);
    lua_settop(L, prevTop);

    // return variable
    gSmLuaSuppressErrors = prevSuppress;
    return value;
}

LuaFunction smlua_get_any_function_mod_variable(const char *variable) {
    lua_State *L = gLuaState;
    u8 prevSuppress = gSmLuaSuppressErrors;

    LuaFunction value = 0;
    for (s32 i = 0; i < gActiveMods.entryCount; i++) {
        // figure out entry
        struct Mod *mod = gActiveMods.entries[i];

        int prevTop = lua_gettop(L);
        lua_getglobal(L, "_G"); // get global table
        lua_getfield(L, LUA_REGISTRYINDEX, mod->relativePath); // get the file's "global" table
        gSmLuaSuppressErrors = true;
        value = smlua_get_function_field(-1, (char *)variable);
        lua_settop(L, prevTop);

        if (gSmLuaConvertSuccess) {
            gSmLuaSuppressErrors = prevSuppress;
            return value;
        }
    }

    // return variable
    gSmLuaSuppressErrors = prevSuppress;
    return value;
}

///////////////////////////////////////////////////////////////////////////////////////////

const char* smlua_lnt_to_str(struct LSTNetworkType* lnt) {
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
        LOG_LUA("  [%d] %s:%d -- %s [%s]",
            level, info.short_src, info.currentline,
            (info.name ? info.name : "<unknown>"), info.what);
        ++level;
    }
}