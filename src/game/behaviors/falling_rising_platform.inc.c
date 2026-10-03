// falling_rising_platform.c.inc

void bhv_squishable_platform_init(void) {
    // synced via area timer
    o->areaTimerType = AREA_TIMER_TYPE_LOOP;
    o->areaTimer = 0;
    o->areaTimerDuration = 512;
}

void bhv_squishable_platform_loop(void) {
    o->header.gfx.scale[1] = (sins(o->oPlatformTimer) + 1.0) * 0.3 + 0.4;
    o->oPlatformTimer += 0x80;
}

void bhv_bitfs_sinking_platform_init(void) {
    // synced via area timer
    o->areaTimerType = AREA_TIMER_TYPE_LOOP;
    o->areaTimer = 0;
    o->areaTimerDuration = 256;
}

void bhv_bitfs_sinking_platform_loop(void) {
    o->oPosY -= sins(o->oPlatformTimer) * 0.58; //! f32 double conversion error accumulates on Wii VC causing the platform to rise up
    o->oPlatformTimer += 0x100;
}

// TODO: Named incorrectly. fix
void bhv_ddd_moving_pole_loop(void) {
    obj_copy_pos_and_angle(o, o->parentObj);
}

void bhv_bitfs_sinking_cage_platform_init(void) {
    if (o->oBehParams2ndByte != 0) {
        o->oPosY -= 300.0f;
    }

    // synced via area timer
    o->areaTimerType = AREA_TIMER_TYPE_LOOP;
    o->areaTimer = 0;
    o->areaTimerDuration = 256;
}

void bhv_bitfs_sinking_cage_platform_loop(void) {
    if (o->oBehParams2ndByte != 0) {
        o->oPosY += sins(o->oPlatformTimer) * 7.0f;
    } else {
        o->oPosY -= sins(o->oPlatformTimer) * 3.0f;
    }
    o->oPlatformTimer += 0x100;
}
