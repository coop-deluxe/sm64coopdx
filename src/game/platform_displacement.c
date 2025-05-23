#include <PR/ultratypes.h>

#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "level_update.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "platform_displacement.h"
#include "mario.h"
#include "types.h"

struct Object *gMarioPlatform = NULL;

/**
 * Determine if Mario is standing on a platform object, meaning that he is
 * within 4 units of the floor. Set his referenced platform object accordingly.
 */
void update_mario_platform(void) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct Surface *floor;
        UNUSED u32 unused;
        f32 marioX;
        f32 marioY;
        f32 marioZ;
        f32 floorHeight;
        u32 awayFromFloor;

        struct Object* player = gMarioStates[i].marioObj;

        if (player == NULL) {
            return;
        }

        //! If Mario moves onto a rotating platform in a PU, the find_floor call
        //  will detect the platform and he will end up receiving a large amount
        //  of displacement since he is considered to be far from the platform's
        //  axis of rotation.

        marioX = player->oPosX;
        marioY = player->oPosY;
        marioZ = player->oPosZ;
        floorHeight = find_floor(marioX, marioY, marioZ, &floor);

        if (absf(marioY - floorHeight) < 4.0f) {
            awayFromFloor = 0;
        } else {
            awayFromFloor = 1;
        }

        switch (awayFromFloor) {
            case 1:
                gMarioPlatform = NULL;
                player->platform = NULL;
                break;

            case 0:
                if (floor != NULL && floor->object != NULL) {
                    gMarioPlatform = floor->object;
                    player->platform = floor->object;
                } else {
                    gMarioPlatform = NULL;
                    player->platform = NULL;
                }
                break;
        }
    }
}

/**
 * Get Mario's position and store it in x, y, and z.
 */
void get_mario_pos(struct MarioState* m, f32 *x, f32 *y, f32 *z) {
    *x = m->pos[0];
    *y = m->pos[1];
    *z = m->pos[2];
}

/**
 * Set Mario's position.
 */
void set_mario_pos(struct MarioState* m, f32 x, f32 y, f32 z) {
    m->pos[0] = x;
    m->pos[1] = y;
    m->pos[2] = z;
}

/**
 * Apply one frame of platform rotation to an object using the given platform.
 * If the object is a Mario object, use the corresponding MarioState instead.
 */
void apply_platform_displacement(struct Object *o, struct Object *platform) {
    f32 x;
    f32 y;
    f32 z;
    f32 platformPosX;
    f32 platformPosY;
    f32 platformPosZ;
    Vec3f currentObjectOffset;
    Vec3f relativeOffset;
    Vec3f newObjectOffset;
    Vec3s rotation;
    f32 displaceMatrix[4][4];
    if (!o || !platform) { return; }

    rotation[0] = platform->oAngleVelPitch;
    rotation[1] = platform->oAngleVelYaw;
    rotation[2] = platform->oAngleVelRoll;

    struct MarioState *m = get_mario_state_from_object(o);
    if (m != NULL) {
        x = m->pos[0];
        y = m->pos[1];
        z = m->pos[2];
    } else {
        x = o->oPosX;
        y = o->oPosY;
        z = o->oPosZ;
    }

    x += platform->oVelX;
    z += platform->oVelZ;

    if (rotation[0] != 0 || rotation[1] != 0 || rotation[2] != 0) {
        if (m != NULL) {
            m->faceAngle[1] += rotation[1];
        }

        platformPosX = platform->oPosX;
        platformPosY = platform->oPosY;
        platformPosZ = platform->oPosZ;

        currentObjectOffset[0] = x - platformPosX;
        currentObjectOffset[1] = y - platformPosY;
        currentObjectOffset[2] = z - platformPosZ;

        rotation[0] = platform->oFaceAnglePitch - platform->oAngleVelPitch;
        rotation[1] = platform->oFaceAngleYaw - platform->oAngleVelYaw;
        rotation[2] = platform->oFaceAngleRoll - platform->oAngleVelRoll;

        mtxf_rotate_zxy_and_translate(displaceMatrix, currentObjectOffset, rotation);
        linear_mtxf_transpose_mul_vec3f(displaceMatrix, relativeOffset, currentObjectOffset);

        rotation[0] = platform->oFaceAnglePitch;
        rotation[1] = platform->oFaceAngleYaw;
        rotation[2] = platform->oFaceAngleRoll;

        mtxf_rotate_zxy_and_translate(displaceMatrix, currentObjectOffset, rotation);
        linear_mtxf_mul_vec3f(displaceMatrix, newObjectOffset, relativeOffset);

        x = platformPosX + newObjectOffset[0];
        y = platformPosY + newObjectOffset[1];
        z = platformPosZ + newObjectOffset[2];
    }

    if (m != NULL) {
        m->pos[0] = x;
        m->pos[1] = y;
        m->pos[2] = z;
    } else {
        o->oPosX = x;
        o->oPosY = y;
        o->oPosZ = z;
    }
}

/**
 * If Mario's platform is not null, apply platform displacement.
 */
void apply_mario_platform_displacement(void) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct Object* player = gMarioStates[i].marioObj;
        if (player == NULL) { continue; }

        struct Object *platform = player->platform;
        if (!(gTimeStopState & TIME_STOP_ACTIVE) && player != NULL && platform != NULL) {
            apply_platform_displacement(player, platform);
        }
    }
}

#ifndef VERSION_JP
/**
 * Set Mario's platform to NULL.
 */
void clear_mario_platform(void) {
    gMarioPlatform = NULL;
}
#endif
