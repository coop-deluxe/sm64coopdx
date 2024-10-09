// heave_ho.c.inc

s16 D_8032F460[][2] = { { 30, 0 }, { 42, 1 }, { 52, 0 },  { 64, 1 },  { 74, 0 },
                        { 86, 1 }, { 96, 0 }, { 108, 1 }, { 118, 0 }, { -1, 0 }, };

void bhv_heave_ho_throw_mario_loop(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (gMarioStates[0].heldByObj == o->parentObj) { marioState = &gMarioStates[0]; }

    struct Object* player = marioState ? marioState->marioObj : NULL;
    o->oParentRelativePosX = 200.0f;
    o->oParentRelativePosY = -50.0f;
    o->oParentRelativePosZ = 0.0f;
    if (o->parentObj) {
        o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
        switch (o->parentObj->oHeaveHoUnk88) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                cur_obj_play_sound_2(SOUND_OBJ_HEAVEHO_TOSSED);
                if (player) {
                    player->oInteractStatus |= INT_STATUS_MARIO_UNK2;
                }
                if (marioState) {
                    marioState->forwardVel = -45.0f;
                    marioState->vel[1] = 95.0f;
                }
                o->parentObj->oHeaveHoUnk88 = 0;
                o->parentObj->usingObj = NULL;
                break;
        }
    }
}

void heave_ho_act_1(void) {
    s32 sp1C = 0;
    o->oForwardVel = 0.0f;
    cur_obj_reverse_animation();
    while (TRUE) {
        if (D_8032F460[sp1C][0] == -1) {
            o->oAction = 2;
            break;
        }
        if (o->oTimer < D_8032F460[sp1C][0]) {
            cur_obj_init_animation_with_accel_and_sound(2, D_8032F460[sp1C][1]);
            break;
        }
        sp1C++;
    }
}

void heave_ho_act_2(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    UNUSED s32 unused;
    s16 angleVel;
    if (1000.0f < cur_obj_lateral_dist_from_mario_to_home())
        angleToPlayer = cur_obj_angle_to_home();
    if (o->oTimer > 150) {
        o->oHeaveHoUnkF4 = (302 - o->oTimer) / 152.0f;
        if (o->oHeaveHoUnkF4 < 0.1) {
            o->oHeaveHoUnkF4 = 0.1;
            o->oAction = 1;
        }
    } else
        o->oHeaveHoUnkF4 = 1.0f;
    cur_obj_init_animation_with_accel_and_sound(0, o->oHeaveHoUnkF4);
    o->oForwardVel = o->oHeaveHoUnkF4 * 10.0f;
    angleVel = o->oHeaveHoUnkF4 * 0x400;
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, angleToPlayer, angleVel);
}

void heave_ho_act_3(void) {
    o->oForwardVel = 0.0f;
    if (o->oTimer == 0)
        o->oHeaveHoUnk88 = 2;
    if (o->oTimer == 1) {
        cur_obj_init_animation_with_accel_and_sound(1, 1.0f);
        o->numCollidedObjs = 20;
    }
    if (cur_obj_check_if_near_animation_end())
        o->oAction = 1;
}

void heave_ho_act_0(void) {
    if (find_water_level(o->oPosX, o->oPosZ) < (o->oPosY - 50.0f)) {
        cur_obj_set_pos_to_home();
        cur_obj_become_tangible();
        cur_obj_unhide();
        o->oAction = 1;
    } else {
        cur_obj_become_intangible();
        cur_obj_hide();
    }
}

void (*sHeaveHoActions[])(void) = { heave_ho_act_0, heave_ho_act_1, heave_ho_act_2, heave_ho_act_3 };

void heave_ho_move(void) {
    cur_obj_update_floor_and_walls();
    CUR_OBJ_CALL_ACTION_FUNCTION(sHeaveHoActions);
    cur_obj_move_standard(-78);
    if (o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER)
        o->oGraphYOffset = -15.0f;
    else
        o->oGraphYOffset = 0.0f;
    if (o->oForwardVel > 3.0f)
        cur_obj_play_sound_1(SOUND_AIR_HEAVEHO_MOVE);
    if (o->oAction != 0 && o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER)
        o->oAction = 0;
    if (o->oInteractStatus & INT_STATUS_GRABBED_MARIO) {
        o->oInteractStatus = 0;
        o->oHeaveHoUnk88 = 1;
        o->oAction = 3;
        o->usingObj = nearest_player_to_object(o);
    }
}

void bhv_heave_ho_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = (gMarioStates[0].heldByObj == o);
    if (*shouldOverride) {
        *shouldOwn = true;
    }
}

u8 bhv_heave_ho_ignore_if_true(void) {
    return (gMarioStates[0].heldByObj == o);
}

void bhv_heave_ho_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, 4000.0f);
        if (so != NULL) {
            so->override_ownership = bhv_heave_ho_override_ownership;
            so->ignore_if_true = bhv_heave_ho_ignore_if_true;
            sync_object_init_field(o, &o->oHeaveHoUnk88);
            sync_object_init_field(o, &o->oHeaveHoUnkF4);
            sync_object_init_field(o, &o->oInteractStatus);
            sync_object_init_field(o, &o->oGraphYOffset);
            sync_object_init_field(o, &o->oFaceAngleYaw);
        }
    }

    cur_obj_scale(2.0f);
    switch (o->oHeldState) {
        case HELD_FREE:
            heave_ho_move();
            break;
        case HELD_HELD:
            cur_obj_unrender_and_reset_state(0, 0);
            break;
        case HELD_THROWN:
            cur_obj_get_dropped();
            break;
        case HELD_DROPPED:
            cur_obj_get_dropped();
            break;
    }
    o->oInteractStatus = 0;
}
