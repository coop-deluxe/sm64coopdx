
struct ObjectHitbox sRecoveryHeartHitbox = {
    .interactType = 0,
    .downOffset = 0,
    .damageOrCoinValue = 0,
    .health = 0,
    .numLootCoins = 0,
    .radius = 50,
    .height = 50,
    .hurtboxRadius = 50,
    .hurtboxHeight = 50,
};

void bhv_recovery_heart_loop(void) {
    u8 collided = FALSE;
    obj_set_hitbox(o, &sRecoveryHeartHitbox);

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (!gMarioStates[i].visibleToEnemies) { continue; }
        if (obj_check_if_collided_with_object(o, gMarioStates[i].marioObj)) { collided = TRUE; }
    }

    if (collided) {
        if (o->oSpinningHeartPlayedSound == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_HEART_SPIN);
            o->oSpinningHeartPlayedSound += 1;
        }

        struct MarioState* marioState = nearest_interacting_mario_state_to_object(o);
        if (marioState) {
            o->oAngleVelYaw = (s32)(200.0f * marioState->forwardVel) + 1000;
        }
    } else {
        o->oSpinningHeartPlayedSound = 0;

        if ((o->oAngleVelYaw -= 50) < 400) {
            o->oAngleVelYaw = 400;
            o->oSpinningHeartTotalSpin = 0;
        }
    }

    if ((o->oSpinningHeartTotalSpin += o->oAngleVelYaw) >= 0x10000) {

        struct MarioState* nearestInteractingState = nearest_interacting_mario_state_to_object(o);
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (!gMarioStates[i].visibleToEnemies) { continue; }
            if (!is_player_active(&gMarioStates[i])) { continue; }
            if (&gMarioStates[i] == nearestInteractingState) {
                gMarioStates[i].healCounter += 4;
            }
        }
        o->oSpinningHeartTotalSpin -= 0x10000;
    }

    o->oFaceAngleYaw += o->oAngleVelYaw;
}
