#include "sm64.h"
#include "types.h"

#include "data/dynos.c.h"
#include "game/hud.h"
#include "pc/lua/smlua.h"
#include "smlua_misc_utils.h"
#include "pc/debuglog.h"
#include "game/object_list_processor.h"

u32 get_network_area_timer(void) {
    return gNetworkAreaTimer;
}

///

s32* get_temp_s32_pointer(s32 initialValue) {
    static s32 value = 0;
    value = initialValue;
    return &value;
}

s32 deref_s32_pointer(s32* pointer) {
    if (pointer == NULL) {
        LOG_LUA("Tried to dereference null pointer!");
        return 0;
    }
    return *pointer;
}

///

void hud_hide(void) {
    gOverrideHideHud = 1;
}

void hud_show(void) {
    gOverrideHideHud = 0;
}

///

bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct) {
    return dynos_warp_to_level(aLevel, aArea, aAct);
}

bool warp_restart_level(void) {
    return dynos_warp_restart_level();
}

bool warp_exit_level(s32 aDelay) {
    return dynos_warp_exit_level(aDelay);
}

bool warp_to_castle(s32 aLevel) {
    return dynos_warp_to_castle(aLevel);
}

///

u32 allocate_mario_action(u32 actFlags) {
    actFlags = actFlags & (~((u32)0xFF));
    return actFlags | ACT_FLAG_CUSTOM_ACTION | gLuaMarioActionIndex++;
}

///

f32 get_hand_foot_pos_x(struct MarioState* m, u8 index) {
    if (index >= 4) { index = 0; }
    return m->marioBodyState->handFootPos[index][0];
}

f32 get_hand_foot_pos_y(struct MarioState* m, u8 index) {
    if (index >= 4) { index = 0; }
    return m->marioBodyState->handFootPos[index][1];
}

f32 get_hand_foot_pos_z(struct MarioState* m, u8 index) {
    if (index >= 4) { index = 0; }
    return m->marioBodyState->handFootPos[index][2];
}

///

s16 get_current_save_file_num(void) {
    extern s16 gCurrSaveFileNum;
    return gCurrSaveFileNum;
}

///

void movtexqc_register(const char* name, s16 level, s16 area, s16 type) {
    dynos_movtexqc_register(name, level, area, type);
}

f32 get_environment_region(u8 index) {
    if (gEnvironmentRegions != NULL && index <= gEnvironmentRegions[0]) {
        return gEnvironmentRegions[6 * (int)index];
    }
    return -11000;
}

void set_environment_region(u8 index, s32 value) {
    if (gEnvironmentRegions != NULL && index <= gEnvironmentRegions[0]) {
        gEnvironmentRegions[6 * (int)index] = value;
    }
}
