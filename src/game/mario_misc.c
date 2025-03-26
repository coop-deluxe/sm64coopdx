#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "envfx_snow.h"
#include "game_init.h"
#include "goddard/renderer.h"
#include "interaction.h"
#include "level_update.h"
#include "mario_misc.h"
#include "memory.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "skybox.h"
#include "hardcoded.h"
#include "sound_init.h"
#include "pc/network/network.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/mods/mods.h"

#define TOAD_STAR_1_REQUIREMENT gBehaviorValues.ToadStar1Requirement
#define TOAD_STAR_2_REQUIREMENT gBehaviorValues.ToadStar2Requirement
#define TOAD_STAR_3_REQUIREMENT gBehaviorValues.ToadStar3Requirement

#define TOAD_STAR_1_DIALOG gBehaviorValues.dialogs.ToadStar1Dialog
#define TOAD_STAR_2_DIALOG gBehaviorValues.dialogs.ToadStar2Dialog
#define TOAD_STAR_3_DIALOG gBehaviorValues.dialogs.ToadStar3Dialog

#define TOAD_STAR_1_DIALOG_AFTER gBehaviorValues.dialogs.ToadStar1AfterDialog
#define TOAD_STAR_2_DIALOG_AFTER gBehaviorValues.dialogs.ToadStar2AfterDialog
#define TOAD_STAR_3_DIALOG_AFTER gBehaviorValues.dialogs.ToadStar3AfterDialog

enum ToadMessageStates {
    TOAD_MESSAGE_FADED,
    TOAD_MESSAGE_OPAQUE,
    TOAD_MESSAGE_OPACIFYING,
    TOAD_MESSAGE_FADING,
    TOAD_MESSAGE_TALKING
};

enum UnlockDoorStarStates {
    UNLOCK_DOOR_STAR_RISING,
    UNLOCK_DOOR_STAR_WAITING,
    UNLOCK_DOOR_STAR_SPAWNING_PARTICLES,
    UNLOCK_DOOR_STAR_DONE
};

struct PlayerColor {
    Lights1 parts[PLAYER_PART_MAX];
};

/**
 * The eye texture on succesive frames of Mario's blink animation.
 * He intentionally blinks twice each time.
 */
static s8 gMarioBlinkAnimation[7] = { 1, 2, 1, 0, 1, 2, 1 };

/**
 * The scale values per frame for Mario's foot/hand for his attack animation
 * There are 3 scale animations in groups of 6 frames.
 * The first animation starts at frame index 3 and goes down, the others start at frame index 5.
 * The values get divided by 10 before assigning, so e.g. 12 gives a scale factor 1.2.
 * All combined, this means e.g. the first animation scales Mario's fist by {2.4, 1.6, 1.2, 1.0} on
 * successive frames.
 */
static s8 gMarioAttackScaleAnimation[3 * 6] = {
    10, 12, 16, 24, 10, 10, 10, 14, 20, 30, 10, 10, 10, 16, 20, 26, 26, 20,
};

struct MarioBodyState gBodyStates[MAX_PLAYERS];
struct GraphNodeObject gMirrorMario[MAX_PLAYERS];  // copy of Mario's geo node for drawing mirror Mario
struct PlayerColor gNetworkPlayerColors[MAX_PLAYERS];

// This whole file is weirdly organized. It has to be the same file due
// to rodata boundaries and function aligns, which means the programmer
// treated this like a "misc" file for vaguely Mario related things
// (message NPC related things, the Mario head geo, and Mario geo
// functions)

/**
 * Geo node script that draws Mario's head on the title screen.
 */
Gfx *geo_draw_mario_head_goddard(s32 callContext, struct GraphNode *node, Mat4 *c) {
    Gfx *gfx = NULL;
    s16 sfx = 0;
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
    UNUSED Mat4 *transform = c;

    if (callContext == GEO_CONTEXT_RENDER) {
        if (gPlayer1Controller->controllerData != NULL && !gWarpTransition.isActive) {
            gd_copy_p1_contpad(gPlayer1Controller->controllerData);
        }
        gfx = (Gfx *) PHYSICAL_TO_VIRTUAL(gdm_gettestdl(asGenerated->parameter));
        gGoddardVblankCallback = gd_vblank;
        sfx = gd_sfx_to_play();
        play_menu_sounds(sfx);
    }
    return gfx;
}

static void toad_message_faded(void) {
    if (!gCurrentObject) { return; }
    if (gCurrentObject->oDistanceToMario > 700.0f) {
        gCurrentObject->oToadMessageRecentlyTalked = FALSE;
    }
    if (!gCurrentObject->oToadMessageRecentlyTalked && gCurrentObject->oDistanceToMario < 600.0f) {
        gCurrentObject->oToadMessageState = TOAD_MESSAGE_OPACIFYING;
    }
}

static void toad_message_opaque(void) {
    if (!gCurrentObject) { return; }
    if (gCurrentObject->oDistanceToMario > 700.0f) {
        gCurrentObject->oToadMessageState = TOAD_MESSAGE_FADING;
    } else if (!gCurrentObject->oToadMessageRecentlyTalked) {
        gCurrentObject->oInteractionSubtype = INT_SUBTYPE_NPC;
        if (gCurrentObject->oInteractStatus & INT_STATUS_INTERACTED) {
            gCurrentObject->oInteractStatus = 0;
            gCurrentObject->oToadMessageState = TOAD_MESSAGE_TALKING;
            play_toads_jingle();
        }
    }
}

static void toad_message_talking(void) {
    if (!gCurrentObject) { return; }
    if (cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 3, 1, CUTSCENE_DIALOG, gCurrentObject->oToadMessageDialogId, NULL)
        != 0) {
        gCurrentObject->oToadMessageRecentlyTalked = TRUE;
        gCurrentObject->oToadMessageState = TOAD_MESSAGE_FADING;

        u32 dialogId = gCurrentObject->oToadMessageDialogId;
        if (dialogId == TOAD_STAR_1_DIALOG) {
            gCurrentObject->oToadMessageDialogId = TOAD_STAR_1_DIALOG_AFTER;
            bhv_spawn_star_no_level_exit(gMarioStates[0].marioObj, 0, TRUE);
        } else if (dialogId == TOAD_STAR_2_DIALOG) {
            gCurrentObject->oToadMessageDialogId = TOAD_STAR_2_DIALOG_AFTER;
            bhv_spawn_star_no_level_exit(gMarioStates[0].marioObj, 1, TRUE);
        } else if (dialogId == TOAD_STAR_3_DIALOG) {
            gCurrentObject->oToadMessageDialogId = TOAD_STAR_3_DIALOG_AFTER;
            bhv_spawn_star_no_level_exit(gMarioStates[0].marioObj, 2, TRUE);
        }
    }
}

static void toad_message_opacifying(void) {
    if (!gCurrentObject) { return; }
    if ((gCurrentObject->oOpacity += 6) == 255) {
        gCurrentObject->oToadMessageState = TOAD_MESSAGE_OPAQUE;
    }
}

static void toad_message_fading(void) {
    if (!gCurrentObject) { return; }
    if ((gCurrentObject->oOpacity -= 6) == 81) {
        gCurrentObject->oToadMessageState = TOAD_MESSAGE_FADED;
    }
}

void bhv_toad_message_init(void) {
    if (!gCurrentObject) { return; }
    s32 saveFlags = save_file_get_flags();
    s32 starCount = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    s32 dialogId = (gCurrentObject->oBehParams >> 24) & 0xFF;
    s32 enoughStars = TRUE;

    if (dialogId == (s32)TOAD_STAR_1_DIALOG) {
        enoughStars = (starCount >= TOAD_STAR_1_REQUIREMENT);
        if (saveFlags & SAVE_FLAG_COLLECTED_TOAD_STAR_1) {
            dialogId = TOAD_STAR_1_DIALOG_AFTER;
        }
    } else if (dialogId == (s32)TOAD_STAR_2_DIALOG) {
        enoughStars = (starCount >= TOAD_STAR_2_REQUIREMENT);
        if (saveFlags & SAVE_FLAG_COLLECTED_TOAD_STAR_2) {
            dialogId = TOAD_STAR_2_DIALOG_AFTER;
        }
    } else if (dialogId == (s32)TOAD_STAR_3_DIALOG) {
        enoughStars = (starCount >= TOAD_STAR_3_REQUIREMENT);
        if (saveFlags & SAVE_FLAG_COLLECTED_TOAD_STAR_3) {
            dialogId = TOAD_STAR_3_DIALOG_AFTER;
        }
    }

    if (enoughStars) {
        gCurrentObject->oToadMessageDialogId = dialogId;
        gCurrentObject->oToadMessageRecentlyTalked = FALSE;
        gCurrentObject->oToadMessageState = TOAD_MESSAGE_FADED;
        gCurrentObject->oOpacity = 81;
    } else {
        obj_mark_for_deletion(gCurrentObject);
    }
}

void bhv_toad_message_loop(void) {
    if (!gCurrentObject) { return; }
    if (gCurrentObject->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        gCurrentObject->oInteractionSubtype = 0;
        switch (gCurrentObject->oToadMessageState) {
            case TOAD_MESSAGE_FADED:
                toad_message_faded();
                break;
            case TOAD_MESSAGE_OPAQUE:
                toad_message_opaque();
                break;
            case TOAD_MESSAGE_OPACIFYING:
                toad_message_opacifying();
                break;
            case TOAD_MESSAGE_FADING:
                toad_message_fading();
                break;
            case TOAD_MESSAGE_TALKING:
                toad_message_talking();
                break;
        }
    }
}

static void star_door_unlock_spawn_particles(s16 angleOffset) {
    if (!gCurrentObject) { return; }
    struct Object *sparkleParticle = spawn_object(gCurrentObject, 0, bhvSparkleSpawn);
    if (sparkleParticle == NULL) { return; }

    sparkleParticle->oPosX +=
        100.0f * sins((gCurrentObject->oUnlockDoorStarTimer * 0x2800) + angleOffset);
    sparkleParticle->oPosZ +=
        100.0f * coss((gCurrentObject->oUnlockDoorStarTimer * 0x2800) + angleOffset);
    // Particles are spawned lower each frame
    sparkleParticle->oPosY -= gCurrentObject->oUnlockDoorStarTimer * 10.0f;
}

void bhv_unlock_door_star_init(void) {
    if (!gCurrentObject) { return; }
    gCurrentObject->oUnlockDoorStarState = UNLOCK_DOOR_STAR_RISING;
    gCurrentObject->oUnlockDoorStarTimer = 0;
    gCurrentObject->oUnlockDoorStarYawVel = 0x1000;
    gCurrentObject->oPosX += 30.0f * sins(gMarioState->faceAngle[1] - 0x4000);
    gCurrentObject->oPosY += 160.0f;
    gCurrentObject->oPosZ += 30.0f * coss(gMarioState->faceAngle[1] - 0x4000);
    gCurrentObject->oMoveAngleYaw = 0x7800;
    obj_scale(gCurrentObject, 0.5f);
}

void bhv_unlock_door_star_loop(void) {
    if (!gCurrentObject) { return; }
    UNUSED u8 unused1[4];
    s16 prevYaw = gCurrentObject->oMoveAngleYaw;
    UNUSED u8 unused2[4];

    // Speed up the star every frame
    if (gCurrentObject->oUnlockDoorStarYawVel < 0x2400) {
        gCurrentObject->oUnlockDoorStarYawVel += 0x60;
    }
    switch (gCurrentObject->oUnlockDoorStarState) {
        case UNLOCK_DOOR_STAR_RISING:
            gCurrentObject->oPosY += 3.4f; // Raise the star up in the air
            gCurrentObject->oMoveAngleYaw +=
                gCurrentObject->oUnlockDoorStarYawVel; // Apply yaw velocity
            obj_scale(gCurrentObject, gCurrentObject->oUnlockDoorStarTimer / 50.0f
                                             + 0.5f); // Scale the star to be bigger
            if (++gCurrentObject->oUnlockDoorStarTimer == 30) {
                gCurrentObject->oUnlockDoorStarTimer = 0;
                gCurrentObject->oUnlockDoorStarState++; // Sets state to UNLOCK_DOOR_STAR_WAITING
            }
            break;
        case UNLOCK_DOOR_STAR_WAITING:
            gCurrentObject->oMoveAngleYaw +=
                gCurrentObject->oUnlockDoorStarYawVel; // Apply yaw velocity
            if (++gCurrentObject->oUnlockDoorStarTimer == 30) {
                play_sound(SOUND_MENU_STAR_SOUND,
                           gCurrentObject->header.gfx.cameraToObject); // Play final sound
                cur_obj_hide();                                            // Hide the object
                gCurrentObject->oUnlockDoorStarTimer = 0;
                gCurrentObject
                    ->oUnlockDoorStarState++; // Sets state to UNLOCK_DOOR_STAR_SPAWNING_PARTICLES
            }
            break;
        case UNLOCK_DOOR_STAR_SPAWNING_PARTICLES:
            // Spawn two particles, opposite sides of the star.
            star_door_unlock_spawn_particles(0);
            star_door_unlock_spawn_particles(0x8000);
            if (gCurrentObject->oUnlockDoorStarTimer++ == 20) {
                gCurrentObject->oUnlockDoorStarTimer = 0;
                gCurrentObject->oUnlockDoorStarState++; // Sets state to UNLOCK_DOOR_STAR_DONE
            }
            break;
        case UNLOCK_DOOR_STAR_DONE: // The object stays loaded for an additional 50 frames so that the
                                    // sound doesn't immediately stop.
            if (gCurrentObject->oUnlockDoorStarTimer++ == 50) {
                obj_mark_for_deletion(gCurrentObject);
            }
            break;
    }
    // Checks if the angle has cycled back to 0.
    // This means that the code will execute when the star completes a full revolution.
    if (prevYaw > (s16) gCurrentObject->oMoveAngleYaw) {
        play_sound(
            SOUND_GENERAL_SHORT_STAR,
            gCurrentObject->header.gfx.cameraToObject); // Play a sound every time the star spins once
    }
}

/**
 * Generate a display list that sets the correct blend mode and color for mirror Mario.
 */
static Gfx *make_gfx_mario_alpha(struct GraphNodeGenerated *node, s16 alpha) {
    Gfx *gfx;
    Gfx *gfxHead = NULL;

    if (alpha == 255) {
        node->fnNode.node.flags = (node->fnNode.node.flags & 0xFF) | (LAYER_OPAQUE << 8);
        gfxHead = alloc_display_list(2 * sizeof(*gfxHead));
        if (gfxHead == NULL) { return NULL; }
        gfx = gfxHead;
    } else {
        node->fnNode.node.flags = (node->fnNode.node.flags & 0xFF) | (LAYER_TRANSPARENT << 8);
        gfxHead = alloc_display_list(3 * sizeof(*gfxHead));
        if (gfxHead == NULL) { return NULL; }
        gfx = gfxHead;
        gDPSetAlphaCompare(gfx++, G_AC_DITHER);
    }
    gDPSetEnvColor(gfx++, 255, 255, 255, alpha);
    gSPEndDisplayList(gfx);
    return gfxHead;
}

static u8 geo_get_processing_object_index(void) {
    // sloppy way to fix mirror marios
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if ((struct GraphNodeObject*)gCurGraphNodeObject == &gMirrorMario[i]) {
            return i;
        }
    }
    if (gCurGraphNodeProcessingObject == NULL) { return 0; }

    struct NetworkPlayer* np = network_player_from_global_index(gCurGraphNodeProcessingObject->globalPlayerIndex);
    u8 index = (np == NULL) ? 0 : np->localIndex;
    return (index >= MAX_PLAYERS) ? 0 : index;
}

struct MarioState *geo_get_mario_state(void) {
    u8 index = geo_get_processing_object_index();
    return &gMarioStates[index];
}

struct MarioBodyState *geo_get_body_state(void) {
    u8 index = geo_get_processing_object_index();
    return &gBodyStates[index];
}

/**
 * Sets the correct blend mode and color for mirror Mario.
 */
Gfx* geo_mirror_mario_set_alpha(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    UNUSED u8 unused1[4];
    Gfx* gfx = NULL;
    struct GraphNodeGenerated* asGenerated = (struct GraphNodeGenerated*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();
    s16 alpha;
    UNUSED u8 unused2[4];

    if (callContext == GEO_CONTEXT_RENDER) {
        alpha = (bodyState->modelState & 0x100) ? (bodyState->modelState & 0xFF) : 255;
        gfx = make_gfx_mario_alpha(asGenerated, alpha);
    }
    return gfx;
}

/**
 * Determines if Mario is standing or running for the level of detail of his model.
 * If Mario is standing still, he is always high poly. If he is running,
 * his level of detail depends on the distance to the camera.
 */
Gfx* geo_switch_mario_stand_run(s32 callContext, struct GraphNode* node, UNUSED Mat4* mtx) {
    struct GraphNodeSwitchCase* switchCase = (struct GraphNodeSwitchCase*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        // assign result. 0 if moving, 1 if stationary.
        switchCase->selectedCase = ((bodyState->action & ACT_FLAG_STATIONARY) == 0);
    }
    return NULL;
}

/**
 * Geo node script that makes Mario blink
 */
Gfx* geo_switch_mario_eyes(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    struct GraphNodeSwitchCase* switchCase = (struct GraphNodeSwitchCase*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();
    s16 blinkFrame;

    if (callContext == GEO_CONTEXT_RENDER) {
        if (bodyState->eyeState == 0) {
            blinkFrame = ((switchCase->numCases * 32 + (gAreaUpdateCounter + geo_get_processing_object_index() * 32)) >> 1) & 0x1F;
            if (blinkFrame < 7) {
                switchCase->selectedCase = gMarioBlinkAnimation[blinkFrame];
            }
            else {
                switchCase->selectedCase = 0;
            }
        }
        else {
            switchCase->selectedCase = bodyState->eyeState - 1;
        }
    }
    return NULL;
}

/**
 * Makes Mario's upper body tilt depending on the rotation stored in his bodyState
 */
Gfx* geo_mario_tilt_torso(s32 callContext, struct GraphNode* node, Mat4* mtx) {
    Mat4 * curTransform = mtx;
    u8 plrIdx = geo_get_processing_object_index();
    struct MarioBodyState* bodyState = &gBodyStates[plrIdx];
    s32 action = bodyState->action;
    bodyState->mirrorMario = gCurGraphNodeObject == &gMirrorMario[plrIdx];

    u8 charIndex = gNetworkPlayers[plrIdx].overrideModelIndex;
    if (charIndex >= CT_MAX) { charIndex = 0; }
    struct Character* character = &gCharacters[charIndex];

    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation* rotNode = (struct GraphNodeRotation*) node->next;

        if (action != ACT_BUTT_SLIDE && action != ACT_HOLD_BUTT_SLIDE && action != ACT_WALKING && action != ACT_RIDING_SHELL_GROUND
        && !bodyState->allowPartRotation) {
            vec3s_copy(bodyState->torsoAngle, gVec3sZero);
        }
        rotNode->rotation[0] = bodyState->torsoAngle[1] * character->torsoRotMult;
        rotNode->rotation[1] = bodyState->torsoAngle[2] * character->torsoRotMult;
        rotNode->rotation[2] = bodyState->torsoAngle[0] * character->torsoRotMult;
        if (plrIdx != 0) {
            // only interpolate angles for the local player
            vec3s_copy(rotNode->prevRotation, rotNode->rotation);
            rotNode->prevTimestamp = gGlobalTimer;
        }
        // update torso position in bodyState
        get_pos_from_transform_mtx(bodyState->torsoPos, *curTransform, *gCurGraphNodeCamera->matrixPtr);
        bodyState->updateTorsoTime = gGlobalTimer;
    }
    return NULL;
}

/**
 * Makes Mario's head rotate with the camera angle when in C-up mode
 */
Gfx* geo_mario_head_rotation(s32 callContext, struct GraphNode* node, Mat4* c) {
    u8 plrIdx = geo_get_processing_object_index();
    struct MarioBodyState* bodyState = &gBodyStates[plrIdx];
    s32 action = bodyState->action;
    bodyState->mirrorMario = gCurGraphNodeObject == &gMirrorMario[plrIdx];

    bool marioActive = gMarioObjects[plrIdx] != NULL && gMarioObjects[plrIdx]->activeFlags != ACTIVE_FLAG_DEACTIVATED;

    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation* rotNode = (struct GraphNodeRotation*) node->next;
        struct Camera* camera = gCurGraphNodeCamera->config.camera;

        if (!marioActive) {
            node->flags &= ~GRAPH_RENDER_ACTIVE;
        } else if (((plrIdx == 0) && (camera->mode == CAMERA_MODE_C_UP)) || ((plrIdx != 0) && (action == ACT_FIRST_PERSON))) {
            rotNode->rotation[0] = gPlayerCameraState[plrIdx].headRotation[1];
            rotNode->rotation[2] = gPlayerCameraState[plrIdx].headRotation[0];
        }
        else if (action & ACT_FLAG_WATER_OR_TEXT || bodyState->allowPartRotation) {
            rotNode->rotation[0] = bodyState->headAngle[1];
            rotNode->rotation[1] = bodyState->headAngle[2];
            rotNode->rotation[2] = bodyState->headAngle[0];
        } else {
            vec3s_set(bodyState->headAngle, 0, 0, 0);
            vec3s_set(rotNode->rotation, 0, 0, 0);
        }

        if (plrIdx != 0) {
            // only interpolate angles for the local player
            vec3s_copy(rotNode->prevRotation, rotNode->rotation);
            rotNode->prevTimestamp = gGlobalTimer;
        }

        // update head position in bodyState
        get_pos_from_transform_mtx(bodyState->headPos,
                                   *c,
                                   *gCurGraphNodeCamera->matrixPtr);
        bodyState->updateHeadPosTime = gGlobalTimer;
    }
    return NULL;
}

/**
 * Switch between hand models.
 * Possible options are described in the MarioHandGSCId enum.
 */
Gfx* geo_switch_mario_hand(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    struct GraphNodeSwitchCase* switchCase = (struct GraphNodeSwitchCase*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        if (bodyState->handState == MARIO_HAND_FISTS) {
            // switch between fists (0) and open (1)
            switchCase->selectedCase = ((bodyState->action & ACT_FLAG_SWIMMING_OR_FLYING) != 0);
        }
        else {
            if (switchCase->numCases == 0) {
                switchCase->selectedCase =
                    (bodyState->handState < 5) ? bodyState->handState : MARIO_HAND_OPEN;
            }
            else {
                switchCase->selectedCase =
                    (bodyState->handState < 2) ? bodyState->handState : MARIO_HAND_FISTS;
            }
        }
    }
    return NULL;
}

/**
 * Increase Mario's hand / foot size when he punches / kicks.
 * Since animation geo nodes only support rotation, this scaling animation
 * was scripted separately. The node with this script should be placed before
 * a scaling node containing the hand / foot geo layout.
 * ! Since the animation gets updated in GEO_CONTEXT_RENDER, drawing Mario multiple times
 * (such as in the mirror room) results in a faster and desynced punch / kick animation.
 */
Gfx* geo_mario_hand_foot_scaler(s32 callContext, struct GraphNode* node, Mat4* mtx) {
    Mat4 * curTransform = mtx;
    static s16 sMarioAttackAnimCounter[MAX_PLAYERS] = { 0 };
    struct GraphNodeGenerated* asGenerated = (struct GraphNodeGenerated*) node;
    struct GraphNodeScale* scaleNode = (struct GraphNodeScale*) node->next;
    u8 index = geo_get_processing_object_index();
    struct MarioBodyState* bodyState = geo_get_body_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        scaleNode->scale = 1.0f;
        if (asGenerated->parameter == bodyState->punchState >> 6) {
            if (sMarioAttackAnimCounter[index] != gAreaUpdateCounter && (bodyState->punchState & 0x3F) > 0) {
                bodyState->punchState -= 1;
                sMarioAttackAnimCounter[index] = gAreaUpdateCounter;
            }
            scaleNode->scale =
                gMarioAttackScaleAnimation[asGenerated->parameter * 6 + (bodyState->punchState & 0x3F)]
                / 10.0f;
        }
        // update hand/foot position in bodyState
        get_pos_from_transform_mtx(bodyState->handFootPos[(asGenerated->parameter & 0x03)],
                                   *curTransform,
                                   *gCurGraphNodeCamera->matrixPtr);

    }
    return NULL;
}

/**
 * Switch between normal cap, wing cap, vanish cap and metal cap.
 */
Gfx* geo_switch_mario_cap_effect(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    struct GraphNodeSwitchCase* switchCase = (struct GraphNodeSwitchCase*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        switchCase->selectedCase = bodyState->modelState >> 8;
    }
    return NULL;
}

/**
 * Determine whether Mario's head is drawn with or without a cap on.
 * Also sets the visibility of the wing cap wings on or off.
 */
Gfx* geo_switch_mario_cap_on_off(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    if (!node) { return NULL; }
    struct GraphNode* next = node->next;
    struct GraphNodeSwitchCase* switchCase = (struct GraphNodeSwitchCase*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        if (switchCase == NULL || bodyState == NULL) { return NULL; }
        switchCase->selectedCase = bodyState->capState & 1;
        while (next && (next != node)) {
            if (next->type == GRAPH_NODE_TYPE_TRANSLATION_ROTATION) {
                if (bodyState->capState & 2) {
                    next->flags |= GRAPH_RENDER_ACTIVE;
                }
                else {
                    next->flags &= ~GRAPH_RENDER_ACTIVE;
                }
            }
            next = next->next;
        }
    }
    return NULL;
}

/**
 * Geo node script that makes the wings on Mario's wing cap flap.
 * Should be placed before a rotation node.
 */
Gfx* geo_mario_rotate_wing_cap_wings(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    s16 rotX;
    struct GraphNodeGenerated* asGenerated = (struct GraphNodeGenerated*) node;
    struct MarioBodyState* bodyState = geo_get_body_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        struct GraphNodeRotation* rotNode = (struct GraphNodeRotation*) node->next;

        if (!bodyState->wingFlutter) {
            rotX = (coss((gAreaUpdateCounter & 0xF) << 12) + 1.0f) * 4096.0f;
        } else {
            rotX = (coss((gAreaUpdateCounter & 7) << 13) + 1.0f) * 6144.0f;
        }
        if (!(asGenerated->parameter & 1)) {
            rotNode->rotation[0] = -rotX;
        } else {
            rotNode->rotation[0] = rotX;
        }
    }
    return NULL;
}

/**
 * Geo node that updates the held object node and the HOLP.
 */
Gfx* geo_switch_mario_hand_grab_pos(s32 callContext, struct GraphNode* b, Mat4* mtx) {
    struct GraphNodeHeldObject* asHeldObj = (struct GraphNodeHeldObject*) b;
    Mat4* curTransform = mtx;
    struct MarioState* marioState = geo_get_mario_state();

    if (callContext == GEO_CONTEXT_RENDER) {
        asHeldObj->objNode = NULL;
        if (marioState->heldObj != NULL) {
            asHeldObj->objNode = marioState->heldObj;
            switch (marioState->marioBodyState->grabPos) {
            case GRAB_POS_LIGHT_OBJ:
                if (marioState->action & ACT_FLAG_THROWING) {
                    vec3s_set(asHeldObj->translation, 50, 0, 0);
                }
                else {
                    vec3s_set(asHeldObj->translation, 50, 0, 110);
                }
                break;
            case GRAB_POS_HEAVY_OBJ:
                vec3s_set(asHeldObj->translation, 145, -173, 180);
                break;
            case GRAB_POS_BOWSER:
                vec3s_set(asHeldObj->translation, 80, -270, 1260);
                break;
            }
        }
    }
    else if (callContext == GEO_CONTEXT_HELD_OBJ) {
        // ! The HOLP is set here, which is why it only updates when the held object is drawn.
        // This is why it won't update during a pause buffered hitstun or when the camera is very far
        // away.
        get_pos_from_transform_mtx(marioState->marioBodyState->heldObjLastPosition, *curTransform,
            (f32(*)[4])gCurGraphNodeCamera->matrixPtr);
    }
    return NULL;
}

// X position of the mirror
#define MIRROR_X 4331.53

/**
 * Geo node that creates a clone of Mario's geo node and updates it to becomes
 * a mirror image of the player.
 */
Gfx* geo_render_mirror_mario(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        f32 mirroredX;
        struct MarioState* marioState = &gMarioStates[i];
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        struct Object* mario = marioState->marioObj;

        switch (callContext) {
            case GEO_CONTEXT_CREATE:
                init_graph_node_object(NULL, &gMirrorMario[i], NULL, gVec3fZero, gVec3sZero, gVec3fOne);
                break;
            case GEO_CONTEXT_AREA_LOAD:
                geo_add_child(node, &gMirrorMario[i].node);
                break;
            case GEO_CONTEXT_AREA_UNLOAD:
                geo_remove_child_from_parent(node, &gMirrorMario[i].node);
                break;
            case GEO_CONTEXT_RENDER:
                if (mario && (((struct GraphNode*)&mario->header.gfx)->flags & GRAPH_RENDER_ACTIVE) && np->connected) {
                    // TODO: Is this a geo layout copy or a graph node copy?
                    gMirrorMario[i].sharedChild = mario->header.gfx.sharedChild;
                    dynos_actor_override(mario, (void*)&gMirrorMario[i].sharedChild);
                    gMirrorMario[i].areaIndex = mario->header.gfx.areaIndex;
                    vec3s_copy(gMirrorMario[i].angle, mario->header.gfx.angle);
                    vec3f_copy(gMirrorMario[i].pos, mario->header.gfx.pos);
                    vec3f_copy(gMirrorMario[i].scale, mario->header.gfx.scale);

                    dynos_gfx_swap_animations(mario);
                    gMirrorMario[i].animInfo = mario->header.gfx.animInfo;
                    dynos_gfx_swap_animations(mario);

                    mirroredX = MIRROR_X - gMirrorMario[i].pos[0];
                    gMirrorMario[i].pos[0] = mirroredX + MIRROR_X;
                    gMirrorMario[i].angle[1] = -gMirrorMario[i].angle[1];
                    gMirrorMario[i].scale[0] *= -1.0f;
                    gMirrorMario[i].node.flags |= GRAPH_RENDER_ACTIVE;

                    smlua_call_event_hooks_graph_node_object_and_int_param(HOOK_MIRROR_MARIO_RENDER, &gMirrorMario[i], i);
                } else {
                    gMirrorMario[i].node.flags &= ~GRAPH_RENDER_ACTIVE;
                }
                break;
        }
    }
    return NULL;
}

/**
 * Since Mirror Mario has an x scale of -1, the mesh becomes inside out.
 * This node corrects that by changing the culling mode accordingly.
 */
Gfx* geo_mirror_mario_backface_culling(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    struct GraphNodeGenerated* asGenerated = (struct GraphNodeGenerated*) node;
    Gfx* gfx = NULL;

    u8 isMirrorMario = FALSE;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (gCurGraphNodeObject == &gMirrorMario[i]) {
            isMirrorMario = TRUE;
        }
    }

    if (callContext == GEO_CONTEXT_RENDER && isMirrorMario) {
        gfx = alloc_display_list(3 * sizeof(*gfx));
        if (gfx == NULL) { return NULL; }

        if ((asGenerated->parameter & 0x01) == 0) {
            gSPClearGeometryMode(&gfx[0], G_CULL_BACK);
            gSPSetGeometryMode(&gfx[1], G_CULL_FRONT);
            gSPEndDisplayList(&gfx[2]);
        } else {
            gSPClearGeometryMode(&gfx[0], G_CULL_FRONT);
            gSPSetGeometryMode(&gfx[1], G_CULL_BACK);
            gSPEndDisplayList(&gfx[2]);
        }

        u32 layer = ((asGenerated->parameter & 0x02) == 2) ? LAYER_TRANSPARENT : LAYER_OPAQUE;
        if ((asGenerated->parameter & 0xFC) != 0) {
            layer = asGenerated->parameter >> 2;
        }
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (layer << 8);
    }
    return gfx;
}

static struct PlayerColor geo_mario_get_player_color(const struct PlayerPalette *palette) {
    struct PlayerColor color = { 0 };
    u8 index = geo_get_processing_object_index();
    struct MarioBodyState* bodyState = &gBodyStates[index];
    for (s32 part = 0; part != PLAYER_PART_MAX; ++part) {
        color.parts[part] = (Lights1) gdSPDefLights1(
            // Shadow
            palette->parts[part][0] * bodyState->shadeR / 255.0f,
            palette->parts[part][1] * bodyState->shadeG / 255.0f,
            palette->parts[part][2] * bodyState->shadeB / 255.0f,
            // Light
            palette->parts[part][0] * bodyState->lightR / 255.0f,
            palette->parts[part][1] * bodyState->lightG / 255.0f,
            palette->parts[part][2] * bodyState->lightB / 255.0f,
            0x28 + bodyState->lightingDirX * 127.0f, 0x28 + bodyState->lightingDirY * 127.0f, 0x28 + bodyState->lightingDirZ * 127.0f
        );
    }
    return color;
}

static Gfx *geo_mario_create_player_colors_dl(s32 index, Gfx *capEnemyGfx, Gfx *capEnemyDecalGfx) {
    s32 size = ((PLAYER_PART_MAX * 2) + 1) + (capEnemyGfx != NULL) + (capEnemyDecalGfx != NULL);
    Gfx *gfx = alloc_display_list(size * sizeof(Gfx));
    if (gfx) {
        Gfx *gfxp = gfx;
        for (s32 part = 0; part != PLAYER_PART_MAX; ++part) {
            gSPLight(gfxp++, &gNetworkPlayerColors[index].parts[part].l, (2 * (part + 1)) + 1);
            gSPLight(gfxp++, &gNetworkPlayerColors[index].parts[part].a, (2 * (part + 1)) + 2);
        }
        if (capEnemyGfx) { gSPDisplayList(gfxp++, capEnemyGfx); }
        if (capEnemyDecalGfx) { gSPDisplayList(gfxp++, capEnemyDecalGfx); }
        gSPEndDisplayList(gfxp);
    }
    return gfx;
}

/**
 * Generate DL that sets player color depending on player number.
 */
Gfx* geo_mario_set_player_colors(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    struct GraphNodeGenerated* asGenerated = (struct GraphNodeGenerated*) node;
    Gfx* gfx = NULL;
    u8 index = geo_get_processing_object_index();

    struct PlayerColor color = geo_mario_get_player_color(&gNetworkPlayers[index].overridePalette);
    gNetworkPlayerColors[index] = color;

    struct MarioBodyState* bodyState = &gBodyStates[index];
    bodyState->mirrorMario = gCurGraphNodeObject == &gMirrorMario[index];

    if (callContext == GEO_CONTEXT_RENDER) {
        gfx = geo_mario_create_player_colors_dl(index, NULL, NULL);
        u32 layer = LAYER_OPAQUE;
        if (asGenerated->parameter == 0) {
            // put on transparent layer if vanish effect, opaque otherwise
            layer = ((bodyState->modelState >> 8) & 1) ? LAYER_TRANSPARENT : LAYER_OPAQUE;
        } else if (asGenerated->parameter == 1) {
            layer = LAYER_OPAQUE;
        } else if (asGenerated->parameter == 2) {
            layer = LAYER_TRANSPARENT;
        } else if (asGenerated->parameter >= 3) {
            layer = asGenerated->parameter - 3;
        }
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (layer << 8);
    }
    return gfx;
}

Gfx* geo_mario_cap_display_list(s32 callContext, struct GraphNode* node, UNUSED Mat4* c) {
    if (callContext != GEO_CONTEXT_RENDER) { return NULL; }
    u8 globalIndex = geo_get_processing_object_index();

    struct PlayerColor color = geo_mario_get_player_color(&gNetworkPlayers[globalIndex].overridePalette);
    gNetworkPlayerColors[globalIndex] = color;

    u8 charIndex = gNetworkPlayers[globalIndex].overrideModelIndex;
    if (charIndex >= CT_MAX) { charIndex = 0; }
    struct Character* character = &gCharacters[charIndex];

    Gfx *gfx = geo_mario_create_player_colors_dl(globalIndex, character->capEnemyGfx, character->capEnemyDecalGfx);
    struct GraphNodeGenerated* asGenerated = (struct GraphNodeGenerated*)node;
    asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (character->capEnemyLayer << 8);
    return gfx;
}

Gfx *geo_process_lua_function(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c) {
    extern s16 gMatStackIndex;
    lua_State *L = gLuaState;
    if (!L) { return NULL; }

    // Do nothing outside of geo_process
    if (callContext != GEO_CONTEXT_RENDER) {
        return NULL;
    }

    // Check node type
    if (!node || !(node->type & GRAPH_NODE_TYPE_FUNCTIONAL)) {
        return NULL;
    }
    struct FnGraphNode *fnNode = (struct FnGraphNode *) node;
    struct GraphNode *sharedChild = geo_find_shared_child(node);

    // Retrieve mod index and function name
    s32 modIndex = -1;
    const char *funcStr = NULL;
    if (!dynos_actor_get_mod_index_and_token(sharedChild, fnNode->luaTokenIndex, &modIndex, &funcStr)) {
        if (modIndex == -1) {
            LOG_ERROR("Could not find graph node mod index");
        } else if (funcStr == NULL) {
            LOG_ERROR("Could not find graph node function name");
        }
        return NULL;
    }

    // Retrieve function ref
    gSmLuaConvertSuccess = true;
    LuaFunction funcRef = smlua_get_function_mod_variable(modIndex, funcStr);
    if (!gSmLuaConvertSuccess) {
        gSmLuaConvertSuccess = true;
        funcRef = smlua_get_any_function_mod_variable(funcStr);
    }
    if (!gSmLuaConvertSuccess || funcRef == 0) {
        LOG_LUA("Failed to call lua function, could not find lua function '%s'", funcStr);
        return NULL;
    }

    // Get the mod
    if (modIndex >= gActiveMods.entryCount) {
        LOG_LUA("Failed to call lua function, could not find mod");
        return NULL;
    }
    struct Mod *mod = gActiveMods.entries[modIndex];

    // Push the callback, the graph node and the current matrix stack index
    lua_rawgeti(L, LUA_REGISTRYINDEX, funcRef);
    smlua_push_object(L, LOT_GRAPHNODE, node, NULL);
    lua_pushinteger(L, gMatStackIndex);

    // Call the callback
    if (0 != smlua_call_hook(L, 2, 0, 0, mod)) {
        LOG_LUA("Failed to call the function callback: '%s'", funcStr);
    }

    return NULL;
}
