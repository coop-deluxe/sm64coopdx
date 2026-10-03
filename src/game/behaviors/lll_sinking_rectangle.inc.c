// lll_sinking_rectangle.c.inc

void sinking_rectangular_plat_actions(f32 yPosMultiplier, s32 timerIncreaseAmount) {
    switch (o->oAction) {
        case 0:
            o->oAction++;
            break;
        case 1:
            o->oPosY -= sins(o->oLllWoodPieceOscillationTimer) * yPosMultiplier;
            o->oLllWoodPieceOscillationTimer += timerIncreaseAmount;
            break;
        case 2:
            break;
    }
}

void bhv_lll_sinking_rectangular_platform_loop(void) {
    // uses standard distance-based syncing
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, o->oLllWoodPieceOscillationTimer);
        sync_object_init_field(o, o->oFaceAnglePitch);
    }
    f32 yPosMultiplier = 0.4f;
    s32 timerIncreaseAmount = 0x100;
    if (o->oMoveAngleYaw != 0) {
        sinking_rectangular_plat_actions(yPosMultiplier, timerIncreaseAmount);
    } else {
        o->oFaceAnglePitch = sins(o->oLllWoodPieceOscillationTimer) * 512.0f;
        o->oLllWoodPieceOscillationTimer += 0x100;
    }
}

void bhv_lll_sinking_square_platforms_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, o->oLllWoodPieceOscillationTimer);
    }
    f32 yPosMultiplier = 0.5f;
    s32 timerIncreaseAmount = 0x100;
    sinking_rectangular_plat_actions(yPosMultiplier, timerIncreaseAmount);
}
