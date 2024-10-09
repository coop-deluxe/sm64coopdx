// tower_platform.c.inc

void bhv_wf_solid_tower_platform_loop(void) {
    if (!o->parentObj) { return; }
    if (o->parentObj->oAction == 1) {
        cur_obj_become_tangible();
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    } else if (o->parentObj->oAction > 1) {
        cur_obj_become_intangible();
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }
}

void bhv_wf_elevator_tower_platform_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        sync_object_init_field(o, &o->oAction);
        sync_object_init_field(o, &o->oPosY);
        sync_object_init_field(o, &o->oTimer);
    }

    switch (o->oAction) {
        case 0:
            if (gMarioObject && gMarioObject->platform == o) {
                o->oAction++;
                network_send_object(o);
            }
            break;
        case 1:
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
            if (o->oTimer > 140)
                o->oAction++;
            else
                o->oPosY += 5.0f;
            break;
        case 2:
            if (o->oTimer > 60)
                o->oAction++;
            break;
        case 3:
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
            if (o->oTimer > 140)
                o->oAction = 0;
            else
                o->oPosY -= 5.0f;
            break;
    }

    if (o->parentObj) {
        if (o->parentObj->oAction == 1) {
            cur_obj_become_tangible();
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        } else if (o->parentObj->oAction > 1) {
            cur_obj_become_intangible();
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        }
    }
}

void bhv_wf_sliding_tower_platform_loop(void) {
    s32 sp24 = o->oPlatformUnk110 / o->oPlatformUnk10C;
    switch (o->oAction) {
        case 0:
            if (o->oTimer > sp24) {
                o->oAction++;
            }
            o->oForwardVel = -o->oPlatformUnk10C;
            break;
        case 1:
            if (o->oTimer > sp24)
                o->oAction = 0;
            o->oForwardVel = o->oPlatformUnk10C;
            break;
    }
    cur_obj_compute_vel_xz();
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;

    if (o->parentObj) {
        if (o->parentObj->oAction == 1) {
            cur_obj_become_tangible();
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        } else if (o->parentObj->oAction > 1) {
            cur_obj_become_intangible();
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        }
    }
}

void spawn_and_init_wf_platforms(s16 a, const BehaviorScript *bhv) {
    s16 yaw;
    struct Object *platform = spawn_object(o, a, bhv);
    yaw = o->oPlatformSpawnerUnkF4 * o->oPlatformSpawnerUnkFC + o->oPlatformSpawnerUnkF8;
    if (platform != NULL) {
        platform->oMoveAngleYaw = yaw;
        platform->oPosX += o->oPlatformSpawnerUnk100 * sins(yaw);
        platform->oPosY += 100 * o->oPlatformSpawnerUnkF4;
        platform->oPosZ += o->oPlatformSpawnerUnk100 * coss(yaw);
        platform->oPlatformUnk110 = o->oPlatformSpawnerUnk104;
        platform->oPlatformUnk10C = o->oPlatformSpawnerUnk108;
    }
    o->oPlatformSpawnerUnkF4++;

    if (platform != NULL) {
        if (bhv == smlua_override_behavior(bhvWfSolidTowerPlatform) || bhv == smlua_override_behavior(bhvWfSlidingTowerPlatform)) {
            u32 loopTime = 1 + (platform->oPlatformUnk110 / platform->oPlatformUnk10C);
            loopTime *= 2;
            loopTime += 1;
            platform->areaTimerType = AREA_TIMER_TYPE_LOOP;
            platform->areaTimer = 0;
            platform->areaTimerDuration = loopTime;
            platform->areaTimerRunOnceCallback = load_object_collision_model;
        }
    }
}

void spawn_wf_platform_group(void) {
    UNUSED s32 unused = 8;
    o->oPlatformSpawnerUnkF4 = 0;
    o->oPlatformSpawnerUnkF8 = 0;
    o->oPlatformSpawnerUnkFC = 0x2000;
    o->oPlatformSpawnerUnk100 = 704.0f;
    o->oPlatformSpawnerUnk104 = 380.0f;
    o->oPlatformSpawnerUnk108 = 3.0f;
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSlidingTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSlidingTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSlidingTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM, bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR, bhvWfElevatorTowerPlatform);
}

void bhv_tower_platform_group_init(void) {
    spawn_wf_platform_group();
}

void bhv_tower_platform_group_loop(void) {

    u8 anyPlayerInRange = FALSE;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (gMarioStates[i].marioObj->oPosY > o->oHomeY - 1000.0f) { anyPlayerInRange = TRUE; }
    }

    switch (o->oAction) {
        case 0:
            if (anyPlayerInRange) { o->oAction++; }
            break;
        case 1:
            if (!anyPlayerInRange) { o->oAction++; }
            break;
        case 2:
        case 3:
        case 4:
            o->oAction++;
            break;
        case 5:
            o->oAction = 0;
            break;
    }
}
