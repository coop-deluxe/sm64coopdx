/**
 * Behavior for MIPS (everyone's favorite yellow rabbit).
 */

static Trajectory** sMipsPaths[] = {
    &gBehaviorValues.trajectories.MipsTrajectory,
    &gBehaviorValues.trajectories.Mips2Trajectory,
    &gBehaviorValues.trajectories.Mips3Trajectory,
    &gBehaviorValues.trajectories.Mips4Trajectory,
    &gBehaviorValues.trajectories.Mips5Trajectory,
    &gBehaviorValues.trajectories.Mips6Trajectory,
    &gBehaviorValues.trajectories.Mips7Trajectory,
    &gBehaviorValues.trajectories.Mips8Trajectory,
    &gBehaviorValues.trajectories.Mips9Trajectory,
    &gBehaviorValues.trajectories.Mips10Trajectory,
};

static u32 mipsPrevHeldState = 0;

static void bhv_mips_on_received_pre(UNUSED u8 fromLocalIndex) {
    mipsPrevHeldState = o->oHeldState;
}

static void bhv_mips_on_received_post(UNUSED u8 fromLocalIndex) {
    if (mipsPrevHeldState == HELD_HELD && o->oHeldState == HELD_FREE) {
        cur_obj_init_animation(0);
    }
}

/**
 * Initializes MIPS' physics parameters and checks if he should be active,
 * hiding him if necessary.
 */
void bhv_mips_init(void) {
    // Retrieve star flags for Castle Secret Stars on current save file.
    u8 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, -1);

    // If the player has >= 15 stars and hasn't collected first MIPS star...
    if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= gBehaviorValues.MipsStar1Requirement
        && !(starFlags & SAVE_FLAG_TO_STAR_FLAG(SAVE_FLAG_COLLECTED_MIPS_STAR_1))) {
        o->oBehParams2ndByte = 0;
#ifndef VERSION_JP
        o->oMipsForwardVelocity = 40.0f;
#endif
    }
    // If the player has >= 50 stars and hasn't collected second MIPS star...
    else if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= gBehaviorValues.MipsStar2Requirement
             && !(starFlags & SAVE_FLAG_TO_STAR_FLAG(SAVE_FLAG_COLLECTED_MIPS_STAR_2))) {
        o->oBehParams2ndByte = 1;
#ifndef VERSION_JP
        o->oMipsForwardVelocity = 45.0f;
#endif
    } else {
        // No MIPS stars are available, hide MIPS.
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    o->oInteractionSubtype = INT_SUBTYPE_HOLDABLE_NPC;

#ifndef VERSION_JP
    o->oGravity = 15.0f;
#else
    o->oGravity = 2.5f;
#endif
    o->oFriction = 0.89f;
    o->oBuoyancy = 1.2f;

    cur_obj_init_animation(0);

    struct SyncObject* so = sync_object_init(o, 4000.0f);
    if (so) {
        sync_object_init_field(o, &o->oMipsStartWaypointIndex);
        sync_object_init_field(o, &o->oForwardVel);
        sync_object_init_field(o, &o->oMipsStarStatus);
        sync_object_init_field(o, &o->oBehParams2ndByte);
        sync_object_init_field(o, &o->oHeldState);
        sync_object_init_field(o, &o->oFlags);
        so->on_received_pre = bhv_mips_on_received_pre;
        so->on_received_post = bhv_mips_on_received_post;
    }
}

/**
 * Helper function that finds the waypoint that is both within 800 units of MIPS
 * and furthest from Mario's current location.
 */
s16 bhv_mips_find_furthest_waypoint_to_mario(void) {
    s8 i;
    s16 x, y, z;
    s16 furthestWaypointIndex = -1;
    f32 furthestWaypointDistance = -10000.0f;
    f32 distanceToMario;
    struct Waypoint *waypoint;

    struct Object* player = nearest_player_to_object(o);

    // For each waypoint in MIPS path...
    for (i = 0; i < 10; i++) {
        waypoint = segmented_to_virtual(*sMipsPaths[i]);
        x = waypoint->pos[0];
        y = waypoint->pos[1];
        z = waypoint->pos[2];

        // Is the waypoint within 800 units of MIPS?
        if (is_point_close_to_object(o, x, y, z, 800)) {
            // Is this further from Mario than the last waypoint?
            distanceToMario = player ? (sqr(x - player->header.gfx.pos[0]) + sqr(z - player->header.gfx.pos[2])) : 10000;
            if (furthestWaypointDistance < distanceToMario) {
                furthestWaypointIndex = i;
                furthestWaypointDistance = distanceToMario;
            }
        }
    }

    // Set MIPS' next waypoint to be the closest waypoint to Mario.
    o->oMipsStartWaypointIndex = furthestWaypointIndex;
    return (s16) o->oMipsStartWaypointIndex;
}

/**
 * Wait until Mario comes close, then resume following our path.
 */
void bhv_mips_act_wait_for_nearby_mario(void) {
    UNUSED s16 collisionFlags = 0;

    o->oForwardVel = 0.0f;
    collisionFlags = object_step();

    // If Mario is within 500 units...
    if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 500)) {
        // If we fail to find a suitable waypoint...
        if (bhv_mips_find_furthest_waypoint_to_mario() == -1) {
            // Call it quits.
            o->oAction = MIPS_ACT_WAIT_FOR_ANIMATION_DONE;
        } else {
            // Resume path following.
            cur_obj_init_animation(1);
            o->oAction = MIPS_ACT_FOLLOW_PATH;
        }
    }
}

/**
 * Continue to follow our path around the basement area.
 */
void bhv_mips_act_follow_path(void) {
    s16 collisionFlags = 0;
    s32 followStatus = 0;
    struct Waypoint **pathBase;
    struct Waypoint *waypoint;

    // Retrieve current waypoint.
    pathBase = segmented_to_virtual(sMipsPaths[0]);
    s32 length = get_trajectory_length((Trajectory*)pathBase);
    if (o->oMipsStartWaypointIndex >= length || o->oMipsStartWaypointIndex < 0) { return; }
    waypoint = segmented_to_virtual(pathBase[o->oMipsStartWaypointIndex]);

    // Set start waypoint and follow the path from there.
    o->oPathedStartWaypoint = waypoint;
    followStatus = cur_obj_follow_path(followStatus);

    // Update velocity and angle and do movement.
#ifndef VERSION_JP
    o->oForwardVel = o->oMipsForwardVelocity;
#else
    o->oForwardVel = 45.0f;
#endif
    o->oMoveAngleYaw = o->oPathedTargetYaw;
    collisionFlags = object_step();

    // If we are at the end of the path, do idle animation and wait for Mario.
    if (followStatus == PATH_REACHED_END) {
        cur_obj_init_animation(0);
        o->oAction = MIPS_ACT_WAIT_FOR_NEARBY_MARIO;
    }

    // Play sounds during walk animation.
    if (cur_obj_check_if_near_animation_end() == 1 && (collisionFlags & OBJ_COL_FLAG_UNDERWATER)) {
        cur_obj_play_sound_2(SOUND_OBJ_MIPS_RABBIT_WATER);
        spawn_object(o, MODEL_NONE, bhvShallowWaterSplash);
    } else if (cur_obj_check_if_near_animation_end() == 1) {
        cur_obj_play_sound_2(SOUND_OBJ_MIPS_RABBIT);
    }
}

/**
 * Seems to wait until the current animation is done, then go idle.
 */
void bhv_mips_act_wait_for_animation_done(void) {
    if (cur_obj_check_if_near_animation_end() == 1) {
        cur_obj_init_animation(0);
        o->oAction = MIPS_ACT_IDLE;
    }
}

/**
 * Handles MIPS falling down after being thrown.
 */
void bhv_mips_act_fall_down(void) {

    s16 collisionFlags = 0;

    collisionFlags = object_step();
    o->header.gfx.animInfo.animFrame = 0;

    if ((collisionFlags & OBJ_COL_FLAG_GROUNDED) == 1) {
        o->oAction = MIPS_ACT_WAIT_FOR_ANIMATION_DONE;

        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        o->oMoveAngleYaw = o->oFaceAngleYaw;

        if (collisionFlags & OBJ_COL_FLAG_UNDERWATER)
            spawn_object(o, MODEL_NONE, bhvShallowWaterSplash);
    }
}

/**
 * Idle loop, after you catch MIPS and put him down.
 */
void bhv_mips_act_idle(void) {
    UNUSED s16 collisionFlags = 0;

    o->oForwardVel = 0;
    collisionFlags = object_step();

    // Spawn a star if he was just picked up for the first time.
    if (o->oMipsStarStatus == MIPS_STAR_STATUS_SHOULD_SPAWN_STAR) {
        bhv_spawn_star_no_level_exit(o, o->oBehParams2ndByte + 3, TRUE);
        o->oMipsStarStatus = MIPS_STAR_STATUS_ALREADY_SPAWNED_STAR;
    }
}

/**
 * Handles all the actions MIPS does when he is not held.
 */
void bhv_mips_free(void) {
    switch (o->oAction) {
        case MIPS_ACT_WAIT_FOR_NEARBY_MARIO:
            bhv_mips_act_wait_for_nearby_mario();
            break;

        case MIPS_ACT_FOLLOW_PATH:
            bhv_mips_act_follow_path();
            break;

        case MIPS_ACT_WAIT_FOR_ANIMATION_DONE:
            bhv_mips_act_wait_for_animation_done();
            break;

        case MIPS_ACT_FALL_DOWN:
            bhv_mips_act_fall_down();
            break;

        case MIPS_ACT_IDLE:
            bhv_mips_act_idle();
            break;
    }
}

static u8 bhv_mips_held_continue_dialog(void) {
    return (o->heldByPlayerIndex == 0 && o->oHeldState == HELD_HELD && o->oMipsStarStatus == MIPS_STAR_STATUS_HAVENT_SPAWNED_STAR);
}

/**
 * Handles MIPS being held by Mario.
 */
void bhv_mips_held(void) {
    s16 dialogID;

    if (o->heldByPlayerIndex >= MAX_PLAYERS) { return; }
    struct Object* player = gMarioStates[o->heldByPlayerIndex].marioObj;

    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    cur_obj_init_animation(4); // Held animation.
    cur_obj_set_pos_relative(player, 0, 60.0f, 100.0f);
    cur_obj_become_intangible();

    // If MIPS hasn't spawned his star yet...
    if (o->oMipsStarStatus == MIPS_STAR_STATUS_HAVENT_SPAWNED_STAR) {
        // Choose dialog based on which MIPS encounter this is.
        if (o->oBehParams2ndByte == 0)
            dialogID = gBehaviorValues.dialogs.Mips1Dialog;
        else
            dialogID = gBehaviorValues.dialogs.Mips2Dialog;

        if (should_start_or_continue_dialog(&gMarioStates[o->heldByPlayerIndex], o) && set_mario_npc_dialog(&gMarioStates[0], 1, bhv_mips_held_continue_dialog) == 2) {
            //o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogID)) {
                o->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oMipsStarStatus = MIPS_STAR_STATUS_SHOULD_SPAWN_STAR;
                set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
            }
        }
    }
}

/**
 * Handles MIPS being dropped by Mario.
 */
void bhv_mips_dropped(void) {
    cur_obj_get_dropped();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    cur_obj_init_animation(0);
    o->oHeldState = HELD_FREE;
    cur_obj_become_tangible();
    o->oForwardVel = 3.0f;
    o->oAction = MIPS_ACT_IDLE;
    if (sync_object_is_owned_locally(o->oSyncID)) {
        network_send_object(o);
    }
}

/**
 * Handles MIPS being thrown by Mario.
 */
void bhv_mips_thrown(void) {
    cur_obj_enable_rendering_2();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState = HELD_FREE;
    o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
    cur_obj_init_animation(2);
    cur_obj_become_tangible();
    o->oForwardVel = 25.0f;
    o->oVelY = 20.0f;
    o->oAction = MIPS_ACT_FALL_DOWN;
    if (sync_object_is_owned_locally(o->oSyncID)) {
        network_send_object(o);
    }
}

/**
 * MIPS' main loop.
 */
void bhv_mips_loop(void) {
    // Determine what to do based on MIPS' held status.
    switch (o->oHeldState) {
        case HELD_FREE:
            bhv_mips_free();
            break;

        case HELD_HELD:
            bhv_mips_held();
            break;

        case HELD_THROWN:
            bhv_mips_thrown();
            break;

        case HELD_DROPPED:
            bhv_mips_dropped();
            break;
    }
}
