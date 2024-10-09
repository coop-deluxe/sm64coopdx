// lll_sinking_rock_block.c.inc

void bhv_lll_sinking_rock_block_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, &o->oSinkWhenSteppedOnUnk104);
        sync_object_init_field(o, &o->oGraphYOffset);
    }
    lll_octagonal_mesh_find_y_offset(&o->oSinkWhenSteppedOnUnk104, &o->oSinkWhenSteppedOnUnk108, 124, -110);
    o->oGraphYOffset = 0.0f;
    o->oPosY = o->oHomeY + o->oSinkWhenSteppedOnUnk108;
}
