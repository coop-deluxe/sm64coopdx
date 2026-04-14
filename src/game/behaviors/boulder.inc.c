// boulder.c.inc

void bhv_big_boulder_init(void) {
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;

    o->oGravity = 8.0f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 2.0f;
}

void boulder_act_1(void) {
    s16 step = object_step_without_floor_orient();
    if ((step & 0x09) == 0x01 && o->oVelY > 10.0f) {
        cur_obj_play_sound_2(SOUND_GENERAL_GRINDEL_ROLL);
        spawn_mist_particles();
    }

    if (o->oForwardVel > 70.0) {
        o->oForwardVel = 70.0f;
    }

    if (o->oPosY < -1000.0f) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    if (o->oBehParams2ndByte == 2 && (step & OBJ_COL_FLAG_HIT_WALL)) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        obj_explode_and_spawn_coins(46.0f, 1);
    }
}

void bhv_big_boulder_loop(void) {
    cur_obj_scale(1.5f);
    o->oGraphYOffset = 270.0f;
    switch (o->oAction) {
        case 0:
            o->oForwardVel = 40.0f;
            o->oAction = 1;
            break;

        case 1:
            boulder_act_1();
            adjust_rolling_face_pitch(1.5f);
            cur_obj_play_sound_1(SOUND_ENV_UNKNOWN2);
            break;
    }

    set_rolling_sphere_hitbox();
}

void bhv_big_boulder_generator_loop(void) {
    // this sync object works by only letting the owner of the spawner spawn boulders
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, o->oTimer);
    }

    struct Object *spawnedBoulderObject;
    if (o->oTimer >= 256) {
        o->oTimer = 0;
        if (sync_object_is_owned_locally(o->oSyncID)) {
            network_send_object(o);
        }
    }

    bool anyMarioInProperRoom = false;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct MarioState *marioState = &gMarioStates[i];
        if (!is_player_active(marioState)) continue;
        if (marioState->currentRoom != 4) continue;
        anyMarioInProperRoom = true;
    }

    // only spawn object if mario is in the correct room and within range
    if (!anyMarioInProperRoom || is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1500)) {
        return;
    }

    if (sync_object_is_owned_locally(o->oSyncID)) {
        if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 6000)) {
            if ((o->oTimer & 0x3F) == 0) {
                spawnedBoulderObject = spawn_object(o, MODEL_HMC_ROLLING_ROCK, bhvBigBoulder);
                if (spawnedBoulderObject != NULL) {
                    spawnedBoulderObject->oMoveAngleYaw = random_float() * 4096.0f;

                    struct Object *spawn_objects[] = { spawnedBoulderObject };
                    u32 models[] = { MODEL_HMC_ROLLING_ROCK };
                    network_send_spawn_objects(spawn_objects, models, 1);
                }
            }
        } else {
            if ((o->oTimer & 0x7F) == 0) {
                spawnedBoulderObject = spawn_object(o, MODEL_HMC_ROLLING_ROCK, bhvBigBoulder);
                if (spawnedBoulderObject != NULL) {
                    spawnedBoulderObject->oMoveAngleYaw = random_float() * 4096.0f;

                    struct Object *spawn_objects[] = { spawnedBoulderObject };
                    u32 models[] = { MODEL_HMC_ROLLING_ROCK };
                    network_send_spawn_objects(spawn_objects, models, 1);
                }
            }
        }
    }
}
