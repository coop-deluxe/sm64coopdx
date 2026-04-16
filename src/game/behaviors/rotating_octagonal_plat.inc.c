// rotating_octagonal_plat.inc.c

static void const *sOctagonalPlatformCollision[] = {
    bits_seg7_collision_0701AA84,
    rr_seg7_collision_07029508,
};

static s16 sOctagonalPlatformAngularVelocities[] = { 300, -300, 600, -600 };

void bhv_rotating_octagonal_plat_init(void) {
    if (BHV_ARR_CHECK(sOctagonalPlatformCollision, (u8)(o->oBehParams >> 16), void const*)) {
        o->collisionData = segmented_to_virtual(sOctagonalPlatformCollision[(u8)(o->oBehParams >> 16)]);
    }
    o->oAngleVelYaw = BHV_ARR(sOctagonalPlatformAngularVelocities, (u8)(o->oBehParams >> 24), s16);
}

void bhv_rotating_octagonal_plat_loop(void) {
    o->oFaceAngleYaw += o->oAngleVelYaw;
}
