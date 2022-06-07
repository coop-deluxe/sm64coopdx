/**
 * Behavior for bhvSslMovingPyramidWall.
 *
 * This controls the moving walls found within Shifting Sand Land's pyramid.
 * Each wall starts at an initial position and moves up or down at a constant
 * speed.
 */

/**
 * Initialize the moving wall to be at one of three possible initial starting
 * positions.
 */
void bhv_ssl_moving_pyramid_wall_init(void) {
    switch (o->oBehParams2ndByte) {
        case PYRAMID_WALL_BP_POSITION_HIGH:
            break;

        case PYRAMID_WALL_BP_POSITION_MIDDLE:
            o->oPosY -= 256.0f;
            o->oTimer += 50;
            break;

        case PYRAMID_WALL_BP_POSITION_LOW:
            o->oPosY -= 512.0f;
            o->oAction = PYRAMID_WALL_ACT_MOVING_UP;
            break;
    }
    
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oVelY);
            sync_object_init_field(o, &o->oPosY);
        }
    }
}

/**
 * Move up or down at a constant velocity for a period of time, then switch to
 * do the other.
 */
void bhv_ssl_moving_pyramid_wall_loop(void) {
    switch (o->oAction) {
        case PYRAMID_WALL_ACT_MOVING_DOWN:
            o->oVelY = -5.12f;
            if (o->oTimer == 100) {
                o->oAction = PYRAMID_WALL_ACT_MOVING_UP;
                if (sync_object_is_owned_locally(o->oSyncID)) {
                    network_send_object(o);
                }
            }
            break;

        case PYRAMID_WALL_ACT_MOVING_UP:
            o->oVelY = 5.12f;
            if (o->oTimer == 100)
                o->oAction = PYRAMID_WALL_ACT_MOVING_DOWN;
            break;
    }

    o->oPosY += o->oVelY;
}
