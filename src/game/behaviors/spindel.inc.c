// spindel.c.inc

void bhv_spindel_init(void) {
    o->oHomeY = o->oPosY;
    o->oSpindelUnkF4 = 0;
    o->oSpindelUnkF8 = 0;

    // uses standard distance-based syncing
    sync_object_init(o, 4000.0f);
    sync_object_init_field(o, o->oSpindelUnkF4);
    sync_object_init_field(o, o->oSpindelUnkF8);
    sync_object_init_field(o, o->oAngleVelPitch);
    sync_object_init_field(o, o->oMoveAnglePitch);
}

void bhv_spindel_loop(void) {
    if (o->oSpindelUnkF4 == -1) {
        if (o->oTimer == 32) {
            o->oSpindelUnkF4 = 0;
            o->oTimer = 0;
        } else {
            o->oVelZ = 0.0f;
            o->oAngleVelPitch = 0;
            return;
        }
    }

    s32 shake = 10 - o->oSpindelUnkF4;

    if (shake < 0) {
        shake *= -1;
    }

    shake -= 6;
    if (shake < 0) {
        shake = 0;
    }

    if (o->oTimer == shake + 8) {
        o->oTimer = 0;
        o->oSpindelUnkF4++;
        if (o->oSpindelUnkF4 == 20) {
            if (o->oSpindelUnkF8 == 0) {
                o->oSpindelUnkF8 = 1;
            } else {
                o->oSpindelUnkF8 = 0;
            }

            o->oSpindelUnkF4 = -1;
        }
    }

    if (shake == 4 || shake == 3) {
        shake = 4;
    } else if (shake == 2 || shake == 1) {
        shake = 2;
    } else if (shake == 0) {
        shake = 1;
    }

    if (o->oTimer < shake * 8) {
        if (o->oSpindelUnkF8 == 0) {
            o->oVelZ = 20 / shake;
            o->oAngleVelPitch = 1024 / shake;
        } else {
            o->oVelZ = -20 / shake;
            o->oAngleVelPitch = -1024 / shake;
        }

        o->oPosZ += o->oVelZ;
        o->oMoveAnglePitch += o->oAngleVelPitch;

        if (absf_2(o->oMoveAnglePitch & 0x1fff) < 800.0f && o->oAngleVelPitch != 0) {
            cur_obj_play_sound_2(SOUND_GENERAL2_SPINDEL_ROLL);
        }

        f32 yOffset = sins(o->oMoveAnglePitch * 4) * 23.0;
        if (yOffset < 0.0f) {
            yOffset *= -1.0f;
        }

        o->oPosY = o->oHomeY + yOffset;

        if (o->oTimer + 1 == shake * 8) {
            set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
        }
    }
}
