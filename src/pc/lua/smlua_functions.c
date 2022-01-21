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

int smlua_play_sound(lua_State* L) {
    s32 soundsBits = lua_tointeger(L, 1);

    f32* pos = smlua_get_vec3f_from_buffer();
    pos[0] = smlua_get_number_field(2, "x");
    if (!gSmLuaConvertSuccess) { return 0; }
    pos[1] = smlua_get_number_field(2, "y");
    if (!gSmLuaConvertSuccess) { return 0; }
    pos[2] = smlua_get_number_field(2, "z");
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void play_sound(s32 soundBits, f32 * pos);
    play_sound(soundsBits, pos);

    return 1;
}

int smlua_func_perform_water_full_step(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    f32* nextPos = smlua_get_vec3f_from_buffer();
    nextPos[0] = smlua_get_number_field(2, "x");
    if (!gSmLuaConvertSuccess) { return 0; }
    nextPos[1] = smlua_get_number_field(2, "y");
    if (!gSmLuaConvertSuccess) { return 0; }
    nextPos[2] = smlua_get_number_field(2, "z");
    if (!gSmLuaConvertSuccess) { return 0; }

    extern u32 perform_water_full_step(struct MarioState *m, Vec3f nextPos);
    lua_pushinteger(L, perform_water_full_step(m, nextPos));
    return 1;
}

int smlua_func_apply_water_current(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    Vec3f step;
    step[0] = smlua_get_number_field(2, "x");
    if (!gSmLuaConvertSuccess) { return 0; }
    step[1] = smlua_get_number_field(2, "y");
    if (!gSmLuaConvertSuccess) { return 0; }
    step[2] = smlua_get_number_field(2, "z");
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void apply_water_current(struct MarioState *m, Vec3f step);
    apply_water_current(m, step);

    smlua_push_number_field(step[0], "x");
    smlua_push_number_field(step[1], "y");
    smlua_push_number_field(step[2], "z");

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
    smlua_bind_function(L, "play_sound", smlua_play_sound);
    smlua_bind_function(L, "perform_water_full_step", smlua_func_perform_water_full_step);
    smlua_bind_function(L, "apply_water_current", smlua_func_apply_water_current);
    smlua_bind_function(L, "atan2s", smlua_func_atan2s);
}