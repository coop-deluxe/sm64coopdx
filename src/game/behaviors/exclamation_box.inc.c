// exclamation_box.c.inc

struct ObjectHitbox sExclamationBoxHitbox = {
    /* interactType: */ INTERACT_BREAKABLE,
    /* downOffset: */ 5,
    /* damageOrCoinValue: */ 0,
    /* health: */ 1,
    /* numLootCoins: */ 0,
    /* radius: */ 40,
    /* height: */ 30,
    /* hurtboxRadius: */ 40,
    /* hurtboxHeight: */ 30,
};

void bhv_rotating_exclamation_box_loop(void) {
    if (!o->parentObj || o->parentObj->oAction != 1)
        obj_mark_for_deletion(o);
}

void exclamation_box_act_0(void) {
    o->oExclamationBoxForce = FALSE;
    if (o->oBehParams2ndByte < 3) {
        o->oAnimState = o->oBehParams2ndByte;
        if ((save_file_get_flags() & BHV_ARR(D_8032F0C0, o->oBehParams2ndByte, s32))
            || ((o->oBehParams >> 24) & 0xFF) != 0)
            o->oAction = 2;
        else
            o->oAction = 1;
    } else {
        o->oAnimState = 3;
        o->oAction = 2;
    }
}

void exclamation_box_act_1(void) {
    cur_obj_become_intangible();
    if (o->oTimer == 0) {
        spawn_object(o, smlua_model_util_load(E_MODEL_EXCLAMATION_POINT), bhvRotatingExclamationMark);
        cur_obj_set_model(smlua_model_util_load(E_MODEL_EXCLAMATION_BOX_OUTLINE));
    }
    if ((save_file_get_flags() & BHV_ARR(D_8032F0C0, o->oBehParams2ndByte, s32))
        || ((o->oBehParams >> 24) & 0xFF) != 0) {
        o->oAction = 2;
        cur_obj_set_model(smlua_model_util_load(E_MODEL_EXCLAMATION_BOX));
    }
}

void exclamation_box_act_2(void) {
    obj_set_hitbox(o, &sExclamationBoxHitbox);
    if (o->oTimer == 0) {
        cur_obj_unhide();
        cur_obj_become_tangible();
        o->oInteractStatus = 0;
        o->oPosY = o->oHomeY;
        o->oGraphYOffset = 0.0f;
    }

    u8 isNearest = (nearest_mario_state_to_object(o) == &gMarioStates[0]);
    if (o->oExclamationBoxForce || isNearest) {
        if (o->oExclamationBoxForce || (isNearest && cur_obj_was_attacked_or_ground_pounded())) {
            if (!o->oExclamationBoxForce) {
                o->oExclamationBoxForce = TRUE;
                network_send_object(o);
                o->oExclamationBoxForce = FALSE;
            }
            cur_obj_become_intangible();
            o->oExclamationBoxUnkFC = 0x4000;
            o->oVelY = 30.0f;
            o->oGravity = -8.0f;
            o->oFloorHeight = o->oPosY;
            o->oAction = 3;
            queue_rumble_data_object(o, 5, 80);
        }
    }
    load_object_collision_model();
}

void exclamation_box_act_3(void) {
    UNUSED s32 unused;
    cur_obj_move_using_fvel_and_gravity();
    if (o->oVelY < 0.0f) {
        o->oVelY = 0.0f;
        o->oGravity = 0.0f;
    }
    o->oExclamationBoxUnkF8 = (sins(o->oExclamationBoxUnkFC) + 1.0) * 0.3 + 0.0;
    o->oExclamationBoxUnkF4 = (-sins(o->oExclamationBoxUnkFC) + 1.0) * 0.5 + 1.0;
    o->oGraphYOffset = (-sins(o->oExclamationBoxUnkFC) + 1.0) * 26.0;
    o->oExclamationBoxUnkFC += 0x1000;
    o->header.gfx.scale[0] = o->oExclamationBoxUnkF4 * 2.0f;
    o->header.gfx.scale[1] = o->oExclamationBoxUnkF8 * 2.0f;
    o->header.gfx.scale[2] = o->oExclamationBoxUnkF4 * 2.0f;
    if (o->oTimer == 7)
        o->oAction = 4;
}

static s32 exclamation_replace_model(struct MarioState* m, s32 model) {
    if (!m) { return model; }
    switch (model) {
        case MODEL_MARIOS_CAP:              return m->character->capModelId;
        case MODEL_MARIOS_METAL_CAP:        return m->character->capMetalModelId;
        case MODEL_MARIOS_WING_CAP:         return m->character->capWingModelId;
        case MODEL_MARIOS_WINGED_METAL_CAP: return m->character->capMetalWingModelId;
        default:                            return model;
    }
}

void exclamation_box_spawn_contents(struct ExclamationBoxContent *content, u8 itemId) {
    if (content == NULL) { return; }
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    struct Object *spawnedObject = NULL;

    if (o->oExclamationBoxForce) {
        return;
    }

    for (u8 i = 0; i < gExclamationBoxSize; i++) {
        if (itemId == content->id) {
            s32 model = exclamation_replace_model(marioState, smlua_model_util_load(content->model));

            spawnedObject = spawn_object(o, model, get_behavior_from_id(content->behavior));
            if (spawnedObject != NULL) {
                spawnedObject->oVelY = 20.0f;
                spawnedObject->oForwardVel = 3.0f;
                if (player) {
                    spawnedObject->oMoveAngleYaw = player->oMoveAngleYaw;
                    spawnedObject->globalPlayerIndex = player->globalPlayerIndex;
                }
            }
            o->oBehParams |= content->firstByte << 24;
            if (content->model == E_MODEL_STAR)
                o->oFlags |= OBJ_FLAG_PERSISTENT_RESPAWN;

            // send non-star spawn events
            // stars cant be sent here due to jankiness in oBehParams
            if (content->behavior != get_id_from_behavior(smlua_override_behavior(bhvSpawnedStar)) && spawnedObject != NULL) {
                // hack: Sync everything
                sync_object_set_id(spawnedObject);
                struct SyncObject* so = sync_object_get(spawnedObject->oSyncID);
                so->extendedModelId = content->model;

                struct Object* spawn_objects[] = { spawnedObject };
                u32 models[] = { model };
                network_send_spawn_objects(spawn_objects, models, 1);
            }
            break;
        }
        content++;
    }
}

void exclamation_box_act_4(void) {
    exclamation_box_spawn_contents(gExclamationBoxContents, o->oBehParams2ndByte);
    spawn_mist_particles_variable(0, 0, 46.0f);
    spawn_triangle_break_particles(20, 139, 0.3f, o->oAnimState);
    create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
    u8 threshold = gBehaviorValues.RespawnShellBoxes ? 3 : 2;
    if (o->oBehParams2ndByte <= threshold) {
        o->oAction = 5;
        cur_obj_hide();
    } else {
        o->oAction = 6;
        cur_obj_become_intangible();
        cur_obj_hide();
    }
}

void exclamation_box_act_5(void) {
    o->oExclamationBoxForce = FALSE;
    if (o->oTimer > 300) {
        o->oAction = 2;
        sync_object_forget_last_reliable_packet(o->oSyncID);
    }
}
void exclamation_box_act_6(void) {
    o->oExclamationBoxForce = FALSE;
    if (o->oTimer > 1000)
        obj_mark_for_deletion(o);
}

void (*sExclamationBoxActions[])(void) = { exclamation_box_act_0, exclamation_box_act_1,
                                           exclamation_box_act_2, exclamation_box_act_3,
                                           exclamation_box_act_4, exclamation_box_act_5,
                                           exclamation_box_act_6 };

void bhv_exclamation_box_init(void) {
    struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    if (so) {
        so->syncDeathEvent = FALSE;
        sync_object_init_field(o, &o->oExclamationBoxForce);
        sync_object_init_field(o, &o->areaTimer);
    }

    o->areaTimerType = AREA_TIMER_TYPE_MAXIMUM;
    o->areaTimer = 0;
    o->areaTimerDuration = 300;
}

void bhv_exclamation_box_loop(void) {
    cur_obj_scale(2.0f);
    CUR_OBJ_CALL_ACTION_FUNCTION(sExclamationBoxActions);
}
