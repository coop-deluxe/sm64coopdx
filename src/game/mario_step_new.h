#ifndef MARIO_STEP_NEW_H
#define MARIO_STEP_NEW_H

#include <PR/ultratypes.h>

#include "types.h"

#define WALLMAXNORMAL 0.08f
#define FLOOR_SNAP_OFFSET 78

// how tall mario is for the purpose of collision
#define MARIOWIDENESS (FLOOR_SNAP_OFFSET * 2.f - 1.f)
#define MARIOHEIGHT (FLOOR_SNAP_OFFSET * 2.f - 1.f)

// Movedata lets us pass by struct to reduce arg passing overhead
struct MoveData {
    struct WallCollisionData WallCDs;
    struct Surface *HitSurface; // Raycast hit result
    //struct Surface *Wall;
    struct Surface *Floor;
    struct Surface *Ceil;
    f32 IntendedPos[3]; // Position we believe to be a good enough approximation for where mario can go
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
