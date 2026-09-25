// tree_particles.c.inc

#include "game/envfx_snow.h"

void bhv_tree_snow_or_leaf_loop(void) {
    cur_obj_update_floor_height();
    if (o->oTimer == 0) {
        o->oAngleVelPitch = (random_float() - 0.5) * 0x1000;
        o->oAngleVelRoll = (random_float() - 0.5) * 0x1000;
        o->oTreeSnowOrLeafUnkF8 = 4;
        o->oTreeSnowOrLeafUnkFC = random_float() * 0x400 + 0x600;
    }
    if (o->oPosY < o->oFloorHeight || o->oFloorHeight < gLevelValues.floorLowerLimit || o->oTimer > 100) {
        obj_mark_for_deletion(o);
    }
    if (gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY * 212 / 240)) {
        obj_mark_for_deletion(o);
    }
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oFaceAngleRoll += o->oAngleVelRoll;
    o->oVelY += -3.0f;
    if (o->oVelY < -8.0f) {
        o->oVelY = -8.0f;
    }
    if (o->oForwardVel > 0) {
        o->oForwardVel -= 0.3;
    } else {
        o->oForwardVel = 0;
    }
    o->oPosX += sins(o->oMoveAngleYaw) * sins(o->oTreeSnowOrLeafUnkF4) * o->oTreeSnowOrLeafUnkF8;
    o->oPosZ += coss(o->oMoveAngleYaw) * sins(o->oTreeSnowOrLeafUnkF4) * o->oTreeSnowOrLeafUnkF8;
    o->oTreeSnowOrLeafUnkF4 += o->oTreeSnowOrLeafUnkFC;
    o->oPosY += o->oVelY;
}

void bhv_snow_leaf_particle_spawn_init(void) {
    s32 isSnow = (gEnvFxMode == ENVFX_SNOW_NORMAL || gEnvFxMode == ENVFX_SNOW_BLIZZARD);
    struct Object *snowOrLeafObj; // Either snow or leaf
    f32 scale;
    struct Object *player = nearest_player_to_object(o);
    if (player) {
        player->oActiveParticleFlags &= ~0x2000;
    }
    if (isSnow) {
        if (random_float() < 0.5) {
            snowOrLeafObj = spawn_object(o, MODEL_WHITE_PARTICLE_DL, bhvTreeSnow);
            if (snowOrLeafObj != NULL) {
                scale = random_float();
                obj_scale_xyz(snowOrLeafObj, scale, scale, scale);
                snowOrLeafObj->oMoveAngleYaw = random_u16();
                snowOrLeafObj->oForwardVel = random_float() * 5.0f;
                snowOrLeafObj->oVelY = random_float() * 15.0f;
            }
        }
    } else {
        if (random_float() < 0.3) {
            snowOrLeafObj = spawn_object(o, MODEL_LEAVES, bhvTreeLeaf);
            if (snowOrLeafObj != NULL) {
                scale = random_float() * 3.0f;
                obj_scale_xyz(snowOrLeafObj, scale, scale, scale);
                snowOrLeafObj->oMoveAngleYaw = random_u16();
                snowOrLeafObj->oForwardVel = random_float() * 5.0f + 5.0f;
                snowOrLeafObj->oVelY = random_float() * 15.0f;
                snowOrLeafObj->oFaceAnglePitch = random_u16();
                snowOrLeafObj->oFaceAngleRoll = random_u16();
                snowOrLeafObj->oFaceAngleYaw = random_u16();
            }
        }
    }
}
