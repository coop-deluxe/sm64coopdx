// tumbling_bridge.c.inc

#include "levels/wf/header.h"
#include "levels/bbh/header.h"
#include "levels/lll/header.h"
#include "levels/bitfs/header.h"

struct Struct8032F34C sTumblingBridgeParams[] = {
    { 9, -512, 0x80, MODEL_WF_TUMBLING_BRIDGE_PART, wf_seg7_collision_tumbling_bridge },
    { 9, -412, 103, MODEL_BBH_TUMBLING_PLATFORM_PART, bbh_seg7_collision_07026B1C },
    { 9, -512, 0x80, MODEL_LLL_FALLING_PLATFORM, lll_seg7_collision_0701D21C },
    { 9, -512, 0x80, MODEL_BITFS_TUMBLING_PLATFORM_PART, bitfs_seg7_collision_07015288 }
};

void bhv_tumbling_bridge_platform_loop(void) {
    u8 isLLL = obj_has_behavior(o->parentObj, bhvLllTumblingBridge);
    if (isLLL && !sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field_with_size(o, &o->activeFlags, 16);
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPosX);
            sync_object_init_field(o, &o->oPosY);
            sync_object_init_field(o, &o->oPosZ);
            sync_object_init_field(o, &o->oVelX);
            sync_object_init_field(o, &o->oVelY);
            sync_object_init_field(o, &o->oVelZ);
            sync_object_init_field(o, &o->oFaceAnglePitch);
            sync_object_init_field(o, &o->oFaceAngleYaw);
            sync_object_init_field(o, &o->oFaceAngleRoll);
        }
    }

    if (o->parentObj && gCurrCourseNum == COURSE_LLL) {
        if (o->parentObj->oIntangibleTimer == -1) {
            cur_obj_hide();
            o->oIntangibleTimer = o->parentObj->oIntangibleTimer;
        } else {
            cur_obj_unhide();
            o->oIntangibleTimer = o->parentObj->oIntangibleTimer;
        }
    }
    switch (o->oAction) {
        case 0:
            if ((o->oInteractStatus & INT_STATUS_INTERACTED) || gMarioStates[0].marioObj->platform == o) {
                o->oAction++;
                o->oTumblingBridgeUnkF4 = random_sign() * 0x80;
                if (!(o->oInteractStatus & INT_STATUS_INTERACTED)) {
                    network_send_collect_item(o);
                }
                o->oInteractStatus &= ~INT_STATUS_INTERACTED;
            }
            break;
        case 1:
            cur_obj_update_floor_height();
            if (o->oTimer > 5) {
                o->oAction++;
                cur_obj_play_sound_2(SOUND_GENERAL_PLATFORM);
            }
            break;
        case 2:
            if (o->oAngleVelPitch < 0x400)
                o->oAngleVelPitch += 0x80;
            if (o->oAngleVelRoll > -0x400 && o->oAngleVelRoll < 0x400)
                o->oAngleVelRoll += o->oTumblingBridgeUnkF4; // acceleration?
            o->oGravity = -3.0f;
            cur_obj_rotate_face_angle_using_vel();
            cur_obj_move_using_fvel_and_gravity();
            if (o->oPosY < o->oFloorHeight - 300.0f) {
                o->oAction++;
                if (isLLL) { network_send_object(o); }
            }
            break;
        case 3:
            break;
    }
    if (o->parentObj && o->parentObj->oAction == 3) {
        obj_mark_for_deletion(o);
        if (isLLL) { network_send_object(o); }
    }

    if (o->parentObj && o->parentObj->oIntangibleTimer != -1) {
        load_object_collision_model();
    } else if (gCurrCourseNum != COURSE_LLL) {
        load_object_collision_model();
    }
}

void tumbling_bridge_act_1(void) {
    struct Object *platformObj;
    s32 i;
    s32 bridgeID = o->oBehParams2ndByte;
    s32 relativePlatformX;
    s32 relativePlatformZ;
    s32 relativePlatformY = 0;
    s32 relativeInitialPlatformY = 0;
    if (!BHV_ARR_CHECK(sTumblingBridgeParams, bridgeID, struct Struct8032F34C)) { return; }

    for (i = 0; i < sTumblingBridgeParams[bridgeID].numBridgeSections; i++) {
        relativePlatformX = 0;
        relativePlatformZ = 0;

        if (bridgeID == 3)
            relativePlatformX = sTumblingBridgeParams[bridgeID].bridgeRelativeStartingXorZ
                                + sTumblingBridgeParams[bridgeID].platformWidth * i;
        else
            relativePlatformZ = sTumblingBridgeParams[bridgeID].bridgeRelativeStartingXorZ
                                + sTumblingBridgeParams[bridgeID].platformWidth * i;

        if (cur_obj_has_behavior(bhvLllTumblingBridge)) {
            if (i % 3 == 0)
                relativePlatformY -= 150;
            relativeInitialPlatformY = 450;
        }

        platformObj = spawn_object_relative(
            0, relativePlatformX, relativePlatformY + relativeInitialPlatformY, relativePlatformZ, o,
            sTumblingBridgeParams[bridgeID].model, bhvTumblingBridgePlatform);
        if (platformObj == NULL) { continue; }
        obj_set_collision_data(platformObj, sTumblingBridgeParams[bridgeID].segAddr);
    }

    o->oAction = 2;
}

void tumbling_bridge_act_2(void) {
    struct MarioState* marioState = nearest_possible_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    cur_obj_hide();
    if (cur_obj_has_behavior(bhvLllTumblingBridge))
        cur_obj_unhide();
    else if (distanceToPlayer > 1200.0f) {
        o->oAction = 3;
        cur_obj_unhide();
    }
}

void tumbling_bridge_act_3(void) {
    cur_obj_unhide();
    o->oAction = 0;
}

void tumbling_bridge_act_0(void) {
    struct MarioState* marioState = nearest_possible_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    if (cur_obj_has_behavior(bhvLllTumblingBridge) || distanceToPlayer < 1000.0f)
        o->oAction = 1;
}

void (*sTumblingBridgeActions[])(void) = { tumbling_bridge_act_0, tumbling_bridge_act_1,
                                           tumbling_bridge_act_2, tumbling_bridge_act_3 };

s16 D_8032F38C[] = { -51, 0,     0, -461, 0,   0, -512, 0,   0,    -2611, 0,
                     0,   -2360, 0, 0,    214, 0, 0,    -50, 1945, 1,     0 };

void bhv_tumbling_bridge_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oIntangibleTimer);
        }
    }

    CUR_OBJ_CALL_ACTION_FUNCTION(sTumblingBridgeActions);
}
