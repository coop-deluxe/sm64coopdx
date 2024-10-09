// whomp.c.inc

void whomp_play_sfx_from_pound_animation(void) {
    UNUSED s32 sp2C = o->header.gfx.animInfo.animFrame;
    s32 sp28 = 0;
    if (o->oForwardVel < 5.0f) {
        sp28 = cur_obj_check_anim_frame(0);
        sp28 |= cur_obj_check_anim_frame(23);
    } else {
        sp28 = cur_obj_check_anim_frame_in_range(0, 3);
        sp28 |= cur_obj_check_anim_frame_in_range(23, 3);
    }
    if (sp28)
        cur_obj_play_sound_2(SOUND_OBJ_POUNDING1);
}

u8 whomp_act_0_continue_dialog(void) { return o->oAction == 0; }

void whomp_act_0(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    cur_obj_init_animation_with_accel_and_sound(0, 1.0f);
    cur_obj_set_pos_to_home();
    if (o->oBehParams2ndByte != 0) {
        gSecondCameraFocus = o;
        cur_obj_scale(2.0f);
        if (o->oSubAction == 0) {
            if (distanceToPlayer < 600.0f) {
                o->oSubAction++;
                seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            } else {
                cur_obj_set_pos_to_home();
                o->oHealth = gBehaviorValues.KingWhompHealth;
            }
        } else if (marioState && should_start_or_continue_dialog(marioState, o) && cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 2, 1, CUTSCENE_DIALOG, gBehaviorValues.dialogs.KingWhompDialog, whomp_act_0_continue_dialog)) {
            o->oAction = 2;
            network_send_object(o);
        }
    } else if (distanceToPlayer < 500.0f)
        o->oAction = 1;
    whomp_play_sfx_from_pound_animation();
}

void whomp_act_7(void) {
    if (o->oSubAction == 0) {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_accel_and_sound(0, 1.0f);
        if (o->oTimer > 31)
            o->oSubAction++;
        else
            o->oMoveAngleYaw += 0x400;
    } else {
        o->oForwardVel = 3.0f;
        if (o->oTimer > 42)
            o->oAction = 1;
    }
    whomp_play_sfx_from_pound_animation();
}

void whomp_act_1(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    s16 sp26;
    f32 sp20;
    f32 sp1C;
    sp26 = abs_angle_diff(angleToPlayer, o->oMoveAngleYaw);
    sp20 = cur_obj_lateral_dist_to_home();
    if (gCurrLevelNum == LEVEL_BITS)
        sp1C = 200.0f;
    else
        sp1C = 700.0f;
    cur_obj_init_animation_with_accel_and_sound(0, 1.0f);
    o->oForwardVel = 3.0f;
    if (sp20 > sp1C)
        o->oAction = 7;
    else if (sp26 < 0x2000) {
        if (distanceToPlayer < 1500.0f) {
            o->oForwardVel = 9.0f;
            cur_obj_init_animation_with_accel_and_sound(0, 3.0f);
        }
        if (distanceToPlayer < 300.0f)
            o->oAction = 3;
    }
    whomp_play_sfx_from_pound_animation();
}

void whomp_act_2(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    s16 sp1E;
    cur_obj_init_animation_with_accel_and_sound(0, 1.0f);
    o->oForwardVel = 3.0f;
    cur_obj_rotate_yaw_toward(angleToPlayer, 0x200);
    if (o->oTimer > 30) {
        sp1E = abs_angle_diff(angleToPlayer, o->oMoveAngleYaw);
        if (sp1E < 0x2000) {
            if (distanceToPlayer < 1500.0f) {
                o->oForwardVel = 9.0f;
                cur_obj_init_animation_with_accel_and_sound(0, 3.0f);
            }
            if (distanceToPlayer < 300.0f)
                o->oAction = 3;
        }
    }
    whomp_play_sfx_from_pound_animation();
    if (mario_is_far_below_object(1000.0f)) {
        o->oAction = 0;
        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
    }
}

void whomp_act_3(void) {
    o->oForwardVel = 0.0f;
    cur_obj_init_animation_with_accel_and_sound(1, 1.0f);
    if (cur_obj_check_if_near_animation_end())
        o->oAction = 4;
}

void whomp_act_4(void) {
    if (o->oTimer == 0)
        o->oVelY = 40.0f;
    if (o->oTimer < 8) {
    } else {
        o->oAngleVelPitch += 0x100;
        o->oFaceAnglePitch += o->oAngleVelPitch;
        if (o->oFaceAnglePitch > 0x4000) {
            o->oAngleVelPitch = 0;
            o->oFaceAnglePitch = 0x4000;
            o->oAction = 5;
        }
    }
}

void whomp_act_5(void) {
    if (o->oSubAction == 0 && o->oMoveFlags & OBJ_MOVE_LANDED) {
        cur_obj_play_sound_2(SOUND_OBJ_WHOMP_LOWPRIO);
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        o->oVelY = 0.0f;
        o->oSubAction++;
    }
    if (o->oMoveFlags & OBJ_MOVE_ON_GROUND)
        o->oAction = 6;
}

void king_whomp_on_ground(void) {
    struct Object* player = nearest_player_to_object(o);

    Vec3f pos;
    if (o->oSubAction == 0) {
        if (cur_obj_is_mario_ground_pounding_platform()) {
            o->oHealth--;
            cur_obj_play_sound_2(SOUND_OBJ2_WHOMP_SOUND_SHORT);
            cur_obj_play_sound_2(SOUND_OBJ_KING_WHOMP_DEATH);
            if (o->oHealth == 0)
                o->oAction = 8;
            else {
                vec3f_copy_2(pos, &o->oPosX);
                if (player) {
                    vec3f_copy_2(&o->oPosX, &player->oPosX);
                }
                spawn_mist_particles_variable(0, 0, 100.0f);
                spawn_triangle_break_particles(20, 138, 3.0f, 4);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
                vec3f_copy_2(&o->oPosX, pos);
            }
            o->oSubAction++;
        }
        o->oWhompShakeVal = 0;
    } else {
        if (o->oWhompShakeVal < 10) {
            if (o->oWhompShakeVal % 2)
                o->oPosY += 8.0f;
            else
                o->oPosY -= 8.0f;
        } else
            o->oSubAction = 10;
        o->oWhompShakeVal++;
    }
}

void whomp_on_ground(void) {

    if (o->oSubAction == 0) {
        if (cur_obj_is_any_player_on_platform()) {
            if (cur_obj_is_mario_ground_pounding_platform()) {
                o->oNumLootCoins = 5;
                obj_spawn_loot_yellow_coins(o, 5, 20.0f);
                o->oAction = 8;
            } else {
                struct MarioState* marioState = nearest_mario_state_to_object(o);
                if (marioState) {
                    cur_obj_spawn_loot_coin_at_mario_pos(marioState);
                }
                o->oSubAction++;
            }
        }
    } else if (!cur_obj_is_mario_on_platform())
        o->oSubAction = 0;
}

void whomp_act_6(void) {
    if (o->oSubAction != 10) {
        o->oForwardVel = 0.0f;
        o->oAngleVelPitch = 0;
        o->oAngleVelYaw = 0;
        o->oAngleVelRoll = 0;
        if (o->oBehParams2ndByte != 0)
            king_whomp_on_ground();
        else
            whomp_on_ground();
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        if (o->oTimer > 100 || (marioState && marioState->action == ACT_SQUISHED && o->oTimer > 30))
            o->oSubAction = 10;
    } else {
        if (o->oFaceAnglePitch > 0) {
            o->oAngleVelPitch = -0x200;
            o->oFaceAnglePitch += o->oAngleVelPitch;
        } else {
            o->oAngleVelPitch = 0;
            o->oFaceAnglePitch = 0;
            if (o->oBehParams2ndByte != 0)
                o->oAction = 2;
            else
                o->oAction = 1;
        }
    }
}

u8 whomp_act_8_continue_dialog(void) { return o->oAction == 8; }

void whomp_act_8(void) {
    if (o->oBehParams2ndByte != 0) {
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        if (marioState && should_start_or_continue_dialog(marioState, o) && cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 2, 2, CUTSCENE_DIALOG, gBehaviorValues.dialogs.KingWhompDefeatDialog, whomp_act_8_continue_dialog)) {
            obj_set_angle(o, 0, 0, 0);
            cur_obj_hide();
            cur_obj_become_intangible();
            spawn_mist_particles_variable(0, 0, 200.0f);
            spawn_triangle_break_particles(20, 138, 3.0f, 4);
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            o->oPosY += 100.0f;

            f32* starPos = gLevelValues.starPositions.KingWhompStarPos;
            spawn_default_star(starPos[0], starPos[1], starPos[2]);

            cur_obj_play_sound_2(SOUND_OBJ_KING_WHOMP_DEATH);
            o->oAction = 9;
            network_send_object(o);
        }
    } else {
        spawn_mist_particles_variable(0, 0, 100.0f);
        spawn_triangle_break_particles(20, 138, 3.0f, 4);
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        create_sound_spawner(SOUND_OBJ_THWOMP);
        obj_mark_for_deletion(o);
    }
}

void whomp_act_9(void) {
    if (o->oTimer == 60)
        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
}

void (*sWhompActions[])(void) = {
    whomp_act_0, whomp_act_1, whomp_act_2, whomp_act_3, whomp_act_4,
    whomp_act_5, whomp_act_6, whomp_act_7, whomp_act_8, whomp_act_9
};

// MM
void bhv_whomp_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oAngleVelPitch);
        sync_object_init_field(o, &o->oFaceAnglePitch);
        sync_object_init_field(o, &o->oForwardVel);
        sync_object_init_field(o, &o->oHealth);
        sync_object_init_field(o, &o->oFaceAnglePitch);
    }

    cur_obj_update_floor_and_walls();
    CUR_OBJ_CALL_ACTION_FUNCTION(sWhompActions);
    cur_obj_move_standard(-20);
    if (o->oAction != 9) {
        // o->oBehParams2ndByte here seems to be a flag
        // indicating whether this is a normal or king whomp
        if (o->oBehParams2ndByte != 0)
            cur_obj_hide_if_mario_far_away_y(2000.0f);
        else
            cur_obj_hide_if_mario_far_away_y(1000.0f);
        load_object_collision_model();
    }
}
