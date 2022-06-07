/**
 * Behaviors for bhvPyramidElevator and bhvPyramidElevatorTrajectoryMarkerBall.
 *
 * This controls the elevator that descends Shifting Sand Land's pyramid, as
 * well as the small marker balls that demarcate its trajactory.
 */

/**
 * Generate the ten trajectory marker balls that indicate where the elevator
 * moves.
 */
void bhv_pyramid_elevator_init(void) {
    for (s32 i = 0; i < 10; i++) {
        struct Object *ball = spawn_object(o, MODEL_TRAJECTORY_MARKER_BALL, bhvPyramidElevatorTrajectoryMarkerBall);
        if (ball == NULL) { continue; }
        ball->oPosY = 4600 - i * 460;
    }
    
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oPosY);
            sync_object_init_field(o, &o->oVelY);
        }
    }
}

void bhv_pyramid_elevator_loop(void) {
    switch (o->oAction) {
        /**
         * Do not move until Mario stands on the elevator. When he does,
         * transition to the starting state.
         */
        case PYRAMID_ELEVATOR_IDLE:
            if (cur_obj_is_any_player_on_platform()) {
                o->oAction = PYRAMID_ELEVATOR_START_MOVING;
                network_send_object(o);
            }
            break;

        /**
         * Use a sine wave to start the elevator's movement with a small jolt.
         * After a certain amount of time, transition to a constant-velocity state.
         */
        case PYRAMID_ELEVATOR_START_MOVING:
            o->oPosY = o->oHomeY - sins(o->oTimer * 0x1000) * 10.0f;
            if (o->oTimer == 8) {
                o->oAction = PYRAMID_ELEVATOR_CONSTANT_VELOCITY;
                if (cur_obj_is_mario_on_platform()) { network_send_object(o); }
            }
            break;

        /**
         * Move downwards with constant velocity. Once at the bottom of the
         * track, transition to the final state.
         */
        case PYRAMID_ELEVATOR_CONSTANT_VELOCITY:
            o->oVelY = -10.0f;
            o->oPosY += o->oVelY;
            if (o->oPosY < 128.0f) {
                o->oPosY = 128.0f;
                o->oAction = PYRAMID_ELEVATOR_END_MOVING;
                if (cur_obj_is_mario_on_platform()) { network_send_object(o); }
            }
            break;

        /**
         * Use a sine wave to stop the elevator's movement with a small jolt.
         * Then, remain at the bottom of the track.
         */
        case PYRAMID_ELEVATOR_END_MOVING:
            o->oPosY = sins(o->oTimer * 0x1000) * 10.0f + 128.0f;
            if (o->oTimer >= 8) {
                o->oAction = PYRAMID_ELEVATOR_AT_BOTTOM;
                network_send_object(o);
            }
            break;
        
        /**
         * The elevator is now at the bottom and finished it's moving
         * We will no longer move from this point.
         */
        case PYRAMID_ELEVATOR_AT_BOTTOM:
            o->oVelY = 0;
            o->oPosY = 128.0f;
            break;
    }
}

/**
 * Deactivate the trajectory marker balls if the elevator is not moving.
 * Otherwise, set their scale.
 */
void bhv_pyramid_elevator_trajectory_marker_ball_loop(void) {
    cur_obj_scale(0.15f);
    struct Object *elevator = cur_obj_nearest_object_with_behavior(bhvPyramidElevator);

    if (elevator != NULL) {
        if (elevator->oAction != PYRAMID_ELEVATOR_IDLE) {
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
}
