// checkerboard_platform.c.inc

struct CheckerboardPlatformStartPos sCheckerboardPlatformStartpos[] = { { 145, { 0.7f, 1.5f, 0.7f }, 7.0f },
                                       { 235, { 1.2f, 2.0f, 1.2f }, 11.6f } };

void bhv_checkerboard_elevator_group_init(void) {
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    s32 relativeZ;
    if (o->oBehParams2ndByte == 0) {
        o->oBehParams2ndByte = 65;
    }
    s32 relativeY = o->oBehParams2ndByte * 10;
    s32 startPosIndex = (o->oBehParams >> 24) & 0XFF;
    for (s32 i = 0; i < 2; i++) {
        if (i == 0) {
            relativeZ = -sCheckerboardPlatformStartpos[startPosIndex].relativePosZ;
        } else {
            relativeZ = sCheckerboardPlatformStartpos[startPosIndex].relativePosZ;
        }

        struct Object *checkerboardPlatform = spawn_object_relative(i, 0, i * relativeY, relativeZ, o, MODEL_CHECKERBOARD_PLATFORM, bhvCheckerboardPlatformSub);
        if (checkerboardPlatform == NULL) { continue; }
        checkerboardPlatform->oCheckerBoardPlatformUnk1AC = sCheckerboardPlatformStartpos[startPosIndex].radius;
        checkerboardPlatform->oTimer = 0;
        vec3f_copy(checkerboardPlatform->header.gfx.scale, sCheckerboardPlatformStartpos[startPosIndex].scale);
    }
}

void bhv_checkerboard_elevator_group_loop(void) { }

void checkerboard_plat_act_move_y(UNUSED s32 unused, f32 vel, s32 time) {
    o->oMoveAnglePitch = 0;
    o->oAngleVelPitch = 0;
    o->oForwardVel = 0.0f;
    o->oVelY = vel;
    if (o->oTimer > time) {
        o->oAction++;
    }
}

void checkerboard_plat_act_rotate(s32 nextAction, s16 pitch) {
    o->oVelY = 0.0f;
    o->oAngleVelPitch = pitch;
    if (o->oTimer + 1 == 0x8000 / absi(pitch)) {
        o->oAction = nextAction;
    }
    o->oCheckerBoardPlatformUnkF8 = nextAction;
}

static void bhv_checkerboard_platform_run_once(void) {
    if (o->oDistanceToMario < 1000.0f) {
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
    }
    load_object_collision_model();
}

void bhv_checkerboard_platform_init(void) {
    o->oCheckerBoardPlatformUnkFC = o->parentObj ? o->parentObj->oBehParams2ndByte : 0;
    o->areaTimerType = AREA_TIMER_TYPE_LOOP;
    o->areaTimer = 0;
    o->areaTimerDuration = 132 + o->oCheckerBoardPlatformUnkFC * 2;
    o->areaTimerRunOnceCallback = bhv_checkerboard_platform_run_once;
}

void bhv_checkerboard_platform_loop(void) {
    f32 radius = o->oCheckerBoardPlatformUnk1AC;
    o->oCheckerBoardPlatformUnkF8 = 0;
    switch (o->oAction) {
        case 0:
            if (o->oBehParams2ndByte == 0) {
                o->oAction = 1;
            } else {
                o->oAction = 3;
            }
            break;
        case 1:
            checkerboard_plat_act_move_y(2, 10.0f, o->oCheckerBoardPlatformUnkFC);
            break;
        case 2:
            checkerboard_plat_act_rotate(3, 512);
            break;
        case 3:
            checkerboard_plat_act_move_y(4, -10.0f, o->oCheckerBoardPlatformUnkFC);
            break;
        case 4:
            checkerboard_plat_act_rotate(1, -512);
            break;
    }
    o->oMoveAnglePitch += absi(o->oAngleVelPitch);
    o->oFaceAnglePitch += absi(o->oAngleVelPitch);
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    if (o->oMoveAnglePitch != 0) {
        o->oForwardVel = signum_positive(o->oAngleVelPitch) * sins(o->oMoveAnglePitch) * radius;
        o->oVelY = signum_positive(o->oAngleVelPitch) * coss(o->oMoveAnglePitch) * radius;
    }
    if (o->oCheckerBoardPlatformUnkF8 == 1) {
        o->oAngleVelPitch = 0;
        o->oFaceAnglePitch &= ~0x7FFF;
        cur_obj_move_using_fvel_and_gravity();
    } else {
        cur_obj_move_using_fvel_and_gravity();
    }
}
