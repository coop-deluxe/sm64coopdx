#include "dynos.cpp.h"
extern "C" {
#include "sm64.h"
#include "seq_ids.h"
#include "course_table.h"
#include "audio/external.h"
#include "engine/surface_collision.h"
#include "game/mario.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"
#include "game/sound_init.h"
#include "game/object_list_processor.h"
#include "pc/network/packets/packet.h"
#include "pc/lua/smlua_hooks.h"
extern s8 gDialogBoxState;
extern s16 gMenuMode;
extern s32 gWdwWaterLevelSet;
extern u8 sSpawnTypeFromWarpBhv[];
extern void set_mario_initial_action(struct MarioState *, u32, u32);
extern void set_play_mode(s16);
}

//
// Data
//

       s32 gDDDBowsersSub     = -1;
       s32 gDDDPoles          = -1;
static s32 sDynosWarpLevelNum = -1;
static s32 sDynosWarpAreaNum  = -1;
static s32 sDynosWarpActNum   = -1;
static s32 sDynosWarpNodeNum  = -1;
static s32 sDynosExitLevelNum = -1;
static s32 sDynosExitAreaNum  = -1;

//
// Specific Warp Node
//

bool DynOS_Warp_ToWarpNode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId) {
    if (!DynOS_Level_GetWarp(aLevel, aArea, aWarpId)) {
        return false;
    }

    if (aLevel != gCurrLevelNum) {
        // stop music
        play_music(SEQ_PLAYER_LEVEL, 0, 0);
    }

    sDynosWarpLevelNum = aLevel;
    sDynosWarpAreaNum  = aArea;
    sDynosWarpActNum   = aAct;
    sDynosWarpNodeNum  = aWarpId;
    return true;
}

//
// Level Entry
//

bool DynOS_Warp_ToLevel(s32 aLevel, s32 aArea, s32 aAct) {
    if (!DynOS_Level_GetWarpEntry(aLevel, aArea)) {
        return false;
    }

    // stop music
    play_music(SEQ_PLAYER_LEVEL, 0, 0);

    sDynosWarpLevelNum = aLevel;
    sDynosWarpAreaNum  = aArea;
    sDynosWarpActNum   = aAct;
    return true;
}

bool DynOS_Warp_RestartLevel() {
    return DynOS_Warp_ToLevel(gCurrLevelNum, 1, gCurrActNum);
}

//
// Level Exit
//

bool DynOS_Warp_ExitLevel(s32 aDelay) {
    if (DynOS_Level_GetCourse(gCurrLevelNum) == COURSE_NONE || !DynOS_Level_GetWarpDeath(gCurrLevelNum, gCurrAreaIndex)) {
        return false;
    }

    // Close the pause menu if it was open
    level_set_transition(0, NULL);
    gDialogBoxState = 0;
    gMenuMode = -1;

    // Cancel out every music/sound/sequence
    for (u16 seqid = 0; seqid != SEQ_COUNT; ++seqid) {
        stop_background_music(seqid);
    }
    play_shell_music();
    stop_shell_music();
    stop_cap_music();
    stop_secondary_music(0);
    fadeout_music(0);
    fadeout_level_music(0);

    // Play Mario head transition, and change play mode to avoid getting stuck on the pause menu
    aDelay = MAX(1, aDelay);
    gMarioState->invincTimer = -1;
    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, aDelay, 0x00, 0x00, 0x00);
    set_play_mode(0);
    sDynosExitLevelNum = gCurrLevelNum;
    sDynosExitAreaNum = gCurrAreaIndex;
    return true;
}

bool DynOS_Warp_ToCastle(s32 aLevel) {
    if (DynOS_Level_GetCourse(aLevel) == COURSE_NONE || !DynOS_Level_GetWarpDeath(aLevel, 1)) {
        return false;
    }

    // Close the pause menu if it was open
    level_set_transition(0, NULL);
    gDialogBoxState = 0;
    gMenuMode = -1;

    // Cancel out every music/sound/sequence
    for (u16 seqid = 0; seqid != SEQ_COUNT; ++seqid) {
        stop_background_music(seqid);
    }
    play_shell_music();
    stop_shell_music();
    stop_cap_music();
    stop_secondary_music(0);
    fadeout_music(0);
    fadeout_level_music(0);

    // Change play mode to avoid getting stuck on the pause menu
    set_play_mode(0);
    sDynosExitLevelNum = aLevel;
    sDynosExitAreaNum = 1;
    return true;
}

//
// Update
//

static void *DynOS_Warp_UpdateWarp(void *aCmd, bool aIsLevelInitDone) {
    static s32 sDynosWarpTargetArea = -1;

    // Phase 1 - Clear the previous level and set up the new level
    if (sDynosWarpTargetArea == -1) {

        // Close the pause menu if it was open
        level_set_transition(0, NULL);
        gDialogBoxState = 0;
        gMenuMode = -1;

        // Cancel out every music/sound/sequence
        for (u16 seqid = 0; seqid != SEQ_COUNT; ++seqid) {
            stop_background_music(seqid);
        }
        play_shell_music();
        stop_shell_music();
        stop_cap_music();
        stop_secondary_music(0);
        fadeout_music(0);
        fadeout_level_music(0);

        // Free everything from the current level
        clear_objects();
        clear_area_graph_nodes();
        clear_areas();

        // Reset Mario's state
        gMarioState->healCounter = 0;
        gMarioState->hurtCounter = 0;
        gMarioState->numCoins = 0;
        gMarioState->input = 0;
        gMarioState->controller->buttonPressed = 0;
        gHudDisplay.coins = 0;

        // Set up new level values
        gCurrLevelNum = sDynosWarpLevelNum;
        gCurrCourseNum = DynOS_Level_GetCourse(gCurrLevelNum);
        gSavedCourseNum = gCurrCourseNum;
        gCurrActNum = MAX(0, sDynosWarpActNum * (gCurrCourseNum <= COURSE_STAGES_MAX));
        gDialogCourseActNum = gCurrActNum;
        gCurrAreaIndex = sDynosWarpAreaNum;
        gCurrActStarNum = sDynosWarpActNum;
        sDynosWarpTargetArea = gCurrAreaIndex;

        // Set up new level script
        sWarpDest.type = 0;
        sWarpDest.levelNum = 0;
        sWarpDest.areaIdx = gCurrAreaIndex;
        sWarpDest.nodeId = 0;
        sWarpDest.arg = 0;
        return (void *) DynOS_Level_GetScript(gCurrLevelNum);

    } else {

        // Phase 2 - Set Mario spawn info after the MARIO_POS command
        if (*((u8 *) aCmd) == 0x2B) {
            gMarioSpawnInfo->areaIndex = sDynosWarpTargetArea;
            gCurrAreaIndex = sDynosWarpTargetArea;
        }

        // Phase 3 - End level initialization
        if (aIsLevelInitDone && gMarioObjects[0]) {

            // Get Warp
            s16 *_Warp;
            if (sDynosWarpNodeNum == -1) {
                _Warp = DynOS_Level_GetWarpEntry(gCurrLevelNum, gCurrAreaIndex);
            } else {
                _Warp = DynOS_Level_GetWarp(gCurrLevelNum, gCurrAreaIndex, sDynosWarpNodeNum);
            }
            s16 sDynosWarpSpawnType = sSpawnTypeFromWarpBhv[_Warp[2]];

            // Init Mario
            gMarioSpawnInfo->startPos[0] = _Warp[3] + (sDynosWarpSpawnType == MARIO_SPAWN_DOOR_WARP) * 300.0f * sins(_Warp[6]);
            gMarioSpawnInfo->startPos[1] = _Warp[4];
            gMarioSpawnInfo->startPos[2] = _Warp[5] + (sDynosWarpSpawnType == MARIO_SPAWN_DOOR_WARP) * 300.0f * coss(_Warp[6]);
            gMarioSpawnInfo->startAngle[0] = 0;
            gMarioSpawnInfo->startAngle[1] = _Warp[6] + (gCurrLevelNum == LEVEL_CASTLE_GROUNDS && DynOS_Level_IsVanillaLevel(LEVEL_CASTLE_GROUNDS) ? 0x8000 : 0);
            gMarioSpawnInfo->startAngle[2] = 0;
            gMarioSpawnInfo->areaIndex = gCurrAreaIndex;
            init_mario();
            set_mario_initial_action(gMarioState, sDynosWarpSpawnType, 0);

            // Init transition
            if (gCurrentArea != NULL) {
                reset_camera(gCurrentArea->camera);
                init_camera(gCurrentArea->camera);
            }
            sDelayedWarpOp = WARP_OP_NONE;
            switch (sDynosWarpSpawnType) {
                case MARIO_SPAWN_UNKNOWN_03:           play_transition(WARP_TRANSITION_FADE_FROM_STAR,   0x10, 0x00, 0x00, 0x00); break;
                case MARIO_SPAWN_DOOR_WARP:            play_transition(WARP_TRANSITION_FADE_FROM_CIRCLE, 0x10, 0x00, 0x00, 0x00); break;
                case MARIO_SPAWN_TELEPORT:             play_transition(WARP_TRANSITION_FADE_FROM_COLOR,  0x14, 0xFF, 0xFF, 0xFF); break;
                case MARIO_SPAWN_SPIN_AIRBORNE:        play_transition(WARP_TRANSITION_FADE_FROM_COLOR,  0x1A, 0xFF, 0xFF, 0xFF); break;
                case MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE: play_transition(WARP_TRANSITION_FADE_FROM_CIRCLE, 0x10, 0x00, 0x00, 0x00); break;
                case MARIO_SPAWN_UNKNOWN_27:           play_transition(WARP_TRANSITION_FADE_FROM_COLOR,  0x10, 0x00, 0x00, 0x00); break;
                default:                               play_transition(WARP_TRANSITION_FADE_FROM_STAR,   0x10, 0x00, 0x00, 0x00); break;
            }

            // Set music
            if (sWarpDest.type != WARP_TYPE_SAME_AREA && sWarpDest.type != WARP_TYPE_NOT_WARPING) {
                if (gCurrentArea != NULL) {
                    set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
                }
                if (gMarioState->flags & MARIO_METAL_CAP)  play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_METAL_CAP));
                if (gMarioState->flags & MARIO_VANISH_CAP) play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
                if (gMarioState->flags & MARIO_WING_CAP)   play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
                if (gCurrLevelNum == LEVEL_BOWSER_1 ||
                    gCurrLevelNum == LEVEL_BOWSER_2 ||
                    gCurrLevelNum == LEVEL_BOWSER_3) {
                    sound_banks_enable(0, 0xFFFF); // Bowser levels sound fix
                }
            }

            // lua hooks
            smlua_call_event_hooks(HOOK_ON_WARP);

            // Reset values
            sDynosWarpTargetArea = -1;
            sDynosWarpLevelNum   = -1;
            sDynosWarpAreaNum    = -1;
            sDynosWarpActNum     = -1;
            sDynosWarpNodeNum    = -1;
        }
    }

    // Reset DDD settings to default
    if (gCurrCourseNum == COURSE_NONE) {
        gDDDBowsersSub = -1;
        gDDDPoles = -1;
    }

    return NULL;
}

static void DynOS_Warp_FindExitPosition(s16 &aPosX, s16 &aPosY, s16 &aPosZ, s16 aFYaw, f32 aDist) {
    for (f32 _Dist = aDist; _Dist > 0.f; _Dist -= 10.f) {
        f32 _PosX = (f32) aPosX + _Dist * sins(aFYaw + 0x8000);
        f32 _PosZ = (f32) aPosZ + _Dist * coss(aFYaw + 0x8000);
        for (f32 _DeltaY = 0.f; _DeltaY <= 5000.f; _DeltaY += 100.f) {
            f32 _PosY = (f32) aPosY + _DeltaY;
            struct Surface *_Floor;
            f32 _FloorY = find_floor(_PosX, _PosY, _PosZ, &_Floor);
            if (_Floor &&
                _Floor->type != SURFACE_WARP &&
                _Floor->type != SURFACE_BURNING &&
                _Floor->type != SURFACE_DEATH_PLANE &&
                _Floor->type != SURFACE_VERTICAL_WIND &&
                _Floor->type != SURFACE_DEEP_QUICKSAND &&
                _Floor->type != SURFACE_INSTANT_QUICKSAND &&
                _Floor->type != SURFACE_INSTANT_MOVING_QUICKSAND) {
                aPosX = _PosX;
                aPosY = _FloorY;
                aPosZ = _PosZ;
                return;
            }
        }
    }
}

static void *DynOS_Warp_UpdateExit(void *aCmd, bool aIsLevelInitDone) {
    static s32  sDynosExitTargetArea = -1;
    static s16 *sDynosExitTargetWarp = NULL;

    // Phase 0 - Wait for the Mario head transition to end
    if (sDynosExitTargetArea == -1 && DynOS_IsTransitionActive()) {
        return NULL;
    }

    // Phase 1 - Clear the previous level and set up the new level
    if (sDynosExitTargetArea == -1) {

        // Bowser levels
        if (sDynosExitLevelNum == LEVEL_BOWSER_1) sDynosExitLevelNum = LEVEL_BITDW;
        if (sDynosExitLevelNum == LEVEL_BOWSER_2) sDynosExitLevelNum = LEVEL_BITFS;
        if (sDynosExitLevelNum == LEVEL_BOWSER_3) sDynosExitLevelNum = LEVEL_BITS;

        // Exit warp to Castle warp
        // Uses the death warp, as it's the only warp that exists for every stage in the game
        s16 *_ExitWarp = DynOS_Level_GetWarpDeath(sDynosExitLevelNum, sDynosExitAreaNum);
        sDynosExitTargetWarp = DynOS_Level_GetWarp(_ExitWarp[7], _ExitWarp[8], _ExitWarp[9]);

        // Free everything from the current level
        clear_objects();
        clear_area_graph_nodes();
        clear_areas();

        // Reset Mario's state
        gMarioState->healCounter = 0;
        gMarioState->hurtCounter = 0;
        gMarioState->numCoins = 0;
        gMarioState->input = 0;
        gMarioState->controller->buttonPressed = 0;
        gHudDisplay.coins = 0;

        // Set up new level values
        gCurrLevelNum = _ExitWarp[7];
        gCurrCourseNum = DynOS_Level_GetCourse(gCurrLevelNum);
        gSavedCourseNum = gCurrCourseNum;
        gDialogCourseActNum = gCurrActNum;
        gCurrAreaIndex = _ExitWarp[8];
        sDynosExitTargetArea = _ExitWarp[8];

        // Set up new level script
        sWarpDest.type = 0;
        sWarpDest.levelNum = 0;
        sWarpDest.areaIdx = gCurrAreaIndex;
        sWarpDest.nodeId = 0;
        sWarpDest.arg = 0;
        return (void *) DynOS_Level_GetScript(gCurrLevelNum);

    } else {

        // Phase 2 - Set Mario spawn info after the MARIO_POS command
        if (*((u8 *) aCmd) == 0x2B) {
            gMarioSpawnInfo->areaIndex = sDynosExitTargetArea;
            gCurrAreaIndex = sDynosExitTargetArea;
        }

        // Phase 3 - End level initialization
        if (sDynosExitTargetWarp && aIsLevelInitDone && gMarioObjects[0]) {

            // Find target position
            // Because of course, every hack has its own warp distances and orientations...
            s16 _TargetPosX = sDynosExitTargetWarp[3];
            s16 _TargetPosY = sDynosExitTargetWarp[4];
            s16 _TargetPosZ = sDynosExitTargetWarp[5];
            s16 _TargetFYaw = sDynosExitTargetWarp[6];
            s16 _TargetDYaw = 0;
            f32 _TargetDist = 500.f;
            DynOS_Warp_FindExitPosition(_TargetPosX, _TargetPosY, _TargetPosZ, _TargetFYaw + _TargetDYaw, _TargetDist);

            // Init Mario
            gMarioSpawnInfo->startPos[0] = _TargetPosX;
            gMarioSpawnInfo->startPos[1] = _TargetPosY;
            gMarioSpawnInfo->startPos[2] = _TargetPosZ;
            gMarioSpawnInfo->startAngle[0] = 0;
            gMarioSpawnInfo->startAngle[1] = _TargetFYaw + _TargetDYaw;
            gMarioSpawnInfo->startAngle[2] = 0;
            gMarioSpawnInfo->areaIndex = gCurrAreaIndex;
            init_mario();
            set_mario_initial_action(gMarioState, MARIO_SPAWN_UNKNOWN_02, 0);

            // Init transition
            if (gCurrentArea != NULL) {
                reset_camera(gCurrentArea->camera);
                init_camera(gCurrentArea->camera);
            }
            sDelayedWarpOp = WARP_OP_NONE;
            play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0x00, 0x00, 0x00);
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP, gGlobalSoundSource);

            // Set music
            if (gCurrentArea != NULL) {
                set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
            }
            sDynosExitTargetWarp = NULL;

            // lua hooks
            smlua_call_event_hooks(HOOK_ON_WARP);
        }

        // Phase 4 - Unlock Mario as soon as the second transition is ended
        if (!sDynosExitTargetWarp && !DynOS_IsTransitionActive()) {
            sDynosExitTargetArea = -1;
            sDynosExitLevelNum   = -1;
            sDynosExitAreaNum    = -1;
        }
    }

    return NULL;
}

void *DynOS_Warp_Update(void *aCmd, bool aIsLevelInitDone) {

    // Level Exit
    if (sDynosExitLevelNum != -1 &&
        sDynosExitAreaNum != -1) {
        return DynOS_Warp_UpdateExit(aCmd, aIsLevelInitDone);
    }

    // Level Warp
    if (sDynosWarpLevelNum != -1 &&
        sDynosWarpAreaNum != -1 &&
        sDynosWarpActNum != -1) {
        return DynOS_Warp_UpdateWarp(aCmd, aIsLevelInitDone);
    }

    return NULL;
}
