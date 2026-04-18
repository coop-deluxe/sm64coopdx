// controllable_platform.c.inc
static s8 sOldControllablePlatformDirectionState = 0;
static s8 sControllablePlatformDirectionState = 0;
static struct Object* sControllablePlatformSubs[4] = { 0 };

void controllable_platform_act_1(void) {
    o->oParentRelativePosY -= 4.0f;
    if (o->oParentRelativePosY < 41.0f) {
        o->oParentRelativePosY = 41.0f;
        o->oAction = 2;
    }
}

void controllable_platform_act_2(void) {
    if (o->oBehParams2ndByte == sControllablePlatformDirectionState) {
        return;
    }

    o->oParentRelativePosY += 4.0f;
    if (o->oParentRelativePosY > 51.0f) {
        o->oParentRelativePosY = 51.0f;
        o->oAction = 0;
    }
}

void bhv_controllable_platform_sub_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oTimer < 30) {
                break;
            }

            if (gMarioStates[0].marioObj->platform == o) {
                sControllablePlatformDirectionState = o->oBehParams2ndByte;
#ifdef VERSION_SH
                if (o->parentObj) { o->parentObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE; }
#endif
                o->oAction = 1;
                cur_obj_play_sound_2(SOUND_GENERAL_MOVING_PLATFORM_SWITCH);
                if (o->parentObj) { network_send_object(o->parentObj); }
            }
            break;

        case 1:
            controllable_platform_act_1();
            break;

        case 2:
            controllable_platform_act_2();
            break;
    }

    if (o->parentObj) {
        o->oVelX = o->parentObj->oVelX;
        o->oVelZ = o->parentObj->oVelZ;

        if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
}

static void bhv_controllable_platform_on_received_post(UNUSED u8 localIndex) {
    sOldControllablePlatformDirectionState = sControllablePlatformDirectionState;
}

void bhv_controllable_platform_init(void) {
    sControllablePlatformSubs[0] = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformSub, 0,
                                                            51, 204, 0, 0, 0);
    if (sControllablePlatformSubs[0] != NULL) { sControllablePlatformSubs[0]->oBehParams2ndByte = 1; }

    sControllablePlatformSubs[1] = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformSub, 0,
                                                            51, -204, 0, -0x8000, 0);
    if (sControllablePlatformSubs[1] != NULL) { sControllablePlatformSubs[1]->oBehParams2ndByte = 2; }

    sControllablePlatformSubs[2] = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformSub, 204,
                                                            51, 0, 0, 0x4000, 0);
    if (sControllablePlatformSubs[2] != NULL) { sControllablePlatformSubs[2]->oBehParams2ndByte = 3; }

    sControllablePlatformSubs[3] = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformSub,
                                                            -204, 51, 0, 0, -0x4000, 0);
    if (sControllablePlatformSubs[3] != NULL) { sControllablePlatformSubs[3]->oBehParams2ndByte = 4; }

    sControllablePlatformDirectionState = 0;

    o->oControllablePlatformUnkFC = o->oPosY;

    // syncing here works by using an event-based system. We only send the object if
    // the current direction state changes or mario taps one of the buttons
    // each time we send the object we also send it's position data
    struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    if (so != NULL) {
        so->on_received_post = bhv_controllable_platform_on_received_post;
        sync_object_init_field(o, o->oPosX);
        sync_object_init_field(o, o->oPosY);
        sync_object_init_field(o, o->oPosZ);
        sync_object_init_field(o, o->oVelX);
        sync_object_init_field(o, o->oVelY);
        sync_object_init_field(o, o->oVelZ);
        sync_object_init_field(o, o->oAction);
        sync_object_init_field(o, o->oPrevAction);
        sync_object_init_field(o, o->oTimer);
        sync_object_init_field(o, o->activeFlags);
        sync_object_init_field(o, sControllablePlatformDirectionState);
        sync_object_init_field(o, o->header.gfx.node.flags);

        sync_object_init_field(o, o->oControllablePlatformUnkF8);
        sync_object_init_field(o, o->oControllablePlatformUnkFC);
        sync_object_init_field(o, o->oControllablePlatformUnk100);
        sync_object_init_field(o, o->oFaceAnglePitch);
        sync_object_init_field(o, o->oFaceAngleRoll);
        for (s32 i = 0; i < 4; i++) {
            if (sControllablePlatformSubs[i] == NULL) { continue; }
            sync_object_init_field(o, sControllablePlatformSubs[i]->oAction);
            sync_object_init_field(o, sControllablePlatformSubs[i]->oPrevAction);
            sync_object_init_field(o, sControllablePlatformSubs[i]->oTimer);
            sync_object_init_field(o, sControllablePlatformSubs[i]->oParentRelativePosY);
        }
    }
}

void controllable_platform_hit_wall(s8 nextDir) {
    o->oControllablePlatformUnkF8 = nextDir;
    o->oTimer = 0;
    sControllablePlatformDirectionState = 5;

    cur_obj_play_sound_2(SOUND_GENERAL_QUIET_POUND1);
#ifdef VERSION_SH
    queue_rumble_data(50, 80);
#endif
}

void controllable_platform_check_walls(s8 nextDir, s8 wallDir[3], Vec3f dist1, UNUSED Vec3f dist2, Vec3f dist3) {
    if (wallDir[1] == 1 || (wallDir[0] == 1 && wallDir[2] == 1))
        controllable_platform_hit_wall(nextDir);
    else {
        if (wallDir[0] == 1) {
            if (((nextDir == 1 || nextDir == 2) && (s32) dist1[2] != 0)
                || ((nextDir == 3 || nextDir == 4) && (s32) dist1[0] != 0)) {
                controllable_platform_hit_wall(nextDir);
            } else {
                o->oPosX += dist1[0];
                o->oPosZ += dist1[2];
            }
        }

        if (wallDir[2] == 1) {
            if (((nextDir == 1 || nextDir == 2) && (s32) dist3[2] != 0)
                || ((nextDir == 3 || nextDir == 4) && (s32) dist3[0] != 0)) {
                controllable_platform_hit_wall(nextDir);
            } else {
                o->oPosX += dist3[0];
                o->oPosZ += dist3[2];
            }
        }
    }

    if (!is_point_within_radius_of_any_player(o->oPosX, o->oPosY, o->oPosZ, 400)) {
        sControllablePlatformDirectionState = 6;
        o->oControllablePlatformUnk100 = 1;
        o->oTimer = 0;
    }
}

void controllable_platform_shake_on_wall_hit(void) {
    if (o->oControllablePlatformUnkF8 == 1 || o->oControllablePlatformUnkF8 == 2) {
        o->oFaceAnglePitch = sins(o->oTimer * 0x1000) * 182.04444 * 10.0;
        o->oPosY = o->oControllablePlatformUnkFC + sins(o->oTimer * 0x2000) * 20.0f;
    } else {
        o->oFaceAngleRoll = sins(o->oTimer * 0x1000) * 182.04444 * 10.0;
        o->oPosY = o->oControllablePlatformUnkFC + sins(o->oTimer * 0x2000) * 20.0f;
    }

    if (o->oTimer == 32) {
        sControllablePlatformDirectionState = o->oControllablePlatformUnkF8;
        o->oFaceAnglePitch = 0;
        o->oFaceAngleRoll = 0;
        o->oPosY = o->oControllablePlatformUnkFC;
    }
}

void controllable_platform_tilt_from_mario(void) {
    struct MarioState *marioState = nearest_possible_mario_state_to_object(o);
    struct Object *player = marioState ? marioState->marioObj : NULL;
    if (!player) { return; }

    u8 playerCount = 0;
    f32 x = 0;
    f32 z = 0;

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (gMarioStates[i].marioObj->platform == o || gMarioStates[i].marioObj->platform == cur_obj_nearest_object_with_behavior(bhvControllablePlatformSub)) {
            x += gMarioStates[i].pos[0];
            z += gMarioStates[i].pos[2];
            playerCount++;
        }
    }

    if (playerCount > 0) {
        x /= (f32)playerCount;
        z /= (f32)playerCount;

        s16 dx = player->header.gfx.pos[0] - x;
        s16 dz = player->header.gfx.pos[2] - z;

        o->oFaceAnglePitch = dz * 4;
        o->oFaceAngleRoll = -dx * 4;
        if (sControllablePlatformDirectionState == 6) {
            sControllablePlatformDirectionState = 0;
            o->oTimer = 0;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }
}

void bhv_controllable_platform_loop(void) {
    s8 wallDisplacement[3];
    Vec3f dist1, dist2, dist3;

    o->oAngleVelRoll = 0;
    o->oAngleVelPitch = 0;
    o->oVelX = 0;
    o->oVelZ = 0;

    switch (sControllablePlatformDirectionState) {
        case 0:
            o->oFaceAnglePitch /= 2;
            o->oFaceAngleRoll /= 2;
            if (o->oControllablePlatformUnk100 == 1 && o->oTimer > 30) {
                sControllablePlatformDirectionState = 6;
                o->oTimer = 0;
            }
            break;

        case 1:
            o->oVelZ = 10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX + 250.0, o->oPosY, o->oPosZ + 300.0, 50.0f);
            wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX, o->oPosY, o->oPosZ + 300.0, 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX - 250.0, o->oPosY, o->oPosZ + 300.0, 50.0f);
            controllable_platform_check_walls(2, wallDisplacement, dist1, dist2, dist3);
            break;

        case 2:
            o->oVelZ = -10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX + 250.0, o->oPosY, o->oPosZ - 300.0, 50.0f);
            wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX, o->oPosY, o->oPosZ - 300.0, 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX - 250.0, o->oPosY, o->oPosZ - 300.0, 50.0f);
            controllable_platform_check_walls(1, wallDisplacement, dist1, dist2, dist3);
            break;

        case 3:
            o->oVelX = 10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX + 300.0, o->oPosY, o->oPosZ + 250.0, 50.0f);
            wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX + 300.0, o->oPosY, o->oPosZ, 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX + 300.0, o->oPosY, o->oPosZ - 250.0, 50.0f);
            controllable_platform_check_walls(4, wallDisplacement, dist1, dist2, dist3);
            break;

        case 4:
            o->oVelX = -10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX - 300.0, o->oPosY, o->oPosZ + 250.0, 50.0f);
            wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX - 300.0, o->oPosY, o->oPosZ, 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX - 300.0, o->oPosY, o->oPosZ - 250.0, 50.0f);
            controllable_platform_check_walls(3, wallDisplacement, dist1, dist2, dist3);
            break;

        case 5:
            controllable_platform_shake_on_wall_hit();
            return;
            break;

        case 6:
            if (obj_flicker_and_disappear(o, 150)) {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->activeFlags = ACTIVE_FLAG_ACTIVE;
                o->oControllablePlatformUnk100 = 0;
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oAngleVelRoll = 0;
                o->oAngleVelPitch = 0;
                o->oVelX = 0;
                o->oVelZ = 0;
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                sControllablePlatformDirectionState = 0;
                o->oTimer = 0;
                for (s32 i = 0; i < 4; i++) {
                    if (!sControllablePlatformSubs[i]) { continue; }
                    sControllablePlatformSubs[i]->oParentRelativePosY = 51.0f;
                    sControllablePlatformSubs[i]->oAction = 0;
                    sControllablePlatformSubs[i]->oTimer = 0;
                    sControllablePlatformSubs[i]->oVelX = 0;
                    sControllablePlatformSubs[i]->oVelZ = 0;
                }
            }
            break;
    }

    controllable_platform_tilt_from_mario();
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
    if (sControllablePlatformDirectionState != 0 && sControllablePlatformDirectionState != 6) {
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
    }

    if (sync_object_is_owned_locally(o->oSyncID) && sOldControllablePlatformDirectionState != sControllablePlatformDirectionState) {
        network_send_object(o);
    }
    sOldControllablePlatformDirectionState = sControllablePlatformDirectionState;
}
