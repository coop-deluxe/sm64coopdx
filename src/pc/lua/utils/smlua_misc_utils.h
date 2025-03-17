#ifndef SMLUA_MISC_UTILS_H
#define SMLUA_MISC_UTILS_H

#include "dialog_ids.h"
#include "game/camera.h"

enum HudDisplayValue {
    HUD_DISPLAY_LIVES,
    HUD_DISPLAY_COINS,
    HUD_DISPLAY_STARS,
    HUD_DISPLAY_WEDGES,
    HUD_DISPLAY_KEYS,
    HUD_DISPLAY_FLAGS,
    HUD_DISPLAY_TIMER,
    HUD_DISPLAY_CAMERA_STATUS
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
    HUD_DISPLAY_FLAGS_CAMERA = 0x0080,
    HUD_DISPLAY_FLAGS_POWER = 0x0100,
    HUD_DISPLAY_FLAGS_EMPHASIZE_POWER = 0x8000
};

struct DateTime {
    s32 year;
    s32 month;
    s32 day;
    s32 hour;
    s32 minute;
    s32 second;
};


/* |description|Gets the current area's networked timer|descriptionEnd| */
u32 get_network_area_timer(void);
/* |description|Gets the area update counter incremented when objects are updated|descriptionEnd| */
u16 get_area_update_counter(void);

/* |description|Creates a DJUI popup that is broadcasted to every client|descriptionEnd| */
void djui_popup_create_global(const char* message, int lines);
/* |description|Returns if popups are disabled|descriptionEnd| */
bool djui_is_popup_disabled(void);
/* |description|Sets if popups are disabled|descriptionEnd| */
void djui_set_popup_disabled_override(bool value);
/* |description|Resets if popups are disabled|descriptionEnd| */
void djui_reset_popup_disabled_override(void);
/* |description|Checks if the DJUI playerlist is open|descriptionEnd| */
bool djui_is_playerlist_open(void);
/* |description|Checks if the DJUI playerlist is attempting to be opened|descriptionEnd| */
bool djui_attempting_to_open_playerlist(void);
/* |description|Gets the DJUI menu font|descriptionEnd| */
enum DjuiFontType djui_menu_get_font(void);
/* |description|Gets the DJUI menu theme|descriptionEnd| */
struct DjuiTheme* djui_menu_get_theme(void);

/* |description|Gets the current state of the dialog box|descriptionEnd| */
s8 get_dialog_box_state(void);
/* |description|Gets the current dialog box ID|descriptionEnd| */
s16 get_dialog_id(void);

/* |description|Gets if the last objective collected was a star (0) or a key (1)|descriptionEnd| */
u8 get_last_star_or_key(void);
/* |description|Sets if the last objective collected was a star (0) or a key (1)|descriptionEnd| */
void set_last_star_or_key(u8 value);
/* |description|Gets the last course a star or key was collected in|descriptionEnd| */
u8 get_last_completed_course_num(void);
/* |description|Sets the last course a star or key was collected in|descriptionEnd| */
void set_last_completed_course_num(u8 courseNum);
/* |description|Gets the last collected star's number (1-7) |descriptionEnd| */
u8 get_last_completed_star_num(void);
/* |description|Sets the last collected star's number (1-7) |descriptionEnd| */
void set_last_completed_star_num(u8 starNum);
/* |description|Checks if the save file's coin "HI SCORE" was obtained with the last star or key collection|descriptionEnd| */
bool get_got_file_coin_hi_score(void);
/* |description|Sets if the save file's coin "HI SCORE" was obtained with the last star or key collection|descriptionEnd| */
void set_got_file_coin_hi_score(bool value);
/* |description|Checks if the save file has been modified without saving|descriptionEnd| */
bool get_save_file_modified(void);
/* |description|Sets if the save file has been modified without saving|descriptionEnd| */
void set_save_file_modified(bool value);

/* |description|Hides the HUD|descriptionEnd| */
void hud_hide(void);
/* |description|Shows the HUD|descriptionEnd| */
void hud_show(void);
/* |description|Checks if the HUD is hidden|descriptionEnd| */
bool hud_is_hidden(void);
/* |description|Gets a HUD display value|descriptionEnd| */
s32  hud_get_value(enum HudDisplayValue type);
/* |description|Sets a HUD display value|descriptionEnd| */
void hud_set_value(enum HudDisplayValue type, s32 value);
/* |description|Renders a power meter on the HUD|descriptionEnd| */
void hud_render_power_meter(s32 health, f32 x, f32 y, f32 width, f32 height);
/* |description|Renders an interpolated power meter on the HUD|descriptionEnd| */
void hud_render_power_meter_interpolated(s32 health, f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height);
/* |description|Gets if the star counter on the HUD should flash|descriptionEnd| */
s8 hud_get_flash(void);
/* |description|Sets if the star counter on the HUD should flash|descriptionEnd| */
void hud_set_flash(s8 value);

/* |description|Checks if the game is paused|descriptionEnd| */
bool is_game_paused(void);
/* |description|Checks if a screen transition is playing|descriptionEnd| */
bool is_transition_playing(void);

/* |description|Allocates an action ID with bitwise flags|descriptionEnd| */
u32 allocate_mario_action(u32 actFlags);

/* |description|
Gets the X coordinate of Mario's hand (0-1) or foot (2-3)
but it is important to note that the positions are not updated off-screen|descriptionEnd| */
f32 get_hand_foot_pos_x(struct MarioState* m, u8 index);
/* |description|
Gets the Y coordinate of Mario's hand (0-1) or foot (2-3)
but It is important to note that the positions are not updated off-screen|descriptionEnd| */
f32 get_hand_foot_pos_y(struct MarioState* m, u8 index);
/* |description|
Gets the Z coordinate of Mario's hand (0-1) or foot (2-3)
but it is important to note that the positions are not updated off-screen|descriptionEnd| */
f32 get_hand_foot_pos_z(struct MarioState* m, u8 index);

/* |description|Gets the current save file number (1-indexed)|descriptionEnd| */
s16 get_current_save_file_num(void);
/* |description|Checks if the save file is using its backup slot|descriptionEnd| */
bool save_file_get_using_backup_slot(void);
/* |description|Sets if the save file should use its backup slot|descriptionEnd| */
void save_file_set_using_backup_slot(bool usingBackupSlot);

/* |description|Registers a custom moving texture entry (used for vanilla water boxes)|descriptionEnd| */
void movtexqc_register(const char* name, s16 level, s16 area, s16 type);
/* |description|Gets the water level in an area corresponding to `index` (0-indexed)|descriptionEnd| */
s16 get_water_level(u8 index);
/* |description|Sets the water level in an area corresponding to `index` (0-indexed)|descriptionEnd| */
void set_water_level(u8 index, s16 height, bool sync);

/* |description|Plays a screen transition|descriptionEnd| */
void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue);

/* |description|Checks if a course is a main course and not the castle or secret levels|descriptionEnd| */
bool course_is_main_course(u16 courseNum);

/* |description|Gets TTC's speed setting|descriptionEnd| */
s16 get_ttc_speed_setting(void);
/* |description|Sets TTC's speed setting (TTC_SPEED_*)|descriptionEnd| */
void set_ttc_speed_setting(s16 speed);

/* |description|Gets the Unix Timestamp|descriptionEnd| */
s64 get_time(void);
/* |description|Gets the system clock's date and time|descriptionEnd| */
struct DateTime* get_date_and_time(void);

/* |description|Gets the non overridden environment effect (e.g. snow)|descriptionEnd| */
u16 get_envfx(void);
/* |description|Sets the override environment effect (e.g. snow)|descriptionEnd| */
void set_override_envfx(s32 envfx);

/* |description|Gets the global timer that has been ticking at 30 frames per second since game boot|descriptionEnd| */
u32 get_global_timer(void);

/* |description|Gets the choice selected inside of a dialog box (0-1)|descriptionEnd| */
s32 get_dialog_response(void);

/* |description|Gets the local discord ID if it isn't disabled, otherwise "0" is returned|descriptionEnd| */
const char* get_local_discord_id(void);
/* |description|Gets the CoopNet ID of a player with `localIndex` if CoopNet is being used and the player is connected, otherwise "-1" is returned|descriptionEnd| */
const char* get_coopnet_id(s8 localIndex);

/* |description|Gets the master volume level|descriptionEnd| */
f32 get_volume_master(void);
/* |description|Gets the volume level of music|descriptionEnd| */
f32 get_volume_level(void);
/* |description|Gets the volume level of sound effects|descriptionEnd| */
f32 get_volume_sfx(void);
/* |description|Gets the volume level of environment sounds effects|descriptionEnd| */
f32 get_volume_env(void);
/* |description|Sets the master volume level|descriptionEnd| */
void set_volume_master(f32 volume);
/* |description|Sets the volume level of music|descriptionEnd| */
void set_volume_level(f32 volume);
/* |description|Sets the volume level of sound effects|descriptionEnd| */
void set_volume_sfx(f32 volume);
/* |description|Sets the volume level of environment sounds effects|descriptionEnd| */
void set_volume_env(f32 volume);

/* |description|Gets an environment region (gas/water boxes) height value|descriptionEnd| */
f32 get_environment_region(u8 index);
/* |description|Sets an environment region (gas/water boxes) height value|descriptionEnd| */
void set_environment_region(u8 index, s32 value);

/* |description|Checks if a file exists inside of a mod|descriptionEnd| */
bool mod_file_exists(const char* filename);
/* |description|Gets the mod currently being processed|descriptionEnd| */
struct Mod* get_active_mod(void);

/* |description|Sets the window title to a custom title|descriptionEnd| */
void set_window_title(const char* title);
/* |description|Resets the window title|descriptionEnd| */
void reset_window_title(void);

/* |description|Gets the name of the operating system the game is running on|descriptionEnd| */
const char* get_os_name(void);

#endif
