
void bhv_ddd_pole_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = TRUE;
    *shouldOwn = (gNetworkType == NT_SERVER);
}

void bhv_ddd_pole_init(void) {
    if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))) {
        obj_mark_for_deletion(o);
    } else {
        o->hitboxDownOffset = 100.0f;
        o->oDDDPoleMaxOffset = 100.0f * o->oBehParams2ndByte;

        struct SyncObject* so = network_init_object(o, SYNC_DISTANCE_ONLY_EVENTS);
        so->override_ownership = bhv_ddd_pole_override_ownership;
        network_init_object_field(o, &o->oPosX);
        network_init_object_field(o, &o->oPosY);
        network_init_object_field(o, &o->oPosZ);
        network_init_object_field(o, &o->oDDDPoleVel);
        network_init_object_field(o, &o->oDDDPoleOffset);
        network_init_object_field(o, &o->oAction);
        network_init_object_field(o, &o->oPrevAction);
        network_init_object_field(o, &o->oTimer);
    }
}

void bhv_ddd_pole_update(void) {
    if (o->oTimer > 20) {
        o->oDDDPoleOffset += o->oDDDPoleVel;

        if (clamp_f32(&o->oDDDPoleOffset, 0.0f, o->oDDDPoleMaxOffset)) {
            o->oDDDPoleVel = -o->oDDDPoleVel;
            o->oTimer = 0;
            if (network_owns_object(o)) {
                network_send_object(o);
            }
        }
    }

    obj_set_dist_from_home(o->oDDDPoleOffset);
}
