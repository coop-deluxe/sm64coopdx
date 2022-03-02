#include "smlua.h"

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
        LOG_LUA("improper param count: expected %u, received %u", expected, top);
        smlua_logline();
        return false;
    }
    return true;
}

bool smlua_functions_valid_param_range(lua_State* L, int min, int max) {
    int top = lua_gettop(L);
    if (top < min || top > max) {
        LOG_LUA("improper param count: expected (%u - %u), received %u", min, max, top);
        smlua_logline();
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
    if (network_player_connected_count() < 2) {
        if(!smlua_functions_valid_param_count(L, 0)) { return 0; }
    

        init_mario_after_warp();
    
        return 1;
    } else {
        LOG_LUA("This function can only be used in single-player");
    }
    return 0;
}

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    // misc
    smlua_bind_function(L, "sins", smlua_func_sins);
    smlua_bind_function(L, "coss", smlua_func_coss);
    smlua_bind_function(L, "atan2s", smlua_func_atan2s);
    smlua_bind_function(L, "init_mario_after_warp", smlua_func_init_mario_after_warp);
}