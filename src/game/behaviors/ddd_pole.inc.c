
void bhv_ddd_pole_init(void) {
    if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))) {
        obj_mark_for_deletion(o);
    } else {
        o->hitboxDownOffset = 100.0f;
        o->oDDDPoleMaxOffset = 100.0f * o->oBehParams2ndByte;
    }
}

static void bhv_ddd_pole_update_inner(void) {
    if (o->oTimer > 20) {
        o->oDDDPoleOffset += o->oDDDPoleVel;

        if (clamp_f32(&o->oDDDPoleOffset, 0.0f, o->oDDDPoleMaxOffset)) {
            o->oDDDPoleVel = -o->oDDDPoleVel;
            o->oTimer = 0;
        }
    }

    obj_set_dist_from_home(o->oDDDPoleOffset);
}

void bhv_ddd_pole_update(void) {
    u32 loopLength = (((u16)o->oDDDPoleMaxOffset / 10) + 20) * 2;
    cur_obj_area_timer_loop(loopLength, bhv_ddd_pole_update_inner);
}
