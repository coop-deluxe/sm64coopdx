#include "dynos.cpp.h"

#define OBJECT_FIELDS_INDEX_DIRECTLY

extern "C" {
#include "include/behavior_commands.h"
#include "include/behavior_data.h"
#include "include/behavior_table.h"
#include "include/model_ids.h"
#include "include/object_constants.h"
#include "include/object_fields.h"
#include "src/game/area.h"
#include "src/game/object_list_processor.h"
#include "src/game/interaction.h"
#include "src/pc/lua/utils/smlua_anim_utils.h"
#include "src/pc/lua/utils/smlua_collision_utils.h"

// Models and Animations
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/custom0.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "actors/zcustom0.h"
#include "levels/castle_grounds/header.h"
}

// Current Behavior Version
#define BEHAVIOR_MAJOR_VER 1
#define BEHAVIOR_MINOR_VER 0
#define BEHAVIOR_PATCH_VER 0

// Minimum Behavior Version (That can be read)
#define BEHAVIOR_MIN_MAJOR_VER 1
#define BEHAVIOR_MIN_MINOR_VER 0
#define BEHAVIOR_MIN_PATCH_VER 0

#undef OBJECT_FIELDS_INDEX_DIRECTLY

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
void ClearBhvDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

  /////////////
 // Parsing //
/////////////

#define BEHAVIOR_SCRIPT_SIZE_PER_TOKEN 4

#define bhv_constant(x) if (_Arg == #x) { return (BehaviorScript) (x); }
#define bhv_legacy_constant(x, y) if (_Arg == #x) { return (BehaviorScript) (y); }

s64 DynOS_Bhv_ParseBehaviorIntegerScriptConstants(const String &_Arg, bool *found) {
    *found = true;
    
    // All of these eveluate down into a integer which can be worked with.
    // Be it for flags or otherwise.
    
    // Active Flags
    bhv_constant(ACTIVE_FLAG_DEACTIVATED);
    bhv_constant(ACTIVE_FLAG_ACTIVE);
    bhv_constant(ACTIVE_FLAG_FAR_AWAY);
    bhv_constant(ACTIVE_FLAG_UNK2);
    bhv_constant(ACTIVE_FLAG_IN_DIFFERENT_ROOM);
    bhv_constant(ACTIVE_FLAG_UNIMPORTANT);
    bhv_constant(ACTIVE_FLAG_INITIATED_TIME_STOP);
    bhv_constant(ACTIVE_FLAG_MOVE_THROUGH_GRATE);
    bhv_constant(ACTIVE_FLAG_DITHERED_ALPHA);
    bhv_constant(ACTIVE_FLAG_UNK8);
    bhv_constant(ACTIVE_FLAG_UNK9);
    bhv_constant(ACTIVE_FLAG_UNK10);


    // Interact Flags
    bhv_constant(INTERACT_HOOT);
    bhv_constant(INTERACT_GRABBABLE);
    bhv_constant(INTERACT_DOOR);
    bhv_constant(INTERACT_DAMAGE);
    bhv_constant(INTERACT_COIN);
    bhv_constant(INTERACT_CAP);
    bhv_constant(INTERACT_POLE);
    bhv_constant(INTERACT_KOOPA);
    bhv_constant(INTERACT_UNKNOWN_08);
    bhv_constant(INTERACT_BREAKABLE);
    bhv_constant(INTERACT_STRONG_WIND);
    bhv_constant(INTERACT_WARP_DOOR);
    bhv_constant(INTERACT_STAR_OR_KEY);
    bhv_constant(INTERACT_WARP);
    bhv_constant(INTERACT_CANNON_BASE);
    bhv_constant(INTERACT_BOUNCE_TOP);
    bhv_constant(INTERACT_WATER_RING);
    bhv_constant(INTERACT_BULLY);
    bhv_constant(INTERACT_FLAME);
    bhv_constant(INTERACT_KOOPA_SHELL);
    bhv_constant(INTERACT_BOUNCE_TOP2);
    bhv_constant(INTERACT_MR_BLIZZARD);
    bhv_constant(INTERACT_HIT_FROM_BELOW);
    bhv_constant(INTERACT_TEXT);
    bhv_constant(INTERACT_TORNADO);
    bhv_constant(INTERACT_WHIRLPOOL);
    bhv_constant(INTERACT_CLAM_OR_BUBBA);
    bhv_constant(INTERACT_BBH_ENTRANCE);
    bhv_constant(INTERACT_SNUFIT_BULLET);
    bhv_constant(INTERACT_SHOCK);
    bhv_constant(INTERACT_IGLOO_BARRIER);
    bhv_constant(INTERACT_PLAYER);

    
    // Interact Subtype Flags
    
    // INTERACT_WARP
    bhv_constant(INT_SUBTYPE_FADING_WARP);

    // Damaging interactions
    bhv_constant(INT_SUBTYPE_DELAY_INVINCIBILITY);
    bhv_constant(INT_SUBTYPE_BIG_KNOCKBACK); /* Used by Bowser, sets Mario's forward velocity to 40 on hit */

    // INTERACT_GRABBABLE
    bhv_constant(INT_SUBTYPE_GRABS_MARIO); /* Also makes the object heavy */
    bhv_constant(INT_SUBTYPE_HOLDABLE_NPC); /* Allows the object to be gently dropped, and sets vertical speed to 0 when dropped with no forwards velocity */
    bhv_constant(INT_SUBTYPE_DROP_IMMEDIATELY); /* This gets set by grabbable NPCs that talk to Mario to make him drop them after the dialog is finished */
    bhv_constant(INT_SUBTYPE_KICKABLE);
    bhv_constant(INT_SUBTYPE_NOT_GRABBABLE); /* Used by Heavy-Ho to allow it to throw Mario, without Mario being able to pick it up */

    // INTERACT_DOOR
    bhv_constant(INT_SUBTYPE_STAR_DOOR);

    //INTERACT_BOUNCE_TOP
    bhv_constant(INT_SUBTYPE_TWIRL_BOUNCE);

    // INTERACT_STAR_OR_KEY
    bhv_constant(INT_SUBTYPE_NO_EXIT);
    bhv_constant(INT_SUBTYPE_GRAND_STAR);

    // INTERACT_TEXT
    bhv_constant(INT_SUBTYPE_SIGN);
    bhv_constant(INT_SUBTYPE_NPC);

    // INTERACT_CLAM_OR_BUBBA
    bhv_constant(INT_SUBTYPE_EATS_MARIO);


    // Object List Types
    bhv_constant(OBJ_LIST_PLAYER);
    bhv_constant(OBJ_LIST_UNUSED_1);
    bhv_constant(OBJ_LIST_DESTRUCTIVE);
    bhv_constant(OBJ_LIST_UNUSED_3);
    bhv_constant(OBJ_LIST_GENACTOR);
    bhv_constant(OBJ_LIST_PUSHABLE);
    bhv_constant(OBJ_LIST_LEVEL);
    bhv_constant(OBJ_LIST_UNUSED_7);
    bhv_constant(OBJ_LIST_DEFAULT);
    bhv_constant(OBJ_LIST_SURFACE);
    bhv_constant(OBJ_LIST_POLELIKE);
    bhv_constant(OBJ_LIST_SPAWNER);
    bhv_constant(OBJ_LIST_UNIMPORTANT);


    // Object Flags
    bhv_constant(OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE);
    bhv_constant(OBJ_FLAG_MOVE_XZ_USING_FVEL);
    bhv_constant(OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL);
    bhv_constant(OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW);
    bhv_constant(OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE);
    bhv_constant(OBJ_FLAG_0020);
    bhv_constant(OBJ_FLAG_COMPUTE_DIST_TO_MARIO);
    bhv_constant(OBJ_FLAG_ACTIVE_FROM_AFAR);
    bhv_constant(OBJ_FLAG_0100);
    bhv_constant(OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT);
    bhv_constant(OBJ_FLAG_HOLDABLE);
    bhv_constant(OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM);
    bhv_constant(OBJ_FLAG_1000);
    bhv_constant(OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO);
    bhv_constant(OBJ_FLAG_PERSISTENT_RESPAWN);
    bhv_constant(OBJ_FLAG_8000);
    bhv_constant(OBJ_FLAG_30);


    // Particle Flags
    bhv_constant(ACTIVE_PARTICLE_DUST);
    bhv_constant(ACTIVE_PARTICLE_UNUSED_1);
    bhv_constant(ACTIVE_PARTICLE_UNUSED_2);
    bhv_constant(ACTIVE_PARTICLE_SPARKLES);
    bhv_constant(ACTIVE_PARTICLE_H_STAR);
    bhv_constant(ACTIVE_PARTICLE_BUBBLE);
    bhv_constant(ACTIVE_PARTICLE_WATER_SPLASH);
    bhv_constant(ACTIVE_PARTICLE_IDLE_WATER_WAVE);
    bhv_constant(ACTIVE_PARTICLE_SHALLOW_WATER_WAVE);
    bhv_constant(ACTIVE_PARTICLE_PLUNGE_BUBBLE);
    bhv_constant(ACTIVE_PARTICLE_WAVE_TRAIL);
    bhv_constant(ACTIVE_PARTICLE_FIRE);
    bhv_constant(ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH);
    bhv_constant(ACTIVE_PARTICLE_LEAF);
    bhv_constant(ACTIVE_PARTICLE_DIRT);
    bhv_constant(ACTIVE_PARTICLE_MIST_CIRCLE);
    bhv_constant(ACTIVE_PARTICLE_SNOW);
    bhv_constant(ACTIVE_PARTICLE_BREATH);
    bhv_constant(ACTIVE_PARTICLE_V_STAR);
    bhv_constant(ACTIVE_PARTICLE_TRIANGLE);
    
    // Other constants
    bhv_constant(NULL);
    bhv_constant(FALSE);
    
    *found = false;
    return 0;
}

s64 DynOS_Bhv_ParseBehaviorScriptConstants(const String &_Arg, bool *found) {
    *found = true;
    
    // Behavior names
    bhv_constant(bhvStarDoor);
    bhv_constant(bhvMrI);
    bhv_constant(bhvMrIBody);
    bhv_constant(bhvMrIParticle);
    bhv_constant(bhvPurpleParticle);
    bhv_constant(bhvGiantPole);
    bhv_constant(bhvPoleGrabbing);
    bhv_constant(bhvThiHugeIslandTop);
    bhv_constant(bhvThiTinyIslandTop);
    bhv_constant(bhvCapSwitchBase);
    bhv_constant(bhvCapSwitch);
    bhv_constant(bhvKingBobomb);
    bhv_constant(bhvBobombAnchorMario);
    bhv_constant(bhvBetaChestBottom);
    bhv_constant(bhvBetaChestLid);
    bhv_constant(bhvBubbleParticleSpawner);
    bhv_constant(bhvBubbleMaybe);
    bhv_constant(bhvBubblePlayer);
    bhv_constant(bhvSmallWaterWave);
    bhv_constant(bhvSmallWaterWave398);
    bhv_constant(bhvWaterAirBubble);
    bhv_constant(bhvSmallParticle);
    bhv_constant(bhvPlungeBubble);
    bhv_constant(bhvSmallParticleSnow);
    bhv_constant(bhvSmallParticleBubbles);
    bhv_constant(bhvFishGroup);
    bhv_constant(bhvCannon);
    bhv_constant(bhvCannonBarrel);
    bhv_constant(bhvCannonBaseUnused);
    bhv_constant(bhvChuckya);
    bhv_constant(bhvChuckyaAnchorMario);
    bhv_constant(bhvUnused05A8);
    bhv_constant(bhvRotatingPlatform);
    bhv_constant(bhvTower);
    bhv_constant(bhvBulletBillCannon);
    bhv_constant(bhvWfBreakableWallRight);
    bhv_constant(bhvWfBreakableWallLeft);
    bhv_constant(bhvKickableBoard);
    bhv_constant(bhvTowerDoor);
    bhv_constant(bhvRotatingCounterClockwise);
    bhv_constant(bhvWfRotatingWoodenPlatform);
    bhv_constant(bhvKoopaShellUnderwater);
    bhv_constant(bhvExitPodiumWarp);
    bhv_constant(bhvFadingWarp);
    bhv_constant(bhvWarp);
    bhv_constant(bhvWarpPipe);
    bhv_constant(bhvWhitePuffExplosion);
    bhv_constant(bhvSpawnedStar);
    bhv_constant(bhvSpawnedStarNoLevelExit);
    bhv_constant(bhvMrIBlueCoin);
    bhv_constant(bhvCoinInsideBoo);
    bhv_constant(bhvCoinFormationSpawn);
    bhv_constant(bhvCoinFormation);
    bhv_constant(bhvOneCoin);
    bhv_constant(bhvYellowCoin);
    bhv_constant(bhvTemporaryYellowCoin);
    bhv_constant(bhvThreeCoinsSpawn);
    bhv_constant(bhvTenCoinsSpawn);
    bhv_constant(bhvSingleCoinGetsSpawned);
    bhv_constant(bhvCoinSparkles);
    bhv_constant(bhvGoldenCoinSparkles);
    bhv_constant(bhvWallTinyStarParticle);
    bhv_constant(bhvVertStarParticleSpawner);
    bhv_constant(bhvPoundTinyStarParticle);
    bhv_constant(bhvHorStarParticleSpawner);
    bhv_constant(bhvPunchTinyTriangle);
    bhv_constant(bhvTriangleParticleSpawner);
    bhv_constant(bhvDoorWarp);
    bhv_constant(bhvDoor);
    bhv_constant(bhvGrindel);
    bhv_constant(bhvThwomp2);
    bhv_constant(bhvThwomp);
    bhv_constant(bhvTumblingBridgePlatform);
    bhv_constant(bhvWfTumblingBridge);
    bhv_constant(bhvBbhTumblingBridge);
    bhv_constant(bhvLllTumblingBridge);
    bhv_constant(bhvFlame);
    bhv_constant(bhvAnotherElavator);
    bhv_constant(bhvRrElevatorPlatform);
    bhv_constant(bhvHmcElevatorPlatform);
    bhv_constant(bhvWaterMist);
    bhv_constant(bhvBreathParticleSpawner);
    bhv_constant(bhvBreakBoxTriangle);
    bhv_constant(bhvWaterMist2);
    bhv_constant(bhvUnused0DFC);
    bhv_constant(bhvMistCircParticleSpawner);
    bhv_constant(bhvDirtParticleSpawner);
    bhv_constant(bhvSnowParticleSpawner);
    bhv_constant(bhvWind);
    bhv_constant(bhvEndToad);
    bhv_constant(bhvEndPeach);
    bhv_constant(bhvUnusedParticleSpawn);
    bhv_constant(bhvUkiki);
    bhv_constant(bhvUkikiCageChild);
    bhv_constant(bhvUkikiCageStar);
    bhv_constant(bhvUkikiCage);
    bhv_constant(bhvBitfsSinkingPlatforms);
    bhv_constant(bhvBitfsSinkingCagePlatform);
    bhv_constant(bhvDddMovingPole);
    bhv_constant(bhvBitfsTiltingInvertedPyramid);
    bhv_constant(bhvSquishablePlatform);
    bhv_constant(bhvCutOutObject);
    bhv_constant(bhvBetaMovingFlamesSpawn);
    bhv_constant(bhvBetaMovingFlames);
    bhv_constant(bhvRrRotatingBridgePlatform);
    bhv_constant(bhvFlamethrower);
    bhv_constant(bhvFlamethrowerFlame);
    bhv_constant(bhvBouncingFireball);
    bhv_constant(bhvBouncingFireballFlame);
    bhv_constant(bhvBowserShockWave);
    bhv_constant(bhvFireParticleSpawner);
    bhv_constant(bhvBlackSmokeMario);
    bhv_constant(bhvBlackSmokeBowser);
    bhv_constant(bhvBlackSmokeUpward);
    bhv_constant(bhvBetaFishSplashSpawner);
    bhv_constant(bhvSpindrift);
    bhv_constant(bhvTowerPlatformGroup);
    bhv_constant(bhvWfSlidingTowerPlatform);
    bhv_constant(bhvWfElevatorTowerPlatform);
    bhv_constant(bhvWfSolidTowerPlatform);
    bhv_constant(bhvLeafParticleSpawner);
    bhv_constant(bhvTreeSnow);
    bhv_constant(bhvTreeLeaf);
    bhv_constant(bhvAnotherTiltingPlatform);
    bhv_constant(bhvSquarishPathMoving);
    bhv_constant(bhvSquarishPathParent);
    bhv_constant(bhvPiranhaPlantBubble);
    bhv_constant(bhvPiranhaPlantWakingBubbles);
    bhv_constant(bhvFloorSwitchAnimatesObject);
    bhv_constant(bhvFloorSwitchGrills);
    bhv_constant(bhvFloorSwitchHardcodedModel);
    bhv_constant(bhvFloorSwitchHiddenObjects);
    bhv_constant(bhvHiddenObject);
    bhv_constant(bhvBreakableBox);
    bhv_constant(bhvPushableMetalBox);
    bhv_constant(bhvHeaveHo);
    bhv_constant(bhvHeaveHoThrowMario);
    bhv_constant(bhvCcmTouchedStarSpawn);
    bhv_constant(bhvUnusedPoundablePlatform);
    bhv_constant(bhvBetaTrampolineTop);
    bhv_constant(bhvBetaTrampolineSpring);
    bhv_constant(bhvJumpingBox);
    bhv_constant(bhvBooCage);
    bhv_constant(bhvStub);
    bhv_constant(bhvIgloo);
    bhv_constant(bhvBowserKey);
    bhv_constant(bhvGrandStar);
    bhv_constant(bhvBetaBooKey);
    bhv_constant(bhvAlphaBooKey);
    bhv_constant(bhvBulletBill);
    bhv_constant(bhvWhitePuffSmoke);
    bhv_constant(bhvUnused1820);
    bhv_constant(bhvBowserTailAnchor);
    bhv_constant(bhvBowser);
    bhv_constant(bhvBowserBodyAnchor);
    bhv_constant(bhvBowserFlameSpawn);
    bhv_constant(bhvTiltingBowserLavaPlatform);
    bhv_constant(bhvFallingBowserPlatform);
    bhv_constant(bhvBlueBowserFlame);
    bhv_constant(bhvFlameFloatingLanding);
    bhv_constant(bhvBlueFlamesGroup);
    bhv_constant(bhvFlameBouncing);
    bhv_constant(bhvFlameMovingForwardGrowing);
    bhv_constant(bhvFlameBowser);
    bhv_constant(bhvFlameLargeBurningOut);
    bhv_constant(bhvBlueFish);
    bhv_constant(bhvTankFishGroup);
    bhv_constant(bhvCheckerboardElevatorGroup);
    bhv_constant(bhvCheckerboardPlatformSub);
    bhv_constant(bhvBowserKeyUnlockDoor);
    bhv_constant(bhvBowserKeyCourseExit);
    bhv_constant(bhvInvisibleObjectsUnderBridge);
    bhv_constant(bhvWaterLevelPillar);
    bhv_constant(bhvDddWarp);
    bhv_constant(bhvMoatGrills);
    bhv_constant(bhvClockMinuteHand);
    bhv_constant(bhvClockHourHand);
    bhv_constant(bhvMacroUkiki);
    bhv_constant(bhvStub1D0C);
    bhv_constant(bhvLllRotatingHexagonalPlatform);
    bhv_constant(bhvLllSinkingRockBlock);
    bhv_constant(bhvStub1D70);
    bhv_constant(bhvLllMovingOctagonalMeshPlatform);
    bhv_constant(bhvSnowBall);
    bhv_constant(bhvLllRotatingBlockWithFireBars);
    bhv_constant(bhvLllRotatingHexFlame);
    bhv_constant(bhvLllWoodPiece);
    bhv_constant(bhvLllFloatingWoodBridge);
    bhv_constant(bhvVolcanoFlames);
    bhv_constant(bhvLllRotatingHexagonalRing);
    bhv_constant(bhvLllSinkingRectangularPlatform);
    bhv_constant(bhvLllSinkingSquarePlatforms);
    bhv_constant(bhvLllTiltingInvertedPyramid);
    bhv_constant(bhvUnused1F30);
    bhv_constant(bhvKoopaShell);
    bhv_constant(bhvKoopaShellFlame);
    bhv_constant(bhvToxBox);
    bhv_constant(bhvPiranhaPlant);
    bhv_constant(bhvLllHexagonalMesh);
    bhv_constant(bhvLllBowserPuzzlePiece);
    bhv_constant(bhvLllBowserPuzzle);
    bhv_constant(bhvTuxiesMother);
    bhv_constant(bhvPenguinBaby);
    bhv_constant(bhvUnused20E0);
    bhv_constant(bhvSmallPenguin);
    bhv_constant(bhvManyBlueFishSpawner);
    bhv_constant(bhvFewBlueFishSpawner);
    bhv_constant(bhvFishSpawner);
    bhv_constant(bhvFish);
    bhv_constant(bhvWdwExpressElevator);
    bhv_constant(bhvWdwExpressElevatorPlatform);
    bhv_constant(bhvChirpChirp);
    bhv_constant(bhvChirpChirpUnused);
    bhv_constant(bhvBub);
    bhv_constant(bhvExclamationBox);
    bhv_constant(bhvRotatingExclamationMark);
    bhv_constant(bhvSoundSpawner);
    bhv_constant(bhvRockSolid);
    bhv_constant(bhvBowserSubDoor);
    bhv_constant(bhvBowsersSub);
    bhv_constant(bhvSushiShark);
    bhv_constant(bhvSushiSharkCollisionChild);
    bhv_constant(bhvJrbSlidingBox);
    bhv_constant(bhvShipPart3);
    bhv_constant(bhvInSunkenShip3);
    bhv_constant(bhvSunkenShipPart);
    bhv_constant(bhvSunkenShipSetRotation);
    bhv_constant(bhvSunkenShipPart2);
    bhv_constant(bhvInSunkenShip);
    bhv_constant(bhvInSunkenShip2);
    bhv_constant(bhvMistParticleSpawner);
    bhv_constant(bhvWhitePuff1);
    bhv_constant(bhvWhitePuff2);
    bhv_constant(bhvWhitePuffSmoke2);
    bhv_constant(bhvPurpleSwitchHiddenBoxes);
    bhv_constant(bhvBlueCoinSwitch);
    bhv_constant(bhvHiddenBlueCoin);
    bhv_constant(bhvOpenableCageDoor);
    bhv_constant(bhvOpenableGrill);
    bhv_constant(bhvWaterLevelDiamond);
    bhv_constant(bhvInitializeChangingWaterLevel);
    bhv_constant(bhvTweesterSandParticle);
    bhv_constant(bhvTweester);
    bhv_constant(bhvMerryGoRoundBooManager);
    bhv_constant(bhvPlaysMusicTrackWhenTouched);
    bhv_constant(bhvAnimatedTexture);
    bhv_constant(bhvBooInCastle);
    bhv_constant(bhvBooWithCage);
    bhv_constant(bhvBalconyBigBoo);
    bhv_constant(bhvMerryGoRoundBigBoo);
    bhv_constant(bhvGhostHuntBigBoo);
    bhv_constant(bhvCourtyardBooTriplet);
    bhv_constant(bhvBoo);
    bhv_constant(bhvMerryGoRoundBoo);
    bhv_constant(bhvGhostHuntBoo);
    bhv_constant(bhvHiddenStaircaseStep);
    bhv_constant(bhvBooBossSpawnedBridge);
    bhv_constant(bhvBbhTiltingTrapPlatform);
    bhv_constant(bhvHauntedBookshelf);
    bhv_constant(bhvMeshElevator);
    bhv_constant(bhvMerryGoRound);
    bhv_constant(bhvInsideCannon);
    bhv_constant(bhvBetaBowserAnchor);
    bhv_constant(bhvStaticCheckeredPlatform);
    bhv_constant(bhvUnused2A10);
    bhv_constant(bhvStar);
    bhv_constant(bhvStaticObject);
    bhv_constant(bhvUnused2A54);
    bhv_constant(bhvCastleFloorTrap);
    bhv_constant(bhvFloorTrapInCastle);
    bhv_constant(bhvTree);
    bhv_constant(bhvSparkle);
    bhv_constant(bhvSparkleSpawn);
    bhv_constant(bhvSparkleParticleSpawner);
    bhv_constant(bhvScuttlebug);
    bhv_constant(bhvScuttlebugSpawn);
    bhv_constant(bhvWhompKingBoss);
    bhv_constant(bhvSmallWhomp);
    bhv_constant(bhvWaterSplash);
    bhv_constant(bhvWaterDroplet);
    bhv_constant(bhvWaterDropletSplash);
    bhv_constant(bhvBubbleSplash);
    bhv_constant(bhvIdleWaterWave);
    bhv_constant(bhvObjectWaterSplash);
    bhv_constant(bhvShallowWaterWave);
    bhv_constant(bhvShallowWaterSplash);
    bhv_constant(bhvObjectWaveTrail);
    bhv_constant(bhvWaveTrail);
    bhv_constant(bhvTinyStrongWindParticle);
    bhv_constant(bhvStrongWindParticle);
    bhv_constant(bhvSLSnowmanWind);
    bhv_constant(bhvSLWalkingPenguin);
    bhv_constant(bhvYellowBall);
    bhv_constant(bhvMario);
    bhv_constant(bhvToadMessage);
    bhv_constant(bhvUnlockDoorStar);
    bhv_constant(bhvInstantActiveWarp);
    bhv_constant(bhvAirborneWarp);
    bhv_constant(bhvHardAirKnockBackWarp);
    bhv_constant(bhvSpinAirborneCircleWarp);
    bhv_constant(bhvDeathWarp);
    bhv_constant(bhvSpinAirborneWarp);
    bhv_constant(bhvFlyingWarp);
    bhv_constant(bhvPaintingStarCollectWarp);
    bhv_constant(bhvPaintingDeathWarp);
    bhv_constant(bhvAirborneDeathWarp);
    bhv_constant(bhvAirborneStarCollectWarp);
    bhv_constant(bhvLaunchStarCollectWarp);
    bhv_constant(bhvLaunchDeathWarp);
    bhv_constant(bhvSwimmingWarp);
    bhv_constant(bhvRandomAnimatedTexture);
    bhv_constant(bhvYellowBackgroundInMenu);
    bhv_constant(bhvMenuButton);
    bhv_constant(bhvMenuButtonManager);
    bhv_constant(bhvActSelectorStarType);
    bhv_constant(bhvActSelector);
    bhv_constant(bhvMovingYellowCoin);
    bhv_constant(bhvMovingBlueCoin);
    bhv_constant(bhvBlueCoinSliding);
    bhv_constant(bhvBlueCoinJumping);
    bhv_constant(bhvSeaweed);
    bhv_constant(bhvSeaweedBundle);
    bhv_constant(bhvBobomb);
    bhv_constant(bhvBobombFuseSmoke);
    bhv_constant(bhvBobombBuddy);
    bhv_constant(bhvBobombBuddyOpensCannon);
    bhv_constant(bhvCannonClosed);
    bhv_constant(bhvWhirlpool);
    bhv_constant(bhvJetStream);
    bhv_constant(bhvMessagePanel);
    bhv_constant(bhvSignOnWall);
    bhv_constant(bhvHomingAmp);
    bhv_constant(bhvCirclingAmp);
    bhv_constant(bhvButterfly);
    bhv_constant(bhvHoot);
    bhv_constant(bhvBetaHoldableObject);
    bhv_constant(bhvCarrySomething1);
    bhv_constant(bhvCarrySomething2);
    bhv_constant(bhvCarrySomething3);
    bhv_constant(bhvCarrySomething4);
    bhv_constant(bhvCarrySomething5);
    bhv_constant(bhvCarrySomething6);
    bhv_constant(bhvObjectBubble);
    bhv_constant(bhvObjectWaterWave);
    bhv_constant(bhvExplosion);
    bhv_constant(bhvBobombBullyDeathSmoke);
    bhv_constant(bhvSmoke);
    bhv_constant(bhvBobombExplosionBubble);
    bhv_constant(bhvBobombExplosionBubble3600);
    bhv_constant(bhvRespawner);
    bhv_constant(bhvSmallBully);
    bhv_constant(bhvBigBully);
    bhv_constant(bhvBigBullyWithMinions);
    bhv_constant(bhvSmallChillBully);
    bhv_constant(bhvBigChillBully);
    bhv_constant(bhvJetStreamRingSpawner);
    bhv_constant(bhvJetStreamWaterRing);
    bhv_constant(bhvMantaRayWaterRing);
    bhv_constant(bhvMantaRayRingManager);
    bhv_constant(bhvBowserBomb);
    bhv_constant(bhvBowserBombExplosion);
    bhv_constant(bhvBowserBombSmoke);
    bhv_constant(bhvCelebrationStar);
    bhv_constant(bhvCelebrationStarSparkle);
    bhv_constant(bhvStarKeyCollectionPuffSpawner);
    bhv_constant(bhvLllDrawbridgeSpawner);
    bhv_constant(bhvLllDrawbridge);
    bhv_constant(bhvSmallBomp);
    bhv_constant(bhvLargeBomp);
    bhv_constant(bhvWfSlidingPlatform);
    bhv_constant(bhvMoneybag);
    bhv_constant(bhvMoneybagHidden);
    bhv_constant(bhvPitBowlingBall);
    bhv_constant(bhvFreeBowlingBall);
    bhv_constant(bhvBowlingBall);
    bhv_constant(bhvTtmBowlingBallSpawner);
    bhv_constant(bhvBobBowlingBallSpawner);
    bhv_constant(bhvThiBowlingBallSpawner);
    bhv_constant(bhvRrCruiserWing);
    bhv_constant(bhvSpindel);
    bhv_constant(bhvSslMovingPyramidWall);
    bhv_constant(bhvPyramidElevator);
    bhv_constant(bhvPyramidElevatorTrajectoryMarkerBall);
    bhv_constant(bhvPyramidTop);
    bhv_constant(bhvPyramidTopFragment);
    bhv_constant(bhvPyramidPillarTouchDetector);
    bhv_constant(bhvWaterfallSoundLoop);
    bhv_constant(bhvVolcanoSoundLoop);
    bhv_constant(bhvCastleFlagWaving);
    bhv_constant(bhvBirdsSoundLoop);
    bhv_constant(bhvAmbientSounds);
    bhv_constant(bhvSandSoundLoop);
    bhv_constant(bhvHiddenAt120Stars);
    bhv_constant(bhvSnowmansBottom);
    bhv_constant(bhvSnowmansHead);
    bhv_constant(bhvSnowmansBodyCheckpoint);
    bhv_constant(bhvBigSnowmanWhole);
    bhv_constant(bhvBigBoulder);
    bhv_constant(bhvBigBoulderGenerator);
    bhv_constant(bhvWingCap);
    bhv_constant(bhvMetalCap);
    bhv_constant(bhvNormalCap);
    bhv_constant(bhvVanishCap);
    bhv_constant(bhvStar);
    bhv_constant(bhvStarSpawnCoordinates);
    bhv_constant(bhvHiddenRedCoinStar);
    bhv_constant(bhvRedCoin);
    bhv_constant(bhvBowserCourseRedCoinStar);
    bhv_constant(bhvHiddenStar);
    bhv_constant(bhvHiddenStarTrigger);
    bhv_constant(bhvTtmRollingLog);
    bhv_constant(bhvLllVolcanoFallingTrap);
    bhv_constant(bhvLllRollingLog);
    bhv_constant(bhv1upWalking);
    bhv_constant(bhv1upRunningAway);
    bhv_constant(bhv1upSliding);
    bhv_constant(bhv1Up);
    bhv_constant(bhv1upJumpOnApproach);
    bhv_constant(bhvHidden1up);
    bhv_constant(bhvHidden1upTrigger);
    bhv_constant(bhvHidden1upInPole);
    bhv_constant(bhvHidden1upInPoleTrigger);
    bhv_constant(bhvHidden1upInPoleSpawner);
    bhv_constant(bhvControllablePlatform);
    bhv_constant(bhvControllablePlatformSub);
    bhv_constant(bhvBreakableBoxSmall);
    bhv_constant(bhvSlidingSnowMound);
    bhv_constant(bhvSnowMoundSpawn);
    bhv_constant(bhvWdwSquareFloatingPlatform);
    bhv_constant(bhvWdwRectangularFloatingPlatform);
    bhv_constant(bhvJrbFloatingPlatform);
    bhv_constant(bhvArrowLift);
    bhv_constant(bhvOrangeNumber);
    bhv_constant(bhvMantaRay);
    bhv_constant(bhvFallingPillar);
    bhv_constant(bhvFallingPillarHitbox);
    bhv_constant(bhvPillarBase);
    bhv_constant(bhvJrbFloatingBox);
    bhv_constant(bhvDecorativePendulum);
    bhv_constant(bhvTreasureChestsShip);
    bhv_constant(bhvTreasureChestsJrb);
    bhv_constant(bhvTreasureChests);
    bhv_constant(bhvTreasureChestBottom);
    bhv_constant(bhvTreasureChestTop);
    bhv_constant(bhvMips);
    bhv_constant(bhvYoshi);
    bhv_constant(bhvKoopa);
    bhv_constant(bhvKoopaRaceEndpoint);
    bhv_constant(bhvKoopaFlag);
    bhv_constant(bhvPokey);
    bhv_constant(bhvPokeyBodyPart);
    bhv_constant(bhvSwoop);
    bhv_constant(bhvFlyGuy);
    bhv_constant(bhvGoomba);
    bhv_constant(bhvGoombaTripletSpawner);
    bhv_constant(bhvChainChomp);
    bhv_constant(bhvChainChompChainPart);
    bhv_constant(bhvWoodenPost);
    bhv_constant(bhvChainChompGate);
    bhv_constant(bhvWigglerHead);
    bhv_constant(bhvWigglerBody);
    bhv_constant(bhvEnemyLakitu);
    bhv_constant(bhvCameraLakitu);
    bhv_constant(bhvCloud);
    bhv_constant(bhvCloudPart);
    bhv_constant(bhvSpiny);
    bhv_constant(bhvMontyMole);
    bhv_constant(bhvMontyMoleHole);
    bhv_constant(bhvMontyMoleRock);
    bhv_constant(bhvPlatformOnTrack);
    bhv_constant(bhvTrackBall);
    bhv_constant(bhvSeesawPlatform);
    bhv_constant(bhvFerrisWheelAxle);
    bhv_constant(bhvFerrisWheelPlatform);
    bhv_constant(bhvWaterBombSpawner);
    bhv_constant(bhvWaterBomb);
    bhv_constant(bhvWaterBombShadow);
    bhv_constant(bhvTTCRotatingSolid);
    bhv_constant(bhvTTCPendulum);
    bhv_constant(bhvTTCTreadmill);
    bhv_constant(bhvTTCMovingBar);
    bhv_constant(bhvTTCCog);
    bhv_constant(bhvTTCPitBlock);
    bhv_constant(bhvTTCElevator);
    bhv_constant(bhvTTC2DRotator);
    bhv_constant(bhvTTCSpinner);
    bhv_constant(bhvMrBlizzard);
    bhv_constant(bhvMrBlizzardSnowball);
    bhv_constant(bhvSlidingPlatform2);
    bhv_constant(bhvOctagonalPlatformRotating);
    bhv_constant(bhvAnimatesOnFloorSwitchPress);
    bhv_constant(bhvActivatedBackAndForthPlatform);
    bhv_constant(bhvRecoveryHeart);
    bhv_constant(bhvWaterBombCannon);
    bhv_constant(bhvCannonBarrelBubbles);
    bhv_constant(bhvUnagi);
    bhv_constant(bhvUnagiSubobject);
    bhv_constant(bhvDorrie);
    bhv_constant(bhvHauntedChair);
    bhv_constant(bhvMadPiano);
    bhv_constant(bhvFlyingBookend);
    bhv_constant(bhvBookendSpawn);
    bhv_constant(bhvHauntedBookshelfManager);
    bhv_constant(bhvBookSwitch);
    bhv_constant(bhvFirePiranhaPlant);
    bhv_constant(bhvSmallPiranhaFlame);
    bhv_constant(bhvFireSpitter);
    bhv_constant(bhvFlyguyFlame);
    bhv_constant(bhvSnufit);
    bhv_constant(bhvSnufitBalls);
    bhv_constant(bhvHorizontalGrindel);
    bhv_constant(bhvEyerokBoss);
    bhv_constant(bhvEyerokHand);
    bhv_constant(bhvKlepto);
    bhv_constant(bhvBird);
    bhv_constant(bhvRacingPenguin);
    bhv_constant(bhvPenguinRaceFinishLine);
    bhv_constant(bhvPenguinRaceShortcutCheck);
    bhv_constant(bhvCoffinSpawner);
    bhv_constant(bhvCoffin);
    bhv_constant(bhvClamShell);
    bhv_constant(bhvSkeeter);
    bhv_constant(bhvSkeeterWave);
    bhv_constant(bhvSwingPlatform);
    bhv_constant(bhvDonutPlatformSpawner);
    bhv_constant(bhvDonutPlatform);
    bhv_constant(bhvDDDPole);
    bhv_constant(bhvRedCoinStarMarker);
    bhv_constant(bhvTripletButterfly);
    bhv_constant(bhvBubba);
    bhv_constant(bhvBeginningLakitu);
    bhv_constant(bhvBeginningPeach);
    bhv_constant(bhvEndBirds1);
    bhv_constant(bhvEndBirds2);
    bhv_constant(bhvIntroScene);
    bhv_constant(bhvUnusedFakeStar);

    // Legacy behavior names
    bhv_legacy_constant(bhvFish2, bhvManyBlueFishSpawner);
    bhv_legacy_constant(bhvFish3, bhvFewBlueFishSpawner);
    bhv_legacy_constant(bhvLargeFishGroup, bhvFishSpawner);


    // Behavior ids
    bhv_constant(id_bhv1Up);
    bhv_constant(id_bhv1upJumpOnApproach);
    bhv_constant(id_bhv1upRunningAway);
    bhv_constant(id_bhv1upSliding);
    bhv_constant(id_bhv1upWalking);
    bhv_constant(id_bhvActivatedBackAndForthPlatform);
    bhv_constant(id_bhvActSelector);
    bhv_constant(id_bhvActSelectorStarType);
    bhv_constant(id_bhvAirborneDeathWarp);
    bhv_constant(id_bhvAirborneStarCollectWarp);
    bhv_constant(id_bhvAirborneWarp);
    bhv_constant(id_bhvAlphaBooKey);
    bhv_constant(id_bhvAmbientSounds);
    bhv_constant(id_bhvAnimatedTexture);
    bhv_constant(id_bhvAnimatesOnFloorSwitchPress);
    bhv_constant(id_bhvAnotherElavator);
    bhv_constant(id_bhvAnotherTiltingPlatform);
    bhv_constant(id_bhvArrowLift);
    bhv_constant(id_bhvBalconyBigBoo);
    bhv_constant(id_bhvBbhTiltingTrapPlatform);
    bhv_constant(id_bhvBbhTumblingBridge);
    bhv_constant(id_bhvBeginningLakitu);
    bhv_constant(id_bhvBeginningPeach);
    bhv_constant(id_bhvBetaBooKey);
    bhv_constant(id_bhvBetaBowserAnchor);
    bhv_constant(id_bhvBetaChestBottom);
    bhv_constant(id_bhvBetaChestLid);
    bhv_constant(id_bhvBetaFishSplashSpawner);
    bhv_constant(id_bhvBetaHoldableObject);
    bhv_constant(id_bhvBetaMovingFlames);
    bhv_constant(id_bhvBetaMovingFlamesSpawn);
    bhv_constant(id_bhvBetaTrampolineSpring);
    bhv_constant(id_bhvBetaTrampolineTop);
    bhv_constant(id_bhvBigBoulder);
    bhv_constant(id_bhvBigBoulderGenerator);
    bhv_constant(id_bhvBigBully);
    bhv_constant(id_bhvBigBullyWithMinions);
    bhv_constant(id_bhvBigChillBully);
    bhv_constant(id_bhvBigSnowmanWhole);
    bhv_constant(id_bhvBird);
    bhv_constant(id_bhvBirdsSoundLoop);
    bhv_constant(id_bhvBitfsSinkingCagePlatform);
    bhv_constant(id_bhvBitfsSinkingPlatforms);
    bhv_constant(id_bhvBitfsTiltingInvertedPyramid);
    bhv_constant(id_bhvBlackSmokeBowser);
    bhv_constant(id_bhvBlackSmokeMario);
    bhv_constant(id_bhvBlackSmokeUpward);
    bhv_constant(id_bhvBlueBowserFlame);
    bhv_constant(id_bhvBlueCoinJumping);
    bhv_constant(id_bhvBlueCoinSliding);
    bhv_constant(id_bhvBlueCoinSwitch);
    bhv_constant(id_bhvBlueFish);
    bhv_constant(id_bhvBlueFlamesGroup);
    bhv_constant(id_bhvBobBowlingBallSpawner);
    bhv_constant(id_bhvBobomb);
    bhv_constant(id_bhvBobombAnchorMario);
    bhv_constant(id_bhvBobombBuddy);
    bhv_constant(id_bhvBobombBuddyOpensCannon);
    bhv_constant(id_bhvBobombBullyDeathSmoke);
    bhv_constant(id_bhvBobombExplosionBubble);
    bhv_constant(id_bhvBobombExplosionBubble3600);
    bhv_constant(id_bhvBobombFuseSmoke);
    bhv_constant(id_bhvBoo);
    bhv_constant(id_bhvBooBossSpawnedBridge);
    bhv_constant(id_bhvBooCage);
    bhv_constant(id_bhvBooInCastle);
    bhv_constant(id_bhvBookendSpawn);
    bhv_constant(id_bhvBookSwitch);
    bhv_constant(id_bhvBooWithCage);
    bhv_constant(id_bhvBouncingFireball);
    bhv_constant(id_bhvBouncingFireballFlame);
    bhv_constant(id_bhvBowlingBall);
    bhv_constant(id_bhvBowser);
    bhv_constant(id_bhvBowserBodyAnchor);
    bhv_constant(id_bhvBowserBomb);
    bhv_constant(id_bhvBowserBombExplosion);
    bhv_constant(id_bhvBowserBombSmoke);
    bhv_constant(id_bhvBowserCourseRedCoinStar);
    bhv_constant(id_bhvBowserFlameSpawn);
    bhv_constant(id_bhvBowserKey);
    bhv_constant(id_bhvBowserKeyCourseExit);
    bhv_constant(id_bhvBowserKeyUnlockDoor);
    bhv_constant(id_bhvBowserShockWave);
    bhv_constant(id_bhvBowsersSub);
    bhv_constant(id_bhvBowserSubDoor);
    bhv_constant(id_bhvBowserTailAnchor);
    bhv_constant(id_bhvBreakableBox);
    bhv_constant(id_bhvBreakableBoxSmall);
    bhv_constant(id_bhvBreakBoxTriangle);
    bhv_constant(id_bhvBreathParticleSpawner);
    bhv_constant(id_bhvBub);
    bhv_constant(id_bhvBubba);
    bhv_constant(id_bhvBubbleMaybe);
    bhv_constant(id_bhvBubbleParticleSpawner);
    bhv_constant(id_bhvBubblePlayer);
    bhv_constant(id_bhvBubbleSplash);
    bhv_constant(id_bhvBulletBill);
    bhv_constant(id_bhvBulletBillCannon);
    bhv_constant(id_bhvButterfly);
    bhv_constant(id_bhvCameraLakitu);
    bhv_constant(id_bhvCannon);
    bhv_constant(id_bhvCannonBarrel);
    bhv_constant(id_bhvCannonBarrelBubbles);
    bhv_constant(id_bhvCannonBaseUnused);
    bhv_constant(id_bhvCannonClosed);
    bhv_constant(id_bhvCapSwitch);
    bhv_constant(id_bhvCapSwitchBase);
    bhv_constant(id_bhvCarrySomething1);
    bhv_constant(id_bhvCarrySomething2);
    bhv_constant(id_bhvCarrySomething3);
    bhv_constant(id_bhvCarrySomething4);
    bhv_constant(id_bhvCarrySomething5);
    bhv_constant(id_bhvCarrySomething6);
    bhv_constant(id_bhvCastleFlagWaving);
    bhv_constant(id_bhvCastleFloorTrap);
    bhv_constant(id_bhvCcmTouchedStarSpawn);
    bhv_constant(id_bhvCelebrationStar);
    bhv_constant(id_bhvCelebrationStarSparkle);
    bhv_constant(id_bhvChainChomp);
    bhv_constant(id_bhvChainChompChainPart);
    bhv_constant(id_bhvChainChompGate);
    bhv_constant(id_bhvCheckerboardElevatorGroup);
    bhv_constant(id_bhvCheckerboardPlatformSub);
    bhv_constant(id_bhvChirpChirp);
    bhv_constant(id_bhvChirpChirpUnused);
    bhv_constant(id_bhvChuckya);
    bhv_constant(id_bhvChuckyaAnchorMario);
    bhv_constant(id_bhvCirclingAmp);
    bhv_constant(id_bhvClamShell);
    bhv_constant(id_bhvClockHourHand);
    bhv_constant(id_bhvClockMinuteHand);
    bhv_constant(id_bhvCloud);
    bhv_constant(id_bhvCloudPart);
    bhv_constant(id_bhvCoffin);
    bhv_constant(id_bhvCoffinSpawner);
    bhv_constant(id_bhvCoinFormation);
    bhv_constant(id_bhvCoinFormationSpawn);
    bhv_constant(id_bhvCoinInsideBoo);
    bhv_constant(id_bhvCoinSparkles);
    bhv_constant(id_bhvControllablePlatform);
    bhv_constant(id_bhvControllablePlatformSub);
    bhv_constant(id_bhvCourtyardBooTriplet);
    bhv_constant(id_bhvCutOutObject);
    bhv_constant(id_bhvDddMovingPole);
    bhv_constant(id_bhvDDDPole);
    bhv_constant(id_bhvDddWarp);
    bhv_constant(id_bhvDeathWarp);
    bhv_constant(id_bhvDecorativePendulum);
    bhv_constant(id_bhvDirtParticleSpawner);
    bhv_constant(id_bhvDonutPlatform);
    bhv_constant(id_bhvDonutPlatformSpawner);
    bhv_constant(id_bhvDoor);
    bhv_constant(id_bhvDoorWarp);
    bhv_constant(id_bhvDorrie);
    bhv_constant(id_bhvEndBirds1);
    bhv_constant(id_bhvEndBirds2);
    bhv_constant(id_bhvEndPeach);
    bhv_constant(id_bhvEndToad);
    bhv_constant(id_bhvEnemyLakitu);
    bhv_constant(id_bhvExclamationBox);
    bhv_constant(id_bhvExitPodiumWarp);
    bhv_constant(id_bhvExplosion);
    bhv_constant(id_bhvEyerokBoss);
    bhv_constant(id_bhvEyerokHand);
    bhv_constant(id_bhvFadingWarp);
    bhv_constant(id_bhvFallingBowserPlatform);
    bhv_constant(id_bhvFallingPillar);
    bhv_constant(id_bhvFallingPillarHitbox);
    bhv_constant(id_bhvFerrisWheelAxle);
    bhv_constant(id_bhvFerrisWheelPlatform);
    bhv_constant(id_bhvFewBlueFishSpawner);
    bhv_constant(id_bhvFireParticleSpawner);
    bhv_constant(id_bhvFirePiranhaPlant);
    bhv_constant(id_bhvFireSpitter);
    bhv_constant(id_bhvFish);
    bhv_constant(id_bhvFishGroup);
    bhv_constant(id_bhvFishSpawner);
    bhv_constant(id_bhvFlame);
    bhv_constant(id_bhvFlameBouncing);
    bhv_constant(id_bhvFlameBowser);
    bhv_constant(id_bhvFlameFloatingLanding);
    bhv_constant(id_bhvFlameLargeBurningOut);
    bhv_constant(id_bhvFlameMovingForwardGrowing);
    bhv_constant(id_bhvFlamethrower);
    bhv_constant(id_bhvFlamethrowerFlame);
    bhv_constant(id_bhvFloorSwitchAnimatesObject);
    bhv_constant(id_bhvFloorSwitchGrills);
    bhv_constant(id_bhvFloorSwitchHardcodedModel);
    bhv_constant(id_bhvFloorSwitchHiddenObjects);
    bhv_constant(id_bhvFloorTrapInCastle);
    bhv_constant(id_bhvFlyGuy);
    bhv_constant(id_bhvFlyguyFlame);
    bhv_constant(id_bhvFlyingBookend);
    bhv_constant(id_bhvFlyingWarp);
    bhv_constant(id_bhvFreeBowlingBall);
    bhv_constant(id_bhvGhostHuntBigBoo);
    bhv_constant(id_bhvGhostHuntBoo);
    bhv_constant(id_bhvGiantPole);
    bhv_constant(id_bhvGoldenCoinSparkles);
    bhv_constant(id_bhvGoomba);
    bhv_constant(id_bhvGoombaTripletSpawner);
    bhv_constant(id_bhvGrandStar);
    bhv_constant(id_bhvGrindel);
    bhv_constant(id_bhvHardAirKnockBackWarp);
    bhv_constant(id_bhvHauntedBookshelf);
    bhv_constant(id_bhvHauntedBookshelfManager);
    bhv_constant(id_bhvHauntedChair);
    bhv_constant(id_bhvHeaveHo);
    bhv_constant(id_bhvHeaveHoThrowMario);
    bhv_constant(id_bhvHidden1up);
    bhv_constant(id_bhvHidden1upInPole);
    bhv_constant(id_bhvHidden1upInPoleSpawner);
    bhv_constant(id_bhvHidden1upInPoleTrigger);
    bhv_constant(id_bhvHidden1upTrigger);
    bhv_constant(id_bhvHiddenAt120Stars);
    bhv_constant(id_bhvHiddenBlueCoin);
    bhv_constant(id_bhvHiddenObject);
    bhv_constant(id_bhvHiddenRedCoinStar);
    bhv_constant(id_bhvHiddenStaircaseStep);
    bhv_constant(id_bhvHiddenStar);
    bhv_constant(id_bhvHiddenStarTrigger);
    bhv_constant(id_bhvHmcElevatorPlatform);
    bhv_constant(id_bhvHomingAmp);
    bhv_constant(id_bhvHoot);
    bhv_constant(id_bhvHorizontalGrindel);
    bhv_constant(id_bhvHorStarParticleSpawner);
    bhv_constant(id_bhvIdleWaterWave);
    bhv_constant(id_bhvIgloo);
    bhv_constant(id_bhvInitializeChangingWaterLevel);
    bhv_constant(id_bhvInsideCannon);
    bhv_constant(id_bhvInstantActiveWarp);
    bhv_constant(id_bhvInSunkenShip);
    bhv_constant(id_bhvInSunkenShip2);
    bhv_constant(id_bhvInSunkenShip3);
    bhv_constant(id_bhvIntroScene);
    bhv_constant(id_bhvInvisibleObjectsUnderBridge);
    bhv_constant(id_bhvJetStream);
    bhv_constant(id_bhvJetStreamRingSpawner);
    bhv_constant(id_bhvJetStreamWaterRing);
    bhv_constant(id_bhvJrbFloatingBox);
    bhv_constant(id_bhvJrbFloatingPlatform);
    bhv_constant(id_bhvJrbSlidingBox);
    bhv_constant(id_bhvJumpingBox);
    bhv_constant(id_bhvKickableBoard);
    bhv_constant(id_bhvKingBobomb);
    bhv_constant(id_bhvKlepto);
    bhv_constant(id_bhvKoopa);
    bhv_constant(id_bhvKoopaFlag);
    bhv_constant(id_bhvKoopaRaceEndpoint);
    bhv_constant(id_bhvKoopaShell);
    bhv_constant(id_bhvKoopaShellFlame);
    bhv_constant(id_bhvKoopaShellUnderwater);
    bhv_constant(id_bhvLargeBomp);
    bhv_constant(id_bhvLaunchDeathWarp);
    bhv_constant(id_bhvLaunchStarCollectWarp);
    bhv_constant(id_bhvLeafParticleSpawner);
    bhv_constant(id_bhvLllBowserPuzzle);
    bhv_constant(id_bhvLllBowserPuzzlePiece);
    bhv_constant(id_bhvLllDrawbridge);
    bhv_constant(id_bhvLllDrawbridgeSpawner);
    bhv_constant(id_bhvLllFloatingWoodBridge);
    bhv_constant(id_bhvLllHexagonalMesh);
    bhv_constant(id_bhvLllMovingOctagonalMeshPlatform);
    bhv_constant(id_bhvLllRollingLog);
    bhv_constant(id_bhvLllRotatingBlockWithFireBars);
    bhv_constant(id_bhvLllRotatingHexagonalPlatform);
    bhv_constant(id_bhvLllRotatingHexagonalRing);
    bhv_constant(id_bhvLllRotatingHexFlame);
    bhv_constant(id_bhvLllSinkingRectangularPlatform);
    bhv_constant(id_bhvLllSinkingRockBlock);
    bhv_constant(id_bhvLllSinkingSquarePlatforms);
    bhv_constant(id_bhvLllTiltingInvertedPyramid);
    bhv_constant(id_bhvLllTumblingBridge);
    bhv_constant(id_bhvLllVolcanoFallingTrap);
    bhv_constant(id_bhvLllWoodPiece);
    bhv_constant(id_bhvMacroUkiki);
    bhv_constant(id_bhvMadPiano);
    bhv_constant(id_bhvMantaRay);
    bhv_constant(id_bhvMantaRayRingManager);
    bhv_constant(id_bhvMantaRayWaterRing);
    bhv_constant(id_bhvManyBlueFishSpawner);
    bhv_constant(id_bhvMario);
    bhv_constant(id_bhvMenuButton);
    bhv_constant(id_bhvMenuButtonManager);
    bhv_constant(id_bhvMerryGoRound);
    bhv_constant(id_bhvMerryGoRoundBigBoo);
    bhv_constant(id_bhvMerryGoRoundBoo);
    bhv_constant(id_bhvMerryGoRoundBooManager);
    bhv_constant(id_bhvMeshElevator);
    bhv_constant(id_bhvMessagePanel);
    bhv_constant(id_bhvMetalCap);
    bhv_constant(id_bhvMips);
    bhv_constant(id_bhvMistCircParticleSpawner);
    bhv_constant(id_bhvMistParticleSpawner);
    bhv_constant(id_bhvMoatGrills);
    bhv_constant(id_bhvMoneybag);
    bhv_constant(id_bhvMoneybagHidden);
    bhv_constant(id_bhvMontyMole);
    bhv_constant(id_bhvMontyMoleHole);
    bhv_constant(id_bhvMontyMoleRock);
    bhv_constant(id_bhvMovingBlueCoin);
    bhv_constant(id_bhvMovingYellowCoin);
    bhv_constant(id_bhvMrBlizzard);
    bhv_constant(id_bhvMrBlizzardSnowball);
    bhv_constant(id_bhvMrI);
    bhv_constant(id_bhvMrIBlueCoin);
    bhv_constant(id_bhvMrIBody);
    bhv_constant(id_bhvMrIParticle);
    bhv_constant(id_bhvNormalCap);
    bhv_constant(id_bhvObjectBubble);
    bhv_constant(id_bhvObjectWaterSplash);
    bhv_constant(id_bhvObjectWaterWave);
    bhv_constant(id_bhvObjectWaveTrail);
    bhv_constant(id_bhvOctagonalPlatformRotating);
    bhv_constant(id_bhvOneCoin);
    bhv_constant(id_bhvOpenableCageDoor);
    bhv_constant(id_bhvOpenableGrill);
    bhv_constant(id_bhvOrangeNumber);
    bhv_constant(id_bhvPaintingDeathWarp);
    bhv_constant(id_bhvPaintingStarCollectWarp);
    bhv_constant(id_bhvPenguinBaby);
    bhv_constant(id_bhvPenguinRaceFinishLine);
    bhv_constant(id_bhvPenguinRaceShortcutCheck);
    bhv_constant(id_bhvPillarBase);
    bhv_constant(id_bhvPiranhaPlant);
    bhv_constant(id_bhvPiranhaPlantBubble);
    bhv_constant(id_bhvPiranhaPlantWakingBubbles);
    bhv_constant(id_bhvPitBowlingBall);
    bhv_constant(id_bhvPlatformOnTrack);
    bhv_constant(id_bhvPlaysMusicTrackWhenTouched);
    bhv_constant(id_bhvPlungeBubble);
    bhv_constant(id_bhvPokey);
    bhv_constant(id_bhvPokeyBodyPart);
    bhv_constant(id_bhvPoleGrabbing);
    bhv_constant(id_bhvPoundTinyStarParticle);
    bhv_constant(id_bhvPunchTinyTriangle);
    bhv_constant(id_bhvPurpleParticle);
    bhv_constant(id_bhvPurpleSwitchHiddenBoxes);
    bhv_constant(id_bhvPushableMetalBox);
    bhv_constant(id_bhvPyramidElevator);
    bhv_constant(id_bhvPyramidElevatorTrajectoryMarkerBall);
    bhv_constant(id_bhvPyramidPillarTouchDetector);
    bhv_constant(id_bhvPyramidTop);
    bhv_constant(id_bhvPyramidTopFragment);
    bhv_constant(id_bhvRacingPenguin);
    bhv_constant(id_bhvRandomAnimatedTexture);
    bhv_constant(id_bhvRecoveryHeart);
    bhv_constant(id_bhvRedCoin);
    bhv_constant(id_bhvRedCoinStarMarker);
    bhv_constant(id_bhvRespawner);
    bhv_constant(id_bhvRockSolid);
    bhv_constant(id_bhvRotatingCounterClockwise);
    bhv_constant(id_bhvRotatingExclamationMark);
    bhv_constant(id_bhvRotatingPlatform);
    bhv_constant(id_bhvRrCruiserWing);
    bhv_constant(id_bhvRrElevatorPlatform);
    bhv_constant(id_bhvRrRotatingBridgePlatform);
    bhv_constant(id_bhvSandSoundLoop);
    bhv_constant(id_bhvScuttlebug);
    bhv_constant(id_bhvScuttlebugSpawn);
    bhv_constant(id_bhvSeaweed);
    bhv_constant(id_bhvSeaweedBundle);
    bhv_constant(id_bhvSeesawPlatform);
    bhv_constant(id_bhvShallowWaterSplash);
    bhv_constant(id_bhvShallowWaterWave);
    bhv_constant(id_bhvShipPart3);
    bhv_constant(id_bhvSignOnWall);
    bhv_constant(id_bhvSingleCoinGetsSpawned);
    bhv_constant(id_bhvSkeeter);
    bhv_constant(id_bhvSkeeterWave);
    bhv_constant(id_bhvSlidingPlatform2);
    bhv_constant(id_bhvSlidingSnowMound);
    bhv_constant(id_bhvSLSnowmanWind);
    bhv_constant(id_bhvSLWalkingPenguin);
    bhv_constant(id_bhvSmallBomp);
    bhv_constant(id_bhvSmallBully);
    bhv_constant(id_bhvSmallChillBully);
    bhv_constant(id_bhvSmallParticle);
    bhv_constant(id_bhvSmallParticleBubbles);
    bhv_constant(id_bhvSmallParticleSnow);
    bhv_constant(id_bhvSmallPenguin);
    bhv_constant(id_bhvSmallPiranhaFlame);
    bhv_constant(id_bhvSmallWaterWave);
    bhv_constant(id_bhvSmallWaterWave398);
    bhv_constant(id_bhvSmallWhomp);
    bhv_constant(id_bhvSmoke);
    bhv_constant(id_bhvSnowBall);
    bhv_constant(id_bhvSnowmansBodyCheckpoint);
    bhv_constant(id_bhvSnowmansBottom);
    bhv_constant(id_bhvSnowmansHead);
    bhv_constant(id_bhvSnowMoundSpawn);
    bhv_constant(id_bhvSnowParticleSpawner);
    bhv_constant(id_bhvSnufit);
    bhv_constant(id_bhvSnufitBalls);
    bhv_constant(id_bhvSoundSpawner);
    bhv_constant(id_bhvSparkle);
    bhv_constant(id_bhvSparkleParticleSpawner);
    bhv_constant(id_bhvSparkleSpawn);
    bhv_constant(id_bhvSpawnedStar);
    bhv_constant(id_bhvSpawnedStarNoLevelExit);
    bhv_constant(id_bhvSpinAirborneCircleWarp);
    bhv_constant(id_bhvSpinAirborneWarp);
    bhv_constant(id_bhvSpindel);
    bhv_constant(id_bhvSpindrift);
    bhv_constant(id_bhvSpiny);
    bhv_constant(id_bhvSquarishPathMoving);
    bhv_constant(id_bhvSquarishPathParent);
    bhv_constant(id_bhvSquishablePlatform);
    bhv_constant(id_bhvSslMovingPyramidWall);
    bhv_constant(id_bhvStar);
    bhv_constant(id_bhvStarDoor);
    bhv_constant(id_bhvStarKeyCollectionPuffSpawner);
    bhv_constant(id_bhvStarSpawnCoordinates);
    bhv_constant(id_bhvStaticCheckeredPlatform);
    bhv_constant(id_bhvStaticObject);
    bhv_constant(id_bhvStrongWindParticle);
    bhv_constant(id_bhvStub);
    bhv_constant(id_bhvStub1D0C);
    bhv_constant(id_bhvStub1D70);
    bhv_constant(id_bhvSunkenShipPart);
    bhv_constant(id_bhvSunkenShipPart2);
    bhv_constant(id_bhvSunkenShipSetRotation);
    bhv_constant(id_bhvSushiShark);
    bhv_constant(id_bhvSushiSharkCollisionChild);
    bhv_constant(id_bhvSwimmingWarp);
    bhv_constant(id_bhvSwingPlatform);
    bhv_constant(id_bhvSwoop);
    bhv_constant(id_bhvTankFishGroup);
    bhv_constant(id_bhvTemporaryYellowCoin);
    bhv_constant(id_bhvTenCoinsSpawn);
    bhv_constant(id_bhvThiBowlingBallSpawner);
    bhv_constant(id_bhvThiHugeIslandTop);
    bhv_constant(id_bhvThiTinyIslandTop);
    bhv_constant(id_bhvThreeCoinsSpawn);
    bhv_constant(id_bhvThwomp);
    bhv_constant(id_bhvThwomp2);
    bhv_constant(id_bhvTiltingBowserLavaPlatform);
    bhv_constant(id_bhvTinyStrongWindParticle);
    bhv_constant(id_bhvToadMessage);
    bhv_constant(id_bhvTower);
    bhv_constant(id_bhvTowerDoor);
    bhv_constant(id_bhvTowerPlatformGroup);
    bhv_constant(id_bhvToxBox);
    bhv_constant(id_bhvTrackBall);
    bhv_constant(id_bhvTreasureChestBottom);
    bhv_constant(id_bhvTreasureChests);
    bhv_constant(id_bhvTreasureChestsJrb);
    bhv_constant(id_bhvTreasureChestsShip);
    bhv_constant(id_bhvTreasureChestTop);
    bhv_constant(id_bhvTree);
    bhv_constant(id_bhvTreeLeaf);
    bhv_constant(id_bhvTreeSnow);
    bhv_constant(id_bhvTriangleParticleSpawner);
    bhv_constant(id_bhvTripletButterfly);
    bhv_constant(id_bhvTTC2DRotator);
    bhv_constant(id_bhvTTCCog);
    bhv_constant(id_bhvTTCElevator);
    bhv_constant(id_bhvTTCMovingBar);
    bhv_constant(id_bhvTTCPendulum);
    bhv_constant(id_bhvTTCPitBlock);
    bhv_constant(id_bhvTTCRotatingSolid);
    bhv_constant(id_bhvTTCSpinner);
    bhv_constant(id_bhvTTCTreadmill);
    bhv_constant(id_bhvTtmBowlingBallSpawner);
    bhv_constant(id_bhvTtmRollingLog);
    bhv_constant(id_bhvTumblingBridgePlatform);
    bhv_constant(id_bhvTuxiesMother);
    bhv_constant(id_bhvTweester);
    bhv_constant(id_bhvTweesterSandParticle);
    bhv_constant(id_bhvUkiki);
    bhv_constant(id_bhvUkikiCage);
    bhv_constant(id_bhvUkikiCageChild);
    bhv_constant(id_bhvUkikiCageStar);
    bhv_constant(id_bhvUnagi);
    bhv_constant(id_bhvUnagiSubobject);
    bhv_constant(id_bhvUnlockDoorStar);
    bhv_constant(id_bhvUnused05A8);
    bhv_constant(id_bhvUnused0DFC);
    bhv_constant(id_bhvUnused1820);
    bhv_constant(id_bhvUnused1F30);
    bhv_constant(id_bhvUnused20E0);
    bhv_constant(id_bhvUnused2A10);
    bhv_constant(id_bhvUnused2A54);
    bhv_constant(id_bhvUnusedFakeStar);
    bhv_constant(id_bhvUnusedParticleSpawn);
    bhv_constant(id_bhvUnusedPoundablePlatform);
    bhv_constant(id_bhvVanishCap);
    bhv_constant(id_bhvVertStarParticleSpawner);
    bhv_constant(id_bhvVolcanoFlames);
    bhv_constant(id_bhvVolcanoSoundLoop);
    bhv_constant(id_bhvWallTinyStarParticle);
    bhv_constant(id_bhvWarp);
    bhv_constant(id_bhvWarpPipe);
    bhv_constant(id_bhvWaterAirBubble);
    bhv_constant(id_bhvWaterBomb);
    bhv_constant(id_bhvWaterBombCannon);
    bhv_constant(id_bhvWaterBombShadow);
    bhv_constant(id_bhvWaterBombSpawner);
    bhv_constant(id_bhvWaterDroplet);
    bhv_constant(id_bhvWaterDropletSplash);
    bhv_constant(id_bhvWaterfallSoundLoop);
    bhv_constant(id_bhvWaterLevelDiamond);
    bhv_constant(id_bhvWaterLevelPillar);
    bhv_constant(id_bhvWaterMist);
    bhv_constant(id_bhvWaterMist2);
    bhv_constant(id_bhvWaterSplash);
    bhv_constant(id_bhvWaveTrail);
    bhv_constant(id_bhvWdwExpressElevator);
    bhv_constant(id_bhvWdwExpressElevatorPlatform);
    bhv_constant(id_bhvWdwRectangularFloatingPlatform);
    bhv_constant(id_bhvWdwSquareFloatingPlatform);
    bhv_constant(id_bhvWfBreakableWallLeft);
    bhv_constant(id_bhvWfBreakableWallRight);
    bhv_constant(id_bhvWfElevatorTowerPlatform);
    bhv_constant(id_bhvWfRotatingWoodenPlatform);
    bhv_constant(id_bhvWfSlidingPlatform);
    bhv_constant(id_bhvWfSlidingTowerPlatform);
    bhv_constant(id_bhvWfSolidTowerPlatform);
    bhv_constant(id_bhvWfTumblingBridge);
    bhv_constant(id_bhvWhirlpool);
    bhv_constant(id_bhvWhitePuff1);
    bhv_constant(id_bhvWhitePuff2);
    bhv_constant(id_bhvWhitePuffExplosion);
    bhv_constant(id_bhvWhitePuffSmoke);
    bhv_constant(id_bhvWhitePuffSmoke2);
    bhv_constant(id_bhvWhompKingBoss);
    bhv_constant(id_bhvWigglerBody);
    bhv_constant(id_bhvWigglerHead);
    bhv_constant(id_bhvWind);
    bhv_constant(id_bhvWingCap);
    bhv_constant(id_bhvWoodenPost);
    bhv_constant(id_bhvYellowBackgroundInMenu);
    bhv_constant(id_bhvYellowBall);
    bhv_constant(id_bhvYellowCoin);
    bhv_constant(id_bhvYoshi);
    
    // Define a special type for new ids that don't override.
    if (_Arg == "id_bhvNewId") { return (BehaviorScript) (0xFFFF); }
    
    // Legacy behavior ids
    bhv_legacy_constant(id_bhvFish2, id_bhvManyBlueFishSpawner);
    bhv_legacy_constant(id_bhvFish3, id_bhvFewBlueFishSpawner);
    bhv_legacy_constant(id_bhvLargeFishGroup, id_bhvFishSpawner);
    

    // Model constants
    bhv_constant(ACT_1);
    bhv_constant(ACT_2);
    bhv_constant(ACT_3);
    bhv_constant(ACT_4);
    bhv_constant(ACT_5);
    bhv_constant(ACT_6);
    bhv_constant(ALL_ACTS_MACRO);
    bhv_constant(ALL_ACTS);
    bhv_constant(COIN_FORMATION_FLAG_VERTICAL);
    bhv_constant(COIN_FORMATION_FLAG_RING);
    bhv_constant(COIN_FORMATION_FLAG_ARROW);
    bhv_constant(COIN_FORMATION_FLAG_FLYING);
    bhv_constant(MODEL_NONE);
    bhv_constant(MODEL_MARIO);
    bhv_constant(MODEL_LEVEL_GEOMETRY_03);
    bhv_constant(MODEL_LEVEL_GEOMETRY_04);
    bhv_constant(MODEL_LEVEL_GEOMETRY_05);
    bhv_constant(MODEL_LEVEL_GEOMETRY_06);
    bhv_constant(MODEL_LEVEL_GEOMETRY_07);
    bhv_constant(MODEL_LEVEL_GEOMETRY_08);
    bhv_constant(MODEL_LEVEL_GEOMETRY_09);
    bhv_constant(MODEL_LEVEL_GEOMETRY_0A);
    bhv_constant(MODEL_LEVEL_GEOMETRY_0B);
    bhv_constant(MODEL_LEVEL_GEOMETRY_0C);
    bhv_constant(MODEL_LEVEL_GEOMETRY_0D);
    bhv_constant(MODEL_LEVEL_GEOMETRY_0E);
    bhv_constant(MODEL_LEVEL_GEOMETRY_0F);
    bhv_constant(MODEL_LEVEL_GEOMETRY_10);
    bhv_constant(MODEL_LEVEL_GEOMETRY_11);
    bhv_constant(MODEL_LEVEL_GEOMETRY_12);
    bhv_constant(MODEL_LEVEL_GEOMETRY_13);
    bhv_constant(MODEL_LEVEL_GEOMETRY_14);
    bhv_constant(MODEL_LEVEL_GEOMETRY_15);
    bhv_constant(MODEL_LEVEL_GEOMETRY_16);
    bhv_constant(MODEL_BOB_BUBBLY_TREE);
    bhv_constant(MODEL_WDW_BUBBLY_TREE);
    bhv_constant(MODEL_CASTLE_GROUNDS_BUBBLY_TREE);
    bhv_constant(MODEL_WF_BUBBLY_TREE);
    bhv_constant(MODEL_THI_BUBBLY_TREE);
    bhv_constant(MODEL_COURTYARD_SPIKY_TREE);
    bhv_constant(MODEL_CCM_SNOW_TREE);
    bhv_constant(MODEL_SL_SNOW_TREE);
    bhv_constant(MODEL_UNKNOWN_TREE_1A);
    bhv_constant(MODEL_SSL_PALM_TREE);
    bhv_constant(MODEL_CASTLE_CASTLE_DOOR_UNUSED);
    bhv_constant(MODEL_CASTLE_WOODEN_DOOR_UNUSED);
    bhv_constant(MODEL_BBH_HAUNTED_DOOR);
    bhv_constant(MODEL_HMC_WOODEN_DOOR);
    bhv_constant(MODEL_UNKNOWN_DOOR_1E);
    bhv_constant(MODEL_HMC_METAL_DOOR);
    bhv_constant(MODEL_HMC_HAZY_MAZE_DOOR);
    bhv_constant(MODEL_UNKNOWN_DOOR_21);
    bhv_constant(MODEL_CASTLE_DOOR_0_STARS);
    bhv_constant(MODEL_CASTLE_DOOR_1_STAR);
    bhv_constant(MODEL_CASTLE_DOOR_3_STARS);
    bhv_constant(MODEL_CASTLE_KEY_DOOR);
    bhv_constant(MODEL_CASTLE_CASTLE_DOOR);
    bhv_constant(MODEL_CASTLE_GROUNDS_CASTLE_DOOR);
    bhv_constant(MODEL_CASTLE_WOODEN_DOOR);
    bhv_constant(MODEL_COURTYARD_WOODEN_DOOR);
    bhv_constant(MODEL_CCM_CABIN_DOOR);
    bhv_constant(MODEL_UNKNOWN_DOOR_28);
    bhv_constant(MODEL_CASTLE_METAL_DOOR);
    bhv_constant(MODEL_CASTLE_GROUNDS_METAL_DOOR);
    bhv_constant(MODEL_UNKNOWN_DOOR_2A);
    bhv_constant(MODEL_UNKNOWN_DOOR_2B);
    bhv_constant(MODEL_WF_TOWER_TRAPEZOID_PLATORM);
    bhv_constant(MODEL_WF_TOWER_SQUARE_PLATORM);
    bhv_constant(MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED);
    bhv_constant(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR);
    bhv_constant(MODEL_BBH_STAIRCASE_STEP);
    bhv_constant(MODEL_BBH_TILTING_FLOOR_PLATFORM);
    bhv_constant(MODEL_BBH_TUMBLING_PLATFORM);
    bhv_constant(MODEL_BBH_TUMBLING_PLATFORM_PART);
    bhv_constant(MODEL_BBH_MOVING_BOOKSHELF);
    bhv_constant(MODEL_BBH_MESH_ELEVATOR);
    bhv_constant(MODEL_BBH_MERRY_GO_ROUND);
    bhv_constant(MODEL_BBH_WOODEN_TOMB);
    bhv_constant(MODEL_CCM_ROPEWAY_LIFT);
    bhv_constant(MODEL_CCM_SNOWMAN_HEAD);
    bhv_constant(MODEL_CASTLE_BOWSER_TRAP);
    bhv_constant(MODEL_CASTLE_WATER_LEVEL_PILLAR);
    bhv_constant(MODEL_CASTLE_CLOCK_MINUTE_HAND);
    bhv_constant(MODEL_CASTLE_CLOCK_HOUR_HAND);
    bhv_constant(MODEL_CASTLE_CLOCK_PENDULUM);
    bhv_constant(MODEL_HMC_METAL_PLATFORM);
    bhv_constant(MODEL_HMC_METAL_ARROW_PLATFORM);
    bhv_constant(MODEL_HMC_ELEVATOR_PLATFORM);
    bhv_constant(MODEL_HMC_ROLLING_ROCK);
    bhv_constant(MODEL_HMC_ROCK_PIECE);
    bhv_constant(MODEL_HMC_ROCK_SMALL_PIECE);
    bhv_constant(MODEL_HMC_RED_GRILLS);
    bhv_constant(MODEL_SSL_PYRAMID_TOP);
    bhv_constant(MODEL_SSL_GRINDEL);
    bhv_constant(MODEL_SSL_SPINDEL);
    bhv_constant(MODEL_SSL_MOVING_PYRAMID_WALL);
    bhv_constant(MODEL_SSL_PYRAMID_ELEVATOR);
    bhv_constant(MODEL_BOB_CHAIN_CHOMP_GATE);
    bhv_constant(MODEL_BOB_SEESAW_PLATFORM);
    bhv_constant(MODEL_BOB_BARS_GRILLS);
    bhv_constant(MODEL_SL_SNOW_TRIANGLE);
    bhv_constant(MODEL_SL_CRACKED_ICE);
    bhv_constant(MODEL_SL_CRACKED_ICE_CHUNK);
    bhv_constant(MODEL_WDW_SQUARE_FLOATING_PLATFORM);
    bhv_constant(MODEL_WDW_ARROW_LIFT);
    bhv_constant(MODEL_WDW_WATER_LEVEL_DIAMOND);
    bhv_constant(MODEL_WDW_HIDDEN_PLATFORM);
    bhv_constant(MODEL_WDW_EXPRESS_ELEVATOR);
    bhv_constant(MODEL_WDW_RECTANGULAR_FLOATING_PLATFORM);
    bhv_constant(MODEL_WDW_ROTATING_PLATFORM);
    bhv_constant(MODEL_JRB_SHIP_LEFT_HALF_PART);
    bhv_constant(MODEL_JRB_SHIP_BACK_LEFT_PART);
    bhv_constant(MODEL_JRB_SHIP_RIGHT_HALF_PART);
    bhv_constant(MODEL_JRB_SHIP_BACK_RIGHT_PART);
    bhv_constant(MODEL_JRB_SUNKEN_SHIP);
    bhv_constant(MODEL_JRB_SUNKEN_SHIP_BACK);
    bhv_constant(MODEL_JRB_ROCK);
    bhv_constant(MODEL_JRB_SLIDING_BOX);
    bhv_constant(MODEL_JRB_FALLING_PILLAR);
    bhv_constant(MODEL_JRB_FALLING_PILLAR_BASE);
    bhv_constant(MODEL_JRB_FLOATING_PLATFORM);
    bhv_constant(MODEL_THI_HUGE_ISLAND_TOP);
    bhv_constant(MODEL_THI_TINY_ISLAND_TOP);
    bhv_constant(MODEL_TTC_ROTATING_CUBE);
    bhv_constant(MODEL_TTC_ROTATING_PRISM);
    bhv_constant(MODEL_TTC_PENDULUM);
    bhv_constant(MODEL_TTC_LARGE_TREADMILL);
    bhv_constant(MODEL_TTC_SMALL_TREADMILL);
    bhv_constant(MODEL_TTC_PUSH_BLOCK);
    bhv_constant(MODEL_TTC_ROTATING_HEXAGON);
    bhv_constant(MODEL_TTC_ROTATING_TRIANGLE);
    bhv_constant(MODEL_TTC_PIT_BLOCK);
    bhv_constant(MODEL_TTC_PIT_BLOCK_UNUSED);
    bhv_constant(MODEL_TTC_ELEVATOR_PLATFORM);
    bhv_constant(MODEL_TTC_CLOCK_HAND);
    bhv_constant(MODEL_TTC_SPINNER);
    bhv_constant(MODEL_TTC_SMALL_GEAR);
    bhv_constant(MODEL_TTC_LARGE_GEAR);
    bhv_constant(MODEL_RR_SLIDING_PLATFORM);
    bhv_constant(MODEL_RR_FLYING_CARPET);
    bhv_constant(MODEL_RR_OCTAGONAL_PLATFORM);
    bhv_constant(MODEL_RR_ROTATING_BRIDGE_PLATFORM);
    bhv_constant(MODEL_RR_TRIANGLE_PLATFORM);
    bhv_constant(MODEL_RR_CRUISER_WING);
    bhv_constant(MODEL_RR_SEESAW_PLATFORM);
    bhv_constant(MODEL_RR_L_SHAPED_PLATFORM);
    bhv_constant(MODEL_RR_SWINGING_PLATFORM);
    bhv_constant(MODEL_RR_DONUT_PLATFORM);
    bhv_constant(MODEL_RR_ELEVATOR_PLATFORM);
    bhv_constant(MODEL_RR_TRICKY_TRIANGLES);
    bhv_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME1);
    bhv_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME2);
    bhv_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME3);
    bhv_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME4);
    bhv_constant(MODEL_BITDW_SQUARE_PLATFORM);
    bhv_constant(MODEL_BITDW_SEESAW_PLATFORM);
    bhv_constant(MODEL_BITDW_SLIDING_PLATFORM);
    bhv_constant(MODEL_BITDW_FERRIS_WHEEL_AXLE);
    bhv_constant(MODEL_BITDW_BLUE_PLATFORM);
    bhv_constant(MODEL_BITDW_STAIRCASE_FRAME4);
    bhv_constant(MODEL_BITDW_STAIRCASE_FRAME3);
    bhv_constant(MODEL_BITDW_STAIRCASE_FRAME2);
    bhv_constant(MODEL_BITDW_STAIRCASE_FRAME1);
    bhv_constant(MODEL_BITDW_STAIRCASE);
    bhv_constant(MODEL_VCUTM_SEESAW_PLATFORM);
    bhv_constant(MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER);
    bhv_constant(MODEL_BITFS_PLATFORM_ON_TRACK);
    bhv_constant(MODEL_BITFS_TILTING_SQUARE_PLATFORM);
    bhv_constant(MODEL_BITFS_SINKING_PLATFORMS);
    bhv_constant(MODEL_BITFS_BLUE_POLE);
    bhv_constant(MODEL_BITFS_SINKING_CAGE_PLATFORM);
    bhv_constant(MODEL_BITFS_ELEVATOR);
    bhv_constant(MODEL_BITFS_STRETCHING_PLATFORMS);
    bhv_constant(MODEL_BITFS_SEESAW_PLATFORM);
    bhv_constant(MODEL_BITFS_MOVING_SQUARE_PLATFORM);
    bhv_constant(MODEL_BITFS_SLIDING_PLATFORM);
    bhv_constant(MODEL_BITFS_TUMBLING_PLATFORM_PART);
    bhv_constant(MODEL_BITFS_TUMBLING_PLATFORM);
    bhv_constant(MODEL_BITS_SLIDING_PLATFORM);
    bhv_constant(MODEL_BITS_TWIN_SLIDING_PLATFORMS);
    bhv_constant(MODEL_BITS_OCTAGONAL_PLATFORM);
    bhv_constant(MODEL_BITS_BLUE_PLATFORM);
    bhv_constant(MODEL_BITS_FERRIS_WHEEL_AXLE);
    bhv_constant(MODEL_BITS_ARROW_PLATFORM);
    bhv_constant(MODEL_BITS_SEESAW_PLATFORM);
    bhv_constant(MODEL_BITS_TILTING_W_PLATFORM);
    bhv_constant(MODEL_BITS_STAIRCASE);
    bhv_constant(MODEL_BITS_STAIRCASE_FRAME1);
    bhv_constant(MODEL_BITS_STAIRCASE_FRAME2);
    bhv_constant(MODEL_BITS_STAIRCASE_FRAME3);
    bhv_constant(MODEL_BITS_STAIRCASE_FRAME4);
    bhv_constant(MODEL_BITS_WARP_PIPE);
    bhv_constant(MODEL_LLL_DRAWBRIDGE_PART);
    bhv_constant(MODEL_LLL_ROTATING_BLOCK_FIRE_BARS);
    bhv_constant(MODEL_LLL_ROTATING_HEXAGONAL_RING);
    bhv_constant(MODEL_LLL_SINKING_RECTANGULAR_PLATFORM);
    bhv_constant(MODEL_LLL_SINKING_SQUARE_PLATFORMS);
    bhv_constant(MODEL_LLL_TILTING_SQUARE_PLATFORM);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_1);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_2);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_3);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_4);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_5);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_6);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_7);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_8);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_9);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_10);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_11);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_12);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_13);
    bhv_constant(MODEL_LLL_BOWSER_PIECE_14);
    bhv_constant(MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM);
    bhv_constant(MODEL_LLL_SINKING_ROCK_BLOCK);
    bhv_constant(MODEL_LLL_ROLLING_LOG);
    bhv_constant(MODEL_LLL_WOOD_BRIDGE);
    bhv_constant(MODEL_LLL_LARGE_WOOD_BRIDGE);
    bhv_constant(MODEL_LLL_FALLING_PLATFORM);
    bhv_constant(MODEL_LLL_LARGE_FALLING_PLATFORM);
    bhv_constant(MODEL_LLL_VOLCANO_FALLING_TRAP);
    bhv_constant(MODEL_DDD_BOWSER_SUB_DOOR);
    bhv_constant(MODEL_DDD_BOWSER_SUB);
    bhv_constant(MODEL_DDD_POLE);
    bhv_constant(MODEL_WF_BREAKABLE_WALL_RIGHT);
    bhv_constant(MODEL_WF_BREAKABLE_WALL_LEFT);
    bhv_constant(MODEL_WF_KICKABLE_BOARD);
    bhv_constant(MODEL_WF_TOWER_DOOR);
    bhv_constant(MODEL_WF_KICKABLE_BOARD_FELLED);
    bhv_constant(MODEL_CASTLE_GROUNDS_VCUTM_GRILL);
    bhv_constant(MODEL_CASTLE_GROUNDS_FLAG);
    bhv_constant(MODEL_CASTLE_GROUNDS_CANNON_GRILL);
    bhv_constant(MODEL_BOWSER_2_TILTING_ARENA);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_1);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_2);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_3);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_4);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_5);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_6);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_7);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_8);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_9);
    bhv_constant(MODEL_BOWSER_3_FALLING_PLATFORM_10);
    bhv_constant(MODEL_TTM_ROLLING_LOG);
    bhv_constant(MODEL_TTM_STAR_CAGE);
    bhv_constant(MODEL_TTM_BLUE_SMILEY);
    bhv_constant(MODEL_TTM_YELLOW_SMILEY);
    bhv_constant(MODEL_TTM_STAR_SMILEY);
    bhv_constant(MODEL_TTM_MOON_SMILEY);
    bhv_constant(MODEL_BULLET_BILL);
    bhv_constant(MODEL_YELLOW_SPHERE);
    bhv_constant(MODEL_HOOT);
    bhv_constant(MODEL_YOSHI_EGG);
    bhv_constant(MODEL_THWOMP);
    bhv_constant(MODEL_HEAVE_HO);
    bhv_constant(MODEL_BLARGG);
    bhv_constant(MODEL_BULLY);
    bhv_constant(MODEL_BULLY_BOSS);
    bhv_constant(MODEL_WATER_BOMB);
    bhv_constant(MODEL_WATER_BOMB_SHADOW);
    bhv_constant(MODEL_KING_BOBOMB);
    bhv_constant(MODEL_MANTA_RAY);
    bhv_constant(MODEL_UNAGI);
    bhv_constant(MODEL_SUSHI);
    bhv_constant(MODEL_DL_WHIRLPOOL);
    bhv_constant(MODEL_CLAM_SHELL);
    bhv_constant(MODEL_POKEY_HEAD);
    bhv_constant(MODEL_POKEY_BODY_PART);
    bhv_constant(MODEL_TWEESTER);
    bhv_constant(MODEL_KLEPTO);
    bhv_constant(MODEL_EYEROK_LEFT_HAND);
    bhv_constant(MODEL_EYEROK_RIGHT_HAND);
    bhv_constant(MODEL_DL_MONTY_MOLE_HOLE);
    bhv_constant(MODEL_MONTY_MOLE);
    bhv_constant(MODEL_UKIKI);
    bhv_constant(MODEL_FWOOSH);
    bhv_constant(MODEL_SPINDRIFT);
    bhv_constant(MODEL_MR_BLIZZARD_HIDDEN);
    bhv_constant(MODEL_MR_BLIZZARD);
    bhv_constant(MODEL_PENGUIN);
    bhv_constant(MODEL_CAP_SWITCH_EXCLAMATION);
    bhv_constant(MODEL_CAP_SWITCH);
    bhv_constant(MODEL_CAP_SWITCH_BASE);
    bhv_constant(MODEL_BOO);
    bhv_constant(MODEL_BETA_BOO_KEY);
    bhv_constant(MODEL_HAUNTED_CHAIR);
    bhv_constant(MODEL_MAD_PIANO);
    bhv_constant(MODEL_BOOKEND_PART);
    bhv_constant(MODEL_BOOKEND);
    bhv_constant(MODEL_HAUNTED_CAGE);
    bhv_constant(MODEL_BIRDS);
    bhv_constant(MODEL_YOSHI);
    bhv_constant(MODEL_ENEMY_LAKITU);
    bhv_constant(MODEL_SPINY_BALL);
    bhv_constant(MODEL_SPINY);
    bhv_constant(MODEL_WIGGLER_HEAD);
    bhv_constant(MODEL_WIGGLER_BODY);
    bhv_constant(MODEL_BUBBA);
    bhv_constant(MODEL_UNKNOWN_54);
    bhv_constant(MODEL_UNKNOWN_58);
    bhv_constant(MODEL_BOWSER);
    bhv_constant(MODEL_BOWSER_BOMB_CHILD_OBJ);
    bhv_constant(MODEL_BOWSER_SMOKE);
    bhv_constant(MODEL_BOWSER_FLAMES);
    bhv_constant(MODEL_BOWSER_WAVE);
    bhv_constant(MODEL_BOWSER2);
    bhv_constant(MODEL_BUB);
    bhv_constant(MODEL_TREASURE_CHEST_BASE);
    bhv_constant(MODEL_TREASURE_CHEST_LID);
    bhv_constant(MODEL_CYAN_FISH);
    bhv_constant(MODEL_WATER_RING);
    bhv_constant(MODEL_SKEETER);
    bhv_constant(MODEL_PIRANHA_PLANT);
    bhv_constant(MODEL_WHOMP);
    bhv_constant(MODEL_KOOPA_WITH_SHELL);
    bhv_constant(MODEL_METALLIC_BALL);
    bhv_constant(MODEL_CHAIN_CHOMP);
    bhv_constant(MODEL_KOOPA_FLAG);
    bhv_constant(MODEL_WOODEN_POST);
    bhv_constant(MODEL_MIPS);
    bhv_constant(MODEL_BOO_CASTLE);
    bhv_constant(MODEL_LAKITU);
    bhv_constant(MODEL_CHILL_BULLY);
    bhv_constant(MODEL_BIG_CHILL_BULLY);
    bhv_constant(MODEL_MONEYBAG);
    bhv_constant(MODEL_SWOOP);
    bhv_constant(MODEL_SCUTTLEBUG);
    bhv_constant(MODEL_MR_I_IRIS);
    bhv_constant(MODEL_MR_I);
    bhv_constant(MODEL_DORRIE);
    bhv_constant(MODEL_YELLOW_COIN);
    bhv_constant(MODEL_YELLOW_COIN_NO_SHADOW);
    bhv_constant(MODEL_BLUE_COIN);
    bhv_constant(MODEL_BLUE_COIN_NO_SHADOW);
    bhv_constant(MODEL_HEART);
    bhv_constant(MODEL_TRANSPARENT_STAR);
    bhv_constant(MODEL_STAR);
    bhv_constant(MODEL_TTM_SLIDE_EXIT_PODIUM);
    bhv_constant(MODEL_WOODEN_SIGNPOST);
    bhv_constant(MODEL_UNKNOWN_7D);
    bhv_constant(MODEL_CANNON_BARREL);
    bhv_constant(MODEL_CANNON_BASE);
    bhv_constant(MODEL_BREAKABLE_BOX);
    bhv_constant(MODEL_BREAKABLE_BOX_SMALL);
    bhv_constant(MODEL_EXCLAMATION_BOX_OUTLINE);
    bhv_constant(MODEL_EXCLAMATION_POINT);
    bhv_constant(MODEL_MARIOS_WINGED_METAL_CAP);
    bhv_constant(MODEL_MARIOS_METAL_CAP);
    bhv_constant(MODEL_MARIOS_WING_CAP);
    bhv_constant(MODEL_MARIOS_CAP);
    bhv_constant(MODEL_EXCLAMATION_BOX);
    bhv_constant(MODEL_DIRT_ANIMATION);
    bhv_constant(MODEL_CARTOON_STAR);
    bhv_constant(MODEL_BLUE_COIN_SWITCH);
    bhv_constant(MODEL_MIST);
    bhv_constant(MODEL_SPARKLES_ANIMATION);
    bhv_constant(MODEL_RED_FLAME);
    bhv_constant(MODEL_BLUE_FLAME);
    bhv_constant(MODEL_BURN_SMOKE);
    bhv_constant(MODEL_SPARKLES);
    bhv_constant(MODEL_SMOKE);
    bhv_constant(MODEL_BURN_SMOKE_UNUSED);
    bhv_constant(MODEL_WHITE_PARTICLE_DL);
    bhv_constant(MODEL_SAND_DUST);
    bhv_constant(MODEL_WHITE_PARTICLE);
    bhv_constant(MODEL_PEBBLE);
    bhv_constant(MODEL_LEAVES);
    bhv_constant(MODEL_WAVE_TRAIL);
    bhv_constant(MODEL_WHITE_PARTICLE_SMALL);
    bhv_constant(MODEL_SMALL_WATER_SPLASH);
    bhv_constant(MODEL_IDLE_WATER_WAVE);
    bhv_constant(MODEL_WATER_SPLASH);
    bhv_constant(MODEL_BUBBLE);
    bhv_constant(MODEL_PURPLE_MARBLE);
    bhv_constant(MODEL_UNKNOWN_AC);
    bhv_constant(MODEL_WF_SLIDING_PLATFORM);
    bhv_constant(MODEL_WF_SMALL_BOMP);
    bhv_constant(MODEL_WF_ROTATING_WOODEN_PLATFORM);
    bhv_constant(MODEL_WF_TUMBLING_BRIDGE_PART);
    bhv_constant(MODEL_WF_LARGE_BOMP);
    bhv_constant(MODEL_WF_TUMBLING_BRIDGE);
    bhv_constant(MODEL_BOWSER_BOMB);
    bhv_constant(MODEL_WATER_MINE);
    bhv_constant(MODEL_BOWLING_BALL);
    bhv_constant(MODEL_TRAMPOLINE);
    bhv_constant(MODEL_TRAMPOLINE_CENTER);
    bhv_constant(MODEL_TRAMPOLINE_BASE);
    bhv_constant(MODEL_UNKNOWN_B8);
    bhv_constant(MODEL_FISH);
    bhv_constant(MODEL_FISH_SHADOW);
    bhv_constant(MODEL_BUTTERFLY);
    bhv_constant(MODEL_BLACK_BOBOMB);
    bhv_constant(MODEL_KOOPA_SHELL);
    bhv_constant(MODEL_KOOPA_WITHOUT_SHELL);
    bhv_constant(MODEL_GOOMBA);
    bhv_constant(MODEL_SEAWEED);
    bhv_constant(MODEL_AMP);
    bhv_constant(MODEL_BOBOMB_BUDDY);
    bhv_constant(MODEL_SSL_TOX_BOX);
    bhv_constant(MODEL_BOWSER_KEY_CUTSCENE);
    bhv_constant(MODEL_DL_CANNON_LID);
    bhv_constant(MODEL_CHECKERBOARD_PLATFORM);
    bhv_constant(MODEL_RED_FLAME_SHADOW);
    bhv_constant(MODEL_BOWSER_KEY);
    bhv_constant(MODEL_EXPLOSION);
    bhv_constant(MODEL_SNUFIT);
    bhv_constant(MODEL_PURPLE_SWITCH);
    bhv_constant(MODEL_CASTLE_STAR_DOOR_30_STARS);
    bhv_constant(MODEL_CASTLE_STAR_DOOR_50_STARS);
    bhv_constant(MODEL_CCM_SNOWMAN_BASE);
    bhv_constant(MODEL_1UP);
    bhv_constant(MODEL_CASTLE_STAR_DOOR_8_STARS);
    bhv_constant(MODEL_CASTLE_STAR_DOOR_70_STARS);
    bhv_constant(MODEL_RED_COIN);
    bhv_constant(MODEL_RED_COIN_NO_SHADOW);
    bhv_constant(MODEL_METAL_BOX);
    bhv_constant(MODEL_METAL_BOX_DL);
    bhv_constant(MODEL_NUMBER);
    bhv_constant(MODEL_FLYGUY);
    bhv_constant(MODEL_TOAD);
    bhv_constant(MODEL_PEACH);
    bhv_constant(MODEL_CHUCKYA);
    bhv_constant(MODEL_WHITE_PUFF);
    bhv_constant(MODEL_TRAJECTORY_MARKER_BALL);
    bhv_constant(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_RED_ERASE_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_BLUE_COPY_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_YELLOW_FILE_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_GREEN_SCORE_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON_FADE);
    bhv_constant(MODEL_MAIN_MENU_MARIO_NEW_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_MARIO_NEW_BUTTON_FADE);
    bhv_constant(MODEL_MAIN_MENU_PURPLE_SOUND_BUTTON);
    bhv_constant(MODEL_MAIN_MENU_GENERIC_BUTTON);
    bhv_constant(MODEL_LLL_ROTATING_HEXAGONAL_PLATFORM);
    bhv_constant(MODEL_WF_GIANT_POLE);
    bhv_constant(MODEL_WF_ROTATING_PLATFORM);
    bhv_constant(MODEL_BITDW_WARP_PIPE);
    bhv_constant(MODEL_THI_WARP_PIPE);
    bhv_constant(MODEL_VCUTM_WARP_PIPE);
    bhv_constant(MODEL_CASTLE_GROUNDS_WARP_PIPE);
    bhv_constant(MODEL_BUBBLE_PLAYER);
    bhv_constant(MODEL_LUIGI);
    bhv_constant(MODEL_LUIGIS_CAP);
    bhv_constant(MODEL_LUIGIS_METAL_CAP);
    bhv_constant(MODEL_LUIGIS_WING_CAP);
    bhv_constant(MODEL_LUIGIS_WINGED_METAL_CAP);
    bhv_constant(MODEL_TOAD_PLAYER);
    bhv_constant(MODEL_TOADS_CAP);
    bhv_constant(MODEL_TOADS_METAL_CAP);
    bhv_constant(MODEL_TOADS_WING_CAP);
    bhv_constant(MODEL_WALUIGI);
    bhv_constant(MODEL_WALUIGIS_CAP);
    bhv_constant(MODEL_WALUIGIS_METAL_CAP);
    bhv_constant(MODEL_WALUIGIS_WING_CAP);
    bhv_constant(MODEL_WALUIGIS_WINGED_METAL_CAP);
    bhv_constant(MODEL_WARIO);
    bhv_constant(MODEL_WARIOS_CAP);
    bhv_constant(MODEL_WARIOS_METAL_CAP);
    bhv_constant(MODEL_WARIOS_WING_CAP);
    bhv_constant(MODEL_WARIOS_WINGED_METAL_CAP);
    bhv_constant(MODEL_ERROR_MODEL);


    // Object Fields
    bhv_constant(oFlags);
    bhv_constant(oDialogResponse);
    bhv_constant(oDialogState);
    bhv_constant(oUnk94);
    bhv_constant(oSyncID);
    bhv_constant(oIntangibleTimer);
    bhv_constant(oPosX);
    bhv_constant(oPosY);
    bhv_constant(oPosZ);
    bhv_constant(oVelX);
    bhv_constant(oVelY);
    bhv_constant(oVelZ);
    bhv_constant(oForwardVel);
    bhv_constant(oForwardVelS32);
    bhv_constant(oUnkBC);
    bhv_constant(oUnkC0);
    bhv_constant(oMoveAnglePitch);
    bhv_constant(oMoveAngleYaw);
    bhv_constant(oMoveAngleRoll);
    bhv_constant(oFaceAnglePitch);
    bhv_constant(oFaceAngleYaw);
    bhv_constant(oFaceAngleRoll);
    bhv_constant(oGraphYOffset);
    bhv_constant(oActiveParticleFlags);
    bhv_constant(oGravity);
    bhv_constant(oFloorHeight);
    bhv_constant(oMoveFlags);
    bhv_constant(oAnimState);
    bhv_constant(oAngleVelPitch);
    bhv_constant(oAngleVelYaw);
    bhv_constant(oAngleVelRoll);
    bhv_constant(oAnimations);
    bhv_constant(oHeldState);
    bhv_constant(oWallHitboxRadius);
    bhv_constant(oDragStrength);
    bhv_constant(oInteractType);
    bhv_constant(oInteractStatus);
    bhv_constant(oParentRelativePosX);
    bhv_constant(oParentRelativePosY);
    bhv_constant(oParentRelativePosZ);
    bhv_constant(oBehParams2ndByte);
    bhv_constant(oAction);
    bhv_constant(oSubAction);
    bhv_constant(oTimer);
    bhv_constant(oBounciness);
    bhv_constant(oDistanceToMario);
    bhv_constant(oAngleToMario);
    bhv_constant(oHomeX);
    bhv_constant(oHomeY);
    bhv_constant(oHomeZ);
    bhv_constant(oFriction);
    bhv_constant(oBuoyancy);
    bhv_constant(oSoundStateID);
    bhv_constant(oOpacity);
    bhv_constant(oDamageOrCoinValue);
    bhv_constant(oHealth);
    bhv_constant(oBehParams);
    bhv_constant(oPrevAction);
    bhv_constant(oInteractionSubtype);
    bhv_constant(oCollisionDistance);
    bhv_constant(oNumLootCoins);
    bhv_constant(oDrawingDistance);
    bhv_constant(oRoom);
    bhv_constant(oSyncDeath);
    bhv_constant(oUnk1A8);
    bhv_constant(oWallAngle);
    bhv_constant(oFloorType);
    bhv_constant(oFloorRoom);
    bhv_constant(oAngleToHome);
    bhv_constant(oFloor);
    bhv_constant(oDeathSound);
    bhv_constant(oPathedStartWaypoint);
    bhv_constant(oPathedPrevWaypoint);
    bhv_constant(oPathedPrevWaypointFlags);
    bhv_constant(oPathedTargetPitch);
    bhv_constant(oPathedTargetYaw);
    bhv_constant(oMacroUnk108);
    bhv_constant(oMacroUnk10C);
    bhv_constant(oMacroUnk110);

    /* 1-UpHidden */
    bhv_constant(o1UpHiddenUnkF4);
    bhv_constant(o1UpForceSpawn);

    /* ActivatedBackandForthPlatform */
    bhv_constant(oActivatedBackAndForthPlatformMaxOffset);
    bhv_constant(oActivatedBackAndForthPlatformOffset);
    bhv_constant(oActivatedBackAndForthPlatformVel);
    bhv_constant(oActivatedBackAndForthPlatformCountdown);
    bhv_constant(oActivatedBackAndForthPlatformStartYaw);
    bhv_constant(oActivatedBackAndForthPlatformVertical);
    bhv_constant(oActivatedBackAndForthPlatformFlipRotation);

    /* Amp */
    bhv_constant(oAmpRadiusOfRotation);
    bhv_constant(oAmpYPhase);

    /* HomingAmp */
    bhv_constant(oHomingAmpLockedOn);
    bhv_constant(oHomingAmpAvgY);

    /* ArrowLift */
    bhv_constant(oArrowLiftDisplacement);
    bhv_constant(oArrowLiftUnk100);

    /* Back-and-ForthPlatform */
    bhv_constant(oBackAndForthPlatformDirection);
    bhv_constant(oBackAndForthPlatformPathLength);
    bhv_constant(oBackAndForthPlatformDistance);
    bhv_constant(oBackAndForthPlatformVel);

    /* Bird */
    bhv_constant(oBirdSpeed);
    bhv_constant(oBirdTargetPitch);
    bhv_constant(oBirdTargetYaw);

    /* BirdChirpChirp */
    bhv_constant(oBirdChirpChirpUnkF4);

    /* EndBirds */
    bhv_constant(oEndBirdUnk104);

    /* HiddenBlueCoin */
    bhv_constant(oHiddenBlueCoinSwitch);

    /* Bob-omb */
    bhv_constant(oBobombBlinkTimer);
    bhv_constant(oBobombFuseLit);
    bhv_constant(oBobombFuseTimer);

    /* Bob-ombBuddy */
    bhv_constant(oBobombBuddyBlinkTimer);
    bhv_constant(oBobombBuddyHasTalkedToMario);
    bhv_constant(oBobombBuddyRole);
    bhv_constant(oBobombBuddyCannonStatus);
    bhv_constant(oBobombBuddyPosXCopy);
    bhv_constant(oBobombBuddyPosYCopy);
    bhv_constant(oBobombBuddyPosZCopy);
    
    /* Bob-ombExplosionBubble */
    bhv_constant(oBobombExpBubGfxScaleFacX);
    bhv_constant(oBobombExpBubGfxScaleFacY);
    bhv_constant(oBobombExpBubGfxExpRateX);
    bhv_constant(oBobombExpBubGfxExpRateY);

    /* Bomp(Small) */
    bhv_constant(oSmallBompInitX);

    /* Boo */
    bhv_constant(oBooDeathStatus);
    bhv_constant(oBooTargetOpacity);
    bhv_constant(oBooBaseScale);
    bhv_constant(oBooOscillationTimer);
    bhv_constant(oBooMoveYawDuringHit);
    bhv_constant(oBooMoveYawBeforeHit);
    bhv_constant(oBooParentBigBoo);
    bhv_constant(oBooNegatedAggressiveness);
    bhv_constant(oBooInitialMoveYaw);
    bhv_constant(oBooTurningSpeed);

    /* BigBoo */
    bhv_constant(oBigBooNumMinionBoosKilled);

    /* Bookend */
    bhv_constant(oBookendUnkF4);
    bhv_constant(oBookendUnkF8);

    /* BookSwitch */
    bhv_constant(oBookSwitchUnkF4);

    /* BookSwitchManager */
    bhv_constant(oBookSwitchManagerUnkF4);
    bhv_constant(oBookSwitchManagerUnkF8);

    /* HauntedBookshelf */
    bhv_constant(oHauntedBookshelfShouldOpen);

    /* BouncingFireBall */
    bhv_constant(oBouncingFireBallUnkF4);

    /* BowlingBall */
    bhv_constant(oBowlingBallTargetYaw);
    //-reservedforpathing

    /* BowlingBallSpawner(Generic) */
    bhv_constant(oBBallSpawnerMaxSpawnDist);
    bhv_constant(oBBallSpawnerSpawnOdds);
    bhv_constant(oBBallSpawnerPeriodMinus1);

    /* Bowser */
    bhv_constant(oBowserUnk88);
    bhv_constant(oBowserUnkF4);
    bhv_constant(oBowserUnkF8);
    bhv_constant(oBowserDistToCentre);
    bhv_constant(oBowserUnk106);
    bhv_constant(oBowserUnk108);
    bhv_constant(oBowserHeldAnglePitch);
    bhv_constant(oBowserHeldAngleVelYaw);
    bhv_constant(oBowserUnk10E);
    bhv_constant(oBowserUnk110);
    bhv_constant(oBowserAngleToCentre);
    bhv_constant(oBowserUnk1AC);
    bhv_constant(oBowserUnk1AE);
    bhv_constant(oBowserEyesShut);
    bhv_constant(oBowserUnk1B2);

    /* BowserShockwave */
    bhv_constant(oBowserShockWaveUnkF4);

    /* BlackSmokeBowser */
    bhv_constant(oBlackSmokeBowserUnkF4);

    /* BowserKeyCutscene */
    bhv_constant(oBowserKeyScale);

    /* BowserPuzzle */
    bhv_constant(oBowserPuzzleCompletionFlags);

    /* BowserPuzzlePiece */
    bhv_constant(oBowserPuzzlePieceOffsetX);
    bhv_constant(oBowserPuzzlePieceOffsetY);
    bhv_constant(oBowserPuzzlePieceOffsetZ);
    bhv_constant(oBowserPuzzlePieceContinuePerformingAction);
    bhv_constant(oBowserPuzzlePieceActionList);
    bhv_constant(oBowserPuzzlePieceNextAction);

    /* Bubba */
    bhv_constant(oBubbaUnkF4);
    bhv_constant(oBubbaUnkF8);
    bhv_constant(oBubbaUnkFC);
    bhv_constant(oBubbaUnk100);
    bhv_constant(oBubbaUnk104);
    bhv_constant(oBubbaUnk108);
    bhv_constant(oBubbaUnk10C);
    bhv_constant(oBubbaUnk1AC);
    bhv_constant(oBubbaUnk1AE);
    bhv_constant(oBubbaUnk1B0);
    bhv_constant(oBubbaUnk1B2);

    /* BulletBill */
    bhv_constant(oBulletBillInitialMoveYaw);

    /* Bully(allvariants) */
    bhv_constant(oBullySubtype);
    bhv_constant(oBullyPrevX);
    bhv_constant(oBullyPrevY);
    bhv_constant(oBullyPrevZ);
    bhv_constant(oBullyKBTimerAndMinionKOCounter);
    bhv_constant(oBullyMarioCollisionAngle);
    bhv_constant(oBullyLastNetworkPlayerIndex);

    /* Butterfly */
    bhv_constant(oButterflyYPhase);

    /* TripletButterfly */
    bhv_constant(oTripletButterflyScale);
    bhv_constant(oTripletButterflySpeed);
    bhv_constant(oTripletButterflyBaseYaw);
    bhv_constant(oTripletButterflyTargetPitch);
    bhv_constant(oTripletButterflyTargetYaw);
    bhv_constant(oTripletButterflyType);
    bhv_constant(oTripletButterflyModel);
    bhv_constant(oTripletButterflySelectedButterfly);
    bhv_constant(oTripletButterflyScalePhase);
    
    /* Cannon */
    bhv_constant(oCannonUnkF4);
    bhv_constant(oCannonUnkF8);
    bhv_constant(oCannonUnk10C);
    bhv_constant(oCannonPlayerIndex);

    /* Cap */
    bhv_constant(oCapUnkF4);
    bhv_constant(oCapUnkF8);

    /* ChainChomp */
    bhv_constant(oChainChompSegments);
    bhv_constant(oChainChompMaxDistFromPivotPerChainPart);
    bhv_constant(oChainChompMaxDistBetweenChainParts);
    bhv_constant(oChainChompDistToPivot);
    bhv_constant(oChainChompUnk104);
    bhv_constant(oChainChompRestrictedByChain);
    bhv_constant(oChainChompTargetPitch);
    bhv_constant(oChainChompNumLunges);
    bhv_constant(oChainChompReleaseStatus);
    bhv_constant(oChainChompHitGate);

    /* CheckerboardPlatform */
    bhv_constant(oCheckerBoardPlatformUnkF8);
    bhv_constant(oCheckerBoardPlatformUnkFC);
    bhv_constant(oCheckerBoardPlatformUnk1AC);

    /* CheepCheep */
    bhv_constant(oCheepCheepUnkF4);
    bhv_constant(oCheepCheepUnkF8);
    bhv_constant(oCheepCheepUnkFC);
    bhv_constant(oCheepCheepUnk104);
    bhv_constant(oCheepCheepUnk108);

    /* Chuckya */
    bhv_constant(oChuckyaUnk88);
    bhv_constant(oChuckyaUnkF8);
    bhv_constant(oChuckyaUnkFC);
    bhv_constant(oChuckyaUnk100);

    /* Clam */
    bhv_constant(oClamUnkF4);

    /* Cloud */
    bhv_constant(oCloudCenterX);
    bhv_constant(oCloudCenterY);
    bhv_constant(oCloudBlowing);
    bhv_constant(oCloudGrowSpeed);
    bhv_constant(oCloudFwooshMovementRadius);

    /* Coin */
    bhv_constant(oCoinUnkF4);
    bhv_constant(oCoinUnkF8);
    bhv_constant(oCoinUnk110);
#ifndef VERSION_JP
    bhv_constant(oCoinUnk1B0);
#endif

    /* CollisionParticle */
    bhv_constant(oCollisionParticleUnkF4);

    /* ControllablePlatform */
    bhv_constant(oControllablePlatformUnkF8);
    bhv_constant(oControllablePlatformUnkFC);
    bhv_constant(oControllablePlatformUnk100);

    /* BreakableBoxSmall(SmallCorkBox) */
    bhv_constant(oBreakableBoxSmallReleased);
    bhv_constant(oBreakableBoxSmallFramesSinceReleased);

    /* JumpingBox(CrazyBox) */
    bhv_constant(oJumpingBoxUnkF4);
    bhv_constant(oJumpingBoxUnkF8);

    /* RRCruiserWing */
    bhv_constant(oRRCruiserWingUnkF4);
    bhv_constant(oRRCruiserWingUnkF8);

    /* DonutPlatformSpawner */
    bhv_constant(oDonutPlatformSpawnerSpawnedPlatforms);

    /* Door */
    bhv_constant(oDoorUnk88);
    bhv_constant(oDoorUnkF8);
    bhv_constant(oDoorUnkFC);
    bhv_constant(oDoorUnk100);

    /* Dorrie */
    bhv_constant(oDorrieDistToHome);
    bhv_constant(oDorrieOffsetY);
    bhv_constant(oDorrieVelY);
    bhv_constant(oDorrieForwardDistToMario);
    bhv_constant(oDorrieYawVel);
    bhv_constant(oDorrieLiftingMario);
    bhv_constant(oDorrieGroundPounded);
    bhv_constant(oDorrieAngleToHome);
    bhv_constant(oDorrieNeckAngle);
    bhv_constant(oDorrieHeadRaiseSpeed);

    /* Elevator */
    bhv_constant(oElevatorUnkF4);
    bhv_constant(oElevatorUnkF8);
    bhv_constant(oElevatorUnkFC);
    bhv_constant(oElevatorUnk100);

    /* ExclamationBox */
    bhv_constant(oExclamationBoxUnkF4);
    bhv_constant(oExclamationBoxUnkF8);
    bhv_constant(oExclamationBoxUnkFC);
    bhv_constant(oExclamationBoxForce);

    /* EyerokBoss */
    bhv_constant(oEyerokBossNumHands);
    bhv_constant(oEyerokBossUnkFC);
    bhv_constant(oEyerokBossActiveHand);
    bhv_constant(oEyerokBossUnk104);
    bhv_constant(oEyerokBossUnk108);
    bhv_constant(oEyerokBossUnk10C);
    bhv_constant(oEyerokBossUnk110);
    bhv_constant(oEyerokBossUnk1AC);

    /* EyerokHand */
    bhv_constant(oEyerokHandWakeUpTimer);
    bhv_constant(oEyerokReceivedAttack);
    bhv_constant(oEyerokHandUnkFC);
    bhv_constant(oEyerokHandUnk100);
    bhv_constant(oEyerokHandDead);

    /* FallingPillar */
    bhv_constant(oFallingPillarPitchAcceleration);

    /* FireSpitter */
    bhv_constant(oFireSpitterScaleVel);
    bhv_constant(oFireSpitterLastWaterY);

    /* BlueFish */
    bhv_constant(oBlueFishRandomVel);
    bhv_constant(oBlueFishRandomTime);
    bhv_constant(oBlueFishRandomAngle);

    /* FishGroup */
    bhv_constant(oFishWaterLevel);
    bhv_constant(oFishGoalY);
    bhv_constant(oFishHeightOffset);
    bhv_constant(oFishYawVel);
    bhv_constant(oFishRoamDistance);
    bhv_constant(oFishGoalVel);
    bhv_constant(oFishDepthDistance);
    bhv_constant(oFishActiveDistance);

    /* Flame */
    bhv_constant(oFlameScale);
    bhv_constant(oFlameSpeedTimerOffset);
    bhv_constant(oFlameUnkFC);
    bhv_constant(oFlameBowser);

    /* BlueFlame */
    bhv_constant(oBlueFlameNextScale);
    
    /* SmallPiranhaFlame */
    bhv_constant(oSmallPiranhaFlameStartSpeed);
    bhv_constant(oSmallPiranhaFlameEndSpeed);
    bhv_constant(oSmallPiranhaFlameModel);
    bhv_constant(oSmallPiranhaFlameNextFlameTimer);
    bhv_constant(oSmallPiranhaFlameSpeed);

    /* MovingFlame */
    bhv_constant(oMovingFlameTimer);

    /* FlamethrowerFlame */
    bhv_constant(oFlameThowerFlameUnk110);

    /* Flamethrower */
    bhv_constant(oFlameThowerUnk110);

    /* FloatingPlatform */
    bhv_constant(oFloatingPlatformUnkF4);
    bhv_constant(oFloatingPlatformUnkF8);
    bhv_constant(oFloatingPlatformUnkFC);
    bhv_constant(oFloatingPlatformUnk100);

    /* FloorSwitchPressAnimation */
    bhv_constant(oFloorSwitchPressAnimationUnkF4);
    bhv_constant(oFloorSwitchPressAnimationUnkF8);
    bhv_constant(oFloorSwitchPressAnimationUnkFC);
    bhv_constant(oFloorSwitchPressAnimationUnk100);

    /* FlyGuy */
    bhv_constant(oFlyGuyIdleTimer);
    bhv_constant(oFlyGuyOscTimer);
    bhv_constant(oFlyGuyUnusedJitter);
    bhv_constant(oFlyGuyLungeYDecel);
    bhv_constant(oFlyGuyLungeTargetPitch);
    bhv_constant(oFlyGuyTargetRoll);
    bhv_constant(oFlyGuyScaleVel);

    /* GrandStar */
    bhv_constant(oGrandStarUnk108);

    /* HorizontalGrindel */
    bhv_constant(oHorizontalGrindelTargetYaw);
    bhv_constant(oHorizontalGrindelDistToHome);
    bhv_constant(oHorizontalGrindelOnGround);

    /* Goomba */
    bhv_constant(oGoombaSize);
    bhv_constant(oGoombaScale);
    bhv_constant(oGoombaWalkTimer);
    bhv_constant(oGoombaTargetYaw);
    bhv_constant(oGoombaBlinkTimer);
    bhv_constant(oGoombaTurningAwayFromWall);
    bhv_constant(oGoombaRelativeSpeed);
    bhv_constant(oGoombaJumpCooldown);

    /* HauntedChair */
    bhv_constant(oHauntedChairUnkF4);
    bhv_constant(oHauntedChairUnkF8);
    bhv_constant(oHauntedChairUnkFC);
    bhv_constant(oHauntedChairUnk100);
    bhv_constant(oHauntedChairUnk104);

    /* Heave-Ho */
    bhv_constant(oHeaveHoUnk88);
    bhv_constant(oHeaveHoUnkF4);

    /* HiddenObject */
    bhv_constant(oHiddenObjectUnkF4);

    /* Hoot */
    bhv_constant(oHootAvailability);
    bhv_constant(oHootMarioReleaseTime);

    /* HorizontalMovement */
    bhv_constant(oHorizontalMovementUnkF4);
    bhv_constant(oHorizontalMovementUnkF8);
    bhv_constant(oHorizontalMovementUnk100);
    bhv_constant(oHorizontalMovementUnk104);
    bhv_constant(oHorizontalMovementUnk108);

    /* KickableBoard */
    bhv_constant(oKickableBoardF4);
    bhv_constant(oKickableBoardF8);

    /* KingBob-omb */
    bhv_constant(oKingBobombUnk88);
    bhv_constant(oKingBobombUnkF8);
    bhv_constant(oKingBobombUnkFC);
    bhv_constant(oKingBobombUnk100);
    bhv_constant(oKingBobombUnk104);
    bhv_constant(oKingBobombUnk108);

    /* Klepto */
    bhv_constant(oKleptoDistanceToTarget);
    bhv_constant(oKleptoUnkF8);
    bhv_constant(oKleptoUnkFC);
    bhv_constant(oKleptoSpeed);
    bhv_constant(oKleptoStartPosX);
    bhv_constant(oKleptoStartPosY);
    bhv_constant(oKleptoStartPosZ);
    bhv_constant(oKleptoTimeUntilTargetChange);
    bhv_constant(oKleptoTargetNumber);
    bhv_constant(oKleptoUnk1AE);
    bhv_constant(oKleptoUnk1B0);
    bhv_constant(oKleptoYawToTarget);

    /* Koopa */
    bhv_constant(oKoopaAgility);
    bhv_constant(oKoopaMovementType);
    bhv_constant(oKoopaTargetYaw);
    bhv_constant(oKoopaUnshelledTimeUntilTurn);
    bhv_constant(oKoopaTurningAwayFromWall);
    bhv_constant(oKoopaDistanceToMario);
    bhv_constant(oKoopaAngleToMario);
    bhv_constant(oKoopaBlinkTimer);
    bhv_constant(oKoopaCountdown);
    bhv_constant(oKoopaTheQuickRaceIndex);
    bhv_constant(oKoopaTheQuickInitTextboxCooldown);
    //-forkoopathequickreservedforpathing

    /* KoopaRaceEndpoint */
    bhv_constant(oKoopaRaceEndpointRaceBegun);
    bhv_constant(oKoopaRaceEndpointKoopaFinished);
    bhv_constant(oKoopaRaceEndpointRaceStatus);
    bhv_constant(oKoopaRaceEndpointUnk100);
    bhv_constant(oKoopaRaceEndpointRaceEnded);

    /* KoopaShellFlame */
    bhv_constant(oKoopaShellFlameUnkF4);
    bhv_constant(oKoopaShellFlameUnkF8);

    /* CameraLakitu */
    bhv_constant(oCameraLakituBlinkTimer);
    bhv_constant(oCameraLakituSpeed);
    bhv_constant(oCameraLakituCircleRadius);
    bhv_constant(oCameraLakituFinishedDialog);
#ifndef VERSION_JP
    bhv_constant(oCameraLakituUnk104);
#endif
    bhv_constant(oCameraLakituPitchVel);
    bhv_constant(oCameraLakituYawVel);

    /* EvilLakitu */
    bhv_constant(oEnemyLakituNumSpinies);
    bhv_constant(oEnemyLakituBlinkTimer);
    bhv_constant(oEnemyLakituSpinyCooldown);
    bhv_constant(oEnemyLakituFaceForwardCountdown);
    
    /* IntroCutsceneLakitu */
    bhv_constant(oIntroLakituSplineSegmentProgress);
    bhv_constant(oIntroLakituSplineSegment);
    bhv_constant(oIntroLakituUnk100);
    bhv_constant(oIntroLakituUnk104);
    bhv_constant(oIntroLakituUnk108);
    bhv_constant(oIntroLakituUnk10C);
    bhv_constant(oIntroLakituUnk110);
    bhv_constant(oIntroLakituCloud);

    /* MainMenuButton */
    bhv_constant(oMenuButtonState);
    bhv_constant(oMenuButtonTimer);
    bhv_constant(oMenuButtonOrigPosX);
    bhv_constant(oMenuButtonOrigPosY);
    bhv_constant(oMenuButtonOrigPosZ);
    bhv_constant(oMenuButtonScale);
    bhv_constant(oMenuButtonActionPhase);
    bhv_constant(oMenuButtonIsCustom);

    /* MantaRay */
    bhv_constant(oMantaTargetPitch);
    bhv_constant(oMantaTargetYaw);

    /* Merry-Go-Round */
    bhv_constant(oMerryGoRoundStopped);
    bhv_constant(oMerryGoRoundMusicShouldPlay);
    bhv_constant(oMerryGoRoundMarioIsOutside);

    /* Merry-Go-RoundBooManager */
    bhv_constant(oMerryGoRoundBooManagerNumBoosKilled);
    bhv_constant(oMerryGoRoundBooManagerNumBoosSpawned);

    /* Mips */
    bhv_constant(oMipsStarStatus);
    bhv_constant(oMipsStartWaypointIndex);
    //-reservedforpathing
    bhv_constant(oMipsForwardVelocity);

    /* Moneybag */
    bhv_constant(oMoneybagJumpState);

    /* MontyMole */
    bhv_constant(oMontyMoleCurrentHole);
    bhv_constant(oMontyMoleHeightRelativeToFloor);
    bhv_constant(oMontyMoleHoleX);
    bhv_constant(oMontyMoleHoleY);
    bhv_constant(oMontyMoleHoleZ);

    /* MontyMoleHole */
    bhv_constant(oMontyMoleHoleCooldown);

    /* Mr.Blizzard */
    bhv_constant(oMrBlizzardScale);
    bhv_constant(oMrBlizzardHeldObj);
    bhv_constant(oMrBlizzardGraphYVel);
    bhv_constant(oMrBlizzardTimer);
    bhv_constant(oMrBlizzardDizziness);
    bhv_constant(oMrBlizzardChangeInDizziness);
    bhv_constant(oMrBlizzardGraphYOffset);
    bhv_constant(oMrBlizzardDistFromHome);
    bhv_constant(oMrBlizzardTargetMoveYaw);

    /* Mr.I */
    bhv_constant(oMrIUnkF4);
    bhv_constant(oMrIUnkFC);
    bhv_constant(oMrIUnk100);
    bhv_constant(oMrIUnk104);
    bhv_constant(oMrIUnk108);
    bhv_constant(oMrISize);
    bhv_constant(oMrIUnk110);

    /* ObjectRespawner */
    bhv_constant(oRespawnerModelToRespawn);
    bhv_constant(oRespawnerMinSpawnDist);
    bhv_constant(oRespawnerBehaviorToRespawn);

    /* OpenableGrill */
    bhv_constant(oOpenableGrillUnk88);
    bhv_constant(oOpenableGrillUnkF4);

    /* IntroCutscenePeach */
    bhv_constant(oIntroPeachYawFromFocus);
    bhv_constant(oIntroPeachPitchFromFocus);
    bhv_constant(oIntroPeachDistToCamera);

    /* RacingPenguin */
    bhv_constant(oRacingPenguinInitTextCooldown);
    //-reservedforpathing
    bhv_constant(oRacingPenguinWeightedNewTargetSpeed);
    bhv_constant(oRacingPenguinFinalTextbox);
    bhv_constant(oRacingPenguinMarioWon);
    bhv_constant(oRacingPenguinReachedBottom);
    bhv_constant(oRacingPenguinMarioCheated);

    /* SmallPenguin */
    bhv_constant(oSmallPenguinUnk88);
    bhv_constant(oSmallPenguinUnk100);
    bhv_constant(oSmallPenguinUnk104);
    bhv_constant(oSmallPenguinUnk108);
    bhv_constant(oSmallPenguinUnk110);

    /* SLWalkingPenguin */
    bhv_constant(oSLWalkingPenguinWindCollisionXPos);
    bhv_constant(oSLWalkingPenguinWindCollisionZPos);
    bhv_constant(oSLWalkingPenguinCurStep);
    bhv_constant(oSLWalkingPenguinCurStepTimer);

    /* PiranhaPlant */
    bhv_constant(oPiranhaPlantSleepMusicState);
    bhv_constant(oPiranhaPlantScale);

    /* FirePiranhaPlant */
    bhv_constant(oFirePiranhaPlantNeutralScale);
    bhv_constant(oFirePiranhaPlantScale);
    bhv_constant(oFirePiranhaPlantActive);
    bhv_constant(oFirePiranhaPlantDeathSpinTimer);
    bhv_constant(oFirePiranhaPlantDeathSpinVel);

    /* Pitoune */
    bhv_constant(oPitouneUnkF4);
    bhv_constant(oPitouneUnkF8);
    bhv_constant(oPitouneUnkFC);

    /* Platform */
    bhv_constant(oPlatformTimer);
    bhv_constant(oPlatformUnkF8);
    bhv_constant(oPlatformUnkFC);
    bhv_constant(oPlatformUnk10C);
    bhv_constant(oPlatformUnk110);

    /* PlatformonTracks */
    bhv_constant(oPlatformOnTrackBaseBallIndex);
    bhv_constant(oPlatformOnTrackDistMovedSinceLastBall);
    bhv_constant(oPlatformOnTrackSkiLiftRollVel);
    bhv_constant(oPlatformOnTrackStartWaypoint);
    bhv_constant(oPlatformOnTrackPrevWaypoint);
    bhv_constant(oPlatformOnTrackPrevWaypointFlags);
    bhv_constant(oPlatformOnTrackPitch);
    bhv_constant(oPlatformOnTrackYaw);
    bhv_constant(oPlatformOnTrackOffsetY);
    bhv_constant(oPlatformOnTrackIsNotSkiLift);
    bhv_constant(oPlatformOnTrackIsNotHMC);
    bhv_constant(oPlatformOnTrackType);
    bhv_constant(oPlatformOnTrackWasStoodOn);

    /* PlatformSpawner */
    bhv_constant(oPlatformSpawnerUnkF4);
    bhv_constant(oPlatformSpawnerUnkF8);
    bhv_constant(oPlatformSpawnerUnkFC);
    bhv_constant(oPlatformSpawnerUnk100);
    bhv_constant(oPlatformSpawnerUnk104);
    bhv_constant(oPlatformSpawnerUnk108);

    /* Pokey */
    bhv_constant(oPokeyAliveBodyPartFlags);
    bhv_constant(oPokeyNumAliveBodyParts);
    bhv_constant(oPokeyBottomBodyPartSize);
    bhv_constant(oPokeyHeadWasKilled);
    bhv_constant(oPokeyTargetYaw);
    bhv_constant(oPokeyChangeTargetTimer);
    bhv_constant(oPokeyTurningAwayFromWall);

    /* PokeyBodyPart */
    bhv_constant(oPokeyBodyPartDeathDelayAfterHeadKilled);
    bhv_constant(oPokeyBodyPartBlinkTimer);

    /* DDDPole */
    bhv_constant(oDDDPoleVel);
    bhv_constant(oDDDPoleMaxOffset);
    bhv_constant(oDDDPoleOffset);

    /* PyramidTop */
    bhv_constant(oPyramidTopPillarsTouched);

    /* PyramidTopExplosion */
    bhv_constant(oPyramidTopFragmentsScale);

    /* RollingLog */
    bhv_constant(oRollingLogUnkF4);

    /* LllRotatingHexFlame */
    bhv_constant(oLllRotatingHexFlameUnkF4);
    bhv_constant(oLllRotatingHexFlameUnkF8);
    bhv_constant(oLllRotatingHexFlameUnkFC);

    /* Scuttlebug */
    bhv_constant(oScuttlebugUnkF4);
    bhv_constant(oScuttlebugUnkF8);
    bhv_constant(oScuttlebugUnkFC);

    /* ScuttlebugSpawner */
    bhv_constant(oScuttlebugSpawnerUnk88);
    bhv_constant(oScuttlebugSpawnerUnkF4);

    /* SeesawPlatform */
    bhv_constant(oSeesawPlatformPitchVel);

    /* ShipPart3 */
    bhv_constant(oShipPart3UnkF4);
    bhv_constant(oShipPart3UnkF8);

    /* SinkWhenSteppedOn */
    bhv_constant(oSinkWhenSteppedOnUnk104);
    bhv_constant(oSinkWhenSteppedOnUnk108);

    /* Skeeter */
    bhv_constant(oSkeeterTargetAngle);
    bhv_constant(oSkeeterUnkF8);
    bhv_constant(oSkeeterUnkFC);
    bhv_constant(oSkeeterWaitTime);
    bhv_constant(oSkeeterLastWaterY);
    bhv_constant(oSkeeterUnk1AC);

    /* JrbSlidingBox */
    bhv_constant(oJrbSlidingBoxUnkF4);
    bhv_constant(oJrbSlidingBoxUnkF8);
    bhv_constant(oJrbSlidingBoxUnkFC);

    /* WFSlidingBrickPlatform */
    bhv_constant(oWFSlidBrickPtfmMovVel);

    /* Smoke */
    bhv_constant(oSmokeTimer);

    /* Snowman'sBottom */
    bhv_constant(oSnowmansBottomUnkF4);
    bhv_constant(oSnowmansBottomUnkF8);
    bhv_constant(oSnowmansBottomUnk1AC);
    //-reservedforpathing

    /* Snowman'sHead */
    bhv_constant(oSnowmansHeadUnkF4);

    /* SnowmanWindBlowing */
    bhv_constant(oSLSnowmanWindOriginalYaw);

    /* Snufit */
    bhv_constant(oSnufitRecoil);
    bhv_constant(oSnufitScale);
    bhv_constant(oSnufitCircularPeriod);
    bhv_constant(oSnufitBodyScalePeriod);
    bhv_constant(oSnufitBodyBaseScale);
    bhv_constant(oSnufitBullets);
    bhv_constant(oSnufitXOffset);
    bhv_constant(oSnufitYOffset);
    bhv_constant(oSnufitZOffset);
    bhv_constant(oSnufitBodyScale);

    /* Spindel */
    bhv_constant(oSpindelUnkF4);
    bhv_constant(oSpindelUnkF8);

    /* SpinningHeart */
    bhv_constant(oSpinningHeartTotalSpin);
    bhv_constant(oSpinningHeartPlayedSound);

    /* Spiny */
    bhv_constant(oSpinyTimeUntilTurn);
    bhv_constant(oSpinyTargetYaw);
    bhv_constant(oSpinyTurningAwayFromWall);

    /* SoundEffect */
    bhv_constant(oSoundEffectUnkF4);

    /* StarSpawn */
    bhv_constant(oStarSpawnDisFromHome);
    bhv_constant(oStarSpawnUnkFC);
    bhv_constant(oStarSpawnExtCutsceneFlags);

    /* HiddenStar */
    //Secrets/RedCoins
    bhv_constant(oHiddenStarTriggerCounter);
    bhv_constant(oHiddenStarLastInteractedObject);
    
    //Overallverydifficulttodetermineusage,mostlystubbedcode.
    /* SparkleSpawnStar */
    bhv_constant(oSparkleSpawnUnk1B0);

    /* SealedDoorStar */
    bhv_constant(oUnlockDoorStarState);
    bhv_constant(oUnlockDoorStarTimer);
    bhv_constant(oUnlockDoorStarYawVel);

    /* CelebrationStar */
    bhv_constant(oCelebStarUnkF4);
    bhv_constant(oCelebStarDiameterOfRotation);

    /* StarSelector */
    bhv_constant(oStarSelectorType);
    bhv_constant(oStarSelectorTimer);
    bhv_constant(oStarSelectorSize);

    /* SushiShark */
    bhv_constant(oSushiSharkUnkF4);

    /* SwingPlatform */
    bhv_constant(oSwingPlatformAngle);
    bhv_constant(oSwingPlatformSpeed);

    /* Swoop */
    bhv_constant(oSwoopBonkCountdown);
    bhv_constant(oSwoopTargetPitch);
    bhv_constant(oSwoopTargetYaw);

    /* Thwomp */
    bhv_constant(oThwompRandomTimer);

    /* TiltingPlatform */
    bhv_constant(oTiltingPyramidNormalX);
    bhv_constant(oTiltingPyramidNormalY);
    bhv_constant(oTiltingPyramidNormalZ);
    bhv_constant(oTiltingPyramidMarioOnPlatform);

    /* ToadMessage */
    bhv_constant(oToadMessageDialogId);
    bhv_constant(oToadMessageRecentlyTalked);
    bhv_constant(oToadMessageState);

    /* ToxBox */
    bhv_constant(oToxBoxMovementPattern);
    bhv_constant(oToxBoxMovementStep);

    /* TTCRotatingSolid */
    bhv_constant(oTTCRotatingSolidNumTurns);
    bhv_constant(oTTCRotatingSolidNumSides);
    bhv_constant(oTTCRotatingSolidRotationDelay);
    bhv_constant(oTTCRotatingSolidVelY);
    bhv_constant(oTTCRotatingSolidSoundTimer);

    /* TTCPendulum */
    bhv_constant(oTTCPendulumAccelDir);
    bhv_constant(oTTCPendulumAngle);
    bhv_constant(oTTCPendulumAngleVel);
    bhv_constant(oTTCPendulumAngleAccel);
    bhv_constant(oTTCPendulumDelay);
    bhv_constant(oTTCPendulumSoundTimer);

    /* TTCTreadmill */
    bhv_constant(oTTCTreadmillBigSurface);
    bhv_constant(oTTCTreadmillSmallSurface);
    bhv_constant(oTTCTreadmillSpeed);
    bhv_constant(oTTCTreadmillTargetSpeed);
    bhv_constant(oTTCTreadmillTimeUntilSwitch);

    /* TTCMovingBar */
    bhv_constant(oTTCMovingBarDelay);
    bhv_constant(oTTCMovingBarStoppedTimer);
    bhv_constant(oTTCMovingBarOffset);
    bhv_constant(oTTCMovingBarSpeed);
    bhv_constant(oTTCMovingBarStartOffset);

    /* TTCCog */
    bhv_constant(oTTCCogDir);
    bhv_constant(oTTCCogSpeed);
    bhv_constant(oTTCCogTargetVel);

    /* TTCPitBlock */
    bhv_constant(oTTCPitBlockPeakY);
    bhv_constant(oTTCPitBlockDir);
    bhv_constant(oTTCPitBlockWaitTime);

    /* TTCElevator */
    bhv_constant(oTTCElevatorDir);
    bhv_constant(oTTCElevatorPeakY);
    bhv_constant(oTTCElevatorMoveTime);

    /* TTC2DRotator */
    bhv_constant(oTTC2DRotatorMinTimeUntilNextTurn);
    bhv_constant(oTTC2DRotatorTargetYaw);
    bhv_constant(oTTC2DRotatorIncrement);
    bhv_constant(oTTC2DRotatorRandomDirTimer);
    bhv_constant(oTTC2DRotatorSpeed);

    /* TTCSpinner */
    bhv_constant(oTTCSpinnerDir);
    bhv_constant(oTTCChangeDirTimer);

    /* BetaTrampoline */
    bhv_constant(oBetaTrampolineMarioOnTrampoline);

    /* TreasureChest */
    bhv_constant(oTreasureChestCurrentAnswer);
    bhv_constant(oTreasureChestIsLastInteractionIncorrect);
    bhv_constant(oTreasureChestIsAboveWater);
    bhv_constant(oTreasureChestSound);
    bhv_constant(oTreasureChestLastNetworkPlayerIndex);

    /* TreeSnowOrLeaf */
    bhv_constant(oTreeSnowOrLeafUnkF4);
    bhv_constant(oTreeSnowOrLeafUnkF8);
    bhv_constant(oTreeSnowOrLeafUnkFC);

    /* TumblingBridge */
    bhv_constant(oTumblingBridgeUnkF4);

    /* Tweester */
    bhv_constant(oTweesterScaleTimer);
    bhv_constant(oTweesterUnused);

    /* Ukiki */
    bhv_constant(oUkikiTauntCounter);
    bhv_constant(oUkikiTauntsToBeDone);
    //-reservedforpathing
    bhv_constant(oUkikiChaseFleeRange);
    bhv_constant(oUkikiTextState);
    bhv_constant(oUkikiTextboxTimer);
    bhv_constant(oUkikiCageSpinTimer);
    bhv_constant(oUkikiHasCap);

    /* UkikiCage */
    bhv_constant(oUkikiCageNextAction);

    /* Unagi */
    bhv_constant(oUnagiUnkF4);
    bhv_constant(oUnagiUnkF8);
    //-reservedforpathing
    bhv_constant(oUnagiUnk110);
    bhv_constant(oUnagiUnk1AC);
    bhv_constant(oUnagiUnk1B0);
    bhv_constant(oUnagiUnk1B2);

    /* WaterBomb */
    bhv_constant(oWaterBombVerticalStretch);
    bhv_constant(oWaterBombStretchSpeed);
    bhv_constant(oWaterBombOnGround);
    bhv_constant(oWaterBombNumBounces);

    /* WaterBombSpawner */
    bhv_constant(oWaterBombSpawnerBombActive);
    bhv_constant(oWaterBombSpawnerTimeToSpawn);

    /* WaterBombCannon */
    bhv_constant(oWaterCannonUnkF4);
    bhv_constant(oWaterCannonUnkF8);
    bhv_constant(oWaterCannonUnkFC);
    bhv_constant(oWaterCannonUnk100);

    /* CannonBarrelBubbles */
    bhv_constant(oCannonBarrelBubblesUnkF4);

    /* WaterLevelPillar */
    bhv_constant(oWaterLevelPillarDrained);

    /* WaterLevelTrigger */
    bhv_constant(oWaterLevelTriggerUnkF4);
    bhv_constant(oWaterLevelTriggerTargetWaterLevel);

    /* WaterObjects */
    bhv_constant(oWaterObjUnkF4);
    bhv_constant(oWaterObjUnkF8);
    bhv_constant(oWaterObjUnkFC);
    bhv_constant(oWaterObjUnk100);

    /* WaterRing(bothvariants) */
    bhv_constant(oWaterRingScalePhaseX);
    bhv_constant(oWaterRingScalePhaseY);
    bhv_constant(oWaterRingScalePhaseZ);
    bhv_constant(oWaterRingNormalX);
    bhv_constant(oWaterRingNormalY);
    bhv_constant(oWaterRingNormalZ);
    bhv_constant(oWaterRingMarioDistInFront);
    bhv_constant(oWaterRingIndex);
    bhv_constant(oWaterRingAvgScale);

    /* WaterRingSpawner(JetStreamRingSpawnerandMantaRay) */
    bhv_constant(oWaterRingSpawnerRingsCollected);

    /* WaterRingManager(JetStreamRingSpawnerandMantaRayRingManager) */
    bhv_constant(oWaterRingMgrNextRingIndex);
    bhv_constant(oWaterRingMgrLastRingCollected);

    /* WaveTrail */
    bhv_constant(oWaveTrailSize);

    /* Whirlpool */
    bhv_constant(oWhirlpoolInitFacePitch);
    bhv_constant(oWhirlpoolInitFaceRoll);
    bhv_constant(oWhirlpoolTimeout);

    /* WhitePuffExplode */
    bhv_constant(oWhitePuffUnkF4);
    bhv_constant(oWhitePuffUnkF8);
    bhv_constant(oWhitePuffUnkFC);

    /* WhiteWindParticle */
    bhv_constant(oStrongWindParticlePenguinObj);

    /* Whomp */
    bhv_constant(oWhompShakeVal);

    /* Wiggler */
    bhv_constant(oWigglerFallThroughFloorsHeight);
    bhv_constant(oWigglerSegments);
    bhv_constant(oWigglerWalkAnimSpeed);
    bhv_constant(oWigglerSquishSpeed);
    bhv_constant(oWigglerTimeUntilRandomTurn);
    bhv_constant(oWigglerTargetYaw);
    bhv_constant(oWigglerWalkAwayFromWallTimer);
    bhv_constant(oWigglerUnused);
    bhv_constant(oWigglerTextStatus);

    /* LllWoodPiece */
    bhv_constant(oLllWoodPieceOscillationTimer);

    /* WoodenPost */
    bhv_constant(oWoodenPostTotalMarioAngle);
    bhv_constant(oWoodenPostPrevAngleToMario);
    bhv_constant(oWoodenPostSpeedY);
    bhv_constant(oWoodenPostMarioPounding);
    bhv_constant(oWoodenPostOffsetY);

    /* Yoshi */
    bhv_constant(oYoshiBlinkTimer);
    bhv_constant(oYoshiChosenHome);
    bhv_constant(oYoshiTargetYaw);

    /* BreakableWall */
    bhv_constant(oBreakableWallForce);

    *found = false;
    return 0;
}

template <typename T>
DataNode<T> *FindDataNode(DataNodes<T> &aDataNodes, String &aName, u32 aModelIdentifier) {
    DataNode<T> *best = NULL;
    for (auto& node : aDataNodes) {
        if (aName == node->mName) {
            if (aModelIdentifier == node->mModelIdentifier) {
                return node;
            }
            best = node;
        }
    }
    return best;
}

static BehaviorScript ParseBehaviorScriptSymbolArgInternal(GfxData *aGfxData, DataNode<BehaviorScript> *aNode, u64 &aTokenIndex, bool *found) {
    String _Arg = aNode->mTokens[aTokenIndex++];
    u64 _ModelIdentifier = aNode->mModelIdentifier;
    *found = true;
    
    // Built-in functions
    const void *_FunctionPtr = DynOS_Builtin_Func_GetFromName(_Arg.begin());
    if (_FunctionPtr != NULL) {
        return (s64) _FunctionPtr;
    }

    // Built-in actors
    auto builtinActor = DynOS_Builtin_Actor_GetFromName(_Arg.begin());
    if (builtinActor != NULL) {
        return (BehaviorScript)builtinActor;
    }

    // Built-in Lvl Geos
    auto builtinGeo = DynOS_Builtin_LvlGeo_GetFromName(_Arg.begin());
    if (builtinGeo != NULL) {
        return (BehaviorScript)builtinGeo;
    }

    // Built-in Cols
    auto builtinCol = DynOS_Builtin_Col_GetFromName(_Arg.begin());
    if (builtinCol != NULL) {
        return (BehaviorScript)builtinCol;
    }
    
    // Built-in Animations
    auto builtinAnim = DynOS_Builtin_Anim_GetFromName(_Arg.begin());
    if (builtinAnim != NULL) {
        return (BehaviorScript)builtinAnim;
    }
    
    // Brackets
    // Make sure we parse out the brackets if they are present.
    if (_Arg[0] == '(') {
        // Remove first bracket.
        _Arg = _Arg.SubString(1);
        
        s32 _Brk = _Arg.FindLast(')');
        
        // Remove last bracket.
        if (_Brk != -1) { _Arg = _Arg.SubString(0, _Brk); }
    }
    
    /*
    // Offset
    s32 _Offset = 0;
    s32 _Plus = -1;
    // Make sure we parse out all additions or offsets.
    do {
        _Plus = _Arg.FindLast('+');
        
        // If we didn't find anything. Break early.
        if (_Plus == -1) { break; }
        
        _Offset += _Arg.SubString(_Plus + 1).ParseInt();
        _Arg = _Arg.SubString(0, _Plus);
    }
    while(_Plus != -1);
    */

    // OR Operations
    s32 _OrValue = 0;
    s32 _Or = -1;
    // Make sure we parse out all or operations.
    do {
        _Or = _Arg.FindLast('|');
        
        // If we didn't find anything. Break early.
        if (_Or == -1) { break; }
        
        bool constantFound = false;
        s64 constantValue = DynOS_Bhv_ParseBehaviorIntegerScriptConstants(_Arg.SubString(_Or + 1), &constantFound);
        
        if (constantFound) {
            _OrValue |= constantValue;
        } else {
            _OrValue |= _Arg.SubString(_Or + 1).ParseInt();
        }
        
        _Arg = _Arg.SubString(0, _Or);
    }
    while(_Or != -1);
    
    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        // Support OR operations on integers.
        if (_OrValue != 0) { integerValue |= _OrValue; }
        return integerValue;
    }
    
    // Parse integer constants
    bool intConstantFound = false;
    s64 constantIntValue = DynOS_Bhv_ParseBehaviorIntegerScriptConstants(_Arg, &intConstantFound);
    if (intConstantFound) {
        // Support OR operations on integer constants.
        if (_OrValue != 0) { constantIntValue |= _OrValue; }
        return (BehaviorScript) constantIntValue;
    }
    
    // Recursive descent parsing
    bool rdIntSuccess = false;
    s64 rdIntValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdIntSuccess, DynOS_Bhv_ParseBehaviorIntegerScriptConstants);
    if (rdIntSuccess) {
        // Support OR operations on integer constants.
        if (_OrValue != 0) { rdIntValue |= _OrValue; }
        return (BehaviorScript)rdIntValue;
    }
    
    // Parse all other constants last so everything else is found for certain.
    bool constantFound = false;
    s64 constantValue = DynOS_Bhv_ParseBehaviorScriptConstants(_Arg, &constantFound);
    if (constantFound) {
        return (BehaviorScript) constantValue;
    }
    
    // Recursive descent parsing
    bool rdSuccess = false;
    s64 rdValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdSuccess, DynOS_Bhv_ParseBehaviorScriptConstants);
    if (rdSuccess) {
        return (BehaviorScript)rdValue;
    }

    *found = false;
    return 0;
}

static BehaviorScript ParseBehaviorScriptSymbolArg(GfxData *aGfxData, DataNode<BehaviorScript> *aNode, u64 &aTokenIndex) {
    bool found = true;
    BehaviorScript value = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &found);
    if (!found) {
        const String &_Arg = aNode->mTokens[aTokenIndex - 1];
        PrintError("  ERROR: Unknown bhv arg: %s", _Arg.begin());
    }
    return value;
}

#define AddPointerToList(symbol, aGfxData, pointer) \
    /*Print("%s: Adding pointer %x to list.", symbol, pointer);*/ \
    aGfxData->mPointerList.Add(pointer); \

#define bhv_symbol_0(symb)                       \
    if (_Symbol == #symb) {                      \
        BehaviorScript _Bs[] = { symb() };          \
        memcpy(aHead, _Bs, sizeof(_Bs));         \
        aHead += (sizeof(_Bs) / sizeof(_Bs[0])); \
        return;                                  \
    }
    
#define bhv_symbol_1(symb, n)                                                              \
    if (_Symbol == #symb) {                                                                \
        BehaviorScript _Arg0 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { AddPointerToList(#symb, aGfxData, aHead + n); }                      \
        BehaviorScript _Bs[] = { symb(_Arg0) };                                            \
        memcpy(aHead, _Bs, sizeof(_Bs));                                                   \
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));                                           \
        return;                                                                            \
    }
    
#define bhv_symbol_2(symb, n1, n2)                                                         \
    if (_Symbol == #symb) {                                                                \
        BehaviorScript _Arg0 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        BehaviorScript _Arg1 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { AddPointerToList(#symb, aGfxData, aHead + n1); }                    \
        if (n2 != 0) { AddPointerToList(#symb, aGfxData, aHead + n2); }                    \
        BehaviorScript _Bs[] = { symb(_Arg0, _Arg1) };                                     \
        memcpy(aHead, _Bs, sizeof(_Bs));                                                   \
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));                                           \
        return;                                                                            \
    }
    
#define bhv_symbol_3(symb, n1, n2, n3)                                                     \
    if (_Symbol == #symb) {                                                                \
        BehaviorScript _Arg0 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        BehaviorScript _Arg1 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        BehaviorScript _Arg2 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { AddPointerToList(#symb, aGfxData, aHead + n1); }                    \
        if (n2 != 0) { AddPointerToList(#symb, aGfxData, aHead + n2); }                    \
        if (n3 != 0) { AddPointerToList(#symb, aGfxData, aHead + n3); }                    \
        BehaviorScript _Bs[] = { symb(_Arg0, _Arg1, _Arg2) };                              \
        memcpy(aHead, _Bs, sizeof(_Bs));                                                   \
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));                                           \
        return;                                                                            \
    }
    
#define bhv_symbol_4(symb, n1, n2, n3, n4)                                                       \
    if (_Symbol == #symb) {                                                                      \
        BehaviorScript _Arg0 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg1 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg2 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg3 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg4 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg5 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg6 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        BehaviorScript _Arg7 = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);       \
        if (n1 != 0) { AddPointerToList(#symb, aGfxData, aHead + n1); }                          \
        if (n2 != 0) { AddPointerToList(#symb, aGfxData, aHead + n2); }                          \
        if (n3 != 0) { AddPointerToList(#symb, aGfxData, aHead + n3); }                          \
        if (n4 != 0) { AddPointerToList(#symb, aGfxData, aHead + n4); }                          \
        BehaviorScript _Bs[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7) }; \
        memcpy(aHead, _Bs, sizeof(_Bs));                                                         \
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));                                                 \
        return;                                                                                  \
    }

static void ParseBehaviorScriptSymbol(GfxData *aGfxData, DataNode<BehaviorScript> *aNode, BehaviorScript *&aHead, u64 &aTokenIndex, Array<u64> &aSwitchNodes) {
    const String &_Symbol = aNode->mTokens[aTokenIndex++];

    bhv_symbol_0(RETURN);
    bhv_symbol_0(END_REPEAT);
    bhv_symbol_0(END_REPEAT_CONTINUE);
    bhv_symbol_0(BEGIN_LOOP);
    bhv_symbol_0(END_LOOP);
    bhv_symbol_0(BREAK);
    bhv_symbol_0(BREAK_UNUSED);
    bhv_symbol_0(DEACTIVATE);
    bhv_symbol_0(DROP_TO_FLOOR);
    bhv_symbol_0(BILLBOARD);
    bhv_symbol_0(CYLBOARD);
    bhv_symbol_0(HIDE);
    bhv_symbol_0(SET_HOME);
    bhv_symbol_0(DISABLE_RENDERING);
    
    bhv_symbol_1(ID, 0);
    bhv_symbol_1(BEGIN, 0);
    bhv_symbol_1(DELAY, 0);
    bhv_symbol_1(BEGIN_REPEAT, 0);
    bhv_symbol_1(CMD_NOP_1, 0);
    bhv_symbol_1(CMD_NOP_2, 0);
    bhv_symbol_1(CMD_NOP_3, 0);
    bhv_symbol_1(SET_MODEL, 0);
    bhv_symbol_1(DELAY_VAR, 0);
    bhv_symbol_1(BEGIN_REPEAT_UNUSED, 0);
    bhv_symbol_1(ANIMATE, 0);
    bhv_symbol_1(SET_INTERACT_TYPE, 0);
    bhv_symbol_1(SET_INTERACT_SUBTYPE, 0);
    //bhv_symbol_1(SPAWN_WATER_DROPLET, 1);
    
    bhv_symbol_2(ADD_FLOAT, 0, 0);
    bhv_symbol_2(SET_FLOAT, 0, 0);
    bhv_symbol_2(ADD_INT, 0, 0);
    bhv_symbol_2(SET_INT, 0, 0);
    bhv_symbol_2(OR_INT, 0, 0);
    bhv_symbol_2(BIT_CLEAR, 0, 0);
    bhv_symbol_2(SET_HITBOX, 0, 0);
    bhv_symbol_2(CMD_NOP_4, 0, 0);
    bhv_symbol_2(SET_HURTBOX, 0, 0);
    bhv_symbol_2(SCALE, 0, 0);
    bhv_symbol_2(PARENT_BIT_CLEAR, 0, 0);
    bhv_symbol_2(ANIMATE_TEXTURE, 0, 0);
    bhv_symbol_2(SET_INT_UNUSED, 0, 0);
    
    bhv_symbol_3(SET_INT_RAND_RSHIFT, 0, 0, 0);
    bhv_symbol_3(SET_RANDOM_INT, 0, 0, 0);
    bhv_symbol_3(ADD_RANDOM_FLOAT, 0, 0, 0);
    bhv_symbol_3(ADD_INT_RAND_RSHIFT, 0, 0, 0);
    bhv_symbol_3(SUM_FLOAT, 0, 0, 0);
    bhv_symbol_3(SUM_INT, 0, 0, 0);
    bhv_symbol_3(SET_HITBOX_WITH_OFFSET, 0, 0, 0);
    
    bhv_symbol_4(SET_OBJ_PHYSICS, 0, 0, 0, 0);
    
    // Both CALL and GOTO can have a offset to their addresses
    // in their non-extended counterparts.
    // We might be able to support this in DynOS. But I would not know how.
    
    // Call Behavior
    if (_Symbol == "CALL") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        
        BehaviorScript behavior = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        if (foundBeh) {
            aGfxData->mPointerList.Add(aHead + 1);
            BehaviorScript _Bs[] = { CALL(behavior) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
            BehaviorScript _Bs[] = { CALL_EXT(behIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }
    
    // Call Behavior
    if (_Symbol == "CALL_NATIVE") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundFunc = true;
        
        BehaviorScript function = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundFunc);
        
        if (foundFunc) {
            aGfxData->mPointerList.Add(aHead + 1);
            BehaviorScript _Bs[] = { CALL_NATIVE(function) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 funcIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
            BehaviorScript _Bs[] = { CALL_NATIVE_EXT(funcIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }
    
    // Jump to Behavior (Goto)
    if (_Symbol == "GOTO") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        
        BehaviorScript behavior = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        if (foundBeh) {
            aGfxData->mPointerList.Add(aHead + 1);
            BehaviorScript _Bs[] = { GOTO(behavior) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
            BehaviorScript _Bs[] = { GOTO_EXT(behIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }
    
    
    // Spawn Child
    if (_Symbol == "SPAWN_CHILD") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        
        BehaviorScript modelID = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        BehaviorScript behavior = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        if (foundBeh) {
            aGfxData->mPointerList.Add(aHead + 2);
            BehaviorScript _Bs[] = { SPAWN_CHILD(modelID, behavior) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 2, aNode->mTokens[topTokenIndex + 1]);
            BehaviorScript _Bs[] = { SPAWN_CHILD_EXT(modelID, behIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }
    
    // Spawn Child with Parameter
    if (_Symbol == "SPAWN_CHILD_WITH_PARAM") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        
        BehaviorScript bhvParam = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        BehaviorScript modelID = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        BehaviorScript behavior = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        if (foundBeh) {
            aGfxData->mPointerList.Add(aHead + 2);
            BehaviorScript _Bs[] = { SPAWN_CHILD_WITH_PARAM(bhvParam, modelID, behavior) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 2, aNode->mTokens[topTokenIndex + 2]);
            BehaviorScript _Bs[] = { SPAWN_CHILD_WITH_PARAM_EXT(bhvParam, modelID, behIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }
    
    // Spawn Object
    if (_Symbol == "SPAWN_OBJ") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        
        BehaviorScript modelID = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        BehaviorScript behavior = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        if (foundBeh) {
            aGfxData->mPointerList.Add(aHead + 2);
            BehaviorScript _Bs[] = { SPAWN_OBJ(modelID, behavior) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 2, aNode->mTokens[topTokenIndex + 1]);
            BehaviorScript _Bs[] = { SPAWN_OBJ_EXT(modelID, behIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }

    if (_Symbol == "LOAD_ANIMATIONS") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundAnimation = true;
        
        BehaviorScript field = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        BehaviorScript animations = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundAnimation);
        
        if (foundAnimation) {
            aGfxData->mPointerList.Add(aHead + 1);
            BehaviorScript _Bs[] = { LOAD_ANIMATIONS(field, animations) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            //u32 animIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
            //BehaviorScript _Bs[] = { LOAD_ANIMATIONS_EXT(field, animIndex) };
            //memcpy(aHead, _Bs, sizeof(_Bs));
            //aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
            PrintError("  ERROR: : Custom external animations are currently not supported. Skipping LOAD_ANIMATIONS_EXT.");
        }
        return;
    }
    
    
    if (_Symbol == "LOAD_COLLISION_DATA") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundCollisionData = true;
        
        BehaviorScript collisionData = ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundCollisionData);
        
        if (foundCollisionData) {
            aGfxData->mPointerList.Add(aHead + 1);
            BehaviorScript _Bs[] = { LOAD_COLLISION_DATA(collisionData) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        } else {
            u32 colDataIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
            BehaviorScript _Bs[] = { LOAD_COLLISION_DATA_EXT(colDataIndex) };
            memcpy(aHead, _Bs, sizeof(_Bs));
            aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        }
        return;
    }
    
    // We support directly using some extended types if needed.

    if (_Symbol == "CALL_EXT" || _Symbol == "CALL_CUSTOM") {
        u64 topTokenIndex = aTokenIndex;

        bool foundBeh = true;
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
        BehaviorScript _Bs[] = { CALL_EXT(behIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    if (_Symbol == "CALL_NATIVE_EXT" || _Symbol == "CALL_CUSTOM_NATIVE") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundFunc = true;
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundFunc);
        
        u32 funcIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
        BehaviorScript _Bs[] = { CALL_NATIVE_EXT(funcIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    if (_Symbol == "GOTO_EXT") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
        BehaviorScript _Bs[] = { GOTO_EXT(behIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    if (_Symbol == "SPAWN_CHILD_EXT" || _Symbol == "SPAWN_LUA_CHILD") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        BehaviorScript modelID = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 2, aNode->mTokens[topTokenIndex + 1]);
        BehaviorScript _Bs[] = { SPAWN_CHILD_EXT(modelID, behIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    if (_Symbol == "SPAWN_CHILD_WITH_PARAM_EXT" || _Symbol == "SPAWN_LUA_CHILD_WITH_PARAM") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        BehaviorScript bhvParam = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        BehaviorScript modelID = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 2, aNode->mTokens[topTokenIndex + 2]);
        BehaviorScript _Bs[] = { SPAWN_CHILD_WITH_PARAM_EXT(bhvParam, modelID, behIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    if (_Symbol == "SPAWN_OBJ_EXT" || _Symbol == "SPAWN_LUA_OBJ") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundBeh = true;
        BehaviorScript modelID = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        
        u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 2, aNode->mTokens[topTokenIndex + 1]);
        BehaviorScript _Bs[] = { SPAWN_OBJ_EXT(modelID, behIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    /*
    if (_Symbol == "LOAD_ANIMATIONS_EXT" || _Symbol == "LOAD_CUSTOM_ANIMATIONS") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundAnimation = true;
        BehaviorScript field = ParseBehaviorScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundAnimation);
        
        u32 animIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
        BehaviorScript _Bs[] = { LOAD_ANIMATIONS_EXT(field, animIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }
    */

    if (_Symbol == "LOAD_COLLISION_DATA_EXT" || _Symbol == "LOAD_CUSTOM_COLLISION_DATA") {
        u64 topTokenIndex = aTokenIndex;
        
        bool foundCollisionData = true;
        ParseBehaviorScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundCollisionData);
        
        u32 colDataIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 0]);
        BehaviorScript _Bs[] = { LOAD_COLLISION_DATA_EXT(colDataIndex) };
        memcpy(aHead, _Bs, sizeof(_Bs));
        aHead += (sizeof(_Bs) / sizeof(_Bs[0]));
        return;
    }

    // Unknown
    PrintError("  ERROR: Unknown behavior symbol: %s", _Symbol.begin());
}

DataNode<BehaviorScript> *DynOS_Bhv_Parse(GfxData *aGfxData, DataNode<BehaviorScript> *aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Behavior script data
    aNode->mData = New<BehaviorScript>(aNode->mTokens.Count() * BEHAVIOR_SCRIPT_SIZE_PER_TOKEN);
    BehaviorScript *_Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseBehaviorScriptSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

static DataNode<BehaviorScript> *GetBehaviorScript(GfxData *aGfxData, const String &aBhvRoot) {
    for (DataNode<BehaviorScript> *_Node : aGfxData->mBehaviorScripts) {
        if (_Node->mName == aBhvRoot) {
            return _Node;
        }
    }
    return NULL;
}

  /////////////
 // Writing //
/////////////

static void DynOS_Bhv_Write(FILE* aFile, GfxData* aGfxData, DataNode<BehaviorScript> *aNode) {
    if (!aNode->mData) return;

    // Name
    WriteBytes<u8>(aFile, DATA_TYPE_BEHAVIOR_SCRIPT);
    aNode->mName.Write(aFile);
    
    // Version
    WriteBytes<u8>(aFile, BEHAVIOR_MAJOR_VER);
    WriteBytes<u8>(aFile, BEHAVIOR_MINOR_VER);
    WriteBytes<u8>(aFile, BEHAVIOR_PATCH_VER);

    // Data
    WriteBytes<u32>(aFile, aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        BehaviorScript *_Head = &aNode->mData[i];
        if (aGfxData->mPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Write(aFile, (const void *) (*_Head), aGfxData);
        } else if (aGfxData->mLuaPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Lua_Write(aFile, *(u32 *)_Head, aGfxData);
        } else {
            WriteBytes<u32>(aFile, *((u32 *) _Head));
        }
    }
}


static bool DynOS_Bhv_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData) {
    FILE *_File = fopen(aOutputFilename.c_str(), "wb");
    if (!_File) {
        PrintError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    for (u64 i = 0; i != aGfxData->mLoadIndex; ++i) {
        for (auto &_Node : aGfxData->mBehaviorScripts) {
            if (_Node->mLoadIndex == i) {
                DynOS_Bhv_Write(_File, aGfxData, _Node);
            }
        }
    }

    fclose(_File);
    return true;
}

  /////////////
 // Reading //
/////////////

static DataNode<BehaviorScript> *DynOS_Bhv_Load(FILE *aFile, GfxData *aGfxData) {
    DataNode<BehaviorScript> *_Node = New<DataNode<BehaviorScript>>();

    // Name
    _Node->mName.Read(aFile);
    
    // Version
    u8 majorVersion = ReadBytes<u8>(aFile);
    u8 minorVersion = ReadBytes<u8>(aFile);
    u8 patchVersion = ReadBytes<u8>(aFile);
    
    // Version Sanity Check
    //
    // If the major version doesn't match, then a drasitc change has happened and
    // we can't read it no matter what. If it's just minor or patch. We might have
    // code to support it.
    u32 dataSize = ReadBytes<u32>(aFile);
    if (majorVersion != BEHAVIOR_MIN_MAJOR_VER || (minorVersion < BEHAVIOR_MIN_MINOR_VER || patchVersion < BEHAVIOR_MIN_PATCH_VER)) {
        PrintError("  ERROR: Behavior version is %u.%u.%u, but reading behaviors under %u.%u.%u is not supported!", majorVersion, minorVersion, patchVersion, BEHAVIOR_MIN_MAJOR_VER, BEHAVIOR_MIN_MINOR_VER, BEHAVIOR_MIN_PATCH_VER);
        
        // Skip the rest of the bytes saved for this behavior.
        SkipBytes(aFile, dataSize);
        // We don't return this since we failed to read the behavior.
        Delete(_Node);
        // We have nothing to return, So return NULL.
        return NULL;
    }

    // Data
    _Node->mSize = dataSize;
    _Node->mData = New<BehaviorScript>(_Node->mSize);

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mBehaviorScripts.Add(_Node);
    }

    // Read it
    for (u32 i = 0; i != _Node->mSize; ++i) {
        if (feof(aFile)) {
            PrintError("  ERROR: Reached EOF when reading file! Expected %llx bytes!", _Node->mSize * sizeof(u32));
            break;
        }
        u32 _Value = ReadBytes<u32>(aFile);
        void *_Ptr = DynOS_Pointer_Load(aFile, aGfxData, _Value, &_Node->mFlags);
        if (_Ptr) {
            _Node->mData[i] = (uintptr_t) _Ptr;
        } else {
            _Node->mData[i] = (uintptr_t) _Value;
        }
    }

    return _Node;
}

GfxData *DynOS_Bhv_LoadFromBinary(const SysPath &aFilename, const char *aBehaviorName) {

    // Load data from binary file
    GfxData *_GfxData = NULL;
    FILE *_File = fopen(aFilename.c_str(), "rb");
    if (_File != NULL) {
        _GfxData = New<GfxData>();
        for (bool _Done = false; !_Done;) {
            switch (ReadBytes<u8>(_File)) {
                case DATA_TYPE_BEHAVIOR_SCRIPT: DynOS_Bhv_Load(_File, _GfxData); break;
                default:                        _Done = true;                                   break;
            }
        }
        fclose(_File);
    }

    return _GfxData;
}

  //////////////
 // Generate //
//////////////

static String GetBehaviorFolder(const Array<Pair<u64, String>> &aBehaviorsFolders, u64 aModelIdentifier) {
    for (const auto &_Pair : aBehaviorsFolders) {
        if (_Pair.first == aModelIdentifier) {
            return _Pair.second;
        }
    }
    return String();
}

static void DynOS_Bhv_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _BehaviorsFolders, GfxData *_GfxData) {
    // do not regen this folder if we find any existing bins
    for (s32 bhvIndex = _GfxData->mBehaviorScripts.Count() - 1; bhvIndex >= 0; bhvIndex--) {
        auto &_BhvNode = _GfxData->mBehaviorScripts[bhvIndex];
        String _BhvRootName = _BhvNode->mName;

        // If there is an existing binary file for this layout, skip and go to the next behavior.
        SysPath _BinFilename = fstring("%s/%s.bhv", aPackFolder.c_str(), _BhvRootName.begin());
        if (fs_sys_file_exists(_BinFilename.c_str())) {
            return;
        }
    }

    // generate in reverse order to detect children
    for (s32 bhvIndex = _GfxData->mBehaviorScripts.Count() - 1; bhvIndex >= 0; bhvIndex--) {
        auto &_BhvNode = _GfxData->mBehaviorScripts[bhvIndex];

        String _BhvRootName = _BhvNode->mName;

        // If there is an existing binary file for this layout, skip and go to the next behavior.
        SysPath _BinFilename = fstring("%s/%s.bhv", aPackFolder.c_str(), _BhvRootName.begin());

        // Init
        _GfxData->mLoadIndex                  = 0;
        _GfxData->mErrorCount                 = 0;
        _GfxData->mModelIdentifier            = _BhvNode->mModelIdentifier;
        _GfxData->mPackFolder                 = aPackFolder;
        _GfxData->mPointerList                = { NULL }; // The NULL pointer is needed, so we add it here
        _GfxData->mPointerOffsetList          = { };
        _GfxData->mLuaPointerList             = { };
        _GfxData->mLuaTokenList               = { };
        _GfxData->mGfxContext.mCurrentTexture = NULL;
        _GfxData->mGfxContext.mCurrentPalette = NULL;
        _GfxData->mGeoNodeStack.Clear();

        // Parse data
        PrintNoNewLine("%s.bhv: Model identifier: %X - Processing... ", _BhvRootName.begin(), _GfxData->mModelIdentifier);
        DynOS_Bhv_Parse(_GfxData, _BhvNode, true);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Bhv_WriteBinary(_BinFilename, _GfxData);
        } else {
            Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }
        
        // Clear data pointers
        ClearBhvDataNodes(_GfxData->mBehaviorScripts);
        
        _GfxData->mPointerList.Clear();
        _GfxData->mPointerOffsetList.Clear();
        _GfxData->mLuaPointerList.Clear();
        _GfxData->mLuaTokenList.Clear();
    }
}

void DynOS_Bhv_GeneratePack(const SysPath &aPackFolder) {
    Print("---------- Behavior Pack folder: \"%s\" ----------", aPackFolder.c_str());
    Array<Pair<u64, String>> _BehaviorsFolders;
    GfxData *_GfxData = New<GfxData>();

    // Read the behavior_data.c files from the pack folder and any subfolders.
    
    // Read the main folder.
    if (fs_sys_dir_exists(aPackFolder.c_str())) {
        _GfxData->mModelIdentifier = 0;

        DynOS_Read_Source(_GfxData, fstring("%s/behavior_data.c", aPackFolder.c_str()));

        if (_GfxData->mModelIdentifier != 0) {
            _BehaviorsFolders.Add({ _GfxData->mModelIdentifier, String(aPackFolder.c_str()) });
        }
    }
    
    // Read the subfolders.
    DIR *aPackDir = opendir(aPackFolder.c_str());
    if (aPackDir) {
        // Read the subfolders.
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            // For each subfolder, read tokens from behavior_data.c
            SysPath _Folder = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (fs_sys_dir_exists(_Folder.c_str())) {
                _GfxData->mModelIdentifier = 0;

                DynOS_Read_Source(_GfxData, fstring("%s/behavior_data.c", _Folder.c_str()));

                if (_GfxData->mModelIdentifier != 0) {
                    _BehaviorsFolders.Add({ _GfxData->mModelIdentifier, String(_PackEnt->d_name) });
                }
            }
        }
        closedir(aPackDir);
    }

    // Generate a binary file for each behavior found in the GfxData
    DynOS_Bhv_Generate(aPackFolder, _BehaviorsFolders, _GfxData);

    DynOS_Gfx_Free(_GfxData);
}