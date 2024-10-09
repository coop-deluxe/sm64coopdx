// koopa_shell.c.inc

struct ObjectHitbox sKoopaShellHitbox = {
    /* interactType: */ INTERACT_KOOPA_SHELL,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 4,
    /* health: */ 1,
    /* numLootCoins: */ 1,
    /* radius: */ 50,
    /* height: */ 50,
    /* hurtboxRadius: */ 50,
    /* hurtboxHeight: */ 50,
};

void koopa_shell_spawn_water_drop(void) {
    UNUSED s32 unused;
    struct Object *drop;
    spawn_object(o, MODEL_WAVE_TRAIL, bhvObjectWaveTrail);
    if (o->heldByPlayerIndex < MAX_PLAYERS) {
        if (gMarioStates[o->heldByPlayerIndex].forwardVel > 10.0f) {
            drop = spawn_object_with_scale(o, MODEL_WHITE_PARTICLE_SMALL, bhvWaterDroplet, 1.5f);
            if (drop != NULL) {
                drop->oVelY = random_float() * 30.0f;
                obj_translate_xz_random(drop, 110.0f);
            }
        }
    }
}

void bhv_koopa_shell_flame_loop(void) {
    if (o->oTimer == 0) {
        o->oMoveAngleYaw = random_u16();
        o->oVelY = random_float() * 30.0f;
        o->oGravity = -4.0f;
        o->oAnimState = random_float() * 10.0f;
        obj_translate_xz_random(o, 110.0f);
        o->oKoopaShellFlameUnkF8 = 4.0f;
    }
    cur_obj_update_floor_height();
    cur_obj_move_using_fvel_and_gravity();
    if (o->oFloorHeight > o->oPosY || o->oTimer > 10)
        obj_mark_for_deletion(o);
    o->oKoopaShellFlameUnkF8 += -0.3;
    cur_obj_scale(o->oKoopaShellFlameUnkF8);
}

void bhv_koopa_shell_flame_spawn(void) {
    s32 i;
    for (i = 0; i < 2; i++)
        spawn_object(o, MODEL_RED_FLAME, bhvKoopaShellFlame);
}

void koopa_shell_spawn_sparkles(f32 a) {
    struct Object *sp1C = spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
    if (sp1C == NULL) { return; }
    sp1C->oPosY += a;
}

void bhv_koopa_shell_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 500.0f);
    }

    struct Surface *sp34;
    obj_set_hitbox(o, &sKoopaShellHitbox);
    cur_obj_scale(1.0f);
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = NULL;
    switch (o->oAction) {
        case 0:
            cur_obj_update_floor_and_walls();
            cur_obj_if_hit_wall_bounce_away();
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                o->oAction++;
                if (marioState) {
                    o->heldByPlayerIndex = marioState->playerIndex;
                }
            }
            o->oFaceAngleYaw += 0x1000;
            cur_obj_move_standard(-20);
            koopa_shell_spawn_sparkles(10.0f);
            break;
        case 1:
            if (o->heldByPlayerIndex < MAX_PLAYERS) {
                player = gMarioStates[o->heldByPlayerIndex].marioObj;
                if (player) {
                    obj_copy_pos(o, player);
                }
                sp34 = cur_obj_update_floor_height_and_get_floor();
                if (absf(find_water_level(o->oPosX, o->oPosZ) - o->oPosY) < 10.0f)
                    koopa_shell_spawn_water_drop();
                else if (5.0f > absf(o->oPosY - o->oFloorHeight)) {
                    if (sp34 != NULL && sp34->type == 1)
                        bhv_koopa_shell_flame_spawn();
                    else
                        koopa_shell_spawn_sparkles(10.0f);
                } else
                    koopa_shell_spawn_sparkles(10.0f);
                if (player) {
                    o->oFaceAngleYaw = player->oMoveAngleYaw;
                }
                if (o->oInteractStatus & INT_STATUS_STOP_RIDING) {
                    o->heldByPlayerIndex = 0;
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                    o->oAction = 0;
                }
            }
            break;
    }
    o->oInteractStatus = 0;
}
