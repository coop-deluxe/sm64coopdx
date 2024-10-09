/**
 * Behavior for bhvKoopa and bhvKoopaRaceEndpoint.
 * bhvKoopa includes normal, unshelled, tiny, and Koopa the Quick.
 * When the race begins, koopa the quick sets his parent to bhvKoopaRaceEndpoint
 * which assists in determining the state of the race. It is positioned at the
 * flag.
 */

/**
 * Hitbox for koopa - this is used for every form except Koopa the Quick, which
 * uses a hardcoded soft hitbox.
 */
static struct ObjectHitbox sKoopaHitbox = {
    /* interactType:      */ INTERACT_KOOPA,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ -1,
    /* radius:            */ 60,
    /* height:            */ 40,
    /* hurtboxRadius:     */ 40,
    /* hurtboxHeight:     */ 30,
};

/**
 * Attack handlers for unshelled koopa and tiny shelled koopa.
 */
static u8 sKoopaUnshelledAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

/**
 * Attack handlers for regular sized shelled koopa.
 */
static u8 sKoopaShelledAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL,
};

/**
 * Data to control the behavior of each instance of Koopa the Quick.
 */
struct KoopaTheQuickProperties {
    s16* initText;
    s16* winText;
};

/**
 * Properties for the BoB race and the THI race.
 */
static struct KoopaTheQuickProperties sKoopaTheQuickProperties[] = {
    { (s16*) &gBehaviorValues.dialogs.KoopaQuickBobStartDialog, (s16*) &gBehaviorValues.dialogs.KoopaQuickBobWinDialog },
    { (s16*) &gBehaviorValues.dialogs.KoopaQuickThiStartDialog, (s16*) &gBehaviorValues.dialogs.KoopaQuickThiWinDialog }
};

static u32 koopaPathedStartWaypoint = 0;
static u32 koopaPathedPrevWaypoint = 0;
static u32 koopaShotFromCannon = 0;

static void bhv_koopa_the_quick_on_received_post(UNUSED u8 fromLocalIndex) {
    void* path = (o->oKoopaTheQuickRaceIndex == 0)
               ? (void*) gBehaviorValues.trajectories.KoopaBobTrajectory
               : (void*) gBehaviorValues.trajectories.KoopaThiTrajectory;
    o->oPathedStartWaypoint = (struct Waypoint*)path + koopaPathedStartWaypoint;
    o->oPathedPrevWaypoint  = (struct Waypoint*)path + koopaPathedPrevWaypoint;
    gMarioShotFromCannon = koopaShotFromCannon;
}

static void bhv_koopa_the_quick_on_sent_pre(void) {
    void* path = (o->oKoopaTheQuickRaceIndex == 0)
               ? (void*) gBehaviorValues.trajectories.KoopaBobTrajectory
               : (void*) gBehaviorValues.trajectories.KoopaThiTrajectory;
    koopaPathedStartWaypoint = ((void*)o->oPathedStartWaypoint - path) / sizeof(struct Waypoint*);
    koopaPathedPrevWaypoint  = ((void*)o->oPathedPrevWaypoint  - path) / sizeof(struct Waypoint*);
    koopaShotFromCannon = gMarioShotFromCannon;
}

void bhv_koopa_the_quick_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = TRUE;
    *shouldOwn = (get_network_player_smallest_global() == gNetworkPlayerLocal);
}

static void bhv_koopa_the_quick_run_once(void) {
    cur_obj_push_mario_away_from_cylinder(140.0f, 300.0f);
}

/**
 * Initialization function.
 */
void bhv_koopa_init(void) {
    if ((o->oKoopaMovementType = o->oBehParams2ndByte) == KOOPA_BP_TINY) {
        // Tiny koopa in THI
        o->oKoopaMovementType = KOOPA_BP_NORMAL;
        o->oKoopaAgility = 1.6f / 3.0f;
        o->oDrawingDistance = 1500.0f;
        cur_obj_scale(0.8f);
        o->oGravity = -6.4f / 3.0f;
    } else if (o->oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE) {
        // Koopa the Quick. Race index is 0 for BoB and 1 for THI
        o->oKoopaTheQuickRaceIndex = o->oKoopaMovementType - KOOPA_BP_KOOPA_THE_QUICK_BASE;
        o->oKoopaAgility = 4.0f;
        cur_obj_scale(3.0f);
    } else {
        o->oKoopaAgility = 1.0f;
    }

    if (o->oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE) {
        // koopa the quick
        if (cur_obj_nearest_object_with_behavior(bhvKoopaRaceEndpoint) != NULL) {
            o->parentObj = cur_obj_nearest_object_with_behavior(bhvKoopaRaceEndpoint);
        } else {
            obj_mark_for_deletion(o);
            return;
        }
        struct SyncObject* so  = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->on_received_post   = bhv_koopa_the_quick_on_received_post;
            so->on_sent_pre        = bhv_koopa_the_quick_on_sent_pre;
            so->override_ownership = bhv_koopa_the_quick_override_ownership;
            sync_object_init_field(o, &koopaPathedStartWaypoint);
            sync_object_init_field(o, &koopaPathedPrevWaypoint);
            sync_object_init_field(o, &koopaShotFromCannon);
            sync_object_init_field(o, &o->oPathedPrevWaypointFlags);
            sync_object_init_field(o, &o->oPathedTargetPitch);
            sync_object_init_field(o, &o->oPathedTargetYaw);
            sync_object_init_field(o, &o->oPosX);
            sync_object_init_field(o, &o->oPosY);
            sync_object_init_field(o, &o->oPosZ);
            sync_object_init_field(o, &o->oVelX);
            sync_object_init_field(o, &o->oVelY);
            sync_object_init_field(o, &o->oVelZ);
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oSubAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oKoopaAgility);
            sync_object_init_field(o, &o->parentObj->oKoopaRaceEndpointRaceBegun);
            sync_object_init_field(o, &o->parentObj->oKoopaRaceEndpointRaceStatus);
            sync_object_init_field(o, &o->oForwardVel);
            sync_object_init_field(o, &o->oMoveAngleYaw);
            sync_object_init_field(o, &o->areaTimer);
        }
        o->areaTimerType = AREA_TIMER_TYPE_MAXIMUM;
        o->areaTimer = 0;
        o->areaTimerDuration = 60;
        o->areaTimerRunOnceCallback = bhv_koopa_the_quick_run_once;
    } else {
        // normal koopa
        sync_object_init(o, 4000.0f);
        sync_object_init_field(o, &o->oKoopaTargetYaw);
        sync_object_init_field(o, &o->oKoopaCountdown);
        sync_object_init_field(o, &o->oKoopaMovementType);
        sync_object_init_field(o, &o->oKoopaUnshelledTimeUntilTurn);
    }
}

/**
 * Play the appropriate footstep sound on the two provided animation frames.
 */
static void koopa_play_footstep_sound(s8 animFrame1, s8 animFrame2) {
    s32 sound;
    if (o->header.gfx.scale[0] > 1.5f) {
        sound = SOUND_OBJ_KOOPA_THE_QUICK_WALK;
    } else {
        sound = SOUND_OBJ_KOOPA_WALK;
    }

    cur_obj_play_sound_at_anim_range(animFrame1, animFrame2, sound);
}

/**
 * If mario is close to koopa, and koopa is facing toward mario, then begin
 * running away.
 */
static s32 koopa_check_run_from_mario(void) {
    s32 distanceToPlayer = o->oDistanceToMario;
    s32 angleToPlayer = o->oAngleToMario;
    if (distanceToPlayer < 300.0f && abs_angle_diff(angleToPlayer, o->oMoveAngleYaw) < 0x3000) {
        o->oAction = KOOPA_SHELLED_ACT_RUN_FROM_MARIO;
        return TRUE;
    }

    return FALSE;
}

/**
 * Stay still for a while, then change target yaw by 45 degrees and begin
 * walking.
 */
static void koopa_shelled_act_stopped(void) {
    o->oForwardVel = 0.0f;
    if (cur_obj_init_anim_and_check_if_end(7)) {
        o->oAction = KOOPA_SHELLED_ACT_WALK;
        o->oKoopaTargetYaw = o->oMoveAngleYaw + 0x2000 * (s16) random_sign();
    }
}

/**
 * Begin walking, then increment sub-action.
 */
static void koopa_walk_start(void) {
    obj_forward_vel_approach(3.0f * o->oKoopaAgility, 0.3f * o->oKoopaAgility);

    if (cur_obj_init_anim_and_check_if_end(11)) {
        o->oSubAction += 1;
        o->oKoopaCountdown = random_linear_offset(30, 100);
    }
}

/**
 * Walk until oKoopaCountdown hits zero, then increment sub-action.
 */
static void koopa_walk(void) {
    cur_obj_init_animation_with_sound(9);
    koopa_play_footstep_sound(2, 17);

    if (o->oKoopaCountdown != 0) {
        o->oKoopaCountdown -= 1;
    } else if (cur_obj_check_if_near_animation_end()) {
        o->oSubAction += 1;
    }
}

/**
 * Stop walking, then enter action KOOPA_SHELLED_ACT_STOPPED.
 */
static void koopa_walk_stop(void) {
    obj_forward_vel_approach(0.0f, 1.0f * o->oKoopaAgility);
    if (cur_obj_init_anim_and_check_if_end(10)) {
        o->oAction = KOOPA_SHELLED_ACT_STOPPED;
    }
}

/**
 * Walk for a while, then come to a stop. During this time, turn toward the
 * target yaw.
 */
static void koopa_shelled_act_walk(void) {
    if (o->oKoopaTurningAwayFromWall) {
        o->oKoopaTurningAwayFromWall = obj_resolve_collisions_and_turn(o->oKoopaTargetYaw, 0x200);
    } else {
        s32 distanceToPlayer = o->oDistanceToMario;
        s32 angleToPlayer = o->oAngleToMario;
        // If far from home, then begin turning toward home
        if (distanceToPlayer >= 25000.0f) {
            o->oKoopaTargetYaw = angleToPlayer;
        }

        o->oKoopaTurningAwayFromWall = obj_bounce_off_walls_edges_objects(&o->oKoopaTargetYaw);
        cur_obj_rotate_yaw_toward(o->oKoopaTargetYaw, 0x200);
    }

    switch (o->oSubAction) {
        case KOOPA_SHELLED_SUB_ACT_START_WALK:
            koopa_walk_start();
            break;
        case KOOPA_SHELLED_SUB_ACT_WALK:
            koopa_walk();
            break;
        case KOOPA_SHELLED_SUB_ACT_STOP_WALK:
            koopa_walk_stop();
            break;
    }

    koopa_check_run_from_mario();
}

/**
 * Run while turning away from mario. Come to a stop once mario is far enough
 * away.
 */
static void koopa_shelled_act_run_from_mario(void) {
    cur_obj_init_animation_with_sound(1);
    koopa_play_footstep_sound(0, 11);

    s32 distanceToPlayer = o->oDistanceToMario;
    s32 angleToPlayer = o->oAngleToMario;

    // If far from home, run toward it
    if (distanceToPlayer >= 25000.0f) {
        angleToPlayer += 0x8000;
        distanceToPlayer = 0.0f;
    }

    if (o->oTimer > 30 && distanceToPlayer > 800.0f) {
        if (obj_forward_vel_approach(0.0f, 1.0f)) {
            o->oAction = KOOPA_SHELLED_ACT_STOPPED;
        }
    } else {
        cur_obj_rotate_yaw_toward(angleToPlayer + 0x8000, 0x400);
        obj_forward_vel_approach(17.0f, 1.0f);
    }
}

/**
 * If on the ground, decelerate. Generate dust if moving fast enough.
 */
static void koopa_dive_update_speed(f32 decel) {
    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        obj_forward_vel_approach(0.0f, decel);
        if (o->oForwardVel > 5.0f) {
            if (!(o->oTimer % 4)) {
                spawn_object_with_scale(o, MODEL_SMOKE, bhvWhitePuffSmoke2, 1.0f);
            }
        }
    }
}

/**
 * Slide on the ground and then come to a stop.
 */
static void koopa_shelled_act_lying(void) {
    if (o->oForwardVel != 0.0f) {
        if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
            o->oMoveAngleYaw = cur_obj_reflect_move_angle_off_wall();
        }

        cur_obj_init_anim_extend(5);
        koopa_dive_update_speed(0.3f);
    } else if (o->oKoopaCountdown != 0) {
        o->oKoopaCountdown -= 1;
        cur_obj_extend_animation_if_at_end();
    } else if (cur_obj_init_anim_and_check_if_end(6)) {
        o->oAction = KOOPA_SHELLED_ACT_STOPPED;
    }
}

/**
 * Attack handler for regular-sized shelled koopa.
 * Lose shell and enter lying action.
 */
void shelled_koopa_attack_handler(s32 attackType) {
    if (o->header.gfx.scale[0] > 0.8f) {
        cur_obj_play_sound_2(SOUND_OBJ_KOOPA_DAMAGE);

        o->oKoopaMovementType = KOOPA_BP_UNSHELLED;
        o->oAction = KOOPA_UNSHELLED_ACT_LYING;
        o->oForwardVel = 20.0f;

        // If attacked from the side, get knocked away from mario
        if (attackType != ATTACK_FROM_ABOVE && attackType != ATTACK_GROUND_POUND_OR_TWIRL) {
            struct Object* player = nearest_player_to_object(o);
            if (player) {
                s32 angleToPlayer = obj_angle_to_object(o, player);
                o->oMoveAngleYaw = angleToPlayer;
            }
        }

        cur_obj_set_model(smlua_model_util_load(E_MODEL_KOOPA_WITHOUT_SHELL));

        struct MarioState* marioState = nearest_mario_state_to_object(o);
        if (marioState && marioState->playerIndex == 0) {
            struct Object* shell = spawn_object(o, MODEL_KOOPA_SHELL, bhvKoopaShell);
            if (shell != NULL) {
                sync_object_set_id(shell);

                struct Object* spawn_objects[] = { shell };
                u32 models[] = { MODEL_KOOPA_SHELL };
                network_send_spawn_objects(spawn_objects, models, 1);
            }
        }

        //! Because bob-ombs/corkboxes come after koopa in processing order,
        //  they can interact with the koopa on the same frame that this
        //  happens. This causes the koopa to die immediately.
        cur_obj_become_intangible();
    } else {
        // Die if tiny koopa
        obj_die_if_health_non_positive();
    }
}

/**
 * Update function for both regular and tiny shelled koopa.
 */
static void koopa_shelled_update(void) {
    u16 modelId = smlua_model_util_load(E_MODEL_KOOPA_WITH_SHELL);
    if (!cur_obj_has_model(modelId)) {
        cur_obj_set_model(modelId);
    }

    cur_obj_update_floor_and_walls();
    obj_update_blinking(&o->oKoopaBlinkTimer, 20, 50, 4);

    switch (o->oAction) {
        case KOOPA_SHELLED_ACT_STOPPED:
            koopa_shelled_act_stopped();
            koopa_check_run_from_mario();
            break;

        case KOOPA_SHELLED_ACT_WALK:
            koopa_shelled_act_walk();
            break;

        case KOOPA_SHELLED_ACT_RUN_FROM_MARIO:
            koopa_shelled_act_run_from_mario();
            break;

        case KOOPA_SHELLED_ACT_LYING:
            koopa_shelled_act_lying();
            break;
    }

    if (o->header.gfx.scale[0] > 0.8f) {
        obj_handle_attacks(&sKoopaHitbox, o->oAction, sKoopaShelledAttackHandlers);
    } else {
        // If tiny koopa, die after attacking mario.
        obj_handle_attacks(&sKoopaHitbox, KOOPA_SHELLED_ACT_DIE, sKoopaUnshelledAttackHandlers);
        if (o->oAction == KOOPA_SHELLED_ACT_DIE) {
            obj_die_if_health_non_positive();
        }
    }

    cur_obj_move_standard(-78);
}

/**
 * Attempt to run toward the shell if it exists while still running away from
 * mario. If the shell doesn't exist, run around randomly.
 * When close enough to the shell and with good angle and speed, enter the dive
 * action.
 */
static void koopa_unshelled_act_run(void) {
    s32 distanceToPlayer = o->oDistanceToMario;
    s32 angleToPlayer = o->oAngleToMario;

    f32 distToShell = 99999.0f;
    struct Object *shell;

    cur_obj_init_animation_with_sound(3);
    koopa_play_footstep_sound(0, 6);

    if (o->oKoopaTurningAwayFromWall) {
        o->oKoopaTurningAwayFromWall = obj_resolve_collisions_and_turn(o->oKoopaTargetYaw, 0x600);
    } else {

        // If far from home, then turn toward home
        if (distanceToPlayer >= 25000.0f) {
            o->oKoopaTargetYaw = angleToPlayer;
        }

        // If shell exists, then turn toward shell
        shell = cur_obj_find_nearest_object_with_behavior(bhvKoopaShell, &distToShell);
        if (shell != NULL) {
            //! This overrides turning toward home
            o->oKoopaTargetYaw = obj_angle_to_object(o, shell);
        } else if (!(o->oKoopaTurningAwayFromWall =
                         obj_bounce_off_walls_edges_objects(&o->oKoopaTargetYaw))) {
            // Otherwise run around randomly
            if (o->oKoopaUnshelledTimeUntilTurn != 0) {
                o->oKoopaUnshelledTimeUntilTurn -= 1;
            } else {
                o->oKoopaTargetYaw = obj_random_fixed_turn(0x2000);
            }
        }

        // If mario is far away, or our running away from mario coincides with
        // running toward the shell
        if (distanceToPlayer > 800.0f
            || (shell != NULL
                && abs_angle_diff(o->oKoopaTargetYaw, angleToPlayer + 0x8000) < 0x2000)) {
            // then turn toward the shell
            cur_obj_rotate_yaw_toward(o->oKoopaTargetYaw, 0x600);
        } else {
            // otherwise continue running from mario
            cur_obj_rotate_yaw_toward(angleToPlayer + 0x8000, 0x600);
        }
    }

    // If we think we have a shot, dive for the shell
    if (obj_forward_vel_approach(20.0f, 1.0f) && distToShell < 600.0f
        && abs_angle_diff(o->oKoopaTargetYaw, o->oMoveAngleYaw) < 0xC00) {
        o->oMoveAngleYaw = o->oKoopaTargetYaw;
        o->oAction = KOOPA_UNSHELLED_ACT_DIVE;
        o->oForwardVel *= 1.2f;
        o->oVelY = distToShell / 20.0f;
        o->oKoopaCountdown = 20;
    }
}

/**
 * Dive and slide along the ground. If close enough to the shell, pick it up,
 * and otherwise enter the running action.
 */
static void koopa_unshelled_act_dive(void) {
    struct Object *shell;
    f32 distToShell;

    if (o->oTimer > 10) {
        cur_obj_become_tangible();
    }

    if (o->oTimer > 10) {
        shell = cur_obj_find_nearest_object_with_behavior(bhvKoopaShell, &distToShell);

        s32 distanceToPlayer = o->oDistanceToMario;

        // If we got the shell and mario didn't, put on the shell
        //! The shell comes after koopa in processing order, and the shell is
        //  responsible for positioning itself under mario.
        //  If mario has more than 200 speed and is riding the shell, then
        //  from the perspective of the koopa, the shell is always lagging 200
        //  units behind mario.
        //  Using this, we can get the koopa to pick up and despawn its shell
        //  while mario is riding it.
        if (shell != NULL && distanceToPlayer && distToShell < 50.0f) {
            o->oKoopaMovementType = KOOPA_BP_NORMAL;
            o->oAction = KOOPA_SHELLED_ACT_LYING;
            o->oForwardVel *= 0.5f;

            cur_obj_set_model(smlua_model_util_load(E_MODEL_KOOPA_WITH_SHELL));
            obj_mark_for_deletion(shell);
            goto end;
        }
    }

    if (o->oForwardVel != 0.0f) {
        if (o->oAction == KOOPA_UNSHELLED_ACT_LYING) {
            o->oAnimState = 1;
            cur_obj_init_anim_extend(2);
        } else {
            cur_obj_init_anim_extend(5);
        }
        koopa_dive_update_speed(0.5f);
    } else if (o->oKoopaCountdown != 0) {
        o->oKoopaCountdown -= 1;
        cur_obj_extend_animation_if_at_end();
    } else if (cur_obj_init_anim_and_check_if_end(6)) {
        o->oAction = KOOPA_UNSHELLED_ACT_RUN;
    }

end:;
}

/**
 * Unused action function.
 */
static void koopa_unshelled_act_unused3(void) {
    cur_obj_init_anim_extend(0);
}

/**
 * Update function for koopa after losing his shell.
 */
static void koopa_unshelled_update(void) {
    u16 modelId = smlua_model_util_load(E_MODEL_KOOPA_WITHOUT_SHELL);
    if (!cur_obj_has_model(modelId)) {
        cur_obj_set_model(modelId);
    }

    cur_obj_update_floor_and_walls();
    obj_update_blinking(&o->oKoopaBlinkTimer, 10, 15, 3);

    switch (o->oAction) {
        case KOOPA_UNSHELLED_ACT_RUN:
            koopa_unshelled_act_run();
            break;
        case KOOPA_UNSHELLED_ACT_DIVE:
        case KOOPA_UNSHELLED_ACT_LYING:
            koopa_unshelled_act_dive();
            break;
        case KOOPA_UNSHELLED_ACT_UNUSED3:
            koopa_unshelled_act_unused3();
            break;
    }

    obj_handle_attacks(&sKoopaHitbox, o->oAction, sKoopaUnshelledAttackHandlers);
    cur_obj_move_standard(-78);
}

/**
 * Wait 50 frames, then play the race starting sound, disable time stop, and
 * optionally begin the timer.
 */
s32 obj_begin_race(s32 noTimer) {
    if (o->oTimer == 50) {
        cur_obj_play_sound_2(SOUND_GENERAL_RACE_GUN_SHOT);

        if (!noTimer) {
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_LEVEL_SLIDE), 0);

            level_control_timer(TIMER_CONTROL_SHOW);
            level_control_timer(TIMER_CONTROL_START);

            if (o->parentObj) { o->parentObj->oKoopaRaceEndpointRaceBegun = TRUE; }
        }

        // Unfreeze mario and disable time stop to begin the race
        set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
        disable_time_stop_including_mario();
    } else if (o->oTimer > 50) {
        return TRUE;
    }

    return FALSE;
}

/**
 * Wait for mario to approach, and then enter the show init text action.
 */
static void koopa_the_quick_act_wait_before_race(void) {
    koopa_shelled_act_stopped();

    struct MarioState* marioState = nearest_mario_state_to_object(o);

    if (o->oKoopaTheQuickInitTextboxCooldown != 0) {
        o->oKoopaTheQuickInitTextboxCooldown -= 1;
    } else if (marioState == &gMarioStates[0] && cur_obj_can_mario_activate_textbox_2(&gMarioStates[0], 400.0f, 400.0f)) {
        //! The next action doesn't execute until next frame, giving mario one
        //  frame where he can jump, and thus no longer be ready to speak.
        //  (On J, he has two frames and doing this enables time stop - see
        //  cur_obj_update_dialog_with_cutscene for that glitch)
        o->oAction = KOOPA_THE_QUICK_ACT_SHOW_INIT_TEXT;
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(7);
    }
}

u8 koopa_the_quick_act_show_init_text_continue_dialog(void) { return o->oAction == KOOPA_THE_QUICK_ACT_SHOW_INIT_TEXT; }

/**
 * Display the dialog asking mario if he wants to race. Begin the race or
 * return to the waiting action.
 */
static void koopa_the_quick_act_show_init_text(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    s32 response = 0;
    if (marioState && should_start_or_continue_dialog(marioState, o) && BHV_ARR_CHECK(sKoopaTheQuickProperties, o->oKoopaTheQuickRaceIndex, struct KoopaTheQuickProperties)) {
        response = obj_update_race_proposition_dialog(&gMarioStates[0], *sKoopaTheQuickProperties[o->oKoopaTheQuickRaceIndex].initText, koopa_the_quick_act_show_init_text_continue_dialog);
    }

    if (response == 1) {
        UNUSED s32 unused;

        gMarioShotFromCannon = FALSE;
        o->oAction = KOOPA_THE_QUICK_ACT_RACE;
        o->oForwardVel = 0.0f;

        o->parentObj = cur_obj_nearest_object_with_behavior(bhvKoopaRaceEndpoint);
        o->oPathedStartWaypoint = o->oPathedPrevWaypoint = (o->oKoopaTheQuickRaceIndex == 0)
               ? (struct Waypoint*) gBehaviorValues.trajectories.KoopaBobTrajectory
               : (struct Waypoint*) gBehaviorValues.trajectories.KoopaThiTrajectory;

        o->oKoopaTurningAwayFromWall = FALSE;
        o->oFlags |= OBJ_FLAG_ACTIVE_FROM_AFAR;

        network_send_object(o);
    } else if (response == 2) {
        o->oAction = KOOPA_THE_QUICK_ACT_WAIT_BEFORE_RACE;
        o->oKoopaTheQuickInitTextboxCooldown = 60;
    }
}

/**
 * If there is a bowling ball nearby, either slow down, or return +/-1 to
 * indicate that the ball is likely to collide.
 */
static s32 koopa_the_quick_detect_bowling_ball(void) {
    struct Object *ball;
    f32 distToBall;
    s16 angleToBall;
    f32 ballSpeedInKoopaRunDir;

    ball = cur_obj_find_nearest_object_with_behavior(bhvBowlingBall, &distToBall);
    if (ball != NULL) {
        angleToBall = obj_turn_toward_object(o, ball, O_MOVE_ANGLE_YAW_INDEX, 0);
        ballSpeedInKoopaRunDir = ball->oForwardVel * coss(ball->oMoveAngleYaw - o->oMoveAngleYaw);

        if (abs_angle_diff(o->oMoveAngleYaw, angleToBall) < 0x4000) {
            // The ball is in front of ktq

            if (distToBall < 400.0f) {
                if (ballSpeedInKoopaRunDir < o->oForwardVel * 0.7f) {
                    // The ball is moving slowly or toward him
                    return 1;
                } else {
                    // The ball is moving relatively quickly, so we'll just
                    // slow down a bit
                    //! This can go negative and is unbounded. If placed next to
                    //  oob, ktq can get PU speed.
                    o->oForwardVel -= 2.0f;
                }
            }
        } else if (distToBall < 300.0f && ballSpeedInKoopaRunDir > o->oForwardVel) {
            // The ball is coming at ktq from behind, and it's moving faster
            // than him
            return -1;
        }
    }

    return 0;
}

/**
 * Play the running animation at a speed proportional to ktq's forward velocity.
 * If he is moving backward, then the animation will play backward.
 */
static void koopa_the_quick_animate_footsteps(void) {
    //! With high negative speed (using the bowling ball deceleration), we can
    //  index out of the animation's bounds
    cur_obj_init_animation_with_accel_and_sound(9, o->oForwardVel * 0.09f);
    koopa_play_footstep_sound(2, 17);
}

/**
 * Begin the race, then follow the race path. Avoid bowling balls by slowing
 * down or jumping. After finishing the race, enter the decelerate action.
 */
static void koopa_the_quick_act_race(void) {
    f32 downhillSteepness;
    s32 bowlingBallStatus;

    if (obj_begin_race(FALSE)) {
        // Hitbox is slightly larger while racing
        cur_obj_push_mario_away_from_cylinder(180.0f, 300.0f);

        struct Waypoint* lastPrevWaypoint = o->oPathedPrevWaypoint;
        if (cur_obj_follow_path(0) == PATH_REACHED_END) {
            o->oAction = KOOPA_THE_QUICK_ACT_DECELERATE;
            if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
        } else {
            downhillSteepness = 1.0f + sins((s16)(f32) o->oPathedTargetPitch);
            cur_obj_rotate_yaw_toward(o->oPathedTargetYaw, (s32)(o->oKoopaAgility * 150.0f));

            switch (o->oSubAction) {
                case KOOPA_THE_QUICK_SUB_ACT_START_RUN:
                    koopa_walk_start();
                    break;

                case KOOPA_THE_QUICK_SUB_ACT_RUN:
                    koopa_the_quick_animate_footsteps();

                    struct Object* player = nearest_player_to_object(o);
                    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;

                    if (o->parentObj  && o->parentObj->oKoopaRaceEndpointRaceStatus != 0 && distanceToPlayer > 1500.0f
                        && (o->oPathedPrevWaypointFlags & WAYPOINT_MASK_00FF) < 28) {
                        // Move faster if mario has already finished the race or
                        // cheated by shooting from cannon
                        o->oKoopaAgility = gBehaviorValues.KoopaCatchupAgility;
                    } else if (o->oKoopaTheQuickRaceIndex != KOOPA_THE_QUICK_BOB_INDEX) {
                        o->oKoopaAgility = gBehaviorValues.KoopaThiAgility;
                    } else {
                        o->oKoopaAgility = gBehaviorValues.KoopaBobAgility;
                    }

                    obj_forward_vel_approach(o->oKoopaAgility * 6.0f * downhillSteepness,
                                             o->oKoopaAgility * 0.1f);

                    // Move upward if we hit a wall, to climb it
                    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
                        o->oVelY = 20.0f;
                    }

                    // If we're about to collide with a bowling ball or we hit an
                    // edge, jump
                    bowlingBallStatus = koopa_the_quick_detect_bowling_ball();
                    if (bowlingBallStatus != 0 || (o->oMoveFlags & OBJ_MOVE_HIT_EDGE)) {
                        // If the ball is coming at us from behind, then set speed
                        // to zero to let it move under and past us
                        if (bowlingBallStatus < 0) {
                            o->oForwardVel = 0.0f;
                        }

                        if (bowlingBallStatus != 0
                            || (o->oPathedPrevWaypointFlags & WAYPOINT_MASK_00FF) >= 8) {
                            o->oVelY = 80.0f;
                        } else {
                            o->oVelY = 40.0f;
                        }

                        o->oGravity = -6.0f;
                        o->oSubAction = 2;
                        o->oMoveFlags = 0;

                        cur_obj_init_animation_with_sound(12);
                    }
                    break;

                case KOOPA_THE_QUICK_SUB_ACT_JUMP:
                    // We could perform a goomba double jump if we could deactivate
                    // ktq
                    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                        if (cur_obj_init_anim_and_check_if_end(13)) {
                            o->oSubAction -= 1;
                        }

                        koopa_the_quick_detect_bowling_ball();
                    }
            }
        }

        if (lastPrevWaypoint != o->oPathedPrevWaypoint) {
            if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
        }
    }
}

/**
 * Decelerate and then enter the stop action.
 */
static void koopa_the_quick_act_decelerate(void) {
    obj_forward_vel_approach(3.0f, 1.0f);
    cur_obj_init_animation_with_accel_and_sound(9, 0.99f);

    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = KOOPA_THE_QUICK_ACT_STOP;
        o->oForwardVel = 3.0f;
        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
    }
}

/**
 * Stop and then enter the after race action.
 */
static void koopa_the_quick_act_stop(void) {
    koopa_walk_stop();

    // koopa_walk_stop() was written for shelled koopa, so it enters the
    // KOOPA_SHELLED_ACT_STOPPED at the end
    if (o->oAction == KOOPA_SHELLED_ACT_STOPPED) {
        o->oAction = KOOPA_THE_QUICK_ACT_AFTER_RACE;
        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
    }
}

u8 koopa_the_quick_act_after_race_continue_dialog(void) { return o->oAction == KOOPA_THE_QUICK_ACT_AFTER_RACE && o->parentObj->oKoopaRaceEndpointUnk100 > 0; }

/**
 * Wait for mario to approach, then show text indicating the status of the race.
 * If mario got to the finish line first and didn't use the cannon, then spawn
 * the star.
 */
static void koopa_the_quick_act_after_race(void) {
    cur_obj_init_animation_with_sound(7);

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!o->parentObj) { return; }

    if (o->parentObj->oKoopaRaceEndpointUnk100 == 0) {
        if (marioState == &gMarioStates[0] && cur_obj_can_mario_activate_textbox_2(&gMarioStates[0], 400.0f, 400.0f)) {
            stop_background_music(SEQUENCE_ARGS(4, SEQ_LEVEL_SLIDE));

            // Determine which text to display

            if (o->parentObj->oKoopaRaceEndpointRaceStatus != 0) {
                if (o->parentObj->oKoopaRaceEndpointRaceStatus < 0) {
                    // Mario cheated
                    o->parentObj->oKoopaRaceEndpointRaceStatus = 0;
                    o->parentObj->oKoopaRaceEndpointUnk100 = gBehaviorValues.dialogs.KoopaQuickCheatedDialog;
                } else {
                    // Mario won
                    o->parentObj->oKoopaRaceEndpointUnk100 = *sKoopaTheQuickProperties[o->oKoopaTheQuickRaceIndex].winText;
                }
            } else {
                // KtQ won
                o->parentObj->oKoopaRaceEndpointUnk100 = gBehaviorValues.dialogs.KoopaQuickLostDialog;
            }

            o->oFlags &= ~OBJ_FLAG_ACTIVE_FROM_AFAR;
        }
    } else if (o->parentObj->oKoopaRaceEndpointUnk100 > 0) {
        if (marioState && should_start_or_continue_dialog(marioState, o)) {
            s32 dialogResponse = cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 2, 1, CUTSCENE_DIALOG, o->parentObj->oKoopaRaceEndpointUnk100, koopa_the_quick_act_after_race_continue_dialog);
            if (dialogResponse != 0) {
                o->parentObj->oKoopaRaceEndpointUnk100 = -1;
                o->oTimer = 0;
            }
        }
    } else if (o->parentObj->oKoopaRaceEndpointRaceStatus != 0) {
        if (o->oKoopaTheQuickRaceIndex == 0) {
            f32* starPos = gLevelValues.starPositions.KoopaBobStarPos;
            spawn_default_star(starPos[0], starPos[1], starPos[2]);
        } else {
            f32* starPos = gLevelValues.starPositions.KoopaThiStarPos;
            spawn_default_star(starPos[0], starPos[1], starPos[2]);
        }

        o->parentObj->oKoopaRaceEndpointRaceStatus = 0;
    }
}

/**
 * Update function for koopa the quick.
 */
static void koopa_the_quick_update(void) {
    cur_obj_update_floor_and_walls();
    obj_update_blinking(&o->oKoopaBlinkTimer, 10, 15, 3);

    switch (o->oAction) {
        case KOOPA_THE_QUICK_ACT_WAIT_BEFORE_RACE:
        case KOOPA_THE_QUICK_ACT_UNUSED1:
            koopa_the_quick_act_wait_before_race();
            break;
        case KOOPA_THE_QUICK_ACT_SHOW_INIT_TEXT:
            koopa_the_quick_act_show_init_text();
            break;
        case KOOPA_THE_QUICK_ACT_RACE:
            koopa_the_quick_act_race();
            break;
        case KOOPA_THE_QUICK_ACT_DECELERATE:
            koopa_the_quick_act_decelerate();
            break;
        case KOOPA_THE_QUICK_ACT_STOP:
            koopa_the_quick_act_stop();
            break;
        case KOOPA_THE_QUICK_ACT_AFTER_RACE:
            koopa_the_quick_act_after_race();
            break;
    }

    if (o->parentObj != o && o->parentObj) {
        if (dist_between_objects(o, o->parentObj) < 400.0f) {
            o->parentObj->oKoopaRaceEndpointKoopaFinished = TRUE;
        }
    }

    cur_obj_move_standard(-78);
}

/**
 * Update function.
 */
void bhv_koopa_update(void) {
    // PARTIAL_UPDATE
    o->oDeathSound = SOUND_OBJ_KOOPA_FLYGUY_DEATH;

    if (o->oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE) {
        koopa_the_quick_update();
    } else if (obj_update_standard_actions(o->oKoopaAgility * 1.5f)) {
        struct Object* player = nearest_player_to_object(o);
        s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
        s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

        o->oKoopaDistanceToMario = distanceToPlayer;
        o->oKoopaAngleToMario = angleToPlayer;

        treat_far_home_as_mario(1000.0f, &distanceToPlayer, &angleToPlayer);
        o->oDistanceToMario = distanceToPlayer;
        o->oAngleToMario = angleToPlayer;

        switch (o->oKoopaMovementType) {
            case KOOPA_BP_UNSHELLED:
                koopa_unshelled_update();
                break;
            case KOOPA_BP_NORMAL:
                koopa_shelled_update();
                break;
            case KOOPA_BP_KOOPA_THE_QUICK_BOB:
            case KOOPA_BP_KOOPA_THE_QUICK_THI:
                koopa_the_quick_update();
                break;
        }
    } else {
        o->oAnimState = 1;
    }

    obj_face_yaw_approach(o->oMoveAngleYaw, 0x600);
}

/**
 * Update function for bhvKoopaRaceEndpoint.
 */
void bhv_koopa_race_endpoint_update(void) {
    if (o->oKoopaRaceEndpointRaceBegun && !o->oKoopaRaceEndpointRaceEnded) {
        struct Object* player = nearest_player_to_object(o);
        s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
        if (o->oKoopaRaceEndpointKoopaFinished || distanceToPlayer < 400.0f) {
            o->oKoopaRaceEndpointRaceEnded = TRUE;
            level_control_timer(TIMER_CONTROL_STOP);

            if (!o->oKoopaRaceEndpointKoopaFinished) {
                play_race_fanfare();
                if (gMarioShotFromCannon) {
                    o->oKoopaRaceEndpointRaceStatus = -1;
                } else {
                    o->oKoopaRaceEndpointRaceStatus = 1;
                }
            }
        }
    }
}
