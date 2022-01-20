#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "game/mario_step.h"
#include "game/mario_actions_stationary.h"
#include "audio/external.h"
#include "object_fields.h"
#include "engine/math_util.h"

  //////////
 // misc //
//////////

int smlua_get_camera_position(lua_State* L) {
    if (gMarioStates[0].marioObj == NULL) {
        if (gCamera == NULL) {
            lua_pushnumber(L, 0);
            lua_pushnumber(L, 0);
            lua_pushnumber(L, 0);
            return 0;
        }
        lua_pushnumber(L, gCamera->pos[0]);
        lua_pushnumber(L, gCamera->pos[1]);
        lua_pushnumber(L, gCamera->pos[2]);
        return 0;
    }

    f32* pos = &gMarioStates[0].marioObj->header.gfx.cameraToObject[0];
    lua_pushnumber(L, pos[0]);
    lua_pushnumber(L, pos[1]);
    lua_pushnumber(L, pos[2]);
    return 1;
}

int smlua_check_fall_damage_or_get_stuck(lua_State* L) {
    u32 hardFallAction = lua_tointeger(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern s32 check_fall_damage_or_get_stuck(struct MarioState* m, u32 hardFallAction);
    lua_pushinteger(L, check_fall_damage_or_get_stuck(&gMarioStates[index], hardFallAction));
    return 1;
}

int smlua_play_sound(lua_State* L) {
    s32 soundsBits = lua_tointeger(L, -4);
    f32 pos[3] = { lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1) };
    extern void play_sound(s32 soundBits, f32 * pos);
    play_sound(soundsBits, pos);
    return 1;
}

int smlua_func_atan2s(lua_State* L) {
    f32 y = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 x = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, atan2s(y, x));
    return 1;
}

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    // misc
    smlua_bind_function(L, "get_camera_position", smlua_get_camera_position);
    smlua_bind_function(L, "check_fall_damage_or_get_stuck", smlua_check_fall_damage_or_get_stuck);
    smlua_bind_function(L, "play_sound", smlua_play_sound);
    smlua_bind_function(L, "atan2s", smlua_func_atan2s);
}