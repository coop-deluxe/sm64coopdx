// sushi.c.inc

void bhv_sushi_shark_collision_loop(void) {
}

void bhv_sushi_shark_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oSushiSharkUnkF4);
    }

    struct Object* player = nearest_player_to_object(o);

    f32 sp1C = find_water_level(o->oPosX, o->oPosZ);
    o->oPosX = o->oHomeX + sins(o->oSushiSharkUnkF4) * 1700.0f;
    o->oPosZ = o->oHomeZ + coss(o->oSushiSharkUnkF4) * 1700.0f;
    o->oPosY = sp1C + o->oHomeY + sins(o->oSushiSharkUnkF4) * 200.0f;
    o->oMoveAngleYaw = o->oSushiSharkUnkF4 + 0x4000;
    o->oSushiSharkUnkF4 += 0x80;
    if (player && player->oPosY - sp1C > -500.0f)
        if (o->oPosY - sp1C > -200.0f)
            spawn_object_with_scale(o, MODEL_WAVE_TRAIL, bhvObjectWaveTrail, 4.0f);
    if ((o->oTimer & 0xF) == 0)
        cur_obj_play_sound_2(SOUND_OBJ_SUSHI_SHARK_WATER_SOUND);
    o->oInteractStatus = 0;
}
