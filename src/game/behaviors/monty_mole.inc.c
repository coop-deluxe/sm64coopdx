
/**
 * Behavior for bhvMontyMole, bhvMontyMoleHole, and bhvMontyMoleRock.
 * The monty mole holes are placed statically. The monty moles repeatedly
 * search for an available hole to pop out of.
 */

/**
 * The first hole in the list of monty mole holes. The list is a singly linked
 * list using the parentObj field.
 */
struct Object *sMontyMoleHoleList;

/**
 * The number of nearby monty moles that have been killed in a row.
 */
s32 sMontyMoleKillStreak;

/**
 * The position of the last killed monty mole, used for determining whether
 * the next killed monty mole is nearby.
 */
f32 sMontyMoleLastKilledPosX;
f32 sMontyMoleLastKilledPosY;
f32 sMontyMoleLastKilledPosZ;

/**
 * Link all objects with the given behavior using parentObj.
 * The result is a singly linked list in reverse processing order. Return the
 * start of this list.
 */
static struct Object *link_objects_with_behavior(const BehaviorScript *behavior) {
    behavior = smlua_override_behavior(behavior);
    const BehaviorScript *behaviorAddr;
    struct Object *obj;
    struct Object *lastObject;
    struct ObjectNode *listHead;

    behaviorAddr = segmented_to_virtual(behavior);
    lastObject = NULL;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];

    obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            obj->parentObj = lastObject;
            lastObject = obj;
        }

        obj = (struct Object *) obj->header.next;
    }

    return lastObject;
}

/**
 * Select a random hole that is within minDistToMario and 1500 of mario, and
 * whose cooldown is zero. Return NULL if no hole is available.
 */
static struct Object *monty_mole_select_available_hole(f32 minDistToMario) {
    struct Object* player;
    s32 distanceToPlayer;

    struct Object *hole = sMontyMoleHoleList;
    s32 numAvailableHoles = 0;
    s32 sanity = 0;

    while (hole != NULL) {
        player = nearest_player_to_object(hole);
        distanceToPlayer = player ? dist_between_objects(hole, player) : 10000;
        if (hole->oMontyMoleHoleCooldown == 0) {
            if (distanceToPlayer < 1500.0f && distanceToPlayer > minDistToMario) {
                numAvailableHoles++;
            }
        }

        if (sanity++ > 100) { break; }
        if (hole == hole->parentObj) { break; }
        hole = hole->parentObj;
    }

    if (numAvailableHoles != 0) {
        s32 selectedHole = (s32)(random_float() * numAvailableHoles);

        hole = sMontyMoleHoleList;
        numAvailableHoles = 0;

        while (hole != NULL) {
            player = nearest_player_to_object(hole);
            distanceToPlayer = player ? dist_between_objects(hole, player) : 10000;
            if (hole->oMontyMoleHoleCooldown == 0) {
                if (distanceToPlayer < 1500.0f && distanceToPlayer > minDistToMario) {
                    if (numAvailableHoles == selectedHole) {
                        return hole;
                    }

                    numAvailableHoles++;
                }
            }

            hole = hole->parentObj;
        }
    }

    return NULL;
}

/**
 * Update function for bhvMontyMoleHole.
 */
void bhv_monty_mole_hole_update(void) {
    // If hole list hasn't been constructed yet, construct it
    if (o->parentObj == o) {
        sMontyMoleHoleList = link_objects_with_behavior(bhvMontyMoleHole);
        sMontyMoleKillStreak = 0;
    } else if (o->oMontyMoleHoleCooldown > 0) {
        o->oMontyMoleHoleCooldown -= 1;
    }
}

/**
 * Spawn dirt particles when rising out of the ground.
 */
void monty_mole_spawn_dirt_particles(s8 offsetY, s8 velYBase) {
    static struct SpawnParticlesInfo sMontyMoleRiseFromGroundParticles = {
        /* behParam:        */ 0,
        /* count:           */ 3,
        /* model:           */ MODEL_SAND_DUST,
        /* offsetY:         */ 0,
        /* forwardVelBase:  */ 4,
        /* forwardVelRange: */ 4,
        /* velYBase:        */ 10,
        /* velYRange:       */ 15,
        /* gravity:         */ -4,
        /* dragStrength:    */ 0,
        /* sizeBase:        */ 10.0f,
        /* sizeRange:       */ 7.0f,
    };

    sMontyMoleRiseFromGroundParticles.offsetY = offsetY;
    sMontyMoleRiseFromGroundParticles.velYBase = velYBase;
    cur_obj_spawn_particles(&sMontyMoleRiseFromGroundParticles);
}

static void bhv_monty_mole_on_received_post(UNUSED u8 fromLocalIndex) {
    if (o->oMontyMoleHoleX == 0 && o->oMontyMoleHoleY == 0 && o->oMontyMoleHoleZ == 0) { return; }

    o->oMontyMoleCurrentHole = NULL;

    f32 savePosX = o->oPosX;
    f32 savePosY = o->oPosY;
    f32 savePosZ = o->oPosZ;

    o->oPosX = o->oMontyMoleHoleX;
    o->oPosY = o->oMontyMoleHoleY;
    o->oPosZ = o->oMontyMoleHoleZ;

    o->oMontyMoleCurrentHole = cur_obj_nearest_object_with_behavior(bhvMontyMoleHole);

    o->oPosX = savePosX;
    o->oPosY = savePosY;
    o->oPosZ = savePosZ;
}

/**
 * Init function for bhvMontyMole.
 */
void bhv_monty_mole_init(void) {
    o->oMontyMoleCurrentHole = NULL;
    o->oMontyMoleHoleX = 0;
    o->oMontyMoleHoleY = 0;
    o->oMontyMoleHoleZ = 0;

    struct SyncObject* so = sync_object_init(o, 4000.0f);
    if (so) {
        so->on_received_post = bhv_monty_mole_on_received_post;
        sync_object_init_field(o, &o->oMontyMoleHeightRelativeToFloor);
        sync_object_init_field(o, &o->oMontyMoleHoleX);
        sync_object_init_field(o, &o->oMontyMoleHoleY);
        sync_object_init_field(o, &o->oMontyMoleHoleZ);
        sync_object_init_field(o, &o->oFaceAnglePitch);
        sync_object_init_field(o, &o->oGravity);
        sync_object_init_field(o, &o->oIntangibleTimer);
        sync_object_init_field(o, &o->oFaceAnglePitch);
        sync_object_init_field_with_size(o, &o->header.gfx.node.flags, 16);
    }
}

/**
 * Search for an available hole. Once one is available, claim it and enter
 * either the rise from hole or jump out of hole action.
 */
static void monty_mole_act_select_hole(void) {
    u8 networkOwns = sync_object_is_owned_locally(o->oSyncID);
    struct MarioState* marioState = nearest_mario_state_to_object(o);

    f32 minDistToMario;

    if (o->oBehParams2ndByte != MONTY_MOLE_BP_NO_ROCK) {
        minDistToMario = 200.0f;
    } else if (marioState && marioState->forwardVel < 8.0f) {
        minDistToMario = 100.0f;
    } else {
        minDistToMario = 500.0f;
    }

    // Select a hole to pop out of
    if ((o->oMontyMoleCurrentHole = monty_mole_select_available_hole(minDistToMario)) != NULL) {
        o->oMontyMoleHoleX = o->oMontyMoleCurrentHole->oPosX;
        o->oMontyMoleHoleY = o->oMontyMoleCurrentHole->oPosY;
        o->oMontyMoleHoleZ = o->oMontyMoleCurrentHole->oPosZ;

        cur_obj_play_sound_2(SOUND_OBJ2_MONTY_MOLE_APPEAR);

        // Mark hole as unavailable
        o->oMontyMoleCurrentHole->oMontyMoleHoleCooldown = -1;

        // Position at hole
        o->oPosX = o->oMontyMoleCurrentHole->oPosX;
        o->oPosY = o->oFloorHeight = o->oMontyMoleCurrentHole->oPosY;
        o->oPosZ = o->oMontyMoleCurrentHole->oPosZ;

        struct Object* holePlayer = nearest_player_to_object(o->oMontyMoleCurrentHole);
        s32 angleToHolePlayer = holePlayer ? obj_angle_to_object(o->oMontyMoleCurrentHole, holePlayer) : 0;

        o->oFaceAnglePitch = 0;
        o->oMoveAngleYaw = angleToHolePlayer;

        struct Object* player = nearest_player_to_object(o);
        s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

        if (distanceToPlayer > 500.0f || minDistToMario > 100.0f || random_sign() < 0) {
            o->oAction = MONTY_MOLE_ACT_RISE_FROM_HOLE;
            o->oVelY = 3.0f;
            o->oGravity = 0.0f;
            monty_mole_spawn_dirt_particles(0, 10);
        } else {
            o->oAction = MONTY_MOLE_ACT_JUMP_OUT_OF_HOLE;
            o->oVelY = 50.0f;
            o->oGravity = -4.0f;
            monty_mole_spawn_dirt_particles(0, 20);
        }

        cur_obj_unhide();
        cur_obj_become_tangible();

        if (networkOwns) { network_send_object(o); }
    }
}

/**
 * Move upward until high enough, then enter the spawn rock action.
 */
static void monty_mole_act_rise_from_hole(void) {
    cur_obj_init_animation_with_sound(1);

    if (o->oMontyMoleHeightRelativeToFloor >= 49.0f) {
        o->oPosY = o->oFloorHeight + 50.0f;
        o->oVelY = 0.0f;

        if (cur_obj_check_if_near_animation_end()) {
            o->oAction = MONTY_MOLE_ACT_SPAWN_ROCK;
        }
    }
}

/**
 * If mario is close enough, then spawn a rock and enter the throw rock action.
 * Otherwise, enter the begin jump into hole action.
 */
static void monty_mole_act_spawn_rock(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    struct Object *rock;

    if (cur_obj_init_anim_and_check_if_end(2)) {
        if (o->oBehParams2ndByte != MONTY_MOLE_BP_NO_ROCK
            && abs_angle_diff(angleToPlayer, o->oMoveAngleYaw) < 0x4000
            && sync_object_is_owned_locally(o->oSyncID)
            && (rock = spawn_object(o, MODEL_PEBBLE, bhvMontyMoleRock)) != NULL) {

            struct Object* spawn_objects[] = { rock };
            u32 models[] = { MODEL_PEBBLE };
            network_send_spawn_objects(spawn_objects, models, 1);

            o->prevObj = rock;
            o->oAction = MONTY_MOLE_ACT_THROW_ROCK;
        } else {
            o->oAction = MONTY_MOLE_ACT_BEGIN_JUMP_INTO_HOLE;
        }
    }
}

/**
 * Wait until mario is relatively close, then set vely to 40 and enter the jump
 * into hole action.
 */
static void monty_mole_act_begin_jump_into_hole(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (cur_obj_init_anim_and_check_if_end(3) || (marioState && obj_is_near_to_and_facing_mario(marioState, 1000.0f, 0x4000))) {
        o->oAction = MONTY_MOLE_ACT_JUMP_INTO_HOLE;
        o->oVelY = 40.0f;
        o->oGravity = -6.0f;
    }
}

/**
 * Throw the held rock, then enter the begin jump into hole action.
 */
static void monty_mole_act_throw_rock(void) {
    if (cur_obj_init_anim_check_frame(8, 10)) {
        cur_obj_play_sound_2(SOUND_OBJ_MONTY_MOLE_ATTACK);
        o->prevObj = NULL;
    }

    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = MONTY_MOLE_ACT_BEGIN_JUMP_INTO_HOLE;
    }
}

/**
 * Tilt downward and wait until close to landing, then enter the hide action.
 */
static void monty_mole_act_jump_into_hole(void) {
    cur_obj_init_anim_extend(0);

    o->oFaceAnglePitch = -atan2s(o->oVelY, -4.0f);

    if (o->oVelY < 0.0f && o->oMontyMoleHeightRelativeToFloor < 120.0f) {
        o->oAction = MONTY_MOLE_ACT_HIDE;
        o->oGravity = 0.0f;
        monty_mole_spawn_dirt_particles(-80, 15);
    }
}

/**
 * Become intangible and enter the select hole action.
 */
static void monty_mole_hide_in_hole(void) {
    if (o->oMontyMoleCurrentHole == NULL) { return; }
    o->oMontyMoleCurrentHole->oMontyMoleHoleCooldown = 30;
    o->oAction = MONTY_MOLE_ACT_SELECT_HOLE;
    o->oVelY = 0.0f;

    //! Even though the object becomes intangible here, it is still possible
    //  for a bob-omb to interact with it later in the frame (since bob-ombs
    //  come after monty moles in processing order).
    //  This means that the monty mole can be attacked while in the select hole
    //  action. If no hole is available (e.g. because mario is too far away),
    //  the game will crash because of the line above that accesses
    //  oMontyMoleCurrentHole.
    cur_obj_become_intangible();
}

/**
 * Wait to land on the floor, then hide.
 */
static void monty_mole_act_hide(void) {
    cur_obj_init_animation_with_sound(1);

    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        cur_obj_hide();
        monty_mole_hide_in_hole();
    } else {
        approach_f32_ptr(&o->oVelY, -4.0f, 0.5f);
    }
}

/**
 * Jump upward and then fall back down. Then enter the begin jump into hole
 * action.
 */
static void monty_mole_act_jump_out_of_hole(void) {
    if (o->oVelY > 0.0f) {
        cur_obj_init_animation_with_sound(9);
    } else {
        cur_obj_init_anim_extend(4);

        if (o->oMontyMoleHeightRelativeToFloor < 50.0f) {
            o->oPosY = o->oFloorHeight + 50.0f;
            o->oAction = MONTY_MOLE_ACT_BEGIN_JUMP_INTO_HOLE;
            o->oVelY = o->oGravity = 0.0f;
        }
    }
}

/**
 * Hitbox for monty mole.
 */
static struct ObjectHitbox sMontyMoleHitbox = {
    .interactType = INTERACT_BOUNCE_TOP,
    .downOffset = 0,
    .damageOrCoinValue = 2,
    .health = -1,
    .numLootCoins = 0,
    .radius = 70,
    .height = 50,
    .hurtboxRadius = 30,
    .hurtboxHeight = 40,
};

/**
 * Update function for bhvMontyMole.
 */
void bhv_monty_mole_update(void) {
    // PARTIAL_UPDATE

    o->oDeathSound = SOUND_OBJ_DYING_ENEMY1;
    cur_obj_update_floor_and_walls();

    // if we can't find our floor, set it to the hole's floor
    if (!o->oFloor && o->oMontyMoleCurrentHole) {
        struct Object* hole = o->oMontyMoleCurrentHole;
        struct Surface* floor = NULL;
        o->oFloorHeight = find_floor(hole->oPosX, hole->oPosY, hole->oPosZ, &floor);
        o->oFloor = floor;
    }

    o->oMontyMoleHeightRelativeToFloor = o->oPosY - o->oFloorHeight;

    switch (o->oAction) {
        case MONTY_MOLE_ACT_SELECT_HOLE:
            monty_mole_act_select_hole();
            break;
        case MONTY_MOLE_ACT_RISE_FROM_HOLE:
            monty_mole_act_rise_from_hole();
            break;
        case MONTY_MOLE_ACT_SPAWN_ROCK:
            monty_mole_act_spawn_rock();
            break;
        case MONTY_MOLE_ACT_BEGIN_JUMP_INTO_HOLE:
            monty_mole_act_begin_jump_into_hole();
            break;
        case MONTY_MOLE_ACT_THROW_ROCK:
            monty_mole_act_throw_rock();
            break;
        case MONTY_MOLE_ACT_JUMP_INTO_HOLE:
            monty_mole_act_jump_into_hole();
            break;
        case MONTY_MOLE_ACT_HIDE:
            monty_mole_act_hide();
            break;
        case MONTY_MOLE_ACT_JUMP_OUT_OF_HOLE:
            monty_mole_act_jump_out_of_hole();
            break;
    }

    // Spawn a 1-up if you kill 8 monty moles
    if (obj_check_attacks(&sMontyMoleHitbox, o->oAction)) {
        if (sMontyMoleKillStreak != 0) {
            f32 dx = o->oPosX - sMontyMoleLastKilledPosX;
            f32 dy = o->oPosY - sMontyMoleLastKilledPosY;
            f32 dz = o->oPosZ - sMontyMoleLastKilledPosZ;

            f32 distToLastKill = sqrtf(dx * dx + dy * dy + dz * dz);

            //! The two farthest holes on the bottom level of TTM are more than
            //  1500 units away from each other, so the counter resets if you
            //  attack moles in these holes consecutively.
            if (distToLastKill < 1500.0f) {
                if (sMontyMoleKillStreak == 7 && sync_object_is_owned_locally(o->oSyncID)) {
                    play_puzzle_jingle();
                    struct Object* oneUp = spawn_object(o, MODEL_1UP, bhv1upWalking);
                    if (oneUp != NULL) {
                        struct Object* spawn_objects[] = { oneUp };
                        u32 models[] = { MODEL_1UP };
                        network_send_spawn_objects(spawn_objects, models, 1);
                    }
                }
            } else {
                sMontyMoleKillStreak = 0;
            }
        }

        //! No overflow check
        sMontyMoleKillStreak += 1;

        sMontyMoleLastKilledPosX = o->oPosX;
        sMontyMoleLastKilledPosY = o->oPosY;
        sMontyMoleLastKilledPosZ = o->oPosZ;

        monty_mole_hide_in_hole();

        // Throw rock if holding one
        o->prevObj = NULL;
    }

    cur_obj_move_standard(78);
}

/**
 * Wait for monty mole to throw the rock, then enter the move action.
 */
static void monty_mole_rock_act_held(void) {
    // The position is offset since the monty mole is throwing it with its hand
    o->oParentRelativePosX = 80.0f;
    o->oParentRelativePosY = -50.0f;
    o->oParentRelativePosZ = 0.0f;

    if (o->parentObj == NULL || o->parentObj->prevObj == NULL) {
        struct Object* player = nearest_player_to_object(o);
        s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
        if (distanceToPlayer > 600.0f) {
            distanceToPlayer = 600.0f;
        }

        o->oAction = MONTY_MOLE_ROCK_ACT_MOVE;

        // The angle is adjusted to compensate for the start position offset
        if (o->parentObj != NULL) {
            o->oMoveAngleYaw = (s32)(o->parentObj->oMoveAngleYaw + 0x1F4 - distanceToPlayer * 0.1f);
        }

        o->oForwardVel = 40.0f;
        o->oVelY = distanceToPlayer * 0.08f + 8.0f;

        o->oMoveFlags = 0;
    }
}

/**
 * Hitbox for monty mole rock.
 */
static struct ObjectHitbox sMontyMoleRockHitbox = {
    .interactType = INTERACT_MR_BLIZZARD,
    .downOffset = 15,
    .damageOrCoinValue = 1,
    .health = 99,
    .numLootCoins = 0,
    .radius = 30,
    .height = 15,
    .hurtboxRadius = 30,
    .hurtboxHeight = 15,
};

/**
 * The particles that spawn when a monty mole rock breaks.
 */
static struct SpawnParticlesInfo sMontyMoleRockBreakParticles = {
    /* behParam:        */ 0,
    /* count:           */ 2,
    /* model:           */ MODEL_PEBBLE,
    /* offsetY:         */ 10,
    /* forwardVelBase:  */ 4,
    /* forwardVelRange: */ 4,
    /* velYBase:        */ 10,
    /* velYRange:       */ 15,
    /* gravity:         */ -4,
    /* dragStrength:    */ 0,
    /* sizeBase:        */ 8.0f,
    /* sizeRange:       */ 4.0f,
};

/**
 * Move, then despawn after hitting the ground or water.
 */
static void monty_mole_rock_act_move(void) {
    cur_obj_update_floor_and_walls();

    if (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_ENTERED_WATER)) {
        cur_obj_spawn_particles(&sMontyMoleRockBreakParticles);
        obj_mark_for_deletion(o);
    }

    cur_obj_move_standard(78);
}

/**
 * Update function for bhvMontyMoleRock.
 */
void bhv_monty_mole_rock_update(void) {
    // PARTIAL_UPDATE
    //! Since we can prevent them from despawning using partial updates, we
    //  can fill up object slots to crash the game.

    obj_check_attacks(&sMontyMoleRockHitbox, o->oAction);

    switch (o->oAction) {
        case MONTY_MOLE_ROCK_ACT_HELD:
            monty_mole_rock_act_held();
            break;
        case MONTY_MOLE_ROCK_ACT_MOVE:
            monty_mole_rock_act_move();
            break;
    }
}
