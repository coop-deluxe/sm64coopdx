
/**
 * Behavior for bhvPlatformOnTrack and bhvTrackBall.
 * The platform spawns up to 5 track balls at a time, which then despawn
 * themselves as the platform moves past them.
 */

/**
 * Collision models for the different types of platforms.
 */
static void const *sPlatformOnTrackCollisionModels[] = {
    /* PLATFORM_ON_TRACK_TYPE_CARPET    */ rr_seg7_collision_07029038,
    /* PLATFORM_ON_TRACK_TYPE_SKI_LIFT  */ ccm_seg7_collision_070163F8,
    /* PLATFORM_ON_TRACK_TYPE_CHECKERED */ checkerboard_platform_seg8_collision_0800D710,
    /* PLATFORM_ON_TRACK_TYPE_GRATE     */ bitfs_seg7_collision_070157E0,
};

/**
 * Paths for the different instances of these platforms.
 */
static Trajectory** sPlatformOnTrackPaths[] = {
    &gBehaviorValues.trajectories.PlatformRrTrajectory,
    &gBehaviorValues.trajectories.PlatformRr2Trajectory,
    &gBehaviorValues.trajectories.PlatformCcmTrajectory,
    &gBehaviorValues.trajectories.PlatformBitfsTrajectory,
    &gBehaviorValues.trajectories.PlatformHmcTrajectory,
    &gBehaviorValues.trajectories.PlatformLllTrajectory,
    &gBehaviorValues.trajectories.PlatformLll2Trajectory,
    &gBehaviorValues.trajectories.PlatformRr3Trajectory,
    &gBehaviorValues.trajectories.PlatformRr4Trajectory,
};

/**
 * Despawn all track balls and enter the init action.
 */
static void platform_on_track_reset(void) {
    o->oAction = PLATFORM_ON_TRACK_ACT_INIT;
    // This will cause the track balls to all despawn
    o->oPlatformOnTrackBaseBallIndex += 99;
}

/**
 * If this platform is the kind that disappears, pause for a while, then
 * begin blinking, and finally reset.
 */
static void platform_on_track_mario_not_on_platform(void) {
    if (!((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_DONT_DISAPPEAR)) {
        // Once oTimer reaches 150, blink 40 times
        if (cur_obj_wait_then_blink(150, 40)) {
            platform_on_track_reset();
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
        }
    }
}

static u32 platformTrackPathedPrevWaypoint = 0;

static void bhv_platform_track_on_received_post(UNUSED u8 fromLocalIndex) {
    if (o->oPathedStartWaypoint == NULL) { return; }
    o->oPathedPrevWaypoint = (struct Waypoint*)o->oPathedStartWaypoint + platformTrackPathedPrevWaypoint;
}

static void bhv_platform_track_on_sent_pre(void) {
    if (o->oPathedStartWaypoint == NULL) { platformTrackPathedPrevWaypoint = 0; return; }
    platformTrackPathedPrevWaypoint = ((u8*)o->oPathedPrevWaypoint - (u8*)o->oPathedStartWaypoint) / sizeof(struct Waypoint*);
}

/**
 * Init function for bhvPlatformOnTrack.
 */
void bhv_platform_on_track_init(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, 1000.0f);
        if (so != NULL) {
            so->on_sent_pre = bhv_platform_track_on_sent_pre;
            so->on_received_post = bhv_platform_track_on_received_post;
            so->maxUpdateRate = 5.0f;
            sync_object_init_field(o, &platformTrackPathedPrevWaypoint);
            sync_object_init_field(o, &o->oPlatformOnTrackBaseBallIndex);
            sync_object_init_field(o, &o->oPlatformOnTrackDistMovedSinceLastBall);
            sync_object_init_field(o, &o->oPlatformOnTrackSkiLiftRollVel);
            sync_object_init_field(o, &o->oPlatformOnTrackPrevWaypointFlags);
            sync_object_init_field(o, &o->oPlatformOnTrackPitch);
            sync_object_init_field(o, &o->oPlatformOnTrackYaw);
            sync_object_init_field(o, &o->oPlatformOnTrackOffsetY);
        }
    }

    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        s16 pathIndex = (u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_MASK_PATH;
        o->oPlatformOnTrackType = ((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_MASK_TYPE) >> 4;

        o->oPlatformOnTrackIsNotSkiLift = o->oPlatformOnTrackType - PLATFORM_ON_TRACK_TYPE_SKI_LIFT;

        if (BHV_ARR_CHECK(sPlatformOnTrackCollisionModels, o->oPlatformOnTrackType, void const *)) {
            o->collisionData = segmented_to_virtual(sPlatformOnTrackCollisionModels[o->oPlatformOnTrackType]);
        }

        if (BHV_ARR_CHECK(sPlatformOnTrackPaths, pathIndex, Trajectory**)) {
            o->oPlatformOnTrackStartWaypoint = segmented_to_virtual(*sPlatformOnTrackPaths[pathIndex]);
        }

        o->oPlatformOnTrackIsNotHMC = pathIndex - 4;

        o->oBehParams2ndByte = o->oMoveAngleYaw; // TODO: Weird?

        if (o->oPlatformOnTrackType == PLATFORM_ON_TRACK_TYPE_CHECKERED) {
            o->header.gfx.scale[1] = 2.0f;
        }
    }
}

/**
 * Move to the start waypoint, spawn the first track balls, and enter the
 * wait for mario action.
 */
static void platform_on_track_act_init(void) {
    s32 i;

    o->oPlatformOnTrackPrevWaypoint = o->oPlatformOnTrackStartWaypoint;
    o->oPlatformOnTrackPrevWaypointFlags = 0;
    o->oPlatformOnTrackBaseBallIndex = 0;

    o->oPosX = o->oHomeX = o->oPlatformOnTrackStartWaypoint->pos[0];
    o->oPosY = o->oHomeY = o->oPlatformOnTrackStartWaypoint->pos[1];
    o->oPosZ = o->oHomeZ = o->oPlatformOnTrackStartWaypoint->pos[2];

    o->oFaceAngleYaw = o->oBehParams2ndByte;
    o->oForwardVel = o->oVelX = o->oVelY = o->oVelZ = o->oPlatformOnTrackDistMovedSinceLastBall = 0.0f;

    o->oPlatformOnTrackWasStoodOn = FALSE;

    if (o->oPlatformOnTrackIsNotSkiLift) {
        o->oFaceAngleRoll = 0;
    }

    // Spawn track balls
    for (i = 1; i < 6; i++) {
        platform_on_track_update_pos_or_spawn_ball(i, o->oHomeX, o->oHomeY, o->oHomeZ);
    }

    o->oAction = PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO;
}

/**
 * Wait for mario to stand on the platform for 20 frames, then begin moving.
 */
static void platform_on_track_act_wait_for_mario(void) {
    if (cur_obj_is_any_player_on_platform()) {
        if (o->oTimer > 20) {
            o->oAction = PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK;
            if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
        }
    } else {
        if (o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM) {
            platform_on_track_reset();
            if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
        }

        o->oTimer = 0;
    }
}

/**
 * Move along the track. After reaching the end, either start falling,
 * return to the init action, or continue moving back to the start waypoint.
 */
static void platform_on_track_act_move_along_track(void) {
    s16 initialAngle;

    if (!o->oPlatformOnTrackIsNotSkiLift) {
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR3);
    } else if (!o->oPlatformOnTrackIsNotHMC) {
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
    }

    // Fall after reaching the last waypoint if desired
    if (o->oPlatformOnTrackPrevWaypointFlags == WAYPOINT_FLAGS_END
        && !((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_RETURN_TO_START)) {
        o->oAction = PLATFORM_ON_TRACK_ACT_FALL;
    } else {
        // The ski lift should pause or stop after reaching a special waypoint
        if (o->oPlatformOnTrackPrevWaypointFlags != 0 && !o->oPlatformOnTrackIsNotSkiLift) {
            if (o->oPlatformOnTrackPrevWaypointFlags == WAYPOINT_FLAGS_END
                || o->oPlatformOnTrackPrevWaypointFlags == WAYPOINT_FLAGS_PLATFORM_ON_TRACK_PAUSE) {
                cur_obj_play_sound_2(SOUND_GENERAL_UNKNOWN4_LOWPRIO);

                o->oForwardVel = 0.0f;
                if (o->oPlatformOnTrackPrevWaypointFlags == WAYPOINT_FLAGS_END) {
                    o->oAction = PLATFORM_ON_TRACK_ACT_INIT;
                } else {
                    o->oAction = PLATFORM_ON_TRACK_ACT_PAUSE_BRIEFLY;
                }
            }
        } else {
            // The ski lift accelerates, while the others instantly start
            if (!o->oPlatformOnTrackIsNotSkiLift) {
                obj_forward_vel_approach(10.0, 0.1f);
            } else {
                o->oForwardVel = 10.0f;
            }

            // Spawn a new track ball if necessary
            if (approach_f32_ptr(&o->oPlatformOnTrackDistMovedSinceLastBall, 300.0f, o->oForwardVel)) {
                o->oPlatformOnTrackDistMovedSinceLastBall -= 300.0f;

                o->oHomeX = o->oPosX;
                o->oHomeY = o->oPosY;
                o->oHomeZ = o->oPosZ;
                o->oPlatformOnTrackBaseBallIndex = (u16)(o->oPlatformOnTrackBaseBallIndex + 1);

                platform_on_track_update_pos_or_spawn_ball(5, o->oHomeX, o->oHomeY, o->oHomeZ);
            }
        }

        platform_on_track_update_pos_or_spawn_ball(0, o->oPosX, o->oPosY, o->oPosZ);

        o->oMoveAnglePitch = o->oPlatformOnTrackPitch;
        o->oMoveAngleYaw = o->oPlatformOnTrackYaw;

        //! Both oAngleVelYaw and oAngleVelRoll aren't reset until the platform
        //  starts moving again, resulting in unexpected platform displacement
        //  after reappearing

        // Turn face yaw and compute yaw vel
        if (!((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_DONT_TURN_YAW)) {
            s16 targetFaceYaw = o->oMoveAngleYaw + 0x4000;
            s16 yawSpeed = abs_angle_diff(targetFaceYaw, o->oFaceAngleYaw) / 20;

            initialAngle = o->oFaceAngleYaw;
            clamp_s16(&yawSpeed, 100, 500);
            obj_face_yaw_approach(targetFaceYaw, yawSpeed);
            o->oAngleVelYaw = (s16) o->oFaceAngleYaw - initialAngle;
        }

        // Turn face roll and compute roll vel
        if (((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_DONT_TURN_ROLL)) {
            s16 rollSpeed = abs_angle_diff(o->oMoveAnglePitch, o->oFaceAngleRoll) / 20;

            initialAngle = o->oFaceAngleRoll;
            clamp_s16(&rollSpeed, 100, 500);
            //! If the platform is moving counterclockwise upward or
            //  clockwise downward, this will be backward
            obj_face_roll_approach(o->oMoveAnglePitch, rollSpeed);
            o->oAngleVelRoll = (s16) o->oFaceAngleRoll - initialAngle;
        }
    }

    if (!cur_obj_is_any_player_on_platform()) {
        platform_on_track_mario_not_on_platform();
    } else {
        o->oTimer = 0;
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    }
}

/**
 * Wait 20 frames then continue moving.
 */
static void platform_on_track_act_pause_briefly(void) {
    if (o->oTimer > 20) {
        o->oAction = PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK;
    }
}

/**
 * Fall downward with no terminal velocity, stopping after reaching y = -12k
 * and eventually blinking and disappearing.
 */
static void platform_on_track_act_fall(void) {
    cur_obj_move_using_vel_and_gravity();

    if (!cur_obj_is_any_player_on_platform()) {
        platform_on_track_mario_not_on_platform();
    } else {
        o->oTimer = 0;
        //! Doesn't ensure visibility
    }
}

/**
 * Control the rocking of the ski lift.
 */
static void platform_on_track_rock_ski_lift(void) {
    s32 targetRoll = 0;
    UNUSED s32 initialRoll = o->oFaceAngleRoll;

    o->oFaceAngleRoll += (s32) o->oPlatformOnTrackSkiLiftRollVel;

    struct Object* player = NULL;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (gMarioStates[i].marioObj->platform != o) { continue; }
        player = gMarioStates[i].marioObj;
        break;
    }

    // Tilt away from the moving direction and toward mario
    if (player != NULL) {
        s32 distanceToPlayer = dist_between_objects(o, player);
        s32 angleToPlayer = obj_angle_to_object(o, player);
        targetRoll = o->oForwardVel * sins(o->oMoveAngleYaw) * -50.0f
                     + (s32)(distanceToPlayer * sins(angleToPlayer - o->oFaceAngleYaw) * -4.0f);
    }

    oscillate_toward(
        /* value          */ &o->oFaceAngleRoll,
        /* vel            */ &o->oPlatformOnTrackSkiLiftRollVel,
        /* target         */ targetRoll,
        /* velCloseToZero */ 5.0f,
        /* accel          */ 6.0f,
        /* slowdown       */ 1.5f);
    clamp_f32(&o->oPlatformOnTrackSkiLiftRollVel, -100.0f, 100.0f);
}

/**
 * Update function for bhvPlatformOnTrack.
 */
void bhv_platform_on_track_update(void) {
    if (!o->oPlatformOnTrackStartWaypoint) { return; }

    switch (o->oAction) {
        case PLATFORM_ON_TRACK_ACT_INIT:
            platform_on_track_act_init();
            break;
        case PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO:
            platform_on_track_act_wait_for_mario();
            break;
        case PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK:
            platform_on_track_act_move_along_track();
            break;
        case PLATFORM_ON_TRACK_ACT_PAUSE_BRIEFLY:
            platform_on_track_act_pause_briefly();
            break;
        case PLATFORM_ON_TRACK_ACT_FALL:
            platform_on_track_act_fall();
            break;
    }

    if (!o->oPlatformOnTrackIsNotSkiLift) {
        platform_on_track_rock_ski_lift();
    } else if (o->oPlatformOnTrackType == PLATFORM_ON_TRACK_TYPE_CARPET) {
        if (!o->oPlatformOnTrackWasStoodOn && cur_obj_is_any_player_on_platform()) {
            o->oPlatformOnTrackOffsetY = -8.0f;
            o->oPlatformOnTrackWasStoodOn = TRUE;
        }

        approach_f32_ptr(&o->oPlatformOnTrackOffsetY, 0.0f, 0.5f);
        o->oPosY += o->oPlatformOnTrackOffsetY;
    }
}

/**
 * Update function for bhvTrackBall.
 */
void bhv_track_ball_update(void) {
    // Despawn after the elevator passes this ball
    s16 relativeIndex = o->parentObj ?
        ((s16) o->oBehParams2ndByte - (s16) o->parentObj->oPlatformOnTrackBaseBallIndex - 1)
        : 0;
    if (relativeIndex < 1 || relativeIndex > 5) {
        obj_mark_for_deletion(o);
    }
}
