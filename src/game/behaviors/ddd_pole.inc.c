
void bhv_ddd_pole_init(void) {
    if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))) {
        obj_mark_for_deletion(o);
    } else {
        o->hitboxDownOffset = 100.0f;
        o->oDDDPoleMaxOffset = 100.0f * o->oBehParams2ndByte;
    }
}


void bhv_ddd_pole_update(void) {
    // make sure we're loaded and synchronized
    if (!gNetworkAreaLoaded) {
        o->oTimer = 0;
        o->oDDDPoleTimer = 0;
        return;
    } else {
        // catch up, jumping full loop cycles at a time
        u16 loopTime = (((u16)o->oDDDPoleMaxOffset / 10) + 20) * 2;
        if (o->oDDDPoleTimer == 0 && (gNetworkAreaTimer - o->oDDDPoleTimer) >= loopTime) {
            o->oDDDPoleTimer = ((gNetworkAreaTimer - o->oDDDPoleTimer) / loopTime) * loopTime;
            o->oTimer = 0;
        }
    }

    while (o->oDDDPoleTimer < gNetworkAreaTimer) {
        if (o->oTimer > 20) {
            o->oDDDPoleOffset += o->oDDDPoleVel;

            if (clamp_f32(&o->oDDDPoleOffset, 0.0f, o->oDDDPoleMaxOffset)) {
                o->oDDDPoleVel = -o->oDDDPoleVel;
                o->oTimer = 0;
            }
        }

        obj_set_dist_from_home(o->oDDDPoleOffset);

        o->oDDDPoleTimer++;
        if (o->oDDDPoleTimer < gNetworkAreaTimer) {
            cur_obj_fake_update();
        }
    }
}
