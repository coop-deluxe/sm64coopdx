// bubba.inc.c

static struct ObjectHitbox sBubbaHitbox = {
    .interactType = INTERACT_CLAM_OR_BUBBA,
    .downOffset = 0,
    .damageOrCoinValue = 1,
    .health = 99,
    .numLootCoins = 0,
    .radius = 300,
    .height = 200,
    .hurtboxRadius = 300,
    .hurtboxHeight = 200,
};

void bubba_act_0(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    f32 sp24;

    sp24 = cur_obj_lateral_dist_to_home();

    treat_far_home_as_mario(2000.0f, &distanceToPlayer, &angleToPlayer);

    o->oAnimState = 0;

    o->oBubbaUnk1AC = obj_get_pitch_to_home(sp24);

    approach_f32_ptr(&o->oBubbaUnkF4, 5.0f, 0.5f);

    if (o->oBubbaUnkFC != 0) {
        if (abs_angle_diff(o->oMoveAngleYaw, o->oBubbaUnk1AE) < 800) {
            o->oBubbaUnkFC = 0;
        }
    } else {
        if (distanceToPlayer >= 25000.0f) {
            o->oBubbaUnk1AE = angleToPlayer;
            o->oBubbaUnkF8 = random_linear_offset(20, 30);
        }

        if ((o->oBubbaUnkFC = o->oMoveFlags & OBJ_MOVE_HIT_WALL) != 0) {
            o->oBubbaUnk1AE = cur_obj_reflect_move_angle_off_wall();
        } else if (o->oTimer > 30 && distanceToPlayer < 2000.0f) {
            o->oAction = 1;
        } else if (o->oBubbaUnkF8 != 0) {
            o->oBubbaUnkF8 -= 1;
        } else {
            o->oBubbaUnk1AE = obj_random_fixed_turn(0x2000);
            o->oBubbaUnkF8 = random_linear_offset(100, 100);
        }
    }
}

void bubba_act_1(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    treat_far_home_as_mario(2500.0f, &distanceToPlayer, &angleToPlayer);

    if (distanceToPlayer > 2500.0f) {
        o->oAction = 0;
    } else if (o->oBubbaUnk100 != 0) {
        if (--o->oBubbaUnk100 == 0) {
            cur_obj_play_sound_2(SOUND_OBJ_BUBBA_CHOMP);
            o->oAction = 0;
        } else if (o->oBubbaUnk100 < 15) {
            o->oAnimState = 1;
        } else if (o->oBubbaUnk100 == 20) {
            s16 val06 = 10000 - (s16)(20.0f * (find_water_level(o->oPosX, o->oPosZ) - o->oPosY));
            o->oBubbaUnk1AC -= val06;
            o->oMoveAnglePitch = o->oBubbaUnk1AC;
            o->oBubbaUnkF4 = 40.0f;
            obj_compute_vel_from_move_pitch(o->oBubbaUnkF4);
            o->oAnimState = 0;
        } else {
            o->oBubbaUnk1AE = angleToPlayer;
            o->oBubbaUnk1AC = o->oBubbaUnk104;

            cur_obj_rotate_yaw_toward(o->oBubbaUnk1AE, 400);
            obj_move_pitch_approach(o->oBubbaUnk1AC, 400);
        }
    } else {
        if (player && abs_angle_diff(player->oFaceAngleYaw, angleToPlayer) < 0x3000) {
            s16 val04 = 0x4000 - atan2s(800.0f, distanceToPlayer - 800.0f);
            if ((s16)(o->oMoveAngleYaw - angleToPlayer) < 0) {
                val04 = -val04;
            }

            o->oBubbaUnk1AE = angleToPlayer + val04;
            ;
        } else {
            o->oBubbaUnk1AE = angleToPlayer;
        }

        o->oBubbaUnk1AC = o->oBubbaUnk104;

        if (obj_is_near_to_and_facing_mario(marioState, 500.0f, 3000)
            && abs_angle_diff(o->oBubbaUnk1AC, o->oMoveAnglePitch) < 3000) {
            o->oBubbaUnk100 = 30;
            o->oBubbaUnkF4 = 0;
            o->oAnimState = 1;
        } else {
            approach_f32_ptr(&o->oBubbaUnkF4, 20.0f, 0.5f);
        }
    }
}

void bhv_bubba_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oBubbaUnkF4);
        sync_object_init_field(o, &o->oBubbaUnkF8);
        sync_object_init_field(o, &o->oBubbaUnkFC);
        sync_object_init_field(o, &o->oBubbaUnk100);
        sync_object_init_field(o, &o->oBubbaUnk104);
        sync_object_init_field(o, &o->oBubbaUnk108);
        sync_object_init_field(o, &o->oBubbaUnk10C);
        sync_object_init_field(o, &o->oBubbaUnk1AC);
        sync_object_init_field(o, &o->oBubbaUnk1B0);
        sync_object_init_field(o, &o->oAnimState);
        sync_object_init_field(o, &o->oMoveAnglePitch);
    }

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    UNUSED s32 unused;

    o->oInteractionSubtype &= ~INT_SUBTYPE_EATS_MARIO;
    if (marioState) {
        o->oBubbaUnk104 = obj_turn_pitch_toward_mario(marioState, 120.0f, 0);
    }

    if (abs_angle_diff(angleToPlayer, o->oMoveAngleYaw) < 0x1000
        && abs_angle_diff(o->oBubbaUnk104 + 0x800, o->oMoveAnglePitch) < 0x2000) {
        if (o->oAnimState != 0 && distanceToPlayer < 250.0f) {
            o->oInteractionSubtype |= INT_SUBTYPE_EATS_MARIO;
        }

        o->hurtboxRadius = 100.0f;
    } else {
        o->hurtboxRadius = 150.0f;
    }

    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case 0:
            bubba_act_0();
            break;
        case 1:
            bubba_act_1();
            break;
    }

    if (o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER) {
        if (o->oMoveFlags & OBJ_MOVE_ENTERED_WATER) {
            struct Object *sp38 = spawn_object(o, MODEL_WATER_SPLASH, bhvWaterSplash);
            if (sp38 != NULL) {
                obj_scale(sp38, 3.0f);
            }

            o->oBubbaUnk108 = o->oVelY;
            o->oBubbaUnk10C = 0.0f;
        } else {
            approach_f32_ptr(&o->oBubbaUnk108, 0.0f, 4.0f);
            if ((o->oBubbaUnk10C -= o->oBubbaUnk108) > 1.0f) {
                s16 sp36 = random_u16();
                o->oBubbaUnk10C -= 1.0f;
                spawn_object_relative(0, 150.0f * coss(sp36), 0x64, 150.0f * sins(sp36), o,
                                      MODEL_WHITE_PARTICLE_SMALL, bhvSmallParticleSnow);
            }
        }

        obj_smooth_turn(&o->oBubbaUnk1B0, &o->oMoveAnglePitch, o->oBubbaUnk1AC, 0.05f, 10, 50, 2000);
        obj_smooth_turn(&o->oBubbaUnk1B2, &o->oMoveAngleYaw, o->oBubbaUnk1AE, 0.05f, 10, 50, 2000);
        obj_compute_vel_from_move_pitch(o->oBubbaUnkF4);
    } else {
        o->oBubbaUnkF4 = sqrtf(o->oForwardVel * o->oForwardVel + o->oVelY * o->oVelY);
        o->oMoveAnglePitch = obj_get_pitch_from_vel();
        obj_face_pitch_approach(o->oMoveAnglePitch, 400);
        o->oBubbaUnk1B0 = 0;
    }

    obj_face_pitch_approach(o->oMoveAnglePitch, 400);
    obj_check_attacks(&sBubbaHitbox, o->oAction);

    cur_obj_move_standard(78);

    o->oFloorHeight += 150.0f;
    if (o->oPosY < o->oFloorHeight) {
        o->oPosY = o->oFloorHeight;
    }
}
