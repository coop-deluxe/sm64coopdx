// warp.c.inc

void bhv_warp_loop(void) {
    u16 radius;
    if (o->oTimer == 0) {
        radius = (o->oBehParams >> 24) & 0xFF;
        if (radius == 0) {
            o->hitboxRadius = 50.0f;
        } else if (radius == 0xFF) {
            o->hitboxRadius = 10000.0f;
        } else {
            o->hitboxRadius = radius * 10.0;
        }
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = 0;
}

void bhv_fading_warp_loop(void) { // identical to the above function except for o->hitboxRadius
    u16 radius;
    if (o->oTimer == 0) {
        radius = (o->oBehParams >> 24) & 0xFF;
        if (radius == 0) {
            o->hitboxRadius = 85.0f;
        } else if (radius == 0xFF) {
            o->hitboxRadius = 10000.0f;
        } else {
            o->hitboxRadius = radius * 10.0;
        }
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = 0;
}
