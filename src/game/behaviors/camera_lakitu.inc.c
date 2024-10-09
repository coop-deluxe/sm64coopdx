
/**
 * Behavior for bhvCameraLakitu. This includes both the intro lakitu and the
 * lakitu visible in the mirror room.
 * TODO: Processing order relative to bhvCloud
 */

static u8 lakituTargetLocalIndex = UNKNOWN_LOCAL_INDEX;

static u8 bhv_camera_lakitu_ignore_if_true(void) {
    return (lakituTargetLocalIndex == 0);
}

static void bhv_camera_lakitu_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = TRUE;
    *shouldOwn = (lakituTargetLocalIndex == 0);
}

static void bhv_camera_lakitu_on_received_post(u8 localIndex) {
    if (lakituTargetLocalIndex == UNKNOWN_LOCAL_INDEX) {
        lakituTargetLocalIndex = localIndex;
    }
}

/**
 * Init function for camera lakitu.
 * If this is the intro lakitu, despawn unless this is the start of the game.
 * Spawn cloud if not the intro lakitu.
 */
void bhv_camera_lakitu_init(void) {
    if (o->oBehParams2ndByte != CAMERA_LAKITU_BP_FOLLOW_CAMERA) {
        // Despawn unless this is the very beginning of the game
        if (!gNeverEnteredCastle) {
            obj_mark_for_deletion(o);
            return;
        }
    } else {
        spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, o, MODEL_MIST, bhvCloud);
    }
    lakituTargetLocalIndex = UNKNOWN_LOCAL_INDEX;

    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, 4000.0f);
        if (so) {
            so->ignore_if_true = bhv_camera_lakitu_ignore_if_true;
            so->override_ownership = bhv_camera_lakitu_override_ownership;
            so->on_received_post = bhv_camera_lakitu_on_received_post;
            sync_object_init_field(o, &o->oAngleVelPitch);
            sync_object_init_field(o, &o->oFaceAnglePitch);
            sync_object_init_field(o, &o->oCameraLakituBlinkTimer);
            sync_object_init_field(o, &o->oCameraLakituSpeed);
            sync_object_init_field(o, &o->oCameraLakituCircleRadius);
            sync_object_init_field(o, &o->oCameraLakituFinishedDialog);
            sync_object_init_field(o, &o->oCameraLakituPitchVel);
#ifndef VERSION_JP
            sync_object_init_field(o, &o->oCameraLakituUnk104);
#endif
        }
    }
}

static u8 camera_lakitu_intro_act_trigger_cutscene_continue_dialog(void) {
    return (o->oAction == CAMERA_LAKITU_INTRO_ACT_TRIGGER_CUTSCENE);
}

/**
 * Wait for mario to stand on the bridge, then interrupt his action and enter
 * the spawn cloud action.
 */
static void camera_lakitu_intro_act_trigger_cutscene(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!marioState) { return; }
    struct Object* player = marioState->marioObj;

    //! These bounds are slightly smaller than the actual bridge bounds, allowing
    //  the RTA speedrunning method of lakitu skip
    if (player->oPosX > -544.0f && player->oPosX < 545.0f && player->oPosY > 800.0f
        && player->oPosZ > -2000.0f && player->oPosZ < -177.0f)
    {
        if (should_start_or_continue_dialog(marioState, o) && set_mario_npc_dialog(&gMarioStates[0], 2, camera_lakitu_intro_act_trigger_cutscene_continue_dialog) == 1) {
            o->oAction = CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD;
        }
    }
}

static u8 camera_lakitu_intro_act_spawn_cloud_continue_dialog(void) {
    return (o->oAction == CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD);
}
/**
 * Warp up into the air and spawn cloud, then enter the TODO action.
 */
static void camera_lakitu_intro_act_spawn_cloud(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (marioState && should_start_or_continue_dialog(marioState, o) && set_mario_npc_dialog(&gMarioStates[0], 2, camera_lakitu_intro_act_spawn_cloud_continue_dialog) == 2) {
        o->oAction = CAMERA_LAKITU_INTRO_ACT_UNK2;

        o->oPosX = 1800.0f;
        o->oPosY = 2400.0f;
        o->oPosZ = -2400.0f;

        o->oMoveAnglePitch = 0x4000;
        o->oCameraLakituSpeed = 60.0f;
        o->oCameraLakituCircleRadius = 1000.0f;

        spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, o, MODEL_MIST, bhvCloud);
    }
}

u8 camera_lakitu_intro_act_show_dialog_continue_dialog(void) { return o->oCameraLakituFinishedDialog != TRUE; }

/**
 * Circle down to mario, show the dialog, then fly away.
 */
static void camera_lakitu_intro_act_show_dialog(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (lakituTargetLocalIndex != UNKNOWN_LOCAL_INDEX) {
        marioState = &gMarioStates[lakituTargetLocalIndex];
    }
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    s16 targetMovePitch = 0;
    s16 targetMoveYaw = 0;

    cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY);

    // Face toward mario
    if (marioState) {
        o->oFaceAnglePitch = obj_turn_pitch_toward_mario(marioState, 120.0f, 0);
    }
    o->oFaceAngleYaw = angleToPlayer;

    // After finishing dialog, fly away and despawn
    if (o->oCameraLakituFinishedDialog) {
        approach_f32_ptr(&o->oCameraLakituSpeed, 60.0f, 3.0f);
        if (distanceToPlayer > 6000.0f) {
            obj_mark_for_deletion(o);
        }

        targetMovePitch = -0x3000;
        targetMoveYaw = -0x6000;
    } else {
        if (o->oCameraLakituSpeed != 0.0f) {
            if (distanceToPlayer > 5000.0f) {
                targetMovePitch = o->oMoveAnglePitch;
                targetMoveYaw = angleToPlayer;
            } else {
                if (lakituTargetLocalIndex == UNKNOWN_LOCAL_INDEX) {
                    if (marioState && marioState->playerIndex == 0) {
                        lakituTargetLocalIndex = 0;
                    } else {
                        goto afterChase;
                    }
                }
                // Stay moving in a circle around mario
                s16 turnAmount = 0x4000
                                 - atan2s(o->oCameraLakituCircleRadius,
                                          distanceToPlayer - o->oCameraLakituCircleRadius);
                if ((s16)(o->oMoveAngleYaw - angleToPlayer) < 0) {
                    turnAmount = -turnAmount;
                }

                targetMoveYaw = angleToPlayer + turnAmount;
                targetMovePitch = o->oFaceAnglePitch;

                approach_f32_ptr(&o->oCameraLakituCircleRadius, 200.0f, 50.0f);
                if (distanceToPlayer < 1000.0f) {
#ifndef VERSION_JP
                    if (!o->oCameraLakituUnk104) {
                        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_LAKITU), 0);
                        o->oCameraLakituUnk104 = TRUE;
                    }
#endif

                    // Once within 1000 units, slow down
                    approach_f32_ptr(&o->oCameraLakituSpeed, 20.0f, 1.0f);
                    if (distanceToPlayer < 500.0f
                        && player
                        && abs_angle_diff(player->oFaceAngleYaw, o->oFaceAngleYaw) > 0x7000) {
                        // Once within 500 units and facing toward mario, come
                        // to a stop
                        approach_f32_ptr(&o->oCameraLakituSpeed, 0.0f, 5.0f);
                    }
                }
            }
        } else if (marioState && should_start_or_continue_dialog(marioState, o) && cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 2, DIALOG_UNK2_FLAG_0, CUTSCENE_DIALOG, gBehaviorValues.dialogs.LakituIntroDialog, camera_lakitu_intro_act_show_dialog_continue_dialog) != 0) {
            o->oCameraLakituFinishedDialog = TRUE;
        }
    }

afterChase:
    o->oCameraLakituPitchVel = approach_s16_symmetric(o->oCameraLakituPitchVel, 0x7D0, 0x190);
    obj_move_pitch_approach(targetMovePitch, o->oCameraLakituPitchVel);

    o->oCameraLakituYawVel = approach_s16_symmetric(o->oCameraLakituYawVel, 0x7D0, 0x64);
    cur_obj_rotate_yaw_toward(targetMoveYaw, o->oCameraLakituYawVel);

    // vel y is explicitly computed, so gravity doesn't apply
    obj_compute_vel_from_move_pitch(o->oCameraLakituSpeed);
    cur_obj_move_using_fvel_and_gravity();
}

/**
 * Update function for camera lakitu.
 */
void bhv_camera_lakitu_update(void) {
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        obj_update_blinking(&o->oCameraLakituBlinkTimer, 20, 40, 4);

        if (o->oBehParams2ndByte != CAMERA_LAKITU_BP_FOLLOW_CAMERA) {
            switch (o->oAction) {
                case CAMERA_LAKITU_INTRO_ACT_TRIGGER_CUTSCENE:
                    camera_lakitu_intro_act_trigger_cutscene();
                    break;
                case CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD:
                    camera_lakitu_intro_act_spawn_cloud();
                    break;
                case CAMERA_LAKITU_INTRO_ACT_UNK2:
                    camera_lakitu_intro_act_show_dialog();
                    break;
            }
        } else {
            f32 val0C = (f32) 0x875C3D / 0x800 - gLakituState.curPos[0];
            if (gLakituState.curPos[0] < 1700.0f || val0C < 0.0f) {
                cur_obj_hide();
            } else {
                cur_obj_unhide();

                o->oPosX = gLakituState.curPos[0];
                o->oPosY = gLakituState.curPos[1];
                o->oPosZ = gLakituState.curPos[2];

                o->oHomeX = gLakituState.curFocus[0];
                o->oHomeZ = gLakituState.curFocus[2];

                o->oFaceAngleYaw = -cur_obj_angle_to_home();
                o->oFaceAnglePitch = atan2s(cur_obj_lateral_dist_to_home(),
                                            o->oPosY - gLakituState.curFocus[1]);

                o->oPosX = (f32) 0x875C3D / 0x800 + val0C;
            }
        }
    }
}
