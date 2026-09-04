#ifndef LEVEL_UPDATE_H
#define LEVEL_UPDATE_H

#include <PR/ultratypes.h>

#include "types.h"

#include "pc/djui/djui.h"

enum TimerControl {
    TIMER_CONTROL_SHOW,
    TIMER_CONTROL_START,
    TIMER_CONTROL_STOP,
    TIMER_CONTROL_HIDE
};

enum WarpOperation {
    WARP_OP_NONE,
    WARP_OP_LOOK_UP,
    WARP_OP_SPIN_SHRINK,
    WARP_OP_WARP_DOOR,
    WARP_OP_WARP_OBJECT,
    WARP_OP_TELEPORT,
    WARP_OP_TRIGGERS_LEVEL_SELECT = 0x10,
    WARP_OP_STAR_EXIT,
    WARP_OP_DEATH,
    WARP_OP_WARP_FLOOR,
    WARP_OP_GAME_OVER,
    WARP_OP_CREDITS_END,
    WARP_OP_DEMO_NEXT,
    WARP_OP_CREDITS_START,
    WARP_OP_CREDITS_NEXT,
    WARP_OP_DEMO_END,
    WARP_OP_FORCE_SYNC,
    WARP_OP_EXIT
};

enum SpecialWarpDestination {
    WARP_SPECIAL_LEVEL_SELECT        = -9,
    WARP_SPECIAL_INTRO_SPLASH_SCREEN = -8,
    WARP_SPECIAL_SWITCH_FILE         = -7,
    WARP_SPECIAL_MARIO_HEAD_DIZZY    = -3,
    WARP_SPECIAL_MARIO_HEAD_REGULAR  = -2,
    WARP_SPECIAL_ENDING              = -1,
    WARP_SPECIAL_NONE                =  0,
};

enum WarpFlags {
    WARP_FLAG_NONE            = (0 << 0),
    WARP_FLAG_DOOR_PULLED     = (1 << 0),
    WARP_FLAG_DOOR_FLIP_MARIO = (1 << 1),
    WARP_FLAG_DOOR_IS_WARP    = (1 << 2),
    WARP_FLAG_EXIT_COURSE     = (1 << 3),
};

enum MarioSpawnType {
    MARIO_SPAWN_NONE,
    MARIO_SPAWN_DOOR_WARP,
    MARIO_SPAWN_IDLE,
    MARIO_SPAWN_PIPE,
    MARIO_SPAWN_TELEPORT,
    MARIO_SPAWN_INSTANT_ACTIVE = 0x10,
    MARIO_SPAWN_SWIMMING,
    MARIO_SPAWN_AIRBORNE,
    MARIO_SPAWN_HARD_AIR_KNOCKBACK,
    MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE,
    MARIO_SPAWN_DEATH,
    MARIO_SPAWN_SPIN_AIRBORNE,
    MARIO_SPAWN_FLYING,
    MARIO_SPAWN_PAINTING_STAR_COLLECT = 0x20,
    MARIO_SPAWN_PAINTING_DEATH,
    MARIO_SPAWN_AIRBORNE_STAR_COLLECT,
    MARIO_SPAWN_AIRBORNE_DEATH,
    MARIO_SPAWN_LAUNCH_STAR_COLLECT,
    MARIO_SPAWN_LAUNCH_DEATH,
    MARIO_SPAWN_UNUSED_38,
    MARIO_SPAWN_FADE_FROM_BLACK
};

enum WarpNodes {
    WARP_NODE_MAIN_ENTRY    = 0x0A,
    WARP_NODE_DEFAULT       = 0xF0,
    WARP_NODE_DEATH         = 0xF1,
    WARP_NODE_LOOK_UP       = 0xF2,
    WARP_NODE_WARP_FLOOR    = 0xF3,
    WARP_NODE_CREDITS_MIN   = 0xF8,
    WARP_NODE_CREDITS_START = 0xF8,
    WARP_NODE_CREDITS_NEXT  = 0xF9,
    WARP_NODE_CREDITS_END   = 0xFA
};

enum WarpType {
    WARP_TYPE_NOT_WARPING,
    WARP_TYPE_CHANGE_LEVEL,
    WARP_TYPE_CHANGE_AREA,
    WARP_TYPE_SAME_AREA
};

#define PRESS_START_DEMO_TIMER 800

// From Surface 0xD3 to 0xFC
#define PAINTING_WARP_INDEX_START 0x00 // Value greater than or equal to Surface 0xD3
#define PAINTING_WARP_INDEX_FA 0x2A    // THI Huge Painting index left
#define PAINTING_WARP_INDEX_END 0x2D   // Value less than Surface 0xFD

struct CreditsEntry
{
    /*0x00*/ u8 levelNum;
    /*0x01*/ u8 areaIndex;
    /*0x02*/ u8 actNum;
    /*0x03*/ s8 marioAngle;
    /*0x04*/ Vec3s marioPos;
    /*0x0C*/ const char **string;
};

extern struct CreditsEntry *gCurrCreditsEntry;

extern struct MarioState gMarioStates[];
extern struct MarioState *gMarioState;

extern s16 sCurrPlayMode;
extern s16 sTransitionTimer;
extern void (*sTransitionUpdate)(s16 *);

extern s16 gChangeLevel;
extern s16 gChangeActNum;
extern s16 gDelayedInitSound;

struct WarpDest {
    u8 type;
    s16 levelNum;
    u8 areaIdx;
    u8 nodeId;
    u32 arg;
};

extern struct WarpDest sWarpDest;
extern s8 sWarpCheckpointActive;
extern u16 gFanfareDebounce;

extern s16 sSpecialWarpDest;
extern s16 sDelayedWarpOp;
extern s16 sDelayedWarpTimer;
extern s16 sSourceWarpNodeId;
extern s32 sDelayedWarpArg;
extern s8 sTimerRunning;

struct HudDisplay {
    /*0x00*/ s16 lives;
    /*0x02*/ s16 coins;
    /*0x04*/ s16 stars;
    /*0x06*/ s16 wedges;
    /*0x08*/ s16 keys;
    /*0x0A*/ s16 flags;
    /*0x0C*/ u16 timer;
};

extern struct HudDisplay gHudDisplay;
extern bool gNeverEnteredCastle;

extern u32 gControlTimerStartNat;
extern u32 gControlTimerStopNat;

enum HUDDisplayFlag {
    HUD_DISPLAY_FLAG_LIVES = 0x0001,
    HUD_DISPLAY_FLAG_COIN_COUNT = 0x0002,
    HUD_DISPLAY_FLAG_STAR_COUNT = 0x0004,
    HUD_DISPLAY_FLAG_CAMERA_AND_POWER = 0x0008,
    HUD_DISPLAY_FLAG_KEYS = 0x0010,
    HUD_DISPLAY_FLAG_UNKNOWN_0020 = 0x0020,
    HUD_DISPLAY_FLAG_TIMER = 0x0040,
    HUD_DISPLAY_FLAG_CAMERA = 0x0080,
    HUD_DISPLAY_FLAG_POWER = 0x0100,
    HUD_DISPLAY_FLAG_EMPHASIZE_POWER = 0x8000,

    HUD_DISPLAY_NONE = 0x0000,
    HUD_DISPLAY_DEFAULT = HUD_DISPLAY_FLAG_LIVES | HUD_DISPLAY_FLAG_COIN_COUNT | HUD_DISPLAY_FLAG_STAR_COUNT | HUD_DISPLAY_FLAG_CAMERA_AND_POWER | HUD_DISPLAY_FLAG_CAMERA | HUD_DISPLAY_FLAG_POWER | HUD_DISPLAY_FLAG_KEYS | HUD_DISPLAY_FLAG_UNKNOWN_0020
};

/* |description|Returns if the level timer is running|descriptionEnd| */
u8 level_control_timer_running(void);
u16 level_control_timer(s32 timerOp);
/* |description|Checks if the start button has been pressed as well as some other conditions for opening the pause menu depending on if pause anywhere is enabled|descriptionEnd|*/
bool pressed_pause(void);
/* |description|Fades into a special warp with `arg` and using `color`|descriptionEnd| */
void fade_into_special_warp(enum SpecialWarpDestination arg, u32 color);
void load_level_init_text(u32 arg);
void warp_credits(void);
/* |description|Gets an instant warp from the current area's instant warp array (0-3)|descriptionEnd| */
struct InstantWarp *get_instant_warp(u8 index);
/* |description|Gets a painting warp node from the local mario's floor type|descriptionEnd| */
struct WarpNode *get_painting_warp_node(void);
/* |description|Initiates a painting warp of `paintingIndex`|descriptionEnd| */
void initiate_painting_warp(s16 paintingIndex);
/* |description|Triggers a warp (WARP_OP_*) for the level. Pass in `gMarioStates[0]` for `m`|descriptionEnd| */
s16 level_trigger_warp(struct MarioState *m, enum WarpOperation warpOp);
void level_set_transition(s16 length, void (*updateFunction)(s16 *));
void set_play_mode(s16 playMode);
/* |description|Special warps to arg (`WARP_SPECIAL_*`)|descriptionEnd| */
void warp_special(enum SpecialWarpDestination arg);
/* |description|Initiates a warp to `destLevel` in `destArea` at `destWarpNode` with `warpFlags`. This function is unstable and it's generally recommended to use `warp_to_level` instead|descriptionEnd| */
void initiate_warp(s16 destLevel, s16 destArea, s16 destWarpNode, s32 warpFlags);

s32 lvl_init_or_update(s16 initOrUpdate, UNUSED s32 unused);
s32 lvl_init_from_save_file(UNUSED s16 arg0, s16 levelNum);
/* |description|Sets the level number and handles the act select screen. `param` is used for overriding the level ID in level scripts, set to 0 in Lua|descriptionEnd| */
s32 lvl_set_current_level(s16 param, s16 levelNum);
s32 lvl_play_the_end_screen_sound(UNUSED s16 arg0, UNUSED s32 arg1);
void basic_update(UNUSED s16 *arg);

s32 init_level(void);

void star_select_finish_selection(void);

s32 lvl_exiting_credits(UNUSED s16 arg0, UNUSED s32 arg1);

void fake_lvl_init_from_save_file(void);
void lvl_skip_credits(void);

s16 get_menu_level(void);
void update_menu_level(void);
void stop_demo(UNUSED struct DjuiBase* caller);

#endif // LEVEL_UPDATE_H
