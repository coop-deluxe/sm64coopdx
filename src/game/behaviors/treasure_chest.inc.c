// treasure_chest.c.inc

/**
 * Hitbox for treasure chest bottom.
 */
static struct ObjectHitbox sTreasureChestBottomHitbox = {
    .interactType = INTERACT_SHOCK,
    .downOffset = 0,
    .damageOrCoinValue = 1,
    .health = 0,
    .numLootCoins = 0,
    .radius = 300,
    .height = 300,
    .hurtboxRadius = 310,
    .hurtboxHeight = 310,
};


void bhv_treasure_chest_top_loop(void) {
    if (!o->parentObj || !o->parentObj->parentObj) {
        obj_mark_for_deletion(o);
        return;
    }
    struct Object *rootParent = o->parentObj->parentObj;

    switch (o->oAction) {
        case 0:
            if (o->parentObj->oAction == 1) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer == 0) {
                if (rootParent->oTreasureChestIsAboveWater == 0) {
                    spawn_object_relative(0, 0, -80, 120, o, MODEL_BUBBLE, bhvWaterAirBubble);
                    play_sound(SOUND_GENERAL_CLAM_SHELL1, o->header.gfx.cameraToObject);
                } else {
                    play_sound(SOUND_GENERAL_OPEN_CHEST, o->header.gfx.cameraToObject);
                }
            }

            o->oFaceAnglePitch += -0x200;
            if (o->oFaceAnglePitch < -0x4000) {
                o->oFaceAnglePitch = -0x4000;
                o->oAction++;
                if (o->parentObj->oBehParams2ndByte != 4) {
                    spawn_orange_number(o->parentObj->oBehParams2ndByte, 0, -40, 0);
                }
            }
            break;

        case 2:
            if (o->parentObj->oAction == 0) {
                o->oAction = 3;
            }
            break;

        case 3:
            o->oFaceAnglePitch += 0x800;
            if (o->oFaceAnglePitch > 0) {
                o->oFaceAnglePitch = 0;
                o->oAction = 0;
            }
    }
}

void bhv_treasure_chest_bottom_init(void) {
    spawn_object_relative(0, 0, 102, -77, o, MODEL_TREASURE_CHEST_LID, bhvTreasureChestTop);
    obj_set_hitbox(o, &sTreasureChestBottomHitbox);
}

void bhv_treasure_chest_bottom_loop(void) {
    if (!o->parentObj) { return; }
    if (o->parentObj != NULL && o->parentObj->oTreasureChestSound != 0) {
        switch (o->parentObj->oTreasureChestSound) {
            case 1: play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource); break;
            case 2: play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);      break;
            case 3: play_puzzle_jingle(); fade_volume_scale(0, 127, 1000);       break;
            case 4: play_puzzle_jingle();                                        break;
        }
        o->parentObj->oTreasureChestSound = 0;
    }
    struct MarioState *player = nearest_mario_state_to_object(o);
    switch (o->oAction) {
        case 0:
            if (player && sync_object_is_owned_locally(o->parentObj->oSyncID) && obj_check_if_facing_toward_angle(o->oMoveAngleYaw, player->marioObj->header.gfx.angle[1] + 0x8000, 0x3000)) {
                if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 150)) {
                    if (!o->parentObj->oTreasureChestIsLastInteractionIncorrect) {
                        if (o->parentObj->oTreasureChestCurrentAnswer == o->oBehParams2ndByte) {
                            play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                            o->parentObj->oTreasureChestCurrentAnswer++;
                            o->oAction = 1;
                            o->parentObj->oTreasureChestSound = 1;
                        } else {
                            o->parentObj->oTreasureChestCurrentAnswer = 1;
                            o->parentObj->oTreasureChestIsLastInteractionIncorrect = 1;
                            o->oAction = 2;
                            cur_obj_become_tangible();
                            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                            o->parentObj->oTreasureChestSound = 2;
                        }
                        o->parentObj->oTreasureChestLastNetworkPlayerIndex = gNetworkPlayers[player->playerIndex].globalIndex;
                        network_send_object(o->parentObj);
                        o->parentObj->oTreasureChestSound = 0;
                    }
                }
            }
            break;

        case 1:
            if (o->parentObj->oTreasureChestIsLastInteractionIncorrect == 1) {
                o->oAction = 0;
            }
            break;

        case 2:
            cur_obj_become_intangible();
            if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 500)) {
                o->parentObj->oTreasureChestIsLastInteractionIncorrect = 0;
                o->oAction = 0;
            }
    }

    cur_obj_push_mario_away_from_cylinder(150.0f, 150.0f);
    o->oInteractStatus = 0;
}

struct Object* spawn_treasure_chest(s8 index, s32 x, s32 y, s32 z, s16 r) {
    struct Object *obj = spawn_object_abs_with_rot(o, 0, MODEL_TREASURE_CHEST_BASE, bhvTreasureChestBottom, x, y, z, 0, r, 0);
    if (obj != NULL) { obj->oBehParams2ndByte = index; }
    return obj;
}

void bhv_treasure_chest_ship_init(void) {
    struct Object *chests[4] = { 0 };
    chests[0] = spawn_treasure_chest(1, 400, -350, -2700, 0);
    chests[1] = spawn_treasure_chest(2, 650, -350, -940, -0x6001);
    chests[2] = spawn_treasure_chest(3, -550, -350, -770, 0x5FFF);
    chests[3] = spawn_treasure_chest(4, 100, -350, -1700, 0);
    
    o->oTreasureChestCurrentAnswer = 1;
    o->oTreasureChestIsAboveWater = 0;
    
    // We haven't interacted with a player yet.
    // We also don't sync this as not only is it not required
    // but it also is only set for an interaction.
    // Therefore this object must already be loaded for it to be set
    // and if it wasn't. You couldn't of possibly been the one
    // who last interacted to begin with.
    o->oTreasureChestLastNetworkPlayerIndex = UNKNOWN_GLOBAL_INDEX;

    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oTreasureChestCurrentAnswer);
            sync_object_init_field(o, &o->oTreasureChestIsLastInteractionIncorrect);
            sync_object_init_field(o, &o->oTreasureChestIsAboveWater);
            sync_object_init_field(o, &o->oTreasureChestSound);
            sync_object_init_field(o, &o->oTreasureChestLastNetworkPlayerIndex);
            for (s32 i = 0; i < 4; i++) {
                struct Object *chest = chests[i];
                sync_object_init_field(o, &chest->oAction);
                sync_object_init_field(o, &chest->oPrevAction);
                sync_object_init_field(o, &chest->oTimer);
                sync_object_init_field(o, &chest->oIntangibleTimer);
            }
        }
    }
}

void bhv_treasure_chest_ship_loop(void) {
    switch (o->oAction) {
        case 0:
            if (sync_object_is_owned_locally(o->oSyncID) && o->oTreasureChestCurrentAnswer == 5) {
                play_puzzle_jingle();
                fade_volume_scale(0, 127, 1000);
                o->oAction = 1;
                o->oTreasureChestSound = 3;
                network_send_object(o);
                o->oTreasureChestSound = 0;
            }
            break;

        case 1:
            if (gEnvironmentRegions != NULL && gEnvironmentRegionsLength > 6) {
                gEnvironmentRegions[6] += -5;
                play_sound(SOUND_ENV_WATER_DRAIN, gGlobalSoundSource);
                set_environmental_camera_shake(SHAKE_ENV_JRB_SHIP_DRAIN);
                if (gEnvironmentRegions[6] < -335) {
                    gEnvironmentRegions[6] = -335;
                    o->activeFlags = 0;
                }
#ifdef VERSION_SH
                reset_rumble_timers_2(2);
#endif
            }
            break;
    }
}

void bhv_treasure_chest_jrb_init(void) {
    struct Object *chests[4] = { 0 };
    chests[0] = spawn_treasure_chest(1, -1700, -2812, -1150, 0x7FFF);
    chests[1] = spawn_treasure_chest(2, -1150, -2812, -1550, 0x7FFF);
    chests[2] = spawn_treasure_chest(3, -2400, -2812, -1800, 0x7FFF);
    chests[3] = spawn_treasure_chest(4, -1800, -2812, -2100, 0x7FFF);
    
    o->oTreasureChestCurrentAnswer = 1;
    o->oTreasureChestIsAboveWater = 1;
    
    // We haven't interacted with a player yet.
    // We also don't sync this as not only is it not required
    // but it also is only set for an interaction.
    // Therefore this object must already be loaded for it to be set
    // and if it wasn't. You couldn't of possibly been the one
    // who last interacted to begin with.
    o->oTreasureChestLastNetworkPlayerIndex = UNKNOWN_GLOBAL_INDEX;

    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oTreasureChestCurrentAnswer);
            sync_object_init_field(o, &o->oTreasureChestIsLastInteractionIncorrect);
            sync_object_init_field(o, &o->oTreasureChestIsAboveWater);
            sync_object_init_field(o, &o->oTreasureChestSound);
            sync_object_init_field(o, &o->oTreasureChestLastNetworkPlayerIndex);
            for (s32 i = 0; i < 4; i++) {
                struct Object *chest = chests[i];
                sync_object_init_field(o, &chest->oAction);
                sync_object_init_field(o, &chest->oPrevAction);
                sync_object_init_field(o, &chest->oTimer);
                sync_object_init_field(o, &chest->oIntangibleTimer);
            }
        }
    }
}

void bhv_treasure_chest_jrb_loop(void) {
    switch (o->oAction) {
        case 0:
            if (sync_object_is_owned_locally(o->oSyncID) && o->oTreasureChestCurrentAnswer == 5) {
                play_puzzle_jingle();
                o->oAction = 1;
                o->oTreasureChestSound = 4;
                network_send_object(o);
                o->oTreasureChestSound = 0;
            }
            break;

        case 1:
            if (o->oTimer == 60) {
                spawn_mist_particles();

                f32* starPos = gLevelValues.starPositions.TreasureJrbStarPos;
                spawn_networked_default_star(starPos[0], starPos[1], starPos[2], o->oTreasureChestLastNetworkPlayerIndex);

                o->oAction = 2;
            }
            break;

        case 2:
            break;
    }
}

void bhv_treasure_chest_init(void) {
    struct Object *chests[4] = { 0 };
    chests[0] = spawn_treasure_chest(1, -4500, -5119, 1300, -0x6001);
    chests[1] = spawn_treasure_chest(2, -1800, -5119, 1050, 0x1FFF);
    chests[2] = spawn_treasure_chest(3, -4500, -5119, -1100, 9102);
    chests[3] = spawn_treasure_chest(4, -2400, -4607, 125, 16019);

    o->oTreasureChestCurrentAnswer = 1;
    o->oTreasureChestIsAboveWater = 0;
    
    // We haven't interacted with a player yet.
    // We also don't sync this as not only is it not required
    // but it also is only set for an interaction.
    // Therefore this object must already be loaded for it to be set
    // and if it wasn't. You couldn't of possibly been the one
    // who last interacted to begin with.
    o->oTreasureChestLastNetworkPlayerIndex = UNKNOWN_GLOBAL_INDEX;

    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oPrevAction);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oTreasureChestCurrentAnswer);
            sync_object_init_field(o, &o->oTreasureChestIsLastInteractionIncorrect);
            sync_object_init_field(o, &o->oTreasureChestIsAboveWater);
            sync_object_init_field(o, &o->oTreasureChestSound);
            sync_object_init_field(o, &o->oTreasureChestLastNetworkPlayerIndex);
            for (s32 i = 0; i < 4; i++) {
                struct Object *chest = chests[i];
                sync_object_init_field(o, &chest->oAction);
                sync_object_init_field(o, &chest->oPrevAction);
                sync_object_init_field(o, &chest->oTimer);
                sync_object_init_field(o, &chest->oIntangibleTimer);
            }
        }
    }
}

void bhv_treasure_chest_loop(void) {
    switch (o->oAction) {
        case 0:
            if (sync_object_is_owned_locally(o->oSyncID) && o->oTreasureChestCurrentAnswer == 5) {
                play_puzzle_jingle();
                o->oAction = 1;
                o->oTreasureChestSound = 4;
                network_send_object(o);
                o->oTreasureChestSound = 0;
            }
            break;

        case 1:
            if (o->oTimer == 60) {
                spawn_mist_particles();

                f32* starPos = gLevelValues.starPositions.TreasureChestStarPos;
                spawn_networked_default_star(starPos[0], starPos[1], starPos[2], o->oTreasureChestLastNetworkPlayerIndex);

                o->oAction = 2;
            }
            break;

        case 2:
            break;
    }
}