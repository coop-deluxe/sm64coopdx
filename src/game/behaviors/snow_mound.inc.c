// snow_mound.c.inc

void bhv_sliding_snow_mound_loop(void) {
    switch (o->oAction) {
        case 0:
            o->oVelX = -40.0f;
            o->oPosX += o->oVelX;
            if (o->oTimer >= 118)
                o->oAction = 1;

            cur_obj_play_sound_1(SOUND_ENV_SINK_QUICKSAND);
            break;

        case 1:
            o->oVelX = -5.0f;
            o->oPosX += o->oVelX;
            o->oVelY = -10.0f;
            o->oPosY += o->oVelY;
            o->oPosZ = o->oHomeZ - 2.0f;
            if (o->oTimer > 50)
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}

void bhv_snow_mound_spawn_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = TRUE;
    *shouldOwn = (get_network_player_smallest_global() == gNetworkPlayerLocal);
}

void bhv_snow_mound_spawn_loop(void) {
    struct Object* player = nearest_player_to_object(o);

    struct Object *sp1C = NULL;

    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->override_ownership = bhv_snow_mound_spawn_override_ownership;
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
        }
    }

    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 6000)
        || (player && (o->oPosY + 1000.0f < player->header.gfx.pos[1])))
        return;

    if (o->oTimer == 64 || o->oTimer == 128 || o->oTimer == 192 || o->oTimer == 224 || o->oTimer == 256) {
        if (sync_object_is_owned_locally(o->oSyncID)) {
            sp1C = spawn_object(o, MODEL_SL_SNOW_TRIANGLE, bhvSlidingSnowMound);
            if (sp1C != NULL) {
                sp1C->oHomeX = o->oPosX;
                sp1C->oHomeY = o->oPosY;
                sp1C->oHomeZ = o->oPosZ;
            }
            network_send_object(o);
        }
    }

    if (sp1C != NULL && o->oTimer == 256) {
        sp1C->header.gfx.scale[0] = 2.0f;
        sp1C->header.gfx.scale[1] = 2.0f;
    }

    if (sp1C != NULL) {
        struct Object* spawn_objects[] = { sp1C };
        u32 models[] = { MODEL_SL_SNOW_TRIANGLE };
        network_send_spawn_objects(spawn_objects, models, 1);
    }

    if (o->oTimer >= 256)
        o->oTimer = 0;
}
