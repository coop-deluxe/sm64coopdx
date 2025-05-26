// spindrift.c.inc

struct ObjectHitbox sSpindriftHitbox = {
    .interactType = INTERACT_BOUNCE_TOP,
    .downOffset = 0,
    .damageOrCoinValue = 2,
    .health = 1,
    .numLootCoins = 3,
    .radius = 90,
    .height = 80,
    .hurtboxRadius = 80,
    .hurtboxHeight = 70,
};

void bhv_spindrift_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oFlags);
    }

    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    o->activeFlags |= ACTIVE_FLAG_UNK10;
    if (cur_obj_set_hitbox_and_die_if_attacked(&sSpindriftHitbox, SOUND_OBJ_DYING_ENEMY1, 0))
        cur_obj_change_action(1);
    cur_obj_update_floor_and_walls();
    switch (o->oAction) {
        case 0:
            approach_forward_vel(&o->oForwardVel, 4.0f, 1.0f);
            if (cur_obj_lateral_dist_from_mario_to_home() > 1000.0f) {
                angleToPlayer = cur_obj_angle_to_home();
            } else if (distanceToPlayer > 300.0f) {
                //angleToPlayer = angleToPlayer;
            }
            cur_obj_rotate_yaw_toward(angleToPlayer, 0x400);
            break;
        case 1:
            o->oFlags &= ~8;
            o->oForwardVel = -10.0f;
            if (o->oTimer > 20) {
                o->oAction = 0;
                o->oInteractStatus = 0;
                o->oFlags |= 8;
            }
            break;
    }
    cur_obj_move_standard(-60);
}
