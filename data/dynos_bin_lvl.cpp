#include "dynos.cpp.h"
extern "C" {
#include "include/level_commands.h"
#include "include/model_ids.h"
#include "include/behavior_data.h"
#include "include/surface_terrains.h"
#include "include/seq_ids.h"
#include "level_commands.h"
#include "src/game/level_update.h"
#include "include/dialog_ids.h"
#include "levels/scripts.h"
#include "src/game/area.h"
}

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
static void ClearLvlDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

//
// Lvl Functions
//

static const Array<Pair<const char *, void *>> &__LvlFunctions() {
#define define_lvl_function(name) { #name, (void *) name }
static const Array<Pair<const char *, void *>> sLvlFunctions = {
    define_lvl_function(lvl_init_or_update)
};
#undef define_lvl_function
return sLvlFunctions;
}
#define sLvlFunctions __LvlFunctions()

void *DynOS_Lvl_GetFunctionPointerFromName(const String &aName) {
    for (const auto &_LvlFunction : sLvlFunctions) {
        if (aName == _LvlFunction.first) {
            return _LvlFunction.second;
        }
    };
    return NULL;
}

s32 DynOS_Lvl_GetFunctionIndex(const void *aPtr) {
    for (const auto &_LvlFunction : sLvlFunctions) {
        if (_LvlFunction.second == aPtr) {
            return (s32) (&_LvlFunction - sLvlFunctions.begin());
        }
    }
    return -1;
}

void *DynOS_Lvl_GetFunctionPointerFromIndex(s32 aIndex) {
    return sLvlFunctions[aIndex].second;
}

  /////////////
 // Parsing //
/////////////

#define LEVEL_SCRIPT_SIZE_PER_TOKEN 4

#define lvl_constant(x) if (_Arg == #x) { return (LevelScript) (x); }

// TODO: this was made so that recursive descent can parse the constants...
// but RD should really use any function pointer passed to it
s64 DynOS_Lvl_ParseLevelScriptConstants(const String& _Arg, bool* found) {
    *found = true;

    // Behavior constants
    lvl_constant(bhvStarDoor);
    lvl_constant(bhvMrI);
    lvl_constant(bhvMrIBody);
    lvl_constant(bhvMrIParticle);
    lvl_constant(bhvPurpleParticle);
    lvl_constant(bhvGiantPole);
    lvl_constant(bhvPoleGrabbing);
    lvl_constant(bhvThiHugeIslandTop);
    lvl_constant(bhvThiTinyIslandTop);
    lvl_constant(bhvCapSwitchBase);
    lvl_constant(bhvCapSwitch);
    lvl_constant(bhvKingBobomb);
    lvl_constant(bhvBobombAnchorMario);
    lvl_constant(bhvBetaChestBottom);
    lvl_constant(bhvBetaChestLid);
    lvl_constant(bhvBubbleParticleSpawner);
    lvl_constant(bhvBubbleMaybe);
    lvl_constant(bhvBubblePlayer);
    lvl_constant(bhvSmallWaterWave);
    lvl_constant(bhvSmallWaterWave398);
    lvl_constant(bhvWaterAirBubble);
    lvl_constant(bhvSmallParticle);
    lvl_constant(bhvPlungeBubble);
    lvl_constant(bhvSmallParticleSnow);
    lvl_constant(bhvSmallParticleBubbles);
    lvl_constant(bhvFishGroup);
    lvl_constant(bhvCannon);
    lvl_constant(bhvCannonBarrel);
    lvl_constant(bhvCannonBaseUnused);
    lvl_constant(bhvChuckya);
    lvl_constant(bhvChuckyaAnchorMario);
    lvl_constant(bhvUnused05A8);
    lvl_constant(bhvRotatingPlatform);
    lvl_constant(bhvTower);
    lvl_constant(bhvBulletBillCannon);
    lvl_constant(bhvWfBreakableWallRight);
    lvl_constant(bhvWfBreakableWallLeft);
    lvl_constant(bhvKickableBoard);
    lvl_constant(bhvTowerDoor);
    lvl_constant(bhvRotatingCounterClockwise);
    lvl_constant(bhvWfRotatingWoodenPlatform);
    lvl_constant(bhvKoopaShellUnderwater);
    lvl_constant(bhvExitPodiumWarp);
    lvl_constant(bhvFadingWarp);
    lvl_constant(bhvWarp);
    lvl_constant(bhvWarpPipe);
    lvl_constant(bhvWhitePuffExplosion);
    lvl_constant(bhvSpawnedStar);
    lvl_constant(bhvSpawnedStarNoLevelExit);
    lvl_constant(bhvMrIBlueCoin);
    lvl_constant(bhvCoinInsideBoo);
    lvl_constant(bhvCoinFormationSpawn);
    lvl_constant(bhvCoinFormation);
    lvl_constant(bhvOneCoin);
    lvl_constant(bhvYellowCoin);
    lvl_constant(bhvTemporaryYellowCoin);
    lvl_constant(bhvThreeCoinsSpawn);
    lvl_constant(bhvTenCoinsSpawn);
    lvl_constant(bhvSingleCoinGetsSpawned);
    lvl_constant(bhvCoinSparkles);
    lvl_constant(bhvGoldenCoinSparkles);
    lvl_constant(bhvWallTinyStarParticle);
    lvl_constant(bhvVertStarParticleSpawner);
    lvl_constant(bhvPoundTinyStarParticle);
    lvl_constant(bhvHorStarParticleSpawner);
    lvl_constant(bhvPunchTinyTriangle);
    lvl_constant(bhvTriangleParticleSpawner);
    lvl_constant(bhvDoorWarp);
    lvl_constant(bhvDoor);
    lvl_constant(bhvGrindel);
    lvl_constant(bhvThwomp2);
    lvl_constant(bhvThwomp);
    lvl_constant(bhvTumblingBridgePlatform);
    lvl_constant(bhvWfTumblingBridge);
    lvl_constant(bhvBbhTumblingBridge);
    lvl_constant(bhvLllTumblingBridge);
    lvl_constant(bhvFlame);
    lvl_constant(bhvAnotherElavator);
    lvl_constant(bhvRrElevatorPlatform);
    lvl_constant(bhvHmcElevatorPlatform);
    lvl_constant(bhvWaterMist);
    lvl_constant(bhvBreathParticleSpawner);
    lvl_constant(bhvBreakBoxTriangle);
    lvl_constant(bhvWaterMist2);
    lvl_constant(bhvUnused0DFC);
    lvl_constant(bhvMistCircParticleSpawner);
    lvl_constant(bhvDirtParticleSpawner);
    lvl_constant(bhvSnowParticleSpawner);
    lvl_constant(bhvWind);
    lvl_constant(bhvEndToad);
    lvl_constant(bhvEndPeach);
    lvl_constant(bhvUnusedParticleSpawn);
    lvl_constant(bhvUkiki);
    lvl_constant(bhvUkikiCageChild);
    lvl_constant(bhvUkikiCageStar);
    lvl_constant(bhvUkikiCage);
    lvl_constant(bhvBitfsSinkingPlatforms);
    lvl_constant(bhvBitfsSinkingCagePlatform);
    lvl_constant(bhvDddMovingPole);
    lvl_constant(bhvBitfsTiltingInvertedPyramid);
    lvl_constant(bhvSquishablePlatform);
    lvl_constant(bhvCutOutObject);
    lvl_constant(bhvBetaMovingFlamesSpawn);
    lvl_constant(bhvBetaMovingFlames);
    lvl_constant(bhvRrRotatingBridgePlatform);
    lvl_constant(bhvFlamethrower);
    lvl_constant(bhvFlamethrowerFlame);
    lvl_constant(bhvBouncingFireball);
    lvl_constant(bhvBouncingFireballFlame);
    lvl_constant(bhvBowserShockWave);
    lvl_constant(bhvFireParticleSpawner);
    lvl_constant(bhvBlackSmokeMario);
    lvl_constant(bhvBlackSmokeBowser);
    lvl_constant(bhvBlackSmokeUpward);
    lvl_constant(bhvBetaFishSplashSpawner);
    lvl_constant(bhvSpindrift);
    lvl_constant(bhvTowerPlatformGroup);
    lvl_constant(bhvWfSlidingTowerPlatform);
    lvl_constant(bhvWfElevatorTowerPlatform);
    lvl_constant(bhvWfSolidTowerPlatform);
    lvl_constant(bhvLeafParticleSpawner);
    lvl_constant(bhvTreeSnow);
    lvl_constant(bhvTreeLeaf);
    lvl_constant(bhvAnotherTiltingPlatform);
    lvl_constant(bhvSquarishPathMoving);
    lvl_constant(bhvSquarishPathParent);
    lvl_constant(bhvPiranhaPlantBubble);
    lvl_constant(bhvPiranhaPlantWakingBubbles);
    lvl_constant(bhvFloorSwitchAnimatesObject);
    lvl_constant(bhvFloorSwitchGrills);
    lvl_constant(bhvFloorSwitchHardcodedModel);
    lvl_constant(bhvFloorSwitchHiddenObjects);
    lvl_constant(bhvHiddenObject);
    lvl_constant(bhvBreakableBox);
    lvl_constant(bhvPushableMetalBox);
    lvl_constant(bhvHeaveHo);
    lvl_constant(bhvHeaveHoThrowMario);
    lvl_constant(bhvCcmTouchedStarSpawn);
    lvl_constant(bhvUnusedPoundablePlatform);
    lvl_constant(bhvBetaTrampolineTop);
    lvl_constant(bhvBetaTrampolineSpring);
    lvl_constant(bhvJumpingBox);
    lvl_constant(bhvBooCage);
    lvl_constant(bhvStub);
    lvl_constant(bhvIgloo);
    lvl_constant(bhvBowserKey);
    lvl_constant(bhvGrandStar);
    lvl_constant(bhvBetaBooKey);
    lvl_constant(bhvAlphaBooKey);
    lvl_constant(bhvBulletBill);
    lvl_constant(bhvWhitePuffSmoke);
    lvl_constant(bhvUnused1820);
    lvl_constant(bhvBowserTailAnchor);
    lvl_constant(bhvBowser);
    lvl_constant(bhvBowserBodyAnchor);
    lvl_constant(bhvBowserFlameSpawn);
    lvl_constant(bhvTiltingBowserLavaPlatform);
    lvl_constant(bhvFallingBowserPlatform);
    lvl_constant(bhvBlueBowserFlame);
    lvl_constant(bhvFlameFloatingLanding);
    lvl_constant(bhvBlueFlamesGroup);
    lvl_constant(bhvFlameBouncing);
    lvl_constant(bhvFlameMovingForwardGrowing);
    lvl_constant(bhvFlameBowser);
    lvl_constant(bhvFlameLargeBurningOut);
    lvl_constant(bhvBlueFish);
    lvl_constant(bhvTankFishGroup);
    lvl_constant(bhvCheckerboardElevatorGroup);
    lvl_constant(bhvCheckerboardPlatformSub);
    lvl_constant(bhvBowserKeyUnlockDoor);
    lvl_constant(bhvBowserKeyCourseExit);
    lvl_constant(bhvInvisibleObjectsUnderBridge);
    lvl_constant(bhvWaterLevelPillar);
    lvl_constant(bhvDddWarp);
    lvl_constant(bhvMoatGrills);
    lvl_constant(bhvClockMinuteHand);
    lvl_constant(bhvClockHourHand);
    lvl_constant(bhvMacroUkiki);
    lvl_constant(bhvStub1D0C);
    lvl_constant(bhvLllRotatingHexagonalPlatform);
    lvl_constant(bhvLllSinkingRockBlock);
    lvl_constant(bhvStub1D70);
    lvl_constant(bhvLllMovingOctagonalMeshPlatform);
    lvl_constant(bhvSnowBall);
    lvl_constant(bhvLllRotatingBlockWithFireBars);
    lvl_constant(bhvLllRotatingHexFlame);
    lvl_constant(bhvLllWoodPiece);
    lvl_constant(bhvLllFloatingWoodBridge);
    lvl_constant(bhvVolcanoFlames);
    lvl_constant(bhvLllRotatingHexagonalRing);
    lvl_constant(bhvLllSinkingRectangularPlatform);
    lvl_constant(bhvLllSinkingSquarePlatforms);
    lvl_constant(bhvLllTiltingInvertedPyramid);
    lvl_constant(bhvUnused1F30);
    lvl_constant(bhvKoopaShell);
    lvl_constant(bhvKoopaShellFlame);
    lvl_constant(bhvToxBox);
    lvl_constant(bhvPiranhaPlant);
    lvl_constant(bhvLllHexagonalMesh);
    lvl_constant(bhvLllBowserPuzzlePiece);
    lvl_constant(bhvLllBowserPuzzle);
    lvl_constant(bhvTuxiesMother);
    lvl_constant(bhvPenguinBaby);
    lvl_constant(bhvUnused20E0);
    lvl_constant(bhvSmallPenguin);
    lvl_constant(bhvManyBlueFishSpawner);
    lvl_constant(bhvFewBlueFishSpawner);
    lvl_constant(bhvFishSpawner);
    lvl_constant(bhvFish);
    lvl_constant(bhvWdwExpressElevator);
    lvl_constant(bhvWdwExpressElevatorPlatform);
    lvl_constant(bhvChirpChirp);
    lvl_constant(bhvChirpChirpUnused);
    lvl_constant(bhvBub);
    lvl_constant(bhvExclamationBox);
    lvl_constant(bhvRotatingExclamationMark);
    lvl_constant(bhvSoundSpawner);
    lvl_constant(bhvRockSolid);
    lvl_constant(bhvBowserSubDoor);
    lvl_constant(bhvBowsersSub);
    lvl_constant(bhvSushiShark);
    lvl_constant(bhvSushiSharkCollisionChild);
    lvl_constant(bhvJrbSlidingBox);
    lvl_constant(bhvShipPart3);
    lvl_constant(bhvInSunkenShip3);
    lvl_constant(bhvSunkenShipPart);
    lvl_constant(bhvSunkenShipSetRotation);
    lvl_constant(bhvSunkenShipPart2);
    lvl_constant(bhvInSunkenShip);
    lvl_constant(bhvInSunkenShip2);
    lvl_constant(bhvMistParticleSpawner);
    lvl_constant(bhvWhitePuff1);
    lvl_constant(bhvWhitePuff2);
    lvl_constant(bhvWhitePuffSmoke2);
    lvl_constant(bhvPurpleSwitchHiddenBoxes);
    lvl_constant(bhvBlueCoinSwitch);
    lvl_constant(bhvHiddenBlueCoin);
    lvl_constant(bhvOpenableCageDoor);
    lvl_constant(bhvOpenableGrill);
    lvl_constant(bhvWaterLevelDiamond);
    lvl_constant(bhvInitializeChangingWaterLevel);
    lvl_constant(bhvTweesterSandParticle);
    lvl_constant(bhvTweester);
    lvl_constant(bhvMerryGoRoundBooManager);
    lvl_constant(bhvPlaysMusicTrackWhenTouched);
    lvl_constant(bhvAnimatedTexture);
    lvl_constant(bhvBooInCastle);
    lvl_constant(bhvBooWithCage);
    lvl_constant(bhvBalconyBigBoo);
    lvl_constant(bhvMerryGoRoundBigBoo);
    lvl_constant(bhvGhostHuntBigBoo);
    lvl_constant(bhvCourtyardBooTriplet);
    lvl_constant(bhvBoo);
    lvl_constant(bhvMerryGoRoundBoo);
    lvl_constant(bhvGhostHuntBoo);
    lvl_constant(bhvHiddenStaircaseStep);
    lvl_constant(bhvBooBossSpawnedBridge);
    lvl_constant(bhvBbhTiltingTrapPlatform);
    lvl_constant(bhvHauntedBookshelf);
    lvl_constant(bhvMeshElevator);
    lvl_constant(bhvMerryGoRound);
    lvl_constant(bhvInsideCannon);
    lvl_constant(bhvBetaBowserAnchor);
    lvl_constant(bhvStaticCheckeredPlatform);
    lvl_constant(bhvUnused2A10);
    lvl_constant(bhvStar);
    lvl_constant(bhvStaticObject);
    lvl_constant(bhvUnused2A54);
    lvl_constant(bhvCastleFloorTrap);
    lvl_constant(bhvFloorTrapInCastle);
    lvl_constant(bhvTree);
    lvl_constant(bhvSparkle);
    lvl_constant(bhvSparkleSpawn);
    lvl_constant(bhvSparkleParticleSpawner);
    lvl_constant(bhvScuttlebug);
    lvl_constant(bhvScuttlebugSpawn);
    lvl_constant(bhvWhompKingBoss);
    lvl_constant(bhvSmallWhomp);
    lvl_constant(bhvWaterSplash);
    lvl_constant(bhvWaterDroplet);
    lvl_constant(bhvWaterDropletSplash);
    lvl_constant(bhvBubbleSplash);
    lvl_constant(bhvIdleWaterWave);
    lvl_constant(bhvObjectWaterSplash);
    lvl_constant(bhvShallowWaterWave);
    lvl_constant(bhvShallowWaterSplash);
    lvl_constant(bhvObjectWaveTrail);
    lvl_constant(bhvWaveTrail);
    lvl_constant(bhvTinyStrongWindParticle);
    lvl_constant(bhvStrongWindParticle);
    lvl_constant(bhvSLSnowmanWind);
    lvl_constant(bhvSLWalkingPenguin);
    lvl_constant(bhvYellowBall);
    lvl_constant(bhvMario);
    lvl_constant(bhvToadMessage);
    lvl_constant(bhvUnlockDoorStar);
    lvl_constant(bhvInstantActiveWarp);
    lvl_constant(bhvAirborneWarp);
    lvl_constant(bhvHardAirKnockBackWarp);
    lvl_constant(bhvSpinAirborneCircleWarp);
    lvl_constant(bhvDeathWarp);
    lvl_constant(bhvSpinAirborneWarp);
    lvl_constant(bhvFlyingWarp);
    lvl_constant(bhvPaintingStarCollectWarp);
    lvl_constant(bhvPaintingDeathWarp);
    lvl_constant(bhvAirborneDeathWarp);
    lvl_constant(bhvAirborneStarCollectWarp);
    lvl_constant(bhvLaunchStarCollectWarp);
    lvl_constant(bhvLaunchDeathWarp);
    lvl_constant(bhvSwimmingWarp);
    lvl_constant(bhvRandomAnimatedTexture);
    lvl_constant(bhvYellowBackgroundInMenu);
    lvl_constant(bhvMenuButton);
    lvl_constant(bhvMenuButtonManager);
    lvl_constant(bhvActSelectorStarType);
    lvl_constant(bhvActSelector);
    lvl_constant(bhvMovingYellowCoin);
    lvl_constant(bhvMovingBlueCoin);
    lvl_constant(bhvBlueCoinSliding);
    lvl_constant(bhvBlueCoinJumping);
    lvl_constant(bhvSeaweed);
    lvl_constant(bhvSeaweedBundle);
    lvl_constant(bhvBobomb);
    lvl_constant(bhvBobombFuseSmoke);
    lvl_constant(bhvBobombBuddy);
    lvl_constant(bhvBobombBuddyOpensCannon);
    lvl_constant(bhvCannonClosed);
    lvl_constant(bhvWhirlpool);
    lvl_constant(bhvJetStream);
    lvl_constant(bhvMessagePanel);
    lvl_constant(bhvSignOnWall);
    lvl_constant(bhvHomingAmp);
    lvl_constant(bhvCirclingAmp);
    lvl_constant(bhvButterfly);
    lvl_constant(bhvHoot);
    lvl_constant(bhvBetaHoldableObject);
    lvl_constant(bhvCarrySomething1);
    lvl_constant(bhvCarrySomething2);
    lvl_constant(bhvCarrySomething3);
    lvl_constant(bhvCarrySomething4);
    lvl_constant(bhvCarrySomething5);
    lvl_constant(bhvCarrySomething6);
    lvl_constant(bhvObjectBubble);
    lvl_constant(bhvObjectWaterWave);
    lvl_constant(bhvExplosion);
    lvl_constant(bhvBobombBullyDeathSmoke);
    lvl_constant(bhvSmoke);
    lvl_constant(bhvBobombExplosionBubble);
    lvl_constant(bhvBobombExplosionBubble3600);
    lvl_constant(bhvRespawner);
    lvl_constant(bhvSmallBully);
    lvl_constant(bhvBigBully);
    lvl_constant(bhvBigBullyWithMinions);
    lvl_constant(bhvSmallChillBully);
    lvl_constant(bhvBigChillBully);
    lvl_constant(bhvJetStreamRingSpawner);
    lvl_constant(bhvJetStreamWaterRing);
    lvl_constant(bhvMantaRayWaterRing);
    lvl_constant(bhvMantaRayRingManager);
    lvl_constant(bhvBowserBomb);
    lvl_constant(bhvBowserBombExplosion);
    lvl_constant(bhvBowserBombSmoke);
    lvl_constant(bhvCelebrationStar);
    lvl_constant(bhvCelebrationStarSparkle);
    lvl_constant(bhvStarKeyCollectionPuffSpawner);
    lvl_constant(bhvLllDrawbridgeSpawner);
    lvl_constant(bhvLllDrawbridge);
    lvl_constant(bhvSmallBomp);
    lvl_constant(bhvLargeBomp);
    lvl_constant(bhvWfSlidingPlatform);
    lvl_constant(bhvMoneybag);
    lvl_constant(bhvMoneybagHidden);
    lvl_constant(bhvPitBowlingBall);
    lvl_constant(bhvFreeBowlingBall);
    lvl_constant(bhvBowlingBall);
    lvl_constant(bhvTtmBowlingBallSpawner);
    lvl_constant(bhvBobBowlingBallSpawner);
    lvl_constant(bhvThiBowlingBallSpawner);
    lvl_constant(bhvRrCruiserWing);
    lvl_constant(bhvSpindel);
    lvl_constant(bhvSslMovingPyramidWall);
    lvl_constant(bhvPyramidElevator);
    lvl_constant(bhvPyramidElevatorTrajectoryMarkerBall);
    lvl_constant(bhvPyramidTop);
    lvl_constant(bhvPyramidTopFragment);
    lvl_constant(bhvPyramidPillarTouchDetector);
    lvl_constant(bhvWaterfallSoundLoop);
    lvl_constant(bhvVolcanoSoundLoop);
    lvl_constant(bhvCastleFlagWaving);
    lvl_constant(bhvBirdsSoundLoop);
    lvl_constant(bhvAmbientSounds);
    lvl_constant(bhvSandSoundLoop);
    lvl_constant(bhvHiddenAt120Stars);
    lvl_constant(bhvSnowmansBottom);
    lvl_constant(bhvSnowmansHead);
    lvl_constant(bhvSnowmansBodyCheckpoint);
    lvl_constant(bhvBigSnowmanWhole);
    lvl_constant(bhvBigBoulder);
    lvl_constant(bhvBigBoulderGenerator);
    lvl_constant(bhvWingCap);
    lvl_constant(bhvMetalCap);
    lvl_constant(bhvNormalCap);
    lvl_constant(bhvVanishCap);
    lvl_constant(bhvStar);
    lvl_constant(bhvStarSpawnCoordinates);
    lvl_constant(bhvHiddenRedCoinStar);
    lvl_constant(bhvRedCoin);
    lvl_constant(bhvBowserCourseRedCoinStar);
    lvl_constant(bhvHiddenStar);
    lvl_constant(bhvHiddenStarTrigger);
    lvl_constant(bhvTtmRollingLog);
    lvl_constant(bhvLllVolcanoFallingTrap);
    lvl_constant(bhvLllRollingLog);
    lvl_constant(bhv1upWalking);
    lvl_constant(bhv1upRunningAway);
    lvl_constant(bhv1upSliding);
    lvl_constant(bhv1Up);
    lvl_constant(bhv1upJumpOnApproach);
    lvl_constant(bhvHidden1up);
    lvl_constant(bhvHidden1upTrigger);
    lvl_constant(bhvHidden1upInPole);
    lvl_constant(bhvHidden1upInPoleTrigger);
    lvl_constant(bhvHidden1upInPoleSpawner);
    lvl_constant(bhvControllablePlatform);
    lvl_constant(bhvControllablePlatformSub);
    lvl_constant(bhvBreakableBoxSmall);
    lvl_constant(bhvSlidingSnowMound);
    lvl_constant(bhvSnowMoundSpawn);
    lvl_constant(bhvWdwSquareFloatingPlatform);
    lvl_constant(bhvWdwRectangularFloatingPlatform);
    lvl_constant(bhvJrbFloatingPlatform);
    lvl_constant(bhvArrowLift);
    lvl_constant(bhvOrangeNumber);
    lvl_constant(bhvMantaRay);
    lvl_constant(bhvFallingPillar);
    lvl_constant(bhvFallingPillarHitbox);
    lvl_constant(bhvPillarBase);
    lvl_constant(bhvJrbFloatingBox);
    lvl_constant(bhvDecorativePendulum);
    lvl_constant(bhvTreasureChestsShip);
    lvl_constant(bhvTreasureChestsJrb);
    lvl_constant(bhvTreasureChests);
    lvl_constant(bhvTreasureChestBottom);
    lvl_constant(bhvTreasureChestTop);
    lvl_constant(bhvMips);
    lvl_constant(bhvYoshi);
    lvl_constant(bhvKoopa);
    lvl_constant(bhvKoopaRaceEndpoint);
    lvl_constant(bhvKoopaFlag);
    lvl_constant(bhvPokey);
    lvl_constant(bhvPokeyBodyPart);
    lvl_constant(bhvSwoop);
    lvl_constant(bhvFlyGuy);
    lvl_constant(bhvGoomba);
    lvl_constant(bhvGoombaTripletSpawner);
    lvl_constant(bhvChainChomp);
    lvl_constant(bhvChainChompChainPart);
    lvl_constant(bhvWoodenPost);
    lvl_constant(bhvChainChompGate);
    lvl_constant(bhvWigglerHead);
    lvl_constant(bhvWigglerBody);
    lvl_constant(bhvEnemyLakitu);
    lvl_constant(bhvCameraLakitu);
    lvl_constant(bhvCloud);
    lvl_constant(bhvCloudPart);
    lvl_constant(bhvSpiny);
    lvl_constant(bhvMontyMole);
    lvl_constant(bhvMontyMoleHole);
    lvl_constant(bhvMontyMoleRock);
    lvl_constant(bhvPlatformOnTrack);
    lvl_constant(bhvTrackBall);
    lvl_constant(bhvSeesawPlatform);
    lvl_constant(bhvFerrisWheelAxle);
    lvl_constant(bhvFerrisWheelPlatform);
    lvl_constant(bhvWaterBombSpawner);
    lvl_constant(bhvWaterBomb);
    lvl_constant(bhvWaterBombShadow);
    lvl_constant(bhvTTCRotatingSolid);
    lvl_constant(bhvTTCPendulum);
    lvl_constant(bhvTTCTreadmill);
    lvl_constant(bhvTTCMovingBar);
    lvl_constant(bhvTTCCog);
    lvl_constant(bhvTTCPitBlock);
    lvl_constant(bhvTTCElevator);
    lvl_constant(bhvTTC2DRotator);
    lvl_constant(bhvTTCSpinner);
    lvl_constant(bhvMrBlizzard);
    lvl_constant(bhvMrBlizzardSnowball);
    lvl_constant(bhvSlidingPlatform2);
    lvl_constant(bhvOctagonalPlatformRotating);
    lvl_constant(bhvAnimatesOnFloorSwitchPress);
    lvl_constant(bhvActivatedBackAndForthPlatform);
    lvl_constant(bhvRecoveryHeart);
    lvl_constant(bhvWaterBombCannon);
    lvl_constant(bhvCannonBarrelBubbles);
    lvl_constant(bhvUnagi);
    lvl_constant(bhvUnagiSubobject);
    lvl_constant(bhvDorrie);
    lvl_constant(bhvHauntedChair);
    lvl_constant(bhvMadPiano);
    lvl_constant(bhvFlyingBookend);
    lvl_constant(bhvBookendSpawn);
    lvl_constant(bhvHauntedBookshelfManager);
    lvl_constant(bhvBookSwitch);
    lvl_constant(bhvFirePiranhaPlant);
    lvl_constant(bhvSmallPiranhaFlame);
    lvl_constant(bhvFireSpitter);
    lvl_constant(bhvFlyguyFlame);
    lvl_constant(bhvSnufit);
    lvl_constant(bhvSnufitBalls);
    lvl_constant(bhvHorizontalGrindel);
    lvl_constant(bhvEyerokBoss);
    lvl_constant(bhvEyerokHand);
    lvl_constant(bhvKlepto);
    lvl_constant(bhvBird);
    lvl_constant(bhvRacingPenguin);
    lvl_constant(bhvPenguinRaceFinishLine);
    lvl_constant(bhvPenguinRaceShortcutCheck);
    lvl_constant(bhvCoffinSpawner);
    lvl_constant(bhvCoffin);
    lvl_constant(bhvClamShell);
    lvl_constant(bhvSkeeter);
    lvl_constant(bhvSkeeterWave);
    lvl_constant(bhvSwingPlatform);
    lvl_constant(bhvDonutPlatformSpawner);
    lvl_constant(bhvDonutPlatform);
    lvl_constant(bhvDDDPole);
    lvl_constant(bhvRedCoinStarMarker);
    lvl_constant(bhvTripletButterfly);
    lvl_constant(bhvBubba);
    lvl_constant(bhvBeginningLakitu);
    lvl_constant(bhvBeginningPeach);
    lvl_constant(bhvEndBirds1);
    lvl_constant(bhvEndBirds2);
    lvl_constant(bhvIntroScene);
    lvl_constant(bhvUnusedFakeStar);

    // Level constants
    lvl_constant(LEVEL_UNKNOWN_1);
    lvl_constant(LEVEL_UNKNOWN_2);
    lvl_constant(LEVEL_UNKNOWN_3);
    lvl_constant(LEVEL_BBH);
    lvl_constant(LEVEL_CCM);
    lvl_constant(LEVEL_CASTLE);
    lvl_constant(LEVEL_HMC);
    lvl_constant(LEVEL_SSL);
    lvl_constant(LEVEL_BOB);
    lvl_constant(LEVEL_SL);
    lvl_constant(LEVEL_WDW);
    lvl_constant(LEVEL_JRB);
    lvl_constant(LEVEL_THI);
    lvl_constant(LEVEL_TTC);
    lvl_constant(LEVEL_RR);
    lvl_constant(LEVEL_CASTLE_GROUNDS);
    lvl_constant(LEVEL_BITDW);
    lvl_constant(LEVEL_VCUTM);
    lvl_constant(LEVEL_BITFS);
    lvl_constant(LEVEL_SA);
    lvl_constant(LEVEL_BITS);
    lvl_constant(LEVEL_LLL);
    lvl_constant(LEVEL_DDD);
    lvl_constant(LEVEL_WF);
    lvl_constant(LEVEL_ENDING);
    lvl_constant(LEVEL_CASTLE_COURTYARD);
    lvl_constant(LEVEL_PSS);
    lvl_constant(LEVEL_COTMC);
    lvl_constant(LEVEL_TOTWC);
    lvl_constant(LEVEL_BOWSER_1);
    lvl_constant(LEVEL_WMOTR);
    lvl_constant(LEVEL_UNKNOWN_32);
    lvl_constant(LEVEL_BOWSER_2);
    lvl_constant(LEVEL_BOWSER_3);
    lvl_constant(LEVEL_UNKNOWN_35);
    lvl_constant(LEVEL_TTM);
    lvl_constant(LEVEL_UNKNOWN_37);
    lvl_constant(LEVEL_UNKNOWN_38);

    // Surface constants
    lvl_constant(TERRAIN_GRASS);
    lvl_constant(TERRAIN_STONE);
    lvl_constant(TERRAIN_SNOW);
    lvl_constant(TERRAIN_SAND);
    lvl_constant(TERRAIN_SPOOKY);
    lvl_constant(TERRAIN_WATER);
    lvl_constant(TERRAIN_SLIDE);
    lvl_constant(TERRAIN_MASK);

    // Seq ids constants
    lvl_constant(SEQ_BASE_ID);
    lvl_constant(SEQ_VARIATION);
    lvl_constant(SEQ_SOUND_PLAYER);
    lvl_constant(SEQ_EVENT_CUTSCENE_COLLECT_STAR);
    lvl_constant(SEQ_MENU_TITLE_SCREEN);
    lvl_constant(SEQ_LEVEL_GRASS);
    lvl_constant(SEQ_LEVEL_INSIDE_CASTLE);
    lvl_constant(SEQ_LEVEL_WATER);
    lvl_constant(SEQ_LEVEL_HOT);
    lvl_constant(SEQ_LEVEL_BOSS_KOOPA);
    lvl_constant(SEQ_LEVEL_SNOW);
    lvl_constant(SEQ_LEVEL_SLIDE);
    lvl_constant(SEQ_LEVEL_SPOOKY);
    lvl_constant(SEQ_EVENT_PIRANHA_PLANT);
    lvl_constant(SEQ_LEVEL_UNDERGROUND);
    lvl_constant(SEQ_MENU_STAR_SELECT);
    lvl_constant(SEQ_EVENT_POWERUP);
    lvl_constant(SEQ_EVENT_METAL_CAP);
    lvl_constant(SEQ_EVENT_KOOPA_MESSAGE);
    lvl_constant(SEQ_LEVEL_KOOPA_ROAD);
    lvl_constant(SEQ_EVENT_HIGH_SCORE);
    lvl_constant(SEQ_EVENT_MERRY_GO_ROUND);
    lvl_constant(SEQ_EVENT_RACE);
    lvl_constant(SEQ_EVENT_CUTSCENE_STAR_SPAWN);
    lvl_constant(SEQ_EVENT_BOSS);
    lvl_constant(SEQ_EVENT_CUTSCENE_COLLECT_KEY);
    lvl_constant(SEQ_EVENT_ENDLESS_STAIRS);
    lvl_constant(SEQ_LEVEL_BOSS_KOOPA_FINAL);
    lvl_constant(SEQ_EVENT_CUTSCENE_CREDITS);
    lvl_constant(SEQ_EVENT_SOLVE_PUZZLE);
    lvl_constant(SEQ_EVENT_TOAD_MESSAGE);
    lvl_constant(SEQ_EVENT_PEACH_MESSAGE);
    lvl_constant(SEQ_EVENT_CUTSCENE_INTRO);
    lvl_constant(SEQ_EVENT_CUTSCENE_VICTORY);
    lvl_constant(SEQ_EVENT_CUTSCENE_ENDING);
    lvl_constant(SEQ_MENU_FILE_SELECT);
    lvl_constant(SEQ_EVENT_CUTSCENE_LAKITU);
    lvl_constant(SEQ_COUNT);

    // Model constants
    lvl_constant(ACT_1);
    lvl_constant(ACT_2);
    lvl_constant(ACT_3);
    lvl_constant(ACT_4);
    lvl_constant(ACT_5);
    lvl_constant(ACT_6);
    lvl_constant(ALL_ACTS_MACRO);
    lvl_constant(ALL_ACTS);
    lvl_constant(COIN_FORMATION_FLAG_VERTICAL);
    lvl_constant(COIN_FORMATION_FLAG_RING);
    lvl_constant(COIN_FORMATION_FLAG_ARROW);
    lvl_constant(COIN_FORMATION_FLAG_FLYING);
    lvl_constant(MODEL_NONE);
    lvl_constant(MODEL_MARIO);
    lvl_constant(MODEL_LEVEL_GEOMETRY_03);
    lvl_constant(MODEL_LEVEL_GEOMETRY_04);
    lvl_constant(MODEL_LEVEL_GEOMETRY_05);
    lvl_constant(MODEL_LEVEL_GEOMETRY_06);
    lvl_constant(MODEL_LEVEL_GEOMETRY_07);
    lvl_constant(MODEL_LEVEL_GEOMETRY_08);
    lvl_constant(MODEL_LEVEL_GEOMETRY_09);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0A);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0B);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0C);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0D);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0E);
    lvl_constant(MODEL_LEVEL_GEOMETRY_0F);
    lvl_constant(MODEL_LEVEL_GEOMETRY_10);
    lvl_constant(MODEL_LEVEL_GEOMETRY_11);
    lvl_constant(MODEL_LEVEL_GEOMETRY_12);
    lvl_constant(MODEL_LEVEL_GEOMETRY_13);
    lvl_constant(MODEL_LEVEL_GEOMETRY_14);
    lvl_constant(MODEL_LEVEL_GEOMETRY_15);
    lvl_constant(MODEL_LEVEL_GEOMETRY_16);
    lvl_constant(MODEL_BOB_BUBBLY_TREE);
    lvl_constant(MODEL_WDW_BUBBLY_TREE);
    lvl_constant(MODEL_CASTLE_GROUNDS_BUBBLY_TREE);
    lvl_constant(MODEL_WF_BUBBLY_TREE);
    lvl_constant(MODEL_THI_BUBBLY_TREE);
    lvl_constant(MODEL_COURTYARD_SPIKY_TREE);
    lvl_constant(MODEL_CCM_SNOW_TREE);
    lvl_constant(MODEL_SL_SNOW_TREE);
    lvl_constant(MODEL_UNKNOWN_TREE_1A);
    lvl_constant(MODEL_SSL_PALM_TREE);
    lvl_constant(MODEL_CASTLE_CASTLE_DOOR_UNUSED);
    lvl_constant(MODEL_CASTLE_WOODEN_DOOR_UNUSED);
    lvl_constant(MODEL_BBH_HAUNTED_DOOR);
    lvl_constant(MODEL_HMC_WOODEN_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_1E);
    lvl_constant(MODEL_HMC_METAL_DOOR);
    lvl_constant(MODEL_HMC_HAZY_MAZE_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_21);
    lvl_constant(MODEL_CASTLE_DOOR_0_STARS);
    lvl_constant(MODEL_CASTLE_DOOR_1_STAR);
    lvl_constant(MODEL_CASTLE_DOOR_3_STARS);
    lvl_constant(MODEL_CASTLE_KEY_DOOR);
    lvl_constant(MODEL_CASTLE_CASTLE_DOOR);
    lvl_constant(MODEL_CASTLE_GROUNDS_CASTLE_DOOR);
    lvl_constant(MODEL_CASTLE_WOODEN_DOOR);
    lvl_constant(MODEL_COURTYARD_WOODEN_DOOR);
    lvl_constant(MODEL_CCM_CABIN_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_28);
    lvl_constant(MODEL_CASTLE_METAL_DOOR);
    lvl_constant(MODEL_CASTLE_GROUNDS_METAL_DOOR);
    lvl_constant(MODEL_UNKNOWN_DOOR_2A);
    lvl_constant(MODEL_UNKNOWN_DOOR_2B);
    lvl_constant(MODEL_WF_TOWER_TRAPEZOID_PLATORM);
    lvl_constant(MODEL_WF_TOWER_SQUARE_PLATORM);
    lvl_constant(MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED);
    lvl_constant(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR);
    lvl_constant(MODEL_BBH_STAIRCASE_STEP);
    lvl_constant(MODEL_BBH_TILTING_FLOOR_PLATFORM);
    lvl_constant(MODEL_BBH_TUMBLING_PLATFORM);
    lvl_constant(MODEL_BBH_TUMBLING_PLATFORM_PART);
    lvl_constant(MODEL_BBH_MOVING_BOOKSHELF);
    lvl_constant(MODEL_BBH_MESH_ELEVATOR);
    lvl_constant(MODEL_BBH_MERRY_GO_ROUND);
    lvl_constant(MODEL_BBH_WOODEN_TOMB);
    lvl_constant(MODEL_CCM_ROPEWAY_LIFT);
    lvl_constant(MODEL_CCM_SNOWMAN_HEAD);
    lvl_constant(MODEL_CASTLE_BOWSER_TRAP);
    lvl_constant(MODEL_CASTLE_WATER_LEVEL_PILLAR);
    lvl_constant(MODEL_CASTLE_CLOCK_MINUTE_HAND);
    lvl_constant(MODEL_CASTLE_CLOCK_HOUR_HAND);
    lvl_constant(MODEL_CASTLE_CLOCK_PENDULUM);
    lvl_constant(MODEL_HMC_METAL_PLATFORM);
    lvl_constant(MODEL_HMC_METAL_ARROW_PLATFORM);
    lvl_constant(MODEL_HMC_ELEVATOR_PLATFORM);
    lvl_constant(MODEL_HMC_ROLLING_ROCK);
    lvl_constant(MODEL_HMC_ROCK_PIECE);
    lvl_constant(MODEL_HMC_ROCK_SMALL_PIECE);
    lvl_constant(MODEL_HMC_RED_GRILLS);
    lvl_constant(MODEL_SSL_PYRAMID_TOP);
    lvl_constant(MODEL_SSL_GRINDEL);
    lvl_constant(MODEL_SSL_SPINDEL);
    lvl_constant(MODEL_SSL_MOVING_PYRAMID_WALL);
    lvl_constant(MODEL_SSL_PYRAMID_ELEVATOR);
    lvl_constant(MODEL_BOB_CHAIN_CHOMP_GATE);
    lvl_constant(MODEL_BOB_SEESAW_PLATFORM);
    lvl_constant(MODEL_BOB_BARS_GRILLS);
    lvl_constant(MODEL_SL_SNOW_TRIANGLE);
    lvl_constant(MODEL_SL_CRACKED_ICE);
    lvl_constant(MODEL_SL_CRACKED_ICE_CHUNK);
    lvl_constant(MODEL_WDW_SQUARE_FLOATING_PLATFORM);
    lvl_constant(MODEL_WDW_ARROW_LIFT);
    lvl_constant(MODEL_WDW_WATER_LEVEL_DIAMOND);
    lvl_constant(MODEL_WDW_HIDDEN_PLATFORM);
    lvl_constant(MODEL_WDW_EXPRESS_ELEVATOR);
    lvl_constant(MODEL_WDW_RECTANGULAR_FLOATING_PLATFORM);
    lvl_constant(MODEL_WDW_ROTATING_PLATFORM);
    lvl_constant(MODEL_JRB_SHIP_LEFT_HALF_PART);
    lvl_constant(MODEL_JRB_SHIP_BACK_LEFT_PART);
    lvl_constant(MODEL_JRB_SHIP_RIGHT_HALF_PART);
    lvl_constant(MODEL_JRB_SHIP_BACK_RIGHT_PART);
    lvl_constant(MODEL_JRB_SUNKEN_SHIP);
    lvl_constant(MODEL_JRB_SUNKEN_SHIP_BACK);
    lvl_constant(MODEL_JRB_ROCK);
    lvl_constant(MODEL_JRB_SLIDING_BOX);
    lvl_constant(MODEL_JRB_FALLING_PILLAR);
    lvl_constant(MODEL_JRB_FALLING_PILLAR_BASE);
    lvl_constant(MODEL_JRB_FLOATING_PLATFORM);
    lvl_constant(MODEL_THI_HUGE_ISLAND_TOP);
    lvl_constant(MODEL_THI_TINY_ISLAND_TOP);
    lvl_constant(MODEL_TTC_ROTATING_CUBE);
    lvl_constant(MODEL_TTC_ROTATING_PRISM);
    lvl_constant(MODEL_TTC_PENDULUM);
    lvl_constant(MODEL_TTC_LARGE_TREADMILL);
    lvl_constant(MODEL_TTC_SMALL_TREADMILL);
    lvl_constant(MODEL_TTC_PUSH_BLOCK);
    lvl_constant(MODEL_TTC_ROTATING_HEXAGON);
    lvl_constant(MODEL_TTC_ROTATING_TRIANGLE);
    lvl_constant(MODEL_TTC_PIT_BLOCK);
    lvl_constant(MODEL_TTC_PIT_BLOCK_UNUSED);
    lvl_constant(MODEL_TTC_ELEVATOR_PLATFORM);
    lvl_constant(MODEL_TTC_CLOCK_HAND);
    lvl_constant(MODEL_TTC_SPINNER);
    lvl_constant(MODEL_TTC_SMALL_GEAR);
    lvl_constant(MODEL_TTC_LARGE_GEAR);
    lvl_constant(MODEL_RR_SLIDING_PLATFORM);
    lvl_constant(MODEL_RR_FLYING_CARPET);
    lvl_constant(MODEL_RR_OCTAGONAL_PLATFORM);
    lvl_constant(MODEL_RR_ROTATING_BRIDGE_PLATFORM);
    lvl_constant(MODEL_RR_TRIANGLE_PLATFORM);
    lvl_constant(MODEL_RR_CRUISER_WING);
    lvl_constant(MODEL_RR_SEESAW_PLATFORM);
    lvl_constant(MODEL_RR_L_SHAPED_PLATFORM);
    lvl_constant(MODEL_RR_SWINGING_PLATFORM);
    lvl_constant(MODEL_RR_DONUT_PLATFORM);
    lvl_constant(MODEL_RR_ELEVATOR_PLATFORM);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME1);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME2);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME3);
    lvl_constant(MODEL_RR_TRICKY_TRIANGLES_FRAME4);
    lvl_constant(MODEL_BITDW_SQUARE_PLATFORM);
    lvl_constant(MODEL_BITDW_SEESAW_PLATFORM);
    lvl_constant(MODEL_BITDW_SLIDING_PLATFORM);
    lvl_constant(MODEL_BITDW_FERRIS_WHEEL_AXLE);
    lvl_constant(MODEL_BITDW_BLUE_PLATFORM);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME4);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME3);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME2);
    lvl_constant(MODEL_BITDW_STAIRCASE_FRAME1);
    lvl_constant(MODEL_BITDW_STAIRCASE);
    lvl_constant(MODEL_VCUTM_SEESAW_PLATFORM);
    lvl_constant(MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER);
    lvl_constant(MODEL_BITFS_PLATFORM_ON_TRACK);
    lvl_constant(MODEL_BITFS_TILTING_SQUARE_PLATFORM);
    lvl_constant(MODEL_BITFS_SINKING_PLATFORMS);
    lvl_constant(MODEL_BITFS_BLUE_POLE);
    lvl_constant(MODEL_BITFS_SINKING_CAGE_PLATFORM);
    lvl_constant(MODEL_BITFS_ELEVATOR);
    lvl_constant(MODEL_BITFS_STRETCHING_PLATFORMS);
    lvl_constant(MODEL_BITFS_SEESAW_PLATFORM);
    lvl_constant(MODEL_BITFS_MOVING_SQUARE_PLATFORM);
    lvl_constant(MODEL_BITFS_SLIDING_PLATFORM);
    lvl_constant(MODEL_BITFS_TUMBLING_PLATFORM_PART);
    lvl_constant(MODEL_BITFS_TUMBLING_PLATFORM);
    lvl_constant(MODEL_BITS_SLIDING_PLATFORM);
    lvl_constant(MODEL_BITS_TWIN_SLIDING_PLATFORMS);
    lvl_constant(MODEL_BITS_OCTAGONAL_PLATFORM);
    lvl_constant(MODEL_BITS_BLUE_PLATFORM);
    lvl_constant(MODEL_BITS_FERRIS_WHEEL_AXLE);
    lvl_constant(MODEL_BITS_ARROW_PLATFORM);
    lvl_constant(MODEL_BITS_SEESAW_PLATFORM);
    lvl_constant(MODEL_BITS_TILTING_W_PLATFORM);
    lvl_constant(MODEL_BITS_STAIRCASE);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME1);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME2);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME3);
    lvl_constant(MODEL_BITS_STAIRCASE_FRAME4);
    lvl_constant(MODEL_BITS_WARP_PIPE);
    lvl_constant(MODEL_LLL_DRAWBRIDGE_PART);
    lvl_constant(MODEL_LLL_ROTATING_BLOCK_FIRE_BARS);
    lvl_constant(MODEL_LLL_ROTATING_HEXAGONAL_RING);
    lvl_constant(MODEL_LLL_SINKING_RECTANGULAR_PLATFORM);
    lvl_constant(MODEL_LLL_SINKING_SQUARE_PLATFORMS);
    lvl_constant(MODEL_LLL_TILTING_SQUARE_PLATFORM);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_1);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_2);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_3);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_4);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_5);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_6);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_7);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_8);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_9);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_10);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_11);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_12);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_13);
    lvl_constant(MODEL_LLL_BOWSER_PIECE_14);
    lvl_constant(MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM);
    lvl_constant(MODEL_LLL_SINKING_ROCK_BLOCK);
    lvl_constant(MODEL_LLL_ROLLING_LOG);
    lvl_constant(MODEL_LLL_WOOD_BRIDGE);
    lvl_constant(MODEL_LLL_LARGE_WOOD_BRIDGE);
    lvl_constant(MODEL_LLL_FALLING_PLATFORM);
    lvl_constant(MODEL_LLL_LARGE_FALLING_PLATFORM);
    lvl_constant(MODEL_LLL_VOLCANO_FALLING_TRAP);
    lvl_constant(MODEL_DDD_BOWSER_SUB_DOOR);
    lvl_constant(MODEL_DDD_BOWSER_SUB);
    lvl_constant(MODEL_DDD_POLE);
    lvl_constant(MODEL_WF_BREAKABLE_WALL_RIGHT);
    lvl_constant(MODEL_WF_BREAKABLE_WALL_LEFT);
    lvl_constant(MODEL_WF_KICKABLE_BOARD);
    lvl_constant(MODEL_WF_TOWER_DOOR);
    lvl_constant(MODEL_WF_KICKABLE_BOARD_FELLED);
    lvl_constant(MODEL_CASTLE_GROUNDS_VCUTM_GRILL);
    lvl_constant(MODEL_CASTLE_GROUNDS_FLAG);
    lvl_constant(MODEL_CASTLE_GROUNDS_CANNON_GRILL);
    lvl_constant(MODEL_BOWSER_2_TILTING_ARENA);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_1);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_2);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_3);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_4);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_5);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_6);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_7);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_8);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_9);
    lvl_constant(MODEL_BOWSER_3_FALLING_PLATFORM_10);
    lvl_constant(MODEL_TTM_ROLLING_LOG);
    lvl_constant(MODEL_TTM_STAR_CAGE);
    lvl_constant(MODEL_TTM_BLUE_SMILEY);
    lvl_constant(MODEL_TTM_YELLOW_SMILEY);
    lvl_constant(MODEL_TTM_STAR_SMILEY);
    lvl_constant(MODEL_TTM_MOON_SMILEY);
    lvl_constant(MODEL_BULLET_BILL);
    lvl_constant(MODEL_YELLOW_SPHERE);
    lvl_constant(MODEL_HOOT);
    lvl_constant(MODEL_YOSHI_EGG);
    lvl_constant(MODEL_THWOMP);
    lvl_constant(MODEL_HEAVE_HO);
    lvl_constant(MODEL_BLARGG);
    lvl_constant(MODEL_BULLY);
    lvl_constant(MODEL_BULLY_BOSS);
    lvl_constant(MODEL_WATER_BOMB);
    lvl_constant(MODEL_WATER_BOMB_SHADOW);
    lvl_constant(MODEL_KING_BOBOMB);
    lvl_constant(MODEL_MANTA_RAY);
    lvl_constant(MODEL_UNAGI);
    lvl_constant(MODEL_SUSHI);
    lvl_constant(MODEL_DL_WHIRLPOOL);
    lvl_constant(MODEL_CLAM_SHELL);
    lvl_constant(MODEL_POKEY_HEAD);
    lvl_constant(MODEL_POKEY_BODY_PART);
    lvl_constant(MODEL_TWEESTER);
    lvl_constant(MODEL_KLEPTO);
    lvl_constant(MODEL_EYEROK_LEFT_HAND);
    lvl_constant(MODEL_EYEROK_RIGHT_HAND);
    lvl_constant(MODEL_DL_MONTY_MOLE_HOLE);
    lvl_constant(MODEL_MONTY_MOLE);
    lvl_constant(MODEL_UKIKI);
    lvl_constant(MODEL_FWOOSH);
    lvl_constant(MODEL_SPINDRIFT);
    lvl_constant(MODEL_MR_BLIZZARD_HIDDEN);
    lvl_constant(MODEL_MR_BLIZZARD);
    lvl_constant(MODEL_PENGUIN);
    lvl_constant(MODEL_CAP_SWITCH_EXCLAMATION);
    lvl_constant(MODEL_CAP_SWITCH);
    lvl_constant(MODEL_CAP_SWITCH_BASE);
    lvl_constant(MODEL_BOO);
    lvl_constant(MODEL_BETA_BOO_KEY);
    lvl_constant(MODEL_HAUNTED_CHAIR);
    lvl_constant(MODEL_MAD_PIANO);
    lvl_constant(MODEL_BOOKEND_PART);
    lvl_constant(MODEL_BOOKEND);
    lvl_constant(MODEL_HAUNTED_CAGE);
    lvl_constant(MODEL_BIRDS);
    lvl_constant(MODEL_YOSHI);
    lvl_constant(MODEL_ENEMY_LAKITU);
    lvl_constant(MODEL_SPINY_BALL);
    lvl_constant(MODEL_SPINY);
    lvl_constant(MODEL_WIGGLER_HEAD);
    lvl_constant(MODEL_WIGGLER_BODY);
    lvl_constant(MODEL_BUBBA);
    lvl_constant(MODEL_UNKNOWN_54);
    lvl_constant(MODEL_UNKNOWN_58);
    lvl_constant(MODEL_BOWSER);
    lvl_constant(MODEL_BOWSER_BOMB_CHILD_OBJ);
    lvl_constant(MODEL_BOWSER_SMOKE);
    lvl_constant(MODEL_BOWSER_FLAMES);
    lvl_constant(MODEL_BOWSER_WAVE);
    lvl_constant(MODEL_BOWSER2);
    lvl_constant(MODEL_BUB);
    lvl_constant(MODEL_TREASURE_CHEST_BASE);
    lvl_constant(MODEL_TREASURE_CHEST_LID);
    lvl_constant(MODEL_CYAN_FISH);
    lvl_constant(MODEL_WATER_RING);
    lvl_constant(MODEL_SKEETER);
    lvl_constant(MODEL_PIRANHA_PLANT);
    lvl_constant(MODEL_WHOMP);
    lvl_constant(MODEL_KOOPA_WITH_SHELL);
    lvl_constant(MODEL_METALLIC_BALL);
    lvl_constant(MODEL_CHAIN_CHOMP);
    lvl_constant(MODEL_KOOPA_FLAG);
    lvl_constant(MODEL_WOODEN_POST);
    lvl_constant(MODEL_MIPS);
    lvl_constant(MODEL_BOO_CASTLE);
    lvl_constant(MODEL_LAKITU);
    lvl_constant(MODEL_CHILL_BULLY);
    lvl_constant(MODEL_BIG_CHILL_BULLY);
    lvl_constant(MODEL_MONEYBAG);
    lvl_constant(MODEL_SWOOP);
    lvl_constant(MODEL_SCUTTLEBUG);
    lvl_constant(MODEL_MR_I_IRIS);
    lvl_constant(MODEL_MR_I);
    lvl_constant(MODEL_DORRIE);
    lvl_constant(MODEL_YELLOW_COIN);
    lvl_constant(MODEL_YELLOW_COIN_NO_SHADOW);
    lvl_constant(MODEL_BLUE_COIN);
    lvl_constant(MODEL_BLUE_COIN_NO_SHADOW);
    lvl_constant(MODEL_HEART);
    lvl_constant(MODEL_TRANSPARENT_STAR);
    lvl_constant(MODEL_STAR);
    lvl_constant(MODEL_TTM_SLIDE_EXIT_PODIUM);
    lvl_constant(MODEL_WOODEN_SIGNPOST);
    lvl_constant(MODEL_UNKNOWN_7D);
    lvl_constant(MODEL_CANNON_BARREL);
    lvl_constant(MODEL_CANNON_BASE);
    lvl_constant(MODEL_BREAKABLE_BOX);
    lvl_constant(MODEL_BREAKABLE_BOX_SMALL);
    lvl_constant(MODEL_EXCLAMATION_BOX_OUTLINE);
    lvl_constant(MODEL_EXCLAMATION_POINT);
    lvl_constant(MODEL_MARIOS_WINGED_METAL_CAP);
    lvl_constant(MODEL_MARIOS_METAL_CAP);
    lvl_constant(MODEL_MARIOS_WING_CAP);
    lvl_constant(MODEL_MARIOS_CAP);
    lvl_constant(MODEL_EXCLAMATION_BOX);
    lvl_constant(MODEL_DIRT_ANIMATION);
    lvl_constant(MODEL_CARTOON_STAR);
    lvl_constant(MODEL_BLUE_COIN_SWITCH);
    lvl_constant(MODEL_MIST);
    lvl_constant(MODEL_SPARKLES_ANIMATION);
    lvl_constant(MODEL_RED_FLAME);
    lvl_constant(MODEL_BLUE_FLAME);
    lvl_constant(MODEL_BURN_SMOKE);
    lvl_constant(MODEL_SPARKLES);
    lvl_constant(MODEL_SMOKE);
    lvl_constant(MODEL_BURN_SMOKE_UNUSED);
    lvl_constant(MODEL_WHITE_PARTICLE_DL);
    lvl_constant(MODEL_SAND_DUST);
    lvl_constant(MODEL_WHITE_PARTICLE);
    lvl_constant(MODEL_PEBBLE);
    lvl_constant(MODEL_LEAVES);
    lvl_constant(MODEL_WAVE_TRAIL);
    lvl_constant(MODEL_WHITE_PARTICLE_SMALL);
    lvl_constant(MODEL_SMALL_WATER_SPLASH);
    lvl_constant(MODEL_IDLE_WATER_WAVE);
    lvl_constant(MODEL_WATER_SPLASH);
    lvl_constant(MODEL_BUBBLE);
    lvl_constant(MODEL_PURPLE_MARBLE);
    lvl_constant(MODEL_UNKNOWN_AC);
    lvl_constant(MODEL_WF_SLIDING_PLATFORM);
    lvl_constant(MODEL_WF_SMALL_BOMP);
    lvl_constant(MODEL_WF_ROTATING_WOODEN_PLATFORM);
    lvl_constant(MODEL_WF_TUMBLING_BRIDGE_PART);
    lvl_constant(MODEL_WF_LARGE_BOMP);
    lvl_constant(MODEL_WF_TUMBLING_BRIDGE);
    lvl_constant(MODEL_BOWSER_BOMB);
    lvl_constant(MODEL_WATER_MINE);
    lvl_constant(MODEL_BOWLING_BALL);
    lvl_constant(MODEL_TRAMPOLINE);
    lvl_constant(MODEL_TRAMPOLINE_CENTER);
    lvl_constant(MODEL_TRAMPOLINE_BASE);
    lvl_constant(MODEL_UNKNOWN_B8);
    lvl_constant(MODEL_FISH);
    lvl_constant(MODEL_FISH_SHADOW);
    lvl_constant(MODEL_BUTTERFLY);
    lvl_constant(MODEL_BLACK_BOBOMB);
    lvl_constant(MODEL_KOOPA_SHELL);
    lvl_constant(MODEL_KOOPA_WITHOUT_SHELL);
    lvl_constant(MODEL_GOOMBA);
    lvl_constant(MODEL_SEAWEED);
    lvl_constant(MODEL_AMP);
    lvl_constant(MODEL_BOBOMB_BUDDY);
    lvl_constant(MODEL_SSL_TOX_BOX);
    lvl_constant(MODEL_BOWSER_KEY_CUTSCENE);
    lvl_constant(MODEL_DL_CANNON_LID);
    lvl_constant(MODEL_CHECKERBOARD_PLATFORM);
    lvl_constant(MODEL_RED_FLAME_SHADOW);
    lvl_constant(MODEL_BOWSER_KEY);
    lvl_constant(MODEL_EXPLOSION);
    lvl_constant(MODEL_SNUFIT);
    lvl_constant(MODEL_PURPLE_SWITCH);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_30_STARS);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_50_STARS);
    lvl_constant(MODEL_CCM_SNOWMAN_BASE);
    lvl_constant(MODEL_1UP);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_8_STARS);
    lvl_constant(MODEL_CASTLE_STAR_DOOR_70_STARS);
    lvl_constant(MODEL_RED_COIN);
    lvl_constant(MODEL_RED_COIN_NO_SHADOW);
    lvl_constant(MODEL_METAL_BOX);
    lvl_constant(MODEL_METAL_BOX_DL);
    lvl_constant(MODEL_NUMBER);
    lvl_constant(MODEL_FLYGUY);
    lvl_constant(MODEL_TOAD);
    lvl_constant(MODEL_PEACH);
    lvl_constant(MODEL_CHUCKYA);
    lvl_constant(MODEL_WHITE_PUFF);
    lvl_constant(MODEL_TRAJECTORY_MARKER_BALL);
    lvl_constant(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_RED_ERASE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_BLUE_COPY_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_YELLOW_FILE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_GREEN_SCORE_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_MARIO_SAVE_BUTTON_FADE);
    lvl_constant(MODEL_MAIN_MENU_MARIO_NEW_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_MARIO_NEW_BUTTON_FADE);
    lvl_constant(MODEL_MAIN_MENU_PURPLE_SOUND_BUTTON);
    lvl_constant(MODEL_MAIN_MENU_GENERIC_BUTTON);
    lvl_constant(MODEL_LLL_ROTATING_HEXAGONAL_PLATFORM);
    lvl_constant(MODEL_WF_GIANT_POLE);
    lvl_constant(MODEL_WF_ROTATING_PLATFORM);
    lvl_constant(MODEL_BITDW_WARP_PIPE);
    lvl_constant(MODEL_THI_WARP_PIPE);
    lvl_constant(MODEL_VCUTM_WARP_PIPE);
    lvl_constant(MODEL_CASTLE_GROUNDS_WARP_PIPE);
    lvl_constant(MODEL_BUBBLE_PLAYER);
    lvl_constant(MODEL_LUIGI);
    lvl_constant(MODEL_LUIGIS_CAP);
    lvl_constant(MODEL_LUIGIS_METAL_CAP);
    lvl_constant(MODEL_LUIGIS_WING_CAP);
    lvl_constant(MODEL_LUIGIS_WINGED_METAL_CAP);
    lvl_constant(MODEL_TOAD_PLAYER);
    lvl_constant(MODEL_TOADS_CAP);
    lvl_constant(MODEL_TOADS_METAL_CAP);
    lvl_constant(MODEL_TOADS_WING_CAP);
    lvl_constant(MODEL_WALUIGI);
    lvl_constant(MODEL_WALUIGIS_CAP);
    lvl_constant(MODEL_WALUIGIS_METAL_CAP);
    lvl_constant(MODEL_WALUIGIS_WING_CAP);
    lvl_constant(MODEL_WALUIGIS_WINGED_METAL_CAP);
    lvl_constant(MODEL_WARIO);
    lvl_constant(MODEL_WARIOS_CAP);
    lvl_constant(MODEL_WARIOS_METAL_CAP);
    lvl_constant(MODEL_WARIOS_WING_CAP);
    lvl_constant(MODEL_WARIOS_WINGED_METAL_CAP);
    lvl_constant(MODEL_ERROR_MODEL);

    // dialog constants
    lvl_constant(DIALOG_000);
    lvl_constant(DIALOG_001);
    lvl_constant(DIALOG_002);
    lvl_constant(DIALOG_003);
    lvl_constant(DIALOG_004);
    lvl_constant(DIALOG_005);
    lvl_constant(DIALOG_006);
    lvl_constant(DIALOG_007);
    lvl_constant(DIALOG_008);
    lvl_constant(DIALOG_009);
    lvl_constant(DIALOG_010);
    lvl_constant(DIALOG_011);
    lvl_constant(DIALOG_012);
    lvl_constant(DIALOG_013);
    lvl_constant(DIALOG_014);
    lvl_constant(DIALOG_015);
    lvl_constant(DIALOG_016);
    lvl_constant(DIALOG_017);
    lvl_constant(DIALOG_018);
    lvl_constant(DIALOG_019);
    lvl_constant(DIALOG_020);
    lvl_constant(DIALOG_021);
    lvl_constant(DIALOG_022);
    lvl_constant(DIALOG_023);
    lvl_constant(DIALOG_024);
    lvl_constant(DIALOG_025);
    lvl_constant(DIALOG_026);
    lvl_constant(DIALOG_027);
    lvl_constant(DIALOG_028);
    lvl_constant(DIALOG_029);
    lvl_constant(DIALOG_030);
    lvl_constant(DIALOG_031);
    lvl_constant(DIALOG_032);
    lvl_constant(DIALOG_033);
    lvl_constant(DIALOG_034);
    lvl_constant(DIALOG_035);
    lvl_constant(DIALOG_036);
    lvl_constant(DIALOG_037);
    lvl_constant(DIALOG_038);
    lvl_constant(DIALOG_039);
    lvl_constant(DIALOG_040);
    lvl_constant(DIALOG_041);
    lvl_constant(DIALOG_042);
    lvl_constant(DIALOG_043);
    lvl_constant(DIALOG_044);
    lvl_constant(DIALOG_045);
    lvl_constant(DIALOG_046);
    lvl_constant(DIALOG_047);
    lvl_constant(DIALOG_048);
    lvl_constant(DIALOG_049);
    lvl_constant(DIALOG_050);
    lvl_constant(DIALOG_051);
    lvl_constant(DIALOG_052);
    lvl_constant(DIALOG_053);
    lvl_constant(DIALOG_054);
    lvl_constant(DIALOG_055);
    lvl_constant(DIALOG_056);
    lvl_constant(DIALOG_057);
    lvl_constant(DIALOG_058);
    lvl_constant(DIALOG_059);
    lvl_constant(DIALOG_060);
    lvl_constant(DIALOG_061);
    lvl_constant(DIALOG_062);
    lvl_constant(DIALOG_063);
    lvl_constant(DIALOG_064);
    lvl_constant(DIALOG_065);
    lvl_constant(DIALOG_066);
    lvl_constant(DIALOG_067);
    lvl_constant(DIALOG_068);
    lvl_constant(DIALOG_069);
    lvl_constant(DIALOG_070);
    lvl_constant(DIALOG_071);
    lvl_constant(DIALOG_072);
    lvl_constant(DIALOG_073);
    lvl_constant(DIALOG_074);
    lvl_constant(DIALOG_075);
    lvl_constant(DIALOG_076);
    lvl_constant(DIALOG_077);
    lvl_constant(DIALOG_078);
    lvl_constant(DIALOG_079);
    lvl_constant(DIALOG_080);
    lvl_constant(DIALOG_081);
    lvl_constant(DIALOG_082);
    lvl_constant(DIALOG_083);
    lvl_constant(DIALOG_084);
    lvl_constant(DIALOG_085);
    lvl_constant(DIALOG_086);
    lvl_constant(DIALOG_087);
    lvl_constant(DIALOG_088);
    lvl_constant(DIALOG_089);
    lvl_constant(DIALOG_090);
    lvl_constant(DIALOG_091);
    lvl_constant(DIALOG_092);
    lvl_constant(DIALOG_093);
    lvl_constant(DIALOG_094);
    lvl_constant(DIALOG_095);
    lvl_constant(DIALOG_096);
    lvl_constant(DIALOG_097);
    lvl_constant(DIALOG_098);
    lvl_constant(DIALOG_099);
    lvl_constant(DIALOG_100);
    lvl_constant(DIALOG_101);
    lvl_constant(DIALOG_102);
    lvl_constant(DIALOG_103);
    lvl_constant(DIALOG_104);
    lvl_constant(DIALOG_105);
    lvl_constant(DIALOG_106);
    lvl_constant(DIALOG_107);
    lvl_constant(DIALOG_108);
    lvl_constant(DIALOG_109);
    lvl_constant(DIALOG_110);
    lvl_constant(DIALOG_111);
    lvl_constant(DIALOG_112);
    lvl_constant(DIALOG_113);
    lvl_constant(DIALOG_114);
    lvl_constant(DIALOG_115);
    lvl_constant(DIALOG_116);
    lvl_constant(DIALOG_117);
    lvl_constant(DIALOG_118);
    lvl_constant(DIALOG_119);
    lvl_constant(DIALOG_120);
    lvl_constant(DIALOG_121);
    lvl_constant(DIALOG_122);
    lvl_constant(DIALOG_123);
    lvl_constant(DIALOG_124);
    lvl_constant(DIALOG_125);
    lvl_constant(DIALOG_126);
    lvl_constant(DIALOG_127);
    lvl_constant(DIALOG_128);
    lvl_constant(DIALOG_129);
    lvl_constant(DIALOG_130);
    lvl_constant(DIALOG_131);
    lvl_constant(DIALOG_132);
    lvl_constant(DIALOG_133);
    lvl_constant(DIALOG_134);
    lvl_constant(DIALOG_135);
    lvl_constant(DIALOG_136);
    lvl_constant(DIALOG_137);
    lvl_constant(DIALOG_138);
    lvl_constant(DIALOG_139);
    lvl_constant(DIALOG_140);
    lvl_constant(DIALOG_141);
    lvl_constant(DIALOG_142);
    lvl_constant(DIALOG_143);
    lvl_constant(DIALOG_144);
    lvl_constant(DIALOG_145);
    lvl_constant(DIALOG_146);
    lvl_constant(DIALOG_147);
    lvl_constant(DIALOG_148);
    lvl_constant(DIALOG_149);
    lvl_constant(DIALOG_150);
    lvl_constant(DIALOG_151);
    lvl_constant(DIALOG_152);
    lvl_constant(DIALOG_153);
    lvl_constant(DIALOG_154);
    lvl_constant(DIALOG_155);
    lvl_constant(DIALOG_156);
    lvl_constant(DIALOG_157);
    lvl_constant(DIALOG_158);
    lvl_constant(DIALOG_159);
    lvl_constant(DIALOG_160);
    lvl_constant(DIALOG_161);
    lvl_constant(DIALOG_162);
    lvl_constant(DIALOG_163);
    lvl_constant(DIALOG_164);
    lvl_constant(DIALOG_165);
    lvl_constant(DIALOG_166);
    lvl_constant(DIALOG_167);
    lvl_constant(DIALOG_168);
    lvl_constant(DIALOG_169);
    lvl_constant(DIALOG_COUNT);

    // global scripts
    lvl_constant(level_main_scripts_entry);
    lvl_constant(script_func_global_1);
    lvl_constant(script_func_global_2);
    lvl_constant(script_func_global_3);
    lvl_constant(script_func_global_4);
    lvl_constant(script_func_global_5);
    lvl_constant(script_func_global_6);
    lvl_constant(script_func_global_7);
    lvl_constant(script_func_global_8);
    lvl_constant(script_func_global_9);
    lvl_constant(script_func_global_10);
    lvl_constant(script_func_global_11);
    lvl_constant(script_func_global_12);
    lvl_constant(script_func_global_13);
    lvl_constant(script_func_global_14);
    lvl_constant(script_func_global_15);
    lvl_constant(script_func_global_16);
    lvl_constant(script_func_global_17);
    lvl_constant(script_func_global_18);

    // level command constants
    lvl_constant(OP_AND);
    lvl_constant(OP_NAND);
    lvl_constant(OP_EQ);
    lvl_constant(OP_NEQ);
    lvl_constant(OP_LT);
    lvl_constant(OP_LEQ);
    lvl_constant(OP_GT);
    lvl_constant(OP_GEQ);
    lvl_constant(OP_SET);
    lvl_constant(OP_GET);
    lvl_constant(VAR_CURR_SAVE_FILE_NUM);
    lvl_constant(VAR_CURR_COURSE_NUM);
    lvl_constant(VAR_CURR_ACT_NUM);
    lvl_constant(VAR_CURR_LEVEL_NUM);
    lvl_constant(VAR_CURR_AREA_INDEX);
    lvl_constant(WARP_CHECKPOINT);
    lvl_constant(WARP_NO_CHECKPOINT);
    lvl_constant(WHIRLPOOL_COND_ALWAYS);
    lvl_constant(WHIRLPOOL_COND_BOWSER2_BEATEN);
    lvl_constant(WHIRLPOOL_COND_AT_LEAST_SECOND_STAR);
    lvl_constant(REGULAR_FACE);
    lvl_constant(DIZZY_FACE);

    // warp transitions
    lvl_constant(WARP_TRANSITION_FADE_FROM_COLOR);
    lvl_constant(WARP_TRANSITION_FADE_INTO_COLOR);
    lvl_constant(WARP_TRANSITION_FADE_FROM_STAR);
    lvl_constant(WARP_TRANSITION_FADE_INTO_STAR);
    lvl_constant(WARP_TRANSITION_FADE_FROM_CIRCLE);
    lvl_constant(WARP_TRANSITION_FADE_INTO_CIRCLE);
    lvl_constant(WARP_TRANSITION_FADE_FROM_MARIO);
    lvl_constant(WARP_TRANSITION_FADE_INTO_MARIO);
    lvl_constant(WARP_TRANSITION_FADE_FROM_BOWSER);
    lvl_constant(WARP_TRANSITION_FADE_INTO_BOWSER);

    // vanilla actors
    s32 actorCount = DynOS_Geo_GetActorCount();
    for (s32 i = 0; i < actorCount; i++) {
        if (DynOS_Geo_IsCustomActor(i)) { break; }
        if (!strcmp(_Arg.begin(), DynOS_Geo_GetActorName(i))) {
            return (LevelScript)DynOS_Geo_GetActorLayout(i);
        }
    }

    // vanilla level geos
    s32 lvlGeoCount = DynOS_Lvl_GetGeoCount();
    for (s32 i = 0; i < lvlGeoCount; i++) {
        if (!strcmp(_Arg.begin(), DynOS_Lvl_GetGeoName(i))) {
            return (LevelScript)DynOS_Lvl_GetGeoLayout(i);
        }
    }

    *found = false;
    return 0;
}

static LevelScript ParseLevelScriptSymbolArgInternal(GfxData* aGfxData, DataNode<LevelScript>* aNode, u64& aTokenIndex, bool* found) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Lvl functions
    void *_LvlFunctionPtr = DynOS_Lvl_GetFunctionPointerFromName(_Arg);
    if (_LvlFunctionPtr != NULL) {
        return (LevelScript) _LvlFunctionPtr;
    }

    bool constantFound = false;
    s64 constantValue = DynOS_Lvl_ParseLevelScriptConstants(_Arg, &constantFound);
    if (constantFound) {
        return (LevelScript) constantValue;
    }

    // Other constants
    lvl_constant(NULL);
    lvl_constant(FALSE);

    // Level Scripts
    for (auto& _Node : aGfxData->mLevelScripts) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_Lvl_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Geo layouts
    for (auto& _Node : aGfxData->mGeoLayouts) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_Geo_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Collisions
    for (auto& _Node : aGfxData->mCollisions) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_Col_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // MacroObjects
    for (auto& _Node : aGfxData->mMacroObjects) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_MacroObject_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Trajectories
    for (auto& _Node : aGfxData->mTrajectories) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_Trajectory_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Movtexs
    for (auto& _Node : aGfxData->mMovtexs) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_Movtex_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // MovtexQCs
    for (auto& _Node : aGfxData->mMovtexQCs) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_MovtexQC_Parse(aGfxData, _Node)->mData;
        }
    }

    // Rooms
    for (auto& _Node : aGfxData->mRooms) {
        if (_Arg == _Node->mName) {
            return (LevelScript) DynOS_Rooms_Parse(aGfxData, _Node)->mData;
        }
    }

    // Integers
    s32 x;
    if ((_Arg[1] == 'x' && sscanf(_Arg.begin(), "%x", &x) == 1) || (sscanf(_Arg.begin(), "%d", &x) == 1)) {
        return (LevelScript) x;
    }

    // Recursive descent parsing
    bool rdSuccess = false;
    s64 rdValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdSuccess);
    if (rdSuccess) {
        return (LevelScript)rdValue;
    }

    *found = false;
    return 0;
}

static LevelScript ParseLevelScriptSymbolArg(GfxData* aGfxData, DataNode<LevelScript>* aNode, u64& aTokenIndex) {
    bool found = true;
    LevelScript value = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &found);
    if (!found) {
        const String& _Arg = aNode->mTokens[aTokenIndex - 1];
        PrintError("  ERROR: Unknown lvl arg: %s", _Arg.begin());
    }
    return value;
}

#define lvl_symbol_0(symb)                       \
    if (_Symbol == #symb) {                      \
        LevelScript _Ls[] = { symb() };          \
        memcpy(aHead, _Ls, sizeof(_Ls));         \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0])); \
        return;                                  \
    }

#define lvl_symbol_1(symb, n)                                                        \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }                       \
        LevelScript _Ls[] = { symb(_Arg0) };                                         \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_2(symb, n1, n2)                                                   \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1) };                                  \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_3(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2) };                           \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_4(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };                    \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_5(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) };             \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_6(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg5 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) };      \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_noop(symb, skipCount) \
    if (_Symbol == #symb) {              \
        aTokenIndex += skipCount;        \
        return;                          \
    }

static void ParseLevelScriptSymbol(GfxData* aGfxData, DataNode<LevelScript>* aNode, LevelScript*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    // execution
    lvl_symbol_4(EXECUTE, 1, 2, 3);
    lvl_symbol_4(EXIT_AND_EXECUTE, 1, 2, 3);
    lvl_symbol_0(EXIT);

    // sleep
    lvl_symbol_1(SLEEP, 0);
    lvl_symbol_1(SLEEP_BEFORE_EXIT, 0);

    // jumps
    lvl_symbol_1(JUMP, 1);
    lvl_symbol_1(JUMP_LINK, 1);
    lvl_symbol_0(RETURN);
    lvl_symbol_1(JUMP_LINK_PUSH_ARG, 0);
    lvl_symbol_0(JUMP_N_TIMES);
    lvl_symbol_0(LOOP_BEGIN);
    lvl_symbol_2(LOOP_UNTIL, 0, 0);
    lvl_symbol_3(JUMP_IF, 2, 0, 0);
    lvl_symbol_2(SKIP_IF, 0, 0);
    lvl_symbol_0(SKIP);
    lvl_symbol_0(SKIP_NOP);

    // calls
    lvl_symbol_2(CALL, 1, 0);
    lvl_symbol_2(CALL_LOOP, 1, 0);

    // misc memory
    lvl_symbol_1(SET_REG, 0);
    lvl_symbol_0(PUSH_POOL);
    lvl_symbol_0(POP_POOL);
    lvl_symbol_3(FIXED_LOAD, 1, 2, 3);
    lvl_symbol_noop(LOAD_RAW, 3);
    lvl_symbol_noop(LOAD_MIO0, 3);
    lvl_symbol_1(LOAD_MARIO_HEAD, 0);
    lvl_symbol_noop(LOAD_MIO0_TEXTURE, 3);

    // levels
    lvl_symbol_0(INIT_LEVEL);
    lvl_symbol_0(CLEAR_LEVEL);
    lvl_symbol_0(ALLOC_LEVEL_POOL);
    lvl_symbol_0(FREE_LEVEL_POOL);

    // areas
    lvl_symbol_2(AREA, 1, 0);
    lvl_symbol_0(END_AREA);

    // models
    lvl_symbol_3(LOAD_MODEL_FROM_DL, 1, 0, 0);
    lvl_symbol_2(LOAD_MODEL_FROM_GEO, 1, 0);
    lvl_symbol_3(CMD23, 1, 0, 0);

    // objects
    lvl_symbol_3(MARIO, 2, 0, 0);

    // warps
    lvl_symbol_5(WARP_NODE, 0, 0, 0);
    lvl_symbol_5(PAINTING_WARP_NODE, 0, 0, 0);
    lvl_symbol_5(INSTANT_WARP, 0, 0, 0);

    // misc
    lvl_symbol_1(LOAD_AREA, 0);
    lvl_symbol_1(CMD2A, 0);
    lvl_symbol_5(MARIO_POS, 0, 0, 0);
    lvl_symbol_0(CMD2C);
    lvl_symbol_0(CMD2D);
    lvl_symbol_1(TERRAIN, 1);
    lvl_symbol_1(ROOMS, 1);
    lvl_symbol_2(SHOW_DIALOG, 0, 0);
    lvl_symbol_1(TERRAIN_TYPE, 0);
    lvl_symbol_0(NOP);

    // transitions
    lvl_symbol_5(TRANSITION, 0, 0, 0);
    lvl_symbol_1(BLACKOUT, 0);
    lvl_symbol_1(GAMMA, 0);

    // music
    lvl_symbol_2(SET_BACKGROUND_MUSIC, 0, 0);
    lvl_symbol_1(SET_MENU_MUSIC, 0);
    lvl_symbol_1(STOP_MUSIC, 0);

    // misc
    lvl_symbol_1(MACRO_OBJECTS, 1);
    lvl_symbol_5(CMD3A, 0, 0, 0);
    lvl_symbol_6(WHIRLPOOL, 0, 0, 0);
    lvl_symbol_2(GET_OR_SET, 0, 0);
    lvl_symbol_0(ADV_DEMO);
    lvl_symbol_0(CLEAR_DEMO_PTR);

    // object
    if (_Symbol == "OBJECT") {
        u64 topTokenIndex = aTokenIndex;

        bool foundModel = true;
        bool foundBeh = true;
        LevelScript model    = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundModel);
        LevelScript posX     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posY     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posZ     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleX   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleY   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleZ   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript behParam = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript beh      = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);

        if (foundModel && foundBeh) {
            aGfxData->mPointerList.Add(aHead + 5);
            LevelScript _Ls[] = { OBJECT(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            // remember model/beh as pointer
            aGfxData->mPointerList.Add(aHead + 5);
            aGfxData->mPointerList.Add(aHead + 6);

            // add model/beh tokens
            u32 tokenListIndex = aGfxData->mPointerTokenList.Count();
            aGfxData->mPointerTokenList.Add(aNode->mTokens[topTokenIndex + 0]);
            aGfxData->mPointerTokenList.Add(aNode->mTokens[topTokenIndex + 8]);

            // get model/beh tokens
            String& modelToken = aGfxData->mPointerTokenList[tokenListIndex + 0];
            String& behToken   = aGfxData->mPointerTokenList[tokenListIndex + 1];

            LevelScript _Ls[] = { OBJECT_EXT(modelToken.begin(), posX, posY, posZ, angleX, angleY, angleZ, behParam, behToken.begin()) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // object with acts
    if (_Symbol == "OBJECT_WITH_ACTS") {
        u64 topTokenIndex = aTokenIndex;

        bool foundModel = true;
        bool foundBeh = true;
        LevelScript model    = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundModel);
        LevelScript posX     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posY     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posZ     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleX   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleY   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleZ   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript behParam = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript beh      = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        LevelScript acts      = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);

        if (foundModel && foundBeh) {
            aGfxData->mPointerList.Add(aHead + 5);
            LevelScript _Ls[] = { OBJECT_WITH_ACTS(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh, acts) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            // remember model/beh as pointer
            aGfxData->mPointerList.Add(aHead + 5);
            aGfxData->mPointerList.Add(aHead + 6);

            // add model/beh tokens
            u32 tokenListIndex = aGfxData->mPointerTokenList.Count();
            aGfxData->mPointerTokenList.Add(aNode->mTokens[topTokenIndex + 0]);
            aGfxData->mPointerTokenList.Add(aNode->mTokens[topTokenIndex + 8]);

            // get model/beh tokens
            String& modelToken = aGfxData->mPointerTokenList[tokenListIndex + 0];
            String& behToken   = aGfxData->mPointerTokenList[tokenListIndex + 1];

            LevelScript _Ls[] = { OBJECT_WITH_ACTS_EXT(modelToken.begin(), posX, posY, posZ, angleX, angleY, angleZ, behParam, behToken.begin(), acts) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // Unknown
    PrintError("  ERROR: Unknown lvl symbol: %s", _Symbol.begin());
}

DataNode<LevelScript>* DynOS_Lvl_Parse(GfxData* aGfxData, DataNode<LevelScript>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Level script data
    aNode->mData = New<LevelScript>(aNode->mTokens.Count() * LEVEL_SCRIPT_SIZE_PER_TOKEN);
    LevelScript* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseLevelScriptSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

static DataNode<LevelScript> *GetLevelScript(GfxData *aGfxData, const String& aGeoRoot) {
    for (DataNode<LevelScript> *_Node : aGfxData->mLevelScripts) {
        if (_Node->mName == aGeoRoot) {
            return _Node;
        }
    }
    return NULL;
}

  /////////////
 // Writing //
/////////////

static void DynOS_Lvl_Write(FILE* aFile, GfxData* aGfxData, DataNode<LevelScript> *aNode) {
    if (!aNode->mData) return;

    // Name
    WriteBytes<u8>(aFile, DATA_TYPE_LEVEL_SCRIPT);
    aNode->mName.Write(aFile);

    // Data
    WriteBytes<u32>(aFile, aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        LevelScript *_Head = &aNode->mData[i];
        if (aGfxData->mPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Write(aFile, (const void *) (*_Head), aGfxData);
        } else {
            WriteBytes<u32>(aFile, *((u32 *) _Head));
        }
    }
}

static bool DynOS_Lvl_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData) {
    FILE *_File = fopen(aOutputFilename.c_str(), "wb");
    if (!_File) {
        PrintError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    for (u64 i = 0; i != aGfxData->mLoadIndex; ++i) {
        for (auto &_Node : aGfxData->mLights) {
            if (_Node->mLoadIndex == i) {
                DynOS_Lights_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLightTs) {
            if (_Node->mLoadIndex == i) {
                DynOS_LightT_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mAmbientTs) {
            if (_Node->mLoadIndex == i) {
                DynOS_AmbientT_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTextures) {
            if (_Node->mLoadIndex == i) {
                DynOS_Tex_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mVertices) {
            if (_Node->mLoadIndex == i) {
                DynOS_Vtx_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mDisplayLists) {
            if (_Node->mLoadIndex == i) {
                DynOS_Gfx_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mGeoLayouts) {
            if (_Node->mLoadIndex == i) {
                DynOS_Geo_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mCollisions) {
            if (_Node->mLoadIndex == i) {
                DynOS_Col_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLevelScripts) {
            if (_Node->mLoadIndex == i) {
                DynOS_Lvl_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mMacroObjects) {
            if (_Node->mLoadIndex == i) {
                DynOS_MacroObject_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTrajectories) {
            if (_Node->mLoadIndex == i) {
                DynOS_Trajectory_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mMovtexs) {
            if (_Node->mLoadIndex == i) {
                DynOS_Movtex_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mMovtexQCs) {
            if (_Node->mLoadIndex == i) {
                DynOS_MovtexQC_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mRooms) {
            if (_Node->mLoadIndex == i) {
                DynOS_Rooms_Write(_File, aGfxData, _Node);
            }
        }
    }
    fclose(_File);
    return true;
}

  /////////////
 // Reading //
/////////////

static DataNode<LevelScript>* DynOS_Lvl_Load(FILE *aFile, GfxData *aGfxData) {
    DataNode<LevelScript> *_Node = New<DataNode<LevelScript>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = ReadBytes<u32>(aFile);
    _Node->mData = New<LevelScript>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        u32 _Value = ReadBytes<u32>(aFile);
        void *_Ptr = DynOS_Pointer_Load(aFile, aGfxData, _Value, true);
        if (_Ptr) {
            _Node->mData[i] = (uintptr_t) _Ptr;
        } else {
            _Node->mData[i] = (uintptr_t) _Value;
        }
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mLevelScripts.Add(_Node);
    }

    return _Node;
}

GfxData *DynOS_Lvl_LoadFromBinary(const SysPath &aPackFolder, const char *aLevelName) {
    struct DynosGfxDataCache { SysPath mPackFolder; Array<Pair<const char *, GfxData *>> mGfxData; };
    static Array<DynosGfxDataCache *> sDynosGfxDataCache;

    // Load data from binary file
    GfxData *_GfxData = NULL;
    SysPath _Filename = fstring("%s/%s.lvl", aPackFolder.begin(), aLevelName);
    FILE *_File = fopen(_Filename.c_str(), "rb");
    if (_File) {
        _GfxData = New<GfxData>();
        for (bool _Done = false; !_Done;) {
            switch (ReadBytes<u8>(_File)) {
                case DATA_TYPE_LIGHT:           DynOS_Lights_Load     (_File, _GfxData); break;
                case DATA_TYPE_LIGHT_T:         DynOS_LightT_Load     (_File, _GfxData); break;
                case DATA_TYPE_AMBIENT_T:       DynOS_AmbientT_Load   (_File, _GfxData); break;
                case DATA_TYPE_TEXTURE:         DynOS_Tex_Load        (_File, _GfxData); break;
                case DATA_TYPE_VERTEX:          DynOS_Vtx_Load        (_File, _GfxData); break;
                case DATA_TYPE_DISPLAY_LIST:    DynOS_Gfx_Load        (_File, _GfxData); break;
                case DATA_TYPE_GEO_LAYOUT:      DynOS_Geo_Load        (_File, _GfxData); break;
                case DATA_TYPE_ANIMATION:       DynOS_Anim_Load       (_File, _GfxData); break;
                case DATA_TYPE_ANIMATION_TABLE: DynOS_Anim_Table_Load (_File, _GfxData); break;
                case DATA_TYPE_GFXDYNCMD:       DynOS_GfxDynCmd_Load  (_File, _GfxData); break;
                case DATA_TYPE_COLLISION:       DynOS_Col_Load        (_File, _GfxData); break;
                case DATA_TYPE_LEVEL_SCRIPT:    DynOS_Lvl_Load        (_File, _GfxData); break;
                case DATA_TYPE_MACRO_OBJECT:    DynOS_MacroObject_Load(_File, _GfxData); break;
                case DATA_TYPE_TRAJECTORY:      DynOS_Trajectory_Load (_File, _GfxData); break;
                case DATA_TYPE_MOVTEX:          DynOS_Movtex_Load     (_File, _GfxData); break;
                case DATA_TYPE_MOVTEXQC:        DynOS_MovtexQC_Load   (_File, _GfxData); break;
                case DATA_TYPE_ROOMS:           DynOS_Rooms_Load      (_File, _GfxData); break;
                default:                        _Done = true;                            break;
            }
        }
        fclose(_File);
    }

    return _GfxData;
}

  //////////////
 // Generate //
//////////////

static bool DynOS_Lvl_GeneratePack_Internal(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    bool generated = false;
    for (auto &_LvlNode : _GfxData->mLevelScripts) {
        String _LvlRootName = _LvlNode->mName;
        DataNode<LevelScript> *_LvlRoot = GetLevelScript(_GfxData, _LvlRootName);
        if (_LvlRoot == NULL) { continue; }
        if (_LvlRootName.Find("_entry") == -1) { continue; }
        // If there is an existing binary file for this level, skip and go to the next level
        SysPath _LvlFilename = fstring("%s/%s.lvl", aPackFolder.c_str(), _LvlRootName.begin());
        if (fs_sys_file_exists(_LvlFilename.c_str())) {
            continue;
        }

        // Init
        _GfxData->mErrorCount = 0;
        _GfxData->mLoadIndex = 0;
        _GfxData->mPackFolder = aPackFolder;

        // Parse data
        PrintNoNewLine("%s.lvl: Model identifier: %X - Processing... ", _LvlRootName.begin(), _GfxData->mModelIdentifier);
        DynOS_Lvl_Parse(_GfxData, _LvlRoot, true);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Lvl_WriteBinary(_LvlFilename, _GfxData);
        } else {
            Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

        // Clear data pointers
        ClearLvlDataNodes(_GfxData->mLevelScripts);
        generated = true;
    }
    return generated;
}

static void DynOS_Lvl_GeneratePack_Recursive(const SysPath &directory, GfxData *_GfxData) {
    DIR *aPackDir = opendir(directory.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            SysPath path = fstring("%s/%s", directory.c_str(), _PackEnt->d_name);

            // Recurse through subfolders
            if (fs_sys_dir_exists(path.c_str())) {
                DynOS_Lvl_GeneratePack_Recursive(path, _GfxData);
                continue;
            }

            // skip files that don't end in '.c'
            size_t nameLen = strlen(_PackEnt->d_name);
            if (_PackEnt->d_name[nameLen - 2] != '.' || _PackEnt->d_name[nameLen - 1] != 'c') {
                continue;
            }

            // read the file
            DynOS_Read_Source(_GfxData, path.c_str());
        }
        closedir(aPackDir);
    }
}

void DynOS_Lvl_GeneratePack(const SysPath &aPackFolder) {
    Print("---------- Level pack folder: \"%s\" ----------", aPackFolder.c_str());
    Array<Pair<u64, String>> _ActorsFolders;

    DIR *aPackDir = opendir(aPackFolder.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            // For each subfolder, read tokens from script.c
            SysPath _Folder = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (!fs_sys_dir_exists(_Folder.c_str())) continue;

            // Only parse folders with a 'script.c'
            if (!fs_sys_file_exists(fstring("%s/script.c", _Folder.c_str()).c_str()) && !fs_sys_file_exists(fstring("%s/custom.script.c", _Folder.c_str()).c_str())) continue;

            GfxData *_GfxData = New<GfxData>();
            _GfxData->mModelIdentifier = 0;

            DynOS_Lvl_GeneratePack_Recursive(_Folder, _GfxData);

            // Generate a binary file for each level found in the GfxData
            DynOS_Lvl_GeneratePack_Internal(aPackFolder, _ActorsFolders, _GfxData);
            DynOS_Gfx_Free(_GfxData);

        }
        closedir(aPackDir);
    }
}
