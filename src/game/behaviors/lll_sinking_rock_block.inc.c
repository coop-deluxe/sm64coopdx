// lll_sinking_rock_block.c.inc

void bhv_lll_sinking_rock_block_loop(void) {
    if (!network_sync_object_initialized(o)) {
        network_init_object(o, 1000.0f);
        network_init_object_field(o, &o->oSinkWhenSteppedOnUnk104);
        network_init_object_field(o, &o->oGraphYOffset);
    }
    lll_octagonal_mesh_find_y_offset(&o->oSinkWhenSteppedOnUnk104, &o->oSinkWhenSteppedOnUnk108, 124, -110);
    o->oGraphYOffset = 0.0f;
    o->oPosY = o->oHomeY + o->oSinkWhenSteppedOnUnk108;
}
