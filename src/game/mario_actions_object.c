#include <PR/ultratypes.h>

#include "sm64.h"
#include "mario_actions_object.h"
#include "types.h"
#include "mario_step.h"
#include "mario.h"
#include "audio/external.h"
#include "interaction.h"
#include "engine/math_util.h"
#include "rumble_init.h"
#include "behavior_data.h"
#include "pc/debuglog.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "object_helpers.h"
#include "pc/lua/smlua.h"

/**
 * Used by act_punching() to determine Mario's forward velocity during each
 * animation frame.
 */
s8 sPunchingForwardVelocities[8] = { 0, 1, 1, 2, 3, 5, 7, 10 };

void animated_stationary_ground_step(struct MarioState *m, s32 animation, u32 endAction) {
    stationary_ground_step(m);
    set_character_animation(m, animation);
    if (is_anim_at_end(m)) {
        set_mario_action(m, endAction, 0);
    }
}

s32 mario_update_punch_sequence(struct MarioState *m) {
    if (!m) { return 0; }
    u32 endAction, crouchEndAction;
    s32 animFrame;

    if (m->action & ACT_FLAG_MOVING) {
        endAction = ACT_WALKING, crouchEndAction = ACT_CROUCH_SLIDE;
    } else {
        endAction = ACT_IDLE, crouchEndAction = ACT_CROUCHING;
    }

    switch (m->actionArg) {
        case 0:
            play_character_sound(m, CHAR_SOUND_PUNCH_YAH);
            // Fall-through:
        case 1:
            set_character_animation(m, CHAR_ANIM_FIRST_PUNCH);
            if (is_anim_past_end(m)) {
                m->actionArg = 2;
            } else {
                m->actionArg = 1;
            }

            if (m->marioObj->header.gfx.animInfo.animFrame >= 2) {
                if (mario_check_object_grab(m)) {
                    return TRUE;
                }

                m->flags |= MARIO_PUNCHING;
            }

            if (m->actionArg == 2) {
                m->marioBodyState->punchState = (0 << 6) | 4;
            }
            break;

        case 2:
            set_character_animation(m, CHAR_ANIM_FIRST_PUNCH_FAST);

            if (m->marioObj->header.gfx.animInfo.animFrame <= 0) {
                m->flags |= MARIO_PUNCHING;
            }

            if (m->input & INPUT_B_PRESSED) {
                m->actionArg = 3;
            }

            if (is_anim_at_end(m)) {
                set_mario_action(m, endAction, 0);
            }
            break;

        case 3:
            play_character_sound(m, CHAR_SOUND_PUNCH_WAH);
            // Fall-through:
        case 4:
            set_character_animation(m, CHAR_ANIM_SECOND_PUNCH);
            if (is_anim_past_end(m)) {
                m->actionArg = 5;
            } else {
                m->actionArg = 4;
            }

            if (m->marioObj->header.gfx.animInfo.animFrame > 0) {
                m->flags |= MARIO_PUNCHING;
            }

            if (m->actionArg == 5) {
                m->marioBodyState->punchState = (1 << 6) | 4;
            }
            break;

        case 5:
            set_character_animation(m, CHAR_ANIM_SECOND_PUNCH_FAST);
            if (m->marioObj->header.gfx.animInfo.animFrame <= 0) {
                m->flags |= MARIO_PUNCHING;
            }

            if (m->input & INPUT_B_PRESSED) {
                m->actionArg = 6;
            }

            if (is_anim_at_end(m)) {
                set_mario_action(m, endAction, 0);
            }
            break;

        case 6:
            play_mario_action_sound(m, CHAR_SOUND_PUNCH_HOO, 1);
            animFrame = set_character_animation(m, CHAR_ANIM_GROUND_KICK);
            if (animFrame == 0) {
                m->marioBodyState->punchState = (2 << 6) | 6;
            }

            if (animFrame >= 0 && animFrame < 8) {
                m->flags |= MARIO_KICKING;
            }

            if (is_anim_at_end(m)) {
                set_mario_action(m, endAction, 0);
            }
            break;

        case 9:
            play_mario_action_sound(m, CHAR_SOUND_PUNCH_HOO, 1);
            set_character_animation(m, CHAR_ANIM_BREAKDANCE);
            animFrame = m->marioObj->header.gfx.animInfo.animFrame;

            if (animFrame >= 2 && animFrame < 8) {
                m->flags |= MARIO_TRIPPING;
            }

            if (is_anim_at_end(m)) {
                set_mario_action(m, crouchEndAction, 0);
            }
            break;
    }

    return FALSE;
}

s32 act_punching(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_UNKNOWN_10) {
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) {
        return check_common_action_exits(m);
    }

    if (m->actionState == 0 && (m->input & INPUT_A_DOWN)) {
        return set_mario_action(m, ACT_JUMP_KICK, 0);
    }

    m->actionState = 1;
    if (m->actionArg == 0) {
        m->actionTimer = 7;
    }

    mario_set_forward_vel(m, sPunchingForwardVelocities[m->actionTimer]);
    if (m->actionTimer > 0) {
        m->actionTimer--;
    }

    mario_update_punch_sequence(m);
    perform_ground_step(m);
    return FALSE;
}

s32 act_picking_up(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_UNKNOWN_10) {
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->actionState == 0 && is_anim_at_end(m)) {
        //! While the animation is playing, it is possible for the used object
        // to unload. This allows you to pick up a vacant or newly loaded object
        // slot (cloning via fake object).
        mario_grab_used_object(m);
        if (m->heldObj != NULL) {
            play_character_sound_if_no_flag(m, CHAR_SOUND_HRMM, MARIO_MARIO_SOUND_PLAYED);
            m->actionState = 1;
        } else {
            set_mario_action(m, ACT_IDLE, 0);
            return FALSE;
        }
    }

    if (m->actionState == 1 && m->heldObj != NULL) {
        if (m->heldObj->oInteractionSubtype & INT_SUBTYPE_GRABS_MARIO) {
            m->marioBodyState->grabPos = GRAB_POS_HEAVY_OBJ;
            set_character_animation(m, CHAR_ANIM_GRAB_HEAVY_OBJECT);
            if (is_anim_at_end(m)) {
                set_mario_action(m, ACT_HOLD_HEAVY_IDLE, 0);
            }
        } else {
            m->marioBodyState->grabPos = GRAB_POS_LIGHT_OBJ;
            set_character_animation(m, CHAR_ANIM_PICK_UP_LIGHT_OBJ);
            if (is_anim_at_end(m)) {
                set_mario_action(m, ACT_HOLD_IDLE, 0);
            }
        }
    }

    stationary_ground_step(m);
    return FALSE;
}

s32 act_dive_picking_up(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_UNKNOWN_10) {
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    //! Hands-free holding. Landing on a slope or being pushed off a ledge while
    // landing from a dive grab sets Mario's action to a non-holding action
    // without dropping the object, causing the hands-free holding glitch.
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    animated_stationary_ground_step(m, CHAR_ANIM_STOP_SLIDE_LIGHT_OBJ, ACT_HOLD_IDLE);
    return FALSE;
}

s32 act_placing_down(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_UNKNOWN_10) {
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (++m->actionTimer == 8) {
        mario_drop_held_object(m);
    }

    animated_stationary_ground_step(m, CHAR_ANIM_PLACE_LIGHT_OBJ, ACT_IDLE);
    return FALSE;
}

s32 act_throwing(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->heldObj && (m->heldObj->oInteractionSubtype & INT_SUBTYPE_HOLDABLE_NPC)) {
        return set_mario_action(m, ACT_PLACING_DOWN, 0);
    }

    if (m->input & INPUT_UNKNOWN_10) {
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (++m->actionTimer == 7) {
        mario_throw_held_object(m);
        play_character_sound_if_no_flag(m, CHAR_SOUND_WAH2, MARIO_MARIO_SOUND_PLAYED);
        play_sound_if_no_flag(m, SOUND_ACTION_THROW, MARIO_ACTION_SOUND_PLAYED);
        queue_rumble_data_mario(m, 3, 50);
    }

    animated_stationary_ground_step(m, CHAR_ANIM_GROUND_THROW, ACT_IDLE);
    return FALSE;
}

s32 act_heavy_throw(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_UNKNOWN_10) {
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (++m->actionTimer == 13) {
        mario_drop_held_object(m);
        play_character_sound_if_no_flag(m, CHAR_SOUND_WAH2, MARIO_MARIO_SOUND_PLAYED);
        play_sound_if_no_flag(m, SOUND_ACTION_THROW, MARIO_ACTION_SOUND_PLAYED);
        queue_rumble_data_mario(m, 3, 50);
    }

    animated_stationary_ground_step(m, CHAR_ANIM_HEAVY_THROW, ACT_IDLE);
    return FALSE;
}

s32 act_stomach_slide_stop(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_UNKNOWN_10) {
        return set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    animated_stationary_ground_step(m, CHAR_ANIM_SLOW_LAND_FROM_DIVE, ACT_IDLE);
    return FALSE;
}

s32 act_picking_up_bowser(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->playerIndex != 0) {
        m->usedObj = cur_obj_nearest_object_with_behavior(bhvBowser);
    }
    if (m->actionState == 0) {
        m->actionState = 1;
        m->angleVel[1] = 0;
        m->marioBodyState->grabPos = GRAB_POS_BOWSER;
        mario_grab_used_object(m);
        if (m->heldObj != NULL) {
            queue_rumble_data_mario(m, 5, 80);
            play_character_sound(m, CHAR_SOUND_HRMM);
            if (m->playerIndex == 0) {
                network_send_object(m->heldObj);
            } else {
                set_mario_action(m, ACT_IDLE, 0);
                return FALSE;
            }
        }
    }

    set_character_animation(m, CHAR_ANIM_GRAB_BOWSER);
    if (is_anim_at_end(m)) {
        set_mario_action(m, ACT_HOLDING_BOWSER, 0);
    }

    stationary_ground_step(m);
    return FALSE;
}

s32 act_holding_bowser(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->playerIndex != 0) {
        if (m->marioBodyState->grabPos != GRAB_POS_BOWSER) {
            m->usedObj = cur_obj_nearest_object_with_behavior(bhvBowser);
            m->actionState = 1;
            m->angleVel[1] = 0;
            m->marioBodyState->grabPos = GRAB_POS_BOWSER;
            mario_grab_used_object(m);
            if (m->heldObj != NULL) {
                queue_rumble_data_mario(m, 5, 80);
                play_character_sound(m, CHAR_SOUND_HRMM);
            } else {
                set_mario_action(m, ACT_IDLE, 0);
                return FALSE;
            }
        }
    }

    s16 spin;

    if (m->playerIndex == 0 && m->input & INPUT_B_PRESSED) {
#ifndef VERSION_JP
        if (m->angleVel[1] <= -0xE00 || m->angleVel[1] >= 0xE00) {
            play_character_sound(m, CHAR_SOUND_SO_LONGA_BOWSER);
        } else {
            play_character_sound(m, CHAR_SOUND_HERE_WE_GO);
        }
#else
        play_character_sound(m, CHAR_SOUND_HERE_WE_GO);
#endif
        return set_mario_action(m, ACT_RELEASING_BOWSER, 0);
    }

    if (m->playerIndex == 0 && m->angleVel[1] == 0) {
        if (m->actionTimer++ > 120) {
            return set_mario_action(m, ACT_RELEASING_BOWSER, 1);
        }

        set_character_animation(m, CHAR_ANIM_HOLDING_BOWSER);
    } else {
        m->actionTimer = 0;
        set_character_animation(m, CHAR_ANIM_SWINGING_BOWSER);
    }

    if (m->intendedMag > 20.0f) {
        if (m->actionArg == 0) {
            m->actionArg = 1;
            m->twirlYaw = m->intendedYaw;
        } else {
            // spin = acceleration
            spin = (s16)(m->intendedYaw - m->twirlYaw) / 0x80;

            if (spin < -0x80) {
                spin = -0x80;
            }
            if (spin > 0x80) {
                spin = 0x80;
            }

            m->twirlYaw = m->intendedYaw;
            m->angleVel[1] += spin;

            if (m->angleVel[1] > 0x1000) {
                m->angleVel[1] = 0x1000;
            }
            if (m->angleVel[1] < -0x1000) {
                m->angleVel[1] = -0x1000;
            }
        }
    } else {
        m->actionArg = 0;
        m->angleVel[1] = approach_s32(m->angleVel[1], 0, 64, 64);
    }

    // spin = starting yaw
    spin = m->faceAngle[1];
    m->faceAngle[1] += m->angleVel[1];

    // play sound on overflow
    if (m->angleVel[1] <= -0x100 && spin < m->faceAngle[1]) {
        queue_rumble_data_mario(m, 4, 20);
        play_sound(SOUND_OBJ_BOWSER_SPINNING, m->marioObj->header.gfx.cameraToObject);
    }
    if (m->angleVel[1] >= 0x100 && spin > m->faceAngle[1]) {
        queue_rumble_data_mario(m, 4, 20);
        play_sound(SOUND_OBJ_BOWSER_SPINNING, m->marioObj->header.gfx.cameraToObject);
    }

    stationary_ground_step(m);
    if (m->angleVel[1] >= 0) {
        m->marioObj->header.gfx.angle[0] = -m->angleVel[1];
    } else {
        m->marioObj->header.gfx.angle[0] = m->angleVel[1];
    }

    return FALSE;
}

s32 act_releasing_bowser(struct MarioState *m) {
    if (!m) { return 0; }
    if (++m->actionTimer == 1 && m->playerIndex == 0) {
        if (m->actionArg == 0) {
            queue_rumble_data_mario(m, 5, 50);
            mario_throw_held_object(m);
        } else {
            queue_rumble_data_mario(m, 4, 50);
            mario_drop_held_object(m);
        }
    }

    m->angleVel[1] = 0;
    animated_stationary_ground_step(m, CHAR_ANIM_RELEASE_BOWSER, ACT_IDLE);
    return FALSE;
}

s32 check_common_object_cancels(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->playerIndex != 0) { return FALSE; }

    f32 waterSurface = m->waterLevel - 100;
    if (m->pos[1] < waterSurface) {
        return set_water_plunge_action(m);
    }

    if (m->input & INPUT_SQUISHED) {
        return drop_and_set_mario_action(m, ACT_SQUISHED, 0);
    }

    if (m->health < 0x100) {
        return drop_and_set_mario_action(m, ACT_STANDING_DEATH, 0);
    }

    return FALSE;
}

s32 mario_execute_object_action(struct MarioState *m) {
    if (!m) { return FALSE; }
    s32 cancel;

    if (check_common_object_cancels(m)) {
        return TRUE;
    }

    if (mario_update_quicksand(m, 0.5f)) {
        return TRUE;
    }

    if (!smlua_call_action_hook(ACTION_HOOK_EVERY_FRAME, m, &cancel)) {
        /* clang-format off */
        switch (m->action) {
            case ACT_PUNCHING:           cancel = act_punching(m);           break;
            case ACT_PICKING_UP:         cancel = act_picking_up(m);         break;
            case ACT_DIVE_PICKING_UP:    cancel = act_dive_picking_up(m);    break;
            case ACT_STOMACH_SLIDE_STOP: cancel = act_stomach_slide_stop(m); break;
            case ACT_PLACING_DOWN:       cancel = act_placing_down(m);       break;
            case ACT_THROWING:           cancel = act_throwing(m);           break;
            case ACT_HEAVY_THROW:        cancel = act_heavy_throw(m);        break;
            case ACT_PICKING_UP_BOWSER:  cancel = act_picking_up_bowser(m);  break;
            case ACT_HOLDING_BOWSER:     cancel = act_holding_bowser(m);     break;
            case ACT_RELEASING_BOWSER:   cancel = act_releasing_bowser(m);   break;
            default:
                LOG_ERROR("Attempted to execute unimplemented action '%04X'", m->action);
                set_mario_action(m, ACT_IDLE, 0);
                return false;
        }
        /* clang-format on */
    }

    if (!cancel && (m->input & INPUT_IN_WATER)) {
        set_mario_particle_flags(m, PARTICLE_IDLE_WATER_WAVE, FALSE);
    }

    return cancel;
}
