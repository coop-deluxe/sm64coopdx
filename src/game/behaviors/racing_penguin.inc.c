struct RacingPenguinData {
    s16* text;
    f32* radius;
    f32* height;
};

static struct RacingPenguinData sRacingPenguinData[] = {
    { (s16*) &gBehaviorValues.dialogs.RacingPenguinStartDialog, &gBehaviorValues.RacingPenguinRadius, &gBehaviorValues.RacingPenguinHeight },
    { (s16*) &gBehaviorValues.dialogs.RacingPenguinBigStartDialog, &gBehaviorValues.RacingPenguinBigRadius, &gBehaviorValues.RacingPenguinBigHeight },
};

static u32 penguinPathedStartWaypoint = 0;
static u32 penguinPathedPrevWaypoint = 0;

static void bhv_racing_penguin_the_quick_on_received_post(UNUSED u8 fromLocalIndex) {
    void* path = segmented_to_virtual(gBehaviorValues.trajectories.RacingPenguinTrajectory);
    o->oPathedStartWaypoint = (struct Waypoint*)path + penguinPathedStartWaypoint;
    o->oPathedPrevWaypoint  = (struct Waypoint*)path + penguinPathedPrevWaypoint;
}

static void bhv_racing_penguin_the_quick_on_sent_pre(void) {
    void* path = segmented_to_virtual(gBehaviorValues.trajectories.RacingPenguinTrajectory);
    penguinPathedStartWaypoint = ((void*)o->oPathedStartWaypoint - path) / sizeof(struct Waypoint*);
    penguinPathedPrevWaypoint  = ((void*)o->oPathedPrevWaypoint - path) / sizeof(struct Waypoint*);
}

void bhv_racing_penguin_the_quick_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = TRUE;
    *shouldOwn = (get_network_player_smallest_global() == gNetworkPlayerLocal);
}

void bhv_racing_penguin_run_once(void) {
    cur_obj_align_gfx_with_floor();
    if (BHV_ARR_CHECK(sRacingPenguinData, o->oBehParams2ndByte, struct RacingPenguinData)) {
        cur_obj_push_mario_away_from_cylinder(
            *sRacingPenguinData[o->oBehParams2ndByte].radius,
            *sRacingPenguinData[o->oBehParams2ndByte].height);
    }
}

void bhv_racing_penguin_init(void) {
    if (gMarioStates[0].numStars == 120) {
        cur_obj_scale(8.0f);
        o->header.gfx.scale[1] = 5.0f;
        o->oBehParams2ndByte = 1;
    }

    struct Object* objFinishLine = cur_obj_nearest_object_with_behavior(bhvPenguinRaceFinishLine);
    if (objFinishLine) { objFinishLine->parentObj = o; }

    struct Object* objShortcutCheck = cur_obj_nearest_object_with_behavior(bhvPenguinRaceShortcutCheck);
    if (objShortcutCheck) { objShortcutCheck->parentObj = o; }

    struct SyncObject* so  = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    if (so) {
        so->on_received_post   = bhv_racing_penguin_the_quick_on_received_post;
        so->on_sent_pre        = bhv_racing_penguin_the_quick_on_sent_pre;
        so->override_ownership = bhv_racing_penguin_the_quick_override_ownership;
        sync_object_init_field(o, &penguinPathedStartWaypoint);
        sync_object_init_field(o, &penguinPathedPrevWaypoint);
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
        sync_object_init_field(o, &o->oForwardVel);
        sync_object_init_field(o, &o->oMoveAngleYaw);
        sync_object_init_field(o, &o->oRacingPenguinWeightedNewTargetSpeed);
        sync_object_init_field(o, &o->oRacingPenguinMarioWon);
        sync_object_init_field(o, &o->oRacingPenguinReachedBottom);
        sync_object_init_field(o, &o->areaTimer);
    }
    o->areaTimerType = AREA_TIMER_TYPE_MAXIMUM;
    o->areaTimer = 0;
    o->areaTimerDuration = 60;
    o->areaTimerRunOnceCallback = bhv_racing_penguin_run_once;
}

static void racing_penguin_act_wait_for_mario(void) {
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return; }
    if (o->oTimer > o->oRacingPenguinInitTextCooldown && o->oPosY - player->oPosY <= 0.0f
        && cur_obj_can_mario_activate_textbox_2(&gMarioStates[0], 400.0f, 400.0f)) {
        o->oAction = RACING_PENGUIN_ACT_SHOW_INIT_TEXT;
    }
}

u8 racing_penguin_act_show_init_text_continue_dialog(void) { return o->oAction == RACING_PENGUIN_ACT_SHOW_INIT_TEXT; }

static void racing_penguin_act_show_init_text(void) {
    if (!gMarioStates[0].visibleToEnemies) { return; }
    if (!BHV_ARR_CHECK(sRacingPenguinData, o->oBehParams2ndByte, struct RacingPenguinData)) { return; }
    s32 response = obj_update_race_proposition_dialog(&gMarioStates[0], *sRacingPenguinData[o->oBehParams2ndByte].text, racing_penguin_act_show_init_text_continue_dialog);

    if (response == 1) {
        struct Object *child;

        child = cur_obj_nearest_object_with_behavior(bhvPenguinRaceFinishLine);
        child->parentObj = o;

        child = cur_obj_nearest_object_with_behavior(bhvPenguinRaceShortcutCheck);
        child->parentObj = o;

        o->oPathedStartWaypoint = o->oPathedPrevWaypoint =
            segmented_to_virtual(gBehaviorValues.trajectories.RacingPenguinTrajectory);
        o->oPathedPrevWaypointFlags = 0;

        o->oAction = RACING_PENGUIN_ACT_PREPARE_FOR_RACE;
        o->oVelY = 60.0f;

        network_send_object(o);
    } else if (response == 2) {
        o->oAction = RACING_PENGUIN_ACT_WAIT_FOR_MARIO;
        o->oRacingPenguinInitTextCooldown = 60;
    }
}

static void racing_penguin_act_prepare_for_race(void) {
    if (obj_begin_race(TRUE)) {
        o->oAction = RACING_PENGUIN_ACT_RACE;
        o->oForwardVel = 20.0f;
        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
    }

    cur_obj_rotate_yaw_toward(0x4000, 2500);
}

static void racing_penguin_act_race(void) {
    f32 targetSpeed;
    f32 minSpeed;

    // prevent segfault / error state
    if (o->oPathedStartWaypoint == NULL) {
        struct Object* child = NULL;
        child = cur_obj_nearest_object_with_behavior(bhvPenguinRaceFinishLine);
        if (child) { child->parentObj = o; }

        child = cur_obj_nearest_object_with_behavior(bhvPenguinRaceShortcutCheck);
        if (child) { child->parentObj = o; }

        o->oPathedStartWaypoint = o->oPathedPrevWaypoint = segmented_to_virtual(gBehaviorValues.trajectories.RacingPenguinTrajectory);
        o->oPathedPrevWaypointFlags = 0;
    }

    struct Waypoint* lastPrevWaypoint = o->oPathedPrevWaypoint;
    if (cur_obj_follow_path(0) == PATH_REACHED_END) {
        o->oRacingPenguinReachedBottom = TRUE;
        o->oAction = RACING_PENGUIN_ACT_FINISH_RACE;
        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
    } else {
        struct Object* player = nearest_player_to_object(o);
        targetSpeed = player ? (o->oPosY - player->oPosY) : o->oPosY;
        minSpeed = 70.0f;

        cur_obj_play_sound_1(SOUND_AIR_ROUGH_SLIDE);

        if (targetSpeed < 100.0f || (o->oPathedPrevWaypointFlags & WAYPOINT_MASK_00FF) >= 35) {
            if ((o->oPathedPrevWaypointFlags & WAYPOINT_MASK_00FF) >= 35) {
                minSpeed = 60.0f;
            }

            approach_f32_ptr(&o->oRacingPenguinWeightedNewTargetSpeed, -500.0f, 100.0f);
        } else {
            approach_f32_ptr(&o->oRacingPenguinWeightedNewTargetSpeed, 1000.0f, 30.0f);
        }

        targetSpeed = 0.1f * (o->oRacingPenguinWeightedNewTargetSpeed + targetSpeed);
        clamp_f32(&targetSpeed, minSpeed, 150.0f);
        obj_forward_vel_approach(targetSpeed, 0.4f);

        cur_obj_init_animation_with_sound(1);
        cur_obj_rotate_yaw_toward(o->oPathedTargetYaw, (s32)(15.0f * o->oForwardVel));

        if (cur_obj_check_if_at_animation_end() && (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND)) {
            spawn_object_relative_with_scale(0, 0, -100, 0, 4.0f, o, MODEL_SMOKE, bhvWhitePuffSmoke2);
        }
    }

    // Removed the in-air shortcut check due to inconsistent detection and the
    // fact that one player can fall off while the other player completes the
    // race.
    /*u8 isInAir = FALSE;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        isInAir = isInAir || mario_is_in_air_action(&gMarioStates[i]);
    }

    if (isInAir) {
        if (o->oTimer > 60 && !o->oRacingPenguinMarioCheated) {
            o->oRacingPenguinMarioCheated = TRUE;
            network_send_object(o);
        }
    } else {
        o->oTimer = 0;
    }*/

    if (lastPrevWaypoint != o->oPathedPrevWaypoint) {
        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
    }
}

static void racing_penguin_act_finish_race(void) {
    if (o->oForwardVel != 0.0f) {
        if (o->oTimer > 5 && (o->oMoveFlags & OBJ_MOVE_HIT_WALL)) {
            cur_obj_play_sound_2(SOUND_OBJ_POUNDING_LOUD);
            set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
            o->oForwardVel = 0.0f;
        }
    } else if (cur_obj_init_anim_and_check_if_end(2) != 0) {
        o->oAction = RACING_PENGUIN_ACT_SHOW_FINAL_TEXT;
    }
}

u8 racing_penguin_act_show_final_text_continue_dialog(void) { return o->oAction == RACING_PENGUIN_ACT_SHOW_FINAL_TEXT && o->oRacingPenguinFinalTextbox > 0; }

static void racing_penguin_act_show_final_text(void) {
    s32 textResult;

    if (o->oRacingPenguinFinalTextbox == 0) {
        if (cur_obj_rotate_yaw_toward(0, 200)) {
            cur_obj_init_animation_with_sound(3);
            o->oForwardVel = 0.0f;

            if (cur_obj_can_mario_activate_textbox_2(&gMarioStates[0], 400.0f, 400.0f)) {
                if (o->oRacingPenguinMarioWon) {
                    if (o->oRacingPenguinMarioCheated) {
                        o->oRacingPenguinFinalTextbox = gBehaviorValues.dialogs.RacingPenguinCheatDialog;
                        o->oRacingPenguinMarioWon = FALSE;
                    } else {
                        o->oRacingPenguinFinalTextbox = gBehaviorValues.dialogs.RacingPenguinWinDialog;
                    }
                } else {
                    o->oRacingPenguinFinalTextbox = gBehaviorValues.dialogs.RacingPenguinLostDialog;
                }
            }
        } else {
            cur_obj_init_animation_with_sound(0);

#ifndef VERSION_JP
            play_penguin_walking_sound(1);
#endif

            o->oForwardVel = 4.0f;
        }
    } else if (o->oRacingPenguinFinalTextbox > 0) {
        if ((textResult = cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 2, 1, CUTSCENE_DIALOG, o->oRacingPenguinFinalTextbox, racing_penguin_act_show_final_text_continue_dialog)) != 0) {
            o->oRacingPenguinFinalTextbox = -1;
            o->oTimer = 0;
        }
    } else if (o->oRacingPenguinMarioWon) {

    f32* starPos = gLevelValues.starPositions.RacingPenguinStarPos;
#ifdef VERSION_JP
        spawn_default_star(starPos[0], starPos[1], starPos[2]);
#else
        cur_obj_spawn_star_at_y_offset(starPos[0], starPos[1], starPos[2], 200.0f);
#endif
        o->oRacingPenguinMarioWon = FALSE;
        if (sync_object_is_owned_locally(o->oSyncID)) { network_send_object(o); }
    }
}

void bhv_racing_penguin_update(void) {
    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case RACING_PENGUIN_ACT_WAIT_FOR_MARIO:
            racing_penguin_act_wait_for_mario();
            break;
        case RACING_PENGUIN_ACT_SHOW_INIT_TEXT:
            racing_penguin_act_show_init_text();
            break;
        case RACING_PENGUIN_ACT_PREPARE_FOR_RACE:
            racing_penguin_act_prepare_for_race();
            break;
        case RACING_PENGUIN_ACT_RACE:
            racing_penguin_act_race();
            break;
        case RACING_PENGUIN_ACT_FINISH_RACE:
            racing_penguin_act_finish_race();
            break;
        case RACING_PENGUIN_ACT_SHOW_FINAL_TEXT:
            racing_penguin_act_show_final_text();
            break;
    }

    cur_obj_move_standard(78);
}

void bhv_penguin_race_finish_line_update(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    if (!o->parentObj) {
        return;
    }

    if (o->parentObj->oRacingPenguinReachedBottom
        || (player && distanceToPlayer < 1000.0f && player->oPosZ - o->oPosZ < 0.0f)) {
        if (!o->parentObj->oRacingPenguinReachedBottom && !o->parentObj->oRacingPenguinMarioWon) {
            o->parentObj->oRacingPenguinMarioWon = TRUE;
            network_send_object(o->parentObj);
        }
    }
}

void bhv_penguin_race_shortcut_check_update(void) {
    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    if (distanceToPlayer < 500.0f && o->parentObj && !o->parentObj->oRacingPenguinMarioCheated) {
        o->parentObj->oRacingPenguinMarioCheated = TRUE;
        network_send_object(o->parentObj);
    }
}
