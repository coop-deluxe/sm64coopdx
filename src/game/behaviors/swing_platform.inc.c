
void bhv_swing_platform_init(void) {
    o->oSwingPlatformAngle = 0x2000;

    struct SyncObject* so = sync_object_init(o, 4000.0f);
    if (so) {
        so->minUpdateRate = 5.0f;
        sync_object_init_field(o, &o->oSwingPlatformAngle);
        sync_object_init_field(o, &o->oFaceAngleRoll);
        sync_object_init_field(o, &o->oSwingPlatformSpeed);
        sync_object_init_field(o, &o->oAngleVelRoll);
    }
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
