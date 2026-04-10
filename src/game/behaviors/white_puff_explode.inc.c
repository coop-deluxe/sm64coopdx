// white_puff_explode.c.inc

void bhv_white_puff_exploding_loop(void) {
    f32 newScale;
    if (o->oTimer == 0) {
        cur_obj_compute_vel_xz();
        o->oWhitePuffScale = o->header.gfx.scale[0];
        switch (o->oBehParams2ndByte) {
            case 2:
                o->oOpacity = 254;
                o->oWhitePuffSetOpacity = -21;
                o->oWhitePuffSetLarger = 0;
                break;
            case 3:
                o->oOpacity = 254;
                o->oWhitePuffSetOpacity = -13;
                o->oWhitePuffSetLarger = 1;
                break;
        }
    }
    cur_obj_move_using_vel_and_gravity();
    cur_obj_apply_drag_xz(o->oDragStrength);
    if (o->oVelY > 100.0f)
        o->oVelY = 100.0f;
    if (o->oTimer > 20)
        obj_mark_for_deletion(o);
    if (o->oOpacity) {
        o->oOpacity += o->oWhitePuffSetOpacity;
        if (o->oOpacity < 2)
            obj_mark_for_deletion(o);
        if (o->oWhitePuffSetLarger)
            newScale = o->oWhitePuffScale * ((254 - o->oOpacity) / 254.0);
        else
            newScale = o->oWhitePuffScale * (o->oOpacity / 254.0);
        cur_obj_scale(newScale);
    }
}
