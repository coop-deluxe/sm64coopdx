static Vec3s sDonutPlatformPositions[] = {
    { 0x0B4C, 0xF7D7, 0x19A4 }, { 0xF794, 0x08A3, 0xFFA9 }, { 0x069C, 0x09D8, 0xFFE0 },
    { 0x05CF, 0x09D8, 0xFFE0 }, { 0x0502, 0x09D8, 0xFFE0 }, { 0x054C, 0xF7D7, 0x19A4 },
    { 0x0A7F, 0xF7D7, 0x19A4 }, { 0x09B2, 0xF7D7, 0x19A4 }, { 0x06E6, 0xF7D7, 0x19A4 },
    { 0x0619, 0xF7D7, 0x19A4 }, { 0xEFB5, 0xF7D7, 0x19A4 }, { 0x00E6, 0xF7D7, 0x19A4 },
    { 0x0019, 0xF7D7, 0x19A4 }, { 0xFF4D, 0xF7D7, 0x19A4 }, { 0xF081, 0xF7D7, 0x19A4 },
    { 0xE34F, 0xF671, 0x197A }, { 0xEEE8, 0xF7D7, 0x19A4 }, { 0xE74F, 0xF7D7, 0x197A },
    { 0xE683, 0xF7D7, 0x197A }, { 0xE5B6, 0xF7D7, 0x197A }, { 0xEE83, 0xF4A4, 0x19A4 },
    { 0xE41C, 0xF671, 0x197A }, { 0xE4E9, 0xF671, 0x197A }, { 0xECE9, 0xF4A4, 0x19A4 },
    { 0xEDB6, 0xF4A4, 0x19A4 }, { 0xFC3F, 0x0A66, 0xFF45 }, { 0x00EF, 0x04CD, 0xFF53 },
    { 0x0022, 0x04CD, 0xFF53 }, { 0xFF57, 0x04CD, 0xFF53 }, { 0xFB73, 0x0A66, 0xFF45 },
    { 0xFD0C, 0x0A66, 0xFF45 },
};

void bhv_donut_platform_spawner_update(void) {
    if (o->oDonutPlatformSpawnerSpawnedPlatforms != 0) { return; }
    o->oDonutPlatformSpawnerSpawnedPlatforms = 1;

    for (s32 i = 0; i < 31; i++) {
        struct Object* platform = spawn_object_relative(i,
            sDonutPlatformPositions[i][0],
            sDonutPlatformPositions[i][1],
            sDonutPlatformPositions[i][2],
            o,
            MODEL_RR_DONUT_PLATFORM,
            bhvDonutPlatform);
        if (platform == NULL) { continue; }
    }
}

void bhv_donut_platform_update(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oGravity);
        sync_object_init_field(o, &o->oIntangibleTimer);
    }

    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    if (o->oAction == 2) {
        cur_obj_set_pos_to_home();
        o->oGravity = 0;
        o->oVelX = 0;
        o->oVelY = 0;
        o->oVelZ = 0;
        if (distanceToPlayer > 1000 && distanceToPlayer < 2000) {
            cur_obj_unhide();
            cur_obj_become_tangible();
            o->oAction = 0;
        } else {
            cur_obj_hide();
            cur_obj_become_intangible();
            return;
        }
    }

    if (o->oTimer != 0 && (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND)) {
        if (distanceToPlayer > 2500.0f) {
            o->oAction = 2;
            o->oMoveFlags = OBJ_MOVE_IN_AIR;
        } else {
            s16 oldActiveFlags = o->activeFlags;
            obj_explode_and_spawn_coins(150.0f, 1);
            o->activeFlags = oldActiveFlags;
            o->oAction = 2;
            o->oMoveFlags = OBJ_MOVE_IN_AIR;
            create_sound_spawner(SOUND_GENERAL_DONUT_PLATFORM_EXPLOSION);
            network_send_object(o);
        }
    } else {
        if (o->oGravity == 0.0f) {
            if (cur_obj_is_any_player_on_platform()) {
                cur_obj_shake_y(4.0f);
                if (o->oTimer > 15) {
                    o->oGravity = -0.1f;
                }
            } else {
                cur_obj_set_pos_to_home();
                o->oTimer = 0;
            }
        } else {
            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(78);
        }

        load_object_collision_model();
    }
}
