// water_wave.c.inc
// This file does absolutly nothing, lol.

void bhv_object_water_wave_init(void) {
    o->oPosY = find_water_level(o->oPosX, o->oPosZ);
}

void bhv_object_water_wave_loop(void) {
    s32 globalTimer = gGlobalTimer;
    if ((globalTimer % 16) == 0)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}
