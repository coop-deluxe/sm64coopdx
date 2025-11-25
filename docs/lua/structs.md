## [:rewind: Lua Reference](lua.md)

# Supported Structs
- [AnimInfo](#AnimInfo)
- [Animation](#Animation)
- [Area](#Area)
- [BehaviorDialogs](#BehaviorDialogs)
- [BehaviorTrajectories](#BehaviorTrajectories)
- [BehaviorValues](#BehaviorValues)
- [Camera](#Camera)
- [ChainSegment](#ChainSegment)
- [Character](#Character)
- [Color](#Color)
- [Controller](#Controller)
- [CustomLevelInfo](#CustomLevelInfo)
- [DateTime](#DateTime)
- [DialogEntry](#DialogEntry)
- [DisplayListNode](#DisplayListNode)
- [DjuiColor](#DjuiColor)
- [DjuiInteractableTheme](#DjuiInteractableTheme)
- [DjuiPanelTheme](#DjuiPanelTheme)
- [DjuiTheme](#DjuiTheme)
- [DjuiThreePanelTheme](#DjuiThreePanelTheme)
- [ExclamationBoxContent](#ExclamationBoxContent)
- [FirstPersonCamera](#FirstPersonCamera)
- [FnGraphNode](#FnGraphNode)
- [Gfx](#Gfx)
- [GlobalObjectAnimations](#GlobalObjectAnimations)
- [GlobalObjectCollisionData](#GlobalObjectCollisionData)
- [GlobalTextures](#GlobalTextures)
- [GraphNode](#GraphNode)
- [GraphNodeAnimatedPart](#GraphNodeAnimatedPart)
- [GraphNodeBackground](#GraphNodeBackground)
- [GraphNodeBillboard](#GraphNodeBillboard)
- [GraphNodeBone](#GraphNodeBone)
- [GraphNodeCamera](#GraphNodeCamera)
- [GraphNodeCullingRadius](#GraphNodeCullingRadius)
- [GraphNodeDisplayList](#GraphNodeDisplayList)
- [GraphNodeGenerated](#GraphNodeGenerated)
- [GraphNodeHeldObject](#GraphNodeHeldObject)
- [GraphNodeLevelOfDetail](#GraphNodeLevelOfDetail)
- [GraphNodeMasterList](#GraphNodeMasterList)
- [GraphNodeObject](#GraphNodeObject)
- [GraphNodeObjectParent](#GraphNodeObjectParent)
- [GraphNodeOrthoProjection](#GraphNodeOrthoProjection)
- [GraphNodePerspective](#GraphNodePerspective)
- [GraphNodeRoot](#GraphNodeRoot)
- [GraphNodeRotation](#GraphNodeRotation)
- [GraphNodeScale](#GraphNodeScale)
- [GraphNodeScaleXYZ](#GraphNodeScaleXYZ)
- [GraphNodeShadow](#GraphNodeShadow)
- [GraphNodeStart](#GraphNodeStart)
- [GraphNodeSwitchCase](#GraphNodeSwitchCase)
- [GraphNodeTranslation](#GraphNodeTranslation)
- [GraphNodeTranslationRotation](#GraphNodeTranslationRotation)
- [HudUtilsRotation](#HudUtilsRotation)
- [InstantWarp](#InstantWarp)
- [LakituState](#LakituState)
- [LevelValues](#LevelValues)
- [MarioAnimation](#MarioAnimation)
- [MarioBodyState](#MarioBodyState)
- [MarioState](#MarioState)
- [Mat4](#Mat4)
- [Mod](#Mod)
- [ModAudio](#ModAudio)
- [ModFs](#ModFs)
- [ModFsFile](#ModFsFile)
- [NametagsSettings](#NametagsSettings)
- [NetworkPlayer](#NetworkPlayer)
- [Object](#Object)
- [ObjectHitbox](#ObjectHitbox)
- [ObjectNode](#ObjectNode)
- [ObjectWarpNode](#ObjectWarpNode)
- [Painting](#Painting)
- [PaintingValues](#PaintingValues)
- [PlayerCameraState](#PlayerCameraState)
- [PlayerPalette](#PlayerPalette)
- [RayIntersectionInfo](#RayIntersectionInfo)
- [RomhackCameraSettings](#RomhackCameraSettings)
- [ServerSettings](#ServerSettings)
- [SpawnInfo](#SpawnInfo)
- [SpawnParticlesInfo](#SpawnParticlesInfo)
- [StarPositions](#StarPositions)
- [StarsNeededForDialog](#StarsNeededForDialog)
- [StaticObjectCollision](#StaticObjectCollision)
- [Surface](#Surface)
- [TextureInfo](#TextureInfo)
- [Vec2f](#Vec2f)
- [Vec2i](#Vec2i)
- [Vec2s](#Vec2s)
- [Vec3f](#Vec3f)
- [Vec3i](#Vec3i)
- [Vec3s](#Vec3s)
- [Vec4f](#Vec4f)
- [Vec4i](#Vec4i)
- [Vec4s](#Vec4s)
- [Vtx](#Vtx)
- [WallCollisionData](#WallCollisionData)
- [WarpNode](#WarpNode)
- [WaterDropletParams](#WaterDropletParams)
- [Waypoint](#Waypoint)
- [Whirlpool](#Whirlpool)

<br />

## [AnimInfo](#AnimInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| curAnim | [Animation](structs.md#Animation) |  |
| prevAnimPtr | [Animation](structs.md#Animation) |  |
| animID | `integer` |  |
| prevAnimID | `integer` |  |
| animFrame | `integer` |  |
| prevAnimFrame | `integer` |  |
| prevAnimFrameTimestamp | `integer` |  |
| animFrameAccelAssist | `integer` |  |
| animAccel | `integer` |  |
| animTimer | `integer` |  |
| animYTrans | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Animation](#Animation)

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | `integer` | read-only |
| animYTransDivisor | `integer` | read-only |
| startFrame | `integer` | read-only |
| loopStart | `integer` | read-only |
| loopEnd | `integer` | read-only |
| values | `Pointer` <`integer`> | read-only |
| index | `Pointer` <`integer`> | read-only |
| length | `integer` | read-only |
| valuesLength | `integer` | read-only |
| indexLength | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [Area](#Area)

| Field | Type | Access |
| ----- | ---- | ------ |
| index | `integer` |  |
| flags | `integer` |  |
| terrainType | `integer` |  |
| root | [GraphNodeRoot](structs.md#GraphNodeRoot) |  |
| terrainData | `Pointer` <`integer`> | read-only |
| surfaceRooms | `Pointer` <`integer`> | read-only |
| macroObjects | `Pointer` <`integer`> | read-only |
| warpNodes | [ObjectWarpNode](structs.md#ObjectWarpNode) | read-only |
| paintingWarpNodes | [WarpNode](structs.md#WarpNode) | read-only |
| instantWarps | [InstantWarp](structs.md#InstantWarp) |  |
| objectSpawnInfos | [SpawnInfo](structs.md#SpawnInfo) | read-only |
| camera | [Camera](structs.md#Camera) |  |
| whirlpools | `Array` <`Whirlpool`> |  |
| dialog | `Array` <`integer`> |  |
| musicParam | `integer` |  |
| musicParam2 | `integer` |  |
| localAreaTimer | `integer` | read-only |
| macroObjectsAltered | `Pointer` <`integer`> | read-only |
| numRedCoins | `integer` |  |
| numSecrets | `integer` |  |
| nextSyncID | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [BehaviorDialogs](#BehaviorDialogs)

| Field | Type | Access |
| ----- | ---- | ------ |
| BobombBuddyBob1Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| BobombBuddyBob2Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| BobombBuddyOther1Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| BobombBuddyOther2Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser1DefeatedDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser1Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser2DefeatedDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser2Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser3Defeated120StarsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser3DefeatedDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Bowser3Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| CapswitchBaseDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| CapswitchMetalDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| CapswitchVanishDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| CapswitchWingDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| CastleEnterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| CollectedStarDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DefaultCutsceneDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeed1StarDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeed30StarsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeed3StarsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeed50StarsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeed70StarsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeed8StarsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| DoorNeedKeyDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| EyerokDefeatedDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| EyerokIntroDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| GhostHuntAfterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| GhostHuntDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| HootIntroDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| HootTiredDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| HundredCoinsDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| IntroPipeDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KeyDoor1DontHaveDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KeyDoor1HaveDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KeyDoor2DontHaveDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KeyDoor2HaveDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KingBobombCheatDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KingBobombDefeatDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KingBobombIntroDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KingWhompDefeatDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KingWhompDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KoopaQuickBobStartDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KoopaQuickBobWinDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KoopaQuickCheatedDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KoopaQuickLostDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KoopaQuickThiStartDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| KoopaQuickThiWinDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| LakituIntroDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| MetalCourseDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Mips1Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| Mips2Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| PeachLetterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| RacingPenguinBigStartDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| RacingPenguinCheatDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| RacingPenguinLostDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| RacingPenguinStartDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| RacingPenguinWinDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| SnowmanHeadAfterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| SnowmanHeadBodyDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| SnowmanHeadDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| SnowmanWindDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| StarCollectionBaseDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| StarDoorDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| ToadStar1AfterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| ToadStar1Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| ToadStar2AfterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| ToadStar2Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| ToadStar3AfterDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| ToadStar3Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| TuxieMotherDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| TuxieMotherBabyFoundDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| TuxieMotherBabyWrongDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| UkikiCageDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| UkikiCapGiveDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| UkikiCapStealDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| UkikiHeldDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| VanishCourseDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| WigglerAttack1Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| WigglerAttack2Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| WigglerAttack3Dialog | [enum DialogId](constants.md#enum-DialogId) |  |
| WigglerDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| WingCourseDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| YoshiDialog | [enum DialogId](constants.md#enum-DialogId) |  |

[:arrow_up_small:](#)

<br />

## [BehaviorTrajectories](#BehaviorTrajectories)

| Field | Type | Access |
| ----- | ---- | ------ |
| KoopaBobTrajectory | `Pointer` <`Trajectory`> |  |
| KoopaThiTrajectory | `Pointer` <`Trajectory`> |  |
| UnagiTrajectory | `Pointer` <`Trajectory`> |  |
| Unagi2Trajectory | `Pointer` <`Trajectory`> |  |
| SnowmanHeadTrajectory | `Pointer` <`Trajectory`> |  |
| RacingPenguinTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallBobTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallBob2Trajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallTtmTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallThiLargeTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallThiSmallTrajectory | `Pointer` <`Trajectory`> |  |
| MipsTrajectory | `Pointer` <`Trajectory`> |  |
| Mips2Trajectory | `Pointer` <`Trajectory`> |  |
| Mips3Trajectory | `Pointer` <`Trajectory`> |  |
| Mips4Trajectory | `Pointer` <`Trajectory`> |  |
| Mips5Trajectory | `Pointer` <`Trajectory`> |  |
| Mips6Trajectory | `Pointer` <`Trajectory`> |  |
| Mips7Trajectory | `Pointer` <`Trajectory`> |  |
| Mips8Trajectory | `Pointer` <`Trajectory`> |  |
| Mips9Trajectory | `Pointer` <`Trajectory`> |  |
| Mips10Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformRrTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformRr2Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformRr3Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformRr4Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformCcmTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformBitfsTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformHmcTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformLllTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformLll2Trajectory | `Pointer` <`Trajectory`> |  |

[:arrow_up_small:](#)

<br />

## [BehaviorValues](#BehaviorValues)

| Field | Type | Access |
| ----- | ---- | ------ |
| KoopaBobAgility | `number` |  |
| KoopaCatchupAgility | `number` |  |
| KoopaThiAgility | `number` |  |
| RacingPenguinBigHeight | `number` |  |
| RacingPenguinBigRadius | `number` |  |
| RacingPenguinHeight | `number` |  |
| RacingPenguinRadius | `number` |  |
| ToadStar1Requirement | `integer` |  |
| ToadStar2Requirement | `integer` |  |
| ToadStar3Requirement | `integer` |  |
| KingBobombFVel | `number` |  |
| KingBobombYawVel | `integer` |  |
| KingBobombHealth | `integer` |  |
| KingWhompHealth | `integer` |  |
| MipsStar1Requirement | `integer` |  |
| MipsStar2Requirement | `integer` |  |
| BowlingBallBobSpeed | `number` |  |
| BowlingBallBob2Speed | `number` |  |
| BowlingBallTtmSpeed | `number` |  |
| BowlingBallThiLargeSpeed | `number` |  |
| BowlingBallThiSmallSpeed | `number` |  |
| GrateStarRequirement | `integer` |  |
| ChillBullyDeathPosY | `number` |  |
| ShowStarMilestones | `integer` |  |
| ShowStarDialog | `integer` |  |
| RespawnShellBoxes | `integer` |  |
| MultipleCapCollection | `integer` |  |
| InfiniteRenderDistance | `integer` |  |
| CourtyardBoosRequirement | `integer` |  |
| starsNeededForDialog | [StarsNeededForDialog](structs.md#StarsNeededForDialog) | read-only |
| dialogs | [BehaviorDialogs](structs.md#BehaviorDialogs) | read-only |
| trajectories | [BehaviorTrajectories](structs.md#BehaviorTrajectories) | read-only |

[:arrow_up_small:](#)

<br />

## [Camera](#Camera)

| Field | Type | Access |
| ----- | ---- | ------ |
| mode | `integer` |  |
| defMode | `integer` |  |
| yaw | `integer` |  |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| unusedVec1 | [Vec3f](structs.md#Vec3f) | read-only |
| areaCenX | `number` |  |
| areaCenZ | `number` |  |
| cutscene | `integer` |  |
| filler31 | `Array` <`integer`> |  |
| nextYaw | `integer` |  |
| filler3C | `Array` <`integer`> |  |
| doorStatus | `integer` |  |
| areaCenY | `number` |  |
| mtx | [Mat4](structs.md#Mat4) | read-only |

[:arrow_up_small:](#)

<br />

## [ChainSegment](#ChainSegment)

| Field | Type | Access |
| ----- | ---- | ------ |
| posX | `number` |  |
| posY | `number` |  |
| posZ | `number` |  |
| pitch | `integer` |  |
| yaw | `integer` |  |
| roll | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Character](#Character)

| Field | Type | Access |
| ----- | ---- | ------ |
| type | [enum CharacterType](constants.md#enum-CharacterType) | read-only |
| name | `string` | read-only |
| hudHead | `integer` | read-only |
| hudHeadTexture | [TextureInfo](structs.md#TextureInfo) | read-only |
| cameraHudHead | `integer` | read-only |
| modelId | `integer` | read-only |
| capModelId | `integer` | read-only |
| capMetalModelId | `integer` | read-only |
| capWingModelId | `integer` | read-only |
| capMetalWingModelId | `integer` | read-only |
| capEnemyLayer | `integer` | read-only |
| capEnemyGfx | `Pointer` <`Gfx`> | read-only |
| capEnemyDecalGfx | `Pointer` <`Gfx`> | read-only |
| torsoRotMult | `number` | read-only |
| animOffsetEnabled | `integer` | read-only |
| animOffsetLowYPoint | `number` | read-only |
| animOffsetFeet | `number` | read-only |
| animOffsetHand | `number` | read-only |
| animSlowLedgeGrab | `integer` | read-only |
| animFallOverBackwards | `integer` | read-only |
| animBackwardAirKb | `integer` | read-only |
| animDyingOnBack | `integer` | read-only |
| animBackflip | `integer` | read-only |
| animClimbUpPole | `integer` | read-only |
| animGrabPoleShort | `integer` | read-only |
| animGrabPoleSwingPart1 | `integer` | read-only |
| animGrabPoleSwingPart2 | `integer` | read-only |
| animHandstandIdle | `integer` | read-only |
| animHandstandJump | `integer` | read-only |
| animStartHandstand | `integer` | read-only |
| animReturnFromHandstand | `integer` | read-only |
| animIdleOnPole | `integer` | read-only |
| animAPose | `integer` | read-only |
| animSkidOnGround | `integer` | read-only |
| animStopSkid | `integer` | read-only |
| animCrouchFromFastLongjump | `integer` | read-only |
| animCrouchFromSlowLongjump | `integer` | read-only |
| animFastLongjump | `integer` | read-only |
| animSlowLongjump | `integer` | read-only |
| animAirborneOnStomach | `integer` | read-only |
| animWalkWithLightObj | `integer` | read-only |
| animRunWithLightObj | `integer` | read-only |
| animSlowWalkWithLightObj | `integer` | read-only |
| animShiveringWarmingHand | `integer` | read-only |
| animShiveringReturnToIdle | `integer` | read-only |
| animShivering | `integer` | read-only |
| animClimbDownLedge | `integer` | read-only |
| animCreditsWaving | `integer` | read-only |
| animCreditsLookUp | `integer` | read-only |
| animCreditsReturnFromLookUp | `integer` | read-only |
| animCreditsRaiseHand | `integer` | read-only |
| animCreditsLowerHand | `integer` | read-only |
| animCreditsTakeOffCap | `integer` | read-only |
| animCreditsStartWalkLookUp | `integer` | read-only |
| animCreditsLookBackThenRun | `integer` | read-only |
| animFinalBowserRaiseHandSpin | `integer` | read-only |
| animFinalBowserWingCapTakeOff | `integer` | read-only |
| animCreditsPeaceSign | `integer` | read-only |
| animStandUpFromLavaBoost | `integer` | read-only |
| animFireLavaBurn | `integer` | read-only |
| animWingCapFly | `integer` | read-only |
| animHangOnOwl | `integer` | read-only |
| animLandOnStomach | `integer` | read-only |
| animAirForwardKb | `integer` | read-only |
| animDyingOnStomach | `integer` | read-only |
| animSuffocating | `integer` | read-only |
| animCoughing | `integer` | read-only |
| animThrowCatchKey | `integer` | read-only |
| animDyingFallOver | `integer` | read-only |
| animIdleOnLedge | `integer` | read-only |
| animFastLedgeGrab | `integer` | read-only |
| animHangOnCeiling | `integer` | read-only |
| animPutCapOn | `integer` | read-only |
| animTakeCapOffThenOn | `integer` | read-only |
| animQuicklyPutCapOn | `integer` | read-only |
| animHeadStuckInGround | `integer` | read-only |
| animGroundPoundLanding | `integer` | read-only |
| animTripleJumpGroundPound | `integer` | read-only |
| animStartGroundPound | `integer` | read-only |
| animGroundPound | `integer` | read-only |
| animBottomStuckInGround | `integer` | read-only |
| animIdleWithLightObj | `integer` | read-only |
| animJumpLandWithLightObj | `integer` | read-only |
| animJumpWithLightObj | `integer` | read-only |
| animFallLandWithLightObj | `integer` | read-only |
| animFallWithLightObj | `integer` | read-only |
| animFallFromSlidingWithLightObj | `integer` | read-only |
| animSlidingOnBottomWithLightObj | `integer` | read-only |
| animStandUpFromSlidingWithLightObj | `integer` | read-only |
| animRidingShell | `integer` | read-only |
| animWalking | `integer` | read-only |
| animForwardFlip | `integer` | read-only |
| animJumpRidingShell | `integer` | read-only |
| animLandFromDoubleJump | `integer` | read-only |
| animDoubleJumpFall | `integer` | read-only |
| animSingleJump | `integer` | read-only |
| animLandFromSingleJump | `integer` | read-only |
| animAirKick | `integer` | read-only |
| animDoubleJumpRise | `integer` | read-only |
| animStartForwardSpinning | `integer` | read-only |
| animThrowLightObject | `integer` | read-only |
| animFallFromSlideKick | `integer` | read-only |
| animBendKnessRidingShell | `integer` | read-only |
| animLegsStuckInGround | `integer` | read-only |
| animGeneralFall | `integer` | read-only |
| animGeneralLand | `integer` | read-only |
| animBeingGrabbed | `integer` | read-only |
| animGrabHeavyObject | `integer` | read-only |
| animSlowLandFromDive | `integer` | read-only |
| animFlyFromCannon | `integer` | read-only |
| animMoveOnWireNetRight | `integer` | read-only |
| animMoveOnWireNetLeft | `integer` | read-only |
| animMissingCap | `integer` | read-only |
| animPullDoorWalkIn | `integer` | read-only |
| animPushDoorWalkIn | `integer` | read-only |
| animUnlockDoor | `integer` | read-only |
| animStartReachPocket | `integer` | read-only |
| animReachPocket | `integer` | read-only |
| animStopReachPocket | `integer` | read-only |
| animGroundThrow | `integer` | read-only |
| animGroundKick | `integer` | read-only |
| animFirstPunch | `integer` | read-only |
| animSecondPunch | `integer` | read-only |
| animFirstPunchFast | `integer` | read-only |
| animSecondPunchFast | `integer` | read-only |
| animPickUpLightObj | `integer` | read-only |
| animPushing | `integer` | read-only |
| animStartRidingShell | `integer` | read-only |
| animPlaceLightObj | `integer` | read-only |
| animForwardSpinning | `integer` | read-only |
| animBackwardSpinning | `integer` | read-only |
| animBreakdance | `integer` | read-only |
| animRunning | `integer` | read-only |
| animRunningUnused | `integer` | read-only |
| animSoftBackKb | `integer` | read-only |
| animSoftFrontKb | `integer` | read-only |
| animDyingInQuicksand | `integer` | read-only |
| animIdleInQuicksand | `integer` | read-only |
| animMoveInQuicksand | `integer` | read-only |
| animElectrocution | `integer` | read-only |
| animShocked | `integer` | read-only |
| animBackwardKb | `integer` | read-only |
| animForwardKb | `integer` | read-only |
| animIdleHeavyObj | `integer` | read-only |
| animStandAgainstWall | `integer` | read-only |
| animSidestepLeft | `integer` | read-only |
| animSidestepRight | `integer` | read-only |
| animStartSleepIdle | `integer` | read-only |
| animStartSleepScratch | `integer` | read-only |
| animStartSleepYawn | `integer` | read-only |
| animStartSleepSitting | `integer` | read-only |
| animSleepIdle | `integer` | read-only |
| animSleepStartLying | `integer` | read-only |
| animSleepLying | `integer` | read-only |
| animDive | `integer` | read-only |
| animSlideDive | `integer` | read-only |
| animGroundBonk | `integer` | read-only |
| animStopSlideLightObj | `integer` | read-only |
| animSlideKick | `integer` | read-only |
| animCrouchFromSlideKick | `integer` | read-only |
| animSlideMotionless | `integer` | read-only |
| animStopSlide | `integer` | read-only |
| animFallFromSlide | `integer` | read-only |
| animSlide | `integer` | read-only |
| animTiptoe | `integer` | read-only |
| animTwirlLand | `integer` | read-only |
| animTwirl | `integer` | read-only |
| animStartTwirl | `integer` | read-only |
| animStopCrouching | `integer` | read-only |
| animStartCrouching | `integer` | read-only |
| animCrouching | `integer` | read-only |
| animCrawling | `integer` | read-only |
| animStopCrawling | `integer` | read-only |
| animStartCrawling | `integer` | read-only |
| animSummonStar | `integer` | read-only |
| animReturnStarApproachDoor | `integer` | read-only |
| animBackwardsWaterKb | `integer` | read-only |
| animSwimWithObjPart1 | `integer` | read-only |
| animSwimWithObjPart2 | `integer` | read-only |
| animFlutterkickWithObj | `integer` | read-only |
| animWaterActionEndWithObj | `integer` | read-only |
| animStopGrabObjWater | `integer` | read-only |
| animWaterIdleWithObj | `integer` | read-only |
| animDrowningPart1 | `integer` | read-only |
| animDrowningPart2 | `integer` | read-only |
| animWaterDying | `integer` | read-only |
| animWaterForwardKb | `integer` | read-only |
| animFallFromWater | `integer` | read-only |
| animSwimPart1 | `integer` | read-only |
| animSwimPart2 | `integer` | read-only |
| animFlutterkick | `integer` | read-only |
| animWaterActionEnd | `integer` | read-only |
| animWaterPickUpObj | `integer` | read-only |
| animWaterGrabObjPart2 | `integer` | read-only |
| animWaterGrabObjPart1 | `integer` | read-only |
| animWaterThrowObj | `integer` | read-only |
| animWaterIdle | `integer` | read-only |
| animWaterStarDance | `integer` | read-only |
| animReturnFromWaterStarDance | `integer` | read-only |
| animGrabBowser | `integer` | read-only |
| animSwingingBowser | `integer` | read-only |
| animReleaseBowser | `integer` | read-only |
| animHoldingBowser | `integer` | read-only |
| animHeavyThrow | `integer` | read-only |
| animWalkPanting | `integer` | read-only |
| animWalkWithHeavyObj | `integer` | read-only |
| animTurningPart1 | `integer` | read-only |
| animTurningPart2 | `integer` | read-only |
| animSlideflipLand | `integer` | read-only |
| animSlideflip | `integer` | read-only |
| animTripleJumpLand | `integer` | read-only |
| animTripleJump | `integer` | read-only |
| animFirstPerson | `integer` | read-only |
| animIdleHeadLeft | `integer` | read-only |
| animIdleHeadRight | `integer` | read-only |
| animIdleHeadCenter | `integer` | read-only |
| animHandstandLeft | `integer` | read-only |
| animHandstandRight | `integer` | read-only |
| animWakeFromSleep | `integer` | read-only |
| animWakeFromLying | `integer` | read-only |
| animStartTiptoe | `integer` | read-only |
| animSlidejump | `integer` | read-only |
| animStartWallkick | `integer` | read-only |
| animStarDance | `integer` | read-only |
| animReturnFromStarDance | `integer` | read-only |
| animForwardSpinningFlip | `integer` | read-only |
| animTripleJumpFly | `integer` | read-only |
| anims | `Array` <`integer`> | read-only |
| soundFreqScale | `number` | read-only |
| soundYahWahHoo | `integer` | read-only |
| soundHoohoo | `integer` | read-only |
| soundYahoo | `integer` | read-only |
| soundUh | `integer` | read-only |
| soundHrmm | `integer` | read-only |
| soundWah2 | `integer` | read-only |
| soundWhoa | `integer` | read-only |
| soundEeuh | `integer` | read-only |
| soundAttacked | `integer` | read-only |
| soundOoof | `integer` | read-only |
| soundOoof2 | `integer` | read-only |
| soundHereWeGo | `integer` | read-only |
| soundYawning | `integer` | read-only |
| soundSnoring1 | `integer` | read-only |
| soundSnoring2 | `integer` | read-only |
| soundWaaaooow | `integer` | read-only |
| soundHaha | `integer` | read-only |
| soundHaha_2 | `integer` | read-only |
| soundUh2 | `integer` | read-only |
| soundUh2_2 | `integer` | read-only |
| soundOnFire | `integer` | read-only |
| soundDying | `integer` | read-only |
| soundPantingCold | `integer` | read-only |
| soundPanting | `integer` | read-only |
| soundCoughing1 | `integer` | read-only |
| soundCoughing2 | `integer` | read-only |
| soundCoughing3 | `integer` | read-only |
| soundPunchYah | `integer` | read-only |
| soundPunchHoo | `integer` | read-only |
| soundMamaMia | `integer` | read-only |
| soundGroundPoundWah | `integer` | read-only |
| soundDrowning | `integer` | read-only |
| soundPunchWah | `integer` | read-only |
| soundYahooWahaYippee | `integer` | read-only |
| soundDoh | `integer` | read-only |
| soundGameOver | `integer` | read-only |
| soundHello | `integer` | read-only |
| soundPressStartToPlay | `integer` | read-only |
| soundTwirlBounce | `integer` | read-only |
| soundSnoring3 | `integer` | read-only |
| soundSoLongaBowser | `integer` | read-only |
| soundImaTired | `integer` | read-only |
| soundLetsAGo | `integer` | read-only |
| soundOkeyDokey | `integer` | read-only |
| sounds | `Array` <`integer`> | read-only |

[:arrow_up_small:](#)

<br />

## [Color](#Color)

| Field | Type | Access |
| ----- | ---- | ------ |
| r | `integer` |  |
| g | `integer` |  |
| b | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Controller](#Controller)

| Field | Type | Access |
| ----- | ---- | ------ |
| port | `integer` |  |
| stickX | `number` |  |
| stickY | `number` |  |
| stickMag | `number` |  |
| rawStickX | `integer` |  |
| rawStickY | `integer` |  |
| extStickX | `integer` |  |
| extStickY | `integer` |  |
| buttonDown | `integer` |  |
| buttonPressed | `integer` |  |
| buttonReleased | `integer` |  |

[:arrow_up_small:](#)

<br />

## [CustomLevelInfo](#CustomLevelInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| script | `Pointer` <`LevelScript`> | read-only |
| scriptEntryName | `string` | read-only |
| courseNum | `integer` |  |
| levelNum | `integer` |  |
| fullName | `string` | read-only |
| shortName | `string` | read-only |
| acousticReach | `integer` |  |
| echoLevel1 | `integer` |  |
| echoLevel2 | `integer` |  |
| echoLevel3 | `integer` |  |
| modIndex | `integer` |  |
| next | [CustomLevelInfo](structs.md#CustomLevelInfo) | read-only |

[:arrow_up_small:](#)

<br />

## [DateTime](#DateTime)

| Field | Type | Access |
| ----- | ---- | ------ |
| year | `integer` |  |
| month | `integer` |  |
| day | `integer` |  |
| hour | `integer` |  |
| minute | `integer` |  |
| second | `integer` |  |

[:arrow_up_small:](#)

<br />

## [DialogEntry](#DialogEntry)

| Field | Type | Access |
| ----- | ---- | ------ |
| unused | `integer` | read-only |
| linesPerBox | `integer` | read-only |
| leftOffset | `integer` | read-only |
| width | `integer` | read-only |
| text | `string` | read-only |
| replaced | `boolean` | read-only |

[:arrow_up_small:](#)

<br />

## [DisplayListNode](#DisplayListNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| next | [DisplayListNode](structs.md#DisplayListNode) |  |
| usingCamSpace | `integer` |  |

[:arrow_up_small:](#)

<br />

## [DjuiColor](#DjuiColor)

| Field | Type | Access |
| ----- | ---- | ------ |
| r | `integer` |  |
| g | `integer` |  |
| b | `integer` |  |
| a | `integer` |  |

[:arrow_up_small:](#)

<br />

## [DjuiInteractableTheme](#DjuiInteractableTheme)

| Field | Type | Access |
| ----- | ---- | ------ |
| textColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| defaultRectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| cursorDownRectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| hoveredRectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| defaultBorderColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| cursorDownBorderColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| hoveredBorderColor | [DjuiColor](structs.md#DjuiColor) | read-only |

[:arrow_up_small:](#)

<br />

## [DjuiPanelTheme](#DjuiPanelTheme)

| Field | Type | Access |
| ----- | ---- | ------ |
| hudFontHeader | `boolean` |  |

[:arrow_up_small:](#)

<br />

## [DjuiTheme](#DjuiTheme)

| Field | Type | Access |
| ----- | ---- | ------ |
| id | `string` | read-only |
| name | `string` | read-only |
| interactables | [DjuiInteractableTheme](structs.md#DjuiInteractableTheme) | read-only |
| threePanels | [DjuiThreePanelTheme](structs.md#DjuiThreePanelTheme) | read-only |
| panels | [DjuiPanelTheme](structs.md#DjuiPanelTheme) | read-only |

[:arrow_up_small:](#)

<br />

## [DjuiThreePanelTheme](#DjuiThreePanelTheme)

| Field | Type | Access |
| ----- | ---- | ------ |
| rectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| borderColor | [DjuiColor](structs.md#DjuiColor) | read-only |

[:arrow_up_small:](#)

<br />

## [ExclamationBoxContent](#ExclamationBoxContent)

| Field | Type | Access |
| ----- | ---- | ------ |
| id | `integer` |  |
| unused | `integer` |  |
| firstByte | `integer` |  |
| model | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |  |
| behavior | [enum BehaviorId](constants.md#enum-BehaviorId) |  |

[:arrow_up_small:](#)

<br />

## [FirstPersonCamera](#FirstPersonCamera)

| Field | Type | Access |
| ----- | ---- | ------ |
| enabled | `boolean` | read-only |
| forcePitch | `boolean` |  |
| forceYaw | `boolean` |  |
| forceRoll | `boolean` |  |
| centerL | `boolean` |  |
| pitch | `integer` |  |
| yaw | `integer` |  |
| crouch | `number` |  |
| fov | `number` |  |
| offset | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [FnGraphNode](#FnGraphNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |

[:arrow_up_small:](#)

<br />

## [Gfx](#Gfx)

| Field | Type | Access |
| ----- | ---- | ------ |
| w0 | `integer` | read-only |
| w1 | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GlobalObjectAnimations](#GlobalObjectAnimations)

| Field | Type | Access |
| ----- | ---- | ------ |
| amp_seg8_anims_08004034 | `Pointer` <`ObjectAnimPointer`> | read-only |
| birds_seg5_anims_050009E8 | `Pointer` <`ObjectAnimPointer`> | read-only |
| blargg_seg5_anims_0500616C | `Pointer` <`ObjectAnimPointer`> | read-only |
| blue_fish_seg3_anims_0301C2B0 | `Pointer` <`ObjectAnimPointer`> | read-only |
| bobomb_seg8_anims_0802396C | `Pointer` <`ObjectAnimPointer`> | read-only |
| bookend_seg5_anims_05002540 | `Pointer` <`ObjectAnimPointer`> | read-only |
| bowser_key_seg3_anims_list | `Pointer` <`ObjectAnimPointer`> | read-only |
| bowser_seg6_anims_06057690 | `Pointer` <`ObjectAnimPointer`> | read-only |
| bub_seg6_anims_06012354 | `Pointer` <`ObjectAnimPointer`> | read-only |
| bully_seg5_anims_0500470C | `Pointer` <`ObjectAnimPointer`> | read-only |
| butterfly_seg3_anims_030056B0 | `Pointer` <`ObjectAnimPointer`> | read-only |
| castle_grounds_seg7_anims_flags | `Pointer` <`ObjectAnimPointer`> | read-only |
| chain_chomp_seg6_anims_06025178 | `Pointer` <`ObjectAnimPointer`> | read-only |
| chair_seg5_anims_05005784 | `Pointer` <`ObjectAnimPointer`> | read-only |
| chilly_chief_seg6_anims_06003994 | `Pointer` <`ObjectAnimPointer`> | read-only |
| chuckya_seg8_anims_0800C070 | `Pointer` <`ObjectAnimPointer`> | read-only |
| clam_shell_seg5_anims_05001744 | `Pointer` <`ObjectAnimPointer`> | read-only |
| cyan_fish_seg6_anims_0600E264 | `Pointer` <`ObjectAnimPointer`> | read-only |
| door_seg3_anims_030156C0 | `Pointer` <`ObjectAnimPointer`> | read-only |
| dorrie_seg6_anims_0600F638 | `Pointer` <`ObjectAnimPointer`> | read-only |
| eyerok_seg5_anims_050116E4 | `Pointer` <`ObjectAnimPointer`> | read-only |
| flyguy_seg8_anims_08011A64 | `Pointer` <`ObjectAnimPointer`> | read-only |
| goomba_seg8_anims_0801DA4C | `Pointer` <`ObjectAnimPointer`> | read-only |
| heave_ho_seg5_anims_0501534C | `Pointer` <`ObjectAnimPointer`> | read-only |
| hoot_seg5_anims_05005768 | `Pointer` <`ObjectAnimPointer`> | read-only |
| king_bobomb_seg5_anims_0500FE30 | `Pointer` <`ObjectAnimPointer`> | read-only |
| klepto_seg5_anims_05008CFC | `Pointer` <`ObjectAnimPointer`> | read-only |
| koopa_flag_seg6_anims_06001028 | `Pointer` <`ObjectAnimPointer`> | read-only |
| koopa_seg6_anims_06011364 | `Pointer` <`ObjectAnimPointer`> | read-only |
| lakitu_enemy_seg5_anims_050144D4 | `Pointer` <`ObjectAnimPointer`> | read-only |
| lakitu_seg6_anims_060058F8 | `Pointer` <`ObjectAnimPointer`> | read-only |
| mad_piano_seg5_anims_05009B14 | `Pointer` <`ObjectAnimPointer`> | read-only |
| manta_seg5_anims_05008EB4 | `Pointer` <`ObjectAnimPointer`> | read-only |
| mips_seg6_anims_06015634 | `Pointer` <`ObjectAnimPointer`> | read-only |
| moneybag_seg6_anims_06005E5C | `Pointer` <`ObjectAnimPointer`> | read-only |
| monty_mole_seg5_anims_05007248 | `Pointer` <`ObjectAnimPointer`> | read-only |
| peach_seg5_anims_0501C41C | `Pointer` <`ObjectAnimPointer`> | read-only |
| penguin_seg5_anims_05008B74 | `Pointer` <`ObjectAnimPointer`> | read-only |
| piranha_plant_seg6_anims_0601C31C | `Pointer` <`ObjectAnimPointer`> | read-only |
| scuttlebug_seg6_anims_06015064 | `Pointer` <`ObjectAnimPointer`> | read-only |
| seaweed_seg6_anims_0600A4D4 | `Pointer` <`ObjectAnimPointer`> | read-only |
| skeeter_seg6_anims_06007DE0 | `Pointer` <`ObjectAnimPointer`> | read-only |
| snowman_seg5_anims_0500D118 | `Pointer` <`ObjectAnimPointer`> | read-only |
| spindrift_seg5_anims_05002D68 | `Pointer` <`ObjectAnimPointer`> | read-only |
| spiny_seg5_anims_05016EAC | `Pointer` <`ObjectAnimPointer`> | read-only |
| spiny_egg_seg5_anims_050157E4 | `Pointer` <`ObjectAnimPointer`> | read-only |
| sushi_seg5_anims_0500AE54 | `Pointer` <`ObjectAnimPointer`> | read-only |
| swoop_seg6_anims_060070D0 | `Pointer` <`ObjectAnimPointer`> | read-only |
| toad_seg6_anims_0600FB58 | `Pointer` <`ObjectAnimPointer`> | read-only |
| ukiki_seg5_anims_05015784 | `Pointer` <`ObjectAnimPointer`> | read-only |
| unagi_seg5_anims_05012824 | `Pointer` <`ObjectAnimPointer`> | read-only |
| water_ring_seg6_anims_06013F7C | `Pointer` <`ObjectAnimPointer`> | read-only |
| whomp_seg6_anims_06020A04 | `Pointer` <`ObjectAnimPointer`> | read-only |
| wiggler_seg5_anims_0500C874 | `Pointer` <`ObjectAnimPointer`> | read-only |
| wiggler_seg5_anims_0500EC8C | `Pointer` <`ObjectAnimPointer`> | read-only |
| yoshi_seg5_anims_05024100 | `Pointer` <`ObjectAnimPointer`> | read-only |

[:arrow_up_small:](#)

<br />

## [GlobalObjectCollisionData](#GlobalObjectCollisionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| bbh_seg7_collision_coffin | `Pointer` <`Collision`> |  |
| bbh_seg7_collision_haunted_bookshelf | `Pointer` <`Collision`> |  |
| bbh_seg7_collision_merry_go_round | `Pointer` <`Collision`> |  |
| bbh_seg7_collision_mesh_elevator | `Pointer` <`Collision`> |  |
| bbh_seg7_collision_staircase_step | `Pointer` <`Collision`> |  |
| bbh_seg7_collision_tilt_floor_platform | `Pointer` <`Collision`> |  |
| bitdw_seg7_collision_moving_pyramid | `Pointer` <`Collision`> |  |
| bitfs_seg7_collision_inverted_pyramid | `Pointer` <`Collision`> |  |
| bitfs_seg7_collision_sinking_cage_platform | `Pointer` <`Collision`> |  |
| bitfs_seg7_collision_sinking_platform | `Pointer` <`Collision`> |  |
| bitfs_seg7_collision_squishable_platform | `Pointer` <`Collision`> |  |
| blue_coin_switch_seg8_collision_08000E98 | `Pointer` <`Collision`> |  |
| bob_seg7_collision_chain_chomp_gate | `Pointer` <`Collision`> |  |
| bowser_2_seg7_collision_tilting_platform | `Pointer` <`Collision`> |  |
| breakable_box_seg8_collision_08012D70 | `Pointer` <`Collision`> |  |
| cannon_lid_seg8_collision_08004950 | `Pointer` <`Collision`> |  |
| capswitch_collision_050033D0 | `Pointer` <`Collision`> |  |
| capswitch_collision_05003448 | `Pointer` <`Collision`> |  |
| castle_grounds_seg7_collision_cannon_grill | `Pointer` <`Collision`> |  |
| castle_grounds_seg7_collision_moat_grills | `Pointer` <`Collision`> |  |
| checkerboard_platform_seg8_collision_0800D710 | `Pointer` <`Collision`> |  |
| ddd_seg7_collision_bowser_sub_door | `Pointer` <`Collision`> |  |
| ddd_seg7_collision_submarine | `Pointer` <`Collision`> |  |
| door_seg3_collision_0301CE78 | `Pointer` <`Collision`> |  |
| dorrie_seg6_collision_0600F644 | `Pointer` <`Collision`> |  |
| dorrie_seg6_collision_0600FBB8 | `Pointer` <`Collision`> |  |
| exclamation_box_outline_seg8_collision_08025F78 | `Pointer` <`Collision`> |  |
| hmc_seg7_collision_controllable_platform | `Pointer` <`Collision`> |  |
| hmc_seg7_collision_controllable_platform_sub | `Pointer` <`Collision`> |  |
| hmc_seg7_collision_elevator | `Pointer` <`Collision`> |  |
| inside_castle_seg7_collision_floor_trap | `Pointer` <`Collision`> |  |
| inside_castle_seg7_collision_star_door | `Pointer` <`Collision`> |  |
| inside_castle_seg7_collision_water_level_pillar | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_floating_box | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_floating_platform | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_in_sunken_ship | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_in_sunken_ship_2 | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_in_sunken_ship_3 | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_pillar_base | `Pointer` <`Collision`> |  |
| jrb_seg7_collision_rock_solid | `Pointer` <`Collision`> |  |
| lll_hexagonal_mesh_seg3_collision_0301CECC | `Pointer` <`Collision`> |  |
| lll_seg7_collision_drawbridge | `Pointer` <`Collision`> |  |
| lll_seg7_collision_falling_wall | `Pointer` <`Collision`> |  |
| lll_seg7_collision_floating_block | `Pointer` <`Collision`> |  |
| lll_seg7_collision_hexagonal_platform | `Pointer` <`Collision`> |  |
| lll_seg7_collision_inverted_pyramid | `Pointer` <`Collision`> |  |
| lll_seg7_collision_octagonal_moving_platform | `Pointer` <`Collision`> |  |
| lll_seg7_collision_pitoune | `Pointer` <`Collision`> |  |
| lll_seg7_collision_puzzle_piece | `Pointer` <`Collision`> |  |
| lll_seg7_collision_rotating_fire_bars | `Pointer` <`Collision`> |  |
| lll_seg7_collision_rotating_platform | `Pointer` <`Collision`> |  |
| lll_seg7_collision_sinking_pyramids | `Pointer` <`Collision`> |  |
| lll_seg7_collision_slow_tilting_platform | `Pointer` <`Collision`> |  |
| lll_seg7_collision_wood_piece | `Pointer` <`Collision`> |  |
| metal_box_seg8_collision_08024C28 | `Pointer` <`Collision`> |  |
| penguin_seg5_collision_05008B88 | `Pointer` <`Collision`> |  |
| poundable_pole_collision_06002490 | `Pointer` <`Collision`> |  |
| purple_switch_seg8_collision_0800C7A8 | `Pointer` <`Collision`> |  |
| rr_seg7_collision_donut_platform | `Pointer` <`Collision`> |  |
| rr_seg7_collision_elevator_platform | `Pointer` <`Collision`> |  |
| rr_seg7_collision_pendulum | `Pointer` <`Collision`> |  |
| rr_seg7_collision_rotating_platform_with_fire | `Pointer` <`Collision`> |  |
| sl_seg7_collision_pound_explodes | `Pointer` <`Collision`> |  |
| sl_seg7_collision_sliding_snow_mound | `Pointer` <`Collision`> |  |
| springboard_collision_05001A28 | `Pointer` <`Collision`> |  |
| ssl_seg7_collision_0702808C | `Pointer` <`Collision`> |  |
| ssl_seg7_collision_grindel | `Pointer` <`Collision`> |  |
| ssl_seg7_collision_pyramid_elevator | `Pointer` <`Collision`> |  |
| ssl_seg7_collision_pyramid_top | `Pointer` <`Collision`> |  |
| ssl_seg7_collision_spindel | `Pointer` <`Collision`> |  |
| ssl_seg7_collision_tox_box | `Pointer` <`Collision`> |  |
| thi_seg7_collision_top_trap | `Pointer` <`Collision`> |  |
| thwomp_seg5_collision_0500B7D0 | `Pointer` <`Collision`> |  |
| thwomp_seg5_collision_0500B92C | `Pointer` <`Collision`> |  |
| ttc_seg7_collision_clock_main_rotation | `Pointer` <`Collision`> |  |
| ttc_seg7_collision_clock_pendulum | `Pointer` <`Collision`> |  |
| ttc_seg7_collision_clock_platform | `Pointer` <`Collision`> |  |
| ttc_seg7_collision_rotating_clock_platform2 | `Pointer` <`Collision`> |  |
| ttc_seg7_collision_sliding_surface | `Pointer` <`Collision`> |  |
| ttm_seg7_collision_pitoune_2 | `Pointer` <`Collision`> |  |
| ttm_seg7_collision_podium_warp | `Pointer` <`Collision`> |  |
| ttm_seg7_collision_ukiki_cage | `Pointer` <`Collision`> |  |
| unknown_seg8_collision_080262F8 | `Pointer` <`Collision`> |  |
| warp_pipe_seg3_collision_03009AC8 | `Pointer` <`Collision`> |  |
| wdw_seg7_collision_arrow_lift | `Pointer` <`Collision`> |  |
| wdw_seg7_collision_express_elevator_platform | `Pointer` <`Collision`> |  |
| wdw_seg7_collision_rect_floating_platform | `Pointer` <`Collision`> |  |
| wdw_seg7_collision_square_floating_platform | `Pointer` <`Collision`> |  |
| wf_seg7_collision_breakable_wall | `Pointer` <`Collision`> |  |
| wf_seg7_collision_breakable_wall_2 | `Pointer` <`Collision`> |  |
| wf_seg7_collision_bullet_bill_cannon | `Pointer` <`Collision`> |  |
| wf_seg7_collision_clocklike_rotation | `Pointer` <`Collision`> |  |
| wf_seg7_collision_kickable_board | `Pointer` <`Collision`> |  |
| wf_seg7_collision_large_bomp | `Pointer` <`Collision`> |  |
| wf_seg7_collision_platform | `Pointer` <`Collision`> |  |
| wf_seg7_collision_sliding_brick_platform | `Pointer` <`Collision`> |  |
| wf_seg7_collision_small_bomp | `Pointer` <`Collision`> |  |
| wf_seg7_collision_tower | `Pointer` <`Collision`> |  |
| wf_seg7_collision_tower_door | `Pointer` <`Collision`> |  |
| whomp_seg6_collision_06020A0C | `Pointer` <`Collision`> |  |
| wooden_signpost_seg3_collision_0302DD80 | `Pointer` <`Collision`> |  |

[:arrow_up_small:](#)

<br />

## [GlobalTextures](#GlobalTextures)

| Field | Type | Access |
| ----- | ---- | ------ |
| camera | [TextureInfo](structs.md#TextureInfo) | read-only |
| lakitu | [TextureInfo](structs.md#TextureInfo) | read-only |
| no_camera | [TextureInfo](structs.md#TextureInfo) | read-only |
| arrow_up | [TextureInfo](structs.md#TextureInfo) | read-only |
| arrow_down | [TextureInfo](structs.md#TextureInfo) | read-only |
| coin | [TextureInfo](structs.md#TextureInfo) | read-only |
| star | [TextureInfo](structs.md#TextureInfo) | read-only |
| apostrophe | [TextureInfo](structs.md#TextureInfo) | read-only |
| double_quote | [TextureInfo](structs.md#TextureInfo) | read-only |
| mario_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| luigi_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| toad_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| waluigi_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| wario_head | [TextureInfo](structs.md#TextureInfo) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNode](#GraphNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| prev | [GraphNode](structs.md#GraphNode) | read-only |
| next | [GraphNode](structs.md#GraphNode) | read-only |
| parent | [GraphNode](structs.md#GraphNode) | read-only |
| children | [GraphNode](structs.md#GraphNode) | read-only |
| type | `integer` | read-only |
| flags | `integer` |  |
| extraFlags | `integer` |  |
| hookProcess | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeAnimatedPart](#GraphNodeAnimatedPart)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeBackground](#GraphNodeBackground)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| unused | `integer` | read-only |
| background | `integer` |  |
| prevCameraPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevCameraFocus | [Vec3f](structs.md#Vec3f) | read-only |
| prevCameraTimestamp | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeBillboard](#GraphNodeBillboard)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeBone](#GraphNodeBone)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |
| rotation | [Vec3s](structs.md#Vec3s) | read-only |
| scale | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeCamera](#GraphNodeCamera)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| prevPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevFocus | [Vec3f](structs.md#Vec3f) | read-only |
| prevTimestamp | `integer` | read-only |
| matrixPtr | `Pointer` <`Mat4`> |  |
| matrixPtrPrev | `Pointer` <`Mat4`> | read-only |
| roll | `integer` |  |
| rollScreen | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeCullingRadius](#GraphNodeCullingRadius)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| cullingRadius | `integer` |  |
| pad1E | `Array` <`integer`> |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeDisplayList](#GraphNodeDisplayList)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeGenerated](#GraphNodeGenerated)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| parameter | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeHeldObject](#GraphNodeHeldObject)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| playerIndex | `integer` |  |
| objNode | [Object](structs.md#Object) |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |
| prevShadowPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevShadowPosTimestamp | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeLevelOfDetail](#GraphNodeLevelOfDetail)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| minDistance | `integer` |  |
| maxDistance | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeMasterList](#GraphNodeMasterList)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeObject](#GraphNodeObject)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| sharedChild | [GraphNode](structs.md#GraphNode) | read-only |
| unk4C | [SpawnInfo](structs.md#SpawnInfo) | read-only |
| throwMatrix | `Pointer` <`Mat4`> |  |
| throwMatrixPrev | `Pointer` <`Mat4`> | read-only |
| prevThrowMatrix | [Mat4](structs.md#Mat4) | read-only |
| angle | [Vec3s](structs.md#Vec3s) | read-only |
| prevAngle | [Vec3s](structs.md#Vec3s) | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| prevPos | [Vec3f](structs.md#Vec3f) | read-only |
| shadowPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevShadowPos | [Vec3f](structs.md#Vec3f) | read-only |
| scale | [Vec3f](structs.md#Vec3f) | read-only |
| prevScale | [Vec3f](structs.md#Vec3f) | read-only |
| cameraToObject | [Vec3f](structs.md#Vec3f) | read-only |
| prevTimestamp | `integer` | read-only |
| prevShadowPosTimestamp | `integer` | read-only |
| prevScaleTimestamp | `integer` | read-only |
| prevThrowMatrixTimestamp | `integer` | read-only |
| skipInterpolationTimestamp | `integer` | read-only |
| animInfo | [AnimInfo](structs.md#AnimInfo) | read-only |
| areaIndex | `integer` |  |
| activeAreaIndex | `integer` |  |
| shadowInvisible | `boolean` |  |
| disableAutomaticShadowPos | `boolean` |  |
| skipInViewCheck | `boolean` |  |
| inited | `boolean` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeObjectParent](#GraphNodeObjectParent)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| sharedChild | [GraphNode](structs.md#GraphNode) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeOrthoProjection](#GraphNodeOrthoProjection)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| scale | `number` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodePerspective](#GraphNodePerspective)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| unused | `integer` | read-only |
| fov | `number` |  |
| near | `integer` |  |
| far | `integer` |  |
| prevFov | `number` |  |
| prevTimestamp | `number` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeRoot](#GraphNodeRoot)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| areaIndex | `integer` | read-only |
| x | `integer` |  |
| y | `integer` |  |
| width | `integer` |  |
| height | `integer` |  |
| numViews | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeRotation](#GraphNodeRotation)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| rotation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeScale](#GraphNodeScale)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| scale | `number` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeScaleXYZ](#GraphNodeScaleXYZ)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| scale | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeShadow](#GraphNodeShadow)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| shadowScale | `integer` |  |
| shadowSolidity | `integer` |  |
| shadowType | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeStart](#GraphNodeStart)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeSwitchCase](#GraphNodeSwitchCase)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| unused | `integer` | read-only |
| parameter | `integer` |  |
| selectedCase | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeTranslation](#GraphNodeTranslation)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |
| pad1E | `Array` <`integer`> |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeTranslationRotation](#GraphNodeTranslationRotation)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| displayList | `Pointer` <`Gfx`> |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |
| rotation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [HudUtilsRotation](#HudUtilsRotation)

| Field | Type | Access |
| ----- | ---- | ------ |
| rotation | `number` |  |
| rotationDiff | `number` |  |
| prevPivotX | `number` |  |
| prevPivotY | `number` |  |
| pivotX | `number` |  |
| pivotY | `number` |  |

[:arrow_up_small:](#)

<br />

## [InstantWarp](#InstantWarp)

| Field | Type | Access |
| ----- | ---- | ------ |
| id | `integer` |  |
| area | `integer` |  |
| displacement | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [LakituState](#LakituState)

| Field | Type | Access |
| ----- | ---- | ------ |
| curFocus | [Vec3f](structs.md#Vec3f) | read-only |
| curPos | [Vec3f](structs.md#Vec3f) | read-only |
| goalFocus | [Vec3f](structs.md#Vec3f) | read-only |
| goalPos | [Vec3f](structs.md#Vec3f) | read-only |
| filler30 | `Array` <`integer`> |  |
| mode | `integer` |  |
| defMode | `integer` |  |
| filler3E | `Array` <`integer`> |  |
| focusDistance | `number` |  |
| oldPitch | `integer` |  |
| oldYaw | `integer` |  |
| oldRoll | `integer` |  |
| shakeMagnitude | [Vec3s](structs.md#Vec3s) | read-only |
| shakePitchPhase | `integer` |  |
| shakePitchVel | `integer` |  |
| shakePitchDecay | `integer` |  |
| unusedVec1 | [Vec3f](structs.md#Vec3f) | read-only |
| unusedVec2 | [Vec3s](structs.md#Vec3s) | read-only |
| filler72 | `Array` <`integer`> |  |
| roll | `integer` |  |
| yaw | `integer` |  |
| nextYaw | `integer` |  |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| shakeRollPhase | `integer` |  |
| shakeRollVel | `integer` |  |
| shakeRollDecay | `integer` |  |
| shakeYawPhase | `integer` |  |
| shakeYawVel | `integer` |  |
| shakeYawDecay | `integer` |  |
| focHSpeed | `number` |  |
| focVSpeed | `number` |  |
| posHSpeed | `number` |  |
| posVSpeed | `number` |  |
| keyDanceRoll | `integer` |  |
| lastFrameAction | `integer` |  |
| unused | `integer` |  |
| skipCameraInterpolationTimestamp | `integer` |  |

[:arrow_up_small:](#)

<br />

## [LevelValues](#LevelValues)

| Field | Type | Access |
| ----- | ---- | ------ |
| fixCollisionBugs | `integer` |  |
| fixCollisionBugsRoundedCorners | `integer` |  |
| fixCollisionBugsFalseLedgeGrab | `integer` |  |
| fixCollisionBugsGroundPoundBonks | `integer` |  |
| fixCollisionBugsPickBestWall | `integer` |  |
| fixVanishFloors | `integer` |  |
| fixInvalidShellRides | `integer` |  |
| hudCapTimer | `integer` |  |
| hudRedCoinsRadar | `integer` |  |
| hudSecretsRadar | `integer` |  |
| starHeal | `integer` |  |
| mushroom1UpHeal | `integer` |  |
| floatingStarDance | `integer` |  |
| previewBlueCoins | `integer` |  |
| respawnBlueCoinsSwitch | `integer` |  |
| visibleSecrets | `integer` |  |
| showStarNumber | `integer` |  |
| extendedPauseDisplay | `integer` |  |
| pauseExitAnywhere | `integer` |  |
| disableActs | `integer` |  |
| bubbleOnDeathBarrierInCapStages | `integer` |  |
| entryLevel | [enum LevelNum](constants.md#enum-LevelNum) |  |
| exitCastleLevel | [enum LevelNum](constants.md#enum-LevelNum) |  |
| exitCastleArea | `integer` |  |
| exitCastleWarpNode | `integer` |  |
| wingCapLookUpReq | `integer` |  |
| skipCreditsAt | [enum LevelNum](constants.md#enum-LevelNum) |  |
| pssSlideStarTime | `integer` |  |
| pssSlideStarIndex | `integer` |  |
| coinsRequiredForCoinStar | `integer` |  |
| infiniteStairsRequirement | `integer` |  |
| wingCapDuration | `integer` |  |
| metalCapDuration | `integer` |  |
| vanishCapDuration | `integer` |  |
| wingCapDurationTotwc | `integer` |  |
| metalCapDurationCotmc | `integer` |  |
| vanishCapDurationVcutm | `integer` |  |
| wingCapSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| metalCapSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| vanishCapSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| shellSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| starPositions | [StarPositions](structs.md#StarPositions) | read-only |
| cellHeightLimit | `integer` |  |
| floorLowerLimit | `integer` |  |
| floorLowerLimitMisc | `integer` |  |
| floorLowerLimitShadow | `integer` |  |
| maxLives | `integer` |  |
| maxCoins | `integer` |  |
| numCoinsToLife | `integer` |  |
| wdwWaterLevelSpeed | `number` |  |
| useGlobalStarIds | `integer` |  |
| zoomOutCameraOnPause | `integer` |  |
| jrbDarkenSkybox | `integer` |  |
| wallMaxRadius | `number` |  |
| floorNormalMinY | `number` |  |
| ceilNormalMaxY | `number` |  |

[:arrow_up_small:](#)

<br />

## [MarioAnimation](#MarioAnimation)

| Field | Type | Access |
| ----- | ---- | ------ |
| currentAnimAddr | `Pointer` <`integer`> | read-only |
| targetAnim | [Animation](structs.md#Animation) |  |

[:arrow_up_small:](#)

<br />

## [MarioBodyState](#MarioBodyState)

| Field | Type | Access |
| ----- | ---- | ------ |
| capState | `integer` |  |
| eyeState | `integer` |  |
| handState | `integer` |  |
| punchState | `integer` |  |
| modelState | `integer` |  |
| allowPartRotation | `integer` |  |
| grabPos | `integer` |  |
| wingFlutter | `integer` |  |
| mirrorMario | `boolean` |  |
| headAngle | [Vec3s](structs.md#Vec3s) | read-only |
| torsoAngle | [Vec3s](structs.md#Vec3s) | read-only |
| headPos | [Vec3f](structs.md#Vec3f) | read-only |
| torsoPos | [Vec3f](structs.md#Vec3f) | read-only |
| heldObjLastPosition | [Vec3f](structs.md#Vec3f) | read-only |
| animPartsPos | `Array` <`Vec3f`> | read-only |
| currAnimPart | `integer` | read-only |
| updateTorsoTime | `integer` | read-only |
| updateHeadPosTime | `integer` | read-only |
| action | `integer` |  |
| shadeR | `integer` |  |
| shadeG | `integer` |  |
| shadeB | `integer` |  |
| lightR | `integer` |  |
| lightG | `integer` |  |
| lightB | `integer` |  |
| lightingDirX | `number` |  |
| lightingDirY | `number` |  |
| lightingDirZ | `number` |  |

[:arrow_up_small:](#)

<br />

## [MarioState](#MarioState)

| Field | Type | Access |
| ----- | ---- | ------ |
| playerIndex | `integer` | read-only |
| input | `integer` |  |
| numCoins | `integer` |  |
| numStars | `integer` |  |
| numLives | `integer` |  |
| numKeys | `integer` |  |
| health | `integer` |  |
| hurtCounter | `integer` |  |
| healCounter | `integer` |  |
| isSnoring | `integer` |  |
| freeze | `integer` |  |
| cap | `integer` |  |
| capTimer | `integer` |  |
| invincTimer | `integer` |  |
| skipWarpInteractionsTimer | `integer` |  |
| squishTimer | `integer` |  |
| bounceSquishTimer | `integer` |  |
| knockbackTimer | `integer` |  |
| wallKickTimer | `integer` |  |
| doubleJumpTimer | `integer` |  |
| specialTripleJump | `integer` |  |
| fadeWarpOpacity | `integer` |  |
| wasNetworkVisible | `integer` |  |
| dialogId | `integer` | read-only |
| prevNumStarsForDialog | `integer` |  |
| unkB0 | `integer` |  |
| action | `integer` |  |
| prevAction | `integer` |  |
| actionArg | `integer` |  |
| actionTimer | `integer` |  |
| actionState | `integer` |  |
| flags | `integer` |  |
| quicksandDepth | `number` |  |
| controller | [Controller](structs.md#Controller) | read-only |
| marioBodyState | [MarioBodyState](structs.md#MarioBodyState) | read-only |
| character | [Character](structs.md#Character) |  |
| terrainSoundAddend | `integer` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| nonInstantWarpPos | [Vec3f](structs.md#Vec3f) | read-only |
| vel | [Vec3f](structs.md#Vec3f) | read-only |
| slideVelX | `number` |  |
| slideVelZ | `number` |  |
| forwardVel | `number` |  |
| peakHeight | `number` |  |
| intendedMag | `number` |  |
| intendedYaw | `integer` |  |
| framesSinceA | `integer` |  |
| framesSinceB | `integer` |  |
| faceAngle | [Vec3s](structs.md#Vec3s) | read-only |
| angleVel | [Vec3s](structs.md#Vec3s) | read-only |
| slideYaw | `integer` |  |
| twirlYaw | `integer` |  |
| heldObj | [Object](structs.md#Object) |  |
| heldByObj | [Object](structs.md#Object) |  |
| interactObj | [Object](structs.md#Object) |  |
| riddenObj | [Object](structs.md#Object) |  |
| usedObj | [Object](structs.md#Object) |  |
| marioObj | [Object](structs.md#Object) | read-only |
| bubbleObj | [Object](structs.md#Object) |  |
| collidedObjInteractTypes | `integer` |  |
| particleFlags | `integer` |  |
| animation | [MarioAnimation](structs.md#MarioAnimation) |  |
| splineKeyframe | `Pointer` <`Vec4s`> |  |
| splineKeyframeFraction | `number` |  |
| splineState | `integer` |  |
| curAnimOffset | `number` |  |
| minimumBoneY | `number` |  |
| wall | [Surface](structs.md#Surface) |  |
| ceil | [Surface](structs.md#Surface) |  |
| floor | [Surface](structs.md#Surface) |  |
| spawnInfo | [SpawnInfo](structs.md#SpawnInfo) |  |
| area | [Area](structs.md#Area) | read-only |
| statusForCamera | [PlayerCameraState](structs.md#PlayerCameraState) | read-only |
| ceilHeight | `number` |  |
| floorHeight | `number` |  |
| wallNormal | [Vec3f](structs.md#Vec3f) | read-only |
| unkC4 | `number` |  |
| floorAngle | `integer` |  |
| waterLevel | `integer` |  |
| currentRoom | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Mat4](#Mat4)

| Field | Type | Access |
| ----- | ---- | ------ |
| m00 | `number` |  |
| m01 | `number` |  |
| m02 | `number` |  |
| m03 | `number` |  |
| m10 | `number` |  |
| m11 | `number` |  |
| m12 | `number` |  |
| m13 | `number` |  |
| m20 | `number` |  |
| m21 | `number` |  |
| m22 | `number` |  |
| m23 | `number` |  |
| m30 | `number` |  |
| m31 | `number` |  |
| m32 | `number` |  |
| m33 | `number` |  |

[:arrow_up_small:](#)

<br />

## [Mod](#Mod)

| Field | Type | Access |
| ----- | ---- | ------ |
| name | `string` | read-only |
| incompatible | `string` | read-only |
| category | `string` | read-only |
| description | `string` | read-only |
| relativePath | `string` | read-only |
| basePath | `string` | read-only |
| index | `integer` | read-only |
| fileCount | `integer` | read-only |
| fileCapacity | `integer` | read-only |
| isDirectory | `boolean` | read-only |
| enabled | `boolean` | read-only |
| selectable | `boolean` | read-only |
| renderBehindHud | `boolean` | read-only |
| pausable | `boolean` | read-only |
| ignoreScriptWarnings | `boolean` | read-only |
| size | `integer` | read-only |
| customBehaviorIndex | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [ModAudio](#ModAudio)

| Field | Type | Access |
| ----- | ---- | ------ |
| filepath | `string` | read-only |
| isStream | `boolean` | read-only |
| baseVolume | `number` |  |
| loaded | `boolean` | read-only |

[:arrow_up_small:](#)

<br />

## [ModFs](#ModFs)

| Field | Type | Access |
| ----- | ---- | ------ |
| mod | [Mod](structs.md#Mod) | read-only |
| modPath | `string` | read-only |
| numFiles | `integer` | read-only |
| totalSize | `integer` | read-only |
| isPublic | `boolean` | read-only |

**Functions:**

| Name | Reference |
| ---- | --------- |
| get_filename | [`mod_fs_get_filename`](functions-5.md#mod_fs_get_filename) |
| get_file | [`mod_fs_get_file`](functions-5.md#mod_fs_get_file) |
| create_file | [`mod_fs_create_file`](functions-5.md#mod_fs_create_file) |
| move_file | [`mod_fs_move_file`](functions-5.md#mod_fs_move_file) |
| copy_file | [`mod_fs_copy_file`](functions-5.md#mod_fs_copy_file) |
| delete_file | [`mod_fs_delete_file`](functions-5.md#mod_fs_delete_file) |
| clear | [`mod_fs_clear`](functions-5.md#mod_fs_clear) |
| save | [`mod_fs_save`](functions-5.md#mod_fs_save) |
| delete | [`mod_fs_delete`](functions-5.md#mod_fs_delete) |
| set_public | [`mod_fs_set_public`](functions-5.md#mod_fs_set_public) |

[:arrow_up_small:](#)

<br />

## [ModFsFile](#ModFsFile)

| Field | Type | Access |
| ----- | ---- | ------ |
| modFs | [ModFs](structs.md#ModFs) | read-only |
| filepath | `string` | read-only |
| size | `integer` | read-only |
| offset | `integer` | read-only |
| isText | `boolean` | read-only |
| isPublic | `boolean` | read-only |

**Functions:**

| Name | Reference |
| ---- | --------- |
| read_bool | [`mod_fs_file_read_bool`](functions-5.md#mod_fs_file_read_bool) |
| read_integer | [`mod_fs_file_read_integer`](functions-5.md#mod_fs_file_read_integer) |
| read_number | [`mod_fs_file_read_number`](functions-5.md#mod_fs_file_read_number) |
| read_bytes | [`mod_fs_file_read_bytes`](functions-5.md#mod_fs_file_read_bytes) |
| read_string | [`mod_fs_file_read_string`](functions-5.md#mod_fs_file_read_string) |
| read_line | [`mod_fs_file_read_line`](functions-5.md#mod_fs_file_read_line) |
| write_bool | [`mod_fs_file_write_bool`](functions-5.md#mod_fs_file_write_bool) |
| write_integer | [`mod_fs_file_write_integer`](functions-5.md#mod_fs_file_write_integer) |
| write_number | [`mod_fs_file_write_number`](functions-5.md#mod_fs_file_write_number) |
| write_bytes | [`mod_fs_file_write_bytes`](functions-5.md#mod_fs_file_write_bytes) |
| write_string | [`mod_fs_file_write_string`](functions-5.md#mod_fs_file_write_string) |
| write_line | [`mod_fs_file_write_line`](functions-5.md#mod_fs_file_write_line) |
| seek | [`mod_fs_file_seek`](functions-5.md#mod_fs_file_seek) |
| rewind | [`mod_fs_file_rewind`](functions-5.md#mod_fs_file_rewind) |
| is_eof | [`mod_fs_file_is_eof`](functions-5.md#mod_fs_file_is_eof) |
| fill | [`mod_fs_file_fill`](functions-5.md#mod_fs_file_fill) |
| erase | [`mod_fs_file_erase`](functions-5.md#mod_fs_file_erase) |
| set_text_mode | [`mod_fs_file_set_text_mode`](functions-5.md#mod_fs_file_set_text_mode) |
| set_public | [`mod_fs_file_set_public`](functions-5.md#mod_fs_file_set_public) |

[:arrow_up_small:](#)

<br />

## [NametagsSettings](#NametagsSettings)

| Field | Type | Access |
| ----- | ---- | ------ |
| showHealth | `boolean` |  |
| showSelfTag | `boolean` |  |

[:arrow_up_small:](#)

<br />

## [NetworkPlayer](#NetworkPlayer)

| Field | Type | Access |
| ----- | ---- | ------ |
| connected | `boolean` | read-only |
| type | `integer` | read-only |
| localIndex | `integer` | read-only |
| globalIndex | `integer` | read-only |
| lastReceived | `number` | read-only |
| lastSent | `number` | read-only |
| lastPingSent | `number` | read-only |
| currLevelAreaSeqId | `integer` | read-only |
| currCourseNum | `integer` | read-only |
| currActNum | `integer` | read-only |
| currLevelNum | `integer` | read-only |
| currAreaIndex | `integer` | read-only |
| currLevelSyncValid | `boolean` | read-only |
| currAreaSyncValid | `boolean` | read-only |
| currPositionValid | `boolean` | read-only |
| fadeOpacity | `integer` | read-only |
| onRxSeqId | `integer` | read-only |
| modelIndex | `integer` | read-only |
| ping | `integer` | read-only |
| palette | [PlayerPalette](structs.md#PlayerPalette) | read-only |
| name | `string` | read-only |
| description | `string` | read-only |
| descriptionR | `integer` | read-only |
| descriptionG | `integer` | read-only |
| descriptionB | `integer` | read-only |
| descriptionA | `integer` | read-only |
| overrideLocation | `string` | read-only |
| overrideModelIndex | `integer` |  |
| overridePalette | [PlayerPalette](structs.md#PlayerPalette) |  |

[:arrow_up_small:](#)

<br />

## [Object](#Object)

| Field | Type | Access |
| ----- | ---- | ------ |
| header | [ObjectNode](structs.md#ObjectNode) | read-only |
| prevObj | [Object](structs.md#Object) |  |
| parentObj | [Object](structs.md#Object) |  |
| usingObj | [Object](structs.md#Object) |  |
| platform | [Object](structs.md#Object) |  |
| collidedObjs | `Array` <`Object`> |  |
| collisionData | `Pointer` <`Collision`> |  |
| behavior | `Pointer` <`BehaviorScript`> | read-only |
| curBhvCommand | `Pointer` <`BehaviorScript`> | read-only |
| bhvStack | `Array` <`integer`> | read-only |
| bhvStackIndex | `integer` | read-only |
| bhvDelayTimer | `integer` |  |
| activeFlags | `integer` |  |
| collidedObjInteractTypes | `integer` |  |
| numCollidedObjs | `integer` |  |
| respawnInfoType | `integer` | read-only |
| hitboxRadius | `number` |  |
| hitboxHeight | `number` |  |
| hurtboxRadius | `number` |  |
| hurtboxHeight | `number` |  |
| hitboxDownOffset | `number` |  |
| unused1 | `integer` |  |
| areaTimer | `integer` |  |
| areaTimerDuration | `integer` |  |
| areaTimerType | [enum AreaTimerType](constants.md#enum-AreaTimerType) |  |
| transform | [Mat4](structs.md#Mat4) | read-only |
| numSurfaces | `integer` | read-only |
| heldByPlayerIndex | `integer` |  |
| setHome | `integer` |  |
| ctx | `integer` |  |
| allowRemoteInteractions | `integer` |  |
| globalPlayerIndex | `integer` |  |
| coopFlags | `integer` | read-only |
| hookRender | `integer` |  |

### Object-Independent Data Fields
| Field | Type | Access |
| ----- | ---- | ------ |
| oFlags | `integer` |  |
| oDialogResponse | `integer` |  |
| oDialogState | `integer` |  |
| oUnk94 | `integer` |  |
| oSyncID | `integer` | read-only |
| oIntangibleTimer | `integer` |  |
| oPosX | `number` |  |
| oPosY | `number` |  |
| oPosZ | `number` |  |
| oVelX | `number` |  |
| oVelY | `number` |  |
| oVelZ | `number` |  |
| oForwardVel | `number` |  |
| oForwardVelS32 | `integer` |  |
| oUnkBC | `number` |  |
| oUnkC0 | `number` |  |
| oMoveAnglePitch | `integer` |  |
| oMoveAngleYaw | `integer` |  |
| oMoveAngleRoll | `integer` |  |
| oFaceAnglePitch | `integer` |  |
| oFaceAngleYaw | `integer` |  |
| oFaceAngleRoll | `integer` |  |
| oGraphYOffset | `number` |  |
| oActiveParticleFlags | `integer` |  |
| oGravity | `number` |  |
| oFloorHeight | `number` |  |
| oMoveFlags | `integer` |  |
| oAnimState | `integer` |  |
| oAngleVelPitch | `integer` |  |
| oAngleVelYaw | `integer` |  |
| oAngleVelRoll | `integer` |  |
| oAnimations | `Pointer` <`ObjectAnimPointer`> |  |
| oHeldState | `integer` |  |
| oWallHitboxRadius | `number` |  |
| oDragStrength | `number` |  |
| oInteractType | `integer` |  |
| oInteractStatus | `integer` |  |
| oParentRelativePosX | `number` |  |
| oParentRelativePosY | `number` |  |
| oParentRelativePosZ | `number` |  |
| oBehParams2ndByte | `integer` |  |
| oAction | `integer` |  |
| oSubAction | `integer` |  |
| oTimer | `integer` |  |
| oBounciness | `number` |  |
| oDistanceToMario | `number` |  |
| oAngleToMario | `integer` |  |
| oHomeX | `number` |  |
| oHomeY | `number` |  |
| oHomeZ | `number` |  |
| oFriction | `number` |  |
| oBuoyancy | `number` |  |
| oSoundStateID | `integer` |  |
| oOpacity | `integer` |  |
| oDamageOrCoinValue | `integer` |  |
| oHealth | `integer` |  |
| oBehParams | `integer` |  |
| oPrevAction | `integer` |  |
| oInteractionSubtype | `integer` |  |
| oCollisionDistance | `number` |  |
| oNumLootCoins | `integer` |  |
| oDrawingDistance | `number` |  |
| oRoom | `integer` |  |
| oSyncDeath | `integer` |  |
| oUnk1A8 | `integer` |  |
| oWallAngle | `integer` |  |
| oFloorType | `integer` |  |
| oFloorRoom | `integer` |  |
| oAngleToHome | `integer` |  |
| oFloor | [Surface](structs.md#Surface) |  |
| oDeathSound | `integer` |  |

### Object-Dependent Data Fields
| Field | Type | Access |
| ----- | ---- | ------ |
| oPathedStartWaypoint | [Waypoint](structs.md#Waypoint) |  |
| oPathedPrevWaypoint | [Waypoint](structs.md#Waypoint) |  |
| oPathedPrevWaypointFlags | `integer` |  |
| oPathedTargetPitch | `integer` |  |
| oPathedTargetYaw | `integer` |  |
| oMacroUnk108 | `number` |  |
| oMacroUnk10C | `number` |  |
| oMacroUnk110 | `number` |  |
| oMarioParticleFlags | `integer` |  |
| oMarioPoleUnk108 | `integer` |  |
| oMarioReadingSignDYaw | `integer` |  |
| oMarioPoleYawVel | `integer` |  |
| oMarioCannonObjectYaw | `integer` |  |
| oMarioTornadoYawVel | `integer` |  |
| oMarioReadingSignDPosX | `number` |  |
| oMarioPolePos | `number` |  |
| oMarioCannonInputYaw | `integer` |  |
| oMarioTornadoPosY | `number` |  |
| oMarioReadingSignDPosZ | `number` |  |
| oMarioWhirlpoolPosY | `number` |  |
| oMarioJumboStarCutscenePosZ | `number` |  |
| oMarioBurnTimer | `integer` |  |
| oMarioLongJumpIsSlow | `integer` |  |
| oMarioSteepJumpYaw | `integer` |  |
| oMarioWalkingPitch | `integer` |  |
| o1UpHiddenUnkF4 | `integer` |  |
| o1UpForceSpawn | `integer` |  |
| oActivatedBackAndForthPlatformMaxOffset | `number` |  |
| oActivatedBackAndForthPlatformOffset | `number` |  |
| oActivatedBackAndForthPlatformVel | `number` |  |
| oActivatedBackAndForthPlatformCountdown | `integer` |  |
| oActivatedBackAndForthPlatformStartYaw | `integer` |  |
| oActivatedBackAndForthPlatformVertical | `integer` |  |
| oActivatedBackAndForthPlatformFlipRotation | `integer` |  |
| oAmpRadiusOfRotation | `number` |  |
| oAmpYPhase | `integer` |  |
| oHomingAmpLockedOn | `integer` |  |
| oHomingAmpAvgY | `number` |  |
| oArrowLiftDisplacement | `number` |  |
| oArrowLiftUnk100 | `integer` |  |
| oBackAndForthPlatformDirection | `number` |  |
| oBackAndForthPlatformPathLength | `number` |  |
| oBackAndForthPlatformDistance | `number` |  |
| oBackAndForthPlatformVel | `number` |  |
| oBirdSpeed | `number` |  |
| oBirdTargetPitch | `integer` |  |
| oBirdTargetYaw | `integer` |  |
| oBirdChirpChirpUnkF4 | `integer` |  |
| oEndBirdUnk104 | `number` |  |
| oHiddenBlueCoinSwitch | [Object](structs.md#Object) |  |
| oBobombBlinkTimer | `integer` |  |
| oBobombFuseLit | `integer` |  |
| oBobombFuseTimer | `integer` |  |
| oBobombBuddyBlinkTimer | `integer` |  |
| oBobombBuddyHasTalkedToMario | `integer` |  |
| oBobombBuddyRole | `integer` |  |
| oBobombBuddyCannonStatus | `integer` |  |
| oBobombBuddyPosXCopy | `number` |  |
| oBobombBuddyPosYCopy | `number` |  |
| oBobombBuddyPosZCopy | `number` |  |
| oBobombExpBubGfxScaleFacX | `integer` |  |
| oBobombExpBubGfxScaleFacY | `integer` |  |
| oBobombExpBubGfxExpRateX | `integer` |  |
| oBobombExpBubGfxExpRateY | `integer` |  |
| oSmallBompInitX | `number` |  |
| oBooDeathStatus | `integer` |  |
| oBooTargetOpacity | `integer` |  |
| oBooBaseScale | `number` |  |
| oBooOscillationTimer | `integer` |  |
| oBooMoveYawDuringHit | `integer` |  |
| oBooMoveYawBeforeHit | `number` |  |
| oBooParentBigBoo | [Object](structs.md#Object) |  |
| oBooNegatedAggressiveness | `number` |  |
| oBooInitialMoveYaw | `integer` |  |
| oBooTurningSpeed | `integer` |  |
| oBigBooNumMinionBoosKilled | `integer` |  |
| oBookendUnkF4 | `integer` |  |
| oBookendUnkF8 | `integer` |  |
| oBookSwitchUnkF4 | `number` |  |
| oBookSwitchManagerUnkF4 | `integer` |  |
| oBookSwitchManagerUnkF8 | `integer` |  |
| oHauntedBookshelfShouldOpen | `integer` |  |
| oBouncingFireBallUnkF4 | `integer` |  |
| oBowlingBallTargetYaw | `integer` |  |
| oBBallSpawnerMaxSpawnDist | `number` |  |
| oBBallSpawnerSpawnOdds | `number` |  |
| oBBallSpawnerPeriodMinus1 | `integer` |  |
| oBowserUnk88 | `integer` |  |
| oBowserUnkF4 | `integer` |  |
| oBowserUnkF8 | `integer` |  |
| oBowserDistToCentre | `number` |  |
| oBowserUnk106 | `integer` |  |
| oBowserUnk108 | `integer` |  |
| oBowserHeldAnglePitch | `integer` |  |
| oBowserHeldAngleVelYaw | `integer` |  |
| oBowserUnk10E | `integer` |  |
| oBowserUnk110 | `integer` |  |
| oBowserAngleToCentre | `integer` |  |
| oBowserUnk1AC | `integer` |  |
| oBowserUnk1AE | `integer` |  |
| oBowserEyesShut | `integer` |  |
| oBowserUnk1B2 | `integer` |  |
| oBowserShockWaveUnkF4 | `number` |  |
| oBlackSmokeBowserUnkF4 | `number` |  |
| oBowserKeyScale | `number` |  |
| oBowserPuzzleCompletionFlags | `integer` |  |
| oBowserPuzzlePieceOffsetX | `number` |  |
| oBowserPuzzlePieceOffsetY | `number` |  |
| oBowserPuzzlePieceOffsetZ | `number` |  |
| oBowserPuzzlePieceContinuePerformingAction | `integer` |  |
| oBubbaUnkF4 | `number` |  |
| oBubbaUnkF8 | `integer` |  |
| oBubbaUnkFC | `integer` |  |
| oBubbaUnk100 | `integer` |  |
| oBubbaUnk104 | `integer` |  |
| oBubbaUnk108 | `number` |  |
| oBubbaUnk10C | `number` |  |
| oBubbaUnk1AC | `integer` |  |
| oBubbaUnk1AE | `integer` |  |
| oBubbaUnk1B0 | `integer` |  |
| oBubbaUnk1B2 | `integer` |  |
| oBulletBillInitialMoveYaw | `integer` |  |
| oBullySubtype | `integer` |  |
| oBullyPrevX | `number` |  |
| oBullyPrevY | `number` |  |
| oBullyPrevZ | `number` |  |
| oBullyKBTimerAndMinionKOCounter | `integer` |  |
| oBullyMarioCollisionAngle | `integer` |  |
| oBullyLastNetworkPlayerIndex | `integer` |  |
| oButterflyYPhase | `integer` |  |
| oTripletButterflyScale | `number` |  |
| oTripletButterflySpeed | `number` |  |
| oTripletButterflyBaseYaw | `number` |  |
| oTripletButterflyTargetPitch | `integer` |  |
| oTripletButterflyTargetYaw | `integer` |  |
| oTripletButterflyType | `integer` |  |
| oTripletButterflyModel | `integer` |  |
| oTripletButterflySelectedButterfly | `integer` |  |
| oTripletButterflyScalePhase | `integer` |  |
| oCannonUnkF4 | `integer` |  |
| oCannonUnkF8 | `integer` |  |
| oCannonUnk10C | `integer` |  |
| oCannonPlayerIndex | `integer` |  |
| oCapUnkF4 | `integer` |  |
| oCapUnkF8 | `integer` |  |
| oChainChompSegments | [ChainSegment](structs.md#ChainSegment) | read-only |
| oChainChompMaxDistFromPivotPerChainPart | `number` |  |
| oChainChompMaxDistBetweenChainParts | `number` |  |
| oChainChompDistToPivot | `number` |  |
| oChainChompUnk104 | `number` |  |
| oChainChompRestrictedByChain | `integer` |  |
| oChainChompTargetPitch | `integer` |  |
| oChainChompNumLunges | `integer` |  |
| oChainChompReleaseStatus | `integer` |  |
| oChainChompHitGate | `integer` |  |
| oCheckerBoardPlatformUnkF8 | `integer` |  |
| oCheckerBoardPlatformUnkFC | `integer` |  |
| oCheckerBoardPlatformUnk1AC | `number` |  |
| oCheepCheepUnkF4 | `number` |  |
| oCheepCheepUnkF8 | `number` |  |
| oCheepCheepUnkFC | `number` |  |
| oCheepCheepUnk104 | `number` |  |
| oCheepCheepUnk108 | `number` |  |
| oChuckyaUnk88 | `integer` |  |
| oChuckyaUnkF8 | `integer` |  |
| oChuckyaUnkFC | `integer` |  |
| oChuckyaUnk100 | `integer` |  |
| oClamUnkF4 | `integer` |  |
| oCloudCenterX | `number` |  |
| oCloudCenterY | `number` |  |
| oCloudBlowing | `integer` |  |
| oCloudGrowSpeed | `number` |  |
| oCloudFwooshMovementRadius | `integer` |  |
| oCoinUnkF4 | `integer` |  |
| oCoinUnkF8 | `integer` |  |
| oCoinUnk110 | `number` |  |
| oCoinUnk1B0 | `integer` |  |
| oCollisionParticleUnkF4 | `number` |  |
| oControllablePlatformUnkF8 | `integer` |  |
| oControllablePlatformUnkFC | `number` |  |
| oControllablePlatformUnk100 | `integer` |  |
| oBreakableBoxSmallReleased | `integer` |  |
| oBreakableBoxSmallFramesSinceReleased | `integer` |  |
| oJumpingBoxUnkF4 | `integer` |  |
| oJumpingBoxUnkF8 | `integer` |  |
| oRRCruiserWingUnkF4 | `integer` |  |
| oRRCruiserWingUnkF8 | `integer` |  |
| oDonutPlatformSpawnerSpawnedPlatforms | `integer` |  |
| oDoorUnk88 | `integer` |  |
| oDoorUnkF8 | `integer` |  |
| oDoorUnkFC | `integer` |  |
| oDoorUnk100 | `integer` |  |
| oDorrieDistToHome | `number` |  |
| oDorrieOffsetY | `number` |  |
| oDorrieVelY | `number` |  |
| oDorrieForwardDistToMario | `number` |  |
| oDorrieYawVel | `integer` |  |
| oDorrieLiftingMario | `integer` |  |
| oDorrieGroundPounded | `integer` |  |
| oDorrieAngleToHome | `integer` |  |
| oDorrieNeckAngle | `integer` |  |
| oDorrieHeadRaiseSpeed | `integer` |  |
| oElevatorUnkF4 | `number` |  |
| oElevatorUnkF8 | `number` |  |
| oElevatorUnkFC | `number` |  |
| oElevatorUnk100 | `integer` |  |
| oExclamationBoxUnkF4 | `number` |  |
| oExclamationBoxUnkF8 | `number` |  |
| oExclamationBoxUnkFC | `integer` |  |
| oExclamationBoxForce | `integer` |  |
| oEyerokBossNumHands | `integer` |  |
| oEyerokBossUnkFC | `integer` |  |
| oEyerokBossActiveHand | `integer` |  |
| oEyerokBossUnk104 | `integer` |  |
| oEyerokBossUnk108 | `number` |  |
| oEyerokBossUnk10C | `number` |  |
| oEyerokBossUnk110 | `number` |  |
| oEyerokBossUnk1AC | `integer` |  |
| oEyerokHandWakeUpTimer | `integer` |  |
| oEyerokReceivedAttack | `integer` |  |
| oEyerokHandUnkFC | `integer` |  |
| oEyerokHandUnk100 | `integer` |  |
| oEyerokHandDead | `integer` |  |
| oFallingPillarPitchAcceleration | `number` |  |
| oFireSpitterScaleVel | `number` |  |
| oFireSpitterLastWaterY | `number` |  |
| oBlueFishRandomVel | `number` |  |
| oBlueFishRandomTime | `integer` |  |
| oBlueFishRandomAngle | `number` |  |
| oFishWaterLevel | `number` |  |
| oFishGoalY | `number` |  |
| oFishHeightOffset | `number` |  |
| oFishYawVel | `integer` |  |
| oFishRoamDistance | `number` |  |
| oFishGoalVel | `number` |  |
| oFishDepthDistance | `number` |  |
| oFishActiveDistance | `number` |  |
| oFlameScale | `number` |  |
| oFlameSpeedTimerOffset | `integer` |  |
| oFlameUnkFC | `number` |  |
| oFlameBowser | [Object](structs.md#Object) |  |
| oBlueFlameNextScale | `number` |  |
| oSmallPiranhaFlameStartSpeed | `number` |  |
| oSmallPiranhaFlameEndSpeed | `number` |  |
| oSmallPiranhaFlameModel | `integer` |  |
| oSmallPiranhaFlameNextFlameTimer | `integer` |  |
| oSmallPiranhaFlameSpeed | `number` |  |
| oMovingFlameTimer | `integer` |  |
| oFlameThowerFlameUnk110 | `integer` |  |
| oFlameThowerUnk110 | `integer` |  |
| oFloatingPlatformUnkF4 | `integer` |  |
| oFloatingPlatformUnkF8 | `number` |  |
| oFloatingPlatformUnkFC | `number` |  |
| oFloatingPlatformUnk100 | `integer` |  |
| oFloorSwitchPressAnimationUnkF4 | `integer` |  |
| oFloorSwitchPressAnimationUnkF8 | `integer` |  |
| oFloorSwitchPressAnimationUnkFC | `integer` |  |
| oFloorSwitchPressAnimationUnk100 | `integer` |  |
| oFlyGuyIdleTimer | `integer` |  |
| oFlyGuyOscTimer | `integer` |  |
| oFlyGuyUnusedJitter | `integer` |  |
| oFlyGuyLungeYDecel | `number` |  |
| oFlyGuyLungeTargetPitch | `integer` |  |
| oFlyGuyTargetRoll | `integer` |  |
| oFlyGuyScaleVel | `number` |  |
| oGrandStarUnk108 | `integer` |  |
| oHorizontalGrindelTargetYaw | `integer` |  |
| oHorizontalGrindelDistToHome | `number` |  |
| oHorizontalGrindelOnGround | `integer` |  |
| oGoombaSize | `integer` |  |
| oGoombaScale | `number` |  |
| oGoombaWalkTimer | `integer` |  |
| oGoombaTargetYaw | `integer` |  |
| oGoombaBlinkTimer | `integer` |  |
| oGoombaTurningAwayFromWall | `integer` |  |
| oGoombaRelativeSpeed | `number` |  |
| oGoombaJumpCooldown | `integer` |  |
| oHauntedChairUnkF4 | `integer` |  |
| oHauntedChairUnkF8 | `number` |  |
| oHauntedChairUnkFC | `number` |  |
| oHauntedChairUnk100 | `Pointer` <`integer`> | read-only |
| oHauntedChairUnk104 | `integer` |  |
| oHeaveHoUnk88 | `integer` |  |
| oHeaveHoUnkF4 | `number` |  |
| oHiddenObjectUnkF4 | [Object](structs.md#Object) |  |
| oHootAvailability | `integer` |  |
| oHootMarioReleaseTime | `integer` |  |
| oHorizontalMovementUnkF4 | `integer` |  |
| oHorizontalMovementUnkF8 | `integer` |  |
| oHorizontalMovementUnk100 | `number` |  |
| oHorizontalMovementUnk104 | `integer` |  |
| oHorizontalMovementUnk108 | `number` |  |
| oKickableBoardF4 | `integer` |  |
| oKickableBoardF8 | `integer` |  |
| oKingBobombUnk88 | `integer` |  |
| oKingBobombUnkF8 | `integer` |  |
| oKingBobombUnkFC | `integer` |  |
| oKingBobombUnk100 | `integer` |  |
| oKingBobombUnk104 | `integer` |  |
| oKingBobombUnk108 | `integer` |  |
| oKleptoDistanceToTarget | `number` |  |
| oKleptoUnkF8 | `number` |  |
| oKleptoUnkFC | `number` |  |
| oKleptoSpeed | `number` |  |
| oKleptoStartPosX | `number` |  |
| oKleptoStartPosY | `number` |  |
| oKleptoStartPosZ | `number` |  |
| oKleptoTimeUntilTargetChange | `integer` |  |
| oKleptoTargetNumber | `integer` |  |
| oKleptoUnk1AE | `integer` |  |
| oKleptoUnk1B0 | `integer` |  |
| oKleptoYawToTarget | `integer` |  |
| oKoopaAgility | `number` |  |
| oKoopaMovementType | `integer` |  |
| oKoopaTargetYaw | `integer` |  |
| oKoopaUnshelledTimeUntilTurn | `integer` |  |
| oKoopaTurningAwayFromWall | `integer` |  |
| oKoopaDistanceToMario | `number` |  |
| oKoopaAngleToMario | `integer` |  |
| oKoopaBlinkTimer | `integer` |  |
| oKoopaCountdown | `integer` |  |
| oKoopaTheQuickRaceIndex | `integer` |  |
| oKoopaTheQuickInitTextboxCooldown | `integer` |  |
| oKoopaRaceEndpointRaceBegun | `integer` |  |
| oKoopaRaceEndpointKoopaFinished | `integer` |  |
| oKoopaRaceEndpointRaceStatus | `integer` |  |
| oKoopaRaceEndpointUnk100 | `integer` |  |
| oKoopaRaceEndpointRaceEnded | `integer` |  |
| oKoopaShellFlameUnkF4 | `number` |  |
| oKoopaShellFlameUnkF8 | `number` |  |
| oCameraLakituBlinkTimer | `integer` |  |
| oCameraLakituSpeed | `number` |  |
| oCameraLakituCircleRadius | `number` |  |
| oCameraLakituFinishedDialog | `integer` |  |
| oCameraLakituUnk104 | `integer` |  |
| oCameraLakituPitchVel | `integer` |  |
| oCameraLakituYawVel | `integer` |  |
| oEnemyLakituNumSpinies | `integer` |  |
| oEnemyLakituBlinkTimer | `integer` |  |
| oEnemyLakituSpinyCooldown | `integer` |  |
| oEnemyLakituFaceForwardCountdown | `integer` |  |
| oIntroLakituSplineSegmentProgress | `number` |  |
| oIntroLakituSplineSegment | `number` |  |
| oIntroLakituUnk100 | `number` |  |
| oIntroLakituUnk104 | `number` |  |
| oIntroLakituUnk108 | `number` |  |
| oIntroLakituUnk10C | `number` |  |
| oIntroLakituUnk110 | `number` |  |
| oIntroLakituCloud | [Object](structs.md#Object) |  |
| oMenuButtonState | `integer` |  |
| oMenuButtonTimer | `integer` |  |
| oMenuButtonOrigPosX | `number` |  |
| oMenuButtonOrigPosY | `number` |  |
| oMenuButtonOrigPosZ | `number` |  |
| oMenuButtonScale | `number` |  |
| oMenuButtonActionPhase | `integer` |  |
| oMenuButtonIsCustom | `integer` |  |
| oMantaTargetPitch | `integer` |  |
| oMantaTargetYaw | `integer` |  |
| oMerryGoRoundStopped | `integer` |  |
| oMerryGoRoundMusicShouldPlay | `integer` |  |
| oMerryGoRoundMarioIsOutside | `integer` |  |
| oMerryGoRoundBooManagerNumBoosKilled | `integer` |  |
| oMerryGoRoundBooManagerNumBoosSpawned | `integer` |  |
| oMipsStarStatus | `integer` |  |
| oMipsStartWaypointIndex | `integer` |  |
| oMipsForwardVelocity | `number` |  |
| oMoneybagJumpState | `integer` |  |
| oMontyMoleCurrentHole | [Object](structs.md#Object) |  |
| oMontyMoleHeightRelativeToFloor | `number` |  |
| oMontyMoleHoleX | `number` |  |
| oMontyMoleHoleY | `number` |  |
| oMontyMoleHoleZ | `number` |  |
| oMontyMoleHoleCooldown | `integer` |  |
| oMrBlizzardScale | `number` |  |
| oMrBlizzardHeldObj | [Object](structs.md#Object) |  |
| oMrBlizzardGraphYVel | `number` |  |
| oMrBlizzardTimer | `integer` |  |
| oMrBlizzardDizziness | `number` |  |
| oMrBlizzardChangeInDizziness | `number` |  |
| oMrBlizzardGraphYOffset | `number` |  |
| oMrBlizzardDistFromHome | `integer` |  |
| oMrBlizzardTargetMoveYaw | `integer` |  |
| oMrIUnkF4 | `integer` |  |
| oMrIUnkFC | `integer` |  |
| oMrIUnk100 | `integer` |  |
| oMrIUnk104 | `integer` |  |
| oMrIUnk108 | `integer` |  |
| oMrISize | `number` |  |
| oMrIUnk110 | `integer` |  |
| oRespawnerModelToRespawn | `integer` |  |
| oRespawnerMinSpawnDist | `number` |  |
| oOpenableGrillUnk88 | `integer` |  |
| oOpenableGrillUnkF4 | [Object](structs.md#Object) |  |
| oIntroPeachYawFromFocus | `number` |  |
| oIntroPeachPitchFromFocus | `number` |  |
| oIntroPeachDistToCamera | `number` |  |
| oRacingPenguinInitTextCooldown | `integer` |  |
| oRacingPenguinWeightedNewTargetSpeed | `number` |  |
| oRacingPenguinFinalTextbox | `integer` |  |
| oRacingPenguinMarioWon | `integer` |  |
| oRacingPenguinReachedBottom | `integer` |  |
| oRacingPenguinMarioCheated | `integer` |  |
| oSmallPenguinUnk88 | `integer` |  |
| oSmallPenguinUnk100 | `integer` |  |
| oSmallPenguinUnk104 | `number` |  |
| oSmallPenguinUnk108 | `number` |  |
| oSmallPenguinUnk110 | `integer` |  |
| oSLWalkingPenguinWindCollisionXPos | `number` |  |
| oSLWalkingPenguinWindCollisionZPos | `number` |  |
| oSLWalkingPenguinCurStep | `integer` |  |
| oSLWalkingPenguinCurStepTimer | `integer` |  |
| oPiranhaPlantSleepMusicState | `integer` |  |
| oPiranhaPlantScale | `number` |  |
| oFirePiranhaPlantNeutralScale | `number` |  |
| oFirePiranhaPlantScale | `number` |  |
| oFirePiranhaPlantActive | `integer` |  |
| oFirePiranhaPlantDeathSpinTimer | `integer` |  |
| oFirePiranhaPlantDeathSpinVel | `number` |  |
| oPitouneUnkF4 | `number` |  |
| oPitouneUnkF8 | `number` |  |
| oPitouneUnkFC | `number` |  |
| oPlatformTimer | `integer` |  |
| oPlatformUnkF8 | [Object](structs.md#Object) |  |
| oPlatformUnkFC | `integer` |  |
| oPlatformUnk10C | `number` |  |
| oPlatformUnk110 | `number` |  |
| oPlatformOnTrackBaseBallIndex | `integer` |  |
| oPlatformOnTrackDistMovedSinceLastBall | `number` |  |
| oPlatformOnTrackSkiLiftRollVel | `number` |  |
| oPlatformOnTrackStartWaypoint | [Waypoint](structs.md#Waypoint) |  |
| oPlatformOnTrackPrevWaypoint | [Waypoint](structs.md#Waypoint) |  |
| oPlatformOnTrackPrevWaypointFlags | `integer` |  |
| oPlatformOnTrackPitch | `integer` |  |
| oPlatformOnTrackYaw | `integer` |  |
| oPlatformOnTrackOffsetY | `number` |  |
| oPlatformOnTrackIsNotSkiLift | `integer` |  |
| oPlatformOnTrackIsNotHMC | `integer` |  |
| oPlatformOnTrackType | `integer` |  |
| oPlatformOnTrackWasStoodOn | `integer` |  |
| oPlatformSpawnerUnkF4 | `integer` |  |
| oPlatformSpawnerUnkF8 | `integer` |  |
| oPlatformSpawnerUnkFC | `integer` |  |
| oPlatformSpawnerUnk100 | `number` |  |
| oPlatformSpawnerUnk104 | `number` |  |
| oPlatformSpawnerUnk108 | `number` |  |
| oPokeyAliveBodyPartFlags | `integer` |  |
| oPokeyNumAliveBodyParts | `integer` |  |
| oPokeyBottomBodyPartSize | `number` |  |
| oPokeyHeadWasKilled | `integer` |  |
| oPokeyTargetYaw | `integer` |  |
| oPokeyChangeTargetTimer | `integer` |  |
| oPokeyTurningAwayFromWall | `integer` |  |
| oPokeyBodyPartDeathDelayAfterHeadKilled | `integer` |  |
| oPokeyBodyPartBlinkTimer | `integer` |  |
| oDDDPoleVel | `number` |  |
| oDDDPoleMaxOffset | `number` |  |
| oDDDPoleOffset | `number` |  |
| oPyramidTopPillarsTouched | `integer` |  |
| oPyramidTopFragmentsScale | `number` |  |
| oRollingLogUnkF4 | `number` |  |
| oLllRotatingHexFlameUnkF4 | `number` |  |
| oLllRotatingHexFlameUnkF8 | `number` |  |
| oLllRotatingHexFlameUnkFC | `number` |  |
| oScuttlebugUnkF4 | `integer` |  |
| oScuttlebugUnkF8 | `integer` |  |
| oScuttlebugUnkFC | `integer` |  |
| oScuttlebugSpawnerUnk88 | `integer` |  |
| oScuttlebugSpawnerUnkF4 | `integer` |  |
| oSeesawPlatformPitchVel | `number` |  |
| oShipPart3UnkF4 | `integer` |  |
| oShipPart3UnkF8 | `integer` |  |
| oSinkWhenSteppedOnUnk104 | `integer` |  |
| oSinkWhenSteppedOnUnk108 | `number` |  |
| oSkeeterTargetAngle | `integer` |  |
| oSkeeterUnkF8 | `integer` |  |
| oSkeeterUnkFC | `number` |  |
| oSkeeterWaitTime | `integer` |  |
| oSkeeterLastWaterY | `number` |  |
| oSkeeterUnk1AC | `integer` |  |
| oJrbSlidingBoxUnkF4 | [Object](structs.md#Object) |  |
| oJrbSlidingBoxUnkF8 | `integer` |  |
| oJrbSlidingBoxUnkFC | `number` |  |
| oWFSlidBrickPtfmMovVel | `number` |  |
| oSmokeTimer | `integer` |  |
| oSnowmansBottomUnkF4 | `number` |  |
| oSnowmansBottomUnkF8 | `integer` |  |
| oSnowmansBottomUnk1AC | `integer` |  |
| oSnowmansHeadUnkF4 | `integer` |  |
| oSLSnowmanWindOriginalYaw | `integer` |  |
| oSnufitRecoil | `integer` |  |
| oSnufitScale | `number` |  |
| oSnufitCircularPeriod | `integer` |  |
| oSnufitBodyScalePeriod | `integer` |  |
| oSnufitBodyBaseScale | `integer` |  |
| oSnufitBullets | `integer` |  |
| oSnufitXOffset | `integer` |  |
| oSnufitYOffset | `integer` |  |
| oSnufitZOffset | `integer` |  |
| oSnufitBodyScale | `integer` |  |
| oSpindelUnkF4 | `integer` |  |
| oSpindelUnkF8 | `integer` |  |
| oSpinningHeartTotalSpin | `integer` |  |
| oSpinningHeartPlayedSound | `integer` |  |
| oSpinyTimeUntilTurn | `integer` |  |
| oSpinyTargetYaw | `integer` |  |
| oSpinyTurningAwayFromWall | `integer` |  |
| oSoundEffectUnkF4 | `integer` |  |
| oStarSpawnDisFromHome | `number` |  |
| oStarSpawnUnkFC | `number` |  |
| oStarSpawnExtCutsceneFlags | `integer` |  |
| oHiddenStarTriggerCounter | `integer` |  |
| oSparkleSpawnUnk1B0 | `integer` |  |
| oUnlockDoorStarState | `integer` |  |
| oUnlockDoorStarTimer | `integer` |  |
| oUnlockDoorStarYawVel | `integer` |  |
| oCelebStarUnkF4 | `integer` |  |
| oCelebStarDiameterOfRotation | `integer` |  |
| oStarSelectorType | `integer` |  |
| oStarSelectorTimer | `integer` |  |
| oStarSelectorSize | `number` |  |
| oSushiSharkUnkF4 | `integer` |  |
| oSwingPlatformAngle | `number` |  |
| oSwingPlatformSpeed | `number` |  |
| oSwoopBonkCountdown | `integer` |  |
| oSwoopTargetPitch | `integer` |  |
| oSwoopTargetYaw | `integer` |  |
| oThwompRandomTimer | `integer` |  |
| oTiltingPyramidNormalX | `number` |  |
| oTiltingPyramidNormalY | `number` |  |
| oTiltingPyramidNormalZ | `number` |  |
| oTiltingPyramidMarioOnPlatform | `integer` |  |
| oToadMessageDialogId | `integer` |  |
| oToadMessageRecentlyTalked | `integer` |  |
| oToadMessageState | `integer` |  |
| oToxBoxMovementStep | `integer` |  |
| oTTCRotatingSolidNumTurns | `integer` |  |
| oTTCRotatingSolidNumSides | `integer` |  |
| oTTCRotatingSolidRotationDelay | `integer` |  |
| oTTCRotatingSolidVelY | `number` |  |
| oTTCRotatingSolidSoundTimer | `integer` |  |
| oTTCPendulumAccelDir | `number` |  |
| oTTCPendulumAngle | `number` |  |
| oTTCPendulumAngleVel | `number` |  |
| oTTCPendulumAngleAccel | `number` |  |
| oTTCPendulumDelay | `integer` |  |
| oTTCPendulumSoundTimer | `integer` |  |
| oTTCTreadmillBigSurface | `Pointer` <`integer`> | read-only |
| oTTCTreadmillSmallSurface | `Pointer` <`integer`> | read-only |
| oTTCTreadmillSpeed | `number` |  |
| oTTCTreadmillTargetSpeed | `number` |  |
| oTTCTreadmillTimeUntilSwitch | `integer` |  |
| oTTCMovingBarDelay | `integer` |  |
| oTTCMovingBarStoppedTimer | `integer` |  |
| oTTCMovingBarOffset | `number` |  |
| oTTCMovingBarSpeed | `number` |  |
| oTTCMovingBarStartOffset | `number` |  |
| oTTCCogDir | `number` |  |
| oTTCCogSpeed | `number` |  |
| oTTCCogTargetVel | `number` |  |
| oTTCPitBlockPeakY | `number` |  |
| oTTCPitBlockDir | `integer` |  |
| oTTCPitBlockWaitTime | `integer` |  |
| oTTCElevatorDir | `number` |  |
| oTTCElevatorPeakY | `number` |  |
| oTTCElevatorMoveTime | `integer` |  |
| oTTC2DRotatorMinTimeUntilNextTurn | `integer` |  |
| oTTC2DRotatorTargetYaw | `integer` |  |
| oTTC2DRotatorIncrement | `integer` |  |
| oTTC2DRotatorRandomDirTimer | `integer` |  |
| oTTC2DRotatorSpeed | `integer` |  |
| oTTCSpinnerDir | `integer` |  |
| oTTCChangeDirTimer | `integer` |  |
| oBetaTrampolineMarioOnTrampoline | `integer` |  |
| oTreasureChestCurrentAnswer | `integer` |  |
| oTreasureChestIsLastInteractionIncorrect | `integer` |  |
| oTreasureChestIsAboveWater | `integer` |  |
| oTreasureChestSound | `integer` |  |
| oTreasureChestLastNetworkPlayerIndex | `integer` |  |
| oTreeSnowOrLeafUnkF4 | `integer` |  |
| oTreeSnowOrLeafUnkF8 | `integer` |  |
| oTreeSnowOrLeafUnkFC | `integer` |  |
| oTumblingBridgeUnkF4 | `integer` |  |
| oTweesterScaleTimer | `integer` |  |
| oTweesterUnused | `integer` |  |
| oUkikiTauntCounter | `integer` |  |
| oUkikiTauntsToBeDone | `integer` |  |
| oUkikiChaseFleeRange | `number` |  |
| oUkikiTextState | `integer` |  |
| oUkikiTextboxTimer | `integer` |  |
| oUkikiCageSpinTimer | `integer` |  |
| oUkikiHasCap | `integer` |  |
| oUkikiCageNextAction | `integer` |  |
| oUnagiUnkF4 | `number` |  |
| oUnagiUnkF8 | `number` |  |
| oUnagiUnk110 | `number` |  |
| oUnagiUnk1AC | `number` |  |
| oUnagiUnk1B0 | `integer` |  |
| oUnagiUnk1B2 | `integer` |  |
| oWaterBombVerticalStretch | `number` |  |
| oWaterBombStretchSpeed | `number` |  |
| oWaterBombOnGround | `integer` |  |
| oWaterBombNumBounces | `number` |  |
| oWaterBombSpawnerBombActive | `integer` |  |
| oWaterBombSpawnerTimeToSpawn | `integer` |  |
| oWaterCannonUnkF4 | `integer` |  |
| oWaterCannonUnkF8 | `integer` |  |
| oWaterCannonUnkFC | `integer` |  |
| oWaterCannonUnk100 | `integer` |  |
| oCannonBarrelBubblesUnkF4 | `number` |  |
| oWaterLevelPillarDrained | `integer` |  |
| oWaterLevelTriggerUnkF4 | `integer` |  |
| oWaterLevelTriggerTargetWaterLevel | `integer` |  |
| oWaterObjUnkF4 | `integer` |  |
| oWaterObjUnkF8 | `integer` |  |
| oWaterObjUnkFC | `integer` |  |
| oWaterObjUnk100 | `integer` |  |
| oWaterRingScalePhaseX | `integer` |  |
| oWaterRingScalePhaseY | `integer` |  |
| oWaterRingScalePhaseZ | `integer` |  |
| oWaterRingNormalX | `number` |  |
| oWaterRingNormalY | `number` |  |
| oWaterRingNormalZ | `number` |  |
| oWaterRingMarioDistInFront | `number` |  |
| oWaterRingIndex | `integer` |  |
| oWaterRingAvgScale | `number` |  |
| oWaterRingSpawnerRingsCollected | `integer` |  |
| oWaterRingMgrNextRingIndex | `integer` |  |
| oWaterRingMgrLastRingCollected | `integer` |  |
| oWaveTrailSize | `number` |  |
| oWhirlpoolInitFacePitch | `integer` |  |
| oWhirlpoolInitFaceRoll | `integer` |  |
| oWhirlpoolTimeout | `integer` |  |
| oWhitePuffUnkF4 | `number` |  |
| oWhitePuffUnkF8 | `integer` |  |
| oWhitePuffUnkFC | `integer` |  |
| oStrongWindParticlePenguinObj | [Object](structs.md#Object) |  |
| oWhompShakeVal | `integer` |  |
| oWigglerFallThroughFloorsHeight | `number` |  |
| oWigglerSegments | [ChainSegment](structs.md#ChainSegment) | read-only |
| oWigglerWalkAnimSpeed | `number` |  |
| oWigglerSquishSpeed | `number` |  |
| oWigglerTimeUntilRandomTurn | `integer` |  |
| oWigglerTargetYaw | `integer` |  |
| oWigglerWalkAwayFromWallTimer | `integer` |  |
| oWigglerUnused | `integer` |  |
| oWigglerTextStatus | `integer` |  |
| oLllWoodPieceOscillationTimer | `integer` |  |
| oWoodenPostTotalMarioAngle | `integer` |  |
| oWoodenPostPrevAngleToMario | `integer` |  |
| oWoodenPostSpeedY | `number` |  |
| oWoodenPostMarioPounding | `integer` |  |
| oWoodenPostOffsetY | `number` |  |
| oYoshiBlinkTimer | `integer` |  |
| oYoshiChosenHome | `integer` |  |
| oYoshiTargetYaw | `integer` |  |
| oBreakableWallForce | `integer` |  |
| oLightID | `integer` |  |

[:arrow_up_small:](#)

<br />

## [ObjectHitbox](#ObjectHitbox)

| Field | Type | Access |
| ----- | ---- | ------ |
| interactType | `integer` |  |
| health | `integer` |  |
| damageOrCoinValue | `integer` |  |
| numLootCoins | `integer` |  |
| downOffset | `integer` |  |
| radius | `integer` |  |
| height | `integer` |  |
| hurtboxRadius | `integer` |  |
| hurtboxHeight | `integer` |  |

[:arrow_up_small:](#)

<br />

## [ObjectNode](#ObjectNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| gfx | [GraphNodeObject](structs.md#GraphNodeObject) | read-only |
| next | [ObjectNode](structs.md#ObjectNode) | read-only |
| prev | [ObjectNode](structs.md#ObjectNode) | read-only |

[:arrow_up_small:](#)

<br />

## [ObjectWarpNode](#ObjectWarpNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| node | [WarpNode](structs.md#WarpNode) | read-only |
| object | [Object](structs.md#Object) |  |
| next | [ObjectWarpNode](structs.md#ObjectWarpNode) | read-only |

[:arrow_up_small:](#)

<br />

## [Painting](#Painting)

| Field | Type | Access |
| ----- | ---- | ------ |
| id | `integer` | read-only |
| imageCount | `integer` | read-only |
| textureType | `integer` | read-only |
| lastFloor | `integer` |  |
| currFloor | `integer` |  |
| floorEntered | `integer` |  |
| state | `integer` |  |
| pitch | `number` |  |
| yaw | `number` |  |
| posX | `number` |  |
| posY | `number` |  |
| posZ | `number` |  |
| currRippleMag | `number` |  |
| passiveRippleMag | `number` |  |
| entryRippleMag | `number` |  |
| rippleDecay | `number` |  |
| passiveRippleDecay | `number` |  |
| entryRippleDecay | `number` |  |
| currRippleRate | `number` |  |
| passiveRippleRate | `number` |  |
| entryRippleRate | `number` |  |
| dispersionFactor | `number` |  |
| passiveDispersionFactor | `number` |  |
| entryDispersionFactor | `number` |  |
| rippleTimer | `number` |  |
| rippleX | `number` |  |
| rippleY | `number` |  |
| textureArray | `Array` <`Pointer` <`Texture`>> | read-only |
| textureWidth | `integer` | read-only |
| textureHeight | `integer` | read-only |
| rippleTrigger | `integer` |  |
| alpha | `integer` |  |
| marioWasUnder | `integer` |  |
| marioIsUnder | `integer` |  |
| marioWentUnder | `integer` |  |
| size | `number` |  |

[:arrow_up_small:](#)

<br />

## [PaintingValues](#PaintingValues)

| Field | Type | Access |
| ----- | ---- | ------ |
| cotmc_painting | [Painting](structs.md#Painting) |  |
| bob_painting | [Painting](structs.md#Painting) |  |
| ccm_painting | [Painting](structs.md#Painting) |  |
| wf_painting | [Painting](structs.md#Painting) |  |
| jrb_painting | [Painting](structs.md#Painting) |  |
| lll_painting | [Painting](structs.md#Painting) |  |
| ssl_painting | [Painting](structs.md#Painting) |  |
| hmc_painting | [Painting](structs.md#Painting) |  |
| ddd_painting | [Painting](structs.md#Painting) |  |
| wdw_painting | [Painting](structs.md#Painting) |  |
| thi_tiny_painting | [Painting](structs.md#Painting) |  |
| ttm_painting | [Painting](structs.md#Painting) |  |
| ttc_painting | [Painting](structs.md#Painting) |  |
| sl_painting | [Painting](structs.md#Painting) |  |
| thi_huge_painting | [Painting](structs.md#Painting) |  |
| ttm_slide_painting | [Painting](structs.md#Painting) |  |

[:arrow_up_small:](#)

<br />

## [PlayerCameraState](#PlayerCameraState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | `integer` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| faceAngle | [Vec3s](structs.md#Vec3s) | read-only |
| headRotation | [Vec3s](structs.md#Vec3s) | read-only |
| unused | `integer` |  |
| cameraEvent | `integer` |  |
| usedObj | [Object](structs.md#Object) |  |

[:arrow_up_small:](#)

<br />

## [PlayerPalette](#PlayerPalette)

| Field | Type | Access |
| ----- | ---- | ------ |
| parts | `Array` <`Color`> | read-only |

[:arrow_up_small:](#)

<br />

## [RayIntersectionInfo](#RayIntersectionInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| surface | [Surface](structs.md#Surface) |  |
| hitPos | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [RomhackCameraSettings](#RomhackCameraSettings)

| Field | Type | Access |
| ----- | ---- | ------ |
| enable | [enum RomhackCameraOverride](constants.md#enum-RomhackCameraOverride) |  |
| centering | `integer` |  |
| dpad | `integer` |  |
| collisions | `integer` |  |
| slowFall | `integer` |  |
| zoomedInDist | `integer` |  |
| zoomedOutDist | `integer` |  |
| zoomedInHeight | `integer` |  |
| zoomedOutHeight | `integer` |  |
| modsOnly | `integer` |  |

[:arrow_up_small:](#)

<br />

## [ServerSettings](#ServerSettings)

| Field | Type | Access |
| ----- | ---- | ------ |
| playerInteractions | [enum PlayerInteractions](constants.md#enum-PlayerInteractions) |  |
| bouncyLevelBounds | [enum BouncyLevelBounds](constants.md#enum-BouncyLevelBounds) |  |
| pvpType | [enum PvpType](constants.md#enum-PvpType) |  |
| playerKnockbackStrength | `integer` |  |
| stayInLevelAfterStar | `integer` |  |
| skipIntro | `integer` |  |
| bubbleDeath | `integer` |  |
| enablePlayersInLevelDisplay | `integer` |  |
| enablePlayerList | `integer` |  |
| headlessServer | `integer` |  |
| nametags | `integer` |  |
| maxPlayers | `integer` |  |
| pauseAnywhere | `integer` |  |

[:arrow_up_small:](#)

<br />

## [SpawnInfo](#SpawnInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| startPos | [Vec3s](structs.md#Vec3s) | read-only |
| startAngle | [Vec3s](structs.md#Vec3s) | read-only |
| areaIndex | `integer` |  |
| activeAreaIndex | `integer` |  |
| behaviorArg | `integer` |  |
| unk18 | [GraphNode](structs.md#GraphNode) | read-only |
| next | [SpawnInfo](structs.md#SpawnInfo) | read-only |
| syncID | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [SpawnParticlesInfo](#SpawnParticlesInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| behParam | `integer` |  |
| count | `integer` |  |
| model | `integer` | read-only |
| offsetY | `integer` |  |
| forwardVelBase | `integer` |  |
| forwardVelRange | `integer` |  |
| velYBase | `integer` |  |
| velYRange | `integer` |  |
| gravity | `integer` |  |
| dragStrength | `integer` |  |
| sizeBase | `number` |  |
| sizeRange | `number` |  |

[:arrow_up_small:](#)

<br />

## [StarPositions](#StarPositions)

| Field | Type | Access |
| ----- | ---- | ------ |
| KoopaBobStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KoopaThiStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KingBobombStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KingWhompStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| EyerockStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BigBullyStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| ChillBullyStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BigPiranhasStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| TuxieMotherStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| WigglerStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| PssSlideStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| RacingPenguinStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| TreasureJrbStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| TreasureChestStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| GhostHuntBooStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KleptoStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| MerryGoRoundStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| MrIStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BalconyBooStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BigBullyTrioStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| MantaRayStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| SnowmanHeadStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| CcmSlideStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| UkikiCageStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| UnagiStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| JetstreamRingStarPos | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [StarsNeededForDialog](#StarsNeededForDialog)

| Field | Type | Access |
| ----- | ---- | ------ |
| dialog1 | `integer` |  |
| dialog2 | `integer` |  |
| dialog3 | `integer` |  |
| dialog4 | `integer` |  |
| dialog5 | `integer` |  |
| dialog6 | `integer` |  |

[:arrow_up_small:](#)

<br />

## [StaticObjectCollision](#StaticObjectCollision)

| Field | Type | Access |
| ----- | ---- | ------ |
| index | `integer` | read-only |
| length | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [Surface](#Surface)

| Field | Type | Access |
| ----- | ---- | ------ |
| type | `integer` |  |
| flags | `integer` |  |
| room | `integer` |  |
| force | `integer` |  |
| lowerY | `integer` |  |
| upperY | `integer` |  |
| vertex1 | [Vec3s](structs.md#Vec3s) | read-only |
| vertex2 | [Vec3s](structs.md#Vec3s) | read-only |
| vertex3 | [Vec3s](structs.md#Vec3s) | read-only |
| prevVertex1 | [Vec3s](structs.md#Vec3s) | read-only |
| prevVertex2 | [Vec3s](structs.md#Vec3s) | read-only |
| prevVertex3 | [Vec3s](structs.md#Vec3s) | read-only |
| normal | [Vec3f](structs.md#Vec3f) | read-only |
| originOffset | `number` |  |
| modifiedTimestamp | `integer` |  |
| object | [Object](structs.md#Object) |  |

[:arrow_up_small:](#)

<br />

## [TextureInfo](#TextureInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| texture | `Pointer` <`Texture`> | read-only |
| name | `string` | read-only |
| width | `integer` | read-only |
| height | `integer` | read-only |
| format | `integer` | read-only |
| size | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [Vec2f](#Vec2f)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `number` |  |
| y | `number` |  |

[:arrow_up_small:](#)

<br />

## [Vec2i](#Vec2i)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `integer` |  |
| y | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vec2s](#Vec2s)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `integer` |  |
| y | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vec3f](#Vec3f)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `number` |  |
| y | `number` |  |
| z | `number` |  |

[:arrow_up_small:](#)

<br />

## [Vec3i](#Vec3i)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `integer` |  |
| y | `integer` |  |
| z | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vec3s](#Vec3s)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `integer` |  |
| y | `integer` |  |
| z | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vec4f](#Vec4f)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `number` |  |
| y | `number` |  |
| z | `number` |  |
| w | `number` |  |

[:arrow_up_small:](#)

<br />

## [Vec4i](#Vec4i)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `integer` |  |
| y | `integer` |  |
| z | `integer` |  |
| w | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vec4s](#Vec4s)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `integer` |  |
| y | `integer` |  |
| z | `integer` |  |
| w | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vtx](#Vtx)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `number` |  |
| y | `number` |  |
| z | `number` |  |
| flag | `integer` |  |
| tu | `integer` |  |
| tv | `integer` |  |
| r | `integer` |  |
| nx | `integer` |  |
| g | `integer` |  |
| ny | `integer` |  |
| b | `integer` |  |
| nz | `integer` |  |
| a | `integer` |  |

[:arrow_up_small:](#)

<br />

## [WallCollisionData](#WallCollisionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `number` |  |
| y | `number` |  |
| z | `number` |  |
| offsetY | `number` |  |
| radius | `number` |  |
| unused | `integer` |  |
| numWalls | `integer` |  |
| walls | `Array` <`Surface`> |  |
| normalAddition | [Vec3f](structs.md#Vec3f) | read-only |
| normalCount | `integer` |  |

[:arrow_up_small:](#)

<br />

## [WarpNode](#WarpNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| id | `integer` |  |
| destLevel | `integer` |  |
| destArea | `integer` |  |
| destNode | `integer` |  |

[:arrow_up_small:](#)

<br />

## [WaterDropletParams](#WaterDropletParams)

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | `integer` |  |
| model | `integer` | read-only |
| behavior | `Pointer` <`BehaviorScript`> | read-only |
| moveAngleRange | `integer` |  |
| moveRange | `integer` |  |
| randForwardVelOffset | `number` |  |
| randForwardVelScale | `number` |  |
| randYVelOffset | `number` |  |
| randYVelScale | `number` |  |
| randSizeOffset | `number` |  |
| randSizeScale | `number` |  |

[:arrow_up_small:](#)

<br />

## [Waypoint](#Waypoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | `integer` |  |
| pos | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [Whirlpool](#Whirlpool)

| Field | Type | Access |
| ----- | ---- | ------ |
| pos | [Vec3s](structs.md#Vec3s) | read-only |
| strength | `integer` |  |

[:arrow_up_small:](#)

<br />

