
/**
 * Behaviors for bhvFerrisWheelAxle and bhvFerrisWheelPlatform.
 * These are the revolving sets of four platforms in BitDW and BitS.
 * The axle spawns the four platforms.
 */

/**
 * Properties for the ferris wheel axle and platforms.
 */
struct FerrisWheelProperties {
    void const *axleCollision;
    void const *platformCollision;
    s16 platformModel;
};

/**
 * Properties for the ferris wheels in BitS and BitDW, respectively.
 */
static struct FerrisWheelProperties sFerrisWheelProperties[] = {
    { bits_seg7_collision_0701ACAC, bits_seg7_collision_0701AC28, MODEL_BITS_BLUE_PLATFORM },
    { bitdw_seg7_collision_0700F7F0, bitdw_seg7_collision_0700F898, MODEL_BITDW_BLUE_PLATFORM },
};

/**
 * Init function for bhvFerrisWheelAxle.
 * It doesn't have an update function, but it increments its roll in its
 * behavior script.
 */
void bhv_ferris_wheel_axle_init(void) {
    struct Object *platform;
    s32 i;

    if (!BHV_ARR_CHECK(sFerrisWheelProperties, o->oBehParams2ndByte, struct FerrisWheelProperties)) {
        return;
    }

    o->collisionData = segmented_to_virtual(sFerrisWheelProperties[o->oBehParams2ndByte].axleCollision);

    for (i = 0; i < 4; i++) {
        platform = spawn_object_relative(i, 0, 0, 0, o,
                                         sFerrisWheelProperties[o->oBehParams2ndByte].platformModel,
                                         bhvFerrisWheelPlatform);

        if (platform != NULL) {
            platform->collisionData =
                segmented_to_virtual(sFerrisWheelProperties[o->oBehParams2ndByte].platformCollision);
        }
    }

    struct SyncObject* so = sync_object_init(o, 2000.0f);
    if (so) {
        so->hasStandardFields = FALSE;
        so->maxUpdateRate = 5.0f;
        sync_object_init_field(o, &o->oFaceAngleRoll);
    }
}

void bhv_ferris_wheel_platform_init(void) {
    struct SyncObject* so = sync_object_init(o, 2000.0f);
    if (so) {
        so->hasStandardFields = FALSE;
        so->maxUpdateRate = 5.0f;
        sync_object_init_field(o, &o->oPosX);
        sync_object_init_field(o, &o->oPosY);
        sync_object_init_field(o, &o->oPosZ);
    }
}

/**
 * Update function for bhvFerrisWheelPlatform.
 * Position self relative to parent using the parent's roll.
 */
void bhv_ferris_wheel_platform_update(void) {
    f32 offsetXZ;
    s16 offsetAngle;

    if (!o->parentObj) { return; }

    obj_perform_position_op(POS_OP_SAVE_POSITION);

    offsetAngle = o->parentObj->oFaceAngleRoll + o->oBehParams2ndByte * 0x4000;
    offsetXZ = 400.0f * coss(offsetAngle);

    o->oPosX = o->parentObj->oPosX + offsetXZ * sins(o->parentObj->oMoveAngleYaw)
               + 300.0f * coss(o->parentObj->oMoveAngleYaw);

    o->oPosY = o->parentObj->oPosY + 400.0f * sins(offsetAngle);

    o->oPosZ = o->parentObj->oPosZ + offsetXZ * coss(o->parentObj->oMoveAngleYaw)
               + 300.0f * sins(o->parentObj->oMoveAngleYaw);

    obj_perform_position_op(POS_OP_COMPUTE_VELOCITY);
}
