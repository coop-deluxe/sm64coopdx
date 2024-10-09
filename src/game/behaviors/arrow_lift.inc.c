/**
 * Behavior for WDW arrow lifts.
 * When a player stands on an arrow lift, it starts moving between
 * two positions 384 units apart.
 * Arrow lifts move either along the X axis or the Z axis.
 * Their facing angle is always perpendicular to the axis they move on.
 * The angle the arrow lifts move initially is 90º clockwise of the face angle.
 * This means an arrow lift at (0, 0, 0) with face angle 0 (positive Z) will
 * move between (0, 0, 0) and (-384, 0, 0).
 */

/**
 * Move the arrow lift away from its original position.
 */
static s32 arrow_lift_move_away(void) {
    s8 status = ARROW_LIFT_NOT_DONE_MOVING;

    o->oMoveAngleYaw = o->oFaceAngleYaw - 0x4000;
    o->oVelY = 0;
    o->oForwardVel = 12;
    // Cumulative displacement is used to keep track of how far the platform
    // has travelled, so that it can stop.
    o->oArrowLiftDisplacement += o->oForwardVel;

    // Stop the platform after moving 384 units.
    if (o->oArrowLiftDisplacement > 384) {
        o->oForwardVel = 0;
        o->oArrowLiftDisplacement = 384;
        status = ARROW_LIFT_DONE_MOVING;
    }

    obj_move_xyz_using_fvel_and_yaw(o);
    return status;
}

/**
 * Move the arrow lift back to its original position.
 */
static s8 arrow_lift_move_back(void) {
    s8 status = ARROW_LIFT_NOT_DONE_MOVING;

    o->oMoveAngleYaw = o->oFaceAngleYaw + 0x4000;
    o->oVelY = 0;
    o->oForwardVel = 12;
    o->oArrowLiftDisplacement -= o->oForwardVel;

    // Stop the platform after returning back to its original position.
    if (o->oArrowLiftDisplacement < 0) {
        o->oForwardVel = 0;
        o->oArrowLiftDisplacement = 0;
        status = ARROW_LIFT_DONE_MOVING;
    }

    obj_move_xyz_using_fvel_and_yaw(o);
    return status;
}

/**
 * Arrow lift update function.
 */
void bhv_arrow_lift_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oAction);
        }
    }

    switch (o->oAction) {
        case ARROW_LIFT_ACT_IDLE:
            // Wait 61 frames before moving.
            if (o->oTimer > 60) {
                if (cur_obj_is_any_player_on_platform()) {
                    o->oAction = ARROW_LIFT_ACT_MOVING_AWAY;
                    network_send_object(o);
                }
            }

            break;

        case ARROW_LIFT_ACT_MOVING_AWAY:
            if (arrow_lift_move_away() == ARROW_LIFT_DONE_MOVING) {
                o->oAction = ARROW_LIFT_ACT_MOVING_BACK;
            }

            break;

        case ARROW_LIFT_ACT_MOVING_BACK:
            // Wait 61 frames before moving (after stopping after moving forwards).
            if (o->oTimer > 60) {
                if (arrow_lift_move_back() == ARROW_LIFT_DONE_MOVING) {
                    o->oAction = ARROW_LIFT_ACT_IDLE;
                }
            }

            break;
    }
}
