#include <ultra64.h>
#include <stdbool.h>
#include <time.h>

#include "sm64.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "audio/external.h"
#include "level_update.h"
#include "game_init.h"
#include "level_update.h"
#include "main.h"
#include "engine/math_util.h"
#include "engine/graph_node.h"
#include "area.h"
#include "save_file.h"
#include "sound_init.h"
#include "mario.h"
#include "camera.h"
#include "object_list_processor.h"
#include "ingame_menu.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "save_file.h"
#include "hardcoded.h"
#include "debug_course.h"
#ifdef VERSION_EU
#include "memory.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#endif
#include "level_table.h"
#include "course_table.h"
#include "../../include/libc/stdlib.h"
#include "rumble_init.h"
#include "game/interaction.h"
#include "menu/intro_geo.h"

#include "pc/pc_main.h"
#include "pc/cliopts.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/djui/djui.h"
// used for getting gMainMenuSounds
#include "pc/djui/djui_panel_menu_options.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/mods/mods.h"
#include "pc/nametags.h"

#include "game/screen_transition.h"

#include "engine/level_script.h"

#define MENU_LEVEL_MIN 0
#define MENU_LEVEL_MAX 17

struct SavedWarpValues gReceiveWarp = { 0 };
extern s8 sReceivedLoadedActNum;
u8 gRejectInstantWarp = 0;
u16 gFanFareDebounce = 0;

s16 gChangeLevel = -1;
s16 gChangeLevelTransition = -1;
s16 gChangeActNum = -1;

s16 gDelayedInitSound = -1;

static bool sFirstCastleGroundsMenu = true;
bool gIsDemoActive = false;
static u16 gDemoCountdown = 0;
static int sDemoNumber = -1;
static bool sCancelNextActSelector = false;

// TODO: Make these ifdefs better
const char *credits01[] = { "1GAME DIRECTOR", "SHIGERU MIYAMOTO" };
const char *credits02[] = { "2ASSISTANT DIRECTORS", "YOSHIAKI KOIZUMI", "TAKASHI TEZUKA" };
const char *credits03[] = { "2SYSTEM PROGRAMMERS", "YASUNARI NISHIDA", "YOSHINORI TANIMOTO" };
const char *credits04[] = { "3PROGRAMMERS", "HAJIME YAJIMA", "DAIKI IWAMOTO", "TOSHIO IWAWAKI" };
#if defined(VERSION_JP) || defined(VERSION_SH)
const char *credits05[] = { "1CAMERA PROGRAMMER", "TAKUMI KAWAGOE" };
const char *credits06[] = { "1MARIO FACE PROGRAMMER", "GILES GODDARD" };
const char *credits07[] = { "2COURSE DIRECTORS", "YOICHI YAMADA", "YASUHISA YAMAMURA" };
const char *credits08[] = { "2COURSE DESIGNERS", "KENTA USUI", "NAOKI MORI" };
const char *credits09[] = { "3COURSE DESIGNERS", "YOSHIKI HARUHANA", "MAKOTO MIYANAGA",
                            "KATSUHIKO KANNO" };
const char *credits10[] = { "1SOUND COMPOSER", "KOJI KONDO" };

#ifdef VERSION_SH
const char *credits11[] = { "4SOUND EFFECTS", "SOUND PROGRAMMER", "YOJI INAGAKI", "HIDEAKI SHIMIZU" };
const char *credits12[] = { "23D ANIMATORS", "YOSHIAKI KOIZUMI", "SATORU TAKIZAWA" };
const char *credits13[] = { "1CG DESIGNER", "MASANAO ARIMOTO" };
const char *credits14[] = { "3TECHNICAL SUPPORT", "TAKAO SAWANO", "HIROHITO YOSHIMOTO", "HIROTO YADA" };
const char *credits15[] = { "1TECHNICAL SUPPORT", "SGI. 64PROJECT STAFF" };
const char *credits16[] = { "2PROGRESS MANAGEMENT", "KIMIYOSHI FUKUI", "KEIZO KATO" };
const char *credits17[] = { "4MARIO VOICE", "PEACH VOICE", "CHARLES MARTINET", "LESLIE SWAN" };
const char *credits18[] = { "3SPECIAL THANKS TO", "JYOHO KAIHATUBU", "ALL NINTENDO",
                            "MARIO CLUB STAFF" };
const char *credits19[] = { "1PRODUCER", "SHIGERU MIYAMOTO" };
const char *credits20[] = { "1EXECUTIVE PRODUCER", "HIROSHI YAMAUCHI" };
#else // VERSION_JP
const char *credits11[] = { "1SOUND EFFECTS", "YOJI INAGAKI" };
const char *credits12[] = { "1SOUND PROGRAMMER", "HIDEAKI SHIMIZU" };
const char *credits13[] = { "23D ANIMATORS", "YOSHIAKI KOIZUMI", "SATORU TAKIZAWA" };
const char *credits14[] = { "1CG DESIGNER", "MASANAO ARIMOTO" };
const char *credits15[] = { "3TECHNICAL SUPPORT", "TAKAO SAWANO", "HIROHITO YOSHIMOTO", "HIROTO YADA" };
const char *credits16[] = { "1TECHNICAL SUPPORT", "SGI. 64PROJECT STAFF" };
const char *credits17[] = { "2PROGRESS MANAGEMENT", "KIMIYOSHI FUKUI", "KEIZO KATO" };
const char *credits18[] = { "3SPECIAL THANKS TO", "JYOHO KAIHATUBU", "ALL NINTENDO",
                            "MARIO CLUB STAFF" };
const char *credits19[] = { "1PRODUCER", "SHIGERU MIYAMOTO" };
const char *credits20[] = { "1EXECUTIVE PRODUCER", "HIROSHI YAMAUCHI" };
#endif
#else // VERSION_US || VERSION_EU
const char *credits05[] = {
    "4CAMERA PROGRAMMER", "MARIO FACE PROGRAMMER", "TAKUMI KAWAGOE", "GILES GODDARD"
}; // US combines camera programmer and Mario face programmer
const char *credits06[] = { "2COURSE DIRECTORS", "YOICHI YAMADA", "YASUHISA YAMAMURA" };
const char *credits07[] = { "2COURSE DESIGNERS", "KENTA USUI", "NAOKI MORI" };
const char *credits08[] = { "3COURSE DESIGNERS", "YOSHIKI HARUHANA", "MAKOTO MIYANAGA",
                            "KATSUHIKO KANNO" };
#ifdef VERSION_US
const char *credits09[] = { "1SOUND COMPOSER", "KOJI KONDO" };
const char *credits10[] = { "4SOUND EFFECTS", "SOUND PROGRAMMER", "YOJI INAGAKI",
                            "HIDEAKI SHIMIZU" }; // as well as sound effects and sound programmer
const char *credits11[] = { "23-D ANIMATORS", "YOSHIAKI KOIZUMI", "SATORU TAKIZAWA" };
const char *credits12[] = { "1ADDITIONAL GRAPHICS", "MASANAO ARIMOTO" };
const char *credits13[] = { "3TECHNICAL SUPPORT", "TAKAO SAWANO", "HIROHITO YOSHIMOTO", "HIROTO YADA" };
const char *credits14[] = { "1TECHNICAL SUPPORT", "SGI N64 PROJECT STAFF" };
const char *credits15[] = { "2PROGRESS MANAGEMENT", "KIMIYOSHI FUKUI", "KEIZO KATO" };
const char *credits16[] = { "5SCREEN TEXT WRITER", "TRANSLATION", "LESLIE SWAN", "MINA AKINO",
                            "HIRO YAMADA" }; // ...in order to make room for these 2 new lines
#else // VERSION_EU
const char *credits09[] = { "7SOUND COMPOSER", "SOUND EFFECTS", "SOUND PROGRAMMER", "KOJI KONDO",
                            "YOJI INAGAKI", "HIDEAKI SHIMIZU" };
const char *credits10[] = { "63-D ANIMATORS", "ADDITIONAL GRAPHICS", "YOSHIAKI KOIZUMI", "SATORU TAKIZAWA",
                            "MASANAO ARIMOTO" };
const char *credits11[] = { "3TECHNICAL SUPPORT", "TAKAO SAWANO", "HIROHITO YOSHIMOTO", "HIROTO YADA" };
const char *credits12[] = { "1TECHNICAL SUPPORT", "SGI N64 PROJECT STAFF" };
const char *credits13[] = { "2PROGRESS MANAGEMENT", "KIMIYOSHI FUKUI", "KEIZO KATO" };
const char *credits14[] = { "5SCREEN TEXT WRITER", "ENGLISH TRANSLATION", "LESLIE SWAN", "MINA AKINO",
                            "HIRO YAMADA" };
const char *credits15[] = { "4SCREEN TEXT WRITER", "FRENCH TRANSLATION", "JULIEN BARDAKOFF",
                            "KENJI HARAGUCHI" };
const char *credits16[] = { "4SCREEN TEXT WRITER", "GERMAN TRANSLATION", "THOMAS GOERG",
                            "THOMAS SPINDLER" };
#endif
const char *credits17[] = { "4MARIO VOICE", "PEACH VOICE", "CHARLES MARTINET", "LESLIE SWAN" };
const char *credits18[] = { "3SPECIAL THANKS TO", "EAD STAFF", "ALL NINTENDO PERSONNEL",
#ifdef VERSION_US
                           "MARIO CLUB STAFF" };
#else // VERSION_EU
                           "SUPER MARIO CLUB STAFF" };
#endif
const char *credits19[] = { "1PRODUCER", "SHIGERU MIYAMOTO" };
const char *credits20[] = { "1EXECUTIVE PRODUCER", "HIROSHI YAMAUCHI" };
#endif


struct CreditsEntry sCreditsSequence[] = {
    { LEVEL_CASTLE_GROUNDS, 1, 1, -128, { 0, 8000, 0 }, NULL },
    { LEVEL_BOB, 1, 1, 117, { 713, 3918, -3889 }, credits01 },
    { LEVEL_WF, 1, 50, 46, { 347, 5376, 326 }, credits02 },
    { LEVEL_JRB, 1, 18, 22, { 3800, -4840, 2727 }, credits03 },
    { LEVEL_CCM, 2, 34, 25, { -5464, 6656, -6575 }, credits04 },
    { LEVEL_BBH, 1, 1, 60, { 257, 1922, 2580 }, credits05 },
    { LEVEL_HMC, 1, -15, 123, { -6469, 1616, -6054 }, credits06 },
    { LEVEL_THI, 3, 17, -32, { 508, 1024, 1942 }, credits07 },
    { LEVEL_LLL, 2, 33, 124, { -73, 82, -1467 }, credits08 },
    { LEVEL_SSL, 1, 65, 98, { -5906, 1024, -2576 }, credits09 },
    { LEVEL_DDD, 1, 50, 47, { -4884, -4607, -272 }, credits10 },
    { LEVEL_SL, 1, 17, -34, { 1925, 3328, 563 }, credits11 },
    { LEVEL_WDW, 1, 33, 105, { -537, 1850, 1818 }, credits12 },
    { LEVEL_TTM, 1, 2, -33, { 2613, 313, 1074 }, credits13 },
    { LEVEL_THI, 1, 51, 54, { -2609, 512, 856 }, credits14 },
    { LEVEL_TTC, 1, 17, -72, { -1304, -71, -967 }, credits15 },
    { LEVEL_RR, 1, 33, 64, { 1565, 1024, -148 }, credits16 },
    { LEVEL_SA, 1, 1, 24, { -1050, -1330, -1559 }, credits17 },
    { LEVEL_COTMC, 1, 49, -16, { -254, 415, -6045 }, credits18 },
    { LEVEL_DDD, 2, -111, -64, { 3948, 1185, -104 }, credits19 },
    { LEVEL_CCM, 1, 33, 31, { 3169, -4607, 5240 }, credits20 },
    { LEVEL_CASTLE_GROUNDS, 1, 1, -128, { 0, 906, -1200 }, NULL },
    { LEVEL_NONE, 0, 1, 0, { 0, 0, 0 }, NULL },
};

struct MarioState gMarioStates[MAX_PLAYERS] = { 0 };
struct HudDisplay gHudDisplay;
s16 sCurrPlayMode;
u16 D_80339ECA;
s16 sTransitionTimer;
void (*sTransitionUpdate)(s16 *);
struct WarpDest sWarpDest;
s16 D_80339EE0;
s16 sDelayedWarpOp;
s16 sDelayedWarpTimer;
s16 sSourceWarpNodeId;
s32 sDelayedWarpArg;
#if defined(VERSION_EU) || defined(VERSION_SH)
s16 unusedEULevelUpdateBss1;
#endif
s8 sTimerRunning;
bool gNeverEnteredCastle;

struct MarioState *gMarioState = &gMarioStates[0];
u8 unused1[4] = { 0 };
s8 sWarpCheckpointActive = FALSE;
u8 unused3[4];
u8 unused4[2];

u32 gControlTimerStartNat = 0;
u32 gControlTimerStopNat = 0;

u8 level_control_timer_running(void) {
    return sTimerRunning;
}

u16 level_control_timer(s32 timerOp) {
    switch (timerOp) {
        case TIMER_CONTROL_SHOW:
            gHudDisplay.flags |= HUD_DISPLAY_FLAG_TIMER;
            sTimerRunning = FALSE;
            gHudDisplay.timer = 0;
            gControlTimerStartNat = 0;
            gControlTimerStopNat = 0;
            break;

        case TIMER_CONTROL_START:
            if (!sTimerRunning) {
                sTimerRunning = TRUE;
                gControlTimerStartNat = gNetworkAreaTimer;
            }
            break;

        case TIMER_CONTROL_STOP:
            if (sTimerRunning) {
                sTimerRunning = FALSE;
                gControlTimerStopNat = gNetworkAreaTimer;
            }
            break;

        case TIMER_CONTROL_HIDE:
            gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_TIMER;
            sTimerRunning = FALSE;
            gHudDisplay.timer = 0;
            gControlTimerStartNat = 0;
            gControlTimerStopNat = 0;
            break;
    }

    return gHudDisplay.timer;
}

u32 pressed_pause(void) {
    if (gServerSettings.pauseAnywhere) {
        if (get_dialog_id() < 0 && sCurrPlayMode == PLAY_MODE_NORMAL && sDelayedWarpOp == WARP_OP_NONE) {
            return gPlayer1Controller->buttonPressed & START_BUTTON;
        }
    } else {
        u32 dialogActive = get_dialog_id() >= 0;
        u32 intangible = (gMarioState->action & ACT_FLAG_INTANGIBLE) != 0;
        u32 firstPerson = gMarioState->action == ACT_FIRST_PERSON;

        if (!intangible && !dialogActive && !firstPerson && !gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE) {
            return (gPlayer1Controller->buttonPressed & START_BUTTON);
        }
    }

    return FALSE;
}

void set_play_mode(s16 playMode) {
    sCurrPlayMode = playMode;
    D_80339ECA = 0;
}

void warp_special(s32 arg) {
    if (arg != 0 && arg != SPECIAL_WARP_CAKE && arg != SPECIAL_WARP_GODDARD && arg != SPECIAL_WARP_GODDARD_GAMEOVER && arg != SPECIAL_WARP_TITLE && arg != SPECIAL_WARP_LEVEL_SELECT) {
        LOG_ERROR("Invalid parameter value for warp_special: Expected 0, SPECIAL_WARP_CAKE, SPECIAL_WARP_GODDARD, SPECIAL_WARP_GODDARD_GAMEOVER, SPECIAL_WARP_TITLE, or SPECIAL_WARP_LEVEL_SELECT");
        return;
    }

    sCurrPlayMode = PLAY_MODE_CHANGE_LEVEL;
    D_80339ECA = 0;
    D_80339EE0 = arg;
}

void fade_into_special_warp(u32 arg, u32 color) {
    if (color != 0) {
        color = 0xFF;
    }

    fadeout_music(190);
    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x10, color, color, color);
    level_set_transition(16, NULL);

    warp_special(arg);
}

void stub_level_update_1(void) {
}

void load_level_init_text(u32 arg) {
    s32 gotAchievement;
    u32 dialogID = gCurrentArea->dialog[arg];

    if (dialogID == gBehaviorValues.dialogs.VanishCourseDialog) {
        gotAchievement = save_file_get_flags() & SAVE_FLAG_HAVE_VANISH_CAP;
    } else if (dialogID == gBehaviorValues.dialogs.MetalCourseDialog) {
        gotAchievement = save_file_get_flags() & SAVE_FLAG_HAVE_METAL_CAP;
    } else if (dialogID == gBehaviorValues.dialogs.WingCourseDialog) {
        gotAchievement = save_file_get_flags() & SAVE_FLAG_HAVE_WING_CAP;
    } else if (dialogID == 255) {
        gotAchievement = TRUE;
    } else {
        gotAchievement = save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1);
    }

    if (!gotAchievement) {
        //level_set_transition(-1, NULL);
        create_dialog_box(dialogID);
    }
}

void init_door_warp(struct SpawnInfo *spawnInfo, u32 arg1) {
    if (arg1 & 0x00000002) {
        spawnInfo->startAngle[1] += 0x8000;
    }

    spawnInfo->startPos[0] += 300.0f * sins(spawnInfo->startAngle[1]);
    spawnInfo->startPos[2] += 300.0f * coss(spawnInfo->startAngle[1]);
}

void set_mario_initial_cap_powerup(struct MarioState *m) {
    u32 capCourseIndex = gCurrCourseNum - COURSE_CAP_COURSES;

    switch (capCourseIndex) {
        case COURSE_COTMC - COURSE_CAP_COURSES:
            m->flags |= MARIO_METAL_CAP | MARIO_CAP_ON_HEAD;
            m->capTimer = gLevelValues.metalCapDurationCotmc;
            break;

        case COURSE_TOTWC - COURSE_CAP_COURSES:
            m->flags |= MARIO_WING_CAP | MARIO_CAP_ON_HEAD;
            m->capTimer = gLevelValues.wingCapDurationTotwc;
            break;

        case COURSE_VCUTM - COURSE_CAP_COURSES:
            m->flags |= MARIO_VANISH_CAP | MARIO_CAP_ON_HEAD;
            m->capTimer = gLevelValues.vanishCapDurationVcutm;
            break;
    }
}

void set_mario_initial_action(struct MarioState *m, u32 spawnType, u32 actionArg) {
    switch (spawnType) {
        case MARIO_SPAWN_DOOR_WARP:
            set_mario_action(m, ACT_WARP_DOOR_SPAWN, actionArg);
            break;
        case MARIO_SPAWN_IDLE:
            set_mario_action(m, ACT_IDLE, 0);
            break;
        case MARIO_SPAWN_PIPE:
            set_mario_action(m, ACT_EMERGE_FROM_PIPE, 0);
            break;
        case MARIO_SPAWN_TELEPORT:
            set_mario_action(m, ACT_TELEPORT_FADE_IN, 0);
            break;
        case MARIO_SPAWN_INSTANT_ACTIVE:
            set_mario_action(m, ACT_IDLE, 0);
            break;
        case MARIO_SPAWN_AIRBORNE:
            set_mario_action(m, ACT_SPAWN_NO_SPIN_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_HARD_AIR_KNOCKBACK:
            set_mario_action(m, ACT_HARD_BACKWARD_AIR_KB, 0);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE:
            set_mario_action(m, ACT_SPAWN_SPIN_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_DEATH:
            set_mario_action(m, ACT_FALLING_DEATH_EXIT, 0);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE:
            set_mario_action(m, ACT_SPAWN_SPIN_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_FLYING:
            set_mario_action(m, ACT_FLYING, 2);
            break;
        case MARIO_SPAWN_SWIMMING:
            set_mario_action(m, ACT_WATER_IDLE, 1);
            break;
        case MARIO_SPAWN_PAINTING_STAR_COLLECT:
            set_mario_action(m, ACT_EXIT_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_PAINTING_DEATH:
            set_mario_action(m, ACT_DEATH_EXIT, 0);
            break;
        case MARIO_SPAWN_AIRBORNE_STAR_COLLECT:
            set_mario_action(m, ACT_FALLING_EXIT_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_AIRBORNE_DEATH:
            set_mario_action(m, ACT_UNUSED_DEATH_EXIT, 0);
            break;
        case MARIO_SPAWN_LAUNCH_STAR_COLLECT:
            set_mario_action(m, ACT_SPECIAL_EXIT_AIRBORNE, 0);
            break;
        case MARIO_SPAWN_LAUNCH_DEATH:
            set_mario_action(m, ACT_SPECIAL_DEATH_EXIT, 0);
            break;
    }

    set_mario_initial_cap_powerup(m);
}

void init_mario_after_warp(void) {
    struct ObjectWarpNode *spawnNode = area_get_warp_node(sWarpDest.nodeId);
    if (spawnNode == NULL) { LOG_ERROR("Failed to find spawn node: %u", sWarpDest.nodeId); }
    if (spawnNode == NULL || spawnNode->object == NULL) { spawnNode = area_get_warp_node(0xFA); }
    if (spawnNode == NULL || spawnNode->object == NULL) { spawnNode = area_get_warp_node(0x00); }
    if (spawnNode == NULL || spawnNode->object == NULL) { spawnNode = area_get_any_warp_node(); }
    if (spawnNode == NULL || spawnNode->object == NULL) { return; }

    u32 marioSpawnType = get_mario_spawn_type(spawnNode->object);

    if (gMarioState && gMarioState->action != ACT_UNINITIALIZED) {
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            gPlayerSpawnInfos[i].startPos[0] = (s16) spawnNode->object->oPosX;
            gPlayerSpawnInfos[i].startPos[1] = (s16) spawnNode->object->oPosY;
            gPlayerSpawnInfos[i].startPos[2] = (s16) spawnNode->object->oPosZ;

            gPlayerSpawnInfos[i].startAngle[0] = 0;
            gPlayerSpawnInfos[i].startAngle[1] = spawnNode->object->oMoveAngleYaw;
            gPlayerSpawnInfos[i].startAngle[2] = 0;

            if (marioSpawnType == MARIO_SPAWN_DOOR_WARP) {
                init_door_warp(&gPlayerSpawnInfos[i], sWarpDest.arg);
            }

            if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL || sWarpDest.type == WARP_TYPE_CHANGE_AREA) {
                gPlayerSpawnInfos[i].areaIndex = sWarpDest.areaIdx;
                if (i == 0) { load_mario_area(); }
            }

            // enforce bubble on area change
            if (gServerSettings.bubbleDeath) {
                if (i == 0 && gMarioStates[i].numLives == -1) {
                    mario_set_bubbled(&gMarioStates[i]);
                    gMarioStates[i].health = 0xFF;
                }
            }
        }

        init_mario();
        set_mario_initial_action(gMarioState, marioSpawnType, sWarpDest.arg);

        // remove offset from local mario during warps
        if (sWarpDest.type == WARP_TYPE_SAME_AREA && marioSpawnType != MARIO_SPAWN_DOOR_WARP) {
            gMarioState[0].pos[0] = (s16)spawnNode->object->oPosX;
            gMarioState[0].pos[1] = (s16)spawnNode->object->oPosY;
            gMarioState[0].pos[2] = (s16)spawnNode->object->oPosZ;
            if (gMarioState[0].marioObj != NULL) {
                gMarioState[0].marioObj->oPosX = spawnNode->object->oPosX;
                gMarioState[0].marioObj->oPosY = spawnNode->object->oPosY;
                gMarioState[0].marioObj->oPosZ = spawnNode->object->oPosZ;
            }
        }

        gMarioState->interactObj = spawnNode->object;
        gMarioState->usedObj = spawnNode->object;
    }

    if (gCurrentArea) {
        reset_camera(gCurrentArea->camera);
    }
    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;

    switch (marioSpawnType) {
        case MARIO_SPAWN_PIPE:
            play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0x00, 0x00, 0x00);
            break;
        case MARIO_SPAWN_DOOR_WARP:
            play_transition(WARP_TRANSITION_FADE_FROM_CIRCLE, 0x10, 0x00, 0x00, 0x00);
            break;
        case MARIO_SPAWN_TELEPORT:
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x14, 0xFF, 0xFF, 0xFF);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE:
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x1A, 0xFF, 0xFF, 0xFF);
            break;
        case MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE:
            play_transition(WARP_TRANSITION_FADE_FROM_CIRCLE, 0x10, 0x00, 0x00, 0x00);
            break;
        case MARIO_SPAWN_FADE_FROM_BLACK:
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x10, 0x00, 0x00, 0x00);
            break;
        default:
            play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0x00, 0x00, 0x00);
            break;
    }

    if (gCurrDemoInput == NULL && gMarioState) {
        if (gCurrentArea) {
            set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
        }

        if (gMarioState->flags & MARIO_METAL_CAP) {
            play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_METAL_CAP));
        }

        if (gMarioState->flags & (MARIO_VANISH_CAP | MARIO_WING_CAP)) {
            play_cap_music(SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP));
        }

#ifndef VERSION_JP
        if (gCurrLevelNum == LEVEL_BOB
            && get_current_background_music() != SEQUENCE_ARGS(4, SEQ_LEVEL_SLIDE)
            && sTimerRunning) {
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_LEVEL_SLIDE), 0);
        }
#endif

        if (sWarpDest.levelNum == LEVEL_CASTLE && sWarpDest.areaIdx == 1
#ifndef VERSION_JP
            && (sWarpDest.nodeId == 31 || sWarpDest.nodeId == 32)
#else
            && sWarpDest.nodeId == 31
#endif
        )
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP, gGlobalSoundSource);
#ifndef VERSION_JP
        if (sWarpDest.levelNum == LEVEL_CASTLE_GROUNDS && sWarpDest.areaIdx == 1
            && (sWarpDest.nodeId == 7 || sWarpDest.nodeId == 10 || sWarpDest.nodeId == 20
                || sWarpDest.nodeId == 30)) {
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP, gGlobalSoundSource);
        }
#endif
    }

    if (gNetworkPlayerLocal != NULL) {
        network_player_update_course_level(gNetworkPlayerLocal, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
    }

    if (gMarioState && gMarioState->health <= 0x110) {
        gMarioState->health = 0x880;
    }

    if (gMarioState) {
        gMarioState->skipWarpInteractionsTimer = 30;
    }

    smlua_call_event_hooks(HOOK_ON_WARP);
}

// used for warps inside one level
void warp_area(void) {
    if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
        if (sWarpDest.type == WARP_TYPE_CHANGE_AREA) {
            level_control_timer(TIMER_CONTROL_HIDE);
            unload_mario_area();
            load_area(sWarpDest.areaIdx);
        }

        init_mario_after_warp();
    }
}

// used for warps between levels
void warp_level(void) {
    gCurrLevelNum = sWarpDest.levelNum;

    level_control_timer(TIMER_CONTROL_HIDE);

    load_area(sWarpDest.areaIdx);
    init_mario_after_warp();
}

void warp_credits(void) {
    s32 marioAction;

    switch (sWarpDest.nodeId) {
        case WARP_NODE_CREDITS_START:
            marioAction = ACT_END_PEACH_CUTSCENE;
            break;

        case WARP_NODE_CREDITS_NEXT:
            marioAction = ACT_CREDITS_CUTSCENE;
            break;

        case WARP_NODE_CREDITS_END:
            marioAction = ACT_END_WAVING_CUTSCENE;
            break;
    }

    gCurrLevelNum = sWarpDest.levelNum;

    load_area(sWarpDest.areaIdx);

    if (gCurrCreditsEntry == NULL) {
        gCurrCreditsEntry = &sCreditsSequence[0];
    }

    if ((gCurrCreditsEntry != NULL) && (gCurrCreditsEntry->levelNum == gLevelValues.skipCreditsAt)) {
        lvl_skip_credits();
        return;
    }

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        vec3s_set(gPlayerSpawnInfos[i].startPos, gCurrCreditsEntry->marioPos[0],
                  gCurrCreditsEntry->marioPos[1], gCurrCreditsEntry->marioPos[2]);

        vec3s_set(gPlayerSpawnInfos[i].startAngle, 0, 0x100 * gCurrCreditsEntry->marioAngle, 0);

        gPlayerSpawnInfos[i].areaIndex = sWarpDest.areaIdx;
    }

    load_mario_area();
    init_mario();

    set_mario_action(gMarioState, marioAction, 0);

    if (gCurrentArea) {
        reset_camera(gCurrentArea->camera);
    }

    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;

    play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x14, 0x00, 0x00, 0x00);

    if ((gCurrCreditsEntry == NULL || gCurrCreditsEntry == sCreditsSequence) && !gDjuiInMainMenu) {
        if (gCurrentArea) {
            set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
        }
    }
}

struct InstantWarp *get_instant_warp(u8 index) {
    if (index >= 4) { return NULL; }
    if (!gCurrentArea) { return NULL; }
    if (gCurrentArea->instantWarps == NULL) { return NULL; }

    return &gCurrentArea->instantWarps[index];
}

void check_instant_warp(void) {
    if (!gCurrentArea) { return; }
    s16 cameraAngle;
    struct Surface *floor;

    if (gRejectInstantWarp > 0) {
        gRejectInstantWarp--;
    }

    if (gCurrLevelNum == LEVEL_CASTLE
        && save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= gLevelValues.infiniteStairsRequirement) {
        return;
    }

    if ((floor = gMarioStates[0].floor) != NULL) {
        s32 index = floor->type - SURFACE_INSTANT_WARP_1B;
        if (index >= INSTANT_WARP_INDEX_START && index < INSTANT_WARP_INDEX_STOP && gCurrentArea->instantWarps != NULL) {
            struct InstantWarp *warp = &gCurrentArea->instantWarps[index];
            if (warp->id != 0) {
                if (gRejectInstantWarp > 0) {
                    vec3f_copy(gMarioStates[0].pos, gMarioStates[0].nonInstantWarpPos);
                    //vec3f_mul(gMarioStates[0].vel, -0.8f);
                    return;
                }

                mario_drop_held_object(&gMarioStates[0]);
                u8 changeOfArea = (gCurrAreaIndex != warp->area);
                gMarioStates[0].pos[0] += warp->displacement[0];
                gMarioStates[0].pos[1] += warp->displacement[1];
                gMarioStates[0].pos[2] += warp->displacement[2];
                vec3f_copy(gMarioStates[0].nonInstantWarpPos, gMarioStates[0].pos);

                if (changeOfArea) {
                    for (s32 i = 0; i < MAX_PLAYERS; i++) {
                        gMarioStates[i].marioObj->oIntangibleTimer = 30;
                    }
                }

                gMarioStates[0].marioObj->oPosX = gMarioStates[0].pos[0];
                gMarioStates[0].marioObj->oPosY = gMarioStates[0].pos[1];
                gMarioStates[0].marioObj->oPosZ = gMarioStates[0].pos[2];

                cameraAngle = gMarioStates[0].area->camera->yaw;
                change_area(warp->area);

                for (s32 i = 0; i < MAX_PLAYERS; i++) {
                    gMarioStates[i].area = gCurrentArea;
                }

                warp_camera(warp->displacement[0], warp->displacement[1], warp->displacement[2]);
                skip_camera_interpolation();
                gMarioStates[0].area->camera->yaw = cameraAngle;

                return;
            }
        }
    }
    vec3f_copy(gMarioStates[0].nonInstantWarpPos, gMarioStates[0].pos);
}

s16 music_changed_through_warp(s16 arg) {
    if (arg == 0) {
        return false;
    }

    struct ObjectWarpNode *warpNode = area_get_warp_node(arg);
    if (!warpNode) { return FALSE; }
    s16 levelNum = warpNode->node.destLevel & 0x7F;

#if BUGFIX_KOOPA_RACE_MUSIC

    s16 destArea = warpNode->node.destArea;
    s16 val4 = TRUE;
    s16 sp2C;

    if (levelNum == LEVEL_BOB && levelNum == gCurrLevelNum && destArea == gCurrAreaIndex) {
        sp2C = get_current_background_music();
        if (sp2C == SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP | SEQ_VARIATION)
            || sp2C == SEQUENCE_ARGS(4, SEQ_EVENT_POWERUP)) {
            val4 = 0;
        }
    } else {
        u16 val8 = gAreas[destArea].musicParam;
        u16 val6 = gAreas[destArea].musicParam2;

        val4 = levelNum == gCurrLevelNum && val8 == gCurrentArea->musicParam
               && val6 == gCurrentArea->musicParam2;

        if (get_current_background_music() != val6) {
            val4 = FALSE;
        }
    }
    return val4;

#else

    u16 val8 = gAreas[warpNode->node.destArea].musicParam;
    u16 val6 = gAreas[warpNode->node.destArea].musicParam2;

    s16 val4 = levelNum == gCurrLevelNum && val8 == gCurrentArea->musicParam
               && val6 == gCurrentArea->musicParam2;

    if (get_current_background_music() != val6) {
        val4 = FALSE;
    }
    return val4;

#endif
}

/**
 * Set the current warp type and destination level/area/node.
 */
void initiate_warp(s16 destLevel, s16 destArea, s16 destWarpNode, s32 arg) {
    if (destWarpNode >= WARP_NODE_CREDITS_MIN) {
        sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    } else if (destLevel != gCurrLevelNum) {
        sWarpDest.type = WARP_TYPE_CHANGE_LEVEL;
    } else if (destArea != gCurrentArea->index) {
        sWarpDest.type = WARP_TYPE_CHANGE_AREA;
    } else {
        sWarpDest.type = WARP_TYPE_SAME_AREA;
    }

    sWarpDest.levelNum = destLevel;
    sWarpDest.areaIdx = destArea;
    sWarpDest.nodeId = destWarpNode;
    sWarpDest.arg = arg;
}

/**
 * Check if Mario is above and close to a painting warp floor, and return the
 * corresponding warp node.
 */
struct WarpNode *get_painting_warp_node(void) {
    if (!gMarioState || !gMarioState->floor || !gCurrentArea || !gCurrentArea->paintingWarpNodes) { return NULL; }

    struct WarpNode *warpNode = NULL;
    s32 paintingIndex = gMarioState->floor->type - SURFACE_PAINTING_WARP_D3;

    if (paintingIndex >= PAINTING_WARP_INDEX_START && paintingIndex < PAINTING_WARP_INDEX_END) {
        if (paintingIndex < PAINTING_WARP_INDEX_FA
            || gMarioState->pos[1] - gMarioState->floorHeight < 80.0f) {
            warpNode = &gCurrentArea->paintingWarpNodes[paintingIndex];
        }
    }

    return warpNode;
}

static void initiate_painting_warp_node(struct WarpNode *pWarpNode) {
    struct WarpNode warpNode = *pWarpNode;

    if (!(warpNode.destLevel & 0x80)) {
        sWarpCheckpointActive = check_warp_checkpoint(&warpNode);
    }

    initiate_warp(warpNode.destLevel & 0x7F, warpNode.destArea, warpNode.destNode, 0);
    check_if_should_set_warp_checkpoint(&warpNode);

    extern s16 gMenuMode;
    if (gMenuMode == -1) {
        play_transition_after_delay(WARP_TRANSITION_FADE_INTO_COLOR, 30, 255, 255, 255, 45);
    }
    level_set_transition(74, basic_update);

    play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
    fadeout_music(398);
    queue_rumble_data(80, 70);
    func_sh_8024C89C(1);
}

/**
 * Check is Mario has entered a painting, and if so, initiate a warp.
 */
void initiate_painting_warp(s16 paintingIndex) {
    if (gCurrentArea && gCurrentArea->paintingWarpNodes && gMarioState && gMarioState->floor && paintingIndex >= -1 && paintingIndex < MAX_PAINTING_WARP_NODES) {
        struct WarpNode *pWarpNode = paintingIndex == -1 ? get_painting_warp_node() : &gCurrentArea->paintingWarpNodes[paintingIndex];

        if (pWarpNode != NULL) {
            if (gMarioState->action & ACT_FLAG_INTANGIBLE) {
                play_painting_eject_sound();
            } else if (pWarpNode->id != 0) {
                initiate_painting_warp_node(pWarpNode);

                set_mario_action(gMarioState, ACT_DISAPPEARED, 0);
                gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;

                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                fadeout_music(398);
#ifdef VERSION_SH
                queue_rumble_data(80, 70);
                func_sh_8024C89C(1);
#endif
            }
        }
    }
}


void verify_warp(struct MarioState *m, bool killMario) {
    if (area_get_warp_node(sSourceWarpNodeId) != NULL) { return; }

    if (area_get_warp_node(WARP_NODE_DEATH) == NULL) {
        dynos_warp_to_start_level();
        return;
    }

    if (!killMario) {
        sSourceWarpNodeId = WARP_NODE_DEATH;
        return;
    }

    m->numLives--;
    if (m->numLives < 0) {
        sDelayedWarpOp = WARP_OP_GAME_OVER;
    } else {
        sSourceWarpNodeId = WARP_NODE_DEATH;
    }
}


/**
 * If there is not already a delayed warp, schedule one. The source node is
 * based on the warp operation and sometimes Mario's used object.
 * Return the time left until the delayed warp is initiated.
 */
s16 level_trigger_warp(struct MarioState *m, s32 warpOp) {
    // only allow for local player
    if (m != &gMarioStates[0]) { return 0; }

    s32 val04 = TRUE;

    if (sDelayedWarpOp == WARP_OP_NONE) {
        m->invincTimer = -1;
        sDelayedWarpArg = 0;
        sDelayedWarpOp = warpOp;

        switch (warpOp) {
            case WARP_OP_DEMO_NEXT:
            case WARP_OP_DEMO_END: sDelayedWarpTimer = 20; // Must be one line to match on -O2
                val04 = FALSE;
                if (!gDjuiInMainMenu) {
                    sSourceWarpNodeId = WARP_NODE_F0;
                    gSavedCourseNum = COURSE_NONE;
                    play_transition(WARP_TRANSITION_FADE_INTO_STAR, 0x14, 0x00, 0x00, 0x00);
                } else {
                    stop_demo(NULL);
                }
                break;

            case WARP_OP_CREDITS_END:
                sDelayedWarpTimer = 60;
                sSourceWarpNodeId = WARP_NODE_F0;
                verify_warp(m, false);
                val04 = FALSE;
                gSavedCourseNum = COURSE_NONE;
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x3C, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_STAR_EXIT:
                sDelayedWarpTimer = 32;
                sSourceWarpNodeId = WARP_NODE_F0;
                verify_warp(m, false);
                gSavedCourseNum = COURSE_NONE;
                play_transition(WARP_TRANSITION_FADE_INTO_MARIO, 0x20, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_DEATH:
                m->numLives--;
                if (m->numLives <= -1) {
                    sDelayedWarpOp = WARP_OP_GAME_OVER;
                }
                sDelayedWarpTimer = 48;
                sSourceWarpNodeId = WARP_NODE_DEATH;
                play_transition(WARP_TRANSITION_FADE_INTO_BOWSER, 0x30, 0x00, 0x00, 0x00);
                play_sound(SOUND_MENU_BOWSER_LAUGH, gGlobalSoundSource);
                break;

            case WARP_OP_EXIT:
                sSourceWarpNodeId = WARP_NODE_DEATH;
                sDelayedWarpTimer = 20;
                play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, 0x14, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_WARP_FLOOR:
                sSourceWarpNodeId = WARP_NODE_WARP_FLOOR;
                verify_warp(m, true);
                sDelayedWarpTimer = 20;
                play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, 0x14, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_LOOK_UP: // enter totwc
                sDelayedWarpTimer = 30;
                sSourceWarpNodeId = WARP_NODE_F2;
                verify_warp(m, false);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x1E, 0xFF, 0xFF, 0xFF);
#ifndef VERSION_JP
                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
#endif
                break;

            case WARP_OP_SPIN_SHRINK: // bbh enter
                if (m->usedObj == NULL) { break; }
                sDelayedWarpTimer = 30;
                sSourceWarpNodeId = (m->usedObj->oBehParams & 0x00FF0000) >> 16;
                verify_warp(m, false);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x1E, 0xFF, 0xFF, 0xFF);
                break;

            case WARP_OP_TELEPORT:
                if (m->usedObj == NULL) { break; }
                sDelayedWarpTimer = 20;
                sSourceWarpNodeId = (m->usedObj->oBehParams & 0x00FF0000) >> 16;
                verify_warp(m, false);
                val04 = !music_changed_through_warp(sSourceWarpNodeId);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0xFF, 0xFF, 0xFF);
                break;

            case WARP_OP_WARP_DOOR:
                if (m->usedObj == NULL) { break; }
                sDelayedWarpTimer = 20;
                sDelayedWarpArg = m->actionArg;
                sSourceWarpNodeId = (m->usedObj->oBehParams & 0x00FF0000) >> 16;
                verify_warp(m, false);
                val04 = !music_changed_through_warp(sSourceWarpNodeId);
                play_transition(WARP_TRANSITION_FADE_INTO_CIRCLE, 0x14, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_WARP_OBJECT:
                if (m->usedObj == NULL) { break; }
                sDelayedWarpTimer = 20;
                sSourceWarpNodeId = (m->usedObj->oBehParams & 0x00FF0000) >> 16;
                verify_warp(m, false);
                val04 = !music_changed_through_warp(sSourceWarpNodeId);
                play_transition(WARP_TRANSITION_FADE_INTO_STAR, 0x14, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_CREDITS_START:
                sDelayedWarpTimer = 30;
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x1E, 0x00, 0x00, 0x00);
                break;

            case WARP_OP_CREDITS_NEXT:
                if (gCurrCreditsEntry == NULL) { gCurrCreditsEntry = &sCreditsSequence[0]; }
                if (gCurrCreditsEntry == &sCreditsSequence[0]) {
                    sDelayedWarpTimer = gDjuiInMainMenu ? 1 : 60;
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x3C, 0x00, 0x00, 0x00);
                } else {
                    sDelayedWarpTimer = 20;
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0x00, 0x00, 0x00);
                }
                val04 = FALSE;
                break;
        }

        if (val04 && gCurrDemoInput == NULL) {
            fadeout_music((3 * sDelayedWarpTimer / 2) * 8 - 2);
        }
    }

    return sDelayedWarpTimer;
}

/**
 * If a delayed warp is ready, initiate it.
 */
void initiate_delayed_warp(void) {
    struct ObjectWarpNode *warpNode;
    s32 destWarpNode;

    if (sDelayedWarpOp != WARP_OP_NONE && --sDelayedWarpTimer == 0) {
        reset_dialog_render_state();

        if (gDebugLevelSelect && (sDelayedWarpOp & WARP_OP_TRIGGERS_LEVEL_SELECT)) {
            warp_special(SPECIAL_WARP_LEVEL_SELECT);
        } else if (gCurrDemoInput != NULL) {
            if (sDelayedWarpOp == WARP_OP_DEMO_END) {
                warp_special(SPECIAL_WARP_TITLE);
            } else {
                warp_special(SPECIAL_WARP_GODDARD);
            }
        } else {
            switch (sDelayedWarpOp) {
                case WARP_OP_GAME_OVER:
                    gChangeLevel = gLevelValues.entryLevel;
                    gMarioStates[0].numLives = 4;
                    gMarioStates[0].health = 0x880;
                    break;

                case WARP_OP_CREDITS_END:
                    warp_special(SPECIAL_WARP_CAKE);
                    sound_banks_enable(SEQ_PLAYER_SFX,
                                       SOUND_BANKS_ALL & ~SOUND_BANKS_DISABLED_AFTER_CREDITS);
                    break;

                case WARP_OP_DEMO_NEXT:
                    if (!gDjuiInMainMenu) {
                        warp_special(SPECIAL_WARP_GODDARD);
                    }
                    break;

                case WARP_OP_CREDITS_START:
                    gCurrCreditsEntry = &sCreditsSequence[0];

                    if ((gCurrCreditsEntry != NULL) && (gCurrCreditsEntry->levelNum == gLevelValues.skipCreditsAt)) {
                        lvl_skip_credits();
                    } else if (gCurrCreditsEntry != NULL) {
                        // instance players in the credits
                        gCurrActStarNum = 99;
                        gCurrActNum = 99;
                        initiate_warp(gCurrCreditsEntry->levelNum, gCurrCreditsEntry->areaIndex,
                                    WARP_NODE_CREDITS_START, 0);
                    }
                    break;

                case WARP_OP_CREDITS_NEXT:
                    if (gCurrCreditsEntry == NULL) { gCurrCreditsEntry = &sCreditsSequence[0]; }
                    sound_banks_disable(SEQ_PLAYER_SFX, gDjuiInMainMenu ? SOUND_BANKS_ALL & ~(1 << SOUND_BANK_MENU) : SOUND_BANKS_ALL);

                    gCurrCreditsEntry += 1;

                    if ((gCurrCreditsEntry != NULL) && (gCurrCreditsEntry->levelNum == gLevelValues.skipCreditsAt)) {
                        lvl_skip_credits();
                    } else if (gCurrCreditsEntry != NULL) {
                        gCurrActNum = gCurrCreditsEntry->unk02 & 0x07;
                        if (gCurrCreditsEntry->levelNum == LEVEL_CASTLE_GROUNDS && gDjuiInMainMenu) {
                            gCurrCreditsEntry = &sCreditsSequence[1];
                            destWarpNode = WARP_NODE_CREDITS_NEXT;
                        } else if ((gCurrCreditsEntry + 1)->levelNum == LEVEL_NONE) {
                            destWarpNode = WARP_NODE_CREDITS_END;
                        } else {
                            destWarpNode = WARP_NODE_CREDITS_NEXT;
                        }

                        initiate_warp(gCurrCreditsEntry->levelNum, gCurrCreditsEntry->areaIndex,
                                    destWarpNode, 0);
                    }
                    break;

                default:
                    warpNode = area_get_warp_node(sSourceWarpNodeId);
                    if (warpNode != NULL) {
                        initiate_warp(warpNode->node.destLevel & 0x7F, warpNode->node.destArea,
                                        warpNode->node.destNode, sDelayedWarpArg);

                        check_if_should_set_warp_checkpoint(&warpNode->node);
                        if (sWarpDest.type != WARP_TYPE_CHANGE_LEVEL) {
                            level_set_transition(2, NULL);
                        }
                    }
                    break;
            }
        }
    }
}

void update_hud_values(void) {
    if (gCurrCreditsEntry == NULL) {
        s16 numHealthWedges = gMarioState->health > 0 ? MIN(gMarioState->health >> 8, 8) : 0;

        if (gCurrCourseNum >= COURSE_MIN) {
            gHudDisplay.flags |= HUD_DISPLAY_FLAG_COIN_COUNT;
        } else {
            gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_COIN_COUNT;
        }

        if (gHudDisplay.coins < gMarioState->numCoins) {
            if (gGlobalTimer & 0x00000001) {
                u32 coinSound;
                if (gMarioState->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                    coinSound = SOUND_GENERAL_COIN_WATER;
                } else {
                    coinSound = SOUND_GENERAL_COIN;
                }

                gHudDisplay.coins += 1;
                play_sound(coinSound, gMarioState->marioObj->header.gfx.cameraToObject);

                if (gServerSettings.stayInLevelAfterStar > 0 && gCurrCourseNum != COURSE_NONE) {
                    // retain vanilla behavior
                    if (gLevelValues.numCoinsToLife == 50) {
                        if (gHudDisplay.coins == 50 || gHudDisplay.coins == 100 || gHudDisplay.coins == 150) {
                            gMarioState->numLives++;
                            play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
                        }
                    } else {
                        if (gLevelValues.numCoinsToLife != 0 && gHudDisplay.coins % gLevelValues.numCoinsToLife == 0 && gHudDisplay.coins > 0) {
                            gMarioState->numLives++;
                            play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
                        }
                    }
                }
            }
        }

        if (gMarioState->numLives > gLevelValues.maxLives) {
            gMarioState->numLives = gLevelValues.maxLives;
        }

#if BUGFIX_MAX_LIVES
        if (gMarioState->numCoins > gLevelValues.maxCoins) {
            gMarioState->numCoins = gLevelValues.maxCoins;
        }

        if (gHudDisplay.coins > gLevelValues.maxCoins) {
            gHudDisplay.coins = gLevelValues.maxCoins;
        }
#else
        if (gMarioState->numCoins > gLevelValues.maxCoins) {
            gMarioState->numLives = (s8) gLevelValues.maxCoins;
        }
#endif

        gHudDisplay.stars = gMarioState->numStars;
        gHudDisplay.lives = gMarioState->numLives;
        gHudDisplay.keys = gMarioState->numKeys;

        if (numHealthWedges > gHudDisplay.wedges && !gDjuiInMainMenu) {
            play_sound(SOUND_MENU_POWER_METER, gGlobalSoundSource);
        }
        gHudDisplay.wedges = numHealthWedges;

        if (gMarioState->hurtCounter > 0) {
            gHudDisplay.flags |= HUD_DISPLAY_FLAG_EMPHASIZE_POWER;
        } else {
            gHudDisplay.flags &= ~HUD_DISPLAY_FLAG_EMPHASIZE_POWER;
        }
    }
}

/**
 * Update objects, HUD, and camera. This update function excludes things like
 * endless staircase, warps, pausing, etc. This is used when entering a painting,
 * presumably to allow painting and camera updating while avoiding triggering the
 * warp twice.
 */
void basic_update(UNUSED s16 *arg) {
    area_update_objects();
    update_hud_values();

    if (gCurrentArea != NULL) {
        update_camera(gCurrentArea->camera);
    }
}

bool find_demo_number(void) {
    switch (gCurrLevelNum) {
        case LEVEL_BOWSER_1:
            sDemoNumber = 0;
            return true;
        case LEVEL_WF:
            sDemoNumber = 1;
            return true;
        case LEVEL_CCM:
            sDemoNumber = 2;
            return true;
        case LEVEL_BBH:
            sDemoNumber = 3;
            return true;
        case LEVEL_JRB:
            sDemoNumber = 4;
            return true;
        case LEVEL_HMC:
            sDemoNumber = 5;
            return true;
        case LEVEL_PSS:
            sDemoNumber = 6;
            return true;
        default:
            sDemoNumber = -1;
    }
    return false;
}

static void start_demo(void) {
    if (gIsDemoActive) {
        gIsDemoActive = false;
    } else {
        gIsDemoActive = true;

        if (find_demo_number()) {
            gChangeLevel = gCurrLevelNum;
        }

        if (sDemoNumber >= 0 && sDemoNumber <= 6) {
            gCurrDemoInput = NULL;
            alloc_anim_dma_table(&gDemo, gDemoInputs, gDemoTargetAnim);
            load_patchable_table(&gDemo, sDemoNumber, false);
            gCurrDemoInput = ((struct DemoInput *) gDemo.targetAnim);
        } else {
            gIsDemoActive = false;
        }
    }
}

void stop_demo(UNUSED struct DjuiBase* caller) {
    if (gIsDemoActive) {
        gIsDemoActive = false;
        gCurrDemoInput = NULL;
        gChangeLevel = gCurrLevelNum;
        gDemoCountdown = 0;
        if (gDjuiInMainMenu || gNetworkType == NT_NONE) {
            update_menu_level();
        }
    }
}

int gPressedStart = 0;

s32 play_mode_normal(void) {
    if (!gDjuiInMainMenu) {
        if (gCurrDemoInput != NULL) {
            print_intro_text();
            if (gPlayer1Controller->buttonPressed & END_DEMO) {
                level_trigger_warp(gMarioState, gCurrLevelNum == LEVEL_PSS ? WARP_OP_DEMO_END : WARP_OP_DEMO_NEXT);
            } else if (!gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE && (gPlayer1Controller->buttonPressed & START_BUTTON)) {
                gPressedStart = 1;
                level_trigger_warp(gMarioState, WARP_OP_DEMO_NEXT);
            }
        }
    } else {
        if (gDjuiInMainMenu &&
            !configMenuStaffRoll &&
            gCurrDemoInput == NULL &&
            configMenuDemos &&
            !gDjuiInPlayerMenu &&
            (++gDemoCountdown) == PRESS_START_DEMO_TIMER &&
            (find_demo_number() && (sDemoNumber <= 6 && sDemoNumber > -1)) &&
            gNetworkType == NT_NONE) {
            start_demo();
        }

        if (((gCurrDemoInput != NULL) &&
            (gPlayer1Controller->buttonPressed & END_DEMO || !gIsDemoActive || !gDjuiInMainMenu || gNetworkType != NT_NONE || gDjuiInPlayerMenu)) ||
            (gCurrDemoInput == NULL && gIsDemoActive)) {
            gPlayer1Controller->buttonPressed &= ~END_DEMO;
            stop_demo(NULL);
        }
    }

    warp_area();
    check_instant_warp();

    if (sTimerRunning) {
        gHudDisplay.timer = gNetworkAreaTimer - gControlTimerStartNat;
        if (gHudDisplay.timer >= 17999) {
            gHudDisplay.timer = 17999;
        }
    } else if (gControlTimerStopNat > 0) {
        gHudDisplay.timer = gControlTimerStopNat - gControlTimerStartNat;
        if (gHudDisplay.timer >= 17999) {
            gHudDisplay.timer = 17999;
        }
    }

    area_update_objects();
    update_hud_values();

    if (gCurrentArea != NULL) {
        update_camera(gCurrentArea->camera);
    }

    initiate_painting_warp(-1);
    initiate_delayed_warp();

    // If either initiate_painting_warp or initiate_delayed_warp initiated a
    // warp, change play mode accordingly.
    if (sCurrPlayMode == PLAY_MODE_NORMAL || sCurrPlayMode == PLAY_MODE_PAUSED) {
        if (gCurrCreditsEntry != NULL && gCurrCreditsEntry != &sCreditsSequence[0]) {
            // special case for credit warps
            if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL) {
                set_play_mode(PLAY_MODE_CHANGE_LEVEL);
            } else if (sTransitionTimer != 0) {
                set_play_mode(PLAY_MODE_CHANGE_AREA);
            }
        } else if (!gReceiveWarp.received) {
            if (sWarpDest.type == WARP_TYPE_CHANGE_LEVEL) {
                set_play_mode(PLAY_MODE_CHANGE_LEVEL);
            } else if (sTransitionTimer != 0) {
                set_play_mode(PLAY_MODE_CHANGE_AREA);
            } else if (sCurrPlayMode == PLAY_MODE_NORMAL && pressed_pause()) {
                lower_background_noise(1);
                cancel_rumble();
                gCameraMovementFlags |= CAM_MOVE_PAUSE_SCREEN;
                set_play_mode(PLAY_MODE_PAUSED);
            }
        }
    }


    return 0;
}

s32 play_mode_paused(void) {
    if (gPauseScreenMode == 0) {
        set_menu_mode(RENDER_PAUSE_SCREEN);
    } else if (gPauseScreenMode == 1) {
        raise_background_noise(1);
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        set_play_mode(PLAY_MODE_NORMAL);
    } else if (gPauseScreenMode == 2) {
        extern s16 gPrevMenuMode;
        if (gPrevMenuMode > 1) { // Course complete screen
            raise_background_noise(1);
            gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        } else { // Pause menu
            level_trigger_warp(&gMarioStates[0], WARP_OP_EXIT);
        }
        set_play_mode(PLAY_MODE_NORMAL);
    } else if (gPauseScreenMode == 3) {
        // Exit level
        if (gDebugLevelSelect) {
            fade_into_special_warp(-9, 1);
        } else {
            initiate_warp(gLevelValues.exitCastleLevel, gLevelValues.exitCastleArea, gLevelValues.exitCastleWarpNode, 0);
            fade_into_special_warp(0, 0);
            gSavedCourseNum = COURSE_NONE;
        }
        set_play_mode(PLAY_MODE_CHANGE_LEVEL);
    } /* else if (gPauseScreenMode == 4) {
        // We should only be getting "int 4" to here
        initiate_warp(LEVEL_CASTLE, 1, 0x1F, 0);
        fade_into_special_warp(0, 0);
        game_exit();
    }*/

    if (!gLevelValues.zoomOutCameraOnPause || !network_check_singleplayer_pause()) {
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
    }
    return 0;
}

/**
 * Debug mode that lets you frame advance by pressing D-pad down. Unfortunately
 * it uses the pause camera, making it basically unusable in most levels.
 */
s32 play_mode_frame_advance(void) {
    if (gPlayer1Controller->buttonPressed & D_JPAD) {
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        play_mode_normal();
    } else if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        gCameraMovementFlags &= ~CAM_MOVE_PAUSE_SCREEN;
        raise_background_noise(1);
        set_play_mode(PLAY_MODE_NORMAL);
    } else {
        gCameraMovementFlags |= CAM_MOVE_PAUSE_SCREEN;
    }

    return 0;
}

/**
 * Set the transition, which is a period of time after the warp is initiated
 * but before it actually occurs. If updateFunction is not NULL, it will be
 * called each frame during the transition.
 */
void level_set_transition(s16 length, void (*updateFunction)(s16 *)) {
    sTransitionTimer = length;
    sTransitionUpdate = updateFunction;
}

/**
 * Play the transition and then return to normal play mode.
 */
s32 play_mode_change_area(void) {
    // fade out all players
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        gNetworkPlayers[i].fadeOpacity = 0;
    }

    //! This maybe was supposed to be sTransitionTimer == -1? sTransitionUpdate
    // is never set to -1.
    if (sTransitionUpdate == (void (*)(s16 *)) - 1) {
        update_camera(gCurrentArea->camera);
    } else if (sTransitionUpdate != NULL) {
        sTransitionUpdate(&sTransitionTimer);
    }

    if (sTransitionTimer > 0) {
        sTransitionTimer -= 1;
    }

    if (sTransitionTimer == 0) {
        sTransitionUpdate = NULL;
        set_play_mode(PLAY_MODE_NORMAL);
    }

    return 0;
}

/**
 * Play the transition and then return to normal play mode.
 */
s32 play_mode_change_level(void) {
    // fade out all players
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        gNetworkPlayers[i].fadeOpacity = 0;
    }

    if (sTransitionUpdate != NULL) {
        sTransitionUpdate(&sTransitionTimer);
    }

    if (--sTransitionTimer == -1) {
        gHudDisplay.flags = HUD_DISPLAY_NONE;
        sTransitionTimer = 0;
        sTransitionUpdate = NULL;
        if (gCurrActStarNum != 99) {
            gCurrActStarNum = 0;
        }
        if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
            return sWarpDest.levelNum;
        } else {
            return D_80339EE0;
        }
    }

    return 0;
}

/**
 * Unused play mode. Doesn't call transition update and doesn't reset transition at the end.
 */
UNUSED static s32 play_mode_unused(void) {
    if (--sTransitionTimer == -1) {
        gHudDisplay.flags = HUD_DISPLAY_NONE;

        if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
            return sWarpDest.levelNum;
        } else {
            return D_80339EE0;
        }
    }

    return 0;
}

void update_menu_level(void) {
    // figure out level
    s32 curLevel = 0;
    switch (configMenuLevel) {
        case 0:  curLevel = LEVEL_CASTLE_GROUNDS; break;
        case 1:  curLevel = LEVEL_BOB;            break;
        case 2:  curLevel = LEVEL_WF;             break;
        case 3:  curLevel = LEVEL_WMOTR;          break;
        case 4:  curLevel = LEVEL_JRB;            break;
        case 5:  curLevel = LEVEL_SSL;            break;
        case 6:  curLevel = LEVEL_TTM;            break;
        case 7:  curLevel = LEVEL_SL;             break;
        case 8:  curLevel = LEVEL_BBH;            break;
        case 9:  curLevel = LEVEL_LLL;            break;
        case 10: curLevel = LEVEL_THI;            break;
        case 11: curLevel = LEVEL_HMC;            break;
        case 12: curLevel = LEVEL_CCM;            break;
        case 13: curLevel = LEVEL_RR;             break;
        case 14: curLevel = LEVEL_BITDW;          break;
        case 15: curLevel = LEVEL_PSS;            break;
        case 16: curLevel = LEVEL_TTC;            break;
        case 17: curLevel = LEVEL_WDW;            break;
        default: curLevel = LEVEL_CASTLE_GROUNDS; break;
    }

    // figure out music
    stop_cap_music();
    reset_volume();
    disable_background_sound();
    if (gMainMenuSounds[configMenuSound].sound == STAGE_MUSIC) {
        // if staff roll is on, set configMenuSound to Title Screen sequence, or 0
        if (configMenuStaffRoll) {
            configMenuSound = 0;
        }
        if (curLevel == LEVEL_CASTLE_GROUNDS) {
            set_background_music(0, SEQ_MENU_FILE_SELECT, 0);
        } else if (gCurrentArea != NULL) {
            set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
        }
    } else {
        set_background_music(0, gMainMenuSounds[configMenuSound].sound, 0);
    }

    if (configMenuStaffRoll) {
        return;
    } else {
        gCurrCreditsEntry = NULL;
    }

    // warp to level
    if (gCurrLevelNum != curLevel) {
        if (gIsDemoActive) {
            stop_demo(NULL);
        }

        gChangeLevel = curLevel;
        gChangeActNum = 6;
        gDemoCountdown = 0;
    }
    if (gIsDemoActive) { return; }

    if (gCurrAreaIndex != 2 && gCurrLevelNum == LEVEL_THI) {
        sWarpDest.type = WARP_TYPE_CHANGE_AREA;
        sWarpDest.areaIdx = 2;
        sWarpDest.nodeId = 0x0A;
    }

    struct Object *o;
    // set mario/camera pos
    switch (gCurrLevelNum) {
        case LEVEL_CASTLE_GROUNDS:
            if (gMarioState->action != ACT_INTRO_CUTSCENE && gMarioState->prevAction != ACT_INTRO_CUTSCENE) {
                vec3f_set(gMarioState->pos, -1328, 260, 4664);
                vec3f_set(gLakituState.curPos, -1328, 390, 6064);
                gMarioState->faceAngle[1] = 0;
                gLakituState.nextYaw = gMarioState->faceAngle[1] + 0x8000;
            }
            break;
        case LEVEL_BOB:
            vec3f_set(gMarioState->pos, 7008, 864, 1943);
            vec3f_set(gLakituState.curPos, 7909, 1064, 2843);
            gMarioState->faceAngle[1] = 0x2000;

            // delete all goombas as they interfere with the main menu
            o = find_object_with_behavior(bhvGoomba);
            if (o != NULL) {
                obj_mark_for_deletion(o);
            }
            break;
        case LEVEL_WF:
            vec3f_set(gMarioState->pos, -2904, 2560, -327);
            vec3f_set(gLakituState.curPos, -4504, 2760, -777);
            gMarioState->faceAngle[1] = -15536;
            break;
        case LEVEL_WMOTR:
            vec3f_set(gMarioState->pos, 3548, -2738, 4663);
            vec3f_set(gLakituState.curPos, 3548, -2438, 6063);
            gMarioState->faceAngle[1] = 0;
            break;
        case LEVEL_JRB:
            vec3f_set(gMarioState->pos, 3639, 1536, 6202);
            vec3f_set(gLakituState.curPos, 5039, 1736, 6402);
            break;
        case LEVEL_SSL:
            vec3f_set(gMarioState->pos, -2048, 256, 961);
            vec3f_set(gLakituState.curPos, -2048, 356, 2461);
            gMarioState->faceAngle[1] = 0;
            break;
        case LEVEL_TTM:
            vec3f_set(gMarioState->pos, 2488, 1460, 2011);
            vec3f_set(gLakituState.curPos, 3488, 1763, 3411);
            gMarioState->faceAngle[1] = 0x1000;
            break;
        case LEVEL_SL:
            vec3f_set(gMarioState->pos, 5494, 1024, 443);
            vec3f_set(gLakituState.curPos, 6994, 1124, 443);
            gMarioState->faceAngle[1] = 0x4000;
            break;
        case LEVEL_BBH:
            vec3f_set(gMarioState->pos, 666, -204, 5303);
            vec3f_set(gLakituState.curPos, 666, -204, 6803);
            gMarioState->faceAngle[1] = 0;

            // delete all scuttlebugs as they interfere with the main menu
            o = find_object_with_behavior(bhvScuttlebug);
            if (o != NULL) {
                obj_mark_for_deletion(o);
            }
            break;
        case LEVEL_LLL:
            vec3f_set(gMarioState->pos, -2376, 638, 956);
            vec3f_set(gLakituState.curPos, -3576, 938, 1576);
            gMarioState->faceAngle[1] = -0x2800;
            break;
        case LEVEL_THI:
            vec3f_set(gMarioState->pos, -1010, 341, -324);
            vec3f_set(gLakituState.curPos, -2246, 431, -324);
            gMarioState->faceAngle[1] = -0x4000;

            // delete all goombas as they interfere with the main menu
            o = find_object_with_behavior(bhvGoomba);
            if (o != NULL) {
                obj_mark_for_deletion(o);
            }
            break;
        case LEVEL_HMC:
            vec3f_set(gMarioState->pos, -3600, -4279, 3616);
            vec3f_set(gLakituState.curPos, -6000, -2938, 600);
            gMarioState->faceAngle[1] = -0x6000;
            break;
        case LEVEL_CCM:
            vec3f_set(gMarioState->pos, -1127, -3580, 6162);
            vec3f_set(gLakituState.curPos, -1330, -2830, 9099);
            gMarioState->faceAngle[1] = -0x1000;
            break;
        case LEVEL_RR:
            vec3f_set(gMarioState->pos, 1418, 3167, -2349);
            vec3f_set(gLakituState.curPos, -1518, 4567, -4549);
            gMarioState->faceAngle[1] = -0x6000;
            break;
        case LEVEL_BITDW:
            vec3f_set(gMarioState->pos, -4507, 1126, -285);
            vec3f_set(gLakituState.curPos, -2507, 2126, -285);
            break;
        case LEVEL_PSS:
            vec3f_set(gMarioState->pos, -4729, -3057, -3025);
            vec3f_set(gLakituState.curPos, -2729, -1557, -5025);
            gMarioState->faceAngle[1] = 0x5000;
            break;
        case LEVEL_TTC:
            vec3f_set(gMarioState->pos, -645, 0, -750);
            vec3f_set(gLakituState.curPos, 2500, 570, -240);
            gMarioState->faceAngle[1] = 0x2000;
            break;
        case LEVEL_WDW:
            vec3f_set(gMarioState->pos, -2684, 3328, 3000);
            vec3f_set(gLakituState.curPos, -4002, 4000, 4622);
            gMarioState->faceAngle[1] = -0x1C34;
            break;
    }

    gMarioState->health = 0x880;
    // reset input
    gMarioState->input = 0;
    gMarioState->intendedMag = 0;
    gMarioState->controller->buttonDown = 0;
    gMarioState->controller->buttonPressed = 0;
    gMarioState->controller->rawStickX = 0;
    gMarioState->controller->rawStickY = 0;
    gMarioState->controller->stickX = 0;
    gMarioState->controller->stickY = 0;
    gMarioState->controller->extStickX = 0;
    gMarioState->controller->extStickY = 0;
    gMarioState->controller->stickMag = 0;
}

s32 update_level(void) {
    // update main menu level
    if (gDjuiInMainMenu) {
        update_menu_level();
    }
    sCancelNextActSelector = gDjuiInMainMenu;

    if (gFanFareDebounce > 0) { gFanFareDebounce--; }

    s32 changeLevel = 0;

    if (gChangeLevel != -1) {
        gHudDisplay.flags = HUD_DISPLAY_NONE;
        sTransitionTimer = 0;
        sTransitionUpdate = NULL;
        changeLevel = gChangeLevel;
        gChangeLevel = -1;
        gChangeLevelTransition = -1;
        return changeLevel;
    } else if (!gWarpTransition.isActive && sDelayedWarpOp == WARP_OP_NONE && gChangeLevelTransition != -1) {
        gHudDisplay.flags = HUD_DISPLAY_NONE;
        sTransitionTimer = 0;
        sTransitionUpdate = NULL;
        changeLevel = gChangeLevelTransition;
        gChangeLevel = -1;
        gChangeLevelTransition = -1;
        return changeLevel;
    }

    if (gCurrentArea != NULL) {
        gCurrentArea->localAreaTimer++;
    }

    switch (sCurrPlayMode) {
        case PLAY_MODE_NORMAL:
            changeLevel = play_mode_normal();
            break;
        case PLAY_MODE_PAUSED:
            if (!network_check_singleplayer_pause()) {
                changeLevel = play_mode_normal();
            }

            if (sCurrPlayMode == PLAY_MODE_PAUSED) {
                changeLevel = play_mode_paused();
            }
            break;
        case PLAY_MODE_CHANGE_AREA:
            changeLevel = play_mode_change_area();
            break;
        case PLAY_MODE_CHANGE_LEVEL:
            changeLevel = play_mode_change_level();
            break;
        case PLAY_MODE_FRAME_ADVANCE:
            changeLevel = play_mode_frame_advance();
            break;
    }

    if (changeLevel) {
        reset_volume();
        enable_background_sound();
    }

    return changeLevel;
}

s32 init_level(void) {
    sync_objects_clear();
    reset_dialog_render_state();

    s32 val4 = 0;

    set_play_mode(PLAY_MODE_NORMAL);

    sDelayedWarpOp = WARP_OP_NONE;
    sTransitionTimer = 0;
    D_80339EE0 = 0;

    for (int i = 0; i < 8; i++) {
        gSpawnedStarDefault[i] = 0;
        gSpawnedStarNLE[i] = 0;
        gSpawnedStarRed[i] = 0;
        gSpawnedStarHidden[i] = 0;
    }

    gSpawnedStarDefaultCount = 0;
    gSpawnedStarNLECount = 0;
    gSpawnedStarRedCount = 0;
    gSpawnedStarHiddenCount = 0;

    if (gCurrCreditsEntry == NULL) {
        gHudDisplay.flags = HUD_DISPLAY_DEFAULT;
    } else {
        gHudDisplay.flags = HUD_DISPLAY_NONE;
    }

    sTimerRunning = FALSE;

    if (sWarpDest.type != WARP_TYPE_NOT_WARPING) {
        if (sWarpDest.nodeId >= WARP_NODE_CREDITS_MIN) {
            warp_credits();
        } else {
            warp_level();
        }
    } else {
        if (gPlayerSpawnInfos[0].areaIndex >= 0) {
            load_mario_area();
            init_mario();
        }

        if (gCurrentArea != NULL) {
            reset_camera(gCurrentArea->camera);

            if (gCurrDemoInput != NULL) {
                set_mario_action(gMarioState, ACT_IDLE, 0);
            } else if (!gDebugLevelSelect) {
                if (gMarioState && gMarioState->action != ACT_UNINITIALIZED) {
                    bool skipIntro = (gNetworkType == NT_NONE || gServerSettings.skipIntro != 0);
                    if (gDjuiInMainMenu && gNetworkType == NT_NONE) {
                        // pick random main menu level
                        if (configMenuRandom) {
                            srand(time(0));
                            int randLevel = rand() % (MENU_LEVEL_MAX - MENU_LEVEL_MIN) + 1;
                            configMenuLevel = randLevel;
                        }

                        if (configMenuStaffRoll) {
                            gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
                            warp_credits();
                            level_trigger_warp(gMarioState, WARP_OP_CREDITS_NEXT);
                            sFirstCastleGroundsMenu = false;
                        } else {
                            if (configMenuLevel == 0 && sFirstCastleGroundsMenu) {
                                set_mario_action(gMarioState, ACT_INTRO_CUTSCENE, 7);
                                sFirstCastleGroundsMenu = false;
                            } else {
                                set_mario_action(gMarioState, ACT_IDLE, 0);
                            }
                        }
                    } else if (skipIntro || save_file_exists(gCurrSaveFileNum - 1) || gDjuiInMainMenu) {
                        set_mario_action(gMarioState, ACT_IDLE, 0);
                    } else {
                        set_mario_action(gMarioState, ACT_INTRO_CUTSCENE, 0);
                        val4 = 1;
                    }
                }
            }
        }

        if (val4 != 0) {
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 0x5A, 0xFF, 0xFF, 0xFF);
        } else {
            play_transition(WARP_TRANSITION_FADE_FROM_STAR, 0x10, 0xFF, 0xFF, 0xFF);
        }

        if (gCurrDemoInput == NULL && gCurrentArea) {
            set_background_music(gCurrentArea->musicParam, gCurrentArea->musicParam2, 0);
        }
    }

    if (gCurrDemoInput == NULL) {
        cancel_rumble();
    }

    if (gMarioState && gMarioState->action == ACT_INTRO_CUTSCENE) {
        sound_banks_disable(SEQ_PLAYER_SFX, SOUND_BANKS_DISABLED_DURING_INTRO_CUTSCENE);
    }

    if (gNetworkPlayerLocal != NULL) {
        network_player_update_course_level(gNetworkPlayerLocal, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
    }
    smlua_call_event_hooks(HOOK_ON_LEVEL_INIT);

    // clear texture 1 on level init -- can linger and corrupt textures otherwise
    extern u8 gGfxPcResetTex1;
    gGfxPcResetTex1 = 1;

    // reset nametags
    nametags_reset();

    if (gDelayedInitSound >= 0) {
        play_character_sound(&gMarioStates[0], gDelayedInitSound);
        gDelayedInitSound = -1;
    }

    return 1;
}

/**
 * Initialize the current level if initOrUpdate is 0, or update the level if it is 1.
 */
s32 lvl_init_or_update(s16 initOrUpdate, UNUSED s32 unused) {
    s32 result = 0;

    switch (initOrUpdate) {
        case 0:
            result = init_level();

            break;
        case 1:
            result = update_level();
            break;
    }

    return result;
}

s32 lvl_init_from_save_file(UNUSED s16 arg0, s16 levelNum) {
#ifdef VERSION_EU
    s16 var = eu_get_language();
    switch (var) {
        case LANGUAGE_ENGLISH:
            load_segment_decompress(0x19, _translation_en_mio0SegmentRomStart,
                                    _translation_en_mio0SegmentRomEnd);
            break;
        case LANGUAGE_FRENCH:
            load_segment_decompress(0x19, _translation_fr_mio0SegmentRomStart,
                                    _translation_fr_mio0SegmentRomEnd);
            break;
        case LANGUAGE_GERMAN:
            load_segment_decompress(0x19, _translation_de_mio0SegmentRomStart,
                                    _translation_de_mio0SegmentRomEnd);
            break;
    }
#endif
    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;
    gNeverEnteredCastle = !save_file_exists(gCurrSaveFileNum - 1) && (gServerSettings.skipIntro == 0);
    if (gNetworkType == NT_NONE) { gNeverEnteredCastle = true; }

    gCurrLevelNum = levelNum;
    gCurrCourseNum = COURSE_NONE;
    gSavedCourseNum = COURSE_NONE;
    gCurrCreditsEntry = NULL;
    gMarioStates[0].specialTripleJump = FALSE;

    init_mario_from_save_file();
    disable_warp_checkpoint();
    save_file_move_cap_to_default_location();
    select_mario_cam_mode();
    set_yoshi_as_not_dead();

    return levelNum;
}

s32 lvl_set_current_level(s16 arg0, s16 levelNum) {
    s32 warpCheckpointActive = sWarpCheckpointActive;
    s16 level = arg0 != 0 ? arg0 : levelNum;

    sWarpCheckpointActive = FALSE;
    gCurrLevelNum = level;
    gCurrCourseNum = get_level_course_num(level);

    bool foundHook = false;
    bool hookUseActSelect = false;
    smlua_call_event_hooks_use_act_select(HOOK_USE_ACT_SELECT, level, &foundHook, &hookUseActSelect);

    if (!foundHook || !hookUseActSelect) {
        if (gCurrDemoInput != NULL || gCurrCreditsEntry != NULL || gCurrCourseNum == COURSE_NONE) {
            return 0;
        }
    }

    if (gCurrLevelNum != LEVEL_BOWSER_1 && gCurrLevelNum != LEVEL_BOWSER_2
        && gCurrLevelNum != LEVEL_BOWSER_3) {
        gMarioState->numCoins = 0;
        gHudDisplay.coins = 0;
        gCurrCourseStarFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1);
    }

    if (gSavedCourseNum != gCurrCourseNum) {
        gSavedCourseNum = gCurrCourseNum;
        nop_change_course();
        disable_warp_checkpoint();
    }

    if (gDjuiInMainMenu) {
        return 0;
    }

    if (foundHook) {
        return hookUseActSelect;
    }

    if (gLevelValues.disableActs) {
        return 0;
    }

    if (gCurrCourseNum > COURSE_STAGES_MAX || warpCheckpointActive) {
        return 0;
    }

    if (gDebugLevelSelect && !gShowProfiler) {
        return 0;
    }

    if (sCancelNextActSelector) {
        sCancelNextActSelector = false;
        return 0;
    }

    return 1;
}

/**
 * Play the "thank you so much for to playing my game" sound.
 */
s32 lvl_play_the_end_screen_sound(UNUSED s16 arg0, UNUSED s32 arg1) {
    play_sound(SOUND_MENU_THANK_YOU_PLAYING_MY_GAME, gGlobalSoundSource);
    return 1;
}

s32 lvl_exiting_credits(UNUSED s16 arg0, UNUSED s32 arg1) {
    gCurrActStarNum = 0;
    gCurrActNum = 0;
    return 1;
}

void fake_lvl_init_from_save_file(void) {
    sWarpDest.type = WARP_TYPE_NOT_WARPING;
    sDelayedWarpOp = WARP_OP_NONE;
    gNeverEnteredCastle = !save_file_exists(gCurrSaveFileNum - 1) && (gServerSettings.skipIntro == 0);
    if (gNetworkType == NT_NONE) { gNeverEnteredCastle = true; }

    gCurrCreditsEntry = NULL;
    gMarioStates[0].specialTripleJump = false;

    init_mario_from_save_file();
    disable_warp_checkpoint();
    save_file_move_cap_to_default_location();
    select_mario_cam_mode();
    set_yoshi_as_not_dead();
    fadeout_music(30);

    gChangeLevel = gLevelValues.entryLevel;
}

void lvl_skip_credits(void) {
    gCurrCreditsEntry = NULL;
    gCurrActStarNum = 0;
    gCurrActNum = 0;
    gChangeLevel = gLevelValues.entryLevel;
    gMarioStates[0].health = 0x880;
    play_transition(0x09, 0x14, 0x00, 0x00, 0x00);
}
