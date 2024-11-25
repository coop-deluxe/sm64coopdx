#ifndef HARDCODED_H
#define HARDCODED_H
#include "types.h"
#include "level_table.h"
#include "dialog_ids.h"
#include "seq_ids.h"
#include "paintings.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "include/behavior_table.h"

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
    u8 fixCollisionBugs;
    u8 fixCollisionBugsRoundedCorners;
    u8 fixCollisionBugsFalseLedgeGrab;
    u8 fixCollisionBugsGroundPoundBonks;
    u8 fixCollisionBugsPickBestWall;
    u8 fixVanishFloors;
    u8 hudCapTimer;
    u8 hudRedCoinsRadar;
    u8 hudSecretsRadar;
    u8 starHeal;
    u8 mushroom1UpHeal;
    u8 floatingStarDance;
    u8 previewBlueCoins;
    u8 respawnBlueCoinsSwitch;
    u8 visibleSecrets;
    u8 showStarNumber;
    u8 extendedPauseDisplay;
    u8 pauseExitAnywhere;
    u8 disableActs;
    u8 bubbleOnDeathBarrierInCapStages;
    enum LevelNum entryLevel;
    enum LevelNum exitCastleLevel;
    s16 exitCastleArea;
    u8 exitCastleWarpNode;
    s16 wingCapLookUpReq;
    enum LevelNum skipCreditsAt;
    u16 pssSlideStarTime;
    u8 pssSlideStarIndex;
    s16 coinsRequiredForCoinStar;
    s16 infiniteStairsRequirement;
    u16 wingCapDuration;
    u16 metalCapDuration;
    u16 vanishCapDuration;
    u16 wingCapDurationTotwc;
    u16 metalCapDurationCotmc;
    u16 vanishCapDurationVcutm;
    enum SeqId wingCapSequence;
    enum SeqId metalCapSequence;
    enum SeqId vanishCapSequence;
    struct StarPositions starPositions;
    s16 cellHeightLimit;
    s16 floorLowerLimit;
    s16 floorLowerLimitMisc;
    s16 floorLowerLimitShadow;
    u16 maxLives;
    u16 maxCoins;
    u16 numCoinsToLife;
    f32 wdwWaterLevelSpeed;
    u8 useGlobalStarIds;
    u8 zoomOutCameraOnPause;
    u8 jrbDarkenSkybox;
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
    Trajectory* BowlingBallThiLargeTrajectory;
    Trajectory* BowlingBallThiSmallTrajectory;
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

struct BehaviorDialogs {
    enum DialogId BobombBuddyBob1Dialog;
    enum DialogId BobombBuddyBob2Dialog;
    enum DialogId BobombBuddyOther1Dialog;
    enum DialogId BobombBuddyOther2Dialog;
    enum DialogId Bowser1DefeatedDialog;
    enum DialogId Bowser1Dialog;
    enum DialogId Bowser2DefeatedDialog;
    enum DialogId Bowser2Dialog;
    enum DialogId Bowser3Defeated120StarsDialog;
    enum DialogId Bowser3DefeatedDialog;
    enum DialogId Bowser3Dialog;
    enum DialogId CapswitchBaseDialog;
    enum DialogId CapswitchMetalDialog;
    enum DialogId CapswitchVanishDialog;
    enum DialogId CapswitchWingDialog;
    enum DialogId CastleEnterDialog;
    enum DialogId CollectedStarDialog;
    enum DialogId DefaultCutsceneDialog;
    enum DialogId DoorNeed1StarDialog;
    enum DialogId DoorNeed30StarsDialog;
    enum DialogId DoorNeed3StarsDialog;
    enum DialogId DoorNeed50StarsDialog;
    enum DialogId DoorNeed70StarsDialog;
    enum DialogId DoorNeed8StarsDialog;
    enum DialogId DoorNeedKeyDialog;
    enum DialogId EyerokDefeatedDialog;
    enum DialogId EyerokIntroDialog;
    enum DialogId GhostHuntAfterDialog;
    enum DialogId GhostHuntDialog;
    enum DialogId HootIntroDialog;
    enum DialogId HootTiredDialog;
    enum DialogId HundredCoinsDialog;
    enum DialogId IntroPipeDialog;
    enum DialogId KeyDoor1DontHaveDialog;
    enum DialogId KeyDoor1HaveDialog;
    enum DialogId KeyDoor2DontHaveDialog;
    enum DialogId KeyDoor2HaveDialog;
    enum DialogId KingBobombCheatDialog;
    enum DialogId KingBobombDefeatDialog;
    enum DialogId KingBobombIntroDialog;
    enum DialogId KingWhompDefeatDialog;
    enum DialogId KingWhompDialog;
    enum DialogId KoopaQuickBobStartDialog;
    enum DialogId KoopaQuickBobWinDialog;
    enum DialogId KoopaQuickCheatedDialog;
    enum DialogId KoopaQuickLostDialog;
    enum DialogId KoopaQuickThiStartDialog;
    enum DialogId KoopaQuickThiWinDialog;
    enum DialogId LakituIntroDialog;
    enum DialogId MetalCourseDialog;
    enum DialogId Mips1Dialog;
    enum DialogId Mips2Dialog;
    enum DialogId PeachLetterDialog;
    enum DialogId RacingPenguinBigStartDialog;
    enum DialogId RacingPenguinCheatDialog;
    enum DialogId RacingPenguinLostDialog;
    enum DialogId RacingPenguinStartDialog;
    enum DialogId RacingPenguinWinDialog;
    enum DialogId SnowmanHeadAfterDialog;
    enum DialogId SnowmanHeadBodyDialog;
    enum DialogId SnowmanHeadDialog;
    enum DialogId SnowmanWindDialog;
    enum DialogId StarCollectionBaseDialog;
    enum DialogId StarDoorDialog;
    enum DialogId ToadStar1AfterDialog;
    enum DialogId ToadStar1Dialog;
    enum DialogId ToadStar2AfterDialog;
    enum DialogId ToadStar2Dialog;
    enum DialogId ToadStar3AfterDialog;
    enum DialogId ToadStar3Dialog;
    enum DialogId TuxieMotherDialog;
    enum DialogId TuxieMotherBabyFoundDialog;
    enum DialogId TuxieMotherBabyWrongDialog;
    enum DialogId UkikiCageDialog;
    enum DialogId UkikiCapGiveDialog;
    enum DialogId UkikiCapStealDialog;
    enum DialogId UkikiHeldDialog;
    enum DialogId VanishCourseDialog;
    enum DialogId WigglerAttack1Dialog;
    enum DialogId WigglerAttack2Dialog;
    enum DialogId WigglerAttack3Dialog;
    enum DialogId WigglerDialog;
    enum DialogId WingCourseDialog;
    enum DialogId YoshiDialog;
};

#define STARS_NEEDED_FOR_DIALOG_COUNT 6
struct StarsNeededForDialog {
    u16 dialog1;
    u16 dialog2;
    u16 dialog3;
    u16 dialog4;
    u16 dialog5;
    u16 dialog6;
};

struct BehaviorValues {
    f32 KoopaBobAgility;
    f32 KoopaCatchupAgility;
    f32 KoopaThiAgility;
    f32 RacingPenguinBigHeight;
    f32 RacingPenguinBigRadius;
    f32 RacingPenguinHeight;
    f32 RacingPenguinRadius;
    u16 ToadStar1Requirement;
    u16 ToadStar2Requirement;
    u16 ToadStar3Requirement;
    f32 KingBobombFVel;
    s16 KingBobombYawVel;
    s16 KingBobombHealth;
    s16 KingWhompHealth;
    s16 MipsStar1Requirement;
    s16 MipsStar2Requirement;
    f32 BowlingBallBobSpeed;
    f32 BowlingBallBob2Speed;
    f32 BowlingBallTtmSpeed;
    f32 BowlingBallThiLargeSpeed;
    f32 BowlingBallThiSmallSpeed;
    u16 GrateStarRequirement;
    f32 ChillBullyDeathPosY;
    u8  ShowStarMilestones;
    u8  ShowStarDialog;
    u8  RespawnShellBoxes;
    u8  MultipleCapCollection;
    u8  InfiniteRenderDistance;
    s16 CourtyardBoosRequirement;
    struct StarsNeededForDialog starsNeededForDialog;
    struct BehaviorDialogs dialogs;
    struct BehaviorTrajectories trajectories;
};

extern struct BehaviorValues gBehaviorValues;

#define EXCLAMATION_BOX_MAX_SIZE 99

struct ExclamationBoxContent {
    u8 id;
    u8 unused;
    u8 firstByte;
    enum ModelExtendedId model;
    enum BehaviorId behavior;
};

extern struct ExclamationBoxContent* gExclamationBoxContents;
extern u8 gExclamationBoxSize;

  //////////////
 // Painting //
//////////////

struct PaintingValues {
    struct Painting* cotmc_painting;

    struct Painting* bob_painting;
    struct Painting* ccm_painting;
    struct Painting* wf_painting;
    struct Painting* jrb_painting;
    struct Painting* lll_painting;
    struct Painting* ssl_painting;
    struct Painting* hmc_painting;
    struct Painting* ddd_painting;
    struct Painting* wdw_painting;
    struct Painting* thi_tiny_painting;
    struct Painting* ttm_painting;
    struct Painting* ttc_painting;
    struct Painting* sl_painting;
    struct Painting* thi_huge_painting;

    struct Painting* ttm_slide_painting;
};

extern struct PaintingValues gPaintingValues;

  ///////////////
 // Functions //
///////////////

void hardcoded_reset_default_values(void);

#endif
