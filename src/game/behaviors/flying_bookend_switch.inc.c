// flying_bookend_switch.inc.c

struct Struct80331B30 {
    s16 unk00;
    s16 unk02;
};

struct ObjectHitbox sFlyingBookendHitbox = {
    .interactType = INTERACT_HIT_FROM_BELOW,
    .downOffset = 0,
    .damageOrCoinValue = 2,
    .health = 0,
    .numLootCoins = -1,
    .radius = 60,
    .height = 30,
    .hurtboxRadius = 40,
    .hurtboxHeight = 30,
};

struct Struct80331B30 D_80331B30[] = {
    { 52, 150 },
    { 135, 3 },
    { -75, 78 },
};

struct ObjectHitbox sBookSwitchHitbox = {
    .interactType = INTERACT_BREAKABLE,
    .downOffset = 0,
    .damageOrCoinValue = 0,
    .health = 99,
    .numLootCoins = 0,
    .radius = 20,
    .height = 30,
    .hurtboxRadius = 20,
    .hurtboxHeight = 30,
};

void flying_bookend_act_0(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (marioState && obj_is_near_to_and_facing_mario(marioState, 400.0f, 0x3000)) {
        cur_obj_play_sound_2(SOUND_OBJ_DEFAULT_DEATH);
        o->oAction = 1;
        o->oBookendUnkF4 = o->oFaceAnglePitch + 0x7FFF;
        o->oBookendUnkF8 = o->oFaceAngleRoll - 0x7FFF;
        cur_obj_set_model(smlua_model_util_load(E_MODEL_BOOKEND_PART));
    }
}

void flying_bookend_act_1(void) {
    if (obj_forward_vel_approach(3.0f, 1.0f)) {
        if (cur_obj_init_anim_and_check_if_end(2)) {
            o->oAction = 2;
            o->oForwardVel = 0.0f;
        } else {
            o->oForwardVel = 3.0f;
            if (o->oTimer > 5) {
                obj_face_pitch_approach(o->oBookendUnkF4, 2000);
                if (o->oTimer >= 10) {
                    obj_face_roll_approach(o->oBookendUnkF8, 2000);
                    if (o->oTimer >= 20) {
                        approach_f32_ptr(&o->header.gfx.scale[0], 3.0f, 0.2f);
                    }
                }
            }
        }
    }

    cur_obj_move_using_fvel_and_gravity();
}

void flying_bookend_act_2(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    cur_obj_init_animation_with_sound(1);
    cur_obj_update_floor_and_walls();

    if (o->oForwardVel == 0.0f) {
        if (marioState) {
            obj_turn_pitch_toward_mario(marioState, 120.0f, 1000);
        }
        o->oFaceAnglePitch = o->oMoveAnglePitch + 0x7FFF;
        cur_obj_rotate_yaw_toward(angleToPlayer, 1000);

        if (o->oTimer > 30) {
            obj_compute_vel_from_move_pitch(50.0f);
        }
    }

    cur_obj_move_standard(78);
}

void flying_bookend_act_3(void) {
    o->oDamageOrCoinValue = 1;
    o->oNumLootCoins = 0;

    if (o->oTimer >= 4) {
        o->oAction = 2;
        o->oForwardVel = 50.0f;
    }

    obj_forward_vel_approach(50.0f, 2.0f);
    cur_obj_move_using_fvel_and_gravity();
}

void bhv_flying_bookend_loop(void) {
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        o->oDeathSound = SOUND_OBJ_POUNDING1;
        cur_obj_scale(o->header.gfx.scale[0]);

        switch (o->oAction) {
            case 0:
                flying_bookend_act_0();
                break;
            case 1:
                flying_bookend_act_1();
                break;
            case 2:
                flying_bookend_act_2();
                break;
            case 3:
                flying_bookend_act_3();
                break;
        }

        obj_check_attacks(&sFlyingBookendHitbox, -1);
        if (o->oAction == -1 || (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_HIT_WALL))) {
            o->oNumLootCoins = 0;
            obj_die_if_health_non_positive();
        }

        o->oGraphYOffset = 30.0f * o->header.gfx.scale[0];
    }
}

void bhv_bookend_spawn_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) { sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS); }

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (marioState && marioState->playerIndex != 0) { return; }

    struct Object* book;

    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        if (o->oTimer > 40 && marioState && obj_is_near_to_and_facing_mario(marioState, 600.0f, 0x2000)) {
            book = spawn_object(o, MODEL_BOOKEND, bhvFlyingBookend);
            if (book != NULL) {
                book->oAction = 3;

                struct Object* spawn_objects[] = { book };
                u32 models[] = { MODEL_BOOKEND };
                network_send_spawn_objects(spawn_objects, models, 1);

                cur_obj_play_sound_2(SOUND_OBJ_DEFAULT_DEATH);
            }
            o->oTimer = 0;
        }
    }
}

void bookshelf_manager_act_0(void) {
    // spawn book switches

    s32 val04;

    //if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        for (val04 = 0; val04 < 3; val04++) {
            spawn_object_relative(val04, D_80331B30[val04].unk00, D_80331B30[val04].unk02, 0, o, MODEL_BOOKEND, bhvBookSwitch);
        }

        o->oAction = 1;
    //}
}

void bookshelf_manager_act_1(void) {
    // wait until mario is near

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (o->oBookSwitchManagerUnkF8 == 0) {
        if (so && so->owned && marioState && obj_is_near_to_and_facing_mario(marioState, 500.0f, 0x3000)) {
            o->oBookSwitchManagerUnkF8 = 1;
            network_send_object(o);
        }
    } else if (o->oTimer > 60 && so && so->owned) {
        o->oAction = 2;
        o->oBookSwitchManagerUnkF8 = 0;
        network_send_object(o);
    }
}

void bookshelf_manager_act_2(void) {
    // detect if we can open, and open bookshelf if we should

    //if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        struct SyncObject* so = sync_object_get(o->oSyncID);
        if (o->oBookSwitchManagerUnkF4 < 0) {
            if (o->oTimer > 30) {
                if (so && so->owned) {
                    o->oBookSwitchManagerUnkF4 = o->oBookSwitchManagerUnkF8 = 0;
                    network_send_object(o);
                }
            } else if (o->oTimer > 10) {
                if (so && so->owned) {
                    o->oBookSwitchManagerUnkF8 = 1;
                    network_send_object(o);
                }
            }
        } else {
            if (o->oBookSwitchManagerUnkF4 >= 3) {
                if (o->oTimer > 100) {
                    if (so && so->owned) {
                        o->parentObj = cur_obj_nearest_object_with_behavior(bhvHauntedBookshelf);
                        o->oAction = 3;
                        network_send_object(o);
                        if (o->parentObj != NULL) {
                            o->parentObj->oAction = 1;
                            o->oPosX = o->parentObj->oPosX;
                            network_send_object(o->parentObj);
                        }
                    }
                } else if (o->oTimer == 30) {
                    play_puzzle_jingle();
                }
            } else {
                o->oTimer = 0;
            }
        }
    //}
}

void bookshelf_manager_act_3(void) {
    // opening bookshelf

    if (o->parentObj == NULL || o->parentObj->behavior != smlua_override_behavior(bhvHauntedBookshelf)) {
        o->parentObj = cur_obj_nearest_object_with_behavior(bhvHauntedBookshelf);
    }

    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (o->oTimer > 85) {
        if (so && so->owned) {
            o->oAction = 4;
            network_send_object(o);
        }
    } else if (o->parentObj != NULL) {
        o->oForwardVel = o->parentObj->oPosX - o->oPosX;
        o->oPosX = o->parentObj->oPosX;
    }
}

void bookshelf_manager_act_4(void) {
    // bookshelf is done opening

    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (o->oBookSwitchManagerUnkF4 >= 3) {
        obj_mark_for_deletion(o);
    } else if (so && so->owned) {
        o->oAction = 0;
        network_send_object(o);
    }
}

void bhv_haunted_bookshelf_manager_override_ownership(u8* shouldOverride, u8* shouldOwn) {
    *shouldOverride = TRUE;
    *shouldOwn = get_network_player_smallest_global() == gNetworkPlayerLocal;
}

static u8 bhv_haunted_bookshelf_manager_ignore_if_true(void) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return true; }
    return so->owned;
}

void bhv_haunted_bookshelf_manager_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->syncDeathEvent = FALSE;
            so->override_ownership = bhv_haunted_bookshelf_manager_override_ownership;
            so->ignore_if_true = bhv_haunted_bookshelf_manager_ignore_if_true;
            sync_object_init_field_with_size(o, &o->activeFlags, 16);
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oBookSwitchManagerUnkF8);
            sync_object_init_field(o, &o->oBookSwitchManagerUnkF4);
            sync_object_init_field(o, &o->oTimer);
            sync_object_init_field(o, &o->oPosX);
            sync_object_init_field(o, &o->oForwardVel);
        }
    }

    switch (o->oAction) {
        case 0:
            bookshelf_manager_act_0();
            break;
        case 2:
            bookshelf_manager_act_2();
            break;
        case 1:
            bookshelf_manager_act_1();
            break;
        case 3:
            bookshelf_manager_act_3();
            break;
        case 4:
            bookshelf_manager_act_4();
            break;
    }
}

void bhv_book_switch_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            so->override_ownership = bhv_haunted_bookshelf_manager_override_ownership;
            so->ignore_if_true = bhv_haunted_bookshelf_manager_ignore_if_true;

            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oBookSwitchUnkF4);
            sync_object_init_field(o, &o->oIntangibleTimer);
            sync_object_init_field(o, &o->oPosX);
            sync_object_init_field(o, &o->oPosZ);
            sync_object_init_field(o, &o->oTimer);
        }
    }

    s32 sp3C;
    struct Object* book;
    s16 sp36;
    s16 sp34;

    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    struct SyncObject* so = sync_object_get(o->oSyncID);

    o->header.gfx.scale[0] = 2.0f;
    o->header.gfx.scale[1] = 0.9f;
    if (!o->parentObj) { return; }

    if (o->parentObj->oAction == 4) {
        obj_mark_for_deletion(o);
    } else {
        sp3C = obj_check_attacks(&sBookSwitchHitbox, o->oAction);
        if (o->parentObj->oBookSwitchManagerUnkF8 != 0 || o->oAction == 1) {
            if (distanceToPlayer < 100.0f) {
                cur_obj_become_tangible();
            } else {
                cur_obj_become_intangible();
            }

            if (so && so->owned && o->oAction != 1) {
                o->oAction = 1;
                network_send_object(o);
            }

            if (o->oBookSwitchUnkF4 == 0.0f) {
                cur_obj_play_sound_2(SOUND_OBJ_DEFAULT_DEATH);
            }

            if (approach_f32_ptr(&o->oBookSwitchUnkF4, 50.0f, 20.0f)) {
                if (o->parentObj->oBookSwitchManagerUnkF4 >= 0 && o->oTimer > 60) {
                    if (sp3C == 1 || sp3C == 2 || sp3C == 6) {
                        if (so && so->owned && o->oAction != 2) {
                            o->oAction = 2;
                            network_send_object(o);
                        }
                    }
                }
            } else {
                o->oTimer = 0;
            }
        } else {
            cur_obj_become_intangible();
            if (approach_f32_ptr(&o->oBookSwitchUnkF4, 0.0f, 20.0f)) {
                if (o->oAction != 0) {
                    if (o->parentObj->oBookSwitchManagerUnkF4 == o->oBehParams2ndByte) {
                        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                        if (so && so->owned) {
                            o->parentObj->oBookSwitchManagerUnkF4 += 1;
                            network_send_object(o->parentObj);
                        }
                    } else {
                        sp36 = random_u16() & 0x1;
                        sp34 = (marioState && player) ? player->oPosZ + 1.5f * marioState->vel[2] : 0;

                        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                        if (sp34 > 0) {
                            sp34 = 0;
                        }

                        if (so && so->owned) {
                            book = spawn_object_abs_with_rot(o, 0, MODEL_BOOKEND, bhvFlyingBookend,
                                                             0x1FC * sp36 - 0x8CA, 890, sp34, 0,
                                                             0x8000 * sp36 + 0x4000, 0);
                            if (book != NULL) {
                                book->oAction = 3;
                                struct Object* spawn_objects[] = { book };
                                u32 models[] = { MODEL_BOOKEND };
                                network_send_spawn_objects(spawn_objects, models, 1);
                            }
                        }

                        if (so && so->owned) {
                            o->parentObj->oBookSwitchManagerUnkF4 = -1;
                            network_send_object(o->parentObj);
                        }
                    }

                    if (so && so->owned && o->oAction != 0) {
                        o->oAction = 0;
                        network_send_object(o);
                    }
                }
            }
        }

        o->oPosX += o->parentObj->oForwardVel;
        o->oPosZ = o->oHomeZ - o->oBookSwitchUnkF4;
        cur_obj_push_mario_away_from_cylinder(70.0f, 70.0f);
    }
}
