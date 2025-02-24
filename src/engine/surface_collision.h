#ifndef SURFACE_COLLISION_H
#define SURFACE_COLLISION_H

#include <PR/ultratypes.h>

#include "types.h"

#include "engine/extended_bounds.h"


#define CELL_HEIGHT_LIMIT           20000
#define FLOOR_LOWER_LIMIT           -11000
#define FLOOR_LOWER_LIMIT_MISC      (FLOOR_LOWER_LIMIT + 1000)
// same as FLOOR_LOWER_LIMIT_MISC, explicitly for shadow.c
// It doesn't match if ".0" is removed or ".f" is added
#define FLOOR_LOWER_LIMIT_SHADOW    (FLOOR_LOWER_LIMIT + 1000.0)

struct WallCollisionData
{
    /*0x00*/ f32 x;
    /*????*/ f32 y;
    /*????*/ f32 z;
    /*0x0C*/ f32 offsetY;
    /*0x10*/ f32 radius;
    /*0x14*/ s16 unused;
    /*0x16*/ s16 numWalls;
    /*0x18*/ struct Surface *walls[4];
    /*????*/ Vec3f normalAddition;
    /*????*/ u8 normalCount;
};

struct FloorGeometry
{
    f32 unused[4]; // possibly position data?
    f32 normalX;
    f32 normalY;
    f32 normalZ;
    f32 originOffset;
};

extern Vec3f gFindWallDirection;
extern u8 gFindWallDirectionActive;
extern u8 gFindWallDirectionAirborne;

s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius);

/* |description|
Detects wall collisions at a given position and adjusts the position based on the walls found.
Returns the number of wall collisions detected
|descriptionEnd| */
s32 find_wall_collisions(struct WallCollisionData *colData);
f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil);

/* |description|
Finds the height of the highest ceiling above a given position (x, y, z).
If no ceiling is found, returns the default height limit of `gLevelValues.cellHeightLimit`(20000 by default)
|descriptionEnd| */
f32 find_ceil_height(f32 x, f32 y, f32 z);
f32 find_floor_height_and_data(f32 xPos, f32 yPos, f32 zPos, struct FloorGeometry **floorGeo);

/* |description|
Finds the height of the highest floor below a given position (x, y, z).
If no floor is found, returns the default floor height of `gLevelValues.floorLowerLimit`(-11000 by default)
|descriptionEnd| */
f32 find_floor_height(f32 x, f32 y, f32 z);
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);

/* |description|
Finds the height of water at a given position (x, z), if the position is within a water region.
If no water is found, returns the default height of `gLevelValues.floorLowerLimit`(-11000 by default)
|descriptionEnd| */
f32 find_water_level(f32 x, f32 z);

/* |description|
Finds the height of the poison gas at a given position (x, z), if the position is within a gas region.
If no gas is found, returns the default height of `gLevelValues.floorLowerLimit`(-11000 by default)
|descriptionEnd| */
f32 find_poison_gas_level(f32 x, f32 z);
void debug_surface_list_info(f32 xPos, f32 zPos);
void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, f32 precision);

/* |description|
Sets whether collision finding functions should check wall directions.
|descriptionEnd| */
void set_find_wall_direction(Vec3f dir, bool active, bool airborne);

#endif // SURFACE_COLLISION_H
