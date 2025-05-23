#include <PR/ultratypes.h>

#include "sm64.h"
#include "actors/common0.h"
#include "actors/group11.h"
#include "actors/group17.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "game_init.h"
#include "geo_misc.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "levels/bitdw/header.h"
#include "levels/bitfs/header.h"
#include "levels/bits/header.h"
#include "levels/bob/header.h"
#include "levels/ccm/header.h"
#include "levels/hmc/header.h"
#include "levels/jrb/header.h"
#include "levels/lll/header.h"
#include "levels/rr/header.h"
#include "levels/ssl/header.h"
#include "levels/thi/header.h"
#include "levels/ttc/header.h"
#include "levels/vcutm/header.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "obj_behaviors_2.h"
#include "object_constants.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "platform_displacement.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "seq_ids.h"
#include "spawn_sound.h"
#include "hardcoded.h"
#include "engine/surface_load.h"
#include "pc/network/network.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "pc/lua/smlua_hooks.h"

#define POS_OP_SAVE_POSITION 0
#define POS_OP_COMPUTE_VELOCITY 1
#define POS_OP_RESTORE_POSITION 2

#define o gCurrentObject

/* BSS (declared to force order) */
extern s32 sNumActiveFirePiranhaPlants;
extern s32 sNumKilledFirePiranhaPlants;
extern f32 sObjSavedPosX;
extern f32 sObjSavedPosY;
extern f32 sObjSavedPosZ;
extern struct Object *sMontyMoleHoleList;
extern s32 sMontyMoleKillStreak;
extern f32 sMontyMoleLastKilledPosX;
extern f32 sMontyMoleLastKilledPosY;
extern f32 sMontyMoleLastKilledPosZ;
extern struct Object *sMasterTreadmill;

/**
 * The treadmill that plays sounds and controls the others on random setting.
 */
struct Object *sMasterTreadmill;


f32 sObjSavedPosX;
f32 sObjSavedPosY;
f32 sObjSavedPosZ;

void wiggler_jumped_on_attack_handler(void);
void huge_goomba_weakly_attacked(void);

/* |description|Checks if the current object's rendering is enabled|descriptionEnd| */
s32 obj_is_rendering_enabled(void) {
    if (!o) { return 0; }
    if (o->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* |description|Calculates the current object's theoretical pitch from forward velocity and vertical velocity|descriptionEnd| */
s16 obj_get_pitch_from_vel(void) {
    if (!o) { return 0; }
    return -atan2s(o->oForwardVel, o->oVelY);
}

/**
 * Show dialog proposing a race.
 * If the player accepts the race, then leave time stop enabled and Mario in the
 * text action so that the racing object can wait before starting the race.
 * If the player declines the race, then disable time stop and allow Mario to
 * move again.
 */
static s32 obj_update_race_proposition_dialog(struct MarioState* m, s16 dialogID, u8 (*inContinueDialogFunction)(void)) {
    s32 dialogResponse = cur_obj_update_dialog_with_cutscene(m, 2, DIALOG_UNK2_FLAG_0 | DIALOG_UNK2_LEAVE_TIME_STOP_ENABLED, CUTSCENE_RACE_DIALOG, dialogID, inContinueDialogFunction);

    if (dialogResponse == 2) {
        set_mario_npc_dialog(m, 0, NULL);
        disable_time_stop_including_mario();
    }

    return dialogResponse;
}

/* |description|Sets the current object's position to the home with an additional forward vector multiplied by `distFromHome` |descriptionEnd| */
void obj_set_dist_from_home(f32 distFromHome) {
    if (!o) { return; }
    o->oPosX = o->oHomeX + distFromHome * coss(o->oMoveAngleYaw);
    o->oPosZ = o->oHomeZ + distFromHome * sins(o->oMoveAngleYaw);
}

/* |description|Checks if the current object is in `maxDist` to `m` and the angle difference is less than `maxAngleDiff`|descriptionEnd| */
s32 obj_is_near_to_and_facing_mario(struct MarioState* m, f32 maxDist, s16 maxAngleDiff) {
    if (!o || !m) { return 0; }
    struct Object* player = m->marioObj;
    s32 distanceToPlayer = dist_between_objects(o, player);
    s32 angleToPlayer = obj_angle_to_object(o, player);
    if (distanceToPlayer < maxDist
        && abs_angle_diff(o->oMoveAngleYaw, angleToPlayer) < maxAngleDiff) {
        return TRUE;
    }
    return FALSE;
}

//! Although having no return value, this function
//! must be u32 to match other functions on -O2.
static BAD_RETURN(u32) obj_perform_position_op(s32 op) {
    if (!o) { return; }
    switch (op) {
        case POS_OP_SAVE_POSITION:
            sObjSavedPosX = o->oPosX;
            sObjSavedPosY = o->oPosY;
            sObjSavedPosZ = o->oPosZ;
            break;

        case POS_OP_COMPUTE_VELOCITY:
            o->oVelX = o->oPosX - sObjSavedPosX;
            o->oVelY = o->oPosY - sObjSavedPosY;
            o->oVelZ = o->oPosZ - sObjSavedPosZ;
            break;

        case POS_OP_RESTORE_POSITION:
            o->oPosX = sObjSavedPosX;
            o->oPosY = sObjSavedPosY;
            o->oPosZ = sObjSavedPosZ;
            break;
    }
}

/* |description|Handles the platform on track's trajectory marker ball spawning|descriptionEnd| */
void platform_on_track_update_pos_or_spawn_ball(s32 ballIndex, f32 x, f32 y, f32 z) {
    if (!o) { return; }
    struct Object *trackBall = NULL;
    struct Waypoint *initialPrevWaypoint = NULL;
    struct Waypoint *nextWaypoint = NULL;
    struct Waypoint *prevWaypoint = NULL;
    f32 amountToMove = 0;
    f32 dx = 0;
    f32 dy = 0;
    f32 dz = 0;
    f32 distToNextWaypoint = 100;

    if (ballIndex == 0 || ((u16)(o->oBehParams >> 16) & 0x0080)) {
        initialPrevWaypoint = o->oPlatformOnTrackPrevWaypoint;
        nextWaypoint = initialPrevWaypoint;

        if (ballIndex != 0) {
            amountToMove = 300.0f * ballIndex;
        } else {
            obj_perform_position_op(POS_OP_SAVE_POSITION);
            o->oPlatformOnTrackPrevWaypointFlags = 0;
            amountToMove = o->oForwardVel;
        }

        do {
            prevWaypoint = nextWaypoint;
            if (!prevWaypoint) { break; }

            nextWaypoint += 1;
            if (nextWaypoint->flags == WAYPOINT_FLAGS_END) {
                if (ballIndex == 0) {
                    o->oPlatformOnTrackPrevWaypointFlags = WAYPOINT_FLAGS_END;
                }

                if (((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_RETURN_TO_START)) {
                    nextWaypoint = o->oPlatformOnTrackStartWaypoint;
                } else {
                    return;
                }
            }

            dx = nextWaypoint->pos[0] - x;
            dy = nextWaypoint->pos[1] - y;
            dz = nextWaypoint->pos[2] - z;

            distToNextWaypoint = sqrtf(dx * dx + dy * dy + dz * dz);

            // Move directly to the next waypoint, even if it's farther away
            // than amountToMove
            amountToMove -= distToNextWaypoint;
            x += dx;
            y += dy;
            z += dz;
        } while (amountToMove > 0.0f);

        // If we moved farther than amountToMove, move in the opposite direction
        // No risk of near-zero division: If distToNextWaypoint is close to
        // zero, then that means we didn't cross a waypoint this frame (since
        // otherwise distToNextWaypoint would equal the distance between two
        // waypoints, which should never be that small). But this implies that
        // amountToMove - distToNextWaypoint <= 0, and amountToMove is at least
        // 0.1 (from platform on track behavior).
        distToNextWaypoint = amountToMove / distToNextWaypoint;
        x += dx * distToNextWaypoint;
        y += dy * distToNextWaypoint;
        z += dz * distToNextWaypoint;

        if (ballIndex != 0) {
            trackBall = spawn_object_relative(o->oPlatformOnTrackBaseBallIndex + ballIndex, 0, 0, 0, o,
                                              MODEL_TRAJECTORY_MARKER_BALL, bhvTrackBall);

            if (trackBall != NULL) {
                trackBall->oPosX = x;
                trackBall->oPosY = y;
                trackBall->oPosZ = z;
            }
        } else {
            if (prevWaypoint != initialPrevWaypoint) {
                if (o->oPlatformOnTrackPrevWaypointFlags == 0) {
                    o->oPlatformOnTrackPrevWaypointFlags = initialPrevWaypoint->flags;
                }
                o->oPlatformOnTrackPrevWaypoint = prevWaypoint;
            }

            o->oPosX = x;
            o->oPosY = y;
            o->oPosZ = z;

            obj_perform_position_op(POS_OP_COMPUTE_VELOCITY);

            o->oPlatformOnTrackPitch =
                atan2s(sqrtf(o->oVelX * o->oVelX + o->oVelZ * o->oVelZ), -o->oVelY);
            o->oPlatformOnTrackYaw = atan2s(o->oVelZ, o->oVelX);
        }
    }
}

/* |description|Spins an object in every direction with `pitchSpeed` and `rollSpeed`|descriptionEnd| */
void cur_obj_spin_all_dimensions(f32 pitchSpeed, f32 rollSpeed) {
    if (!o) { return; }
    f32 roll;
    f32 upwardOffset;
    f32 pitch;
    f32 cosAngle;
    f32 sinAngle;
    f32 finalOffsetX;
    f32 finalOffsetY;
    f32 finalOffsetZ;
    f32 tempOffsetX;
    f32 tempOffsetZ;

    if (o->oForwardVel == 0.0f) {
        roll = upwardOffset = pitch = 0.0f;

        if (o->oMoveFlags & OBJ_MOVE_IN_AIR) {
            upwardOffset = 50.0f;
        } else {
            if (o->oFaceAnglePitch < 0) {
                pitch = -pitchSpeed;
            } else if (o->oFaceAnglePitch > 0) {
                pitch = pitchSpeed;
            }

            if (o->oFaceAngleRoll < 0) {
                roll = -rollSpeed;
            } else if (o->oFaceAngleRoll > 0) {
                roll = rollSpeed;
            }
        }

        cosAngle = coss(o->oFaceAnglePitch);
        sinAngle = sins(o->oFaceAnglePitch);
        finalOffsetZ = pitch * cosAngle + upwardOffset * sinAngle;
        finalOffsetY = upwardOffset * cosAngle - pitch * sinAngle;

        cosAngle = coss(o->oFaceAngleRoll);
        sinAngle = sins(o->oFaceAngleRoll);
        tempOffsetX = roll * cosAngle + finalOffsetY * sinAngle;
        finalOffsetY = finalOffsetY * cosAngle - roll * sinAngle;

        cosAngle = coss(o->oFaceAngleYaw);
        sinAngle = sins(o->oFaceAngleYaw);
        finalOffsetX = tempOffsetX * cosAngle - finalOffsetZ * sinAngle;
        finalOffsetZ = finalOffsetZ * cosAngle + tempOffsetX * sinAngle;

        tempOffsetX = roll * cosAngle - pitch * sinAngle;
        tempOffsetZ = pitch * cosAngle + roll * sinAngle;

        o->oPosX = o->oHomeX - tempOffsetX + finalOffsetX;
        o->oGraphYOffset = upwardOffset - finalOffsetY;
        o->oPosZ = o->oHomeZ + tempOffsetZ - finalOffsetZ;
    }
}

/* |description|Approaches the current object's yaw to `targetYaw` by `turnAmount`|descriptionEnd| */
void obj_rotate_yaw_and_bounce_off_walls(s16 targetYaw, s16 turnAmount) {
    if (!o) { return; }
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        targetYaw = cur_obj_reflect_move_angle_off_wall();
    }
    cur_obj_rotate_yaw_toward(targetYaw, turnAmount);
}

/* |description|Gets the current object's theoretical pitch to the home with the lateral distance from it|descriptionEnd| */
s16 obj_get_pitch_to_home(f32 latDistToHome) {
    if (!o) { return 0; }
    return atan2s(latDistToHome, o->oPosY - o->oHomeY);
}

/* |description|Computes the current object's forward vel and vertical velocity with the move angle pitch|descriptionEnd| */
void obj_compute_vel_from_move_pitch(f32 speed) {
    if (!o) { return; }
    o->oForwardVel = speed * coss(o->oMoveAnglePitch);
    o->oVelY = speed * -sins(o->oMoveAnglePitch);
}

static s32 clamp_s16(s16 *value, s16 minimum, s16 maximum) {
    if (*value <= minimum) {
        *value = minimum;
    } else if (*value >= maximum) {
        *value = maximum;
    } else {
        return FALSE;
    }

    return TRUE;
}

static s32 clamp_f32(f32 *value, f32 minimum, f32 maximum) {
    if (*value <= minimum) {
        *value = minimum;
    } else if (*value >= maximum) {
        *value = maximum;
    } else {
        return FALSE;
    }

    return TRUE;
}

/* |description|Initializes an animation for the current object and loops back around if the animation ends|descriptionEnd| */
void cur_obj_init_anim_extend(s32 animIndex) {
    cur_obj_init_animation_with_sound(animIndex);
    cur_obj_extend_animation_if_at_end();
}

/* |description|Initializes an animation for the current object and returns if the animation has ended|descriptionEnd| */
s32 cur_obj_init_anim_and_check_if_end(s32 animIndex) {
    cur_obj_init_animation_with_sound(animIndex);
    return cur_obj_check_if_near_animation_end();
}

/* |description|Initializes an animation for the current object and checks if the animation frame is a specific frame|descriptionEnd| */
s32 cur_obj_init_anim_check_frame(s32 animIndex, s32 animFrame) {
    cur_obj_init_animation_with_sound(animIndex);
    return cur_obj_check_anim_frame(animFrame);
}

/* |description|Sets the current object's animation to a new animation if the current animation has ended|descriptionEnd| */
s32 cur_obj_set_anim_if_at_end(s32 animIndex) {
    if (cur_obj_check_if_at_animation_end()) {
        cur_obj_init_animation_with_sound(animIndex);
        return TRUE;
    }
    return FALSE;
}

/* |description|Plays a sound when the animation frame is in a range|descriptionEnd| */
s32 cur_obj_play_sound_at_anim_range(s8 startFrame, s8 endFrame, u32 sound) {
    if (!o) { return 0; }
    s32 val04;

    if ((val04 = o->header.gfx.animInfo.animAccel / 0x10000) <= 0) {
        val04 = 1;
    }

    if (cur_obj_check_anim_frame_in_range(startFrame, val04) || cur_obj_check_anim_frame_in_range(endFrame, val04)) {
        cur_obj_play_sound_2(sound);
        return TRUE;
    }

    return FALSE;
}

/* |description|Turns the current object towards `m` by `turnAmount` and subtracts and adds `targetOffsetY` to the Y position, effectively cancelling any effect out|descriptionEnd| */
s16 obj_turn_pitch_toward_mario(struct MarioState* m, f32 targetOffsetY, s16 turnAmount) {
    if (!o) { return 0; }
    if (!m) { return 0; }
    s16 targetPitch;

    o->oPosY -= targetOffsetY;
    targetPitch = obj_turn_toward_object(o, m->marioObj, O_MOVE_ANGLE_PITCH_INDEX, turnAmount);
    o->oPosY += targetOffsetY;

    return targetPitch;
}

/* |description|Approaches a `target` for `px` using `delta`|descriptionEnd| */
s32 approach_f32_ptr(f32 *px, f32 target, f32 delta) {
    if (!px) { return FALSE; }
    if (*px > target) {
        delta = -delta;
    }

    *px += delta;

    if ((*px - target) * delta >= 0) {
        *px = target;
        return TRUE;
    }
    return FALSE;
}

/* |description|Approaches a `target` value with the current object's forward velocity using `delta`|descriptionEnd| */
s32 obj_forward_vel_approach(f32 target, f32 delta) {
    if (!o) { return 0; }
    return approach_f32_ptr(&o->oForwardVel, target, delta);
}

/* |description|Approaches a `target` value with the current object's vertical velocity using `delta`|descriptionEnd| */
s32 obj_y_vel_approach(f32 target, f32 delta) {
    if (!o) { return 0; }
    return approach_f32_ptr(&o->oVelY, target, delta);
}

/* |description|Approaches a `target` value with the current object's move pitch using `delta`|descriptionEnd| */
s32 obj_move_pitch_approach(s16 target, s16 delta) {
    if (!o) { return 0; }
    o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, target, delta);

    if ((s16) o->oMoveAnglePitch == target) {
        return TRUE;
    }

    return FALSE;
}

/* |description|Approaches a `target` value with the current object's facing pitch using `delta`|descriptionEnd| */
s32 obj_face_pitch_approach(s16 targetPitch, s16 deltaPitch) {
    if (!o) { return 0; }
    o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, deltaPitch);

    if ((s16) o->oFaceAnglePitch == targetPitch) {
        return TRUE;
    }

    return FALSE;
}

/* |description|Approaches a `target` value with the current object's facing yaw using `delta`|descriptionEnd| */
s32 obj_face_yaw_approach(s16 targetYaw, s16 deltaYaw) {
    if (!o) { return 0; }
    o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, targetYaw, deltaYaw);

    if ((s16) o->oFaceAngleYaw == targetYaw) {
        return TRUE;
    }

    return FALSE;
}

/* |description|Approaches a `target` value with the current object's facing roll using `delta`|descriptionEnd| */
s32 obj_face_roll_approach(s16 targetRoll, s16 deltaRoll) {
    if (!o) { return 0; }
    o->oFaceAngleRoll = approach_s16_symmetric(o->oFaceAngleRoll, targetRoll, deltaRoll);

    if ((s16) o->oFaceAngleRoll == targetRoll) {
        return TRUE;
    }

    return FALSE;
}

/* |description|Smoothly turns the `angle` integer pointer using parameters, although usage in Lua is difficult due to the amount of pointers needed|descriptionEnd| */
s32 obj_smooth_turn(s16 *angleVel, s32 *angle, s16 targetAngle, f32 targetSpeedProportion,
                           s16 accel, s16 minSpeed, s16 maxSpeed) {
    s16 currentSpeed;
    s16 currentAngle = (s16)(*angle);

    *angleVel =
        approach_s16_symmetric(*angleVel, (targetAngle - currentAngle) * targetSpeedProportion, accel);

    currentSpeed = absi(*angleVel);
    clamp_s16(&currentSpeed, minSpeed, maxSpeed);

    *angle = approach_s16_symmetric(*angle, targetAngle, currentSpeed);
    return (s16)(*angle) == targetAngle;
}

/* |description|Rolls the current object to the move angle subtracted by `targetYaw`, clamping between negative and positive `maxRoll` and using `rollSpeed`|descriptionEnd| */
void obj_roll_to_match_yaw_turn(s16 targetYaw, s16 maxRoll, s16 rollSpeed) {
    if (!o) { return; }
    s16 targetRoll = o->oMoveAngleYaw - targetYaw;
    clamp_s16(&targetRoll, -maxRoll, maxRoll);
    obj_face_roll_approach(targetRoll, rollSpeed);
}

/* |description|Generates a random offset with a base and range of `base` to `range`|descriptionEnd| */
s16 random_linear_offset(s16 base, s16 range) {
    return base + (s16)(range * random_float());
}

/* |description|Generates a random offset using step multiplied a value between 0 and `mod` (the random function goes to 65535 but wraps around to 0 at `mod`)|descriptionEnd| */
s16 random_mod_offset(s16 base, s16 step, s16 mod) {
    if (!mod) { return 0; }
    return base + step * (random_u16() % mod);
}

/* |description|Rotates the current object's move angle yaw using `delta` in either a randomly decided positive or negative direction|descriptionEnd| */
s16 obj_random_fixed_turn(s16 delta) {
    if (!o) { return 0; }
    return o->oMoveAngleYaw + (s16) random_sign() * delta;
}

/* |description|
Begin by increasing the current object's scale by `*scaleVel`, and slowly decreasing
`scaleVel`. Once the object starts to shrink, wait a bit, and then begin to
scale the object toward `endScale`. The first time it reaches below
`shootFireScale` during this time, return 1.
Return -1 once it's reached endScale
|descriptionEnd| */
s32 obj_grow_then_shrink(f32 *scaleVel, f32 shootFireScale, f32 endScale) {
    if (!o) { return 0; }
    if (o->oTimer < 2) {
        o->header.gfx.scale[0] += *scaleVel;

        if ((*scaleVel -= 0.01f) > -0.03f) {
            o->oTimer = 0;
        }
    } else if (o->oTimer > 10) {
        if (approach_f32_ptr(&o->header.gfx.scale[0], endScale, 0.05f)) {
            return -1;
        } else if (*scaleVel != 0.0f && o->header.gfx.scale[0] < shootFireScale) {
            *scaleVel = 0.0f;
            return 1;
        }
    }

    return 0;
}

/* |description||descriptionEnd| */
s32 oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel,
                            f32 slowdown) {
    if (value == NULL || vel == NULL) { return FALSE; }
    s32 startValue = *value;
    *value += (s32) *vel;

    if (*value == target
        || ((*value - target) * (startValue - target) < 0 && *vel > -velCloseToZero
            && *vel < velCloseToZero)) {
        *value = target;
        *vel = 0.0f;
        return TRUE;
    } else {
        if (*value >= target) {
            accel = -accel;
        }
        if (*vel * accel < 0.0f) {
            accel *= slowdown;
        }

        *vel += accel;
    }

    return FALSE;
}

/* |description|Update the current object's blinking through `oAnimState`|descriptionEnd| */
void obj_update_blinking(s32 *blinkTimer, s16 baseCycleLength, s16 cycleLengthRange,
                                s16 blinkLength) {
    if (!o) { return; }
    if (*blinkTimer != 0) {
        *blinkTimer -= 1;
    } else {
        *blinkTimer = random_linear_offset(baseCycleLength, cycleLengthRange);
    }

    if (*blinkTimer > blinkLength) {
        o->oAnimState = 0;
    } else {
        o->oAnimState = 1;
    }
}

/* |description|Resolves "collisions" with the current object and other objects by offsetting the current object's position|descriptionEnd| */
s32 obj_resolve_object_collisions(s32 *targetYaw) {
    if (!o) { return 0; }
    struct Object *otherObject;
    f32 dx;
    f32 dz;
    s16 angle;
    f32 radius;
    f32 otherRadius;
    f32 relativeRadius;
    f32 newCenterX;
    f32 newCenterZ;

    if (o->numCollidedObjs != 0) {
        otherObject = o->collidedObjs[0];
        if (!(otherObject->oInteractType & INTERACT_PLAYER)) {
            //! If one object moves after collisions are detected and this code
            //  runs, the objects can move toward each other (transport cloning)

            dx = otherObject->oPosX - o->oPosX;
            dz = otherObject->oPosZ - o->oPosZ;
            angle = atan2s(dx, dz); //! This should be atan2s(dz, dx)

            radius = o->hitboxRadius;
            otherRadius = otherObject->hitboxRadius;
            relativeRadius = radius / (radius + otherRadius);

            newCenterX = o->oPosX + dx * relativeRadius;
            newCenterZ = o->oPosZ + dz * relativeRadius;

            o->oPosX = newCenterX - radius * coss(angle);
            o->oPosZ = newCenterZ - radius * sins(angle);

            otherObject->oPosX = newCenterX + otherRadius * coss(angle);
            otherObject->oPosZ = newCenterZ + otherRadius * sins(angle);

            if (targetYaw != NULL && abs_angle_diff(o->oMoveAngleYaw, angle) < 0x4000) {
                // Bounce off object (or it would, if the above atan2s bug
                // were fixed)
                *targetYaw = (s16)(angle - o->oMoveAngleYaw + angle + 0x8000);
                return TRUE;
            }
        }
    }

    return FALSE;
}

/* |description|Bounces the current object off of walls, edges, and objects using `*targetYaw`|descriptionEnd| */
s32 obj_bounce_off_walls_edges_objects(s32 *targetYaw) {
    if (!o) { return 0; }
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        *targetYaw = cur_obj_reflect_move_angle_off_wall();
    } else if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
        *targetYaw = (s16)(o->oMoveAngleYaw + 0x8000);
    } else if (!obj_resolve_object_collisions(targetYaw)) {
        return FALSE;
    }

    return TRUE;
}

/* |description|Resolves collisions and turns the current object towards `targetYaw` using `turnSpeed`|descriptionEnd| */
s32 obj_resolve_collisions_and_turn(s16 targetYaw, s16 turnSpeed) {
    obj_resolve_object_collisions(NULL);

    if (cur_obj_rotate_yaw_toward(targetYaw, turnSpeed)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/* |description|Spawns mist particles, plays a sound (`oDeathSound`,) spawns coins (`oNumLootCoins`,) and hides the object if the health is less than 0 or deletes the object if the health is 0 or higher|descriptionEnd| */
void obj_die_if_health_non_positive(void) {
    if (!o) { return; }
    if (o->oHealth <= 0 || o->oSyncDeath) {
        if (o->oDeathSound == 0) {
            spawn_mist_particles_with_sound(SOUND_OBJ_DEFAULT_DEATH);
        } else if (o->oDeathSound > 0) {
            spawn_mist_particles_with_sound(o->oDeathSound);
        } else {
            spawn_mist_particles();
        }

        if ((s32)o->oNumLootCoins < 0) {
            spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
        } else {
            obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
        }
        // This doesn't do anything
        obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);

        if (o->oHealth < 0) {
            cur_obj_hide();
            cur_obj_become_intangible();
        } else {
            obj_mark_for_deletion(o);
        }
    }
}

/* |description|Sets the current object's health to 0 and runs `obj_die_if_health_non_positive()`|descriptionEnd| */
void obj_unused_die(void) {
    if (!o) { return; }
    o->oHealth = 0;
    obj_die_if_health_non_positive();
}

/* |description|Sets the current object's action, forward velocity, and vertical velocity to preset values (`OBJ_ACT_*`)|descriptionEnd| */
void obj_set_knockback_action(s32 attackType) {
    if (!o) { return; }
    switch (attackType) {
        case ATTACK_KICK_OR_TRIP:
        case ATTACK_FAST_ATTACK:
            o->oAction = OBJ_ACT_VERTICAL_KNOCKBACK;
            o->oForwardVel = 20.0f;
            o->oVelY = 50.0f;
            break;

        default:
            o->oAction = OBJ_ACT_HORIZONTAL_KNOCKBACK;
            o->oForwardVel = 50.0f;
            o->oVelY = 30.0f;
            break;
    }

    o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;

    struct Object* player = nearest_player_to_object(o);
    if (player) {
        o->oMoveAngleYaw = obj_angle_to_object(player, o);
    }
}

/* |description|Plays `SOUND_OBJ_STOMPED` and sets the current object's action to `OBJ_ACT_SQUISHED`|descriptionEnd| */
void obj_set_squished_action(void) {
    if (!o) { return; }
    cur_obj_play_sound_2(SOUND_OBJ_STOMPED);
    o->oAction = OBJ_ACT_SQUISHED;
}

/* |description||descriptionEnd| */
s32 obj_die_if_above_lava_and_health_non_positive(void) {
    if (!o) { return 0; }
    if (o->oMoveFlags & OBJ_MOVE_UNDERWATER_ON_GROUND) {
        if (o->oGravity + o->oBuoyancy > 0.0f
            || find_water_level(o->oPosX, o->oPosZ) - o->oPosY < 150.0f) {
            return FALSE;
        }
    } else if (!(o->oMoveFlags & OBJ_MOVE_ABOVE_LAVA)) {
        if (o->oMoveFlags & OBJ_MOVE_ENTERED_WATER) {
            if (o->oWallHitboxRadius < 200.0f) {
                cur_obj_play_sound_2(SOUND_OBJ_DIVING_INTO_WATER);
            } else {
                cur_obj_play_sound_2(SOUND_OBJ_DIVING_IN_WATER);
            }
        }
        return FALSE;
    }

    obj_die_if_health_non_positive();
    return TRUE;
}

s32 obj_handle_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction,
                              u8 *attackHandlers) {
    if (!o) { return 0; }
    s32 attackType;

    obj_set_hitbox(o, hitbox);

    //! Die immediately if above lava
    if (obj_die_if_above_lava_and_health_non_positive()) {
        return 1;
    } else if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
            if (o->oAction != attackedMarioAction) {
                o->oAction = attackedMarioAction;
                o->oTimer = 0;
            }
        } else {
            attackType = o->oInteractStatus & INT_STATUS_ATTACK_MASK;

            switch (attackHandlers[attackType - 1]) {
                case ATTACK_HANDLER_NOP:
                    break;

                case ATTACK_HANDLER_DIE_IF_HEALTH_NON_POSITIVE:
                    obj_die_if_health_non_positive();
                    break;

                case ATTACK_HANDLER_KNOCKBACK:
                    obj_set_knockback_action(attackType);
                    break;

                case ATTACK_HANDLER_SQUISHED:
                    obj_set_squished_action();
                    break;

                case ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL:
                    shelled_koopa_attack_handler(attackType);
                    break;

                case ATTACK_HANDLER_SET_SPEED_TO_ZERO:
                    obj_set_speed_to_zero();
                    break;

                case ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON:
                    wiggler_jumped_on_attack_handler();
                    break;

                case ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED:
                    huge_goomba_weakly_attacked();
                    break;

                case ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN:
                    o->oNumLootCoins = -1;
                    obj_set_squished_action();
                    break;
            }

            o->oInteractStatus = 0;
            return attackType;
        }
    }

    o->oInteractStatus = 0;
    return 0;
}

void obj_act_knockback(UNUSED f32 baseScale) {
    if (!o) { return; }
    cur_obj_update_floor_and_walls();

    if (o->header.gfx.animInfo.curAnim != NULL) {
        cur_obj_extend_animation_if_at_end();
    }

    //! Dies immediately if above lava
    if ((o->oMoveFlags
         & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_MASK_IN_WATER | OBJ_MOVE_HIT_WALL | OBJ_MOVE_ABOVE_LAVA))
        || (o->oAction == OBJ_ACT_VERTICAL_KNOCKBACK && o->oTimer >= 9) || o->oSyncDeath) {
        obj_die_if_health_non_positive();
    }

    cur_obj_move_standard(-78);
}

void obj_act_squished(f32 baseScale) {
    if (!o) { return; }
    f32 targetScaleY = baseScale * 0.3f;

    cur_obj_update_floor_and_walls();

    if (o->header.gfx.animInfo.curAnim != NULL) {
        cur_obj_extend_animation_if_at_end();
    }

    if (approach_f32_ptr(&o->header.gfx.scale[1], targetScaleY, baseScale * 0.14f)) {
        o->header.gfx.scale[0] = o->header.gfx.scale[2] = baseScale * 2.0f - o->header.gfx.scale[1];

        if (o->oTimer >= 16 || o->oSyncDeath) {
            obj_die_if_health_non_positive();
        }
    }

    o->oForwardVel = 0.0f;
    cur_obj_move_standard(-78);
}

s32 obj_update_standard_actions(f32 scale) {
    if (!o) { return 0; }
    if (o->oAction < 100) {
        return TRUE;
    } else {
        cur_obj_become_intangible();

        switch (o->oAction) {
            case OBJ_ACT_HORIZONTAL_KNOCKBACK:
            case OBJ_ACT_VERTICAL_KNOCKBACK:
                obj_act_knockback(scale);
                break;

            case OBJ_ACT_SQUISHED:
                obj_act_squished(scale);
                break;
        }

        return FALSE;
    }
}

/* |description|Checks the current object's interaction status and sets action to `attackedMarioAction` if Mario has been attacked and runs `obj_die_if_health_non_positive()` if the object is attacked by Mario. Sets the hitbox parameters and resets interaction status to 0|descriptionEnd| */
s32 obj_check_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction) {
    if (!o) { return 0; }
    s32 attackType;

    obj_set_hitbox(o, hitbox);

    //! Dies immediately if above lava
    if (obj_die_if_above_lava_and_health_non_positive()) {
        return 1;
    } else if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
            if (o->oAction != attackedMarioAction) {
                o->oAction = attackedMarioAction;
                o->oTimer = 0;
            }
        } else {
            attackType = o->oInteractStatus & INT_STATUS_ATTACK_MASK;
            obj_die_if_health_non_positive();
            o->oInteractStatus = 0;
            return attackType;
        }
    }

    o->oInteractStatus = 0;
    return 0;
}

/* |description|Moves the current object for specifically one second (`oTimer` < 30)|descriptionEnd| */
s32 obj_move_for_one_second(s32 endAction) {
    if (!o) { return 0; }
    cur_obj_update_floor_and_walls();
    cur_obj_extend_animation_if_at_end();

    if (o->oTimer > 30) {
        o->oAction = endAction;
        return TRUE;
    }

    cur_obj_move_standard(-78);
    return FALSE;
}

/**
 * If we are far from home (> threshold away), then set oAngleToMario to the
 * angle to home and oDistanceToMario to 25000.
 * If we are close to home, but Mario is far from us (> threshold away), then
 * keep oAngleToMario the same and set oDistanceToMario to 20000.
 * If we are close to both home and Mario, then keep both oAngleToMario and
 * oDistanceToMario the same.
 *
 * The point of this function is to avoid having to write extra code to get
 * the object to return to home. When Mario is far away and the object is far
 * from home, it could theoretically re-use the "approach Mario" logic to approach
 * its home instead.
 * However, most objects that use this function handle the far-from-home case
 * separately anyway.
 * This function causes seemingly erroneous behavior in some objects that try to
 * attack Mario (e.g. fly guy shooting fire or lunging), especially when combined
 * with partial updates.
 */
void treat_far_home_as_mario(f32 threshold, s32* distanceToPlayer, s32* angleToPlayer) {
    if (!o) { return; }
    f32 dx = o->oHomeX - o->oPosX;
    f32 dy = o->oHomeY - o->oPosY;
    f32 dz = o->oHomeZ - o->oPosZ;
    f32 distance = sqrtf(dx * dx + dy * dy + dz * dz);

    if (distance > threshold) {
        o->oAngleToMario = atan2s(dz, dx);
        o->oDistanceToMario = 25000.0f;
        if (distanceToPlayer != NULL) {
            *distanceToPlayer = o->oDistanceToMario;
        }
        if (angleToPlayer != NULL) {
            *angleToPlayer = o->oAngleToMario;
        }
    } else {
        struct Object* player = nearest_player_to_object(o);
        if (player) {
            dx = o->oHomeX - player->oPosX;
            dy = o->oHomeY - player->oPosY;
            dz = o->oHomeZ - player->oPosZ;
            distance = sqrtf(dx * dx + dy * dy + dz * dz);

            if (distance > threshold) {
                o->oDistanceToMario = 20000.0f;
                if (distanceToPlayer != NULL) {
                    *distanceToPlayer = o->oDistanceToMario;
                }
            }
        } else {
            o->oDistanceToMario = 20000.0f;
            if (distanceToPlayer != NULL) {
                *distanceToPlayer = o->oDistanceToMario;
            }
        }
    }
}

#include "behaviors/koopa.inc.c" // TODO: Text arg field name
#include "behaviors/pokey.inc.c"
#include "behaviors/swoop.inc.c"
#include "behaviors/fly_guy.inc.c"
#include "behaviors/goomba.inc.c"
#include "behaviors/chain_chomp.inc.c" // TODO: chain_chomp_sub_act_lunge documentation
#include "behaviors/wiggler.inc.c"     // TODO
#include "behaviors/spiny.inc.c"
#include "behaviors/enemy_lakitu.inc.c" // TODO
#include "behaviors/cloud.inc.c"
#include "behaviors/camera_lakitu.inc.c" // TODO: 104 label, follow cam documentation
#include "behaviors/monty_mole.inc.c"    // TODO
#include "behaviors/platform_on_track.inc.c"
#include "behaviors/seesaw_platform.inc.c"
#include "behaviors/ferris_wheel.inc.c"
#include "behaviors/water_bomb.inc.c" // TODO: Shadow position
#include "behaviors/ttc_rotating_solid.inc.c"
#include "behaviors/ttc_pendulum.inc.c"
#include "behaviors/ttc_treadmill.inc.c" // TODO
#include "behaviors/ttc_moving_bar.inc.c"
#include "behaviors/ttc_cog.inc.c"
#include "behaviors/ttc_pit_block.inc.c"
#include "behaviors/ttc_elevator.inc.c"
#include "behaviors/ttc_2d_rotator.inc.c"
#include "behaviors/ttc_spinner.inc.c"
#include "behaviors/mr_blizzard.inc.c"
#include "behaviors/sliding_platform_2.inc.c"
#include "behaviors/rotating_octagonal_plat.inc.c"
#include "behaviors/animated_floor_switch.inc.c"
#include "behaviors/activated_bf_plat.inc.c"
#include "behaviors/recovery_heart.inc.c"
#include "behaviors/water_bomb_cannon.inc.c"
#include "behaviors/unagi.inc.c"
#include "behaviors/dorrie.inc.c"
#include "behaviors/haunted_chair.inc.c"
#include "behaviors/mad_piano.inc.c"
#include "behaviors/flying_bookend_switch.inc.c"

/**
 * Used by bowser, fly guy, piranha plant, and fire spitters.
 */
struct Object* obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, s32 model,
                   f32 startSpeed, f32 endSpeed, s16 movePitch) {
    struct Object *obj = spawn_object_relative_with_scale(1, relativePosX, relativePosY, relativePosZ,
                                                           scale, o, model, bhvSmallPiranhaFlame);

    if (obj != NULL) {
        obj->oSmallPiranhaFlameStartSpeed = startSpeed;
        obj->oSmallPiranhaFlameEndSpeed = endSpeed;
        obj->oSmallPiranhaFlameModel = model;
        obj->oMoveAnglePitch = movePitch;
    }
    return obj;
}

#include "behaviors/fire_piranha_plant.inc.c"
#include "behaviors/fire_spitter.inc.c"
#include "behaviors/flame.inc.c"
#include "behaviors/snufit.inc.c"
#include "behaviors/horizontal_grindel.inc.c"
#include "behaviors/eyerok.inc.c"
#include "behaviors/klepto.inc.c"
#include "behaviors/bird.inc.c"
#include "behaviors/racing_penguin.inc.c"
#include "behaviors/coffin.inc.c"
#include "behaviors/clam.inc.c"
#include "behaviors/skeeter.inc.c"
#include "behaviors/swing_platform.inc.c"
#include "behaviors/donut_platform.inc.c"
#include "behaviors/ddd_pole.inc.c"
#include "behaviors/reds_star_marker.inc.c"
#include "behaviors/triplet_butterfly.inc.c"
#include "behaviors/bubba.inc.c"
