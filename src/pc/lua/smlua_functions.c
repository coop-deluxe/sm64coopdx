#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "audio/external.h"
#include "object_fields.h"

///////////////////////////////////////



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


///////////////////////////////////////

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

int smlua_update_sliding(lua_State* L) {
    f32 stopSpeed = lua_tonumber(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern s32 update_sliding(struct MarioState* m, f32 stopSpeed);
    lua_pushinteger(L, update_sliding(&gMarioStates[index], stopSpeed));
    return 1;
}

int smlua_common_slide_action(lua_State* L) {
    u32 endAction = lua_tointeger(L, -3);
    u32 airAction = lua_tointeger(L, -2);
    u32 animation = lua_tointeger(L, -1);

    lua_getfield(L, -4, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern void common_slide_action(struct MarioState* m, u32 endAction, u32 airAction, s32 animation);
    common_slide_action(&gMarioStates[index], endAction, airAction, animation);
    return 1;
}

int smlua_update_sliding_angle(lua_State* L) {
    f32 accel = lua_tonumber(L, -2);
    f32 lossFactor = lua_tonumber(L, -1);

    lua_getfield(L, -3, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern void update_sliding_angle(struct MarioState* m, f32 accel, f32 lossFactor);
    update_sliding_angle(&gMarioStates[index], accel, lossFactor);
    return 1;
}

int smlua_perform_air_step(lua_State* L) {
    u32 stepArg = lua_tointeger(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern s32 perform_air_step(struct MarioState* m, u32 stepArg);
    lua_pushinteger(L, perform_air_step(&gMarioStates[index], stepArg));
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

int smlua_mario_bonk_reflection(lua_State* L) {
    u32 negateSpeed = lua_tointeger(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern void mario_bonk_reflection(struct MarioState* m, u32 negateSpeed);
    mario_bonk_reflection(&gMarioStates[index], negateSpeed);
    return 1;
}

int smlua_play_sound(lua_State* L) {
    s32 soundsBits = lua_tointeger(L, -4);
    f32 pos[3] = { lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1) };
    extern void play_sound(s32 soundBits, f32 * pos);
    play_sound(soundsBits, pos);
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

      //////////
     // misc //
    //////////

    smlua_bind_function(L, "get_camera_position", smlua_get_camera_position);
    smlua_bind_function(L, "update_sliding", smlua_update_sliding);
    smlua_bind_function(L, "common_slide_action", smlua_common_slide_action);
    smlua_bind_function(L, "update_sliding_angle", smlua_update_sliding_angle);
    smlua_bind_function(L, "perform_air_step", smlua_perform_air_step);
    smlua_bind_function(L, "check_fall_damage_or_get_stuck", smlua_check_fall_damage_or_get_stuck);
    smlua_bind_function(L, "mario_bonk_reflection", smlua_mario_bonk_reflection);
    smlua_bind_function(L, "play_sound", smlua_play_sound);
}