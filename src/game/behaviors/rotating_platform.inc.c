// rotating_platform.c.inc

#include "levels/wf/header.h"
#include "levels/wdw/header.h"

struct WFRotatingPlatformData sWFRotatingPlatformData[] = {
    { 0, 100, wf_seg7_collision_rotating_platform, 2000 },
    { 0, 150, wdw_seg7_collision_070186B4, 1000 }
};

static void bhv_wf_rotating_wooden_platform_run_once(void) {
    if (o->oAction != 0) {
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
    }
    load_object_collision_model();
}

void bhv_wf_rotating_wooden_platform_init(void) {
    o->areaTimerType = AREA_TIMER_TYPE_LOOP;
    o->areaTimer = 0;
    o->areaTimerDuration = 380;
    o->areaTimerRunOnceCallback = bhv_wf_rotating_wooden_platform_run_once;
}

void bhv_wf_rotating_wooden_platform_loop(void) {
    if (o->oAction == 0) {
        o->oAngleVelYaw = 0;
        if (o->oTimer > 60) {
            o->oAction++;
        }
    } else {
        o->oAngleVelYaw = 0x100;
        if (o->oTimer > 126) {
            o->oAction = 0;
        }
    }
    cur_obj_rotate_face_angle_using_vel();
}

void bhv_rotating_platform_loop(void) {
    s8 sp1F = o->oBehParams >> 24;
    if (o->oTimer == 0 && BHV_ARR_CHECK(sWFRotatingPlatformData, o->oBehParams2ndByte, struct WFRotatingPlatformData)) {
        obj_set_collision_data(o, sWFRotatingPlatformData[o->oBehParams2ndByte].collisionData);
        o->oCollisionDistance = sWFRotatingPlatformData[o->oBehParams2ndByte].collisionDistance;
        cur_obj_scale(sWFRotatingPlatformData[o->oBehParams2ndByte].scale * 0.01f);
    }
    o->oAngleVelYaw = sp1F << 4;
    o->oFaceAngleYaw += o->oAngleVelYaw;
}
