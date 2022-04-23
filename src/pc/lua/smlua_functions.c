#include "smlua.h"
#include "smlua_cobject.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "game/mario_step.h"
#include "game/mario_actions_stationary.h"
#include "audio/external.h"
#include "object_fields.h"
#include "engine/math_util.h"

bool smlua_functions_valid_param_count(lua_State* L, int expected) {
    int top = lua_gettop(L);
    if (top != expected) {
        LOG_LUA_LINE("improper param count: expected %u, received %u", expected, top);
        return false;
    }
    return true;
}

bool smlua_functions_valid_param_range(lua_State* L, int min, int max) {
    int top = lua_gettop(L);
    if (top < min || top > max) {
        LOG_LUA_LINE("improper param count: expected (%u - %u), received %u", min, max, top);
        return false;
    }
    return true;
}

  //////////
 // misc //
//////////

int smlua_func_sins(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    f32 x = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushnumber(L, sins(x));
    return 1;
}

int smlua_func_coss(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    f32 x = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushnumber(L, coss(x));
    return 1;
}

int smlua_func_atan2s(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    f32 y = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 x = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, atan2s(y, x));
    return 1;
}

int smlua_func_init_mario_after_warp(lua_State* L) {
    if (network_player_connected_count() >= 2) {
        LOG_LUA_LINE("This function can only be used in single-player");
        return 0;
    }

    if(!smlua_functions_valid_param_count(L, 0)) { return 0; }

    extern void init_mario_after_warp(void);
    init_mario_after_warp();

    return 1;
}

int smlua_func_reset_level(lua_State* L) {
    if (network_player_connected_count() >= 2) {
        LOG_LUA_LINE("This function can only be used in single-player");
        return 0;
    }
    
    if(!smlua_functions_valid_param_count(L, 0)) { return 0; }

    gChangeLevel = gCurrLevelNum;

    return 1;
}

int smlua_func_network_init_object(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    struct Object* obj = smlua_to_cobject(L, 1, LOT_OBJECT);
    if (!gSmLuaConvertSuccess || obj == NULL) { return 0; }

    bool standardSync = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    if (lua_type(L, 3) != LUA_TNIL && lua_type(L, 3) != LUA_TTABLE) {
        LOG_LUA_LINE("network_init_object() called with an invalid type for param 3: %u", lua_type(L, 3));
        return 0;
    }

    struct SyncObject* so = network_init_object(obj, standardSync ? 4000.0f : SYNC_DISTANCE_ONLY_EVENTS);
    if (so == NULL) {
        LOG_LUA_LINE("Failed to allocate sync object.");
        return 0;
    }

    if (lua_type(L, 3) == LUA_TTABLE) {
        lua_pushnil(L);  // first key

        while (lua_next(L, 3) != 0) {
            // uses 'key' (at index -2) and 'value' (at index -1)
            if (lua_type(L, -1) != LUA_TSTRING) {
                LOG_LUA_LINE("Invalid type passed to network_init_object(): %u", lua_type(L, -1));
                lua_pop(L, 1); // pop value
                continue;
            }
            const char* fieldIdentifier = smlua_to_string(L, -1);
            if (!gSmLuaConvertSuccess) {
                LOG_LUA_LINE("Invalid field passed to network_init_object()");
                lua_pop(L, 1); // pop value
                continue;
            }

            struct LuaObjectField* data = smlua_get_object_field(LOT_OBJECT, fieldIdentifier);
            if (data == NULL) {
                data = smlua_get_custom_field(L, LOT_OBJECT, lua_gettop(L));
            }

            u8 lvtSize = 0;
            if ((data->valueType == LVT_U32) || (data->valueType == LVT_S32) || (data->valueType == LVT_F32)) { lvtSize = 32; }
            if ((data->valueType == LVT_U16) || (data->valueType == LVT_S16)) { lvtSize = 16; }
            if ((data->valueType == LVT_U8) || (data->valueType == LVT_S8)) { lvtSize = 8; }

            if (data == NULL || lvtSize == 0) {
                LOG_LUA_LINE("Invalid field passed to network_init_object(): %s", fieldIdentifier);
                lua_pop(L, 1); // pop value
                continue;
            }

            u8* field = ((u8*)(intptr_t)obj) + data->valueOffset;
            network_init_object_field_with_size(obj, field, lvtSize);

            lua_pop(L, 1); // pop value
        }
        lua_pop(L, 1); // pop key
    }

    return 1;
}

int smlua_func_network_send_object(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    struct Object* obj = smlua_to_cobject(L, 1, LOT_OBJECT);
    if (!gSmLuaConvertSuccess || obj == NULL) { return 0; }

    bool reliable = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    if (obj->oSyncID == 0 || gSyncObjects[obj->oSyncID].o != obj) {
        LOG_LUA_LINE("Failed to retrieve sync object.");
        return 0;
    }

    network_send_object_reliability(obj, reliable);

    return 1;
}

int smlua_func_network_send(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }
    network_send_lua_custom(true);
}

int smlua_func_network_send_to(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }
    network_send_lua_custom(false);
}

  //////////
 // bind //
//////////

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    // misc
    smlua_bind_function(L, "sins", smlua_func_sins);
    smlua_bind_function(L, "coss", smlua_func_coss);
    smlua_bind_function(L, "atan2s", smlua_func_atan2s);
    smlua_bind_function(L, "init_mario_after_warp", smlua_func_init_mario_after_warp);
    smlua_bind_function(L, "network_init_object", smlua_func_network_init_object);
    smlua_bind_function(L, "network_send_object", smlua_func_network_send_object);
    smlua_bind_function(L, "reset_level", smlua_func_reset_level);
    smlua_bind_function(L, "network_send", smlua_func_network_send);
    smlua_bind_function(L, "network_send_to", smlua_func_network_send_to);
}
