// bowser.c.inc
static u32 networkBowserAnimationIndex = 0;
static u8 bowserIsDying = FALSE;
static u8 bowserCutscenePlayed = FALSE;
static u8 bowserIsCutscenePlayer = FALSE;

void bowser_tail_anchor_act_0(void) {
    struct Object* bowser = o->parentObj;
    struct Object* player = nearest_player_to_object(o);
    cur_obj_become_tangible();
    cur_obj_scale(1.0f);
    if (bowser->oAction == 5 || bowser->oAction == 6 || bowser->oAction == 19 || bowser->oAction == 20) {
        bowser->oIntangibleTimer = -1;
    } else if (player && obj_check_if_collided_with_object(o, player)) {
        bowser->oIntangibleTimer = 0;
        o->oAction = 2;
    } else {
        bowser->oIntangibleTimer = -1;
    }
}

void bowser_tail_anchor_act_1(void) {
    if (o->oTimer > 30)
        o->oAction = 0;
}

void bowser_tail_anchor_act_2(void) {
    if (o->parentObj->oAction == 19) {
        o->parentObj->oIntangibleTimer = -1;
        o->oAction = 0;
    }
    cur_obj_become_intangible();
}

void (*sBowserTailAnchorActions[])(void) = { bowser_tail_anchor_act_0, bowser_tail_anchor_act_1,
                                             bowser_tail_anchor_act_2 };
s8 D_8032F4FC[] = { 7, 8, 9, 12, 13, 14, 15, 4, 3, 16, 17, 19, 3, 3, 3, 3 };
s16 D_8032F50C[] = { 60, 0 };
s16 D_8032F510[] = { 50, 0 };
s8 D_8032F514[] = { 24, 42, 60, -1 };
s16* sBowserDefeatedDialogText[3] = {
    (s16*) &gBehaviorValues.dialogs.Bowser1DefeatedDialog,
    (s16*) &gBehaviorValues.dialogs.Bowser2DefeatedDialog,
    (s16*) &gBehaviorValues.dialogs.Bowser3DefeatedDialog
};
s16 D_8032F520[][3] = { { 1, 10, 40 },   { 0, 0, 74 },    { -1, -10, 114 },  { 1, -20, 134 },
                        { -1, 20, 154 }, { 1, 40, 164 },  { -1, -40, 174 },  { 1, -80, 179 },
                        { -1, 80, 184 }, { 1, 160, 186 }, { -1, -160, 186 }, { 1, 0, 0 }, };

void bhv_bowser_tail_anchor_init(void) {
    if (!o->parentObj) { mark_obj_for_deletion(o); return; }
    sync_object_init_field(o->parentObj, &o->oAction);
    sync_object_init_field(o->parentObj, &o->oPrevAction);
    sync_object_init_field(o->parentObj, &o->oTimer);
    sync_object_init_field(o->parentObj, &o->oIntangibleTimer);
    sync_object_init_field(o->parentObj, &o->oInteractStatus);
    sync_object_init_field(o->parentObj, &o->header.gfx.scale[0]);
    sync_object_init_field(o->parentObj, &o->header.gfx.scale[1]);
    sync_object_init_field(o->parentObj, &o->header.gfx.scale[2]);
}

void bhv_bowser_tail_anchor_loop(void) {
    if (!o->parentObj) { return; }
    CUR_OBJ_CALL_ACTION_FUNCTION(sBowserTailAnchorActions);
    o->oParentRelativePosX = 90.0f;
    if (o->parentObj->oAction == 4)
        o->parentObj->oIntangibleTimer = -1;
    o->oInteractStatus = 0;
}

void bhv_bowser_flame_spawn_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    }
    struct Object *bowser = o->parentObj;
    if (!bowser) { return; }
    s32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24 = coss(bowser->oMoveAngleYaw);
    f32 sp20 = sins(bowser->oMoveAngleYaw);
    s16 *sp1C = segmented_to_virtual(bowser_seg6_unkmoveshorts_060576FC);
    if (bowser->oSoundStateID == 6) {
        sp30 = bowser->header.gfx.animInfo.animFrame + 1.0f;
        if (bowser->header.gfx.animInfo.curAnim && bowser->header.gfx.animInfo.curAnim->loopEnd == sp30) {
            sp30 = 0;
        }
        if (sp30 > 45 && sp30 < 85) {
            cur_obj_play_sound_1(SOUND_AIR_BOWSER_SPIT_FIRE);
            sp2C = sp1C[5 * sp30];
            sp28 = sp1C[5 * sp30 + 2];
            o->oPosX = bowser->oPosX + (sp28 * sp20 + sp2C * sp24);
            o->oPosY = bowser->oPosY + sp1C[5 * sp30 + 1];
            o->oPosZ = bowser->oPosZ + (sp28 * sp24 - sp2C * sp20);
            o->oMoveAnglePitch = sp1C[5 * sp30 + 4] + 0xC00;
            o->oMoveAngleYaw = sp1C[5 * sp30 + 3] + (s16) bowser->oMoveAngleYaw;
            if (!(sp30 & 1)) {
                struct MarioState* marioState = nearest_mario_state_to_object(o);
                if (marioState && marioState->playerIndex == 0) {
                    struct Object* flame = spawn_object(o, MODEL_RED_FLAME, bhvFlameMovingForwardGrowing);
                    if (flame != NULL) {
                        struct Object* spawn_objects[] = { flame };
                        u32 models[] = { MODEL_RED_FLAME };
                        network_send_spawn_objects(spawn_objects, models, 1);
                    }
                }
            }
        }
    }
}

void bhv_bowser_body_anchor_init(void) {
    if (!o->parentObj) { mark_obj_for_deletion(o); return; }
    sync_object_init_field(o->parentObj, &o->oInteractType);
    sync_object_init_field(o->parentObj, &o->oInteractStatus);
    sync_object_init_field(o->parentObj, &o->oIntangibleTimer);
    sync_object_init_field(o->parentObj, &o->oDamageOrCoinValue);
}

void bhv_bowser_body_anchor_loop(void) {
    if (!o->parentObj) { return; }
    obj_copy_pos_and_angle(o, o->parentObj);
    if (o->parentObj->oAction == 4) {
#ifndef VERSION_JP
        if (o->parentObj->oSubAction == 11)
            o->oInteractType = 0;
        else
            o->oInteractType = 0x800000;
#else
        o->oInteractType = 0x800000;
#endif
    } else {
        o->oInteractType = 8;
        if (o->parentObj->oOpacity < 100)
            cur_obj_become_intangible();
        else
            cur_obj_become_tangible();
    }
    if (o->parentObj->oHeldState != HELD_FREE) {
        cur_obj_become_intangible();
        o->parentObj->oOpacity = 0xFF;
    }
    o->oInteractStatus = 0;
}

s32 bowser_spawn_shockwave(void) {
    struct Object *wave;
    if (o->oBehParams2ndByte == 2) {
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        if (marioState && marioState->playerIndex == 0) {
            wave = spawn_object(o, MODEL_BOWSER_WAVE, bhvBowserShockWave);
            if (wave != NULL) {
                wave->oPosY = o->oFloorHeight;

                struct Object* spawn_objects[] = { wave };
                u32 models[] = { MODEL_BOWSER_WAVE };
                network_send_spawn_objects(spawn_objects, models, 1);
            }
        }
        return 1;
    }
    return 0;
}

void bowser_bounce(s32 *a) {
    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        a[0]++;
        if (a[0] < 4) {
            cur_obj_start_cam_event(o, CAM_EVENT_BOWSER_THROW_BOUNCE);
            spawn_mist_particles_variable(0, 0, 60.0f);
            cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
        }
    }
}

#define BITDW (o->oBehParams2ndByte == 0)
#define BITFS (o->oBehParams2ndByte == 1)
#define BITS (o->oBehParams2ndByte == 2)

s32 bowser_set_anim_look_up_and_walk(void) {
    cur_obj_init_animation_with_sound(15);
    if (cur_obj_check_anim_frame(21))
        o->oForwardVel = 3.0f;
    if (cur_obj_check_if_near_animation_end())
        return 1;
    else
        return 0;
}

s32 bowser_set_anim_slow_gait(void) {
    o->oForwardVel = 3.0f;
    cur_obj_init_animation_with_sound(13);
    if (cur_obj_check_if_near_animation_end()) {
        return 1;
    }
    return 0;
}

s32 bowser_set_anim_look_down(void) {
    cur_obj_init_animation_with_sound(14);
    if (cur_obj_check_anim_frame(20)) {
        o->oForwardVel = 0.0f;
    }
    if (cur_obj_check_if_near_animation_end()) {
        return 1;
    }
    return 0;
}

void bowser_initialize_action(void) {
    if (o->oBowserUnk88 == 0 && !bowserCutscenePlayed) {
        o->oAction = 5;
    } else if (o->oBowserUnk88 == 1 && !bowserCutscenePlayed) {
        o->oAction = 6;
    } else if (o->oBehParams2ndByte == 1) {
        bowserCutscenePlayed = TRUE;
        o->oAction = 13;
        if (bowserIsCutscenePlayer) { network_send_object_reliability(o, TRUE); }
    } else {
        bowserCutscenePlayed = TRUE;
        o->oAction = 0;
        if (bowserIsCutscenePlayer) { network_send_object_reliability(o, TRUE); }
    }
}

void bowser_act_text_wait(void) // not much
{
    o->oForwardVel = 0.0f;
    cur_obj_init_animation_with_sound(12);
    bowser_initialize_action();
}

void bowser_act_intro_walk(void) {
    if (o->oSubAction == 0) {
        if (bowser_set_anim_look_up_and_walk())
            o->oSubAction++;
    } else if (o->oSubAction == 1) {
        if (bowser_set_anim_slow_gait())
            o->oSubAction++;
    } else if (bowser_set_anim_look_down()) {
        if (o->oBowserUnk88 == 1)
            o->oBowserUnk88 = 0;
        bowser_initialize_action();
    }
}

static void bowser_debug_actions(void) // unused
{
    if (gDebugInfo[5][1] != 0) {
        o->oAction = D_8032F4FC[gDebugInfo[5][2] & 0xf];
        gDebugInfo[5][1] = 0;
    }
}

void bowser_bitdw_act_controller(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!marioState) { return; }
    struct Object* player = marioState->marioObj;
    s32 distanceToPlayer = dist_between_objects(o, player);
    if (marioState->playerIndex != 0) { return; }

    f32 rand = random_float();
    if (o->oBowserUnk110 == 0) {
        if (o->oBowserUnkF4 & 2) {
            if (distanceToPlayer < 1500.0f)
                o->oAction = 15; // nearby
            else
                o->oAction = 17; // far away
        } else
            o->oAction = 14;
        o->oBowserUnk110++;
    } else {
        o->oBowserUnk110 = 0;
#ifndef VERSION_JP
        if (!gCurrDemoInput && marioState->playerIndex == 0) {
            if (rand < 0.1)
                o->oAction = 3; // rare 1/10 chance
            else
                o->oAction = 14; // common
        } else {
            o->oAction = 14; // ensure demo starts with action 14.
        }
#else
        if (rand < 0.1)
            o->oAction = 3; // rare 1/10 chance
        else
            o->oAction = 14; // common
#endif
    }
    network_send_object(o);
}

void bowser_bitfs_act_controller(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!marioState) { return; }
    struct Object* player = marioState->marioObj;
    s32 distanceToPlayer = dist_between_objects(o, player);
    if (marioState->playerIndex != 0) { return; }

    f32 rand = random_float();
    if (o->oBowserUnk110 == 0) {
        if (o->oBowserUnkF4 & 2) {
            if (distanceToPlayer < 1300.0f) // nearby
            {
                if (rand < 0.5) // 50/50
                    o->oAction = 16;
                else
                    o->oAction = 9;
            } else // far away
            {
                o->oAction = 7;
                if (500.0f < o->oBowserDistToCentre && o->oBowserDistToCentre < 1500.0f
                    && rand < 0.5) // away from centre and good luck
                    o->oAction = 13;
            }
        } else
            o->oAction = 14;
        o->oBowserUnk110++;
    } else {
        o->oBowserUnk110 = 0;
        o->oAction = 14;
    }
    network_send_object(o);
}

void bowser_general_bits_act_controller(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!marioState) { return; }
    struct Object* player = marioState->marioObj;
    s32 distanceToPlayer = dist_between_objects(o, player);
    if (marioState->playerIndex != 0) { return; }

    f32 rand = random_float();
    if (o->oBowserUnkF4 & 2) {
        if (distanceToPlayer < 1000.0f) {
            if (rand < 0.4)
                o->oAction = 9;
            else if (rand < 0.8)
                o->oAction = 8;
            else
                o->oAction = 15;
        } else if (rand < 0.5)
            o->oAction = 13;
        else
            o->oAction = 7;
    } else
        o->oAction = 14;
    network_send_object(o);
}

void bowser_set_act_jump(void) {
    o->oAction = 13;
}

void bowser_bits_act_controller(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!marioState) { return; }
    if (marioState->playerIndex != 0) { return; }
    switch (o->oBowserUnk110) {
        case 0:
            if (o->oBowserUnk106 == 0)
                bowser_general_bits_act_controller();
            else
                bowser_set_act_jump();
            o->oBowserUnk110 = 1;
            break;
        case 1:
            o->oBowserUnk110 = 0;
            o->oAction = 14;
            break;
    }
    network_send_object(o);
}

#ifndef VERSION_JP
void bowser_reset_fallen_off_stage(void) {
    if (o->oVelY < 0 && o->oPosY < (o->oHomeY - 300.0f)) {
        o->oPosX = o->oPosZ = 0;
        o->oPosY = o->oHomeY + 2000.0f;
        o->oVelY = 0;
        o->oForwardVel = 0;
    }
}
#endif

void bowser_act_unused_slow_walk(void) // unused?
{
    if (cur_obj_init_animation_and_check_if_near_end(12))
        o->oAction = 0;
}

void bowser_act_default(void) // only lasts one frame
{
    o->oBowserEyesShut = 0;
    cur_obj_init_animation_with_sound(12);
    // stop him still
    o->oAngleVelYaw = 0;
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    if (BITDW) {
        bowser_bitdw_act_controller();
    } else if (BITFS) {
        bowser_bitfs_act_controller();
    } else {
        bowser_bits_act_controller();
    }
    // Action 14 commonly follows
}

void bowser_act_breath_fire(void) {
    o->oForwardVel = 0.0f;
    if (o->oTimer == 0)
        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_INHALING);
    if (cur_obj_init_animation_and_check_if_near_end(6))
        o->oAction = 0;
}

void bowser_act_walk_to_mario(void) // turn towards Mario
{
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return; }
    s32 angleToPlayer = obj_angle_to_object(o, player);

    UNUSED s32 facing; // is Bowser facing Mario?
    s16 turnSpeed;
    s16 angleFromMario = abs_angle_diff(o->oMoveAngleYaw, angleToPlayer);
    if (BITFS)
        turnSpeed = 0x400;
    else if (o->oHealth > 2)
        turnSpeed = 0x400;
    else if (o->oHealth == 2)
        turnSpeed = 0x300;
    else
        turnSpeed = 0x200;
    facing = cur_obj_rotate_yaw_toward(angleToPlayer, turnSpeed);
    if (o->oSubAction == 0) {
        o->oBowserUnkF8 = 0;
        if (bowser_set_anim_look_up_and_walk())
            o->oSubAction++;
    } else if (o->oSubAction == 1) {
        if (bowser_set_anim_slow_gait()) {
            o->oBowserUnkF8++;
            if (o->oBowserUnkF4 & 0x20000) {
                if (o->oBowserUnkF8 > 4)
                    o->oBowserUnkF4 &= ~0x20000;
            } else if (angleFromMario < 0x2000)
                o->oSubAction++;
        }
    } else if (bowser_set_anim_look_down())
        o->oAction = 0;
}

void bowser_act_teleport(void) {
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return; }
    s32 distanceToPlayer = dist_between_objects(o, player);
    s32 angleToPlayer = obj_angle_to_object(o, player);

    switch (o->oSubAction) {
        case 0:
            cur_obj_become_intangible();
            o->oBowserUnk1AC = 0;
            o->oBowserUnkF8 = 30;
            if (o->oTimer == 0)
                cur_obj_play_sound_2(SOUND_OBJ2_BOWSER_TELEPORT);
            if (o->oOpacity == 0) {
                o->oSubAction++;
                o->oMoveAngleYaw = angleToPlayer;
            }
            break;
        case 1:
            if (o->oBowserUnkF8--)
                o->oForwardVel = 100.0f;
            else {
                o->oSubAction = 2;
                o->oMoveAngleYaw = angleToPlayer;
            }
            if (abs_angle_diff(o->oMoveAngleYaw, angleToPlayer) > 0x4000)
                if (distanceToPlayer > 500.0f) {
                    o->oSubAction = 2;
                    o->oMoveAngleYaw = angleToPlayer; // large change in angle?
                    cur_obj_play_sound_2(SOUND_OBJ2_BOWSER_TELEPORT);
                }
            break;
        case 2:
            o->oForwardVel = 0.0f;
            o->oBowserUnk1AC = 0xFF;
            if (o->oOpacity == 0xFF)
                o->oAction = 0;
            cur_obj_become_tangible();
            break;
    }
}

void bowser_act_spit_fire_into_sky(void) // only in sky
{
    s32 frame;
    cur_obj_init_animation_with_sound(11);
    frame = o->header.gfx.animInfo.animFrame;
    if (frame > 24 && frame < 36) {
        cur_obj_play_sound_1(SOUND_AIR_BOWSER_SPIT_FIRE);
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        if (marioState && marioState->playerIndex == 0) {
            struct Object* flame = NULL;
            if (frame == 35) {
                flame = spawn_object_relative(1, 0, 0x190, 0x64, o, MODEL_RED_FLAME, bhvBlueBowserFlame);
            } else {
                flame = spawn_object_relative(0, 0, 0x190, 0x64, o, MODEL_RED_FLAME, bhvBlueBowserFlame);
            }
            if (flame != NULL) {
                struct Object* spawn_objects[] = { flame };
                u32 models[] = { MODEL_RED_FLAME };
                network_send_spawn_objects(spawn_objects, models, 1);
            }
        }
    }
    if (cur_obj_check_if_near_animation_end())
        o->oAction = 0;
    o->oBowserUnkF4 |= 0x20000;
}

void bowser_act_hit_mine(void) {
    if (o->oTimer == 0) {
        o->oForwardVel = -400.0f;
        o->oVelY = 100.0f;
        o->oMoveAngleYaw = o->oBowserAngleToCentre + 0x8000;
        o->oBowserEyesShut = 1;
    }
    if (o->oSubAction == 0) {
        cur_obj_init_animation_with_sound(25);
        o->oSubAction++;
        o->oBowserUnkF8 = 0;
    } else if (o->oSubAction == 1) {
        cur_obj_init_animation_with_sound(25);
        cur_obj_extend_animation_if_at_end();
        bowser_bounce(&o->oBowserUnkF8);
        if ((o->oBowserUnkF8 > 2)) {
            cur_obj_init_animation_with_sound(26);
            o->oVelY = 0.0f;
            o->oForwardVel = 0.0f;
            o->oSubAction++;
        }
    } else if (o->oSubAction == 2) {
        if (cur_obj_check_if_near_animation_end()) {
            if (o->oHealth == 1)
                o->oAction = 3;
            else
                o->oAction = 0;
            o->oBowserEyesShut = 0;
        }
    } else {
    }
}

s32 bowser_set_anim_in_air(void) {
    cur_obj_init_animation_with_sound(9);
    if (cur_obj_check_anim_frame(11))
        return 1;
    else
        return 0;
}

s32 bowser_land(void) {
    struct Object* player = gMarioStates[0].marioObj;
    s32 distanceToPlayer = dist_between_objects(o, player);

    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        o->oForwardVel = 0;
        o->oVelY = 0;
        spawn_mist_particles_variable(0, 0, 60.0f);
        cur_obj_init_animation_with_sound(8);
        o->header.gfx.animInfo.animFrame = 0;
        cur_obj_start_cam_event(o, CAM_EVENT_BOWSER_JUMP);
        if (BITDW) {
            if (distanceToPlayer < 850.0f)
                player->oInteractStatus |= INT_STATUS_MARIO_UNK1;
            else
                player->oInteractStatus |= INT_STATUS_HOOT_GRABBED_BY_MARIO; // hmm...
        }
        return 1;
    } else
        return 0;
}

void bowser_short_second_hop(void) {
    if (BITS && o->oBowserUnkF4 & 0x10000)
        if (o->oBowserDistToCentre > 1000.0f)
            o->oForwardVel = 60.0f;
}

void bowser_act_jump(void) {
    UNUSED s32 unused;
    if (o->oSubAction == 0) {
        if (bowser_set_anim_in_air()) {
            if (BITS && o->oBowserUnkF4 & 0x10000)
                o->oVelY = 70.0f;
            else
                o->oVelY = 80.0f;
            o->oBowserUnkF8 = 0;
            bowser_short_second_hop();
            o->oSubAction++;
        }
    } else if (o->oSubAction == 1) {
#ifndef VERSION_JP
        if (o->oBehParams2ndByte == 2 && o->oBowserUnkF4 & 0x10000)
            bowser_reset_fallen_off_stage();
#endif
        if (bowser_land()) {
            o->oBowserUnkF4 &= ~0x10000;
            o->oForwardVel = 0.0f;
            o->oSubAction++;
            bowser_spawn_shockwave();
            if (BITFS)
                o->oAction = 19;
        } else {
        }
    } else if (cur_obj_check_if_near_animation_end())
        o->oAction = 0;
}

void bowser_act_jump_towards_mario(void) {
    f32 sp1C = D_8032F50C[0];
    f32 sp18 = D_8032F510[0];
    if (o->oSubAction == 0) {
        if (bowser_set_anim_in_air()) {
            o->oVelY = sp1C;
            o->oForwardVel = sp18;
            o->oBowserUnkF8 = 0;
            o->oSubAction++;
        }
    } else if (o->oSubAction == 1) {
        if (bowser_land())
            o->oSubAction++;
    } else if (cur_obj_check_if_near_animation_end())
        o->oAction = 0;
}

void bowser_act_hit_edge(void) {
    o->oForwardVel = 0.0f;
    if (o->oTimer == 0)
        o->oBowserUnkF8 = 0;
    switch (o->oSubAction) {
        case 0:
            cur_obj_init_animation_with_sound(23);
            if (cur_obj_check_if_near_animation_end())
                o->oBowserUnkF8++;
            if (o->oBowserUnkF8 > 0)
                o->oSubAction++;
            break;
        case 1:
            cur_obj_init_animation_with_sound(24);
            if (cur_obj_check_if_near_animation_end())
                o->oAction = 11;
            break;
    }
}

void bowser_act_spit_fire_onto_floor(void) {
    if (gHudDisplay.wedges < 4)
        o->oBowserUnk108 = 3;
    else
        o->oBowserUnk108 = random_float() * 3.0f + 1.0f;
    cur_obj_init_animation_with_sound(22);
    if (cur_obj_check_anim_frame(5))
        obj_spit_fire(0, 200, 180, 7.0f, MODEL_RED_FLAME, 30.0f, 10.0f, 0x1000);
    if (cur_obj_check_if_near_animation_end())
        o->oSubAction++;
    if (o->oSubAction >= o->oBowserUnk108)
        o->oAction = 0;
}

s32 bowser_turn_on_timer(s32 a0, s16 a1) {
    if (o->oSubAction == 0) {
        if (cur_obj_init_animation_and_check_if_near_end(15))
            o->oSubAction++;
    } else if (o->oSubAction == 1) {
        if (cur_obj_init_animation_and_check_if_near_end(14))
            o->oSubAction++;
    } else
        cur_obj_init_animation_with_sound(12);
    o->oForwardVel = 0.0f;
    o->oMoveAngleYaw += a1;
    if (o->oTimer >= a0)
        return 1;
    else
        return 0;
}

void bowser_act_turn_from_edge(void) {
    if (bowser_turn_on_timer(63, 0x200))
        o->oAction = 0;
}

void bowser_act_charge_mario(void) {
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return; }
    s32 angleToPlayer = obj_angle_to_object(o, player);

    s32 sp34;
    if (o->oTimer == 0)
        o->oForwardVel = 0.0f;
    switch (o->oSubAction) {
        case 0:
            o->oBowserUnkF8 = 0;
            if (cur_obj_init_animation_and_check_if_near_end(18))
                o->oSubAction = 1;
            break;
        case 1:
            o->oForwardVel = 50.0f;
            if (cur_obj_init_animation_and_check_if_near_end(0x13) != 0) {
                o->oBowserUnkF8++;
                if (o->oBowserUnkF8 >= 6)
                    o->oSubAction = 3;
                if (o->oBowserUnkF8 >= 2)
                    if (abs_angle_diff(angleToPlayer, o->oMoveAngleYaw) > 0x2000)
                        o->oSubAction = 3;
            }
            cur_obj_rotate_yaw_toward(angleToPlayer, 0x200);
            break;
        case 3:
            o->oBowserUnkF8 = 0;
            cur_obj_init_animation_with_sound(21);
            spawn_object_relative_with_scale(0, 100, -50, 0, 3.0f, o, MODEL_SMOKE, bhvWhitePuffSmoke2);
            spawn_object_relative_with_scale(0, -100, -50, 0, 3.0f, o, MODEL_SMOKE,
                                             bhvWhitePuffSmoke2);
            if (approach_f32_signed(&o->oForwardVel, 0, -1.0f))
                o->oSubAction = 2;
            cur_obj_extend_animation_if_at_end();
            break;
        case 2:
            o->oForwardVel = 0.0f;
            cur_obj_init_animation_with_sound(20);
            if (cur_obj_check_if_near_animation_end()) {
                if (BITS)
                    sp34 = 10;
                else
                    sp34 = 30;
                if (o->oBowserUnkF8 > sp34)
                    o->oAction = 0;
                o->oBowserUnkF8++;
            }
            cur_obj_extend_animation_if_at_end();
            break;
    }
    if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE)
        o->oAction = 10;
}

s32 bowser_check_hit_mine(void) {
    struct Object *mine;
    f32 sp18;
    mine = cur_obj_find_nearest_object_with_behavior(bhvBowserBomb, &sp18);
    if (mine != NULL && sp18 < 800.0f) {
        mine->oInteractStatus |= INT_STATUS_HIT_MINE;
        return 1;
    }
    return 0;
}

void bowser_act_thrown_dropped(void)
{
    UNUSED s32 unused;
    if (o->oTimer < 2)
        o->oBowserUnkF8 = 0;
    if (o->oSubAction == 0) {
        cur_obj_init_animation_with_sound(2);
        bowser_bounce(&o->oBowserUnkF8);
        if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
            o->oForwardVel = 0.0f;
            o->oSubAction++;
        }
    } else if (cur_obj_init_animation_and_check_if_near_end(0))
        o->oAction = 0;
    if (bowser_check_hit_mine()) {
        o->oHealth--;
        if (o->oHealth <= 0)
            o->oAction = 4;
        else
            o->oAction = 12;
    }
}

void bowser_set_goal_invisible(void) {
    o->oBowserUnk1AC = 0;
    if (o->oOpacity == 0) {
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;
        o->oPosY = o->oHomeY - 1000.0f;
    }
}

void bowser_act_jump_onto_stage(void) {
    s32 sp2C;
    UNUSED s32 unused;
    struct Surface *sp24 = o->oFloor;
    if (sp24 != NULL && sp24->flags & 1)
        sp2C = 1;
    else
        sp2C = 0;
    o->oBowserUnkF4 |= 0x10000;
    switch (o->oSubAction) {
        case 0:
            if (o->oTimer == 0) {
                o->oFaceAnglePitch = 0;
                o->oFaceAngleRoll = 0;
            } //? missing else
            o->oFaceAnglePitch += 0x800;
            o->oFaceAngleRoll += 0x800;
            if (!(o->oFaceAnglePitch & 0xFFFF))
                o->oSubAction++;
            bowser_set_goal_invisible();
            break;
        case 1:
            cur_obj_init_animation_with_sound(9);
            if (cur_obj_check_anim_frame(11)) {
                o->oMoveAngleYaw = o->oBowserAngleToCentre;
                o->oVelY = 150.0f;
                o->oBowserUnk1AC = 0xFF;
                o->oBowserUnkF8 = 0;
                o->oSubAction++;
            } else
                bowser_set_goal_invisible();
            break;
        case 2:
            if (o->oPosY > o->oHomeY) {
                o->oDragStrength = 0.0f;
                if (o->oBowserDistToCentre < 2500.0f) {
                    if (absf(o->oFloorHeight - o->oHomeY) < 100.0f)
                        approach_f32_signed(&o->oForwardVel, 0, -5.0f);
                    else
                        cur_obj_forward_vel_approach_upward(150.0f, 2.0f);
                } else
                    cur_obj_forward_vel_approach_upward(150.0f, 2.0f);
            }
            if (bowser_land()) {
                o->oDragStrength = 10.0f;
                o->oSubAction++;
                if (sp2C == 0)
                    bowser_spawn_shockwave();
                else if (BITS)
                    o->oAction = 13;
                if (BITFS)
                    o->oAction = 19;
            }
#ifndef VERSION_JP
            bowser_reset_fallen_off_stage();
#else
            if (o->oVelY < 0.0f && o->oPosY < o->oHomeY - 300.0f) {
                o->oPosZ = 0.0f, o->oPosX = o->oPosZ;
                o->oPosY = o->oHomeY + 2000.0f;
                o->oVelY = 0.0f;
            }
#endif
            break;
        case 3:
            if (cur_obj_check_if_near_animation_end()) {
                o->oAction = 0;
                o->oBowserUnkF4 &= ~0x10000;
                cur_obj_extend_animation_if_at_end();
            }
            break;
    }
    print_debug_bottom_up("sp %d", o->oForwardVel);
}

void bowser_act_dance(void) {
    if (is_item_in_array(o->oTimer, D_8032F514))
        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
    if (cur_obj_init_animation_and_check_if_near_end(10))
        o->oAction = 0;
}

void bowser_spawn_grand_star_key(void) {
    struct Object* reward = NULL;
    if (BITS) {
        struct Object* prevReward = cur_obj_nearest_object_with_behavior(bhvGrandStar);
        reward = (prevReward != NULL) ? prevReward : spawn_object(o, MODEL_STAR, bhvGrandStar);
        gSecondCameraFocus = reward;

        if (sync_object_is_owned_locally(o->oSyncID) && prevReward == NULL && reward != NULL) {
            // set the home position
            reward->oHomeX = reward->oPosX;
            reward->oHomeY = reward->oPosY;
            reward->oHomeZ = reward->oPosZ;
            
            sync_object_set_id(reward);
            
            struct Object* spawn_objects[] = { reward };
            u32 models[] = { MODEL_STAR };
            network_send_spawn_objects(spawn_objects, models, 1);
        }
    } else {
        struct Object* prevReward = cur_obj_nearest_object_with_behavior(bhvBowserKey);
        reward = (prevReward != NULL) ? prevReward : spawn_object(o, MODEL_BOWSER_KEY, bhvBowserKey);
        gSecondCameraFocus = reward;
        cur_obj_play_sound_2(SOUND_GENERAL2_BOWSER_KEY);

        if (prevReward == NULL && reward != NULL) {
            // set the home position
            reward->oHomeX = reward->oPosX;
            reward->oHomeY = reward->oPosY;
            reward->oHomeZ = reward->oPosZ;
            struct Object* spawn_objects[] = { reward };
            u32 models[] = { MODEL_BOWSER_KEY };
            network_send_spawn_objects(spawn_objects, models, 1);
        }
    }
    if (gSecondCameraFocus != NULL) {
        gSecondCameraFocus->oAngleVelYaw = o->oAngleVelYaw;
    }
}

void bowser_fly_back_dead(void) {
    cur_obj_init_animation_with_sound(16);
    if (BITS)
        o->oForwardVel = -400.0f;
    else
        o->oForwardVel = -200.0f;
    o->oVelY = 100.0f;
    o->oMoveAngleYaw = o->oBowserAngleToCentre + 0x8000;
    o->oBowserUnkF8 = 0;
    o->oSubAction++;
}

void bowser_dead_bounce(void) {
    o->oBowserEyesShut = 1;
    bowser_bounce(&o->oBowserUnkF8);
    if (o->oMoveFlags & OBJ_MOVE_LANDED)
        cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
    if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
        o->oForwardVel = 0.0f;
        o->oSubAction++;
    }
}

s32 bowser_dead_wait_for_mario(void) {
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return 0; }
    s32 distanceToPlayer = dist_between_objects(o, player);
    s32 angleToPlayer = obj_angle_to_object(o, player);

    s32 ret = 0;
    cur_obj_become_intangible();
    if (cur_obj_init_animation_and_check_if_near_end(17) && distanceToPlayer < 700.0f
        && abs_angle_diff(player->oMoveAngleYaw, angleToPlayer) > 0x6000)
        ret = 1;
    cur_obj_extend_animation_if_at_end();
    o->oBowserUnkF8 = 0;
    return ret;
}

s32 bowser_dead_twirl_into_trophy(void) {
    bowserIsDying = TRUE;
    if (o->header.gfx.scale[0] < 0.8)
        o->oAngleVelYaw += 0x80;
    if (o->header.gfx.scale[0] > 0.2) {
        o->header.gfx.scale[0] = o->header.gfx.scale[0] - 0.02;
        o->header.gfx.scale[2] = o->header.gfx.scale[2] - 0.02;
    } else {
        o->header.gfx.scale[1] = o->header.gfx.scale[1] - 0.01;
        o->oVelY = 20.0f;
        o->oGravity = 0.0f;
    }
    if (o->header.gfx.scale[1] < 0.5)
        return 1;
    o->oMoveAngleYaw += o->oAngleVelYaw;
    if (o->oOpacity >= 3)
        o->oOpacity -= 2;
    return 0;
}

void bowser_dead_hide(void) {
    cur_obj_scale(0);
    o->oForwardVel = 0;
    o->oVelY = 0;
    o->oGravity = 0;
}

u8 bowser_dead_not_bits_end_continue_dialog(void) { return o->oAction == 4 && o->oSubAction == 3; }

s32 bowser_dead_not_bits_end(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);

    if (o->oBowserUnkF8 < 2) {
        if (o->oBowserUnkF8 == 0) {
            seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            o->oBowserUnkF8++;
        }
        if (marioState && should_start_or_continue_dialog(marioState, o) && cur_obj_update_dialog(marioState, 2, 18, *sBowserDefeatedDialogText[o->oBehParams2ndByte], 0, bowser_dead_not_bits_end_continue_dialog)) {
            o->oBowserUnkF8++;
            cur_obj_play_sound_2(SOUND_GENERAL2_BOWSER_EXPLODE);
            seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
            seq_player_fade_out(SEQ_PLAYER_LEVEL, 1);
            network_send_object(o);

        }
    } else if (bowser_dead_twirl_into_trophy()) {
        bowser_dead_hide();
        spawn_triangle_break_particles(20, 116, 1.0f, 0);
        bowser_spawn_grand_star_key();
        if (gMarioStates[0].visibleToEnemies) {
            set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
        }
        return 1;
    }
    return 0;
}

u8 bowser_dead_bits_end_continue_dialog(void) { return o->oAction == 4 && o->oBowserUnkF8 < 2; }

s32 bowser_dead_bits_end(void) {
    struct MarioState *marioState = nearest_mario_state_to_object(o);
    
    if (o->oBowserUnkF8 < 2) {
        s32 dialogID = gBehaviorValues.dialogs.Bowser3Defeated120StarsDialog;
        if (gHudDisplay.stars < 120) {
            dialogID = gBehaviorValues.dialogs.Bowser3DefeatedDialog;
        }
        if (o->oBowserUnkF8 == 0) {
            seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            o->oBowserUnkF8++;
        }
        if (marioState && should_start_or_continue_dialog(marioState, o) && cur_obj_update_dialog(marioState, 2, 18, dialogID, 0, bowser_dead_bits_end_continue_dialog)) {
            cur_obj_set_model(smlua_model_util_load(E_MODEL_BOWSER2));
            seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
            seq_player_fade_out(SEQ_PLAYER_LEVEL, 1);
            bowser_spawn_grand_star_key();
            o->oBowserUnkF8++;
        }
    } else if (o->oOpacity > 4)
        o->oOpacity -= 4;
    else {
        bowser_dead_hide();
        return 1;
    }
    return 0;
}

void bowser_act_dead(void) {
    switch (o->oSubAction) {
        case 0:
            bowser_fly_back_dead();
            break;
        case 1:
            bowser_dead_bounce();
            break;
        case 2:
            if (bowser_dead_wait_for_mario()) {
                o->oBowserUnkF8 = 0;
                if (BITS)
                    o->oSubAction = 10;
                else {
                    o->activeFlags |= ACTIVE_FLAG_DITHERED_ALPHA;
                    o->oSubAction++;
                }
            }
            break;
        case 3:
            if (bowser_dead_not_bits_end())
                o->oSubAction++;
            break;
        case 4:
            break;
        case 10:
            if (bowser_dead_bits_end())
                o->oSubAction++;
            break;
        case 11:
            break;
    }
}

void bhv_tilting_bowser_lava_platform_init(void) {
    sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    sync_object_init_field(o, &o->oAngleVelPitch);
    sync_object_init_field(o, &o->oAngleVelRoll);
    sync_object_init_field(o, &o->oFaceAnglePitch);
    sync_object_init_field(o, &o->oFaceAngleRoll);
    sync_object_init_field(o, &o->oMoveAnglePitch);
    sync_object_init_field(o, &o->oMoveAngleRoll);
}

void bowser_tilt_platform(struct Object* platform, s16 a1) {
    s16 angle;
    angle = o->oBowserAngleToCentre + 0x8000;
    platform->oAngleVelPitch = coss(angle) * a1;
    platform->oAngleVelRoll = -sins(angle) * a1;
}

void bowser_act_ride_tilting_platform(void) {
    struct Object* platform = cur_obj_nearest_object_with_behavior(bhvTiltingBowserLavaPlatform);
    UNUSED s16 sp2A = o->oBowserAngleToCentre + 0x8000;
    s16 sp28;
    UNUSED s32 unused;
    s32 i;
    s32 sp1C;
    if (platform == NULL)
        o->oAction = 0;
    else {
        i = 0;
        sp1C = 1;
        while (D_8032F520[i][2] != 0) {
            if (o->oTimer < D_8032F520[i][2]) {
                sp28 = D_8032F520[i][1];
                if (D_8032F520[i][0] > 0)
                    sp28 = (D_8032F520[i][2] - o->oTimer - 1) * sp28;
                else
                    sp28 = (o->oTimer - D_8032F520[i - 1][2]) * sp28;
                bowser_tilt_platform(platform, sp28);
                if (sp28 != 0)
                    play_sound(SOUND_ENV_UNKNOWN4, platform->header.gfx.cameraToObject);
                sp1C = 0;
                break;
            }
            i++;
        }
        if (sp1C) {
            o->oAction = 0;
            platform->oAngleVelPitch = 0;
            platform->oAngleVelRoll = 0;
            platform->oFaceAnglePitch = 0;
            platform->oFaceAngleRoll = 0;
        }
    }
    cur_obj_extend_animation_if_at_end();
}

void bowser_act_nothing(void) {
    
}

s32 bowser_check_fallen_off_stage(void) // bowser off stage?
{
    if (o->oAction != 2 && o->oAction != 19) {
        if (o->oPosY < o->oHomeY - 1000.0f)
            return 1;
        if (o->oMoveFlags & OBJ_MOVE_LANDED) {
            if (o->oFloorType == SURFACE_BURNING)
                return 1;
            if (o->oFloorType == SURFACE_DEATH_PLANE)
                return 1;
        }
    }
    return 0;
}

void (*sBowserActions[])(void) = { bowser_act_default,  bowser_act_thrown_dropped,  bowser_act_jump_onto_stage,  bowser_act_dance,
                                   bowser_act_dead,  bowser_act_text_wait,  bowser_act_intro_walk,  bowser_act_charge_mario,
                                   bowser_act_spit_fire_into_sky,  bowser_act_spit_fire_onto_floor,  bowser_act_hit_edge, bowser_act_turn_from_edge,
                                   bowser_act_hit_mine, bowser_act_jump, bowser_act_walk_to_mario, bowser_act_breath_fire,
                                   bowser_act_teleport, bowser_act_jump_towards_mario, bowser_act_unused_slow_walk, bowser_act_ride_tilting_platform,
                                   bowser_act_nothing, };
struct SoundState D_8032F5B8[] = { { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 1, 0, -1, SOUND_OBJ_BOWSER_WALK },
                                   { 1, 0, -1, SOUND_OBJ2_BOWSER_ROAR },
                                   { 1, 0, -1, SOUND_OBJ2_BOWSER_ROAR },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 1, 20, 40, SOUND_OBJ_BOWSER_WALK },
                                   { 1, 20, -1, SOUND_OBJ_BOWSER_WALK },
                                   { 1, 20, 40, SOUND_OBJ_BOWSER_WALK },
                                   { 1, 0, -1, SOUND_OBJ_BOWSER_TAIL_PICKUP },
                                   { 1, 0, -1, SOUND_OBJ_BOWSER_DEFEATED },
                                   { 1, 8, -1, SOUND_OBJ_BOWSER_WALK },
                                   { 1, 8, 17, SOUND_OBJ_BOWSER_WALK },
                                   { 1, 8, -10, SOUND_OBJ_BOWSER_WALK },
                                   { 0, 0, 0, NO_SOUND },
                                   { 1, 5, -1, SOUND_OBJ_FLAME_BLOWN },
                                   { 0, 0, 0, NO_SOUND },
                                   { 0, 0, 0, NO_SOUND },
                                   { 1, 0, -1, SOUND_OBJ_BOWSER_TAIL_PICKUP },
                                   { 1, 0, -1, SOUND_OBJ2_BOWSER_ROAR } };
s8 D_8032F690[4] = { 0, 0, 1, 0 };
s8 D_8032F694[4] = { 1, 1, 3, 0 };
extern u8 bowser_3_seg7_collision_07004B94[];
extern u8 bowser_3_seg7_collision_07004C18[];
extern u8 bowser_3_seg7_collision_07004C9C[];
extern u8 bowser_3_seg7_collision_07004D20[];
extern u8 bowser_3_seg7_collision_07004DA4[];
extern u8 bowser_3_seg7_collision_07004E28[];
extern u8 bowser_3_seg7_collision_07004EAC[];
extern u8 bowser_3_seg7_collision_07004F30[];
extern u8 bowser_3_seg7_collision_07004FB4[];
extern u8 bowser_3_seg7_collision_07005038[];
struct Struct8032F698 D_8032F698[] = { { NULL, 0, 0, 0, 0 },
                                       { bowser_3_seg7_collision_07004B94, -800, -1000, -20992, 0 },
                                       { bowser_3_seg7_collision_07004C18, -1158, 390, -18432, 0 },
                                       { bowser_3_seg7_collision_07004C9C, -1158, 390, -7680, 0 },
                                       { bowser_3_seg7_collision_07004D20, 0, 1240, -6144, 0 },
                                       { bowser_3_seg7_collision_07004DA4, 0, 1240, 6144, 0 },
                                       { bowser_3_seg7_collision_07004E28, 1158, 390, 7680, 0 },
                                       { bowser_3_seg7_collision_07004EAC, 1158, 390, 18432, 0 },
                                       { bowser_3_seg7_collision_07004F30, 800, -1000, 20992, 0 },
                                       { bowser_3_seg7_collision_07004FB4, 800, -1000, -31744, 0 },
                                       { bowser_3_seg7_collision_07005038, -800, -1000, 31744, 0 } };

void bowser_free_update(void) {
    struct Surface *floor;
    struct Object *platform;
    UNUSED f32 floorHeight;
    if ((platform = o->platform) != NULL)
        apply_platform_displacement((u32)-1, platform);
    o->oBowserUnk10E = 0;

    cur_obj_update_floor_and_walls();
    CUR_OBJ_CALL_ACTION_FUNCTION(sBowserActions);
    cur_obj_move_standard(-78);
    if (bowser_check_fallen_off_stage())
        o->oAction = 2; // bowser go home?
    floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    if ((floor != NULL) && (floor->object != 0))
        o->platform = floor->object;
    else
        o->platform = NULL;
    exec_anim_sound_state(D_8032F5B8, sizeof(D_8032F5B8) / sizeof(struct SoundState));
}

void bowser_held_update(void) {
    if (o->heldByPlayerIndex >= MAX_PLAYERS) { return; }
    struct MarioState* marioState = &gMarioStates[o->heldByPlayerIndex];
    struct Object* player = marioState->marioObj;

    if (marioState->heldObj != o) {
        o->oHeldState = HELD_FREE;
        return;
    }

    o->oBowserUnkF4 &= ~0x20000;
    cur_obj_become_intangible();

    switch (o->oBowserUnk10E) {
        case 0:
            cur_obj_play_sound_2(SOUND_OBJ_BOWSER_TAIL_PICKUP);
            cur_obj_unrender_and_reset_state(3, 1);
            o->oBowserUnk10E++;
            break;
        case 1:
            if (cur_obj_check_if_near_animation_end()) {
                cur_obj_init_animation_with_sound(2);
                o->oBowserUnk10E++;
            }
            break;
        case 2:
            break;
    }
    o->oMoveFlags = 0;
    o->oBowserHeldAnglePitch = player->oMoveAnglePitch;
    o->oBowserHeldAngleVelYaw = player->oAngleVelYaw;
    o->oMoveAngleYaw = player->oMoveAngleYaw;
}

void bowser_thrown_dropped_update(void) {
    u8 needsSync = (o->oSubAction != 0 || o->oBowserUnk10E != 0);
    f32 sp1C;
    o->oBowserUnk10E = 0;
    cur_obj_get_thrown_or_placed(1.0f, 1.0f, 1);
    sp1C = o->oBowserHeldAngleVelYaw / 3000.0 * 70.0f;
    if (sp1C < 0.0f)
        sp1C = -sp1C;
    if (sp1C > 90.0f)
        sp1C *= 2.5; // > 90 => get bigger?
    o->oForwardVel = coss(o->oBowserHeldAnglePitch) * sp1C;
    o->oVelY = -sins(o->oBowserHeldAnglePitch) * sp1C;
    cur_obj_become_intangible();
    if (o->prevObj) {
        o->prevObj->oAction = 1; // not sure what prevObj is
        o->prevObj->oTimer = 0;
        o->prevObj->oSubAction = 0;
    }
    o->oTimer = 0;
    o->oSubAction = 0;

    if (needsSync) {
        network_send_object(o);
    }
}

void bhv_bowser_loop(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    // look for animation difference and override

    struct AnimationTable *animations = o->oAnimations;
    struct Animation* anim = NULL;
    if (animations && networkBowserAnimationIndex < animations->count) {
        anim = (struct Animation*)animations->anims[networkBowserAnimationIndex];
        if (o->header.gfx.animInfo.curAnim != anim) {
            geo_obj_init_animation(&o->header.gfx, anim);
        }
    }

    // If Bowser isn't in a cutscene, It's been played already.
    if (!bowserCutscenePlayed && (o->oAction != 5 && o->oAction != 6 && o->oAction != 20)) {
        bowserCutscenePlayed = TRUE;
    }

    s16 angleToMario;  // AngleToMario from Bowser's perspective
    s16 angleToCentre; // AngleToCentre from Bowser's perspective

    o->oBowserDistToCentre = sqrtf(o->oPosX * o->oPosX + o->oPosZ * o->oPosZ);
    o->oBowserAngleToCentre = atan2s(0.0f - o->oPosZ, 0.0f - o->oPosX);
    angleToMario = abs_angle_diff(o->oMoveAngleYaw, angleToPlayer);
    angleToCentre = abs_angle_diff(o->oMoveAngleYaw, o->oBowserAngleToCentre);
    o->oBowserUnkF4 &= ~0xFF;
    if (angleToMario < 0x2000)
        o->oBowserUnkF4 |= 2;
    if (angleToCentre < 0x3800)
        o->oBowserUnkF4 |= 4;
    if (o->oBowserDistToCentre < 1000.0f)
        o->oBowserUnkF4 |= 0x10;
    if (distanceToPlayer < 850.0f)
        o->oBowserUnkF4 |= 8;
    switch (o->oHeldState) {
        case HELD_FREE:
            bowser_free_update();
            break;
        case HELD_HELD:
            bowser_held_update();
            break;
        case HELD_THROWN:
            bowser_thrown_dropped_update();
            break;
        case HELD_DROPPED:
            bowser_thrown_dropped_update();
            break;
    }
    cur_obj_align_gfx_with_floor();
    if (o->oAction != 4)
        if (o->oBowserUnk1AC != o->oOpacity) {
            if (o->oBowserUnk1AC > o->oOpacity) {
                o->oOpacity += 20;
                if (o->oOpacity >= 0x100)
                    o->oOpacity = 0xFF;
            } else {
                o->oOpacity -= 20;
                if (o->oOpacity < 0)
                    o->oOpacity = 0;
            }
        }

    // update animation index
    if (animations) {
        anim = (struct Animation*)animations->anims[networkBowserAnimationIndex];
        if (o->header.gfx.animInfo.curAnim != anim) {
            for (u32 i = 0; i < animations->count; i++) {
                if (o->header.gfx.animInfo.curAnim == o->oAnimations->anims[i]) {
                    networkBowserAnimationIndex = i;
                }
            }
        }
    }
}

void bhv_bowser_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    // Nothing state sanity check.
    if (o->oAction == 20) {
        *shouldOverride = TRUE;
        *shouldOwn = FALSE;
        return;
    }
    
    // tilting platform
    static u8 tiltingTimer = 0;
    if (o->oAction == 19) { tiltingTimer = 5; }
    if (tiltingTimer > 0) {
        tiltingTimer--;
        *shouldOverride = TRUE;
        *shouldOwn = (get_network_player_smallest_global() == gNetworkPlayerLocal);
    }
}

static u8 bhv_bowser_ignore_if_true(void) {
    if (bowserIsDying) { return TRUE; }
    if (o->oAction == 19) { return TRUE; } // let the platform get to a stable state
    if (bowserIsCutscenePlayer && (o->oAction == 5 || o->oAction == 6)) { return TRUE; } // Ignore updates till our cutscene is done.
    return FALSE;
}

void bhv_bowser_init(void) {
    bowserIsDying = FALSE;
    s32 level; // 0 is dw, 1 is fs, 2 is sky
    o->oBowserUnk110 = 1;
    o->oOpacity = 0xFF;
    o->oBowserUnk1AC = 0xFF;
    if (gCurrLevelNum == LEVEL_BOWSER_2)
        level = 1;
    else if (gCurrLevelNum == LEVEL_BOWSER_3)
        level = 2;
    else
        level = 0;
    o->oBehParams2ndByte = level;
    o->oBowserUnk1B2 = D_8032F690[level];
    o->oHealth = D_8032F694[level];
    cur_obj_start_cam_event(o, CAM_EVENT_BOWSER_INIT);
    o->oBowserUnk1AE = 0;
    o->oBowserEyesShut = 0;
    bowserCutscenePlayed = FALSE;
    
    // Make sure we're the first to trigger Bowser.
    if (!is_other_player_active()) {
        bowserIsCutscenePlayer = TRUE;
        o->oAction = 5; // bowser_act_text_wait
    } else { // If we aren't do nothing till we get our sync.
        bowserIsCutscenePlayer = FALSE;
        o->oAction = 20; // bowser_act_nothing
    }
    
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, 8000.0f);
        if (so) {
            so->override_ownership = bhv_bowser_override_ownership;
            so->ignore_if_true = bhv_bowser_ignore_if_true;
            so->fullObjectSync = TRUE;
            sync_object_init_field_with_size(o, &o->header.gfx.node.flags, 16);
            sync_object_init_field_with_size(o, &o->header.gfx.animInfo.animFrame, 16);
            sync_object_init_field(o, &networkBowserAnimationIndex);
            sync_object_init_field(o, &o->header.gfx.scale[0]);
            sync_object_init_field(o, &o->header.gfx.scale[1]);
            sync_object_init_field(o, &o->header.gfx.scale[2]);
        }
    }
}

#undef BITDW
#undef BITFS
#undef BITS

Gfx *geo_update_body_rot_from_parent(s32 run, UNUSED struct GraphNode *node, Mat4 mtx) {
    Mat4 sp20;
    struct Object *sp1C;

    if (run == TRUE) {
        sp1C = (struct Object *) gCurGraphNodeObject;
        if (sp1C->prevObj != NULL) {
            create_transformation_from_matrices(sp20, mtx, *gCurGraphNodeCamera->matrixPtr);
            obj_update_pos_from_parent_transformation(sp20, sp1C->prevObj);
            obj_set_gfx_pos_from_pos(sp1C->prevObj);
        }
    }
    return NULL;
}

void bowser_open_eye_switch(struct Object *a0, struct GraphNodeSwitchCase *switchCase) {
    struct Object* player = nearest_player_to_object(o);
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    s32 sp1C;
    s16 sp1A;
    sp1A = abs_angle_diff(a0->oMoveAngleYaw, angleToPlayer);
    sp1C = switchCase->selectedCase;
    switch (sp1C) {
        case 0:
            if (sp1A > 0x2000) {
                if (a0->oAngleVelYaw > 0)
                    switchCase->selectedCase = 5;
                if (a0->oAngleVelYaw < 0)
                    switchCase->selectedCase = 3;
            }
            if (a0->oBowserUnk1AE > 50)
                switchCase->selectedCase = 1;
            break;
        case 1:
            if (a0->oBowserUnk1AE > 2)
                switchCase->selectedCase = 2;
            break;
        case 2:
            if (a0->oBowserUnk1AE > 2)
                switchCase->selectedCase = 9;
            break;
        case 9:
            if (a0->oBowserUnk1AE > 2)
                switchCase->selectedCase = 0;
            break;
        case 5:
            if (a0->oBowserUnk1AE > 2) {
                switchCase->selectedCase = 6;
                if (a0->oAngleVelYaw <= 0)
                    switchCase->selectedCase = 0;
            }
            break;
        case 6:
            if (a0->oAngleVelYaw <= 0)
                switchCase->selectedCase = 5;
            break;
        case 3:
            if (a0->oBowserUnk1AE > 2) {
                switchCase->selectedCase = 4;
                if (a0->oAngleVelYaw >= 0)
                    switchCase->selectedCase = 0;
            }
            break;
        case 4:
            if (a0->oAngleVelYaw >= 0)
                switchCase->selectedCase = 3;
            break;
        default:
            switchCase->selectedCase = 0;
    }
    if (switchCase->selectedCase != sp1C)
        a0->oBowserUnk1AE = -1;
}

/** Geo switch for controlling the state of bowser's eye direction and open/closed
 * state. Checks whether oBowserEyesShut is TRUE and closes eyes if so and processes
 * direction otherwise.
 */
Gfx *geo_switch_bowser_eyes(s32 run, struct GraphNode *node, UNUSED Mat4 *mtx) {
    UNUSED s16 sp36;
    UNUSED s32 unused;
    struct Object *obj = (struct Object *) gCurGraphNodeObject;
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
    if (run == TRUE) {
        if (gCurGraphNodeHeldObject != NULL)
            obj = gCurGraphNodeHeldObject->objNode;
        switch (sp36 = obj->oBowserEyesShut) {
            case 0: // eyes open, handle eye looking direction
                bowser_open_eye_switch(obj, switchCase);
                break;
            case 1: // eyes closed, blinking
                switchCase->selectedCase = 2;
                break;
        }
        obj->oBowserUnk1AE++;
    }
    return NULL;
}

Gfx *geo_bits_bowser_coloring(s32 run, struct GraphNode *node, UNUSED s32 a2) {
    Gfx *sp2C = NULL;
    Gfx *sp28;
    struct Object *sp24;
    struct GraphNodeGenerated *sp20;

    if (run == 1) {
        sp24 = (struct Object *) gCurGraphNodeObject;
        sp20 = (struct GraphNodeGenerated *) node;
        if (gCurGraphNodeHeldObject != 0)
            sp24 = gCurGraphNodeHeldObject->objNode;
        if (sp24->oOpacity == 0xFF)
            sp20->fnNode.node.flags = (sp20->fnNode.node.flags & 0xFF) | GRAPH_NODE_TYPE_FUNCTIONAL;
        else
            sp20->fnNode.node.flags = (sp20->fnNode.node.flags & 0xFF) | (GRAPH_NODE_TYPE_FUNCTIONAL | GRAPH_NODE_TYPE_400);
        sp28 = sp2C = alloc_display_list(2 * sizeof(Gfx));
        if (sp28 == NULL) { return NULL; }

        if (sp24->oBowserUnk1B2 != 0) {
            gSPClearGeometryMode(sp28++, G_LIGHTING);
        }
        gSPEndDisplayList(sp28);
    }
    return sp2C;
}

void falling_bowser_plat_act_0(void) {
    o->oPlatformUnkF8 = cur_obj_nearest_object_with_behavior(bhvBowser);
    if (BHV_ARR_CHECK(D_8032F698, o->oBehParams2ndByte, struct Struct8032F698)) {
        obj_set_collision_data(o, D_8032F698[o->oBehParams2ndByte].unk0);
    }
    if (o->oPlatformUnkF8 != 0)
        o->oAction = 1;
}

void falling_bowser_plat_act_1(void) {
    u8 doSend = FALSE;
    UNUSED s32 unused;
    struct Object *sp0 = o->oPlatformUnkF8;
    if (sp0 && sp0->platform == o) {
        if (sp0->oAction == 13 && sp0->oBowserUnkF4 & 0x10000) {
            o->oAction = 2;
            doSend = TRUE;
        }
    }
    if (sp0 && sp0->oHealth == 1 && (sp0->oAction == 3 || sp0->oHeldState != HELD_FREE))
        o->oSubAction = 1;
    if (o->oSubAction == 0)
        o->oPlatformUnkFC = 0;
    else {
        if ((gDebugInfo[4][6] + 20) * (o->oBehParams2ndByte - 1) < o->oPlatformUnkFC) {
            o->oAction = 2;
            doSend = TRUE;
        }
        o->oPlatformUnkFC++;
    }

    if (doSend) {
        network_send_object(o);
    }
}

void falling_bowser_plat_act_2(void) {
    Vec3f sp24;
    s16 sp22;
    f32 sp1C;
    UNUSED struct Object *sp18 = o->oPlatformUnkF8;
    if (o->oTimer == 0 || o->oTimer == 22)
        cur_obj_play_sound_2(SOUND_GENERAL_BOWSER_PLATFORM_2);
    if (o->oTimer < 22) {
        set_environmental_camera_shake(SHAKE_ENV_FALLING_BITS_PLAT);
        o->oVelY = 8.0f;
        o->oGravity = 0.0f;
    } else
        o->oGravity = -4.0f;
    if ((o->oTimer & 1) == 0 && o->oTimer < 14 && BHV_ARR_CHECK(D_8032F698, o->oBehParams2ndByte, struct Struct8032F698)) {
        sp22 = D_8032F698[o->oBehParams2ndByte].unk3 + (gDebugInfo[4][1] << 8);
        sp1C = -(o->oTimer / 2) * 290 + 1740;
        vec3f_copy_2(sp24, &o->oPosX);
        o->oPosX = D_8032F698[o->oBehParams2ndByte].unk1 + sins(sp22 + 5296) * sp1C;
        o->oPosZ = D_8032F698[o->oBehParams2ndByte].unk2 + coss(sp22 + 5296) * sp1C;
        o->oPosY = 307.0f;
        spawn_mist_particles_variable(4, 0, 100.0f);
        o->oPosX = D_8032F698[o->oBehParams2ndByte].unk1 + sins(sp22 - 5296) * sp1C;
        o->oPosZ = D_8032F698[o->oBehParams2ndByte].unk2 + coss(sp22 - 5296) * sp1C;
        spawn_mist_particles_variable(4, 0, 100);
        vec3f_copy_2(&o->oPosX, sp24);
    }
    cur_obj_move_using_fvel_and_gravity();
    if (o->oTimer > 300)
        obj_mark_for_deletion(o);
}

void (*sFallingBowserPlatformActions[])(void) = { falling_bowser_plat_act_0,
                                                  falling_bowser_plat_act_1,
                                                  falling_bowser_plat_act_2 };

struct ObjectHitbox sGrowingBowserFlameHitbox = {
    /* interactType: */ INTERACT_FLAME,
    /* downOffset: */ 20,
    /* damageOrCoinValue: */ 1,
    /* health: */ 0,
    /* numLootCoins: */ 0,
    /* radius: */ 10,
    /* height: */ 40,
    /* hurtboxRadius: */ 0,
    /* hurtboxHeight: */ 0,
};

struct ObjectHitbox sBowserFlameHitbox = {
    /* interactType: */ INTERACT_FLAME,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 1,
    /* health: */ 0,
    /* numLootCoins: */ 0,
    /* radius: */ 10,
    /* height: */ 40,
    /* hurtboxRadius: */ 0,
    /* hurtboxHeight: */ 0,
};

f32 D_8032F748[] = { -8.0f, -6.0f, -3.0f };

u8 bhv_falling_bowser_platform_ignore_if_true(void) {
    return (o->oAction > 1);
}

void bhv_falling_bowser_platform_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->ignore_if_true = bhv_falling_bowser_platform_ignore_if_true;
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oTimer);
        }
    }

    CUR_OBJ_CALL_ACTION_FUNCTION(sFallingBowserPlatformActions);
}

void bowser_flame_despawn(void) {
    obj_mark_for_deletion(o);
    spawn_object_with_scale(o, MODEL_NONE, bhvBlackSmokeUpward, 1.0f);
    if (random_float() < 0.1) {
        spawn_object(o, MODEL_YELLOW_COIN, bhvTemporaryYellowCoin);
    }
}

s32 bowser_flame_should_despawn(s32 maxTime) {
    if (maxTime < o->oTimer)
        return 1;
    if (o->oFloorType == SURFACE_BURNING)
        return 1;
    if (o->oFloorType == SURFACE_DEATH_PLANE)
        return 1;
    return 0;
}

void bhv_flame_bowser_init(void) {
    o->oAnimState = (s32)(random_float() * 10.0f);
    o->oMoveAngleYaw = random_u16();
    if (random_float() < 0.2)
        o->oVelY = 80.0f;
    else
        o->oVelY = 20.0f;
    o->oForwardVel = 10.0f;
    o->oGravity = -1.0f;
    o->oFlameScale = random_float() + 1.0f;
}

void bhv_flame_large_burning_out_init(void) {
    o->oAnimState = (s32)(random_float() * 10.0f);
    o->oMoveAngleYaw = random_u16();
    o->oVelY = 10.0f;
    o->oForwardVel = 0.0f;
    o->oFlameScale = 7.0f;
}

void bowser_flame_move(void) {
    s32 sp4;
    sp4 = ((o->oFlameSpeedTimerOffset + gGlobalTimer) & 0x3F) << 10;
    o->oPosX += sins(o->oMoveAngleYaw) * sins(sp4) * 4.0f;
    o->oPosZ += coss(o->oMoveAngleYaw) * sins(sp4) * 4.0f;
}

void bhv_flame_bowser_loop(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
    if (o->oVelY < -4.0f)
        o->oVelY = -4.0f;
    if (o->oAction == 0) {
        cur_obj_become_intangible();
        bowser_flame_move();
        if (o->oMoveFlags & OBJ_MOVE_LANDED) {
            o->oAction++;
            if (cur_obj_has_behavior(bhvFlameLargeBurningOut))
                o->oFlameScale = 8.0f;
            else
                o->oFlameScale = random_float() * 2 + 6.0f;
            o->oForwardVel = 0;
            o->oVelY = 0;
            o->oGravity = 0;
        }
    } else {
        cur_obj_become_tangible();
        if (o->oTimer > o->oFlameScale * 10 + 5.0f) {
            o->oFlameScale -= 0.15;
            if (o->oFlameScale <= 0)
                bowser_flame_despawn();
        }
    }
    cur_obj_scale(o->oFlameScale);
    o->oGraphYOffset = o->header.gfx.scale[1] * 14.0f;
    obj_set_hitbox(o, &sBowserFlameHitbox);
}

void bhv_flame_moving_forward_growing_init(void) {
    o->oForwardVel = 30.0f;
    obj_translate_xz_random(o, 80.0f);
    o->oAnimState = (s32)(random_float() * 10.0f);
    o->oFlameScale = 3.0f;
}

void bhv_flame_moving_forward_growing_loop(void) {
    UNUSED s32 unused;
    UNUSED struct Object *sp18;
    obj_set_hitbox(o, &sGrowingBowserFlameHitbox);
    o->oFlameScale = o->oFlameScale + 0.5;
    cur_obj_scale(o->oFlameScale);
    if (o->oMoveAnglePitch > 0x800)
        o->oMoveAnglePitch -= 0x200;
    cur_obj_set_pos_via_transform();
    cur_obj_update_floor_height();
    if (o->oFlameScale > 30.0f)
        obj_mark_for_deletion(o);
    if (o->oPosY < o->oFloorHeight) {
        o->oPosY = o->oFloorHeight;
        sp18 = spawn_object(o, MODEL_RED_FLAME, bhvFlameBowser);
        obj_mark_for_deletion(o);
    }
}

void bhv_flame_floating_landing_init(void) {
    o->oAnimState = (s32)(random_float() * 10.0f);
    o->oMoveAngleYaw = random_u16();
    if (o->oBehParams2ndByte != 0)
        o->oForwardVel = random_float() * 5.0f;
    else
        o->oForwardVel = random_float() * 70.0f;
    o->oVelY = random_float() * 20.0f;
    o->oGravity = -1.0f;
    o->oFlameSpeedTimerOffset = random_float() * 64.0f;
}

void bhv_flame_floating_landing_loop(void) {
    UNUSED s32 unused;
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(0x4e);
    bowser_flame_move();
    if (bowser_flame_should_despawn(900)) {
        obj_mark_for_deletion(o);
    }

    if (BHV_ARR_CHECK(D_8032F748, o->oBehParams2ndByte, f32)) {
        if (o->oVelY < D_8032F748[o->oBehParams2ndByte]) {
            o->oVelY = D_8032F748[o->oBehParams2ndByte];
        }
    }

    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        if (o->oBehParams2ndByte == 0)
            spawn_object(o, MODEL_RED_FLAME, bhvFlameLargeBurningOut);
        else
            spawn_object(o, MODEL_NONE, bhvBlueFlamesGroup); //? wonder if they meant MODEL_BLUE_FLAME?
        obj_mark_for_deletion(o);
    }
    o->oGraphYOffset = o->header.gfx.scale[1] * 14.0f;
}

void bhv_blue_bowser_flame_init(void) {
    obj_translate_xz_random(o, 80.0f);
    o->oAnimState = (s32)(random_float() * 10.0f);
    o->oVelY = 7.0f;
    o->oForwardVel = 35.0f;
    o->oFlameScale = 3.0f;
    o->oFlameUnkFC = random_float() * 0.5;
    o->oGravity = 1.0f;
    o->oFlameSpeedTimerOffset = (s32)(random_float() * 64.0f);
}

void bhv_blue_bowser_flame_loop(void) {
    s32 i;
    obj_set_hitbox(o, &sGrowingBowserFlameHitbox);
    if (o->oFlameScale < 16.0f)
        o->oFlameScale = o->oFlameScale + 0.5;
    cur_obj_scale(o->oFlameScale);
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(0x4e);
    if (o->oTimer > 0x14) {
        if (o->oBehParams2ndByte == 0)
            for (i = 0; i < 3; i++)
                spawn_object_relative_with_scale(0, 0, 0, 0, 5.0f, o, MODEL_RED_FLAME,
                                                 bhvFlameFloatingLanding);
        else {
            spawn_object_relative_with_scale(1, 0, 0, 0, 8.0f, o, MODEL_BLUE_FLAME,
                                             bhvFlameFloatingLanding);
            spawn_object_relative_with_scale(2, 0, 0, 0, 8.0f, o, MODEL_BLUE_FLAME,
                                             bhvFlameFloatingLanding);
        }
        obj_mark_for_deletion(o);
    }
}

void bhv_flame_bouncing_init(void) {
    o->oAnimState = (s32)(random_float() * 10.0f);
    o->oVelY = 30.0f;
    o->oForwardVel = 20.0f;
    o->oFlameScale = o->header.gfx.scale[0];
    o->oFlameSpeedTimerOffset = (s32)(random_float() * 64.0f);
}

void bhv_flame_bouncing_loop(void) {
    struct Object *bowser;
    if (o->oTimer == 0)
        o->oFlameBowser = cur_obj_nearest_object_with_behavior(bhvBowser);
    bowser = o->oFlameBowser;
    o->oForwardVel = 15.0f;
    o->oBounciness = -1.0f;
    cur_obj_scale(o->oFlameScale);
    obj_set_hitbox(o, &sGrowingBowserFlameHitbox);
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
    if (bowser_flame_should_despawn(300))
        obj_mark_for_deletion(o);
    if (bowser != NULL)
        if (bowser->oHeldState == 0)
            if (lateral_dist_between_objects(o, bowser) < 300.0f)
                obj_mark_for_deletion(o);
}

void bhv_blue_flames_group_loop(void) {
    struct Object* player = nearest_player_to_object(o);
    struct Object *flame;
    s32 i;
    if (o->oTimer == 0) {
        if (player) {
            o->oMoveAngleYaw = obj_angle_to_object(o, player);
        }
        o->oBlueFlameNextScale = 5.0f;
    }
    if (o->oTimer < 16) {
        if ((o->oTimer & 1) == 0) {
            for (i = 0; i < 3; i++) {
                flame = spawn_object(o, MODEL_BLUE_FLAME, bhvFlameBouncing);
                if (flame != NULL) {
                    flame->oMoveAngleYaw += i * 0x5555;
                    flame->header.gfx.scale[0] = o->oBlueFlameNextScale;
                }
            }
            o->oBlueFlameNextScale -= 0.5;
        }
    } else
        obj_mark_for_deletion(o);
}
