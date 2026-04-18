// snowman.c.inc

static struct ObjectHitbox sRollingSphereHitbox = {
    .interactType = INTERACT_DAMAGE,
    .downOffset = 0,
    .damageOrCoinValue = 3,
    .health = 0,
    .numLootCoins = 0,
    .radius = 210,
    .height = 350,
    .hurtboxRadius = 0,
    .hurtboxHeight = 0,
};

static void bhv_snowmans_bottom_override_ownership(u8 *shouldOverride, u8 *shouldOwn) {
    if (o->oAction != 0 || o->oSubAction != 0) {
        *shouldOverride = TRUE;
        if (o->globalPlayerIndex >= MAX_PLAYERS) o->globalPlayerIndex = 0;
        struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->globalPlayerIndex)];
        if (!is_player_active(marioState)) {
            // use player with the smallest global index instead
            marioState = &gMarioStates[get_network_player_smallest_global()->localIndex];
        }
        *shouldOwn = marioState->playerIndex == 0;
    }
}

void bhv_snowmans_bottom_init(void) {
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;

    o->oGravity = 10.0f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 2.0f;

    o->oVelY = 0;
    o->oForwardVel = 0;
    o->oSnowmansBottomUnkF4 = 0.4f;

    struct Object *snowmansHeadObj = cur_obj_nearest_object_with_behavior(bhvSnowmansHead);
    if (snowmansHeadObj != NULL) {
        o->parentObj = snowmansHeadObj;
    }
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvSnowmansBodyCheckpoint, -402, 461, -2898, 0, 0, 0);

    // uses event based syncing. The person who talks to the bottom snowman is the one who owns it and steers it
    // everyone else is ignore until the snowman enters the head, which in that case any mario can talk to the snowman
    // and collect the star
    struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    if (so) {
        so->override_ownership = bhv_snowmans_bottom_override_ownership;
        sync_object_init_field(o, o->oAction);
        sync_object_init_field(o, o->oSubAction);
        sync_object_init_field(o, o->oForwardVel);
        sync_object_init_field(o, o->globalPlayerIndex);
    }
}

void set_rolling_sphere_hitbox(void) {
    obj_set_hitbox(o, &sRollingSphereHitbox);

    if ((o->oInteractStatus & INT_STATUS_INTERACTED) != 0) {
        o->oInteractStatus = 0;
    }
}

void adjust_rolling_face_pitch(f32 f12) {
    o->oFaceAnglePitch += (s16)(o->oForwardVel * (100.0f / f12));
    o->oSnowmansBottomUnkF4 += o->oForwardVel * 1e-4;

    if (o->oSnowmansBottomUnkF4 > 1.0) {
        o->oSnowmansBottomUnkF4 = 1.0f;
    }
}

void snowmans_bottom_act_1(void) {
    if (o->globalPlayerIndex >= MAX_PLAYERS) o->globalPlayerIndex = 0;
    struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->globalPlayerIndex)];
    if (!is_player_active(marioState)) {
        // use player with the smallest global index instead
        marioState = &gMarioStates[get_network_player_smallest_global()->localIndex];
    }
    struct Object *player = marioState->visibleToEnemies ? marioState->marioObj : NULL;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    o->oPathedStartWaypoint = segmented_to_virtual(gBehaviorValues.trajectories.SnowmanHeadTrajectory);
    object_step_without_floor_orient();
    s32 followStatus = cur_obj_follow_path(0);
    o->oSnowmansBottomUnkF8 = o->oPathedTargetYaw;
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oSnowmansBottomUnkF8, 0x400);

    if (o->oForwardVel > 70.0) {
        o->oForwardVel = 70.0f;
    }

    if (followStatus == -1) {
        if (obj_check_if_facing_toward_angle(o->oMoveAngleYaw, angleToPlayer, 0x2000) == TRUE && o->oSnowmansBottomUnk1AC == 1) {
            o->oSnowmansBottomUnkF8 = angleToPlayer;
        } else {
            o->oSnowmansBottomUnkF8 = o->oMoveAngleYaw;
        }
        o->oAction = 2;
    }
}

void snowmans_bottom_act_2(void) {
    object_step_without_floor_orient();
    if (o->oForwardVel > 70.0) {
        o->oForwardVel = 70.0f;
    }

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oSnowmansBottomUnkF8, 0x400);
    if (is_point_close_to_object(o, -4230.0f, -1344.0f, 1813.0f, 300)) {
        spawn_mist_particles_variable(0, 0, 70.0f);
        o->oMoveAngleYaw = atan2s(1813.0f - o->oPosZ, -4230.0f - o->oPosX);
        o->oVelY = 80.0f;
        o->oForwardVel = 15.0f;
        o->oAction = 3;

        o->parentObj->oAction = 2;
        o->parentObj->oVelY = 100.0f;
        o->parentObj->globalPlayerIndex = o->globalPlayerIndex;
        network_send_object(o);
        cur_obj_play_sound_2(SOUND_OBJ_SNOWMAN_BOUNCE);
    }

    if (o->oTimer == 200) {
        create_respawner(MODEL_CCM_SNOWMAN_BASE, bhvSnowmansBottom, 3000);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void snowmans_bottom_act_3(void) {
    s16 collisionFlags = object_step_without_floor_orient();
    if ((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED) {
        o->oAction = 4;
        cur_obj_become_intangible();
    }

    if ((collisionFlags & OBJ_COL_FLAG_GROUNDED) != 0) {
        spawn_mist_particles_variable(0, 0, 70.0f);
        o->oPosX = -4230.0f;
        o->oPosZ = 1813.0f;
        o->oForwardVel = 0.0f;
    }
}

static u8 bhv_snowmans_bottom_loop_continue_dialog(void) {
    return (o->oAction == 0);
}

static void bhv_snowmans_bottom_handle_dialog() {
    if (o->oSubAction == 0) {
        struct MarioState *marioState = nearest_mario_state_to_object(o);
        if (marioState && should_start_or_continue_dialog(marioState, o) && dist_between_objects(o, marioState->marioObj) <= 400) {
            o->oSubAction++;
            o->globalPlayerIndex = network_global_index_from_local(marioState->playerIndex);
            network_send_object(o);
        }
    } else {
        if (o->globalPlayerIndex >= MAX_PLAYERS) o->globalPlayerIndex = 0;
        struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->globalPlayerIndex)];
        if (!is_player_active(marioState)) {
            // use player with the smallest global index instead
            marioState = &gMarioStates[get_network_player_smallest_global()->localIndex];
        }
        if (marioState->playerIndex == 0 && should_start_or_continue_dialog(marioState, o) && (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 400) == 1) && set_mario_npc_dialog(marioState, 1, bhv_snowmans_bottom_loop_continue_dialog) && cutscene_object_with_dialog(CUTSCENE_DIALOG, o, gBehaviorValues.dialogs.SnowmanHeadBodyDialog)) {
            o->oForwardVel = 10.0f;
            o->oAction = 1;
            set_mario_npc_dialog(marioState, 0, NULL);
            network_send_object(o);
        }
    }
}

void bhv_snowmans_bottom_loop(void) {
    switch (o->oAction) {
        case 0:
            bhv_snowmans_bottom_handle_dialog();
            break;

        case 1:
            snowmans_bottom_act_1();
            adjust_rolling_face_pitch(o->oSnowmansBottomUnkF4);
            cur_obj_play_sound_1(SOUND_ENV_UNKNOWN2);
            break;

        case 2:
            snowmans_bottom_act_2();
            adjust_rolling_face_pitch(o->oSnowmansBottomUnkF4);
            cur_obj_play_sound_1(SOUND_ENV_UNKNOWN2);
            break;

        case 3:
            snowmans_bottom_act_3();
            break;

        case 4:
            cur_obj_push_mario_away_from_cylinder(210.0f, 550);
            break;
    }

    set_rolling_sphere_hitbox();
    set_object_visibility(o, 8000);
    cur_obj_scale(o->oSnowmansBottomUnkF4);
    o->oGraphYOffset = o->oSnowmansBottomUnkF4 * 180.0f;
}

void bhv_snowmans_head_init(void) {
    u8 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1);
    s8 behParams = (o->oBehParams >> 24) & 0xFF;

    cur_obj_scale(0.7f);

    o->oGravity = 5.0f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 2.0f;

    if ((starFlags & (1 << behParams)) && gCurrActNum != behParams + 1) {
        spawn_object_abs_with_rot(o, 0, MODEL_CCM_SNOWMAN_BASE, bhvBigSnowmanWhole, -4230, -1344, 1813, 0, 0, 0);
        o->oPosX = -4230.0f;
        o->oPosY = -994.0f;
        o->oPosZ = 1813.0f;
        o->oAction = 1;
    }

    sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    sync_object_init_field(o, o->oAction);
    sync_object_init_field(o, o->globalPlayerIndex);
}

static u8 bhv_snowmans_head_action_0_continue_dialog(void) {
    return (o->oAction == 0);
}

static u8 bhv_snowmans_head_action_4_continue_dialog(void) {
    return (o->oAction == 4);
}

void bhv_snowmans_head_loop(void) {
    s16 collisionFlags;
    switch (o->oAction) {
        case 0:
            if (trigger_obj_dialog_when_facing(&gMarioStates[0], &o->oSnowmansHeadUnkF4, gBehaviorValues.dialogs.SnowmanHeadDialog, 400.0f, 1, bhv_snowmans_head_action_0_continue_dialog)) {
                o->oAction = 1;
            }
            break;

        case 1:
            break;

        case 2:
            collisionFlags = object_step_without_floor_orient();
            if (collisionFlags & OBJ_COL_FLAG_NO_Y_VEL) {
                o->oAction = 3;
            }
            break;

        case 3:
            object_step_without_floor_orient();
            if (o->oPosY < -994.0f) {
                o->oPosY = -994.0f;
                o->oAction = 4;
                cur_obj_play_sound_2(SOUND_OBJ_SNOWMAN_EXPLODE);
                play_puzzle_jingle();
            }
            break;

        case 4:
            if (trigger_obj_dialog_when_facing(&gMarioStates[0], &o->oSnowmansHeadUnkF4, gBehaviorValues.dialogs.SnowmanHeadAfterDialog, 700.0f, 2, bhv_snowmans_head_action_4_continue_dialog)) {
                spawn_mist_particles();
                f32 *starPos = gLevelValues.starPositions.SnowmanHeadStarPos;
                spawn_default_star(starPos[0], starPos[1], starPos[2]);
                o->oAction = 1;
                network_send_object(o);
            }
            break;
    }

    cur_obj_push_mario_away_from_cylinder(180.0f, 150.0f);
}

void bhv_snowmans_body_checkpoint_loop(void) {
    if (!o->parentObj) {
        return;
    }

    if (o->parentObj->globalPlayerIndex >= MAX_PLAYERS) o->parentObj->globalPlayerIndex = 0;
    struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->parentObj->globalPlayerIndex)];
    if (!is_player_active(marioState)) {
        // use player with the smallest global index instead
        marioState = &gMarioStates[get_network_player_smallest_global()->localIndex];
    }
    struct Object *player = marioState->visibleToEnemies ? marioState->marioObj : NULL;

    if (dist_between_objects(player, o) <= 800) {
        o->parentObj->oSnowmansBottomUnk1AC++;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}
