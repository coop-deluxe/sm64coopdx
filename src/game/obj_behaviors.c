#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "envfx_bubbles.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "level_update.h"
#include "levels/bob/header.h"
#include "levels/ttm/header.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_misc.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "hardcoded.h"
#include "engine/surface_load.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "pc/lua/utils/smlua_obj_utils.h"
#include "game/rng_position.h"
#include "rumble_init.h"

/**
 * @file obj_behaviors.c
 * This file contains a portion of the obj behaviors and many helper functions for those
 * specific behaviors. Few functions besides the bhv_ functions are used elsewhere in the repo.
 */

#define o gCurrentObject

#define OBJ_COL_FLAG_GROUNDED   (1 << 0)
#define OBJ_COL_FLAG_HIT_WALL   (1 << 1)
#define OBJ_COL_FLAG_UNDERWATER (1 << 2)
#define OBJ_COL_FLAG_NO_Y_VEL   (1 << 3)
#define OBJ_COL_FLAGS_LANDED    (OBJ_COL_FLAG_GROUNDED | OBJ_COL_FLAG_NO_Y_VEL)

/**
 * Current object floor as defined in object_step.
 */
static struct Surface *sObjFloor;

/**
 * Set to false when an object close to the floor should not be oriented in reference
 * to it. Happens with boulder, falling pillar, and the rolling snowman body.
 */
static s8 sOrientObjWithFloor = TRUE;

/**
 * Keeps track of Mario's previous non-zero room.
 * Helps keep track of room when Mario is over an object.
 */
s16 sPrevCheckMarioRoom = 0;

/**
 * Tracks whether or not Yoshi has walked/jumped off the roof.
 */
s8 sYoshiDead = FALSE;

/* |description|Resets Yoshi as being alive|descriptionEnd| */
void set_yoshi_as_not_dead(void) {
    sYoshiDead = FALSE;
}

/**
 * An unused geo function. Bears strong similarity to geo_bits_bowser_coloring, and relates something
 * of the opacity of an object to something else. Perhaps like, giving a parent object the same
 * opacity?
 */
Gfx UNUSED *geo_obj_transparency_something(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    Gfx *gfxHead;
    Gfx *gfx;
    struct Object *heldObject;
    struct Object *obj;
    UNUSED struct Object *unusedObject;
    UNUSED s32 pad;

    gfxHead = NULL;

    if (callContext == GEO_CONTEXT_RENDER) {
        heldObject = (struct Object *) gCurGraphNodeObject;
        obj = (struct Object *) node;
        unusedObject = (struct Object *) node;


        if (gCurGraphNodeHeldObject != NULL) {
            heldObject = gCurGraphNodeHeldObject->objNode;
        }

        gfxHead = alloc_display_list(3 * sizeof(Gfx));
        if (gfxHead == NULL) { return NULL; }
        gfx = gfxHead;
        if (obj != NULL) {
            obj->header.gfx.node.flags =
                (obj->header.gfx.node.flags & 0xFF) | (GRAPH_NODE_TYPE_FUNCTIONAL | GRAPH_NODE_TYPE_400);
        }

        if (heldObject != NULL) {
            gDPSetEnvColor(gfx++, 255, 255, 255, heldObject->oOpacity);
        }

        gSPEndDisplayList(gfx);
    }

    return gfxHead;
}

/* |description|An absolute value (always positive) function.|descriptionEnd| */
f32 absf_2(f32 f) {
    if (f < 0) {
        f *= -1.0f;
    }
    return f;
}

/**
 * Turns an object away from floors/walls that it runs into.
 */
void turn_obj_away_from_surface(f32 velX, f32 velZ, f32 nX, UNUSED f32 nY, f32 nZ, f32 *objYawX,
                            f32 *objYawZ) {
    if (!objYawX || !objYawZ) { return; }
    *objYawX = (nZ * nZ - nX * nX) * velX / (nX * nX + nZ * nZ)
               - 2 * velZ * (nX * nZ) / (nX * nX + nZ * nZ);
    if (isnan(*objYawX)) { *objYawX = 0; }

    *objYawZ = (nX * nX - nZ * nZ) * velZ / (nX * nX + nZ * nZ)
               - 2 * velX * (nX * nZ) / (nX * nX + nZ * nZ);
    if (isnan(*objYawZ)) { *objYawZ = 0; }
}

/* |description|Finds any wall collisions, applies them, and turns away from the surface.|descriptionEnd| */
s8 obj_find_wall(f32 objNewX, f32 objY, f32 objNewZ, f32 objVelX, f32 objVelZ) {
    if (!o) { return 0; }
    struct WallCollisionData hitbox = { 0 };
    f32 wall_nX, wall_nY, wall_nZ, objVelXCopy, objVelZCopy, objYawX, objYawZ;

    hitbox.x = objNewX;
    hitbox.y = objY;
    hitbox.z = objNewZ;
    hitbox.offsetY = o->hitboxHeight / 2;
    hitbox.radius = o->hitboxRadius;

    if (find_wall_collisions(&hitbox) != 0) {
        o->oPosX = hitbox.x;
        o->oPosY = hitbox.y;
        o->oPosZ = hitbox.z;

        if (gLevelValues.fixCollisionBugs && hitbox.normalCount > 0) {
            wall_nX = hitbox.normalAddition[0] / hitbox.normalCount;
            wall_nY = hitbox.normalAddition[1] / hitbox.normalCount;
            wall_nZ = hitbox.normalAddition[2] / hitbox.normalCount;
        } else {
            wall_nX = hitbox.walls[0]->normal.x;
            wall_nY = hitbox.walls[0]->normal.y;
            wall_nZ = hitbox.walls[0]->normal.z;
        }

        objVelXCopy = objVelX;
        objVelZCopy = objVelZ;

        // Turns away from the first wall only.
        turn_obj_away_from_surface(objVelXCopy, objVelZCopy, wall_nX, wall_nY, wall_nZ, &objYawX, &objYawZ);

        o->oMoveAngleYaw = atan2s(objYawZ, objYawX);
        return FALSE;
    }

    return TRUE;
}

/* |description|Turns an object away from steep floors, similarly to walls.|descriptionEnd| */
s8 turn_obj_away_from_steep_floor(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ) {
    if (!o) { return 0; }
    f32 floor_nX, floor_nY, floor_nZ, objVelXCopy, objVelZCopy, objYawX, objYawZ;

    if (objFloor == NULL) {
        //! (OOB Object Crash) TRUNC overflow exception after 36 minutes
        o->oMoveAngleYaw += 32767.999200000002; /* ¯\_(ツ)_/¯ */
        return FALSE;
    }

    floor_nX = objFloor->normal.x;
    floor_nY = objFloor->normal.y;
    floor_nZ = objFloor->normal.z;

    // If the floor is steep and we are below it (i.e. walking into it), turn away from the floor.
    if (floor_nY < 0.5 && floorY > o->oPosY) {
        objVelXCopy = objVelX;
        objVelZCopy = objVelZ;
        turn_obj_away_from_surface(objVelXCopy, objVelZCopy, floor_nX, floor_nY, floor_nZ, &objYawX,
                               &objYawZ);
        o->oMoveAngleYaw = atan2s(objYawZ, objYawX);
        return FALSE;
    }

    return TRUE;
}

/* |description|Orients an object with the given normals, typically the surface under the object.|descriptionEnd| */
void obj_orient_graph(struct Object *obj, f32 normalX, f32 normalY, f32 normalZ) {
    if (!obj) { return; }
    Vec3f objVisualPosition, surfaceNormals;

    Mat4 *throwMatrix;

    // Passes on orienting certain objects that shouldn't be oriented, like boulders.
    if (!sOrientObjWithFloor) {
        return;
    }

    // Passes on orienting billboard objects, i.e. coins, trees, etc.
    if ((obj->header.gfx.node.flags & GRAPH_RENDER_BILLBOARD) && !(obj->header.gfx.sharedChild && obj->header.gfx.sharedChild->extraFlags & GRAPH_EXTRA_FORCE_3D)) {
        return;
    }

    throwMatrix = alloc_display_list(sizeof(*throwMatrix));
    // If out of memory, fail to try orienting the object.
    if (throwMatrix == NULL) {
        return;
    }

    objVisualPosition[0] = obj->oPosX;
    objVisualPosition[1] = obj->oPosY + obj->oGraphYOffset;
    objVisualPosition[2] = obj->oPosZ;

    surfaceNormals[0] = normalX;
    surfaceNormals[1] = normalY;
    surfaceNormals[2] = normalZ;

    mtxf_align_terrain_normal(*throwMatrix, surfaceNormals, objVisualPosition, obj->oFaceAngleYaw);
    obj->header.gfx.throwMatrix = throwMatrix;
}

/**
 * Determines an object's forward speed multiplier.
 */
void calc_obj_friction(f32 *objFriction, f32 floor_nY) {
    if (!o) { return; }
    if (!objFriction) { return; }
    if (floor_nY < 0.2 && o->oFriction < 0.9999) {
        *objFriction = 0;
    } else {
        *objFriction = o->oFriction;
    }
}

/* |description|Updates an objects speed for gravity and updates Y position.|descriptionEnd| */
void calc_new_obj_vel_and_pos_y(struct Surface *objFloor, f32 objFloorY, f32 objVelX, f32 objVelZ) {
    if (!o) { return; }
    if (!objFloor) { return; }
    f32 floor_nX = objFloor->normal.x;
    f32 floor_nY = objFloor->normal.y;
    f32 floor_nZ = objFloor->normal.z;
    f32 objFriction;

    // Caps vertical speed with a "terminal velocity".
    o->oVelY -= o->oGravity;
    if (o->oVelY > 75.0) {
        o->oVelY = 75.0;
    }
    if (o->oVelY < -75.0) {
        o->oVelY = -75.0;
    }

    o->oPosY += o->oVelY;

    //Snap the object up to the floor.
    if (o->oPosY < objFloorY) {
        o->oPosY = objFloorY;

        // Bounces an object if the ground is hit fast enough.
        if (o->oVelY < -17.5) {
            o->oVelY = -(o->oVelY / 2);
        } else {
            o->oVelY = 0;
        }
    }

    //! (Obj Position Crash) If you got an object with height past 2^31, the game would crash.
    if ((s32) o->oPosY >= (s32) objFloorY && (s32) o->oPosY < (s32) objFloorY + 37) {
        obj_orient_graph(o, floor_nX, floor_nY, floor_nZ);

        // Adds horizontal component of gravity for horizontal speed.
        objVelX += floor_nX * (floor_nX * floor_nX + floor_nZ * floor_nZ)
                   / (floor_nX * floor_nX + floor_nY * floor_nY + floor_nZ * floor_nZ) * o->oGravity
                   * 2;
        objVelZ += floor_nZ * (floor_nX * floor_nX + floor_nZ * floor_nZ)
                   / (floor_nX * floor_nX + floor_nY * floor_nY + floor_nZ * floor_nZ) * o->oGravity
                   * 2;

        if (objVelX < 0.000001 && objVelX > -0.000001) {
            objVelX = 0;
        }
        if (objVelZ < 0.000001 && objVelZ > -0.000001) {
            objVelZ = 0;
        }

        if (objVelX != 0 || objVelZ != 0) {
            o->oMoveAngleYaw = atan2s(objVelZ, objVelX);
        }

        calc_obj_friction(&objFriction, floor_nY);
        o->oForwardVel = sqrtf(objVelX * objVelX + objVelZ * objVelZ) * objFriction;
    }
}

/* |description|Adjusts the current object's veloicty and y position for being underwater|descriptionEnd| */
void calc_new_obj_vel_and_pos_y_underwater(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ, f32 waterY) {
    if (!o) { return; }
    if (!objFloor) { return; }
    f32 floor_nX = objFloor->normal.x;
    f32 floor_nY = objFloor->normal.y;
    f32 floor_nZ = objFloor->normal.z;

    f32 netYAccel = (1.0f - o->oBuoyancy) * (-1.0f * o->oGravity);
    o->oVelY -= netYAccel;

    // Caps vertical speed with a "terminal velocity".
    if (o->oVelY > 75.0) {
        o->oVelY = 75.0;
    }
    if (o->oVelY < -75.0) {
        o->oVelY = -75.0;
    }

    o->oPosY += o->oVelY;

    //Snap the object up to the floor.
    if (o->oPosY < floorY) {
        o->oPosY = floorY;

        // Bounces an object if the ground is hit fast enough.
        if (o->oVelY < -17.5) {
            o->oVelY = -(o->oVelY / 2);
        } else {
            o->oVelY = 0;
        }
    }

    // If moving fast near the surface of the water, flip vertical speed? To emulate skipping?
    if (o->oForwardVel > 12.5 && (waterY + 30.0f) > o->oPosY && (waterY - 30.0f) < o->oPosY) {
        o->oVelY = -o->oVelY;
    }

    if ((s32) o->oPosY >= (s32) floorY && (s32) o->oPosY < (s32) floorY + 37) {
        obj_orient_graph(o, floor_nX, floor_nY, floor_nZ);

        // Adds horizontal component of gravity for horizontal speed.
        objVelX += floor_nX * (floor_nX * floor_nX + floor_nZ * floor_nZ)
                   / (floor_nX * floor_nX + floor_nY * floor_nY + floor_nZ * floor_nZ) * netYAccel * 2;
        objVelZ += floor_nZ * (floor_nX * floor_nX + floor_nZ * floor_nZ)
                   / (floor_nX * floor_nX + floor_nY * floor_nY + floor_nZ * floor_nZ) * netYAccel * 2;
    }

    if (objVelX < 0.000001 && objVelX > -0.000001) {
        objVelX = 0;
    }
    if (objVelZ < 0.000001 && objVelZ > -0.000001) {
        objVelZ = 0;
    }

    if (o->oVelY < 0.000001 && o->oVelY > -0.000001) {
        o->oVelY = 0;
    }

    if (objVelX != 0 || objVelZ != 0) {
        o->oMoveAngleYaw = atan2s(objVelZ, objVelX);
    }

    // Decreases both vertical velocity and forward velocity. Likely so that skips above
    // don't loop infinitely.
    o->oForwardVel = sqrtf(objVelX * objVelX + objVelZ * objVelZ) * 0.8;
    o->oVelY *= 0.8;
}

/* |description|Updates an objects position from oForwardVel and oMoveAngleYaw.|descriptionEnd| */
void obj_update_pos_vel_xz(void) {
    if (!o) { return; }
    f32 xVel = o->oForwardVel * sins(o->oMoveAngleYaw);
    f32 zVel = o->oForwardVel * coss(o->oMoveAngleYaw);

    o->oPosX += xVel;
    o->oPosZ += zVel;
}

/* |description|Generates splashes if at surface of water, entering water, or bubbles if underwater|descriptionEnd| */
void obj_splash(s32 waterY, s32 objY) {
    if (!o) { return; }
    u32 globalTimer = gGlobalTimer;

    // Spawns waves if near surface of water and plays a noise if entering.
    if ((f32)(waterY + 30) > o->oPosY && o->oPosY > (f32)(waterY - 30)) {
        spawn_object(o, MODEL_IDLE_WATER_WAVE, bhvObjectWaterWave);

        if (o->oVelY < -20.0f) {
            cur_obj_play_sound_2(SOUND_OBJ_DIVING_INTO_WATER);
        }
    }

    // Spawns bubbles if underwater.
    if ((objY + 50) < waterY && (globalTimer & 0x1F) == 0) {
        spawn_object(o, MODEL_WHITE_PARTICLE_SMALL, bhvObjectBubble);
    }
}

/* |description|
Generic object move function. Handles walls, water, floors, and gravity.
Returns flags for certain interactions
|descriptionEnd| */
s16 object_step(void) {
    if (!o) { return 0; }
    f32 objX = o->oPosX;
    f32 objY = o->oPosY;
    f32 objZ = o->oPosZ;

    f32 floorY;
    f32 waterY = gLevelValues.floorLowerLimitMisc;

    f32 objVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    f32 objVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);

    s16 collisionFlags = 0;

    // Find any wall collisions, receive the push, and set the flag.
    if (obj_find_wall(objX + objVelX, objY, objZ + objVelZ, objVelX, objVelZ) == 0) {
        collisionFlags += OBJ_COL_FLAG_HIT_WALL;
    }

    floorY = find_floor(objX + objVelX, objY, objZ + objVelZ, &sObjFloor);
    if (turn_obj_away_from_steep_floor(sObjFloor, floorY, objVelX, objVelZ) == 1) {
        waterY = find_water_level(objX + objVelX, objZ + objVelZ);
        if (waterY > objY) {
            calc_new_obj_vel_and_pos_y_underwater(sObjFloor, floorY, objVelX, objVelZ, waterY);
            collisionFlags += OBJ_COL_FLAG_UNDERWATER;
        } else {
            calc_new_obj_vel_and_pos_y(sObjFloor, floorY, objVelX, objVelZ);
        }
    } else {
        // Treat any awkward floors similar to a wall.
        collisionFlags +=
            ((collisionFlags & OBJ_COL_FLAG_HIT_WALL) ^ OBJ_COL_FLAG_HIT_WALL);
    }

    obj_update_pos_vel_xz();
    if ((s32) o->oPosY == (s32) floorY) {
        collisionFlags += OBJ_COL_FLAG_GROUNDED;
    }

    if ((s32) o->oVelY == 0) {
        collisionFlags += OBJ_COL_FLAG_NO_Y_VEL;
    }

    // Generate a splash if in water.
    obj_splash((s32) waterY, (s32) o->oPosY);
    return collisionFlags;
}

/* |description|
Takes an object step but does not orient with the object's floor.
Used for boulders, falling pillars, and the rolling snowman body
|descriptionEnd| */
s16 object_step_without_floor_orient(void) {
    s16 collisionFlags = 0;
    sOrientObjWithFloor = FALSE;
    collisionFlags = object_step();
    sOrientObjWithFloor = TRUE;

    return collisionFlags;
}

/* |description|
Don't use this function outside of of a context where the current object and `obj` are the same.
Moves `obj` based on a seemingly random mix of using either the current obj or `obj`'s fields
|descriptionEnd| */
void obj_move_xyz_using_fvel_and_yaw(struct Object *obj) {
    if (!o || !obj) { return; }
    o->oVelX = obj->oForwardVel * sins(obj->oMoveAngleYaw);
    o->oVelZ = obj->oForwardVel * coss(obj->oMoveAngleYaw);

    obj->oPosX += o->oVelX;
    obj->oPosY += obj->oVelY;
    obj->oPosZ += o->oVelZ;
}

/* |description|Checks if a point is within distance from any active Mario visible to enemies' graphical position|descriptionEnd| */
s8 is_point_within_radius_of_mario(f32 x, f32 y, f32 z, s32 dist) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (!gMarioStates[i].visibleToEnemies) { continue; }
        struct Object* player = gMarioStates[i].marioObj;
        if (!player) { continue; }
        f32 mGfxX = player->header.gfx.pos[0];
        f32 mGfxY = player->header.gfx.pos[1];
        f32 mGfxZ = player->header.gfx.pos[2];

        if ((x - mGfxX) * (x - mGfxX) + (y - mGfxY) * (y - mGfxY) + (z - mGfxZ) * (z - mGfxZ)
            < (f32)(dist * dist)) {
            return TRUE;
        }
    }

    return FALSE;
}

/* |description|Checks if a point is within distance from any active Mario's graphical position|descriptionEnd| */
s8 is_point_within_radius_of_any_player(f32 x, f32 y, f32 z, s32 dist) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        struct Object* player = gMarioStates[i].marioObj;
        if (!player) { continue; }
        f32 mGfxX = player->header.gfx.pos[0];
        f32 mGfxY = player->header.gfx.pos[1];
        f32 mGfxZ = player->header.gfx.pos[2];

        if ((x - mGfxX) * (x - mGfxX) + (y - mGfxY) * (y - mGfxY) + (z - mGfxZ) * (z - mGfxZ)
            < (f32)(dist * dist)) {
            return TRUE;
        }
    }

    return FALSE;
}

/* |description|Checks if `m` is in the current course/act/level/area and isn't bubbled|descriptionEnd| */
u8 is_player_active(struct MarioState* m) {
    if (!m) { return FALSE; }
    if (gNetworkType == NT_NONE && m == &gMarioStates[0]) { return TRUE; }
    if (m->action == ACT_BUBBLED) { return FALSE; }
    struct NetworkPlayer* np = &gNetworkPlayers[m->playerIndex];
    if (np == gNetworkPlayerServer && gServerSettings.headlessServer) { return FALSE; }
    if (np->type != NPT_LOCAL) {
        if (!np->connected) { return FALSE; }
        if (gNetworkPlayerLocal == NULL) { return FALSE; }
        bool levelAreaMismatch =
            (np->currCourseNum   != gNetworkPlayerLocal->currCourseNum
            || np->currActNum    != gNetworkPlayerLocal->currActNum
            || np->currLevelNum  != gNetworkPlayerLocal->currLevelNum
            || np->currAreaIndex != gNetworkPlayerLocal->currAreaIndex);
        if (levelAreaMismatch) { return FALSE; }
    }
    return TRUE;
}

/* |description|Checks if any player besides the local player is in the current course/act/level/area|descriptionEnd| */
u8 is_other_player_active(void) {
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        struct MarioState *m = &gMarioStates[i];
        if (is_player_active(m)) { return TRUE; }
    }
    return FALSE;
}

/* |description|Checks if `m` is in the current course/act/level/area|descriptionEnd| */
u8 is_player_in_local_area(struct MarioState* m) {
    if (!m) { return FALSE; }
    if (gNetworkType == NT_NONE && m == &gMarioStates[0]) { return TRUE; }
    struct NetworkPlayer* np = &gNetworkPlayers[m->playerIndex];
    if (np == gNetworkPlayerServer && gServerSettings.headlessServer) { return FALSE; }
    if (np->type != NPT_LOCAL) {
        if (!np->connected) { return FALSE; }
        if (gNetworkPlayerLocal == NULL) { return FALSE; }
        bool levelAreaMismatch =
            (np->currCourseNum   != gNetworkPlayerLocal->currCourseNum
            || np->currActNum    != gNetworkPlayerLocal->currActNum
            || np->currLevelNum  != gNetworkPlayerLocal->currLevelNum
            || np->currAreaIndex != gNetworkPlayerLocal->currAreaIndex);
        if (levelAreaMismatch) { return FALSE; }
    }
    return TRUE;
}

/* |description|Gets the nearest active Mario who isn't bubbled to `obj`|descriptionEnd| */
struct MarioState* nearest_mario_state_to_object(struct Object *obj) {
    if (!obj) { return NULL; }
    struct MarioState* nearest = NULL;
    f32 nearestDist = 0;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gMarioStates[i].marioObj) { continue; }
        if (gMarioStates[i].marioObj == obj) { continue; }
        if (!gMarioStates[i].visibleToEnemies) { continue; }
        if (!is_player_active(&gMarioStates[i])) { continue; }
        float dist = dist_between_objects(obj, gMarioStates[i].marioObj);
        if (nearest == NULL || dist < nearestDist) {
            nearest = &gMarioStates[i];
            nearestDist = dist;
        }
    }

    return nearest;
}

/* |description|Gets the nearest possible Mario to `obj` despite anything like bubbled state or enemy visibility|descriptionEnd| */
struct MarioState* nearest_possible_mario_state_to_object(struct Object *obj) {
    if (!obj) { return NULL; }
    struct MarioState* nearest = NULL;
    f32 nearestDist = 0;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gMarioStates[i].marioObj) { continue; }
        if (gMarioStates[i].marioObj == obj) { continue; }
        if (!is_player_active(&gMarioStates[i])) { continue; }
        float dist = dist_between_objects(obj, gMarioStates[i].marioObj);
        if (nearest == NULL || dist < nearestDist) {
            nearest = &gMarioStates[i];
            nearestDist = dist;
        }
    }

    return nearest;
}

/* |description|Gets the nearest player (Mario Object) to `obj`|descriptionEnd| */
struct Object* nearest_player_to_object(struct Object *obj) {
    if (!obj) { return NULL; }
    struct MarioState* nearest = nearest_mario_state_to_object(obj);
    if (nearest == NULL) { return NULL; }
    return nearest->marioObj;
}

/* |description|Gets the nearest interacting Mario to `obj`|descriptionEnd| */
struct MarioState *nearest_interacting_mario_state_to_object(struct Object *obj) {
    if (!obj) { return NULL; }
    struct MarioState *nearest = NULL;
    f32 nearestDist = 0;

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gMarioStates[i].marioObj) { continue; }
        if (gMarioStates[i].marioObj == obj) { continue; }
        if (gMarioStates[i].interactObj != obj) { continue; }
        if (!gMarioStates[i].visibleToEnemies) { continue; }
        if (!is_player_active(&gMarioStates[i])) { continue; }
        float dist = dist_between_objects(obj, gMarioStates[i].marioObj);
        if (nearest == NULL || dist < nearestDist) {
            nearest = &gMarioStates[i];
            nearestDist = dist;
        }
    }

    if (nearest == NULL) {
        nearest = &gMarioStates[0];
    }

    return nearest;
}

/* |description|Gets the nearest interacting player (Mario Object) to `obj`|descriptionEnd| */
struct Object *nearest_interacting_player_to_object(struct Object *obj) {
    if (!obj) { return NULL; }
    struct MarioState *nearest = nearest_interacting_mario_state_to_object(obj);
    if (!nearest) { return NULL; }
    return nearest->marioObj;
}

/* |description|Checks if `m` is the nearest Mario to `obj`|descriptionEnd| */
u8 is_nearest_mario_state_to_object(struct MarioState *m, struct Object *obj) {
    if (m == NULL || obj == NULL) { return FALSE; }
    struct MarioState *nearest = nearest_mario_state_to_object(obj);
    return m == nearest;
}

/* |description|Checks if `m` is the nearest player (Mario Object) to `obj` |descriptionEnd| */
u8 is_nearest_player_to_object(struct Object *m, struct Object *obj) {
    if (m == NULL || obj == NULL) { return FALSE; }
    struct MarioState *nearest = nearest_mario_state_to_object(obj);
    if (!nearest) { return FALSE; }
    return m == nearest->marioObj;
}

/* |description|Checks if a point is within `dist` of `obj`|descriptionEnd|*/
s8 is_point_close_to_object(struct Object *obj, f32 x, f32 y, f32 z, s32 dist) {
    if (!obj) { return FALSE; }
    f32 objX = obj->oPosX;
    f32 objY = obj->oPosY;
    f32 objZ = obj->oPosZ;

    if ((x - objX) * (x - objX) + (y - objY) * (y - objY) + (z - objZ) * (z - objZ)
        < (f32)(dist * dist)) {
        return TRUE;
    }

    return FALSE;
}

/* |description|Sets an object as visible if within a certain distance of Mario's graphical position|descriptionEnd| */
void set_object_visibility(struct Object *obj, s32 dist) {
    if (!obj) { return; }
    s32 distanceToPlayer = dist_between_objects(obj, gMarioStates[0].marioObj);
    if (distanceToPlayer < dist * draw_distance_scalar()) {
        obj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    } else {
        obj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }
}

/* |description|Turns an object towards home if Mario is not near to it|descriptionEnd| */
s8 obj_return_home_if_safe(struct Object *obj, f32 homeX, f32 y, f32 homeZ, s32 dist) {
    if (!obj) { return FALSE; }
    f32 homeDistX = homeX - obj->oPosX;
    f32 homeDistZ = homeZ - obj->oPosZ;
    s16 angleTowardsHome = atan2s(homeDistZ, homeDistX);

    if (is_point_within_radius_of_mario(homeX, y, homeZ, dist) == TRUE) {
        return TRUE;
    } else {
        obj->oMoveAngleYaw = approach_s16_symmetric(obj->oMoveAngleYaw, angleTowardsHome, 320);
    }

    return FALSE;
}

/* |description|Randomly displaces an objects home if RNG says to, and turns the object towards its home|descriptionEnd| */
void obj_return_and_displace_home(struct Object *obj, f32 homeX, UNUSED f32 homeY, f32 homeZ, s32 baseDisp) {
    if (!obj) { return; }
    s16 angleToNewHome;
    f32 homeDistX, homeDistZ;

    if ((s32)(random_float() * 50.0f) == 0) {
        obj->oHomeX = (f32)(baseDisp * 2) * random_float() - (f32) baseDisp + homeX;
        obj->oHomeZ = (f32)(baseDisp * 2) * random_float() - (f32) baseDisp + homeZ;
    }

    homeDistX = obj->oHomeX - obj->oPosX;
    homeDistZ = obj->oHomeZ - obj->oPosZ;
    angleToNewHome = atan2s(homeDistZ, homeDistX);
    obj->oMoveAngleYaw = approach_s16_symmetric(obj->oMoveAngleYaw, angleToNewHome, 320);
}

/* |description|
A series of checks using sin and cos to see if a given angle is facing in the same direction
of a given angle, within a certain range
|descriptionEnd|*/
s8 obj_check_if_facing_toward_angle(u32 base, u32 goal, s16 range) {
    s16 dAngle = (u16) goal - (u16) base;

    if (((f32) sins(-range) < (f32) sins(dAngle)) && ((f32) sins(dAngle) < (f32) sins(range))
        && (coss(dAngle) > 0)) {
        return TRUE;
    }

    return FALSE;
}

/* |description|Finds any wall collisions and returns what the displacement vector would be.|descriptionEnd| */
s8 obj_find_wall_displacement(Vec3f dist, f32 x, f32 y, f32 z, f32 radius) {
    struct WallCollisionData hitbox;
    UNUSED u8 filler[0x20];

    hitbox.x = x;
    hitbox.y = y;
    hitbox.z = z;
    hitbox.offsetY = 10.0f;
    hitbox.radius = radius;

    if (find_wall_collisions(&hitbox) != 0) {
        dist[0] = hitbox.x - x;
        dist[1] = hitbox.y - y;
        dist[2] = hitbox.z - z;
        return TRUE;
    } else {
        return FALSE;
    }
}

/* |description|
Spawns a number of coins at the location of an object with a random forward velocity, y velocity, and direction
|descriptionEnd| */
void obj_spawn_yellow_coins(struct Object *obj, s8 nCoins) {
    if (!o) { return; }
    if (!obj) { return; }
    struct Object *coin;
    s8 count;

    rng_position_init(o->oPosX, o->oPosY, o->oPosZ);
    for (count = 0; count < nCoins; count++) {
        coin = spawn_object(obj, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
        if (coin != NULL) {
            coin->oForwardVel = random_float() * 20;
            coin->oVelY = random_float() * 40 + 20;
            coin->oMoveAngleYaw = random_u16();
        }
    }
    rng_position_finish();
}

/* |description|Controls whether certain objects should flicker/when to despawn|descriptionEnd| */
s8 obj_flicker_and_disappear(struct Object *obj, s16 lifeSpan) {
    if (!obj) { return FALSE; }
    if (obj->oTimer < lifeSpan) {
        return FALSE;
    }

    if (obj->oTimer < lifeSpan + 40) {
        if (obj->oTimer % 2 != 0) {
            obj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        } else {
            obj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    } else {
        obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return TRUE;
    }

    return FALSE;
}

/* |description|Checks if a given room is Mario's current room, even if on an object|descriptionEnd| */
s8 current_mario_room_check(s16 room) {
    s16 result;

    // Since object surfaces have room 0, this tests if the surface is an
    // object first and uses the last room if so.
    if (gMarioCurrentRoom == 0) {
        if (room == sPrevCheckMarioRoom) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        if (room == gMarioCurrentRoom) {
            result = TRUE;
        } else {
            result = FALSE;
        }

        sPrevCheckMarioRoom = gMarioCurrentRoom;
    }

    return result;
}

/**
 * Triggers dialog when Mario is facing an object and controls it while in the dialog.
 */
s16 trigger_obj_dialog_when_facing(struct MarioState* m, s32 *inDialog, s16 dialogID, f32 dist, s32 actionArg, u8 (*inContinueDialogFunction)(void)) {
    if (!o) { return 0; }
    if (!m || !inDialog) { return 0; }
    s16 dialogueResponse;

    s32 angleToPlayer = obj_angle_to_object(o, m->marioObj);

    if ((is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, (s32) dist) == TRUE
         && obj_check_if_facing_toward_angle(o->oFaceAngleYaw, m->marioObj->header.gfx.angle[1] + 0x8000, 0x1000) == TRUE
         && obj_check_if_facing_toward_angle(o->oMoveAngleYaw, angleToPlayer, 0x1000) == TRUE)
        || (*inDialog == 1)) {
        *inDialog = 1;

        if (set_mario_npc_dialog(m, actionArg, inContinueDialogFunction) == 2) { //If Mario is speaking.
            dialogueResponse = cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogID);
            if (dialogueResponse != 0) {
                set_mario_npc_dialog(m, 0, NULL);
                *inDialog = 0;
                return dialogueResponse;
            }
            return 0;
        }
    }

    return 0;
}

/* |description|
Checks if `floor`'s type is burning or death plane and if so change the
current object's action accordingly
|descriptionEnd| */
void obj_check_floor_death(s16 collisionFlags, struct Surface *floor) {
    if (!o) { return; }
    if (floor == NULL) { return; }

    if ((collisionFlags & OBJ_COL_FLAG_GROUNDED) == OBJ_COL_FLAG_GROUNDED) {
        switch (floor->type) {
            case SURFACE_BURNING:
                o->oAction = OBJ_ACT_LAVA_DEATH;
                break;
            //! @BUG Doesn't check for the vertical wind death floor.
            case SURFACE_DEATH_PLANE:
                o->oAction = OBJ_ACT_DEATH_PLANE_DEATH;
                break;
            default:
                break;
        }
    }
}

/* |description|
Controls an object dying in lava by creating smoke, sinking the object, playing
audio, and eventually despawning it. Returns TRUE when the obj is dead
|descriptionEnd| */
s8 obj_lava_death(void) {
    if (!o) { return 0; }
    struct Object *deathSmoke;

    if (o->oTimer >= 31) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return TRUE;
    } else {
        // Sinking effect
        o->oPosY -= 10.0f;
    }

    if ((o->oTimer % 8) == 0) {
        cur_obj_play_sound_2(SOUND_OBJ_BULLY_EXPLODE_2);
        deathSmoke = spawn_object(o, MODEL_SMOKE, bhvBobombBullyDeathSmoke);
        if (deathSmoke != NULL) {
            deathSmoke->oPosX += random_float() * 20.0f;
            deathSmoke->oPosY += random_float() * 20.0f;
            deathSmoke->oPosZ += random_float() * 20.0f;
            deathSmoke->oForwardVel = random_float() * 10.0f;
        }
    }

    return FALSE;
}

/* |description|Spawns an orange number object relatively, such as those that count up for secrets.|descriptionEnd| */
void spawn_orange_number(s8 behParam, s16 relX, s16 relY, s16 relZ) {
    struct Object *orangeNumber;
    orangeNumber = spawn_object_relative(behParam, relX, relY, relZ, o, MODEL_NUMBER, bhvOrangeNumber);
    if (orangeNumber == NULL) { return; }
    orangeNumber->oPosY += 25.0f;
}

/**
 * Unused variables for debug_sequence_tracker.
 */
s8 sDebugSequenceTracker = 0;
s8 sDebugTimer = 0;

/**
 * Unused presumably debug function that tracks for a sequence of inputs.
 */
s8 UNUSED debug_sequence_tracker(s16 debugInputSequence[]) {
    // If end of sequence reached, return true.
    if (debugInputSequence[sDebugSequenceTracker] == 0) {
        sDebugSequenceTracker = 0;
        return TRUE;
    }

    // If the third controller button pressed is next in sequence, reset timer and progress to next value.
    if (debugInputSequence[sDebugSequenceTracker] & gPlayer1Controller->buttonPressed) {
        sDebugSequenceTracker++;
        sDebugTimer = 0;
    // If wrong input or timer reaches 10, reset sequence progress.
    } else if (sDebugTimer == 10 || gPlayer1Controller->buttonPressed != 0) {
        sDebugSequenceTracker = 0;
        sDebugTimer = 0;
        return FALSE;
    }
    sDebugTimer++;

    return FALSE;
}

// We need the spawn_star file first so the spawn_star functions can be accessed by below behaviors.
#include "behaviors/spawn_star.inc.c"
#include "behaviors/moving_coin.inc.c"
#include "behaviors/seaweed.inc.c"
#include "behaviors/bobomb.inc.c"
#include "behaviors/cannon_door.inc.c"
#include "behaviors/whirlpool.inc.c"
#include "behaviors/amp.inc.c"
#include "behaviors/butterfly.inc.c"
#include "behaviors/hoot.inc.c"
#include "behaviors/beta_holdable_object.inc.c"
#include "behaviors/bubble.inc.c"
#include "behaviors/water_wave.inc.c"
#include "behaviors/explosion.inc.c"
#include "behaviors/corkbox.inc.c"
#include "behaviors/bully.inc.c"
#include "behaviors/water_ring.inc.c"
#include "behaviors/bowser_bomb.inc.c"
#include "behaviors/celebration_star.inc.c"
#include "behaviors/drawbridge.inc.c"
#include "behaviors/bomp.inc.c"
#include "behaviors/sliding_platform.inc.c"
#include "behaviors/moneybag.inc.c"
#include "behaviors/bowling_ball.inc.c"
#include "behaviors/cruiser.inc.c"
#include "behaviors/spindel.inc.c"
#include "behaviors/pyramid_wall.inc.c"
#include "behaviors/pyramid_elevator.inc.c"
#include "behaviors/pyramid_top.inc.c"
#include "behaviors/sound_waterfall.inc.c"
#include "behaviors/sound_volcano.inc.c"
#include "behaviors/castle_flag.inc.c"
#include "behaviors/sound_birds.inc.c"
#include "behaviors/sound_ambient.inc.c"
#include "behaviors/sound_sand.inc.c"
#include "behaviors/castle_cannon_grate.inc.c"
#include "behaviors/snowman.inc.c"
#include "behaviors/boulder.inc.c"
#include "behaviors/cap.inc.c"
#include "behaviors/red_coin.inc.c"
#include "behaviors/hidden_star.inc.c"
#include "behaviors/rolling_log.inc.c"
#include "behaviors/mushroom_1up.inc.c"
#include "behaviors/controllable_platform.inc.c"
#include "behaviors/breakable_box_small.inc.c"
#include "behaviors/snow_mound.inc.c"
#include "behaviors/floating_platform.inc.c"
#include "behaviors/arrow_lift.inc.c"
#include "behaviors/orange_number.inc.c"
#include "behaviors/manta_ray.inc.c"
#include "behaviors/falling_pillar.inc.c"
#include "behaviors/floating_box.inc.c"
#include "behaviors/decorative_pendulum.inc.c"
#include "behaviors/treasure_chest.inc.c"
#include "behaviors/mips.inc.c"
#include "behaviors/yoshi.inc.c"
