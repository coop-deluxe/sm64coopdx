// thi_top.c.inc

struct SpawnParticlesInfo D_8032F134 = {
    0, 30, MODEL_WHITE_PARTICLE_SMALL, 0, 40, 0, 20, 40, 252, 30, 20.0f, 0.0f
};

UNUSED u8 unused8032F134[] = { 10, 11, 12 };

void bhv_thi_huge_island_top_loop(void) {
    if (gTHIWaterDrained & 1) {
        if (o->oTimer == 0 && gEnvironmentRegionsLength > 18) {
            gEnvironmentRegions[18] = 3000;
        }
        cur_obj_hide();
    } else
        load_object_collision_model();
}

void bhv_thi_tiny_island_top_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &o->oAction);
        sync_object_init_field(o, &o->oPrevAction);
        sync_object_init_field(o, &o->oTimer);
        sync_object_init_field_with_size(o, &o->header.gfx.node.flags, 16);
    }

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    if (!(gTHIWaterDrained & 1)) {
        if (o->oAction == 0) {
            if (distanceToPlayer < 500.0f && mario_is_ground_pound_landing(marioState)) {
                o->oAction++;
                cur_obj_spawn_particles(&D_8032F134);
                spawn_triangle_break_particles(20, 138, 0.3f, 3);
                cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
                cur_obj_hide();
                network_send_object(o);
            }
        } else {
            if (o->oTimer < 50) {
                if (gEnvironmentRegions && gEnvironmentRegionsLength > 18) { gEnvironmentRegions[18]--; }
                cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
            } else {
                gTHIWaterDrained |= 1;
                play_puzzle_jingle();
                o->oAction += 1;
            }
        }
    } else {
        if (o->oTimer == 0) {
            if (gEnvironmentRegions && gEnvironmentRegionsLength > 18) { gEnvironmentRegions[18] = 700; }
        }
        cur_obj_hide();
    }
}
