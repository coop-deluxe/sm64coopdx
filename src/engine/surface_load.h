#ifndef SURFACE_LOAD_H
#define SURFACE_LOAD_H

#include <PR/ultratypes.h>

#include "surface_collision.h"
#include "types.h"

#define NUM_CELLS       (2 * LEVEL_BOUNDARY_MAX / CELL_SIZE)
#define NUM_CELLS_INDEX (NUM_CELLS - 1)

struct SurfaceNode
{
    struct SurfaceNode *next;
    struct Surface *surface;
};

enum
{
    SPATIAL_PARTITION_FLOORS,
    SPATIAL_PARTITION_CEILS,
    SPATIAL_PARTITION_WALLS
};

typedef struct SurfaceNode SpatialPartitionCell[3];

extern SpatialPartitionCell gStaticSurfacePartition[NUM_CELLS][NUM_CELLS];
extern SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];

extern s32 gSurfaceNodesAllocated;
extern s32 gSurfacesAllocated;
extern s32 gNumStaticSurfaceNodes;
extern s32 gNumStaticSurfaces;
extern s32 gNumSOCSurfaceNodes;
extern s32 gNumSOCSurfaces;

void alloc_surface_pools(void);

u32 get_area_terrain_size(s16 *data);

void load_area_terrain(s16 index, s16 *data, s8 *surfaceRooms, s16 *macroObjects);
void clear_dynamic_surfaces(void);
/* |description|
Loads the object's collision data into dynamic collision.
You must run this every frame in your object's behavior loop for it to have collision
|descriptionEnd| */
void load_object_collision_model(void);
/* |description|
Loads the object's collision data into static collision.
You may run this only once to capture the object's collision at that frame.
|descriptionEnd| */
struct StaticObjectCollision *load_static_object_collision();
/* |description|Toggles a collection of static object surfaces|descriptionEnd| */
void toggle_static_object_collision(struct StaticObjectCollision *col, bool tangible);
/* |description|Gets a surface corresponding to `index` from the static object collision|descriptionEnd| */
struct Surface *get_static_object_surface(struct StaticObjectCollision *col, u32 index);
/* |description|Gets a surface corresponding to `index` from the surface pool buffer|descriptionEnd| */
struct Surface *obj_get_surface_from_index(struct Object *o, u32 index);
/* |description|Checks if a surface has force|descriptionEnd| */
bool surface_has_force(s16 surfaceType);

#endif // SURFACE_LOAD_H
