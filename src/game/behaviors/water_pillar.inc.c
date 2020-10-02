// water_pillar.c.inc

void water_level_pillar_undrained(void) {
    struct Object *sp1C;
    switch (o->oAction) {
        case 0:
            if (cur_obj_is_mario_ground_pounding_platform()) {
                o->oAction++;
                spawn_mist_particles();
                network_send_object(o);
            }
            break;
        case 1:
            if (o->oTimer < 4)
                o->oPosY -= 20.0f;
            else
                o->oAction++;
            break;
        case 2:
            sp1C = cur_obj_nearest_object_with_behavior(bhvWaterLevelPillar);
            if (sp1C != NULL) {
                if (sp1C->oAction < 2)
                    o->oAction++;
            }
            break;
        case 3:
            sp1C = cur_obj_nearest_object_with_behavior(bhvWaterLevelPillar);
            if (sp1C != NULL) {
                if (sp1C->oAction > 1) {
                    o->oAction++;

                    save_file_set_flags(SAVE_FLAG_MOAT_DRAINED);
                    play_puzzle_jingle();
                }
            }
            break;
        case 4:
            cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
            if (o->oTimer < 300) {
                gEnvironmentLevels[2] =
                    (s32) approach_f32_symmetric(gEnvironmentLevels[2], -2450.0f, 5.0f);
                gEnvironmentLevels[0] =
                    (s32) approach_f32_symmetric(gEnvironmentLevels[0], -2450.0f, 5.0f);
                reset_rumble_timers_2(&gMarioStates[0], 2);
            } else
                o->oAction++;
            break;
        case 5:
            break;
    }
}

void water_level_pillar_drained(void) {
    if (o->oTimer == 0) {
        o->oPosY -= 80.0f;
        gEnvironmentLevels[2] = -2450;
        gEnvironmentLevels[0] = -2450;
    }
}

static u8 bhv_water_level_pillar_ignore_if_true(void) {
    return (o->oWaterLevelPillarUnkF8) || (o->oAction != 0);
}

void bhv_water_level_pillar_init(void) {
    if (save_file_get_flags() & SAVE_FLAG_MOAT_DRAINED)
        o->oWaterLevelPillarUnkF8 = 1;

    struct SyncObject* so = network_init_object(o, SYNC_DISTANCE_ONLY_EVENTS);
    so->ignore_if_true = bhv_water_level_pillar_ignore_if_true;
    network_init_object_field(o, &o->oAction);
    network_init_object_field(o, &o->oPrevAction);
    network_init_object_field(o, &o->oTimer);
    network_init_object_field(o, &o->oWaterLevelPillarUnkF8);
}

void bhv_water_level_pillar_loop(void) {
    if (o->oWaterLevelPillarUnkF8)
        water_level_pillar_drained();
    else
        water_level_pillar_undrained();
    gEnvironmentRegions[18] = gEnvironmentLevels[2];
    gEnvironmentRegions[6] = gEnvironmentLevels[0];
}
