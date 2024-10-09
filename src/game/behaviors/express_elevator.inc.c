// express_elevator.c.inc

void bhv_wdw_express_elevator_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &o->oAction);
        sync_object_init_field(o, &o->oPrevAction);
        sync_object_init_field(o, &o->oTimer);
        sync_object_init_field(o, &o->oVelY);
        sync_object_init_field(o, &o->oPosY);
    }

    o->oVelY = 0.0f;
    if (o->oAction == 0) {
        if (cur_obj_is_any_player_on_platform()) {
            o->oAction++;
            network_send_object(o);
        }
    } else if (o->oAction == 1) {
        o->oVelY = -20.0f;
        o->oPosY += o->oVelY;
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
        if (o->oTimer > 132)
            o->oAction++;
    } else if (o->oAction == 2) {
        if (o->oTimer > 110)
            o->oAction++;
    } else if (o->oAction == 3) {
        o->oVelY = 10.0f;
        o->oPosY += o->oVelY;
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
        if (o->oPosY >= o->oHomeY) {
            o->oPosY = o->oHomeY;
            o->oAction++;
        }
    } else if (!cur_obj_is_any_player_on_platform())
        o->oAction = 0;
}
