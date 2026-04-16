// hoot.c.inc

static u8 localTalkToHoot = 0;

static u8 bhv_hoot_ignore_if_true(void) {
    return (gMarioStates[0].action == ACT_RIDING_HOOT) && (gMarioStates[0].usedObj == o);
}

void bhv_hoot_init(void) {
    cur_obj_init_animation(0);

    o->oHomeX = o->oPosX + 800.0f;
    o->oHomeY = o->oPosY - 150.0f;
    o->oHomeZ = o->oPosZ + 300.0f;
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

    cur_obj_become_intangible();
    localTalkToHoot = 0;

    // uses standard distance-based syncing
    struct SyncObject* so = sync_object_init(o, 4000.0f);
    if (so) {
        so->ignore_if_true = bhv_hoot_ignore_if_true;
        sync_object_init_field(o, o->oHootAvailability);
        sync_object_init_field(o, o->oMoveAnglePitch);
        sync_object_init_field(o, o->header.gfx.animInfo.animFrame);
    }
}

f32 hoot_find_next_floor(struct FloorGeometry **floor, f32 dist) {
    f32 nextX = dist * sins(o->oMoveAngleYaw) + o->oPosX;
    f32 nextZ = dist * coss(o->oMoveAngleYaw) + o->oPosZ;
    f32 floorY = find_floor_height_and_data(nextX, 10000.0f, nextZ, floor);

    return floorY;
}

void hoot_floor_bounce(void) {
    struct FloorGeometry *floor;
    f32 floorY;

    floorY = hoot_find_next_floor(&floor, 375.0f);
    if (floorY + 75.0f > o->oPosY)
        o->oMoveAnglePitch -= 3640.8888;

    floorY = hoot_find_next_floor(&floor, 200.0f);
    if (floorY + 125.0f > o->oPosY)
        o->oMoveAnglePitch -= 7281.7776;

    floorY = hoot_find_next_floor(&floor, 0);
    if (floorY + 125.0f > o->oPosY) {
        o->oPosY = floorY + 125.0f;
    }
    if (o->oMoveAnglePitch < -21845.3328) {
        o->oMoveAnglePitch = -21845;
    }
}

void hoot_free_step(s16 fastOscY, s32 speed) {
    struct FloorGeometry *floor;
    s16 yaw = o->oMoveAngleYaw;
    s16 pitch = o->oMoveAnglePitch;
    s16 animFrame = o->header.gfx.animInfo.animFrame;
    f32 xPrev = o->oPosX;
    f32 zPrev = o->oPosZ;
    f32 hSpeed;

    o->oVelY = sins(pitch) * speed;
    hSpeed = coss(pitch) * speed;
    o->oVelX = sins(yaw) * hSpeed;
    o->oVelZ = coss(yaw) * hSpeed;

    o->oPosX += o->oVelX;
    if (fastOscY == 0) {
        o->oPosY -= o->oVelY + coss((s32)(animFrame * 3276.8)) * 50.0f / 4;
    } else {
        o->oPosY -= o->oVelY + coss((s32)(animFrame * 6553.6)) * 50.0f / 4;
    }
    o->oPosZ += o->oVelZ;

    find_floor_height_and_data(o->oPosX, o->oPosY, o->oPosZ, &floor);
    if (floor == NULL) {
        o->oPosX = xPrev;
        o->oPosZ = zPrev;
    }

    if (animFrame == 0) {
        cur_obj_play_sound_2(SOUND_GENERAL_SWISH_WATER);
    }
}

void hoot_player_set_yaw(void) {
    if (o->heldByPlayerIndex >= MAX_PLAYERS) { return; }
    struct MarioState *marioState = &gMarioStates[o->heldByPlayerIndex];
    s16 stickX = marioState->controller->rawStickX;
    s16 stickY = marioState->controller->rawStickY;
    if (stickX < 10 && stickX >= -9) {
        stickX = 0;
    }
    if (stickY < 10 && stickY >= -9) {
        stickY = 0;
    }

    o->oMoveAngleYaw -= 5 * stickX;
}

void hoot_carry_step(s32 speed, UNUSED f32 xPrev, UNUSED f32 zPrev) {
    s16 yaw = o->oMoveAngleYaw;
    s16 pitch = o->oMoveAnglePitch;
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    o->oVelY = sins(pitch) * speed;
    f32 hSpeed = coss(pitch) * speed;
    o->oVelX = sins(yaw) * hSpeed;
    o->oVelZ = coss(yaw) * hSpeed;

    o->oPosX += o->oVelX;
    o->oPosY -= o->oVelY + coss((s32)(animFrame * 6553.6)) * 50.0f / 4;
    o->oPosZ += o->oVelZ;

    if (animFrame == 0) {
        cur_obj_play_sound_2(SOUND_GENERAL_SWISH_WATER);
    }
}

void hoot_surface_collision(f32 xPrev, UNUSED f32 yPrev, f32 zPrev) {
    struct FloorGeometry *floor;
    struct WallCollisionData hitbox;
    f32 floorY;

    hitbox.x = o->oPosX;
    hitbox.y = o->oPosY;
    hitbox.z = o->oPosZ;
    hitbox.offsetY = 10.0;
    hitbox.radius = 50.0;

    if (find_wall_collisions(&hitbox) != 0) {
        o->oPosX = hitbox.x;
        o->oPosY = hitbox.y;
        o->oPosZ = hitbox.z;

        if (o->heldByPlayerIndex < MAX_PLAYERS) {
            gMarioStates[o->heldByPlayerIndex].marioObj->oInteractStatus |= INT_STATUS_MARIO_UNK7; /* bit 7 */
        }
    }

    floorY = find_floor_height_and_data(o->oPosX, o->oPosY, o->oPosZ, &floor);
    if (floor == NULL) {
        o->oPosX = xPrev;
        o->oPosZ = zPrev;
        return;
    }

    if (absf_2(o->oPosX) > 8000.0f) {
        o->oPosX = xPrev;
    }
    if (absf_2(o->oPosZ) > 8000.0f) {
        o->oPosZ = zPrev;
    }

    if (floorY + 125.0f > o->oPosY) {
        o->oPosY = floorY + 125.0f;
    }
}

void hoot_act_ascent(f32 xPrev, f32 zPrev) {
    f32 negX = 0 - o->oPosX;
    f32 negZ = 0 - o->oPosZ;
    s16 angleToOrigin = atan2s(negZ, negX);

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, angleToOrigin, 0x500);
    o->oMoveAnglePitch = 0xCE38;

    if (o->oTimer >= 29) {
        cur_obj_play_sound_1(SOUND_ENV_WIND2);
        o->header.gfx.animInfo.animFrame = 1;
    }

    if (o->oPosY > 6500.0f) {
        o->oAction = HOOT_ACT_CARRY;
    }

    hoot_carry_step(60, xPrev, zPrev);
}

void hoot_action_loop(void) {
    struct MarioState *marioState = nearest_mario_state_to_object(o);
    f32 xPrev = o->oPosX;
    f32 yPrev = o->oPosY;
    f32 zPrev = o->oPosZ;

    switch (o->oAction) {
        case HOOT_ACT_ASCENT:
            hoot_act_ascent(xPrev, zPrev);
            break;

        case HOOT_ACT_CARRY:
            hoot_player_set_yaw();

            o->oMoveAnglePitch = 0x71C;

            if (o->oPosY < 2700.0f) {
                //set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);

                if (marioState == &gMarioStates[0] && cutscene_object_with_dialog(CUTSCENE_DIALOG, o, gBehaviorValues.dialogs.HootTiredDialog)) {
                    clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);

                    o->oAction = HOOT_ACT_TIRED;
                }
            }

            hoot_carry_step(20, xPrev, zPrev);
            break;

        case HOOT_ACT_TIRED:
            hoot_player_set_yaw();

            o->oMoveAnglePitch = 0;

            hoot_carry_step(20, xPrev, zPrev);

            if (o->oTimer >= 61) {
                if (o->heldByPlayerIndex < MAX_PLAYERS) {
                    gMarioStates[o->heldByPlayerIndex].marioObj->oInteractStatus |= INT_STATUS_MARIO_UNK7; /* bit 7 */
                }
            }
            break;
    }

    hoot_surface_collision(xPrev, yPrev, zPrev);
}

void hoot_turn_to_home(void) {
    f32 homeDistX = o->oHomeX - o->oPosX;
    f32 homeDistY = o->oHomeY - o->oPosY;
    f32 homeDistZ = o->oHomeZ - o->oPosZ;
    s16 hAngleToHome = atan2s(homeDistZ, homeDistX);
    s16 vAngleToHome = atan2s(sqrtf(homeDistX * homeDistX + homeDistZ * homeDistZ), -homeDistY);

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, hAngleToHome, 0x140);
    o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, vAngleToHome, 0x140);
}

void hoot_awake_loop(void) {
    if (o->oInteractStatus == INT_STATUS_MARIO_STUNNED) {
        hoot_action_loop();
        cur_obj_init_animation(1);
    } else {
        cur_obj_init_animation(0);

        hoot_turn_to_home();
        hoot_floor_bounce();
        hoot_free_step(0, 10);

        o->oAction = 0;
        o->oTimer = 0;
    }

    set_object_visibility(o, 2000);
}

static u8 hoot_wants_to_talk_continue_dialog(void) {
    return (o->oHootAvailability == HOOT_AVAIL_WANTS_TO_TALK && localTalkToHoot == 1);
}

void bhv_hoot_loop(void) {
    struct MarioState *marioState = nearest_mario_state_to_object(o);
    static u8 forceFlySanity = TRUE;

    switch (o->oHootAvailability) {
        case HOOT_AVAIL_ASLEEP_IN_TREE:
            forceFlySanity = TRUE;
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 50)) {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->oHootAvailability = HOOT_AVAIL_WANTS_TO_TALK;
            }
            break;

        case HOOT_AVAIL_WANTS_TO_TALK:
            hoot_awake_loop();

            if (marioState == &gMarioStates[0] && localTalkToHoot == 0) {
                localTalkToHoot = 1;
            }

            if (localTalkToHoot == 1 && set_mario_npc_dialog(&gMarioStates[0], 2, hoot_wants_to_talk_continue_dialog) == 2 && cutscene_object_with_dialog(CUTSCENE_DIALOG, o, gBehaviorValues.dialogs.HootIntroDialog)) {
                localTalkToHoot = 2;
                set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
                cur_obj_become_tangible();
                o->oHootAvailability = HOOT_AVAIL_READY_TO_FLY;
                network_send_object(o);
            }
            break;

        case HOOT_AVAIL_READY_TO_FLY:
            if (forceFlySanity) {
                set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
                cur_obj_become_tangible();
                forceFlySanity = FALSE;
            }
            hoot_awake_loop();
            break;
    }
}
