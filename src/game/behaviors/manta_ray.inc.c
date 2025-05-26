/**
 * @file Behavior file for the manta ray in DDD.
 *
 * The manta ray spawns on stars 2-6. It generally follows a fixed path, leaving rings.
 * These rings contain a significant bug that is documented in water_ring.inc.c
 */

static Trajectory sMantaRayTraj[] = { 
    TRAJECTORY_POS(0, /*pos*/ -4500, -1380,   -40), 
    TRAJECTORY_POS(1, /*pos*/ -4120, -2240,   740), 
    TRAJECTORY_POS(2, /*pos*/ -3280, -3080,  1040), 
    TRAJECTORY_POS(3, /*pos*/ -2240, -3320,   720), 
    TRAJECTORY_POS(4, /*pos*/ -1840, -3140,  -280), 
    TRAJECTORY_POS(5, /*pos*/ -2320, -2480, -1100), 
    TRAJECTORY_POS(6, /*pos*/ -3220, -1600, -1360), 
    TRAJECTORY_POS(7, /*pos*/ -4180, -1020, -1040), 
    TRAJECTORY_END(),
};

static struct ObjectHitbox sMantaRayHitbox = {
    .interactType = INTERACT_DAMAGE,
    .downOffset = 0,
    .damageOrCoinValue = 0,
    .health = 3,
    .numLootCoins = 0,
    .radius = 210,
    .height = 60,
    .hurtboxRadius = 200,
    .hurtboxHeight = 50,
};

/**
 * Initializes the manta ray when spawned.
 */
void bhv_manta_ray_init(void) {
    struct Object *ringManager;
    ringManager = spawn_object(o, MODEL_NONE, bhvMantaRayRingManager);
    if (ringManager != NULL) {
        o->parentObj = ringManager;
    }
    obj_set_hitbox(o, &sMantaRayHitbox);
    cur_obj_scale(2.5f);

    sync_object_init(o, 4000.0f);
    sync_object_init_field(o, &o->oMantaTargetPitch);
    sync_object_init_field(o, &o->oMantaTargetYaw);
    sync_object_init_field(o, &o->oWaterRingSpawnerRingsCollected);
    sync_object_init_field(o, &o->oMoveAnglePitch);
    sync_object_init_field(o, &o->oMoveAngleRoll);
    if (ringManager != NULL) {
        sync_object_init_field(o, &ringManager->oWaterRingMgrNextRingIndex);
    }
}

static void manta_ray_move(void) {
    s16 animFrame;
    s32 pathStatus = 0;

    animFrame = o->header.gfx.animInfo.animFrame;
    gCurrentObject->oPathedStartWaypoint = (struct Waypoint *) sMantaRayTraj;
    pathStatus = cur_obj_follow_path(pathStatus);
    o->oMantaTargetYaw   = o->oPathedTargetYaw;
    o->oMantaTargetPitch = o->oPathedTargetPitch;
    o->oForwardVel = 10.0f;

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oMantaTargetYaw, 0x80);
    o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, o->oMantaTargetPitch, 0x80);
    
    // This causes the ray to tilt as it turns.
    if ((s16) o->oMantaTargetYaw != (s16) o->oMoveAngleYaw) {
        o->oMoveAngleRoll -= 91;
        if (o->oMoveAngleRoll < -5461.3332) {
            o->oMoveAngleRoll = -0x4000 / 3;
        }
    } else {
        o->oMoveAngleRoll += 91;
        if (o->oMoveAngleRoll > 5461.3332) {
            o->oMoveAngleRoll = 0x4000 / 3;
        }
    }

    cur_obj_set_pos_via_transform();
    if (animFrame == 0) {
        cur_obj_play_sound_2(SOUND_GENERAL_MOVING_WATER);
    }
}

static void manta_ray_act_spawn_ring(void) {
    struct Object *ringManager = o->parentObj;
    struct Object *ring;

    if (!sync_object_is_owned_locally(o->oSyncID)) { return; }

    if (o->oTimer >= 300) {
        o->oTimer = 0;
    }
    
    if (o->oTimer == 0 || o->oTimer == 50 || o->oTimer == 150 || o->oTimer == 200 || o->oTimer == 250) {
        ring = spawn_object(o, MODEL_WATER_RING, bhvMantaRayWaterRing);
        if (ring != NULL) {
            ring->oFaceAngleYaw = o->oMoveAngleYaw;
            ring->oFaceAnglePitch = o->oMoveAnglePitch + 0x4000;
            ring->oPosX = o->oPosX + 200.0f * sins(o->oMoveAngleYaw + 0x8000);
            ring->oPosY = o->oPosY + 10.0f + 200.0f * sins(o->oMoveAnglePitch);
            ring->oPosZ = o->oPosZ + 200.0f * coss(o->oMoveAngleYaw + 0x8000);
            ring->oWaterRingIndex = ringManager->oWaterRingMgrNextRingIndex;
        }

        ringManager->oWaterRingMgrNextRingIndex++;
        if (ringManager->oWaterRingMgrNextRingIndex > 10000) {
            ringManager->oWaterRingMgrNextRingIndex = 0;
        }
        
        if (ring != NULL) {
            struct Object *spawn_objects[] = { ring };
            u32 models[] = { MODEL_WATER_RING };
            network_send_spawn_objects(spawn_objects, models, 1);
        }

        network_send_object(o);
    }
}

/**
 * Behavior that occurs every frame.
 */
void bhv_manta_ray_loop(void) {
    switch (o->oAction) {
        case MANTA_ACT_SPAWN_RINGS:
            manta_ray_move();
            manta_ray_act_spawn_ring();

            // Spawn a star after collecting 5 rings.
            if (o->oWaterRingSpawnerRingsCollected == 5) {
                spawn_mist_particles();
                f32* starPos = gLevelValues.starPositions.MantaRayStarPos;
                spawn_default_star(starPos[0], starPos[1], starPos[2]);
                o->oAction = MANTA_ACT_NO_RINGS;
            }
            break;

        case MANTA_ACT_NO_RINGS:
            manta_ray_move();
            break;
    }

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        o->oInteractStatus = 0;
    }
}
