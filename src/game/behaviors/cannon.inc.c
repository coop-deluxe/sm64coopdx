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

    struct Object *player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

    if (distanceToPlayer < 500.0f) {
        //cur_obj_become_tangible();
        //cur_obj_enable_rendering();
        if (player == gMarioStates[0].marioObj) {
            if (o->oInteractStatus & INT_STATUS_INTERACTED && (!(o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB))) { // bob-omb explodes when it gets into a cannon
                o->oAction = 4;
                o->oCannonUnk10C = 1;
                o->oCannonUnkF8 = 1;
                o->oCannonPlayerIndex = network_global_index_from_local(0);
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
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(SOUND_OBJ_CANNON1);
    }
    o->oPosY += 5.0f;
    o->oPosX += (f32)((o->oTimer / 2 & 1) - 0.5) * 2;
    o->oPosZ += (f32)((o->oTimer / 2 & 1) - 0.5) * 2;
    if (o->oTimer > 67) {
        o->oPosX += (f32)((o->oTimer / 2 & 1) - 0.5) * 4;
        o->oPosZ += (f32)((o->oTimer / 2 & 1) - 0.5) * 4;
        o->oAction = 6;
        network_send_object(o);
    }
    int localIndex = network_local_index_from_global(o->oCannonPlayerIndex);
    if (localIndex > 0 && localIndex < MAX_PLAYERS) {
        struct MarioState *controlledBy = &gMarioStates[localIndex];
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
        if (o->oTimer >= 6) {
            if (o->oTimer < 22) {
                o->oMoveAngleYaw = sins(o->oCannonUnkF4) * 0x4000 + ((s16)(o->oBehParams2ndByte << 8));
                o->oCannonUnkF4 += 0x400;
            } else if (o->oTimer >= 26 && o->oCannonPlayerIndex >= 0 && o->oCannonPlayerIndex < MAX_PLAYERS) {
                struct MarioState* controlledBy = &gMarioStates[network_local_index_from_global(o->oCannonPlayerIndex)];
                if (controlledBy && controlledBy->marioObj != NULL) {
                    controlledBy->marioObj->oMarioCannonObjectYaw = o->oMoveAngleYaw;
                    controlledBy->marioObj->oMarioCannonInputYaw = 0;
                }
                controlledBy->faceAngle[0] = 8192;

                o->oCannonUnkF4 = 0;
                o->oAction = 5;
                network_send_object(o);
            }
        }
    }
}

void opened_cannon_act_5(void) {
    if (o->oTimer == 0)
        cur_obj_play_sound_2(SOUND_OBJ_CANNON3);
    if (o->oTimer >= 4) {
        if (o->oTimer < 20) {
            o->oCannonUnkF4 += 0x400;
            o->oMoveAnglePitch = sins(o->oCannonUnkF4) * 0x2000;
        } else if (o->oTimer >= 25) {
            o->oAction = 1;
            network_send_object(o);
        }
    }
}

void opened_cannon_act_1(void) {
    if (o->oCannonPlayerIndex == network_global_index_from_local(0)) {
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
    } else if (o->oCannonPlayerIndex >= 0 && o->oCannonPlayerIndex < MAX_PLAYERS) {
        struct MarioState* controlledBy = &gMarioStates[network_local_index_from_global(o->oCannonPlayerIndex)];
        o->oMoveAnglePitch = 14563 + controlledBy->faceAngle[0] * -0.5f;
        if (controlledBy->marioObj != NULL) {
            o->oMoveAngleYaw = controlledBy->marioObj->oMarioCannonObjectYaw + controlledBy->marioObj->oMarioCannonInputYaw;
        }
    }
    o->oCannonUnk10C = 0;
    if (network_local_index_from_global(o->oCannonPlayerIndex) == 0) {
        gMarioShotFromCannon = 1;
    }
}

void opened_cannon_act_2(void) {
    o->oAction = 3;
}

void opened_cannon_act_3(void) {
    if (o->oTimer > 3) {
        o->oAction = 0;
        if (o->heldByPlayerIndex == 0) { network_send_object(o); }
    }
}

void (*sOpenedCannonActions[])(void) = { opened_cannon_act_0, opened_cannon_act_1, opened_cannon_act_2,
                                         opened_cannon_act_3, opened_cannon_act_4, opened_cannon_act_5,
                                         opened_cannon_act_6 };

static void eject_mario_if_necessary() {
    // check if we should be ejected or not
    struct MarioState* m = &gMarioStates[0];
    u8 shouldEject =  (m->action == ACT_IN_CANNON)
                   && (m->interactObj == o)
                   && gNetworkPlayers[0].globalIndex != o->oCannonPlayerIndex;

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
        cur_obj_become_tangible();
        cur_obj_enable_rendering();
    }
}

static void bhv_cannon_base_sanity_check(void) {
    eject_mario_if_necessary();

    // figure out if it's still in use
    struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->oCannonPlayerIndex)];
    bool inUse = (is_player_active(marioState) && marioState->action == ACT_IN_CANNON && marioState->interactObj == o);

    static u8 sSanityTimer = 0;

    // if it isn't in use and at least 15 frames, or half a second, has passed, then reset the cannon for the local player
    if (!inUse && o->oAction != 0 && sSanityTimer++ >= 15) {
        o->oAction = 0;
        o->oTimer = 0;
    } else if (inUse || o->oAction == 0) {
        sSanityTimer = 0;
    }
}

void bhv_cannon_override_ownership(u8 *shouldOverride, u8 *shouldOwn) {
    struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->oCannonPlayerIndex)];
    if (o->oAction != 0 && is_player_active(marioState)) {
        *shouldOverride = TRUE;
        *shouldOwn = marioState->playerIndex == 0;
    }
}

void bhv_cannon_base_loop(void) {
    // syncing here works using events, the cannon player index can be used as a sanity check for
    // if mario should be in the cannon or not
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->override_ownership = bhv_cannon_override_ownership;
            sync_object_init_field(o, o->oAction);
            sync_object_init_field(o, o->oPrevAction);
            sync_object_init_field(o, o->oTimer);
            sync_object_init_field(o, o->oPosX);
            sync_object_init_field(o, o->oPosY);
            sync_object_init_field(o, o->oPosZ);
            // oCannonUnk10C is only set, not used
            sync_object_init_field(o, o->oCannonUnk10C);
            // oCannonUnkF8 is only set, not used
            sync_object_init_field(o, o->oCannonUnkF8);
            sync_object_init_field(o, o->oCannonUnkF4);
            sync_object_init_field(o, o->oCannonPlayerIndex);
        }
    }

    if ((o->oAction != 0) && (network_local_index_from_global(o->oCannonPlayerIndex) != 0 || gMarioState->action != ACT_IN_CANNON)) {
        cur_obj_push_mario_away_from_cylinder(220, 300);
    }

    CUR_OBJ_CALL_ACTION_FUNCTION(sOpenedCannonActions);

    bhv_cannon_base_sanity_check();

    if (o->oCannonUnkF8) o->oCannonUnkF8++;
    o->oInteractStatus = 0;
}

void bhv_cannon_barrel_loop(void) {
    struct Object *parent = o->parentObj;
    if (parent && parent->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        cur_obj_enable_rendering();
        obj_copy_pos(o, o->parentObj);
        o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
        o->oFaceAnglePitch = o->parentObj->oMoveAnglePitch;
    } else {
        cur_obj_disable_rendering();
    }
}
