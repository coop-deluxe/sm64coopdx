
void bhv_swing_platform_init(void) {
    o->oSwingPlatformAngle = 0x2000;

    struct SyncObject* so = network_init_object(o, 4000.0f);
    so->minUpdateRate = 5.0f;
    network_init_object_field(o, &o->oSwingPlatformAngle);
    network_init_object_field(o, &o->oFaceAngleRoll);
    network_init_object_field(o, &o->oSwingPlatformSpeed);
    network_init_object_field(o, &o->oAngleVelRoll);
}

void bhv_swing_platform_update(void) {

    s32 startRoll = o->oFaceAngleRoll;

    if (o->oFaceAngleRoll < 0) {
        o->oSwingPlatformSpeed += 4.0f;
    } else {
        o->oSwingPlatformSpeed -= 4.0f;
    }

    o->oSwingPlatformAngle += o->oSwingPlatformSpeed;
    o->oFaceAngleRoll = o->oSwingPlatformAngle;
    o->oAngleVelRoll = o->oFaceAngleRoll - startRoll;
}
