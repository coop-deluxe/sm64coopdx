#include "sm64.h"
#include "types.h"

#include "data/dynos.c.h"
#include "game/camera.h"
#include "game/hud.h"
#include "pc/lua/smlua.h"
#include "smlua_misc_utils.h"
#include "pc/debuglog.h"
#include "pc/mods/mod.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"

#include "game/object_list_processor.h"
#include "game/rendering_graph_node.h"
#include "game/level_update.h"
#include "pc/djui/djui_hud_utils.h"

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
        LOG_LUA_LINE("Tried to dereference null pointer!");
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

s32 hud_get_value(enum HudDisplayValue type) {
    switch (type) {
        case HUD_DISPLAY_LIVES:  return gHudDisplay.lives;
        case HUD_DISPLAY_COINS:  return gHudDisplay.coins;
        case HUD_DISPLAY_STARS:  return gHudDisplay.stars;
        case HUD_DISPLAY_WEDGES: return gHudDisplay.wedges;
        case HUD_DISPLAY_KEYS:   return gHudDisplay.keys;
        case HUD_DISPLAY_FLAGS:  return gHudDisplay.flags;
        case HUD_DISPLAY_TIMER:  return gHudDisplay.timer;
    }
    return 0;
}

void hud_set_value(enum HudDisplayValue type, s32 value) {
    switch (type) {
        case HUD_DISPLAY_LIVES:  gHudDisplay.lives  = value; break;
        case HUD_DISPLAY_COINS:  gHudDisplay.coins  = value; break;
        case HUD_DISPLAY_STARS:  gHudDisplay.stars  = value; break;
        case HUD_DISPLAY_WEDGES: gHudDisplay.wedges = value; break;
        case HUD_DISPLAY_KEYS:   gHudDisplay.keys   = value; break;
        case HUD_DISPLAY_FLAGS:  gHudDisplay.flags  = value; break;
        case HUD_DISPLAY_TIMER:  gHudDisplay.timer  = value; break;
    }
}

void hud_render_power_meter(s32 health, f32 x, f32 y, f32 width, f32 height) {
    extern const u8 texture_power_meter_left_side[];
    extern const u8 texture_power_meter_right_side[];
    extern const u8 texture_power_meter_full[];
    extern const u8 texture_power_meter_seven_segments[];
    extern const u8 texture_power_meter_six_segments[];
    extern const u8 texture_power_meter_five_segments[];
    extern const u8 texture_power_meter_four_segments[];
    extern const u8 texture_power_meter_three_segments[];
    extern const u8 texture_power_meter_two_segments[];
    extern const u8 texture_power_meter_one_segments[];
    static struct TextureInfo sPowerMeterTexturesInfo[] = {
        { (u8*)texture_power_meter_left_side,      8, 32, 64 },
        { (u8*)texture_power_meter_right_side,     8, 32, 64 },
        { (u8*)texture_power_meter_one_segments,   8, 32, 32 },
        { (u8*)texture_power_meter_two_segments,   8, 32, 32 },
        { (u8*)texture_power_meter_three_segments, 8, 32, 32 },
        { (u8*)texture_power_meter_four_segments,  8, 32, 32 },
        { (u8*)texture_power_meter_five_segments,  8, 32, 32 },
        { (u8*)texture_power_meter_six_segments,   8, 32, 32 },
        { (u8*)texture_power_meter_seven_segments, 8, 32, 32 },
        { (u8*)texture_power_meter_full,           8, 32, 32 },
    };
    djui_hud_render_texture(&sPowerMeterTexturesInfo[0], x, y, width / 64, height / 64);
    djui_hud_render_texture(&sPowerMeterTexturesInfo[1], x + width / 2, y, width / 64, height / 64);
    s32 numWedges = MIN(MAX(health >> 8, 0), 8);
    if (numWedges != 0) {
        djui_hud_render_texture(&sPowerMeterTexturesInfo[numWedges + 1], x + width / 4, y + height / 4, width / 64,  height / 64);
    }
}

///

void camera_freeze(void) {
    gOverrideFreezeCamera = TRUE;
}

void camera_unfreeze(void) {
    gOverrideFreezeCamera = FALSE;
}

///

extern s16 gMenuMode;
bool is_game_paused(void) {
    return gMenuMode != -1;
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

void save_file_set_using_backup_slot(bool usingBackupSlot) {
    extern u8 gSaveFileUsingBackupSlot;
    gSaveFileUsingBackupSlot = usingBackupSlot ? 1 : 0;
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

void set_override_fov(f32 fov) {
    gOverrideFOV = fov;
}

void set_override_near(f32 near) {
    gOverrideNear = near;
}

void set_override_far(f32 far) {
    gOverrideFar = far;
}
