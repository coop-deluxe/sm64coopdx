// yoshi.c.inc

// X/Z coordinates of Yoshi's homes that he switches between.
// Note that this doesn't contain the Y coordinate since the castle roof is flat,
// so o->oHomeY is never updated.
static s16 sYoshiHomeLocations[] = { 0, -5625, -1364, -5912, -1403, -4609, -1004, -5308 };
static s16 sYoshiRespawnPos[] = { -12406, 1076, -8567 };
static u8 sYoshiRespawnDuration = 2 * 30;
static u8 sYoshiTalkingState = 0;
static bool sYoshiNeeded = false;

extern void push_mario_out_of_object(struct MarioState *m, struct Object *o, f32 padding);

static u8 yoshi_talk_loop_continue_dialog(void) {
    return sYoshiTalkingState == 0 || sYoshiTalkingState == 1;
}

void bhv_yoshi_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = o->oAction == YOSHI_ACT_TALK;
    *shouldOwn = false;
    if (*shouldOverride) {
        *shouldOwn = (gNetworkPlayerLocal->globalIndex == o->globalPlayerIndex);
    }
}

void bhv_yoshi_init(void) {
    sOverrideYoshiAlive = false;
    sYoshiTalkingState = 0;
    o->oGravity = 2.0f;
    o->oFriction = 0.9f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;

    if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) < 120) {
        o->oAction = YOSHI_ACT_GONE;
    }

    struct SyncObject* so = sync_object_init(o, 4000.0f);
    if (so != NULL) {
        so->override_ownership = bhv_yoshi_override_ownership;
        sync_object_init_field(o, o->oYoshiBlinkTimer);
        sync_object_init_field(o, o->oYoshiChosenHome);
        sync_object_init_field(o, o->oYoshiTargetYaw);
        sync_object_init_field(o, o->oHomeX);
        sync_object_init_field(o, o->oHomeY);
        sync_object_init_field(o, o->oHomeZ);
        sync_object_init_field(o, o->oAction);
        sync_object_init_field_with_size(o, o->globalPlayerIndex, 8);
    }
}

void yoshi_walk_loop(void) {
    sYoshiTalkingState = 0;
    cur_obj_become_tangible();
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    o->oForwardVel = 10.0f;
    object_step();
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x500);
    if (is_point_close_to_object(o, o->oHomeX, 3174.0f, o->oHomeZ, 200))
        o->oAction = YOSHI_ACT_IDLE;

    cur_obj_init_animation(1);
    if (animFrame == 0 || animFrame == 15)
        cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);

    if (o->oInteractStatus == INT_STATUS_INTERACTED) {
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        o->globalPlayerIndex = gNetworkPlayers[marioState->playerIndex].globalIndex;
        o->oAction = YOSHI_ACT_TALK;
    }

    if (o->oPosY < 2100.0f) {
        create_respawner(MODEL_YOSHI, bhvYoshi, 3000);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void yoshi_idle_loop(void) {
    sYoshiTalkingState = 0;
    cur_obj_become_tangible();
    s16 chosenHome;

    if (o->oTimer > 90) {
        chosenHome = random_float() * 3.99;

        if (o->oYoshiChosenHome == chosenHome) {
            return;
        } else {
            o->oYoshiChosenHome = chosenHome;
        }

        o->oHomeX = sYoshiHomeLocations[o->oYoshiChosenHome * 2];
        o->oHomeZ = sYoshiHomeLocations[o->oYoshiChosenHome * 2 + 1];
        o->oYoshiTargetYaw = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
        o->oAction = YOSHI_ACT_WALK;
    }

    cur_obj_init_animation(0);
    if (o->oInteractStatus == INT_STATUS_INTERACTED) {
        struct MarioState* marioState = nearest_mario_state_to_object(o);
        o->globalPlayerIndex = gNetworkPlayers[marioState->playerIndex].globalIndex;
        o->oAction = YOSHI_ACT_TALK;
    }

    // Credits; Yoshi appears at this position overlooking the castle near the end of the credits
    if (gPlayerCameraState->cameraEvent == CAM_EVENT_START_ENDING ||
        gPlayerCameraState->cameraEvent == CAM_EVENT_START_END_WAVING ||
        gDjuiInMainMenu) {
        o->oAction = YOSHI_ACT_CREDITS;
        o->oPosX = -1798.0f;
        o->oPosY = 3174.0f;
        o->oPosZ = -3644.0f;
    }
}

void yoshi_talk_loop(void) {
    cur_obj_become_intangible();
    sYoshiTalkingState = 1;
    push_mario_out_of_object(&gMarioStates[0], o, -10.0f);
    struct NetworkPlayer* np = network_player_from_global_index(o->globalPlayerIndex);
    struct MarioState* marioState = &gMarioStates[np->localIndex];
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    if (np->localIndex != 0) {
        cur_obj_init_animation((s16) o->oMoveAngleYaw == angleToPlayer ? 0 : 1);
        return;
    }

    if ((s16) o->oMoveAngleYaw == angleToPlayer) {
        cur_obj_init_animation(0);
        if (set_mario_npc_dialog(&gMarioStates[0], 1, yoshi_talk_loop_continue_dialog) == 2) {
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, gBehaviorValues.dialogs.YoshiDialog)) {
                o->oInteractStatus = 0;
                o->oHomeX = sYoshiHomeLocations[2];
                o->oHomeZ = sYoshiHomeLocations[3];
                o->oYoshiTargetYaw = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
                o->oAction = YOSHI_ACT_GIVE_PRESENT;
            }
        }
    } else {
        cur_obj_init_animation(1);
        play_puzzle_jingle();
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, angleToPlayer, 0x500);
    }
}

void yoshi_walk_and_jump_off_roof_loop(void) {
    push_mario_out_of_object(&gMarioStates[0], o, -10.0f);
    cur_obj_become_intangible();
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    o->oForwardVel = 10.0f;
    object_step();
    cur_obj_init_animation(1);
    if (o->oTimer == 0
    && o->globalPlayerIndex == gNetworkPlayerLocal->globalIndex
    && gMarioStates[0].interactObj == o
    && (gMarioStates[0].action == ACT_READING_NPC_DIALOG
    ||  gMarioStates[0].action == ACT_WAITING_FOR_DIALOG))
        cutscene_object(CUTSCENE_STAR_SPAWN, o);

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x500);
    if (is_point_close_to_object(o, o->oHomeX, 3174.0f, o->oHomeZ, 200)) {
        cur_obj_init_animation(2);
        cur_obj_play_sound_2(SOUND_GENERAL_ENEMY_ALERT1);
        o->oForwardVel = 50.0f;
        o->oVelY = 40.0f;
        o->oMoveAngleYaw = -0x3FFF;
        o->oAction = YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN;
    }

    if (animFrame == 0 || animFrame == 15) {
        cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
    }
}

void yoshi_finish_jumping_and_despawn_loop(void) {
    push_mario_out_of_object(&gMarioStates[0], o, -10.0f);
    cur_obj_become_intangible();
    cur_obj_extend_animation_if_at_end();
    obj_move_xyz_using_fvel_and_yaw(o);
    o->oVelY -= 2.0;
    if (o->oPosY < 2100.0f) {
        sYoshiTalkingState = 2;
        gObjCutsceneDone = TRUE;
        o->oAction = YOSHI_ACT_GONE;
    }
}

void yoshi_give_present_loop(void) {
    cur_obj_become_intangible();
    push_mario_out_of_object(&gMarioStates[0], o, -10.0f);
    if (gNetworkPlayerLocal->globalIndex == o->globalPlayerIndex) {
        if (gHudDisplay.lives == 100) {
            play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
            gMarioStates[0].specialTripleJump = true;
            if (sYoshiNeeded) {
                sYoshiTalkingState = 2;
                o->oAction = YOSHI_ACT_IDLE;
            } else {
                o->oAction = YOSHI_ACT_WALK_JUMP_OFF_ROOF;
            }
            return;
        }

        if ((gGlobalTimer & 0x03) == 0) {
            play_sound(SOUND_MENU_YOSHI_GAIN_LIVES, gGlobalSoundSource);
            gMarioState->numLives++;
        }
    }
}

void yoshi_gone() {
    cur_obj_become_intangible();
    cur_obj_hide();
}

void yoshi_reappear() {
    if (gCurrLevelNum != LEVEL_CASTLE_GROUNDS || !dynos_level_is_vanilla_level(gCurrLevelNum)) {
        o->oHomeX = sYoshiHomeLocations[2];
        o->oHomeY = 3174.0f;
        o->oHomeZ = sYoshiHomeLocations[3];
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;
        cur_obj_init_animation(0);
        spawn_mist_particles();
        cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
        o->oAction = YOSHI_ACT_IDLE;
        return;
    }

    u8 decAmount = 4;
    if (o->oTimer == 0) {
        o->oHomeX = sYoshiHomeLocations[2];
        o->oHomeY = 3174.0f;
        o->oHomeZ = sYoshiHomeLocations[3];
        o->oPosX = sYoshiRespawnPos[0];
        o->oPosY = sYoshiRespawnPos[1];
        o->oPosZ = sYoshiRespawnPos[2];
        cur_obj_init_animation(2);
        cur_obj_play_sound_2(SOUND_GENERAL_ENEMY_ALERT1);
        spawn_mist_particles();
        o->oVelY = 160;
    }
    s16 dx = o->oHomeX - sYoshiRespawnPos[0];
    s16 dz = o->oHomeZ - sYoshiRespawnPos[2];
    s16 distXZ = sqrtf(dx * dx + dz * dz);
    o->oForwardVel = distXZ / sYoshiRespawnDuration;
    o->oVelY -= decAmount;
    o->oMoveAngleYaw = cur_obj_angle_to_home();
    obj_move_xyz_using_fvel_and_yaw(o);
    cur_obj_extend_animation_if_at_end();
    if (o->oPosY < o->oHomeY && o->oVelY < 0) { o->oPosY = o->oHomeY; }
    if (o->oTimer >= sYoshiRespawnDuration) {
        o->oPosX = o->oHomeX;
        o->oPosY = 3174.0f;
        o->oPosZ = o->oHomeZ;
        cur_obj_init_animation(0);
        spawn_mist_particles();
        cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;
        o->oAction = YOSHI_ACT_IDLE;
    }
}

void bhv_yoshi_loop(void) {
    switch (o->oAction) {
        case YOSHI_ACT_IDLE:
            yoshi_idle_loop();
            break;

        case YOSHI_ACT_WALK:
            yoshi_walk_loop();
            break;

        case YOSHI_ACT_TALK:
            yoshi_talk_loop();
            break;

        case YOSHI_ACT_WALK_JUMP_OFF_ROOF:
            yoshi_walk_and_jump_off_roof_loop();
            break;

        case YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN:
            yoshi_finish_jumping_and_despawn_loop();
            break;

        case YOSHI_ACT_GIVE_PRESENT:
            yoshi_give_present_loop();
            break;

        case YOSHI_ACT_GONE:
            yoshi_gone();
            break;

        case YOSHI_ACT_REAPPEAR:
            yoshi_reappear();
            break;

        case YOSHI_ACT_CREDITS:
            cur_obj_init_animation(0);
            break;
    }

    // sanity check reading dialog
    if (gMarioStates[0].interactObj == o
    && gNetworkPlayerLocal->globalIndex != o->globalPlayerIndex
    && o->oAction != YOSHI_ACT_IDLE
    && o->oAction != YOSHI_ACT_WALK
    && (gMarioStates[0].action == ACT_READING_NPC_DIALOG
    ||  gMarioStates[0].action == ACT_WAITING_FOR_DIALOG)) {
        set_mario_action(&gMarioStates[0], ACT_IDLE, 0);
    }

    if (sOverrideYoshiAlive) {
        LOG_CONSOLE("Overidden")
        sYoshiNeeded = true;
    } else if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) < 120) {
        LOG_CONSOLE("Not sufficent star count")
        sYoshiNeeded = false;
    } else {
        sYoshiNeeded = false;
        for (u8 i = 0; i < MAX_PLAYERS; i++) {
            if (gNetworkPlayers[i].currLevelNum == LEVEL_CASTLE_GROUNDS && !gMarioStates[i].specialTripleJump) {
                sYoshiNeeded = true;
                break;
            }
        }
    }

    if (!sYoshiNeeded
    && o->oAction != YOSHI_ACT_GONE
    && o->oAction != YOSHI_ACT_WALK_JUMP_OFF_ROOF
    && o->oAction != YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN
    && o->oAction != YOSHI_ACT_REAPPEAR) {
        o->oAction = YOSHI_ACT_WALK_JUMP_OFF_ROOF;
    } else if (sYoshiNeeded && o->oAction == YOSHI_ACT_GONE) {
        o->oAction = YOSHI_ACT_REAPPEAR;
    }

    if (o->oAction != YOSHI_ACT_GONE) {
        cur_obj_unhide();
    }

    curr_obj_random_blink(&o->oYoshiBlinkTimer);
}
