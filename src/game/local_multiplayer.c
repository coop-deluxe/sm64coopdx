#include "local_multiplayer.h"
#include "pc/network/network.h"
#include "level_update.h"
#include "pc/lua/smlua.h"
#include "gfx_dimensions.h"

static struct MarioState tempM = { 0 };
static struct NetworkPlayer tempNp = { 0 };
static struct LakituState tempLs = { 0 };
static struct Controller tempCtr = { 0 };

static struct GfxLoad dls[POSSIBLE_NUM_PLAYERS] = { 0 };

struct Controller gSharedController = { 0 };
struct Controller *gSharedCtr = &gSharedController;

Gfx *sRenderBehindPos = NULL;

enum NetworkType nType = NT_NONE;

u16 realPlayerIndex = 0;

int gSx = 0;
int gSy = 0;

int gSw = 2;
int gSh = 2;

u16 gNumPlayersLocal = 2;

u16 gCurrPlayer = 0;

bool twoPlayerLandscape = true;

static const ScreenSize screenSizes[] = {
    { 2, 2, 1.f },
    { 2, 1, 2.f },
    { 1, 1, 2.f },
    { 1, 1, 1.f },
};

float aspect_mask = 1.f;

static int patchCurState = -1;
static bool patchAwait = false;
void patch_mario_state_player_index(u8 index) {
    if (index != 0 && index < gNumPlayersLocal) {
        realPlayerIndex = index; // Make sure we can still know what player it really is

        // Swap player indexes, so treat this Mario as the local Mario
        gMarioStates[index].playerIndex = 0;
        gMarioStates[0].playerIndex = index;

        // Fully swap the two Mario states
        // have to do this so that interactions between the two players works
        memcpy(&tempM, &gMarioStates[0], sizeof(struct MarioState));
        memcpy(&gMarioStates[0], &gMarioStates[index], sizeof(struct MarioState));
        memcpy(&gMarioStates[index], &tempM, sizeof(struct MarioState));
        gMarioState = &gMarioStates[0];

        // Network hacks to make things behave
        nType = gNetworkType;
        gNetworkType = NT_CLIENT;
        gNetworkPlayerServer = &gNetworkPlayers[index];
        gNetworkPlayerLocal = &gNetworkPlayers[index];

        // Remember the last state
        patchCurState = index;
        patchAwait = true;
    }
}

void unpatch_mario_state_player_index() {
    if (patchAwait) {
        realPlayerIndex = 0;

        // Swap back the two Mario states
        memcpy(&tempM, &gMarioStates[patchCurState], sizeof(struct MarioState));
        memcpy(&gMarioStates[patchCurState], &gMarioStates[0], sizeof(struct MarioState));
        memcpy(&gMarioStates[0], &tempM, sizeof(struct MarioState));
        gMarioState = &gMarioStates[patchCurState];

        // Set the player indexes to be right again
        gMarioStates[patchCurState].playerIndex = patchCurState;
        gMarioStates[0].playerIndex = 0;

        // Restore the network variables
        gNetworkType = nType;
        gNetworkPlayerServer = &gNetworkPlayers[0];
        gNetworkPlayerLocal = &gNetworkPlayers[0];

        patchAwait = false;
    }
}

extern struct EnvFxParticle *gEnvFxBuffers[];
extern struct EnvFxParticle *gEnvFxBuffer;

void set_local_player(u8 index) {
    static int lastIndex = -1;
    if (index >= gNumPlayersLocal) { return; } // Only allowed splitscreen players
    memcpy(&gHudDisplays[index], &gHudDisplay, sizeof(struct HudDisplay)); // why does lastIndex not work? it's using index now (guess: there's probably more to it than i thought)
    memcpy(&gHudDisplay, &gHudDisplays[index], sizeof(struct HudDisplay));
    set_screen_rendering(index);
    swap_lakitu_state(index);
    // gEnvFxBuffers[lastIndex] = gEnvFxBuffer;
    // gEnvFxBuffer = gEnvFxBuffers[index];
    lastIndex = index;
}

void unset_local_player() {
    set_local_player(0);
}

void save_player_dl(u8 index, Gfx *gl, int len) {
    dls[index].len = len;
    dls[index].gfx = gl;
}

struct GfxLoad *load_player_dl(u8 index) {
    return &dls[index];
}

#define transform_x(type) void transform_x_##type(type *x, enum HudUtilsResolution res) { \
    f32 w = 1.f; \
    if (gSx == 0) { w = 0.f; } \
    if (gSx == 1) { w = 0.5f; } \
    if (res == RESOLUTION_DJUI) { \
        u32 windowWidth, windowHeight; \
        gfx_get_dimensions(&windowWidth, &windowHeight); \
        *x += windowHeight * w; \
    } else { \
        *x += GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_WIDTH * w; \
    } \
} \
void subtract_x_##type(type *x, enum HudUtilsResolution res) { \
    f32 w = 1.f; \
    if (gSx == 0) { w = 0.5f; } \
    if (gSx == 1) { w = 1.f; } \
    if (res == RESOLUTION_DJUI) { \
        u32 windowWidth, windowHeight; \
        gfx_get_dimensions(&windowWidth, &windowHeight); \
        *x -= windowHeight * w; \
    } else if (gSx == 0) { /* checking this because for some reason it's inverted */ \
        *x -= GFX_SCREEN_WIDTH(); \
    } \
}

#define transform_y(type) void transform_y_##type(type *y, enum HudUtilsResolution res) { \
    f32 h = 1.f; \
    if (gSy == 0) { h = 0.f; } \
    if (gSy == 1) { h = 0.5f; } \
    if (res == RESOLUTION_DJUI) { \
        u32 windowWidth, windowHeight; \
        gfx_get_dimensions(&windowWidth, &windowHeight); \
        *y += windowHeight * h; \
    } else { \
        *y += SCREEN_HEIGHT * h; \
    } \
} \
void subtract_y_##type(type *y, enum HudUtilsResolution res) { \
    f32 h = 1.f; \
    if (gSy == 0) { h = 0.5f; } \
    if (gSy == 1) { h = 0.f; } \
    if (res == RESOLUTION_DJUI) { \
        u32 windowWidth, windowHeight; \
        gfx_get_dimensions(&windowWidth, &windowHeight); \
        *y -= windowHeight * h; \
    } else { \
        *y -= SCREEN_HEIGHT * h; \
    } \
}

#define transform(type) transform_x(type) transform_y(type)

transform(s16)
transform(u16)
transform(s32)
transform(u32)
transform(f32)

Vp *viewport_set_scale(f32 x, f32 y, f32 scaleW, f32 scaleH) {
    static Vp tmp = { {
        { 640, 480, 511, 0 },
        { 640, 480, 511, 0 },
    } };
    static Vp vps[POSSIBLE_NUM_PLAYERS] = { 0 };
    Vp *vp = &vps[gCurrPlayer];
    memcpy(vp, &tmp, sizeof(Vp));
    Vp_t *viewport = &vp->vp;
    viewport->vscale[0] = scaleW * 2.0f;
    viewport->vscale[1] = scaleH * 2.0f;
    viewport->vtrans[0] = (scaleW + x) * 2.0f;
    viewport->vtrans[1] = (scaleH + y) * 2.0f;
    return vp;
}

void set_screen_rendering(u16 index) {
    gCurrPlayer = index;
    switch (index) {
        case 0: gSx = 0, gSy = 0; break;
        case 1:
            if (twoPlayerLandscape && gNumPlayersLocal == 2) {
                gSx = 0, gSy = 1;
            } else {
                gSx = 1, gSy = 0;
            }
            break;
        case 2: gSx = 0, gSy = 1; break;
        case 3: gSx = 1, gSy = 1; break;
    }

    const ScreenSize *size = &screenSizes[gNumPlayersLocal - 1];
    gSw = size->w;
    gSh = size->h;
    aspect_mask = size->a;
}
