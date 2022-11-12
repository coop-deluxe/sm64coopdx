
static void fire_spitter_act_idle(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    approach_f32_ptr(&o->header.gfx.scale[0], 0.2f, 0.002f);
    if (o->oTimer > 150 && distanceToPlayer < 800.0f && !(o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER)) {
        o->oAction = FIRE_SPITTER_ACT_SPIT_FIRE;
        o->oFireSpitterScaleVel = 0.05f;
    }
}

static void fire_spitter_act_spit_fire(void) {
    s32 scaleStatus;

    struct Object* player = nearest_player_to_object(o);
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;
    if (player) {
        o->oMoveAngleYaw = angleToPlayer;
    }

    // Increase scale by 0.05, 0.04, ..., -0.03. Then wait ~8 frames, then
    // starting moving scale by 0.05 each frame toward 0.1. The first time
    // it becomes below 0.15 during this latter portion, shoot fire.
    scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
    if (scaleStatus != 0) {
        if (scaleStatus < 0) {
            o->oAction = FIRE_SPITTER_ACT_IDLE;
        } else {
            if (sync_object_is_owned_locally(o->oSyncID)) {
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);

                struct Object* fire = obj_spit_fire(0, 0, 0, 5.0f, MODEL_RED_FLAME_SHADOW, 20.0f, 15.0f, 0x1000);
                struct Object* spawn_objects[] = { fire };
                u32 models[] = { MODEL_RED_FLAME_SHADOW };
                network_send_spawn_objects(spawn_objects, models, 1);

                network_send_object(o);
            }
        }
    }
}

static void bhv_fire_spitter_on_received_post(UNUSED u8 localIndex) {
    cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
}

void bhv_fire_spitter_update(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->on_received_post = bhv_fire_spitter_on_received_post;
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oFireSpitterScaleVel);
            sync_object_init_field(o, &o->header.gfx.scale[0]);
            sync_object_init_field(o, &o->header.gfx.scale[1]);
            sync_object_init_field(o, &o->header.gfx.scale[2]);
        }
    }

    cur_obj_scale(o->header.gfx.scale[0]);
    o->oGraphYOffset = 40.0f;
    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case FIRE_SPITTER_ACT_IDLE:
            fire_spitter_act_idle();
            break;
        case FIRE_SPITTER_ACT_SPIT_FIRE:
            fire_spitter_act_spit_fire();
            break;
    }

    // HACK: when water level suddenly changes, the fire spitter can disappear into the floor
    f32 waterLevel = find_water_level(o->oPosX, o->oPosZ);
    if (fabs(o->oFireSpitterLastWaterY - waterLevel) > 100) {
        o->oMoveFlags = OBJ_MOVE_IN_AIR;
    }
    o->oFireSpitterLastWaterY = waterLevel;
    cur_obj_move_standard(78);
}
