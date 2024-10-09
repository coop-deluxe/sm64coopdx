// breakable_wall.c.inc

void bhv_wf_breakable_wall_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &o->oBreakableWallForce);
    }

    if (o->oBreakableWallForce || gMarioStates[0].action == ACT_SHOT_FROM_CANNON) {
        cur_obj_become_tangible();
        if (o->oBreakableWallForce || obj_check_if_collided_with_object(o, gMarioObject)) {
            if (!o->oBreakableWallForce) {
                o->oBreakableWallForce = TRUE;
                network_send_object(o);
                struct SyncObject* so = sync_object_get(o->oSyncID);
                if (so) { so->syncDeathEvent = FALSE; }
            }
            if (cur_obj_has_behavior(bhvWfBreakableWallRight))
                play_puzzle_jingle();
            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
            o->oInteractType = 8;
            o->oDamageOrCoinValue = 1;
            obj_explode_and_spawn_coins(80.0f, 0);
        }
    } else
        cur_obj_become_intangible();
}
