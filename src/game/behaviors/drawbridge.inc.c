// drawbridge.c.inc

void bhv_lll_drawbridge_spawner_init(void) {
    struct Object *drawbridge[2];

    drawbridge[0] = spawn_object(o, MODEL_LLL_DRAWBRIDGE_PART, bhvLllDrawbridge);
    if (drawbridge[0] != NULL) {
        drawbridge[0]->oMoveAngleYaw = o->oMoveAngleYaw;
        drawbridge[0]->oPosX += coss(o->oMoveAngleYaw) * 640.0f;
        drawbridge[0]->oPosZ += sins(o->oMoveAngleYaw) * 640.0f;
    }

    drawbridge[1] = spawn_object(o, MODEL_LLL_DRAWBRIDGE_PART, bhvLllDrawbridge);
    if (drawbridge[1] != NULL) {
        drawbridge[1]->oMoveAngleYaw = o->oMoveAngleYaw + 0x8000;
        drawbridge[1]->oPosX += coss(o->oMoveAngleYaw) * -640.0f;
        drawbridge[1]->oPosZ += sins(o->oMoveAngleYaw) * -640.0f;
    }

    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 3000.0f);
        for (s32 i = 0; i < 2; i++) {
            if (drawbridge[i] == NULL) { continue; }
            sync_object_init_field(o, &drawbridge[i]->oFaceAngleRoll);
            sync_object_init_field(o, &drawbridge[i]->oAction);
            sync_object_init_field(o, &drawbridge[i]->oPrevAction);
            sync_object_init_field(o, &drawbridge[i]->oTimer);
        }
    }

    //o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_lll_drawbridge_spawner_loop(void) { }

void bhv_lll_drawbridge_loop(void) {

    s32 globalTimer = gGlobalTimer;

    switch (o->oAction) {
        case LLL_DRAWBRIDGE_ACT_LOWER:
            o->oFaceAngleRoll += 0x100;
            break;

        case LLL_DRAWBRIDGE_ACT_RAISE:
            o->oFaceAngleRoll -= 0x100;
            break;
    }

    if ((s16) o->oFaceAngleRoll < -0x1FFD) {
        o->oFaceAngleRoll = 0xDFFF;

        //! Because the global timer increments when the game is paused, pausing and unpausing
        //  the game at regular intervals can leave the drawbridge raised indefinitely.
        if (o->oTimer >= 51 && (globalTimer % 8) == 0) {
            o->oAction = LLL_DRAWBRIDGE_ACT_LOWER;
            cur_obj_play_sound_2(SOUND_GENERAL_BOAT_TILT1);
        }
    }

    if ((s16) o->oFaceAngleRoll >= 0) {
        o->oFaceAngleRoll = 0;

        //! Because the global timer increments when the game is paused, pausing and unpausing
        //  the game at regular intervals can leave the drawbridge lowered indefinitely.
        if (o->oTimer >= 51 && (globalTimer % 8) == 0) {
            o->oAction = LLL_DRAWBRIDGE_ACT_RAISE;
            cur_obj_play_sound_2(SOUND_GENERAL_BOAT_TILT2);
        }
    }
}
