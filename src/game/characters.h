#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <PR/ultratypes.h>
#include "pc/configfile.h"
#include "mario_animation_ids.h"
// NOTE: do not include any additional headers

enum CharacterType {
    CT_MARIO,
    CT_LUIGI,
    CT_TOAD,
    CT_WALUIGI,
    CT_WARIO,

    // must be last
    CT_MAX
};

enum CharacterSound {
    CHAR_SOUND_YAH_WAH_HOO,
    CHAR_SOUND_HOOHOO,
    CHAR_SOUND_YAHOO,
    CHAR_SOUND_UH,
    CHAR_SOUND_HRMM,
    CHAR_SOUND_WAH2,
    CHAR_SOUND_WHOA,
    CHAR_SOUND_EEUH,
    CHAR_SOUND_ATTACKED,
    CHAR_SOUND_OOOF,
    CHAR_SOUND_OOOF2,
    CHAR_SOUND_HERE_WE_GO,
    CHAR_SOUND_YAWNING,
    CHAR_SOUND_SNORING1,
    CHAR_SOUND_SNORING2,
    CHAR_SOUND_WAAAOOOW,
    CHAR_SOUND_HAHA,
    CHAR_SOUND_HAHA_2,
    CHAR_SOUND_UH2,
    CHAR_SOUND_UH2_2,
    CHAR_SOUND_ON_FIRE,
    CHAR_SOUND_DYING,
    CHAR_SOUND_PANTING_COLD,
    CHAR_SOUND_PANTING,
    CHAR_SOUND_COUGHING1,
    CHAR_SOUND_COUGHING2,
    CHAR_SOUND_COUGHING3,
    CHAR_SOUND_PUNCH_YAH,
    CHAR_SOUND_PUNCH_HOO,
    CHAR_SOUND_MAMA_MIA,
    CHAR_SOUND_GROUND_POUND_WAH,
    CHAR_SOUND_DROWNING,
    CHAR_SOUND_PUNCH_WAH,
    CHAR_SOUND_YAHOO_WAHA_YIPPEE,
    CHAR_SOUND_DOH,
    CHAR_SOUND_GAME_OVER,
    CHAR_SOUND_HELLO,
    CHAR_SOUND_PRESS_START_TO_PLAY,
    CHAR_SOUND_TWIRL_BOUNCE,
    CHAR_SOUND_SNORING3,
    CHAR_SOUND_SO_LONGA_BOWSER,
    CHAR_SOUND_IMA_TIRED,
    CHAR_SOUND_LETS_A_GO,
    CHAR_SOUND_OKEY_DOKEY,
    CHAR_SOUND_MAX // MUST BE LAST
};

#define BASE_ANIMS() \
    .animSlowLedgeGrab =                    MARIO_ANIM_SLOW_LEDGE_GRAB, \
    .animFallOverBackwards =                MARIO_ANIM_FALL_OVER_BACKWARDS, \
    .animBackwardAirKb =                    MARIO_ANIM_BACKWARD_AIR_KB, \
    .animDyingOnBack =                      MARIO_ANIM_DYING_ON_BACK, \
    .animBackflip =                         MARIO_ANIM_BACKFLIP, \
    .animClimbUpPole =                      MARIO_ANIM_CLIMB_UP_POLE, \
    .animGrabPoleShort =                    MARIO_ANIM_GRAB_POLE_SHORT, \
    .animGrabPoleSwingPart1 =               MARIO_ANIM_GRAB_POLE_SWING_PART1, \
    .animGrabPoleSwingPart2 =               MARIO_ANIM_GRAB_POLE_SWING_PART2, \
    .animHandstandIdle =                    MARIO_ANIM_HANDSTAND_IDLE, \
    .animHandstandJump =                    MARIO_ANIM_HANDSTAND_JUMP, \
    .animStartHandstand =                   MARIO_ANIM_START_HANDSTAND, \
    .animReturnFromHandstand =              MARIO_ANIM_RETURN_FROM_HANDSTAND, \
    .animIdleOnPole =                       MARIO_ANIM_IDLE_ON_POLE, \
    .animAPose =                            MARIO_ANIM_A_POSE, \
    .animSkidOnGround =                     MARIO_ANIM_SKID_ON_GROUND, \
    .animStopSkid =                         MARIO_ANIM_STOP_SKID, \
    .animCrouchFromFastLongjump =           MARIO_ANIM_CROUCH_FROM_FAST_LONGJUMP, \
    .animCrouchFromSlowLongjump =           MARIO_ANIM_CROUCH_FROM_SLOW_LONGJUMP, \
    .animFastLongjump =                     MARIO_ANIM_FAST_LONGJUMP, \
    .animSlowLongjump =                     MARIO_ANIM_SLOW_LONGJUMP, \
    .animAirborneOnStomach =                MARIO_ANIM_AIRBORNE_ON_STOMACH, \
    .animWalkWithLightObj =                 MARIO_ANIM_WALK_WITH_LIGHT_OBJ, \
    .animRunWithLightObj =                  MARIO_ANIM_RUN_WITH_LIGHT_OBJ, \
    .animSlowWalkWithLightObj =             MARIO_ANIM_SLOW_WALK_WITH_LIGHT_OBJ, \
    .animShiveringWarmingHand =             MARIO_ANIM_SHIVERING_WARMING_HAND, \
    .animShiveringReturnToIdle =            MARIO_ANIM_SHIVERING_RETURN_TO_IDLE, \
    .animShivering =                        MARIO_ANIM_SHIVERING, \
    .animClimbDownLedge =                   MARIO_ANIM_CLIMB_DOWN_LEDGE, \
    .animCreditsWaving =                    MARIO_ANIM_CREDITS_WAVING, \
    .animCreditsLookUp =                    MARIO_ANIM_CREDITS_LOOK_UP, \
    .animCreditsReturnFromLookUp =          MARIO_ANIM_CREDITS_RETURN_FROM_LOOK_UP, \
    .animCreditsRaiseHand =                 MARIO_ANIM_CREDITS_RAISE_HAND, \
    .animCreditsLowerHand =                 MARIO_ANIM_CREDITS_LOWER_HAND, \
    .animCreditsTakeOffCap =                MARIO_ANIM_CREDITS_TAKE_OFF_CAP, \
    .animCreditsStartWalkLookUp =           MARIO_ANIM_CREDITS_START_WALK_LOOK_UP, \
    .animCreditsLookBackThenRun =           MARIO_ANIM_CREDITS_LOOK_BACK_THEN_RUN, \
    .animFinalBowserRaiseHandSpin =         MARIO_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN, \
    .animFinalBowserWingCapTakeOff =        MARIO_ANIM_FINAL_BOWSER_WING_CAP_TAKE_OFF, \
    .animCreditsPeaceSign =                 MARIO_ANIM_CREDITS_PEACE_SIGN, \
    .animStandUpFromLavaBoost =             MARIO_ANIM_STAND_UP_FROM_LAVA_BOOST, \
    .animFireLavaBurn =                     MARIO_ANIM_FIRE_LAVA_BURN, \
    .animWingCapFly =                       MARIO_ANIM_WING_CAP_FLY, \
    .animHangOnOwl =                        MARIO_ANIM_HANG_ON_OWL, \
    .animLandOnStomach =                    MARIO_ANIM_LAND_ON_STOMACH, \
    .animAirForwardKb =                     MARIO_ANIM_AIR_FORWARD_KB, \
    .animDyingOnStomach =                   MARIO_ANIM_DYING_ON_STOMACH, \
    .animSuffocating =                      MARIO_ANIM_SUFFOCATING, \
    .animCoughing =                         MARIO_ANIM_COUGHING, \
    .animThrowCatchKey =                    MARIO_ANIM_THROW_CATCH_KEY, \
    .animDyingFallOver =                    MARIO_ANIM_DYING_FALL_OVER, \
    .animIdleOnLedge =                      MARIO_ANIM_IDLE_ON_LEDGE, \
    .animFastLedgeGrab =                    MARIO_ANIM_FAST_LEDGE_GRAB, \
    .animHangOnCeiling =                    MARIO_ANIM_HANG_ON_CEILING, \
    .animPutCapOn =                         MARIO_ANIM_PUT_CAP_ON, \
    .animTakeCapOffThenOn =                 MARIO_ANIM_TAKE_CAP_OFF_THEN_ON, \
    .animQuicklyPutCapOn =                  MARIO_ANIM_QUICKLY_PUT_CAP_ON, \
    .animHeadStuckInGround =                MARIO_ANIM_HEAD_STUCK_IN_GROUND, \
    .animGroundPoundLanding =               MARIO_ANIM_GROUND_POUND_LANDING, \
    .animTripleJumpGroundPound =            MARIO_ANIM_TRIPLE_JUMP_GROUND_POUND, \
    .animStartGroundPound =                 MARIO_ANIM_START_GROUND_POUND, \
    .animGroundPound =                      MARIO_ANIM_GROUND_POUND, \
    .animBottomStuckInGround =              MARIO_ANIM_BOTTOM_STUCK_IN_GROUND, \
    .animIdleWithLightObj =                 MARIO_ANIM_IDLE_WITH_LIGHT_OBJ, \
    .animJumpLandWithLightObj =             MARIO_ANIM_JUMP_LAND_WITH_LIGHT_OBJ, \
    .animJumpWithLightObj =                 MARIO_ANIM_JUMP_WITH_LIGHT_OBJ, \
    .animFallLandWithLightObj =             MARIO_ANIM_FALL_LAND_WITH_LIGHT_OBJ, \
    .animFallWithLightObj =                 MARIO_ANIM_FALL_WITH_LIGHT_OBJ, \
    .animFallFromSlidingWithLightObj =      MARIO_ANIM_FALL_FROM_SLIDING_WITH_LIGHT_OBJ, \
    .animSlidingOnBottomWithLightObj =      MARIO_ANIM_SLIDING_ON_BOTTOM_WITH_LIGHT_OBJ, \
    .animStandUpFromSlidingWithLightObj =   MARIO_ANIM_STAND_UP_FROM_SLIDING_WITH_LIGHT_OBJ, \
    .animRidingShell =                      MARIO_ANIM_RIDING_SHELL, \
    .animWalking =                          MARIO_ANIM_WALKING, \
    .animForwardFlip =                      MARIO_ANIM_FORWARD_FLIP, \
    .animJumpRidingShell =                  MARIO_ANIM_JUMP_RIDING_SHELL, \
    .animLandFromDoubleJump =               MARIO_ANIM_LAND_FROM_DOUBLE_JUMP, \
    .animDoubleJumpFall =                   MARIO_ANIM_DOUBLE_JUMP_FALL, \
    .animSingleJump =                       MARIO_ANIM_SINGLE_JUMP, \
    .animLandFromSingleJump =               MARIO_ANIM_LAND_FROM_SINGLE_JUMP, \
    .animAirKick =                          MARIO_ANIM_AIR_KICK, \
    .animDoubleJumpRise =                   MARIO_ANIM_DOUBLE_JUMP_RISE, \
    .animStartForwardSpinning =             MARIO_ANIM_START_FORWARD_SPINNING, \
    .animThrowLightObject =                 MARIO_ANIM_THROW_LIGHT_OBJECT, \
    .animFallFromSlideKick =                MARIO_ANIM_FALL_FROM_SLIDE_KICK, \
    .animBendKnessRidingShell =             MARIO_ANIM_BEND_KNESS_RIDING_SHELL, \
    .animLegsStuckInGround =                MARIO_ANIM_LEGS_STUCK_IN_GROUND, \
    .animGeneralFall =                      MARIO_ANIM_GENERAL_FALL, \
    .animGeneralLand =                      MARIO_ANIM_GENERAL_LAND, \
    .animBeingGrabbed =                     MARIO_ANIM_BEING_GRABBED, \
    .animGrabHeavyObject =                  MARIO_ANIM_GRAB_HEAVY_OBJECT, \
    .animSlowLandFromDive =                 MARIO_ANIM_SLOW_LAND_FROM_DIVE, \
    .animFlyFromCannon =                    MARIO_ANIM_FLY_FROM_CANNON, \
    .animMoveOnWireNetRight =               MARIO_ANIM_MOVE_ON_WIRE_NET_RIGHT, \
    .animMoveOnWireNetLeft =                MARIO_ANIM_MOVE_ON_WIRE_NET_LEFT, \
    .animMissingCap =                       MARIO_ANIM_MISSING_CAP, \
    .animPullDoorWalkIn =                   MARIO_ANIM_PULL_DOOR_WALK_IN, \
    .animPushDoorWalkIn =                   MARIO_ANIM_PUSH_DOOR_WALK_IN, \
    .animUnlockDoor =                       MARIO_ANIM_UNLOCK_DOOR, \
    .animStartReachPocket =                 MARIO_ANIM_START_REACH_POCKET, \
    .animReachPocket =                      MARIO_ANIM_REACH_POCKET, \
    .animStopReachPocket =                  MARIO_ANIM_STOP_REACH_POCKET, \
    .animGroundThrow =                      MARIO_ANIM_GROUND_THROW, \
    .animGroundKick =                       MARIO_ANIM_GROUND_KICK, \
    .animFirstPunch =                       MARIO_ANIM_FIRST_PUNCH, \
    .animSecondPunch =                      MARIO_ANIM_SECOND_PUNCH, \
    .animFirstPunchFast =                   MARIO_ANIM_FIRST_PUNCH_FAST, \
    .animSecondPunchFast =                  MARIO_ANIM_SECOND_PUNCH_FAST, \
    .animPickUpLightObj =                   MARIO_ANIM_PICK_UP_LIGHT_OBJ, \
    .animPushing =                          MARIO_ANIM_PUSHING, \
    .animStartRidingShell =                 MARIO_ANIM_START_RIDING_SHELL, \
    .animPlaceLightObj =                    MARIO_ANIM_PLACE_LIGHT_OBJ, \
    .animForwardSpinning =                  MARIO_ANIM_FORWARD_SPINNING, \
    .animBackwardSpinning =                 MARIO_ANIM_BACKWARD_SPINNING, \
    .animBreakdance =                       MARIO_ANIM_BREAKDANCE, \
    .animRunning =                          MARIO_ANIM_RUNNING, \
    .animRunningUnused =                    MARIO_ANIM_RUNNING_UNUSED, \
    .animSoftBackKb =                       MARIO_ANIM_SOFT_BACK_KB, \
    .animSoftFrontKb =                      MARIO_ANIM_SOFT_FRONT_KB, \
    .animDyingInQuicksand =                 MARIO_ANIM_DYING_IN_QUICKSAND, \
    .animIdleInQuicksand =                  MARIO_ANIM_IDLE_IN_QUICKSAND, \
    .animMoveInQuicksand =                  MARIO_ANIM_MOVE_IN_QUICKSAND, \
    .animElectrocution =                    MARIO_ANIM_ELECTROCUTION, \
    .animShocked =                          MARIO_ANIM_SHOCKED, \
    .animBackwardKb =                       MARIO_ANIM_BACKWARD_KB, \
    .animForwardKb =                        MARIO_ANIM_FORWARD_KB, \
    .animIdleHeavyObj =                     MARIO_ANIM_IDLE_HEAVY_OBJ, \
    .animStandAgainstWall =                 MARIO_ANIM_STAND_AGAINST_WALL, \
    .animSidestepLeft =                     MARIO_ANIM_SIDESTEP_LEFT, \
    .animSidestepRight =                    MARIO_ANIM_SIDESTEP_RIGHT, \
    .animStartSleepIdle =                   MARIO_ANIM_START_SLEEP_IDLE, \
    .animStartSleepScratch =                MARIO_ANIM_START_SLEEP_SCRATCH, \
    .animStartSleepYawn =                   MARIO_ANIM_START_SLEEP_YAWN, \
    .animStartSleepSitting =                MARIO_ANIM_START_SLEEP_SITTING, \
    .animSleepIdle =                        MARIO_ANIM_SLEEP_IDLE, \
    .animSleepStartLying =                  MARIO_ANIM_SLEEP_START_LYING, \
    .animSleepLying =                       MARIO_ANIM_SLEEP_LYING, \
    .animDive =                             MARIO_ANIM_DIVE, \
    .animSlideDive =                        MARIO_ANIM_SLIDE_DIVE, \
    .animGroundBonk =                       MARIO_ANIM_GROUND_BONK, \
    .animStopSlideLightObj =                MARIO_ANIM_STOP_SLIDE_LIGHT_OBJ, \
    .animSlideKick =                        MARIO_ANIM_SLIDE_KICK, \
    .animCrouchFromSlideKick =              MARIO_ANIM_CROUCH_FROM_SLIDE_KICK, \
    .animSlideMotionless =                  MARIO_ANIM_SLIDE_MOTIONLESS, \
    .animStopSlide =                        MARIO_ANIM_STOP_SLIDE, \
    .animFallFromSlide =                    MARIO_ANIM_FALL_FROM_SLIDE, \
    .animSlide =                            MARIO_ANIM_SLIDE, \
    .animTiptoe =                           MARIO_ANIM_TIPTOE, \
    .animTwirlLand =                        MARIO_ANIM_TWIRL_LAND, \
    .animTwirl =                            MARIO_ANIM_TWIRL, \
    .animStartTwirl =                       MARIO_ANIM_START_TWIRL, \
    .animStopCrouching =                    MARIO_ANIM_STOP_CROUCHING, \
    .animStartCrouching =                   MARIO_ANIM_START_CROUCHING, \
    .animCrouching =                        MARIO_ANIM_CROUCHING, \
    .animCrawling =                         MARIO_ANIM_CRAWLING, \
    .animStopCrawling =                     MARIO_ANIM_STOP_CRAWLING, \
    .animStartCrawling =                    MARIO_ANIM_START_CRAWLING, \
    .animSummonStar =                       MARIO_ANIM_SUMMON_STAR, \
    .animReturnStarApproachDoor =           MARIO_ANIM_RETURN_STAR_APPROACH_DOOR, \
    .animBackwardsWaterKb =                 MARIO_ANIM_BACKWARDS_WATER_KB, \
    .animSwimWithObjPart1 =                 MARIO_ANIM_SWIM_WITH_OBJ_PART1, \
    .animSwimWithObjPart2 =                 MARIO_ANIM_SWIM_WITH_OBJ_PART2, \
    .animFlutterkickWithObj =               MARIO_ANIM_FLUTTERKICK_WITH_OBJ, \
    .animWaterActionEndWithObj =            MARIO_ANIM_WATER_ACTION_END_WITH_OBJ, \
    .animStopGrabObjWater =                 MARIO_ANIM_STOP_GRAB_OBJ_WATER, \
    .animWaterIdleWithObj =                 MARIO_ANIM_WATER_IDLE_WITH_OBJ, \
    .animDrowningPart1 =                    MARIO_ANIM_DROWNING_PART1, \
    .animDrowningPart2 =                    MARIO_ANIM_DROWNING_PART2, \
    .animWaterDying =                       MARIO_ANIM_WATER_DYING, \
    .animWaterForwardKb =                   MARIO_ANIM_WATER_FORWARD_KB, \
    .animFallFromWater =                    MARIO_ANIM_FALL_FROM_WATER, \
    .animSwimPart1 =                        MARIO_ANIM_SWIM_PART1, \
    .animSwimPart2 =                        MARIO_ANIM_SWIM_PART2, \
    .animFlutterkick =                      MARIO_ANIM_FLUTTERKICK, \
    .animWaterActionEnd =                   MARIO_ANIM_WATER_ACTION_END, \
    .animWaterPickUpObj =                   MARIO_ANIM_WATER_PICK_UP_OBJ, \
    .animWaterGrabObjPart2 =                MARIO_ANIM_WATER_GRAB_OBJ_PART2, \
    .animWaterGrabObjPart1 =                MARIO_ANIM_WATER_GRAB_OBJ_PART1, \
    .animWaterThrowObj =                    MARIO_ANIM_WATER_THROW_OBJ, \
    .animWaterIdle =                        MARIO_ANIM_WATER_IDLE, \
    .animWaterStarDance =                   MARIO_ANIM_WATER_STAR_DANCE, \
    .animReturnFromWaterStarDance =         MARIO_ANIM_RETURN_FROM_WATER_STAR_DANCE, \
    .animGrabBowser =                       MARIO_ANIM_GRAB_BOWSER, \
    .animSwingingBowser =                   MARIO_ANIM_SWINGING_BOWSER, \
    .animReleaseBowser =                    MARIO_ANIM_RELEASE_BOWSER, \
    .animHoldingBowser =                    MARIO_ANIM_HOLDING_BOWSER, \
    .animHeavyThrow =                       MARIO_ANIM_HEAVY_THROW, \
    .animWalkPanting =                      MARIO_ANIM_WALK_PANTING, \
    .animWalkWithHeavyObj =                 MARIO_ANIM_WALK_WITH_HEAVY_OBJ, \
    .animTurningPart1 =                     MARIO_ANIM_TURNING_PART1, \
    .animTurningPart2 =                     MARIO_ANIM_TURNING_PART2, \
    .animSlideflipLand =                    MARIO_ANIM_SLIDEFLIP_LAND, \
    .animSlideflip =                        MARIO_ANIM_SLIDEFLIP, \
    .animTripleJumpLand =                   MARIO_ANIM_TRIPLE_JUMP_LAND, \
    .animTripleJump =                       MARIO_ANIM_TRIPLE_JUMP, \
    .animFirstPerson =                      MARIO_ANIM_FIRST_PERSON, \
    .animIdleHeadLeft =                     MARIO_ANIM_IDLE_HEAD_LEFT, \
    .animIdleHeadRight =                    MARIO_ANIM_IDLE_HEAD_RIGHT, \
    .animIdleHeadCenter =                   MARIO_ANIM_IDLE_HEAD_CENTER, \
    .animHandstandLeft =                    MARIO_ANIM_HANDSTAND_LEFT, \
    .animHandstandRight =                   MARIO_ANIM_HANDSTAND_RIGHT, \
    .animWakeFromSleep =                    MARIO_ANIM_WAKE_FROM_SLEEP, \
    .animWakeFromLying =                    MARIO_ANIM_WAKE_FROM_LYING, \
    .animStartTiptoe =                      MARIO_ANIM_START_TIPTOE, \
    .animSlidejump =                        MARIO_ANIM_SLIDEJUMP, \
    .animStartWallkick =                    MARIO_ANIM_START_WALLKICK, \
    .animStarDance =                        MARIO_ANIM_STAR_DANCE, \
    .animReturnFromStarDance =              MARIO_ANIM_RETURN_FROM_STAR_DANCE, \
    .animForwardSpinningFlip =              MARIO_ANIM_FORWARD_SPINNING_FLIP, \
    .animTripleJumpFly =                    MARIO_ANIM_TRIPLE_JUMP_FLY \


struct Character {
    enum CharacterType type;
    char* name;
    char hudHead;
    struct TextureInfo hudHeadTexture;
    u32 cameraHudHead;
    u32 modelId;
    u32 capModelId;
    u32 capMetalModelId;
    u32 capWingModelId;
    u32 capMetalWingModelId;
    u8 capEnemyLayer;
    Gfx* capEnemyGfx;
    Gfx* capEnemyDecalGfx;
    f32 torsoRotMult;
    // anim
    u8 animOffsetEnabled;
    f32 animOffsetLowYPoint;
    f32 animOffsetFeet;
    f32 animOffsetHand;

    // anims
    union {
        struct {
            /* 0x00 */s32 animSlowLedgeGrab;
            /* 0x01 */s32 animFallOverBackwards;
            /* 0x02 */s32 animBackwardAirKb;
            /* 0x03 */s32 animDyingOnBack;
            /* 0x04 */s32 animBackflip;
            /* 0x05 */s32 animClimbUpPole;
            /* 0x06 */s32 animGrabPoleShort;
            /* 0x07 */s32 animGrabPoleSwingPart1;
            /* 0x08 */s32 animGrabPoleSwingPart2;
            /* 0x09 */s32 animHandstandIdle;
            /* 0x0a */s32 animHandstandJump;
            /* 0x0b */s32 animStartHandstand;
            /* 0x0c */s32 animReturnFromHandstand;
            /* 0x0d */s32 animIdleOnPole;
            /* 0x0e */s32 animAPose;
            /* 0x0f */s32 animSkidOnGround;
            /* 0x10 */s32 animStopSkid;
            /* 0x11 */s32 animCrouchFromFastLongjump;
            /* 0x12 */s32 animCrouchFromSlowLongjump;
            /* 0x13 */s32 animFastLongjump;
            /* 0x14 */s32 animSlowLongjump;
            /* 0x15 */s32 animAirborneOnStomach;
            /* 0x16 */s32 animWalkWithLightObj;
            /* 0x17 */s32 animRunWithLightObj;
            /* 0x18 */s32 animSlowWalkWithLightObj;
            /* 0x19 */s32 animShiveringWarmingHand;
            /* 0x1a */s32 animShiveringReturnToIdle;
            /* 0x1b */s32 animShivering;
            /* 0x1c */s32 animClimbDownLedge;
            /* 0x1d */s32 animCreditsWaving;
            /* 0x1e */s32 animCreditsLookUp;
            /* 0x1f */s32 animCreditsReturnFromLookUp;
            /* 0x20 */s32 animCreditsRaiseHand;
            /* 0x21 */s32 animCreditsLowerHand;
            /* 0x22 */s32 animCreditsTakeOffCap;
            /* 0x23 */s32 animCreditsStartWalkLookUp;
            /* 0x24 */s32 animCreditsLookBackThenRun;
            /* 0x25 */s32 animFinalBowserRaiseHandSpin;
            /* 0x26 */s32 animFinalBowserWingCapTakeOff;
            /* 0x27 */s32 animCreditsPeaceSign;
            /* 0x28 */s32 animStandUpFromLavaBoost;
            /* 0x29 */s32 animFireLavaBurn;
            /* 0x2a */s32 animWingCapFly;
            /* 0x2b */s32 animHangOnOwl;
            /* 0x2c */s32 animLandOnStomach;
            /* 0x2d */s32 animAirForwardKb;
            /* 0x2e */s32 animDyingOnStomach;
            /* 0x2f */s32 animSuffocating;
            /* 0x30 */s32 animCoughing;
            /* 0x31 */s32 animThrowCatchKey;
            /* 0x32 */s32 animDyingFallOver;
            /* 0x33 */s32 animIdleOnLedge;
            /* 0x34 */s32 animFastLedgeGrab;
            /* 0x35 */s32 animHangOnCeiling;
            /* 0x36 */s32 animPutCapOn;
            /* 0x37 */s32 animTakeCapOffThenOn;
            /* 0x38 */s32 animQuicklyPutCapOn;
            /* 0x39 */s32 animHeadStuckInGround;
            /* 0x3a */s32 animGroundPoundLanding;
            /* 0x3b */s32 animTripleJumpGroundPound;
            /* 0x3c */s32 animStartGroundPound;
            /* 0x3d */s32 animGroundPound;
            /* 0x3e */s32 animBottomStuckInGround;
            /* 0x3f */s32 animIdleWithLightObj;
            /* 0x40 */s32 animJumpLandWithLightObj;
            /* 0x41 */s32 animJumpWithLightObj;
            /* 0x42 */s32 animFallLandWithLightObj;
            /* 0x43 */s32 animFallWithLightObj;
            /* 0x44 */s32 animFallFromSlidingWithLightObj;
            /* 0x45 */s32 animSlidingOnBottomWithLightObj;
            /* 0x46 */s32 animStandUpFromSlidingWithLightObj;
            /* 0x47 */s32 animRidingShell;
            /* 0x48 */s32 animWalking;
            /* 0x49 */s32 animForwardFlip;
            /* 0x4a */s32 animJumpRidingShell;
            /* 0x4b */s32 animLandFromDoubleJump;
            /* 0x4c */s32 animDoubleJumpFall;
            /* 0x4d */s32 animSingleJump;
            /* 0x4e */s32 animLandFromSingleJump;
            /* 0x4f */s32 animAirKick;
            /* 0x50 */s32 animDoubleJumpRise;
            /* 0x51 */s32 animStartForwardSpinning;
            /* 0x52 */s32 animThrowLightObject;
            /* 0x53 */s32 animFallFromSlideKick;
            /* 0x54 */s32 animBendKnessRidingShell;
            /* 0x55 */s32 animLegsStuckInGround;
            /* 0x56 */s32 animGeneralFall;
            /* 0x57 */s32 animGeneralLand;
            /* 0x58 */s32 animBeingGrabbed;
            /* 0x59 */s32 animGrabHeavyObject;
            /* 0x5a */s32 animSlowLandFromDive;
            /* 0x5b */s32 animFlyFromCannon;
            /* 0x5c */s32 animMoveOnWireNetRight;
            /* 0x5d */s32 animMoveOnWireNetLeft;
            /* 0x5e */s32 animMissingCap;
            /* 0x5f */s32 animPullDoorWalkIn;
            /* 0x60 */s32 animPushDoorWalkIn;
            /* 0x61 */s32 animUnlockDoor;
            /* 0x62 */s32 animStartReachPocket;
            /* 0x63 */s32 animReachPocket;
            /* 0x64 */s32 animStopReachPocket;
            /* 0x65 */s32 animGroundThrow;
            /* 0x66 */s32 animGroundKick;
            /* 0x67 */s32 animFirstPunch;
            /* 0x68 */s32 animSecondPunch;
            /* 0x69 */s32 animFirstPunchFast;
            /* 0x6a */s32 animSecondPunchFast;
            /* 0x6b */s32 animPickUpLightObj;
            /* 0x6c */s32 animPushing;
            /* 0x6d */s32 animStartRidingShell;
            /* 0x6e */s32 animPlaceLightObj;
            /* 0x6f */s32 animForwardSpinning;
            /* 0x70 */s32 animBackwardSpinning;
            /* 0x71 */s32 animBreakdance;
            /* 0x72 */s32 animRunning;
            /* 0x73 */s32 animRunningUnused;
            /* 0x74 */s32 animSoftBackKb;
            /* 0x75 */s32 animSoftFrontKb;
            /* 0x76 */s32 animDyingInQuicksand;
            /* 0x77 */s32 animIdleInQuicksand;
            /* 0x78 */s32 animMoveInQuicksand;
            /* 0x79 */s32 animElectrocution;
            /* 0x7a */s32 animShocked;
            /* 0x7b */s32 animBackwardKb;
            /* 0x7c */s32 animForwardKb;
            /* 0x7d */s32 animIdleHeavyObj;
            /* 0x7e */s32 animStandAgainstWall;
            /* 0x7f */s32 animSidestepLeft;
            /* 0x80 */s32 animSidestepRight;
            /* 0x81 */s32 animStartSleepIdle;
            /* 0x82 */s32 animStartSleepScratch;
            /* 0x83 */s32 animStartSleepYawn;
            /* 0x84 */s32 animStartSleepSitting;
            /* 0x85 */s32 animSleepIdle;
            /* 0x86 */s32 animSleepStartLying;
            /* 0x87 */s32 animSleepLying;
            /* 0x88 */s32 animDive;
            /* 0x89 */s32 animSlideDive;
            /* 0x8a */s32 animGroundBonk;
            /* 0x8b */s32 animStopSlideLightObj;
            /* 0x8c */s32 animSlideKick;
            /* 0x8d */s32 animCrouchFromSlideKick;
            /* 0x8e */s32 animSlideMotionless;
            /* 0x8f */s32 animStopSlide;
            /* 0x90 */s32 animFallFromSlide;
            /* 0x91 */s32 animSlide;
            /* 0x92 */s32 animTiptoe;
            /* 0x93 */s32 animTwirlLand;
            /* 0x94 */s32 animTwirl;
            /* 0x95 */s32 animStartTwirl;
            /* 0x96 */s32 animStopCrouching;
            /* 0x97 */s32 animStartCrouching;
            /* 0x98 */s32 animCrouching;
            /* 0x99 */s32 animCrawling;
            /* 0x9a */s32 animStopCrawling;
            /* 0x9b */s32 animStartCrawling;
            /* 0x9c */s32 animSummonStar;
            /* 0x9d */s32 animReturnStarApproachDoor;
            /* 0x9e */s32 animBackwardsWaterKb;
            /* 0x9f */s32 animSwimWithObjPart1;
            /* 0xa0 */s32 animSwimWithObjPart2;
            /* 0xa1 */s32 animFlutterkickWithObj;
            /* 0xa2 */s32 animWaterActionEndWithObj;
            /* 0xa3 */s32 animStopGrabObjWater;
            /* 0xa4 */s32 animWaterIdleWithObj;
            /* 0xa5 */s32 animDrowningPart1;
            /* 0xa6 */s32 animDrowningPart2;
            /* 0xa7 */s32 animWaterDying;
            /* 0xa8 */s32 animWaterForwardKb;
            /* 0xa9 */s32 animFallFromWater;
            /* 0xaa */s32 animSwimPart1;
            /* 0xab */s32 animSwimPart2;
            /* 0xac */s32 animFlutterkick;
            /* 0xad */s32 animWaterActionEnd;
            /* 0xae */s32 animWaterPickUpObj;
            /* 0xaf */s32 animWaterGrabObjPart2;
            /* 0xb0 */s32 animWaterGrabObjPart1;
            /* 0xb1 */s32 animWaterThrowObj;
            /* 0xb2 */s32 animWaterIdle;
            /* 0xb3 */s32 animWaterStarDance;
            /* 0xb4 */s32 animReturnFromWaterStarDance;
            /* 0xb5 */s32 animGrabBowser;
            /* 0xb6 */s32 animSwingingBowser;
            /* 0xb7 */s32 animReleaseBowser;
            /* 0xb8 */s32 animHoldingBowser;
            /* 0xb9 */s32 animHeavyThrow;
            /* 0xba */s32 animWalkPanting;
            /* 0xbb */s32 animWalkWithHeavyObj;
            /* 0xbc */s32 animTurningPart1;
            /* 0xbd */s32 animTurningPart2;
            /* 0xbe */s32 animSlideflipLand;
            /* 0xbf */s32 animSlideflip;
            /* 0xc0 */s32 animTripleJumpLand;
            /* 0xc1 */s32 animTripleJump;
            /* 0xc2 */s32 animFirstPerson;
            /* 0xc3 */s32 animIdleHeadLeft;
            /* 0xc4 */s32 animIdleHeadRight;
            /* 0xc5 */s32 animIdleHeadCenter;
            /* 0xc6 */s32 animHandstandLeft;
            /* 0xc7 */s32 animHandstandRight;
            /* 0xc8 */s32 animWakeFromSleep;
            /* 0xc9 */s32 animWakeFromLying;
            /* 0xca */s32 animStartTiptoe;
            /* 0xcb */s32 animSlidejump;
            /* 0xcc */s32 animStartWallkick;
            /* 0xcd */s32 animStarDance;
            /* 0xce */s32 animReturnFromStarDance;
            /* 0xcf */s32 animForwardSpinningFlip;
            /* 0xd0 */s32 animTripleJumpFly;
        };
        s32 anims[CHAR_ANIM_MAX];
    };

    // sounds
    f32 soundFreqScale;
    union {
        struct {
            s32 soundYahWahHoo;
            s32 soundHoohoo;
            s32 soundYahoo;
            s32 soundUh;
            s32 soundHrmm;
            s32 soundWah2;
            s32 soundWhoa;
            s32 soundEeuh;
            s32 soundAttacked;
            s32 soundOoof;
            s32 soundOoof2;
            s32 soundHereWeGo;
            s32 soundYawning;
            s32 soundSnoring1;
            s32 soundSnoring2;
            s32 soundWaaaooow;
            s32 soundHaha;
            s32 soundHaha_2;
            s32 soundUh2;
            s32 soundUh2_2;
            s32 soundOnFire;
            s32 soundDying;
            s32 soundPantingCold;
            s32 soundPanting;
            s32 soundCoughing1;
            s32 soundCoughing2;
            s32 soundCoughing3;
            s32 soundPunchYah;
            s32 soundPunchHoo;
            s32 soundMamaMia;
            s32 soundGroundPoundWah;
            s32 soundDrowning;
            s32 soundPunchWah;
            s32 soundYahooWahaYippee;
            s32 soundDoh;
            s32 soundGameOver;
            s32 soundHello;
            s32 soundPressStartToPlay;
            s32 soundTwirlBounce;
            s32 soundSnoring3;
            s32 soundSoLongaBowser;
            s32 soundImaTired;
            s32 soundLetsAGo;
            s32 soundOkeyDokey;
        };
        s32 sounds[CHAR_SOUND_MAX];
    };
};

struct MarioState;
extern struct Character gCharacters[];
struct Character* get_character(struct MarioState* m);

void play_character_sound(struct MarioState* m, enum CharacterSound characterSound);
void play_character_sound_offset(struct MarioState* m, enum CharacterSound characterSound, u32 offset);
void play_character_sound_if_no_flag(struct MarioState* m, enum CharacterSound characterSound, u32 flags);

f32 get_character_anim_offset(struct MarioState* m);
s32 get_character_anim(struct MarioState* m, enum CharacterAnimID characterAnim);
void update_character_anim_offset(struct MarioState* m);

#endif // CHARACTERS_H
