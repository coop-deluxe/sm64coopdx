
/**
 * Behavior for bhvEnemyLakitu.
 * Lakitu comes before it spawned spinies in processing order.
 * TODO: bhvCloud processing order
 */

/**
 * Hitbox for evil lakitu.
 */
static struct ObjectHitbox sEnemyLakituHitbox = {
    .interactType = INTERACT_HIT_FROM_BELOW,
    .downOffset = 0,
    .damageOrCoinValue = 2,
    .health = 0,
    .numLootCoins = 5,
    .radius = 50,
    .height = 50,
    .hurtboxRadius = 40,
    .hurtboxHeight = 50,
};

/**
 * Wait for mario to approach, then spawn the cloud and become visible.
 */
static void enemy_lakitu_act_uninitialized(void) {
    struct Object *player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;

    if (distanceToPlayer < 2000.0f) {
        spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, o, MODEL_MIST, bhvCloud);

        cur_obj_unhide();
        o->oAction = ENEMY_LAKITU_ACT_MAIN;
    }
}   

/**
 * Accelerate toward mario vertically.
 */
static void enemy_lakitu_update_vel_y(f32 offsetY) {
    // In order to encourage oscillation, pass mario by a small margin before
    // accelerating the opposite direction
    f32 margin;
    if (o->oVelY < 0.0f) {
        margin = -3.0f;
    } else {
        margin = 3.0f;
    }

    struct Object* player = nearest_player_to_object(o);
    if (player != NULL) {
        if (o->oPosY < player->oPosY + offsetY + margin) {
            obj_y_vel_approach(4.0f, 0.4f);
        }
        else {
            obj_y_vel_approach(-4.0f, 0.4f);
        }
    }
}

/**
 * Control speed based on distance to mario, turn toward mario, and change move
 * angle toward mario.
 */
static void enemy_lakitu_update_speed_and_angle(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    treat_far_home_as_mario(2000.0f, &distanceToPlayer, &angleToPlayer);

    f32 minSpeed = 0;
    s16 turnSpeed = 0;

    f32 distToMario = distanceToPlayer;
    if (distToMario > 500.0f) {
        distToMario = 500.0f;
    }

    // Move faster the farther away mario is and the faster mario is moving
    if (marioState) {
        if ((minSpeed = 1.2f * marioState->forwardVel) < 8.0f) {
            minSpeed = 8.0f;
        }
    }
    o->oForwardVel = distToMario * 0.04f;
    clamp_f32(&o->oForwardVel, minSpeed, 40.0f);

    // Accelerate toward mario vertically
    enemy_lakitu_update_vel_y(300.0f);

    // Turn toward mario except right after throwing a spiny
    if (o->oEnemyLakituFaceForwardCountdown != 0) {
        o->oEnemyLakituFaceForwardCountdown -= 1;
    } else {
        obj_face_yaw_approach(angleToPlayer, 0x600);
    }

    // Change move angle toward mario faster when farther from mario
    turnSpeed = (s16)(distToMario * 2);
    clamp_s16(&turnSpeed, 0xC8, 0xFA0);
    cur_obj_rotate_yaw_toward(angleToPlayer, turnSpeed);
}

/**
 * When close enough to mario and facing roughly toward him, spawn a spiny and
 * hold it, then enter the hold spiny sub-action.
 */
static void enemy_lakitu_sub_act_no_spiny(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    treat_far_home_as_mario(2000.0f, &distanceToPlayer, &angleToPlayer);

    cur_obj_init_animation_with_sound(1);

    o->oEnemyLakituNumSpinies = cur_obj_count_objects_with_behavior(bhvSpiny, 2000);
    if (o->oEnemyLakituSpinyCooldown != 0) {
        o->oEnemyLakituSpinyCooldown -= 1;
    } else if (o->oEnemyLakituNumSpinies < 3 && distanceToPlayer < 800.0f
               && abs_angle_diff(angleToPlayer, o->oFaceAngleYaw) < 0x4000) {

        if (marioState && marioState->playerIndex == 0) {
            struct Object* spiny = spawn_object(o, MODEL_SPINY_BALL, bhvSpiny);
            if (spiny != NULL) {
                o->prevObj = spiny;
                spiny->oAction = SPINY_ACT_HELD_BY_LAKITU;
                obj_init_animation_with_sound(spiny, &spiny_egg_seg5_anims_050157E4, 0);

                o->oEnemyLakituNumSpinies += 1;
                o->oSubAction = ENEMY_LAKITU_SUB_ACT_HOLD_SPINY;
                o->oEnemyLakituSpinyCooldown = 30;
                network_send_object(o);

                sync_object_set_id(spiny);
                struct Object* spawn_objects[] = { spiny };
                u32 models[] = { MODEL_SPINY_BALL };
                network_send_spawn_objects(spawn_objects, models, 1);
            }
        }
    }
}

/**
 * When close to mario and facing toward him or when mario gets far enough away,
 * enter the throw spiny sub-action.
 */
static void enemy_lakitu_sub_act_hold_spiny(void) {
    if (o->prevObj == NULL) {
        o->oSubAction = ENEMY_LAKITU_SUB_ACT_NO_SPINY;
        o->oEnemyLakituSpinyCooldown = 0;
        return;
    }

    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    treat_far_home_as_mario(2000.0f, &distanceToPlayer, &angleToPlayer);

    cur_obj_init_anim_extend(3);

    if (o->oEnemyLakituSpinyCooldown != 0) {
        o->oEnemyLakituSpinyCooldown -= 1;
    }
    // TODO: Check if anything interesting happens if we bypass this with speed
    else if (distanceToPlayer > o->oDrawingDistance - 100.0f
             || (distanceToPlayer < 500.0f
                 && abs_angle_diff(angleToPlayer, o->oFaceAngleYaw) < 0x2000)) {
        o->oSubAction = ENEMY_LAKITU_SUB_ACT_THROW_SPINY;
        o->oEnemyLakituFaceForwardCountdown = 20;
    }
}

/**
 * Throw the spiny, then enter the no spiny sub-action.
 */
static void enemy_lakitu_sub_act_throw_spiny(void) {
    if (cur_obj_init_anim_check_frame(2, 2)) {
        cur_obj_play_sound_2(SOUND_OBJ_EVIL_LAKITU_THROW);
        o->prevObj = NULL;
    }

    if (cur_obj_check_if_near_animation_end()) {
        o->oSubAction = ENEMY_LAKITU_SUB_ACT_NO_SPINY;
        o->oEnemyLakituSpinyCooldown = random_linear_offset(100, 100);
    }
}

/**
 * Main update function.
 */
static void enemy_lakitu_act_main(void) {
    cur_obj_unhide();
    cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY);

    cur_obj_update_floor_and_walls();

    enemy_lakitu_update_speed_and_angle();
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        o->oMoveAngleYaw = cur_obj_reflect_move_angle_off_wall();
    }

    obj_update_blinking(&o->oEnemyLakituBlinkTimer, 20, 40, 4);

    if (o->prevObj != NULL) {
        if (o->prevObj->behavior != smlua_override_behavior(bhvSpiny) || o->prevObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
            o->prevObj = NULL;
        }
    }

    switch (o->oSubAction) {
        case ENEMY_LAKITU_SUB_ACT_NO_SPINY:
            enemy_lakitu_sub_act_no_spiny();
            break;
        case ENEMY_LAKITU_SUB_ACT_HOLD_SPINY:
            enemy_lakitu_sub_act_hold_spiny();
            break;
        case ENEMY_LAKITU_SUB_ACT_THROW_SPINY:
            enemy_lakitu_sub_act_throw_spiny();
            break;
    }

    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;
    if (distanceToPlayer <= o->oDrawingDistance) {
        cur_obj_move_standard(78);
    }

    // Die and drop held spiny when attacked by mario
    if (obj_check_attacks(&sEnemyLakituHitbox, o->oAction)) {
        // The spiny uses this as a signal to get thrown
        o->prevObj = NULL;
    }
}

/**
 * Update function for bhvEnemyLakitu.
 */
void bhv_enemy_lakitu_update(void) {
    // PARTIAL_UPDATE
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oEnemyLakituBlinkTimer);
        sync_object_init_field(o, &o->oEnemyLakituSpinyCooldown);
        sync_object_init_field(o, &o->oEnemyLakituFaceForwardCountdown);
    }

    treat_far_home_as_mario(2000.0f, NULL, NULL);

    switch (o->oAction) {
        case ENEMY_LAKITU_ACT_UNINITIALIZED:
            enemy_lakitu_act_uninitialized();
            break;
        case ENEMY_LAKITU_ACT_MAIN:
            enemy_lakitu_act_main();
            break;
    }
}
