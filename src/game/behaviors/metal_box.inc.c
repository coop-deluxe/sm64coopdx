// metal_box.c.inc

struct ObjectHitbox sMetalBoxHitbox = {
    .interactType = 0,
    .downOffset = 0,
    .damageOrCoinValue = 0,
    .health = 1,
    .numLootCoins = 0,
    .radius = 220,
    .height = 300,
    .hurtboxRadius = 220,
    .hurtboxHeight = 300,
};

s32 check_if_moving_over_floor(f32 maxDistToFloor, f32 distance) {
    if (!o) { return 0; }
    struct Surface *floor;
    f32 destX = o->oPosX + sins(o->oMoveAngleYaw) * distance;
    f32 floorHeight;
    f32 destZ = o->oPosZ + coss(o->oMoveAngleYaw) * distance;
    floorHeight = find_floor(destX, o->oPosY, destZ, &floor);
    if (absf(floorHeight - o->oPosY) < maxDistToFloor) // abs
        return 1;
    else
        return 0;
}

void bhv_pushable_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 1000.0f);
        sync_object_init_field(o, o->oMoveAngleYaw);
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
                    cur_obj_play_sound_if_visible(SOUND_ENV_METAL_BOX_PUSH);
                }
            }
        }
    }
    cur_obj_move_using_fvel_and_gravity();
}
