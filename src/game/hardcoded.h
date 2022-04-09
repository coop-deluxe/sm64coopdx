#ifndef HARDCODED_H
#include "types.h"
#include "level_table.h"

  ////////////
 // Levels //
////////////

struct StarPositions {
    Vec3f KoopaBobStarPos;
    Vec3f KoopaThiStarPos;
    Vec3f KingBobombStarPos;
    Vec3f KingWhompStarPos;
    Vec3f EyerockStarPos;
    Vec3f BigBullyStarPos;
    Vec3f ChillBullyStarPos;
    Vec3f BigPiranhasStarPos;
    Vec3f TuxieMotherStarPos;
    Vec3f WigglerStarPos;
    Vec3f PssSlideStarPos;
    Vec3f RacingPenguinStarPos;
    Vec3f TreasureJrbStarPos;
    Vec3f TreasureChestStarPos;
    Vec3f GhostHuntBooStarPos;
    Vec3f KleptoStarPos;
    Vec3f MerryGoRoundStarPos;
    Vec3f MrIStarPos;
    Vec3f BalconyBooStarPos;
    Vec3f BigBullyTrioStarPos;
    Vec3f MantaRayStarPos;
    Vec3f SnowmanHeadStarPos;
    Vec3f CcmSlideStarPos;
    Vec3f UkikiCageStarPos;
    Vec3f UnagiStarPos;
    Vec3f JetstreamRingStarPos;
};

struct LevelValues {
    enum LevelNum entryLevel;
    struct StarPositions starPositions;
};

extern struct LevelValues gLevelValues;

  ///////////////
 // Behaviors //
///////////////

struct BehaviorTrajectories {
    const Trajectory* KoopaBobTrajectory;
    const Trajectory* KoopaThiTrajectory;
    const Trajectory* UnagiTrajectory;
    const Trajectory* Unagi2Trajectory;
    const Trajectory* SnowmanHeadTrajectory;
    const Trajectory* RacingPenguinTrajectory;
    const Trajectory* BowlingBallBobTrajectory;
    const Trajectory* BowlingBallBob2Trajectory;
    const Trajectory* BowlingBallTtmTrajectory;
    const Trajectory* MipsTrajectory;
    const Trajectory* Mips2Trajectory;
    const Trajectory* Mips3Trajectory;
    const Trajectory* Mips4Trajectory;
    const Trajectory* Mips5Trajectory;
    const Trajectory* Mips6Trajectory;
    const Trajectory* Mips7Trajectory;
    const Trajectory* Mips8Trajectory;
    const Trajectory* Mips9Trajectory;
    const Trajectory* Mips10Trajectory;
    const Trajectory* PlatformRrTrajectory;
    const Trajectory* PlatformRr2Trajectory;
    const Trajectory* PlatformRr3Trajectory;
    const Trajectory* PlatformRr4Trajectory;
    const Trajectory* PlatformCcmTrajectory;
    const Trajectory* PlatformBitfsTrajectory;
    const Trajectory* PlatformHmcTrajectory;
    const Trajectory* PlatformLllTrajectory;
    const Trajectory* PlatformLll2Trajectory;
};

struct BehaviorValues {
    struct BehaviorTrajectories trajectories;
};

extern struct BehaviorValues gBehaviorValues;

#endif