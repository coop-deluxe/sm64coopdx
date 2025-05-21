// jumping_box.c.inc

struct ObjectHitbox sJumpingBoxHitbox = {
    .interactType = INTERACT_GRABBABLE,
    .downOffset = 20,
    .damageOrCoinValue = 0,
    .health = 1,
    .numLootCoins = 5,
    .radius = 150,
    .height = 250,
    .hurtboxRadius = 150,
    .hurtboxHeight = 250,
};

void jumping_box_act_0(void) {
    if (o->oSubAction == 0) {
        if (o->oJumpingBoxUnkF8-- < 0)
            o->oSubAction++;
        if (o->oTimer > o->oJumpingBoxUnkF4) {
            o->oVelY = random_float() * 5.0f + 15.0f;
            o->oSubAction++;
        }
    } else if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
        o->oSubAction = 0;
        o->oJumpingBoxUnkF8 = random_float() * 60.0f + 30.0f;
    }
}

void jumping_box_act_1(void) {
    if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_IN_WATER | OBJ_MOVE_LANDED)) {
        obj_mark_for_deletion(o);
        spawn_mist_particles();
    }
}

void (*sJumpingBoxActions[])(void) = { jumping_box_act_0, jumping_box_act_1 };

void jumping_box_free_update(void) {
    cur_obj_set_model(smlua_model_util_load(E_MODEL_BREAKABLE_BOX));
    cur_obj_scale(0.5f);
    obj_set_hitbox(o, &sJumpingBoxHitbox);
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
    CUR_OBJ_CALL_ACTION_FUNCTION(sJumpingBoxActions);
}

void bhv_jumping_box_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 500.0f);
        sync_object_init_field(o, &o->oJumpingBoxUnkF4);
    }

    switch (o->oHeldState) {
        case HELD_FREE:
            jumping_box_free_update();
            break;
        case HELD_HELD:
            if (o->heldByPlayerIndex < MAX_PLAYERS) {
                obj_copy_pos(o, gMarioStates[o->heldByPlayerIndex].marioObj);
            }
            cur_obj_set_model(smlua_model_util_load(E_MODEL_BREAKABLE_BOX_SMALL));
            cur_obj_unrender_and_reset_state(-1, 0);
            break;
        case HELD_THROWN:
            cur_obj_get_thrown_or_placed(40.0f, 20.0f, 1);
            break;
        case HELD_DROPPED:
            cur_obj_get_dropped();
            o->oAction = 1;
            break;
    }
    if (o->oInteractStatus & INT_STATUS_STOP_RIDING) {
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        obj_explode_and_spawn_coins(46.0f, 1);
    }
    o->oInteractStatus = 0;
}
