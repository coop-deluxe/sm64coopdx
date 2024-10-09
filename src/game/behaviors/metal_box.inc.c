// metal_box.c.inc

struct ObjectHitbox sMetalBoxHitbox = {
    /* interactType: */ 0,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 0,
    /* health: */ 1,
    /* numLootCoins: */ 0,
    /* radius: */ 220,
    /* height: */ 300,
    /* hurtboxRadius: */ 220,
    /* hurtboxHeight: */ 300,
};

s32 check_if_moving_over_floor(f32 a0, f32 a1) {
    if (!o) { return 0; }
    struct Surface *sp24;
    f32 sp20 = o->oPosX + sins(o->oMoveAngleYaw) * a1;
    f32 floorHeight;
    f32 sp18 = o->oPosZ + coss(o->oMoveAngleYaw) * a1;
    floorHeight = find_floor(sp20, o->oPosY, sp18, &sp24);
    if (absf(floorHeight - o->oPosY) < a0) // abs
        return 1;
    else
        return 0;
}

void bhv_pushable_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, &o->oMoveAngleYaw);
    }

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;

    UNUSED s16 unused;
    s16 sp1C;
    obj_set_hitbox(o, &sMetalBoxHitbox);
    o->oForwardVel = 0.0f;
    if (player) {
        if (obj_check_if_collided_with_object(o, player) && marioState && marioState->flags & MARIO_UNKNOWN_31) {
            sp1C = obj_angle_to_object(o, player);
            if (abs_angle_diff(sp1C, player->oMoveAngleYaw) > 0x4000) {
                o->oMoveAngleYaw = (s16)((player->oMoveAngleYaw + 0x2000) & 0xc000);
                if (check_if_moving_over_floor(8.0f, 150.0f)) {
                    o->oForwardVel = 4.0f;
                    cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
                }
            }
        }
    }
    cur_obj_move_using_fvel_and_gravity();
}
