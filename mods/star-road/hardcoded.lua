------------------
-- Level Values --
------------------

gLevelValues.entryLevel             = LEVEL_CASTLE_GROUNDS
gLevelValues.exitCastleLevel        = LEVEL_CASTLE_GROUNDS
gLevelValues.exitCastleWarpNode     = 128
gLevelValues.skipCreditsAt          = LEVEL_CASTLE_GROUNDS

gLevelValues.pssSlideStarTime       = 540

-- Cap Times
gLevelValues.wingCapDuration        = 2700
gLevelValues.metalCapDuration       = 900
gLevelValues.vanishCapDuration      = 900
gLevelValues.wingCapDurationTotwc   = 1800
gLevelValues.metalCapDurationCotmc  = 900
gLevelValues.vanishCapDurationVcutm = 900

-- Hidden Palace look up req

gLevelValues.wingCapLookUpReq = 120

gLevelValues.fixCollisionBugs = true
gLevelValues.vanishCapSequence = 0x32

-- Replace Stars
starPositions = gLevelValues.starPositions

vec3f_set(starPositions.KoopaBobStarPos,      -2977.0,  1590.0,  3018.0)
vec3f_set(starPositions.KoopaThiStarPos,      -3438.0,  5559.0,  2656.0)
vec3f_set(starPositions.KingBobombStarPos,     4792.0,  1882.0,  3985.0)
vec3f_set(starPositions.KingWhompStarPos,       478.0,  2761.0, -2220.0)
vec3f_set(starPositions.EyerockStarPos,        3156.0, -5550.0, -6841.0)
vec3f_set(starPositions.BigBullyStarPos,        -48.0,  2145.0,  2235.0)
vec3f_set(starPositions.ChillBullyStarPos,     4513.0,  3964.0,  3332.0)
vec3f_set(starPositions.BigPiranhasStarPos,    -946.0,  -677.0, -1069.0)
vec3f_set(starPositions.TuxieMotherStarPos,    5775.0,  2500.0, -5160.0)
vec3f_set(starPositions.WigglerStarPos,        4250.0,   390.0,   424.0)
vec3f_set(starPositions.PssSlideStarPos,       5668.0, -5772.0, -5226.0)
vec3f_set(starPositions.RacingPenguinStarPos,  2476.0,  1302.0, -6029.0)
vec3f_set(starPositions.TreasureChestStarPos, -1800.0, -2500.0, -1700.0)
vec3f_set(starPositions.GhostHuntBooStarPos,   4399.0,  2892.0, -4541.0)
vec3f_set(starPositions.KleptoStarPos,         4399.0,  2892.0, -4541.0)
vec3f_set(starPositions.MerryGoRoundStarPos,  -1600.0, -2100.0,   205.0)
vec3f_set(starPositions.MrIStarPos,           -3173.0, -1638.0,  1809.0)
vec3f_set(starPositions.BalconyBooStarPos,     4398.0,  2892.0, -4532.0)
vec3f_set(starPositions.BigBullyTrioStarPos,   3700.0,   600.0, -5500.0)

---------------------
-- Behavior Values --
---------------------

gBehaviorValues.ToadStar1Requirement = 0
gBehaviorValues.ToadStar2Requirement = 0
gBehaviorValues.ToadStar3Requirement = 0

gBehaviorValues.dialogs.ToadStar1Dialog = DIALOG_082
gBehaviorValues.dialogs.ToadStar2Dialog = DIALOG_076
gBehaviorValues.dialogs.ToadStar3Dialog = DIALOG_083
gBehaviorValues.dialogs.ToadStar1AfterDialog = DIALOG_154
gBehaviorValues.dialogs.ToadStar2AfterDialog = DIALOG_155
gBehaviorValues.dialogs.ToadStar3AfterDialog = DIALOG_156

gBehaviorValues.KingBobombHealth = 4

gBehaviorValues.KoopaBobAgility     = 4.0
gBehaviorValues.KoopaCatchupAgility = 8.0
gBehaviorValues.KoopaThiAgility     = 6.0

gBehaviorValues.MipsStar1Requirement = 0
gBehaviorValues.MipsStar2Requirement = 255

gBehaviorValues.GrateStarRequirement = 65

gBehaviorValues.trajectories.KoopaBobTrajectory            = get_trajectory('KoopaBoB_path')
gBehaviorValues.trajectories.KoopaThiTrajectory            = get_trajectory('KoopaTHI_path')
gBehaviorValues.trajectories.PlatformRrTrajectory          = get_trajectory('rr_seg7_trajectory_0702EC3C_RM2C_path')
gBehaviorValues.trajectories.PlatformRr2Trajectory         = get_trajectory('rr_seg7_trajectory_0702ECC0_RM2C_path')
gBehaviorValues.trajectories.PlatformCcmTrajectory         = get_trajectory('ccm_seg7_trajectory_0701669C_RM2C_path')
gBehaviorValues.trajectories.PlatformBitfsTrajectory       = get_trajectory('bitfs_seg7_trajectory_070159AC_RM2C_path')
gBehaviorValues.trajectories.PlatformHmcTrajectory         = get_trajectory('hmc_seg7_trajectory_0702B86C_RM2C_path')
gBehaviorValues.trajectories.PlatformLllTrajectory         = get_trajectory('lll_seg7_trajectory_0702856C_RM2C_path')
gBehaviorValues.trajectories.PlatformLll2Trajectory        = get_trajectory('lll_seg7_trajectory_07028660_RM2C_path')
gBehaviorValues.trajectories.PlatformRr3Trajectory         = get_trajectory('rr_seg7_trajectory_0702ED9C_RM2C_path')
gBehaviorValues.trajectories.PlatformRr4Trajectory         = get_trajectory('rr_seg7_trajectory_0702EEE0_RM2C_path')
gBehaviorValues.trajectories.RacingPenguinTrajectory       = get_trajectory('ccm_seg7_trajectory_penguin_race_RM2C_path')
gBehaviorValues.trajectories.BowlingBallBobTrajectory      = get_trajectory('ttc_bowling_ball_path')
gBehaviorValues.trajectories.BowlingBallThiLargeTrajectory = get_trajectory('rr_bowling_ball_path')
