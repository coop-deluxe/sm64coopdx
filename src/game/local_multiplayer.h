#define POSSIBLE_NUM_PLAYERS 4

#ifndef GET_NUM_CONST

#include <PR/ultratypes.h>

#include "buffers/buffers.h"

#include "game/level_update.h"
#include "pc/djui/djui_hud_utils.h"

extern int gSx;
extern int gSy;

extern int gSw;
extern int gSh;

extern int numPlayersLocal;

extern int gCurrPlayer;

extern u16 realPlayerIndex;

extern Gfx *sRenderBehindPos;

extern struct Area gCurrentAreaCopies[];

extern struct LakituState gLakituStates[];

extern struct HudDisplay gHudDisplays[];

extern struct Controller gSharedController;
extern struct Controller *gSharedCtr;

typedef struct { u8 w, h; f32 a; } ScreenSize;

struct GfxLoad {
    int len;
    Gfx *gfx;
};

extern void set_screen_rendering(u16 index);

void swap_lakitu_state(u8 index);

void patch_mario_state_player_index(u8 index);
void unpatch_mario_state_player_index();

void set_local_player(u8 index);
void unset_local_player();

void save_player_dl(u8 index, Gfx *gl, int len);
struct GfxLoad *load_player_dl(u8 index);

#define sub(type)\
void transform_x_##type(type *x, enum HudUtilsResolution res); \
void subtract_x_##type(type *x, enum HudUtilsResolution res); \
void transform_y_##type(type *y, enum HudUtilsResolution res); \
void subtract_y_##type(type *y, enum HudUtilsResolution res);

sub(s16)
sub(u16)
sub(s32)
sub(u32)
sub(f32)

Vp *viewport_set_scale(f32 x, f32 y, f32 scaleW, f32 scaleH);

#endif
