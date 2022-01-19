#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "game/mario_step.h"
#include "game/mario_actions_stationary.h"
#include "audio/external.h"
#include "object_fields.h"
#include "engine/math_util.h"

  /////////////
 // mario.h //
/////////////

int smlua_func_is_anim_at_end(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, is_anim_at_end(m));
    return 1;
}

int smlua_func_is_anim_past_end(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, is_anim_past_end(m));
    return 1;
}

int smlua_func_set_mario_animation(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 targetAnimID = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, set_mario_animation(m, targetAnimID));
    return 1;
}

int smlua_func_set_mario_anim_with_accel(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 targetAnimID = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 accel = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, set_mario_anim_with_accel(m, targetAnimID, accel));
    return 1;
}

int smlua_func_set_anim_to_frame(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 animFrame = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    set_anim_to_frame(m, animFrame);
    return 1;
}

int smlua_func_is_anim_past_frame(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 animFrame = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, is_anim_past_frame(m, animFrame));
    return 1;
}

/*
int smlua_func_find_mario_anim_flags_and_translation(lua_State* L) {
    struct Object* o <--- UNIMPLEMENTED
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 yaw = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    Vec3s translation = (Vec3s)smlua_to_cobject(L, 3, LOT_VEC3S);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, find_mario_anim_flags_and_translation(o, yaw, translation));
    return 1;
}
*/

int smlua_func_update_mario_pos_for_anim(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    update_mario_pos_for_anim(m);
    return 1;
}

int smlua_func_return_mario_anim_y_translation(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, return_mario_anim_y_translation(m));
    return 1;
}

int smlua_func_play_sound_if_no_flag(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 flags = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_sound_if_no_flag(m, soundBits, flags);
    return 1;
}

int smlua_func_play_mario_jump_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_jump_sound(m);
    return 1;
}

int smlua_func_adjust_sound_for_speed(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    adjust_sound_for_speed(m);
    return 1;
}

int smlua_func_play_sound_and_spawn_particles(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 waveParticleType = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_sound_and_spawn_particles(m, soundBits, waveParticleType);
    return 1;
}

int smlua_func_play_mario_action_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 waveParticleType = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_action_sound(m, soundBits, waveParticleType);
    return 1;
}

int smlua_func_play_mario_landing_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_landing_sound(m, soundBits);
    return 1;
}

int smlua_func_play_mario_landing_sound_once(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_landing_sound_once(m, soundBits);
    return 1;
}

int smlua_func_play_mario_heavy_landing_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_heavy_landing_sound(m, soundBits);
    return 1;
}

int smlua_func_play_mario_heavy_landing_sound_once(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 soundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_heavy_landing_sound_once(m, soundBits);
    return 1;
}

int smlua_func_play_mario_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 primarySoundBits = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 scondarySoundBits = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_mario_sound(m, primarySoundBits, scondarySoundBits);
    return 1;
}

int smlua_func_mario_set_bubbled(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    mario_set_bubbled(m);
    return 1;
}

int smlua_func_mario_set_forward_vel(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 speed = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    mario_set_forward_vel(m, speed);
    return 1;
}

int smlua_func_mario_get_floor_class(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_get_floor_class(m));
    return 1;
}

int smlua_func_mario_get_terrain_sound_addend(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_get_terrain_sound_addend(m));
    return 1;
}

/*
int smlua_func_resolve_and_return_wall_collisions(lua_State* L) {
    Vec3f pos = (Vec3f)smlua_to_cobject(L, 1, LOT_VEC3F);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 offset = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 radius = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    UNIMPLEMENTED -->(L, resolve_and_return_wall_collisions(pos, offset, radius));
    return 1;
}
*/

/*
int smlua_func_vec3f_find_ceil(lua_State* L) {
    Vec3f pos = (Vec3f)smlua_to_cobject(L, 1, LOT_VEC3F);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 height = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    struct Surface** ceil <--- UNIMPLEMENTED
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushnumber(L, vec3f_find_ceil(pos, height, ceil));
    return 1;
}
*/

int smlua_func_mario_facing_downhill(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 turnYaw = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_facing_downhill(m, turnYaw));
    return 1;
}

int smlua_func_mario_floor_is_slippery(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_floor_is_slippery(m));
    return 1;
}

int smlua_func_mario_floor_is_slope(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_floor_is_slope(m));
    return 1;
}

int smlua_func_mario_floor_is_steep(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_floor_is_steep(m));
    return 1;
}

int smlua_func_find_floor_height_relative_polar(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 angleFromMario = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 distFromMario = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushnumber(L, find_floor_height_relative_polar(m, angleFromMario, distFromMario));
    return 1;
}

int smlua_func_find_floor_slope(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 yawOffset = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, find_floor_slope(m, yawOffset));
    return 1;
}

int smlua_func_update_mario_sound_and_camera(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    update_mario_sound_and_camera(m);
    return 1;
}

int smlua_func_set_steep_jump_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    set_steep_jump_action(m);
    return 1;
}

int smlua_func_set_mario_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionArg = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, set_mario_action(m, action, actionArg));
    return 1;
}

int smlua_func_set_jump_from_landing(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, set_jump_from_landing(m));
    return 1;
}

int smlua_func_set_jumping_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionArg = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, set_jumping_action(m, action, actionArg));
    return 1;
}

int smlua_func_drop_and_set_mario_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionArg = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, drop_and_set_mario_action(m, action, actionArg));
    return 1;
}

int smlua_func_hurt_and_set_mario_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionArg = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 hurtCounter = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, hurt_and_set_mario_action(m, action, actionArg, hurtCounter));
    return 1;
}

int smlua_func_check_common_action_exits(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, check_common_action_exits(m));
    return 1;
}

int smlua_func_check_common_hold_action_exits(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, check_common_hold_action_exits(m));
    return 1;
}

int smlua_func_transition_submerged_to_walking(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, transition_submerged_to_walking(m));
    return 1;
}

int smlua_func_set_water_plunge_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, set_water_plunge_action(m));
    return 1;
}

/*
int smlua_func_execute_mario_action(lua_State* L) {
    struct Object* o <--- UNIMPLEMENTED
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, execute_mario_action(o));
    return 1;
}
*/

int smlua_func_force_idle_state(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, force_idle_state(m));
    return 1;
}

int smlua_func_init_mario(UNUSED lua_State* L) {
    init_mario();
    return 1;
}

int smlua_func_init_mario_from_save_file(UNUSED lua_State* L) {
    init_mario_from_save_file();
    return 1;
}

  ////////////////////////////
 // mario_actions_moving.c //
////////////////////////////

int smlua_func_tilt_body_running(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s16 tilt_body_running(struct MarioState* m);
    lua_pushinteger(L, tilt_body_running(m));
    return 1;
}

int smlua_func_play_step_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 frame1 = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 frame2 = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void play_step_sound(struct MarioState* m, s16 frame1, s16 frame2);
    play_step_sound(m, frame1, frame2);
    return 1;
}

int smlua_func_align_with_floor(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void align_with_floor(struct MarioState* m);
    align_with_floor(m);
    return 1;
}

int smlua_func_begin_walking_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 forwardVel = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionArg = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 begin_walking_action(struct MarioState* m, f32 forwardVel, u32 action, u32 actionArg);
    lua_pushinteger(L, begin_walking_action(m, forwardVel, action, actionArg));
    return 1;
}

int smlua_func_check_ledge_climb_down(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void check_ledge_climb_down(struct MarioState* m);
    check_ledge_climb_down(m);
    return 1;
}

int smlua_func_slide_bonk(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 fastAction = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 slowAction = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void slide_bonk(struct MarioState* m, u32 fastAction, u32 slowAction);
    slide_bonk(m, fastAction, slowAction);
    return 1;
}

int smlua_func_set_triple_jump_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionArg = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 set_triple_jump_action(struct MarioState* m, UNUSED u32 action, UNUSED u32 actionArg);
    lua_pushinteger(L, set_triple_jump_action(m, action, actionArg));
    return 1;
}

int smlua_func_update_sliding_angle(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 accel = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 lossFactor = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_sliding_angle(struct MarioState* m, f32 accel, f32 lossFactor);
    update_sliding_angle(m, accel, lossFactor);
    return 1;
}

int smlua_func_update_sliding(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 stopSpeed = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 update_sliding(struct MarioState* m, f32 stopSpeed);
    lua_pushinteger(L, update_sliding(m, stopSpeed));
    return 1;
}

int smlua_func_apply_slope_accel(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void apply_slope_accel(struct MarioState* m);
    apply_slope_accel(m);
    return 1;
}

int smlua_func_apply_landing_accel(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 frictionFactor = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 apply_landing_accel(struct MarioState* m, f32 frictionFactor);
    lua_pushinteger(L, apply_landing_accel(m, frictionFactor));
    return 1;
}

int smlua_func_update_shell_speed(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_shell_speed(struct MarioState* m);
    update_shell_speed(m);
    return 1;
}

int smlua_func_apply_slope_decel(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 decelCoef = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 apply_slope_decel(struct MarioState* m, f32 decelCoef);
    lua_pushinteger(L, apply_slope_decel(m, decelCoef));
    return 1;
}

int smlua_func_update_decelerating_speed(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 update_decelerating_speed(struct MarioState* m);
    lua_pushinteger(L, update_decelerating_speed(m));
    return 1;
}

int smlua_func_update_walking_speed(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_walking_speed(struct MarioState* m);
    update_walking_speed(m);
    return 1;
}

int smlua_func_should_begin_sliding(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 should_begin_sliding(struct MarioState* m);
    lua_pushinteger(L, should_begin_sliding(m));
    return 1;
}

int smlua_func_analog_stick_held_back(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 analog_stick_held_back(struct MarioState* m);
    lua_pushinteger(L, analog_stick_held_back(m));
    return 1;
}

int smlua_func_check_ground_dive_or_punch(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_ground_dive_or_punch(struct MarioState* m);
    lua_pushinteger(L, check_ground_dive_or_punch(m));
    return 1;
}

int smlua_func_begin_braking_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 begin_braking_action(struct MarioState* m);
    lua_pushinteger(L, begin_braking_action(m));
    return 1;
}

int smlua_func_anim_and_audio_for_walk(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void anim_and_audio_for_walk(struct MarioState* m);
    anim_and_audio_for_walk(m);
    return 1;
}

int smlua_func_anim_and_audio_for_hold_walk(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void anim_and_audio_for_hold_walk(struct MarioState* m);
    anim_and_audio_for_hold_walk(m);
    return 1;
}

int smlua_func_anim_and_audio_for_heavy_walk(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void anim_and_audio_for_heavy_walk(struct MarioState* m);
    anim_and_audio_for_heavy_walk(m);
    return 1;
}

int smlua_func_push_or_sidle_wall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32* startPos = (f32*)smlua_to_cobject(L, 2, LOT_VEC3F);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void push_or_sidle_wall(struct MarioState* m, f32* startPos);
    push_or_sidle_wall(m, startPos);
    return 1;
}

int smlua_func_tilt_body_walking(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 startYaw = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void tilt_body_walking(struct MarioState* m, s16 startYaw);
    tilt_body_walking(m, startYaw);
    return 1;
}

int smlua_func_tilt_body_ground_shell(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 startYaw = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void tilt_body_ground_shell(struct MarioState* m, s16 startYaw);
    tilt_body_ground_shell(m, startYaw);
    return 1;
}

int smlua_func_tilt_body_butt_slide(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void tilt_body_butt_slide(struct MarioState* m);
    tilt_body_butt_slide(m);
    return 1;
}

int smlua_func_common_slide_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 endAction = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 airAction = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 animation = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void common_slide_action(struct MarioState* m, u32 endAction, u32 airAction, s32 animation);
    common_slide_action(m, endAction, airAction, animation);
    return 1;
}

int smlua_func_stomach_slide_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 stopAction = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 airAction = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 animation = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 stomach_slide_action(struct MarioState* m, u32 stopAction, u32 airAction, s32 animation);
    lua_pushinteger(L, stomach_slide_action(m, stopAction, airAction, animation));
    return 1;
}

int smlua_func_common_ground_knockback_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 animation = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 arg2 = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 arg3 = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 arg4 = smlua_to_integer(L, 5);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 common_ground_knockback_action(struct MarioState* m, s32 animation, s32 arg2, s32 arg3, s32 arg4);
    lua_pushinteger(L, common_ground_knockback_action(m, animation, arg2, arg3, arg4));
    return 1;
}

int smlua_func_common_landing_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 animation = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 airAction = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern u32 common_landing_action(struct MarioState* m, s16 animation, u32 airAction);
    lua_pushinteger(L, common_landing_action(m, animation, airAction));
    return 1;
}

int smlua_func_check_common_moving_cancels(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_common_moving_cancels(struct MarioState* m);
    lua_pushinteger(L, check_common_moving_cancels(m));
    return 1;
}

int smlua_func_mario_execute_moving_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 mario_execute_moving_action(struct MarioState* m);
    lua_pushinteger(L, mario_execute_moving_action(m));
    return 1;
}

  //////////////////
 // mario_step.h //
//////////////////

int smlua_func_mario_bonk_reflection(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 arg1 = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    mario_bonk_reflection(arg0, arg1);
    return 1;
}

/*
int smlua_func_transfer_bully_speed(lua_State* L) {
    struct BullyCollisionData* obj1 <--- UNIMPLEMENTED
    if (!gSmLuaConvertSuccess) { return 0; }
    struct BullyCollisionData* obj2 <--- UNIMPLEMENTED
    if (!gSmLuaConvertSuccess) { return 0; }

    transfer_bully_speed(obj1, obj2);
    return 1;
}
*/

/*
int smlua_func_init_bully_collision_data(lua_State* L) {
    struct BullyCollisionData* data <--- UNIMPLEMENTED
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 posX = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 posZ = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 forwardVel = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 yaw = smlua_to_integer(L, 5);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 conversionRatio = smlua_to_number(L, 6);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 radius = smlua_to_number(L, 7);
    if (!gSmLuaConvertSuccess) { return 0; }

    init_bully_collision_data(data, posX, posZ, forwardVel, yaw, conversionRatio, radius);
    return 1;
}
*/

int smlua_func_mario_update_quicksand(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 arg1 = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_update_quicksand(arg0, arg1));
    return 1;
}

int smlua_func_mario_push_off_steep_floor(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 arg1 = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 arg2 = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_push_off_steep_floor(arg0, arg1, arg2));
    return 1;
}

int smlua_func_mario_update_moving_sand(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_update_moving_sand(arg0));
    return 1;
}

int smlua_func_mario_update_windy_ground(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_update_windy_ground(arg0));
    return 1;
}

int smlua_func_stop_and_set_height_to_floor(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    stop_and_set_height_to_floor(arg0);
    return 1;
}

int smlua_func_stationary_ground_step(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, stationary_ground_step(arg0));
    return 1;
}

int smlua_func_perform_ground_step(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, perform_ground_step(arg0));
    return 1;
}

int smlua_func_perform_air_step(lua_State* L) {
    struct MarioState* arg0 = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 arg1 = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, perform_air_step(arg0, arg1));
    return 1;
}

int smlua_func_set_vel_from_pitch_and_yaw(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    set_vel_from_pitch_and_yaw(m);
    return 1;
}

  //////////////////////////////
 // mario_actions_airborne.c //
//////////////////////////////

int smlua_func_play_flip_sounds(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 frame1 = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 frame2 = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    s16 frame3 = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void play_flip_sounds(struct MarioState* m, s16 frame1, s16 frame2, s16 frame3);
    play_flip_sounds(m, frame1, frame2, frame3);
    return 1;
}

int smlua_func_play_far_fall_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void play_far_fall_sound(struct MarioState* m);
    play_far_fall_sound(m);
    return 1;
}

int smlua_func_play_knockback_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void play_knockback_sound(struct MarioState* m);
    play_knockback_sound(m);
    return 1;
}

int smlua_func_lava_boost_on_wall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 lava_boost_on_wall(struct MarioState* m);
    lua_pushinteger(L, lava_boost_on_wall(m));
    return 1;
}

int smlua_func_check_fall_damage(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 hardFallAction = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_fall_damage(struct MarioState* m, u32 hardFallAction);
    lua_pushinteger(L, check_fall_damage(m, hardFallAction));
    return 1;
}

int smlua_func_check_kick_or_dive_in_air(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_kick_or_dive_in_air(struct MarioState* m);
    lua_pushinteger(L, check_kick_or_dive_in_air(m));
    return 1;
}

int smlua_func_should_get_stuck_in_ground(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 should_get_stuck_in_ground(struct MarioState* m);
    lua_pushinteger(L, should_get_stuck_in_ground(m));
    return 1;
}

int smlua_func_check_fall_damage_or_get_stuck(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 hardFallAction = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_fall_damage_or_get_stuck(struct MarioState* m, u32 hardFallAction);
    lua_pushinteger(L, check_fall_damage_or_get_stuck(m, hardFallAction));
    return 1;
}

int smlua_func_check_horizontal_wind(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_horizontal_wind(struct MarioState* m);
    lua_pushinteger(L, check_horizontal_wind(m));
    return 1;
}

int smlua_func_update_air_with_turn(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_air_with_turn(struct MarioState* m);
    update_air_with_turn(m);
    return 1;
}

int smlua_func_update_air_without_turn(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_air_without_turn(struct MarioState* m);
    update_air_without_turn(m);
    return 1;
}

int smlua_func_update_lava_boost_or_twirling(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_lava_boost_or_twirling(struct MarioState* m);
    update_lava_boost_or_twirling(m);
    return 1;
}

int smlua_func_update_flying_yaw(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_flying_yaw(struct MarioState* m);
    update_flying_yaw(m);
    return 1;
}

int smlua_func_update_flying_pitch(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_flying_pitch(struct MarioState* m);
    update_flying_pitch(m);
    return 1;
}

int smlua_func_update_flying(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern void update_flying(struct MarioState* m);
    update_flying(m);
    return 1;
}

int smlua_func_common_air_action_step(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 landAction = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 animation = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 stepArg = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern u32 common_air_action_step(struct MarioState* m, u32 landAction, s32 animation, u32 stepArg);
    lua_pushinteger(L, common_air_action_step(m, landAction, animation, stepArg));
    return 1;
}

int smlua_func_act_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_jump(struct MarioState* m);
    lua_pushinteger(L, act_jump(m));
    return 1;
}

int smlua_func_act_double_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_double_jump(struct MarioState* m);
    lua_pushinteger(L, act_double_jump(m));
    return 1;
}

int smlua_func_act_triple_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_triple_jump(struct MarioState* m);
    lua_pushinteger(L, act_triple_jump(m));
    return 1;
}

int smlua_func_act_backflip(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_backflip(struct MarioState* m);
    lua_pushinteger(L, act_backflip(m));
    return 1;
}

int smlua_func_act_freefall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_freefall(struct MarioState* m);
    lua_pushinteger(L, act_freefall(m));
    return 1;
}

int smlua_func_act_hold_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_hold_jump(struct MarioState* m);
    lua_pushinteger(L, act_hold_jump(m));
    return 1;
}

int smlua_func_act_hold_freefall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_hold_freefall(struct MarioState* m);
    lua_pushinteger(L, act_hold_freefall(m));
    return 1;
}

int smlua_func_act_side_flip(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_side_flip(struct MarioState* m);
    lua_pushinteger(L, act_side_flip(m));
    return 1;
}

int smlua_func_act_wall_kick_air(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_wall_kick_air(struct MarioState* m);
    lua_pushinteger(L, act_wall_kick_air(m));
    return 1;
}

int smlua_func_act_long_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_long_jump(struct MarioState* m);
    lua_pushinteger(L, act_long_jump(m));
    return 1;
}

int smlua_func_act_riding_shell_air(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_riding_shell_air(struct MarioState* m);
    lua_pushinteger(L, act_riding_shell_air(m));
    return 1;
}

int smlua_func_act_twirling(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_twirling(struct MarioState* m);
    lua_pushinteger(L, act_twirling(m));
    return 1;
}

int smlua_func_act_dive(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_dive(struct MarioState* m);
    lua_pushinteger(L, act_dive(m));
    return 1;
}

int smlua_func_act_air_throw(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_air_throw(struct MarioState* m);
    lua_pushinteger(L, act_air_throw(m));
    return 1;
}

int smlua_func_act_water_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_water_jump(struct MarioState* m);
    lua_pushinteger(L, act_water_jump(m));
    return 1;
}

int smlua_func_act_hold_water_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_hold_water_jump(struct MarioState* m);
    lua_pushinteger(L, act_hold_water_jump(m));
    return 1;
}

int smlua_func_act_steep_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_steep_jump(struct MarioState* m);
    lua_pushinteger(L, act_steep_jump(m));
    return 1;
}

int smlua_func_act_ground_pound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_ground_pound(struct MarioState* m);
    lua_pushinteger(L, act_ground_pound(m));
    return 1;
}

int smlua_func_act_burning_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_burning_jump(struct MarioState* m);
    lua_pushinteger(L, act_burning_jump(m));
    return 1;
}

int smlua_func_act_burning_fall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_burning_fall(struct MarioState* m);
    lua_pushinteger(L, act_burning_fall(m));
    return 1;
}

int smlua_func_act_crazy_box_bounce(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_crazy_box_bounce(struct MarioState* m);
    lua_pushinteger(L, act_crazy_box_bounce(m));
    return 1;
}

int smlua_func_check_wall_kick(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_wall_kick(struct MarioState* m);
    lua_pushinteger(L, check_wall_kick(m));
    return 1;
}

int smlua_func_act_backward_air_kb(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_backward_air_kb(struct MarioState* m);
    lua_pushinteger(L, act_backward_air_kb(m));
    return 1;
}

int smlua_func_act_forward_air_kb(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_forward_air_kb(struct MarioState* m);
    lua_pushinteger(L, act_forward_air_kb(m));
    return 1;
}

int smlua_func_act_hard_backward_air_kb(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_hard_backward_air_kb(struct MarioState* m);
    lua_pushinteger(L, act_hard_backward_air_kb(m));
    return 1;
}

int smlua_func_act_hard_forward_air_kb(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_hard_forward_air_kb(struct MarioState* m);
    lua_pushinteger(L, act_hard_forward_air_kb(m));
    return 1;
}

int smlua_func_act_thrown_backward(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_thrown_backward(struct MarioState* m);
    lua_pushinteger(L, act_thrown_backward(m));
    return 1;
}

int smlua_func_act_thrown_forward(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_thrown_forward(struct MarioState* m);
    lua_pushinteger(L, act_thrown_forward(m));
    return 1;
}

int smlua_func_act_soft_bonk(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_soft_bonk(struct MarioState* m);
    lua_pushinteger(L, act_soft_bonk(m));
    return 1;
}

int smlua_func_act_getting_blown(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_getting_blown(struct MarioState* m);
    lua_pushinteger(L, act_getting_blown(m));
    return 1;
}

int smlua_func_act_air_hit_wall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_air_hit_wall(struct MarioState* m);
    lua_pushinteger(L, act_air_hit_wall(m));
    return 1;
}

int smlua_func_act_forward_rollout(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_forward_rollout(struct MarioState* m);
    lua_pushinteger(L, act_forward_rollout(m));
    return 1;
}

int smlua_func_act_backward_rollout(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_backward_rollout(struct MarioState* m);
    lua_pushinteger(L, act_backward_rollout(m));
    return 1;
}

int smlua_func_act_butt_slide_air(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_butt_slide_air(struct MarioState* m);
    lua_pushinteger(L, act_butt_slide_air(m));
    return 1;
}

int smlua_func_act_hold_butt_slide_air(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_hold_butt_slide_air(struct MarioState* m);
    lua_pushinteger(L, act_hold_butt_slide_air(m));
    return 1;
}

int smlua_func_act_lava_boost(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_lava_boost(struct MarioState* m);
    lua_pushinteger(L, act_lava_boost(m));
    return 1;
}

int smlua_func_act_slide_kick(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_slide_kick(struct MarioState* m);
    lua_pushinteger(L, act_slide_kick(m));
    return 1;
}

int smlua_func_act_jump_kick(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_jump_kick(struct MarioState* m);
    lua_pushinteger(L, act_jump_kick(m));
    return 1;
}

int smlua_func_act_shot_from_cannon(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_shot_from_cannon(struct MarioState* m);
    lua_pushinteger(L, act_shot_from_cannon(m));
    return 1;
}

int smlua_func_act_flying(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_flying(struct MarioState* m);
    lua_pushinteger(L, act_flying(m));
    return 1;
}

int smlua_func_act_riding_hoot(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_riding_hoot(struct MarioState* m);
    lua_pushinteger(L, act_riding_hoot(m));
    return 1;
}

int smlua_func_act_flying_triple_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_flying_triple_jump(struct MarioState* m);
    lua_pushinteger(L, act_flying_triple_jump(m));
    return 1;
}

int smlua_func_act_top_of_pole_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_top_of_pole_jump(struct MarioState* m);
    lua_pushinteger(L, act_top_of_pole_jump(m));
    return 1;
}

int smlua_func_act_vertical_wind(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_vertical_wind(struct MarioState* m);
    lua_pushinteger(L, act_vertical_wind(m));
    return 1;
}

int smlua_func_act_special_triple_jump(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 act_special_triple_jump(struct MarioState* m);
    lua_pushinteger(L, act_special_triple_jump(m));
    return 1;
}

int smlua_func_check_common_airborne_cancels(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 check_common_airborne_cancels(struct MarioState* m);
    lua_pushinteger(L, check_common_airborne_cancels(m));
    return 1;
}

int smlua_func_mario_execute_airborne_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    extern s32 mario_execute_airborne_action(struct MarioState* m);
    lua_pushinteger(L, mario_execute_airborne_action(m));
    return 1;
}

  //////////////
 // camera.h //
//////////////

int smlua_func_set_camera_shake_from_hit(lua_State* L) {
    s16 shake = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    set_camera_shake_from_hit(shake);
    return 1;
}

int smlua_func_set_environmental_camera_shake(lua_State* L) {
    s16 shake = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    set_environmental_camera_shake(shake);
    return 1;
}

int smlua_func_set_camera_shake_from_point(lua_State* L) {
    s16 shake = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 posX = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 posY = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 posZ = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    set_camera_shake_from_point(shake, posX, posY, posZ);
    return 1;
}

  ////////////////////////////////
 // mario_actions_stationary.h //
////////////////////////////////


int smlua_func_check_common_idle_cancels(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, check_common_idle_cancels(m));
    return 1;
}

int smlua_func_check_common_hold_idle_cancels(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, check_common_hold_idle_cancels(m));
    return 1;
}

int smlua_func_act_idle(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_idle(m));
    return 1;
}

int smlua_func_play_anim_sound(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 actionState = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 animFrame = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 sound = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { return 0; }

    play_anim_sound(m, actionState, animFrame, sound);
    return 1;
}

int smlua_func_act_start_sleeping(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_start_sleeping(m));
    return 1;
}

int smlua_func_act_sleeping(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_sleeping(m));
    return 1;
}

int smlua_func_act_waking_up(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_waking_up(m));
    return 1;
}

int smlua_func_act_shivering(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_shivering(m));
    return 1;
}

int smlua_func_act_coughing(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_coughing(m));
    return 1;
}

int smlua_func_act_standing_against_wall(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_standing_against_wall(m));
    return 1;
}

int smlua_func_act_in_quicksand(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_in_quicksand(m));
    return 1;
}

int smlua_func_act_crouching(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_crouching(m));
    return 1;
}

int smlua_func_act_panting(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_panting(m));
    return 1;
}

int smlua_func_stopping_step(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 animID = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    stopping_step(m, animID, action);
    return 1;
}

int smlua_func_act_braking_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_braking_stop(m));
    return 1;
}

int smlua_func_act_butt_slide_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_butt_slide_stop(m));
    return 1;
}

int smlua_func_act_hold_butt_slide_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_hold_butt_slide_stop(m));
    return 1;
}

int smlua_func_act_slide_kick_slide_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_slide_kick_slide_stop(m));
    return 1;
}

int smlua_func_act_start_crouching(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_start_crouching(m));
    return 1;
}

int smlua_func_act_stop_crouching(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_stop_crouching(m));
    return 1;
}

int smlua_func_act_start_crawling(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_start_crawling(m));
    return 1;
}

int smlua_func_act_stop_crawling(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_stop_crawling(m));
    return 1;
}

int smlua_func_act_shockwave_bounce(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_shockwave_bounce(m));
    return 1;
}

int smlua_func_landing_step(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    s32 arg1 = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, landing_step(m, arg1, action));
    return 1;
}

int smlua_func_check_common_landing_cancels(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }
    u32 action = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, check_common_landing_cancels(m, action));
    return 1;
}

int smlua_func_act_jump_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_jump_land_stop(m));
    return 1;
}

int smlua_func_act_double_jump_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_double_jump_land_stop(m));
    return 1;
}

int smlua_func_act_side_flip_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_side_flip_land_stop(m));
    return 1;
}

int smlua_func_act_freefall_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_freefall_land_stop(m));
    return 1;
}

int smlua_func_act_triple_jump_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_triple_jump_land_stop(m));
    return 1;
}

int smlua_func_act_backflip_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_backflip_land_stop(m));
    return 1;
}

int smlua_func_act_lava_boost_land(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_lava_boost_land(m));
    return 1;
}

int smlua_func_act_long_jump_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_long_jump_land_stop(m));
    return 1;
}

int smlua_func_act_hold_jump_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_hold_jump_land_stop(m));
    return 1;
}

int smlua_func_act_hold_freefall_land_stop(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_hold_freefall_land_stop(m));
    return 1;
}

int smlua_func_act_air_throw_land(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_air_throw_land(m));
    return 1;
}

int smlua_func_act_twirl_land(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_twirl_land(m));
    return 1;
}

int smlua_func_act_ground_pound_land(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_ground_pound_land(m));
    return 1;
}

int smlua_func_act_first_person(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, act_first_person(m));
    return 1;
}

int smlua_func_check_common_stationary_cancels(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, check_common_stationary_cancels(m));
    return 1;
}

int smlua_func_mario_execute_stationary_action(lua_State* L) {
    struct MarioState* m = (struct MarioState*)smlua_to_cobject(L, 1, LOT_MARIO_STATE);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, mario_execute_stationary_action(m));
    return 1;
}

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

      /////////////
     // mario.h //
    /////////////

    smlua_bind_function(L, "is_anim_at_end", smlua_func_is_anim_at_end);
    smlua_bind_function(L, "is_anim_past_end", smlua_func_is_anim_past_end);
    smlua_bind_function(L, "set_mario_animation", smlua_func_set_mario_animation);
    smlua_bind_function(L, "set_mario_anim_with_accel", smlua_func_set_mario_anim_with_accel);
    smlua_bind_function(L, "set_anim_to_frame", smlua_func_set_anim_to_frame);
    smlua_bind_function(L, "is_anim_past_frame", smlua_func_is_anim_past_frame);
    //smlua_bind_function(L, "find_mario_anim_flags_and_translation", smlua_func_find_mario_anim_flags_and_translation); <--- UNIMPLEMENTED
    smlua_bind_function(L, "update_mario_pos_for_anim", smlua_func_update_mario_pos_for_anim);
    smlua_bind_function(L, "return_mario_anim_y_translation", smlua_func_return_mario_anim_y_translation);
    smlua_bind_function(L, "play_sound_if_no_flag", smlua_func_play_sound_if_no_flag);
    smlua_bind_function(L, "play_mario_jump_sound", smlua_func_play_mario_jump_sound);
    smlua_bind_function(L, "adjust_sound_for_speed", smlua_func_adjust_sound_for_speed);
    smlua_bind_function(L, "play_sound_and_spawn_particles", smlua_func_play_sound_and_spawn_particles);
    smlua_bind_function(L, "play_mario_action_sound", smlua_func_play_mario_action_sound);
    smlua_bind_function(L, "play_mario_landing_sound", smlua_func_play_mario_landing_sound);
    smlua_bind_function(L, "play_mario_landing_sound_once", smlua_func_play_mario_landing_sound_once);
    smlua_bind_function(L, "play_mario_heavy_landing_sound", smlua_func_play_mario_heavy_landing_sound);
    smlua_bind_function(L, "play_mario_heavy_landing_sound_once", smlua_func_play_mario_heavy_landing_sound_once);
    smlua_bind_function(L, "play_mario_sound", smlua_func_play_mario_sound);
    smlua_bind_function(L, "mario_set_bubbled", smlua_func_mario_set_bubbled);
    smlua_bind_function(L, "mario_set_forward_vel", smlua_func_mario_set_forward_vel);
    smlua_bind_function(L, "mario_get_floor_class", smlua_func_mario_get_floor_class);
    smlua_bind_function(L, "mario_get_terrain_sound_addend", smlua_func_mario_get_terrain_sound_addend);
    //smlua_bind_function(L, "resolve_and_return_wall_collisions", smlua_func_resolve_and_return_wall_collisions); <--- UNIMPLEMENTED
    //smlua_bind_function(L, "vec3f_find_ceil", smlua_func_vec3f_find_ceil); <--- UNIMPLEMENTED
    smlua_bind_function(L, "mario_facing_downhill", smlua_func_mario_facing_downhill);
    smlua_bind_function(L, "mario_floor_is_slippery", smlua_func_mario_floor_is_slippery);
    smlua_bind_function(L, "mario_floor_is_slope", smlua_func_mario_floor_is_slope);
    smlua_bind_function(L, "mario_floor_is_steep", smlua_func_mario_floor_is_steep);
    smlua_bind_function(L, "find_floor_height_relative_polar", smlua_func_find_floor_height_relative_polar);
    smlua_bind_function(L, "find_floor_slope", smlua_func_find_floor_slope);
    smlua_bind_function(L, "update_mario_sound_and_camera", smlua_func_update_mario_sound_and_camera);
    smlua_bind_function(L, "set_steep_jump_action", smlua_func_set_steep_jump_action);
    smlua_bind_function(L, "set_mario_action", smlua_func_set_mario_action);
    smlua_bind_function(L, "set_jump_from_landing", smlua_func_set_jump_from_landing);
    smlua_bind_function(L, "set_jumping_action", smlua_func_set_jumping_action);
    smlua_bind_function(L, "drop_and_set_mario_action", smlua_func_drop_and_set_mario_action);
    smlua_bind_function(L, "hurt_and_set_mario_action", smlua_func_hurt_and_set_mario_action);
    smlua_bind_function(L, "check_common_action_exits", smlua_func_check_common_action_exits);
    smlua_bind_function(L, "check_common_hold_action_exits", smlua_func_check_common_hold_action_exits);
    smlua_bind_function(L, "transition_submerged_to_walking", smlua_func_transition_submerged_to_walking);
    smlua_bind_function(L, "set_water_plunge_action", smlua_func_set_water_plunge_action);
    //smlua_bind_function(L, "execute_mario_action", smlua_func_execute_mario_action); <--- UNIMPLEMENTED
    smlua_bind_function(L, "force_idle_state", smlua_func_force_idle_state);
    smlua_bind_function(L, "init_mario", smlua_func_init_mario);
    smlua_bind_function(L, "init_mario_from_save_file", smlua_func_init_mario_from_save_file);

      ////////////////////////////
     // mario_actions_moving.c //
    ////////////////////////////

    smlua_bind_function(L, "tilt_body_running", smlua_func_tilt_body_running);
    smlua_bind_function(L, "play_step_sound", smlua_func_play_step_sound);
    smlua_bind_function(L, "align_with_floor", smlua_func_align_with_floor);
    smlua_bind_function(L, "begin_walking_action", smlua_func_begin_walking_action);
    smlua_bind_function(L, "check_ledge_climb_down", smlua_func_check_ledge_climb_down);
    smlua_bind_function(L, "slide_bonk", smlua_func_slide_bonk);
    smlua_bind_function(L, "set_triple_jump_action", smlua_func_set_triple_jump_action);
    smlua_bind_function(L, "update_sliding_angle", smlua_func_update_sliding_angle);
    smlua_bind_function(L, "update_sliding", smlua_func_update_sliding);
    smlua_bind_function(L, "apply_slope_accel", smlua_func_apply_slope_accel);
    smlua_bind_function(L, "apply_landing_accel", smlua_func_apply_landing_accel);
    smlua_bind_function(L, "update_shell_speed", smlua_func_update_shell_speed);
    smlua_bind_function(L, "apply_slope_decel", smlua_func_apply_slope_decel);
    smlua_bind_function(L, "update_decelerating_speed", smlua_func_update_decelerating_speed);
    smlua_bind_function(L, "update_walking_speed", smlua_func_update_walking_speed);
    smlua_bind_function(L, "should_begin_sliding", smlua_func_should_begin_sliding);
    smlua_bind_function(L, "analog_stick_held_back", smlua_func_analog_stick_held_back);
    smlua_bind_function(L, "check_ground_dive_or_punch", smlua_func_check_ground_dive_or_punch);
    smlua_bind_function(L, "begin_braking_action", smlua_func_begin_braking_action);
    smlua_bind_function(L, "anim_and_audio_for_walk", smlua_func_anim_and_audio_for_walk);
    smlua_bind_function(L, "anim_and_audio_for_hold_walk", smlua_func_anim_and_audio_for_hold_walk);
    smlua_bind_function(L, "anim_and_audio_for_heavy_walk", smlua_func_anim_and_audio_for_heavy_walk);
    smlua_bind_function(L, "push_or_sidle_wall", smlua_func_push_or_sidle_wall);
    smlua_bind_function(L, "tilt_body_walking", smlua_func_tilt_body_walking);
    smlua_bind_function(L, "tilt_body_ground_shell", smlua_func_tilt_body_ground_shell);
    smlua_bind_function(L, "tilt_body_butt_slide", smlua_func_tilt_body_butt_slide);
    smlua_bind_function(L, "common_slide_action", smlua_func_common_slide_action);
    smlua_bind_function(L, "stomach_slide_action", smlua_func_stomach_slide_action);
    smlua_bind_function(L, "common_ground_knockback_action", smlua_func_common_ground_knockback_action);
    smlua_bind_function(L, "common_landing_action", smlua_func_common_landing_action);
    smlua_bind_function(L, "check_common_moving_cancels", smlua_func_check_common_moving_cancels);
    smlua_bind_function(L, "mario_execute_moving_action", smlua_func_mario_execute_moving_action);

      //////////////////
     // mario_step.h //
    //////////////////

    smlua_bind_function(L, "mario_bonk_reflection", smlua_func_mario_bonk_reflection);
    //smlua_bind_function(L, "transfer_bully_speed", smlua_func_transfer_bully_speed); <--- UNIMPLEMENTED
    //smlua_bind_function(L, "init_bully_collision_data", smlua_func_init_bully_collision_data); <--- UNIMPLEMENTED
    smlua_bind_function(L, "mario_update_quicksand", smlua_func_mario_update_quicksand);
    smlua_bind_function(L, "mario_push_off_steep_floor", smlua_func_mario_push_off_steep_floor);
    smlua_bind_function(L, "mario_update_moving_sand", smlua_func_mario_update_moving_sand);
    smlua_bind_function(L, "mario_update_windy_ground", smlua_func_mario_update_windy_ground);
    smlua_bind_function(L, "stop_and_set_height_to_floor", smlua_func_stop_and_set_height_to_floor);
    smlua_bind_function(L, "stationary_ground_step", smlua_func_stationary_ground_step);
    smlua_bind_function(L, "perform_ground_step", smlua_func_perform_ground_step);
    smlua_bind_function(L, "perform_air_step", smlua_func_perform_air_step);
    smlua_bind_function(L, "set_vel_from_pitch_and_yaw", smlua_func_set_vel_from_pitch_and_yaw);

      //////////////////////////////
     // mario_actions_airborne.c //
    //////////////////////////////

    smlua_bind_function(L, "play_flip_sounds", smlua_func_play_flip_sounds);
    smlua_bind_function(L, "play_far_fall_sound", smlua_func_play_far_fall_sound);
    smlua_bind_function(L, "play_knockback_sound", smlua_func_play_knockback_sound);
    smlua_bind_function(L, "lava_boost_on_wall", smlua_func_lava_boost_on_wall);
    smlua_bind_function(L, "check_fall_damage", smlua_func_check_fall_damage);
    smlua_bind_function(L, "check_kick_or_dive_in_air", smlua_func_check_kick_or_dive_in_air);
    smlua_bind_function(L, "should_get_stuck_in_ground", smlua_func_should_get_stuck_in_ground);
    smlua_bind_function(L, "check_fall_damage_or_get_stuck", smlua_func_check_fall_damage_or_get_stuck);
    smlua_bind_function(L, "check_horizontal_wind", smlua_func_check_horizontal_wind);
    smlua_bind_function(L, "update_air_with_turn", smlua_func_update_air_with_turn);
    smlua_bind_function(L, "update_air_without_turn", smlua_func_update_air_without_turn);
    smlua_bind_function(L, "update_lava_boost_or_twirling", smlua_func_update_lava_boost_or_twirling);
    smlua_bind_function(L, "update_flying_yaw", smlua_func_update_flying_yaw);
    smlua_bind_function(L, "update_flying_pitch", smlua_func_update_flying_pitch);
    smlua_bind_function(L, "update_flying", smlua_func_update_flying);
    smlua_bind_function(L, "common_air_action_step", smlua_func_common_air_action_step);
    smlua_bind_function(L, "act_jump", smlua_func_act_jump);
    smlua_bind_function(L, "act_double_jump", smlua_func_act_double_jump);
    smlua_bind_function(L, "act_triple_jump", smlua_func_act_triple_jump);
    smlua_bind_function(L, "act_backflip", smlua_func_act_backflip);
    smlua_bind_function(L, "act_freefall", smlua_func_act_freefall);
    smlua_bind_function(L, "act_hold_jump", smlua_func_act_hold_jump);
    smlua_bind_function(L, "act_hold_freefall", smlua_func_act_hold_freefall);
    smlua_bind_function(L, "act_side_flip", smlua_func_act_side_flip);
    smlua_bind_function(L, "act_wall_kick_air", smlua_func_act_wall_kick_air);
    smlua_bind_function(L, "act_long_jump", smlua_func_act_long_jump);
    smlua_bind_function(L, "act_riding_shell_air", smlua_func_act_riding_shell_air);
    smlua_bind_function(L, "act_twirling", smlua_func_act_twirling);
    smlua_bind_function(L, "act_dive", smlua_func_act_dive);
    smlua_bind_function(L, "act_air_throw", smlua_func_act_air_throw);
    smlua_bind_function(L, "act_water_jump", smlua_func_act_water_jump);
    smlua_bind_function(L, "act_hold_water_jump", smlua_func_act_hold_water_jump);
    smlua_bind_function(L, "act_steep_jump", smlua_func_act_steep_jump);
    smlua_bind_function(L, "act_ground_pound", smlua_func_act_ground_pound);
    smlua_bind_function(L, "act_burning_jump", smlua_func_act_burning_jump);
    smlua_bind_function(L, "act_burning_fall", smlua_func_act_burning_fall);
    smlua_bind_function(L, "act_crazy_box_bounce", smlua_func_act_crazy_box_bounce);
    smlua_bind_function(L, "check_wall_kick", smlua_func_check_wall_kick);
    smlua_bind_function(L, "act_backward_air_kb", smlua_func_act_backward_air_kb);
    smlua_bind_function(L, "act_forward_air_kb", smlua_func_act_forward_air_kb);
    smlua_bind_function(L, "act_hard_backward_air_kb", smlua_func_act_hard_backward_air_kb);
    smlua_bind_function(L, "act_hard_forward_air_kb", smlua_func_act_hard_forward_air_kb);
    smlua_bind_function(L, "act_thrown_backward", smlua_func_act_thrown_backward);
    smlua_bind_function(L, "act_thrown_forward", smlua_func_act_thrown_forward);
    smlua_bind_function(L, "act_soft_bonk", smlua_func_act_soft_bonk);
    smlua_bind_function(L, "act_getting_blown", smlua_func_act_getting_blown);
    smlua_bind_function(L, "act_air_hit_wall", smlua_func_act_air_hit_wall);
    smlua_bind_function(L, "act_forward_rollout", smlua_func_act_forward_rollout);
    smlua_bind_function(L, "act_backward_rollout", smlua_func_act_backward_rollout);
    smlua_bind_function(L, "act_butt_slide_air", smlua_func_act_butt_slide_air);
    smlua_bind_function(L, "act_hold_butt_slide_air", smlua_func_act_hold_butt_slide_air);
    smlua_bind_function(L, "act_lava_boost", smlua_func_act_lava_boost);
    smlua_bind_function(L, "act_slide_kick", smlua_func_act_slide_kick);
    smlua_bind_function(L, "act_jump_kick", smlua_func_act_jump_kick);
    smlua_bind_function(L, "act_shot_from_cannon", smlua_func_act_shot_from_cannon);
    smlua_bind_function(L, "act_flying", smlua_func_act_flying);
    smlua_bind_function(L, "act_riding_hoot", smlua_func_act_riding_hoot);
    smlua_bind_function(L, "act_flying_triple_jump", smlua_func_act_flying_triple_jump);
    smlua_bind_function(L, "act_top_of_pole_jump", smlua_func_act_top_of_pole_jump);
    smlua_bind_function(L, "act_vertical_wind", smlua_func_act_vertical_wind);
    smlua_bind_function(L, "act_special_triple_jump", smlua_func_act_special_triple_jump);
    smlua_bind_function(L, "check_common_airborne_cancels", smlua_func_check_common_airborne_cancels);
    smlua_bind_function(L, "mario_execute_airborne_action", smlua_func_mario_execute_airborne_action);

      //////////////
     // camera.h //
    //////////////

    smlua_bind_function(L, "set_camera_shake_from_hit", smlua_func_set_camera_shake_from_hit);
    smlua_bind_function(L, "set_environmental_camera_shake", smlua_func_set_environmental_camera_shake);
    smlua_bind_function(L, "set_camera_shake_from_point", smlua_func_set_camera_shake_from_point);

      ////////////////////////////////
     // mario_actions_stationary.h //
    ////////////////////////////////

    smlua_bind_function(L, "check_common_idle_cancels", smlua_func_check_common_idle_cancels);
    smlua_bind_function(L, "check_common_hold_idle_cancels", smlua_func_check_common_hold_idle_cancels);
    smlua_bind_function(L, "act_idle", smlua_func_act_idle);
    smlua_bind_function(L, "play_anim_sound", smlua_func_play_anim_sound);
    smlua_bind_function(L, "act_start_sleeping", smlua_func_act_start_sleeping);
    smlua_bind_function(L, "act_sleeping", smlua_func_act_sleeping);
    smlua_bind_function(L, "act_waking_up", smlua_func_act_waking_up);
    smlua_bind_function(L, "act_shivering", smlua_func_act_shivering);
    smlua_bind_function(L, "act_coughing", smlua_func_act_coughing);
    smlua_bind_function(L, "act_standing_against_wall", smlua_func_act_standing_against_wall);
    smlua_bind_function(L, "act_in_quicksand", smlua_func_act_in_quicksand);
    smlua_bind_function(L, "act_crouching", smlua_func_act_crouching);
    smlua_bind_function(L, "act_panting", smlua_func_act_panting);
    smlua_bind_function(L, "stopping_step", smlua_func_stopping_step);
    smlua_bind_function(L, "act_braking_stop", smlua_func_act_braking_stop);
    smlua_bind_function(L, "act_butt_slide_stop", smlua_func_act_butt_slide_stop);
    smlua_bind_function(L, "act_hold_butt_slide_stop", smlua_func_act_hold_butt_slide_stop);
    smlua_bind_function(L, "act_slide_kick_slide_stop", smlua_func_act_slide_kick_slide_stop);
    smlua_bind_function(L, "act_start_crouching", smlua_func_act_start_crouching);
    smlua_bind_function(L, "act_stop_crouching", smlua_func_act_stop_crouching);
    smlua_bind_function(L, "act_start_crawling", smlua_func_act_start_crawling);
    smlua_bind_function(L, "act_stop_crawling", smlua_func_act_stop_crawling);
    smlua_bind_function(L, "act_shockwave_bounce", smlua_func_act_shockwave_bounce);
    smlua_bind_function(L, "landing_step", smlua_func_landing_step);
    smlua_bind_function(L, "check_common_landing_cancels", smlua_func_check_common_landing_cancels);
    smlua_bind_function(L, "act_jump_land_stop", smlua_func_act_jump_land_stop);
    smlua_bind_function(L, "act_double_jump_land_stop", smlua_func_act_double_jump_land_stop);
    smlua_bind_function(L, "act_side_flip_land_stop", smlua_func_act_side_flip_land_stop);
    smlua_bind_function(L, "act_freefall_land_stop", smlua_func_act_freefall_land_stop);
    smlua_bind_function(L, "act_triple_jump_land_stop", smlua_func_act_triple_jump_land_stop);
    smlua_bind_function(L, "act_backflip_land_stop", smlua_func_act_backflip_land_stop);
    smlua_bind_function(L, "act_lava_boost_land", smlua_func_act_lava_boost_land);
    smlua_bind_function(L, "act_long_jump_land_stop", smlua_func_act_long_jump_land_stop);
    smlua_bind_function(L, "act_hold_jump_land_stop", smlua_func_act_hold_jump_land_stop);
    smlua_bind_function(L, "act_hold_freefall_land_stop", smlua_func_act_hold_freefall_land_stop);
    smlua_bind_function(L, "act_air_throw_land", smlua_func_act_air_throw_land);
    smlua_bind_function(L, "act_twirl_land", smlua_func_act_twirl_land);
    smlua_bind_function(L, "act_ground_pound_land", smlua_func_act_ground_pound_land);
    smlua_bind_function(L, "act_first_person", smlua_func_act_first_person);
    smlua_bind_function(L, "check_common_stationary_cancels", smlua_func_check_common_stationary_cancels);
    smlua_bind_function(L, "mario_execute_stationary_action", smlua_func_mario_execute_stationary_action);

      //////////
     // misc //
    //////////

    smlua_bind_function(L, "get_camera_position", smlua_get_camera_position);
    smlua_bind_function(L, "check_fall_damage_or_get_stuck", smlua_check_fall_damage_or_get_stuck);
    smlua_bind_function(L, "play_sound", smlua_play_sound);
    smlua_bind_function(L, "atan2s", smlua_func_atan2s);
}