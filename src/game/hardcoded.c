#include "hardcoded.h"

#include "levels/bbh/header.h"
#include "levels/bitdw/header.h"
#include "levels/bitfs/header.h"
#include "levels/bits/header.h"
#include "levels/bob/header.h"
#include "levels/bowser_1/header.h"
#include "levels/bowser_2/header.h"
#include "levels/bowser_2/header.h"
#include "levels/bowser_3/header.h"
#include "levels/bowser_3/header.h"
#include "levels/castle_courtyard/header.h"
#include "levels/castle_grounds/header.h"
#include "levels/castle_inside/header.h"
#include "levels/ccm/header.h"
#include "levels/cotmc/header.h"
#include "levels/ddd/header.h"
#include "levels/hmc/header.h"
#include "levels/jrb/header.h"
#include "levels/lll/header.h"
#include "levels/pss/header.h"
#include "levels/rr/header.h"
#include "levels/sa/header.h"
#include "levels/sl/header.h"
#include "levels/ssl/header.h"
#include "levels/thi/header.h"
#include "levels/totwc/header.h"
#include "levels/ttc/header.h"
#include "levels/ttm/header.h"
#include "levels/vcutm/header.h"
#include "levels/wdw/header.h"
#include "levels/wf/header.h"
#include "levels/wmotr/header.h"

  ////////////
 // Levels //
////////////

struct LevelValues gLevelValues = {
    .entryLevel = LEVEL_CASTLE_GROUNDS,
    .starPositions = {
        .KoopaBobStarPos      = {  3030.0f,  4500.0f, -4600.0f },
        .KoopaThiStarPos      = {  7100.0f, -1300.0f, -6000.0f },
        .KingBobombStarPos    = {  2000.0f,  4500.0f, -4500.0f },
        .KingWhompStarPos     = {   180.0f,  3880.0f,   340.0f },
        .EyerockStarPos       = {     0.0f,  -900.0f, -3700.0f },
        .BigBullyStarPos      = {  3700.0f,   600.0f, -5500.0f },
        .ChillBullyStarPos    = {   130.0f,  1600.0f, -4335.0f },
        .BigPiranhasStarPos   = { -6300.0f, -1850.0f, -6300.0f },
#ifdef VERSION_JP
        .TuxieMotherStarPos   = { 3500.0f,  -4300.0f,  4650.0f },
#else
        .TuxieMotherStarPos   = {  3167.0f, -4300.0f,  5108.0f },
#endif
        .WigglerStarPos       = {     0.0f,  2048.0f,     0.0f },
        .PssSlideStarPos      = { -6358.0f, -4300.0f,  4700.0f },
        .RacingPenguinStarPos = { -7339.0f, -5700.0f, -6774.0f },
        .TreasureJrbStarPos   = { -1800.0f, -2500.0f, -1700.0f },
        .TreasureChestStarPos = { -1900.0f, -4000.0f, -1400.0f },
        .GhostHuntBooStarPos  = {   980.0f,  1100.0f,   250.0f },
        .KleptoStarPos        = { -5550.0f,   300.0f,  -930.0f },
        .MerryGoRoundStarPos  = { -1600.0f, -2100.0f,   205.0f },
        .MrIStarPos           = {  1370.0f,  2000.0f,  -320.0f },
        .BalconyBooStarPos    = {   700.0f,  3200.0f,  1900.0f },
        .BigBullyTrioStarPos  = {     0.0f,   950.0f, -6800.0f },
        .MantaRayStarPos      = { -3180.0f, -3600.0f,   120.0f },
        .SnowmanHeadStarPos   = { -4700.0f, -1024.0f,  1890.0f },
        .CcmSlideStarPos      = {  2500.0f, -4350.0f,  5750.0f },
        .UkikiCageStarPos     = {  2500.0f, -1200.0f,  1300.0f },
        .UnagiStarPos         = {  6833.0f, -3654.0f,  2230.0f },
        .JetstreamRingStarPos = {  3400.0f, -3200.0f,  -500.0f },
    },
};

  ///////////////
 // Behaviors //
///////////////

struct BehaviorValues gBehaviorValues = {
    .trajectories = {
        .KoopaBobTrajectory        = bob_seg7_trajectory_koopa,
        .KoopaThiTrajectory        = thi_seg7_trajectory_koopa,
        .UnagiTrajectory           = jrb_seg7_trajectory_unagi_1,
        .Unagi2Trajectory          = jrb_seg7_trajectory_unagi_2,
        .SnowmanHeadTrajectory     = ccm_seg7_trajectory_snowman,
        .RacingPenguinTrajectory   = ccm_seg7_trajectory_penguin_race,
        .BowlingBallBobTrajectory  = bob_seg7_metal_ball_path0,
        .BowlingBallBob2Trajectory = bob_seg7_metal_ball_path1,
        .BowlingBallTtmTrajectory  = ttm_seg7_trajectory_070170A0,
        .MipsTrajectory            = inside_castle_seg7_trajectory_mips_0,
        .Mips2Trajectory           = inside_castle_seg7_trajectory_mips_1,
        .Mips3Trajectory           = inside_castle_seg7_trajectory_mips_2,
        .Mips4Trajectory           = inside_castle_seg7_trajectory_mips_3,
        .Mips5Trajectory           = inside_castle_seg7_trajectory_mips_4,
        .Mips6Trajectory           = inside_castle_seg7_trajectory_mips_5,
        .Mips7Trajectory           = inside_castle_seg7_trajectory_mips_6,
        .Mips8Trajectory           = inside_castle_seg7_trajectory_mips_7,
        .Mips9Trajectory           = inside_castle_seg7_trajectory_mips_8,
        .Mips10Trajectory          = inside_castle_seg7_trajectory_mips_9,
        .PlatformRrTrajectory      = rr_seg7_trajectory_0702EC3C,
        .PlatformRr2Trajectory     = rr_seg7_trajectory_0702ECC0,
        .PlatformRr3Trajectory     = rr_seg7_trajectory_0702ED9C,
        .PlatformRr4Trajectory     = rr_seg7_trajectory_0702EEE0,
        .PlatformCcmTrajectory     = ccm_seg7_trajectory_0701669C,
        .PlatformBitfsTrajectory   = bitfs_seg7_trajectory_070159AC,
        .PlatformHmcTrajectory     = hmc_seg7_trajectory_0702B86C,
        .PlatformLllTrajectory     = lll_seg7_trajectory_0702856C,
        .PlatformLll2Trajectory    = lll_seg7_trajectory_07028660,
    },
};
