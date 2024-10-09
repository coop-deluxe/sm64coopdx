// water_mist_particle.c.inc
// TODO: Is this really "mist"?

void bhv_water_mist_spawn_loop(void) {
    clear_particle_flags(0x20000);
    if (o->parentObj == NULL || o->parentObj->behavior != smlua_override_behavior(bhvMario)) {
        obj_mark_for_deletion(o);
        return;
    }
    spawn_object(o->parentObj, MODEL_MIST, bhvWaterMist);
}

void bhv_water_mist_loop(void) {
    if (o->parentObj == NULL || o->parentObj->behavior != smlua_override_behavior(bhvMario)) {
        obj_mark_for_deletion(o);
        return;
    }
    f32 sp1C;
    if (o->oTimer == 0) {
        o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
        obj_translate_xz_random(o, 10.0f);
    }
    cur_obj_move_using_fvel_and_gravity();
    o->oOpacity -= 42;
    sp1C = (254 - o->oOpacity) / 254.0 * 1.0 + 0.5; // seen this before
    cur_obj_scale(sp1C);
    if (o->oOpacity < 2)
        obj_mark_for_deletion(o);
}
