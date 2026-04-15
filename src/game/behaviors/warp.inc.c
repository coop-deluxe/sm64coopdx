// warp.c.inc

void bhv_warp_loop(void) {
    u16 hitboxScale;
    if (o->oTimer == 0) {
        hitboxScale = (o->oBehParams >> 24) & 0xFF;
        if (hitboxScale == 0)
            o->hitboxRadius = 50.0f;
        else if (hitboxScale == 0xFF)
            o->hitboxRadius = 10000.0f;
        else
            o->hitboxRadius = hitboxScale * 10.0;
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = 0;
}

void bhv_fading_warp_loop(void) { // identical to the above function except for o->hitboxRadius
    u16 hitboxScale;
    if (o->oTimer == 0) {
        hitboxScale = (o->oBehParams >> 24) & 0xFF;
        if (hitboxScale == 0)
            o->hitboxRadius = 85.0f;
        else if (hitboxScale == 0xFF)
            o->hitboxRadius = 10000.0f;
        else
            o->hitboxRadius = hitboxScale * 10.0;
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = 0;
}
