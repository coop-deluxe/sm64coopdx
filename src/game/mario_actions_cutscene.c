#include <PR/ultratypes.h>

#include "prevent_bss_reordering.h"
#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_data.h"
#include "camera.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "mario.h"
#include "mario_actions_moving.h"
#include "mario_step.h"
#include "moving_texture.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "save_file.h"
#include "seq_ids.h"
#include "sound_init.h"
#include "rumble_init.h"
#include "obj_behaviors.h"
#include "hardcoded.h"
#include "../../include/libc/stdlib.h"
#include "pc/debuglog.h"
#include "pc/pc_main.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/lua/smlua.h"
#include "pc/lua/smlua_hooks.h"

// TODO: put this elsewhere
enum SaveOption { SAVE_OPT_SAVE_AND_CONTINUE = 1, /*SAVE_OPT_SAVE_AND_QUIT, SAVE_OPT_SAVE_EXIT_GAME,*/ SAVE_OPT_CONTINUE_DONT_SAVE };

static struct Object* sIntroWarpPipeObj[MAX_PLAYERS] = { 0 };
static struct Object *sEndPeachObj;
static struct Object *sEndRightToadObj;
static struct Object *sEndLeftToadObj;
static struct Object *sEndJumboStarObj;
static UNUSED s32 sUnused;
static s16 sEndPeachAnimation;
static s16 sEndToadAnims[2];

static Vp sEndCutsceneVp = { { { 640, 480, 511, 0 }, { 640, 480, 511, 0 } } };
static struct CreditsEntry *sDispCreditsEntry = NULL;

// related to peach gfx?
static s8 D_8032CBE4 = 0;
static s8 D_8032CBE8 = 0;
static s8 D_8032CBEC[7] = { 2, 3, 2, 1, 2, 3, 2 };

extern u8 gLastCollectedStarOrKey;

static BehaviorScript* localDialogNPCBehavior = NULL;

/**
 * Data for the jumbo star cutscene. It specifies the flight path after triple
 * jumping. Each entry is one keyframe.
 * The first number is playback speed, 1000 is the maximum and means it lasts
 * 1 frame. 20 means that it lasts 1000/20 = 50 frames.
 * Speed 0 marks the last keyframe. Since the cubic spline looks 3 keyframes
 * ahead, there should be at least 2 more entries afterwards.
 * The last three numbers of each entry are x, y and z coordinates of points
 * that define the curve.
 */
static Vec4s sJumboStarKeyframes[27] = {
    { 20, 0, 678, -2916 },      { 30, 0, 680, -3500 },      { 40, 1000, 700, -4000 },
    { 50, 2500, 750, -3500 },   { 50, 3500, 800, -2000 },   { 50, 4000, 850, 0 },
    { 50, 3500, 900, 2000 },    { 50, 2000, 950, 3500 },    { 50, 0, 1000, 4000 },
    { 50, -2000, 1050, 3500 },  { 50, -3500, 1100, 2000 },  { 50, -4000, 1150, 0 },
    { 50, -3500, 1200, -2000 }, { 50, -2000, 1250, -3500 }, { 50, 0, 1300, -4000 },
    { 50, 2000, 1350, -3500 },  { 50, 3500, 1400, -2000 },  { 50, 4000, 1450, 0 },
    { 50, 3500, 1500, 2000 },   { 50, 2000, 1600, 3500 },   { 50, 0, 1700, 4000 },
    { 50, -2000, 1800, 3500 },  { 50, -3500, 1900, 2000 },  { 30, -4000, 2000, 0 },
    { 0, -3500, 2100, -2000 },  { 0, -2000, 2200, -3500 },  { 0, 0, 2300, -4000 },
};

/**
 * get_credits_str_width: Calculate width of a Credits String
 * Loop over each character in a credits string and increment the length. If the
 * character is a space, increment by 4; otherwise increment by 7. Once the next
 * character is a null character (equal to 0), stop counting the length since
 * that's the end of the string.
 */
s32 get_credits_str_width(char *str) {
    if (!str) { return 0; }
    u32 c;
    s32 length = 0;

    while ((c = *str++) != 0) {
        length += (c == ' ' ? 4 : 7);
    }

    return length;
}

#define CREDIT_TEXT_MARGIN_X ((s32)(GFX_DIMENSIONS_ASPECT_RATIO * 21))
#define CREDIT_TEXT_X_LEFT GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(CREDIT_TEXT_MARGIN_X)
#define CREDIT_TEXT_X_RIGHT GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(CREDIT_TEXT_MARGIN_X)

/**
 * print_displaying_credits_entry: Print the current displaying Credits Entry
 * Called in render_game. This function checks if sDispCreditsEntry points to a
 * credits entry (see act_credits_cutscene), and if so, display it. The reason
 * this is called every frame in render_game is because the credits need to
 * display on top of everything else.
 * To print a credits entry, we take the first character of the first string,
 * subtract the value of the 0 character, and use that as the number of lines to
 * print, excluding the title. Then, we print the title (after advancing the
 * pointer by 1) at X 28, Y either 28 or 172, depending on the print at bottom
 * flag. Finally, we print each line using the number of lines previously stored
 * as a counter, and increase the Y value by either the constant 16 (JP only) or
 * by the value of lineHeight.
 */
void print_displaying_credits_entry(void) {
    char **currStrPtr;
    char *titleStr;
    s16 numLines;
    s16 strY;
#ifndef VERSION_JP
    s16 lineHeight;
#endif

    if (sDispCreditsEntry != NULL) {
        currStrPtr = (char **) sDispCreditsEntry->unk0C;
        titleStr = *currStrPtr++;
        numLines = *titleStr++ - '0';

        strY = (sDispCreditsEntry->unk02 & 0x20 ? 28 : 172) + (numLines == 1) * 16;
#ifndef VERSION_JP
        lineHeight = 16;
#endif

        dl_rgba16_begin_cutscene_msg_fade();
        print_credits_str_ascii(CREDIT_TEXT_X_LEFT, strY, titleStr);

#ifndef VERSION_JP
        switch (numLines) {
            case 4:
                print_credits_str_ascii(CREDIT_TEXT_X_LEFT, strY + 24, *currStrPtr++);
                numLines = 2;
                lineHeight = 24;
                break;
            case 5:
                print_credits_str_ascii(CREDIT_TEXT_X_LEFT, strY + 16, *currStrPtr++);
                numLines = 3;
                break;
#ifdef VERSION_EU
            case 6:
                print_credits_str_ascii(CREDIT_TEXT_X_LEFT, strY + 32, *currStrPtr++);
                numLines = 3;
                break;
            case 7:
                print_credits_str_ascii(CREDIT_TEXT_X_LEFT, strY + 16, *currStrPtr++);
                print_credits_str_ascii(CREDIT_TEXT_X_LEFT, strY + 32, *currStrPtr++);
                numLines = 3;
                break;
#endif
        }
#endif

        while (numLines-- > 0) {
            print_credits_str_ascii(CREDIT_TEXT_X_RIGHT - get_credits_str_width(*currStrPtr), strY, *currStrPtr);

#ifdef VERSION_JP
            strY += 16;
#else
            strY += lineHeight;
#endif

            currStrPtr++;
        }

        dl_rgba16_stop_cutscene_msg_fade();
        sDispCreditsEntry = NULL;
    }
}

void bhv_end_peach_loop(void) {
    cur_obj_init_animation_with_sound(sEndPeachAnimation);
    if (cur_obj_check_if_near_animation_end()) {
        // anims: 0-3, 4, 5, 6-8, 9, 10, 11
        if (sEndPeachAnimation < 3 || sEndPeachAnimation == 6 || sEndPeachAnimation == 7) {
            sEndPeachAnimation++;
        }
    }
}

void bhv_end_toad_loop(void) {
    if (!gCurrentObject) { return; }
    s32 toadAnimIndex = (gCurrentObject->oPosX >= 0.0f);

    cur_obj_init_animation_with_sound(sEndToadAnims[toadAnimIndex]);
    if (cur_obj_check_if_near_animation_end()) {
        // 0-1, 2-3, 4, 5, 6, 7
        if (sEndToadAnims[toadAnimIndex] == 0 || sEndToadAnims[toadAnimIndex] == 2) {
            sEndToadAnims[toadAnimIndex]++;
        }
    }
}

// Geo switch case function for controlling Peach's eye state.
s32 geo_switch_peach_eyes(s32 run, struct GraphNode *node, UNUSED s32 a2) {
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;

    if (run == TRUE) {
        if (D_8032CBE4 == 0) {
            s16 timer = (gAreaUpdateCounter + 0x20) >> 1 & 0x1F;
            if (timer < 7) {
                switchCase->selectedCase = D_8032CBE8 * 4 + D_8032CBEC[timer];
            } else {
                switchCase->selectedCase = D_8032CBE8 * 4 + 1;
            }
        } else {
            switchCase->selectedCase = D_8032CBE8 * 4 + D_8032CBE4 - 1;
        }
    }

    return 0;
}

// unused
static void stub_is_textbox_active(u16 *a0) {
    if (get_dialog_id() == -1) {
        *a0 = 0;
    }
}

/**
 * get_star_collection_dialog: Determine what dialog should show when Mario
 * collects a star.
 * Determines if Mario has collected enough stars to get a dialog for it, and
 * if so, return the dialog ID. Otherwise, return 0. A dialog is returned if
 * numStars has reached a milestone and prevNumStarsForDialog has not reached it.
 */
s32 get_star_collection_dialog(struct MarioState *m) {
    if (!m) { return 0; }
    s32 dialogID = 0;

    if (smlua_call_event_hooks_ret_int(HOOK_GET_STAR_COLLECTION_DIALOG, &dialogID)) {
        m->prevNumStarsForDialog = m->numStars;
        return dialogID;
    }

    if (!gBehaviorValues.ShowStarMilestones) { return 0; }

    for (s32 i = 0; i < STARS_NEEDED_FOR_DIALOG_COUNT; i++) {
        s32 numStarsRequired = 999;
        switch (i) {
            case 0: numStarsRequired = gBehaviorValues.starsNeededForDialog.dialog1; break;
            case 1: numStarsRequired = gBehaviorValues.starsNeededForDialog.dialog2; break;
            case 2: numStarsRequired = gBehaviorValues.starsNeededForDialog.dialog3; break;
            case 3: numStarsRequired = gBehaviorValues.starsNeededForDialog.dialog4; break;
            case 4: numStarsRequired = gBehaviorValues.starsNeededForDialog.dialog5; break;
            case 5: numStarsRequired = gBehaviorValues.starsNeededForDialog.dialog6; break;
        }

        if (m->prevNumStarsForDialog < numStarsRequired && m->numStars >= numStarsRequired) {
            dialogID = i + gBehaviorValues.dialogs.StarCollectionBaseDialog;
            break;
        }
    }

    m->prevNumStarsForDialog = m->numStars;
    return dialogID;
}

// save menu handler
void handle_save_menu(struct MarioState *m) {
    if (!m) { return; }

    // wait for the menu to show up
    if (is_anim_past_end(m) && gSaveOptSelectIndex != 0) {
        // save and continue / save and quit
        if (gSaveOptSelectIndex == SAVE_OPT_SAVE_AND_CONTINUE /*|| gSaveOptSelectIndex == SAVE_OPT_SAVE_EXIT_GAME || gSaveOptSelectIndex == SAVE_OPT_SAVE_AND_QUIT*/) {
            save_file_do_save(gCurrSaveFileNum - 1, FALSE);

            /*if (gSaveOptSelectIndex == SAVE_OPT_SAVE_AND_QUIT) {
                fade_into_special_warp(-2, 0); // reset game
            } else if (gSaveOptSelectIndex == SAVE_OPT_SAVE_EXIT_GAME) {
                //initiate_warp(LEVEL_CASTLE, 1, 0x1F, 0);
                fade_into_special_warp(0, 0);
                game_exit();
            }*/
        }

        // not quitting
        //if (gSaveOptSelectIndex != SAVE_OPT_SAVE_EXIT_GAME) {
            disable_time_stop();
            m->faceAngle[1] += 0x8000;
            // figure out what dialog to show, if we should
            s32 dialogID = get_star_collection_dialog(m);
            if (dialogID != 0) {
                play_peachs_jingle();
                // look up for dialog
                set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, dialogID);
            } else {
                set_mario_action(m, ACT_IDLE, 0);
            }
        //}
    }
}

/**
 * spawn_obj_at_mario_rel_yaw: Spawns object at Mario with relative yaw.
 * Spawns object with given behavior and model and copies over Mario's position
 * and yaw plus relative yaw.
 */
struct Object *spawn_obj_at_mario_rel_yaw(struct MarioState *m, s32 model, const BehaviorScript *behavior, s16 relYaw) {
    if (!m || !behavior) { return NULL; }
    struct Object *o = spawn_object(m->marioObj, model, behavior);
    if (o == NULL) { return NULL; }

    o->oFaceAngleYaw = m->faceAngle[1] + relYaw;
    o->oPosX = m->pos[0];
    o->oPosY = m->pos[1];
    o->oPosZ = m->pos[2];

    return o;
}

/**
 * cutscene_take_cap_off: Put Mario's cap on.
 * Clears "cap on head" flag, sets "cap in hand" flag, plays sound
 * SOUND_ACTION_UNKNOWN43D.
 */
void cutscene_take_cap_off(struct MarioState *m) {
    if (!m) { return; }
    m->flags &= ~MARIO_CAP_ON_HEAD;
    m->flags |= MARIO_CAP_IN_HAND;
    play_sound(SOUND_ACTION_UNKNOWN43D, m->marioObj->header.gfx.cameraToObject);
}

/**
 * cutscene_put_cap_on: Put Mario's cap on.
 * Clears "cap in hand" flag, sets "cap on head" flag, plays sound
 * SOUND_ACTION_UNKNOWN43E.
 */
void cutscene_put_cap_on(struct MarioState *m) {
    if (!m) { return; }
    m->flags &= ~MARIO_CAP_IN_HAND;
    m->flags |= MARIO_CAP_ON_HEAD;
    play_sound(SOUND_ACTION_UNKNOWN43E, m->marioObj->header.gfx.cameraToObject);
    m->cap = 0;
}

/**
 * mario_ready_to_speak: Determine if Mario is able to speak to a NPC
 * The following conditions must be met in order for Mario to be considered
 * ready to speak.
 * 1: Mario's action must be in the stationary or moving action groups, or if
 *    not, he must be in the "waiting for dialog" state.
 * 2: Mario mat not be riding a shell or be invulnerable.
 * 3: Mario must not be in first person mode.
 */
s32 mario_ready_to_speak(struct MarioState* m) {
    if (!m) { return FALSE; }
    u32 actionGroup = m->action & ACT_GROUP_MASK;
    s32 isReadyToSpeak = FALSE;

    if ((m->action == ACT_WAITING_FOR_DIALOG || actionGroup == ACT_GROUP_STATIONARY
         || actionGroup == ACT_GROUP_MOVING)
        && (!(m->action & (ACT_FLAG_RIDING_SHELL | ACT_FLAG_INVULNERABLE))
            && m->action != ACT_FIRST_PERSON)) {
        isReadyToSpeak = TRUE;
    }

    return isReadyToSpeak;
}

u8 should_start_or_continue_dialog(struct MarioState* m, struct Object* object) {
    if (!m) { return FALSE; }
    if (!m->visibleToEnemies) { return FALSE; }
    if (m->playerIndex == 0) { return TRUE; }
    return (gContinueDialogFunctionObject == object);
}

// (can) place Mario in dialog?
// initiate dialog?
// return values:
// 0 = not in dialog
// 1 = starting dialog
// 2 = speaking
s32 set_mario_npc_dialog(struct MarioState* m, s32 actionArg, u8 (*inContinueDialogFunction)(void)) {
    if (!m) { return 0; }

    s32 dialogState = 0;

    if (m->playerIndex == 0) {
        if (actionArg == 0 || inContinueDialogFunction == NULL) {
            localDialogNPCBehavior = NULL;
            gContinueDialogFunction = NULL;
            gContinueDialogFunctionObject = NULL;
        } else {
            gContinueDialogFunction = inContinueDialogFunction;
            gContinueDialogFunctionObject = gCurrentObject;
        }
    }

    // in dialog
    if (m->action == ACT_READING_NPC_DIALOG) {
        if (m->actionState < 8) {
            dialogState = 1; // starting dialog
        }
        if (m->actionState == 8) {
            if (actionArg == 0) {
                m->actionState++; // exit dialog
            } else {
                dialogState = 2;
            }
        }
    } else if (actionArg != 0 && mario_ready_to_speak(m)) {
        m->usedObj = gCurrentObject;
        set_mario_action(m, ACT_READING_NPC_DIALOG, actionArg);
        if (m->playerIndex == 0 && m->usedObj != NULL) { localDialogNPCBehavior = (BehaviorScript*)m->usedObj->behavior; }
        dialogState = 1; // starting dialog
    }

    return dialogState;
}

// actionargs:
// 1 : no head turn
// 2 : look up
// 3 : look down
// actionstate values:
// 0 - 7: looking toward npc
// 8: in dialog
// 9 - 22: looking away from npc
// 23: end
s32 act_reading_npc_dialog(struct MarioState *m) {
    if (!m || !gCurrentObject) { return 23; }
    s32 headTurnAmount = 0;
    s16 angleToNPC;

    if (m->playerIndex == 0) {
        u8 continueDialogCallback = TRUE;
        if (gContinueDialogFunction != NULL && gContinueDialogFunctionObject != NULL) {
            struct Object* tmp = gCurrentObject;
            gCurrentObject = gContinueDialogFunctionObject;
            continueDialogCallback = gContinueDialogFunction();
            gCurrentObject = tmp;
        }
        if (!continueDialogCallback || m->usedObj == NULL || m->usedObj->activeFlags == ACTIVE_FLAG_DEACTIVATED || m->usedObj->behavior != smlua_override_behavior(localDialogNPCBehavior)) {
            set_mario_npc_dialog(m, 0, NULL);
        }
    }

    if (m->actionArg == 2) {
        headTurnAmount = -1024;
    }
    if (m->actionArg == 3) {
        headTurnAmount = 384;
    }

    if (m->actionState < 8) {
        if (m->usedObj != NULL) {
            // turn to NPC
            angleToNPC = mario_obj_angle_to_object(m, m->usedObj);
            m->faceAngle[1] =
                angleToNPC - approach_s32((angleToNPC - m->faceAngle[1]) << 16 >> 16, 0, 2048, 2048);
            // turn head to npc
            m->actionTimer += headTurnAmount;
        }
        // set animation
        set_character_animation(m, m->heldObj == NULL ? CHAR_ANIM_FIRST_PERSON
                                                  : CHAR_ANIM_IDLE_WITH_LIGHT_OBJ);
    } else if (m->actionState >= 9 && m->actionState < 17) {
        // look back from facing NPC
        m->actionTimer -= headTurnAmount;
    } else if (m->playerIndex == 0 && m->actionState == 23) {
        if (m->flags & MARIO_CAP_IN_HAND) {
            set_mario_action(m, ACT_PUTTING_ON_CAP, 0);
        } else {
            set_mario_action(m, m->heldObj == NULL ? ACT_IDLE : ACT_HOLD_IDLE, 0);
        }
    }
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    vec3s_set(m->marioBodyState->headAngle, m->actionTimer, 0, 0);

    if (m->playerIndex == 0 && m->actionState != 8) {
        m->actionState++;
    }

    if (m->playerIndex != 0 && gCurrentObject->header.gfx.animInfo.animID == -1) {
        // set animation
        set_character_animation(m, m->heldObj == NULL ? CHAR_ANIM_FIRST_PERSON
            : CHAR_ANIM_IDLE_WITH_LIGHT_OBJ);
    }

    return FALSE;
}

// puts Mario in a state where he's waiting for (npc) dialog; doesn't do much
s32 act_waiting_for_dialog(struct MarioState *m) {
    set_character_animation(m, m->heldObj == NULL ? CHAR_ANIM_FIRST_PERSON
                                              : CHAR_ANIM_IDLE_WITH_LIGHT_OBJ);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    return FALSE;
}

// makes Mario disappear and triggers warp
s32 act_disappeared(struct MarioState *m) {
    set_character_animation(m, CHAR_ANIM_A_POSE);
    stop_and_set_height_to_floor(m);
    m->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    if (m->actionArg) {
        m->actionArg--;
        if ((m->actionArg & 0xFFFF) == 0) {
            level_trigger_warp(m, m->actionArg >> 16);
        }
    }
    return FALSE;
}

s32 act_reading_automatic_dialog(struct MarioState *m) {
    if (m == NULL) { return TRUE; }

    // Increment our action state to continue our 'cutscene'.
    m->actionState++;

    if (m->actionState == 2) {
        enable_time_stop_if_alone();
    }
    if (m->actionState < 9) {
        set_character_animation(m, m->prevAction == ACT_STAR_DANCE_WATER ? CHAR_ANIM_WATER_IDLE : CHAR_ANIM_FIRST_PERSON);
        // always look up for automatic dialogs
        m->actionTimer -= 1024;
    } else {
        // set Mario dialog
        if (m->actionState == 9) {
            // only show dialog for local player
            if (m->playerIndex == 0) {
                u32 actionArg = m->actionArg;
                if (GET_HIGH_U16_OF_32(actionArg) == 0) {
                    create_dialog_box(GET_LOW_U16_OF_32(actionArg));
                } else {
                    create_dialog_box_with_var(GET_HIGH_U16_OF_32(actionArg), GET_LOW_U16_OF_32(actionArg));
                }
            }
        } else if (m->actionState == 10) { // wait until dialog is done
            if ((m->playerIndex == 0 && get_dialog_id() >= 0) ||
                (m->playerIndex != 0 && m->dialogId != 0)) {
                m->actionState--;
            }
        } else if (m->actionState < 19) { // wait until dialog is done
            m->actionTimer += 1024;
        }  else if (m->actionState == 25) { // finished action
            disable_time_stop();
            if (gNeverEnteredCastle) {
                gNeverEnteredCastle = false;
                play_cutscene_music(SEQUENCE_ARGS(0, SEQ_LEVEL_INSIDE_CASTLE));
            }
            if (m->prevAction == ACT_STAR_DANCE_WATER) {
                set_mario_action(m, ACT_WATER_IDLE, 0); // 100c star?
            } else {
                // make Mario walk into door after star dialog
                set_mario_action(m, m->prevAction == ACT_UNLOCKING_STAR_DOOR ? ACT_WALKING : ACT_IDLE, 0);
            }
        }
    }

    // apply head turn
    vec3s_set(m->marioBodyState->headAngle, m->actionTimer, 0, 0);
    return FALSE;
}

s32 act_reading_sign(struct MarioState *m) {
    if (m == NULL) { return TRUE; }

    struct Object *marioObj = m->marioObj;

    // If anybody but us is reading a sign,
    // Don't handle their action state.
    if (m->playerIndex != 0) {
        set_character_animation(m, CHAR_ANIM_FIRST_PERSON);
        return FALSE;
    }

    play_sound_if_no_flag(m, SOUND_ACTION_READ_SIGN, MARIO_ACTION_SOUND_PLAYED);

    switch (m->actionState) {
        // start dialog
        case 0:
            if (m == &gMarioStates[0]) {
                trigger_cutscene_dialog(1);
            }
            enable_time_stop_if_alone();
            // reading sign
            set_character_animation(m, CHAR_ANIM_FIRST_PERSON);
            m->actionState = 1;
            // intentional fall through
        // turn toward sign
        case 1:
            m->faceAngle[1] += marioObj->oMarioPoleUnk108 / 11;
            m->pos[0] += marioObj->oMarioReadingSignDPosX / 11.0f;
            m->pos[2] += marioObj->oMarioReadingSignDPosZ / 11.0f;
            // create the text box
            if (m->actionTimer++ == 10) {
                if (m == &gMarioStates[0] && m->usedObj != NULL) {
                    create_dialog_inverted_box(m->usedObj->oBehParams2ndByte);
                }
                m->actionState = 2;
            }
            break;
        // in dialog
        case 2:
            // dialog finished
            if (gCamera->cutscene == 0) {
                disable_time_stop();
                set_mario_action(m, ACT_IDLE, 0);
            }
            break;
    }

    vec3f_copy(marioObj->header.gfx.pos, m->pos);
    vec3s_set(marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    return FALSE;
}

s32 act_debug_free_move(struct MarioState *m) {
    if (m == NULL) { return TRUE; }

    u32 action = ACT_IDLE;

#ifndef DEVELOPMENT
    if (m->pos[1] <= m->waterLevel - 100) {
        action = ACT_WATER_IDLE;
    } else {
        action = ACT_FREEFALL;
    }
    set_mario_action(m, action, 0);
    return FALSE;
#endif

    // integer immediates, generates convert instructions for some reason
    f32 speed = gPlayer1Controller->buttonDown & B_BUTTON ? 1 : 4;

    set_character_animation(m, CHAR_ANIM_A_POSE);
    Vec3f pos;
    vec3f_copy(pos, m->pos);

    if (gPlayer1Controller->buttonDown & A_BUTTON) {
        pos[1] += 16.0f * speed;
    }
    if (gPlayer1Controller->buttonDown & Z_TRIG) {
        pos[1] -= 16.0f * speed;
    }

    if (m->intendedMag > 0) {
        pos[0] += 26.0f * speed * sins(m->intendedYaw);
        pos[2] += 26.0f * speed * coss(m->intendedYaw);
    }

    struct WallCollisionData wcd = { 0 };
    resolve_and_return_wall_collisions_data(pos, 60.0f, 50.0f, &wcd);

    struct Surface *surf = NULL;
    f32 floorHeight = find_floor(pos[0], pos[1], pos[2], &surf);
    if (surf != NULL) {
        if (pos[1] < floorHeight) {
            pos[1] = floorHeight;
        }
        vec3f_copy(m->pos, pos);
    }

    m->faceAngle[1] = m->intendedYaw;
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);

    if (gPlayer1Controller->buttonPressed == L_TRIG && m->marioObj->oTimer > 10) {
        if (m->pos[1] <= m->waterLevel - 100) {
            action = ACT_WATER_IDLE;
        }
        set_mario_action(m, action, 0);
    }

    return FALSE;
}

void general_star_dance_handler(struct MarioState *m, s32 isInWater) {
    if (m == NULL) { return; }

    if (m->actionState == 0) {
        switch (++m->actionTimer) {
            case 1:
                for (s32 i = 0; i < MAX_PLAYERS; i++) {
                    struct MarioState* marioState = &gMarioStates[i];
                    if (!is_player_active(marioState)) { continue; }
                    if (marioState->marioObj == NULL) { continue; }
                    if (marioState->playerIndex != m->playerIndex) { continue; }
                    struct Object* celebStar = spawn_object(marioState->marioObj, MODEL_STAR, bhvCelebrationStar);
                    if (m != marioState && celebStar != NULL) {
                        celebStar->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
                    }
                }
                if (m->playerIndex == 0) {
                    disable_background_sound();
                }
                if (m->actionArg & 1) {
                    play_course_clear();
                } else {
                    if (gCurrLevelNum == LEVEL_BOWSER_1 || gCurrLevelNum == LEVEL_BOWSER_2) {
                        play_music(SEQ_PLAYER_ENV, SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_COLLECT_KEY), 0);
                    } else {
                        play_music(SEQ_PLAYER_ENV, SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_COLLECT_STAR), 0);
                    }
                }
                break;

            case 42:
                play_character_sound(m, CHAR_SOUND_HERE_WE_GO);
                break;

            case 80:
                if ((m->actionArg & 1) == 0) {
                    level_trigger_warp(m, WARP_OP_STAR_EXIT);
                } else if (m->playerIndex == 0) {
                    if (gBehaviorValues.ShowStarDialog) {
                        enable_time_stop_if_alone();
                        create_dialog_box_with_response((gLastCompletedStarNum == 7)
                            ? gBehaviorValues.dialogs.HundredCoinsDialog
                            : gBehaviorValues.dialogs.CollectedStarDialog);
                        m->actionState = 1;
                    } else {
                        m->actionState = 2;
                    }
                } else {
                    set_mario_action(m, isInWater ? ACT_WATER_IDLE : (m->pos[1] <= m->floorHeight ? ACT_IDLE : ACT_FREEFALL), 0);
                }
                break;
        }
    } else if (m->playerIndex != 0) {
        // nothing
    } else if (m->actionState == 1 && gDialogResponse) {
        if (gDialogResponse == 1) {
            save_file_do_save(gCurrSaveFileNum - 1, FALSE);
        }
        m->actionState = 2;
    } else if (m->actionState == 2 && is_anim_at_end(m)) {
        disable_time_stop();
        enable_background_sound();
        s32 dialogID = get_star_collection_dialog(m);
        if (dialogID != 0) {
            // look up for dialog
            set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, dialogID);
        } else {
            set_mario_action(m, isInWater ? ACT_WATER_IDLE : (m->pos[1] <= m->floorHeight ? ACT_IDLE : ACT_FREEFALL), 0);
        }
        if (gServerSettings.stayInLevelAfterStar) {
            if (m->statusForCamera) { m->statusForCamera->action = m->action; }
            soft_reset_camera(m->area->camera);
        }
    }
}

s32 act_star_dance(struct MarioState *m) {
    if (!m) { return 0; }
    if (m == &gMarioStates[0]) {
        m->faceAngle[1] = m->area->camera->yaw;
    }
    set_character_animation(m, m->actionState == 2 ? CHAR_ANIM_RETURN_FROM_STAR_DANCE : CHAR_ANIM_STAR_DANCE);
    general_star_dance_handler(m, 0);
    if (m->actionState != 2 && m->actionTimer >= 40) {
        m->marioBodyState->handState = MARIO_HAND_PEACE_SIGN;
    }
    stop_and_set_height_to_floor(m);
    return FALSE;
}

s32 act_star_dance_water(struct MarioState *m) {
    if (!m) { return 0; }
    if (m == &gMarioStates[0]) {
        m->faceAngle[1] = m->area->camera->yaw;
    }
    set_character_animation(m, m->actionState == 2 ? CHAR_ANIM_RETURN_FROM_WATER_STAR_DANCE : CHAR_ANIM_WATER_STAR_DANCE);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    general_star_dance_handler(m, m->pos[1] < m->waterLevel - 100);
    if (m->actionState != 2 && m->actionTimer >= 62) {
        m->marioBodyState->handState = MARIO_HAND_PEACE_SIGN;
    }
    return FALSE;
}

s32 act_fall_after_star_grab(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->pos[1] < m->waterLevel - 130) {
        play_sound(SOUND_ACTION_UNKNOWN430, m->marioObj->header.gfx.cameraToObject);
        set_mario_particle_flags(m, PARTICLE_WATER_SPLASH, FALSE);
        return set_mario_action(m, ACT_STAR_DANCE_WATER, m->actionArg);
    }
    if (perform_air_step(m, 1) == AIR_STEP_LANDED) {
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
        set_mario_action(m, m->actionArg & 1 ? ACT_STAR_DANCE_NO_EXIT : ACT_STAR_DANCE_EXIT, m->actionArg);
    }
    set_character_animation(m, CHAR_ANIM_GENERAL_FALL);
    return FALSE;
}

s32 common_death_handler(struct MarioState *m, s32 animation, s32 frameToDeathWarp) {
    if (!m) { return 0; }
    s32 animFrame = set_character_animation(m, animation);
    if (animFrame == frameToDeathWarp) {
        if (m->playerIndex != 0) {
            // do nothing
        } else {
            bool allowDeath = true;
            smlua_call_event_hooks_mario_param_ret_bool(HOOK_ON_DEATH, m, &allowDeath);
            if (!allowDeath) { return animFrame; }

            if (mario_can_bubble(m)) {
                mario_set_bubbled(m);
            } else {
                level_trigger_warp(m, WARP_OP_DEATH);
            }
        }
    }
    m->marioBodyState->eyeState = MARIO_EYES_DEAD;
    stop_and_set_height_to_floor(m);
    return animFrame;
}

s32 act_standing_death(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_IN_POISON_GAS) {
        return set_mario_action(m, ACT_SUFFOCATION, 0);
    }

    play_character_sound_if_no_flag(m, CHAR_SOUND_DYING, MARIO_ACTION_SOUND_PLAYED);
    common_death_handler(m, CHAR_ANIM_DYING_FALL_OVER, 80);
    if (m->marioObj->header.gfx.animInfo.animFrame == 77) {
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_BODY_HIT_GROUND);
    }
    return FALSE;
}

s32 act_electrocution(struct MarioState *m) {
    play_character_sound_if_no_flag(m, CHAR_SOUND_DYING, MARIO_ACTION_SOUND_PLAYED);
    common_death_handler(m, CHAR_ANIM_ELECTROCUTION, 43);
    return FALSE;
}

s32 act_suffocation(struct MarioState *m) {
    play_character_sound_if_no_flag(m, CHAR_SOUND_DYING, MARIO_ACTION_SOUND_PLAYED);
    common_death_handler(m, CHAR_ANIM_SUFFOCATING, 86);
    return FALSE;
}

s32 act_death_on_back(struct MarioState *m) {
    play_character_sound_if_no_flag(m, CHAR_SOUND_DYING, MARIO_ACTION_SOUND_PLAYED);
    if (common_death_handler(m, CHAR_ANIM_DYING_ON_BACK, 54) == 40) {
        play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_BODY_HIT_GROUND);
    }
    return FALSE;
}

s32 act_death_on_stomach(struct MarioState *m) {
    play_character_sound_if_no_flag(m, CHAR_SOUND_DYING, MARIO_ACTION_SOUND_PLAYED);
    if (common_death_handler(m, CHAR_ANIM_DYING_ON_STOMACH, 37) == 37) {
        play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_BODY_HIT_GROUND);
    }
    return FALSE;
}

s32 act_quicksand_death(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->actionState == 0) {
        set_character_animation(m, CHAR_ANIM_DYING_IN_QUICKSAND);
        set_anim_to_frame(m, 60);
        m->actionState = 1;
    }
    if (m->actionState == 1) {
        if (m->quicksandDepth >= 100.0f) {
            play_character_sound_if_no_flag(m, CHAR_SOUND_WAAAOOOW, MARIO_MARIO_SOUND_PLAYED);
        }
        if ((m->quicksandDepth += 5.0f) >= 180.0f) {
            if (m->playerIndex != 0) {
                // do nothing
            } else {
                m->actionState = 2;
                bool allowDeath = true;
                smlua_call_event_hooks_mario_param_ret_bool(HOOK_ON_DEATH, m, &allowDeath);
                if (!allowDeath) { return FALSE; }

                if (mario_can_bubble(m)) {
                    mario_set_bubbled(m);
                } else {
                    level_trigger_warp(m, WARP_OP_DEATH);
                }
            }
        }
    }
    stationary_ground_step(m);
    play_sound(SOUND_MOVING_QUICKSAND_DEATH, m->marioObj->header.gfx.cameraToObject);
    return FALSE;
}

s32 act_eaten_by_bubba(struct MarioState *m) {
    if (!m) { return 0; }
    play_character_sound_if_no_flag(m, CHAR_SOUND_DYING, MARIO_ACTION_SOUND_PLAYED);
    set_character_animation(m, CHAR_ANIM_A_POSE);

    if (m->actionTimer++ == 60) {
        if (m->playerIndex != 0) {
            // do nothing
        } else {
            bool allowDeath = true;
            smlua_call_event_hooks_mario_param_ret_bool(HOOK_ON_DEATH, m, &allowDeath);
            if (!allowDeath) { return FALSE; }

            if (mario_can_bubble(m)) {
                m->health = 0xFF;
                mario_set_bubbled(m);
            } else {
                level_trigger_warp(m, WARP_OP_DEATH);
            }
        }
    }

    return FALSE;
}

// set animation and forwardVel; when perform_air_step returns AIR_STEP_LANDED,
// set the new action
s32 launch_mario_until_land(struct MarioState *m, s32 endAction, s32 animation, f32 forwardVel) {
    s32 airStepLanded;
    mario_set_forward_vel(m, forwardVel);
    set_character_animation(m, animation);
    airStepLanded = (perform_air_step(m, 0) == AIR_STEP_LANDED);
    if (airStepLanded) {
        set_mario_action(m, endAction, 0);
    }
    return airStepLanded;
}

s32 act_unlocking_key_door(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->usedObj != NULL) {
        m->faceAngle[1] = m->usedObj->oMoveAngleYaw;

        m->pos[0] = m->usedObj->oPosX + coss(m->faceAngle[1]) * 75.0f;
        m->pos[2] = m->usedObj->oPosZ + sins(m->faceAngle[1]) * 75.0f;
    }

    if (m->actionArg & 2) {
        m->faceAngle[1] += 0x8000;
    }

    if ((m->actionTimer == 0) || (m->playerIndex != 0 && gCurrentObject && gCurrentObject->header.gfx.animInfo.animID == -1)) {
        spawn_obj_at_mario_rel_yaw(m, MODEL_BOWSER_KEY_CUTSCENE, bhvBowserKeyUnlockDoor, 0);
        set_character_animation(m, CHAR_ANIM_UNLOCK_DOOR);
    }

    switch (m->marioObj->header.gfx.animInfo.animFrame) {
        case 79:
            play_sound(SOUND_GENERAL_DOOR_INSERT_KEY, m->marioObj->header.gfx.cameraToObject);
            break;
        case 111:
            play_sound(SOUND_GENERAL_DOOR_TURN_KEY, m->marioObj->header.gfx.cameraToObject);
            break;
    }

    update_mario_pos_for_anim(m);
    stop_and_set_height_to_floor(m);

    if (is_anim_at_end(m)) {
        if (m->usedObj != NULL && ((m->usedObj->oBehParams >> 24) == 1)) {
            save_file_set_flags(SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR);
            save_file_clear_flags(SAVE_FLAG_HAVE_KEY_2);
        } else {
            save_file_set_flags(SAVE_FLAG_UNLOCKED_BASEMENT_DOOR);
            save_file_clear_flags(SAVE_FLAG_HAVE_KEY_1);
        }
        set_mario_action(m, ACT_WALKING, 0);
    }

    m->actionTimer++;
    return FALSE;
}

s32 act_unlocking_star_door(struct MarioState *m) {
    if (!m) { return 0; }
    static u8 allowRemoteStarSpawn = TRUE;
    switch (m->actionState) {
        case 0:
            if (m->usedObj != NULL) {
                m->faceAngle[1] = m->usedObj->oMoveAngleYaw;
            }
            if (m->actionArg & 2) {
                m->faceAngle[1] += 0x8000;
            }
            m->marioObj->oMarioReadingSignDPosX = m->pos[0];
            m->marioObj->oMarioReadingSignDPosZ = m->pos[2];
            set_character_animation(m, CHAR_ANIM_SUMMON_STAR);
            if (m->playerIndex != 0) { allowRemoteStarSpawn = TRUE; }
            m->actionState++;
            break;
        case 1:
            set_character_animation(m, CHAR_ANIM_SUMMON_STAR);
            if (is_anim_at_end(m)) {
                if (m->playerIndex == 0 || allowRemoteStarSpawn) {
                    if (m->playerIndex != 0) { allowRemoteStarSpawn = FALSE; }
                    spawn_object(m->marioObj, MODEL_STAR, bhvUnlockDoorStar);
                }
                m->actionState++;
            }
            break;
        case 2:
            if (m->actionTimer++ == 70) {
                set_character_animation(m, CHAR_ANIM_RETURN_STAR_APPROACH_DOOR);
                m->actionState++;
            }
            break;
        case 3:
            set_character_animation(m, CHAR_ANIM_RETURN_STAR_APPROACH_DOOR);
            if (m->playerIndex != 0) { allowRemoteStarSpawn = TRUE; }
            if (is_anim_at_end(m)) {
                save_file_set_flags(get_door_save_file_flag(m->usedObj));
                set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, gBehaviorValues.dialogs.StarDoorDialog);
            }
            break;
    }

    m->pos[0] = m->marioObj->oMarioReadingSignDPosX;
    m->pos[2] = m->marioObj->oMarioReadingSignDPosZ;

    update_mario_pos_for_anim(m);
    stop_and_set_height_to_floor(m);

    return FALSE;
}

s32 act_entering_star_door(struct MarioState *m) {
    if (!m) { return 0; }
    f32 targetDX = 0;
    f32 targetDZ = 0;
    s16 targetAngle = 0;

    if (m->actionTimer++ == 0) {
        if (m->interactObj != NULL) {
            m->interactObj->oInteractStatus = 0x00010000;
        }

        // ~30 degrees / 1/12 rot
        if (m->usedObj != NULL) { targetAngle = m->usedObj->oMoveAngleYaw + 0x1555; }
        if (m->actionArg & 2) {
            targetAngle += 0x5556; // ~120 degrees / 1/3 rot (total 150d / 5/12)
        }

        // targetDX and targetDZ are the offsets to add to Mario's position to
        // have Mario stand 150 units in front of the door

        if (m->usedObj != NULL) {
            targetDX = m->usedObj->oPosX + 150.0f * sins(targetAngle) - m->pos[0];
            targetDZ = m->usedObj->oPosZ + 150.0f * coss(targetAngle) - m->pos[2];
        }

        m->marioObj->oMarioReadingSignDPosX = targetDX / 20.0f;
        m->marioObj->oMarioReadingSignDPosZ = targetDZ / 20.0f;

        m->faceAngle[1] = atan2s(targetDZ, targetDX);
    }

    // set Mario's animation
    if (m->actionTimer < 15) {
        set_character_animation(m, CHAR_ANIM_FIRST_PERSON);
    } else if (m->actionTimer < 35) { // go through door? for 20 frames
        m->pos[0] += m->marioObj->oMarioReadingSignDPosX;
        m->pos[2] += m->marioObj->oMarioReadingSignDPosZ;

        set_character_anim_with_accel(m, CHAR_ANIM_WALKING, 0x00028000);
    } else {
        if (m->usedObj != NULL) {
            m->faceAngle[1] = m->usedObj->oMoveAngleYaw;
        }

        if (m->actionArg & 2) {
            m->faceAngle[1] += 0x8000;
        }

        m->pos[0] += 12.0f * sins(m->faceAngle[1]);
        m->pos[2] += 12.0f * coss(m->faceAngle[1]);

        set_character_anim_with_accel(m, CHAR_ANIM_WALKING, 0x00028000);
    }

    stop_and_set_height_to_floor(m);

    if (m->actionTimer == 48) {
        set_mario_action(m, ACT_IDLE, 0);
    }

    return FALSE;
}

s32 act_going_through_door(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->actionTimer == 0) {
        if (m->actionArg & 1) {
            if (m->interactObj != NULL) {
                m->interactObj->oInteractStatus = 0x00010000;
            }
            set_character_animation(m, CHAR_ANIM_PULL_DOOR_WALK_IN);
        } else {
            if (m->interactObj != NULL) {
                m->interactObj->oInteractStatus = 0x00020000;
            }
            set_character_animation(m, CHAR_ANIM_PUSH_DOOR_WALK_IN);
        }
    }
    if (m->usedObj != NULL) {
        m->faceAngle[1] = m->usedObj->oMoveAngleYaw;
        m->pos[0] = m->usedObj->oPosX;
        m->pos[2] = m->usedObj->oPosZ;
    }

    update_mario_pos_for_anim(m);
    stop_and_set_height_to_floor(m);

    if (m->actionArg & 4) {
        if (m->actionTimer == 16) {
            level_trigger_warp(m, WARP_OP_WARP_DOOR);
        }
    } else if (is_anim_at_end(m)) {
        if (m->actionArg & 2) {
            m->faceAngle[1] += 0x8000;
        }
        set_mario_action(m, ACT_IDLE, 0);
    }

    m->actionTimer++;
    return FALSE;
}

s32 act_warp_door_spawn(struct MarioState *m) {
    if (!m) { return 0; }

    // Check if other players are also using this door
    // if they are, cancel our interaction with the door
    if (m->usedObj) {
        for (u8 i = 0; i < MAX_PLAYERS; i++) {
            struct MarioState *m2 = &gMarioStates[i];
            if (is_player_active(m2) && (m2->action == ACT_PULLING_DOOR || m2->action == ACT_PUSHING_DOOR) && m->usedObj == m2->usedObj) {
                m->usedObj = NULL;
                break;
            }
        }
    }

    if (m->actionState == 0) {
        m->actionState = 1;
        if (m->usedObj != NULL) {
            if (m->actionArg & 1) {
                m->usedObj->oInteractStatus = 0x00040000;
            } else {
                m->usedObj->oInteractStatus = 0x00080000;
            }
        }
    } else if (m->usedObj == NULL || (m->usedObj->oAction == 0 || m->usedObj->oAction == 100)) {
        if (m->playerIndex == 0) {
            if (gNeverEnteredCastle && gCurrLevelNum == LEVEL_CASTLE) {
                set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, gBehaviorValues.dialogs.CastleEnterDialog);
            } else {
                set_mario_action(m, ACT_IDLE, 0);
            }
        }
    }
    set_character_animation(m, CHAR_ANIM_FIRST_PERSON);
    stop_and_set_height_to_floor(m);
    return FALSE;
}

static s32 launch_mario_until_land_no_collision(struct MarioState *m, s32 endAction, s32 animation, f32 forwardVel) {
    if (!m) { return 0; }
    mario_set_forward_vel(m, forwardVel);
    set_character_animation(m, animation);
    m->pos[0] += m->vel[0];
    m->pos[1] += m->vel[1];
    m->pos[2] += m->vel[2];
    m->vel[1] -= 4.f;
    if (m->vel[1] < -75.f) {
        m->vel[1] = -75.f;
    }
    f32 floorHeight = find_floor_height(m->pos[0], m->pos[1], m->pos[2]);
    s32 landed = floorHeight >= m->pos[1];
    if (landed) {
        m->pos[1] = floorHeight;
        set_mario_action(m, endAction, 0);
    }
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    return landed;
}

s32 act_emerge_from_pipe(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;

    if (m->actionTimer++ < 11) {
        marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
        return FALSE;
    }

    marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

    play_character_sound_if_no_flag(m, CHAR_SOUND_YAHOO, MARIO_MARIO_SOUND_PLAYED);

    if (gCurrLevelNum == LEVEL_THI) {
        if (gCurrAreaIndex == 2) {
            play_sound_if_no_flag(m, SOUND_MENU_EXIT_PIPE, MARIO_ACTION_SOUND_PLAYED);
        } else {
            play_sound_if_no_flag(m, SOUND_MENU_ENTER_PIPE, MARIO_ACTION_SOUND_PLAYED);
        }
    }

    // After Mario has exited the pipe, disable wall and ceiling collision until Mario lands
    // Fix softlocks in narrow places
    if (m->actionTimer > 15) {
        if (launch_mario_until_land_no_collision(m, ACT_JUMP_LAND_STOP, CHAR_ANIM_SINGLE_JUMP, 8.0f)) {
            mario_set_forward_vel(m, 0.0f);
            play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
        }
        return FALSE;
    }

    if (launch_mario_until_land(m, ACT_JUMP_LAND_STOP, CHAR_ANIM_SINGLE_JUMP, 8.0f)) {
        mario_set_forward_vel(m, 0.0f);
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
    }
    return FALSE;
}

s32 act_spawn_spin_airborne(struct MarioState *m) {
    if (!m) { return 0; }
    // entered water, exit action
    if (m->pos[1] < m->waterLevel - 100) {
        if (m == &gMarioStates[0]) {
            load_level_init_text(0);
        }
        return set_water_plunge_action(m);
    }

    // updates all velocity variables based on m->forwardVel
    mario_set_forward_vel(m, m->forwardVel);

    // landed on floor, play spawn land animation
    if (perform_air_step(m, 0.0) == AIR_STEP_LANDED) {
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
        set_mario_action(m, ACT_SPAWN_SPIN_LANDING, 0);
    }

    // is 300 units above floor, spin and play woosh sounds
    if (m->actionState == 0 && m->pos[1] - m->floorHeight > 300.0f) {
        if (set_character_animation(m, CHAR_ANIM_FORWARD_SPINNING) == 0) { // first anim frame
            play_sound(SOUND_ACTION_SPIN, m->marioObj->header.gfx.cameraToObject);
        }
    } else { // under 300 units above floor, enter freefall animation
        m->actionState = 1;
        set_character_animation(m, CHAR_ANIM_GENERAL_FALL);
    }

    return FALSE;
}

s32 act_spawn_spin_landing(struct MarioState *m) {
    stop_and_set_height_to_floor(m);
    set_character_animation(m, CHAR_ANIM_GENERAL_LAND);
    if (is_anim_at_end(m)) {
        if (m == &gMarioStates[0]) {
            load_level_init_text(0);
        }
        set_mario_action(m, ACT_IDLE, 0);
    }
    return FALSE;
}

/**
 * act_exit_airborne: Jump out of a level after collecting a Power Star (no
 ** sparkles)
 * Mario always faces a level entrance when he launches out of it, whether he
 * died or he collected a star/key. Because of that, we need him to move away
 * from the painting by setting his speed to -32.0f and have him face away from
 * the painting by adding 0x8000 (180 deg) to his graphics angle. We also set
 * his heal counter to 31 to restore 7.75 units of his health, and enable the
 * particle flag that generates sparkles.
 */
s32 act_exit_airborne(struct MarioState *m) {
    if (!m) { return 0; }
    if (15 < m->actionTimer++
        && launch_mario_until_land(m, ACT_EXIT_LAND_SAVE_DIALOG, CHAR_ANIM_GENERAL_FALL, -32.0f)) {
        // heal Mario
        m->healCounter = 31;
    }
    // rotate him to face away from the entrance
    m->marioObj->header.gfx.angle[1] += 0x8000;
    set_mario_particle_flags(m, PARTICLE_SPARKLES, FALSE);
    return FALSE;
}

s32 act_falling_exit_airborne(struct MarioState *m) {
    if (!m) { return 0; }
    if (launch_mario_until_land(m, ACT_EXIT_LAND_SAVE_DIALOG, CHAR_ANIM_GENERAL_FALL, 0.0f)) {
        // heal Mario
        m->healCounter = 31;
    }
    // rotate Mario to face away from the entrance
    m->marioObj->header.gfx.angle[1] += 0x8000;
    set_mario_particle_flags(m, PARTICLE_SPARKLES, FALSE);
    return FALSE;
}

s32 act_exit_land_save_dialog(struct MarioState *m) {
    if (!m) { return 0; }
    s32 animFrame;
    stationary_ground_step(m);
    play_mario_landing_sound_once(m, SOUND_ACTION_TERRAIN_LANDING);
    switch (m->actionState) {
        // determine type of exit
        case 0:
            set_character_animation(m, m->actionArg == 0 ? CHAR_ANIM_GENERAL_LAND : CHAR_ANIM_LAND_FROM_SINGLE_JUMP);
            // only allow for local player
            if (m == &gMarioStates[0] && is_anim_past_end(m)) {
                if (gLastCompletedCourseNum != COURSE_BITDW && gLastCompletedCourseNum != COURSE_BITFS) {
                    enable_time_stop_if_alone();
                }

                set_menu_mode(RENDER_COURSE_DONE_SCREEN);
                gSaveOptSelectIndex = 0;

                m->actionState = 3; // star exit with cap
                if (!(m->flags & MARIO_CAP_ON_HEAD)) {
                    m->actionState = 2; // star exit without cap
                }
                if ((gLastCompletedCourseNum == COURSE_BITDW || gLastCompletedCourseNum == COURSE_BITFS)
                    && gLastCollectedStarOrKey == 1) {
                    m->actionState = 1; // key exit
                }
            }
            break;
        // key exit
        case 1:
            animFrame = set_character_animation(m, CHAR_ANIM_THROW_CATCH_KEY);
            switch (animFrame) {
                case -1:
                    spawn_obj_at_mario_rel_yaw(m, MODEL_BOWSER_KEY_CUTSCENE, bhvBowserKeyCourseExit, -32768);
                    //! fall through
                case 67:
                    play_sound(SOUND_ACTION_KEY_SWISH, m->marioObj->header.gfx.cameraToObject);
                    //! fall through
                case 83:
                    play_sound(SOUND_ACTION_PAT_BACK, m->marioObj->header.gfx.cameraToObject);
                    //! fall through
                case 111:
                    play_sound(SOUND_ACTION_UNKNOWN45C, m->marioObj->header.gfx.cameraToObject);
                    // no break
            }
            // only allow for local player
            if (m == &gMarioStates[0]) { handle_save_menu(m); }
            break;
        // exit without cap
        case 2:
            animFrame = set_character_animation(m, CHAR_ANIM_MISSING_CAP);
            if ((animFrame >= 18 && animFrame < 55) || (animFrame >= 112 && animFrame < 134)) {
                m->marioBodyState->handState = MARIO_HAND_OPEN;
            }
            if (!(animFrame < 109) && animFrame < 154) {
                m->marioBodyState->eyeState = MARIO_EYES_HALF_CLOSED;
            }

            // only allow for local player
            if (m == &gMarioStates[0]) { handle_save_menu(m); }
            break;
        // exit with cap
        case 3:
            animFrame = set_character_animation(m, CHAR_ANIM_TAKE_CAP_OFF_THEN_ON);
            switch (animFrame) {
                case 12:
                    cutscene_take_cap_off(m);
                    break;
                case 37:
                // fall through
                case 53:
                    play_sound(SOUND_ACTION_BRUSH_HAIR, m->marioObj->header.gfx.cameraToObject);
                    break;
                case 82:
                    cutscene_put_cap_on(m);
                    break;
            }
            // only allow for local player
            if (m == &gMarioStates[0]) { handle_save_menu(m); }
            break;
    }

    m->marioObj->header.gfx.angle[1] += 0x8000;
    return FALSE;
}

s32 act_death_exit(struct MarioState *m) {
    if (!m) { return 0; }
    if (15 < m->actionTimer++
        && launch_mario_until_land(m, ACT_DEATH_EXIT_LAND, CHAR_ANIM_GENERAL_FALL, -32.0f)) {
#ifdef VERSION_JP
        play_character_sound(m, CHAR_SOUND_OOOF);
#else
        play_character_sound(m, CHAR_SOUND_OOOF2);
#endif
        queue_rumble_data_mario(m, 5, 80);
        // restore 7.75 units of health
        m->healCounter = 31;
    }
    // one unit of health
    m->health = 0x0100;
    return FALSE;
}

s32 act_unused_death_exit(struct MarioState *m) {
    if (!m) { return 0; }
    if (launch_mario_until_land(m, ACT_FREEFALL_LAND_STOP, CHAR_ANIM_GENERAL_FALL, 0.0f)) {
#ifdef VERSION_JP
        play_character_sound(m, CHAR_SOUND_OOOF);
#else
        play_character_sound(m, CHAR_SOUND_OOOF2);
#endif
        // restore 7.75 units of health
        m->healCounter = 31;
    }
    // one unit of health
    m->health = 0x0100;
    return FALSE;
}

s32 act_falling_death_exit(struct MarioState *m) {
    if (!m) { return 0; }
    if (launch_mario_until_land(m, ACT_DEATH_EXIT_LAND, CHAR_ANIM_GENERAL_FALL, 0.0f)) {
#ifdef VERSION_JP
        play_character_sound(m, CHAR_SOUND_OOOF);
#else
        play_character_sound(m, CHAR_SOUND_OOOF2);
#endif
        queue_rumble_data_mario(m, 5, 80);
        // restore 7.75 units of health
        m->healCounter = 31;
    }
    // one unit of health
    m->health = 0x0100;
    return FALSE;
}

// waits 11 frames before actually executing, also has reduced fvel
s32 act_special_exit_airborne(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;

    play_character_sound_if_no_flag(m, CHAR_SOUND_YAHOO, MARIO_MARIO_SOUND_PLAYED);

    if (m->actionTimer++ < 11) {
        marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
        return FALSE;
    }

    if (launch_mario_until_land(m, ACT_EXIT_LAND_SAVE_DIALOG, CHAR_ANIM_SINGLE_JUMP, -24.0f)) {
        // heal Mario
        m->healCounter = 31;
        m->actionArg = 1;
    }

    set_mario_particle_flags(m, PARTICLE_SPARKLES, FALSE);
    // rotate Mario to face away from the entrance
    marioObj->header.gfx.angle[1] += 0x8000;
    // show Mario
    marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

    return FALSE;
}

s32 act_special_death_exit(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;

    if (m->actionTimer++ < 11) {
        marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
        return FALSE;
    }

    if (launch_mario_until_land(m, ACT_HARD_BACKWARD_GROUND_KB, CHAR_ANIM_BACKWARD_AIR_KB, -24.0f)) {
        queue_rumble_data_mario(m, 5, 80);
        m->healCounter = 31;
    }
    // show Mario
    marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
    // one unit of health
    m->health = 0x0100;

    return FALSE;
}

s32 act_spawn_no_spin_airborne(struct MarioState *m) {
    if (!m) { return 0; }
    launch_mario_until_land(m, ACT_SPAWN_NO_SPIN_LANDING, CHAR_ANIM_GENERAL_FALL, 0.0f);
    if (m->pos[1] < m->waterLevel - 100) {
        set_water_plunge_action(m);
    }
    return FALSE;
}

s32 act_spawn_no_spin_landing(struct MarioState *m) {
    play_mario_landing_sound_once(m, SOUND_ACTION_TERRAIN_LANDING);
    set_character_animation(m, CHAR_ANIM_GENERAL_LAND);
    stop_and_set_height_to_floor(m);
    if (is_anim_at_end(m)) {
        if (m == &gMarioStates[0]) {
            load_level_init_text(0);
        }
        set_mario_action(m, ACT_IDLE, 0);
    }
    return FALSE;
}

s32 act_bbh_enter_spin(struct MarioState *m) {
    if (!m) { return 0; }
    f32 cageDX = 0.0f;
    f32 cageDZ = 0.0f;
    f32 forwardVel = 0.0f;

    if (m->usedObj == NULL) {
        m->usedObj = cur_obj_nearest_object_with_behavior(bhvBooCage);
    }

    if (m->usedObj != NULL) {
        cageDX = m->usedObj->oPosX - m->pos[0];
        cageDZ = m->usedObj->oPosZ - m->pos[2];
    }
    f32 cageDist = sqrtf(cageDX * cageDX + cageDZ * cageDZ);

    if (cageDist > 20.0f) {
        forwardVel = 10.0f;
    } else {
        forwardVel = cageDist / 2.0f;
    }
    if (forwardVel < 0.5f) {
        forwardVel = 0.0f;
    }

    switch (m->actionState) {
        case 0:
            {
                f32 floorDist = 512.0f - (m->pos[1] - m->floorHeight);
                m->vel[1] = floorDist > 0 ? sqrtf(4.0f * floorDist + 1.0f) - 1.0f : 2.0f;

                m->actionState = 1;
                m->actionTimer = 100;
            }
            // fall through
        case 1:
            m->faceAngle[1] = atan2s(cageDZ, cageDX);
            mario_set_forward_vel(m, forwardVel);

            if (set_character_animation(m, CHAR_ANIM_FORWARD_SPINNING) == 0) {
                play_sound(SOUND_ACTION_SPIN, m->marioObj->header.gfx.cameraToObject);
            }

            m->flags &= ~MARIO_UNKNOWN_08;
            perform_air_step(m, 0);
            if (m->vel[1] <= 0) {
                m->actionState = 2;
            }
            break;

        case 2:
            // fall through
        case 3:
            m->faceAngle[1] = atan2s(cageDZ, cageDX);
            mario_set_forward_vel(m, forwardVel);
            m->flags &= ~MARIO_UNKNOWN_08;
            if (perform_air_step(m, 0) == AIR_STEP_LANDED) {
                level_trigger_warp(m, WARP_OP_SPIN_SHRINK);
                queue_rumble_data_mario(m, 15, 80);
                m->actionState = 4;
            }
            if (m->actionState == 2) {
                if (m->marioObj->header.gfx.animInfo.animFrame == 0) {
                    m->actionState = 3;
                }
            } else {
                play_sound_if_no_flag(m, SOUND_ACTION_SHRINK_INTO_BBH, MARIO_ACTION_SOUND_PLAYED);
                set_character_animation(m, CHAR_ANIM_DIVE);
                m->marioObj->header.gfx.angle[0] = atan2s(m->forwardVel, -m->vel[1]);
            }
            m->squishTimer = 0xFF;
            if (m->actionTimer >= 11) {
                m->actionTimer -= 6;
                f32 scale = m->actionTimer / 100.0f;
                vec3f_set(m->marioObj->header.gfx.scale, scale, scale, scale);
            }
            break;

        case 4:
            stop_and_set_height_to_floor(m);
            m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            break;
    }

    return FALSE;
}

s32 act_bbh_enter_jump(struct MarioState *m) {
    if (!m) { return 0; }
    play_mario_action_sound(m, m->flags & MARIO_METAL_CAP ? SOUND_ACTION_METAL_JUMP : SOUND_ACTION_TERRAIN_JUMP, 1);
    play_mario_jump_sound(m);

    if (m->usedObj == NULL) {
        m->usedObj = cur_obj_nearest_object_with_behavior(bhvBooCage);
    }

    if (m->actionState == 0 && m->usedObj != NULL) {
        f32 cageDX = m->usedObj->oPosX - m->pos[0];
        f32 cageDZ = m->usedObj->oPosZ - m->pos[2];
        f32 cageDist = sqrtf(cageDX * cageDX + cageDZ * cageDZ);

        m->vel[1] = 60.0f;
        m->faceAngle[1] = atan2s(cageDZ, cageDX);
        mario_set_forward_vel(m, cageDist / 20.0f);

        m->flags &= ~MARIO_UNKNOWN_08;
        m->actionState = 1;
    }

    set_character_animation(m, CHAR_ANIM_DOUBLE_JUMP_RISE);
    perform_air_step(m, 0);

    if (m->vel[1] <= 0.0f) {
        set_mario_action(m, ACT_BBH_ENTER_SPIN, 0);
    }

    return FALSE;
}

s32 act_teleport_fade_out(struct MarioState *m) {
    if (!m) { return 0; }
    play_sound_if_no_flag(m, SOUND_ACTION_TELEPORT, MARIO_ACTION_SOUND_PLAYED);
    set_character_animation(m, m->prevAction == ACT_CROUCHING ? CHAR_ANIM_CROUCHING : CHAR_ANIM_FIRST_PERSON);

    if (m->actionTimer == 0) {
        queue_rumble_data_mario(m, 30, 70);
        if (m->playerIndex == 0) {
            func_sh_8024C89C(2);
        }
    }

    m->flags |= MARIO_TELEPORTING;

    if (m->actionTimer < 32) {
        m->fadeWarpOpacity = (-m->actionTimer << 3) + 0xF8;
    }

    if (m->actionTimer++ == 20) {
        if (m == &gMarioStates[0]) {
            // only do for local player
            level_trigger_warp(m, WARP_OP_TELEPORT);
        }
    }

    stop_and_set_height_to_floor(m);

    return FALSE;
}

s32 act_teleport_fade_in(struct MarioState *m) {
    if (!m) { return 0; }
    play_sound_if_no_flag(m, SOUND_ACTION_TELEPORT, MARIO_ACTION_SOUND_PLAYED);
    set_character_animation(m, CHAR_ANIM_FIRST_PERSON);

    if (m->actionTimer == 0) {
        queue_rumble_data_mario(m, 30, 70);
        if (m->playerIndex == 0) {
            func_sh_8024C89C(2);
        }
    }

    if (m->actionTimer < 32) {
        m->flags |= MARIO_TELEPORTING;
        m->fadeWarpOpacity = m->actionTimer << 3;
    } else {
        m->flags &= ~MARIO_TELEPORTING;
    }

    if (m->actionTimer++ == 32) {
        if (m->pos[1] < m->waterLevel - 100) {
            // Check if the camera is not underwater.
            if (m->playerIndex == 0 && m->area->camera->mode != CAMERA_MODE_WATER_SURFACE) {
                set_camera_mode(m->area->camera, CAMERA_MODE_WATER_SURFACE, 1);
            }
            set_mario_action(m, ACT_WATER_IDLE, 0);
        } else {
            set_mario_action(m, ACT_IDLE, 0);
        }
    }

    stop_and_set_height_to_floor(m);

    return FALSE;
}

s32 act_shocked(struct MarioState *m) {
    if (!m) { return 0; }
    play_character_sound_if_no_flag(m, CHAR_SOUND_WAAAOOOW, MARIO_MARIO_SOUND_PLAYED);
    play_sound(SOUND_MOVING_SHOCKED, m->marioObj->header.gfx.cameraToObject);
    if (m->playerIndex == 0) { set_camera_shake_from_hit(SHAKE_SHOCK); }

    if (set_character_animation(m, CHAR_ANIM_SHOCKED) == 0) {
        m->actionTimer++;
        m->flags |= MARIO_METAL_SHOCK;
    }

    if (m->actionArg == 0) {
        mario_set_forward_vel(m, 0.0f);
        if (perform_air_step(m, 1) == AIR_STEP_LANDED) {
            play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
            m->actionArg = 1;
        }
    } else {
        if (m->actionTimer >= 6) {
            m->invincTimer = 30;
            set_mario_action(m, m->health < 0x0100 ? ACT_ELECTROCUTION : ACT_IDLE, 0);
        }
        stop_and_set_height_to_floor(m);
    }

    return FALSE;
}

s32 act_squished(struct MarioState *m) {
    if (m == NULL) { return TRUE; }

    f32 spaceUnderCeil;
    s16 surfAngle;
    s32 underSteepSurf = FALSE; // seems to be responsible for setting velocity?

    if ((spaceUnderCeil = m->ceilHeight - m->floorHeight) < 0) {
        spaceUnderCeil = 0;
    }

    switch (m->actionState) {
        case 0:
            if (spaceUnderCeil > 160.0f) {
                m->squishTimer = 0;
                // prevent infinite loop for remote players
                if (m == &gMarioStates[0]) {
                    return set_mario_action(m, ACT_IDLE, 0);
                } else {
                    set_mario_action(m, ACT_IDLE, 0);
                    return FALSE;
                }
            }

            m->squishTimer = 0xFF;

            if (spaceUnderCeil >= 10.1f) {
                // Mario becomes a pancake
                f32 squishAmount = spaceUnderCeil / 160.0f;
                vec3f_set(m->marioObj->header.gfx.scale, 2.0f - squishAmount, squishAmount, 2.0f - squishAmount);
            } else {
                if (!(m->flags & MARIO_METAL_CAP) && m->invincTimer == 0) {
                    // cap on: 3 units; cap off: 4.5 units
                    m->hurtCounter += m->flags & MARIO_CAP_ON_HEAD ? 12 : 18;
                    play_character_sound_if_no_flag(m, CHAR_SOUND_ATTACKED, MARIO_MARIO_SOUND_PLAYED);
                }

                // Both of the 1.8's are really floats, but one of them has to
                // be written as a double for this to match on -O2.
                vec3f_set(m->marioObj->header.gfx.scale, 1.8, 0.05f, 1.8f);
                queue_rumble_data_mario(m, 10, 80);
                m->actionState = 1;
            }
            break;
        case 1:
            if (spaceUnderCeil >= 30.0f) {
                m->actionState = 2;
            }
            break;
        case 2:
            m->actionTimer++;
            if (m->actionTimer >= 15) {
                // 1 unit of health
                if (m->health < 0x0100) {
                    //level_trigger_warp(m, WARP_OP_DEATH);
                    // woosh, he's gone!
                    //set_mario_action(m, ACT_DISAPPEARED, 0);
                    drop_and_set_mario_action(m, ACT_DEATH_ON_BACK, 0);
                    m->squishTimer = 0;
                } else if (m->hurtCounter == 0) {
                    // un-squish animation
                    m->squishTimer = 30;
                    set_mario_action(m, ACT_IDLE, 0);
                }
            }
            break;
    }

    // steep floor
    if (m->floor != NULL && m->floor->normal.y < 0.5f) {
        surfAngle = atan2s(m->floor->normal.z, m->floor->normal.x);
        underSteepSurf = TRUE;
    }
    // steep ceiling
    if (m->ceil != NULL && -0.5f < m->ceil->normal.y) {
        surfAngle = atan2s(m->ceil->normal.z, m->ceil->normal.x);
        underSteepSurf = TRUE;
    }

    if (underSteepSurf) {
        m->vel[0] = sins(surfAngle) * 10.0f;
        m->vel[2] = coss(surfAngle) * 10.0f;
        m->vel[1] = 0;

        // check if there's no floor 10 units away from the surface
        if (perform_ground_step(m) == GROUND_STEP_LEFT_GROUND) {
            // instant un-squish
            m->squishTimer = 0;
            set_mario_action(m, ACT_IDLE, 0);
            return FALSE;
        }
    }

    // squished for more than 10 seconds, so kill Mario
    if (m->actionArg++ > 300) {
        if (m->playerIndex != 0) {
            // never kill remote marios
            m->health = 0x100;
        } else {
            bool allowDeath = true;
            smlua_call_event_hooks_mario_param_ret_bool(HOOK_ON_DEATH, m, &allowDeath);
            if (!allowDeath) { return FALSE; }

            if (mario_can_bubble(m)) {
                mario_set_bubbled(m);
            } else {
                // 0 units of health
                m->health = 0x00FF;
                m->hurtCounter = 0;
                level_trigger_warp(m, WARP_OP_DEATH);
                // woosh, he's gone!
                set_mario_action(m, ACT_DISAPPEARED, 0);
            }
        }
    }
    stop_and_set_height_to_floor(m);
    set_character_animation(m, CHAR_ANIM_A_POSE);
    return FALSE;
}

s32 act_putting_on_cap(struct MarioState *m) {
    s32 animFrame = set_character_animation(m, CHAR_ANIM_PUT_CAP_ON);

    if (animFrame == 0 && !gCamera->paletteEditorCap) {
        enable_time_stop_if_alone();
    }

    if (animFrame == 28) {
        cutscene_put_cap_on(m);
        gCamera->paletteEditorCap = false;
    }

    if (is_anim_at_end(m)) {
        set_mario_action(m, ACT_IDLE, 0);
        disable_time_stop();
    }

    stationary_ground_step(m);
    return FALSE;
}

// coop custom action
// actionArg == 1: the action was inited from CUTSCENE_PALETTE_EDITOR
s32 act_taking_off_cap(struct MarioState *m) {
    s16 animFrame = set_character_animation(m, CHAR_ANIM_TAKE_CAP_OFF_THEN_ON);
    switch (animFrame) {
        case 0:
            if (m->actionArg != 1) {
                enable_time_stop_if_alone();
            }
            break;
        case 12:
            cutscene_take_cap_off(m);
            if (m->actionArg == 1) { gCamera->paletteEditorCap = true; }
            break;
    }
    if (animFrame >= 30 || gCamera->cutscene != CUTSCENE_PALETTE_EDITOR) {
        set_mario_action(m, ACT_IDLE, 0);
        disable_time_stop();
    }

    stationary_ground_step(m);
    return FALSE;
}

void stuck_in_ground_handler(struct MarioState *m, s32 animation, s32 unstuckFrame, s32 target2,
                             s32 target3, s32 endAction) {
    if (!m) { return; }
    s32 animFrame = set_character_animation(m, animation);

    if (m->input & INPUT_A_PRESSED) {
        m->actionTimer++;
        if (m->actionTimer >= 5 && animFrame < unstuckFrame - 1) {
            animFrame = unstuckFrame - 1;
            set_anim_to_frame(m, animFrame);
        }
    }

    stop_and_set_height_to_floor(m);

    if (animFrame == -1) {
        play_sound_and_spawn_particles(m, SOUND_ACTION_TERRAIN_STUCK_IN_GROUND, 1);
    } else if (animFrame == unstuckFrame) {
        queue_rumble_data_mario(m, 5, 80);
        play_sound_and_spawn_particles(m, SOUND_ACTION_UNSTUCK_FROM_GROUND, 1);
    } else if (animFrame == target2 || animFrame == target3) {
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
    }

    if (is_anim_at_end(m)) {
        set_mario_action(m, endAction, 0);
    }
}

s32 act_head_stuck_in_ground(struct MarioState *m) {
    stuck_in_ground_handler(m, CHAR_ANIM_HEAD_STUCK_IN_GROUND, 96, 105, 135, ACT_IDLE);
    return FALSE;
}

s32 act_butt_stuck_in_ground(struct MarioState *m) {
    stuck_in_ground_handler(m, CHAR_ANIM_BOTTOM_STUCK_IN_GROUND, 127, 136, -2, ACT_GROUND_POUND_LAND);
    return FALSE;
}

s32 act_feet_stuck_in_ground(struct MarioState *m) {
    stuck_in_ground_handler(m, CHAR_ANIM_LEGS_STUCK_IN_GROUND, 116, 129, -2, ACT_IDLE);
    return FALSE;
}

/**
 * advance_cutscene_step: Advances the current step in the current cutscene.
 * Resets action state and action timer, adds 1 to the action arg (responsible
 * for keeping track of what step of the cutscene Mario is in.)
 */
static void advance_cutscene_step(struct MarioState *m) {
    if (!m) { return; }
    m->actionState = 0;
    m->actionTimer = 0;
    m->actionArg++;
}

static void intro_cutscene_hide_hud_and_mario(struct MarioState *m) {
    if (!m) { return; }
    gHudDisplay.flags = HUD_DISPLAY_NONE;
    m->statusForCamera->cameraEvent = CAM_EVENT_START_INTRO;
    m->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    advance_cutscene_step(m);
}

#ifdef VERSION_EU
    //#define TIMER_SPAWN_PIPE 47
    #define TIMER_SPAWN_PIPE 37
#else
    #define TIMER_SPAWN_PIPE 37
#endif

static void intro_cutscene_peach_lakitu_scene(struct MarioState *m) {
    if (!m) { return; }
    if ((s16) m->statusForCamera->cameraEvent != CAM_EVENT_START_INTRO) {
        if (m->actionTimer++ == TIMER_SPAWN_PIPE) {
            u8 globalIndex = gNetworkPlayers[m->playerIndex].globalIndex;
            if (globalIndex == UNKNOWN_GLOBAL_INDEX) { globalIndex = 0; }
            sIntroWarpPipeObj[globalIndex] =
                spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_CASTLE_GROUNDS_WARP_PIPE,
                                          bhvStaticObject, -1328 - (350 * globalIndex), 60, 4664, 0, 180, 0);
            advance_cutscene_step(m);
        }
    }
}
#undef TIMER_SPAWN_PIPE

#ifdef VERSION_EU
    //#define TIMER_RAISE_PIPE 28
    #define TIMER_RAISE_PIPE 38
#else
    #define TIMER_RAISE_PIPE 38
#endif

static void intro_cutscene_raise_pipe(struct MarioState* m) {
    if (!m) { return; }
    u8 globalIndex = gNetworkPlayers[m->playerIndex].globalIndex;
    if (globalIndex == UNKNOWN_GLOBAL_INDEX) { globalIndex = 0; }

    if (sIntroWarpPipeObj[globalIndex] != NULL) {
        sIntroWarpPipeObj[globalIndex]->oPosY = camera_approach_f32_symmetric(sIntroWarpPipeObj[globalIndex]->oPosY, 260.0f, 10.0f);

        if (m->actionTimer == 0) {
            play_sound(SOUND_MENU_EXIT_PIPE, sIntroWarpPipeObj[globalIndex]->header.gfx.cameraToObject);
        }
    }

    if (m->actionTimer++ == TIMER_RAISE_PIPE) {
        m->vel[1] = 60.0f;
        advance_cutscene_step(m);
    }
}

static void intro_cutscene_raise_pipe_main_menu(struct MarioState* m) {
    if (!m) { return; }
    u8 globalIndex = gNetworkPlayers[m->playerIndex].globalIndex;
    if (globalIndex == UNKNOWN_GLOBAL_INDEX) { globalIndex = 0; }
    if (sIntroWarpPipeObj[globalIndex] == NULL) {
        sIntroWarpPipeObj[globalIndex] =
            spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_CASTLE_GROUNDS_WARP_PIPE,
                bhvStaticObject, m->pos[0], 260, m->pos[2], 0, 180, 0);
    }

    if (m->actionTimer++ > 1) {
        m->vel[1] = 60.0f;
        m->faceAngle[1] = m->area->camera->yaw;
        advance_cutscene_step(m);
        m->actionArg = 3;
        m->actionTimer = 110;
    }
}
#undef TIMER_RAISE_PIPE

static void intro_cutscene_jump_out_of_pipe(struct MarioState *m) {
    if (!m) { return; }
    if (m->actionTimer <= 1) {
        u8 globalIndex = gNetworkPlayers[m->playerIndex].globalIndex;
        if (globalIndex == UNKNOWN_GLOBAL_INDEX) { globalIndex = 0; }
        if (sIntroWarpPipeObj[globalIndex] != NULL) {
            m->pos[0] = sIntroWarpPipeObj[globalIndex]->oPosX;
            m->pos[1] = sIntroWarpPipeObj[globalIndex]->oPosY;
            m->pos[2] = sIntroWarpPipeObj[globalIndex]->oPosZ;
        }
    }

    if (m->actionTimer == 25) {
        gHudDisplay.flags = HUD_DISPLAY_DEFAULT;
    }

    if (m->actionTimer++ >= 118) {
        m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

#ifdef VERSION_EU
        // For some reason these calls were swapped.
        play_sound_if_no_flag(m, SOUND_ACTION_HIT_3, MARIO_ACTION_SOUND_PLAYED);
        play_character_sound_if_no_flag(m, CHAR_SOUND_YAHOO, MARIO_MARIO_SOUND_PLAYED);
#else
        play_character_sound_if_no_flag(m, CHAR_SOUND_YAHOO, MARIO_MARIO_SOUND_PLAYED);
#ifndef VERSION_JP
        play_sound_if_no_flag(m, SOUND_ACTION_HIT_3, MARIO_ACTION_SOUND_PLAYED);
#endif
#endif

        set_character_animation(m, CHAR_ANIM_SINGLE_JUMP);
        mario_set_forward_vel(m, 10.0f);
        if (perform_air_step(m, 0) == AIR_STEP_LANDED) {
            sound_banks_enable(SEQ_PLAYER_SFX, SOUND_BANKS_DISABLED_DURING_INTRO_CUTSCENE);
            play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
#ifndef VERSION_JP
            play_character_sound(m, CHAR_SOUND_HAHA);
#endif
            advance_cutscene_step(m);
        }
    }
}

static void intro_cutscene_land_outside_pipe(struct MarioState *m) {
    set_character_animation(m, CHAR_ANIM_LAND_FROM_SINGLE_JUMP);

    if (is_anim_at_end(m)) {
        advance_cutscene_step(m);
    }

    stop_and_set_height_to_floor(m);
}

static void intro_cutscene_lower_pipe(struct MarioState *m) {
    if (!m) { return; }
    u8 globalIndex = gNetworkPlayers[m->playerIndex].globalIndex;
    if (globalIndex == UNKNOWN_GLOBAL_INDEX) { globalIndex = 0; }
    if (m->actionTimer++ == 0) {
        if (sIntroWarpPipeObj[globalIndex] != NULL) {
            play_sound(SOUND_MENU_ENTER_PIPE, sIntroWarpPipeObj[globalIndex]->header.gfx.cameraToObject);
        }
        set_character_animation(m, CHAR_ANIM_FIRST_PERSON);
    }

    if (sIntroWarpPipeObj[globalIndex] != NULL) {
        sIntroWarpPipeObj[globalIndex]->oPosY -= 5.0f;
        if (sIntroWarpPipeObj[globalIndex]->oPosY <= 50.0f) {
            obj_mark_for_deletion(sIntroWarpPipeObj[globalIndex]);
            advance_cutscene_step(m);
        }
    } else {
        advance_cutscene_step(m);
    }

    stop_and_set_height_to_floor(m);
}

static void intro_cutscene_set_mario_to_idle(struct MarioState *m) {
    if (!m || !gCamera) { return; }
    if (gCamera->cutscene == 0) {
        if (m->playerIndex == 0) {
            gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        }
        set_mario_action(m, ACT_IDLE, 0);
    }

    stop_and_set_height_to_floor(m);
}

enum {
    INTRO_CUTSCENE_HIDE_HUD_AND_MARIO,
    INTRO_CUTSCENE_PEACH_LAKITU_SCENE,
    INTRO_CUTSCENE_RAISE_PIPE,
    INTRO_CUTSCENE_JUMP_OUT_OF_PIPE,
    INTRO_CUTSCENE_LAND_OUTSIDE_PIPE,
    INTRO_CUTSCENE_LOWER_PIPE,
    INTRO_CUTSCENE_SET_MARIO_TO_IDLE,
    INTRO_CUTSCENE_RAISE_PIPE_MAIN_MENU
};

static s32 act_intro_cutscene(struct MarioState *m) {
    if (!m) { return 0; }
    switch (m->actionArg) {
        case INTRO_CUTSCENE_HIDE_HUD_AND_MARIO:
            intro_cutscene_hide_hud_and_mario(m);
            break;
        case INTRO_CUTSCENE_PEACH_LAKITU_SCENE:
            intro_cutscene_peach_lakitu_scene(m);
            break;
        case INTRO_CUTSCENE_RAISE_PIPE:
            intro_cutscene_raise_pipe(m);
            break;
        case INTRO_CUTSCENE_JUMP_OUT_OF_PIPE:
            intro_cutscene_jump_out_of_pipe(m);
            break;
        case INTRO_CUTSCENE_LAND_OUTSIDE_PIPE:
            intro_cutscene_land_outside_pipe(m);
            break;
        case INTRO_CUTSCENE_LOWER_PIPE:
            intro_cutscene_lower_pipe(m);
            break;
        case INTRO_CUTSCENE_SET_MARIO_TO_IDLE:
            intro_cutscene_set_mario_to_idle(m);
            break;
        case INTRO_CUTSCENE_RAISE_PIPE_MAIN_MENU:
            intro_cutscene_raise_pipe_main_menu(m);
            break;
    }
    return FALSE;
}

static void jumbo_star_offset(struct MarioState* m) {
    if (!m) { return; }
    m->pos[0] += 300.0f * sins(m->faceAngle[1] + 0x4000 * m->playerIndex);
    m->pos[2] += 300.0f * coss(m->faceAngle[1] + 0x4000 * m->playerIndex);
}

// jumbo star cutscene: Mario lands after grabbing the jumbo star
static void jumbo_star_cutscene_falling(struct MarioState *m) {
    if (!m) { return; }
    if (m->actionState == 0) {
        m->input |= INPUT_A_DOWN;
        m->flags |= (MARIO_WING_CAP | MARIO_CAP_ON_HEAD);

        m->faceAngle[1] = -0x8000;
        m->pos[0] = 100.0f * m->playerIndex;
        m->pos[2] = 0.0f;

        mario_set_forward_vel(m, 0.0f);
        set_character_animation(m, CHAR_ANIM_GENERAL_FALL);

        if (perform_air_step(m, 1) == AIR_STEP_LANDED) {
            play_cutscene_music(SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_VICTORY));
            play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
            m->actionState++;
        }
    } else {
        set_character_animation(m, CHAR_ANIM_GENERAL_LAND);
        if (is_anim_at_end(m)) {
            m->statusForCamera->cameraEvent = CAM_EVENT_START_GRAND_STAR;
            advance_cutscene_step(m);
        }
    }
}

// jumbo star cutscene: Mario takes off
static s32 jumbo_star_cutscene_taking_off(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;

    if (m->actionState == 0) {
        set_character_animation(m, CHAR_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN);
        marioObj->rawData.asF32[0x22] = 0.0f;

        if (is_anim_past_end(m)) {
            play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
            m->actionState++;
        }
    } else {
        s32 animFrame = set_character_animation(m, CHAR_ANIM_FINAL_BOWSER_WING_CAP_TAKE_OFF);
        if (animFrame == 3 || animFrame == 28 || animFrame == 60) {
            play_sound_and_spawn_particles(m, SOUND_ACTION_TERRAIN_JUMP, 1);
        }
        if (animFrame >= 3) {
            marioObj->rawData.asF32[0x22] -= 32.0f;
        }

        switch (animFrame) {
            case 3:
                play_character_sound_offset(m, CHAR_SOUND_YAH_WAH_HOO, (gAudioRandom % 3 << 16));
                break;

            case 28:
                play_character_sound(m, CHAR_SOUND_HOOHOO);
                break;

            case 60:
                play_character_sound(m, CHAR_SOUND_YAHOO);
                break;
        }
        set_mario_particle_flags(m, PARTICLE_SPARKLES, FALSE);

        if (is_anim_past_end(m)) {
            advance_cutscene_step(m);
        }
    }

    vec3f_set(m->pos, 0.0f, 307.0, marioObj->rawData.asF32[0x22]);
    m->pos[0] += 100.0f * m->playerIndex;

    update_mario_pos_for_anim(m);
    vec3f_copy(marioObj->header.gfx.pos, m->pos);
    vec3s_set(marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);

    // not sure why they did this, probably was from being used to action
    // functions
    return FALSE;
}

// jumbo star cutscene: Mario flying
static s32 jumbo_star_cutscene_flying(struct MarioState *m) {
    if (!m) { return 0; }
    Vec3f targetPos;

    switch (m->actionState) {
        case 0:
            set_character_animation(m, CHAR_ANIM_WING_CAP_FLY);
            anim_spline_init(m, sJumboStarKeyframes);
            m->actionState++;
            // fall through
        case 1:
            if (anim_spline_poll(m, targetPos)) {
                // does this twice
                set_mario_action(m, ACT_FREEFALL, 0);
                m->actionState++;
            } else {
                targetPos[0] += 100.0f * m->playerIndex;
                float heightScalar = min(m->actionTimer / 30.0f, 1.0f);
                targetPos[1] -= 100.0f * m->playerIndex * heightScalar;

                f32 targetDX = targetPos[0] - m->pos[0];
                f32 targetDY = targetPos[1] - m->pos[1];
                f32 targetDZ = targetPos[2] - m->pos[2];
                f32 targetHyp = sqrtf(targetDX * targetDX + targetDZ * targetDZ);
                s16 targetAngle = atan2s(targetDZ, targetDX);

                vec3f_copy(m->pos, targetPos);
                m->marioObj->header.gfx.angle[0] = -atan2s(targetHyp, targetDY);
                m->marioObj->header.gfx.angle[1] = targetAngle;
                m->marioObj->header.gfx.angle[2] = ((m->faceAngle[1] - targetAngle) << 16 >> 16) * 20;
                m->faceAngle[1] = targetAngle;
            }
            break;
        case 2:
            set_mario_action(m, ACT_FREEFALL, 0);
            break;
    }

    m->marioBodyState->handState = MARIO_HAND_RIGHT_OPEN;
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    set_mario_particle_flags(m, PARTICLE_SPARKLES, FALSE);

    if (m->actionTimer++ == 500 && m->playerIndex == 0) {
        level_trigger_warp(m, WARP_OP_CREDITS_START);
    }

    return FALSE;
}

enum { JUMBO_STAR_CUTSCENE_FALLING, JUMBO_STAR_CUTSCENE_TAKING_OFF, JUMBO_STAR_CUTSCENE_FLYING };

static s32 act_jumbo_star_cutscene(struct MarioState *m) {
    if (!m) { return 0; }
    switch (m->actionArg) {
        case JUMBO_STAR_CUTSCENE_FALLING:
            jumbo_star_cutscene_falling(m);
            break;
        case JUMBO_STAR_CUTSCENE_TAKING_OFF:
            jumbo_star_cutscene_taking_off(m);
            break;
        case JUMBO_STAR_CUTSCENE_FLYING:
            jumbo_star_cutscene_flying(m);
            break;
    }
    return FALSE;
}

void generate_yellow_sparkles(s16 x, s16 y, s16 z, f32 radius) {
    static s32 sSparkleGenTheta = 0;
    static s32 sSparkleGenPhi = 0;

    s16 offsetX = radius * coss(sSparkleGenTheta) * sins(sSparkleGenPhi);
    s16 offsetY = radius * sins(sSparkleGenTheta);
    s16 offsetZ = radius * coss(sSparkleGenTheta) * coss(sSparkleGenPhi);

    spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_NONE, bhvSparkleSpawn, x + offsetX, y + offsetY,
                              z + offsetZ, 0, 0, 0);

    //! copy paste error
    offsetX = offsetX * 4 / 3;
    offsetX = offsetY * 4 / 3;
    offsetX = offsetZ * 4 / 3;

    spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_NONE, bhvSparkleSpawn, x - offsetX, y - offsetY,
                              z - offsetZ, 0, 0, 0);

    sSparkleGenTheta += 0x3800;
    sSparkleGenPhi += 0x6000;
}

// not sure what this does, returns the height of the floor.
// (animation related?)
static f32 end_obj_set_visual_pos(struct Object *o) {
    struct Surface *surf;
    Vec3s sp24;

    find_mario_anim_flags_and_translation(o, o->header.gfx.angle[1], sp24);

    f32 x = o->header.gfx.pos[0] + sp24[0];
    f32 y = o->header.gfx.pos[1] + 10.0f;
    f32 z = o->header.gfx.pos[2] + sp24[2];

    return find_floor(x, y, z, &surf);
}

// make Mario fall and soften wing cap gravity
static void end_peach_cutscene_mario_falling(struct MarioState *m) {
    if (!m) { return; }
    if (m->actionTimer == 1) {
        m->statusForCamera->cameraEvent = CAM_EVENT_START_ENDING;
    }

    m->input |= INPUT_A_DOWN;
    m->flags |= (MARIO_WING_CAP | MARIO_CAP_ON_HEAD);

    set_character_animation(m, CHAR_ANIM_GENERAL_FALL);
    mario_set_forward_vel(m, 0.0f);

    if (perform_air_step(m, 0) == AIR_STEP_LANDED) {
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
        advance_cutscene_step(m);
    }
}

// set Mario on the ground, wait and spawn the jumbo star outside the castle.
static void end_peach_cutscene_mario_landing(struct MarioState *m) {
    if (!m) { return; }
    set_character_animation(m, CHAR_ANIM_GENERAL_LAND);
    stop_and_set_height_to_floor(m);

    if (is_anim_at_end(m)) {
        // make wing cap run out
        m->capTimer = 60;

        if (m->playerIndex == 0) {
            sEndJumboStarObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_STAR, bhvStaticObject, 0,
                                                         2528, -1800, 0, 0, 0);
            if (sEndJumboStarObj != NULL) {
                obj_scale(sEndJumboStarObj, 3.0);
            }
        }
        advance_cutscene_step(m);
    }
}

// raise hand animation, lower hand animation, do some special effects
static void end_peach_cutscene_summon_jumbo_star(struct MarioState *m) {
    if (!m) { return; }
    set_character_animation(m, m->actionState == 0 ? CHAR_ANIM_CREDITS_RAISE_HAND
                                               : CHAR_ANIM_CREDITS_LOWER_HAND);
    if (m->playerIndex != 0) { return; }
    if (m->actionState == 0 && is_anim_past_end(m)) {
        m->actionState++;
    }
    if (m->actionTimer == 90) {
        play_cutscene_music(SEQUENCE_ARGS(0, SEQ_EVENT_CUTSCENE_ENDING));
    }
    if (m->actionTimer == 255) {
        advance_cutscene_step(m);
    }

    if (sEndJumboStarObj) {
        sEndJumboStarObj->oFaceAngleYaw += 0x0400;
        generate_yellow_sparkles(0, 2528, -1800, 250.0f);
        play_sound(SOUND_AIR_PEACH_TWINKLE, sEndJumboStarObj->header.gfx.cameraToObject);
    }
}

#if defined(VERSION_EU)
    //#define TIMER_FADE_IN_PEACH 201
    //#define TIMER_DESCEND_PEACH 280
    #define TIMER_FADE_IN_PEACH 276
    #define TIMER_DESCEND_PEACH 355
#elif defined(VERSION_SH)
    #define TIMER_FADE_IN_PEACH 276
    #define TIMER_DESCEND_PEACH 400
#else
    #define TIMER_FADE_IN_PEACH 276
    #define TIMER_DESCEND_PEACH 355
#endif

// free peach from the stained glass window
static void end_peach_cutscene_spawn_peach(struct MarioState *m) {
    if (!m) { return; }
    if (m->playerIndex != 0) { return; }
    if (m->actionTimer == 1) {
        play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 14, 255, 255, 255);
    }
    if (m->actionTimer == 2) {
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
    }
    if (m->actionTimer == 44) {
        play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 192, 255, 255, 255);
    }
    if (m->actionTimer == 40) {
        if (sEndJumboStarObj) { obj_mark_for_deletion(sEndJumboStarObj); }

        sEndPeachObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_PEACH, bhvEndPeach, 0, 2428,
                                                 -1300, 0, 0, 0);
        gCutsceneFocus = sEndPeachObj;

        sEndRightToadObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_TOAD, bhvEndToad, 200,
                                                     906, -1290, 0, 0, 0);

        sEndLeftToadObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_TOAD, bhvEndToad, -200,
                                                    906, -1290, 0, 0, 0);

        if (sEndPeachObj != NULL) { sEndPeachObj->oOpacity = 127; }
        if (sEndRightToadObj != NULL) { sEndRightToadObj->oOpacity = 255; }
        if (sEndLeftToadObj != NULL) { sEndLeftToadObj->oOpacity = 255; }

        D_8032CBE4 = 4;
        sEndPeachAnimation = 4;

        sEndToadAnims[0] = 4;
        sEndToadAnims[1] = 5;
    }

    if (m->actionTimer >= TIMER_FADE_IN_PEACH && sEndPeachObj != NULL) {
        sEndPeachObj->oOpacity = camera_approach_f32_symmetric(sEndPeachObj->oOpacity, 255.0f, 2.0f);
    }
    if (m->actionTimer >= 40) {
        generate_yellow_sparkles(0, 2628, -1300, 150.0f);
    }

    if (m->actionTimer == TIMER_DESCEND_PEACH) {
        advance_cutscene_step(m);
    }
    // probably added sounds later and missed the previous >= 40 check
    if (m->actionTimer >= 40 && sEndPeachObj != NULL) {
        play_sound(SOUND_AIR_PEACH_TWINKLE, sEndPeachObj->header.gfx.cameraToObject);
    }
}

#ifdef VERSION_EU
    //#define TIMER_RUN_TO_PEACH 531
    #define TIMER_RUN_TO_PEACH 584
#else
    #define TIMER_RUN_TO_PEACH 584
#endif

// descend peach
static void end_peach_cutscene_descend_peach(struct MarioState *m) {
    if (!m) { return; }
    if (m->playerIndex != 0) { return; }
    generate_yellow_sparkles(0, sEndPeachObj->oPosY, -1300, 150.0f);

    if (sEndPeachObj->oPosY >= 1300.0f) {
        if (m->actionState < 60) {
            m->actionState += 5;
        }
    } else {
        if (m->actionState >= 27) {
            m->actionState -= 2;
        }
        set_character_animation(m, CHAR_ANIM_CREDITS_RETURN_FROM_LOOK_UP);
    }

    if ((sEndPeachObj->oPosY -= m->actionState / 10) <= 907.0f) {
        sEndPeachObj->oPosY = 906.0f;
    }

    play_sound(SOUND_AIR_PEACH_TWINKLE, sEndPeachObj->header.gfx.cameraToObject);

    if (m->actionTimer >= TIMER_RUN_TO_PEACH) {
        advance_cutscene_step(m);
    }
}

#undef TIMER_RUN_TO_PEACH

// Mario runs to peach
static void end_peach_cutscene_run_to_peach(struct MarioState *m) {
    if (!m) { return; }
    struct Surface *surf;

    if (m->actionTimer == 22) {
        sEndPeachAnimation = 5;
    }

    if ((m->pos[2] -= 20.0f) <= -1181.0f) {
        m->pos[2] = -1180.0f;
        advance_cutscene_step(m);
    }

    m->pos[1] = find_floor(m->pos[0], m->pos[1], m->pos[2], &surf);

    set_character_anim_with_accel(m, CHAR_ANIM_RUNNING, 0x00080000);
    play_step_sound(m, 9, 45);

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    set_mario_particle_flags(m, PARTICLE_DUST, FALSE);
}

// dialog 1
// "Mario!"
// "The power of the Stars is restored to the castle..."
static void end_peach_cutscene_dialog_1(struct MarioState *m) {
    if (!m) { return; }
    s32 animFrame = set_character_animation(m, m->actionState == 0 ? CHAR_ANIM_CREDITS_TAKE_OFF_CAP
                                                               : CHAR_ANIM_CREDITS_LOOK_UP);

    if (m->actionState == 0) {
        if (animFrame == 8) {
            cutscene_take_cap_off(m);
        }

        if (is_anim_at_end(m)) {
            m->actionState++;
        }
    }

    if (m->playerIndex != 0) { return; }

    switch (m->actionTimer) {
#ifdef VERSION_SH
        case 110:
#else
        case 80:
#endif
            sEndPeachAnimation = 6;
            break;

#ifdef VERSION_SH
        case 111:
#else
        case 81:
#endif
            D_8032CBE4 = 3;
            break;

#ifdef VERSION_SH
        case 175:
#else
        case 145:
#endif
            D_8032CBE4 = 2;
            break;

#ifdef VERSION_SH
        case 258:
#else
        case 228:
#endif
            D_8032CBE4 = 1;
            D_8032CBE8 = 1;
            break;

#ifdef VERSION_SH
        case 260:
#else
        case 230:
#endif
            set_cutscene_message(160, 227, 0, 30);
#ifndef VERSION_JP
            seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            play_sound(SOUND_PEACH_MARIO, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;

#ifdef VERSION_SH
        case 305:
#else
        case 275:
#endif
            D_8032CBE4 = 0;
            D_8032CBE8 = 0;
            break;

#ifdef VERSION_SH
        case 320:
#else
        case 290:
#endif
            set_cutscene_message(160, 227, 1, 60);
#ifndef VERSION_JP
            play_sound(SOUND_PEACH_POWER_OF_THE_STARS, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;

#ifdef VERSION_SH
        case 510:
#else
        case 480:
#endif
            advance_cutscene_step(m);
            break;
    }
}

#if defined(VERSION_EU)
    //#define TIMER_SOMETHING_SPECIAL 150
    //#define TIMER_PEACH_KISS        260
    #define TIMER_SOMETHING_SPECIAL 130
    #define TIMER_PEACH_KISS        200
#elif defined(VERSION_SH)
    #define TIMER_SOMETHING_SPECIAL 170
    #define TIMER_PEACH_KISS        250
#else
    #define TIMER_SOMETHING_SPECIAL 130
    #define TIMER_PEACH_KISS        200
#endif

// dialog 2
// "...and it's all thanks to you!"
// "Thank you Mario!"
// "We have to do something special for you..."
static void end_peach_cutscene_dialog_2(struct MarioState *m) {
    if (!m) { return; }
    if (m->playerIndex != 0) { return; }
    sEndPeachAnimation = 9;

    switch (m->actionTimer) {
#ifdef VERSION_SH
        case 39:
#else
        case 29:
#endif
            set_cutscene_message(160, 227, 2, 30);
#ifndef VERSION_JP
            play_sound(SOUND_PEACH_THANKS_TO_YOU, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;

#ifdef VERSION_SH
        case 65:
#else
        case 45:
#endif
            D_8032CBE8 = 1;
            break;

#ifdef VERSION_SH
        case 105:
#else
        case 75:
#endif
            set_cutscene_message(160, 227, 3, 30);
#ifndef VERSION_JP
            play_sound(SOUND_PEACH_THANK_YOU_MARIO, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;

        case TIMER_SOMETHING_SPECIAL:
            set_cutscene_message(160, 227, 4, 40);
#ifndef VERSION_JP
            play_sound(SOUND_PEACH_SOMETHING_SPECIAL, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;

        case TIMER_PEACH_KISS:
            advance_cutscene_step(m);
            break;
    }
}

#undef TIMER_SOMETHING_SPECIAL
#undef TIMER_PEACH_KISS

// blink twice then have half-shut eyes (see end_peach_cutscene_kiss_from_peach)
static u8 sMarioBlinkOverride[20] = {
    MARIO_EYES_HALF_CLOSED, MARIO_EYES_HALF_CLOSED, MARIO_EYES_CLOSED, MARIO_EYES_CLOSED,
    MARIO_EYES_HALF_CLOSED, MARIO_EYES_HALF_CLOSED, MARIO_EYES_OPEN,   MARIO_EYES_OPEN,
    MARIO_EYES_HALF_CLOSED, MARIO_EYES_HALF_CLOSED, MARIO_EYES_CLOSED, MARIO_EYES_CLOSED,
    MARIO_EYES_HALF_CLOSED, MARIO_EYES_HALF_CLOSED, MARIO_EYES_OPEN,   MARIO_EYES_OPEN,
    MARIO_EYES_HALF_CLOSED, MARIO_EYES_HALF_CLOSED, MARIO_EYES_CLOSED, MARIO_EYES_CLOSED,
};

static void end_peach_cutscene_kiss_from_peach(struct MarioState *m) {
    if (!m) { return; }
    sEndPeachAnimation = 10;

    if (m->actionTimer >= 90) {
        m->marioBodyState->eyeState =
            m->actionTimer < 110 ? sMarioBlinkOverride[m->actionTimer - 90] : MARIO_EYES_HALF_CLOSED;
    }

    switch (m->actionTimer) {
        case 8:
            D_8032CBE8 = 0;
            break;

        case 10:
            D_8032CBE4 = 3;
            break;

        case 50:
            D_8032CBE4 = 4;
            break;

        case 75:
            m->marioBodyState->eyeState = MARIO_EYES_HALF_CLOSED;
            break;

        case 76:
            m->marioBodyState->eyeState = MARIO_EYES_CLOSED;
            break;

        case 100:
            D_8032CBE4 = 3;
            break;

        case 136:
            D_8032CBE4 = 0;
            break;

        case 140:
            advance_cutscene_step(m);
            break;
    }
}

static void end_peach_cutscene_star_dance(struct MarioState *m) {
    if (!m) { return; }
    u8 nonMario = (gNetworkPlayers[m->playerIndex].globalIndex != 0);
    s32 animFrame = set_character_animation(m, nonMario ? CHAR_ANIM_START_SLEEP_SITTING : CHAR_ANIM_CREDITS_PEACE_SIGN);

    if (animFrame == (nonMario ? 0 : 77)) {
        cutscene_put_cap_on(m);
    }
    if (animFrame == 88 && m->playerIndex == 0) {
        play_character_sound(m, CHAR_SOUND_HERE_WE_GO);
    }
    if (!nonMario && animFrame >= 98) {
        m->marioBodyState->handState = MARIO_HAND_PEACE_SIGN;
    }

    if (m->actionTimer < 52) {
        m->marioBodyState->eyeState = MARIO_EYES_HALF_CLOSED;
    }

    switch (m->actionTimer) {
        case 70:
            D_8032CBE4 = 1;
            break;

        case 86:
            D_8032CBE4 = 2;
            break;

        case 90:
            D_8032CBE4 = 3;
            break;

        case 120:
            D_8032CBE4 = 0;
            break;

        case 140:
            if (m->playerIndex == 0) {
#ifndef VERSION_JP
                seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
#endif
                play_cutscene_music(SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_CREDITS));
            }
            break;

        case 142:
            advance_cutscene_step(m);
            break;
    }
}

// dialog 3
// "Listen everybody"
// "let's bake a delicious cake..."
// "...for Mario..."
static void end_peach_cutscene_dialog_3(struct MarioState *m) {
    if (!m) { return; }
    u8 nonMario = (gNetworkPlayers[m->playerIndex].globalIndex != 0);
    set_character_animation(m, nonMario ? CHAR_ANIM_SLEEP_IDLE : CHAR_ANIM_FIRST_PERSON);
    if (m->playerIndex != 0) { return; }
    sEndPeachObj->oPosY = end_obj_set_visual_pos(sEndPeachObj);
    sEndRightToadObj->oPosY = end_obj_set_visual_pos(sEndRightToadObj);
    sEndLeftToadObj->oPosY = end_obj_set_visual_pos(sEndLeftToadObj);

    switch (m->actionTimer) {
        case 1:
            sEndPeachAnimation = 0;
            sEndToadAnims[0] = 0;
            sEndToadAnims[1] = 2;
            D_8032CBE8 = 1;
            set_cutscene_message(160, 227, 5, 30);
#ifndef VERSION_JP
            play_sound(SOUND_PEACH_BAKE_A_CAKE, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;

        case 55:
            set_cutscene_message(160, 227, 6, 40);
            break;

        case 130:
            set_cutscene_message(160, 227, 7, 50);
#ifndef VERSION_JP
            play_sound(SOUND_PEACH_FOR_MARIO, sEndPeachObj->header.gfx.cameraToObject);
#endif
            break;
    }

    if (m->actionTimer == 350) {
        advance_cutscene_step(m);
    }
}

// "Mario!"
static void end_peach_cutscene_run_to_castle(struct MarioState *m) {
    if (!m) { return; }
    u8 nonMario = (gNetworkPlayers[m->playerIndex].globalIndex != 0);
    if (nonMario) {
        set_character_animation(m, m->actionState == 0 ? CHAR_ANIM_SLEEP_START_LYING
                                                   : CHAR_ANIM_SLEEP_LYING);
    } else {
        set_character_animation(m, m->actionState == 0 ? CHAR_ANIM_CREDITS_START_WALK_LOOK_UP
                                                   : CHAR_ANIM_CREDITS_LOOK_BACK_THEN_RUN);
        m->marioObj->header.gfx.pos[1] = end_obj_set_visual_pos(m->marioObj);
    }

    if (m->actionState == 0 && is_anim_past_end(m)) {
        m->actionState = 1;
    }

    if (m->actionTimer == 95 && m->playerIndex == 0) {
        set_cutscene_message(160, 227, 0, 40);
#ifndef VERSION_JP
        play_sound(SOUND_PEACH_MARIO2, sEndPeachObj->header.gfx.cameraToObject);
#endif
    }
    if (m->actionTimer == 389) {
        advance_cutscene_step(m);
    }
}

static void end_peach_cutscene_fade_out(struct MarioState *m) {
    if (!m) { return; }
    if (m->actionState == 0 && m->playerIndex == 0) {
        level_trigger_warp(m, WARP_OP_CREDITS_NEXT);
        gPaintingMarioYEntry = 1500.0f; // ensure medium water level in WDW credits cutscene
        m->actionState = 1;
    }
}

enum {
    END_PEACH_CUTSCENE_MARIO_FALLING,
    END_PEACH_CUTSCENE_MARIO_LANDING,
    END_PEACH_CUTSCENE_SUMMON_JUMBO_STAR,
    END_PEACH_CUTSCENE_SPAWN_PEACH,
    END_PEACH_CUTSCENE_DESCEND_PEACH,
    END_PEACH_CUTSCENE_RUN_TO_PEACH,
    END_PEACH_CUTSCENE_DIALOG_1,
    END_PEACH_CUTSCENE_DIALOG_2,
    END_PEACH_CUTSCENE_KISS_FROM_PEACH,
    END_PEACH_CUTSCENE_STAR_DANCE,
    END_PEACH_CUTSCENE_DIALOG_3,
    END_PEACH_CUTSCENE_RUN_TO_CASTLE,
    END_PEACH_CUTSCENE_FADE_OUT
};

static s32 act_end_peach_cutscene(struct MarioState *m) {
    if (!m) { return 0; }
    switch (m->actionArg) {
        case END_PEACH_CUTSCENE_MARIO_FALLING:
            end_peach_cutscene_mario_falling(m);
            break;
        case END_PEACH_CUTSCENE_MARIO_LANDING:
            end_peach_cutscene_mario_landing(m);
            break;
        case END_PEACH_CUTSCENE_SUMMON_JUMBO_STAR:
            end_peach_cutscene_summon_jumbo_star(m);
            break;
        case END_PEACH_CUTSCENE_SPAWN_PEACH:
            end_peach_cutscene_spawn_peach(m);
            break;
        case END_PEACH_CUTSCENE_DESCEND_PEACH:
            end_peach_cutscene_descend_peach(m);
            break;
        case END_PEACH_CUTSCENE_RUN_TO_PEACH:
            end_peach_cutscene_run_to_peach(m);
            break;
        case END_PEACH_CUTSCENE_DIALOG_1:
            end_peach_cutscene_dialog_1(m);
            break;
        case END_PEACH_CUTSCENE_DIALOG_2:
            end_peach_cutscene_dialog_2(m);
            break;
        case END_PEACH_CUTSCENE_KISS_FROM_PEACH:
            end_peach_cutscene_kiss_from_peach(m);
            break;
        case END_PEACH_CUTSCENE_STAR_DANCE:
            end_peach_cutscene_star_dance(m);
            break;
        case END_PEACH_CUTSCENE_DIALOG_3:
            end_peach_cutscene_dialog_3(m);
            break;
        case END_PEACH_CUTSCENE_RUN_TO_CASTLE:
            end_peach_cutscene_run_to_castle(m);
            break;
        case END_PEACH_CUTSCENE_FADE_OUT:
            end_peach_cutscene_fade_out(m);
            break;
    }

    m->actionTimer++;

    if (m->playerIndex == 0) {
        sEndCutsceneVp.vp.vscale[0] = 640;
        sEndCutsceneVp.vp.vscale[1] = 360;
        sEndCutsceneVp.vp.vtrans[0] = 640;
        sEndCutsceneVp.vp.vtrans[1] = 480;
        override_viewport_and_clip(NULL, &sEndCutsceneVp, 0, 0, 0);
    }

    return FALSE;
}

#if defined(VERSION_EU)
    //#define TIMER_CREDITS_SHOW      51
    //#define TIMER_CREDITS_PROGRESS  80
    //#define TIMER_CREDITS_WARP     160
    #define TIMER_CREDITS_SHOW      61
    #define TIMER_CREDITS_PROGRESS  90
    #define TIMER_CREDITS_WARP     200
#elif defined(VERSION_SH)
    #define TIMER_CREDITS_SHOW      61
    #define TIMER_CREDITS_PROGRESS  90
    #define TIMER_CREDITS_WARP     204
#else
    #define TIMER_CREDITS_SHOW      61
    #define TIMER_CREDITS_PROGRESS  90
    #define TIMER_CREDITS_WARP     200
#endif

static s32 act_credits_cutscene(struct MarioState *m) {
    if (!m) { return 0; }
    m->statusForCamera->cameraEvent = CAM_EVENT_START_CREDITS;
    // checks if Mario is underwater (JRB, DDD, SA, etc.)
    if (m->pos[1] < m->waterLevel - 100) {
        if (m->playerIndex == 0 && m->area->camera->mode != CAMERA_MODE_BEHIND_MARIO) {
            set_camera_mode(m->area->camera, CAMERA_MODE_BEHIND_MARIO, 1);
        }
        set_character_animation(m, CHAR_ANIM_WATER_IDLE);
        vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
        // will copy over roll and pitch, if set
        vec3s_copy(m->marioObj->header.gfx.angle, m->faceAngle);
        set_mario_particle_flags(m, PARTICLE_BUBBLE, FALSE);
    } else {
        set_character_animation(m, CHAR_ANIM_FIRST_PERSON);
        if (m->actionTimer > 0) {
            stop_and_set_height_to_floor(m);
        }
    }

    if (m->actionTimer >= TIMER_CREDITS_SHOW) {
        if (m->actionState < 40) {
            m->actionState += 2;
        }

        if (gCurrCreditsEntry != NULL && !gDjuiInMainMenu) {
            if (m->playerIndex == 0) {
                s32 width = m->actionState * 640 / 100;
                s32 height = m->actionState * 480 / 100;

                sEndCutsceneVp.vp.vscale[0] = 640 - width;
                sEndCutsceneVp.vp.vscale[1] = 480 - height;
                sEndCutsceneVp.vp.vtrans[0] = (gCurrCreditsEntry->unk02 & 0x10 ? width : -width) * 56 / 100 + 640;
                sEndCutsceneVp.vp.vtrans[1] = (gCurrCreditsEntry->unk02 & 0x20 ? height : -height) * 66 / 100 + 480;

                override_viewport_and_clip(&sEndCutsceneVp, 0, 0, 0, 0);
            }
        }
    }

    if (gCurrCreditsEntry != NULL) {
        if (m->actionTimer == TIMER_CREDITS_PROGRESS && m->playerIndex == 0) {
            reset_cutscene_msg_fade();
        }

        if (m->actionTimer >= TIMER_CREDITS_PROGRESS && m->playerIndex == 0) {
            sDispCreditsEntry = gCurrCreditsEntry;
        }

        if (m->actionTimer++ == TIMER_CREDITS_WARP && m->playerIndex == 0) {
            level_trigger_warp(m, WARP_OP_CREDITS_NEXT);
        }

        m->marioObj->header.gfx.angle[1] += (gCurrCreditsEntry->unk02 & 0xC0) << 8;
    }

    return FALSE;
}

static s32 act_end_waving_cutscene(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->actionState == 0) {
        m->statusForCamera->cameraEvent = CAM_EVENT_START_END_WAVING;

        sEndPeachObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_PEACH, bhvEndPeach, 60, 906,
                                                 -1180, 0, 0, 0);

        sEndRightToadObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_TOAD, bhvEndToad, 180,
                                                     906, -1170, 0, 0, 0);

        sEndLeftToadObj = spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_TOAD, bhvEndToad, -180,
                                                    906, -1170, 0, 0, 0);

        if (sEndPeachObj != NULL) { sEndPeachObj->oOpacity = 255; }
        if (sEndRightToadObj != NULL) { sEndRightToadObj->oOpacity = 255; }
        if (sEndLeftToadObj != NULL) { sEndLeftToadObj->oOpacity = 255; }

        sEndPeachAnimation = 11;
        sEndToadAnims[0] = 6;
        sEndToadAnims[1] = 7;

        m->actionState = 1;
    }

    set_character_animation(m, CHAR_ANIM_CREDITS_WAVING);
    stop_and_set_height_to_floor(m);

    m->marioObj->header.gfx.angle[1] += 0x8000;
    m->marioObj->header.gfx.pos[0] -= 60.0f;
    m->marioBodyState->handState = MARIO_HAND_RIGHT_OPEN;

    if (m->actionTimer++ == 300) {
        level_trigger_warp(m, WARP_OP_CREDITS_END);
    }

    return FALSE;
}

static s32 check_for_instant_quicksand(struct MarioState *m) {
    if (!m) { return 0; }
    if (m != &gMarioStates[0]) {
        // never kill remote marios
        return FALSE;
    }
    if (m->action == ACT_BUBBLED) { return FALSE; }

    if (m->floor && m->floor->type == SURFACE_INSTANT_QUICKSAND && m->action & ACT_FLAG_INVULNERABLE && m->action != ACT_QUICKSAND_DEATH && m->action != ACT_SHOCKED) {
        update_mario_sound_and_camera(m);
        return drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 0);
    }
    return FALSE;
}

s32 mario_execute_cutscene_action(struct MarioState *m) {
    if (!m) { return FALSE; }

    s32 cancel;

    if (check_for_instant_quicksand(m)) {
        return TRUE;
    }

    if (!smlua_call_action_hook(ACTION_HOOK_EVERY_FRAME, m, &cancel)) {
        /* clang-format off */
        switch (m->action) {
            case ACT_DISAPPEARED:                cancel = act_disappeared(m);                break;
            case ACT_INTRO_CUTSCENE:             cancel = act_intro_cutscene(m);             break;
            case ACT_STAR_DANCE_EXIT:            cancel = act_star_dance(m);                 break;
            case ACT_STAR_DANCE_NO_EXIT:         cancel = act_star_dance(m);                 break;
            case ACT_STAR_DANCE_WATER:           cancel = act_star_dance_water(m);           break;
            case ACT_FALL_AFTER_STAR_GRAB:       cancel = act_fall_after_star_grab(m);       break;
            case ACT_READING_AUTOMATIC_DIALOG:   cancel = act_reading_automatic_dialog(m);   break;
            case ACT_READING_NPC_DIALOG:         cancel = act_reading_npc_dialog(m);         break;
            case ACT_DEBUG_FREE_MOVE:            cancel = act_debug_free_move(m);            break;
            case ACT_READING_SIGN:               cancel = act_reading_sign(m);               break;
            case ACT_JUMBO_STAR_CUTSCENE:        cancel = act_jumbo_star_cutscene(m);        break;
            case ACT_WAITING_FOR_DIALOG:         cancel = act_waiting_for_dialog(m);         break;
            case ACT_STANDING_DEATH:             cancel = act_standing_death(m);             break;
            case ACT_QUICKSAND_DEATH:            cancel = act_quicksand_death(m);            break;
            case ACT_ELECTROCUTION:              cancel = act_electrocution(m);              break;
            case ACT_SUFFOCATION:                cancel = act_suffocation(m);                break;
            case ACT_DEATH_ON_STOMACH:           cancel = act_death_on_stomach(m);           break;
            case ACT_DEATH_ON_BACK:              cancel = act_death_on_back(m);              break;
            case ACT_EATEN_BY_BUBBA:             cancel = act_eaten_by_bubba(m);             break;
            case ACT_END_PEACH_CUTSCENE:         cancel = act_end_peach_cutscene(m);         break;
            case ACT_CREDITS_CUTSCENE:           cancel = act_credits_cutscene(m);           break;
            case ACT_END_WAVING_CUTSCENE:        cancel = act_end_waving_cutscene(m);        break;
            case ACT_PULLING_DOOR:
            case ACT_PUSHING_DOOR:               cancel = act_going_through_door(m);         break;
            case ACT_WARP_DOOR_SPAWN:            cancel = act_warp_door_spawn(m);            break;
            case ACT_EMERGE_FROM_PIPE:           cancel = act_emerge_from_pipe(m);           break;
            case ACT_SPAWN_SPIN_AIRBORNE:        cancel = act_spawn_spin_airborne(m);        break;
            case ACT_SPAWN_SPIN_LANDING:         cancel = act_spawn_spin_landing(m);         break;
            case ACT_EXIT_AIRBORNE:              cancel = act_exit_airborne(m);              break;
            case ACT_EXIT_LAND_SAVE_DIALOG:      cancel = act_exit_land_save_dialog(m);      break;
            case ACT_DEATH_EXIT:                 cancel = act_death_exit(m);                 break;
            case ACT_UNUSED_DEATH_EXIT:          cancel = act_unused_death_exit(m);          break;
            case ACT_FALLING_DEATH_EXIT:         cancel = act_falling_death_exit(m);         break;
            case ACT_SPECIAL_EXIT_AIRBORNE:      cancel = act_special_exit_airborne(m);      break;
            case ACT_SPECIAL_DEATH_EXIT:         cancel = act_special_death_exit(m);         break;
            case ACT_FALLING_EXIT_AIRBORNE:      cancel = act_falling_exit_airborne(m);      break;
            case ACT_UNLOCKING_KEY_DOOR:         cancel = act_unlocking_key_door(m);         break;
            case ACT_UNLOCKING_STAR_DOOR:        cancel = act_unlocking_star_door(m);        break;
            case ACT_ENTERING_STAR_DOOR:         cancel = act_entering_star_door(m);         break;
            case ACT_SPAWN_NO_SPIN_AIRBORNE:     cancel = act_spawn_no_spin_airborne(m);     break;
            case ACT_SPAWN_NO_SPIN_LANDING:      cancel = act_spawn_no_spin_landing(m);      break;
            case ACT_BBH_ENTER_JUMP:             cancel = act_bbh_enter_jump(m);             break;
            case ACT_BBH_ENTER_SPIN:             cancel = act_bbh_enter_spin(m);             break;
            case ACT_TELEPORT_FADE_OUT:          cancel = act_teleport_fade_out(m);          break;
            case ACT_TELEPORT_FADE_IN:           cancel = act_teleport_fade_in(m);           break;
            case ACT_SHOCKED:                    cancel = act_shocked(m);                    break;
            case ACT_SQUISHED:                   cancel = act_squished(m);                   break;
            case ACT_HEAD_STUCK_IN_GROUND:       cancel = act_head_stuck_in_ground(m);       break;
            case ACT_BUTT_STUCK_IN_GROUND:       cancel = act_butt_stuck_in_ground(m);       break;
            case ACT_FEET_STUCK_IN_GROUND:       cancel = act_feet_stuck_in_ground(m);       break;
            case ACT_PUTTING_ON_CAP:             cancel = act_putting_on_cap(m);             break;
            case ACT_TAKING_OFF_CAP:             cancel = act_taking_off_cap(m);             break;
            default:
                LOG_ERROR("Attempted to execute unimplemented action '%04X'", m->action);
                set_mario_action(m, ACT_IDLE, 0);
                return false;
        }
        /* clang-format on */
    }

    if (!cancel && (m->input & INPUT_IN_WATER)) {
        set_mario_particle_flags(m, PARTICLE_IDLE_WATER_WAVE, FALSE);
    }

    return cancel;
}
