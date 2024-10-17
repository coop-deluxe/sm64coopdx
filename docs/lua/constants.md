## [:rewind: Lua Reference](lua.md)

# Supported Constants
- [area.h](#areah)
- [behavior_table.h](#behavior_tableh)
    - [enum BehaviorId](#enum-BehaviorId)
- [camera.h](#camerah)
    - [enum RomhackCameraOverride](#enum-RomhackCameraOverride)
- [characters.h](#charactersh)
    - [enum CharacterSound](#enum-CharacterSound)
    - [enum CharacterType](#enum-CharacterType)
- [dialog_ids.h](#dialog_idsh)
    - [enum DialogId](#enum-DialogId)
- [djui_console.h](#djui_consoleh)
    - [enum ConsoleMessageLevel](#enum-ConsoleMessageLevel)
- [djui_hud_utils.h](#djui_hud_utilsh)
    - [enum DjuiFontType](#enum-DjuiFontType)
    - [enum HudUtilsFilter](#enum-HudUtilsFilter)
    - [enum HudUtilsResolution](#enum-HudUtilsResolution)
- [envfx_snow.h](#envfx_snowh)
- [external.h](#externalh)
    - [enum DialogSound](#enum-DialogSound)
- [first_person_cam.h](#first_person_camh)
- [geo_commands.h](#geo_commandsh)
- [graph_node.h](#graph_nodeh)
- [interaction.c](#interactionc)
- [interaction.h](#interactionh)
    - [enum InteractionFlag](#enum-InteractionFlag)
    - [enum InteractionType](#enum-InteractionType)
- [level_commands.h](#level_commandsh)
- [level_defines.h](#level_definesh)
    - [enum LevelNum](#enum-LevelNum)
- [level_update.h](#level_updateh)
    - [enum HUDDisplayFlag](#enum-HUDDisplayFlag)
- [mario_animation_ids.h](#mario_animation_idsh)
    - [enum CharacterAnimID](#enum-CharacterAnimID)
    - [enum MarioAnimID](#enum-MarioAnimID)
- [mario_geo_switch_case_ids.h](#mario_geo_switch_case_idsh)
    - [enum MarioCapGSCId](#enum-MarioCapGSCId)
    - [enum MarioEyesGSCId](#enum-MarioEyesGSCId)
    - [enum MarioGrabPosGSCId](#enum-MarioGrabPosGSCId)
    - [enum MarioHandGSCId](#enum-MarioHandGSCId)
- [mod_storage.h](#mod_storageh)
- [network.h](#networkh)
    - [enum BouncyLevelBounds](#enum-BouncyLevelBounds)
    - [enum NetworkSystemType](#enum-NetworkSystemType)
    - [enum PlayerInteractions](#enum-PlayerInteractions)
- [network_player.h](#network_playerh)
    - [enum NetworkPlayerType](#enum-NetworkPlayerType)
- [obj_behaviors.c](#obj_behaviorsc)
- [obj_behaviors_2.h](#obj_behaviors_2h)
- [object_constants.h](#object_constantsh)
- [object_list_processor.h](#object_list_processorh)
    - [enum ObjectList](#enum-ObjectList)
- [os_cont.h](#os_conth)
- [player_palette.h](#player_paletteh)
    - [enum PlayerPart](#enum-PlayerPart)
- [save_file.h](#save_fileh)
    - [enum SaveFileIndex](#enum-SaveFileIndex)
- [seq_ids.h](#seq_idsh)
    - [enum SeqId](#enum-SeqId)
- [sm64.h](#sm64h)
- [smlua_hooks.h](#smlua_hooksh)
    - [enum LuaActionHookType](#enum-LuaActionHookType)
    - [enum LuaHookedEventType](#enum-LuaHookedEventType)
    - [enum LuaModMenuElementType](#enum-LuaModMenuElementType)
- [smlua_misc_utils.h](#smlua_misc_utilsh)
    - [enum HudDisplayFlags](#enum-HudDisplayFlags)
    - [enum HudDisplayValue](#enum-HudDisplayValue)
- [smlua_model_utils.h](#smlua_model_utilsh)
    - [enum ModelExtendedId](#enum-ModelExtendedId)
- [sounds.h](#soundsh)
- [surface_terrains.h](#surface_terrainsh)
- [types.h](#typesh)
    - [enum AreaTimerType](#enum-AreaTimerType)
    - [enum SpTaskState](#enum-SpTaskState)
- [version.h](#versionh)

<br />

## [area.h](#area.h)
- INSTANT_WARP_INDEX_START
- INSTANT_WARP_INDEX_STOP
- MAX_AREAS
- WARP_TRANSITION_FADE_FROM_BOWSER
- WARP_TRANSITION_FADE_FROM_CIRCLE
- WARP_TRANSITION_FADE_FROM_COLOR
- WARP_TRANSITION_FADE_FROM_MARIO
- WARP_TRANSITION_FADE_FROM_STAR
- WARP_TRANSITION_FADE_INTO_BOWSER
- WARP_TRANSITION_FADE_INTO_CIRCLE
- WARP_TRANSITION_FADE_INTO_COLOR
- WARP_TRANSITION_FADE_INTO_MARIO
- WARP_TRANSITION_FADE_INTO_STAR

[:arrow_up_small:](#)

<br />

## [behavior_table.h](#behavior_table.h)

### [enum BehaviorId](#BehaviorId)
| Identifier | Value |
| :--------- | :---- |
| id_bhv1Up | 0 |
| id_bhv1upJumpOnApproach | 1 |
| id_bhv1upRunningAway | 2 |
| id_bhv1upSliding | 3 |
| id_bhv1upWalking | 4 |
| id_bhvActivatedBackAndForthPlatform | 5 |
| id_bhvActSelector | 6 |
| id_bhvActSelectorStarType | 7 |
| id_bhvAirborneDeathWarp | 8 |
| id_bhvAirborneStarCollectWarp | 9 |
| id_bhvAirborneWarp | 10 |
| id_bhvAlphaBooKey | 11 |
| id_bhvAmbientSounds | 12 |
| id_bhvAnimatedTexture | 13 |
| id_bhvAnimatesOnFloorSwitchPress | 14 |
| id_bhvAnotherElavator | 15 |
| id_bhvAnotherTiltingPlatform | 16 |
| id_bhvArrowLift | 17 |
| id_bhvBalconyBigBoo | 18 |
| id_bhvBbhTiltingTrapPlatform | 19 |
| id_bhvBbhTumblingBridge | 20 |
| id_bhvBeginningLakitu | 21 |
| id_bhvBeginningPeach | 22 |
| id_bhvBetaBooKey | 23 |
| id_bhvBetaBowserAnchor | 24 |
| id_bhvBetaChestBottom | 25 |
| id_bhvBetaChestLid | 26 |
| id_bhvBetaFishSplashSpawner | 27 |
| id_bhvBetaHoldableObject | 28 |
| id_bhvBetaMovingFlames | 29 |
| id_bhvBetaMovingFlamesSpawn | 30 |
| id_bhvBetaTrampolineSpring | 31 |
| id_bhvBetaTrampolineTop | 32 |
| id_bhvBigBoulder | 33 |
| id_bhvBigBoulderGenerator | 34 |
| id_bhvBigBully | 35 |
| id_bhvBigBullyWithMinions | 36 |
| id_bhvBigChillBully | 37 |
| id_bhvBigSnowmanWhole | 38 |
| id_bhvBird | 39 |
| id_bhvBirdsSoundLoop | 40 |
| id_bhvBitfsSinkingCagePlatform | 41 |
| id_bhvBitfsSinkingPlatforms | 42 |
| id_bhvBitfsTiltingInvertedPyramid | 43 |
| id_bhvBlackSmokeBowser | 44 |
| id_bhvBlackSmokeMario | 45 |
| id_bhvBlackSmokeUpward | 46 |
| id_bhvBlueBowserFlame | 47 |
| id_bhvBlueCoinJumping | 48 |
| id_bhvBlueCoinSliding | 49 |
| id_bhvBlueCoinSwitch | 50 |
| id_bhvBlueFish | 51 |
| id_bhvBlueFlamesGroup | 52 |
| id_bhvBobBowlingBallSpawner | 53 |
| id_bhvBobomb | 54 |
| id_bhvBobombAnchorMario | 55 |
| id_bhvBobombBuddy | 56 |
| id_bhvBobombBuddyOpensCannon | 57 |
| id_bhvBobombBullyDeathSmoke | 58 |
| id_bhvBobombExplosionBubble | 59 |
| id_bhvBobombExplosionBubble3600 | 60 |
| id_bhvBobombFuseSmoke | 61 |
| id_bhvBoo | 62 |
| id_bhvBooBossSpawnedBridge | 63 |
| id_bhvBooCage | 64 |
| id_bhvBooInCastle | 65 |
| id_bhvBookendSpawn | 66 |
| id_bhvBookSwitch | 67 |
| id_bhvBooWithCage | 68 |
| id_bhvBouncingFireball | 69 |
| id_bhvBouncingFireballFlame | 70 |
| id_bhvBowlingBall | 71 |
| id_bhvBowser | 72 |
| id_bhvBowserBodyAnchor | 73 |
| id_bhvBowserBomb | 74 |
| id_bhvBowserBombExplosion | 75 |
| id_bhvBowserBombSmoke | 76 |
| id_bhvBowserCourseRedCoinStar | 77 |
| id_bhvBowserFlameSpawn | 78 |
| id_bhvBowserKey | 79 |
| id_bhvBowserKeyCourseExit | 80 |
| id_bhvBowserKeyUnlockDoor | 81 |
| id_bhvBowserShockWave | 82 |
| id_bhvBowsersSub | 83 |
| id_bhvBowserSubDoor | 84 |
| id_bhvBowserTailAnchor | 85 |
| id_bhvBreakableBox | 86 |
| id_bhvBreakableBoxSmall | 87 |
| id_bhvBreakBoxTriangle | 88 |
| id_bhvBreathParticleSpawner | 89 |
| id_bhvBub | 90 |
| id_bhvBubba | 91 |
| id_bhvBubbleMaybe | 92 |
| id_bhvBubbleParticleSpawner | 93 |
| id_bhvBubblePlayer | 94 |
| id_bhvBubbleSplash | 95 |
| id_bhvBulletBill | 96 |
| id_bhvBulletBillCannon | 97 |
| id_bhvButterfly | 98 |
| id_bhvCameraLakitu | 99 |
| id_bhvCannon | 100 |
| id_bhvCannonBarrel | 101 |
| id_bhvCannonBarrelBubbles | 102 |
| id_bhvCannonBaseUnused | 103 |
| id_bhvCannonClosed | 104 |
| id_bhvCapSwitch | 105 |
| id_bhvCapSwitchBase | 106 |
| id_bhvCarrySomething1 | 107 |
| id_bhvCarrySomething2 | 108 |
| id_bhvCarrySomething3 | 109 |
| id_bhvCarrySomething4 | 110 |
| id_bhvCarrySomething5 | 111 |
| id_bhvCarrySomething6 | 112 |
| id_bhvCastleFlagWaving | 113 |
| id_bhvCastleFloorTrap | 114 |
| id_bhvCcmTouchedStarSpawn | 115 |
| id_bhvCelebrationStar | 116 |
| id_bhvCelebrationStarSparkle | 117 |
| id_bhvChainChomp | 118 |
| id_bhvChainChompChainPart | 119 |
| id_bhvChainChompGate | 120 |
| id_bhvCheckerboardElevatorGroup | 121 |
| id_bhvCheckerboardPlatformSub | 122 |
| id_bhvChirpChirp | 123 |
| id_bhvChirpChirpUnused | 124 |
| id_bhvChuckya | 125 |
| id_bhvChuckyaAnchorMario | 126 |
| id_bhvCirclingAmp | 127 |
| id_bhvClamShell | 128 |
| id_bhvClockHourHand | 129 |
| id_bhvClockMinuteHand | 130 |
| id_bhvCloud | 131 |
| id_bhvCloudPart | 132 |
| id_bhvCoffin | 133 |
| id_bhvCoffinSpawner | 134 |
| id_bhvCoinFormation | 135 |
| id_bhvCoinFormationSpawn | 136 |
| id_bhvCoinInsideBoo | 137 |
| id_bhvCoinSparkles | 138 |
| id_bhvControllablePlatform | 139 |
| id_bhvControllablePlatformSub | 140 |
| id_bhvCourtyardBooTriplet | 141 |
| id_bhvCutOutObject | 142 |
| id_bhvDddMovingPole | 143 |
| id_bhvDDDPole | 144 |
| id_bhvDddWarp | 145 |
| id_bhvDeathWarp | 146 |
| id_bhvDecorativePendulum | 147 |
| id_bhvDirtParticleSpawner | 148 |
| id_bhvDonutPlatform | 149 |
| id_bhvDonutPlatformSpawner | 150 |
| id_bhvDoor | 151 |
| id_bhvDoorWarp | 152 |
| id_bhvDorrie | 153 |
| id_bhvEndBirds1 | 154 |
| id_bhvEndBirds2 | 155 |
| id_bhvEndPeach | 156 |
| id_bhvEndToad | 157 |
| id_bhvEnemyLakitu | 158 |
| id_bhvExclamationBox | 159 |
| id_bhvExitPodiumWarp | 160 |
| id_bhvExplosion | 161 |
| id_bhvEyerokBoss | 162 |
| id_bhvEyerokHand | 163 |
| id_bhvFadingWarp | 164 |
| id_bhvFallingBowserPlatform | 165 |
| id_bhvFallingPillar | 166 |
| id_bhvFallingPillarHitbox | 167 |
| id_bhvFerrisWheelAxle | 168 |
| id_bhvFerrisWheelPlatform | 169 |
| id_bhvFewBlueFishSpawner | 170 |
| id_bhvFireParticleSpawner | 171 |
| id_bhvFirePiranhaPlant | 172 |
| id_bhvFireSpitter | 173 |
| id_bhvFish | 174 |
| id_bhvFishGroup | 175 |
| id_bhvFishSpawner | 176 |
| id_bhvFlame | 177 |
| id_bhvFlameBouncing | 178 |
| id_bhvFlameBowser | 179 |
| id_bhvFlameFloatingLanding | 180 |
| id_bhvFlameLargeBurningOut | 181 |
| id_bhvFlameMovingForwardGrowing | 182 |
| id_bhvFlamethrower | 183 |
| id_bhvFlamethrowerFlame | 184 |
| id_bhvFloorSwitchAnimatesObject | 185 |
| id_bhvFloorSwitchGrills | 186 |
| id_bhvFloorSwitchHardcodedModel | 187 |
| id_bhvFloorSwitchHiddenObjects | 188 |
| id_bhvFloorTrapInCastle | 189 |
| id_bhvFlyGuy | 190 |
| id_bhvFlyguyFlame | 191 |
| id_bhvFlyingBookend | 192 |
| id_bhvFlyingWarp | 193 |
| id_bhvFreeBowlingBall | 194 |
| id_bhvGhostHuntBigBoo | 195 |
| id_bhvGhostHuntBoo | 196 |
| id_bhvGiantPole | 197 |
| id_bhvGoldenCoinSparkles | 198 |
| id_bhvGoomba | 199 |
| id_bhvGoombaTripletSpawner | 200 |
| id_bhvGrandStar | 201 |
| id_bhvGrindel | 202 |
| id_bhvHardAirKnockBackWarp | 203 |
| id_bhvHauntedBookshelf | 204 |
| id_bhvHauntedBookshelfManager | 205 |
| id_bhvHauntedChair | 206 |
| id_bhvHeaveHo | 207 |
| id_bhvHeaveHoThrowMario | 208 |
| id_bhvHidden1up | 209 |
| id_bhvHidden1upInPole | 210 |
| id_bhvHidden1upInPoleSpawner | 211 |
| id_bhvHidden1upInPoleTrigger | 212 |
| id_bhvHidden1upTrigger | 213 |
| id_bhvHiddenAt120Stars | 214 |
| id_bhvHiddenBlueCoin | 215 |
| id_bhvHiddenObject | 216 |
| id_bhvHiddenRedCoinStar | 217 |
| id_bhvHiddenStaircaseStep | 218 |
| id_bhvHiddenStar | 219 |
| id_bhvHiddenStarTrigger | 220 |
| id_bhvHmcElevatorPlatform | 221 |
| id_bhvHomingAmp | 222 |
| id_bhvHoot | 223 |
| id_bhvHorizontalGrindel | 224 |
| id_bhvHorStarParticleSpawner | 225 |
| id_bhvIdleWaterWave | 226 |
| id_bhvIgloo | 227 |
| id_bhvInitializeChangingWaterLevel | 228 |
| id_bhvInsideCannon | 229 |
| id_bhvInstantActiveWarp | 230 |
| id_bhvInSunkenShip | 231 |
| id_bhvInSunkenShip2 | 232 |
| id_bhvInSunkenShip3 | 233 |
| id_bhvIntroScene | 234 |
| id_bhvInvisibleObjectsUnderBridge | 235 |
| id_bhvJetStream | 236 |
| id_bhvJetStreamRingSpawner | 237 |
| id_bhvJetStreamWaterRing | 238 |
| id_bhvJrbFloatingBox | 239 |
| id_bhvJrbFloatingPlatform | 240 |
| id_bhvJrbSlidingBox | 241 |
| id_bhvJumpingBox | 242 |
| id_bhvKickableBoard | 243 |
| id_bhvKingBobomb | 244 |
| id_bhvKlepto | 245 |
| id_bhvKoopa | 246 |
| id_bhvKoopaFlag | 247 |
| id_bhvKoopaRaceEndpoint | 248 |
| id_bhvKoopaShell | 249 |
| id_bhvKoopaShellFlame | 250 |
| id_bhvKoopaShellUnderwater | 251 |
| id_bhvLargeBomp | 252 |
| id_bhvLaunchDeathWarp | 253 |
| id_bhvLaunchStarCollectWarp | 254 |
| id_bhvLeafParticleSpawner | 255 |
| id_bhvLllBowserPuzzle | 256 |
| id_bhvLllBowserPuzzlePiece | 257 |
| id_bhvLllDrawbridge | 258 |
| id_bhvLllDrawbridgeSpawner | 259 |
| id_bhvLllFloatingWoodBridge | 260 |
| id_bhvLllHexagonalMesh | 261 |
| id_bhvLllMovingOctagonalMeshPlatform | 262 |
| id_bhvLllRollingLog | 263 |
| id_bhvLllRotatingBlockWithFireBars | 264 |
| id_bhvLllRotatingHexagonalPlatform | 265 |
| id_bhvLllRotatingHexagonalRing | 266 |
| id_bhvLllRotatingHexFlame | 267 |
| id_bhvLllSinkingRectangularPlatform | 268 |
| id_bhvLllSinkingRockBlock | 269 |
| id_bhvLllSinkingSquarePlatforms | 270 |
| id_bhvLllTiltingInvertedPyramid | 271 |
| id_bhvLllTumblingBridge | 272 |
| id_bhvLllVolcanoFallingTrap | 273 |
| id_bhvLllWoodPiece | 274 |
| id_bhvMacroUkiki | 275 |
| id_bhvMadPiano | 276 |
| id_bhvMantaRay | 277 |
| id_bhvMantaRayRingManager | 278 |
| id_bhvMantaRayWaterRing | 279 |
| id_bhvManyBlueFishSpawner | 280 |
| id_bhvMario | 281 |
| id_bhvMenuButton | 282 |
| id_bhvMenuButtonManager | 283 |
| id_bhvMerryGoRound | 284 |
| id_bhvMerryGoRoundBigBoo | 285 |
| id_bhvMerryGoRoundBoo | 286 |
| id_bhvMerryGoRoundBooManager | 287 |
| id_bhvMeshElevator | 288 |
| id_bhvMessagePanel | 289 |
| id_bhvMetalCap | 290 |
| id_bhvMips | 291 |
| id_bhvMistCircParticleSpawner | 292 |
| id_bhvMistParticleSpawner | 293 |
| id_bhvMoatGrills | 294 |
| id_bhvMoneybag | 295 |
| id_bhvMoneybagHidden | 296 |
| id_bhvMontyMole | 297 |
| id_bhvMontyMoleHole | 298 |
| id_bhvMontyMoleRock | 299 |
| id_bhvMovingBlueCoin | 300 |
| id_bhvMovingYellowCoin | 301 |
| id_bhvMrBlizzard | 302 |
| id_bhvMrBlizzardSnowball | 303 |
| id_bhvMrI | 304 |
| id_bhvMrIBlueCoin | 305 |
| id_bhvMrIBody | 306 |
| id_bhvMrIParticle | 307 |
| id_bhvNormalCap | 308 |
| id_bhvObjectBubble | 309 |
| id_bhvObjectWaterSplash | 310 |
| id_bhvObjectWaterWave | 311 |
| id_bhvObjectWaveTrail | 312 |
| id_bhvOctagonalPlatformRotating | 313 |
| id_bhvOneCoin | 314 |
| id_bhvOpenableCageDoor | 315 |
| id_bhvOpenableGrill | 316 |
| id_bhvOrangeNumber | 317 |
| id_bhvPaintingDeathWarp | 318 |
| id_bhvPaintingStarCollectWarp | 319 |
| id_bhvPenguinBaby | 320 |
| id_bhvPenguinRaceFinishLine | 321 |
| id_bhvPenguinRaceShortcutCheck | 322 |
| id_bhvPillarBase | 323 |
| id_bhvPiranhaPlant | 324 |
| id_bhvPiranhaPlantBubble | 325 |
| id_bhvPiranhaPlantWakingBubbles | 326 |
| id_bhvPitBowlingBall | 327 |
| id_bhvPlatformOnTrack | 328 |
| id_bhvPlaysMusicTrackWhenTouched | 329 |
| id_bhvPlungeBubble | 330 |
| id_bhvPokey | 331 |
| id_bhvPokeyBodyPart | 332 |
| id_bhvPoleGrabbing | 333 |
| id_bhvPoundTinyStarParticle | 334 |
| id_bhvPunchTinyTriangle | 335 |
| id_bhvPurpleParticle | 336 |
| id_bhvPurpleSwitchHiddenBoxes | 337 |
| id_bhvPushableMetalBox | 338 |
| id_bhvPyramidElevator | 339 |
| id_bhvPyramidElevatorTrajectoryMarkerBall | 340 |
| id_bhvPyramidPillarTouchDetector | 341 |
| id_bhvPyramidTop | 342 |
| id_bhvPyramidTopFragment | 343 |
| id_bhvRacingPenguin | 344 |
| id_bhvRandomAnimatedTexture | 345 |
| id_bhvRecoveryHeart | 346 |
| id_bhvRedCoin | 347 |
| id_bhvRedCoinStarMarker | 348 |
| id_bhvRespawner | 349 |
| id_bhvRockSolid | 350 |
| id_bhvRotatingCounterClockwise | 351 |
| id_bhvRotatingExclamationMark | 352 |
| id_bhvRotatingPlatform | 353 |
| id_bhvRrCruiserWing | 354 |
| id_bhvRrElevatorPlatform | 355 |
| id_bhvRrRotatingBridgePlatform | 356 |
| id_bhvSandSoundLoop | 357 |
| id_bhvScuttlebug | 358 |
| id_bhvScuttlebugSpawn | 359 |
| id_bhvSeaweed | 360 |
| id_bhvSeaweedBundle | 361 |
| id_bhvSeesawPlatform | 362 |
| id_bhvShallowWaterSplash | 363 |
| id_bhvShallowWaterWave | 364 |
| id_bhvShipPart3 | 365 |
| id_bhvSignOnWall | 366 |
| id_bhvSingleCoinGetsSpawned | 367 |
| id_bhvSkeeter | 368 |
| id_bhvSkeeterWave | 369 |
| id_bhvSlidingPlatform2 | 370 |
| id_bhvSlidingSnowMound | 371 |
| id_bhvSLSnowmanWind | 372 |
| id_bhvSLWalkingPenguin | 373 |
| id_bhvSmallBomp | 374 |
| id_bhvSmallBully | 375 |
| id_bhvSmallChillBully | 376 |
| id_bhvSmallParticle | 377 |
| id_bhvSmallParticleBubbles | 378 |
| id_bhvSmallParticleSnow | 379 |
| id_bhvSmallPenguin | 380 |
| id_bhvSmallPiranhaFlame | 381 |
| id_bhvSmallWaterWave | 382 |
| id_bhvSmallWaterWave398 | 383 |
| id_bhvSmallWhomp | 384 |
| id_bhvSmoke | 385 |
| id_bhvSnowBall | 386 |
| id_bhvSnowmansBodyCheckpoint | 387 |
| id_bhvSnowmansBottom | 388 |
| id_bhvSnowmansHead | 389 |
| id_bhvSnowMoundSpawn | 390 |
| id_bhvSnowParticleSpawner | 391 |
| id_bhvSnufit | 392 |
| id_bhvSnufitBalls | 393 |
| id_bhvSoundSpawner | 394 |
| id_bhvSparkle | 395 |
| id_bhvSparkleParticleSpawner | 396 |
| id_bhvSparkleSpawn | 397 |
| id_bhvSpawnedStar | 398 |
| id_bhvSpawnedStarNoLevelExit | 399 |
| id_bhvSpinAirborneCircleWarp | 400 |
| id_bhvSpinAirborneWarp | 401 |
| id_bhvSpindel | 402 |
| id_bhvSpindrift | 403 |
| id_bhvSpiny | 404 |
| id_bhvSquarishPathMoving | 405 |
| id_bhvSquarishPathParent | 406 |
| id_bhvSquishablePlatform | 407 |
| id_bhvSslMovingPyramidWall | 408 |
| id_bhvStar | 409 |
| id_bhvStarDoor | 410 |
| id_bhvStarKeyCollectionPuffSpawner | 411 |
| id_bhvStarSpawnCoordinates | 412 |
| id_bhvStaticCheckeredPlatform | 413 |
| id_bhvStaticObject | 414 |
| id_bhvStrongWindParticle | 415 |
| id_bhvStub | 416 |
| id_bhvStub1D0C | 417 |
| id_bhvStub1D70 | 418 |
| id_bhvSunkenShipPart | 419 |
| id_bhvSunkenShipPart2 | 420 |
| id_bhvSunkenShipSetRotation | 421 |
| id_bhvSushiShark | 422 |
| id_bhvSushiSharkCollisionChild | 423 |
| id_bhvSwimmingWarp | 424 |
| id_bhvSwingPlatform | 425 |
| id_bhvSwoop | 426 |
| id_bhvTankFishGroup | 427 |
| id_bhvTemporaryYellowCoin | 428 |
| id_bhvTenCoinsSpawn | 429 |
| id_bhvThiBowlingBallSpawner | 430 |
| id_bhvThiHugeIslandTop | 431 |
| id_bhvThiTinyIslandTop | 432 |
| id_bhvThreeCoinsSpawn | 433 |
| id_bhvThwomp | 434 |
| id_bhvThwomp2 | 435 |
| id_bhvTiltingBowserLavaPlatform | 436 |
| id_bhvTinyStrongWindParticle | 437 |
| id_bhvToadMessage | 438 |
| id_bhvTower | 439 |
| id_bhvTowerDoor | 440 |
| id_bhvTowerPlatformGroup | 441 |
| id_bhvToxBox | 442 |
| id_bhvTrackBall | 443 |
| id_bhvTreasureChestBottom | 444 |
| id_bhvTreasureChests | 445 |
| id_bhvTreasureChestsJrb | 446 |
| id_bhvTreasureChestsShip | 447 |
| id_bhvTreasureChestTop | 448 |
| id_bhvTree | 449 |
| id_bhvTreeLeaf | 450 |
| id_bhvTreeSnow | 451 |
| id_bhvTriangleParticleSpawner | 452 |
| id_bhvTripletButterfly | 453 |
| id_bhvTTC2DRotator | 454 |
| id_bhvTTCCog | 455 |
| id_bhvTTCElevator | 456 |
| id_bhvTTCMovingBar | 457 |
| id_bhvTTCPendulum | 458 |
| id_bhvTTCPitBlock | 459 |
| id_bhvTTCRotatingSolid | 460 |
| id_bhvTTCSpinner | 461 |
| id_bhvTTCTreadmill | 462 |
| id_bhvTtmBowlingBallSpawner | 463 |
| id_bhvTtmRollingLog | 464 |
| id_bhvTumblingBridgePlatform | 465 |
| id_bhvTuxiesMother | 466 |
| id_bhvTweester | 467 |
| id_bhvTweesterSandParticle | 468 |
| id_bhvUkiki | 469 |
| id_bhvUkikiCage | 470 |
| id_bhvUkikiCageChild | 471 |
| id_bhvUkikiCageStar | 472 |
| id_bhvUnagi | 473 |
| id_bhvUnagiSubobject | 474 |
| id_bhvUnlockDoorStar | 475 |
| id_bhvUnused05A8 | 476 |
| id_bhvUnused0DFC | 477 |
| id_bhvUnused1820 | 478 |
| id_bhvUnused1F30 | 479 |
| id_bhvUnused20E0 | 480 |
| id_bhvUnused2A10 | 481 |
| id_bhvUnused2A54 | 482 |
| id_bhvUnusedFakeStar | 483 |
| id_bhvUnusedParticleSpawn | 484 |
| id_bhvUnusedPoundablePlatform | 485 |
| id_bhvVanishCap | 486 |
| id_bhvVertStarParticleSpawner | 487 |
| id_bhvVolcanoFlames | 488 |
| id_bhvVolcanoSoundLoop | 489 |
| id_bhvWallTinyStarParticle | 490 |
| id_bhvWarp | 491 |
| id_bhvWarpPipe | 492 |
| id_bhvWaterAirBubble | 493 |
| id_bhvWaterBomb | 494 |
| id_bhvWaterBombCannon | 495 |
| id_bhvWaterBombShadow | 496 |
| id_bhvWaterBombSpawner | 497 |
| id_bhvWaterDroplet | 498 |
| id_bhvWaterDropletSplash | 499 |
| id_bhvWaterfallSoundLoop | 500 |
| id_bhvWaterLevelDiamond | 501 |
| id_bhvWaterLevelPillar | 502 |
| id_bhvWaterMist | 503 |
| id_bhvWaterMist2 | 504 |
| id_bhvWaterSplash | 505 |
| id_bhvWaveTrail | 506 |
| id_bhvWdwExpressElevator | 507 |
| id_bhvWdwExpressElevatorPlatform | 508 |
| id_bhvWdwRectangularFloatingPlatform | 509 |
| id_bhvWdwSquareFloatingPlatform | 510 |
| id_bhvWfBreakableWallLeft | 511 |
| id_bhvWfBreakableWallRight | 512 |
| id_bhvWfElevatorTowerPlatform | 513 |
| id_bhvWfRotatingWoodenPlatform | 514 |
| id_bhvWfSlidingPlatform | 515 |
| id_bhvWfSlidingTowerPlatform | 516 |
| id_bhvWfSolidTowerPlatform | 517 |
| id_bhvWfTumblingBridge | 518 |
| id_bhvWhirlpool | 519 |
| id_bhvWhitePuff1 | 520 |
| id_bhvWhitePuff2 | 521 |
| id_bhvWhitePuffExplosion | 522 |
| id_bhvWhitePuffSmoke | 523 |
| id_bhvWhitePuffSmoke2 | 524 |
| id_bhvWhompKingBoss | 525 |
| id_bhvWigglerBody | 526 |
| id_bhvWigglerHead | 527 |
| id_bhvWind | 528 |
| id_bhvWingCap | 529 |
| id_bhvWoodenPost | 530 |
| id_bhvYellowBackgroundInMenu | 531 |
| id_bhvYellowBall | 532 |
| id_bhvYellowCoin | 533 |
| id_bhvYoshi | 534 |
| id_RM_Scroll_Texture | 535 |
| id_editor_Scroll_Texture | 536 |
| id_bhvBlueCoinNumber | 537 |
| id_bhvStarNumber | 538 |
| id_bhv_max_count | 539 |

[:arrow_up_small:](#)

<br />

## [camera.h](#camera.h)
- CAMERA_MODE_8_DIRECTIONS
- CAMERA_MODE_BEHIND_MARIO
- CAMERA_MODE_BOSS_FIGHT
- CAMERA_MODE_CLOSE
- CAMERA_MODE_C_UP
- CAMERA_MODE_FIXED
- CAMERA_MODE_FREE_ROAM
- CAMERA_MODE_INSIDE_CANNON
- CAMERA_MODE_NEWCAM
- CAMERA_MODE_NONE
- CAMERA_MODE_OUTWARD_RADIAL
- CAMERA_MODE_PARALLEL_TRACKING
- CAMERA_MODE_RADIAL
- CAMERA_MODE_ROM_HACK
- CAMERA_MODE_SLIDE_HOOT
- CAMERA_MODE_SPIRAL_STAIRS
- CAMERA_MODE_WATER_SURFACE
- CAM_ANGLE_LAKITU
- CAM_ANGLE_MARIO
- CAM_EVENT_BOWSER_INIT
- CAM_EVENT_BOWSER_JUMP
- CAM_EVENT_BOWSER_THROW_BOUNCE
- CAM_EVENT_CANNON
- CAM_EVENT_DOOR
- CAM_EVENT_DOOR_WARP
- CAM_EVENT_SHOT_FROM_CANNON
- CAM_EVENT_START_CREDITS
- CAM_EVENT_START_ENDING
- CAM_EVENT_START_END_WAVING
- CAM_EVENT_START_GRAND_STAR
- CAM_EVENT_START_INTRO
- CAM_EVENT_UNUSED_3
- CAM_FLAG_BEHIND_MARIO_POST_DOOR
- CAM_FLAG_BLOCK_AREA_PROCESSING
- CAM_FLAG_BLOCK_SMOOTH_MOVEMENT
- CAM_FLAG_CAM_NEAR_WALL
- CAM_FLAG_CCM_SLIDE_SHORTCUT
- CAM_FLAG_CHANGED_PARTRACK_INDEX
- CAM_FLAG_COLLIDED_WITH_WALL
- CAM_FLAG_FRAME_AFTER_CAM_INIT
- CAM_FLAG_SLEEPING
- CAM_FLAG_SMOOTH_MOVEMENT
- CAM_FLAG_START_TRANSITION
- CAM_FLAG_TRANSITION_OUT_OF_C_UP
- CAM_FLAG_UNUSED_13
- CAM_FLAG_UNUSED_7
- CAM_FLAG_UNUSED_8
- CAM_FLAG_UNUSED_CUTSCENE_ACTIVE
- CAM_FOV_APP_20
- CAM_FOV_APP_30
- CAM_FOV_APP_45
- CAM_FOV_APP_60
- CAM_FOV_APP_80
- CAM_FOV_BBH
- CAM_FOV_DEFAULT
- CAM_FOV_SET_29
- CAM_FOV_SET_30
- CAM_FOV_SET_45
- CAM_FOV_ZOOM_30
- CAM_MODE_LAKITU_WAS_ZOOMED_OUT
- CAM_MODE_MARIO_ACTIVE
- CAM_MODE_MARIO_SELECTED
- CAM_MOVE_ALREADY_ZOOMED_OUT
- CAM_MOVE_C_UP_MODE
- CAM_MOVE_ENTERED_ROTATE_SURFACE
- CAM_MOVE_FIX_IN_PLACE
- CAM_MOVE_INIT_CAMERA
- CAM_MOVE_METAL_BELOW_WATER
- CAM_MOVE_PAUSE_SCREEN
- CAM_MOVE_RESTRICT
- CAM_MOVE_RETURN_TO_MIDDLE
- CAM_MOVE_ROTATE
- CAM_MOVE_ROTATE_LEFT
- CAM_MOVE_ROTATE_RIGHT
- CAM_MOVE_STARTED_EXITING_C_UP
- CAM_MOVE_SUBMERGED
- CAM_MOVE_UNKNOWN_11
- CAM_MOVE_UNKNOWN_8
- CAM_MOVE_ZOOMED_OUT
- CAM_MOVING_INTO_MODE
- CAM_SELECTION_FIXED
- CAM_SELECTION_MARIO
- CAM_SOUND_C_UP_PLAYED
- CAM_SOUND_FIXED_ACTIVE
- CAM_SOUND_MARIO_ACTIVE
- CAM_SOUND_NORMAL_ACTIVE
- CAM_SOUND_UNUSED_SELECT_FIXED
- CAM_SOUND_UNUSED_SELECT_MARIO
- CAM_STATUS_C_DOWN
- CAM_STATUS_C_MODE_GROUP
- CAM_STATUS_C_UP
- CAM_STATUS_FIXED
- CAM_STATUS_LAKITU
- CAM_STATUS_MARIO
- CAM_STATUS_MODE_GROUP
- CAM_STATUS_NONE
- CUTSCENE_0F_UNUSED
- CUTSCENE_CAP_SWITCH_PRESS
- CUTSCENE_CREDITS
- CUTSCENE_DANCE_CLOSEUP
- CUTSCENE_DANCE_DEFAULT
- CUTSCENE_DANCE_FLY_AWAY
- CUTSCENE_DANCE_ROTATE
- CUTSCENE_DEATH_EXIT
- CUTSCENE_DEATH_ON_BACK
- CUTSCENE_DEATH_ON_STOMACH
- CUTSCENE_DIALOG
- CUTSCENE_DOOR_PULL
- CUTSCENE_DOOR_PULL_MODE
- CUTSCENE_DOOR_PUSH
- CUTSCENE_DOOR_PUSH_MODE
- CUTSCENE_DOOR_WARP
- CUTSCENE_ENDING
- CUTSCENE_END_WAVING
- CUTSCENE_ENTER_BOWSER_ARENA
- CUTSCENE_ENTER_CANNON
- CUTSCENE_ENTER_PAINTING
- CUTSCENE_ENTER_POOL
- CUTSCENE_ENTER_PYRAMID_TOP
- CUTSCENE_EXIT_BOWSER_DEATH
- CUTSCENE_EXIT_BOWSER_SUCC
- CUTSCENE_EXIT_FALL_WMOTR
- CUTSCENE_EXIT_PAINTING_SUCC
- CUTSCENE_EXIT_SPECIAL_SUCC
- CUTSCENE_EXIT_WATERFALL
- CUTSCENE_GRAND_STAR
- CUTSCENE_INTRO_PEACH
- CUTSCENE_KEY_DANCE
- CUTSCENE_LOOP
- CUTSCENE_NONPAINTING_DEATH
- CUTSCENE_PALETTE_EDITOR
- CUTSCENE_PREPARE_CANNON
- CUTSCENE_QUICKSAND_DEATH
- CUTSCENE_RACE_DIALOG
- CUTSCENE_READ_MESSAGE
- CUTSCENE_RED_COIN_STAR_SPAWN
- CUTSCENE_SLIDING_DOORS_OPEN
- CUTSCENE_SSL_PYRAMID_EXPLODE
- CUTSCENE_STANDING_DEATH
- CUTSCENE_STAR_SPAWN
- CUTSCENE_STOP
- CUTSCENE_SUFFOCATION_DEATH
- CUTSCENE_UNLOCK_KEY_DOOR
- CUTSCENE_UNUSED_EXIT
- CUTSCENE_WATER_DEATH
- DOOR_DEFAULT
- DOOR_ENTER_LOBBY
- DOOR_LEAVING_SPECIAL
- HAND_CAM_SHAKE_CUTSCENE
- HAND_CAM_SHAKE_HANG_OWL
- HAND_CAM_SHAKE_HIGH
- HAND_CAM_SHAKE_LOW
- HAND_CAM_SHAKE_OFF
- HAND_CAM_SHAKE_STAR_DANCE
- HAND_CAM_SHAKE_UNUSED
- SHAKE_ATTACK
- SHAKE_ENV_BOWSER_JUMP
- SHAKE_ENV_BOWSER_THROW_BOUNCE
- SHAKE_ENV_EXPLOSION
- SHAKE_ENV_FALLING_BITS_PLAT
- SHAKE_ENV_JRB_SHIP_DRAIN
- SHAKE_ENV_PYRAMID_EXPLODE
- SHAKE_ENV_UNUSED_5
- SHAKE_ENV_UNUSED_6
- SHAKE_ENV_UNUSED_7
- SHAKE_FALL_DAMAGE
- SHAKE_FOV_LARGE
- SHAKE_FOV_MEDIUM
- SHAKE_FOV_SMALL
- SHAKE_FOV_UNUSED
- SHAKE_GROUND_POUND
- SHAKE_HIT_FROM_BELOW
- SHAKE_LARGE_DAMAGE
- SHAKE_MED_DAMAGE
- SHAKE_POS_BOWLING_BALL
- SHAKE_POS_LARGE
- SHAKE_POS_MEDIUM
- SHAKE_POS_SMALL
- SHAKE_SHOCK
- SHAKE_SMALL_DAMAGE

### [enum RomhackCameraOverride](#RomhackCameraOverride)
| Identifier | Value |
| :--------- | :---- |
| RCO_ALL | 0 |
| RCO_ALL_EXCEPT_BOWSER | 1 |
| RCO_NONE | 2 |

[:arrow_up_small:](#)

<br />

## [characters.h](#characters.h)

### [enum CharacterSound](#CharacterSound)
| Identifier | Value |
| :--------- | :---- |
| CHAR_SOUND_YAH_WAH_HOO | 0 |
| CHAR_SOUND_HOOHOO | 1 |
| CHAR_SOUND_YAHOO | 2 |
| CHAR_SOUND_UH | 3 |
| CHAR_SOUND_HRMM | 4 |
| CHAR_SOUND_WAH2 | 5 |
| CHAR_SOUND_WHOA | 6 |
| CHAR_SOUND_EEUH | 7 |
| CHAR_SOUND_ATTACKED | 8 |
| CHAR_SOUND_OOOF | 9 |
| CHAR_SOUND_OOOF2 | 10 |
| CHAR_SOUND_HERE_WE_GO | 11 |
| CHAR_SOUND_YAWNING | 12 |
| CHAR_SOUND_SNORING1 | 13 |
| CHAR_SOUND_SNORING2 | 14 |
| CHAR_SOUND_WAAAOOOW | 15 |
| CHAR_SOUND_HAHA | 16 |
| CHAR_SOUND_HAHA_2 | 17 |
| CHAR_SOUND_UH2 | 18 |
| CHAR_SOUND_UH2_2 | 19 |
| CHAR_SOUND_ON_FIRE | 20 |
| CHAR_SOUND_DYING | 21 |
| CHAR_SOUND_PANTING_COLD | 22 |
| CHAR_SOUND_PANTING | 23 |
| CHAR_SOUND_COUGHING1 | 24 |
| CHAR_SOUND_COUGHING2 | 25 |
| CHAR_SOUND_COUGHING3 | 26 |
| CHAR_SOUND_PUNCH_YAH | 27 |
| CHAR_SOUND_PUNCH_HOO | 28 |
| CHAR_SOUND_MAMA_MIA | 29 |
| CHAR_SOUND_GROUND_POUND_WAH | 30 |
| CHAR_SOUND_DROWNING | 31 |
| CHAR_SOUND_PUNCH_WAH | 32 |
| CHAR_SOUND_YAHOO_WAHA_YIPPEE | 33 |
| CHAR_SOUND_DOH | 34 |
| CHAR_SOUND_GAME_OVER | 35 |
| CHAR_SOUND_HELLO | 36 |
| CHAR_SOUND_PRESS_START_TO_PLAY | 37 |
| CHAR_SOUND_TWIRL_BOUNCE | 38 |
| CHAR_SOUND_SNORING3 | 39 |
| CHAR_SOUND_SO_LONGA_BOWSER | 40 |
| CHAR_SOUND_IMA_TIRED | 41 |
| CHAR_SOUND_LETS_A_GO | 42 |
| CHAR_SOUND_OKEY_DOKEY | 43 |
| CHAR_SOUND_MAX | 44 |

### [enum CharacterType](#CharacterType)
| Identifier | Value |
| :--------- | :---- |
| CT_MARIO | 0 |
| CT_LUIGI | 1 |
| CT_TOAD | 2 |
| CT_WALUIGI | 3 |
| CT_WARIO | 4 |
| CT_MAX | 5 |

[:arrow_up_small:](#)

<br />

## [dialog_ids.h](#dialog_ids.h)

### [enum DialogId](#DialogId)
| Identifier | Value |
| :--------- | :---- |
| DIALOG_000 | 0 |
| DIALOG_001 | 1 |
| DIALOG_002 | 2 |
| DIALOG_003 | 3 |
| DIALOG_004 | 4 |
| DIALOG_005 | 5 |
| DIALOG_006 | 6 |
| DIALOG_007 | 7 |
| DIALOG_008 | 8 |
| DIALOG_009 | 9 |
| DIALOG_010 | 10 |
| DIALOG_011 | 11 |
| DIALOG_012 | 12 |
| DIALOG_013 | 13 |
| DIALOG_014 | 14 |
| DIALOG_015 | 15 |
| DIALOG_016 | 16 |
| DIALOG_017 | 17 |
| DIALOG_018 | 18 |
| DIALOG_019 | 19 |
| DIALOG_020 | 20 |
| DIALOG_021 | 21 |
| DIALOG_022 | 22 |
| DIALOG_023 | 23 |
| DIALOG_024 | 24 |
| DIALOG_025 | 25 |
| DIALOG_026 | 26 |
| DIALOG_027 | 27 |
| DIALOG_028 | 28 |
| DIALOG_029 | 29 |
| DIALOG_030 | 30 |
| DIALOG_031 | 31 |
| DIALOG_032 | 32 |
| DIALOG_033 | 33 |
| DIALOG_034 | 34 |
| DIALOG_035 | 35 |
| DIALOG_036 | 36 |
| DIALOG_037 | 37 |
| DIALOG_038 | 38 |
| DIALOG_039 | 39 |
| DIALOG_040 | 40 |
| DIALOG_041 | 41 |
| DIALOG_042 | 42 |
| DIALOG_043 | 43 |
| DIALOG_044 | 44 |
| DIALOG_045 | 45 |
| DIALOG_046 | 46 |
| DIALOG_047 | 47 |
| DIALOG_048 | 48 |
| DIALOG_049 | 49 |
| DIALOG_050 | 50 |
| DIALOG_051 | 51 |
| DIALOG_052 | 52 |
| DIALOG_053 | 53 |
| DIALOG_054 | 54 |
| DIALOG_055 | 55 |
| DIALOG_056 | 56 |
| DIALOG_057 | 57 |
| DIALOG_058 | 58 |
| DIALOG_059 | 59 |
| DIALOG_060 | 60 |
| DIALOG_061 | 61 |
| DIALOG_062 | 62 |
| DIALOG_063 | 63 |
| DIALOG_064 | 64 |
| DIALOG_065 | 65 |
| DIALOG_066 | 66 |
| DIALOG_067 | 67 |
| DIALOG_068 | 68 |
| DIALOG_069 | 69 |
| DIALOG_070 | 70 |
| DIALOG_071 | 71 |
| DIALOG_072 | 72 |
| DIALOG_073 | 73 |
| DIALOG_074 | 74 |
| DIALOG_075 | 75 |
| DIALOG_076 | 76 |
| DIALOG_077 | 77 |
| DIALOG_078 | 78 |
| DIALOG_079 | 79 |
| DIALOG_080 | 80 |
| DIALOG_081 | 81 |
| DIALOG_082 | 82 |
| DIALOG_083 | 83 |
| DIALOG_084 | 84 |
| DIALOG_085 | 85 |
| DIALOG_086 | 86 |
| DIALOG_087 | 87 |
| DIALOG_088 | 88 |
| DIALOG_089 | 89 |
| DIALOG_090 | 90 |
| DIALOG_091 | 91 |
| DIALOG_092 | 92 |
| DIALOG_093 | 93 |
| DIALOG_094 | 94 |
| DIALOG_095 | 95 |
| DIALOG_096 | 96 |
| DIALOG_097 | 97 |
| DIALOG_098 | 98 |
| DIALOG_099 | 99 |
| DIALOG_100 | 100 |
| DIALOG_101 | 101 |
| DIALOG_102 | 102 |
| DIALOG_103 | 103 |
| DIALOG_104 | 104 |
| DIALOG_105 | 105 |
| DIALOG_106 | 106 |
| DIALOG_107 | 107 |
| DIALOG_108 | 108 |
| DIALOG_109 | 109 |
| DIALOG_110 | 110 |
| DIALOG_111 | 111 |
| DIALOG_112 | 112 |
| DIALOG_113 | 113 |
| DIALOG_114 | 114 |
| DIALOG_115 | 115 |
| DIALOG_116 | 116 |
| DIALOG_117 | 117 |
| DIALOG_118 | 118 |
| DIALOG_119 | 119 |
| DIALOG_120 | 120 |
| DIALOG_121 | 121 |
| DIALOG_122 | 122 |
| DIALOG_123 | 123 |
| DIALOG_124 | 124 |
| DIALOG_125 | 125 |
| DIALOG_126 | 126 |
| DIALOG_127 | 127 |
| DIALOG_128 | 128 |
| DIALOG_129 | 129 |
| DIALOG_130 | 130 |
| DIALOG_131 | 131 |
| DIALOG_132 | 132 |
| DIALOG_133 | 133 |
| DIALOG_134 | 134 |
| DIALOG_135 | 135 |
| DIALOG_136 | 136 |
| DIALOG_137 | 137 |
| DIALOG_138 | 138 |
| DIALOG_139 | 139 |
| DIALOG_140 | 140 |
| DIALOG_141 | 141 |
| DIALOG_142 | 142 |
| DIALOG_143 | 143 |
| DIALOG_144 | 144 |
| DIALOG_145 | 145 |
| DIALOG_146 | 146 |
| DIALOG_147 | 147 |
| DIALOG_148 | 148 |
| DIALOG_149 | 149 |
| DIALOG_150 | 150 |
| DIALOG_151 | 151 |
| DIALOG_152 | 152 |
| DIALOG_153 | 153 |
| DIALOG_154 | 154 |
| DIALOG_155 | 155 |
| DIALOG_156 | 156 |
| DIALOG_157 | 157 |
| DIALOG_158 | 158 |
| DIALOG_159 | 159 |
| DIALOG_160 | 160 |
| DIALOG_161 | 161 |
| DIALOG_162 | 162 |
| DIALOG_163 | 163 |
| DIALOG_164 | 164 |
| DIALOG_165 | 165 |
| DIALOG_166 | 166 |
| DIALOG_167 | 167 |
| DIALOG_168 | 168 |
| DIALOG_169 | 169 |
| DIALOG_COUNT | 170 |

[:arrow_up_small:](#)

<br />

## [djui_console.h](#djui_console.h)

### [enum ConsoleMessageLevel](#ConsoleMessageLevel)
| Identifier | Value |
| :--------- | :---- |
| CONSOLE_MESSAGE_INFO | 0 |
| CONSOLE_MESSAGE_WARNING | 1 |
| CONSOLE_MESSAGE_ERROR | 2 |

[:arrow_up_small:](#)

<br />

## [djui_hud_utils.h](#djui_hud_utils.h)

### [enum DjuiFontType](#DjuiFontType)
| Identifier | Value |
| :--------- | :---- |
| FONT_NORMAL | 0 |
| FONT_MENU | 1 |
| FONT_HUD | 2 |
| FONT_ALIASED | 3 |
| FONT_CUSTOM_HUD | 4 |
| FONT_RECOLOR_HUD | 5 |
| FONT_COUNT | 6 |

### [enum HudUtilsFilter](#HudUtilsFilter)
| Identifier | Value |
| :--------- | :---- |
| FILTER_NEAREST | 0 |
| FILTER_LINEAR | 1 |
| FILTER_COUNT | 2 |

### [enum HudUtilsResolution](#HudUtilsResolution)
| Identifier | Value |
| :--------- | :---- |
| RESOLUTION_DJUI | 0 |
| RESOLUTION_N64 | 1 |
| RESOLUTION_COUNT | 2 |

[:arrow_up_small:](#)

<br />

## [envfx_snow.h](#envfx_snow.h)
- ENVFX_BUBBLE_START
- ENVFX_FLOWERS
- ENVFX_JETSTREAM_BUBBLES
- ENVFX_LAVA_BUBBLES
- ENVFX_MODE_NONE
- ENVFX_MODE_NO_OVERRIDE
- ENVFX_SNOW_BLIZZARD
- ENVFX_SNOW_NORMAL
- ENVFX_SNOW_WATER
- ENVFX_WHIRLPOOL_BUBBLES

[:arrow_up_small:](#)

<br />

## [external.h](#external.h)
- DS_DIFF
- SEQ_PLAYER_ENV
- SEQ_PLAYER_LEVEL
- SEQ_PLAYER_SFX

### [enum DialogSound](#DialogSound)
| Identifier | Value |
| :--------- | :---- |
| DS_UKIKI | 0 |
| DS_TUXIE | 1 |
| DS_BOWS1 | 2 |
| DS_KOOPA | 3 |
| DS_KBOMB | 4 |
| DS_BOO | 5 |
| DS_BOMB | 6 |
| DS_BOWS2 | 7 |
| DS_GRUNT | 8 |
| DS_WIGLR | 9 |
| DS_YOSHI | 10 |
| DS_MAX | 11 |
| DS_NONE | 0xff |

[:arrow_up_small:](#)

<br />

## [first_person_cam.h](#first_person_cam.h)
- FIRST_PERSON_DEFAULT_FOV
- FIRST_PERSON_MARIO_HEAD_POS
- FIRST_PERSON_MARIO_HEAD_POS_SHORT

[:arrow_up_small:](#)

<br />

## [geo_commands.h](#geo_commands.h)
- BACKGROUND_ABOVE_CLOUDS
- BACKGROUND_BELOW_CLOUDS
- BACKGROUND_CUSTOM
- BACKGROUND_DESERT
- BACKGROUND_FLAMING_SKY
- BACKGROUND_GREEN_SKY
- BACKGROUND_HAUNTED
- BACKGROUND_OCEAN_SKY
- BACKGROUND_PURPLE_SKY
- BACKGROUND_SNOW_MOUNTAINS
- BACKGROUND_UNDERWATER_CITY

[:arrow_up_small:](#)

<br />

## [graph_node.h](#graph_node.h)
- GEO_CONTEXT_AREA_INIT
- GEO_CONTEXT_AREA_LOAD
- GEO_CONTEXT_AREA_UNLOAD
- GEO_CONTEXT_CREATE
- GEO_CONTEXT_HELD_OBJ
- GEO_CONTEXT_RENDER
- GFX_NUM_MASTER_LISTS
- GRAPH_EXTRA_FORCE_3D
- GRAPH_NODE_TYPE_400
- GRAPH_NODE_TYPE_ANIMATED_PART
- GRAPH_NODE_TYPE_BACKGROUND
- GRAPH_NODE_TYPE_BILLBOARD
- GRAPH_NODE_TYPE_CAMERA
- GRAPH_NODE_TYPE_CULLING_RADIUS
- GRAPH_NODE_TYPE_DISPLAY_LIST
- GRAPH_NODE_TYPE_FUNCTIONAL
- GRAPH_NODE_TYPE_GENERATED_LIST
- GRAPH_NODE_TYPE_HELD_OBJ
- GRAPH_NODE_TYPE_LEVEL_OF_DETAIL
- GRAPH_NODE_TYPE_MASTER_LIST
- GRAPH_NODE_TYPE_OBJECT
- GRAPH_NODE_TYPE_OBJECT_PARENT
- GRAPH_NODE_TYPE_ORTHO_PROJECTION
- GRAPH_NODE_TYPE_PERSPECTIVE
- GRAPH_NODE_TYPE_ROOT
- GRAPH_NODE_TYPE_ROTATION
- GRAPH_NODE_TYPE_SCALE
- GRAPH_NODE_TYPE_SHADOW
- GRAPH_NODE_TYPE_START
- GRAPH_NODE_TYPE_SWITCH_CASE
- GRAPH_NODE_TYPE_TRANSLATION
- GRAPH_NODE_TYPE_TRANSLATION_ROTATION
- GRAPH_RENDER_ACTIVE
- GRAPH_RENDER_BILLBOARD
- GRAPH_RENDER_CHILDREN_FIRST
- GRAPH_RENDER_CYLBOARD
- GRAPH_RENDER_HAS_ANIMATION
- GRAPH_RENDER_INVISIBLE
- GRAPH_RENDER_PLAYER
- GRAPH_RENDER_Z_BUFFER

[:arrow_up_small:](#)

<br />

## [interaction.c](#interaction.c)

[:arrow_up_small:](#)

<br />

## [interaction.h](#interaction.h)
- ATTACK_FAST_ATTACK
- ATTACK_FROM_ABOVE
- ATTACK_FROM_BELOW
- ATTACK_GROUND_POUND_OR_TWIRL
- ATTACK_KICK_OR_TRIP
- ATTACK_PUNCH
- INTERACT_UNKNOWN_08
- INT_ANY_ATTACK
- INT_ATTACK_NOT_FROM_BELOW
- INT_ATTACK_NOT_WEAK_FROM_ABOVE
- INT_ATTACK_SLIDE
- INT_STATUS_ATTACKED_MARIO
- INT_STATUS_ATTACK_MASK
- INT_STATUS_GRABBED_MARIO
- INT_STATUS_HIT_BY_SHOCKWAVE
- INT_STATUS_HIT_MINE
- INT_STATUS_HOOT_GRABBED_BY_MARIO
- INT_STATUS_INTERACTED
- INT_STATUS_MARIO_DROP_OBJECT
- INT_STATUS_MARIO_UNK1
- INT_STATUS_MARIO_UNK2
- INT_STATUS_MARIO_UNK5
- INT_STATUS_MARIO_UNK6
- INT_STATUS_MARIO_UNK7
- INT_STATUS_STOP_RIDING
- INT_STATUS_TOUCHED_BOB_OMB
- INT_STATUS_TRAP_TURN
- INT_STATUS_WAS_ATTACKED
- INT_SUBTYPE_BIG_KNOCKBACK
- INT_SUBTYPE_DELAY_INVINCIBILITY
- INT_SUBTYPE_DROP_IMMEDIATELY
- INT_SUBTYPE_EATS_MARIO
- INT_SUBTYPE_FADING_WARP
- INT_SUBTYPE_GRABS_MARIO
- INT_SUBTYPE_GRAND_STAR
- INT_SUBTYPE_HOLDABLE_NPC
- INT_SUBTYPE_KICKABLE
- INT_SUBTYPE_NOT_GRABBABLE
- INT_SUBTYPE_NO_EXIT
- INT_SUBTYPE_NPC
- INT_SUBTYPE_SIGN
- INT_SUBTYPE_STAR_DOOR
- INT_SUBTYPE_TWIRL_BOUNCE

### [enum InteractionFlag](#InteractionFlag)
| Identifier | Value |
| :--------- | :---- |
| INT_GROUND_POUND | (1 << 0) |
| INT_PUNCH | (1 << 1) |
| INT_KICK | (1 << 2) |
| INT_TRIP | (1 << 3) |
| INT_SLIDE_KICK | (1 << 4) |
| INT_FAST_ATTACK_OR_SHELL | (1 << 5) |
| INT_HIT_FROM_ABOVE | (1 << 6) |
| INT_HIT_FROM_BELOW | (1 << 7) |
| INT_TWIRL | (1 << 8) |
| INT_GROUND_POUND_OR_TWIRL | (INT_GROUND_POUND | INT_TWIRL) |
| INT_LUA | (1 << 31) |

### [enum InteractionType](#InteractionType)
| Identifier | Value |
| :--------- | :---- |
| INTERACT_HOOT | (1 << 0) |
| INTERACT_GRABBABLE | (1 << 1) |
| INTERACT_DOOR | (1 << 2) |
| INTERACT_DAMAGE | (1 << 3) |
| INTERACT_COIN | (1 << 4) |
| INTERACT_CAP | (1 << 5) |
| INTERACT_POLE | (1 << 6) |
| INTERACT_KOOPA | (1 << 7) |
| INTERACT_SPINY_WALKING | (1 << 8) |
| INTERACT_BREAKABLE | (1 << 9) |
| INTERACT_STRONG_WIND | (1 << 10) |
| INTERACT_WARP_DOOR | (1 << 11) |
| INTERACT_STAR_OR_KEY | (1 << 12) |
| INTERACT_WARP | (1 << 13) |
| INTERACT_CANNON_BASE | (1 << 14) |
| INTERACT_BOUNCE_TOP | (1 << 15) |
| INTERACT_WATER_RING | (1 << 16) |
| INTERACT_BULLY | (1 << 17) |
| INTERACT_FLAME | (1 << 18) |
| INTERACT_KOOPA_SHELL | (1 << 19) |
| INTERACT_BOUNCE_TOP2 | (1 << 20) |
| INTERACT_MR_BLIZZARD | (1 << 21) |
| INTERACT_HIT_FROM_BELOW | (1 << 22) |
| INTERACT_TEXT | (1 << 23) |
| INTERACT_TORNADO | (1 << 24) |
| INTERACT_WHIRLPOOL | (1 << 25) |
| INTERACT_CLAM_OR_BUBBA | (1 << 26) |
| INTERACT_BBH_ENTRANCE | (1 << 27) |
| INTERACT_SNUFIT_BULLET | (1 << 28) |
| INTERACT_SHOCK | (1 << 29) |
| INTERACT_IGLOO_BARRIER | (1 << 30) |
| INTERACT_PLAYER | (1 << 31) |

[:arrow_up_small:](#)

<br />

## [level_commands.h](#level_commands.h)
- WARP_CHECKPOINT
- WARP_NO_CHECKPOINT

[:arrow_up_small:](#)

<br />

## [level_defines.h](#level_defines.h)

### [enum LevelNum](#LevelNum)
| Identifier | Value |
| :--------- | :---- |
| LEVEL_NONE | 0 |
| LEVEL_UNKNOWN_1 | 1 |
| LEVEL_UNKNOWN_2 | 2 |
| LEVEL_UNKNOWN_3 | 3 |
| LEVEL_BBH | 4 |
| LEVEL_CCM | 5 |
| LEVEL_CASTLE | 6 |
| LEVEL_HMC | 7 |
| LEVEL_SSL | 8 |
| LEVEL_BOB | 9 |
| LEVEL_SL | 10 |
| LEVEL_WDW | 11 |
| LEVEL_JRB | 12 |
| LEVEL_THI | 13 |
| LEVEL_TTC | 14 |
| LEVEL_RR | 15 |
| LEVEL_CASTLE_GROUNDS | 16 |
| LEVEL_BITDW | 17 |
| LEVEL_VCUTM | 18 |
| LEVEL_BITFS | 19 |
| LEVEL_SA | 20 |
| LEVEL_BITS | 21 |
| LEVEL_LLL | 22 |
| LEVEL_DDD | 23 |
| LEVEL_WF | 24 |
| LEVEL_ENDING | 25 |
| LEVEL_CASTLE_COURTYARD | 26 |
| LEVEL_PSS | 27 |
| LEVEL_COTMC | 28 |
| LEVEL_TOTWC | 29 |
| LEVEL_BOWSER_1 | 30 |
| LEVEL_WMOTR | 31 |
| LEVEL_UNKNOWN_32 | 32 |
| LEVEL_BOWSER_2 | 33 |
| LEVEL_BOWSER_3 | 34 |
| LEVEL_UNKNOWN_35 | 35 |
| LEVEL_TTM | 36 |
| LEVEL_UNKNOWN_37 | 37 |
| LEVEL_UNKNOWN_38 | 38 |
| LEVEL_COUNT | 39 |

[:arrow_up_small:](#)

<br />

## [level_update.h](#level_update.h)
- MARIO_SPAWN_AIRBORNE
- MARIO_SPAWN_AIRBORNE_DEATH
- MARIO_SPAWN_AIRBORNE_STAR_COLLECT
- MARIO_SPAWN_DEATH
- MARIO_SPAWN_DOOR_WARP
- MARIO_SPAWN_FLYING
- MARIO_SPAWN_HARD_AIR_KNOCKBACK
- MARIO_SPAWN_INSTANT_ACTIVE
- MARIO_SPAWN_LAUNCH_DEATH
- MARIO_SPAWN_LAUNCH_STAR_COLLECT
- MARIO_SPAWN_PAINTING_DEATH
- MARIO_SPAWN_PAINTING_STAR_COLLECT
- MARIO_SPAWN_SPIN_AIRBORNE
- MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE
- MARIO_SPAWN_SWIMMING
- MARIO_SPAWN_TELEPORT
- MARIO_SPAWN_UNKNOWN_02
- MARIO_SPAWN_UNKNOWN_03
- MARIO_SPAWN_UNKNOWN_27
- PAINTING_WARP_INDEX_END
- PAINTING_WARP_INDEX_FA
- PAINTING_WARP_INDEX_START
- PRESS_START_DEMO_TIMER
- SPECIAL_WARP_CAKE
- SPECIAL_WARP_GODDARD
- SPECIAL_WARP_GODDARD_GAMEOVER
- SPECIAL_WARP_LEVEL_SELECT
- SPECIAL_WARP_TITLE
- TIMER_CONTROL_HIDE
- TIMER_CONTROL_SHOW
- TIMER_CONTROL_START
- TIMER_CONTROL_STOP
- WARP_NODE_CREDITS_END
- WARP_NODE_CREDITS_MIN
- WARP_NODE_CREDITS_NEXT
- WARP_NODE_CREDITS_START
- WARP_NODE_DEATH
- WARP_NODE_F0
- WARP_NODE_F2
- WARP_NODE_WARP_FLOOR
- WARP_OP_CREDITS_END
- WARP_OP_CREDITS_NEXT
- WARP_OP_CREDITS_START
- WARP_OP_DEATH
- WARP_OP_DEMO_END
- WARP_OP_DEMO_NEXT
- WARP_OP_EXIT
- WARP_OP_FORCE_SYNC
- WARP_OP_GAME_OVER
- WARP_OP_LOOK_UP
- WARP_OP_NONE
- WARP_OP_SPIN_SHRINK
- WARP_OP_STAR_EXIT
- WARP_OP_TELEPORT
- WARP_OP_TRIGGERS_LEVEL_SELECT
- WARP_OP_WARP_DOOR
- WARP_OP_WARP_FLOOR
- WARP_OP_WARP_OBJECT
- WARP_TYPE_CHANGE_AREA
- WARP_TYPE_CHANGE_LEVEL
- WARP_TYPE_NOT_WARPING
- WARP_TYPE_SAME_AREA

### [enum HUDDisplayFlag](#HUDDisplayFlag)
| Identifier | Value |
| :--------- | :---- |
| HUD_DISPLAY_FLAG_LIVES | 0x0001 |
| HUD_DISPLAY_FLAG_COIN_COUNT | 0x0002 |
| HUD_DISPLAY_FLAG_STAR_COUNT | 0x0004 |
| HUD_DISPLAY_FLAG_CAMERA_AND_POWER | 0x0008 |
| HUD_DISPLAY_FLAG_KEYS | 0x0010 |
| HUD_DISPLAY_FLAG_UNKNOWN_0020 | 0x0020 |
| HUD_DISPLAY_FLAG_TIMER | 0x0040 |
| HUD_DISPLAY_FLAG_CAMERA | 0x0080 |
| HUD_DISPLAY_FLAG_POWER | 0x0100 |
| HUD_DISPLAY_FLAG_EMPHASIZE_POWER | 0x8000 |
| HUD_DISPLAY_NONE | 0x0000 |
| HUD_DISPLAY_DEFAULT | HUD_DISPLAY_FLAG_LIVES | HUD_DISPLAY_FLAG_COIN_COUNT | HUD_DISPLAY_FLAG_STAR_COUNT | HUD_DISPLAY_FLAG_CAMERA_AND_POWER | HUD_DISPLAY_FLAG_CAMERA | HUD_DISPLAY_FLAG_POWER | HUD_DISPLAY_FLAG_KEYS | HUD_DISPLAY_FLAG_UNKNOWN_0020 |

[:arrow_up_small:](#)

<br />

## [mario_animation_ids.h](#mario_animation_ids.h)

### [enum CharacterAnimID](#CharacterAnimID)
| Identifier | Value |
| :--------- | :---- |
| CHAR_ANIM_SLOW_LEDGE_GRAB | 0 |
| CHAR_ANIM_FALL_OVER_BACKWARDS | 1 |
| CHAR_ANIM_BACKWARD_AIR_KB | 2 |
| CHAR_ANIM_DYING_ON_BACK | 3 |
| CHAR_ANIM_BACKFLIP | 4 |
| CHAR_ANIM_CLIMB_UP_POLE | 5 |
| CHAR_ANIM_GRAB_POLE_SHORT | 6 |
| CHAR_ANIM_GRAB_POLE_SWING_PART1 | 7 |
| CHAR_ANIM_GRAB_POLE_SWING_PART2 | 8 |
| CHAR_ANIM_HANDSTAND_IDLE | 9 |
| CHAR_ANIM_HANDSTAND_JUMP | 10 |
| CHAR_ANIM_START_HANDSTAND | 11 |
| CHAR_ANIM_RETURN_FROM_HANDSTAND | 12 |
| CHAR_ANIM_IDLE_ON_POLE | 13 |
| CHAR_ANIM_A_POSE | 14 |
| CHAR_ANIM_SKID_ON_GROUND | 15 |
| CHAR_ANIM_STOP_SKID | 16 |
| CHAR_ANIM_CROUCH_FROM_FAST_LONGJUMP | 17 |
| CHAR_ANIM_CROUCH_FROM_SLOW_LONGJUMP | 18 |
| CHAR_ANIM_FAST_LONGJUMP | 19 |
| CHAR_ANIM_SLOW_LONGJUMP | 20 |
| CHAR_ANIM_AIRBORNE_ON_STOMACH | 21 |
| CHAR_ANIM_WALK_WITH_LIGHT_OBJ | 22 |
| CHAR_ANIM_RUN_WITH_LIGHT_OBJ | 23 |
| CHAR_ANIM_SLOW_WALK_WITH_LIGHT_OBJ | 24 |
| CHAR_ANIM_SHIVERING_WARMING_HAND | 25 |
| CHAR_ANIM_SHIVERING_RETURN_TO_IDLE | 26 |
| CHAR_ANIM_SHIVERING | 27 |
| CHAR_ANIM_CLIMB_DOWN_LEDGE | 28 |
| CHAR_ANIM_CREDITS_WAVING | 29 |
| CHAR_ANIM_CREDITS_LOOK_UP | 30 |
| CHAR_ANIM_CREDITS_RETURN_FROM_LOOK_UP | 31 |
| CHAR_ANIM_CREDITS_RAISE_HAND | 32 |
| CHAR_ANIM_CREDITS_LOWER_HAND | 33 |
| CHAR_ANIM_CREDITS_TAKE_OFF_CAP | 34 |
| CHAR_ANIM_CREDITS_START_WALK_LOOK_UP | 35 |
| CHAR_ANIM_CREDITS_LOOK_BACK_THEN_RUN | 36 |
| CHAR_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN | 37 |
| CHAR_ANIM_FINAL_BOWSER_WING_CAP_TAKE_OFF | 38 |
| CHAR_ANIM_CREDITS_PEACE_SIGN | 39 |
| CHAR_ANIM_STAND_UP_FROM_LAVA_BOOST | 40 |
| CHAR_ANIM_FIRE_LAVA_BURN | 41 |
| CHAR_ANIM_WING_CAP_FLY | 42 |
| CHAR_ANIM_HANG_ON_OWL | 43 |
| CHAR_ANIM_LAND_ON_STOMACH | 44 |
| CHAR_ANIM_AIR_FORWARD_KB | 45 |
| CHAR_ANIM_DYING_ON_STOMACH | 46 |
| CHAR_ANIM_SUFFOCATING | 47 |
| CHAR_ANIM_COUGHING | 48 |
| CHAR_ANIM_THROW_CATCH_KEY | 49 |
| CHAR_ANIM_DYING_FALL_OVER | 50 |
| CHAR_ANIM_IDLE_ON_LEDGE | 51 |
| CHAR_ANIM_FAST_LEDGE_GRAB | 52 |
| CHAR_ANIM_HANG_ON_CEILING | 53 |
| CHAR_ANIM_PUT_CAP_ON | 54 |
| CHAR_ANIM_TAKE_CAP_OFF_THEN_ON | 55 |
| CHAR_ANIM_QUICKLY_PUT_CAP_ON | 56 |
| CHAR_ANIM_HEAD_STUCK_IN_GROUND | 57 |
| CHAR_ANIM_GROUND_POUND_LANDING | 58 |
| CHAR_ANIM_TRIPLE_JUMP_GROUND_POUND | 59 |
| CHAR_ANIM_START_GROUND_POUND | 60 |
| CHAR_ANIM_GROUND_POUND | 61 |
| CHAR_ANIM_BOTTOM_STUCK_IN_GROUND | 62 |
| CHAR_ANIM_IDLE_WITH_LIGHT_OBJ | 63 |
| CHAR_ANIM_JUMP_LAND_WITH_LIGHT_OBJ | 64 |
| CHAR_ANIM_JUMP_WITH_LIGHT_OBJ | 65 |
| CHAR_ANIM_FALL_LAND_WITH_LIGHT_OBJ | 66 |
| CHAR_ANIM_FALL_WITH_LIGHT_OBJ | 67 |
| CHAR_ANIM_FALL_FROM_SLIDING_WITH_LIGHT_OBJ | 68 |
| CHAR_ANIM_SLIDING_ON_BOTTOM_WITH_LIGHT_OBJ | 69 |
| CHAR_ANIM_STAND_UP_FROM_SLIDING_WITH_LIGHT_OBJ | 70 |
| CHAR_ANIM_RIDING_SHELL | 71 |
| CHAR_ANIM_WALKING | 72 |
| CHAR_ANIM_FORWARD_FLIP | 73 |
| CHAR_ANIM_JUMP_RIDING_SHELL | 74 |
| CHAR_ANIM_LAND_FROM_DOUBLE_JUMP | 75 |
| CHAR_ANIM_DOUBLE_JUMP_FALL | 76 |
| CHAR_ANIM_SINGLE_JUMP | 77 |
| CHAR_ANIM_LAND_FROM_SINGLE_JUMP | 78 |
| CHAR_ANIM_AIR_KICK | 79 |
| CHAR_ANIM_DOUBLE_JUMP_RISE | 80 |
| CHAR_ANIM_START_FORWARD_SPINNING | 81 |
| CHAR_ANIM_THROW_LIGHT_OBJECT | 82 |
| CHAR_ANIM_FALL_FROM_SLIDE_KICK | 83 |
| CHAR_ANIM_BEND_KNESS_RIDING_SHELL | 84 |
| CHAR_ANIM_LEGS_STUCK_IN_GROUND | 85 |
| CHAR_ANIM_GENERAL_FALL | 86 |
| CHAR_ANIM_GENERAL_LAND | 87 |
| CHAR_ANIM_BEING_GRABBED | 88 |
| CHAR_ANIM_GRAB_HEAVY_OBJECT | 89 |
| CHAR_ANIM_SLOW_LAND_FROM_DIVE | 90 |
| CHAR_ANIM_FLY_FROM_CANNON | 91 |
| CHAR_ANIM_MOVE_ON_WIRE_NET_RIGHT | 92 |
| CHAR_ANIM_MOVE_ON_WIRE_NET_LEFT | 93 |
| CHAR_ANIM_MISSING_CAP | 94 |
| CHAR_ANIM_PULL_DOOR_WALK_IN | 95 |
| CHAR_ANIM_PUSH_DOOR_WALK_IN | 96 |
| CHAR_ANIM_UNLOCK_DOOR | 97 |
| CHAR_ANIM_START_REACH_POCKET | 98 |
| CHAR_ANIM_REACH_POCKET | 99 |
| CHAR_ANIM_STOP_REACH_POCKET | 100 |
| CHAR_ANIM_GROUND_THROW | 101 |
| CHAR_ANIM_GROUND_KICK | 102 |
| CHAR_ANIM_FIRST_PUNCH | 103 |
| CHAR_ANIM_SECOND_PUNCH | 104 |
| CHAR_ANIM_FIRST_PUNCH_FAST | 105 |
| CHAR_ANIM_SECOND_PUNCH_FAST | 106 |
| CHAR_ANIM_PICK_UP_LIGHT_OBJ | 107 |
| CHAR_ANIM_PUSHING | 108 |
| CHAR_ANIM_START_RIDING_SHELL | 109 |
| CHAR_ANIM_PLACE_LIGHT_OBJ | 110 |
| CHAR_ANIM_FORWARD_SPINNING | 111 |
| CHAR_ANIM_BACKWARD_SPINNING | 112 |
| CHAR_ANIM_BREAKDANCE | 113 |
| CHAR_ANIM_RUNNING | 114 |
| CHAR_ANIM_RUNNING_UNUSED | 115 |
| CHAR_ANIM_SOFT_BACK_KB | 116 |
| CHAR_ANIM_SOFT_FRONT_KB | 117 |
| CHAR_ANIM_DYING_IN_QUICKSAND | 118 |
| CHAR_ANIM_IDLE_IN_QUICKSAND | 119 |
| CHAR_ANIM_MOVE_IN_QUICKSAND | 120 |
| CHAR_ANIM_ELECTROCUTION | 121 |
| CHAR_ANIM_SHOCKED | 122 |
| CHAR_ANIM_BACKWARD_KB | 123 |
| CHAR_ANIM_FORWARD_KB | 124 |
| CHAR_ANIM_IDLE_HEAVY_OBJ | 125 |
| CHAR_ANIM_STAND_AGAINST_WALL | 126 |
| CHAR_ANIM_SIDESTEP_LEFT | 127 |
| CHAR_ANIM_SIDESTEP_RIGHT | 128 |
| CHAR_ANIM_START_SLEEP_IDLE | 129 |
| CHAR_ANIM_START_SLEEP_SCRATCH | 130 |
| CHAR_ANIM_START_SLEEP_YAWN | 131 |
| CHAR_ANIM_START_SLEEP_SITTING | 132 |
| CHAR_ANIM_SLEEP_IDLE | 133 |
| CHAR_ANIM_SLEEP_START_LYING | 134 |
| CHAR_ANIM_SLEEP_LYING | 135 |
| CHAR_ANIM_DIVE | 136 |
| CHAR_ANIM_SLIDE_DIVE | 137 |
| CHAR_ANIM_GROUND_BONK | 138 |
| CHAR_ANIM_STOP_SLIDE_LIGHT_OBJ | 139 |
| CHAR_ANIM_SLIDE_KICK | 140 |
| CHAR_ANIM_CROUCH_FROM_SLIDE_KICK | 141 |
| CHAR_ANIM_SLIDE_MOTIONLESS | 142 |
| CHAR_ANIM_STOP_SLIDE | 143 |
| CHAR_ANIM_FALL_FROM_SLIDE | 144 |
| CHAR_ANIM_SLIDE | 145 |
| CHAR_ANIM_TIPTOE | 146 |
| CHAR_ANIM_TWIRL_LAND | 147 |
| CHAR_ANIM_TWIRL | 148 |
| CHAR_ANIM_START_TWIRL | 149 |
| CHAR_ANIM_STOP_CROUCHING | 150 |
| CHAR_ANIM_START_CROUCHING | 151 |
| CHAR_ANIM_CROUCHING | 152 |
| CHAR_ANIM_CRAWLING | 153 |
| CHAR_ANIM_STOP_CRAWLING | 154 |
| CHAR_ANIM_START_CRAWLING | 155 |
| CHAR_ANIM_SUMMON_STAR | 156 |
| CHAR_ANIM_RETURN_STAR_APPROACH_DOOR | 157 |
| CHAR_ANIM_BACKWARDS_WATER_KB | 158 |
| CHAR_ANIM_SWIM_WITH_OBJ_PART1 | 159 |
| CHAR_ANIM_SWIM_WITH_OBJ_PART2 | 160 |
| CHAR_ANIM_FLUTTERKICK_WITH_OBJ | 161 |
| CHAR_ANIM_WATER_ACTION_END_WITH_OBJ | 162 |
| CHAR_ANIM_STOP_GRAB_OBJ_WATER | 163 |
| CHAR_ANIM_WATER_IDLE_WITH_OBJ | 164 |
| CHAR_ANIM_DROWNING_PART1 | 165 |
| CHAR_ANIM_DROWNING_PART2 | 166 |
| CHAR_ANIM_WATER_DYING | 167 |
| CHAR_ANIM_WATER_FORWARD_KB | 168 |
| CHAR_ANIM_FALL_FROM_WATER | 169 |
| CHAR_ANIM_SWIM_PART1 | 170 |
| CHAR_ANIM_SWIM_PART2 | 171 |
| CHAR_ANIM_FLUTTERKICK | 172 |
| CHAR_ANIM_WATER_ACTION_END | 173 |
| CHAR_ANIM_WATER_PICK_UP_OBJ | 174 |
| CHAR_ANIM_WATER_GRAB_OBJ_PART2 | 175 |
| CHAR_ANIM_WATER_GRAB_OBJ_PART1 | 176 |
| CHAR_ANIM_WATER_THROW_OBJ | 177 |
| CHAR_ANIM_WATER_IDLE | 178 |
| CHAR_ANIM_WATER_STAR_DANCE | 179 |
| CHAR_ANIM_RETURN_FROM_WATER_STAR_DANCE | 180 |
| CHAR_ANIM_GRAB_BOWSER | 181 |
| CHAR_ANIM_SWINGING_BOWSER | 182 |
| CHAR_ANIM_RELEASE_BOWSER | 183 |
| CHAR_ANIM_HOLDING_BOWSER | 184 |
| CHAR_ANIM_HEAVY_THROW | 185 |
| CHAR_ANIM_WALK_PANTING | 186 |
| CHAR_ANIM_WALK_WITH_HEAVY_OBJ | 187 |
| CHAR_ANIM_TURNING_PART1 | 188 |
| CHAR_ANIM_TURNING_PART2 | 189 |
| CHAR_ANIM_SLIDEFLIP_LAND | 190 |
| CHAR_ANIM_SLIDEFLIP | 191 |
| CHAR_ANIM_TRIPLE_JUMP_LAND | 192 |
| CHAR_ANIM_TRIPLE_JUMP | 193 |
| CHAR_ANIM_FIRST_PERSON | 194 |
| CHAR_ANIM_IDLE_HEAD_LEFT | 195 |
| CHAR_ANIM_IDLE_HEAD_RIGHT | 196 |
| CHAR_ANIM_IDLE_HEAD_CENTER | 197 |
| CHAR_ANIM_HANDSTAND_LEFT | 198 |
| CHAR_ANIM_HANDSTAND_RIGHT | 199 |
| CHAR_ANIM_WAKE_FROM_SLEEP | 200 |
| CHAR_ANIM_WAKE_FROM_LYING | 201 |
| CHAR_ANIM_START_TIPTOE | 202 |
| CHAR_ANIM_SLIDEJUMP | 203 |
| CHAR_ANIM_START_WALLKICK | 204 |
| CHAR_ANIM_STAR_DANCE | 205 |
| CHAR_ANIM_RETURN_FROM_STAR_DANCE | 206 |
| CHAR_ANIM_FORWARD_SPINNING_FLIP | 207 |
| CHAR_ANIM_TRIPLE_JUMP_FLY | 208 |
| CHAR_ANIM_MAX | 209 |

### [enum MarioAnimID](#MarioAnimID)
| Identifier | Value |
| :--------- | :---- |
| MARIO_ANIM_SLOW_LEDGE_GRAB | 0 |
| MARIO_ANIM_FALL_OVER_BACKWARDS | 1 |
| MARIO_ANIM_BACKWARD_AIR_KB | 2 |
| MARIO_ANIM_DYING_ON_BACK | 3 |
| MARIO_ANIM_BACKFLIP | 4 |
| MARIO_ANIM_CLIMB_UP_POLE | 5 |
| MARIO_ANIM_GRAB_POLE_SHORT | 6 |
| MARIO_ANIM_GRAB_POLE_SWING_PART1 | 7 |
| MARIO_ANIM_GRAB_POLE_SWING_PART2 | 8 |
| MARIO_ANIM_HANDSTAND_IDLE | 9 |
| MARIO_ANIM_HANDSTAND_JUMP | 10 |
| MARIO_ANIM_START_HANDSTAND | 11 |
| MARIO_ANIM_RETURN_FROM_HANDSTAND | 12 |
| MARIO_ANIM_IDLE_ON_POLE | 13 |
| MARIO_ANIM_A_POSE | 14 |
| MARIO_ANIM_SKID_ON_GROUND | 15 |
| MARIO_ANIM_STOP_SKID | 16 |
| MARIO_ANIM_CROUCH_FROM_FAST_LONGJUMP | 17 |
| MARIO_ANIM_CROUCH_FROM_SLOW_LONGJUMP | 18 |
| MARIO_ANIM_FAST_LONGJUMP | 19 |
| MARIO_ANIM_SLOW_LONGJUMP | 20 |
| MARIO_ANIM_AIRBORNE_ON_STOMACH | 21 |
| MARIO_ANIM_WALK_WITH_LIGHT_OBJ | 22 |
| MARIO_ANIM_RUN_WITH_LIGHT_OBJ | 23 |
| MARIO_ANIM_SLOW_WALK_WITH_LIGHT_OBJ | 24 |
| MARIO_ANIM_SHIVERING_WARMING_HAND | 25 |
| MARIO_ANIM_SHIVERING_RETURN_TO_IDLE | 26 |
| MARIO_ANIM_SHIVERING | 27 |
| MARIO_ANIM_CLIMB_DOWN_LEDGE | 28 |
| MARIO_ANIM_CREDITS_WAVING | 29 |
| MARIO_ANIM_CREDITS_LOOK_UP | 30 |
| MARIO_ANIM_CREDITS_RETURN_FROM_LOOK_UP | 31 |
| MARIO_ANIM_CREDITS_RAISE_HAND | 32 |
| MARIO_ANIM_CREDITS_LOWER_HAND | 33 |
| MARIO_ANIM_CREDITS_TAKE_OFF_CAP | 34 |
| MARIO_ANIM_CREDITS_START_WALK_LOOK_UP | 35 |
| MARIO_ANIM_CREDITS_LOOK_BACK_THEN_RUN | 36 |
| MARIO_ANIM_FINAL_BOWSER_RAISE_HAND_SPIN | 37 |
| MARIO_ANIM_FINAL_BOWSER_WING_CAP_TAKE_OFF | 38 |
| MARIO_ANIM_CREDITS_PEACE_SIGN | 39 |
| MARIO_ANIM_STAND_UP_FROM_LAVA_BOOST | 40 |
| MARIO_ANIM_FIRE_LAVA_BURN | 41 |
| MARIO_ANIM_WING_CAP_FLY | 42 |
| MARIO_ANIM_HANG_ON_OWL | 43 |
| MARIO_ANIM_LAND_ON_STOMACH | 44 |
| MARIO_ANIM_AIR_FORWARD_KB | 45 |
| MARIO_ANIM_DYING_ON_STOMACH | 46 |
| MARIO_ANIM_SUFFOCATING | 47 |
| MARIO_ANIM_COUGHING | 48 |
| MARIO_ANIM_THROW_CATCH_KEY | 49 |
| MARIO_ANIM_DYING_FALL_OVER | 50 |
| MARIO_ANIM_IDLE_ON_LEDGE | 51 |
| MARIO_ANIM_FAST_LEDGE_GRAB | 52 |
| MARIO_ANIM_HANG_ON_CEILING | 53 |
| MARIO_ANIM_PUT_CAP_ON | 54 |
| MARIO_ANIM_TAKE_CAP_OFF_THEN_ON | 55 |
| MARIO_ANIM_QUICKLY_PUT_CAP_ON | 56 |
| MARIO_ANIM_HEAD_STUCK_IN_GROUND | 57 |
| MARIO_ANIM_GROUND_POUND_LANDING | 58 |
| MARIO_ANIM_TRIPLE_JUMP_GROUND_POUND | 59 |
| MARIO_ANIM_START_GROUND_POUND | 60 |
| MARIO_ANIM_GROUND_POUND | 61 |
| MARIO_ANIM_BOTTOM_STUCK_IN_GROUND | 62 |
| MARIO_ANIM_IDLE_WITH_LIGHT_OBJ | 63 |
| MARIO_ANIM_JUMP_LAND_WITH_LIGHT_OBJ | 64 |
| MARIO_ANIM_JUMP_WITH_LIGHT_OBJ | 65 |
| MARIO_ANIM_FALL_LAND_WITH_LIGHT_OBJ | 66 |
| MARIO_ANIM_FALL_WITH_LIGHT_OBJ | 67 |
| MARIO_ANIM_FALL_FROM_SLIDING_WITH_LIGHT_OBJ | 68 |
| MARIO_ANIM_SLIDING_ON_BOTTOM_WITH_LIGHT_OBJ | 69 |
| MARIO_ANIM_STAND_UP_FROM_SLIDING_WITH_LIGHT_OBJ | 70 |
| MARIO_ANIM_RIDING_SHELL | 71 |
| MARIO_ANIM_WALKING | 72 |
| MARIO_ANIM_FORWARD_FLIP | 73 |
| MARIO_ANIM_JUMP_RIDING_SHELL | 74 |
| MARIO_ANIM_LAND_FROM_DOUBLE_JUMP | 75 |
| MARIO_ANIM_DOUBLE_JUMP_FALL | 76 |
| MARIO_ANIM_SINGLE_JUMP | 77 |
| MARIO_ANIM_LAND_FROM_SINGLE_JUMP | 78 |
| MARIO_ANIM_AIR_KICK | 79 |
| MARIO_ANIM_DOUBLE_JUMP_RISE | 80 |
| MARIO_ANIM_START_FORWARD_SPINNING | 81 |
| MARIO_ANIM_THROW_LIGHT_OBJECT | 82 |
| MARIO_ANIM_FALL_FROM_SLIDE_KICK | 83 |
| MARIO_ANIM_BEND_KNESS_RIDING_SHELL | 84 |
| MARIO_ANIM_LEGS_STUCK_IN_GROUND | 85 |
| MARIO_ANIM_GENERAL_FALL | 86 |
| MARIO_ANIM_GENERAL_LAND | 87 |
| MARIO_ANIM_BEING_GRABBED | 88 |
| MARIO_ANIM_GRAB_HEAVY_OBJECT | 89 |
| MARIO_ANIM_SLOW_LAND_FROM_DIVE | 90 |
| MARIO_ANIM_FLY_FROM_CANNON | 91 |
| MARIO_ANIM_MOVE_ON_WIRE_NET_RIGHT | 92 |
| MARIO_ANIM_MOVE_ON_WIRE_NET_LEFT | 93 |
| MARIO_ANIM_MISSING_CAP | 94 |
| MARIO_ANIM_PULL_DOOR_WALK_IN | 95 |
| MARIO_ANIM_PUSH_DOOR_WALK_IN | 96 |
| MARIO_ANIM_UNLOCK_DOOR | 97 |
| MARIO_ANIM_START_REACH_POCKET | 98 |
| MARIO_ANIM_REACH_POCKET | 99 |
| MARIO_ANIM_STOP_REACH_POCKET | 100 |
| MARIO_ANIM_GROUND_THROW | 101 |
| MARIO_ANIM_GROUND_KICK | 102 |
| MARIO_ANIM_FIRST_PUNCH | 103 |
| MARIO_ANIM_SECOND_PUNCH | 104 |
| MARIO_ANIM_FIRST_PUNCH_FAST | 105 |
| MARIO_ANIM_SECOND_PUNCH_FAST | 106 |
| MARIO_ANIM_PICK_UP_LIGHT_OBJ | 107 |
| MARIO_ANIM_PUSHING | 108 |
| MARIO_ANIM_START_RIDING_SHELL | 109 |
| MARIO_ANIM_PLACE_LIGHT_OBJ | 110 |
| MARIO_ANIM_FORWARD_SPINNING | 111 |
| MARIO_ANIM_BACKWARD_SPINNING | 112 |
| MARIO_ANIM_BREAKDANCE | 113 |
| MARIO_ANIM_RUNNING | 114 |
| MARIO_ANIM_RUNNING_UNUSED | 115 |
| MARIO_ANIM_SOFT_BACK_KB | 116 |
| MARIO_ANIM_SOFT_FRONT_KB | 117 |
| MARIO_ANIM_DYING_IN_QUICKSAND | 118 |
| MARIO_ANIM_IDLE_IN_QUICKSAND | 119 |
| MARIO_ANIM_MOVE_IN_QUICKSAND | 120 |
| MARIO_ANIM_ELECTROCUTION | 121 |
| MARIO_ANIM_SHOCKED | 122 |
| MARIO_ANIM_BACKWARD_KB | 123 |
| MARIO_ANIM_FORWARD_KB | 124 |
| MARIO_ANIM_IDLE_HEAVY_OBJ | 125 |
| MARIO_ANIM_STAND_AGAINST_WALL | 126 |
| MARIO_ANIM_SIDESTEP_LEFT | 127 |
| MARIO_ANIM_SIDESTEP_RIGHT | 128 |
| MARIO_ANIM_START_SLEEP_IDLE | 129 |
| MARIO_ANIM_START_SLEEP_SCRATCH | 130 |
| MARIO_ANIM_START_SLEEP_YAWN | 131 |
| MARIO_ANIM_START_SLEEP_SITTING | 132 |
| MARIO_ANIM_SLEEP_IDLE | 133 |
| MARIO_ANIM_SLEEP_START_LYING | 134 |
| MARIO_ANIM_SLEEP_LYING | 135 |
| MARIO_ANIM_DIVE | 136 |
| MARIO_ANIM_SLIDE_DIVE | 137 |
| MARIO_ANIM_GROUND_BONK | 138 |
| MARIO_ANIM_STOP_SLIDE_LIGHT_OBJ | 139 |
| MARIO_ANIM_SLIDE_KICK | 140 |
| MARIO_ANIM_CROUCH_FROM_SLIDE_KICK | 141 |
| MARIO_ANIM_SLIDE_MOTIONLESS | 142 |
| MARIO_ANIM_STOP_SLIDE | 143 |
| MARIO_ANIM_FALL_FROM_SLIDE | 144 |
| MARIO_ANIM_SLIDE | 145 |
| MARIO_ANIM_TIPTOE | 146 |
| MARIO_ANIM_TWIRL_LAND | 147 |
| MARIO_ANIM_TWIRL | 148 |
| MARIO_ANIM_START_TWIRL | 149 |
| MARIO_ANIM_STOP_CROUCHING | 150 |
| MARIO_ANIM_START_CROUCHING | 151 |
| MARIO_ANIM_CROUCHING | 152 |
| MARIO_ANIM_CRAWLING | 153 |
| MARIO_ANIM_STOP_CRAWLING | 154 |
| MARIO_ANIM_START_CRAWLING | 155 |
| MARIO_ANIM_SUMMON_STAR | 156 |
| MARIO_ANIM_RETURN_STAR_APPROACH_DOOR | 157 |
| MARIO_ANIM_BACKWARDS_WATER_KB | 158 |
| MARIO_ANIM_SWIM_WITH_OBJ_PART1 | 159 |
| MARIO_ANIM_SWIM_WITH_OBJ_PART2 | 160 |
| MARIO_ANIM_FLUTTERKICK_WITH_OBJ | 161 |
| MARIO_ANIM_WATER_ACTION_END_WITH_OBJ | 162 |
| MARIO_ANIM_STOP_GRAB_OBJ_WATER | 163 |
| MARIO_ANIM_WATER_IDLE_WITH_OBJ | 164 |
| MARIO_ANIM_DROWNING_PART1 | 165 |
| MARIO_ANIM_DROWNING_PART2 | 166 |
| MARIO_ANIM_WATER_DYING | 167 |
| MARIO_ANIM_WATER_FORWARD_KB | 168 |
| MARIO_ANIM_FALL_FROM_WATER | 169 |
| MARIO_ANIM_SWIM_PART1 | 170 |
| MARIO_ANIM_SWIM_PART2 | 171 |
| MARIO_ANIM_FLUTTERKICK | 172 |
| MARIO_ANIM_WATER_ACTION_END | 173 |
| MARIO_ANIM_WATER_PICK_UP_OBJ | 174 |
| MARIO_ANIM_WATER_GRAB_OBJ_PART2 | 175 |
| MARIO_ANIM_WATER_GRAB_OBJ_PART1 | 176 |
| MARIO_ANIM_WATER_THROW_OBJ | 177 |
| MARIO_ANIM_WATER_IDLE | 178 |
| MARIO_ANIM_WATER_STAR_DANCE | 179 |
| MARIO_ANIM_RETURN_FROM_WATER_STAR_DANCE | 180 |
| MARIO_ANIM_GRAB_BOWSER | 181 |
| MARIO_ANIM_SWINGING_BOWSER | 182 |
| MARIO_ANIM_RELEASE_BOWSER | 183 |
| MARIO_ANIM_HOLDING_BOWSER | 184 |
| MARIO_ANIM_HEAVY_THROW | 185 |
| MARIO_ANIM_WALK_PANTING | 186 |
| MARIO_ANIM_WALK_WITH_HEAVY_OBJ | 187 |
| MARIO_ANIM_TURNING_PART1 | 188 |
| MARIO_ANIM_TURNING_PART2 | 189 |
| MARIO_ANIM_SLIDEFLIP_LAND | 190 |
| MARIO_ANIM_SLIDEFLIP | 191 |
| MARIO_ANIM_TRIPLE_JUMP_LAND | 192 |
| MARIO_ANIM_TRIPLE_JUMP | 193 |
| MARIO_ANIM_FIRST_PERSON | 194 |
| MARIO_ANIM_IDLE_HEAD_LEFT | 195 |
| MARIO_ANIM_IDLE_HEAD_RIGHT | 196 |
| MARIO_ANIM_IDLE_HEAD_CENTER | 197 |
| MARIO_ANIM_HANDSTAND_LEFT | 198 |
| MARIO_ANIM_HANDSTAND_RIGHT | 199 |
| MARIO_ANIM_WAKE_FROM_SLEEP | 200 |
| MARIO_ANIM_WAKE_FROM_LYING | 201 |
| MARIO_ANIM_START_TIPTOE | 202 |
| MARIO_ANIM_SLIDEJUMP | 203 |
| MARIO_ANIM_START_WALLKICK | 204 |
| MARIO_ANIM_STAR_DANCE | 205 |
| MARIO_ANIM_RETURN_FROM_STAR_DANCE | 206 |
| MARIO_ANIM_FORWARD_SPINNING_FLIP | 207 |
| MARIO_ANIM_TRIPLE_JUMP_FLY | 208 |

[:arrow_up_small:](#)

<br />

## [mario_geo_switch_case_ids.h](#mario_geo_switch_case_ids.h)

### [enum MarioCapGSCId](#MarioCapGSCId)
| Identifier | Value |
| :--------- | :---- |
| MARIO_HAS_DEFAULT_CAP_ON | 0 |
| MARIO_HAS_DEFAULT_CAP_OFF | 1 |
| MARIO_HAS_WING_CAP_ON | 2 |
| MARIO_HAS_WING_CAP_OFF | 3 |

### [enum MarioEyesGSCId](#MarioEyesGSCId)
| Identifier | Value |
| :--------- | :---- |
| MARIO_EYES_BLINK | 0 |
| MARIO_EYES_OPEN | 1 |
| MARIO_EYES_HALF_CLOSED | 2 |
| MARIO_EYES_CLOSED | 3 |
| MARIO_EYES_LOOK_LEFT | 4 |
| MARIO_EYES_LOOK_RIGHT | 5 |
| MARIO_EYES_LOOK_UP | 6 |
| MARIO_EYES_LOOK_DOWN | 7 |
| MARIO_EYES_DEAD | 8 |

### [enum MarioGrabPosGSCId](#MarioGrabPosGSCId)
| Identifier | Value |
| :--------- | :---- |
| GRAB_POS_NULL | 0 |
| GRAB_POS_LIGHT_OBJ | 1 |
| GRAB_POS_HEAVY_OBJ | 2 |
| GRAB_POS_BOWSER | 3 |

### [enum MarioHandGSCId](#MarioHandGSCId)
| Identifier | Value |
| :--------- | :---- |
| MARIO_HAND_FISTS | 0 |
| MARIO_HAND_OPEN | 1 |
| MARIO_HAND_PEACE_SIGN | 2 |
| MARIO_HAND_HOLDING_CAP | 3 |
| MARIO_HAND_HOLDING_WING_CAP | 4 |
| MARIO_HAND_RIGHT_OPEN | 5 |

[:arrow_up_small:](#)

<br />

## [mod_storage.h](#mod_storage.h)
- MAX_KEYS
- MAX_KEY_VALUE_LENGTH

[:arrow_up_small:](#)

<br />

## [network.h](#network.h)
- PACKET_LENGTH
- SYNC_DISTANCE_INFINITE
- SYNC_DISTANCE_ONLY_DEATH
- SYNC_DISTANCE_ONLY_EVENTS

### [enum BouncyLevelBounds](#BouncyLevelBounds)
| Identifier | Value |
| :--------- | :---- |
| BOUNCY_LEVEL_BOUNDS_OFF | 0 |
| BOUNCY_LEVEL_BOUNDS_ON | 1 |
| BOUNCY_LEVEL_BOUNDS_ON_CAP | 2 |

### [enum NetworkSystemType](#NetworkSystemType)
| Identifier | Value |
| :--------- | :---- |
| NS_SOCKET | 0 |
| NS_COOPNET | 1 |
| NS_MAX | 2 |

### [enum PlayerInteractions](#PlayerInteractions)
| Identifier | Value |
| :--------- | :---- |
| PLAYER_INTERACTIONS_NONE | 0 |
| PLAYER_INTERACTIONS_SOLID | 1 |
| PLAYER_INTERACTIONS_PVP | 2 |

[:arrow_up_small:](#)

<br />

## [network_player.h](#network_player.h)
- MAX_DESCRIPTION_STRING
- MAX_RX_SEQ_IDS
- NETWORK_PLAYER_PING_TIMEOUT
- NETWORK_PLAYER_TIMEOUT
- UNKNOWN_GLOBAL_INDEX
- UNKNOWN_LOCAL_INDEX
- UNKNOWN_NETWORK_INDEX
- USE_REAL_PALETTE_VAR

### [enum NetworkPlayerType](#NetworkPlayerType)
| Identifier | Value |
| :--------- | :---- |
| NPT_UNKNOWN | 0 |
| NPT_LOCAL | 1 |
| NPT_SERVER | 2 |
| NPT_CLIENT | 3 |

[:arrow_up_small:](#)

<br />

## [obj_behaviors.c](#obj_behaviors.c)
- OBJ_COL_FLAGS_LANDED
- OBJ_COL_FLAG_GROUNDED
- OBJ_COL_FLAG_HIT_WALL
- OBJ_COL_FLAG_NO_Y_VEL
- OBJ_COL_FLAG_UNDERWATER

[:arrow_up_small:](#)

<br />

## [obj_behaviors_2.h](#obj_behaviors_2.h)
- ATTACK_HANDLER_DIE_IF_HEALTH_NON_POSITIVE
- ATTACK_HANDLER_KNOCKBACK
- ATTACK_HANDLER_NOP
- ATTACK_HANDLER_SET_SPEED_TO_ZERO
- ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED
- ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL
- ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON
- ATTACK_HANDLER_SQUISHED
- ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN

[:arrow_up_small:](#)

<br />

## [object_constants.h](#object_constants.h)
- ACTIVATED_BF_PLAT_TYPE_BITFS_ELEVATOR
- ACTIVATED_BF_PLAT_TYPE_BITFS_MESH_PLAT
- ACTIVATED_BF_PLAT_TYPE_BITS_ARROW_PLAT
- ACTIVE_FLAG_ACTIVE
- ACTIVE_FLAG_DEACTIVATED
- ACTIVE_FLAG_DITHERED_ALPHA
- ACTIVE_FLAG_DORMANT
- ACTIVE_FLAG_FAR_AWAY
- ACTIVE_FLAG_INITIATED_TIME_STOP
- ACTIVE_FLAG_IN_DIFFERENT_ROOM
- ACTIVE_FLAG_MOVE_THROUGH_GRATE
- ACTIVE_FLAG_UNIMPORTANT
- ACTIVE_FLAG_UNK10
- ACTIVE_FLAG_UNK2
- ACTIVE_FLAG_UNK8
- ACTIVE_FLAG_UNK9
- ACTIVE_PARTICLE_BREATH
- ACTIVE_PARTICLE_BUBBLE
- ACTIVE_PARTICLE_DIRT
- ACTIVE_PARTICLE_DUST
- ACTIVE_PARTICLE_FIRE
- ACTIVE_PARTICLE_H_STAR
- ACTIVE_PARTICLE_IDLE_WATER_WAVE
- ACTIVE_PARTICLE_LEAF
- ACTIVE_PARTICLE_MIST_CIRCLE
- ACTIVE_PARTICLE_PLUNGE_BUBBLE
- ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH
- ACTIVE_PARTICLE_SHALLOW_WATER_WAVE
- ACTIVE_PARTICLE_SNOW
- ACTIVE_PARTICLE_SPARKLES
- ACTIVE_PARTICLE_TRIANGLE
- ACTIVE_PARTICLE_UNUSED_1
- ACTIVE_PARTICLE_UNUSED_2
- ACTIVE_PARTICLE_V_STAR
- ACTIVE_PARTICLE_WATER_SPLASH
- ACTIVE_PARTICLE_WAVE_TRAIL
- AMP_ACT_ATTACK_COOLDOWN
- AMP_ACT_IDLE
- AMP_BP_ROT_RADIUS_0
- AMP_BP_ROT_RADIUS_200
- AMP_BP_ROT_RADIUS_300
- AMP_BP_ROT_RADIUS_400
- ARROW_LIFT_ACT_IDLE
- ARROW_LIFT_ACT_MOVING_AWAY
- ARROW_LIFT_ACT_MOVING_BACK
- ARROW_LIFT_DONE_MOVING
- ARROW_LIFT_NOT_DONE_MOVING
- BBALL_ACT_INITIALIZE
- BBALL_ACT_ROLL
- BBALL_BP_STYPE_BOB_LOWER
- BBALL_BP_STYPE_BOB_UPPER
- BBALL_BP_STYPE_THI_LARGE
- BBALL_BP_STYPE_THI_SMALL
- BBALL_BP_STYPE_TTM
- BBH_DYNAMIC_SURFACE_ROOM
- BBH_NEAR_MERRY_GO_ROUND_ROOM
- BBH_OUTSIDE_ROOM
- BBH_TILTING_TRAP_PLATFORM_ACT_MARIO_OFF
- BBH_TILTING_TRAP_PLATFORM_ACT_MARIO_ON
- BETA_BOO_KEY_ACT_DROPPED
- BETA_BOO_KEY_ACT_DROPPING
- BETA_BOO_KEY_ACT_IN_BOO
- BETA_CHEST_ACT_IDLE_CLOSED
- BETA_CHEST_ACT_IDLE_OPEN
- BETA_CHEST_ACT_OPENING
- BIRD_ACT_FLY
- BIRD_ACT_INACTIVE
- BIRD_BP_SPAWNED
- BIRD_BP_SPAWNER
- BLUE_COIN_SWITCH_ACT_IDLE
- BLUE_COIN_SWITCH_ACT_RECEDING
- BLUE_COIN_SWITCH_ACT_RESPAWNING
- BLUE_COIN_SWITCH_ACT_TICKING
- BLUE_FISH_ACT_ASCEND
- BLUE_FISH_ACT_DIVE
- BLUE_FISH_ACT_DUPLICATE
- BLUE_FISH_ACT_ROOM
- BLUE_FISH_ACT_SPAWN
- BLUE_FISH_ACT_TURN
- BLUE_FISH_ACT_TURN_BACK
- BOBOMB_ACT_CHASE_MARIO
- BOBOMB_ACT_DEATH_PLANE_DEATH
- BOBOMB_ACT_EXPLODE
- BOBOMB_ACT_LAUNCHED
- BOBOMB_ACT_LAVA_DEATH
- BOBOMB_ACT_PATROL
- BOBOMB_BP_STYPE_GENERIC
- BOBOMB_BP_STYPE_STATIONARY
- BOBOMB_BUDDY_ACT_IDLE
- BOBOMB_BUDDY_ACT_TALK
- BOBOMB_BUDDY_ACT_TURN_TO_TALK
- BOBOMB_BUDDY_BP_STYPE_BOB_CANNON_KBB
- BOBOMB_BUDDY_BP_STYPE_BOB_GRASS
- BOBOMB_BUDDY_BP_STYPE_BOB_GRASS_KBB
- BOBOMB_BUDDY_BP_STYPE_GENERIC
- BOBOMB_BUDDY_CANNON_OPENED
- BOBOMB_BUDDY_CANNON_OPENING
- BOBOMB_BUDDY_CANNON_STOP_TALKING
- BOBOMB_BUDDY_CANNON_UNOPENED
- BOBOMB_BUDDY_HAS_NOT_TALKED
- BOBOMB_BUDDY_HAS_TALKED
- BOBOMB_BUDDY_ROLE_ADVICE
- BOBOMB_BUDDY_ROLE_CANNON
- BOMP_ACT_EXTEND
- BOMP_ACT_POKE_OUT
- BOMP_ACT_RETRACT
- BOMP_ACT_WAIT
- BOO_ATTACKED
- BOO_BOUNCED_ON
- BOO_CAGE_ACT_FALLING
- BOO_CAGE_ACT_IN_BOO
- BOO_CAGE_ACT_MARIO_JUMPING_IN
- BOO_CAGE_ACT_ON_GROUND
- BOO_CAGE_ACT_USELESS
- BOO_DEATH_STATUS_ALIVE
- BOO_DEATH_STATUS_DEAD
- BOO_DEATH_STATUS_DYING
- BOO_NOT_ATTACKED
- BOWSER_PUZZLE_ACT_DONE
- BOWSER_PUZZLE_ACT_SPAWN_PIECES
- BOWSER_PUZZLE_ACT_WAIT_FOR_COMPLETE
- BULLY_ACT_ACTIVATE_AND_FALL
- BULLY_ACT_BACK_UP
- BULLY_ACT_CHASE_MARIO
- BULLY_ACT_DEATH_PLANE_DEATH
- BULLY_ACT_INACTIVE
- BULLY_ACT_KNOCKBACK
- BULLY_ACT_LAVA_DEATH
- BULLY_ACT_PATROL
- BULLY_BP_SIZE_BIG
- BULLY_BP_SIZE_SMALL
- BULLY_STYPE_CHILL
- BULLY_STYPE_GENERIC
- BULLY_STYPE_MINION
- BUTTERFLY_ACT_FOLLOW_MARIO
- BUTTERFLY_ACT_RESTING
- BUTTERFLY_ACT_RETURN_HOME
- CAMERA_LAKITU_BP_FOLLOW_CAMERA
- CAMERA_LAKITU_BP_INTRO
- CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD
- CAMERA_LAKITU_INTRO_ACT_TRIGGER_CUTSCENE
- CAMERA_LAKITU_INTRO_ACT_UNK2
- CANNON_TRAP_DOOR_ACT_CAM_ZOOM
- CANNON_TRAP_DOOR_ACT_CLOSED
- CANNON_TRAP_DOOR_ACT_OPEN
- CANNON_TRAP_DOOR_ACT_OPENING
- CELEB_STAR_ACT_FACE_CAMERA
- CELEB_STAR_ACT_SPIN_AROUND_MARIO
- CHAIN_CHOMP_ACT_MOVE
- CHAIN_CHOMP_ACT_UNINITIALIZED
- CHAIN_CHOMP_ACT_UNLOAD_CHAIN
- CHAIN_CHOMP_CHAIN_PART_BP_PIVOT
- CHAIN_CHOMP_NOT_RELEASED
- CHAIN_CHOMP_RELEASED_BREAK_GATE
- CHAIN_CHOMP_RELEASED_END_CUTSCENE
- CHAIN_CHOMP_RELEASED_JUMP_AWAY
- CHAIN_CHOMP_RELEASED_LUNGE_AROUND
- CHAIN_CHOMP_RELEASED_TRIGGER_CUTSCENE
- CHAIN_CHOMP_SUB_ACT_LUNGE
- CHAIN_CHOMP_SUB_ACT_TURN
- CLOUD_ACT_FWOOSH_HIDDEN
- CLOUD_ACT_MAIN
- CLOUD_ACT_SPAWN_PARTS
- CLOUD_ACT_UNLOAD
- CLOUD_BP_FWOOSH
- CLOUD_BP_LAKITU_CLOUD
- COFFIN_ACT_IDLE
- COFFIN_ACT_STAND_UP
- COFFIN_BP_STATIC
- COFFIN_SPAWNER_ACT_COFFINS_UNLOADED
- DIALOG_UNK1_AWAIT_DIALOG
- DIALOG_UNK1_BEGIN_DIALOG
- DIALOG_UNK1_DISABLE_TIME_STOP
- DIALOG_UNK1_ENABLE_TIME_STOP
- DIALOG_UNK1_FLAG_4
- DIALOG_UNK1_FLAG_DEFAULT
- DIALOG_UNK1_FLAG_RESPONSE
- DIALOG_UNK1_INTERRUPT_MARIO_ACTION
- DIALOG_UNK2_AWAIT_DIALOG
- DIALOG_UNK2_ENABLE_TIME_STOP
- DIALOG_UNK2_END_DIALOG
- DIALOG_UNK2_FLAG_0
- DIALOG_UNK2_LEAVE_TIME_STOP_ENABLED
- DIALOG_UNK2_TURN_AND_INTERRUPT_MARIO_ACTION
- DORRIE_ACT_LOWER_HEAD
- DORRIE_ACT_MOVE
- DORRIE_ACT_RAISE_HEAD
- ENEMY_LAKITU_ACT_MAIN
- ENEMY_LAKITU_ACT_UNINITIALIZED
- ENEMY_LAKITU_SUB_ACT_HOLD_SPINY
- ENEMY_LAKITU_SUB_ACT_NO_SPINY
- ENEMY_LAKITU_SUB_ACT_THROW_SPINY
- EYEROK_BOSS_ACT_DEAD
- EYEROK_BOSS_ACT_DIE
- EYEROK_BOSS_ACT_FIGHT
- EYEROK_BOSS_ACT_PAUSE
- EYEROK_BOSS_ACT_SHOW_INTRO_TEXT
- EYEROK_BOSS_ACT_SLEEP
- EYEROK_BOSS_ACT_WAKE_UP
- EYEROK_HAND_ACT_ATTACKED
- EYEROK_HAND_ACT_BECOME_ACTIVE
- EYEROK_HAND_ACT_BEGIN_DOUBLE_POUND
- EYEROK_HAND_ACT_CLOSE
- EYEROK_HAND_ACT_DEAD
- EYEROK_HAND_ACT_DIE
- EYEROK_HAND_ACT_DOUBLE_POUND
- EYEROK_HAND_ACT_FIST_PUSH
- EYEROK_HAND_ACT_FIST_SWEEP
- EYEROK_HAND_ACT_IDLE
- EYEROK_HAND_ACT_OPEN
- EYEROK_HAND_ACT_PAUSE
- EYEROK_HAND_ACT_RECOVER
- EYEROK_HAND_ACT_RETREAT
- EYEROK_HAND_ACT_SHOW_EYE
- EYEROK_HAND_ACT_SLEEP
- EYEROK_HAND_ACT_SMASH
- EYEROK_HAND_ACT_TARGET_MARIO
- FAKE_MONEYBAG_COIN_ACT_IDLE
- FAKE_MONEYBAG_COIN_ACT_TRANSFORM
- FALLING_PILLAR_ACT_FALLING
- FALLING_PILLAR_ACT_IDLE
- FALLING_PILLAR_ACT_TURNING
- FIRE_PIRANHA_PLANT_ACT_GROW
- FIRE_PIRANHA_PLANT_ACT_HIDE
- FIRE_SPITTER_ACT_IDLE
- FIRE_SPITTER_ACT_SPIT_FIRE
- FISH_ACT_FLEE
- FISH_ACT_INIT
- FISH_ACT_ROAM
- FISH_SPAWNER_ACT_IDLE
- FISH_SPAWNER_ACT_RESPAWN
- FISH_SPAWNER_ACT_SPAWN
- FISH_SPAWNER_BP_FEW_BLUE
- FISH_SPAWNER_BP_FEW_CYAN
- FISH_SPAWNER_BP_MANY_BLUE
- FISH_SPAWNER_BP_MANY_CYAN
- FLY_GUY_ACT_APPROACH_MARIO
- FLY_GUY_ACT_IDLE
- FLY_GUY_ACT_LUNGE
- FLY_GUY_ACT_SHOOT_FIRE
- FREE_BBALL_ACT_IDLE
- FREE_BBALL_ACT_RESET
- FREE_BBALL_ACT_ROLL
- GOOMBA_ACT_ATTACKED_MARIO
- GOOMBA_ACT_JUMP
- GOOMBA_ACT_WALK
- GOOMBA_BP_SIZE_MASK
- GOOMBA_BP_TRIPLET_FLAG_MASK
- GOOMBA_SIZE_HUGE
- GOOMBA_SIZE_REGULAR
- GOOMBA_SIZE_TINY
- GOOMBA_TRIPLET_SPAWNER_ACT_LOADED
- GOOMBA_TRIPLET_SPAWNER_ACT_UNLOADED
- GOOMBA_TRIPLET_SPAWNER_BP_EXTRA_GOOMBAS_MASK
- GOOMBA_TRIPLET_SPAWNER_BP_SIZE_MASK
- HAUNTED_BOOKSHELF_ACT_IDLE
- HAUNTED_BOOKSHELF_ACT_RECEDE
- HELD_DROPPED
- HELD_FREE
- HELD_HELD
- HELD_THROWN
- HIDDEN_BLUE_COIN_ACT_ACTIVE
- HIDDEN_BLUE_COIN_ACT_INACTIVE
- HIDDEN_BLUE_COIN_ACT_WAITING
- HOMING_AMP_ACT_APPEAR
- HOMING_AMP_ACT_ATTACK_COOLDOWN
- HOMING_AMP_ACT_CHASE
- HOMING_AMP_ACT_GIVE_UP
- HOMING_AMP_ACT_INACTIVE
- HOOT_ACT_ASCENT
- HOOT_ACT_CARRY
- HOOT_ACT_TIRED
- HOOT_AVAIL_ASLEEP_IN_TREE
- HOOT_AVAIL_READY_TO_FLY
- HOOT_AVAIL_WANTS_TO_TALK
- JS_RING_SPAWNER_ACT_ACTIVE
- JS_RING_SPAWNER_ACT_INACTIVE
- KLEPTO_ACT_APPROACH_TARGET_HOLDING
- KLEPTO_ACT_CIRCLE_TARGET_HOLDING
- KLEPTO_ACT_DIVE_AT_MARIO
- KLEPTO_ACT_RESET_POSITION
- KLEPTO_ACT_RETREAT
- KLEPTO_ACT_STRUCK_BY_MARIO
- KLEPTO_ACT_TURN_TOWARD_MARIO
- KLEPTO_ACT_WAIT_FOR_MARIO
- KLEPTO_ANIM_STATE_HOLDING_CAP
- KLEPTO_ANIM_STATE_HOLDING_NOTHING
- KLEPTO_ANIM_STATE_HOLDING_STAR
- KOOPA_BP_KOOPA_THE_QUICK_BASE
- KOOPA_BP_KOOPA_THE_QUICK_BOB
- KOOPA_BP_KOOPA_THE_QUICK_THI
- KOOPA_BP_NORMAL
- KOOPA_BP_TINY
- KOOPA_BP_UNSHELLED
- KOOPA_SHELLED_ACT_DIE
- KOOPA_SHELLED_ACT_LYING
- KOOPA_SHELLED_ACT_RUN_FROM_MARIO
- KOOPA_SHELLED_ACT_STOPPED
- KOOPA_SHELLED_ACT_WALK
- KOOPA_SHELLED_SUB_ACT_START_WALK
- KOOPA_SHELLED_SUB_ACT_STOP_WALK
- KOOPA_SHELLED_SUB_ACT_WALK
- KOOPA_THE_QUICK_ACT_AFTER_RACE
- KOOPA_THE_QUICK_ACT_DECELERATE
- KOOPA_THE_QUICK_ACT_RACE
- KOOPA_THE_QUICK_ACT_SHOW_INIT_TEXT
- KOOPA_THE_QUICK_ACT_STOP
- KOOPA_THE_QUICK_ACT_UNUSED1
- KOOPA_THE_QUICK_ACT_WAIT_BEFORE_RACE
- KOOPA_THE_QUICK_BOB_INDEX
- KOOPA_THE_QUICK_SUB_ACT_JUMP
- KOOPA_THE_QUICK_SUB_ACT_RUN
- KOOPA_THE_QUICK_SUB_ACT_START_RUN
- KOOPA_THE_QUICK_THI_INDEX
- KOOPA_UNSHELLED_ACT_DIVE
- KOOPA_UNSHELLED_ACT_LYING
- KOOPA_UNSHELLED_ACT_RUN
- KOOPA_UNSHELLED_ACT_UNUSED3
- LLL_DRAWBRIDGE_ACT_LOWER
- LLL_DRAWBRIDGE_ACT_RAISE
- MAD_PIANO_ACT_ATTACK
- MAD_PIANO_ACT_WAIT
- MANTA_ACT_NO_RINGS
- MANTA_ACT_SPAWN_RINGS
- MIPS_ACT_FALL_DOWN
- MIPS_ACT_FOLLOW_PATH
- MIPS_ACT_IDLE
- MIPS_ACT_WAIT_FOR_ANIMATION_DONE
- MIPS_ACT_WAIT_FOR_NEARBY_MARIO
- MIPS_STAR_STATUS_ALREADY_SPAWNED_STAR
- MIPS_STAR_STATUS_HAVENT_SPAWNED_STAR
- MIPS_STAR_STATUS_SHOULD_SPAWN_STAR
- MONEYBAG_ACT_APPEAR
- MONEYBAG_ACT_DEATH
- MONEYBAG_ACT_DISAPPEAR
- MONEYBAG_ACT_MOVE_AROUND
- MONEYBAG_ACT_RETURN_HOME
- MONEYBAG_ACT_UNUSED_APPEAR
- MONEYBAG_JUMP_JUMP
- MONEYBAG_JUMP_JUMP_AND_BOUNCE
- MONEYBAG_JUMP_LANDING
- MONEYBAG_JUMP_PREPARE
- MONEYBAG_JUMP_WALK_AROUND
- MONEYBAG_JUMP_WALK_HOME
- MONTY_MOLE_ACT_BEGIN_JUMP_INTO_HOLE
- MONTY_MOLE_ACT_HIDE
- MONTY_MOLE_ACT_JUMP_INTO_HOLE
- MONTY_MOLE_ACT_JUMP_OUT_OF_HOLE
- MONTY_MOLE_ACT_RISE_FROM_HOLE
- MONTY_MOLE_ACT_SELECT_HOLE
- MONTY_MOLE_ACT_SPAWN_ROCK
- MONTY_MOLE_ACT_THROW_ROCK
- MONTY_MOLE_BP_NO_ROCK
- MONTY_MOLE_ROCK_ACT_HELD
- MONTY_MOLE_ROCK_ACT_MOVE
- MOV_BCOIN_ACT_MOVING
- MOV_BCOIN_ACT_STILL
- MOV_YCOIN_ACT_BLINKING
- MOV_YCOIN_ACT_DEATH_PLANE_DEATH
- MOV_YCOIN_ACT_IDLE
- MOV_YCOIN_ACT_LAVA_DEATH
- MR_BLIZZARD_ACT_BURROW
- MR_BLIZZARD_ACT_DEATH
- MR_BLIZZARD_ACT_HIDE_UNHIDE
- MR_BLIZZARD_ACT_JUMP
- MR_BLIZZARD_ACT_RISE_FROM_GROUND
- MR_BLIZZARD_ACT_ROTATE
- MR_BLIZZARD_ACT_SPAWN_SNOWBALL
- MR_BLIZZARD_ACT_THROW_SNOWBALL
- MR_BLIZZARD_STYPE_JUMPING
- MR_BLIZZARD_STYPE_NO_CAP
- OBJ_ACT_DEATH_PLANE_DEATH
- OBJ_ACT_HORIZONTAL_KNOCKBACK
- OBJ_ACT_LAVA_DEATH
- OBJ_ACT_SQUISHED
- OBJ_ACT_VERTICAL_KNOCKBACK
- OBJ_FLAG_0020
- OBJ_FLAG_0100
- OBJ_FLAG_1000
- OBJ_FLAG_30
- OBJ_FLAG_8000
- OBJ_FLAG_ACTIVE_FROM_AFAR
- OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO
- OBJ_FLAG_COMPUTE_DIST_TO_MARIO
- OBJ_FLAG_HOLDABLE
- OBJ_FLAG_MOVE_XZ_USING_FVEL
- OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL
- OBJ_FLAG_PERSISTENT_RESPAWN
- OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE
- OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW
- OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM
- OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT
- OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
- OBJ_MOVE_ABOVE_DEATH_BARRIER
- OBJ_MOVE_ABOVE_LAVA
- OBJ_MOVE_AT_WATER_SURFACE
- OBJ_MOVE_BOUNCE
- OBJ_MOVE_ENTERED_WATER
- OBJ_MOVE_HIT_EDGE
- OBJ_MOVE_HIT_WALL
- OBJ_MOVE_IN_AIR
- OBJ_MOVE_LANDED
- OBJ_MOVE_LEAVING_WATER
- OBJ_MOVE_LEFT_GROUND
- OBJ_MOVE_MASK_IN_WATER
- OBJ_MOVE_MASK_ON_GROUND
- OBJ_MOVE_ON_GROUND
- OBJ_MOVE_OUT_SCOPE
- OBJ_MOVE_UNDERWATER_OFF_GROUND
- OBJ_MOVE_UNDERWATER_ON_GROUND
- PENGUIN_ANIM_IDLE
- PENGUIN_ANIM_WALK
- PENGUIN_WALK_BABY
- PENGUIN_WALK_BIG
- PIRANHA_PLANT_ACT_ATTACKED
- PIRANHA_PLANT_ACT_BITING
- PIRANHA_PLANT_ACT_IDLE
- PIRANHA_PLANT_ACT_RESPAWN
- PIRANHA_PLANT_ACT_SHRINK_AND_DIE
- PIRANHA_PLANT_ACT_SLEEPING
- PIRANHA_PLANT_ACT_STOPPED_BITING
- PIRANHA_PLANT_ACT_WAIT_TO_RESPAWN
- PIRANHA_PLANT_ACT_WOKEN_UP
- PIRANHA_PLANT_BUBBLE_ACT_BURST
- PIRANHA_PLANT_BUBBLE_ACT_GROW_SHRINK_LOOP
- PIRANHA_PLANT_BUBBLE_ACT_IDLE
- PLATFORM_ON_TRACK_ACT_FALL
- PLATFORM_ON_TRACK_ACT_INIT
- PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK
- PLATFORM_ON_TRACK_ACT_PAUSE_BRIEFLY
- PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO
- PLATFORM_ON_TRACK_BP_DONT_DISAPPEAR
- PLATFORM_ON_TRACK_BP_DONT_TURN_ROLL
- PLATFORM_ON_TRACK_BP_DONT_TURN_YAW
- PLATFORM_ON_TRACK_BP_MASK_PATH
- PLATFORM_ON_TRACK_BP_MASK_TYPE
- PLATFORM_ON_TRACK_BP_RETURN_TO_START
- PLATFORM_ON_TRACK_TYPE_CARPET
- PLATFORM_ON_TRACK_TYPE_CHECKERED
- PLATFORM_ON_TRACK_TYPE_GRATE
- PLATFORM_ON_TRACK_TYPE_SKI_LIFT
- POKEY_ACT_UNINITIALIZED
- POKEY_ACT_UNLOAD_PARTS
- POKEY_ACT_WANDER
- PURPLE_SWITCH_IDLE
- PURPLE_SWITCH_PRESSED
- PURPLE_SWITCH_TICKING
- PURPLE_SWITCH_UNPRESSED
- PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF
- PYRAMID_ELEVATOR_AT_BOTTOM
- PYRAMID_ELEVATOR_CONSTANT_VELOCITY
- PYRAMID_ELEVATOR_END_MOVING
- PYRAMID_ELEVATOR_IDLE
- PYRAMID_ELEVATOR_START_MOVING
- PYRAMID_TOP_ACT_CHECK_IF_SOLVED
- PYRAMID_TOP_ACT_EXPLODE
- PYRAMID_TOP_ACT_SPINNING
- PYRAMID_WALL_ACT_MOVING_DOWN
- PYRAMID_WALL_ACT_MOVING_UP
- PYRAMID_WALL_BP_POSITION_HIGH
- PYRAMID_WALL_BP_POSITION_LOW
- PYRAMID_WALL_BP_POSITION_MIDDLE
- RACING_PENGUIN_ACT_FINISH_RACE
- RACING_PENGUIN_ACT_PREPARE_FOR_RACE
- RACING_PENGUIN_ACT_RACE
- RACING_PENGUIN_ACT_SHOW_FINAL_TEXT
- RACING_PENGUIN_ACT_SHOW_INIT_TEXT
- RACING_PENGUIN_ACT_WAIT_FOR_MARIO
- RESPAWN_INFO_DONT_RESPAWN
- RESPAWN_INFO_TYPE_16
- RESPAWN_INFO_TYPE_32
- RESPAWN_INFO_TYPE_NULL
- SKEETER_ACT_IDLE
- SKEETER_ACT_LUNGE
- SKEETER_ACT_WALK
- SL_SNOWMAN_WIND_ACT_BLOWING
- SL_SNOWMAN_WIND_ACT_IDLE
- SL_SNOWMAN_WIND_ACT_TALKING
- SL_WALKING_PENGUIN_ACT_MOVING_FORWARDS
- SL_WALKING_PENGUIN_ACT_RETURNING
- SL_WALKING_PENGUIN_ACT_TURNING_BACK
- SL_WALKING_PENGUIN_ACT_TURNING_FORWARDS
- SNUFIT_ACT_IDLE
- SNUFIT_ACT_SHOOT
- SPINY_ACT_ATTACKED_MARIO
- SPINY_ACT_HELD_BY_LAKITU
- SPINY_ACT_THROWN_BY_LAKITU
- SPINY_ACT_WALK
- SWOOP_ACT_IDLE
- SWOOP_ACT_MOVE
- TRIPLET_BUTTERFLY_ACT_ACTIVATE
- TRIPLET_BUTTERFLY_ACT_EXPLODE
- TRIPLET_BUTTERFLY_ACT_INIT
- TRIPLET_BUTTERFLY_ACT_WANDER
- TRIPLET_BUTTERFLY_BP_BUTTERFLY_NUM
- TRIPLET_BUTTERFLY_BP_NO_BOMBS
- TRIPLET_BUTTERFLY_TYPE_EXPLODES
- TRIPLET_BUTTERFLY_TYPE_NORMAL
- TRIPLET_BUTTERFLY_TYPE_SPAWN_1UP
- TTC_2D_ROTATOR_BP_2D_COG
- TTC_2D_ROTATOR_BP_HAND
- TTC_COG_BP_DIR_CCW
- TTC_COG_BP_DIR_CW
- TTC_COG_BP_DIR_MASK
- TTC_COG_BP_SHAPE_HEXAGON
- TTC_COG_BP_SHAPE_MASK
- TTC_COG_BP_SHAPE_TRIANGLE
- TTC_MOVING_BAR_ACT_EXTEND
- TTC_MOVING_BAR_ACT_PULL_BACK
- TTC_MOVING_BAR_ACT_RETRACT
- TTC_MOVING_BAR_ACT_WAIT
- TTC_ROTATING_SOLID_BP_CUBE
- TTC_ROTATING_SOLID_BP_TRIANGULAR_PRISM
- TTC_SPEED_FAST
- TTC_SPEED_RANDOM
- TTC_SPEED_SLOW
- TTC_SPEED_STOPPED
- TWEESTER_ACT_CHASE
- TWEESTER_ACT_HIDE
- TWEESTER_ACT_IDLE
- TWEESTER_SUB_ACT_CHASE
- TWEESTER_SUB_ACT_WAIT
- UKIKI_ACT_GO_TO_CAGE
- UKIKI_ACT_IDLE
- UKIKI_ACT_JUMP
- UKIKI_ACT_RETURN_HOME
- UKIKI_ACT_RUN
- UKIKI_ACT_TURN_TO_MARIO
- UKIKI_ACT_UNUSED_TURN
- UKIKI_ACT_WAIT_TO_RESPAWN
- UKIKI_ANIM_HANDSTAND
- UKIKI_ANIM_HELD
- UKIKI_ANIM_ITCH
- UKIKI_ANIM_JUMP
- UKIKI_ANIM_JUMP_CLAP
- UKIKI_ANIM_LAND
- UKIKI_ANIM_RUN
- UKIKI_ANIM_SCREECH
- UKIKI_ANIM_STATE_CAP_ON
- UKIKI_ANIM_STATE_DEFAULT
- UKIKI_ANIM_STATE_EYE_CLOSED
- UKIKI_ANIM_TURN
- UKIKI_ANIM_UNUSED_APOSE
- UKIKI_ANIM_UNUSED_DEATH
- UKIKI_ANIM_UNUSED_HOP
- UKIKI_ANIM_UNUSED_WALK
- UKIKI_CAGE
- UKIKI_CAGE_ACT_FALL
- UKIKI_CAGE_ACT_HIDE
- UKIKI_CAGE_ACT_SPIN
- UKIKI_CAGE_ACT_WAIT_FOR_UKIKI
- UKIKI_CAGE_STAR_ACT_IN_CAGE
- UKIKI_CAGE_STAR_ACT_SPAWN_STAR
- UKIKI_CAP
- UKIKI_CAP_ON
- UKIKI_SUB_ACT_CAGE_DESPAWN
- UKIKI_SUB_ACT_CAGE_JUMP_TO_CAGE
- UKIKI_SUB_ACT_CAGE_LAND_ON_CAGE
- UKIKI_SUB_ACT_CAGE_RUN_TO_CAGE
- UKIKI_SUB_ACT_CAGE_SPIN_ON_CAGE
- UKIKI_SUB_ACT_CAGE_TALK_TO_MARIO
- UKIKI_SUB_ACT_CAGE_TURN_TO_CAGE
- UKIKI_SUB_ACT_CAGE_WAIT_FOR_MARIO
- UKIKI_SUB_ACT_TAUNT_HANDSTAND
- UKIKI_SUB_ACT_TAUNT_ITCH
- UKIKI_SUB_ACT_TAUNT_JUMP_CLAP
- UKIKI_SUB_ACT_TAUNT_NONE
- UKIKI_SUB_ACT_TAUNT_SCREECH
- UKIKI_TEXT_CAGE_TEXTBOX
- UKIKI_TEXT_DEFAULT
- UKIKI_TEXT_DO_NOT_LET_GO
- UKIKI_TEXT_GAVE_CAP_BACK
- UKIKI_TEXT_GO_TO_CAGE
- UKIKI_TEXT_HAS_CAP
- UKIKI_TEXT_STEAL_CAP
- UKIKI_TEXT_STOLE_CAP
- WATER_BOMB_ACT_DROP
- WATER_BOMB_ACT_EXPLODE
- WATER_BOMB_ACT_INIT
- WATER_BOMB_ACT_SHOT_FROM_CANNON
- WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL
- WATER_LEVEL_DIAMOND_ACT_IDLE
- WATER_LEVEL_DIAMOND_ACT_IDLE_SPINNING
- WATER_LEVEL_DIAMOND_ACT_INIT
- WATER_RING_ACT_COLLECTED
- WATER_RING_ACT_NOT_COLLECTED
- WF_SLID_BRICK_PTFM_ACT_EXTEND
- WF_SLID_BRICK_PTFM_ACT_RETRACT
- WF_SLID_BRICK_PTFM_ACT_WAIT
- WF_SLID_BRICK_PTFM_BP_MOV_VEL_10
- WF_SLID_BRICK_PTFM_BP_MOV_VEL_15
- WF_SLID_BRICK_PTFM_BP_MOV_VEL_20
- WIGGLER_ACT_FALL_THROUGH_FLOOR
- WIGGLER_ACT_JUMPED_ON
- WIGGLER_ACT_KNOCKBACK
- WIGGLER_ACT_SHRINK
- WIGGLER_ACT_UNINITIALIZED
- WIGGLER_ACT_WALK
- WIGGLER_TEXT_STATUS_AWAIT_DIALOG
- WIGGLER_TEXT_STATUS_COMPLETED_DIALOG
- WIGGLER_TEXT_STATUS_SHOWING_DIALOG
- WOODEN_POST_BP_NO_COINS_MASK
- YOSHI_ACT_CREDITS
- YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN
- YOSHI_ACT_GIVE_PRESENT
- YOSHI_ACT_IDLE
- YOSHI_ACT_TALK
- YOSHI_ACT_WALK
- YOSHI_ACT_WALK_JUMP_OFF_ROOF

[:arrow_up_small:](#)

<br />

## [object_list_processor.h](#object_list_processor.h)
- OBJECT_POOL_CAPACITY
- TIME_STOP_ACTIVE
- TIME_STOP_ALL_OBJECTS
- TIME_STOP_DIALOG
- TIME_STOP_ENABLED
- TIME_STOP_MARIO_AND_DOORS
- TIME_STOP_MARIO_OPENED_DOOR
- TIME_STOP_UNKNOWN_0

### [enum ObjectList](#ObjectList)
| Identifier | Value |
| :--------- | :---- |
| OBJ_LIST_PLAYER | 0 |
| OBJ_LIST_EXT | 1 |
| OBJ_LIST_DESTRUCTIVE | 2 |
| OBJ_LIST_UNUSED_3 | 3 |
| OBJ_LIST_GENACTOR | 4 |
| OBJ_LIST_PUSHABLE | 5 |
| OBJ_LIST_LEVEL | 6 |
| OBJ_LIST_UNUSED_7 | 7 |
| OBJ_LIST_DEFAULT | 8 |
| OBJ_LIST_SURFACE | 9 |
| OBJ_LIST_POLELIKE | 10 |
| OBJ_LIST_SPAWNER | 11 |
| OBJ_LIST_UNIMPORTANT | 12 |
| NUM_OBJ_LISTS | 13 |

[:arrow_up_small:](#)

<br />

## [os_cont.h](#os_cont.h)
- A_BUTTON
- B_BUTTON
- CONT_A
- CONT_ABSOLUTE
- CONT_ADDR_CRC_ER
- CONT_B
- CONT_C
- CONT_CARD_ON
- CONT_CARD_PULL
- CONT_COLLISION_ERROR
- CONT_D
- CONT_DOWN
- CONT_E
- CONT_EEP16K
- CONT_EEPROM
- CONT_EEPROM_BUSY
- CONT_F
- CONT_FRAME_ERROR
- CONT_G
- CONT_JOYPORT
- CONT_L
- CONT_LEFT
- CONT_NO_RESPONSE_ERROR
- CONT_OVERRUN_ERROR
- CONT_R
- CONT_RELATIVE
- CONT_RIGHT
- CONT_START
- CONT_TYPE_MASK
- CONT_TYPE_MOUSE
- CONT_TYPE_NORMAL
- CONT_TYPE_VOICE
- CONT_UP
- CONT_X
- CONT_Y
- D_CBUTTONS
- D_JPAD
- L_CBUTTONS
- L_JPAD
- L_TRIG
- R_CBUTTONS
- R_JPAD
- R_TRIG
- START_BUTTON
- U_CBUTTONS
- U_JPAD
- X_BUTTON
- Y_BUTTON
- Z_TRIG

[:arrow_up_small:](#)

<br />

## [player_palette.h](#player_palette.h)
- MAX_PRESET_PALETTES

### [enum PlayerPart](#PlayerPart)
| Identifier | Value |
| :--------- | :---- |
| PANTS | 0 |
| SHIRT | 1 |
| GLOVES | 2 |
| SHOES | 3 |
| HAIR | 4 |
| SKIN | 5 |
| CAP | 6 |
| EMBLEM | 7 |
| PLAYER_PART_MAX | 8 |
| METAL | CAP |

[:arrow_up_small:](#)

<br />

## [save_file.h](#save_file.h)
- EEPROM_SIZE
- NUM_SAVE_FILES
- SAVE_FLAG_CAP_ON_GROUND
- SAVE_FLAG_CAP_ON_KLEPTO
- SAVE_FLAG_CAP_ON_MR_BLIZZARD
- SAVE_FLAG_CAP_ON_UKIKI
- SAVE_FLAG_COLLECTED_MIPS_STAR_1
- SAVE_FLAG_COLLECTED_MIPS_STAR_2
- SAVE_FLAG_COLLECTED_TOAD_STAR_1
- SAVE_FLAG_COLLECTED_TOAD_STAR_2
- SAVE_FLAG_COLLECTED_TOAD_STAR_3
- SAVE_FLAG_DDD_MOVED_BACK
- SAVE_FLAG_FILE_EXISTS
- SAVE_FLAG_HAVE_KEY_1
- SAVE_FLAG_HAVE_KEY_2
- SAVE_FLAG_HAVE_METAL_CAP
- SAVE_FLAG_HAVE_VANISH_CAP
- SAVE_FLAG_HAVE_WING_CAP
- SAVE_FLAG_MOAT_DRAINED
- SAVE_FLAG_UNLOCKED_50_STAR_DOOR
- SAVE_FLAG_UNLOCKED_BASEMENT_DOOR
- SAVE_FLAG_UNLOCKED_BITDW_DOOR
- SAVE_FLAG_UNLOCKED_BITFS_DOOR
- SAVE_FLAG_UNLOCKED_CCM_DOOR
- SAVE_FLAG_UNLOCKED_JRB_DOOR
- SAVE_FLAG_UNLOCKED_PSS_DOOR
- SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR
- SAVE_FLAG_UNLOCKED_WF_DOOR

### [enum SaveFileIndex](#SaveFileIndex)
| Identifier | Value |
| :--------- | :---- |
| SAVE_FILE_A | 0 |
| SAVE_FILE_B | 1 |
| SAVE_FILE_C | 2 |
| SAVE_FILE_D | 3 |

[:arrow_up_small:](#)

<br />

## [seq_ids.h](#seq_ids.h)
- SEQ_BASE_ID
- SEQ_VARIATION

### [enum SeqId](#SeqId)
| Identifier | Value |
| :--------- | :---- |
| SEQ_SOUND_PLAYER | 0 |
| SEQ_EVENT_CUTSCENE_COLLECT_STAR | 1 |
| SEQ_MENU_TITLE_SCREEN | 2 |
| SEQ_LEVEL_GRASS | 3 |
| SEQ_LEVEL_INSIDE_CASTLE | 4 |
| SEQ_LEVEL_WATER | 5 |
| SEQ_LEVEL_HOT | 6 |
| SEQ_LEVEL_BOSS_KOOPA | 7 |
| SEQ_LEVEL_SNOW | 8 |
| SEQ_LEVEL_SLIDE | 9 |
| SEQ_LEVEL_SPOOKY | 10 |
| SEQ_EVENT_PIRANHA_PLANT | 11 |
| SEQ_LEVEL_UNDERGROUND | 12 |
| SEQ_MENU_STAR_SELECT | 13 |
| SEQ_EVENT_POWERUP | 14 |
| SEQ_EVENT_METAL_CAP | 15 |
| SEQ_EVENT_KOOPA_MESSAGE | 16 |
| SEQ_LEVEL_KOOPA_ROAD | 17 |
| SEQ_EVENT_HIGH_SCORE | 18 |
| SEQ_EVENT_MERRY_GO_ROUND | 19 |
| SEQ_EVENT_RACE | 20 |
| SEQ_EVENT_CUTSCENE_STAR_SPAWN | 21 |
| SEQ_EVENT_BOSS | 22 |
| SEQ_EVENT_CUTSCENE_COLLECT_KEY | 23 |
| SEQ_EVENT_ENDLESS_STAIRS | 24 |
| SEQ_LEVEL_BOSS_KOOPA_FINAL | 25 |
| SEQ_EVENT_CUTSCENE_CREDITS | 26 |
| SEQ_EVENT_SOLVE_PUZZLE | 27 |
| SEQ_EVENT_TOAD_MESSAGE | 28 |
| SEQ_EVENT_PEACH_MESSAGE | 29 |
| SEQ_EVENT_CUTSCENE_INTRO | 30 |
| SEQ_EVENT_CUTSCENE_VICTORY | 31 |
| SEQ_EVENT_CUTSCENE_ENDING | 32 |
| SEQ_MENU_FILE_SELECT | 33 |
| SEQ_EVENT_CUTSCENE_LAKITU | 34 |
| SEQ_COUNT | 35 |

[:arrow_up_small:](#)

<br />

## [sm64.h](#sm64.h)
- ACT_AIR_HIT_WALL
- ACT_AIR_THROW
- ACT_AIR_THROW_LAND
- ACT_BACKFLIP
- ACT_BACKFLIP_LAND
- ACT_BACKFLIP_LAND_STOP
- ACT_BACKWARD_AIR_KB
- ACT_BACKWARD_GROUND_KB
- ACT_BACKWARD_ROLLOUT
- ACT_BACKWARD_WATER_KB
- ACT_BBH_ENTER_JUMP
- ACT_BBH_ENTER_SPIN
- ACT_BEGIN_SLIDING
- ACT_BRAKING
- ACT_BRAKING_STOP
- ACT_BREASTSTROKE
- ACT_BUBBLED
- ACT_BURNING_FALL
- ACT_BURNING_GROUND
- ACT_BURNING_JUMP
- ACT_BUTT_SLIDE
- ACT_BUTT_SLIDE_AIR
- ACT_BUTT_SLIDE_STOP
- ACT_BUTT_STUCK_IN_GROUND
- ACT_CAUGHT_IN_WHIRLPOOL
- ACT_CLIMBING_POLE
- ACT_COUGHING
- ACT_CRAWLING
- ACT_CRAZY_BOX_BOUNCE
- ACT_CREDITS_CUTSCENE
- ACT_CROUCHING
- ACT_CROUCH_SLIDE
- ACT_DEATH_EXIT
- ACT_DEATH_EXIT_LAND
- ACT_DEATH_ON_BACK
- ACT_DEATH_ON_STOMACH
- ACT_DEBUG_FREE_MOVE
- ACT_DECELERATING
- ACT_DISAPPEARED
- ACT_DIVE
- ACT_DIVE_PICKING_UP
- ACT_DIVE_SLIDE
- ACT_DOUBLE_JUMP
- ACT_DOUBLE_JUMP_LAND
- ACT_DOUBLE_JUMP_LAND_STOP
- ACT_DROWNING
- ACT_EATEN_BY_BUBBA
- ACT_ELECTROCUTION
- ACT_EMERGE_FROM_PIPE
- ACT_END_PEACH_CUTSCENE
- ACT_END_WAVING_CUTSCENE
- ACT_ENTERING_STAR_DOOR
- ACT_EXIT_AIRBORNE
- ACT_EXIT_LAND_SAVE_DIALOG
- ACT_FALLING_DEATH_EXIT
- ACT_FALLING_EXIT_AIRBORNE
- ACT_FALL_AFTER_STAR_GRAB
- ACT_FEET_STUCK_IN_GROUND
- ACT_FINISH_TURNING_AROUND
- ACT_FIRST_PERSON
- ACT_FLAG_AIR
- ACT_FLAG_ALLOW_FIRST_PERSON
- ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION
- ACT_FLAG_ATTACKING
- ACT_FLAG_BUTT_OR_STOMACH_SLIDE
- ACT_FLAG_CONTROL_JUMP_HEIGHT
- ACT_FLAG_CUSTOM_ACTION
- ACT_FLAG_DIVING
- ACT_FLAG_FLYING
- ACT_FLAG_HANGING
- ACT_FLAG_IDLE
- ACT_FLAG_INTANGIBLE
- ACT_FLAG_INVULNERABLE
- ACT_FLAG_METAL_WATER
- ACT_FLAG_MOVING
- ACT_FLAG_ON_POLE
- ACT_FLAG_PAUSE_EXIT
- ACT_FLAG_RIDING_SHELL
- ACT_FLAG_SHORT_HITBOX
- ACT_FLAG_STATIONARY
- ACT_FLAG_SWIMMING
- ACT_FLAG_SWIMMING_OR_FLYING
- ACT_FLAG_THROWING
- ACT_FLAG_WATER_OR_TEXT
- ACT_FLUTTER_KICK
- ACT_FLYING
- ACT_FLYING_TRIPLE_JUMP
- ACT_FORWARD_AIR_KB
- ACT_FORWARD_GROUND_KB
- ACT_FORWARD_ROLLOUT
- ACT_FORWARD_WATER_KB
- ACT_FREEFALL
- ACT_FREEFALL_LAND
- ACT_FREEFALL_LAND_STOP
- ACT_GETTING_BLOWN
- ACT_GRABBED
- ACT_GRAB_POLE_FAST
- ACT_GRAB_POLE_SLOW
- ACT_GROUND_BONK
- ACT_GROUND_POUND
- ACT_GROUND_POUND_LAND
- ACT_GROUP_AIRBORNE
- ACT_GROUP_AUTOMATIC
- ACT_GROUP_CUTSCENE
- ACT_GROUP_MASK
- ACT_GROUP_MOVING
- ACT_GROUP_OBJECT
- ACT_GROUP_STATIONARY
- ACT_GROUP_SUBMERGED
- ACT_HANGING
- ACT_HANG_MOVING
- ACT_HARD_BACKWARD_AIR_KB
- ACT_HARD_BACKWARD_GROUND_KB
- ACT_HARD_FORWARD_AIR_KB
- ACT_HARD_FORWARD_GROUND_KB
- ACT_HEAD_STUCK_IN_GROUND
- ACT_HEAVY_THROW
- ACT_HOLDING_BOWSER
- ACT_HOLDING_POLE
- ACT_HOLD_BEGIN_SLIDING
- ACT_HOLD_BREASTSTROKE
- ACT_HOLD_BUTT_SLIDE
- ACT_HOLD_BUTT_SLIDE_AIR
- ACT_HOLD_BUTT_SLIDE_STOP
- ACT_HOLD_DECELERATING
- ACT_HOLD_FLUTTER_KICK
- ACT_HOLD_FREEFALL
- ACT_HOLD_FREEFALL_LAND
- ACT_HOLD_FREEFALL_LAND_STOP
- ACT_HOLD_HEAVY_IDLE
- ACT_HOLD_HEAVY_WALKING
- ACT_HOLD_IDLE
- ACT_HOLD_JUMP
- ACT_HOLD_JUMP_LAND
- ACT_HOLD_JUMP_LAND_STOP
- ACT_HOLD_METAL_WATER_FALLING
- ACT_HOLD_METAL_WATER_FALL_LAND
- ACT_HOLD_METAL_WATER_JUMP
- ACT_HOLD_METAL_WATER_JUMP_LAND
- ACT_HOLD_METAL_WATER_STANDING
- ACT_HOLD_METAL_WATER_WALKING
- ACT_HOLD_PANTING_UNUSED
- ACT_HOLD_QUICKSAND_JUMP_LAND
- ACT_HOLD_STOMACH_SLIDE
- ACT_HOLD_SWIMMING_END
- ACT_HOLD_WALKING
- ACT_HOLD_WATER_ACTION_END
- ACT_HOLD_WATER_IDLE
- ACT_HOLD_WATER_JUMP
- ACT_IDLE
- ACT_ID_MASK
- ACT_INDEX_MASK
- ACT_INTRO_CUTSCENE
- ACT_IN_CANNON
- ACT_IN_QUICKSAND
- ACT_JUMBO_STAR_CUTSCENE
- ACT_JUMP
- ACT_JUMP_KICK
- ACT_JUMP_LAND
- ACT_JUMP_LAND_STOP
- ACT_LAVA_BOOST
- ACT_LAVA_BOOST_LAND
- ACT_LEDGE_CLIMB_DOWN
- ACT_LEDGE_CLIMB_FAST
- ACT_LEDGE_CLIMB_SLOW_1
- ACT_LEDGE_CLIMB_SLOW_2
- ACT_LEDGE_GRAB
- ACT_LONG_JUMP
- ACT_LONG_JUMP_LAND
- ACT_LONG_JUMP_LAND_STOP
- ACT_METAL_WATER_FALLING
- ACT_METAL_WATER_FALL_LAND
- ACT_METAL_WATER_JUMP
- ACT_METAL_WATER_JUMP_LAND
- ACT_METAL_WATER_STANDING
- ACT_METAL_WATER_WALKING
- ACT_MOVE_PUNCHING
- ACT_NUM_ACTIONS_PER_GROUP
- ACT_NUM_GROUPS
- ACT_PANTING
- ACT_PICKING_UP
- ACT_PICKING_UP_BOWSER
- ACT_PLACING_DOWN
- ACT_PULLING_DOOR
- ACT_PUNCHING
- ACT_PUSHING_DOOR
- ACT_PUTTING_ON_CAP
- ACT_QUICKSAND_DEATH
- ACT_QUICKSAND_JUMP_LAND
- ACT_READING_AUTOMATIC_DIALOG
- ACT_READING_NPC_DIALOG
- ACT_READING_SIGN
- ACT_RELEASING_BOWSER
- ACT_RIDING_HOOT
- ACT_RIDING_SHELL_FALL
- ACT_RIDING_SHELL_GROUND
- ACT_RIDING_SHELL_JUMP
- ACT_SHIVERING
- ACT_SHOCKED
- ACT_SHOCKWAVE_BOUNCE
- ACT_SHOT_FROM_CANNON
- ACT_SIDE_FLIP
- ACT_SIDE_FLIP_LAND
- ACT_SIDE_FLIP_LAND_STOP
- ACT_SLEEPING
- ACT_SLIDE_KICK
- ACT_SLIDE_KICK_SLIDE
- ACT_SLIDE_KICK_SLIDE_STOP
- ACT_SOFT_BACKWARD_GROUND_KB
- ACT_SOFT_BONK
- ACT_SOFT_FORWARD_GROUND_KB
- ACT_SPAWN_NO_SPIN_AIRBORNE
- ACT_SPAWN_NO_SPIN_LANDING
- ACT_SPAWN_SPIN_AIRBORNE
- ACT_SPAWN_SPIN_LANDING
- ACT_SPECIAL_DEATH_EXIT
- ACT_SPECIAL_EXIT_AIRBORNE
- ACT_SPECIAL_TRIPLE_JUMP
- ACT_SQUISHED
- ACT_STANDING_AGAINST_WALL
- ACT_STANDING_DEATH
- ACT_START_CRAWLING
- ACT_START_CROUCHING
- ACT_START_HANGING
- ACT_START_SLEEPING
- ACT_STAR_DANCE_EXIT
- ACT_STAR_DANCE_NO_EXIT
- ACT_STAR_DANCE_WATER
- ACT_STEEP_JUMP
- ACT_STOMACH_SLIDE
- ACT_STOMACH_SLIDE_STOP
- ACT_STOP_CRAWLING
- ACT_STOP_CROUCHING
- ACT_SUFFOCATION
- ACT_SWIMMING_END
- ACT_TAKING_OFF_CAP
- ACT_TELEPORT_FADE_IN
- ACT_TELEPORT_FADE_OUT
- ACT_THROWING
- ACT_THROWN_BACKWARD
- ACT_THROWN_FORWARD
- ACT_TOP_OF_POLE
- ACT_TOP_OF_POLE_JUMP
- ACT_TOP_OF_POLE_TRANSITION
- ACT_TORNADO_TWIRLING
- ACT_TRIPLE_JUMP
- ACT_TRIPLE_JUMP_LAND
- ACT_TRIPLE_JUMP_LAND_STOP
- ACT_TURNING_AROUND
- ACT_TWIRLING
- ACT_TWIRL_LAND
- ACT_UNINITIALIZED
- ACT_UNKNOWN_0002020E
- ACT_UNLOCKING_KEY_DOOR
- ACT_UNLOCKING_STAR_DOOR
- ACT_UNUSED_DEATH_EXIT
- ACT_VERTICAL_WIND
- ACT_WAITING_FOR_DIALOG
- ACT_WAKING_UP
- ACT_WALKING
- ACT_WALL_KICK_AIR
- ACT_WARP_DOOR_SPAWN
- ACT_WATER_ACTION_END
- ACT_WATER_DEATH
- ACT_WATER_IDLE
- ACT_WATER_JUMP
- ACT_WATER_PLUNGE
- ACT_WATER_PUNCH
- ACT_WATER_SHELL_SWIMMING
- ACT_WATER_SHOCKED
- ACT_WATER_THROW
- AIR_STEP_CHECK_HANG
- AIR_STEP_CHECK_LEDGE_GRAB
- AIR_STEP_GRABBED_CEILING
- AIR_STEP_GRABBED_LEDGE
- AIR_STEP_HIT_LAVA_WALL
- AIR_STEP_HIT_WALL
- AIR_STEP_LANDED
- AIR_STEP_NONE
- C_BUTTONS
- END_DEMO
- GROUND_STEP_HIT_WALL
- GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS
- GROUND_STEP_HIT_WALL_STOP_QSTEPS
- GROUND_STEP_LEFT_GROUND
- GROUND_STEP_NONE
- INPUT_ABOVE_SLIDE
- INPUT_A_DOWN
- INPUT_A_PRESSED
- INPUT_B_PRESSED
- INPUT_FIRST_PERSON
- INPUT_INTERACT_OBJ_GRABBABLE
- INPUT_IN_POISON_GAS
- INPUT_IN_WATER
- INPUT_NONZERO_ANALOG
- INPUT_OFF_FLOOR
- INPUT_SQUISHED
- INPUT_UNKNOWN_10
- INPUT_UNKNOWN_12
- INPUT_ZERO_MOVEMENT
- INPUT_Z_DOWN
- INPUT_Z_PRESSED
- LAYER_ALPHA
- LAYER_FORCE
- LAYER_OPAQUE
- LAYER_OPAQUE_DECAL
- LAYER_OPAQUE_INTER
- LAYER_TRANSPARENT
- LAYER_TRANSPARENT_DECAL
- LAYER_TRANSPARENT_INTER
- MARIO_ACTION_SOUND_PLAYED
- MARIO_CAPS
- MARIO_CAP_IN_HAND
- MARIO_CAP_ON_HEAD
- MARIO_KICKING
- MARIO_MARIO_SOUND_PLAYED
- MARIO_METAL_CAP
- MARIO_METAL_SHOCK
- MARIO_NORMAL_CAP
- MARIO_PUNCHING
- MARIO_SPECIAL_CAPS
- MARIO_TELEPORTING
- MARIO_TRIPPING
- MARIO_UNKNOWN_08
- MARIO_UNKNOWN_13
- MARIO_UNKNOWN_18
- MARIO_UNKNOWN_25
- MARIO_UNKNOWN_30
- MARIO_UNKNOWN_31
- MARIO_VANISH_CAP
- MARIO_WING_CAP
- MODEL_STATE_METAL
- MODEL_STATE_NOISE_ALPHA
- PARTICLE_19
- PARTICLE_2
- PARTICLE_BREATH
- PARTICLE_BUBBLE
- PARTICLE_DIRT
- PARTICLE_DUST
- PARTICLE_FIRE
- PARTICLE_HORIZONTAL_STAR
- PARTICLE_IDLE_WATER_WAVE
- PARTICLE_LEAF
- PARTICLE_MIST_CIRCLE
- PARTICLE_PLUNGE_BUBBLE
- PARTICLE_SHALLOW_WATER_SPLASH
- PARTICLE_SHALLOW_WATER_WAVE
- PARTICLE_SNOW
- PARTICLE_SPARKLES
- PARTICLE_TRIANGLE
- PARTICLE_VERTICAL_STAR
- PARTICLE_WATER_SPLASH
- PARTICLE_WAVE_TRAIL
- STEP_TYPE_AIR
- STEP_TYPE_GROUND
- STEP_TYPE_HANG
- STEP_TYPE_WATER
- VALID_BUTTONS
- WATER_STEP_CANCELLED
- WATER_STEP_HIT_CEILING
- WATER_STEP_HIT_FLOOR
- WATER_STEP_HIT_WALL
- WATER_STEP_NONE

[:arrow_up_small:](#)

<br />

## [smlua_hooks.h](#smlua_hooks.h)

### [enum LuaActionHookType](#LuaActionHookType)
| Identifier | Value |
| :--------- | :---- |
| ACTION_HOOK_EVERY_FRAME | 0 |
| ACTION_HOOK_GRAVITY | 1 |
| ACTION_HOOK_MAX | 2 |

### [enum LuaHookedEventType](#LuaHookedEventType)
| Identifier | Value |
| :--------- | :---- |
| HOOK_UPDATE | 0 |
| HOOK_MARIO_UPDATE | 1 |
| HOOK_BEFORE_MARIO_UPDATE | 2 |
| HOOK_ON_SET_MARIO_ACTION | 3 |
| HOOK_BEFORE_PHYS_STEP | 4 |
| HOOK_ALLOW_PVP_ATTACK | 5 |
| HOOK_ON_PVP_ATTACK | 6 |
| HOOK_ON_PLAYER_CONNECTED | 7 |
| HOOK_ON_PLAYER_DISCONNECTED | 8 |
| HOOK_ON_HUD_RENDER | 9 |
| HOOK_ALLOW_INTERACT | 10 |
| HOOK_ON_INTERACT | 11 |
| HOOK_ON_LEVEL_INIT | 12 |
| HOOK_ON_WARP | 13 |
| HOOK_ON_SYNC_VALID | 14 |
| HOOK_ON_OBJECT_UNLOAD | 15 |
| HOOK_ON_SYNC_OBJECT_UNLOAD | 16 |
| HOOK_ON_PAUSE_EXIT | 17 |
| HOOK_GET_STAR_COLLECTION_DIALOG | 18 |
| HOOK_ON_SET_CAMERA_MODE | 19 |
| HOOK_ON_OBJECT_RENDER | 20 |
| HOOK_ON_DEATH | 21 |
| HOOK_ON_PACKET_RECEIVE | 22 |
| HOOK_USE_ACT_SELECT | 23 |
| HOOK_ON_CHANGE_CAMERA_ANGLE | 24 |
| HOOK_ON_SCREEN_TRANSITION | 25 |
| HOOK_ALLOW_HAZARD_SURFACE | 26 |
| HOOK_ON_CHAT_MESSAGE | 27 |
| HOOK_OBJECT_SET_MODEL | 28 |
| HOOK_CHARACTER_SOUND | 29 |
| HOOK_BEFORE_SET_MARIO_ACTION | 30 |
| HOOK_JOINED_GAME | 31 |
| HOOK_ON_OBJECT_ANIM_UPDATE | 32 |
| HOOK_ON_DIALOG | 33 |
| HOOK_ON_EXIT | 34 |
| HOOK_DIALOG_SOUND | 35 |
| HOOK_ON_HUD_RENDER_BEHIND | 36 |
| HOOK_ON_COLLIDE_LEVEL_BOUNDS | 37 |
| HOOK_MIRROR_MARIO_RENDER | 38 |
| HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED | 39 |
| HOOK_ON_OBJECT_LOAD | 40 |
| HOOK_ON_PLAY_SOUND | 41 |
| HOOK_ON_SEQ_LOAD | 42 |
| HOOK_ON_ATTACK_OBJECT | 43 |
| HOOK_ON_LANGUAGE_CHANGED | 44 |
| HOOK_ON_MODS_LOADED | 45 |
| HOOK_ON_NAMETAGS_RENDER | 46 |
| HOOK_MAX | 47 |

### [enum LuaModMenuElementType](#LuaModMenuElementType)
| Identifier | Value |
| :--------- | :---- |
| MOD_MENU_ELEMENT_BUTTON | 0 |
| MOD_MENU_ELEMENT_CHECKBOX | 1 |
| MOD_MENU_ELEMENT_SLIDER | 2 |
| MOD_MENU_ELEMENT_INPUTBOX | 3 |
| MOD_MENU_ELEMENT_MAX | 4 |

[:arrow_up_small:](#)

<br />

## [smlua_misc_utils.h](#smlua_misc_utils.h)

### [enum HudDisplayFlags](#HudDisplayFlags)
| Identifier | Value |
| :--------- | :---- |
| HUD_DISPLAY_FLAGS_NONE | 0x0000 |
| HUD_DISPLAY_FLAGS_LIVES | 0x0001 |
| HUD_DISPLAY_FLAGS_COIN_COUNT | 0x0002 |
| HUD_DISPLAY_FLAGS_STAR_COUNT | 0x0004 |
| HUD_DISPLAY_FLAGS_CAMERA_AND_POWER | 0x0008 |
| HUD_DISPLAY_FLAGS_KEYS | 0x0010 |
| HUD_DISPLAY_FLAGS_UNKNOWN_0020 | 0x0020 |
| HUD_DISPLAY_FLAGS_TIMER | 0x0040 |
| HUD_DISPLAY_FLAGS_CAMERA | 0x0080 |
| HUD_DISPLAY_FLAGS_POWER | 0x0100 |
| HUD_DISPLAY_FLAGS_EMPHASIZE_POWER | 0x8000 |

### [enum HudDisplayValue](#HudDisplayValue)
| Identifier | Value |
| :--------- | :---- |
| HUD_DISPLAY_LIVES | 0 |
| HUD_DISPLAY_COINS | 1 |
| HUD_DISPLAY_STARS | 2 |
| HUD_DISPLAY_WEDGES | 3 |
| HUD_DISPLAY_KEYS | 4 |
| HUD_DISPLAY_FLAGS | 5 |
| HUD_DISPLAY_TIMER | 6 |
| HUD_DISPLAY_CAMERA_STATUS | 7 |

[:arrow_up_small:](#)

<br />

## [smlua_model_utils.h](#smlua_model_utils.h)

### [enum ModelExtendedId](#ModelExtendedId)
| Identifier | Value |
| :--------- | :---- |
| E_MODEL_NONE | 0 |
| E_MODEL_MARIO | 1 |
| E_MODEL_SMOKE | 2 |
| E_MODEL_SPARKLES | 3 |
| E_MODEL_BUBBLE | 4 |
| E_MODEL_SMALL_WATER_SPLASH | 5 |
| E_MODEL_IDLE_WATER_WAVE | 6 |
| E_MODEL_WATER_SPLASH | 7 |
| E_MODEL_WAVE_TRAIL | 8 |
| E_MODEL_YELLOW_COIN | 9 |
| E_MODEL_STAR | 10 |
| E_MODEL_TRANSPARENT_STAR | 11 |
| E_MODEL_WOODEN_SIGNPOST | 12 |
| E_MODEL_WHITE_PARTICLE_SMALL | 13 |
| E_MODEL_RED_FLAME | 14 |
| E_MODEL_BLUE_FLAME | 15 |
| E_MODEL_BURN_SMOKE | 16 |
| E_MODEL_LEAVES | 17 |
| E_MODEL_PURPLE_MARBLE | 18 |
| E_MODEL_TRAMPOLINE | 19 |
| E_MODEL_TRAMPOLINE_CENTER | 20 |
| E_MODEL_TRAMPOLINE_BASE | 21 |
| E_MODEL_FISH | 22 |
| E_MODEL_FISH_SHADOW | 23 |
| E_MODEL_SPARKLES_ANIMATION | 24 |
| E_MODEL_SAND_DUST | 25 |
| E_MODEL_BUTTERFLY | 26 |
| E_MODEL_BURN_SMOKE_UNUSED | 27 |
| E_MODEL_PEBBLE | 28 |
| E_MODEL_MIST | 29 |
| E_MODEL_WHITE_PUFF | 30 |
| E_MODEL_WHITE_PARTICLE_DL | 31 |
| E_MODEL_WHITE_PARTICLE | 32 |
| E_MODEL_YELLOW_COIN_NO_SHADOW | 33 |
| E_MODEL_BLUE_COIN | 34 |
| E_MODEL_BLUE_COIN_NO_SHADOW | 35 |
| E_MODEL_MARIOS_WINGED_METAL_CAP | 36 |
| E_MODEL_MARIOS_METAL_CAP | 37 |
| E_MODEL_MARIOS_WING_CAP | 38 |
| E_MODEL_MARIOS_CAP | 39 |
| E_MODEL_BOWSER_KEY_CUTSCENE | 40 |
| E_MODEL_BOWSER_KEY | 41 |
| E_MODEL_RED_FLAME_SHADOW | 42 |
| E_MODEL_1UP | 43 |
| E_MODEL_RED_COIN | 44 |
| E_MODEL_RED_COIN_NO_SHADOW | 45 |
| E_MODEL_NUMBER | 46 |
| E_MODEL_EXPLOSION | 47 |
| E_MODEL_DIRT_ANIMATION | 48 |
| E_MODEL_CARTOON_STAR | 49 |
| E_MODEL_BLUE_COIN_SWITCH | 50 |
| E_MODEL_AMP | 51 |
| E_MODEL_PURPLE_SWITCH | 52 |
| E_MODEL_CHECKERBOARD_PLATFORM | 53 |
| E_MODEL_BREAKABLE_BOX | 54 |
| E_MODEL_BREAKABLE_BOX_SMALL | 55 |
| E_MODEL_EXCLAMATION_BOX_OUTLINE | 56 |
| E_MODEL_EXCLAMATION_BOX | 57 |
| E_MODEL_GOOMBA | 58 |
| E_MODEL_EXCLAMATION_POINT | 59 |
| E_MODEL_KOOPA_SHELL | 60 |
| E_MODEL_METAL_BOX | 61 |
| E_MODEL_METAL_BOX_DL | 62 |
| E_MODEL_BLACK_BOBOMB | 63 |
| E_MODEL_BOBOMB_BUDDY | 64 |
| E_MODEL_DL_CANNON_LID | 65 |
| E_MODEL_BOWLING_BALL | 66 |
| E_MODEL_CANNON_BARREL | 67 |
| E_MODEL_CANNON_BASE | 68 |
| E_MODEL_HEART | 69 |
| E_MODEL_FLYGUY | 70 |
| E_MODEL_CHUCKYA | 71 |
| E_MODEL_TRAJECTORY_MARKER_BALL | 72 |
| E_MODEL_BULLET_BILL | 73 |
| E_MODEL_YELLOW_SPHERE | 74 |
| E_MODEL_HOOT | 75 |
| E_MODEL_YOSHI_EGG | 76 |
| E_MODEL_THWOMP | 77 |
| E_MODEL_HEAVE_HO | 78 |
| E_MODEL_BLARGG | 79 |
| E_MODEL_BULLY | 80 |
| E_MODEL_BULLY_BOSS | 81 |
| E_MODEL_WATER_BOMB | 82 |
| E_MODEL_WATER_BOMB_SHADOW | 83 |
| E_MODEL_KING_BOBOMB | 84 |
| E_MODEL_MANTA_RAY | 85 |
| E_MODEL_UNAGI | 86 |
| E_MODEL_SUSHI | 87 |
| E_MODEL_DL_WHIRLPOOL | 88 |
| E_MODEL_CLAM_SHELL | 89 |
| E_MODEL_POKEY_HEAD | 90 |
| E_MODEL_POKEY_BODY_PART | 91 |
| E_MODEL_TWEESTER | 92 |
| E_MODEL_KLEPTO | 93 |
| E_MODEL_EYEROK_LEFT_HAND | 94 |
| E_MODEL_EYEROK_RIGHT_HAND | 95 |
| E_MODEL_DL_MONTY_MOLE_HOLE | 96 |
| E_MODEL_MONTY_MOLE | 97 |
| E_MODEL_UKIKI | 98 |
| E_MODEL_FWOOSH | 99 |
| E_MODEL_SPINDRIFT | 100 |
| E_MODEL_MR_BLIZZARD_HIDDEN | 101 |
| E_MODEL_MR_BLIZZARD | 102 |
| E_MODEL_PENGUIN | 103 |
| E_MODEL_CAP_SWITCH_EXCLAMATION | 104 |
| E_MODEL_CAP_SWITCH | 105 |
| E_MODEL_CAP_SWITCH_BASE | 106 |
| E_MODEL_BOO | 107 |
| E_MODEL_BETA_BOO_KEY | 108 |
| E_MODEL_HAUNTED_CHAIR | 109 |
| E_MODEL_MAD_PIANO | 110 |
| E_MODEL_BOOKEND_PART | 111 |
| E_MODEL_BOOKEND | 112 |
| E_MODEL_HAUNTED_CAGE | 113 |
| E_MODEL_BIRDS | 114 |
| E_MODEL_PEACH | 115 |
| E_MODEL_YOSHI | 116 |
| E_MODEL_ENEMY_LAKITU | 117 |
| E_MODEL_SPINY_BALL | 118 |
| E_MODEL_SPINY | 119 |
| E_MODEL_WIGGLER_HEAD | 120 |
| E_MODEL_WIGGLER_BODY | 121 |
| E_MODEL_BUBBA | 122 |
| E_MODEL_BOWSER | 123 |
| E_MODEL_BOWSER_BOMB_CHILD_OBJ | 124 |
| E_MODEL_BOWSER_BOMB | 125 |
| E_MODEL_BOWSER_SMOKE | 126 |
| E_MODEL_BOWSER_FLAMES | 127 |
| E_MODEL_BOWSER_WAVE | 128 |
| E_MODEL_BOWSER2 | 129 |
| E_MODEL_BUB | 130 |
| E_MODEL_TREASURE_CHEST_BASE | 131 |
| E_MODEL_TREASURE_CHEST_LID | 132 |
| E_MODEL_CYAN_FISH | 133 |
| E_MODEL_WATER_RING | 134 |
| E_MODEL_WATER_MINE | 135 |
| E_MODEL_SEAWEED | 136 |
| E_MODEL_SKEETER | 137 |
| E_MODEL_PIRANHA_PLANT | 138 |
| E_MODEL_WHOMP | 139 |
| E_MODEL_KOOPA_WITH_SHELL | 140 |
| E_MODEL_KOOPA_WITHOUT_SHELL | 141 |
| E_MODEL_METALLIC_BALL | 142 |
| E_MODEL_CHAIN_CHOMP | 143 |
| E_MODEL_KOOPA_FLAG | 144 |
| E_MODEL_WOODEN_POST | 145 |
| E_MODEL_MIPS | 146 |
| E_MODEL_BOO_CASTLE | 147 |
| E_MODEL_LAKITU | 148 |
| E_MODEL_TOAD | 149 |
| E_MODEL_CHILL_BULLY | 150 |
| E_MODEL_BIG_CHILL_BULLY | 151 |
| E_MODEL_MONEYBAG | 152 |
| E_MODEL_SWOOP | 153 |
| E_MODEL_SCUTTLEBUG | 154 |
| E_MODEL_MR_I_IRIS | 155 |
| E_MODEL_MR_I | 156 |
| E_MODEL_DORRIE | 157 |
| E_MODEL_SNUFIT | 158 |
| E_MODEL_ERROR_MODEL | 159 |
| E_MODEL_BUBBLY_TREE | 160 |
| E_MODEL_COURTYARD_SPIKY_TREE | 161 |
| E_MODEL_SNOW_TREE | 162 |
| E_MODEL_PALM_TREE | 163 |
| E_MODEL_CASTLE_CASTLE_DOOR | 164 |
| E_MODEL_BBH_HAUNTED_DOOR | 165 |
| E_MODEL_HMC_WOODEN_DOOR | 166 |
| E_MODEL_HMC_METAL_DOOR | 167 |
| E_MODEL_HMC_HAZY_MAZE_DOOR | 168 |
| E_MODEL_CASTLE_DOOR_0_STARS | 169 |
| E_MODEL_CASTLE_DOOR_1_STAR | 170 |
| E_MODEL_CASTLE_DOOR_3_STARS | 171 |
| E_MODEL_CASTLE_STAR_DOOR_8_STARS | 172 |
| E_MODEL_CASTLE_STAR_DOOR_30_STARS | 173 |
| E_MODEL_CASTLE_STAR_DOOR_50_STARS | 174 |
| E_MODEL_CASTLE_STAR_DOOR_70_STARS | 175 |
| E_MODEL_CASTLE_KEY_DOOR | 176 |
| E_MODEL_CCM_CABIN_DOOR | 177 |
| E_MODEL_CASTLE_METAL_DOOR | 178 |
| E_MODEL_CASTLE_GROUNDS_METAL_DOOR | 179 |
| E_MODEL_WF_TOWER_TRAPEZOID_PLATORM | 180 |
| E_MODEL_WF_TOWER_SQUARE_PLATORM | 181 |
| E_MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED | 182 |
| E_MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR | 183 |
| E_MODEL_BBH_STAIRCASE_STEP | 184 |
| E_MODEL_BBH_TILTING_FLOOR_PLATFORM | 185 |
| E_MODEL_BBH_TUMBLING_PLATFORM | 186 |
| E_MODEL_BBH_TUMBLING_PLATFORM_PART | 187 |
| E_MODEL_BBH_MOVING_BOOKSHELF | 188 |
| E_MODEL_BBH_MESH_ELEVATOR | 189 |
| E_MODEL_BBH_MERRY_GO_ROUND | 190 |
| E_MODEL_BBH_WOODEN_TOMB | 191 |
| E_MODEL_CCM_ROPEWAY_LIFT | 192 |
| E_MODEL_CCM_SNOWMAN_HEAD | 193 |
| E_MODEL_CASTLE_BOWSER_TRAP | 194 |
| E_MODEL_CASTLE_WATER_LEVEL_PILLAR | 195 |
| E_MODEL_CASTLE_CLOCK_MINUTE_HAND | 196 |
| E_MODEL_CASTLE_CLOCK_HOUR_HAND | 197 |
| E_MODEL_CASTLE_CLOCK_PENDULUM | 198 |
| E_MODEL_HMC_METAL_PLATFORM | 199 |
| E_MODEL_HMC_METAL_ARROW_PLATFORM | 200 |
| E_MODEL_HMC_ELEVATOR_PLATFORM | 201 |
| E_MODEL_HMC_ROLLING_ROCK | 202 |
| E_MODEL_HMC_ROCK_PIECE | 203 |
| E_MODEL_HMC_ROCK_SMALL_PIECE | 204 |
| E_MODEL_HMC_RED_GRILLS | 205 |
| E_MODEL_SSL_PYRAMID_TOP | 206 |
| E_MODEL_SSL_GRINDEL | 207 |
| E_MODEL_SSL_SPINDEL | 208 |
| E_MODEL_SSL_MOVING_PYRAMID_WALL | 209 |
| E_MODEL_SSL_PYRAMID_ELEVATOR | 210 |
| E_MODEL_SSL_TOX_BOX | 211 |
| E_MODEL_BOB_CHAIN_CHOMP_GATE | 212 |
| E_MODEL_BOB_SEESAW_PLATFORM | 213 |
| E_MODEL_BOB_BARS_GRILLS | 214 |
| E_MODEL_SL_SNOW_TRIANGLE | 215 |
| E_MODEL_SL_CRACKED_ICE | 216 |
| E_MODEL_SL_CRACKED_ICE_CHUNK | 217 |
| E_MODEL_WDW_SQUARE_FLOATING_PLATFORM | 218 |
| E_MODEL_WDW_ARROW_LIFT | 219 |
| E_MODEL_WDW_WATER_LEVEL_DIAMOND | 220 |
| E_MODEL_WDW_HIDDEN_PLATFORM | 221 |
| E_MODEL_WDW_EXPRESS_ELEVATOR | 222 |
| E_MODEL_WDW_RECTANGULAR_FLOATING_PLATFORM | 223 |
| E_MODEL_WDW_ROTATING_PLATFORM | 224 |
| E_MODEL_JRB_SHIP_LEFT_HALF_PART | 225 |
| E_MODEL_JRB_SHIP_BACK_LEFT_PART | 226 |
| E_MODEL_JRB_SHIP_RIGHT_HALF_PART | 227 |
| E_MODEL_JRB_SHIP_BACK_RIGHT_PART | 228 |
| E_MODEL_JRB_SUNKEN_SHIP | 229 |
| E_MODEL_JRB_SUNKEN_SHIP_BACK | 230 |
| E_MODEL_JRB_ROCK | 231 |
| E_MODEL_JRB_SLIDING_BOX | 232 |
| E_MODEL_JRB_FALLING_PILLAR | 233 |
| E_MODEL_JRB_FALLING_PILLAR_BASE | 234 |
| E_MODEL_JRB_FLOATING_PLATFORM | 235 |
| E_MODEL_THI_HUGE_ISLAND_TOP | 236 |
| E_MODEL_THI_TINY_ISLAND_TOP | 237 |
| E_MODEL_TTC_ROTATING_CUBE | 238 |
| E_MODEL_TTC_ROTATING_PRISM | 239 |
| E_MODEL_TTC_PENDULUM | 240 |
| E_MODEL_TTC_LARGE_TREADMILL | 241 |
| E_MODEL_TTC_SMALL_TREADMILL | 242 |
| E_MODEL_TTC_PUSH_BLOCK | 243 |
| E_MODEL_TTC_ROTATING_HEXAGON | 244 |
| E_MODEL_TTC_ROTATING_TRIANGLE | 245 |
| E_MODEL_TTC_PIT_BLOCK | 246 |
| E_MODEL_TTC_PIT_BLOCK_UNUSED | 247 |
| E_MODEL_TTC_ELEVATOR_PLATFORM | 248 |
| E_MODEL_TTC_CLOCK_HAND | 249 |
| E_MODEL_TTC_SPINNER | 250 |
| E_MODEL_TTC_SMALL_GEAR | 251 |
| E_MODEL_TTC_LARGE_GEAR | 252 |
| E_MODEL_RR_SLIDING_PLATFORM | 253 |
| E_MODEL_RR_FLYING_CARPET | 254 |
| E_MODEL_RR_OCTAGONAL_PLATFORM | 255 |
| E_MODEL_RR_ROTATING_BRIDGE_PLATFORM | 256 |
| E_MODEL_RR_TRIANGLE_PLATFORM | 257 |
| E_MODEL_RR_CRUISER_WING | 258 |
| E_MODEL_RR_SEESAW_PLATFORM | 259 |
| E_MODEL_RR_L_SHAPED_PLATFORM | 260 |
| E_MODEL_RR_SWINGING_PLATFORM | 261 |
| E_MODEL_RR_DONUT_PLATFORM | 262 |
| E_MODEL_RR_ELEVATOR_PLATFORM | 263 |
| E_MODEL_RR_TRICKY_TRIANGLES | 264 |
| E_MODEL_RR_TRICKY_TRIANGLES_FRAME1 | 265 |
| E_MODEL_RR_TRICKY_TRIANGLES_FRAME2 | 266 |
| E_MODEL_RR_TRICKY_TRIANGLES_FRAME3 | 267 |
| E_MODEL_RR_TRICKY_TRIANGLES_FRAME4 | 268 |
| E_MODEL_BITDW_SQUARE_PLATFORM | 269 |
| E_MODEL_BITDW_SEESAW_PLATFORM | 270 |
| E_MODEL_BITDW_SLIDING_PLATFORM | 271 |
| E_MODEL_BITDW_FERRIS_WHEEL_AXLE | 272 |
| E_MODEL_BITDW_BLUE_PLATFORM | 273 |
| E_MODEL_BITDW_STAIRCASE_FRAME4 | 274 |
| E_MODEL_BITDW_STAIRCASE_FRAME3 | 275 |
| E_MODEL_BITDW_STAIRCASE_FRAME2 | 276 |
| E_MODEL_BITDW_STAIRCASE_FRAME1 | 277 |
| E_MODEL_BITDW_STAIRCASE | 278 |
| E_MODEL_BITFS_PLATFORM_ON_TRACK | 279 |
| E_MODEL_BITFS_TILTING_SQUARE_PLATFORM | 280 |
| E_MODEL_BITFS_SINKING_PLATFORMS | 281 |
| E_MODEL_BITFS_BLUE_POLE | 282 |
| E_MODEL_BITFS_SINKING_CAGE_PLATFORM | 283 |
| E_MODEL_BITFS_ELEVATOR | 284 |
| E_MODEL_BITFS_STRETCHING_PLATFORMS | 285 |
| E_MODEL_BITFS_SEESAW_PLATFORM | 286 |
| E_MODEL_BITFS_MOVING_SQUARE_PLATFORM | 287 |
| E_MODEL_BITFS_SLIDING_PLATFORM | 288 |
| E_MODEL_BITFS_TUMBLING_PLATFORM_PART | 289 |
| E_MODEL_BITFS_TUMBLING_PLATFORM | 290 |
| E_MODEL_BITS_SLIDING_PLATFORM | 291 |
| E_MODEL_BITS_TWIN_SLIDING_PLATFORMS | 292 |
| E_MODEL_BITS_OCTAGONAL_PLATFORM | 293 |
| E_MODEL_BITS_BLUE_PLATFORM | 294 |
| E_MODEL_BITS_FERRIS_WHEEL_AXLE | 295 |
| E_MODEL_BITS_ARROW_PLATFORM | 296 |
| E_MODEL_BITS_SEESAW_PLATFORM | 297 |
| E_MODEL_BITS_TILTING_W_PLATFORM | 298 |
| E_MODEL_BITS_STAIRCASE | 299 |
| E_MODEL_BITS_STAIRCASE_FRAME1 | 300 |
| E_MODEL_BITS_STAIRCASE_FRAME2 | 301 |
| E_MODEL_BITS_STAIRCASE_FRAME3 | 302 |
| E_MODEL_BITS_STAIRCASE_FRAME4 | 303 |
| E_MODEL_BITS_WARP_PIPE | 304 |
| E_MODEL_LLL_DRAWBRIDGE_PART | 305 |
| E_MODEL_LLL_ROTATING_BLOCK_FIRE_BARS | 306 |
| E_MODEL_LLL_ROTATING_HEXAGONAL_RING | 307 |
| E_MODEL_LLL_SINKING_RECTANGULAR_PLATFORM | 308 |
| E_MODEL_LLL_SINKING_SQUARE_PLATFORMS | 309 |
| E_MODEL_LLL_TILTING_SQUARE_PLATFORM | 310 |
| E_MODEL_LLL_BOWSER_PIECE_1 | 311 |
| E_MODEL_LLL_BOWSER_PIECE_2 | 312 |
| E_MODEL_LLL_BOWSER_PIECE_3 | 313 |
| E_MODEL_LLL_BOWSER_PIECE_4 | 314 |
| E_MODEL_LLL_BOWSER_PIECE_5 | 315 |
| E_MODEL_LLL_BOWSER_PIECE_6 | 316 |
| E_MODEL_LLL_BOWSER_PIECE_7 | 317 |
| E_MODEL_LLL_BOWSER_PIECE_8 | 318 |
| E_MODEL_LLL_BOWSER_PIECE_9 | 319 |
| E_MODEL_LLL_BOWSER_PIECE_10 | 320 |
| E_MODEL_LLL_BOWSER_PIECE_11 | 321 |
| E_MODEL_LLL_BOWSER_PIECE_12 | 322 |
| E_MODEL_LLL_BOWSER_PIECE_13 | 323 |
| E_MODEL_LLL_BOWSER_PIECE_14 | 324 |
| E_MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM | 325 |
| E_MODEL_LLL_SINKING_ROCK_BLOCK | 326 |
| E_MODEL_LLL_ROLLING_LOG | 327 |
| E_MODEL_LLL_WOOD_BRIDGE | 328 |
| E_MODEL_LLL_LARGE_WOOD_BRIDGE | 329 |
| E_MODEL_LLL_FALLING_PLATFORM | 330 |
| E_MODEL_LLL_LARGE_FALLING_PLATFORM | 331 |
| E_MODEL_LLL_VOLCANO_FALLING_TRAP | 332 |
| E_MODEL_DDD_BOWSER_SUB_DOOR | 333 |
| E_MODEL_DDD_BOWSER_SUB | 334 |
| E_MODEL_DDD_POLE | 335 |
| E_MODEL_WF_BREAKABLE_WALL_RIGHT | 336 |
| E_MODEL_WF_BREAKABLE_WALL_LEFT | 337 |
| E_MODEL_WF_KICKABLE_BOARD | 338 |
| E_MODEL_WF_TOWER_DOOR | 339 |
| E_MODEL_WF_KICKABLE_BOARD_FELLED | 340 |
| E_MODEL_CASTLE_GROUNDS_VCUTM_GRILL | 341 |
| E_MODEL_CASTLE_GROUNDS_FLAG | 342 |
| E_MODEL_CASTLE_GROUNDS_CANNON_GRILL | 343 |
| E_MODEL_BOWSER_2_TILTING_ARENA | 344 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_1 | 345 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_2 | 346 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_3 | 347 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_4 | 348 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_5 | 349 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_6 | 350 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_7 | 351 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_8 | 352 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_9 | 353 |
| E_MODEL_BOWSER_3_FALLING_PLATFORM_10 | 354 |
| E_MODEL_TTM_ROLLING_LOG | 355 |
| E_MODEL_TTM_STAR_CAGE | 356 |
| E_MODEL_TTM_BLUE_SMILEY | 357 |
| E_MODEL_TTM_YELLOW_SMILEY | 358 |
| E_MODEL_TTM_STAR_SMILEY | 359 |
| E_MODEL_TTM_MOON_SMILEY | 360 |
| E_MODEL_BUBBLE_PLAYER | 361 |
| E_MODEL_LUIGI | 362 |
| E_MODEL_LUIGIS_CAP | 363 |
| E_MODEL_LUIGIS_METAL_CAP | 364 |
| E_MODEL_LUIGIS_WING_CAP | 365 |
| E_MODEL_LUIGIS_WINGED_METAL_CAP | 366 |
| E_MODEL_TOAD_PLAYER | 367 |
| E_MODEL_TOADS_CAP | 368 |
| E_MODEL_TOADS_METAL_CAP | 369 |
| E_MODEL_TOADS_WING_CAP | 370 |
| E_MODEL_WALUIGI | 371 |
| E_MODEL_WALUIGIS_CAP | 372 |
| E_MODEL_WALUIGIS_METAL_CAP | 373 |
| E_MODEL_WALUIGIS_WING_CAP | 374 |
| E_MODEL_WALUIGIS_WINGED_METAL_CAP | 375 |
| E_MODEL_WARIO | 376 |
| E_MODEL_WARIOS_CAP | 377 |
| E_MODEL_WARIOS_METAL_CAP | 378 |
| E_MODEL_WARIOS_WING_CAP | 379 |
| E_MODEL_WARIOS_WINGED_METAL_CAP | 380 |
| E_MODEL_MAX | 381 |

[:arrow_up_small:](#)

<br />

## [sounds.h](#sounds.h)
- NO_SOUND
- SOUNDARGS_MASK_BANK
- SOUNDARGS_MASK_PRIORITY
- SOUNDARGS_MASK_SOUNDID
- SOUNDARGS_MASK_STATUS
- SOUNDARGS_SHIFT_BANK
- SOUNDARGS_SHIFT_PRIORITY
- SOUNDARGS_SHIFT_SOUNDID
- SOUND_ACTION_BONK
- SOUND_ACTION_BOUNCE_OFF_OBJECT
- SOUND_ACTION_BRUSH_HAIR
- SOUND_ACTION_CLAP_HANDS_COLD
- SOUND_ACTION_CLIMB_DOWN_TREE
- SOUND_ACTION_CLIMB_UP_POLE
- SOUND_ACTION_CLIMB_UP_TREE
- SOUND_ACTION_FLYING_FAST
- SOUND_ACTION_HANGING_STEP
- SOUND_ACTION_HIT
- SOUND_ACTION_HIT_2
- SOUND_ACTION_HIT_3
- SOUND_ACTION_INTRO_UNK45E
- SOUND_ACTION_INTRO_UNK45F
- SOUND_ACTION_KEY_SWISH
- SOUND_ACTION_METAL_BONK
- SOUND_ACTION_METAL_HEAVY_LANDING
- SOUND_ACTION_METAL_JUMP
- SOUND_ACTION_METAL_JUMP_WATER
- SOUND_ACTION_METAL_LANDING
- SOUND_ACTION_METAL_LAND_WATER
- SOUND_ACTION_METAL_STEP
- SOUND_ACTION_METAL_STEP_TIPTOE
- SOUND_ACTION_METAL_STEP_WATER
- SOUND_ACTION_PAT_BACK
- SOUND_ACTION_QUICKSAND_STEP
- SOUND_ACTION_READ_SIGN
- SOUND_ACTION_SHRINK_INTO_BBH
- SOUND_ACTION_SIDE_FLIP_UNK
- SOUND_ACTION_SPIN
- SOUND_ACTION_SWIM
- SOUND_ACTION_SWIM_FAST
- SOUND_ACTION_TELEPORT
- SOUND_ACTION_TERRAIN_BODY_HIT_GROUND
- SOUND_ACTION_TERRAIN_HEAVY_LANDING
- SOUND_ACTION_TERRAIN_JUMP
- SOUND_ACTION_TERRAIN_LANDING
- SOUND_ACTION_TERRAIN_STEP
- SOUND_ACTION_TERRAIN_STEP_TIPTOE
- SOUND_ACTION_TERRAIN_STUCK_IN_GROUND
- SOUND_ACTION_THROW
- SOUND_ACTION_TWIRL
- SOUND_ACTION_UNK3C
- SOUND_ACTION_UNK53
- SOUND_ACTION_UNK54
- SOUND_ACTION_UNK55
- SOUND_ACTION_UNK5D
- SOUND_ACTION_UNKNOWN430
- SOUND_ACTION_UNKNOWN431
- SOUND_ACTION_UNKNOWN432
- SOUND_ACTION_UNKNOWN434
- SOUND_ACTION_UNKNOWN43D
- SOUND_ACTION_UNKNOWN43E
- SOUND_ACTION_UNKNOWN458
- SOUND_ACTION_UNKNOWN45C
- SOUND_ACTION_UNSTUCK_FROM_GROUND
- SOUND_AIR_AMP_BUZZ
- SOUND_AIR_BLOW_FIRE
- SOUND_AIR_BLOW_WIND
- SOUND_AIR_BOBOMB_LIT_FUSE
- SOUND_AIR_BOWSER_SPIT_FIRE
- SOUND_AIR_CASTLE_OUTDOORS_AMBIENT
- SOUND_AIR_CHUCKYA_MOVE
- SOUND_AIR_HEAVEHO_MOVE
- SOUND_AIR_HOWLING_WIND
- SOUND_AIR_LAKITU_FLY
- SOUND_AIR_LAKITU_FLY_HIGHPRIO
- SOUND_AIR_PEACH_TWINKLE
- SOUND_AIR_ROUGH_SLIDE
- SOUND_AIR_UNK01
- SOUND_AIR_UNK07
- SOUND_BANKS_ALL
- SOUND_BANKS_ALL_BITS
- SOUND_BANKS_BACKGROUND
- SOUND_BANKS_DISABLED_AFTER_CREDITS
- SOUND_BANKS_DISABLED_DURING_INTRO_CUTSCENE
- SOUND_BANKS_FOREGROUND
- SOUND_BANK_ACTION
- SOUND_BANK_AIR
- SOUND_BANK_COUNT
- SOUND_BANK_ENV
- SOUND_BANK_GENERAL
- SOUND_BANK_GENERAL2
- SOUND_BANK_LUIGI_VOICE
- SOUND_BANK_MARIO_VOICE
- SOUND_BANK_MENU
- SOUND_BANK_MOVING
- SOUND_BANK_OBJ
- SOUND_BANK_OBJ2
- SOUND_BANK_TOAD_VOICE
- SOUND_BANK_WARIO_VOICE
- SOUND_CONSTANT_FREQUENCY
- SOUND_DISCRETE
- SOUND_ENV_BOAT_ROCKING1
- SOUND_ENV_DRONING1
- SOUND_ENV_DRONING2
- SOUND_ENV_ELEVATOR1
- SOUND_ENV_ELEVATOR2
- SOUND_ENV_ELEVATOR3
- SOUND_ENV_ELEVATOR4
- SOUND_ENV_ELEVATOR4_2
- SOUND_ENV_MERRY_GO_ROUND_CREAKING
- SOUND_ENV_METAL_BOX_PUSH
- SOUND_ENV_MOVINGSAND
- SOUND_ENV_MOVING_SAND_SNOW
- SOUND_ENV_SINK_QUICKSAND
- SOUND_ENV_SLIDING
- SOUND_ENV_STAR
- SOUND_ENV_UNK07
- SOUND_ENV_UNK12
- SOUND_ENV_UNKNOWN2
- SOUND_ENV_UNKNOWN4
- SOUND_ENV_WATER
- SOUND_ENV_WATERFALL1
- SOUND_ENV_WATERFALL2
- SOUND_ENV_WATER_DRAIN
- SOUND_ENV_WIND1
- SOUND_ENV_WIND2
- SOUND_GENERAL2_1UP_APPEAR
- SOUND_GENERAL2_BIRD_CHIRP2
- SOUND_GENERAL2_BOBOMB_EXPLOSION
- SOUND_GENERAL2_BOWSER_EXPLODE
- SOUND_GENERAL2_BOWSER_KEY
- SOUND_GENERAL2_PURPLE_SWITCH
- SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION
- SOUND_GENERAL2_PYRAMID_TOP_SPIN
- SOUND_GENERAL2_RIGHT_ANSWER
- SOUND_GENERAL2_ROTATING_BLOCK_ALERT
- SOUND_GENERAL2_ROTATING_BLOCK_CLICK
- SOUND_GENERAL2_SPINDEL_ROLL
- SOUND_GENERAL2_STAR_APPEARS
- SOUND_GENERAL2_SWITCH_TICK_FAST
- SOUND_GENERAL2_SWITCH_TICK_SLOW
- SOUND_GENERAL_ACTIVATE_CAP_SWITCH
- SOUND_GENERAL_BIG_CLOCK
- SOUND_GENERAL_BIG_POUND
- SOUND_GENERAL_BIRDS_FLY_AWAY
- SOUND_GENERAL_BOAT_ROCK
- SOUND_GENERAL_BOAT_TILT1
- SOUND_GENERAL_BOAT_TILT2
- SOUND_GENERAL_BOING1
- SOUND_GENERAL_BOING2
- SOUND_GENERAL_BOING2_LOWPRIO
- SOUND_GENERAL_BOING3
- SOUND_GENERAL_BOWSER_BOMB_EXPLOSION
- SOUND_GENERAL_BOWSER_PLATFORM
- SOUND_GENERAL_BOWSER_PLATFORM_2
- SOUND_GENERAL_BOX_LANDING
- SOUND_GENERAL_BOX_LANDING_2
- SOUND_GENERAL_BREAK_BOX
- SOUND_GENERAL_BUBBLES
- SOUND_GENERAL_BUTTON_PRESS
- SOUND_GENERAL_BUTTON_PRESS_2
- SOUND_GENERAL_BUTTON_PRESS_2_LOWPRIO
- SOUND_GENERAL_BUTTON_PRESS_LOWPRIO
- SOUND_GENERAL_CAGE_OPEN
- SOUND_GENERAL_CANNON_UP
- SOUND_GENERAL_CASTLE_TRAP_OPEN
- SOUND_GENERAL_CHAIN_CHOMP1
- SOUND_GENERAL_CHAIN_CHOMP2
- SOUND_GENERAL_CLAM_SHELL1
- SOUND_GENERAL_CLAM_SHELL2
- SOUND_GENERAL_CLAM_SHELL3
- SOUND_GENERAL_CLOSE_IRON_DOOR
- SOUND_GENERAL_CLOSE_WOOD_DOOR
- SOUND_GENERAL_COIN
- SOUND_GENERAL_COIN_DROP
- SOUND_GENERAL_COIN_SPURT
- SOUND_GENERAL_COIN_SPURT_2
- SOUND_GENERAL_COIN_SPURT_EU
- SOUND_GENERAL_COIN_WATER
- SOUND_GENERAL_COLLECT_1UP
- SOUND_GENERAL_DONUT_PLATFORM_EXPLOSION
- SOUND_GENERAL_DOOR_INSERT_KEY
- SOUND_GENERAL_DOOR_TURN_KEY
- SOUND_GENERAL_ELEVATOR_MOVE
- SOUND_GENERAL_ELEVATOR_MOVE_2
- SOUND_GENERAL_ENEMY_ALERT1
- SOUND_GENERAL_EXPLOSION6
- SOUND_GENERAL_EXPLOSION7
- SOUND_GENERAL_FLAME_OUT
- SOUND_GENERAL_GRAND_STAR
- SOUND_GENERAL_GRAND_STAR_JUMP
- SOUND_GENERAL_GRINDEL_ROLL
- SOUND_GENERAL_HAUNTED_CHAIR
- SOUND_GENERAL_HAUNTED_CHAIR_MOVE
- SOUND_GENERAL_HEART_SPIN
- SOUND_GENERAL_LEVEL_SELECT_CHANGE
- SOUND_GENERAL_LOUD_POUND
- SOUND_GENERAL_LOUD_POUND2
- SOUND_GENERAL_METAL_POUND
- SOUND_GENERAL_MOVING_IN_SAND
- SOUND_GENERAL_MOVING_PLATFORM_SWITCH
- SOUND_GENERAL_MOVING_WATER
- SOUND_GENERAL_OPEN_CHEST
- SOUND_GENERAL_OPEN_IRON_DOOR
- SOUND_GENERAL_OPEN_WOOD_DOOR
- SOUND_GENERAL_PAINTING_EJECT
- SOUND_GENERAL_PENDULUM_SWING
- SOUND_GENERAL_PLATFORM
- SOUND_GENERAL_POUND_ROCK
- SOUND_GENERAL_POUND_WOOD_POST
- SOUND_GENERAL_QUIET_BUBBLE
- SOUND_GENERAL_QUIET_BUBBLE2
- SOUND_GENERAL_QUIET_POUND1
- SOUND_GENERAL_QUIET_POUND1_LOWPRIO
- SOUND_GENERAL_QUIET_POUND2
- SOUND_GENERAL_RACE_GUN_SHOT
- SOUND_GENERAL_RED_COIN
- SOUND_GENERAL_SHAKE_COFFIN
- SOUND_GENERAL_SHORT_POUND1
- SOUND_GENERAL_SHORT_POUND2
- SOUND_GENERAL_SHORT_POUND3
- SOUND_GENERAL_SHORT_POUND4
- SOUND_GENERAL_SHORT_POUND5
- SOUND_GENERAL_SHORT_POUND6
- SOUND_GENERAL_SHORT_STAR
- SOUND_GENERAL_SOFT_LANDING
- SOUND_GENERAL_SPLATTERING
- SOUND_GENERAL_STAR_APPEARS
- SOUND_GENERAL_STAR_DOOR_CLOSE
- SOUND_GENERAL_STAR_DOOR_OPEN
- SOUND_GENERAL_SWISH_AIR
- SOUND_GENERAL_SWISH_AIR_2
- SOUND_GENERAL_SWISH_WATER
- SOUND_GENERAL_SWITCH_DOOR_OPEN
- SOUND_GENERAL_UNK32
- SOUND_GENERAL_UNK45
- SOUND_GENERAL_UNK46
- SOUND_GENERAL_UNK46_LOWPRIO
- SOUND_GENERAL_UNKNOWN1
- SOUND_GENERAL_UNKNOWN1_2
- SOUND_GENERAL_UNKNOWN3
- SOUND_GENERAL_UNKNOWN3_2
- SOUND_GENERAL_UNKNOWN3_LOWPRIO
- SOUND_GENERAL_UNKNOWN4
- SOUND_GENERAL_UNKNOWN4_LOWPRIO
- SOUND_GENERAL_VANISH_SFX
- SOUND_GENERAL_VOLCANO_EXPLOSION
- SOUND_GENERAL_WALL_EXPLOSION
- SOUND_GENERAL_WATER_LEVEL_TRIG
- SOUND_GENERAL_YOSHI_TALK
- SOUND_GENERAL_YOSHI_WALK
- SOUND_LOWER_BACKGROUND_MUSIC
- SOUND_MARIO_ATTACKED
- SOUND_MARIO_COUGHING1
- SOUND_MARIO_COUGHING2
- SOUND_MARIO_COUGHING3
- SOUND_MARIO_DOH
- SOUND_MARIO_DROWNING
- SOUND_MARIO_DYING
- SOUND_MARIO_EEUH
- SOUND_MARIO_GAME_OVER
- SOUND_MARIO_GROUND_POUND_WAH
- SOUND_MARIO_HAHA
- SOUND_MARIO_HAHA_2
- SOUND_MARIO_HELLO
- SOUND_MARIO_HERE_WE_GO
- SOUND_MARIO_HOOHOO
- SOUND_MARIO_HRMM
- SOUND_MARIO_IMA_TIRED
- SOUND_MARIO_LETS_A_GO
- SOUND_MARIO_MAMA_MIA
- SOUND_MARIO_OKEY_DOKEY
- SOUND_MARIO_ON_FIRE
- SOUND_MARIO_OOOF
- SOUND_MARIO_OOOF2
- SOUND_MARIO_PANTING
- SOUND_MARIO_PANTING_COLD
- SOUND_MARIO_PRESS_START_TO_PLAY
- SOUND_MARIO_PUNCH_HOO
- SOUND_MARIO_PUNCH_WAH
- SOUND_MARIO_PUNCH_YAH
- SOUND_MARIO_SNORING1
- SOUND_MARIO_SNORING2
- SOUND_MARIO_SNORING3
- SOUND_MARIO_SO_LONGA_BOWSER
- SOUND_MARIO_TWIRL_BOUNCE
- SOUND_MARIO_UH
- SOUND_MARIO_UH2
- SOUND_MARIO_UH2_2
- SOUND_MARIO_WAAAOOOW
- SOUND_MARIO_WAH2
- SOUND_MARIO_WHOA
- SOUND_MARIO_YAHOO
- SOUND_MARIO_YAHOO_WAHA_YIPPEE
- SOUND_MARIO_YAH_WAH_HOO
- SOUND_MARIO_YAWNING
- SOUND_MENU_BOWSER_LAUGH
- SOUND_MENU_CAMERA_BUZZ
- SOUND_MENU_CAMERA_TURN
- SOUND_MENU_CAMERA_UNUSED1
- SOUND_MENU_CAMERA_UNUSED2
- SOUND_MENU_CAMERA_ZOOM_IN
- SOUND_MENU_CAMERA_ZOOM_OUT
- SOUND_MENU_CHANGE_SELECT
- SOUND_MENU_CLICK_CHANGE_VIEW
- SOUND_MENU_CLICK_FILE_SELECT
- SOUND_MENU_COIN_ITS_A_ME_MARIO
- SOUND_MENU_COLLECT_RED_COIN
- SOUND_MENU_COLLECT_SECRET
- SOUND_MENU_ENTER_HOLE
- SOUND_MENU_ENTER_PIPE
- SOUND_MENU_EXIT_A_SIGN
- SOUND_MENU_EXIT_PIPE
- SOUND_MENU_HAND_APPEAR
- SOUND_MENU_HAND_DISAPPEAR
- SOUND_MENU_LET_GO_MARIO_FACE
- SOUND_MENU_MARIO_CASTLE_WARP
- SOUND_MENU_MARIO_CASTLE_WARP2
- SOUND_MENU_MESSAGE_APPEAR
- SOUND_MENU_MESSAGE_DISAPPEAR
- SOUND_MENU_MESSAGE_NEXT_PAGE
- SOUND_MENU_PAUSE
- SOUND_MENU_PAUSE_2
- SOUND_MENU_PAUSE_HIGHPRIO
- SOUND_MENU_PINCH_MARIO_FACE
- SOUND_MENU_POWER_METER
- SOUND_MENU_READ_A_SIGN
- SOUND_MENU_REVERSE_PAUSE
- SOUND_MENU_STAR_SOUND
- SOUND_MENU_STAR_SOUND_LETS_A_GO
- SOUND_MENU_STAR_SOUND_OKEY_DOKEY
- SOUND_MENU_THANK_YOU_PLAYING_MY_GAME
- SOUND_MENU_UNK0C
- SOUND_MENU_UNK10
- SOUND_MENU_YOSHI_GAIN_LIVES
- SOUND_MOVING_AIM_CANNON
- SOUND_MOVING_ALMOST_DROWNING
- SOUND_MOVING_FLYING
- SOUND_MOVING_LAVA_BURN
- SOUND_MOVING_QUICKSAND_DEATH
- SOUND_MOVING_RIDING_SHELL_LAVA
- SOUND_MOVING_SHOCKED
- SOUND_MOVING_SLIDE_DOWN_POLE
- SOUND_MOVING_SLIDE_DOWN_TREE
- SOUND_MOVING_TERRAIN_RIDING_SHELL
- SOUND_MOVING_TERRAIN_SLIDE
- SOUND_MOVING_UNK1A
- SOUND_NO_ECHO
- SOUND_NO_PRIORITY_LOSS
- SOUND_NO_VOLUME_LOSS
- SOUND_OBJ2_BABY_PENGUIN_YELL
- SOUND_OBJ2_BIRD_CHIRP1
- SOUND_OBJ2_BOSS_DIALOG_GRUNT
- SOUND_OBJ2_BOWSER_PUZZLE_PIECE_MOVE
- SOUND_OBJ2_BOWSER_ROAR
- SOUND_OBJ2_BOWSER_TELEPORT
- SOUND_OBJ2_BULLY_ATTACKED
- SOUND_OBJ2_EYEROK_SOUND_LONG
- SOUND_OBJ2_EYEROK_SOUND_SHORT
- SOUND_OBJ2_KING_BOBOMB_DAMAGE
- SOUND_OBJ2_LARGE_BULLY_ATTACKED
- SOUND_OBJ2_MONTY_MOLE_APPEAR
- SOUND_OBJ2_MRI_SPINNING
- SOUND_OBJ2_PIRANHA_PLANT_BITE
- SOUND_OBJ2_PIRANHA_PLANT_DYING
- SOUND_OBJ2_SCUTTLEBUG_ALERT
- SOUND_OBJ2_SCUTTLEBUG_WALK
- SOUND_OBJ2_SWOOP
- SOUND_OBJ2_WHOMP_SOUND_SHORT
- SOUND_OBJ_BABY_PENGUIN_DIVE
- SOUND_OBJ_BABY_PENGUIN_WALK
- SOUND_OBJ_BIG_PENGUIN_WALK
- SOUND_OBJ_BIG_PENGUIN_YELL
- SOUND_OBJ_BIRD_CHIRP3
- SOUND_OBJ_BOBOMB_BUDDY_TALK
- SOUND_OBJ_BOBOMB_WALK
- SOUND_OBJ_BOO_BOUNCE_TOP
- SOUND_OBJ_BOO_LAUGH_LONG
- SOUND_OBJ_BOO_LAUGH_SHORT
- SOUND_OBJ_BOWSER_DEFEATED
- SOUND_OBJ_BOWSER_INHALING
- SOUND_OBJ_BOWSER_INTRO_LAUGH
- SOUND_OBJ_BOWSER_LAUGH
- SOUND_OBJ_BOWSER_SPINNING
- SOUND_OBJ_BOWSER_TAIL_PICKUP
- SOUND_OBJ_BOWSER_WALK
- SOUND_OBJ_BUBBA_CHOMP
- SOUND_OBJ_BULLY_EXPLODE
- SOUND_OBJ_BULLY_EXPLODE_2
- SOUND_OBJ_BULLY_METAL
- SOUND_OBJ_BULLY_WALK
- SOUND_OBJ_BULLY_WALKING
- SOUND_OBJ_CANNON1
- SOUND_OBJ_CANNON2
- SOUND_OBJ_CANNON3
- SOUND_OBJ_CANNON4
- SOUND_OBJ_CHUCKYA_DEATH
- SOUND_OBJ_DEFAULT_DEATH
- SOUND_OBJ_DIVING_INTO_WATER
- SOUND_OBJ_DIVING_IN_WATER
- SOUND_OBJ_DORRIE
- SOUND_OBJ_DYING_ENEMY1
- SOUND_OBJ_DYING_ENEMY2
- SOUND_OBJ_EEL
- SOUND_OBJ_EEL_2
- SOUND_OBJ_ENEMY_DEATH_HIGH
- SOUND_OBJ_ENEMY_DEATH_LOW
- SOUND_OBJ_ENEMY_DEFEAT_SHRINK
- SOUND_OBJ_EVIL_LAKITU_THROW
- SOUND_OBJ_EYEROK_EXPLODE
- SOUND_OBJ_EYEROK_SHOW_EYE
- SOUND_OBJ_FLAME_BLOWN
- SOUND_OBJ_GOOMBA_ALERT
- SOUND_OBJ_GOOMBA_WALK
- SOUND_OBJ_HEAVEHO_TOSSED
- SOUND_OBJ_JUMP_WALK_WATER
- SOUND_OBJ_KING_BOBOMB
- SOUND_OBJ_KING_BOBOMB_JUMP
- SOUND_OBJ_KING_BOBOMB_TALK
- SOUND_OBJ_KING_WHOMP_DEATH
- SOUND_OBJ_KLEPTO1
- SOUND_OBJ_KLEPTO2
- SOUND_OBJ_KOOPA_DAMAGE
- SOUND_OBJ_KOOPA_FLYGUY_DEATH
- SOUND_OBJ_KOOPA_TALK
- SOUND_OBJ_KOOPA_THE_QUICK_WALK
- SOUND_OBJ_KOOPA_WALK
- SOUND_OBJ_MAD_PIANO_CHOMPING
- SOUND_OBJ_MIPS_RABBIT
- SOUND_OBJ_MIPS_RABBIT_WATER
- SOUND_OBJ_MONTY_MOLE_ATTACK
- SOUND_OBJ_MRI_DEATH
- SOUND_OBJ_MRI_SHOOT
- SOUND_OBJ_MR_BLIZZARD_ALERT
- SOUND_OBJ_PIRANHA_PLANT_APPEAR
- SOUND_OBJ_PIRANHA_PLANT_SHRINK
- SOUND_OBJ_POKEY_DEATH
- SOUND_OBJ_POUNDING1
- SOUND_OBJ_POUNDING1_HIGHPRIO
- SOUND_OBJ_POUNDING_CANNON
- SOUND_OBJ_POUNDING_LOUD
- SOUND_OBJ_SKEETER_WALK
- SOUND_OBJ_SNOWMAN_BOUNCE
- SOUND_OBJ_SNOWMAN_EXPLODE
- SOUND_OBJ_SNOW_SAND1
- SOUND_OBJ_SNOW_SAND2
- SOUND_OBJ_SNUFIT_SHOOT
- SOUND_OBJ_SNUFIT_SKEETER_DEATH
- SOUND_OBJ_SOMETHING_LANDING
- SOUND_OBJ_SPINY_UNK59
- SOUND_OBJ_STOMPED
- SOUND_OBJ_SUSHI_SHARK_WATER_SOUND
- SOUND_OBJ_SWOOP_DEATH
- SOUND_OBJ_THWOMP
- SOUND_OBJ_UKIKI_CHATTER_IDLE
- SOUND_OBJ_UKIKI_CHATTER_LONG
- SOUND_OBJ_UKIKI_CHATTER_SHORT
- SOUND_OBJ_UKIKI_STEP_DEFAULT
- SOUND_OBJ_UKIKI_STEP_LEAVES
- SOUND_OBJ_UNK23
- SOUND_OBJ_UNKNOWN2
- SOUND_OBJ_UNKNOWN3
- SOUND_OBJ_UNKNOWN4
- SOUND_OBJ_UNKNOWN6
- SOUND_OBJ_WALKING_WATER
- SOUND_OBJ_WATER_BOMB_BOUNCING
- SOUND_OBJ_WHOMP_LOWPRIO
- SOUND_OBJ_WIGGLER_ATTACKED
- SOUND_OBJ_WIGGLER_DEATH
- SOUND_OBJ_WIGGLER_HIGH_PITCH
- SOUND_OBJ_WIGGLER_JUMP
- SOUND_OBJ_WIGGLER_LOW_PITCH
- SOUND_OBJ_WIGGLER_TALK
- SOUND_PEACH_BAKE_A_CAKE
- SOUND_PEACH_DEAR_MARIO
- SOUND_PEACH_FOR_MARIO
- SOUND_PEACH_MARIO
- SOUND_PEACH_MARIO2
- SOUND_PEACH_POWER_OF_THE_STARS
- SOUND_PEACH_SOMETHING_SPECIAL
- SOUND_PEACH_THANKS_TO_YOU
- SOUND_PEACH_THANK_YOU_MARIO
- SOUND_STATUS_PLAYING
- SOUND_STATUS_STOPPED
- SOUND_STATUS_WAITING
- SOUND_TERRAIN_DEFAULT
- SOUND_TERRAIN_GRASS
- SOUND_TERRAIN_ICE
- SOUND_TERRAIN_SAND
- SOUND_TERRAIN_SNOW
- SOUND_TERRAIN_SPOOKY
- SOUND_TERRAIN_STONE
- SOUND_TERRAIN_WATER
- SOUND_VIBRATO

[:arrow_up_small:](#)

<br />

## [surface_terrains.h](#surface_terrains.h)
- HAZARD_TYPE_LAVA_FLOOR
- HAZARD_TYPE_LAVA_WALL
- HAZARD_TYPE_QUICKSAND
- SURFACE_0004
- SURFACE_BOSS_FIGHT_CAMERA
- SURFACE_BURNING
- SURFACE_CAMERA_8_DIR
- SURFACE_CAMERA_BOUNDARY
- SURFACE_CAMERA_FREE_ROAM
- SURFACE_CAMERA_MIDDLE
- SURFACE_CAMERA_ROTATE_LEFT
- SURFACE_CAMERA_ROTATE_RIGHT
- SURFACE_CLASS_DEFAULT
- SURFACE_CLASS_NOT_SLIPPERY
- SURFACE_CLASS_SLIPPERY
- SURFACE_CLASS_VERY_SLIPPERY
- SURFACE_CLOSE_CAMERA
- SURFACE_DEATH_PLANE
- SURFACE_DEEP_MOVING_QUICKSAND
- SURFACE_DEEP_QUICKSAND
- SURFACE_DEFAULT
- SURFACE_FLAG_DYNAMIC
- SURFACE_FLAG_NO_CAM_COLLISION
- SURFACE_FLAG_X_PROJECTION
- SURFACE_FLOWING_WATER
- SURFACE_HANGABLE
- SURFACE_HARD
- SURFACE_HARD_NOT_SLIPPERY
- SURFACE_HARD_SLIPPERY
- SURFACE_HARD_VERY_SLIPPERY
- SURFACE_HORIZONTAL_WIND
- SURFACE_ICE
- SURFACE_INSTANT_MOVING_QUICKSAND
- SURFACE_INSTANT_QUICKSAND
- SURFACE_INSTANT_WARP_1B
- SURFACE_INSTANT_WARP_1C
- SURFACE_INSTANT_WARP_1D
- SURFACE_INSTANT_WARP_1E
- SURFACE_INTANGIBLE
- SURFACE_LOOK_UP_WARP
- SURFACE_MGR_MUSIC
- SURFACE_MOVING_QUICKSAND
- SURFACE_NOISE_DEFAULT
- SURFACE_NOISE_SLIPPERY
- SURFACE_NOISE_VERY_SLIPPERY
- SURFACE_NOISE_VERY_SLIPPERY_73
- SURFACE_NOISE_VERY_SLIPPERY_74
- SURFACE_NOT_SLIPPERY
- SURFACE_NO_CAM_COLLISION
- SURFACE_NO_CAM_COLLISION_77
- SURFACE_NO_CAM_COL_SLIPPERY
- SURFACE_NO_CAM_COL_VERY_SLIPPERY
- SURFACE_PAINTING_WARP_D3
- SURFACE_PAINTING_WARP_D4
- SURFACE_PAINTING_WARP_D5
- SURFACE_PAINTING_WARP_D6
- SURFACE_PAINTING_WARP_D7
- SURFACE_PAINTING_WARP_D8
- SURFACE_PAINTING_WARP_D9
- SURFACE_PAINTING_WARP_DA
- SURFACE_PAINTING_WARP_DB
- SURFACE_PAINTING_WARP_DC
- SURFACE_PAINTING_WARP_DD
- SURFACE_PAINTING_WARP_DE
- SURFACE_PAINTING_WARP_DF
- SURFACE_PAINTING_WARP_E0
- SURFACE_PAINTING_WARP_E1
- SURFACE_PAINTING_WARP_E2
- SURFACE_PAINTING_WARP_E3
- SURFACE_PAINTING_WARP_E4
- SURFACE_PAINTING_WARP_E5
- SURFACE_PAINTING_WARP_E6
- SURFACE_PAINTING_WARP_E7
- SURFACE_PAINTING_WARP_E8
- SURFACE_PAINTING_WARP_E9
- SURFACE_PAINTING_WARP_EA
- SURFACE_PAINTING_WARP_EB
- SURFACE_PAINTING_WARP_EC
- SURFACE_PAINTING_WARP_ED
- SURFACE_PAINTING_WARP_EE
- SURFACE_PAINTING_WARP_EF
- SURFACE_PAINTING_WARP_F0
- SURFACE_PAINTING_WARP_F1
- SURFACE_PAINTING_WARP_F2
- SURFACE_PAINTING_WARP_F3
- SURFACE_PAINTING_WARP_F7
- SURFACE_PAINTING_WARP_F8
- SURFACE_PAINTING_WARP_F9
- SURFACE_PAINTING_WARP_FA
- SURFACE_PAINTING_WARP_FB
- SURFACE_PAINTING_WARP_FC
- SURFACE_PAINTING_WOBBLE_A6
- SURFACE_PAINTING_WOBBLE_A7
- SURFACE_PAINTING_WOBBLE_A8
- SURFACE_PAINTING_WOBBLE_A9
- SURFACE_PAINTING_WOBBLE_AA
- SURFACE_PAINTING_WOBBLE_AB
- SURFACE_PAINTING_WOBBLE_AC
- SURFACE_PAINTING_WOBBLE_AD
- SURFACE_PAINTING_WOBBLE_AE
- SURFACE_PAINTING_WOBBLE_AF
- SURFACE_PAINTING_WOBBLE_B0
- SURFACE_PAINTING_WOBBLE_B1
- SURFACE_PAINTING_WOBBLE_B2
- SURFACE_PAINTING_WOBBLE_B3
- SURFACE_PAINTING_WOBBLE_B4
- SURFACE_PAINTING_WOBBLE_B5
- SURFACE_PAINTING_WOBBLE_B6
- SURFACE_PAINTING_WOBBLE_B7
- SURFACE_PAINTING_WOBBLE_B8
- SURFACE_PAINTING_WOBBLE_B9
- SURFACE_PAINTING_WOBBLE_BA
- SURFACE_PAINTING_WOBBLE_BB
- SURFACE_PAINTING_WOBBLE_BC
- SURFACE_PAINTING_WOBBLE_BD
- SURFACE_PAINTING_WOBBLE_BE
- SURFACE_PAINTING_WOBBLE_BF
- SURFACE_PAINTING_WOBBLE_C0
- SURFACE_PAINTING_WOBBLE_C1
- SURFACE_PAINTING_WOBBLE_C2
- SURFACE_PAINTING_WOBBLE_C3
- SURFACE_PAINTING_WOBBLE_C4
- SURFACE_PAINTING_WOBBLE_C5
- SURFACE_PAINTING_WOBBLE_C6
- SURFACE_PAINTING_WOBBLE_C7
- SURFACE_PAINTING_WOBBLE_C8
- SURFACE_PAINTING_WOBBLE_C9
- SURFACE_PAINTING_WOBBLE_CA
- SURFACE_PAINTING_WOBBLE_CB
- SURFACE_PAINTING_WOBBLE_CC
- SURFACE_PAINTING_WOBBLE_CD
- SURFACE_PAINTING_WOBBLE_CE
- SURFACE_PAINTING_WOBBLE_CF
- SURFACE_PAINTING_WOBBLE_D0
- SURFACE_PAINTING_WOBBLE_D1
- SURFACE_PAINTING_WOBBLE_D2
- SURFACE_QUICKSAND
- SURFACE_RAYCAST
- SURFACE_SHALLOW_MOVING_QUICKSAND
- SURFACE_SHALLOW_QUICKSAND
- SURFACE_SLIPPERY
- SURFACE_SLOW
- SURFACE_SWITCH
- SURFACE_THI3_WALLKICK
- SURFACE_TIMER_END
- SURFACE_TIMER_START
- SURFACE_TRAPDOOR
- SURFACE_TTC_PAINTING_1
- SURFACE_TTC_PAINTING_2
- SURFACE_TTC_PAINTING_3
- SURFACE_TTM_VINES
- SURFACE_VANISH_CAP_WALLS
- SURFACE_VERTICAL_WIND
- SURFACE_VERY_SLIPPERY
- SURFACE_WALL_MISC
- SURFACE_WARP
- SURFACE_WATER
- SURFACE_WOBBLING_WARP
- TERRAIN_GRASS
- TERRAIN_LOAD_CONTINUE
- TERRAIN_LOAD_END
- TERRAIN_LOAD_ENVIRONMENT
- TERRAIN_LOAD_OBJECTS
- TERRAIN_LOAD_VERTICES
- TERRAIN_MASK
- TERRAIN_SAND
- TERRAIN_SLIDE
- TERRAIN_SNOW
- TERRAIN_SPOOKY
- TERRAIN_STONE
- TERRAIN_WATER

[:arrow_up_small:](#)

<br />

## [types.h](#types.h)
- ANIM_FLAG_2
- ANIM_FLAG_5
- ANIM_FLAG_6
- ANIM_FLAG_7
- ANIM_FLAG_FORWARD
- ANIM_FLAG_HOR_TRANS
- ANIM_FLAG_NOLOOP
- ANIM_FLAG_VERT_TRANS
- COOP_OBJ_FLAG_INITIALIZED
- COOP_OBJ_FLAG_LUA
- COOP_OBJ_FLAG_NETWORK
- COOP_OBJ_FLAG_NON_SYNC
- GRAPH_NODE_GUARD
- MAX_PLAYERS
- OBJECT_CUSTOM_FIELDS_START
- OBJECT_MAX_BHV_STACK
- OBJECT_NUM_CUSTOM_FIELDS
- OBJECT_NUM_FIELDS
- OBJECT_NUM_REGULAR_FIELDS
- PLAY_MODE_CHANGE_AREA
- PLAY_MODE_CHANGE_LEVEL
- PLAY_MODE_FRAME_ADVANCE
- PLAY_MODE_NORMAL
- PLAY_MODE_PAUSED

### [enum AreaTimerType](#AreaTimerType)
| Identifier | Value |
| :--------- | :---- |
| AREA_TIMER_TYPE_NONE | 0 |
| AREA_TIMER_TYPE_LOOP | 1 |
| AREA_TIMER_TYPE_MAXIMUM | 2 |

### [enum SpTaskState](#SpTaskState)
| Identifier | Value |
| :--------- | :---- |
| SPTASK_STATE_NOT_STARTED | 0 |
| SPTASK_STATE_RUNNING | 1 |
| SPTASK_STATE_INTERRUPTED | 2 |
| SPTASK_STATE_FINISHED | 3 |
| SPTASK_STATE_FINISHED_DP | 4 |

[:arrow_up_small:](#)

<br />

## [version.h](#version.h)
- MAX_VERSION_LENGTH
- MINOR_VERSION_NUMBER
- SM64COOPDX_VERSION
- VERSION_NUMBER
- VERSION_REGION
- VERSION_REGION
- VERSION_REGION
- VERSION_REGION
- VERSION_TEXT

[:arrow_up_small:](#)

<br />

