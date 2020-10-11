
/**
 * Behavior for TTC spinner.
 */

/**
 * Spinner speeds on each setting.
 */
static s16 sTTCSpinnerSpeeds[] = {
    /* TTC_SPEED_SLOW    */ 200,
    /* TTC_SPEED_FAST    */ 600,
    /* TTC_SPEED_RANDOM  */ 200,
    /* TTC_SPEED_STOPPED */ 0,
};

/**
 * Update function for bhvTTCSpinner.
 */
void bhv_ttc_spinner_update(void) {
    if (!network_sync_object_initialized(o)) {
        struct SyncObject* so = network_init_object(o, 4000.0f);
        so->minUpdateRate = 5.0f;
        network_init_object_field(o, &o->oAngleVelPitch);
        network_init_object_field(o, &o->oFaceAnglePitch);
        network_init_object_field(o, &o->oTTCSpinnerDir);
        network_init_object_field(o, &o->oTTCChangeDirTimer);
    }

    o->oAngleVelPitch = sTTCSpinnerSpeeds[gTTCSpeedSetting];

    if (gTTCSpeedSetting == TTC_SPEED_RANDOM) {
        if (o->oTimer > o->oTTCChangeDirTimer) {
            o->oTTCSpinnerDir = random_sign();
            o->oTTCChangeDirTimer = random_mod_offset(30, 30, 4);
            o->oTimer = 0;
        } else if (o->oTimer > 5) {
            o->oAngleVelPitch *= o->oTTCSpinnerDir;
        } else {
            // Stop for 5 frames after changing direction
            o->oAngleVelPitch = 0;
        }
    }

    o->oFaceAnglePitch += o->oAngleVelPitch;
}
