// thwomp.c.inc

void grindel_thwomp_act_4(void) {
    if (o->oTimer == 0) {
        o->oThwompRandomTimer = random_float() * 10.0f + 20.0f;
    }
    if (o->oTimer > o->oThwompRandomTimer) {
        o->oAction = 0;
    }
}

void grindel_thwomp_act_2(void) {
    o->oVelY += -4.0f;
    o->oPosY += o->oVelY;
    if (o->oPosY < o->oHomeY) {
        o->oPosY = o->oHomeY;
        o->oVelY = 0;
        o->oAction = 3;
    }
}

void grindel_thwomp_act_3(void) {
    if (o->oTimer == 0) {
        s32 distanceToPlayer = dist_between_objects(o, gMarioStates[0].marioObj);
        if (distanceToPlayer < 1500.0f) {
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
        }
    }
    if (o->oTimer > 9) {
        o->oAction = 4;
    }
}

void grindel_thwomp_act_1(void) {
    if (o->oTimer == 0) {
        o->oThwompRandomTimer = random_float() * 30.0f + 10.0f;
    }
    if (sync_object_is_owned_locally(o->oSyncID) && o->oTimer > o->oThwompRandomTimer) {
        o->oAction = 2;
        network_send_object(o);
    }
}

void grindel_thwomp_act_0(void) {
    if (o->oBehParams2ndByte + 40 < o->oTimer) {
        o->oAction = 1;
        o->oPosY += 5.0f;
    } else
        o->oPosY += 10.0f;
}

void (*sGrindelThwompActions[])(void) = { grindel_thwomp_act_0, grindel_thwomp_act_1,
                                          grindel_thwomp_act_2, grindel_thwomp_act_3,
                                          grindel_thwomp_act_4 };

void bhv_grindel_thwomp_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &o->oAction);
        sync_object_init_field(o, &o->oPosY);
        sync_object_init_field(o, &o->oThwompRandomTimer);
        sync_object_init_field(o, &o->oTimer);
        sync_object_init_field(o, &o->oVelY);
    }
    CUR_OBJ_CALL_ACTION_FUNCTION(sGrindelThwompActions);
}
