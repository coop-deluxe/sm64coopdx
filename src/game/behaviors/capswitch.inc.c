// capswitch.c.inc

static u8 capSwitchForcePress = FALSE;

void cap_switch_act_0(void) {
    o->oAnimState = o->oBehParams2ndByte;
    cur_obj_scale(0.5f);
    o->oPosY += 71.0f;
    spawn_object_relative_with_scale(0, 0, -71, 0, 0.5f, o, MODEL_CAP_SWITCH_BASE, bhvCapSwitchBase);
    if (gCurrLevelNum != LEVEL_UNKNOWN_32) {
        if (save_file_get_flags() & BHV_ARR(D_8032F0C0, o->oBehParams2ndByte, s32)) {
            o->oAction = 3;
            o->header.gfx.scale[1] = 0.1f;
        } else
            o->oAction = 1;
    } else
        o->oAction = 1;
}

void cap_switch_act_1(void) {
    if (capSwitchForcePress || cur_obj_is_mario_on_platform()) {
        save_file_set_flags(BHV_ARR(D_8032F0C0, o->oBehParams2ndByte, s32));
        o->oAction = 2;
        cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
        if (!capSwitchForcePress) {
            capSwitchForcePress = TRUE;
            network_send_object(o);
        }
        capSwitchForcePress = FALSE;
    }
}

u8 cap_switch_act_2_continue_dialog(void) { return o->oAction == 2 && o->oTimer >= 5; }

void cap_switch_act_2(void) {
    capSwitchForcePress = FALSE;
    s32 sp1C;
    if (o->oTimer < 5) {
        cur_obj_scale_over_time(2, 4, 0.5f, 0.1f);
        if (o->oTimer == 4) {
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            spawn_mist_particles();
            spawn_triangle_break_particles(60, 139, 0.3f, o->oBehParams2ndByte);
            queue_rumble_data_object(o, 5, 80);
        }
    } else {
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        if (marioState && should_start_or_continue_dialog(marioState, o)) {
            sp1C = cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 1, 0x0C, CUTSCENE_CAP_SWITCH_PRESS, 0, cap_switch_act_2_continue_dialog);
            if (sp1C) { o->oAction = 3; }
        }
    }
}

void cap_switch_act_3(void) {
    capSwitchForcePress = FALSE;
} // dead function

void (*sCapSwitchActions[])(void) = { cap_switch_act_0, cap_switch_act_1,
                                      cap_switch_act_2, cap_switch_act_3 };

void bhv_cap_switch_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &capSwitchForcePress);
    }

    CUR_OBJ_CALL_ACTION_FUNCTION(sCapSwitchActions);
}
