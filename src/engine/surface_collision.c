#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/debug.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_collision.h"
#include "surface_load.h"
#include "math_util.h"
#include "game/game_init.h"
#include "game/hardcoded.h"
#include "pc/utils/misc.h"
#include "pc/network/network.h"

Vec3f gFindWallDirection = { 0 };
u8 gFindWallDirectionActive = false;
u8 gFindWallDirectionAirborne = false;

#define CLAMP(_val, _min, _max) MAX(MIN((_val), _max), _min)

void set_find_wall_direction(Vec3f dir, bool active, bool airborne) {
    if (active) {
        vec3f_copy(gFindWallDirection, dir);
    }
    gFindWallDirectionActive = active;
    gFindWallDirectionAirborne = airborne;
}

static void closest_point_to_triangle(struct Surface* surf, Vec3f src, Vec3f out) {
    Vec3f v1; vec3s_to_vec3f(v1, surf->vertex1);
    Vec3f v2; vec3s_to_vec3f(v2, surf->vertex2);
    Vec3f v3; vec3s_to_vec3f(v3, surf->vertex3);

    Vec3f edge0; vec3f_dif(edge0, v2, v1);
    Vec3f edge1; vec3f_dif(edge1, v3, v1);
    Vec3f v0;    vec3f_dif(v0,    v1, src);

    f32 a = vec3f_dot(edge0, edge0);
    f32 b = vec3f_dot(edge0, edge1);
    f32 c = vec3f_dot(edge1, edge1);
    f32 d = vec3f_dot(edge0, v0);
    f32 e = vec3f_dot(edge1, v0);

    f32 det = (a * c) - (b * b);
    f32 s   = (b * e) - (c * d);
    f32 t   = (b * d) - (a * e);

    if ((s + t) < det) {
        if (s < 0) {
            if (t < 0) {
                if (d < 0) {
                    s = CLAMP(-d/a, 0, 1);
                    t = 0;
                } else {
                    s = 0;
                    t = CLAMP(-e/c, 0, 1);
                }
            } else {
                s = 0;
                t = CLAMP(-e/c, 0, 1);
            }
        } else if (t < 0) {
            s = CLAMP(-d/a, 0, 1);
            t = 0;
        } else {
            f32 invDet = 1 / det;
            s *= invDet;
            t *= invDet;
        }
    } else {
        if (s < 0) {
            f32 tmp0 = (b + d);
            f32 tmp1 = (c + e);
            if (tmp1 > tmp0) {
                f32 numer = tmp1 - tmp0;
                f32 denom = a-2*b+c;
                s = CLAMP(numer/denom, 0, 1);
                t = (1 - s);
            } else {
                t = CLAMP(-e/c, 0, 1);
                s = 0;
            }
        } else if (t < 0.f) {
            if ((a + d) > (b + e)) {
                f32 numer = c+e-b-d;
                f32 denom = a-2*b+c;
                s = CLAMP(numer/denom, 0, 1);
                t = (1 - s);
            } else {
                s = CLAMP(-e/c, 0, 1);
                t = 0;
            }
        } else {
            f32 numer = c+e-b-d;
            f32 denom = a-2*b+c;
            s = CLAMP(numer/denom, 0, 1);
            t = 1 - s;
        }
    }

    out[0] = v1[0] + s * edge0[0] + t * edge1[0];
    out[1] = v1[1] + s * edge0[1] + t * edge1[1];
    out[2] = v1[2] + s * edge0[2] + t * edge1[2];
}

/**************************************************
 *                      WALLS                     *
 **************************************************/

/**
 * Iterate through the list of walls until all walls are checked and
 * have given their wall push.
 */
static s32 find_wall_collisions_from_list(struct SurfaceNode *surfaceNode,
                                          struct WallCollisionData *data) {
    register struct Surface *surf;
    register f32 offset = 0;
    register f32 radius = data->radius;
    register f32 x = data->x;
    register f32 y = data->y + data->offsetY;
    register f32 z = data->z;
    register f32 px, pz;
    register f32 w1, w2, w3;
    register f32 y1, y2, y3;
    s32 numCols = 0;

    Vec3f cPos = { 0 };
    Vec3f cNorm = { 0 };

    // Max collision radius = 200
    if (radius > 200.0f) {
        radius = 200.0f;
    }

    // Stay in this loop until out of walls.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        // Exclude a large number of walls immediately to optimize.
        if (y < surf->lowerY || y > surf->upperY) {
            continue;
        }

        if (gLevelValues.fixCollisionBugs && gLevelValues.fixCollisionBugsRoundedCorners && !gFindWallDirectionAirborne) {
            // Check AABB to exclude walls before doing expensive triangle check
            f32 minX = MIN(MIN(surf->vertex1[0], surf->vertex2[0]), surf->vertex3[0]) - radius;
            f32 minZ = MIN(MIN(surf->vertex1[2], surf->vertex2[2]), surf->vertex3[2]) - radius;
            f32 maxX = MAX(MAX(surf->vertex1[0], surf->vertex2[0]), surf->vertex3[0]) + radius;
            f32 maxZ = MAX(MAX(surf->vertex1[2], surf->vertex2[2]), surf->vertex3[2]) + radius;
            if (x < minX || x > maxX) { continue; }
            if (z < minZ || z > maxZ) { continue; }

            // Exclude triangles from wrong movement side
            Vec3f norm = { surf->normal.x, surf->normal.y, surf->normal.z };
            if (gFindWallDirectionActive) {
                if (vec3f_dot(norm, gFindWallDirection) > 0) {
                    continue;
                }
            }

            // Find closest point to triangle
            Vec3f src = { x, y, z };
            closest_point_to_triangle(surf, src, cPos);

            // Exclude triangles where y isn't inside of it
            if (fabs(cPos[1] - y) > 1) { continue; }

            // Figure out normal
            f32 dX = src[0] - cPos[0];
            f32 dZ = src[2] - cPos[2];
            f32 dist = sqrtf(dX * dX + dZ * dZ);
            if (dist > radius) { continue; }

            if (dist < __FLT_EPSILON__) {
                dist = __FLT_EPSILON__;
            }

            cNorm[0] = dX / dist;
            cNorm[1] = 0;
            cNorm[2] = dZ / dist;

            // Exclude triangles that are colliding from the wrong side
            if (!gFindWallDirectionActive && vec3f_dot(norm, cNorm) < 0) { continue; }

        } else {

            offset = surf->normal.x * x + surf->normal.y * y + surf->normal.z * z + surf->originOffset;

            if (offset < -radius || offset > radius) {
                continue;
            }

            px = x;
            pz = z;

            //! (Quantum Tunneling) Due to issues with the vertices walls choose and
            //  the fact they are floating point, certain floating point positions
            //  along the seam of two walls may collide with neither wall or both walls.
            if (surf->flags & SURFACE_FLAG_X_PROJECTION) {
                w1 = -surf->vertex1[2]; w2 = -surf->vertex2[2]; w3 = -surf->vertex3[2];
                y1 = surf->vertex1[1];  y2 = surf->vertex2[1];  y3 = surf->vertex3[1];

                if (surf->normal.x > 0.0f) {
                    if ((y1 - y) * (w2 - w1) - (w1 - -pz) * (y2 - y1) > 0.0f) {
                        continue;
                    }
                    if ((y2 - y) * (w3 - w2) - (w2 - -pz) * (y3 - y2) > 0.0f) {
                        continue;
                    }
                    if ((y3 - y) * (w1 - w3) - (w3 - -pz) * (y1 - y3) > 0.0f) {
                        continue;
                    }
                } else {
                    if ((y1 - y) * (w2 - w1) - (w1 - -pz) * (y2 - y1) < 0.0f) {
                        continue;
                    }
                    if ((y2 - y) * (w3 - w2) - (w2 - -pz) * (y3 - y2) < 0.0f) {
                        continue;
                    }
                    if ((y3 - y) * (w1 - w3) - (w3 - -pz) * (y1 - y3) < 0.0f) {
                        continue;
                    }
                }
            } else {
                w1 = surf->vertex1[0]; w2 = surf->vertex2[0]; w3 = surf->vertex3[0];
                y1 = surf->vertex1[1]; y2 = surf->vertex2[1]; y3 = surf->vertex3[1];

                if (surf->normal.z > 0.0f) {
                    if ((y1 - y) * (w2 - w1) - (w1 - px) * (y2 - y1) > 0.0f) {
                        continue;
                    }
                    if ((y2 - y) * (w3 - w2) - (w2 - px) * (y3 - y2) > 0.0f) {
                        continue;
                    }
                    if ((y3 - y) * (w1 - w3) - (w3 - px) * (y1 - y3) > 0.0f) {
                        continue;
                    }
                } else {
                    if ((y1 - y) * (w2 - w1) - (w1 - px) * (y2 - y1) < 0.0f) {
                        continue;
                    }
                    if ((y2 - y) * (w3 - w2) - (w2 - px) * (y3 - y2) < 0.0f) {
                        continue;
                    }
                    if ((y3 - y) * (w1 - w3) - (w3 - px) * (y1 - y3) < 0.0f) {
                        continue;
                    }
                }
            }
        }

        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) {
                continue;
            }
        } else {
            // Ignore camera only surfaces.
            if (surf->type == SURFACE_CAMERA_BOUNDARY || surf->type == SURFACE_RAYCAST) {
                continue;
            }

            // If an object can pass through a vanish cap wall, pass through.
            if (surf->type == SURFACE_VANISH_CAP_WALLS) {
                // If an object can pass through a vanish cap wall, pass through.
                if (gCurrentObject != NULL
                    && (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE)) {
                    continue;
                }

                // If Mario has a vanish cap, pass through the vanish cap wall.
                u8 passThroughWall = FALSE;
                for (s32 i = 0; i < MAX_PLAYERS; i++) {
                    if (gCurrentObject != NULL && gCurrentObject == gMarioStates[i].marioObj
                        && (gMarioStates[i].flags & MARIO_VANISH_CAP)) {
                        passThroughWall = TRUE;
                        break;
                    }
                }
                if (passThroughWall) { continue; }
            }
        }

        //! (Wall Overlaps) Because this doesn't update the x and z local variables,
        //  multiple walls can push mario more than is required.
        //  <Fixed when gLevelValues.fixCollisionBugs != 0>
        if (gLevelValues.fixCollisionBugs && gLevelValues.fixCollisionBugsRoundedCorners && !gFindWallDirectionAirborne) {
            data->x = cPos[0] + cNorm[0] * radius;
            data->z = cPos[2] + cNorm[2] * radius;
            x = data->x;
            z = data->z;
            data->normalAddition[0] += cNorm[0];
            data->normalAddition[2] += cNorm[2];
            data->normalCount++;
        } else {
            data->x += surf->normal.x * (radius - offset);
            data->z += surf->normal.z * (radius - offset);
        }

        //! (Unreferenced Walls) Since this only returns the first four walls,
        //  this can lead to wall interaction being missed. Typically unreferenced walls
        //  come from only using one wall, however.
        if (data->numWalls < 4) {
            data->walls[data->numWalls++] = surf;
        }

        numCols++;
    }

    return numCols;
}

/**
 * Formats the position and wall search for find_wall_collisions.
 */
s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius) {
    struct WallCollisionData collision;
    s32 numCollisions = 0;

    collision.offsetY = offsetY;
    collision.radius = radius;

    collision.x = *xPtr;
    collision.y = *yPtr;
    collision.z = *zPtr;

    collision.numWalls = 0;

    numCollisions = find_wall_collisions(&collision);

    *xPtr = collision.x;
    *yPtr = collision.y;
    *zPtr = collision.z;

    return numCollisions;
}

/**
 * Find wall collisions and receive their push.
 */
s32 find_wall_collisions(struct WallCollisionData *colData) {
    struct SurfaceNode *node;
    s16 cellX, cellZ;
    s32 numCollisions = 0;
    s16 x = colData->x;
    s16 z = colData->z;

    colData->numWalls = 0;

#if EXTENDED_BOUNDS_MODE != 3
    if (x <= -LEVEL_BOUNDARY_MAX || x >= LEVEL_BOUNDARY_MAX) {
        return numCollisions;
    }
    if (z <= -LEVEL_BOUNDARY_MAX || z >= LEVEL_BOUNDARY_MAX) {
        return numCollisions;
    }
#endif

    // World (level) consists of a 16x16 grid. Find where the collision is on
    // the grid (round toward -inf)
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;

    // Check for surfaces belonging to objects.
    node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);

    // Check for surfaces that are a part of level geometry.
    node = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);

    // Increment the debug tracker.
    gNumCalls.wall += 1;

    return numCollisions;
}

/**************************************************
 *                     CEILINGS                   *
 **************************************************/

/**
 * Iterate through the list of ceilings and find the first ceiling over a given point.
 */
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
    register struct Surface *surf;
    register s32 x1, z1, x2, z2, x3, z3;
    struct Surface *ceil = NULL;

    ceil = NULL;

    // set pheight to highest value
    if (gLevelValues.fixCollisionBugs) {
        *pheight = gLevelValues.cellHeightLimit;
    }

    // Stay in this loop until out of ceilings.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        x1 = surf->vertex1[0];
        z1 = surf->vertex1[2];
        z2 = surf->vertex2[2];
        x2 = surf->vertex2[0];

        // Checking if point is in bounds of the triangle laterally.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) > 0) {
            continue;
        }

        // Slight optimization by checking these later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];
        if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) > 0) {
            continue;
        }
        if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) > 0) {
            continue;
        }

        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera != 0) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) {
                continue;
            }
        }
        else {
            // Ignore camera only surfaces.
            if (surf->type == SURFACE_CAMERA_BOUNDARY || surf->type == SURFACE_RAYCAST) {
                continue;
            }

            // If an object can pass through a vanish cap surface, pass through.
            if (gLevelValues.fixVanishFloors && surf->type == SURFACE_VANISH_CAP_WALLS) {
                if (gCurrentObject != NULL
                    && (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE)) {
                    continue;
                }

                // If Mario has a vanish cap, pass through the vanish cap surface.
                u8 passThrough = FALSE;
                for (s32 i = 0; i < MAX_PLAYERS; i++) {
                    if (gCurrentObject != NULL && gCurrentObject == gMarioStates[i].marioObj
                        && (gMarioStates[i].flags & MARIO_VANISH_CAP)) {
                        passThrough = TRUE;
                        break;
                    }
                }
                if (passThrough) { continue; }
            }
        }

        {
            f32 nx = surf->normal.x;
            f32 ny = surf->normal.y;
            f32 nz = surf->normal.z;
            f32 oo = surf->originOffset;
            f32 height;

            // If a wall, ignore it. Likely a remnant, should never occur.
            if (ny == 0.0f) { continue; }

            // Find the ceil height at the specific point.
            height = -(x * nx + nz * z + oo) / ny;

            // Reject ceilings below previously found ceiling
            if (gLevelValues.fixCollisionBugs && (height > *pheight)) {
                continue;
            }

            // Checks for ceiling interaction with a 78 unit buffer.
            //! (Exposed Ceilings) Because any point above a ceiling counts
            //  as interacting with a ceiling, ceilings far below can cause
            // "invisible walls" that are really just exposed ceilings.
            //  <Fixed when gLevelValues.fixCollisionBugs != 0>
            if (y - (height - -78.0f) > 0.0f) {
                continue;
            }

            *pheight = height;
            ceil = surf;

            if (!gLevelValues.fixCollisionBugs) {
                break;
            }
        }
    }

    //! (Surface Cucking) Since only the first ceil is returned and not the lowest,
    //  lower ceilings can be "cucked" by higher ceilings.
    //  <Fixed when gLevelValues.fixCollisionBugs != 0>
    return ceil;
}

/**
 * Find the lowest ceiling above a given position and return the height.
 */
f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil) {
    s16 cellZ, cellX;
    struct Surface *ceil, *dynamicCeil;
    struct SurfaceNode *surfaceList;
    f32 height = gLevelValues.cellHeightLimit;
    f32 dynamicHeight = gLevelValues.cellHeightLimit;
    s16 x, y, z;

    //! (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return ceilings despite them not existing there.
    //(Dynamic ceilings will unload due to the range.)
    x = (s16) posX;
    y = (s16) posY;
    z = (s16) posZ;
    *pceil = NULL;

#if EXTENDED_BOUNDS_MODE != 3
    if (x <= -LEVEL_BOUNDARY_MAX || x >= LEVEL_BOUNDARY_MAX) {
        return height;
    }
    if (z <= -LEVEL_BOUNDARY_MAX || z >= LEVEL_BOUNDARY_MAX) {
        return height;
    }
#endif

    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;

    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, x, y, z, &dynamicHeight);

    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil = find_ceil_from_list(surfaceList, x, y, z, &height);

    if (dynamicHeight < height) {
        ceil = dynamicCeil;
        height = dynamicHeight;
    }

    *pceil = ceil;

    // Increment the debug tracker.
    gNumCalls.ceil += 1;

    return height;
}

f32 find_ceil_height(f32 x, f32 y, f32 z) {
    struct Surface *ceil;

    f32 ceilHeight = find_ceil(x, y, z, &ceil);

    return ceilHeight;
}

/**************************************************
 *                     FLOORS                     *
 **************************************************/

/**
 * Find the height of the highest floor below an object.
 */
f32 unused_obj_find_floor_height(struct Object *obj) {
    struct Surface *floor;
    f32 floorHeight = find_floor(obj->oPosX, obj->oPosY, obj->oPosZ, &floor);
    return floorHeight;
}

/**
 * Basically a local variable that passes through floor geo info.
 */
struct FloorGeometry sFloorGeo;

static u8 unused8038BE50[0x40];

/**
 * Return the floor height underneath (xPos, yPos, zPos) and populate `floorGeo`
 * with data about the floor's normal vector and origin offset. Also update
 * sFloorGeo.
 */
f32 find_floor_height_and_data(f32 xPos, f32 yPos, f32 zPos, struct FloorGeometry **floorGeo) {
    struct Surface *floor;
    f32 floorHeight = find_floor(xPos, yPos, zPos, &floor);

    *floorGeo = NULL;

    if (floor != NULL) {
        sFloorGeo.normalX = floor->normal.x;
        sFloorGeo.normalY = floor->normal.y;
        sFloorGeo.normalZ = floor->normal.z;
        sFloorGeo.originOffset = floor->originOffset;

        *floorGeo = &sFloorGeo;
    }
    return floorHeight;
}

extern f32 gRenderingDelta;
u8 gInterpolatingSurfaces;

/**
 * Iterate through the list of floors and find the first floor under a given point.
 */
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
    register struct Surface *surf;
    register f32 x1, z1, x2, z2, x3, z3;
    f32 nx, ny, nz;
    f32 oo;
    f32 height;
    struct Surface *floor = NULL;
    s32 interpolate;

    // set pheight to lowest value
    if (gLevelValues.fixCollisionBugs) {
        *pheight = gLevelValues.floorLowerLimit;
    }

    // Iterate through the list of floors until there are no more floors.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        if (surf == NULL) { break; }
        surfaceNode = surfaceNode->next;
        interpolate = gInterpolatingSurfaces;

        if (gCheckingSurfaceCollisionsForObject != NULL) {
            if (surf->object != gCheckingSurfaceCollisionsForObject) {
                continue;
            }
        }

        x1 = surf->vertex1[0];
        z1 = surf->vertex1[2];
        x2 = surf->vertex2[0];
        z2 = surf->vertex2[2];
        if (interpolate) {
            f32 diff = (surf->prevVertex1[0] - x1) * (surf->prevVertex1[0] - x1);
            diff += (surf->prevVertex1[1] - surf->vertex1[1]) * (surf->prevVertex1[1] - surf->vertex1[1]);
            diff += (surf->prevVertex1[2] - z1) * (surf->prevVertex1[2] - z1);
            //printf("%f\n", sqrtf(diff));
            if (diff > 10000) {
                interpolate = FALSE;
            } else {
                x1 = delta_interpolate_f32(surf->prevVertex1[0], x1, gRenderingDelta);
                z1 = delta_interpolate_f32(surf->prevVertex1[2], z1, gRenderingDelta);
                x2 = delta_interpolate_f32(surf->prevVertex2[0], x2, gRenderingDelta);
                z2 = delta_interpolate_f32(surf->prevVertex2[2], z2, gRenderingDelta);
            }
        }

        // Check that the point is within the triangle bounds.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) < 0) {
            continue;
        }

        // To slightly save on computation time, set this later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];
        if (interpolate) {
            x3 = delta_interpolate_f32(surf->prevVertex3[0], x3, gRenderingDelta);
            z3 = delta_interpolate_f32(surf->prevVertex3[2], z3, gRenderingDelta);
        }

        if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) < 0) {
            continue;
        }
        if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) < 0) {
            continue;
        }

        // Determine if we are checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera != 0) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) {
                continue;
            }
        }
        else {
            // If we are not checking for the camera, ignore camera only floors.
            if (surf->type == SURFACE_CAMERA_BOUNDARY || surf->type == SURFACE_RAYCAST) {
                continue;
            }

            // If an object can pass through a vanish cap surface, pass through.
            if (gLevelValues.fixVanishFloors && surf->type == SURFACE_VANISH_CAP_WALLS) {
                if (gCurrentObject != NULL
                    && (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE)) {
                    continue;
                }

                // If Mario has a vanish cap, pass through the vanish cap surface.
                u8 passThrough = FALSE;
                for (s32 i = 0; i < MAX_PLAYERS; i++) {
                    if (gCurrentObject != NULL && gCurrentObject == gMarioStates[i].marioObj
                        && (gMarioStates[i].flags & MARIO_VANISH_CAP)) {
                        passThrough = TRUE;
                        break;
                    }
                }
                if (passThrough) { continue; }
            }
        }

        if (interpolate) {
            f32 y1, y2, y3;
            f32 mag;
            y1 = delta_interpolate_f32(surf->prevVertex1[1], surf->vertex1[1], gRenderingDelta);
            y2 = delta_interpolate_f32(surf->prevVertex2[1], surf->vertex2[1], gRenderingDelta);
            y3 = delta_interpolate_f32(surf->prevVertex3[1], surf->vertex3[1], gRenderingDelta);
            nx = (y2 - y1) * (z3 - z2) - (z2 - z1) * (y3 - y2);
            ny = (z2 - z1) * (x3 - x2) - (x2 - x1) * (z3 - z2);
            nz = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
            mag = sqrtf(nx * nx + ny * ny + nz * nz);
            if (mag < 0.0001) {
                continue;
            }
            mag = (f32)(1.0 / mag);
            nx *= mag;
            ny *= mag;
            nz *= mag;
            oo = -(nx * x1 + ny * y1 + nz * z1);
        } else {
            nx = surf->normal.x;
            ny = surf->normal.y;
            nz = surf->normal.z;
            oo = surf->originOffset;
        }

        // If a wall, ignore it. Likely a remnant, should never occur.
        if (ny == 0.0f) {
            continue;
        }

        // Find the height of the floor at a given location.
        height = -(x * nx + nz * z + oo) / ny;

        // Find highest floor
        if (gLevelValues.fixCollisionBugs && (height < *pheight)) {
            continue;
        }

        // Checks for floor interaction with a 78 unit buffer.
        if (y - (height + -78.0f) < 0.0f) {
            continue;
        }

        if (pheight != NULL) {
            *pheight = height;
        }

        if (interpolate) {
            static struct Surface s;
            s.type = surf->type;
            s.normal.x = nx;
            s.normal.y = ny;
            s.normal.z = nz;
            s.originOffset = oo;
            return &s;
        }

        floor = surf;

        if (!gLevelValues.fixCollisionBugs) {
            break;
        }
    }

    //! (Surface Cucking) Since only the first floor is returned and not the highest,
    //  higher floors can be "cucked" by lower floors.
    //  <Fixed when gLevelValues.fixCollisionBugs != 0>
    return floor;
}

/**
 * Find the height of the highest floor below a point.
 */
f32 find_floor_height(f32 x, f32 y, f32 z) {
    struct Surface *floor;

    f32 floorHeight = find_floor(x, y, z, &floor);

    return floorHeight;
}

/**
 * Find the highest dynamic floor under a given position. Perhaps originally static
 * and dynamic floors were checked separately.
 */
f32 unused_find_dynamic_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    struct SurfaceNode *surfaceList;
    struct Surface *floor;
    f32 floorHeight = gLevelValues.floorLowerLimit;

    // Would normally cause PUs, but dynamic floors unload at that range.
    s16 x = (s16) xPos;
    s16 y = (s16) yPos;
    s16 z = (s16) zPos;

    // Each level is split into cells to limit load, find the appropriate cell.
    s16 cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    s16 cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;

    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor = find_floor_from_list(surfaceList, x, y, z, &floorHeight);

    *pfloor = floor;

    return floorHeight;
}

/**
 * Find the highest floor under a given position and return the height.
 */
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    s16 cellZ, cellX;

    struct Surface *floor, *dynamicFloor;
    struct SurfaceNode *surfaceList;

    f32 height = gLevelValues.floorLowerLimit;
    f32 dynamicHeight = gLevelValues.floorLowerLimit;

    //! (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return floors despite them not existing there.
    //(Dynamic floors will unload due to the range.)
    s16 x = (s16) xPos;
    s16 y = (s16) yPos;
    s16 z = (s16) zPos;

    *pfloor = NULL;

#if EXTENDED_BOUNDS_MODE != 3
    if (x <= -LEVEL_BOUNDARY_MAX || x >= LEVEL_BOUNDARY_MAX) {
        return height;
    }
    if (z <= -LEVEL_BOUNDARY_MAX || z >= LEVEL_BOUNDARY_MAX) {
        return height;
    }
#endif

    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;

    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    dynamicFloor = find_floor_from_list(surfaceList, x, y, z, &dynamicHeight);

    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor = find_floor_from_list(surfaceList, x, y, z, &height);

    // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
    // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
    // Mario to pass through.
    if (!gFindFloorIncludeSurfaceIntangible) {
        //! (BBH Crash) Most NULL checking is done by checking the height of the floor returned
        //  instead of checking directly for a NULL floor. If this check returns a NULL floor
        //  (happens when there is no floor under the SURFACE_INTANGIBLE floor) but returns the height
        //  of the SURFACE_INTANGIBLE floor instead of the typical -11000 returned for a NULL floor.
        if (floor != NULL && floor->type == SURFACE_INTANGIBLE) {
            floor = find_floor_from_list(surfaceList, x, (s32)(height - 200.0f), z, &height);
        }
    } else {
        // To prevent accidentally leaving the floor tangible, stop checking for it.
        gFindFloorIncludeSurfaceIntangible = FALSE;
    }

    // If a floor was missed, increment the debug counter.
    if (floor == NULL) {
        gNumFindFloorMisses += 1;
    }

    if (dynamicHeight > height) {
        floor = dynamicFloor;
        height = dynamicHeight;
    }

    *pfloor = floor;

    // Increment the debug tracker.
    gNumCalls.floor += 1;

    return height;
}

/**************************************************
 *               ENVIRONMENTAL BOXES              *
 **************************************************/

/**
 * Finds the height of water at a given location.
 */
f32 find_water_level(f32 x, f32 z) {
    s32 i;
    s32 numRegions;
    s16 val;
    f32 loX, hiX, loZ, hiZ;
    f32 waterLevel = gLevelValues.floorLowerLimit;
    if (!gEnvironmentRegions) { return waterLevel; }
    s16 *p = gEnvironmentRegions;

    if (p != NULL) {
        numRegions = *p++;

        for (i = 0; i < numRegions; i++) {
            val = *p++;
            loX = *p++;
            loZ = *p++;
            hiX = *p++;
            hiZ = *p++;

            // If the location is within a water box and it is a water box.
            // Water is less than 50 val only, while above is gas and such.
            if (loX < x && x < hiX && loZ < z && z < hiZ && val < 50) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    }

    return waterLevel;
}

/**
 * Finds the height of the poison gas (used only in HMC) at a given location.
 */
f32 find_poison_gas_level(f32 x, f32 z) {
    s32 i;
    s32 numRegions;
    UNUSED s32 unused;
    s16 val;
    f32 loX, hiX, loZ, hiZ;
    f32 gasLevel = gLevelValues.floorLowerLimit;
    if (!gEnvironmentRegions) { return gasLevel; }
    s16 *p = gEnvironmentRegions;

    if (p != NULL) {
        numRegions = *p++;

        for (i = 0; i < numRegions; i++) {
            val = *p;

            if (val >= 50) {
                loX = p[1];
                loZ = p[2];
                hiX = p[3];
                hiZ = p[4];

                // If the location is within a gas's box and it is a gas box.
                // Gas has a value of 50, 60, etc.
                if (loX < x && x < hiX && loZ < z && z < hiZ && val % 10 == 0) {
                    // Set the gas height. Since this breaks, only return the first height.
                    gasLevel = p[5];
                    break;
                }
            }

            p += 6;
        }
    }

    return gasLevel;
}

/**************************************************
 *                      DEBUG                     *
 **************************************************/

/**
 * Finds the length of a surface list for debug purposes.
 */
static s32 surface_list_length(struct SurfaceNode *list) {
    s32 count = 0;

    while (list != NULL) {
        list = list->next;
        count++;
    }

    return count;
}

/**
 * Print the area,number of walls, how many times they were called,
 * and some allocation information.
 */
void debug_surface_list_info(f32 xPos, f32 zPos) {
    struct SurfaceNode *list;
    s32 numFloors = 0;
    s32 numWalls = 0;
    s32 numCeils = 0;

    s32 cellX = (xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    s32 cellZ = (zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE;

    list = gStaticSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_FLOORS].next;
    numFloors += surface_list_length(list);

    list = gDynamicSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_FLOORS].next;
    numFloors += surface_list_length(list);

    list = gStaticSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_WALLS].next;
    numWalls += surface_list_length(list);

    list = gDynamicSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_WALLS].next;
    numWalls += surface_list_length(list);

    list = gStaticSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_CEILS].next;
    numCeils += surface_list_length(list);

    list = gDynamicSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_CEILS].next;
    numCeils += surface_list_length(list);

    print_debug_top_down_mapinfo("area   %x", cellZ * NUM_CELLS + cellX);

    // Names represent ground, walls, and roofs as found in SMS.
    print_debug_top_down_mapinfo("dg %d", numFloors);
    print_debug_top_down_mapinfo("dw %d", numWalls);
    print_debug_top_down_mapinfo("dr %d", numCeils);

    set_text_array_x_y(80, -3);

    print_debug_top_down_mapinfo("%d", gNumCalls.floor);
    print_debug_top_down_mapinfo("%d", gNumCalls.wall);
    print_debug_top_down_mapinfo("%d", gNumCalls.ceil);

    set_text_array_x_y(-80, 0);

    // listal- List Allocated?, statbg- Static Background?, movebg- Moving Background?
    print_debug_top_down_mapinfo("listal %d", gSurfaceNodesAllocated);
    print_debug_top_down_mapinfo("statbg %d", gNumStaticSurfaces);
    print_debug_top_down_mapinfo("movebg %d", gSurfacesAllocated - gNumStaticSurfaces);

    gNumCalls.floor = 0;
    gNumCalls.ceil = 0;
    gNumCalls.wall = 0;
}

/**
 * An unused function that finds and interacts with any type of surface.
 * Perhaps an original implementation of surfaces before they were more specialized.
 */
s32 unused_resolve_floor_or_ceil_collisions(s32 checkCeil, f32 *px, f32 *py, f32 *pz, f32 radius,
                                            struct Surface **psurface, f32 *surfaceHeight) {
    f32 nx, ny, nz, oo;
    f32 x = *px;
    f32 y = *py;
    f32 z = *pz;
    f32 offset, distance;

    *psurface = NULL;

    if (checkCeil) {
        *surfaceHeight = find_ceil(x, y, z, psurface);
    } else {
        *surfaceHeight = find_floor(x, y, z, psurface);
    }

    if (*psurface == NULL) {
        return -1;
    }

    nx = (*psurface)->normal.x;
    ny = (*psurface)->normal.y;
    nz = (*psurface)->normal.z;
    oo = (*psurface)->originOffset;

    offset = nx * x + ny * y + nz * z + oo;
    distance = offset >= 0 ? offset : -offset;

    // Interesting surface interaction that should be surf type independent.
    if (distance < radius) {
        *px += nx * (radius - offset);
        *py += ny * (radius - offset);
        *pz += nz * (radius - offset);

        return 1;
    }

    return 0;
}

/**
 * Raycast functions
 */
s32 ray_surface_intersect(Vec3f orig, Vec3f dir, f32 dir_length, struct Surface *surface, Vec3f hit_pos, f32 *length)
{
    Vec3f v0, v1, v2, e1, e2, h, s, q;
    f32 a, f, u, v;
    Vec3f add_dir;

    // Get surface normal and some other stuff
    vec3s_to_vec3f(v0, surface->vertex1);
    vec3s_to_vec3f(v1, surface->vertex2);
    vec3s_to_vec3f(v2, surface->vertex3);

    vec3f_dif(e1, v1, v0);
    vec3f_dif(e2, v2, v0);

    vec3f_cross(h, dir, e2);

    // Check if we're perpendicular from the surface
    a = vec3f_dot(e1, h);
    if (a > -0.00001f && a < 0.00001f)
        return FALSE;

    // Check if we're making contact with the surface
    f = 1.0f / a;

    vec3f_dif(s, orig, v0);
    u = f * vec3f_dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return FALSE;

    vec3f_cross(q, s, e1);
    v = f * vec3f_dot(dir, q);
    if (v < 0.0f || u + v > 1.0f)
        return FALSE;

    // Get the length between our origin and the surface contact point
    *length = f * vec3f_dot(e2, q);
    if (*length <= 0.00001 || *length > dir_length)
        return FALSE;

    // Successful contact
    vec3f_copy(add_dir, dir);
    vec3f_mul(add_dir, *length);
    vec3f_sum(hit_pos, orig, add_dir);
    return TRUE;
}

void find_surface_on_ray_list(struct SurfaceNode *list, Vec3f orig, Vec3f dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length)
{
    s32 hit;
    f32 length;
    Vec3f chk_hit_pos;
    f32 top, bottom;

    // Get upper and lower bounds of ray
    if (dir[1] >= 0.0f)
    {
        top = orig[1] + dir[1] * dir_length;
        bottom = orig[1];
    }
    else
    {
        top = orig[1];
        bottom = orig[1] + dir[1] * dir_length;
    }

    // Iterate through every surface of the list
    for (; list != NULL; list = list->next)
    {
        // Reject surface if out of vertical bounds
        if (list->surface->lowerY > top || list->surface->upperY < bottom)
            continue;

        // Reject no-cam collision surfaces
        if (gCheckingSurfaceCollisionsForCamera && (list->surface->flags & SURFACE_FLAG_NO_CAM_COLLISION))
            continue;

        // Check intersection between the ray and this surface
        if ((hit = ray_surface_intersect(orig, dir, dir_length, list->surface, chk_hit_pos, &length)) != 0)
        {
            if (length <= *max_length)
            {
                *hit_surface = list->surface;
                vec3f_copy(hit_pos, chk_hit_pos);
                *max_length = length;
            }
        }
    }
}


void find_surface_on_ray_cell(s16 cellX, s16 cellZ, Vec3f orig, Vec3f normalized_dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length)
{
    // Skip if OOB
    if (cellX >= 0 && cellX < NUM_CELLS && cellZ >= 0 && cellZ < NUM_CELLS)
    {
        // Iterate through each surface in this partition
        if (normalized_dir[1] > -0.99f)
        {
            find_surface_on_ray_list(gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
        if (normalized_dir[1] < 0.99f)
        {
            find_surface_on_ray_list(gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
        find_surface_on_ray_list(gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
    }
}

void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, f32 precision) {
    f32 max_length;
    s16 cellZ, cellX;
    f32 fCellZ, fCellX;
    f32 dir_length;
    Vec3f normalized_dir;
    f32 step, dx, dz;
    u32 i;

    // Set that no surface has been hit
    *hit_surface = NULL;
    vec3f_sum(hit_pos, orig, dir);

    // Get normalized direction
    dir_length = vec3f_length(dir);
    max_length = dir_length;
    vec3f_copy(normalized_dir, dir);
    vec3f_normalize(normalized_dir);

    // Get our cell coordinate
    fCellX = (orig[0] + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    fCellZ = (orig[2] + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    cellX = (s16)fCellX;
    cellZ = (s16)fCellZ;

    // Don't do DDA if straight down
    if (normalized_dir[1] >= 1.0f || normalized_dir[1] <= -1.0f)
    {
        find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length);
        return;
    }

    // Get cells we cross using DDA
    if (absx(dir[0]) >= absx(dir[2]))
        step = precision * absx(dir[0]) / CELL_SIZE;
    else
        step = precision * absx(dir[2]) / CELL_SIZE;

    dx = dir[0] / step / CELL_SIZE;
    dz = dir[2] / step / CELL_SIZE;

    for (i = 0; i < step && *hit_surface == NULL; i++)
    {
        find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length);

        // Move cell coordinate
        fCellX += dx;
        fCellZ += dz;
        cellX = (s16)fCellX;
        cellZ = (s16)fCellZ;
    }
}
