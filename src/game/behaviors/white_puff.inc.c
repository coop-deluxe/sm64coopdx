// white_puff.c.inc

void bhv_white_puff_1_loop(void) {
    if (o->oTimer == 0) {
        obj_translate_xz_random(o, 40.0f);
        o->oPosY += 30.0f;
    }
    cur_obj_scale(o->oTimer * 0.5f + 0.1f);
    o->oOpacity = 50;
    cur_obj_move_using_fvel_and_gravity();
    if (o->oTimer > 4)
        obj_mark_for_deletion(o);
}

void bhv_white_puff_2_loop(void) {
    if (o->oTimer == 0)
        obj_translate_xz_random(o, 40.0f);
}
