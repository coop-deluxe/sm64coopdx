// cannon.c.inc

void bhv_cannon_base_unused_loop(void) {
    o->oPosY += o->oVelY;
}

void opened_cannon_act_0(void) {
    if (o->oTimer == 0) {
        o->oInteractStatus = 0;
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        o->oMoveAnglePitch = 0;
        o->oMoveAngleYaw = (s16)(o->oBehParams2ndByte << 8);
        o->oCannonUnkF4 = 0;
        o->oCannonUnk10C = 0;
    }
    cur_obj_become_tangible();
    cur_obj_enable_rendering();

    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    if (distanceToPlayer < 500.0f) {
        //cur_obj_become_tangible();
        //cur_obj_enable_rendering();
        if (player == gMarioStates[0].marioObj) {
            if (o->oInteractStatus & INT_STATUS_INTERACTED && (!(o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB))) { // bob-omb explodes when it gets into a cannon
                o->oAction = 4;
                o->oCannonUnk10C = 1;
                o->oCannonUnkF8 = 1;
                o->oCannonPlayerIndex = 0;
                network_send_object(o);
            } else {
                o->oInteractStatus = 0;
            }
        }
    } else {
        //cur_obj_become_intangible();
        //cur_obj_disable_rendering();
        o->oCannonUnk10C = 0;
    }
}

void opened_cannon_act_4(void) {
    if (o->oTimer == 0)
        cur_obj_play_sound_2(SOUND_OBJ_CANNON1);
    o->oPosY += 5.0f;
    o->oPosX += (f32)((o->oTimer / 2 & 1) - 0.5) * 2;
    o->oPosZ += (f32)((o->oTimer / 2 & 1) - 0.5) * 2;
    if (o->oTimer > 67) {
        o->oPosX += (f32)((o->oTimer / 2 & 1) - 0.5) * 4;
        o->oPosZ += (f32)((o->oTimer / 2 & 1) - 0.5) * 4;
        o->oAction = 6;
    }
    if (o->oCannonPlayerIndex > 0 && o->oCannonPlayerIndex < MAX_PLAYERS) {
        struct MarioState* controlledBy = &gMarioStates[o->oCannonPlayerIndex];
        if (controlledBy && controlledBy->marioObj != NULL) {
            controlledBy->marioObj->oMarioCannonObjectYaw = o->oMoveAngleYaw;
            controlledBy->marioObj->oMarioCannonInputYaw = 0;
        }
    }
}

void opened_cannon_act_6(void) {
    if (o->oTimer == 0)
        cur_obj_play_sound_2(SOUND_OBJ_CANNON2);
    if (o->oTimer < 4) {
        o->oPosX += (f32)((o->oTimer / 2 & 1) - 0.5) * 4.0f;
        o->oPosZ += (f32)((o->oTimer / 2 & 1) - 0.5) * 4.0f;
    } else {
        if (o->oTimer < 6) {
        } else {
            if (o->oTimer < 22) {
                o->oMoveAngleYaw = sins(o->oCannonUnkF4) * 0x4000 + ((s16)(o->oBehParams2ndByte << 8));
                o->oCannonUnkF4 += 0x400;
            } else if (o->oTimer < 26) {
            } else if (o->oCannonPlayerIndex >= 0 && o->oCannonPlayerIndex < MAX_PLAYERS) {
                struct MarioState* controlledBy = &gMarioStates[o->oCannonPlayerIndex];
                if (controlledBy && controlledBy->marioObj != NULL) {
                    controlledBy->marioObj->oMarioCannonObjectYaw = o->oMoveAngleYaw;
                    controlledBy->marioObj->oMarioCannonInputYaw = 0;
                }
                controlledBy->faceAngle[0] = 8192;

                o->oCannonUnkF4 = 0;
                o->oAction = 5;
            }
        }
    }
}

void opened_cannon_act_5(void) {
    if (o->oTimer == 0)
        cur_obj_play_sound_2(SOUND_OBJ_CANNON3);
    if (o->oTimer < 4) {
    } else {
        if (o->oTimer < 20) {
            o->oCannonUnkF4 += 0x400;
            o->oMoveAnglePitch = sins(o->oCannonUnkF4) * 0x2000;
        } else if (o->oTimer < 25) {
        } else {
            o->oAction = 1;
        }
    }
}

void opened_cannon_act_1(void) {
    UNUSED s32 unused;
    if (o->oCannonPlayerIndex == 0) {
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
    } else if (o->oCannonPlayerIndex >= 0 && o->oCannonPlayerIndex < MAX_PLAYERS) {
        struct MarioState* controlledBy = &gMarioStates[o->oCannonPlayerIndex];
        o->oMoveAnglePitch = 14563 + controlledBy->faceAngle[0] * -0.5f;
        if (controlledBy->marioObj != NULL) {
            o->oMoveAngleYaw = controlledBy->marioObj->oMarioCannonObjectYaw + controlledBy->marioObj->oMarioCannonInputYaw;
        }
    }
    o->oCannonUnk10C = 0;
    if (o->oCannonPlayerIndex == 0) {
        gMarioShotFromCannon = 1;
    }
}

void opened_cannon_act_2(void) {
    o->oAction = 3;
}

void opened_cannon_act_3(void) {
    UNUSED s32 unused;
    if (o->oTimer > 3) {
        o->oAction = 0;
        if (o->heldByPlayerIndex == 0) { network_send_object(o); }
    }
}

void (*sOpenedCannonActions[])(void) = { opened_cannon_act_0, opened_cannon_act_1, opened_cannon_act_2,
                                         opened_cannon_act_3, opened_cannon_act_4, opened_cannon_act_5,
                                         opened_cannon_act_6 };

u8 unused0EA1FC[] = { 2,  0,   0, 0, 0,  0,   0, 0, 63, 128, 0, 0, 2,  0,   0, 0, 65, 32,  0, 0,
                      63, 128, 0, 0, 2,  0,   0, 0, 65, 160, 0, 0, 63, 128, 0, 0, 2,  0,   0, 0,
                      65, 160, 0, 0, 63, 128, 0, 0, 8,  0,   0, 0, 65, 32,  0, 0, 63, 128, 0, 0 };

static void cannon_on_received_post(u8 fromLocalIndex) {
    // check if we're on in the cannon too
    struct MarioState* m = &gMarioStates[0];
    u8 shouldEject =  (m->action == ACT_IN_CANNON)
                   && (m->interactObj == o)
                   && gNetworkPlayers[fromLocalIndex].globalIndex < gNetworkPlayerLocal->globalIndex;

    if (shouldEject) {
        // eject the player by shooting out of the cannon weakly
        m->forwardVel = 10.0f * coss(m->faceAngle[0]);
        m->vel[1] = 10.0f * sins(m->faceAngle[0]);
        m->pos[0] += 120.0f * coss(m->faceAngle[0]) * sins(m->faceAngle[1]);
        m->pos[1] += 120.0f * sins(m->faceAngle[0]);
        m->pos[2] += 120.0f * coss(m->faceAngle[0]) * coss(m->faceAngle[1]);
        set_mario_action(m, ACT_SHOT_FROM_CANNON, 0);

        // reset things that got messed up
        m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
        reset_camera(gCamera);
        o->oCannonPlayerIndex = fromLocalIndex;
        cur_obj_become_tangible();
        cur_obj_enable_rendering();
    } else {
        o->oCannonPlayerIndex = fromLocalIndex;
    }
}

static void bhv_cannon_base_sanity_check(void) {
    // figure out if it's still in use
    u8 inUse = FALSE;
    if (o->oCannonPlayerIndex == 0) {
        inUse = (gMarioStates[0].action == ACT_IN_CANNON && gMarioStates[0].interactObj == o);
    } else {
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (!is_player_active(&gMarioStates[i])) { continue; }
            if (gMarioStates[i].action == ACT_IN_CANNON && gMarioStates[i].interactObj == o) {
                inUse = TRUE;
                break;
            }
        }
    }

    // figure out if it is visible
    u8 isVisible = (o->header.gfx.node.flags & GRAPH_RENDER_ACTIVE);

    // ensure that it is visibile when it should be
    static u8 visibilitySanity = 0;
    if (isVisible == !inUse) {
        visibilitySanity = 0;
        return;
    }

    // enforce good state if out of whack
    if (!isVisible && !inUse) {
        if (visibilitySanity++ > 15) {
            o->oAction = 0;
            o->oTimer = 0;
            visibilitySanity = 0;
        }
    }
}

void bhv_cannon_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    if ((o->oAction != 0) && (o->oCannonPlayerIndex == 0)) {
        *shouldOverride = TRUE;
        *shouldOwn = TRUE;
    }
}

void bhv_cannon_base_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->on_received_post = cannon_on_received_post;
            so->override_ownership = bhv_cannon_override_ownership;
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oPosX);
            sync_object_init_field(o, &o->oPosY);
            sync_object_init_field(o, &o->oPosZ);
            sync_object_init_field(o, &o->oCannonUnk10C);
            sync_object_init_field(o, &o->oCannonUnk10C);
            sync_object_init_field(o, &o->oCannonUnkF8);
            sync_object_init_field(o, &o->oCannonUnkF4);
        }
    }

    bhv_cannon_base_sanity_check();

    if ((o->oAction != 0) && (o->oCannonPlayerIndex != 0)) {
        cur_obj_push_mario_away_from_cylinder(220, 300);
    }

    CUR_OBJ_CALL_ACTION_FUNCTION(sOpenedCannonActions);
    if (o->oCannonUnkF8)
        o->oCannonUnkF8++;
    o->oInteractStatus = 0;
}

void bhv_cannon_barrel_loop(void) {
    struct Object *parent = o->parentObj;
    if (parent && parent->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        cur_obj_enable_rendering();
        obj_copy_pos(o, o->parentObj);
        o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
        o->oFaceAnglePitch = o->parentObj->oMoveAnglePitch;
    } else
        cur_obj_disable_rendering();
}
