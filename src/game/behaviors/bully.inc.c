// bully.c.inc

static struct ObjectHitbox sSmallBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 73,
    /* height:            */ 123,
    /* hurtboxRadius:     */ 63,
    /* hurtboxHeight:     */ 113,
};

static struct ObjectHitbox sBigBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 115,
    /* height:            */ 235,
    /* hurtboxRadius:     */ 105,
    /* hurtboxHeight:     */ 225,
};

static u8 bhv_bully_ignore_if_true(void) {
    return (o->oAction == BULLY_ACT_LAVA_DEATH) || (o->oAction == BULLY_ACT_DEATH_PLANE_DEATH);
}

static void bhv_bully_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    if ((o->oAction == BULLY_ACT_LAVA_DEATH) || (o->oAction == BULLY_ACT_DEATH_PLANE_DEATH) || (o->oIntangibleTimer != 0)) {
        *shouldOverride = TRUE;
        *shouldOwn = FALSE;
    } else {
        *shouldOverride = FALSE;
    }
}

static void bhv_bully_network_init(void) {
    struct SyncObject* so = sync_object_init(o, 4000.0f);
    if (so) {
        sync_object_init_field(o, &o->oFlags);
        sync_object_init_field(o, &o->oBullyKBTimerAndMinionKOCounter);
        sync_object_init_field(o, &o->oForwardVel);
        sync_object_init_field(o, &o->oBullyPrevX);
        sync_object_init_field(o, &o->oBullyPrevY);
        sync_object_init_field(o, &o->oBullyPrevZ);
        sync_object_init_field(o, &o->oBullyMarioCollisionAngle);
        sync_object_init_field(o, &o->oBullyLastNetworkPlayerIndex);
        so->syncDeathEvent = FALSE;
        so->ignore_if_true = bhv_bully_ignore_if_true;
        so->override_ownership = bhv_bully_override_ownership;
    }
}

void bhv_small_bully_init(void) {
    cur_obj_init_animation(0);

    o->oHomeX = o->oPosX;
    o->oHomeZ = o->oPosZ;
    o->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
    o->oGravity = 4.0;
    o->oFriction = 0.91;
    o->oBuoyancy = 1.3;
    
    // We only set this here so it has a set value just in case.
    // A mod may make a small bully spawn a star.
    // For whatever reason that may be.
    o->oBullyLastNetworkPlayerIndex = UNKNOWN_GLOBAL_INDEX;

    obj_set_hitbox(o, &sSmallBullyHitbox);
    bhv_bully_network_init();
}

void bhv_big_bully_init(void) {
    cur_obj_init_animation(0);

    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
    o->oBehParams2ndByte = BULLY_BP_SIZE_BIG;
    o->oGravity = 5.0;
    o->oFriction = 0.93;
    o->oBuoyancy = 1.3;
    
    // We haven't interacted with a player yet.
    // We also don't sync this as not only is it not required
    // but it also is only set for an interaction.
    // Therefore this object must already be loaded for it to be set
    // and if it wasn't. You couldn't of possibly been the one
    // who last interacted to begin with.
    o->oBullyLastNetworkPlayerIndex = UNKNOWN_GLOBAL_INDEX;

    obj_set_hitbox(o, &sBigBullyHitbox);
    bhv_bully_network_init();

    if (gCurrCourseNum == COURSE_LLL) {
        spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvLllTumblingBridge, 0, 154, -5631, 0, 0, 0);
        struct Object* lllTumblingBridge = cur_obj_nearest_object_with_behavior(bhvLllTumblingBridge);
        if (lllTumblingBridge != NULL) { lllTumblingBridge->oIntangibleTimer = -1; }
    }
}

void bully_check_mario_collision(void) {
    if (
#ifdef VERSION_SH
    o->oAction != BULLY_ACT_LAVA_DEATH && o->oAction != BULLY_ACT_DEATH_PLANE_DEATH &&
#endif
    o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            cur_obj_play_sound_2(SOUND_OBJ2_BULLY_ATTACKED);
        } else {
            cur_obj_play_sound_2(SOUND_OBJ2_LARGE_BULLY_ATTACKED);
        }

        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        o->oAction = BULLY_ACT_KNOCKBACK;
        o->oFlags &= ~0x8; /* bit 3 */
        cur_obj_init_animation(3);
        o->oBullyMarioCollisionAngle = o->oMoveAngleYaw;

        // Get the player who interacted with us.
        struct MarioState *player = nearest_interacting_mario_state_to_object(o);
        if (player) {
            o->oBullyLastNetworkPlayerIndex = gNetworkPlayers[player->playerIndex].globalIndex;
        }
    }
}

void bully_act_chase_mario(void) {
    f32 homeX = o->oHomeX;
    f32 posY = o->oPosY;
    f32 homeZ = o->oHomeZ;

    struct Object* player = nearest_player_to_object(o);

    if (o->oTimer < 10) {
        o->oForwardVel = 3.0;
        if (player) {
            obj_turn_toward_object(o, player, 16, 4096);
        }
    } else if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
        o->oForwardVel = 20.0;
        if (o->oTimer >= 31) {
            o->oTimer = 0;
        }
    } else {
        o->oForwardVel = 30.0;
        if (o->oTimer >= 36) {
            o->oTimer = 0;
        }
    }

    if (!is_point_within_radius_of_mario(homeX, posY, homeZ, 1000)) {
        o->oAction = BULLY_ACT_PATROL;
        cur_obj_init_animation(0);
    }
}

void bully_act_knockback(void) {
    struct Object* player = nearest_player_to_object(o);
    if (o->oForwardVel < 10.0 && (s32) o->oVelY == 0) {
        o->oForwardVel = 1.0;
        o->oBullyKBTimerAndMinionKOCounter++;
        o->oFlags |= 0x8; /* bit 3 */
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        if (player) {
            obj_turn_toward_object(o, player, 16, 1280);
        }
    } else {
        o->header.gfx.animInfo.animFrame = 0;
    }

    if (o->oBullyKBTimerAndMinionKOCounter == 18) {
        o->oAction = BULLY_ACT_CHASE_MARIO;
        o->oBullyKBTimerAndMinionKOCounter = 0;
        cur_obj_init_animation(1);
    }
}

void bully_act_back_up(void) {
    if (o->oTimer == 0) {
        o->oFlags &= ~0x8; /* bit 3 */
        o->oMoveAngleYaw += 0x8000;
    }

    o->oForwardVel = 5.0;

    //! bully_backup_check() happens after this function, and has the potential to reset
    //  the bully's action to BULLY_ACT_BACK_UP. Because the back up action is only
    //  set to end when the timer EQUALS 15, if this happens on that frame, the bully
    //  will be stuck in BULLY_ACT_BACK_UP forever until Mario hits it or its death
    //  conditions are activated. However because its angle is set to its facing angle,
    //  it will walk forward instead of backing up.

    if (o->oTimer == 15) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->oFlags |= 0x8; /* bit 3 */
        o->oAction = BULLY_ACT_PATROL;
    }
}

void bully_backup_check(s16 collisionFlags) {
    if (!(collisionFlags & 0x8) && o->oAction != BULLY_ACT_KNOCKBACK) /* bit 3 */
    {
        o->oPosX = o->oBullyPrevX;
        o->oPosZ = o->oBullyPrevZ;
        o->oAction = BULLY_ACT_BACK_UP;
    }
}

void bully_play_stomping_sound(void) {
    s16 sp26 = o->header.gfx.animInfo.animFrame;
    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            if (sp26 == 0 || sp26 == 12) {
                if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL)
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK);
                else
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALKING);
            }
            break;

        case BULLY_ACT_CHASE_MARIO:
        case BULLY_ACT_BACK_UP:
            if (sp26 == 0 || sp26 == 5) {
                if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL)
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALK);
                else
                    cur_obj_play_sound_2(SOUND_OBJ_BULLY_WALKING);
            }
            break;
    }
}

void bully_step(void) {
    s16 collisionFlags = 0;
    collisionFlags = object_step();
    bully_backup_check(collisionFlags);
    bully_play_stomping_sound();
    obj_check_floor_death(collisionFlags, sObjFloor);

    if (o->oBullySubtype & BULLY_STYPE_CHILL) {
        if (o->oPosY < gBehaviorValues.ChillBullyDeathPosY) {
            o->oAction = BULLY_ACT_LAVA_DEATH;
        }
    }
}

void bully_spawn_coin(void) {
    struct Object *coin = spawn_object(o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
#ifdef VERSION_JP // TODO: maybe move this ifdef logic to the header?
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT);
#elif defined(VERSION_EU) || defined(VERSION_SH)
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_EU);
#else
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_2);
#endif
    if (coin == NULL) { return; }
    coin->oForwardVel = 10.0f;
    coin->oVelY = 100.0f;
    coin->oPosY = o->oPosY + 310.0f;
    coin->oMoveAngleYaw = (f32)(o->oBullyMarioCollisionAngle + 0x8000) + random_float() * 1024.0f;
}

void bully_act_level_death(void) {
    if (obj_lava_death() == 1) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            if (o->oBullySubtype == BULLY_STYPE_MINION)
                o->parentObj->oBullyKBTimerAndMinionKOCounter++;
            bully_spawn_coin();
        } else {
            spawn_mist_particles();

            if (o->oBullySubtype == BULLY_STYPE_CHILL) {
                f32* starPos = gLevelValues.starPositions.ChillBullyStarPos;
                spawn_networked_default_star(starPos[0], starPos[1], starPos[2], o->oBullyLastNetworkPlayerIndex);
            } else {
                f32* starPos = gLevelValues.starPositions.BigBullyTrioStarPos;
                spawn_networked_default_star(starPos[0], starPos[1], starPos[2], o->oBullyLastNetworkPlayerIndex);
                struct Object* lllTumblingBridge = cur_obj_nearest_object_with_behavior(bhvLllTumblingBridge);
                if (lllTumblingBridge != NULL) {
                    lllTumblingBridge->oIntangibleTimer = 0;
                    network_send_object(lllTumblingBridge);
                }
            }
        }
    }
}

void bhv_bully_loop(void) {
    o->oBullyPrevX = o->oPosX;
    o->oBullyPrevY = o->oPosY;
    o->oBullyPrevZ = o->oPosZ;

    //! Because this function runs no matter what, Mario is able to interrupt the bully's
    //  death action by colliding with it. Since the bully hitbox is tall enough to collide
    //  with Mario even when it is under a lava floor, this can get the bully stuck OOB
    //  if there is nothing under the lava floor.
    bully_check_mario_collision();

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0;

            if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 800) == 1) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(1);
            }

            bully_step();
            break;

        case BULLY_ACT_CHASE_MARIO:
            bully_act_chase_mario();
            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case BULLY_ACT_LAVA_DEATH:
            bully_act_level_death();
            break;

        case BULLY_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }

    set_object_visibility(o, 3000);
}

// sp38 = arg0
// sp3c = arg1
// sp40 = arg2
// sp44 = arg3

void big_bully_spawn_minion(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    struct Object *bully =
        spawn_object_abs_with_rot(o, 0, MODEL_BULLY, bhvSmallBully, arg0, arg1, arg2, 0, arg3, 00);
    if (bully != NULL) {
        bully->oBullySubtype = BULLY_STYPE_MINION;
        bully->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
    }
}

void bhv_big_bully_with_minions_init(void) {
    big_bully_spawn_minion(4454, 307, -5426, 0);
    big_bully_spawn_minion(3840, 307, -6041, 0);
    big_bully_spawn_minion(3226, 307, -5426, 0);

    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;

    cur_obj_become_intangible();

    o->oAction = BULLY_ACT_INACTIVE;
    bhv_bully_network_init();
}

void big_bully_spawn_star(void) {
    if (obj_lava_death() == 1) {
        spawn_mist_particles();
        f32* starPos = gLevelValues.starPositions.BigBullyStarPos;
        spawn_networked_default_star(starPos[0], starPos[1], starPos[2], o->oBullyLastNetworkPlayerIndex);
    }
}

void bhv_big_bully_with_minions_loop(void) {
    s16 collisionFlags;

    o->oBullyPrevX = o->oPosX;
    o->oBullyPrevY = o->oPosY;
    o->oBullyPrevZ = o->oPosZ;

    bully_check_mario_collision();

    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0;

            if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 1000) == 1) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(1);
            }

            bully_step();
            break;

        case BULLY_ACT_CHASE_MARIO:
            bully_act_chase_mario();
            bully_step();
            break;

        case BULLY_ACT_KNOCKBACK:
            bully_act_knockback();
            bully_step();
            break;

        case BULLY_ACT_BACK_UP:
            bully_act_back_up();
            bully_step();
            break;

        case BULLY_ACT_INACTIVE:
            //! The Big Bully that spawns from killing its 3 minions uses the knockback timer
            //  for counting the number of dead minions. This means that when it activates,
            //  the knockback timer is at 3 instead of 0. So the bully knockback time will
            //  be reduced by 3 frames (16.67%) on the first hit.
            if (o->oBullyKBTimerAndMinionKOCounter == 3) {
                play_puzzle_jingle();

                if (o->oTimer >= 91)
                    o->oAction = BULLY_ACT_ACTIVATE_AND_FALL;
            }
            break;

        case BULLY_ACT_ACTIVATE_AND_FALL:
            collisionFlags = object_step();
            if ((collisionFlags & 0x9) == 0x9) /* bits 0 and 3 */
                o->oAction = BULLY_ACT_PATROL;

            if (collisionFlags == 1) {
                cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
            }

            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            cur_obj_become_tangible();
            break;

        case BULLY_ACT_LAVA_DEATH:
            big_bully_spawn_star();
            break;

        case BULLY_ACT_DEATH_PLANE_DEATH:
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}
