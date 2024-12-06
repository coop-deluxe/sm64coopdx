#ifndef MARIO_STEP_NEW_H
#define MARIO_STEP_NEW_H

#include <PR/ultratypes.h>

#include "sm64.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "types.h"

// Strict - cos(72.49 deg) 0.30087224993
// Lax - cos(76.65 deg) 0.23089890826
#define WALLMAXNORMAL 0.30f

// Negative Y displacement added to make Mario snap to the nearest floor.
#define FLOOR_SNAP_OFFSET 78

// When grounded, what the angle difference between the wall and Mario's head needs to be for wall collision to occur
// i.e. the angle below which Mario bonks and above which he slides along the wall
#define MAX_ANGLE_DIFF_FOR_WALL_COLLISION_ON_GROUND DEGREES(60)

// When airborne, what the angle difference between the wall and Mario's head needs to be for wall collision to occur
// Tends to be larger as you can't mantle a wall while airborne
#define MAX_ANGLE_DIFF_FOR_WALL_COLLISION_IN_AIR DEGREES(135)

// Movedata lets us pass by struct to reduce arg passing overhead
struct MoveData {
    struct WallCollisionData WallCDs;
    struct Surface *HitSurface; // Raycast hit result
    //struct Surface *Wall;
    struct Surface *Floor;
    struct Surface *Ceil;
    f32 IntendedPos[3]; // Position we believe to be a good enough approximation for where Mario can go
    f32 GoalPos[3];     // Position we originally wanted to move towards
    f32 FloorHeight;
    f32 CeilHeight;
    f32 WaterHeight;
    f32 MarioHeight;
    f32 MarioWidth;
    s32 StepArgs;
    f32 BiggestValidMove; // How much we managed to move
};

s32 PerformStep(struct MarioState *m, Vec3f GoalPos, const s32 StepArgs);

#endif // MARIO_STEP_NEW_H
