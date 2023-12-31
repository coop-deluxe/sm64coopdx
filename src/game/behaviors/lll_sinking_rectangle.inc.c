// lll_sinking_rectangle.c.inc

void sinking_rectangular_plat_actions(f32 a0, s32 a1) {
    switch (o->oAction) {
        case 0:
            o->oAction++;
            break;
        case 1:
            o->oPosY -= sins(o->oLllWoodPieceOscillationTimer) * a0;
            o->oLllWoodPieceOscillationTimer += a1;
            break;
        case 2:
            break;
    }
}

void bhv_lll_sinking_rectangular_platform_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, &o->oLllWoodPieceOscillationTimer);
        sync_object_init_field(o, &o->oFaceAnglePitch);
    }
    f32 sp1C = 0.4f;
    s32 sp18 = 0x100;
    if (o->oMoveAngleYaw != 0)
        sinking_rectangular_plat_actions(sp1C, sp18);
    else {
        o->oFaceAnglePitch = sins(o->oLllWoodPieceOscillationTimer) * 512.0f;
        o->oLllWoodPieceOscillationTimer += 0x100;
    }
}

void bhv_lll_sinking_square_platforms_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, &o->oLllWoodPieceOscillationTimer);
    }
    f32 sp1C = 0.5f;
    s32 sp18 = 0x100;
    sinking_rectangular_plat_actions(sp1C, sp18);
}
