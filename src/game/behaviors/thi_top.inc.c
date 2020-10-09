// thi_top.c.inc

struct SpawnParticlesInfo D_8032F134 = {
    0, 30, MODEL_WHITE_PARTICLE_SMALL, 0, 40, 0, 20, 40, 252, 30, 20.0f, 0.0f
};

UNUSED u8 unused8032F134[] = { 10, 11, 12 };

void bhv_thi_huge_island_top_loop(void) {
    if (gTHIWaterDrained & 1) {
        if (o->oTimer == 0)
            gEnvironmentRegions[18] = 3000;
        cur_obj_hide();
    } else
        load_object_collision_model();
}

void bhv_thi_tiny_island_top_loop(void) {
    if (!network_sync_object_initialized(o)) {
        network_init_object(o, SYNC_DISTANCE_ONLY_EVENTS);
        network_init_object_field(o, &o->oAction);
        network_init_object_field(o, &o->oPrevAction);
        network_init_object_field(o, &o->oTimer);
        network_init_object_field(o, &o->header.gfx.node.flags);
    }

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState->marioObj;
    int distanceToPlayer = dist_between_objects(o, player);

    if (!(gTHIWaterDrained & 1)) {
        if (o->oAction == 0) {
            if (distanceToPlayer < 500.0f)
                if (marioState->action == ACT_GROUND_POUND_LAND) {
                    o->oAction++;
                    cur_obj_spawn_particles(&D_8032F134);
                    spawn_triangle_break_particles(20, 138, 0.3f, 3);
                    cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
                    cur_obj_hide();
                    network_send_object(o);
                }
        } else {
            if (o->oTimer < 50) {
                gEnvironmentRegions[18]--;
                cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
            } else {
                gTHIWaterDrained |= 1;
                play_puzzle_jingle();
                o->oAction += 1;
            }
        }
    } else {
        if (o->oTimer == 0)
            gEnvironmentRegions[18] = 700;
        cur_obj_hide();
    }
}
