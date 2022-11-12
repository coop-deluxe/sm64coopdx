static u8 dorrieLiftingPlayer[MAX_PLAYERS] = { 0 };

static u8 bhv_dorrie_ignore_if_true(void) {
    return (o->oAction == DORRIE_ACT_RAISE_HEAD) && (gMarioStates[0].marioObj->platform == o || dorrieLiftingPlayer[0]);
}

void dorrie_raise_head(void) {
    s16 startAngle;
    f32 xzDisp;
    f32 yDisp;

    startAngle = o->oDorrieNeckAngle;

    o->oDorrieNeckAngle -= (s16) absf(370.0f * sins(o->oDorrieHeadRaiseSpeed));

    xzDisp = 440.0f * (coss(o->oDorrieNeckAngle) - coss(startAngle));
    yDisp = 440.0f * (sins(o->oDorrieNeckAngle) - sins(startAngle));

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (!dorrieLiftingPlayer[i]) { continue; }
        struct Object* player = gMarioStates[i].marioObj;
        set_mario_pos(&gMarioStates[i],
                      player->oPosX + xzDisp * sins(o->oMoveAngleYaw),
                      player->oPosY - yDisp,
                      player->oPosZ + xzDisp * coss(o->oMoveAngleYaw));
    }
}

void dorrie_act_move(void) {
    s16 startYaw;
    s16 targetYaw = 0;
    s16 targetSpeed = 0;
    s16 circularTurn;

    startYaw = o->oMoveAngleYaw;
    o->oDorrieNeckAngle = -0x26F4;
    cur_obj_init_animation_with_sound(1);

    if (o->oDorrieForwardDistToMario < 320.0f && o->oDorrieGroundPounded) {
        cur_obj_play_sound_2(SOUND_OBJ_DORRIE);
        o->collisionData = segmented_to_virtual(dorrie_seg6_collision_0600FBB8);
        o->oAction = DORRIE_ACT_LOWER_HEAD;
        o->oForwardVel = 0.0f;
        o->oDorrieYawVel = 0;
    } else {

        u8 anyPlayerOnPlatform = FALSE;
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (!is_player_active(&gMarioStates[i])) { continue; }
            struct Object* player = gMarioStates[i].marioObj;
            if (player->platform != o) { continue; }

            targetYaw = player->oFaceAngleYaw;
            targetSpeed = 10;

            anyPlayerOnPlatform = TRUE;
            break;
        }

        if (!anyPlayerOnPlatform) {
            circularTurn = 0x4000 - atan2s(2000.0f, o->oDorrieDistToHome - 2000.0f);
            if ((s16)(o->oMoveAngleYaw - o->oDorrieAngleToHome) < 0) {
                circularTurn = -circularTurn;
            }

            targetYaw = o->oDorrieAngleToHome + circularTurn;
            targetSpeed = 5;
        }

        obj_forward_vel_approach(targetSpeed, 0.5f);
        o->oDorrieYawVel =
            approach_s16_symmetric(o->oDorrieYawVel, (s16)(targetYaw - o->oMoveAngleYaw) / 50, 5);
        o->oMoveAngleYaw += o->oDorrieYawVel;
    }

    o->oAngleVelYaw = o->oMoveAngleYaw - startYaw;
}

void dorrie_begin_head_raise(s32 liftingMario) {
    o->oDorrieLiftingMario = liftingMario;
    o->oAction = DORRIE_ACT_RAISE_HEAD;
    o->oDorrieHeadRaiseSpeed = 0;
}

static u8 dorrie_act_lower_head_continue_dialog(void) {
    return (o->oAction == DORRIE_ACT_LOWER_HEAD);
}

void dorrie_act_lower_head(void) {
    s32 distanceToLocalPlayer = dist_between_objects(o, gMarioStates[0].marioObj);

    if (cur_obj_init_anim_check_frame(2, 35)) {
        cur_obj_reverse_animation();

/*#ifdef VERSION_JP
        if (o->oTimer > 150) {
            dorrie_begin_head_raise(FALSE);
        } else if (cur_obj_is_any_player_on_platform()) {
            if (o->oDorrieForwardDistToMario > 830.0f && set_mario_npc_dialog(&gMarioStates[0], 2, dorrie_act_lower_head_continue_dialog) == 1) {
                dorrie_begin_head_raise(TRUE);
            } else if (o->oDorrieForwardDistToMario > 320.0f) {
                o->oTimer = 0;
            }
        }
#else*/
        if (cur_obj_is_any_player_on_platform()) {
            if (gMarioStates[0].marioObj->platform == o
                && o->oDorrieOffsetY == -17.0f && distanceToLocalPlayer > 780.0f
                && set_mario_npc_dialog(&gMarioStates[0], 2, dorrie_act_lower_head_continue_dialog) == 1) {
                dorrie_begin_head_raise(TRUE);
                network_send_object(o);
            } else if (o->oDorrieForwardDistToMario > 320.0f) {
                o->oTimer = 0;
            }
        } else if (o->oTimer > 150) {
            dorrie_begin_head_raise(FALSE);
        }
//#endif

    } else {
        o->oDorrieNeckAngle += 0x115;
    }
}

static u8 dorrie_act_raise_head_continue_dialog(void) {
    return (o->oAction == DORRIE_ACT_RAISE_HEAD);
}

void dorrie_act_raise_head(void) {
    o->collisionData = segmented_to_virtual(dorrie_seg6_collision_0600F644);
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = DORRIE_ACT_MOVE;
        for (s32 i = 0; i < MAX_PLAYERS; i++) { dorrieLiftingPlayer[i] = FALSE; }
    } else if (o->oDorrieLiftingMario && o->header.gfx.animInfo.animFrame < 74) {

        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (!is_player_active(&gMarioStates[i])) { continue; }
            if (gMarioStates[i].marioObj->platform != o) { continue; }
            s32 dist = dist_between_objects(o, gMarioStates[0].marioObj);
            if (dist <= 780.0f) { continue; }
            dorrieLiftingPlayer[i] = TRUE;
        }

        if (dorrieLiftingPlayer[0]) {
            set_mario_npc_dialog(&gMarioStates[0], 2, dorrie_act_raise_head_continue_dialog);
        }
        //if (set_mario_npc_dialog(&gMarioStates[0], 2, dorrie_act_raise_head_continue_dialog) == 2) {
            o->oDorrieHeadRaiseSpeed += 0x1CC;
            if (cur_obj_check_anim_frame(73) && dorrieLiftingPlayer[0]) {
                set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
            }
            dorrie_raise_head();
        /*} else {
            cur_obj_reverse_animation();
        }*/
    }
}

void bhv_dorrie_update(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    if (!sync_object_is_initialized(o->oSyncID)) {
        for (s32 i = 0; i < MAX_PLAYERS; i++) { dorrieLiftingPlayer[i] = FALSE; }
        struct SyncObject* so = sync_object_init(o, 4000.0f);
        if (so) {
            so->ignore_if_true = bhv_dorrie_ignore_if_true;
            sync_object_init_field(o, &o->oDorrieOffsetY);
            sync_object_init_field(o, &o->oDorrieVelY);
            sync_object_init_field(o, &o->oDorrieYawVel);
            sync_object_init_field(o, &o->oDorrieLiftingMario);
            sync_object_init_field(o, &o->oDorrieNeckAngle);
            sync_object_init_field(o, &o->oAngleVelYaw);
        }
    }

    f32 boundsShift;
    UNUSED s32 unused1;
    UNUSED s32 unused2;
    f32 maxOffsetY;

    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {

        o->oDorrieForwardDistToMario = distanceToPlayer * coss(angleToPlayer - o->oMoveAngleYaw);

        obj_perform_position_op(0);
        cur_obj_move_using_fvel_and_gravity();

        o->oDorrieAngleToHome = cur_obj_angle_to_home();
        o->oDorrieDistToHome = cur_obj_lateral_dist_to_home();

        // Shift dorrie's bounds to account for her neck
        boundsShift = 440.0f * coss(o->oDorrieNeckAngle) * coss(o->oMoveAngleYaw - o->oDorrieAngleToHome);

        if (clamp_f32(&o->oDorrieDistToHome, 1650.0f + boundsShift, 2300.0f + boundsShift)) {
            o->oPosX = o->oHomeX - o->oDorrieDistToHome * sins(o->oDorrieAngleToHome);
            o->oPosZ = o->oHomeZ - o->oDorrieDistToHome * coss(o->oDorrieAngleToHome);
        }

        o->oDorrieGroundPounded = cur_obj_is_mario_ground_pounding_platform();

        if (cur_obj_is_any_player_on_platform()) {
            maxOffsetY = -17.0f;
            if (o->oDorrieOffsetY >= 0.0f) {
                if (o->oDorrieGroundPounded) {
                    o->oDorrieVelY = -15.0f;
                } else {
                    o->oDorrieVelY = -6.0f;
                }
            }
        } else {
            maxOffsetY = 0.0f;
        }

        o->oDorrieOffsetY += o->oDorrieVelY;
        approach_f32_ptr(&o->oDorrieVelY, 3.0f, 1.0f);
        if (o->oDorrieVelY > 0.0f && o->oDorrieOffsetY > maxOffsetY) {
            o->oDorrieOffsetY = maxOffsetY;
        }

        o->oPosY = o->oHomeY + o->oDorrieOffsetY;

        switch (o->oAction) {
            case DORRIE_ACT_MOVE:
                dorrie_act_move();
                break;
            case DORRIE_ACT_LOWER_HEAD:
                dorrie_act_lower_head();
                break;
            case DORRIE_ACT_RAISE_HEAD:
                dorrie_act_raise_head();
                break;
        }

        obj_perform_position_op(1);
    }
}
