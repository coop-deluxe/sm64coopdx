#include "sm64.h"
#include "types.h"

#include "data/dynos.c.h"
#include "game/bettercamera.h"
#include "game/camera.h"
#include "game/hardcoded.h"
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
#include "include/course_table.h"

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

bool hud_is_hidden(void) {
    return gOverrideHideHud;
}

extern u8 gLastCollectedStarOrKey;
s32 get_last_star_or_key(void) {
    return gLastCollectedStarOrKey;
}

void set_last_star_or_key(u8 value) {
    gLastCollectedStarOrKey = value;
}

extern s8 gDialogBoxState;
s8 get_dialog_box_state() {
    return gDialogBoxState;
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

bool camera_is_frozen(void) {
    return gOverrideFreezeCamera;
}

bool camera_config_is_free_cam_enabled(void) {
#ifdef BETTERCAMERA
    return configEnableCamera;
#else
    return false;
#endif
}

bool camera_config_is_analog_cam_enabled(void) {
#ifdef BETTERCAMERA
    return configCameraAnalog;
#else
    return false;
#endif
}

bool camera_config_is_mouse_look_enabled(void) {
#ifdef BETTERCAMERA
    return configCameraMouse;
#else
    return false;
#endif
}

bool camera_config_is_x_inverted(void) {
#ifdef BETTERCAMERA
    return configCameraInvertX;
#else
    return false;
#endif
}

bool camera_config_is_y_inverted(void) {
#ifdef BETTERCAMERA
    return configCameraInvertY;
#else
    return false;
#endif
}

u32 camera_config_get_x_sensitivity(void) {
#ifdef BETTERCAMERA
    return configCameraXSens;
#else
    return 0;
#endif
}

u32 camera_config_get_y_sensitivity(void) {
#ifdef BETTERCAMERA
    return configCameraYSens;
#else
    return 0;
#endif
}

u32 camera_config_get_aggression(void) {
#ifdef BETTERCAMERA
    return configCameraAggr;
#else
    return 0;
#endif
}

u32 camera_config_get_pan_level(void) {
#ifdef BETTERCAMERA
    return configCameraPan;
#else
    return 0;
#endif
}

u32 camera_config_get_deceleration(void) {
#ifdef BETTERCAMERA
    return configCameraDegrade;
#else
    return 0;
#endif
}

void camera_config_enable_free_cam(bool enable) {
#ifdef BETTERCAMERA
    configEnableCamera = enable;
    newcam_init_settings();
#endif
}

void camera_config_enable_analog_cam(bool enable) {
#ifdef BETTERCAMERA
    configCameraAnalog = enable;
    newcam_init_settings();
#endif
}

void camera_config_enable_mouse_look(bool enable) {
#ifdef BETTERCAMERA
    configCameraMouse = enable;
    newcam_init_settings();
#endif
}

void camera_config_invert_x(bool invert) {
#ifdef BETTERCAMERA
    configCameraInvertX = invert;
    newcam_init_settings();
#endif
}

void camera_config_invert_y(bool invert) {
#ifdef BETTERCAMERA
    configCameraInvertY = invert;
    newcam_init_settings();
#endif
}

void camera_config_set_x_sensitivity(u32 value) {
#ifdef BETTERCAMERA
    configCameraXSens = MIN(MAX(value, 1), 100);
    newcam_init_settings();
#endif
}

void camera_config_set_y_sensitivity(u32 value) {
#ifdef BETTERCAMERA
    configCameraYSens = MIN(MAX(value, 1), 100);
    newcam_init_settings();
#endif
}

void camera_config_set_aggression(u32 value) {
#ifdef BETTERCAMERA
    configCameraAggr = MIN(MAX(value, 0), 100);
    newcam_init_settings();
#endif
}

void camera_config_set_pan_level(u32 value) {
#ifdef BETTERCAMERA
    configCameraPan = MIN(MAX(value, 0), 100);
    newcam_init_settings();
#endif
}

void camera_config_set_deceleration(u32 value) {
#ifdef BETTERCAMERA
    configCameraDegrade = MIN(MAX(value, 0), 100);
    newcam_init_settings();
#endif
}

///

extern s16 gMenuMode;
bool is_game_paused(void) {
    return gMenuMode != -1;
}

///

bool is_transition_playing(void) {
    return sTransitionUpdate != NULL || gWarpTransition.isActive;
}

///

u32 allocate_mario_action(u32 actFlags) {
    actFlags = actFlags & (~((u32)0x3F));
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

///

f32 get_environment_region(u8 index) {
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0]) {
        return gEnvironmentRegions[6 * (int)index];
    }
    return gLevelValues.floorLowerLimit;
}

void set_environment_region(u8 index, s32 value) {
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0]) {
        gEnvironmentRegions[6 * (int)index] = value;
    }
}

///

void set_override_fov(f32 fov) {
    gOverrideFOV = fov;
}

///

void set_override_near(f32 near) {
    gOverrideNear = near;
}

///

void set_override_far(f32 far) {
    gOverrideFar = far;
}

///

void add_scroll_target(u32 index, const char* name, u32 offset, u32 size) {
    dynos_add_scroll_target(index, name, offset, size);
}

///

bool course_is_main_course(u16 levelNum) {
    return COURSE_IS_MAIN_COURSE(levelNum);
}

///

s16 get_ttc_speed_setting() {
    return gTTCSpeedSetting;
}

void set_ttc_speed_setting(s16 speed) {
    gTTCSpeedSetting = speed;
}

///

u32 get_time(void) {
    return time(NULL);
}
