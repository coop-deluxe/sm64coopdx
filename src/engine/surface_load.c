#include <PR/ultratypes.h>

#include "prevent_bss_reordering.h"

#include "sm64.h"
#include "game/ingame_menu.h"
#include "graph_node.h"
#include "behavior_script.h"
#include "behavior_data.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/macro_special_objects.h"
#include "surface_collision.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_load.h"
#include "game/game_init.h"
#include "engine/math_util.h"
#include "game/level_update.h"
#include "game/hardcoded.h"
#include "pc/network/network.h"
#include "pc/lua/smlua_hooks.h"

/**
 * Partitions for course and object surfaces. The arrays represent
 * the 16x16 cells that each level is split into.
 */
SpatialPartitionCell gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];

/**
 * Pools of data to contain either surface nodes or surfaces.
 */
static struct GrowingArray *sSurfaceNodePool = NULL;
static struct GrowingArray *sSurfacePool = NULL;

/**
 * Allocate the part of the surface node pool to contain a surface node.
 */
static struct SurfaceNode *alloc_surface_node(void) {
    sSurfaceNodePool->count = gSurfaceNodesAllocated++;
    return growing_array_alloc(sSurfaceNodePool, sizeof(struct SurfaceNode));
}

/**
 * Allocate the part of the surface pool to contain a surface and
 * initialize the surface.
 */
static struct Surface *alloc_surface(void) {
    sSurfacePool->count = gSurfacesAllocated++;
    return growing_array_alloc(sSurfacePool, sizeof(struct Surface));
}

/**
 * Iterates through the entire partition, clearing the surfaces.
 */
static void clear_spatial_partition(SpatialPartitionCell *cells) {
    register s32 i = NUM_CELLS * NUM_CELLS;

    while (i--) {
        (*cells)[SPATIAL_PARTITION_FLOORS].next = NULL;
        (*cells)[SPATIAL_PARTITION_CEILS].next = NULL;
        (*cells)[SPATIAL_PARTITION_WALLS].next = NULL;

        cells++;
    }
}

/**
 * Clears the static (level) surface partitions for new use.
 */
static void clear_static_surfaces(void) {
    clear_spatial_partition(&gStaticSurfacePartition[0][0]);
}

/**
 * Add a surface to the correct cell list of surfaces.
 * @param dynamic Determines whether the surface is static or dynamic
 * @param cellX The X position of the cell in which the surface resides
 * @param cellZ The Z position of the cell in which the surface resides
 * @param surface The surface to add
 */
static void add_surface_to_cell(s16 dynamic, s16 cellX, s16 cellZ, struct Surface *surface) {
    struct SurfaceNode *newNode = alloc_surface_node();
    if (newNode == NULL) { return; }
    struct SurfaceNode *list;
    s16 surfacePriority;
    s16 priority;
    s16 sortDir;
    s16 listIndex;

    if (surface->normal.y > 0.01) {
        listIndex = SPATIAL_PARTITION_FLOORS;
        sortDir = 1; // highest to lowest, then insertion order
    } else if (surface->normal.y < -0.01) {
        listIndex = SPATIAL_PARTITION_CEILS;
        sortDir = -1; // lowest to highest, then insertion order
    } else {
        listIndex = SPATIAL_PARTITION_WALLS;
        sortDir = 0; // insertion order

        if (surface->normal.x < -0.707 || surface->normal.x > 0.707) {
            surface->flags |= SURFACE_FLAG_X_PROJECTION;
        }
    }

    //! (Surface Cucking) Surfaces are sorted by the height of their first
    //  vertex. Since vertices aren't ordered by height, this causes many
    //  lower triangles to be sorted higher. This worsens surface cucking since
    //  many functions only use the first triangle in surface order that fits,
    //  missing higher surfaces.
    //  upperY would be a better sort method.
    //  <Fixed when gLevelValues.fixCollisionBugs != 0>

    surfacePriority = gLevelValues.fixCollisionBugs
                    ? (surface->upperY * sortDir)
                    : (surface->vertex1[1] * sortDir);

    newNode->surface = surface;

    if (dynamic) {
        list = &gDynamicSurfacePartition[cellZ][cellX][listIndex];
    } else {
        list = &gStaticSurfacePartition[cellZ][cellX][listIndex];
    }

    // Loop until we find the appropriate place for the surface in the list.
    while (list->next != NULL) {
        priority = list->next->surface->vertex1[1] * sortDir;

        if (surfacePriority > priority) {
            break;
        }

        list = list->next;
    }

    newNode->next = list->next;
    list->next = newNode;
}

/**
 * Returns the lowest of three values.
 */

#define min_3(a0, a1, a2) MIN(MIN(a0, a1), a2)

/**
 * Returns the highest of three values.
 */

#define max_3(a0, a1, a2) MAX(MAX(a0, a1), a2)

/**
 * Every level is split into 16 * 16 cells of surfaces (to limit computing
 * time). This function determines the lower cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s16 lower_cell_index(s32 coord) {
    s16 index;

    // Move from range [-0x2000, 0x2000) to [0, 0x4000)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) {
        coord = 0;
    }

    // [0, 16)
    index = coord / CELL_SIZE;

    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE < 50) {
        index -= 1;
    }

    if (index < 0) {
        index = 0;
    }

    // Potentially > 15, but since the upper index is <= 15, not exploitable
    return index;
}

/**
 * Every level is split into 16 * 16 cells of surfaces (to limit computing
 * time). This function determines the upper cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s16 upper_cell_index(s32 coord) {
    s16 index;

    // Move from range [-0x2000, 0x2000) to [0, 0x4000)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) {
        coord = 0;
    }

    // [0, 16)
    index = coord / CELL_SIZE;

    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE > CELL_SIZE - 50) {
        index += 1;
    }

    if (index > NUM_CELLS_INDEX) {
        index = NUM_CELLS_INDEX;
    }

    // Potentially < 0, but since lower index is >= 0, not exploitable
    return index;
}

/**
 * Every level is split into 16x16 cells, this takes a surface, finds
 * the appropriate cells (with a buffer), and adds the surface to those
 * cells.
 * @param surface The surface to check
 * @param dynamic Boolean determining whether the surface is static or dynamic
 */
static void add_surface(struct Surface *surface, s32 dynamic) {
    // minY/maxY maybe? s32 instead of s16, though.
    s16 minX, minZ, maxX, maxZ;

    s16 minCellX, minCellZ, maxCellX, maxCellZ;

    s16 cellZ, cellX;

    minX = min_3(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0]);
    minZ = min_3(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2]);
    maxX = max_3(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0]);
    maxZ = max_3(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2]);

    minCellX = lower_cell_index(minX);
    maxCellX = upper_cell_index(maxX);
    minCellZ = lower_cell_index(minZ);
    maxCellZ = upper_cell_index(maxZ);

    for (cellZ = minCellZ; cellZ <= maxCellZ; cellZ++) {
        for (cellX = minCellX; cellX <= maxCellX; cellX++) {
            add_surface_to_cell(dynamic, cellX, cellZ, surface);
        }
    }
}

/**
 * Initializes a Surface struct using the given vertex data
 * @param vertexData The raw data containing vertex positions
 * @param vertexIndices Helper which tells positions in vertexData to start reading vertices
 */
static struct Surface *read_surface_data(s16 *vertexData, s16 **vertexIndices) {
    if (vertexData == NULL || vertexIndices == NULL || *vertexIndices == NULL) { return NULL; }

    struct Surface *surface;
    register s32 x1, y1, z1;
    register s32 x2, y2, z2;
    register s32 x3, y3, z3;
    s32 maxY, minY;
    f32 nx, ny, nz;
    f32 mag;
    s32 offset1, offset2, offset3;

    offset1 = 3 * (*vertexIndices)[0];
    offset2 = 3 * (*vertexIndices)[1];
    offset3 = 3 * (*vertexIndices)[2];

    x1 = *(vertexData + offset1 + 0);
    y1 = *(vertexData + offset1 + 1);
    z1 = *(vertexData + offset1 + 2);

    x2 = *(vertexData + offset2 + 0);
    y2 = *(vertexData + offset2 + 1);
    z2 = *(vertexData + offset2 + 2);

    x3 = *(vertexData + offset3 + 0);
    y3 = *(vertexData + offset3 + 1);
    z3 = *(vertexData + offset3 + 2);

    // (v2 - v1) x (v3 - v2)
    nx = (y2 - y1) * (z3 - z2) - (z2 - z1) * (y3 - y2);
    ny = (z2 - z1) * (x3 - x2) - (x2 - x1) * (z3 - z2);
    nz = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    mag = sqrtf(nx * nx + ny * ny + nz * nz);

    // Could have used min_3 and max_3 for this...
    minY = y1;
    if (y2 < minY) {
        minY = y2;
    }
    if (y3 < minY) {
        minY = y3;
    }

    maxY = y1;
    if (y2 > maxY) {
        maxY = y2;
    }
    if (y3 > maxY) {
        maxY = y3;
    }

    // Checking to make sure no DIV/0
    if (mag < 0.0001) {
        return NULL;
    }
    mag = (f32)(1.0 / mag);
    nx *= mag;
    ny *= mag;
    nz *= mag;

    surface = alloc_surface();
    if (surface == NULL) { return NULL; }

    vec3s_copy(surface->prevVertex1, surface->vertex1);
    vec3s_copy(surface->prevVertex2, surface->vertex2);
    vec3s_copy(surface->prevVertex3, surface->vertex3);
    surface->modifiedTimestamp = gGlobalTimer;

    surface->vertex1[0] = x1;
    surface->vertex2[0] = x2;
    surface->vertex3[0] = x3;

    surface->vertex1[1] = y1;
    surface->vertex2[1] = y2;
    surface->vertex3[1] = y3;

    surface->vertex1[2] = z1;
    surface->vertex2[2] = z2;
    surface->vertex3[2] = z3;

    surface->normal.x = nx;
    surface->normal.y = ny;
    surface->normal.z = nz;

    surface->originOffset = -(nx * x1 + ny * y1 + nz * z1);

    surface->lowerY = minY - 5;
    surface->upperY = maxY + 5;

    return surface;
}

/**
 * Returns whether a surface has exertion/moves Mario
 * based on the surface type.
 */
bool surface_has_force(s16 surfaceType) {
    return surfaceType == SURFACE_0004 ||
           surfaceType == SURFACE_FLOWING_WATER ||
           surfaceType == SURFACE_HORIZONTAL_WIND ||
           surfaceType == SURFACE_MOVING_QUICKSAND ||
           surfaceType == SURFACE_DEEP_MOVING_QUICKSAND ||
           surfaceType == SURFACE_SHALLOW_MOVING_QUICKSAND ||
           surfaceType == SURFACE_INSTANT_MOVING_QUICKSAND;
}

/**
 * Returns whether a surface should have the
 * SURFACE_FLAG_NO_CAM_COLLISION flag.
 */
static bool surf_has_no_cam_collision(s16 surfaceType) {
    return surfaceType == SURFACE_RAYCAST ||
           surfaceType == SURFACE_NO_CAM_COLLISION ||
           surfaceType == SURFACE_NO_CAM_COLLISION_77 ||
           surfaceType == SURFACE_NO_CAM_COL_VERY_SLIPPERY ||
           surfaceType == SURFACE_VANISH_CAP_WALLS ||
           surfaceType == SURFACE_SWITCH;
}

/**
 * Load in the surfaces for a given surface type. This includes setting the flags,
 * exertion, and room.
 */
static void load_static_surfaces(s16 **data, s16 *vertexData, s16 surfaceType, s8 **surfaceRooms) {
    s32 numSurfaces;
    struct Surface *surface;
    s8 room = 0;
    bool hasForce = surface_has_force(surfaceType);
    s8 flags = surf_has_no_cam_collision(surfaceType) ? SURFACE_FLAG_NO_CAM_COLLISION : 0;

    numSurfaces = *(*data);
    *data += 1;

    for (s32 i = 0; i < numSurfaces; i++) {
        if (*surfaceRooms != NULL) {
            room = *(*surfaceRooms);
            *surfaceRooms += 1;
        }

        surface = read_surface_data(vertexData, data);
        if (surface != NULL) {
            surface->room = room;
            surface->type = surfaceType;
            surface->flags = flags;

            if (hasForce) {
                surface->force = *(*data + 3);
            } else {
                surface->force = 0;
            }

            add_surface(surface, FALSE);
        }

        *data += 3;
        if (hasForce) {
            *data += 1;
        }
    }
}

/**
 * Read the data for vertices for reference by triangles.
 */
static s16 *read_vertex_data(s16 **data) {
    s32 numVertices;
    s16 *vertexData;

    numVertices = *(*data);
    (*data)++;

    vertexData = *data;
    *data += 3 * numVertices;

    return vertexData;
}

/**
 * Loads in special environmental regions, such as water, poison gas, and JRB fog.
 */
static void load_environmental_regions(s16 **data) {
    s32 numRegions;

    gEnvironmentRegionsLength = 0;
    gEnvironmentRegions = *data;
    numRegions = *(*data)++;
    gEnvironmentRegionsLength++;

    if (numRegions > 20) {
        numRegions = 20;
    }

    for (s32 i = 0; i < numRegions; i++) {
        UNUSED s16 val, loX, loZ, hiX, hiZ;
        s16 height;

        val = *(*data)++;

        loX = *(*data)++;
        hiX = *(*data)++;
        loZ = *(*data)++;
        hiZ = *(*data)++;

        height = *(*data)++;

        gEnvironmentRegionsLength += 6;
        gEnvironmentLevels[i] = height;
    }
}

/**
 * Allocate some of the main pool for surfaces (2300 surf) and for surface nodes (7000 nodes).
 */
void alloc_surface_pools(void) {
    clear_static_surfaces();
    clear_dynamic_surfaces();

    sSurfaceNodePool = growing_array_init(sSurfaceNodePool, 0x1000);
    sSurfacePool = growing_array_init(sSurfacePool, 0x400);

    gEnvironmentRegions = NULL;
    gSurfaceNodesAllocated = 0;
    gSurfacesAllocated = 0;
    gNumStaticSurfaceNodes = 0;
    gNumStaticSurfaces = 0;

    gCCMEnteredSlide = 0;
    reset_red_coins_collected();
}

/**
 * Get the size of the terrain data, to get the correct size when copying later.
 */
u32 get_area_terrain_size(s16 *terrainData) {
    s16 *startPos = terrainData;
    s32 end = FALSE;
    s16 terrainLoadType;
    s32 numVertices;
    s32 numRegions;
    s32 numSurfaces;
    s16 hasForce;
    while (!end) {
        terrainLoadType = *terrainData++;

        switch (terrainLoadType) {
            case TERRAIN_LOAD_VERTICES:
                numVertices = *terrainData++;
                terrainData += 3 * numVertices;
                break;

            case TERRAIN_LOAD_OBJECTS:
                terrainData += get_special_objects_size(terrainData);
                break;

            case TERRAIN_LOAD_ENVIRONMENT:
                numRegions = *terrainData++;
                terrainData += 6 * numRegions;
                break;

            case TERRAIN_LOAD_CONTINUE:
                continue;

            case TERRAIN_LOAD_END:
                end = TRUE;
                break;

            default:
                numSurfaces = *terrainData++;
                hasForce = surface_has_force(terrainLoadType);
                terrainData += (3 + hasForce) * numSurfaces;
                break;
        }
    }

    return terrainData - startPos;
}


/**
 * Process the level file, loading in vertices, surfaces, some objects, and environmental
 * boxes (water, gas, JRB fog).
 */
void load_area_terrain(s16 index, s16 *data, s8 *surfaceRooms, s16 *macroObjects) {
    s16 terrainLoadType = 0;
    s16 *vertexData = NULL;

    // Initialize the data for this.
    gEnvironmentRegions = NULL;
    gSurfaceNodesAllocated = 0;
    gSurfacesAllocated = 0;

    clear_static_surfaces();

    // A while loop iterating through each section of the level data. Sections of data
    // are prefixed by a terrain "type." This type is reused for surfaces as the surface
    // type.
    while (TRUE) {
        terrainLoadType = *data;
        data++;

        if (TERRAIN_LOAD_IS_SURFACE_TYPE_LOW(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
        } else if (terrainLoadType == TERRAIN_LOAD_VERTICES) {
            vertexData = read_vertex_data(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_OBJECTS) {
            spawn_special_objects(index, &data);
        } else if (terrainLoadType == TERRAIN_LOAD_ENVIRONMENT) {
            load_environmental_regions(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_CONTINUE) {
            continue;
        } else if (terrainLoadType == TERRAIN_LOAD_END) {
            break;
        } else if (TERRAIN_LOAD_IS_SURFACE_TYPE_HIGH(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
            continue;
        }
    }

    if (macroObjects != NULL && *macroObjects != -1) {
        // If the first macro object presetID is within the range [0, 29].
        // Generally an early spawning method, every object is in BBH (the first level).
        if (0 <= *macroObjects && *macroObjects < 30) {
            spawn_macro_objects_hardcoded(index, macroObjects);
        }
        // A more general version that can spawn more objects.
        else {
            spawn_macro_objects(index, macroObjects);
        }
    }

    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces = gSurfacesAllocated;
}

/**
 * If not in time stop, clear the surface partitions.
 */
void clear_dynamic_surfaces(void) {
    if (!(gTimeStopState & TIME_STOP_ACTIVE)) {
        gSurfacesAllocated = gNumStaticSurfaces;
        gSurfaceNodesAllocated = gNumStaticSurfaceNodes;

        clear_spatial_partition(&gDynamicSurfacePartition[0][0]);

        for (u16 i = 0; i < OBJECT_POOL_CAPACITY; i++) {
            struct Object *obj = &gObjectPool[i];
            obj->firstSurface = 0;
            obj->numSurfaces = 0;
        }
    }
}

/**
 * Applies an object's transformation to the object's vertices.
 */
void transform_object_vertices(s16 **data, s16 *vertexData) {
    if (!gCurrentObject) { return; }
    register s16 *vertices;
    register f32 vx, vy, vz;
    register s32 numVertices;

    Mat4 *objectTransform;
    Mat4 m;

    objectTransform = &gCurrentObject->transform;

    numVertices = *(*data);
    (*data)++;

    vertices = *data;

    if (gCurrentObject->header.gfx.throwMatrix == NULL) {
        gCurrentObject->header.gfx.throwMatrix = objectTransform;
        obj_build_transform_from_pos_and_angle(gCurrentObject, O_POS_INDEX, O_FACE_ANGLE_INDEX);
    }

    obj_apply_scale_to_matrix(gCurrentObject, m, *objectTransform);

    // Go through all vertices, rotating and translating them to transform the object.
    while (numVertices--) {
        vx = *(vertices++);
        vy = *(vertices++);
        vz = *(vertices++);

        //! No bounds check on vertex data
        *vertexData++ = (s16)(vx * m[0][0] + vy * m[1][0] + vz * m[2][0] + m[3][0]);
        *vertexData++ = (s16)(vx * m[0][1] + vy * m[1][1] + vz * m[2][1] + m[3][1]);
        *vertexData++ = (s16)(vx * m[0][2] + vy * m[1][2] + vz * m[2][2] + m[3][2]);
    }

    *data = vertices;
}

/**
 * Load in the surfaces for the gCurrentObject. This includes setting the flags, exertion, and room.
 */
void load_object_surfaces(s16** data, s16* vertexData) {
    if (!gCurrentObject) { return; }
    s32 surfaceType;
    s32 i;
    s32 numSurfaces;
    s16 hasForce;
    s16 flags;
    s16 room;

    surfaceType = *(*data);
    (*data)++;

    numSurfaces = *(*data);
    (*data)++;

    hasForce = surface_has_force(surfaceType);

    flags = surf_has_no_cam_collision(surfaceType) ? SURFACE_FLAG_NO_CAM_COLLISION : 0;
    flags |= SURFACE_FLAG_DYNAMIC;

    // The DDD warp is initially loaded at the origin and moved to the proper
    // position in paintings.c and doesn't update its room, so set it here.
    if (gCurrentObject->behavior == segmented_to_virtual(smlua_override_behavior(bhvDddWarp))) {
        room = 5;
    } else {
        room = 0;
    }

    for (i = 0; i < numSurfaces; i++) {
        struct Surface* surface = read_surface_data(vertexData, data);

        if (surface != NULL) {

            // Set index of first surface
            if (gCurrentObject->firstSurface == 0) {
                gCurrentObject->firstSurface = gSurfacesAllocated - 1;
            }

            // Increase surface count
            gCurrentObject->numSurfaces++;

            surface->object = gCurrentObject;
            surface->type = surfaceType;

            if (hasForce) {
                surface->force = *(*data + 3);
            } else {
                surface->force = 0;
            }

            surface->flags |= flags;
            surface->room = (s8)room;
            add_surface(surface, TRUE);
        }

        if (hasForce) {
            *data += 4;
        } else {
            *data += 3;
        }
    }
}

/**
 * Transform an object's vertices, reload them, and render the object.
 */
void load_object_collision_model(void) {
    if (!gCurrentObject) { return; }
    if (gCurrentObject->collisionData == NULL) { return; }

    s32 numVertices = 64;
    if (gCurrentObject->collisionData[0] == COL_INIT()) {
        numVertices = gCurrentObject->collisionData[1];
    }
    if (numVertices <= 0) {
        LOG_ERROR("Object collisions had invalid vertex count");
        return;
    }
    if (numVertices >= 4096) {
        LOG_ERROR("Object collisions had too many vertices");
        return;
    }

    static s32 sVertexDataCount = 0;
    static s16* sVertexData = NULL;

    // allocate vertex data
    if (numVertices > sVertexDataCount || sVertexData == NULL) {
        if (sVertexData) { free(sVertexData); }
        sVertexDataCount = numVertices;
        if (sVertexDataCount < 64) { sVertexDataCount = 64; }
        sVertexData = malloc((3 * sVertexDataCount + 1) * sizeof(s16));
        LOG_INFO("Reallocating object vertex data: %u", sVertexDataCount);
    }

    s16* collisionData = gCurrentObject->collisionData;
    f32 tangibleDist = gCurrentObject->oCollisionDistance;

    u8 anyPlayerInTangibleRange = FALSE;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        f32 dist = dist_between_objects(gCurrentObject, gMarioStates[i].marioObj);
        if (dist < tangibleDist) { anyPlayerInTangibleRange = TRUE; }
    }

    // If the object collision is supposed to be loaded more than the
    // drawing distance of 4000, extend the drawing range.
    if (gCurrentObject->oCollisionDistance > 4000.0f) {
        gCurrentObject->oDrawingDistance = gCurrentObject->oCollisionDistance;
    }

    // Update if no Time Stop, in range, and in the current room.
    if (!(gTimeStopState & TIME_STOP_ACTIVE)
        && (anyPlayerInTangibleRange)
        && !(gCurrentObject->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        collisionData++;
        transform_object_vertices(&collisionData, sVertexData);

        // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
        while (*collisionData != TERRAIN_LOAD_CONTINUE) {
            load_object_surfaces(&collisionData, sVertexData);
        }
    }

    f32 marioDist = dist_between_objects(gCurrentObject, gMarioStates[0].marioObj);
    if (marioDist < gCurrentObject->oDrawingDistance * draw_distance_scalar()) {
        gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
    } else {
        gCurrentObject->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    }
}

struct Surface *obj_get_surface_from_index(struct Object *o, u32 index) {
    if (!o || o->firstSurface == 0) { return NULL; }
    if (index >= o->numSurfaces) { return NULL; }
    struct Surface *surf = sSurfacePool->buffer[o->firstSurface + index];
    return surf;
}
