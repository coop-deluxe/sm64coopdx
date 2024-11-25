#include "hardcoded.h"
#include "engine/surface_collision.h"

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

#include "pc/pc_main.h"

extern Trajectory sThiHugeMetalBallTraj[];
extern Trajectory sThiTinyMetalBallTraj[];

  ////////////
 // Levels //
////////////

struct LevelValues gDefaultLevelValues = {
    .fixCollisionBugs                 = FALSE,
    .fixCollisionBugsRoundedCorners   = TRUE,
    .fixCollisionBugsFalseLedgeGrab   = TRUE,
    .fixCollisionBugsGroundPoundBonks = TRUE,
    .fixCollisionBugsPickBestWall     = TRUE,
    .fixVanishFloors                  = FALSE,
    .hudCapTimer                      = FALSE,
    .hudRedCoinsRadar                 = FALSE,
    .hudSecretsRadar                  = FALSE,
    .starHeal                         = FALSE,
    .mushroom1UpHeal                  = FALSE,
    .floatingStarDance                = FALSE,
    .previewBlueCoins                 = FALSE,
    .respawnBlueCoinsSwitch           = FALSE,
    .visibleSecrets                   = FALSE,
    .showStarNumber                   = FALSE,
    .extendedPauseDisplay             = FALSE,
    .pauseExitAnywhere                = TRUE,
    .disableActs                      = FALSE,
    .bubbleOnDeathBarrierInCapStages  = FALSE,
    .entryLevel                       = LEVEL_CASTLE_GROUNDS,
    .exitCastleLevel                  = LEVEL_CASTLE,
    .exitCastleArea                   = 1,
    .exitCastleWarpNode               = 0x1F,
    .wingCapLookUpReq                 = 10,
    .skipCreditsAt                    = (LEVEL_MAX + 1),
    .pssSlideStarTime                 = 630,
    .pssSlideStarIndex                = 1,
    .coinsRequiredForCoinStar         = 100,
    .infiniteStairsRequirement        = 70,
    .wingCapDuration                  = 1800,
    .metalCapDuration                 = 600,
    .vanishCapDuration                = 600,
    .wingCapDurationTotwc             = 1200,
    .metalCapDurationCotmc            = 600,
    .vanishCapDurationVcutm           = 600,
    .wingCapSequence                  = SEQ_EVENT_POWERUP,
    .metalCapSequence                 = SEQ_EVENT_METAL_CAP,
    .vanishCapSequence                = SEQ_EVENT_POWERUP,
    .starPositions = {
        .KoopaBobStarPos              = {  3030.0f,  4500.0f, -4600.0f },
        .KoopaThiStarPos              = {  7100.0f, -1300.0f, -6000.0f },
        .KingBobombStarPos            = {  2000.0f,  4500.0f, -4500.0f },
        .KingWhompStarPos             = {   180.0f,  3880.0f,   340.0f },
        .EyerockStarPos               = {     0.0f,  -900.0f, -3700.0f },
        .BigBullyStarPos              = {  3700.0f,   600.0f, -5500.0f },
        .ChillBullyStarPos            = {   130.0f,  1600.0f, -4335.0f },
        .BigPiranhasStarPos           = { -6300.0f, -1850.0f, -6300.0f },
#ifdef VERSION_JP
        .TuxieMotherStarPos           = { 3500.0f,  -4300.0f,  4650.0f },
#else
        .TuxieMotherStarPos           = {  3167.0f, -4300.0f,  5108.0f },
#endif
        .WigglerStarPos               = {     0.0f,  2048.0f,     0.0f },
        .PssSlideStarPos              = { -6358.0f, -4300.0f,  4700.0f },
        .RacingPenguinStarPos         = { -7339.0f, -5700.0f, -6774.0f },
        .TreasureJrbStarPos           = { -1800.0f, -2500.0f, -1700.0f },
        .TreasureChestStarPos         = { -1900.0f, -4000.0f, -1400.0f },
        .GhostHuntBooStarPos          = {   980.0f,  1100.0f,   250.0f },
        .KleptoStarPos                = { -5550.0f,   300.0f,  -930.0f },
        .MerryGoRoundStarPos          = { -1600.0f, -2100.0f,   205.0f },
        .MrIStarPos                   = {  1370.0f,  2000.0f,  -320.0f },
        .BalconyBooStarPos            = {   700.0f,  3200.0f,  1900.0f },
        .BigBullyTrioStarPos          = {     0.0f,   950.0f, -6800.0f },
        .MantaRayStarPos              = { -3180.0f, -3600.0f,   120.0f },
        .SnowmanHeadStarPos           = { -4700.0f, -1024.0f,  1890.0f },
        .CcmSlideStarPos              = {  2500.0f, -4350.0f,  5750.0f },
        .UkikiCageStarPos             = {  2500.0f, -1200.0f,  1300.0f },
        .UnagiStarPos                 = {  6833.0f, -3654.0f,  2230.0f },
        .JetstreamRingStarPos         = {  3400.0f, -3200.0f,  -500.0f }
    },
    .cellHeightLimit                  = CELL_HEIGHT_LIMIT,
    .floorLowerLimit                  = FLOOR_LOWER_LIMIT,
    .floorLowerLimitMisc              = FLOOR_LOWER_LIMIT_MISC,
    .floorLowerLimitShadow            = FLOOR_LOWER_LIMIT_SHADOW,
    .maxLives                         = 100,
    .maxCoins                         = 999,
    .numCoinsToLife                   = 50,
    .wdwWaterLevelSpeed               = 10.0f,
    .useGlobalStarIds                 = FALSE,
    .zoomOutCameraOnPause             = TRUE,
    .jrbDarkenSkybox                  = TRUE
};

struct LevelValues gLevelValues = { 0 };

  ///////////////
 // Behaviors //
///////////////

struct BehaviorValues gDefaultBehaviorValues = {
    .KoopaBobAgility          = 4.0f,
    .KoopaCatchupAgility      = 8.0f,
    .KoopaThiAgility          = 6.0f,
    .RacingPenguinBigHeight   = 250.0f,
    .RacingPenguinBigRadius   = 350.0f,
    .RacingPenguinHeight      = 200.0f,
    .RacingPenguinRadius      = 200.0f,
    .ToadStar1Requirement     = 12,
    .ToadStar2Requirement     = 25,
    .ToadStar3Requirement     = 35,
    .KingBobombFVel           = 3.0f,
    .KingBobombYawVel         = 0x100,
    .KingBobombHealth         = 3,
    .KingWhompHealth          = 3,
    .MipsStar1Requirement     = 15,
    .MipsStar2Requirement     = 50,
    .BowlingBallBobSpeed      = 20.0f,
    .BowlingBallBob2Speed     = 10.0f,
    .BowlingBallTtmSpeed      = 20.0f,
    .BowlingBallThiLargeSpeed = 25.0f,
    .BowlingBallThiSmallSpeed = 10.0f,
    .GrateStarRequirement     = 120,
    .ChillBullyDeathPosY      = 1030.0f,
    .ShowStarMilestones       = TRUE,
    .ShowStarDialog           = TRUE,
    .RespawnShellBoxes        = TRUE,
    .MultipleCapCollection    = FALSE,
    .InfiniteRenderDistance   = TRUE,
    .CourtyardBoosRequirement = 12,
    .starsNeededForDialog     = { 1, 3, 8, 30, 50, 70 },
    .dialogs = {
        .BobombBuddyBob1Dialog         = DIALOG_004,
        .BobombBuddyBob2Dialog         = DIALOG_105,
        .BobombBuddyOther1Dialog       = DIALOG_047,
        .BobombBuddyOther2Dialog       = DIALOG_106,
        .Bowser1DefeatedDialog         = DIALOG_119,
        .Bowser1Dialog                 = DIALOG_067,
        .Bowser2DefeatedDialog         = DIALOG_120,
        .Bowser2Dialog                 = DIALOG_092,
        .Bowser3Defeated120StarsDialog = DIALOG_163,
        .Bowser3DefeatedDialog         = DIALOG_121,
        .Bowser3Dialog                 = DIALOG_093,
        .CapswitchBaseDialog           = DIALOG_010,
        .CapswitchMetalDialog          = DIALOG_011,
        .CapswitchVanishDialog         = DIALOG_012,
        .CapswitchWingDialog           = DIALOG_010,
        .CastleEnterDialog             = DIALOG_021,
        .CollectedStarDialog           = DIALOG_014,
        .DefaultCutsceneDialog         = DIALOG_001,
        .DoorNeed1StarDialog           = DIALOG_024,
        .DoorNeed30StarsDialog         = DIALOG_027,
        .DoorNeed3StarsDialog          = DIALOG_025,
        .DoorNeed50StarsDialog         = DIALOG_028,
        .DoorNeed70StarsDialog         = DIALOG_029,
        .DoorNeed8StarsDialog          = DIALOG_026,
        .DoorNeedKeyDialog             = DIALOG_022,
        .EyerokDefeatedDialog          = DIALOG_118,
        .EyerokIntroDialog             = DIALOG_117,
        .GhostHuntAfterDialog          = DIALOG_108,
        .GhostHuntDialog               = DIALOG_107,
        .HootIntroDialog               = DIALOG_044,
        .HootTiredDialog               = DIALOG_045,
        .HundredCoinsDialog            = DIALOG_013,
        .IntroPipeDialog               = DIALOG_033,
        .KeyDoor1DontHaveDialog        = DIALOG_022,
        .KeyDoor1HaveDialog            = DIALOG_023,
        .KeyDoor2DontHaveDialog        = DIALOG_022,
        .KeyDoor2HaveDialog            = DIALOG_023,
        .KingBobombCheatDialog         = DIALOG_128,
        .KingBobombDefeatDialog        = DIALOG_116,
        .KingBobombIntroDialog         = DIALOG_017,
        .KingWhompDefeatDialog         = DIALOG_115,
        .KingWhompDialog               = DIALOG_114,
        .KoopaQuickBobStartDialog      = DIALOG_005,
        .KoopaQuickBobWinDialog        = DIALOG_007,
        .KoopaQuickCheatedDialog       = DIALOG_006,
        .KoopaQuickLostDialog          = DIALOG_041,
        .KoopaQuickThiStartDialog      = DIALOG_009,
        .KoopaQuickThiWinDialog        = DIALOG_031,
        .LakituIntroDialog             = DIALOG_034,
        .MetalCourseDialog             = DIALOG_130,
        .Mips1Dialog                   = DIALOG_084,
        .Mips2Dialog                   = DIALOG_162,
        .PeachLetterDialog             = DIALOG_020,
        .RacingPenguinBigStartDialog   = DIALOG_164,
        .RacingPenguinCheatDialog      = DIALOG_132,
        .RacingPenguinLostDialog       = DIALOG_037,
        .RacingPenguinStartDialog      = DIALOG_055,
        .RacingPenguinWinDialog        = DIALOG_056,
        .SnowmanHeadAfterDialog        = DIALOG_111,
        .SnowmanHeadBodyDialog         = DIALOG_110,
        .SnowmanHeadDialog             = DIALOG_109,
        .SnowmanWindDialog             = DIALOG_153,
        .StarCollectionBaseDialog      = DIALOG_141,
        .StarDoorDialog                = DIALOG_038,
        .ToadStar1AfterDialog          = DIALOG_154,
        .ToadStar1Dialog               = DIALOG_082,
        .ToadStar2AfterDialog          = DIALOG_155,
        .ToadStar2Dialog               = DIALOG_076,
        .ToadStar3AfterDialog          = DIALOG_156,
        .ToadStar3Dialog               = DIALOG_083,
        .TuxieMotherDialog             = DIALOG_057,
        .TuxieMotherBabyFoundDialog    = DIALOG_058,
        .TuxieMotherBabyWrongDialog    = DIALOG_059,
        .UkikiCageDialog               = DIALOG_080,
        .UkikiCapGiveDialog            = DIALOG_101,
        .UkikiCapStealDialog           = DIALOG_100,
        .UkikiHeldDialog               = DIALOG_079,
        .VanishCourseDialog            = DIALOG_129,
        .WigglerAttack1Dialog          = DIALOG_152,
        .WigglerAttack2Dialog          = DIALOG_168,
        .WigglerAttack3Dialog          = DIALOG_151,
        .WigglerDialog                 = DIALOG_150,
        .WingCourseDialog              = DIALOG_131,
        .YoshiDialog                   = DIALOG_161
    },
    .trajectories = {
        .KoopaBobTrajectory            = (Trajectory*) bob_seg7_trajectory_koopa,
        .KoopaThiTrajectory            = (Trajectory*) thi_seg7_trajectory_koopa,
        .UnagiTrajectory               = (Trajectory*) jrb_seg7_trajectory_unagi_1,
        .Unagi2Trajectory              = (Trajectory*) jrb_seg7_trajectory_unagi_2,
        .SnowmanHeadTrajectory         = (Trajectory*) ccm_seg7_trajectory_snowman,
        .RacingPenguinTrajectory       = (Trajectory*) ccm_seg7_trajectory_penguin_race,
        .BowlingBallBobTrajectory      = (Trajectory*) bob_seg7_metal_ball_path0,
        .BowlingBallBob2Trajectory     = (Trajectory*) bob_seg7_metal_ball_path1,
        .BowlingBallTtmTrajectory      = (Trajectory*) ttm_seg7_trajectory_070170A0,
        .BowlingBallThiLargeTrajectory = (Trajectory*) sThiHugeMetalBallTraj,
        .BowlingBallThiSmallTrajectory = (Trajectory*) sThiTinyMetalBallTraj,
        .MipsTrajectory                = (Trajectory*) inside_castle_seg7_trajectory_mips_0,
        .Mips2Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_1,
        .Mips3Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_2,
        .Mips4Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_3,
        .Mips5Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_4,
        .Mips6Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_5,
        .Mips7Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_6,
        .Mips8Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_7,
        .Mips9Trajectory               = (Trajectory*) inside_castle_seg7_trajectory_mips_8,
        .Mips10Trajectory              = (Trajectory*) inside_castle_seg7_trajectory_mips_9,
        .PlatformRrTrajectory          = (Trajectory*) rr_seg7_trajectory_0702EC3C,
        .PlatformRr2Trajectory         = (Trajectory*) rr_seg7_trajectory_0702ECC0,
        .PlatformRr3Trajectory         = (Trajectory*) rr_seg7_trajectory_0702ED9C,
        .PlatformRr4Trajectory         = (Trajectory*) rr_seg7_trajectory_0702EEE0,
        .PlatformCcmTrajectory         = (Trajectory*) ccm_seg7_trajectory_0701669C,
        .PlatformBitfsTrajectory       = (Trajectory*) bitfs_seg7_trajectory_070159AC,
        .PlatformHmcTrajectory         = (Trajectory*) hmc_seg7_trajectory_0702B86C,
        .PlatformLllTrajectory         = (Trajectory*) lll_seg7_trajectory_0702856C,
        .PlatformLll2Trajectory        = (Trajectory*) lll_seg7_trajectory_07028660
    }
};

struct BehaviorValues gBehaviorValues = { 0 };

struct ExclamationBoxContent sDefaultExclamationBoxContents[] = {
    { 0, 0, 0, E_MODEL_MARIOS_WING_CAP, id_bhvWingCap },
    { 1, 0, 0, E_MODEL_MARIOS_METAL_CAP, id_bhvMetalCap },
    { 2, 0, 0, E_MODEL_MARIOS_CAP, id_bhvVanishCap },
    { 3, 0, 0, E_MODEL_KOOPA_SHELL, id_bhvKoopaShell },
    { 4, 0, 0, E_MODEL_YELLOW_COIN, id_bhvSingleCoinGetsSpawned },
    { 5, 0, 0, E_MODEL_NONE, id_bhvThreeCoinsSpawn },
    { 6, 0, 0, E_MODEL_NONE, id_bhvTenCoinsSpawn },
    { 7, 0, 0, E_MODEL_1UP, id_bhv1upWalking },
    { 8, 0, 0, E_MODEL_STAR, id_bhvSpawnedStar },
    { 9, 0, 0, E_MODEL_1UP, id_bhv1upRunningAway },
    { 10, 0, 1, E_MODEL_STAR, id_bhvSpawnedStar },
    { 11, 0, 2, E_MODEL_STAR, id_bhvSpawnedStar },
    { 12, 0, 3, E_MODEL_STAR, id_bhvSpawnedStar },
    { 13, 0, 4, E_MODEL_STAR, id_bhvSpawnedStar },
    { 14, 0, 5, E_MODEL_STAR, id_bhvSpawnedStar }
};

// Hack: Create 2 arrays: one that is constantly default and one that can be changed.

struct ExclamationBoxContent sDummyContents[EXCLAMATION_BOX_MAX_SIZE];

struct ExclamationBoxContent* gExclamationBoxContents = sDummyContents;

u8 gExclamationBoxSize = 15;

  //////////////
 // Painting //
//////////////

struct PaintingValues gDefaultPaintingValues = {
    .cotmc_painting =     &cotmc_painting,
    .bob_painting =       &bob_painting,
    .ccm_painting =       &ccm_painting,
    .wf_painting =        &wf_painting,
    .jrb_painting =       &jrb_painting,
    .lll_painting =       &lll_painting,
    .ssl_painting =       &ssl_painting,
    .hmc_painting =       &hmc_painting,
    .ddd_painting =       &ddd_painting,
    .wdw_painting =       &wdw_painting,
    .thi_tiny_painting =  &thi_tiny_painting,
    .ttm_painting =       &ttm_painting,
    .ttc_painting =       &ttc_painting,
    .sl_painting =        &sl_painting,
    .thi_huge_painting =  &thi_huge_painting,
    .ttm_slide_painting = &ttm_slide_painting
};

struct PaintingValues gPaintingValues = { 0 };

  ///////////////
 // functions //
///////////////

AT_STARTUP void hardcoded_reset_default_values(void) {
    gLevelValues = gDefaultLevelValues;
    gBehaviorValues = gDefaultBehaviorValues;

    memcpy(&cotmc_painting, &default_cotmc_painting, sizeof(struct Painting));
    memcpy(&bob_painting, &default_bob_painting, sizeof(struct Painting));
    memcpy(&ccm_painting, &default_ccm_painting, sizeof(struct Painting));
    memcpy(&wf_painting, &default_wf_painting, sizeof(struct Painting));
    memcpy(&jrb_painting, &default_jrb_painting, sizeof(struct Painting));
    memcpy(&lll_painting, &default_lll_painting, sizeof(struct Painting));
    memcpy(&ssl_painting, &default_ssl_painting, sizeof(struct Painting));
    memcpy(&hmc_painting, &default_hmc_painting, sizeof(struct Painting));
    memcpy(&ddd_painting, &default_ddd_painting, sizeof(struct Painting));
    memcpy(&wdw_painting, &default_wdw_painting, sizeof(struct Painting));
    memcpy(&thi_tiny_painting, &default_thi_tiny_painting, sizeof(struct Painting));
    memcpy(&ttm_painting, &default_ttm_painting, sizeof(struct Painting));
    memcpy(&ttc_painting, &default_ttc_painting, sizeof(struct Painting));
    memcpy(&sl_painting, &default_sl_painting, sizeof(struct Painting));
    memcpy(&thi_huge_painting, &default_thi_huge_painting, sizeof(struct Painting));
    memcpy(&ttm_slide_painting, &default_ttm_slide_painting, sizeof(struct Painting));
    memcpy(sDummyContents, sDefaultExclamationBoxContents, sizeof(struct ExclamationBoxContent) * 15);

    gExclamationBoxContents = sDummyContents;
    gExclamationBoxSize = 15;

    gPaintingValues = gDefaultPaintingValues;
}
