#ifndef __EXTENDED_BOUNDS_H__
#define __EXTENDED_BOUNDS_H__

/*
    Better Extended Bounds by anonymous_moose
        Thanks to someone2639 for the shiftable segments patch
        Thanks to Wiseguy for the Surface Pool Full error code and 4x bounds fix

    0: Regular bounds
        Same as vanilla sm64, boundaries are (-8192 to 8191)
        16x16 collision cells.
    1: 2x extended bounds
        level boundaries are twice as big (-16384 to 16383)
        Collision calculations remain as fast as vanilla, at the cost of using more RAM.
        32x32 collision cells.
    2: Regular bounds (performance)
        Same boundaries as vanilla (-8192 to 8191), but with twice the amount of collision cells
        Trades more RAM usage for faster collision calculations.
        32x32 collision cells.
    3: 4x extended bounds
        level boundaries are 4 times as big (-32768 to 32767)
        Collision calculations remain as fast as vanilla, at the cost of using far more RAM (16 times vanilla).
        64x64 collision cells.
    

    If you see "SURFACE POOL FULL" or "SURFACE NODE POOL FULL" in game, you should increase 
    SURFACE_POOL_SIZE or SURFACE_NODE_POOL_SIZE, respectively, or reduce the amount of 
    collision surfaces in your level.
*/

//for the static assert macro
#include "macros.h"

//set this to the extended bounds mode you want, then do "make clean".
#define EXTENDED_BOUNDS_MODE 3

//the maximum amount of collision surfaces (static and dynamic combined)
//8200 should work fine for a 2x extended stage, the vanilla value is 2300
#define SURFACE_POOL_SIZE 0x4000

//make this approximately (amount of collision cells) + (SURFACE_POOL_SIZE * 3)
//22000 should work fine for a 2x extended stage, the vanilla value is 7000
#define SURFACE_NODE_POOL_SIZE 0x10000





//don't touch the stuff past this point unless you know what you're doing!

//default value to check if the user set a proper extended bounds mode
#define LEVEL_BOUNDARY_MAX 0x0000

#if EXTENDED_BOUNDS_MODE == 0
    #undef LEVEL_BOUNDARY_MAX // Undefine the old value to avoid compiler warnings
    #define LEVEL_BOUNDARY_MAX 0x2000L
    #define CELL_SIZE          0x400
#elif EXTENDED_BOUNDS_MODE == 1
    #undef LEVEL_BOUNDARY_MAX
    #define LEVEL_BOUNDARY_MAX 0x4000L
    #define CELL_SIZE          0x400
#elif EXTENDED_BOUNDS_MODE == 2
    #undef LEVEL_BOUNDARY_MAX
    #define LEVEL_BOUNDARY_MAX 0x2000L
    #define CELL_SIZE          0x200
#elif EXTENDED_BOUNDS_MODE == 3
    #undef LEVEL_BOUNDARY_MAX
    #define LEVEL_BOUNDARY_MAX 0x8000L
    #define CELL_SIZE          0x400
#endif

#ifndef __cplusplus
STATIC_ASSERT(LEVEL_BOUNDARY_MAX != 0, "You must set a valid extended bounds mode!");
#endif

#define NUM_CELLS (2 * LEVEL_BOUNDARY_MAX / CELL_SIZE)

#define NOT_ENOUGH_ROOM_FOR_SURFACES (1 << 0)
#define NOT_ENOUGH_ROOM_FOR_NODES    (1 << 1)

#endif // __EXTENDED_BOUNDS_H__
