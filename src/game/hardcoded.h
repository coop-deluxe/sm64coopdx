#ifndef HARDCODED_H
#include "types.h"
#include "level_table.h"
#include  "dialog_ids.h"

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
    enum LevelNum exitCastleLevel;
    s16 exitCastleArea;
    u8 exitCastleWarpNode;
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
    struct BehaviorDialogs dialogs;
    struct BehaviorTrajectories trajectories;
};

extern struct BehaviorValues gBehaviorValues;

#endif