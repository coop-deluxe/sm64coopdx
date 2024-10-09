// bowser_bomb.c.inc

static u32 networkBowserBombHit = 0;

static void bhv_bowser_bomb_hit_player(void) {
    if (networkBowserBombHit == 0) {
        networkBowserBombHit = o->oSyncID;
        network_send_object(o);
    }
    networkBowserBombHit = 0;

    o->oInteractStatus &= ~INT_STATUS_INTERACTED;
    spawn_object(o, smlua_model_util_load(E_MODEL_EXPLOSION), bhvExplosion);
    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

static void bhv_bowser_bomb_interacted(void) {
    if (networkBowserBombHit == 0) {
        networkBowserBombHit = -o->oSyncID;
        network_send_object(o);
    }
    networkBowserBombHit = 0;

    spawn_object(o, smlua_model_util_load(E_MODEL_BOWSER_FLAMES), bhvBowserBombExplosion);
    create_sound_spawner(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION);
    set_camera_shake_from_point(SHAKE_POS_LARGE, o->oPosX, o->oPosY, o->oPosZ);
    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_bowser_bomb_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        networkBowserBombHit = 0;
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->syncDeathEvent = FALSE;
            sync_object_init_field(o, &networkBowserBombHit);
        }
    }

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;

    if (networkBowserBombHit == o->oSyncID || (marioState && marioState->playerIndex == 0 && player && obj_check_if_collided_with_object(o, player) == 1)) {
        bhv_bowser_bomb_hit_player();
    }

    if (networkBowserBombHit == -o->oSyncID || o->oInteractStatus & INT_STATUS_HIT_MINE) {
        bhv_bowser_bomb_interacted();
    }

    set_object_visibility(o, 7000);
}

void bhv_bowser_bomb_explosion_loop(void) {
    struct Object *mineSmoke;

    cur_obj_scale((f32) o->oTimer / 14.0f * 9.0 + 1.0);
    if ((o->oTimer % 4 == 0) && (o->oTimer < 20)) {
        mineSmoke = spawn_object(o, smlua_model_util_load(E_MODEL_BOWSER_SMOKE), bhvBowserBombSmoke);
        if (mineSmoke != NULL) {
            mineSmoke->oPosX += random_float() * 600.0f - 400.0f;
            mineSmoke->oPosZ += random_float() * 600.0f - 400.0f;
            mineSmoke->oVelY += random_float() * 10.0f;
        }
    }

    if (o->oTimer % 2 == 0)
        o->oAnimState++;
    if (o->oTimer == 28)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_bowser_bomb_smoke_loop(void) {
    cur_obj_scale((f32) o->oTimer / 14.0f * 9.0 + 1.0);
    if (o->oTimer % 2 == 0)
        o->oAnimState++;

    o->oOpacity -= 10;
    if (o->oOpacity < 10)
        o->oOpacity = 0;

    o->oPosY += o->oVelY;

    if (o->oTimer == 28)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}
