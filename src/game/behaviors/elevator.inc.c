// elevator.c.inc

void elevator_starting_shake(void) {
    cur_obj_play_sound_2(SOUND_GENERAL_QUIET_POUND1);
    cur_obj_shake_screen(SHAKE_POS_SMALL);
}

void elevator_act_0(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;

    u8 onPlatform = FALSE;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        onPlatform = onPlatform || gMarioStates[i].marioObj->platform == o;
    }

    o->oVelY = 0;
    if (o->oElevatorUnk100 == 2) {
        if (onPlatform) {
            if (o->oPosY > o->oElevatorUnkFC) {
                o->oAction = 2;
            } else {
                o->oAction = 1;
            }
        }
    } else if ((player && player->oPosY > o->oElevatorUnkFC) || o->oElevatorUnk100 == 1) {
        o->oPosY = o->oElevatorUnkF8;
        if (onPlatform) {
            o->oAction = 2;
        }
    } else {
        o->oPosY = o->oElevatorUnkF4;
        if (onPlatform) {
            o->oAction = 1;
        }
    }

    if (marioState && marioState->playerIndex == 0 && o->oAction != 0) { network_send_object(o); }
}

void elevator_act_1(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;

    cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
    if (o->oTimer == 0 && cur_obj_is_any_player_on_platform()) {
        elevator_starting_shake();
    }
    approach_f32_signed(&o->oVelY, 10.0f, 2.0f);
    o->oPosY += o->oVelY;
    if (o->oPosY > o->oElevatorUnkF8) {
        o->oPosY = o->oElevatorUnkF8;
        if (o->oElevatorUnk100 == 2 || o->oElevatorUnk100 == 1) {
            o->oAction = 3;
        } else if (player && player->oPosY < o->oElevatorUnkFC) {
            o->oAction = 2;
        } else {
            o->oAction = 3;
        }
    }

    if (marioState && marioState->playerIndex == 0 && o->oAction != 1) { network_send_object(o); }
}

void elevator_act_2(void) { // Pretty similar code to action 1
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;

    cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
    if (o->oTimer == 0 && cur_obj_is_any_player_on_platform()) {
        elevator_starting_shake();
    }

    approach_f32_signed(&o->oVelY, -10.0f, -2.0f);
    o->oPosY += o->oVelY;
    if (o->oPosY < o->oElevatorUnkF4) {
        o->oPosY = o->oElevatorUnkF4;
        if (o->oElevatorUnk100 == 1) {
            o->oAction = 4;
        } else if (o->oElevatorUnk100 == 2) {
            o->oAction = 3;
        } else if (player && player->oPosY > o->oElevatorUnkFC) {
            o->oAction = 1;
        } else {
            o->oAction = 3;
        }
    }

    if (marioState && marioState->playerIndex == 0 && o->oAction != 2) { network_send_object(o); }
}

void elevator_act_4(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);

    o->oVelY = 0;
    if (o->oTimer == 0) {
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        cur_obj_play_sound_2(SOUND_GENERAL_METAL_POUND);
    }
    if (marioState && !mario_is_in_air_action(marioState) && !cur_obj_is_any_player_on_platform()) {
        o->oAction = 1;
    }

    if (marioState && marioState->playerIndex == 0 && o->oAction != 4) { network_send_object(o); }
}

void elevator_act_3(void) // nearly identical to action 2
{
    struct MarioState* marioState = nearest_mario_state_to_object(o);

    o->oVelY = 0;
    if (o->oTimer == 0) {
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        cur_obj_play_sound_2(SOUND_GENERAL_METAL_POUND);
    }
    if (marioState && !mario_is_in_air_action(marioState) && !cur_obj_is_any_player_on_platform()) {
        o->oAction = 0;
    }

    if (marioState && marioState->playerIndex == 0 && o->oAction != 3) { network_send_object(o); }
}

void bhv_elevator_init(void) {
    s32 sp1C = BHV_ARR(D_8032F38C, o->oBehParams2ndByte * 3 + 2, s16);
    if (sp1C == 0) {
        o->oElevatorUnkF4 = BHV_ARR(D_8032F38C, o->oBehParams2ndByte * 3, s16);
        o->oElevatorUnkF8 = o->oHomeY;
        o->oElevatorUnkFC = (o->oElevatorUnkF4 + o->oElevatorUnkF8) / 2;
        o->oElevatorUnk100 = cur_obj_has_behavior(bhvRrElevatorPlatform);
    } else {
        o->oElevatorUnkF4 = BHV_ARR(D_8032F38C, o->oBehParams2ndByte * 3, s16);
        o->oElevatorUnkF8 = BHV_ARR(D_8032F38C, o->oBehParams2ndByte * 3 + 1, s16);
        o->oElevatorUnkFC = (o->oElevatorUnkF4 + o->oElevatorUnkF8) / 2;
        o->oElevatorUnk100 = 2;
    }

    sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    sync_object_init_field(o, &o->oAction);
    sync_object_init_field(o, &o->oPosY);
    sync_object_init_field(o, &o->oVelY);
}

void (*sElevatorActions[])(void) = { elevator_act_0, elevator_act_1, elevator_act_2, elevator_act_3,
                                     elevator_act_4 };

struct SpawnParticlesInfo D_8032F3CC = { 3, 20, MODEL_MIST, 20, 10, 5, 0, 0, 0, 30, 30.0f, 1.5f };

struct SpawnParticlesInfo D_8032F3E0 = { 0, 5, MODEL_SAND_DUST, 0, 0, 20, 20, 0, 252, 30, 5.0f, 2.0f };

s16 D_8032F3F4[] = { 2, -8, 1, 4 };

struct SpawnParticlesInfo D_8032F3FC = { 0,    5,   MODEL_WHITE_PARTICLE_DL, 0, 0, 20, 20, 0, 252, 30,
                                         2.0f, 2.0f };

void bhv_elevator_loop(void) {
    CUR_OBJ_CALL_ACTION_FUNCTION(sElevatorActions);

    // allow bubbled players to pass through
    if (gMarioStates[0].action == ACT_BUBBLED) {
        cur_obj_become_intangible();
    } else {
        cur_obj_become_tangible();
    }
}
