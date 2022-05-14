#ifndef SMLUA_MISC_UTILS_H
#define SMLUA_MISC_UTILS_H

#include "dialog_ids.h"

u32 get_network_area_timer(void);

s32* get_temp_s32_pointer(s32 initialValue);
s32 deref_s32_pointer(s32* pointer);

enum HudDisplayValue {
    HUD_DISPLAY_LIVES,
    HUD_DISPLAY_COINS,
    HUD_DISPLAY_STARS,
    HUD_DISPLAY_WEDGES,
    HUD_DISPLAY_KEYS,
    HUD_DISPLAY_FLAGS,
    HUD_DISPLAY_TIMER,
};

enum HudDisplayFlags {
    HUD_DISPLAY_FLAGS_NONE = 0x0000,
    HUD_DISPLAY_FLAGS_LIVES = 0x0001,
    HUD_DISPLAY_FLAGS_COIN_COUNT = 0x0002,
    HUD_DISPLAY_FLAGS_STAR_COUNT = 0x0004,
    HUD_DISPLAY_FLAGS_CAMERA_AND_POWER = 0x0008,
    HUD_DISPLAY_FLAGS_KEYS = 0x0010,
    HUD_DISPLAY_FLAGS_UNKNOWN_0020 = 0x0020,
    HUD_DISPLAY_FLAGS_TIMER = 0x0040,
    HUD_DISPLAY_FLAGS_EMPHASIZE_POWER = 0x8000,
};

void hud_hide(void);
void hud_show(void);
s32  hud_get_value(enum HudDisplayValue type);
void hud_set_value(enum HudDisplayValue type, s32 value);
void hud_render_power_meter(s32 health, f32 x, f32 y, f32 width, f32 height);

void camera_freeze(void);
void camera_unfreeze(void);

bool is_game_paused(void);

bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
bool warp_restart_level(void);
bool warp_exit_level(s32 aDelay);
bool warp_to_castle(s32 aLevel);

u32 allocate_mario_action(u32 actFlags);

f32 get_hand_foot_pos_x(struct MarioState* m, u8 index);
f32 get_hand_foot_pos_y(struct MarioState* m, u8 index);
f32 get_hand_foot_pos_z(struct MarioState* m, u8 index);

s16 get_current_save_file_num(void);
void save_file_set_using_backup_slot(bool usingBackupSlot);

void movtexqc_register(const char* name, s16 level, s16 area, s16 type);
f32 get_environment_region(u8 index);
void set_environment_region(u8 index, s32 value);

f32 set_override_fov(f32 fov);
f32 set_override_near(f32 near);
f32 set_override_far(f32 far);

void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue);

#endif
