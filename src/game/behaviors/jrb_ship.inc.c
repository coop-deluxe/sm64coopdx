// jrb_ship.c.inc

struct ObjectHitbox sSkullSlidingBoxHitbox = {
    .interactType = INTERACT_DAMAGE,
    .downOffset = 0,
    .damageOrCoinValue = 1,
    .health = 1,
    .numLootCoins = 0,
    .radius = 130,
    .height = 100,
    .hurtboxRadius = 0,
    .hurtboxHeight = 0,
};

void bhv_sunken_ship_part_loop(void) {
    if (o->oDistanceToMario > 10000.0f) {
        o->oOpacity = 140;
    } else {
        o->oOpacity = o->oDistanceToMario * 140.0f / 10000.0;
    }
    cur_obj_disable_rendering();
}

void bhv_ship_part_3_loop(void) {
    // Syncing TODO: Can't the floating ship use an area timer?
    // this uses a standard distance-based syncing system
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, 4000.0f);
        if (so) {
            so->maxUpdateRate = 5.0f;
            sync_object_init_field(o, o->oFaceAnglePitch);
            sync_object_init_field(o, o->oFaceAngleRoll);
            sync_object_init_field(o, o->oShipPart3UnkF4);
        }
    }

    s16 oldPitch = o->oFaceAnglePitch;
    s16 oldRoll = o->oFaceAngleRoll;
    cur_obj_set_pos_to_home_with_debug();
    o->oShipPart3UnkF4 += 0x100;
    o->oFaceAnglePitch = sins(o->oShipPart3UnkF4) * 1024.0f;
    o->oFaceAngleRoll = sins(o->oShipPart3UnkF8) * 1024.0f;
    o->oAngleVelPitch = o->oFaceAnglePitch - oldPitch;
    o->oAngleVelRoll = o->oFaceAngleRoll - oldRoll;
    if (gMarioObject && gMarioObject->oPosY > 1000.0f) {
        cur_obj_play_sound_1(SOUND_ENV_BOAT_ROCKING1);
    }
}

void bhv_jrb_sliding_box_loop(void) {
    // Syncing TODO: Can't this box use an area timer?
    // this uses a standard distance-based syncing system
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, 4000.0f);
        if (so) {
            so->maxUpdateRate = 5.0f;
            sync_object_init_field(o, o->oFaceAnglePitch);
            sync_object_init_field(o, o->oFaceAngleRoll);
            sync_object_init_field(o, o->oJrbSlidingBoxUnkF8);
            sync_object_init_field(o, o->oJrbSlidingBoxUnkFC);
            sync_object_init_field(o, o->oParentRelativePosX);
            sync_object_init_field(o, o->oParentRelativePosY);
            sync_object_init_field(o, o->oParentRelativePosZ);
        }
    }

    Mat4 mat;
    Vec3f sp48;
    struct Object *sunkenShipObj;
    s16 shipPitch;
    if (o->oJrbSlidingBoxUnkF4 == NULL) {
        sunkenShipObj = cur_obj_nearest_object_with_behavior(bhvInSunkenShip3);
        if (sunkenShipObj != NULL) {
            o->oJrbSlidingBoxUnkF4 = sunkenShipObj;
            o->oParentRelativePosX = o->oPosX - sunkenShipObj->oPosX;
            o->oParentRelativePosY = o->oPosY - sunkenShipObj->oPosY;
            o->oParentRelativePosZ = o->oPosZ - sunkenShipObj->oPosZ;
        }
    } else {
        sunkenShipObj = o->oJrbSlidingBoxUnkF4;
        Vec3s faceAngle;
        faceAngle[0] = sunkenShipObj->oFaceAnglePitch;
        faceAngle[1] = sunkenShipObj->oFaceAngleYaw;
        faceAngle[2] = sunkenShipObj->oFaceAngleRoll;
        Vec3f parentRelativePos;
        parentRelativePos[0] = o->oParentRelativePosX;
        parentRelativePos[1] = o->oParentRelativePosY;
        parentRelativePos[2] = o->oParentRelativePosZ;
        mtxf_rotate_zxy_and_translate(mat, parentRelativePos, faceAngle);
        linear_mtxf_mul_vec3f(mat, sp48, parentRelativePos);
        o->oPosX = sunkenShipObj->oPosX + sp48[0];
        o->oPosY = sunkenShipObj->oPosY + sp48[1];
        o->oPosZ = sunkenShipObj->oPosZ + sp48[2];
        shipPitch = sunkenShipObj->oFaceAnglePitch;
    }
    struct Surface *surface;
    find_floor(o->oPosX, o->oPosY, o->oPosZ, &surface);
    if (surface != NULL) {
        o->oFaceAnglePitch = shipPitch;
    }
    o->oJrbSlidingBoxUnkFC = sins(o->oJrbSlidingBoxUnkF8) * 20.0f;
    o->oJrbSlidingBoxUnkF8 += 0x100;
    o->oParentRelativePosZ += o->oJrbSlidingBoxUnkFC;
    if (gMarioObject && gMarioObject->oPosY > 1000.0f) {
        if (absf(o->oJrbSlidingBoxUnkFC) > 3.0f) {
            cur_obj_play_sound_1(SOUND_AIR_ROUGH_SLIDE);
        }
    }

    obj_set_hitbox(o, &sSkullSlidingBoxHitbox);
    if (!(o->oJrbSlidingBoxUnkF8 & 0x7FFF)) {
        cur_obj_become_tangible();
    }

    if (gMarioObject && obj_check_if_collided_with_object(o, gMarioObject)) {
        o->oInteractStatus = 0;
        cur_obj_become_intangible();
    }
}
