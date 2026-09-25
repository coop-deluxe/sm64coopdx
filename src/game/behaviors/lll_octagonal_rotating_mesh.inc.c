// lll_octagonal_rotating_mesh.c.inc

static s16 sLllOctagonalMeshAction0[] = { 2,  30,      0x4000, 0, 1,   220, 900, 30, 1,  30, 0,   -30, 2,
                     30, -0x4000, 0,      1, 220, 900, 30,  1,  30, 0,  -30, 3,   0 };
static s16 sLllOctagonalMeshAction1[] = { 4,  0,      0, 0, 1,   475, 900, 30, 1,  30, 0,   -30, 2,
                     30, 0x8000, 0, 1, 475, 900, 30,  1,  30, 0,  -30, 3,   0 };
static s16 *sLllOctagonalMeshActionList[] = { sLllOctagonalMeshAction0, sLllOctagonalMeshAction1 };


s32 lll_octagonal_mesh_move(s16 *actionTable, s32 actionOffset) {
    if (!BHV_ARR_CHECK(sLllOctagonalMeshAction0, actionOffset, s16)) { return 0; }
    switch (actionTable[actionOffset]) {
        case 4:
            o->oMoveAngleYaw = actionTable[actionOffset + 2];
            o->oForwardVel = actionTable[actionOffset + 3] / 100.0f;
            if (cur_obj_is_mario_on_platform()) {
                actionOffset += 4;
                o->oTimer = 0;
            }
            break;
        case 2:
            o->oMoveAngleYaw = actionTable[actionOffset + 2];
            o->oForwardVel = actionTable[actionOffset + 3] / 100.0f;
            if (o->oTimer > actionTable[actionOffset + 1]) {
                actionOffset += 4;
                o->oTimer = 0;
            }
            break;
        case 1:
            approach_f32_signed(&o->oForwardVel, actionTable[actionOffset + 2] / 100.0f, actionTable[actionOffset + 3] / 100.0f);
            if (o->oTimer > actionTable[actionOffset + 1]) {
                actionOffset += 4;
                o->oTimer = 0;
            }
            break;
        case 3:
            o->oForwardVel = 0.0f;
            actionOffset = 0;
            break;
    }
    return actionOffset;
}

s32 lll_octagonal_mesh_find_y_offset(s32 *standTimer, f32 *posOffset, s32 standTimerInc, s32 moveDownAmount) {
    if (cur_obj_is_any_player_on_platform()) {
        if (standTimer[0] < 0x4000) {
            standTimer[0] += standTimerInc;
        } else {
            standTimer[0] = 0x4000;
        }
    } else {
        if (standTimer[0] > 0) {
            standTimer[0] -= standTimerInc;
        } else {
            standTimer[0] = 0;
        }
    }

    posOffset[0] = sins(standTimer[0]) * moveDownAmount;
    return standTimer[0] == 0 || standTimer[0] == 0x4000;
}

void bhv_lll_moving_octagonal_mesh_platform_loop(void) {
    // uses standard distance-based syncing
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, o->oHorizontalMovementUnkF8);
        sync_object_init_field(o, o->oHorizontalMovementUnkF4);
        sync_object_init_field(o, o->oHorizontalMovementUnk100);
        sync_object_init_field(o, o->oForwardVel);
    }
    if (o->oAction == 0) {
        o->oHorizontalMovementUnkF8 = 0;
        o->oAction++;
    } else if (BHV_ARR_CHECK(sLllOctagonalMeshActionList, o->oBehParams2ndByte, s16*)) {
        o->oHorizontalMovementUnkF8 = lll_octagonal_mesh_move(sLllOctagonalMeshActionList[o->oBehParams2ndByte], o->oHorizontalMovementUnkF8);
    }
    print_debug_top_down_objectinfo("number %d\n", o->oHorizontalMovementUnkF8);
    cur_obj_move_using_fvel_and_gravity();
    if (lll_octagonal_mesh_find_y_offset(&o->oHorizontalMovementUnk104, &o->oHorizontalMovementUnk108, 0x400, -80)) {
        o->oHorizontalMovementUnkF4 += 0x800;
        o->oHorizontalMovementUnk100 -= sins(o->oHorizontalMovementUnkF4) * 2;
    }
    o->oPosY = o->oHorizontalMovementUnk100 + o->oHomeY + o->oHorizontalMovementUnk108;
}
