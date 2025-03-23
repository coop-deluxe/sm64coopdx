#include <inttypes.h>
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
#include "pc/pc_main.h"
#include "game/object_list_processor.h"
#include "game/rendering_graph_node.h"
#include "game/level_update.h"
#include "pc/djui/djui_console.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/djui/djui_panel_playerlist.h"
#include "pc/djui/djui_theme.h"
#include "game/skybox.h"
#include "pc/gfx/gfx_pc.h"
#include "include/course_table.h"
#include "game/level_geo.h"
#include "game/first_person_cam.h"
#include "pc/lua/utils/smlua_math_utils.h"
#include "pc/lua/utils/smlua_audio_utils.h"

#ifdef DISCORD_SDK
#include "pc/discord/discord.h"
#endif

#ifdef COOPNET
#include "pc/network/coopnet/coopnet.h"
#endif

static struct DateTime sDateTime;

///

u32 get_network_area_timer(void) {
    return gNetworkAreaTimer;
}

u16 get_area_update_counter(void) {
    return gAreaUpdateCounter;
}

///

void djui_popup_create_global(const char* message, int lines) {
    djui_popup_create(message, lines);
    network_send_global_popup(message, lines);
}

struct AllowDjuiPopupOverride {
    bool value;
    bool override;
};

struct AllowDjuiPopupOverride sAllowDjuiPopupOverride;

bool djui_is_popup_disabled(void) {
    // return override if there is one, otherwise return the value in the config.
    return sAllowDjuiPopupOverride.override ? sAllowDjuiPopupOverride.value : configDisablePopups;
}

void djui_set_popup_disabled_override(bool value) {
    // enable override
    sAllowDjuiPopupOverride.override = true;
    // set override to value specified in lua mod
    sAllowDjuiPopupOverride.value = value;
}

void djui_reset_popup_disabled_override(void) {
    // disable override
    sAllowDjuiPopupOverride.override = false;
}

bool djui_is_playerlist_open(void) {
    return gDjuiPlayerList->base.visible;
}

bool djui_attempting_to_open_playerlist(void) {
    return gAttemptingToOpenPlayerlist;
}

enum DjuiFontType djui_menu_get_font(void) {
    return configDjuiThemeFont == 0 ? FONT_NORMAL : FONT_ALIASED;
}

struct DjuiTheme* djui_menu_get_theme(void) {
    return gDjuiThemes[configDjuiTheme];
}

///

extern s8 gDialogBoxState;
s8 get_dialog_box_state(void) {
    return gDialogBoxState;
}

///

extern u8 gLastCollectedStarOrKey;
u8 get_last_star_or_key(void) {
    return gLastCollectedStarOrKey;
}

void set_last_star_or_key(u8 value) {
    gLastCollectedStarOrKey = value;
}

extern u8 gLastCompletedCourseNum;
u8 get_last_completed_course_num(void) {
    return gLastCompletedCourseNum;
}

void set_last_completed_course_num(u8 courseNum) {
    gLastCompletedCourseNum = courseNum;
}

extern u8 gLastCompletedStarNum;
u8 get_last_completed_star_num(void) {
    return gLastCompletedStarNum;
}

void set_last_completed_star_num(u8 starNum) {
    gLastCompletedStarNum = starNum;
}

extern u8 gGotFileCoinHiScore;
bool get_got_file_coin_hi_score(void) {
    return gGotFileCoinHiScore;
}

void set_got_file_coin_hi_score(bool value) {
    gGotFileCoinHiScore = value;
}

extern s8 gSaveFileModified;
bool get_save_file_modified(void) {
    return gSaveFileModified;
}

void set_save_file_modified(bool value) {
    gSaveFileModified = value;
}

///

void hud_hide(void) {
    gOverrideHideHud = TRUE;
}

void hud_show(void) {
    gOverrideHideHud = FALSE;
}

bool hud_is_hidden(void) {
    return gOverrideHideHud;
}

s32 hud_get_value(enum HudDisplayValue type) {
    switch (type) {
        case HUD_DISPLAY_LIVES:         return gHudDisplay.lives;
        case HUD_DISPLAY_COINS:         return gHudDisplay.coins;
        case HUD_DISPLAY_STARS:         return gHudDisplay.stars;
        case HUD_DISPLAY_WEDGES:        return gHudDisplay.wedges;
        case HUD_DISPLAY_KEYS:          return gHudDisplay.keys;
        case HUD_DISPLAY_FLAGS:         return gHudDisplay.flags;
        case HUD_DISPLAY_TIMER:         return gHudDisplay.timer;
        case HUD_DISPLAY_CAMERA_STATUS: return get_hud_camera_status();
    }
    return 0;
}

void hud_set_value(enum HudDisplayValue type, s32 value) {
    switch (type) {
        case HUD_DISPLAY_LIVES:         gHudDisplay.lives  = value;   break;
        case HUD_DISPLAY_COINS:         gHudDisplay.coins  = value;   break;
        case HUD_DISPLAY_STARS:         gHudDisplay.stars  = value;   break;
        case HUD_DISPLAY_WEDGES:        gHudDisplay.wedges = value;   break;
        case HUD_DISPLAY_KEYS:          gHudDisplay.keys   = value;   break;
        case HUD_DISPLAY_FLAGS:         gHudDisplay.flags  = value;   break;
        case HUD_DISPLAY_TIMER:         gHudDisplay.timer  = value;   break;
        case HUD_DISPLAY_CAMERA_STATUS: set_hud_camera_status(value); break;
    }
}

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

void hud_render_power_meter(s32 health, f32 x, f32 y, f32 width, f32 height) {
    static struct TextureInfo sPowerMeterTexturesInfo[] = {
        { (u8*)texture_power_meter_left_side,      8, 32, 64, "texture_power_meter_left_side"      },
        { (u8*)texture_power_meter_right_side,     8, 32, 64, "texture_power_meter_right_side"     },
        { (u8*)texture_power_meter_one_segments,   8, 32, 32, "texture_power_meter_one_segments"   },
        { (u8*)texture_power_meter_two_segments,   8, 32, 32, "texture_power_meter_two_segments"   },
        { (u8*)texture_power_meter_three_segments, 8, 32, 32, "texture_power_meter_three_segments" },
        { (u8*)texture_power_meter_four_segments,  8, 32, 32, "texture_power_meter_four_segments"  },
        { (u8*)texture_power_meter_five_segments,  8, 32, 32, "texture_power_meter_five_segments"  },
        { (u8*)texture_power_meter_six_segments,   8, 32, 32, "texture_power_meter_six_segments"   },
        { (u8*)texture_power_meter_seven_segments, 8, 32, 32, "texture_power_meter_seven_segments" },
        { (u8*)texture_power_meter_full,           8, 32, 32, "texture_power_meter_full"           },
    };
    djui_hud_render_texture(&sPowerMeterTexturesInfo[0], x, y, width / 64, height / 64);
    djui_hud_render_texture(&sPowerMeterTexturesInfo[1], x + (width - 2) / 2, y, width / 64, height / 64);
    s32 numWedges = MIN(MAX(health >> 8, 0), 8);
    if (numWedges != 0) {
        djui_hud_render_texture(&sPowerMeterTexturesInfo[numWedges + 1], x + (width - 4) / 4, y + height / 4, width / 64,  height / 64);
    }
}

void hud_render_power_meter_interpolated(s32 health, f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height) {
    static struct TextureInfo sPowerMeterTexturesInfo[] = {
        { (u8*)texture_power_meter_left_side,      8, 32, 64, "texture_power_meter_left_side"      },
        { (u8*)texture_power_meter_right_side,     8, 32, 64, "texture_power_meter_right_side"     },
        { (u8*)texture_power_meter_one_segments,   8, 32, 32, "texture_power_meter_one_segments"   },
        { (u8*)texture_power_meter_two_segments,   8, 32, 32, "texture_power_meter_two_segments"   },
        { (u8*)texture_power_meter_three_segments, 8, 32, 32, "texture_power_meter_three_segments" },
        { (u8*)texture_power_meter_four_segments,  8, 32, 32, "texture_power_meter_four_segments"  },
        { (u8*)texture_power_meter_five_segments,  8, 32, 32, "texture_power_meter_five_segments"  },
        { (u8*)texture_power_meter_six_segments,   8, 32, 32, "texture_power_meter_six_segments"   },
        { (u8*)texture_power_meter_seven_segments, 8, 32, 32, "texture_power_meter_seven_segments" },
        { (u8*)texture_power_meter_full,           8, 32, 32, "texture_power_meter_full"           },
    };

    djui_hud_render_texture_interpolated(&sPowerMeterTexturesInfo[0],
        prevX, prevY, prevWidth / 64, prevHeight / 64,
        x,     y,     width     / 64, height     / 64);

    djui_hud_render_texture_interpolated(&sPowerMeterTexturesInfo[1],
        prevX + (prevWidth - 2) / 2, prevY, prevWidth / 64, prevHeight / 64,
        x     + (width - 2)     / 2, y,     width     / 64, height     / 64);

    s32 numWedges = MIN(MAX(health >> 8, 0), 8);
    if (numWedges != 0) {
        djui_hud_render_texture_interpolated(&sPowerMeterTexturesInfo[numWedges + 1],
            prevX + (prevWidth - 4) / 4, prevY + prevHeight / 4, prevWidth / 64, prevHeight / 64,
            x     + (width - 4)     / 4, y     + height     / 4, width     / 64, height     / 64);
    }
}

s8 hud_get_flash(void) {
    return gHudFlash;
}

void hud_set_flash(s8 value) {
    gHudFlash = value;
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
    u32 actGroup = ((actFlags & ACT_GROUP_MASK) >> 6);
    u32 actIndex = gLuaMarioActionIndex[actGroup]++;
    if (actIndex >= ACT_NUM_ACTIONS_PER_GROUP) {
        LOG_LUA("Cannot allocate more actions for group %u", actGroup);
        return 0;
    }
    return (actFlags & ~ACT_INDEX_MASK) | ACT_FLAG_CUSTOM_ACTION | actIndex;
}

///

f32 get_hand_foot_pos_x(struct MarioState* m, u8 index) {
    if (!m) { return 0; }
    if (index >= 4) { index = 0; }
    return m->marioBodyState->handFootPos[index][0];
}

f32 get_hand_foot_pos_y(struct MarioState* m, u8 index) {
    if (!m) { return 0; }
    if (index >= 4) { index = 0; }
    return m->marioBodyState->handFootPos[index][1];
}

f32 get_hand_foot_pos_z(struct MarioState* m, u8 index) {
    if (!m) { return 0; }
    if (index >= 4) { index = 0; }
    return m->marioBodyState->handFootPos[index][2];
}

///

s16 get_current_save_file_num(void) {
    extern s16 gCurrSaveFileNum;
    return gCurrSaveFileNum;
}

extern u8 gSaveFileUsingBackupSlot;
bool save_file_get_using_backup_slot(void) {
    return gSaveFileUsingBackupSlot;
}

void save_file_set_using_backup_slot(bool usingBackupSlot) {
    gSaveFileUsingBackupSlot = usingBackupSlot ? TRUE : FALSE;
}

///

void movtexqc_register(const char* name, s16 level, s16 area, s16 type) {
    dynos_movtexqc_register(name, level, area, type);
}

///

s16 get_water_level(u8 index) {
    u8 id = 6 * (index + 1);
    if (gEnvironmentRegions && index < gEnvironmentRegions[0] && gEnvironmentRegionsLength > id) {
        return gEnvironmentRegions[id];
    }
    return gLevelValues.floorLowerLimit;
}

void set_water_level(u8 index, s16 height, bool sync) {
    if (sync && (!gNetworkPlayerLocal || !gNetworkPlayerLocal->currAreaSyncValid)) { return; }

    u8 id = 6 * (index + 1);
    if (gEnvironmentRegions && index < gEnvironmentRegions[0] && gEnvironmentRegionsLength > id) {
        if (gEnvironmentRegions[id] == height) {
            return;
        }
        if (sync) {
            network_send_change_water_level(id, height);
        }
        gEnvironmentRegions[id] = height;
    }
}

///

bool course_is_main_course(u16 courseNum) {
    return COURSE_IS_MAIN_COURSE(courseNum);
}

///

s16 get_ttc_speed_setting(void) {
    return gTTCSpeedSetting;
}

void set_ttc_speed_setting(s16 speed) {
    gTTCSpeedSetting = speed;
}

///

s64 get_time(void) {
    return time(NULL);
}

struct DateTime* get_date_and_time(void) {
    time_t currentTime;
    time(&currentTime);
    struct tm *lt = localtime(&currentTime);

    sDateTime.year = lt->tm_year;
    sDateTime.month = lt->tm_mon;
    sDateTime.day = lt->tm_mday;
    sDateTime.hour = lt->tm_hour;
    sDateTime.minute = lt->tm_min;
    sDateTime.second = lt->tm_sec;
    return &sDateTime;
}

///

u16 get_envfx(void) {
    return gReadOnlyEnvFx;
}

void set_override_envfx(s32 envfx) {
    gOverrideEnvFx = envfx;
}

///

u32 get_global_timer(void) {
    return gGlobalTimer;
}

///

s32 get_dialog_response(void) {
    return gDialogResponse;
}

///

const char* get_local_discord_id(void) {
#ifdef DISCORD_SDK
    if (gDiscordInitialized) {
        static char sDiscordId[64] = "";
        snprintf(sDiscordId, 64, "%" PRIu64 "", (uint64_t)discord_get_user_id());
        return sDiscordId;
    } else {
        return "0";
    }
#else
    return "0";
#endif
}

const char* get_coopnet_id(UNUSED s8 localIndex) {
#ifdef COOPNET
    if (!gNetworkSystem || gNetworkSystem != &gNetworkSystemCoopNet) { return "-1"; }
    if (localIndex < 0 || localIndex >= MAX_PLAYERS) { return "-1"; }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (np == NULL || !np->connected) { return "-1"; }
    return gNetworkSystem->get_id_str(np->localIndex);
#else
    return "-1";
#endif
}

///

f32 get_volume_master(void) {
    return gLuaVolumeMaster;
}

f32 get_volume_level(void) {
    return gLuaVolumeLevel;
}

f32 get_volume_sfx(void) {
    return gLuaVolumeSfx;
}

f32 get_volume_env(void) {
    return gLuaVolumeEnv;
}

void set_volume_master(f32 volume) {
    gLuaVolumeMaster = MIN(volume, 127);
    audio_custom_update_volume();
}

void set_volume_level(f32 volume) {
    gLuaVolumeLevel = MIN(volume, 127);
    audio_custom_update_volume();
}

void set_volume_sfx(f32 volume) {
    gLuaVolumeSfx = MIN(volume, 127);
    audio_custom_update_volume();
}

void set_volume_env(f32 volume) {
    gLuaVolumeEnv = MIN(volume, 127);
    audio_custom_update_volume();
}

///

f32 get_environment_region(u8 index) {
    s32 idx = 6 * index;
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0] && gEnvironmentRegionsLength > idx) {
        return gEnvironmentRegions[idx];
    }
    return gLevelValues.floorLowerLimit;
}

void set_environment_region(u8 index, s32 value) {
    s32 idx = 6 * index;
    if (gEnvironmentRegions != NULL && index > 0 && index <= gEnvironmentRegions[0] && gEnvironmentRegionsLength > idx) {
        gEnvironmentRegions[idx] = value;
    }
}

///

bool mod_file_exists(const char* filename) {
    if (gLuaActiveMod == NULL) { return false; }

    for (s32 i = 0; i < gLuaActiveMod->fileCount; i++) {
        struct ModFile* file = &gLuaActiveMod->files[i];
        if (!strcmp(file->relativePath, filename)) {
            return true;
        }
    }

    return false;
}

struct Mod* get_active_mod(void) {
    return gLuaActiveMod;
}

///

void set_window_title(const char* title) {
    WAPI.set_window_title(title);
}

void reset_window_title(void) {
    WAPI.reset_window_title();
}

///

const char* get_os_name(void) {
#if defined(_WIN32) || defined(_WIN64)
    return "Windows";
#elif __APPLE__ || __MACH__
    return "Mac OSX"; // should be macOS
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Unknown";
#endif
}
