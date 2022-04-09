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
    Trajectory* KoopaBobTrajectory;
    Trajectory* KoopaThiTrajectory;
    Trajectory* UnagiTrajectory;
    Trajectory* Unagi2Trajectory;
    Trajectory* SnowmanHeadTrajectory;
    Trajectory* RacingPenguinTrajectory;
    Trajectory* BowlingBallBobTrajectory;
    Trajectory* BowlingBallBob2Trajectory;
    Trajectory* BowlingBallTtmTrajectory;
    Trajectory* MipsTrajectory;
    Trajectory* Mips2Trajectory;
    Trajectory* Mips3Trajectory;
    Trajectory* Mips4Trajectory;
    Trajectory* Mips5Trajectory;
    Trajectory* Mips6Trajectory;
    Trajectory* Mips7Trajectory;
    Trajectory* Mips8Trajectory;
    Trajectory* Mips9Trajectory;
    Trajectory* Mips10Trajectory;
    Trajectory* PlatformRrTrajectory;
    Trajectory* PlatformRr2Trajectory;
    Trajectory* PlatformRr3Trajectory;
    Trajectory* PlatformRr4Trajectory;
    Trajectory* PlatformCcmTrajectory;
    Trajectory* PlatformBitfsTrajectory;
    Trajectory* PlatformHmcTrajectory;
    Trajectory* PlatformLllTrajectory;
    Trajectory* PlatformLll2Trajectory;
};

struct BehaviorValues {
    f32 KoopaBobAgility;
    f32 KoopaThiAgility;
    f32 KoopaCatchupAgility;
    struct BehaviorTrajectories trajectories;
};

extern struct BehaviorValues gBehaviorValues;

#endif