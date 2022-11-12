// kickable_board.c.inc

s32 check_mario_attacking(struct MarioState* marioState) {
    if (obj_check_if_collided_with_object(o, marioState->marioObj)) {
        if (abs_angle_diff(o->oMoveAngleYaw, marioState->marioObj->oMoveAngleYaw) > 0x6000) {
            if (marioState->action == ACT_SLIDE_KICK)
                return 1;
            if (marioState->action == ACT_PUNCHING)
                return 1;
            if (marioState->action == ACT_MOVE_PUNCHING)
                return 1;
            if (marioState->action == ACT_SLIDE_KICK_SLIDE)
                return 1;
            if (marioState->action == ACT_JUMP_KICK)
                return 2;
            if (marioState->action == ACT_WALL_KICK_AIR)
                return 2;
        }
    }
    return 0;
}

void init_kickable_board_rock(void) {
    o->oKickableBoardF8 = 1600;
    o->oKickableBoardF4 = 0;
}

void bhv_kickable_board_loop(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &o->oAction);
        sync_object_init_field(o, &o->oAngleVelPitch);
        sync_object_init_field(o, &o->oFaceAnglePitch);
        sync_object_init_field(o, &o->oKickableBoardF4);
        sync_object_init_field(o, &o->oKickableBoardF8);
        sync_object_init_field(o, &o->oMoveAngleYaw);
        sync_object_init_field(o, &o->oPosY);
        sync_object_init_field(o, &o->oTimer);
    }
    s32 sp24;
    switch (o->oAction) {
        case 0:
            o->oFaceAnglePitch = 0;
            if (marioState && check_mario_attacking(marioState)) {
                init_kickable_board_rock();
                o->oAction++;
                if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
            }
            load_object_collision_model();
            break;
        case 1:
            o->oFaceAnglePitch = 0;
            load_object_collision_model();
            o->oFaceAnglePitch = -sins(o->oKickableBoardF4) * o->oKickableBoardF8;
            if (marioState) {
                if (o->oTimer > 30 && (sp24 = check_mario_attacking(marioState))) {
                    if (marioState->marioObj->oPosY > o->oPosY + 160.0f && sp24 == 2) {
                        o->oAction++;
                        cur_obj_play_sound_2(SOUND_GENERAL_BUTTON_PRESS_2);
                        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
                    } else
                        o->oTimer = 0;
                }
            }
            if (o->oTimer != 0) {
                o->oKickableBoardF8 -= 8;
                if (o->oKickableBoardF8 < 0) {
                    o->oAction = 0;
                    if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
                }
            } else
                init_kickable_board_rock();
            if (!(o->oKickableBoardF4 & 0x7FFF))
                cur_obj_play_sound_2(SOUND_GENERAL_BUTTON_PRESS_2);
            o->oKickableBoardF4 += 0x400;
            break;
        case 2:
            cur_obj_become_intangible();
            cur_obj_set_model(smlua_model_util_load(E_MODEL_WF_KICKABLE_BOARD_FELLED));
            o->oAngleVelPitch -= 0x80;
            o->oFaceAnglePitch += o->oAngleVelPitch;
            if (o->oFaceAnglePitch < -0x4000) {
                o->oFaceAnglePitch = -0x4000;
                o->oAngleVelPitch = 0;
                o->oAction++;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
                cur_obj_play_sound_2(SOUND_GENERAL_UNKNOWN4);
                if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
            }
            load_object_collision_model();
            break;
        case 3:
            load_object_collision_model();
            break;
    }
    o->header.gfx.throwMatrix = NULL;
}
