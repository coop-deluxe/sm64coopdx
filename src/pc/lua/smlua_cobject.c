#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "audio/external.h"
#include "object_fields.h"

#define LUA_VEC3S_FIELD_COUNT 3
static struct LuaObjectField sVec3sFields[LUA_VEC3S_FIELD_COUNT] = {
    { "x", LVT_S16, sizeof(s16) * 0, false, LOT_NONE },
    { "y", LVT_S16, sizeof(s16) * 1, false, LOT_NONE },
    { "z", LVT_S16, sizeof(s16) * 2, false, LOT_NONE },
};

#define LUA_VEC3F_FIELD_COUNT 3
static struct LuaObjectField sVec3fFields[LUA_VEC3F_FIELD_COUNT] = {
    { "x", LVT_F32, sizeof(f32) * 0, false, LOT_NONE },
    { "y", LVT_F32, sizeof(f32) * 1, false, LOT_NONE },
    { "z", LVT_F32, sizeof(f32) * 2, false, LOT_NONE },
};

struct LuaObjectTable sLuaObjectTable[LOT_MAX] = {
    { LOT_NONE,               NULL,                      0                                  },
    { LOT_VEC3S,              sVec3sFields,              LUA_VEC3S_FIELD_COUNT              },
    { LOT_VEC3F,              sVec3fFields,              LUA_VEC3F_FIELD_COUNT              },
};

static struct LuaObjectField* smlua_get_object_field(u16 lot, const char* key) {
    if (lot > LOT_AUTOGEN_MIN) {
        return smlua_get_object_field_autogen(lot, key);
    }

    struct LuaObjectTable* ot = &sLuaObjectTable[lot];
    // TODO: change this to binary search or hash table or something
    for (int i = 0; i < ot->fieldCount; i++) {
        if (!strcmp(ot->fields[i].key, key)) {
            return &ot->fields[i];
        }
    }
    return NULL;
}

bool smlua_valid_lot(u16 lot) {
    if (lot > LOT_NONE && lot < LOT_MAX) { return true; }
    if (lot > LOT_AUTOGEN_MIN && lot < LOT_AUTOGEN_MAX) { return true; }
    return false;
}

static int smlua__get_field(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    enum LuaObjectType lot = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    u64 pointer = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    const char* key = smlua_to_string(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    if (pointer == 0) {
        LOG_LUA("_get_field on null pointer");
        smlua_logline();
        return 0;
    }

    if (!smlua_valid_lot(lot)) {
        LOG_LUA("_get_field on invalid LOT '%u'", lot);
        smlua_logline();
        return 0;
    }

    if (!smlua_cobject_allowlist_contains(lot, pointer)) {
        LOG_LUA("_get_field received a pointer not in allow list. '%u', '%llu", lot, (u64)pointer);
        smlua_logline();
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(lot, key);
    if (data == NULL) {
        LOG_LUA("_get_field on invalid key '%s', lot '%d'", key, lot);
        smlua_logline();
        return 0;
    }

    u8* p = ((u8*)pointer) + data->valueOffset;
    switch (data->valueType) {
        case LVT_BOOL:       lua_pushboolean(L, *(u8* )p);              break;
        case LVT_U8:         lua_pushinteger(L, *(u8* )p);              break;
        case LVT_U16:        lua_pushinteger(L, *(u16*)p);              break;
        case LVT_U32:        lua_pushinteger(L, *(u32*)p);              break;
        case LVT_S8:         lua_pushinteger(L, *(s8* )p);              break;
        case LVT_S16:        lua_pushinteger(L, *(s16*)p);              break;
        case LVT_S32:        lua_pushinteger(L, *(s32*)p);              break;
        case LVT_F32:        lua_pushnumber( L, *(f32*)p);              break;
        case LVT_COBJECT:    smlua_push_object(L, data->lot, p);        break;
        case LVT_COBJECT_P:  smlua_push_object(L, data->lot, *(u8**)p); break;
        case LVT_STRING:     lua_pushstring(L, (char*)p);               break;
        case LVT_STRING_P:   lua_pushstring(L, *(char**)p);             break;
        default:
            LOG_LUA("_get_field on unimplemented type '%d', key '%s'", data->valueType, key);
            smlua_logline();
            return 0;
    }

    return 1;
}

static int smlua__set_field(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 4)) { return 0; }

    enum LuaObjectType lot = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    u64 pointer = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    const char* key = smlua_to_string(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    if (pointer == 0) {
        LOG_LUA("_set_field on null pointer");
        smlua_logline();
        return 0;
    }

    if (!smlua_valid_lot(lot)) {
        LOG_LUA("_set_field on invalid LOT '%u'", lot);
        smlua_logline();
        return 0;
    }

    if (!smlua_cobject_allowlist_contains(lot, pointer)) {
        LOG_LUA("_set_field received a pointer not in allow list. '%u', '%llu", lot, (u64)pointer);
        smlua_logline();
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(lot, key);
    if (data == NULL) {
        LOG_LUA("_set_field on invalid key '%s'", key);
        smlua_logline();
        return 0;
    }

    if (data->immutable) {
        LOG_LUA("_set_field on immutable key '%s'", key);
        smlua_logline();
        return 0;
    }

    u8* p = ((u8*)pointer) + data->valueOffset;
    switch (data->valueType) {
        case LVT_BOOL:*(u8*) p = smlua_to_boolean(L, -1); break;
        case LVT_U8:  *(u8*) p = smlua_to_integer(L, -1); break;
        case LVT_U16: *(u16*)p = smlua_to_integer(L, -1); break;
        case LVT_U32: *(u32*)p = smlua_to_integer(L, -1); break;
        case LVT_S8:  *(s8*) p = smlua_to_integer(L, -1); break;
        case LVT_S16: *(s16*)p = smlua_to_integer(L, -1); break;
        case LVT_S32: *(s32*)p = smlua_to_integer(L, -1); break;
        case LVT_F32: *(f32*)p = smlua_to_number(L, -1);  break;
        default:
            LOG_LUA("_set_field on unimplemented type '%d', key '%s'", data->valueType, key);
            smlua_logline();
            return 0;
    }
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("_set_field failed to retrieve value type '%d', key '%s'", data->valueType, key);
        smlua_logline();
        return 0;
    }

    return 1;
}

void smlua_cobject_init_globals(void) {
    lua_State* L = gLuaState;

    {
        lua_newtable(L);
        int t = lua_gettop(gLuaState);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            lua_pushinteger(L, i);
            smlua_push_object(L, LOT_MARIOSTATE, &gMarioStates[i]);
            lua_settable(L, t);
        }
        lua_setglobal(L, "gMarioStates");
    }

    {
        lua_newtable(L);
        int t = lua_gettop(gLuaState);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            lua_pushinteger(L, i);
            smlua_push_object(L, LOT_NETWORKPLAYER, &gNetworkPlayers[i]);
            lua_settable(L, t);
        }
        lua_setglobal(L, "gNetworkPlayers");
    }

    {
        lua_newtable(L);
        int t = lua_gettop(gLuaState);
        for (int i = 0; i < CT_MAX; i++) {
            lua_pushinteger(L, i);
            smlua_push_object(L, LOT_CHARACTER, &gCharacters[i]);
            lua_settable(L, t);
        }
        lua_setglobal(L, "gCharacters");
    }

}

void smlua_bind_cobject(void) {
    lua_State* L = gLuaState;

    smlua_bind_function(L, "_get_field", smlua__get_field);
    smlua_bind_function(L, "_set_field", smlua__set_field);

}
