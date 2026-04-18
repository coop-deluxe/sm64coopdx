// lll_rotating_hex_flame.c.inc

void bhv_lll_rotating_hex_flame_loop(void) {
    f32 relativePosX = o->oLllRotatingHexFlameUnkF4;
    f32 relativePosY = o->oLllRotatingHexFlameUnkF8;
    f32 relativePosZ = o->oLllRotatingHexFlameUnkFC;

    if (o->parentObj) {
        cur_obj_set_pos_relative(o->parentObj, relativePosX, relativePosY, relativePosZ);
        o->oPosY = o->parentObj->oPosY + 100.0f;
        if (o->parentObj->oAction == 3) {
            obj_mark_for_deletion(o);
        }
    } else {
        obj_mark_for_deletion(o);
    }
}

void fire_bar_spawn_flames(s16 a0) {
    f32 xOffset = sins(a0) * 200.0f;
    f32 zOffset = coss(a0) * 200.0f;
    s32 amount = (o->oBehParams2ndByte == 0) ? 4 : 3;
    for (s32 i = 0; i < amount; i++) {
        struct Object *lllRotatingHexFlameObj = spawn_object(o, MODEL_RED_FLAME, bhvLllRotatingHexFlame);
        if (lllRotatingHexFlameObj != NULL) {
            lllRotatingHexFlameObj->oLllRotatingHexFlameUnkF4 += xOffset;
            lllRotatingHexFlameObj->oLllRotatingHexFlameUnkF8 = o->oPosY - 200.0f;
            lllRotatingHexFlameObj->oLllRotatingHexFlameUnkFC += zOffset;
            obj_scale_xyz(lllRotatingHexFlameObj, 6.0f, 6.0f, 6.0f);
        }
        xOffset += sins(a0) * 150.0f;
        zOffset += coss(a0) * 150.0f;
    }
}

void fire_bar_act_0(void) {
    o->oAction = 1;
}

void fire_bar_act_1(void) {
    fire_bar_spawn_flames(0);
    fire_bar_spawn_flames(-0x8000);
    o->oAngleVelYaw = 0;
    o->oMoveAngleYaw = 0;
    o->oAction = 2;
}

void fire_bar_act_2(void) {
    o->oAngleVelYaw = -0x100;
    o->oMoveAngleYaw += o->oAngleVelYaw;
}

void fire_bar_act_3(void) {
    o->oAction = 0;
}

void (*sRotatingCwFireBarsActions[])(void) = { fire_bar_act_0, fire_bar_act_1,
                                               fire_bar_act_2, fire_bar_act_3 };

void bhv_lll_rotating_block_fire_bars_loop(void) {
    // uses standard distance-based syncing
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, o->oAngleVelYaw);
    }
    CUR_OBJ_CALL_ACTION_FUNCTION(sRotatingCwFireBarsActions);
    if (o->oBehParams2ndByte == 0) {
        load_object_collision_model();
    }
}
