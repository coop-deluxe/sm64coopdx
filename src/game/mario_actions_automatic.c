#include <PR/ultratypes.h>

#include "sm64.h"
#include "behavior_data.h"
#include "mario_actions_automatic.h"
#include "audio/external.h"
#include "area.h"
#include "mario.h"
#include "mario_step.h"
#include "engine/math_util.h"
#include "memory.h"
#include "engine/graph_node.h"
#include "save_file.h"
#include "engine/surface_collision.h"
#include "interaction.h"
#include "camera.h"
#include "level_table.h"
#include "rumble_init.h"
#include "object_helpers.h"
#include "obj_behaviors.h"
#include "level_update.h"
#include "mario_step.h"
#include "pc/debuglog.h"
#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/lua/smlua.h"

#define POLE_NONE          0
#define POLE_TOUCHED_FLOOR 1
#define POLE_FELL_OFF      2

#define HANG_NONE            0
#define HANG_HIT_CEIL_OR_OOB 1
#define HANG_LEFT_CEIL       2

/* |description|
Spawns leaf particles when Mario climbs a tree, if he is sufficiently high above the floor.
In Shifting Sand Land, the leaf effect spawns higher due to the taller palm trees
|descriptionEnd| */
void add_tree_leaf_particles(struct MarioState *m) {
    if (!m) { return; }
    f32 leafHeight;

    if (m->usedObj != NULL && m->usedObj->behavior == segmented_to_virtual(smlua_override_behavior(bhvTree))) {
        // make leaf effect spawn higher on the Shifting Sand Land palm tree
        if (gCurrLevelNum == LEVEL_SSL) {
            leafHeight = 250.0f;
        } else {
            leafHeight = 100.0f;
        }
        if (m->pos[1] - m->floorHeight > leafHeight) {
            set_mario_particle_flags(m, PARTICLE_LEAF, FALSE);
        }
    }
}

/* |description|
Plays the appropriate climbing sound effect depending on whether Mario is on a tree or a pole. If `b == 1`, it plays the "climbing up" sound; otherwise, it plays the "sliding down" sound
|descriptionEnd| */
void play_climbing_sounds(struct MarioState *m, s32 b) {
    if (!m) { return; }
    s32 isOnTree = (m->usedObj != NULL && m->usedObj->behavior == segmented_to_virtual(smlua_override_behavior(bhvTree)));

    if (b == 1) {
        if (is_anim_past_frame(m, 1)) {
            play_sound(isOnTree ? SOUND_ACTION_CLIMB_UP_TREE : SOUND_ACTION_CLIMB_UP_POLE,
                       m->marioObj->header.gfx.cameraToObject);
        }
    } else {
        play_sound(isOnTree ? SOUND_MOVING_SLIDE_DOWN_TREE : SOUND_MOVING_SLIDE_DOWN_POLE,
                   m->marioObj->header.gfx.cameraToObject);
    }
}

/* |description|
Sets Mario's position and alignment while he is on a climbable pole or tree. This function checks collisions with floors and ceilings, and updates Mario's action if he leaves the pole or touches the floor.
Useful for ensuring Mario's correct placement and transitions when climbing poles or trees
|descriptionEnd| */
s32 set_pole_position(struct MarioState *m, f32 offsetY) {
    if (!m) { return 0; }
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }

    // This is here so if somehow a pole despawns while you are on it.
    // You will just drop from it.
    if (m->usedObj == NULL) {
        // If Mario is no longer interacting with the pole, stop the pole holding action.
        set_mario_action(m, ACT_FREEFALL, 0);
        return POLE_FELL_OFF;
    }

    UNUSED s32 unused1;
    UNUSED s32 unused2;
    UNUSED s32 unused3;
    struct Surface *floor;
    struct Surface *ceil;
    f32 floorHeight;
    f32 ceilHeight;
    s32 collided;
    s32 result = POLE_NONE;
    f32 poleTop = m->usedObj->hitboxHeight - 100.0f;
    struct Object *marioObj = m->marioObj;

    if (marioObj->oMarioPolePos > poleTop) {
        marioObj->oMarioPolePos = poleTop;
    }

    m->pos[0] = m->usedObj->oPosX;
    m->pos[2] = m->usedObj->oPosZ;
    m->pos[1] = m->usedObj->oPosY + marioObj->oMarioPolePos + offsetY;

    collided = f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 60.0f, 50.0f);
    collided |= f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 30.0f, 24.0f);

    ceilHeight = vec3f_mario_ceil(m->pos, m->pos[1], &ceil);
    if (m->pos[1] > ceilHeight - 160.0f) {
        m->pos[1] = ceilHeight - 160.0f;
        marioObj->oMarioPolePos = m->pos[1] - m->usedObj->oPosY;
    }

    floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &floor);
    if (m->pos[1] < floorHeight) {
        m->pos[1] = floorHeight;
        set_mario_action(m, ACT_IDLE, 0);
        result = POLE_TOUCHED_FLOOR;
    } else if (marioObj->oMarioPolePos < -m->usedObj->hitboxDownOffset) {
        m->pos[1] = m->usedObj->oPosY - m->usedObj->hitboxDownOffset;
        set_mario_action(m, ACT_FREEFALL, 0);
        result = POLE_FELL_OFF;
    } else if (collided) {
        if (m->pos[1] > floorHeight + 20.0f) {
            m->forwardVel = -2.0f;
            set_mario_action(m, ACT_SOFT_BONK, 0);
            result = POLE_FELL_OFF;
        } else {
            set_mario_action(m, ACT_IDLE, 0);
            result = POLE_TOUCHED_FLOOR;
        }
    }

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, m->usedObj->oMoveAnglePitch, m->faceAngle[1],
              m->usedObj->oMoveAngleRoll);

    return result;
}

s32 act_holding_pole(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }
    if (m->usedObj == NULL) { return FALSE; }

#ifdef VERSION_JP
    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
        m->faceAngle[1] += 0x8000;
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }

    if (m->input & INPUT_Z_PRESSED) {
        add_tree_leaf_particles(m);
        m->forwardVel = -2.0f;
        return set_mario_action(m, ACT_SOFT_BONK, 0);
    }
#else
    if ((m->input & INPUT_Z_PRESSED) || m->health < 0x100) {
        add_tree_leaf_particles(m);
        m->forwardVel = -2.0f;
        return set_mario_action(m, ACT_SOFT_BONK, 0);
    }

    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
        m->faceAngle[1] += 0x8000;
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }
#endif

    if (m->controller->stickY > 16.0f) {
        f32 poleTop = m->usedObj->hitboxHeight - 100.0f;
        const BehaviorScript *poleBehavior = virtual_to_segmented(0x13, m->usedObj->behavior);

        if (marioObj->oMarioPolePos < poleTop - 0.4f) {
            return set_mario_action(m, ACT_CLIMBING_POLE, 0);
        }

        if (poleBehavior != smlua_override_behavior(bhvGiantPole) && m->controller->stickY > 50.0f) {
            return set_mario_action(m, ACT_TOP_OF_POLE_TRANSITION, 0);
        }
    }

    if (m->controller->stickY < -16.0f) {
        marioObj->oMarioPoleYawVel -= m->controller->stickY * 2;
        if (marioObj->oMarioPoleYawVel > 0x1000) {
            marioObj->oMarioPoleYawVel = 0x1000;
        }

        m->faceAngle[1] += marioObj->oMarioPoleYawVel;
        marioObj->oMarioPolePos -= marioObj->oMarioPoleYawVel / 0x100;

        if (m->usedObj->behavior == segmented_to_virtual(smlua_override_behavior(bhvTree))) {
            //! The Shifting Sand Land palm tree check is done climbing up in
            // add_tree_leaf_particles, but not here, when climbing down.
            if (m->pos[1] - m->floorHeight > 100.0f) {
                set_mario_particle_flags(m, PARTICLE_LEAF, FALSE);
            }
        }
        play_climbing_sounds(m, 2);
        reset_rumble_timers(m);
        set_sound_moving_speed(SOUND_BANK_MOVING, marioObj->oMarioPoleYawVel / 0x100 * 2);
    } else {
        marioObj->oMarioPoleYawVel = 0;
        m->faceAngle[1] -= m->controller->stickX * 16.0f;
    }

    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        set_character_animation(m, CHAR_ANIM_IDLE_ON_POLE);
    }

    return FALSE;
}

s32 act_climbing_pole(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }
    s32 sp24;
    struct Object *marioObj = m->marioObj;
    s16 cameraAngle = m->area->camera->yaw;

#ifndef VERSION_JP
    if (m->health < 0x100) {
        add_tree_leaf_particles(m);
        m->forwardVel = -2.0f;
        return set_mario_action(m, ACT_SOFT_BONK, 0);
    }
#endif

    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
        m->faceAngle[1] += 0x8000;
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }

    if (m->controller->stickY < 8.0f) {
        return set_mario_action(m, ACT_HOLDING_POLE, 0);
    }

    marioObj->oMarioPolePos += m->controller->stickY / 8.0f;
    marioObj->oMarioPoleYawVel = 0;
    m->faceAngle[1] = cameraAngle - approach_s32((s16)(cameraAngle - m->faceAngle[1]), 0, 0x400, 0x400);

    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        sp24 = m->controller->stickY / 4.0f * 0x10000;
        set_character_anim_with_accel(m, CHAR_ANIM_CLIMB_UP_POLE, sp24);
        add_tree_leaf_particles(m);
        play_climbing_sounds(m, 1);
    }

    return FALSE;
}

s32 act_grab_pole_slow(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }
    play_character_sound_if_no_flag(m, CHAR_SOUND_WHOA, MARIO_MARIO_SOUND_PLAYED);

    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        set_character_animation(m, CHAR_ANIM_GRAB_POLE_SHORT);
        if (is_anim_at_end(m)) {
            set_mario_action(m, ACT_HOLDING_POLE, 0);
        }
        add_tree_leaf_particles(m);
    }

    return FALSE;
}

s32 act_grab_pole_fast(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }

    play_character_sound_if_no_flag(m, CHAR_SOUND_WHOA, MARIO_MARIO_SOUND_PLAYED);
    m->faceAngle[1] += marioObj->oMarioPoleYawVel;
    marioObj->oMarioPoleYawVel = marioObj->oMarioPoleYawVel * 8 / 10;

    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        if (marioObj->oMarioPoleYawVel > 0x800) {
            set_character_animation(m, CHAR_ANIM_GRAB_POLE_SWING_PART1);
        } else {
            set_character_animation(m, CHAR_ANIM_GRAB_POLE_SWING_PART2);
            if (is_anim_at_end(m)) {
                marioObj->oMarioPoleYawVel = 0;
                set_mario_action(m, ACT_HOLDING_POLE, 0);
            }
        }
        add_tree_leaf_particles(m);
    }

    return FALSE;
}

s32 act_top_of_pole_transition(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }

    marioObj->oMarioPoleYawVel = 0;
    if (m->actionArg == 0) {
        set_character_animation(m, CHAR_ANIM_START_HANDSTAND);
        if (is_anim_at_end(m)) {
            return set_mario_action(m, ACT_TOP_OF_POLE, 0);
        }
    } else {
        set_character_animation(m, CHAR_ANIM_RETURN_FROM_HANDSTAND);
        if (m->marioObj->header.gfx.animInfo.animFrame == 0) {
            return set_mario_action(m, ACT_HOLDING_POLE, 0);
        }
    }

    set_pole_position(m, return_mario_anim_y_translation(m));
    return FALSE;
}

s32 act_top_of_pole(struct MarioState *m) {
    if (!m) { return 0; }
    UNUSED struct Object *marioObj = m->marioObj;
    if (m->usedObj == NULL) { m->usedObj = cur_obj_find_nearest_pole(); }

    if (m->input & INPUT_A_PRESSED) {
        return set_mario_action(m, ACT_TOP_OF_POLE_JUMP, 0);
    }
    if (m->controller->stickY < -16.0f) {
        return set_mario_action(m, ACT_TOP_OF_POLE_TRANSITION, 1);
    }

    m->faceAngle[1] -= m->controller->stickX * 16.0f;

    set_character_animation(m, CHAR_ANIM_HANDSTAND_IDLE);
    set_pole_position(m, return_mario_anim_y_translation(m));
    return FALSE;
}

/* |description|
Performs a single step of movement while Mario is hanging from a ceiling. It handles wall collisions and checks the floor and ceiling to determine if Mario remains hanging, leaves the ceiling, or hits it
|descriptionEnd| */
s32 perform_hanging_step(struct MarioState *m, Vec3f nextPos) {
    if (!m) { return 0; }
    UNUSED s32 unused;
    struct Surface *ceil;
    struct Surface *floor;
    f32 ceilHeight;
    f32 floorHeight;
    f32 ceilOffset;

    s32 returnValue = 0;
    if (smlua_call_event_hooks_mario_param_and_int_ret_int(HOOK_BEFORE_PHYS_STEP, m, STEP_TYPE_HANG, &returnValue)) return returnValue;

    struct WallCollisionData wcd = { 0 };
    resolve_and_return_wall_collisions_data(nextPos, 50.0f, 50.0f, &wcd);
    m->wall = (wcd.numWalls > 0)
            ? wcd.walls[wcd.numWalls - 1]
            : NULL;

    floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
    ceilHeight = vec3f_mario_ceil(nextPos, floorHeight, &ceil);

    if (floor == NULL) {
        return HANG_HIT_CEIL_OR_OOB;
    }
    if (ceil == NULL) {
        return HANG_LEFT_CEIL;
    }
    if (ceilHeight - floorHeight <= 160.0f) {
        return HANG_HIT_CEIL_OR_OOB;
    }
    if (ceil->type != SURFACE_HANGABLE) {
        return HANG_LEFT_CEIL;
    }

    ceilOffset = ceilHeight - (nextPos[1] + 160.0f);
    if (ceilOffset < -30.0f) {
        return HANG_HIT_CEIL_OR_OOB;
    }
    if (ceilOffset > 30.0f) {
        return HANG_LEFT_CEIL;
    }

    nextPos[1] = m->ceilHeight - 160.0f;
    vec3f_copy(m->pos, nextPos);

    m->floor = floor;
    m->floorHeight = floorHeight;
    m->ceil = ceil;
    m->ceilHeight = ceilHeight;

    return HANG_NONE;
}

/* |description|
Updates Mario's velocity and position while he is moving across a hangable ceiling. It calls `perform_hanging_step()` to handle collisions and movement logic, returning a status code indicating if Mario is still hanging or if he left the ceiling
|descriptionEnd| */
s32 update_hang_moving(struct MarioState *m) {
    if (!m) { return 0; }
    s32 stepResult;
    Vec3f nextPos = { 0 };
    f32 maxSpeed = 4.0f;

    m->forwardVel += 1.0f;
    if (m->forwardVel > maxSpeed) {
        m->forwardVel = maxSpeed;
    }

    m->faceAngle[1] =
        m->intendedYaw - approach_s32((s16)(m->intendedYaw - m->faceAngle[1]), 0, 0x800, 0x800);

    m->slideYaw = m->faceAngle[1];
    m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);

    m->vel[0] = m->slideVelX;
    m->vel[1] = 0.0f;
    m->vel[2] = m->slideVelZ;

    if (m->ceil) {
        nextPos[0] = m->pos[0] - m->ceil->normal.y * m->vel[0];
        nextPos[2] = m->pos[2] - m->ceil->normal.y * m->vel[2];
        nextPos[1] = m->pos[1];
    }

    stepResult = perform_hanging_step(m, nextPos);

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    return stepResult;
}

/* |description|
Keeps Mario stationary while he is hanging from a ceiling. This function zeroes out his velocity and ensures he remains aligned with the ceiling
|descriptionEnd| */
void update_hang_stationary(struct MarioState *m) {
    if (!m) { return; }
    m->forwardVel = 0.0f;
    m->slideVelX = 0.0f;
    m->slideVelZ = 0.0f;

    m->pos[1] = m->ceilHeight - 160.0f;
    vec3f_copy(m->vel, gVec3fZero);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
}

s32 act_start_hanging(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->actionTimer++ == 0) {
        queue_rumble_data_mario(m, 5, 80);
    }

    if ((m->input & INPUT_NONZERO_ANALOG) && m->actionTimer >= 31) {
        return set_mario_action(m, ACT_HANGING, 0);
    }

    if (!(m->input & INPUT_A_DOWN)) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_Z_PRESSED) {
        return set_mario_action(m, ACT_GROUND_POUND, 0);
    }

    if (m->ceil == NULL || m->ceil->type != SURFACE_HANGABLE) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    set_character_animation(m, CHAR_ANIM_HANG_ON_CEILING);
    play_sound_if_no_flag(m, SOUND_ACTION_HANGING_STEP, MARIO_ACTION_SOUND_PLAYED);
    update_hang_stationary(m);

    if (is_anim_at_end(m)) {
        set_mario_action(m, ACT_HANGING, 0);
    }

    return FALSE;
}

s32 act_hanging(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_NONZERO_ANALOG) {
        return set_mario_action(m, ACT_HANG_MOVING, m->actionArg);
    }

    if (!(m->input & INPUT_A_DOWN)) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_Z_PRESSED) {
        return set_mario_action(m, ACT_GROUND_POUND, 0);
    }

    if (m->ceil == NULL || m->ceil->type != SURFACE_HANGABLE) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->actionArg & 1) {
        set_character_animation(m, CHAR_ANIM_HANDSTAND_LEFT);
    } else {
        set_character_animation(m, CHAR_ANIM_HANDSTAND_RIGHT);
    }

    update_hang_stationary(m);

    return FALSE;
}

s32 act_hang_moving(struct MarioState *m) {
    if (!m) { return 0; }
    if (!(m->input & INPUT_A_DOWN)) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_Z_PRESSED) {
        return set_mario_action(m, ACT_GROUND_POUND, 0);
    }

    if (m->ceil == NULL || m->ceil->type != SURFACE_HANGABLE) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->actionArg & 1) {
        set_character_animation(m, CHAR_ANIM_MOVE_ON_WIRE_NET_RIGHT);
    } else {
        set_character_animation(m, CHAR_ANIM_MOVE_ON_WIRE_NET_LEFT);
    }

    if (m->marioObj->header.gfx.animInfo.animFrame == 12) {
        play_sound(SOUND_ACTION_HANGING_STEP, m->marioObj->header.gfx.cameraToObject);
        queue_rumble_data_mario(m, 5, 30);
    }

    if (is_anim_past_end(m)) {
        m->actionArg ^= 1;
        if (m->input & INPUT_ZERO_MOVEMENT) {
            return set_mario_action(m, ACT_HANGING, m->actionArg);
        }
    }

    if (update_hang_moving(m) == HANG_LEFT_CEIL) {
        set_mario_action(m, ACT_FREEFALL, 0);
    }

    return FALSE;
}

/* |description|
Handles Mario letting go of a ledge by adjusting his position and setting his velocity to make him fall away from the ledge. The action then transitions to a 'soft bonk' state
|descriptionEnd| */
s32 let_go_of_ledge(struct MarioState *m) {
    if (!m) { return 0; }
    f32 floorHeight;
    struct Surface *floor;

    m->vel[1] = 0.0f;
    m->forwardVel = -8.0f;
    m->pos[0] -= 60.0f * sins(m->faceAngle[1]);
    m->pos[2] -= 60.0f * coss(m->faceAngle[1]);

    floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &floor);
    if (floorHeight < m->pos[1] - 100.0f) {
        m->pos[1] -= 100.0f;
    } else {
        m->pos[1] = floorHeight;
    }

    return set_mario_action(m, ACT_SOFT_BONK, 0);
}

/* |description|
Moves Mario onto the top of a ledge once he finishes climbing it. This shifts Mario forward slightly on the ledge and updates his animation accordingly
|descriptionEnd| */
void climb_up_ledge(struct MarioState *m) {
    if (!m) { return; }
    set_character_animation(m, CHAR_ANIM_IDLE_HEAD_LEFT);
    m->pos[0] += 14.0f * sins(m->faceAngle[1]);
    m->pos[2] += 14.0f * coss(m->faceAngle[1]);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
}

/* |description|
Gradually adjusts the camera position to track Mario as he climbs a ledge. This creates a smoother view transition from the ledge-grab camera angle to Mario's new location on top of the ledge
|descriptionEnd| */
void update_ledge_climb_camera(struct MarioState *m) {
    if (!m) { return; }
    f32 sp4;

    if (m->actionTimer < 14) {
        sp4 = m->actionTimer;
    } else {
        sp4 = 14.0f;
    }
    m->statusForCamera->pos[0] = m->pos[0] + sp4 * sins(m->faceAngle[1]);
    m->statusForCamera->pos[2] = m->pos[2] + sp4 * coss(m->faceAngle[1]);
    m->statusForCamera->pos[1] = m->pos[1];
    m->actionTimer++;
    m->flags |= MARIO_UNKNOWN_25;
}

/* |description|
Updates Mario's climb onto a ledge by setting the chosen climbing animation and transitioning to the specified end action (e.g., standing idle) once the animation finishes. If the end action is `ACT_IDLE`, Mario is placed on top of the ledge
|descriptionEnd| */
void update_ledge_climb(struct MarioState *m, s32 animation, u32 endAction) {
    stop_and_set_height_to_floor(m);

    set_character_animation(m, animation);
    if (is_anim_at_end(m)) {
        set_mario_action(m, endAction, 0);
        if (endAction == ACT_IDLE) {
            climb_up_ledge(m);
        }
    }
}

s32 act_ledge_grab(struct MarioState *m) {
    if (!m) { return 0; }
    f32 heightAboveFloor;
    s16 intendedDYaw = m->intendedYaw - m->faceAngle[1];
    s32 hasSpaceForMario = (m->ceilHeight - m->floorHeight >= 160.0f);

    if (m->actionTimer < 10) {
        m->actionTimer++;
    }

    if (m->floor->normal.y < 0.9063078f) {
        return let_go_of_ledge(m);
    }

    if (m->input & (INPUT_Z_PRESSED | INPUT_OFF_FLOOR)) {
        return let_go_of_ledge(m);
    }

    if ((m->input & INPUT_A_PRESSED) && hasSpaceForMario) {
        return set_mario_action(m, ACT_LEDGE_CLIMB_FAST, 0);
    }

    if (m->input & INPUT_UNKNOWN_10) {
        if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_UNK1) {
            m->hurtCounter += (m->flags & MARIO_CAP_ON_HEAD) ? 12 : 18;
        }
        return let_go_of_ledge(m);
    }
#ifdef VERSION_EU
    // On EU, you can't slow climb up ledges while holding A.
    if (m->actionTimer == 10 && (m->input & INPUT_NONZERO_ANALOG) && !(m->input & INPUT_A_DOWN))
#else
    if (m->actionTimer == 10 && (m->input & INPUT_NONZERO_ANALOG))
#endif
    {
        if (intendedDYaw >= -0x4000 && intendedDYaw <= 0x4000) {
            if (hasSpaceForMario) {
                return set_mario_action(m, ACT_LEDGE_CLIMB_SLOW_1, 0);
            }
        } else {
            return let_go_of_ledge(m);
        }
    }

    heightAboveFloor = m->pos[1] - find_floor_height_relative_polar(m, -0x8000, 30.0f);
    if (hasSpaceForMario && heightAboveFloor < 100.0f) {
        return set_mario_action(m, ACT_LEDGE_CLIMB_FAST, 0);
    }

    if (m->actionArg == 0) {
        play_character_sound_if_no_flag(m, CHAR_SOUND_WHOA, MARIO_MARIO_SOUND_PLAYED);
    }

    stop_and_set_height_to_floor(m);
    set_character_animation(m, CHAR_ANIM_IDLE_ON_LEDGE);

    return FALSE;
}

s32 act_ledge_climb_slow(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_OFF_FLOOR) {
        return let_go_of_ledge(m);
    }

    if (m->actionTimer >= 28
        && (m->input
            & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE))) {
        climb_up_ledge(m);
        return check_common_action_exits(m);
    }

    if (m->actionTimer == 10) {
        play_character_sound_if_no_flag(m, CHAR_SOUND_EEUH, MARIO_MARIO_SOUND_PLAYED);
    }

    update_ledge_climb(m, CHAR_ANIM_SLOW_LEDGE_GRAB, ACT_IDLE);

    update_ledge_climb_camera(m);
    if (m->marioObj->header.gfx.animInfo.animFrame == 17) {
        m->action = ACT_LEDGE_CLIMB_SLOW_2;
    }

    return FALSE;
}

s32 act_ledge_climb_down(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_OFF_FLOOR) {
        return let_go_of_ledge(m);
    }

    play_character_sound_if_no_flag(m, CHAR_SOUND_WHOA, MARIO_MARIO_SOUND_PLAYED);

    update_ledge_climb(m, CHAR_ANIM_CLIMB_DOWN_LEDGE, ACT_LEDGE_GRAB);
    m->actionArg = 1;

    return FALSE;
}

s32 act_ledge_climb_fast(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->input & INPUT_OFF_FLOOR) {
        return let_go_of_ledge(m);
    }

    play_character_sound_if_no_flag(m, CHAR_SOUND_UH2, MARIO_MARIO_SOUND_PLAYED);

    update_ledge_climb(m, CHAR_ANIM_FAST_LEDGE_GRAB, ACT_IDLE);

    if (m->marioObj->header.gfx.animInfo.animFrame == 8) {
        play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
    }
    update_ledge_climb_camera(m);

    return FALSE;
}

s32 act_grabbed(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_UNK2) {
        s32 thrown = (m->marioObj->oInteractStatus & INT_STATUS_MARIO_UNK6) == 0;

        if (m->usedObj != NULL) {
            m->faceAngle[1] = m->usedObj->oMoveAngleYaw;
        }

        vec3f_copy(m->pos, m->marioObj->header.gfx.pos);
        queue_rumble_data_mario(m, 5, 60);

        m->heldByObj = NULL;
        return set_mario_action(m, (m->forwardVel >= 0.0f) ? ACT_THROWN_FORWARD : ACT_THROWN_BACKWARD,
                                thrown);
    }
    if (m->usedObj != NULL) { m->heldByObj = m->usedObj; }
    set_character_animation(m, CHAR_ANIM_BEING_GRABBED);

    // check if they should still be grabbed
    if (m->playerIndex == 0) {
        // check if the object holding me is being held
        u8 heldObjIsHeld = FALSE;
        if (m->heldByObj != NULL) {
            for (s32 i = 0; i < MAX_PLAYERS; i++) {
                if (!is_player_active(&gMarioStates[i])) { continue; }
                if (gMarioStates[i].heldObj == m->heldByObj) { heldObjIsHeld = TRUE; }
            }
        }

        // error state, get out of grab
        if (heldObjIsHeld || m->heldByObj == NULL || !(m->heldByObj->oInteractStatus | INT_STATUS_GRABBED_MARIO) || (m->heldByObj->usingObj != m->marioObj && m->actionArg != 0)) {
            m->heldByObj = NULL;
            return set_mario_action(m, (m->forwardVel >= 0.0f) ? ACT_THROWN_FORWARD : ACT_THROWN_BACKWARD, FALSE);
        }
    }

    if (m->actionArg == 0) { m->actionArg = 1; }

    return FALSE;
}

s32 act_in_cannon(struct MarioState *m) {
    if (!m) { return 0; }
    struct Object *marioObj = m->marioObj;
    s16 startFacePitch = m->faceAngle[0];
    s16 startFaceYaw = m->faceAngle[1];

    f32 cannonSensitivity = 5.0f;

    if (m->usedObj != NULL) {
        switch (m->actionState) {
            case 0:
                m->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
                m->usedObj->oInteractStatus = INT_STATUS_INTERACTED;

                m->statusForCamera->cameraEvent = CAM_EVENT_CANNON;
                m->statusForCamera->usedObj = m->usedObj;

                vec3f_set(m->vel, 0.0f, 0.0f, 0.0f);

                m->pos[0] = m->usedObj->oPosX;
                m->pos[1] = m->usedObj->oPosY + 350.0f;
                m->pos[2] = m->usedObj->oPosZ;

                m->forwardVel = 0.0f;

                m->actionState = 1;
                break;

            case 1:
                if (m->usedObj->oAction == 1) {
                    m->faceAngle[0] = m->usedObj->oMoveAnglePitch;
                    m->faceAngle[1] = m->usedObj->oMoveAngleYaw;

                    marioObj->oMarioCannonObjectYaw = m->usedObj->oMoveAngleYaw;
                    marioObj->oMarioCannonInputYaw = 0;

                    m->actionState = 2;
                }
                break;

            case 2:
                m->faceAngle[0] -= (s16)(m->controller->stickY * cannonSensitivity);
                marioObj->oMarioCannonInputYaw -= (s16)(m->controller->stickX * cannonSensitivity);

                if (m->faceAngle[0] > 0x38E3) {
                    m->faceAngle[0] = 0x38E3;
                }
                if (m->faceAngle[0] < 0) {
                    m->faceAngle[0] = 0;
                }

                if (marioObj->oMarioCannonInputYaw > 0x4000) {
                    marioObj->oMarioCannonInputYaw = 0x4000;
                }
                if (marioObj->oMarioCannonInputYaw < -0x4000) {
                    marioObj->oMarioCannonInputYaw = -0x4000;
                }

                m->faceAngle[1] = marioObj->oMarioCannonObjectYaw + marioObj->oMarioCannonInputYaw;

                extern struct MarioState gMarioStates[];
                if (m->input & INPUT_A_PRESSED && m == &gMarioStates[0]) {
                    m->forwardVel = 100.0f * coss(m->faceAngle[0]);

                    m->vel[1] = 100.0f * sins(m->faceAngle[0]);

                    m->pos[0] += 120.0f * coss(m->faceAngle[0]) * sins(m->faceAngle[1]);
                    m->pos[1] += 120.0f * sins(m->faceAngle[0]);
                    m->pos[2] += 120.0f * coss(m->faceAngle[0]) * coss(m->faceAngle[1]);

                    play_sound(SOUND_ACTION_FLYING_FAST, m->marioObj->header.gfx.cameraToObject);
                    play_sound(SOUND_OBJ_POUNDING_CANNON, m->marioObj->header.gfx.cameraToObject);

                    m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;

                    set_mario_action(m, ACT_SHOT_FROM_CANNON, 0);
                    queue_rumble_data_mario(m, 60, 70);
                    m->usedObj->oAction = 2;
                    return FALSE;
                } else {
                    if (m->faceAngle[0] != startFacePitch || m->faceAngle[1] != startFaceYaw) {
                        play_sound(SOUND_MOVING_AIM_CANNON, m->marioObj->header.gfx.cameraToObject);
                        reset_rumble_timers_2(m, 0);
                    }
                }
        }
    }

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
    set_character_animation(m, CHAR_ANIM_DIVE);

    return FALSE;
}

s32 act_tornado_twirling(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->usedObj == NULL) { return FALSE; }

    struct Surface *floor;
    Vec3f nextPos;
    f32 sinAngleVel;
    f32 cosAngleVel;
    f32 floorHeight;
    struct Object *marioObj = m->marioObj;
    struct Object *usedObj = m->usedObj;
    s16 prevTwirlYaw = m->twirlYaw;

    f32 dx = (m->pos[0] - usedObj->oPosX) * 0.95f;
    f32 dz = (m->pos[2] - usedObj->oPosZ) * 0.95f;

    if (m->vel[1] < 60.0f) {
        m->vel[1] += 1.0f;
    }

    if ((marioObj->oMarioTornadoPosY += m->vel[1]) < 0.0f) {
        marioObj->oMarioTornadoPosY = 0.0f;
    }
    if (marioObj->oMarioTornadoPosY > usedObj->hitboxHeight) {
        if (m->vel[1] < 20.0f) {
            m->vel[1] = 20.0f;
        }
        return set_mario_action(m, ACT_TWIRLING, 1);
    }

    if (m->angleVel[1] < 0x3000) {
        m->angleVel[1] += 0x100;
    }

    if (marioObj->oMarioTornadoYawVel < 0x1000) {
        marioObj->oMarioTornadoYawVel += 0x100;
    }

    m->twirlYaw += m->angleVel[1];

    sinAngleVel = sins(marioObj->oMarioTornadoYawVel);
    cosAngleVel = coss(marioObj->oMarioTornadoYawVel);

    nextPos[0] = usedObj->oPosX + dx * cosAngleVel + dz * sinAngleVel;
    nextPos[2] = usedObj->oPosZ - dx * sinAngleVel + dz * cosAngleVel;
    nextPos[1] = usedObj->oPosY + marioObj->oMarioTornadoPosY;

    f32_find_wall_collision(&nextPos[0], &nextPos[1], &nextPos[2], 60.0f, 50.0f);

    floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
    if (floor != NULL) {
        m->floor = floor;
        m->floorHeight = floorHeight;
        vec3f_copy(m->pos, nextPos);
    } else {
        if (nextPos[1] >= m->floorHeight) {
            m->pos[1] = nextPos[1];
        } else {
            m->pos[1] = m->floorHeight;
        }
    }

    m->actionTimer++;

    set_character_animation(m, (m->actionArg == 0) ? CHAR_ANIM_START_TWIRL : CHAR_ANIM_TWIRL);

    if (is_anim_past_end(m)) {
        m->actionArg = 1;
    }

    // Play sound on angle overflow
    if (prevTwirlYaw > m->twirlYaw) {
        play_sound(SOUND_ACTION_TWIRL, m->marioObj->header.gfx.cameraToObject);
    }

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1] + m->twirlYaw, 0);
    reset_rumble_timers(m);

    return FALSE;
}


static void bubbled_offset_visual(struct MarioState* m) {
    if (!m) { return; }
    // scary 3d trig ahead

    f32 forwardOffset = 25;
    f32 upOffset = -35;

    // figure out forward vector
    Vec3f forward = {
        sins(m->faceAngle[1]) * coss(m->faceAngle[0]),
        -sins(m->faceAngle[0]),
        coss(m->faceAngle[1]) * coss(m->faceAngle[0]),
    };
    vec3f_normalize(forward);

    // figure out right vector
    Vec3f globalUp = { 0, 1, 0 };
    Vec3f right = { 0 };
    vec3f_cross(right, forward, globalUp);
    vec3f_normalize(right);

    // figure out up vector
    Vec3f up = { 0 };
    vec3f_cross(up, right, forward);
    vec3f_normalize(up);

    // offset forward direction
    vec3f_mul(forward, forwardOffset);
    vec3f_add(m->marioObj->header.gfx.pos, forward);

    // offset up direction
    vec3f_mul(up, upOffset);
    vec3f_add(m->marioObj->header.gfx.pos, up);

    // offset global up direction
    m->marioObj->header.gfx.pos[1] -= upOffset;
}

static struct MarioState* nearest_antibubble_mario_state_to_object(struct Object *obj) {
    if (!obj) { return NULL; }
    struct MarioState* nearest = NULL;
    f32 nearestDist = 0;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct MarioState* m = &gMarioStates[i];
        if (!m->marioObj) { continue; }
        if (m->marioObj == obj) { continue; }
        if (!m->visibleToEnemies) { continue; }
        if (!is_player_active(m)) { continue; }

        switch (m->action) {
            case ACT_WATER_DEATH:
            case ACT_STANDING_DEATH:
            case ACT_QUICKSAND_DEATH:
            case ACT_DEATH_ON_STOMACH:
            case ACT_DEATH_ON_BACK:
                continue;
        }

        float dist = dist_between_objects(obj, m->marioObj);
        if (nearest == NULL || dist < nearestDist) {
            nearest = m;
            nearestDist = dist;
        }
    }

    return nearest;
}

s32 act_bubbled(struct MarioState* m) {
    if (!m) { return 0; }
    if (m->playerIndex == 0 && m->area->camera->mode == CAMERA_MODE_WATER_SURFACE) {
        set_camera_mode(m->area->camera, CAMERA_MODE_FREE_ROAM, 1);
    }
    struct MarioState* targetMarioState = nearest_antibubble_mario_state_to_object(m->marioObj);
    if (targetMarioState == NULL) {
        targetMarioState = &gMarioStates[0];
    }

    struct Object* target = targetMarioState->marioObj;
    s32 angleToPlayer = obj_angle_to_object(m->marioObj, target);
    s32 pitchToPlayer = obj_pitch_to_object(m->marioObj, target);
    s32 distanceToPlayer = dist_between_objects(m->marioObj, target);

    // trigger warp if all are bubbled
    if (m->playerIndex == 0) {
        u8 allInBubble = TRUE;
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (!is_player_active(&gMarioStates[i])) { continue; }
            if (!gMarioStates[i].visibleToEnemies) { continue; }
            if (gMarioStates[i].action != ACT_BUBBLED && gMarioStates[i].health >= 0x100) {
                allInBubble = FALSE;
                break;
            }
        }
        if (allInBubble) {
            level_trigger_warp(m, WARP_OP_DEATH);
            return set_mario_action(m, ACT_SOFT_BONK, 0);
        }
    }

    // create bubble
    if (m->bubbleObj == NULL && is_player_in_local_area(m)) {
        m->bubbleObj = spawn_object(m->marioObj, MODEL_BUBBLE_PLAYER, bhvBubblePlayer);
        if (m->bubbleObj != NULL) {
            m->bubbleObj->heldByPlayerIndex = m->playerIndex;
        }
    }

    // force inactive state
    if (m->heldObj != NULL) { mario_drop_held_object(m); }
    m->heldByObj = NULL;
    m->marioObj->oIntangibleTimer = -1;
    m->squishTimer = 0;
    m->bounceSquishTimer = 0;
    set_character_animation(m, CHAR_ANIM_SLEEP_IDLE);

    // force inputs
    f32 oldPitch = m->faceAngle[0];
    f32 oldYaw   = m->faceAngle[1];
    m->faceAngle[0] = 0;
    m->faceAngle[1] = m->intendedYaw;
    m->forwardVel = m->intendedMag * 1.6f;
    if (m->input & INPUT_A_DOWN) { m->vel[1] += 5.5f; }
    if (m->input & INPUT_Z_DOWN) { m->vel[1] -= 5.5f; }

    // set and smooth velocity
    Vec3f oldVel = { m->vel[0], m->vel[1], m->vel[2] };
    set_vel_from_pitch_and_yaw(m);
    for (s32 i = 0; i < 3; i++) {
        m->vel[i] = (oldVel[i] * 0.9f + m->vel[i] * 0.1f);
    }

    // enforce minimum y for the level
    u8 hasMinY = FALSE;
    f32 minY = 0;
    get_area_minimum_y(&hasMinY, &minY);
    if (hasMinY && m->pos[1] < minY) {
        m->vel[1] = MAX(0, m->vel[1]);
        m->pos[1] += 25;
    }

    // move player
    switch (perform_air_step(m, 0)) {
        case AIR_STEP_LANDED:
            m->vel[1] += 10.0f;
            break;

        case AIR_STEP_HIT_WALL:
        case AIR_STEP_HIT_LAVA_WALL:
            m->vel[0] *= -0.99f;
            m->vel[2] *= -0.99f;
            break;
    }

    // always look toward target
    m->faceAngle[0] = pitchToPlayer - approach_s32((s16)(pitchToPlayer - oldPitch), 0, 0x600, 0x600);
    m->faceAngle[1] = angleToPlayer - approach_s32((s16)(angleToPlayer - oldYaw  ), 0, 0x600, 0x600);
    m->marioObj->header.gfx.angle[0] = m->faceAngle[0];
    m->marioObj->header.gfx.angle[1] = m->faceAngle[1];

    // offset the player model to be in the center of the bubble
    bubbled_offset_visual(m);

    // make invisible on -1 lives
    if (m->playerIndex == 0) {
        if (m->numLives <= -1) {
            m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            level_trigger_warp(m, WARP_OP_DEATH);
            return set_mario_action(m, ACT_SOFT_BONK, 0);
        } else {
            m->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }

    if (gLocalBubbleCounter > 0) { gLocalBubbleCounter--; }

    // pop bubble
    if (m->playerIndex == 0 && distanceToPlayer < 120 && is_player_active(targetMarioState) && m->numLives != -1 && gLocalBubbleCounter == 0) {
        m->marioObj->activeFlags &= ~ACTIVE_FLAG_MOVE_THROUGH_GRATE;
        m->hurtCounter = 0;
        m->healCounter = 31;
        m->health = 0x100;
        m->marioObj->oIntangibleTimer = 0;
        m->peakHeight = m->pos[1];
        mario_set_forward_vel(m, 0.0f);
        m->vel[1] = 0.0f;
        m->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        m->invincTimer = 30 * 3;
        if (m->playerIndex == 0) {
            if (m->statusForCamera) { m->statusForCamera->action = m->action; }
            soft_reset_camera(m->area->camera);
        }
        u8 underWater = (m->pos[1] < ((f32)m->waterLevel));
        return set_mario_action(m, underWater ? ACT_WATER_IDLE : ACT_FREEFALL, 0);
    }

    return FALSE;
}

/* |description|
Checks if Mario should cancel his current automatic action, primarily by detecting if he falls into deep water. If so, transitions him to the water-plunge state
|descriptionEnd| */
s32 check_common_automatic_cancels(struct MarioState *m) {
    if (!m) { return 0; }
    if (m->pos[1] < m->waterLevel - 100) {
        return set_water_plunge_action(m);
    }

    return FALSE;
}

/* |description|
Executes Mario's current automatic action (e.g., climbing a pole, hanging, ledge-grabbing) by calling the corresponding function. It also checks for common cancellations, like falling into water.
Returns true if the action was canceled and a new action was set, or false otherwise
|descriptionEnd| */
s32 mario_execute_automatic_action(struct MarioState *m) {
    if (!m) { return 0; }
    if (!m) { return FALSE; }
    s32 cancel;

    if (check_common_automatic_cancels(m)) {
        return TRUE;
    }

    m->quicksandDepth = 0.0f;

    if (!smlua_call_action_hook(ACTION_HOOK_EVERY_FRAME, m, &cancel)) {
        /* clang-format off */
        switch (m->action) {
            case ACT_HOLDING_POLE:           cancel = act_holding_pole(m);           break;
            case ACT_GRAB_POLE_SLOW:         cancel = act_grab_pole_slow(m);         break;
            case ACT_GRAB_POLE_FAST:         cancel = act_grab_pole_fast(m);         break;
            case ACT_CLIMBING_POLE:          cancel = act_climbing_pole(m);          break;
            case ACT_TOP_OF_POLE_TRANSITION: cancel = act_top_of_pole_transition(m); break;
            case ACT_TOP_OF_POLE:            cancel = act_top_of_pole(m);            break;
            case ACT_START_HANGING:          cancel = act_start_hanging(m);          break;
            case ACT_HANGING:                cancel = act_hanging(m);                break;
            case ACT_HANG_MOVING:            cancel = act_hang_moving(m);            break;
            case ACT_LEDGE_GRAB:             cancel = act_ledge_grab(m);             break;
            case ACT_LEDGE_CLIMB_SLOW_1:     cancel = act_ledge_climb_slow(m);       break;
            case ACT_LEDGE_CLIMB_SLOW_2:     cancel = act_ledge_climb_slow(m);       break;
            case ACT_LEDGE_CLIMB_DOWN:       cancel = act_ledge_climb_down(m);       break;
            case ACT_LEDGE_CLIMB_FAST:       cancel = act_ledge_climb_fast(m);       break;
            case ACT_GRABBED:                cancel = act_grabbed(m);                break;
            case ACT_IN_CANNON:              cancel = act_in_cannon(m);              break;
            case ACT_TORNADO_TWIRLING:       cancel = act_tornado_twirling(m);       break;
            case ACT_BUBBLED:                cancel = act_bubbled(m);                break;
            default:
                LOG_ERROR("Attempted to execute unimplemented action '%04X'", m->action);
                set_mario_action(m, ACT_IDLE, 0);
                return false;
        }
        /* clang-format on */
    }

    return cancel;
}
