// shock_wave.c.inc

f32 sBowserShockwaveHitPoints[] = { 1.9f, 2.4f, 4.0f, 4.8f };

void bhv_bowser_shock_wave_loop(void) {
    s16 fadeFrames = 70;
    o->oBowserShockWaveUnkF4 = o->oTimer * 10;
    cur_obj_scale(o->oBowserShockWaveUnkF4);
    if (gGlobalTimer % 3) {
        o->oOpacity -= 1;
    }
    if (o->oTimer > fadeFrames) {
        o->oOpacity -= 5;
    }
    if (o->oOpacity <= 0) {
        obj_mark_for_deletion(o);
    }
    if (o->oTimer < fadeFrames && mario_is_in_air_action(&gMarioStates[0]) == 0) {
        f32 distMin1 = o->oBowserShockWaveUnkF4 * sBowserShockwaveHitPoints[0];
        f32 distMax1 = o->oBowserShockWaveUnkF4 * sBowserShockwaveHitPoints[1];
        f32 distMin2 = o->oBowserShockWaveUnkF4 * sBowserShockwaveHitPoints[2];
        f32 distMax2 = o->oBowserShockWaveUnkF4 * sBowserShockwaveHitPoints[3];
        if ((distMin1 < o->oDistanceToMario && o->oDistanceToMario < distMax1)
            || (distMin2 < o->oDistanceToMario && o->oDistanceToMario < distMax2)) {
            gMarioStates[0].marioObj->oInteractStatus |= INT_STATUS_HIT_BY_SHOCKWAVE;
        }
    }
}
