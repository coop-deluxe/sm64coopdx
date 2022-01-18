#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "audio/external.h"
#include "object_fields.h"

int smlua_set_mario_action(lua_State* L) {
    int index = lua_tointeger(L, -3);
    u32 action = lua_tointeger(L, -2);
    u32 actionArg = lua_tointeger(L, -1);
    lua_pushinteger(L, set_mario_action(&gMarioStates[index], action, actionArg));
    return 1;
}

int smlua_set_jumping_action(lua_State* L) {
    int index = lua_tointeger(L, -3);
    u32 action = lua_tointeger(L, -2);
    u32 actionArg = lua_tointeger(L, -1);
    lua_pushinteger(L, set_jumping_action(&gMarioStates[index], action, actionArg));
    return 1;
}

int smlua_play_mario_sound(lua_State* L) {
    int index = lua_tointeger(L, -3);
    s32 actionSound = lua_tointeger(L, -2);
    s32 marioSound = lua_tointeger(L, -1);
    play_mario_sound(&gMarioStates[index], actionSound, marioSound);
    return 1;
}

int smlua_mario_set_forward_vel(lua_State* L) {
    int index = lua_tointeger(L, -2);
    f32 forwardVel = lua_tonumber(L, -1);
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
    int index = lua_tointeger(L, -2);
    s32 targetAnimID = lua_tointeger(L, -1);
    lua_pushinteger(L, set_mario_animation(&gMarioStates[index], targetAnimID));
    return 1;
}

int smlua_update_sliding(lua_State* L) {
    int index = lua_tointeger(L, -2);
    f32 stopSpeed = lua_tonumber(L, -1);
    extern s32 update_sliding(struct MarioState* m, f32 stopSpeed);
    lua_pushinteger(L, update_sliding(&gMarioStates[index], stopSpeed));
    return 1;
}

int smlua_common_slide_action(lua_State* L) {
    int index = lua_tointeger(L, -4);
    u32 endAction = lua_tointeger(L, -3);
    u32 airAction = lua_tointeger(L, -2);
    u32 animation = lua_tointeger(L, -1);
    extern void common_slide_action(struct MarioState* m, u32 endAction, u32 airAction, s32 animation);
    common_slide_action(&gMarioStates[index], endAction, airAction, animation);
    return 1;
}

int smlua_set_anim_to_frame(lua_State* L) {
    int index = lua_tointeger(L, -2);
    s16 animFrame = lua_tonumber(L, -1);
    set_anim_to_frame(&gMarioStates[index], animFrame);
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

}