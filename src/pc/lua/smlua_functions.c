#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "audio/external.h"
#include "object_fields.h"

int smlua_set_mario_action(lua_State* L) {
    u32 action = lua_tointeger(L, -2);
    u32 actionArg = lua_tointeger(L, -1);

    lua_getfield(L, -3, "playerIndex");
    int index = lua_tointeger(L, -1);

    lua_pushinteger(L, set_mario_action(&gMarioStates[index], action, actionArg));
    return 1;
}

int smlua_set_jumping_action(lua_State* L) {
    u32 action = lua_tointeger(L, -2);
    u32 actionArg = lua_tointeger(L, -1);

    lua_getfield(L, -3, "playerIndex");
    int index = lua_tointeger(L, -1);

    lua_pushinteger(L, set_jumping_action(&gMarioStates[index], action, actionArg));
    return 1;
}

int smlua_play_mario_sound(lua_State* L) {
    s32 actionSound = lua_tointeger(L, -2);
    s32 marioSound = lua_tointeger(L, -1);

    lua_getfield(L, -3, "playerIndex");
    int index = lua_tointeger(L, -1);

    play_mario_sound(&gMarioStates[index], actionSound, marioSound);
    return 1;
}

int smlua_mario_set_forward_vel(lua_State* L) {
    f32 forwardVel = lua_tonumber(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    mario_set_forward_vel(&gMarioStates[index], forwardVel);
    return 1;
}

int smlua_play_sound(lua_State* L) {
    s32 soundsBits = lua_tointeger(L, -4);
    f32 pos[3] = { lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1) };
    extern void play_sound(s32 soundBits, f32 * pos);
    play_sound(soundsBits, pos);
    return 1;
}

int smlua_set_mario_animation(lua_State* L) {
    s32 targetAnimID = lua_tointeger(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    lua_pushinteger(L, set_mario_animation(&gMarioStates[index], targetAnimID));
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

int smlua_set_anim_to_frame(lua_State* L) {
    s16 animFrame = lua_tonumber(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    set_anim_to_frame(&gMarioStates[index], animFrame);
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

int smlua_mario_floor_is_slope(lua_State* L) {
    lua_getfield(L, -1, "playerIndex");
    int index = lua_tointeger(L, -1);

    lua_pushinteger(L, mario_floor_is_slope(&gMarioStates[index]));
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

int smlua_play_sound_and_spawn_particles(lua_State* L) {
    u32 soundBits = lua_tointeger(L, -3);
    u32 waveParticleType = lua_tointeger(L, -2);

    lua_getfield(L, -3, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern void play_sound_and_spawn_particles(struct MarioState* m, u32 soundBits, u32 waveParticleType);
    play_sound_and_spawn_particles(&gMarioStates[index], soundBits, waveParticleType);
    return 1;
}

int smlua_play_mario_landing_sound_once(lua_State* L) {
    u32 soundBits = lua_tointeger(L, -1);

    lua_getfield(L, -2, "playerIndex");
    int index = lua_tointeger(L, -1);

    extern void play_mario_landing_sound_once(struct MarioState* m, u32 soundBits);
    play_mario_landing_sound_once(&gMarioStates[index], soundBits);
    return 1;
}

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

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    lua_pushcfunction(L, smlua_set_mario_action);
    lua_setglobal(L, "set_mario_action");

    lua_pushcfunction(L, smlua_set_jumping_action);
    lua_setglobal(L, "set_jumping_action");

    lua_pushcfunction(L, smlua_play_mario_sound);
    lua_setglobal(L, "play_mario_sound");

    lua_pushcfunction(L, smlua_mario_set_forward_vel);
    lua_setglobal(L, "mario_set_forward_vel");

    lua_pushcfunction(L, smlua_play_sound);
    lua_setglobal(L, "play_sound");

    lua_pushcfunction(L, smlua_set_mario_animation);
    lua_setglobal(L, "set_mario_animation");

    lua_pushcfunction(L, smlua_update_sliding);
    lua_setglobal(L, "update_sliding");

    lua_pushcfunction(L, smlua_common_slide_action);
    lua_setglobal(L, "common_slide_action");

    lua_pushcfunction(L, smlua_set_anim_to_frame);
    lua_setglobal(L, "set_anim_to_frame");

    lua_pushcfunction(L, smlua_update_sliding_angle);
    lua_setglobal(L, "update_sliding_angle");

    lua_pushcfunction(L, smlua_mario_floor_is_slope);
    lua_setglobal(L, "mario_floor_is_slope");

    lua_pushcfunction(L, smlua_perform_air_step);
    lua_setglobal(L, "perform_air_step");

    lua_pushcfunction(L, smlua_check_fall_damage_or_get_stuck);
    lua_setglobal(L, "check_fall_damage_or_get_stuck");

    lua_pushcfunction(L, smlua_mario_bonk_reflection);
    lua_setglobal(L, "mario_bonk_reflection");

    lua_pushcfunction(L, smlua_play_sound_and_spawn_particles);
    lua_setglobal(L, "play_sound_and_spawn_particles");

    lua_pushcfunction(L, smlua_play_mario_landing_sound_once);
    lua_setglobal(L, "play_mario_landing_sound_once");

    lua_pushcfunction(L, smlua_get_camera_position);
    lua_setglobal(L, "get_camera_position");

}