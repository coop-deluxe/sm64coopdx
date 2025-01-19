#ifndef LEVEL_UPDATE_H
#define LEVEL_UPDATE_H

#include <PR/ultratypes.h>

#include "types.h"

#include "pc/djui/djui.h"

#define TIMER_CONTROL_SHOW  0
#define TIMER_CONTROL_START 1
#define TIMER_CONTROL_STOP  2
#define TIMER_CONTROL_HIDE  3

#define WARP_OP_NONE                      0x00
#define WARP_OP_LOOK_UP                   0x01
#define WARP_OP_SPIN_SHRINK               0x02
#define WARP_OP_WARP_DOOR                 0x03
#define WARP_OP_WARP_OBJECT               0x04
#define WARP_OP_TELEPORT                  0x05
#define WARP_OP_STAR_EXIT                 0x11
#define WARP_OP_DEATH                     0x12
#define WARP_OP_WARP_FLOOR                0x13
#define WARP_OP_GAME_OVER                 0x14
#define WARP_OP_CREDITS_END               0x15
#define WARP_OP_DEMO_NEXT                 0x16
#define WARP_OP_CREDITS_START             0x17
#define WARP_OP_CREDITS_NEXT              0x18
#define WARP_OP_DEMO_END                  0x19
#define WARP_OP_FORCE_SYNC                0x20
#define WARP_OP_EXIT                      0x21

#define WARP_OP_TRIGGERS_LEVEL_SELECT 0x10

#define SPECIAL_WARP_CAKE -1
#define SPECIAL_WARP_GODDARD -2
#define SPECIAL_WARP_GODDARD_GAMEOVER -3
#define SPECIAL_WARP_TITLE -8
#define SPECIAL_WARP_LEVEL_SELECT -9

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

#define MARIO_SPAWN_UNKNOWN_02            0x02
#define MARIO_SPAWN_UNKNOWN_03            0x03
#define MARIO_SPAWN_UNKNOWN_27            0x27

#define WARP_NODE_F0 0xF0
#define WARP_NODE_DEATH 0xF1
#define WARP_NODE_F2 0xF2
#define WARP_NODE_WARP_FLOOR 0xF3
#define WARP_NODE_CREDITS_START 0xF8
#define WARP_NODE_CREDITS_NEXT 0xF9
#define WARP_NODE_CREDITS_END 0xFA
#define WARP_NODE_CREDITS_MIN 0xF8

#define WARP_TYPE_NOT_WARPING 0
#define WARP_TYPE_CHANGE_LEVEL 1
#define WARP_TYPE_CHANGE_AREA 2
#define WARP_TYPE_SAME_AREA 3

#define PRESS_START_DEMO_TIMER 800

// From Surface 0xD3 to 0xFC
#define PAINTING_WARP_INDEX_START 0x00 // Value greater than or equal to Surface 0xD3
#define PAINTING_WARP_INDEX_FA 0x2A    // THI Huge Painting index left
#define PAINTING_WARP_INDEX_END 0x2D   // Value less than Surface 0xFD

struct CreditsEntry
{
    /*0x00*/ u8 levelNum;
    /*0x01*/ u8 areaIndex;
    /*0x02*/ u8 unk02;
    /*0x03*/ s8 marioAngle;
    /*0x04*/ Vec3s marioPos;
    /*0x0C*/ const char **unk0C;
};

extern struct CreditsEntry *gCurrCreditsEntry;

extern struct MarioState gMarioStates[];
extern struct MarioState *gMarioState;

extern s16 sCurrPlayMode;
extern u16 D_80339ECA;
extern s16 sTransitionTimer;
extern void (*sTransitionUpdate)(s16 *);
extern u8 unused3[4];

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

struct SavedWarpValues {
    u8 received;
    struct WarpDest warpDest;
    s8 inWarpCheckpoint;
    s16 ttcSpeedSetting;
    s16 D_80339EE0;
    f32 paintingMarioYEntry;
};

extern struct WarpDest sWarpDest;
extern s8 sWarpCheckpointActive;
extern u8 gRejectInstantWarp;
extern u16 gFanFareDebounce;

extern s16 D_80339EE0;
extern s16 sDelayedWarpOp;
extern s16 sDelayedWarpTimer;
extern s16 sSourceWarpNodeId;
extern s32 sDelayedWarpArg;
extern u8 unused4[2];
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
/* |description|Fades into a special warp with `arg` and using `color`|descriptionEnd| */
void fade_into_special_warp(u32 arg, u32 color);
void load_level_init_text(u32 arg);
void warp_credits(void);
/* |description|Gets an instant warp from the current area's instant warp array (0-3)|descriptionEnd| */
struct InstantWarp *get_instant_warp(u8 index);
/* |description|Gets a painting warp node from the local mario's floor type|descriptionEnd| */
struct WarpNode *get_painting_warp_node(void);
/* |description|Initiates a painting warp of `paintingIndex`|descriptionEnd| */
void initiate_painting_warp(s16 paintingIndex);
/* |description|Triggers a warp (WARP_OP_*) for the level. Pass in `gMarioStates[0]` for `m`|descriptionEnd| */
s16 level_trigger_warp(struct MarioState *m, s32 warpOp);
void level_set_transition(s16 length, void (*updateFunction)(s16 *));
/* |description|Special warps to arg (`SPECIAL_WARP_*`)|descriptionEnd| */
void warp_special(s32 arg);
/* |description|Initiates a warp to `destLevel` in `destArea` at `destWarpNode` with `arg`. This function is unstable and it's generally recommended to use `warp_to_level` instead|descriptionEnd| */
void initiate_warp(s16 destLevel, s16 destArea, s16 destWarpNode, s32 arg);

s32 lvl_init_or_update(s16 initOrUpdate, UNUSED s32 unused);
s32 lvl_init_from_save_file(UNUSED s16 arg0, s16 levelNum);
/* |description|Sets the level number and handles the act select screen|descriptionEnd| */
s32 lvl_set_current_level(s16 arg0, s16 levelNum);
s32 lvl_play_the_end_screen_sound(UNUSED s16 arg0, UNUSED s32 arg1);
void basic_update(UNUSED s16 *arg);

s32 init_level(void);

void star_select_finish_selection(void);

s32 lvl_exiting_credits(UNUSED s16 arg0, UNUSED s32 arg1);

void fake_lvl_init_from_save_file(void);
void lvl_skip_credits(void);

void update_menu_level(void);
void stop_demo(UNUSED struct DjuiBase* caller);

#endif // LEVEL_UPDATE_H
