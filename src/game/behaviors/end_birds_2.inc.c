// end_birds_2.inc.c

void bhv_end_birds_2_loop(void) {
    Vec3f pos;
    f32 dist;
    s16 pitch, yaw;

    gCurrentObject->oForwardVel = (random_float() * 10.f) + 25.f;

    switch (gCurrentObject->oAction) {
        case 0:
            cur_obj_scale(0.7f);
            gCurrentObject->oAction += 1;
            break;
        case 1:
            vec3f_get_dist_and_angle(gCamera->pos, gCamera->focus, &dist, &pitch, &yaw);
            yaw += 0x1000;
            pitch += 0; // nice work, Nintendo
            vec3f_set_dist_and_angle(gCamera->pos, pos, 14000.f, pitch, yaw);
            obj_rotate_towards_point(gCurrentObject, pos, 0, 0, 8, 8);

            if ((gCurrentObject->oEndBirdUnk104 == 0.f) && (gCurrentObject->oTimer == 0)) {
                cur_obj_play_sound_2(SOUND_GENERAL_BIRDS_FLY_AWAY);
            }
            break;
    }

    cur_obj_set_pos_via_transform();
}
