// castle_floor_trap.c.inc

void bhv_floor_trap_in_castle_loop(void) {
    u8 onPlatform = FALSE;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        onPlatform = onPlatform || (gMarioStates[i].marioObj->platform == o);
    }
    if (o->parentObj) {
        if (onPlatform) {
            o->parentObj->oInteractStatus |= INT_STATUS_TRAP_TURN;
        }
        o->oFaceAngleRoll = o->parentObj->oFaceAngleRoll;
    }
}

void bhv_castle_floor_trap_init(void) {
    struct Object *sp2C;
    sp2C = spawn_object_relative(0, -358, 0, 0, o, MODEL_CASTLE_BOWSER_TRAP, bhvFloorTrapInCastle);
    sp2C = spawn_object_relative(0, 358, 0, 0, o, MODEL_CASTLE_BOWSER_TRAP, bhvFloorTrapInCastle);
    if (sp2C == NULL) { return; }
    sp2C->oMoveAngleYaw += 0x8000;
}

void bhv_castle_floor_trap_open_detect(void) {
    if (gMarioStates[0].action == ACT_SPECIAL_EXIT_AIRBORNE
        || gMarioStates[0].action == ACT_SPECIAL_DEATH_EXIT)
        o->oAction = 4; // rotates trapdoor so it looks always open
    else {
        o->oAngleVelRoll = 0x400;
        if (o->oInteractStatus & INT_STATUS_TRAP_TURN)
            o->oAction = 1; // detects interact then opens the trapdoor
    }
}

void bhv_castle_floor_trap_open(void) {
    if (o->oTimer == 0)
        cur_obj_play_sound_2(SOUND_GENERAL_CASTLE_TRAP_OPEN);
    o->oAngleVelRoll -= 0x100;
    o->oFaceAngleRoll += o->oAngleVelRoll;
    if (o->oFaceAngleRoll < -0x4000) {
        o->oFaceAngleRoll = -0x4000;
        o->oAction = 2; // after opening is done, enable close detection
    }
}

void bhv_castle_floor_trap_close_detect(void) {
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return; }
    s32 distanceToPlayer = dist_between_objects(o, player);
    if (distanceToPlayer > 1000.0f)
        o->oAction = 3; // close trapdoor
}

void bhv_castle_floor_trap_close(void) {
    o->oFaceAngleRoll += 0x400;
    if (o->oFaceAngleRoll > 0) {
        o->oFaceAngleRoll = 0;
        o->oAction = 0; // after closing, reloads open detection
        o->oInteractStatus &= ~INT_STATUS_TRAP_TURN;
    }
}

void bhv_castle_floor_trap_rotate(void) {
    o->oFaceAngleRoll = -0x3C00;
}

void bhv_castle_floor_trap_loop(void) {
    UNUSED s32 unused[3];
    switch (o->oAction) {
        case 0:
            bhv_castle_floor_trap_open_detect();
            break;
        case 1:
            bhv_castle_floor_trap_open();
            break;
        case 2:
            bhv_castle_floor_trap_close_detect();
            break;
        case 3:
            bhv_castle_floor_trap_close();
            break;
        case 4:
            bhv_castle_floor_trap_rotate();
            break;
    }
}
