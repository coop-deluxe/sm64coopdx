#include "controller_keyboard_debug.h"
#include "game/level_update.h"
#include "game/camera.h"
#include "pc/network/network.h"

#ifdef DEBUG

static u8 warpToLevel = LEVEL_LLL;

#define SCANCODE_0 0x0B
#define SCANCODE_3 0x04
#define SCANCODE_6 0x07
#define SCANCODE_7 0x08

static void debug_breakpoint_here(void) {
    // create easy breakpoint position for debugging
}

static void debug_warp_level(u8 level) {
    if (sCurrPlayMode == PLAY_MODE_CHANGE_LEVEL) { return; }
    if (sCurrPlayMode == PLAY_MODE_SYNC_LEVEL) { return; }

    // find level from painting
    for (int i = 0; i < 45; i++) {
        struct WarpNode* node = &gCurrentArea->paintingWarpNodes[i];
        if (node == NULL) { break; }
        if (node->destLevel == level) {
            sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
            sWarpDest.levelNum = node->destLevel;
            sWarpDest.areaIdx = node->destArea;
            sWarpDest.nodeId = node->destNode;
            sWarpDest.arg = 0;

            sCurrPlayMode = PLAY_MODE_SYNC_LEVEL;
            network_send_level_warp_begin();
            return;
        }
    }

    struct ObjectWarpNode* objectNode = gCurrentArea->warpNodes;
    while (objectNode != NULL) {
        struct WarpNode* node = &objectNode->node;
        if (node->destLevel == level) {
            sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
            sWarpDest.levelNum = node->destLevel;
            sWarpDest.areaIdx = node->destArea;
            sWarpDest.nodeId = node->destNode;
            sWarpDest.arg = 0;

            sCurrPlayMode = PLAY_MODE_SYNC_LEVEL;
            network_send_level_warp_begin();
            return;
        }
        objectNode = objectNode->next;
    }

    // failed, go to main castle area
    sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    sWarpDest.levelNum = LEVEL_CASTLE;
    sWarpDest.areaIdx = 1;
    sWarpDest.nodeId = 0x1F;
    sWarpDest.arg = 0;
    sCurrPlayMode = PLAY_MODE_SYNC_LEVEL;
    D_80339ECA = 0;
    D_80339EE0 = 0;
    extern s16 gSavedCourseNum;
    gSavedCourseNum = 0;
    network_send_level_warp_begin();
}

static void debug_warp_area() {
    if (sCurrPlayMode == PLAY_MODE_CHANGE_LEVEL) { return; }
    if (sCurrPlayMode == PLAY_MODE_SYNC_LEVEL) { return; }

    struct ObjectWarpNode* objectNode = gCurrentArea->warpNodes;
    while (objectNode != NULL) {
        struct WarpNode* node = &objectNode->node;
        if (node->destLevel == gCurrLevelNum && node->destArea != gCurrAreaIndex) {
            sWarpDest.type = WARP_TYPE_CHANGE_AREA;
            sWarpDest.levelNum = node->destLevel;
            sWarpDest.areaIdx = node->destArea;
            sWarpDest.nodeId = node->destNode;
            sWarpDest.arg = 0;

            sCurrPlayMode = PLAY_MODE_SYNC_LEVEL;
            network_send_level_warp_begin();
            return;
        }
        objectNode = objectNode->next;
    }
}

static void debug_suicide(void) {
    gMarioStates[0].hurtCounter = 31;
}

void debug_keyboard_on_key_down(int scancode) {
    scancode = scancode;
    switch (scancode) {
        case SCANCODE_3: debug_breakpoint_here(); break;
#ifdef DEVELOPMENT
        case SCANCODE_6: debug_warp_level(warpToLevel); break;
        case SCANCODE_7: debug_warp_area(); break;
        case SCANCODE_0: debug_suicide(); break;
#endif
    }
}

#endif