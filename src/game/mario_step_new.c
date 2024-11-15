#include <ultra64.h>

#include "mario_step_new.h"

#include "mario.h"
#include "audio/external.h"
#include "game_init.h"
#include "interaction.h"
#include "mario_step.h"
#include "mario_step_new.h"
#include "pc/lua/smlua.h"
#include "game/hardcoded.h"
#include "game/object_helpers.h"
#include "pc/debuglog.h"

// New system to verify Mario's moves. Inspired by UE5's MoveUpdatedComponent function.
// Advantage:
// 1. Can no longer clip ceilings and steep floors
// 2. No more high speed clips
// 3. Consistently lands on steep floors
// 4. SM64 has an error up to 25% for moving mario. This has an error up to 1.56%.
// 5. Runs 4 collision calls per tick instead of 16 (95% of the time)
// 6. Consistent between swimming, aerial and ground step
// 7. Gets rid of quarterstep oddities
//
// Credit to Kaze Emanuar

// Co-Op Additions:
// 1. Smart Ledge Grabs - No longer can grab through floors.

u32 CheckLedgeGrab(struct MarioState *m, Vec3f intendedPos, Vec3f nextPos) {
    if (!m || m->vel[1] > 0.0f) { 
        return FALSE; 
    }

    f32 displacementX = nextPos[0] - intendedPos[0];
    f32 displacementZ = nextPos[2] - intendedPos[2];

    // Only ledge grab if the wall displaced Mario in the opposite direction of
    // his velocity.
    if (displacementX * m->vel[0] + displacementZ * m->vel[2] > 0.0f) {
        return FALSE;
    }

    struct Surface *ledgeFloor = NULL;
    Vec3f ledgePos;
    ledgePos[0] = nextPos[0] - m->wall->normal.x * 60.0f;
    ledgePos[2] = nextPos[2] - m->wall->normal.z * 60.0f;
    ledgePos[1] = find_floor(ledgePos[0], nextPos[1] + m->marioObj->hitboxHeight, ledgePos[2], &ledgeFloor);

    if (!ledgeFloor || ledgePos[1] - nextPos[1] <= 100.0f) {
        return FALSE; 
    }
    
    if (gLevelValues.fixCollisionBugs && gLevelValues.fixCollisionBugsFalseLedgeGrab) {
        // fix false ledge grabs
        if (ledgeFloor->normal.y < 0.90630779f) {
            return FALSE;
        }
    }
    
    // We'll cast a ray from the top of our height to the ledge grab position.
    // If we hit a surface. We aren't allowed to ledge grab.
    struct Surface *hitSurface = NULL;
    Vec3f HitPos;
    
    nextPos[1] += m->marioObj->hitboxHeight;
    find_surface_on_ray(nextPos, ledgePos, &hitSurface, HitPos, 8.f);
    nextPos[1] -= m->marioObj->hitboxHeight;

    // Don't grab the ledge if collision was found, and it's not the wall we wish to grab.
    if (hitSurface && hitSurface != m->wall) { return FALSE; }

    vec3f_copy(m->pos, ledgePos);
    m->floor = ledgeFloor;
    m->floorHeight = ledgePos[1];
    m->floorAngle = atan2s(ledgeFloor->normal.z, ledgeFloor->normal.x);

    m->faceAngle[0] = 0;
    m->faceAngle[1] = atan2s(m->wall->normal.z, m->wall->normal.x) + 0x8000;
    return TRUE;
}

// CheckMoveEndPosition

// This function checks Mario's final position for collisions.

//     Collision Adjustment:
//         Calculates MoveVector, the vector from Mario’s position to IntendedPos.
//         If MoveVector is non-zero, scales it to account for Mario's hitbox width.
//         Adjusts Mario’s Y position for accurate collision checking based on Mario’s height.
//     Raycasting for Collision:
//         Raycasts from Mario's position to ClipVector to detect potential collisions.
//         If a collision is detected, adjusts IntendedPos based on the collision normal to prevent Mario from clipping through walls or floors.

// Snap to the first collision in direction
void CheckMoveEndPosition(struct MarioState *m, struct MoveData *MoveResult) {
    MoveResult->HitSurface = 0;
    Vec3f MoveVector;
    MoveVector[0] = MoveResult->IntendedPos[0] - m->pos[0];
    MoveVector[1] = MoveResult->IntendedPos[1] - m->pos[1];
    MoveVector[2] = MoveResult->IntendedPos[2] - m->pos[2];
    f32 MoveSize = vec3f_length(MoveVector);
    // If we have no movement, Don't continue.
    if (MoveSize <= 0.0f) { return; }
    
    // Scale up move size to account for mario's size
    f32 ScaledMoveSize = ((MoveSize + MoveResult->MarioWidth) / MoveSize);
    // Seperate clipvector saves us some multiplications down the line!
    Vec3f ClipVector;
    ClipVector[0] = MoveVector[0] * ScaledMoveSize;
    ClipVector[1] = MoveVector[1] * ScaledMoveSize;
    ClipVector[2] = MoveVector[2] * ScaledMoveSize;

    // Use the middle of Mario's to most represent his hitbox (idealls this would be a capsule cast)
    m->pos[1] += MoveResult->MarioHeight / 2;
    Vec3f HitPos;
    find_surface_on_ray(m->pos, ClipVector, &MoveResult->HitSurface, HitPos, 8.f);
    m->pos[1] -= MoveResult->MarioHeight / 2;

    // Don't clip if no collision was found.
    if (MoveResult->HitSurface == NULL) { return; }
    
    //LOG_DEBUG("%f", (MoveResult->HitSurface)->normal.y);
    
    /*
    // Check for around ~cos(72.49 deg), If we as steep or any steeper.
    // We want to reject movement up/into the slope.
    if (absf((MoveResult->HitSurface)->normal.y) <= WALLMAXNORMAL) {
        const f32 DistanceMoved = sqrtf(sqr(HitPos[0] - MoveResult->IntendedPos[0]) +
                                        sqr(HitPos[1] - - MoveResult->MarioHeight / 2 - MoveResult->IntendedPos[1]) +
                                        sqr(HitPos[2] - MoveResult->IntendedPos[2]));

        // Move back either by as wide as Mario is or the whole distance, Whatever is less.
        f32 MoveBackScale = (MIN(DistanceMoved, MoveResult->MarioWidth) / MoveSize);
    
        MoveResult->IntendedPos[0] = HitPos[0] - MoveVector[0] * MoveBackScale;
        MoveResult->IntendedPos[1] = HitPos[1] - MoveVector[1] * MoveBackScale - MoveResult->MarioHeight / 2;
        MoveResult->IntendedPos[2] = HitPos[2] - MoveVector[2] * MoveBackScale;
    }
    */
    
    if ((MoveResult->HitSurface)->normal.y < 0.f) {
        // Let the binary search find a good position towards Mario's direction.
        MoveResult->IntendedPos[0] = HitPos[0] + MoveResult->HitSurface->normal.x;
        MoveResult->IntendedPos[1] = HitPos[1] + MoveResult->HitSurface->normal.y - MoveResult->MarioHeight / 2;
        MoveResult->IntendedPos[2] = HitPos[2] + MoveResult->HitSurface->normal.z;
    } else {
        // Snap far enough down to guarantee find_floor will find a bigger value.
        MoveResult->IntendedPos[1] = HitPos[1] - ((f32) FLOOR_SNAP_OFFSET) / 2.f;
        
        //! This causes issues with vanilla Super Mario 64. 
        //  Mario will zip up slopes very quickly when he is not supposed too. 
        //  This adds additionial offset to Mario's movement when it already accounts for slopes.
        //MoveResult->IntendedPos[0] = HitPos[0];
        //MoveResult->IntendedPos[2] = HitPos[2];
    }
}

// Checks if the new position is valid.
s32 CheckMoveValid(struct MarioState *m, struct MoveData *MoveResult) {
    // Wall collision happens first since walls will never prevent a move.
    if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
        resolve_and_return_wall_collisions_data(MoveResult->IntendedPos, 10.0f, 110.0f, &MoveResult->WallCDs);
    } else {
        resolve_and_return_wall_collisions_data(MoveResult->IntendedPos, 60.0f, MoveResult->MarioWidth + 10.f, &MoveResult->WallCDs);
    }
    MoveResult->FloorHeight = find_floor_air(MoveResult->IntendedPos[0], MoveResult->IntendedPos[1], MoveResult->IntendedPos[2], m->vel[1], &MoveResult->Floor);
    // OOB is invalid
    if (!MoveResult->Floor)
        return 0;
    // A special check for if we're riding a shell.
    MoveResult->WaterHeight = find_water_level(MoveResult->IntendedPos[0], MoveResult->IntendedPos[2]);
    if ((m->action & ACT_FLAG_RIDING_SHELL) && MoveResult->FloorHeight < MoveResult->WaterHeight) {
        MoveResult->FloorHeight = MoveResult->WaterHeight;
        MoveResult->Floor = &gWaterSurfacePseudoFloor;
        MoveResult->Floor->originOffset = MoveResult->FloorHeight; //! Wrong origin offset (no effect)
    }
    // Snap up early to make sure ceiling test happens from the right spot
    if ((MoveResult->StepArgs & STEP_SNAP_TO_FLOOR) && MoveResult->IntendedPos[1] < MoveResult->FloorHeight + FLOOR_SNAP_OFFSET) {
        MoveResult->IntendedPos[1] = MoveResult->FloorHeight;
    } else if (MoveResult->IntendedPos[1] < MoveResult->FloorHeight) {
        MoveResult->IntendedPos[1] = MoveResult->FloorHeight;
    }
    MoveResult->CeilHeight = vec3f_mario_ceil(MoveResult->IntendedPos, MoveResult->IntendedPos[1], &MoveResult->Ceil);
    // Mario does not fit here!
    if (MoveResult->FloorHeight + MoveResult->MarioHeight >= MoveResult->CeilHeight)
        return 0;
 
    return 1;
}

// Scales the move. The Y is assumed to always be valid (if not, we are ceiling bonking anyway)
s32 ScaleMove(struct MarioState *m, struct MoveData *MoveResult, f32 Scale) {
    MoveResult->IntendedPos[0] = (MoveResult->GoalPos[0] - m->pos[0]) * Scale + m->pos[0];
    MoveResult->IntendedPos[1] = MoveResult->GoalPos[1];
    MoveResult->IntendedPos[2] = (MoveResult->GoalPos[2] - m->pos[2]) * Scale + m->pos[2];
}

// FinishMove

// This final function updates Mario’s state based on the collision results from MoveData.

//     Updating Mario's Position and Collision State:
//         Sets Mario's floor, ceiling, and wall collision data.
//         Checks if Mario hits a ceiling during upward movement and removes his velocity if the ceiling is sloped toward him.
//         If IntendedPos is a valid ground position, finalizes Mario’s location there; otherwise, he remains airborne.

s32 FinishMove(struct MarioState *m, struct MoveData *MoveResult) {
    m->floor = MoveResult->Floor;
    m->ceil = MoveResult->Ceil;
    m->floorHeight = MoveResult->FloorHeight;
    m->ceilHeight = MoveResult->CeilHeight;

    vec3f_copy(m->pos, MoveResult->IntendedPos);

    mario_update_wall(m, &MoveResult->WallCDs);
    
    //LOG_DEBUG("\nPOS: (%f, %f, %f)\nVEL: (%f, %f, %f)\nCEIL HEIGHT: %f\nFLOOR HEIGHT: %f\n",
    //          m->pos[0], m->pos[1], m->pos[2], m->vel[0], m->vel[1], m->vel[2], m->ceilHeight, m->floorHeight);
    
    const float CeilDist = m->ceilHeight - m->pos[1];
    if (CeilDist < MoveResult->MarioHeight) {
        const float MissingDist = MoveResult->MarioHeight - CeilDist;
        m->pos[0] += m->ceil->normal.x * MissingDist/2;
        m->pos[1] += m->ceil->normal.y * MissingDist/2;
        m->pos[2] += m->ceil->normal.z * MissingDist/2;
        if ((MoveResult->StepArgs & STEP_CHECK_HANG) && m->ceil != NULL && ((m->ceil->type == SURFACE_HANGABLE))) {
            m->vel[1] = 0.0f; 
            return STEP_GRAB_CEILING;
        }
        
        f32 VelocitySize = vec3f_length(m->vel);
        if (VelocitySize > 0.f) {
            float DotProduct = m->vel[0] * m->ceil->normal.x
                             + m->vel[1] * m->ceil->normal.y
                             + m->vel[2] * m->ceil->normal.z;
            m->vel[0] -= DotProduct * m->ceil->normal.x;
            m->vel[1] -= MAX(0, DotProduct * m->ceil->normal.y);
            m->vel[2] -= DotProduct * m->ceil->normal.z;
        }
        
        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
            return STEP_HIT_CEILING; 
        }
    }

    // If we are not set to snap to the floor but landed despite that, on ground takes priority!
    if (!(MoveResult->StepArgs & STEP_SNAP_TO_FLOOR) && (m->pos[1] <= m->floorHeight)) {
        return STEP_ON_GROUND;
    }

    for (u8 i = 0; i < MoveResult->WallCDs.numWalls; i++) {
        m->wall = MoveResult->WallCDs.walls[i];

        if (m->wall->type == SURFACE_BURNING) {
            return STEP_HIT_LAVA;
        }

        if (MoveResult->StepArgs & STEP_CHECK_LEDGE_GRAB && CheckLedgeGrab(m, MoveResult->GoalPos, MoveResult->IntendedPos)) {
            return STEP_GRAB_LEDGE;
        }

        u16 WallAngleMaxDiff = MoveResult->StepArgs & STEP_SNAP_TO_FLOOR 
                                    ? 0x8000 - MAX_ANGLE_DIFF_FOR_WALL_COLLISION_ON_GROUND 
                                    : 0x8000 - MAX_ANGLE_DIFF_FOR_WALL_COLLISION_IN_AIR;
        if (absi((s16) (atan2s(m->wall->normal.z, m->wall->normal.x) - m->faceAngle[1])) >= WallAngleMaxDiff) {
            return STEP_HIT_WALL;
        }
    }
    
    // If we haven't moved, we hit either oob or a ceiling.
#define ZERO_POINT_FIVE_TO_THE_POWER_OF_MINUS_NUM_SEARCHES 0.015625f
    if (MoveResult->BiggestValidMove < ZERO_POINT_FIVE_TO_THE_POWER_OF_MINUS_NUM_SEARCHES) {
        return STEP_HIT_WALL;
    }

    return m->pos[1] <= m->floorHeight ? STEP_ON_GROUND : STEP_IN_AIR;
}

// Performs a generic step and returns the step result
// [StepArgs] checks for special interactions like ceilings, ledges and floor snapping
s32 PerformStep(struct MarioState *m, Vec3f GoalPos, const s32 StepArgs) {
    struct MoveData MoveResult = { 0 };
    MoveResult.MarioHeight = m->marioObj->hitboxHeight;
    MoveResult.MarioWidth = m->marioObj->hitboxRadius;
    MoveResult.StepArgs = StepArgs;
    vec3f_copy(MoveResult.IntendedPos, GoalPos);
    s32 IterationsRemaining = 2;
DoItAgain:
    CheckMoveEndPosition(m, &MoveResult);
    vec3f_copy(MoveResult.GoalPos, MoveResult.IntendedPos);
 
    if (!CheckMoveValid(m, &MoveResult)) {
        // Move was unsuccessful. Scale it down to a precision of 2^-NUM_SEARCHES
        f32 CurrentMoveSize = 0.5f;
        MoveResult.BiggestValidMove = 0.f;
#define NUM_SEARCHES 6
        for (s32 BinarySplitsReamining = NUM_SEARCHES; BinarySplitsReamining > 0; BinarySplitsReamining--) {
            ScaleMove(m, &MoveResult, MoveResult.BiggestValidMove + CurrentMoveSize);
            if (CheckMoveValid(m, &MoveResult)) {
                MoveResult.BiggestValidMove += CurrentMoveSize;
            }
            CurrentMoveSize *= 0.5f;
        }
        ScaleMove(m, &MoveResult, MoveResult.BiggestValidMove);
        // No valid move can be made. We are stuck OOB.
        // This should only happen if a platform OOB teleported away.
        // Mario should die here.
        if (!CheckMoveValid(m, &MoveResult)) {
            return STEP_HIT_WALL;
        }
        // We've moved, but not the full distance.
        return FinishMove(m, &MoveResult);
    }
    
    // If the move is outright valid (VAST MAJORITY OF MOVES), just exit instantly.

    // Full move happened
    MoveResult.BiggestValidMove = 1.f;
    if (!MoveResult.HitSurface) {
        return FinishMove(m, &MoveResult);
    }

    // Ensure nothing moved mario's feet through a surface.
    // (Ledgegrabs may teleport mario, but they happen in FinishMove)
    struct Surface *HitSurface = NULL;
    Vec3f HitPos = { 0.f };
    Vec3f ClipVector = { 0.f };
    ClipVector[0] = MoveResult.GoalPos[0] - m->pos[0];
    // Move back up because floors in HitSurface move Mario down (ensures snapping)
    ClipVector[1] = MoveResult.GoalPos[1] - m->pos[1] + (MoveResult.HitSurface->normal.y > WALLMAXNORMAL ? FLOOR_SNAP_OFFSET / 2.f + 4.f : 0.f);
    ClipVector[2] = MoveResult.GoalPos[2] - m->pos[2];
    find_surface_on_ray(m->pos, ClipVector, &HitSurface, HitPos, 8.f);
    if (!HitSurface) {
        return FinishMove(m, &MoveResult);
    }
    // Give it another try, we do want to move as much as possible.
    vec3f_copy(MoveResult.GoalPos, HitPos);
    IterationsRemaining--;
    if (IterationsRemaining) {
        goto DoItAgain;
    }
    // No valid moves managed to be made. Emergency exit!
    return STEP_HIT_WALL;
}