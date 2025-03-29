## [:rewind: Lua Reference](lua.md)

# Supported Structs
- [AnimInfo](#AnimInfo)
- [Animation](#Animation)
- [AnimationTable](#AnimationTable)
- [Area](#Area)
- [BehaviorDialogs](#BehaviorDialogs)
- [BehaviorTrajectories](#BehaviorTrajectories)
- [BehaviorValues](#BehaviorValues)
- [BullyCollisionData](#BullyCollisionData)
- [Camera](#Camera)
- [CameraFOVStatus](#CameraFOVStatus)
- [CameraOverride](#CameraOverride)
- [CameraStoredInfo](#CameraStoredInfo)
- [CameraTrigger](#CameraTrigger)
- [ChainSegment](#ChainSegment)
- [Character](#Character)
- [Color](#Color)
- [Controller](#Controller)
- [CustomLevelInfo](#CustomLevelInfo)
- [Cutscene](#Cutscene)
- [CutsceneSplinePoint](#CutsceneSplinePoint)
- [CutsceneVariable](#CutsceneVariable)
- [DateTime](#DateTime)
- [DisplayListNode](#DisplayListNode)
- [DjuiColor](#DjuiColor)
- [DjuiInteractableTheme](#DjuiInteractableTheme)
- [DjuiPanelTheme](#DjuiPanelTheme)
- [DjuiTheme](#DjuiTheme)
- [DjuiThreePanelTheme](#DjuiThreePanelTheme)
- [ExclamationBoxContent](#ExclamationBoxContent)
- [FirstPersonCamera](#FirstPersonCamera)
- [FloorGeometry](#FloorGeometry)
- [FnGraphNode](#FnGraphNode)
- [Gfx](#Gfx)
- [GlobalObjectAnimations](#GlobalObjectAnimations)
- [GlobalObjectCollisionData](#GlobalObjectCollisionData)
- [GlobalTextures](#GlobalTextures)
- [GraphNode](#GraphNode)
- [GraphNodeAnimatedPart](#GraphNodeAnimatedPart)
- [GraphNodeBackground](#GraphNodeBackground)
- [GraphNodeBillboard](#GraphNodeBillboard)
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
- [GraphNodeShadow](#GraphNodeShadow)
- [GraphNodeStart](#GraphNodeStart)
- [GraphNodeSwitchCase](#GraphNodeSwitchCase)
- [GraphNodeTranslation](#GraphNodeTranslation)
- [GraphNodeTranslationRotation](#GraphNodeTranslationRotation)
- [GraphNode_802A45E4](#GraphNode_802A45E4)
- [HandheldShakePoint](#HandheldShakePoint)
- [HudUtilsRotation](#HudUtilsRotation)
- [InstantWarp](#InstantWarp)
- [LakituState](#LakituState)
- [LevelValues](#LevelValues)
- [LinearTransitionPoint](#LinearTransitionPoint)
- [MarioAnimDmaRelatedThing](#MarioAnimDmaRelatedThing)
- [MarioAnimation](#MarioAnimation)
- [MarioBodyState](#MarioBodyState)
- [MarioState](#MarioState)
- [Mat4](#Mat4)
- [Mod](#Mod)
- [ModAudio](#ModAudio)
- [ModAudioSampleCopies](#ModAudioSampleCopies)
- [ModFile](#ModFile)
- [ModeTransitionInfo](#ModeTransitionInfo)
- [NametagsSettings](#NametagsSettings)
- [NetworkPlayer](#NetworkPlayer)
- [Object](#Object)
- [ObjectHitbox](#ObjectHitbox)
- [ObjectNode](#ObjectNode)
- [ObjectWarpNode](#ObjectWarpNode)
- [OffsetSizePair](#OffsetSizePair)
- [Painting](#Painting)
- [PaintingMeshVertex](#PaintingMeshVertex)
- [PaintingValues](#PaintingValues)
- [ParallelTrackingPoint](#ParallelTrackingPoint)
- [PlayerCameraState](#PlayerCameraState)
- [PlayerGeometry](#PlayerGeometry)
- [PlayerPalette](#PlayerPalette)
- [RayIntersectionInfo](#RayIntersectionInfo)
- [RomhackCameraSettings](#RomhackCameraSettings)
- [SPTask](#SPTask)
- [ServerSettings](#ServerSettings)
- [SoundState](#SoundState)
- [SpawnInfo](#SpawnInfo)
- [SpawnParticlesInfo](#SpawnParticlesInfo)
- [StarPositions](#StarPositions)
- [StarsNeededForDialog](#StarsNeededForDialog)
- [Struct802A272C](#Struct802A272C)
- [Surface](#Surface)
- [TextureInfo](#TextureInfo)
- [TransitionInfo](#TransitionInfo)
- [UnusedArea28](#UnusedArea28)
- [VblankHandler](#VblankHandler)
- [Vec2f](#Vec2f)
- [Vec3f](#Vec3f)
- [Vec3s](#Vec3s)
- [Vec4f](#Vec4f)
- [Vec4s](#Vec4s)
- [Vtx](#Vtx)
- [Vtx_Interp](#Vtx_Interp)
- [WallCollisionData](#WallCollisionData)
- [WarpNode](#WarpNode)
- [WarpTransition](#WarpTransition)
- [WarpTransitionData](#WarpTransitionData)
- [WaterDropletParams](#WaterDropletParams)
- [Waypoint](#Waypoint)
- [Whirlpool](#Whirlpool)
- [struct802A1230](#struct802A1230)

<br />

## [AnimInfo](#AnimInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| animAccel | `integer` |  |
| animFrame | `integer` |  |
| animFrameAccelAssist | `integer` |  |
| animID | `integer` |  |
| animTimer | `integer` |  |
| animYTrans | `integer` |  |
| curAnim | [Animation](structs.md#Animation) |  |
| prevAnimFrame | `integer` |  |
| prevAnimFrameTimestamp | `integer` |  |
| prevAnimID | `integer` |  |
| prevAnimPtr | [Animation](structs.md#Animation) |  |

[:arrow_up_small:](#)

<br />

## [Animation](#Animation)

| Field | Type | Access |
| ----- | ---- | ------ |
| animYTransDivisor | `integer` |  |
| flags | `integer` |  |
| index | `Pointer` <`integer`> |  |
| indexLength | `integer` |  |
| length | `integer` | read-only |
| loopEnd | `integer` |  |
| loopStart | `integer` |  |
| startFrame | `integer` |  |
| unusedBoneCount | `integer` |  |
| values | `Pointer` <`integer`> |  |
| valuesLength | `integer` |  |

[:arrow_up_small:](#)

<br />

## [AnimationTable](#AnimationTable)

| Field | Type | Access |
| ----- | ---- | ------ |
| count | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [Area](#Area)

| Field | Type | Access |
| ----- | ---- | ------ |
| camera | [Camera](structs.md#Camera) |  |
| dialog | `Array` <`integer`> |  |
| flags | `integer` |  |
| index | `integer` |  |
| instantWarps | [InstantWarp](structs.md#InstantWarp) |  |
| localAreaTimer | `integer` | read-only |
| macroObjects | `Pointer` <`integer`> | read-only |
| macroObjectsAltered | `Pointer` <`integer`> | read-only |
| musicParam | `integer` |  |
| musicParam2 | `integer` |  |
| nextSyncID | `integer` | read-only |
| numRedCoins | `integer` |  |
| numSecrets | `integer` |  |
| objectSpawnInfos | [SpawnInfo](structs.md#SpawnInfo) | read-only |
| paintingWarpNodes | [WarpNode](structs.md#WarpNode) | read-only |
| surfaceRooms | `Pointer` <`integer`> | read-only |
| terrainData | `Pointer` <`integer`> | read-only |
| terrainType | `integer` |  |
| warpNodes | [ObjectWarpNode](structs.md#ObjectWarpNode) | read-only |
| whirlpools | `Array` <`Whirlpool`> |  |

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
| TuxieMotherBabyFoundDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| TuxieMotherBabyWrongDialog | [enum DialogId](constants.md#enum-DialogId) |  |
| TuxieMotherDialog | [enum DialogId](constants.md#enum-DialogId) |  |
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
| BowlingBallBob2Trajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallBobTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallThiLargeTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallThiSmallTrajectory | `Pointer` <`Trajectory`> |  |
| BowlingBallTtmTrajectory | `Pointer` <`Trajectory`> |  |
| KoopaBobTrajectory | `Pointer` <`Trajectory`> |  |
| KoopaThiTrajectory | `Pointer` <`Trajectory`> |  |
| Mips10Trajectory | `Pointer` <`Trajectory`> |  |
| Mips2Trajectory | `Pointer` <`Trajectory`> |  |
| Mips3Trajectory | `Pointer` <`Trajectory`> |  |
| Mips4Trajectory | `Pointer` <`Trajectory`> |  |
| Mips5Trajectory | `Pointer` <`Trajectory`> |  |
| Mips6Trajectory | `Pointer` <`Trajectory`> |  |
| Mips7Trajectory | `Pointer` <`Trajectory`> |  |
| Mips8Trajectory | `Pointer` <`Trajectory`> |  |
| Mips9Trajectory | `Pointer` <`Trajectory`> |  |
| MipsTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformBitfsTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformCcmTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformHmcTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformLll2Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformLllTrajectory | `Pointer` <`Trajectory`> |  |
| PlatformRr2Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformRr3Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformRr4Trajectory | `Pointer` <`Trajectory`> |  |
| PlatformRrTrajectory | `Pointer` <`Trajectory`> |  |
| RacingPenguinTrajectory | `Pointer` <`Trajectory`> |  |
| SnowmanHeadTrajectory | `Pointer` <`Trajectory`> |  |
| Unagi2Trajectory | `Pointer` <`Trajectory`> |  |
| UnagiTrajectory | `Pointer` <`Trajectory`> |  |

[:arrow_up_small:](#)

<br />

## [BehaviorValues](#BehaviorValues)

| Field | Type | Access |
| ----- | ---- | ------ |
| BowlingBallBob2Speed | `number` |  |
| BowlingBallBobSpeed | `number` |  |
| BowlingBallThiLargeSpeed | `number` |  |
| BowlingBallThiSmallSpeed | `number` |  |
| BowlingBallTtmSpeed | `number` |  |
| ChillBullyDeathPosY | `number` |  |
| CourtyardBoosRequirement | `integer` |  |
| GrateStarRequirement | `integer` |  |
| InfiniteRenderDistance | `integer` |  |
| KingBobombFVel | `number` |  |
| KingBobombHealth | `integer` |  |
| KingBobombYawVel | `integer` |  |
| KingWhompHealth | `integer` |  |
| KoopaBobAgility | `number` |  |
| KoopaCatchupAgility | `number` |  |
| KoopaThiAgility | `number` |  |
| MipsStar1Requirement | `integer` |  |
| MipsStar2Requirement | `integer` |  |
| MultipleCapCollection | `integer` |  |
| RacingPenguinBigHeight | `number` |  |
| RacingPenguinBigRadius | `number` |  |
| RacingPenguinHeight | `number` |  |
| RacingPenguinRadius | `number` |  |
| RespawnShellBoxes | `integer` |  |
| ShowStarDialog | `integer` |  |
| ShowStarMilestones | `integer` |  |
| ToadStar1Requirement | `integer` |  |
| ToadStar2Requirement | `integer` |  |
| ToadStar3Requirement | `integer` |  |
| dialogs | [BehaviorDialogs](structs.md#BehaviorDialogs) | read-only |
| starsNeededForDialog | [StarsNeededForDialog](structs.md#StarsNeededForDialog) | read-only |
| trajectories | [BehaviorTrajectories](structs.md#BehaviorTrajectories) | read-only |

[:arrow_up_small:](#)

<br />

## [BullyCollisionData](#BullyCollisionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| conversionRatio | `number` |  |
| posX | `number` |  |
| posZ | `number` |  |
| radius | `number` |  |
| velX | `number` |  |
| velZ | `number` |  |

[:arrow_up_small:](#)

<br />

## [Camera](#Camera)

| Field | Type | Access |
| ----- | ---- | ------ |
| areaCenX | `number` |  |
| areaCenY | `number` |  |
| areaCenZ | `number` |  |
| cutscene | `integer` |  |
| defMode | `integer` |  |
| doorStatus | `integer` |  |
| filler31 | `Array` <`integer`> |  |
| filler3C | `Array` <`integer`> |  |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| mode | `integer` |  |
| mtx | `Mat4` | read-only |
| nextYaw | `integer` |  |
| paletteEditorCap | `boolean` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| unusedVec1 | [Vec3f](structs.md#Vec3f) | read-only |
| yaw | `integer` |  |

[:arrow_up_small:](#)

<br />

## [CameraFOVStatus](#CameraFOVStatus)

| Field | Type | Access |
| ----- | ---- | ------ |
| decay | `integer` |  |
| fov | `number` |  |
| fovFunc | `integer` |  |
| fovOffset | `number` |  |
| shakeAmplitude | `number` |  |
| shakePhase | `integer` |  |
| shakeSpeed | `integer` |  |
| unusedIsSleeping | `integer` |  |

[:arrow_up_small:](#)

<br />

## [CameraOverride](#CameraOverride)

| Field | Type | Access |
| ----- | ---- | ------ |
| override | `boolean` |  |
| value | `integer` |  |

[:arrow_up_small:](#)

<br />

## [CameraStoredInfo](#CameraStoredInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| cannonYOffset | `number` |  |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| panDist | `number` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [CameraTrigger](#CameraTrigger)

| Field | Type | Access |
| ----- | ---- | ------ |
| area | `integer` |  |
| boundsX | `integer` |  |
| boundsY | `integer` |  |
| boundsYaw | `integer` |  |
| boundsZ | `integer` |  |
| centerX | `integer` |  |
| centerY | `integer` |  |
| centerZ | `integer` |  |

[:arrow_up_small:](#)

<br />

## [ChainSegment](#ChainSegment)

| Field | Type | Access |
| ----- | ---- | ------ |
| pitch | `integer` |  |
| posX | `number` |  |
| posY | `number` |  |
| posZ | `number` |  |
| roll | `integer` |  |
| yaw | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Character](#Character)

| Field | Type | Access |
| ----- | ---- | ------ |
| animAPose | `integer` | read-only |
| animAirForwardKb | `integer` | read-only |
| animAirKick | `integer` | read-only |
| animAirborneOnStomach | `integer` | read-only |
| animBackflip | `integer` | read-only |
| animBackwardAirKb | `integer` | read-only |
| animBackwardKb | `integer` | read-only |
| animBackwardSpinning | `integer` | read-only |
| animBackwardsWaterKb | `integer` | read-only |
| animBeingGrabbed | `integer` | read-only |
| animBendKnessRidingShell | `integer` | read-only |
| animBottomStuckInGround | `integer` | read-only |
| animBreakdance | `integer` | read-only |
| animClimbDownLedge | `integer` | read-only |
| animClimbUpPole | `integer` | read-only |
| animCoughing | `integer` | read-only |
| animCrawling | `integer` | read-only |
| animCreditsLookBackThenRun | `integer` | read-only |
| animCreditsLookUp | `integer` | read-only |
| animCreditsLowerHand | `integer` | read-only |
| animCreditsPeaceSign | `integer` | read-only |
| animCreditsRaiseHand | `integer` | read-only |
| animCreditsReturnFromLookUp | `integer` | read-only |
| animCreditsStartWalkLookUp | `integer` | read-only |
| animCreditsTakeOffCap | `integer` | read-only |
| animCreditsWaving | `integer` | read-only |
| animCrouchFromFastLongjump | `integer` | read-only |
| animCrouchFromSlideKick | `integer` | read-only |
| animCrouchFromSlowLongjump | `integer` | read-only |
| animCrouching | `integer` | read-only |
| animDive | `integer` | read-only |
| animDoubleJumpFall | `integer` | read-only |
| animDoubleJumpRise | `integer` | read-only |
| animDrowningPart1 | `integer` | read-only |
| animDrowningPart2 | `integer` | read-only |
| animDyingFallOver | `integer` | read-only |
| animDyingInQuicksand | `integer` | read-only |
| animDyingOnBack | `integer` | read-only |
| animDyingOnStomach | `integer` | read-only |
| animElectrocution | `integer` | read-only |
| animFallFromSlide | `integer` | read-only |
| animFallFromSlideKick | `integer` | read-only |
| animFallFromSlidingWithLightObj | `integer` | read-only |
| animFallFromWater | `integer` | read-only |
| animFallLandWithLightObj | `integer` | read-only |
| animFallOverBackwards | `integer` | read-only |
| animFallWithLightObj | `integer` | read-only |
| animFastLedgeGrab | `integer` | read-only |
| animFastLongjump | `integer` | read-only |
| animFinalBowserRaiseHandSpin | `integer` | read-only |
| animFinalBowserWingCapTakeOff | `integer` | read-only |
| animFireLavaBurn | `integer` | read-only |
| animFirstPerson | `integer` | read-only |
| animFirstPunch | `integer` | read-only |
| animFirstPunchFast | `integer` | read-only |
| animFlutterkick | `integer` | read-only |
| animFlutterkickWithObj | `integer` | read-only |
| animFlyFromCannon | `integer` | read-only |
| animForwardFlip | `integer` | read-only |
| animForwardKb | `integer` | read-only |
| animForwardSpinning | `integer` | read-only |
| animForwardSpinningFlip | `integer` | read-only |
| animGeneralFall | `integer` | read-only |
| animGeneralLand | `integer` | read-only |
| animGrabBowser | `integer` | read-only |
| animGrabHeavyObject | `integer` | read-only |
| animGrabPoleShort | `integer` | read-only |
| animGrabPoleSwingPart1 | `integer` | read-only |
| animGrabPoleSwingPart2 | `integer` | read-only |
| animGroundBonk | `integer` | read-only |
| animGroundKick | `integer` | read-only |
| animGroundPound | `integer` | read-only |
| animGroundPoundLanding | `integer` | read-only |
| animGroundThrow | `integer` | read-only |
| animHandstandIdle | `integer` | read-only |
| animHandstandJump | `integer` | read-only |
| animHandstandLeft | `integer` | read-only |
| animHandstandRight | `integer` | read-only |
| animHangOnCeiling | `integer` | read-only |
| animHangOnOwl | `integer` | read-only |
| animHeadStuckInGround | `integer` | read-only |
| animHeavyThrow | `integer` | read-only |
| animHoldingBowser | `integer` | read-only |
| animIdleHeadCenter | `integer` | read-only |
| animIdleHeadLeft | `integer` | read-only |
| animIdleHeadRight | `integer` | read-only |
| animIdleHeavyObj | `integer` | read-only |
| animIdleInQuicksand | `integer` | read-only |
| animIdleOnLedge | `integer` | read-only |
| animIdleOnPole | `integer` | read-only |
| animIdleWithLightObj | `integer` | read-only |
| animJumpLandWithLightObj | `integer` | read-only |
| animJumpRidingShell | `integer` | read-only |
| animJumpWithLightObj | `integer` | read-only |
| animLandFromDoubleJump | `integer` | read-only |
| animLandFromSingleJump | `integer` | read-only |
| animLandOnStomach | `integer` | read-only |
| animLegsStuckInGround | `integer` | read-only |
| animMissingCap | `integer` | read-only |
| animMoveInQuicksand | `integer` | read-only |
| animMoveOnWireNetLeft | `integer` | read-only |
| animMoveOnWireNetRight | `integer` | read-only |
| animOffsetEnabled | `integer` | read-only |
| animOffsetFeet | `number` | read-only |
| animOffsetHand | `number` | read-only |
| animOffsetLowYPoint | `number` | read-only |
| animPickUpLightObj | `integer` | read-only |
| animPlaceLightObj | `integer` | read-only |
| animPullDoorWalkIn | `integer` | read-only |
| animPushDoorWalkIn | `integer` | read-only |
| animPushing | `integer` | read-only |
| animPutCapOn | `integer` | read-only |
| animQuicklyPutCapOn | `integer` | read-only |
| animReachPocket | `integer` | read-only |
| animReleaseBowser | `integer` | read-only |
| animReturnFromHandstand | `integer` | read-only |
| animReturnFromStarDance | `integer` | read-only |
| animReturnFromWaterStarDance | `integer` | read-only |
| animReturnStarApproachDoor | `integer` | read-only |
| animRidingShell | `integer` | read-only |
| animRunWithLightObj | `integer` | read-only |
| animRunning | `integer` | read-only |
| animRunningUnused | `integer` | read-only |
| animSecondPunch | `integer` | read-only |
| animSecondPunchFast | `integer` | read-only |
| animShivering | `integer` | read-only |
| animShiveringReturnToIdle | `integer` | read-only |
| animShiveringWarmingHand | `integer` | read-only |
| animShocked | `integer` | read-only |
| animSidestepLeft | `integer` | read-only |
| animSidestepRight | `integer` | read-only |
| animSingleJump | `integer` | read-only |
| animSkidOnGround | `integer` | read-only |
| animSleepIdle | `integer` | read-only |
| animSleepLying | `integer` | read-only |
| animSleepStartLying | `integer` | read-only |
| animSlide | `integer` | read-only |
| animSlideDive | `integer` | read-only |
| animSlideKick | `integer` | read-only |
| animSlideMotionless | `integer` | read-only |
| animSlideflip | `integer` | read-only |
| animSlideflipLand | `integer` | read-only |
| animSlidejump | `integer` | read-only |
| animSlidingOnBottomWithLightObj | `integer` | read-only |
| animSlowLandFromDive | `integer` | read-only |
| animSlowLedgeGrab | `integer` | read-only |
| animSlowLongjump | `integer` | read-only |
| animSlowWalkWithLightObj | `integer` | read-only |
| animSoftBackKb | `integer` | read-only |
| animSoftFrontKb | `integer` | read-only |
| animStandAgainstWall | `integer` | read-only |
| animStandUpFromLavaBoost | `integer` | read-only |
| animStandUpFromSlidingWithLightObj | `integer` | read-only |
| animStarDance | `integer` | read-only |
| animStartCrawling | `integer` | read-only |
| animStartCrouching | `integer` | read-only |
| animStartForwardSpinning | `integer` | read-only |
| animStartGroundPound | `integer` | read-only |
| animStartHandstand | `integer` | read-only |
| animStartReachPocket | `integer` | read-only |
| animStartRidingShell | `integer` | read-only |
| animStartSleepIdle | `integer` | read-only |
| animStartSleepScratch | `integer` | read-only |
| animStartSleepSitting | `integer` | read-only |
| animStartSleepYawn | `integer` | read-only |
| animStartTiptoe | `integer` | read-only |
| animStartTwirl | `integer` | read-only |
| animStartWallkick | `integer` | read-only |
| animStopCrawling | `integer` | read-only |
| animStopCrouching | `integer` | read-only |
| animStopGrabObjWater | `integer` | read-only |
| animStopReachPocket | `integer` | read-only |
| animStopSkid | `integer` | read-only |
| animStopSlide | `integer` | read-only |
| animStopSlideLightObj | `integer` | read-only |
| animSuffocating | `integer` | read-only |
| animSummonStar | `integer` | read-only |
| animSwimPart1 | `integer` | read-only |
| animSwimPart2 | `integer` | read-only |
| animSwimWithObjPart1 | `integer` | read-only |
| animSwimWithObjPart2 | `integer` | read-only |
| animSwingingBowser | `integer` | read-only |
| animTakeCapOffThenOn | `integer` | read-only |
| animThrowCatchKey | `integer` | read-only |
| animThrowLightObject | `integer` | read-only |
| animTiptoe | `integer` | read-only |
| animTripleJump | `integer` | read-only |
| animTripleJumpFly | `integer` | read-only |
| animTripleJumpGroundPound | `integer` | read-only |
| animTripleJumpLand | `integer` | read-only |
| animTurningPart1 | `integer` | read-only |
| animTurningPart2 | `integer` | read-only |
| animTwirl | `integer` | read-only |
| animTwirlLand | `integer` | read-only |
| animUnlockDoor | `integer` | read-only |
| animWakeFromLying | `integer` | read-only |
| animWakeFromSleep | `integer` | read-only |
| animWalkPanting | `integer` | read-only |
| animWalkWithHeavyObj | `integer` | read-only |
| animWalkWithLightObj | `integer` | read-only |
| animWalking | `integer` | read-only |
| animWaterActionEnd | `integer` | read-only |
| animWaterActionEndWithObj | `integer` | read-only |
| animWaterDying | `integer` | read-only |
| animWaterForwardKb | `integer` | read-only |
| animWaterGrabObjPart1 | `integer` | read-only |
| animWaterGrabObjPart2 | `integer` | read-only |
| animWaterIdle | `integer` | read-only |
| animWaterIdleWithObj | `integer` | read-only |
| animWaterPickUpObj | `integer` | read-only |
| animWaterStarDance | `integer` | read-only |
| animWaterThrowObj | `integer` | read-only |
| animWingCapFly | `integer` | read-only |
| cameraHudHead | `integer` | read-only |
| capEnemyDecalGfx | `Pointer` <`Gfx`> | read-only |
| capEnemyGfx | `Pointer` <`Gfx`> | read-only |
| capEnemyLayer | `integer` | read-only |
| capMetalModelId | `integer` | read-only |
| capMetalWingModelId | `integer` | read-only |
| capModelId | `integer` | read-only |
| capWingModelId | `integer` | read-only |
| hudHead | `integer` | read-only |
| hudHeadTexture | [TextureInfo](structs.md#TextureInfo) | read-only |
| modelId | `integer` | read-only |
| name | `string` | read-only |
| soundAttacked | `integer` | read-only |
| soundCoughing1 | `integer` | read-only |
| soundCoughing2 | `integer` | read-only |
| soundCoughing3 | `integer` | read-only |
| soundDoh | `integer` | read-only |
| soundDrowning | `integer` | read-only |
| soundDying | `integer` | read-only |
| soundEeuh | `integer` | read-only |
| soundFreqScale | `number` | read-only |
| soundGameOver | `integer` | read-only |
| soundGroundPoundWah | `integer` | read-only |
| soundHaha | `integer` | read-only |
| soundHaha_2 | `integer` | read-only |
| soundHello | `integer` | read-only |
| soundHereWeGo | `integer` | read-only |
| soundHoohoo | `integer` | read-only |
| soundHrmm | `integer` | read-only |
| soundImaTired | `integer` | read-only |
| soundLetsAGo | `integer` | read-only |
| soundMamaMia | `integer` | read-only |
| soundOkeyDokey | `integer` | read-only |
| soundOnFire | `integer` | read-only |
| soundOoof | `integer` | read-only |
| soundOoof2 | `integer` | read-only |
| soundPanting | `integer` | read-only |
| soundPantingCold | `integer` | read-only |
| soundPressStartToPlay | `integer` | read-only |
| soundPunchHoo | `integer` | read-only |
| soundPunchWah | `integer` | read-only |
| soundPunchYah | `integer` | read-only |
| soundSnoring1 | `integer` | read-only |
| soundSnoring2 | `integer` | read-only |
| soundSnoring3 | `integer` | read-only |
| soundSoLongaBowser | `integer` | read-only |
| soundTwirlBounce | `integer` | read-only |
| soundUh | `integer` | read-only |
| soundUh2 | `integer` | read-only |
| soundUh2_2 | `integer` | read-only |
| soundWaaaooow | `integer` | read-only |
| soundWah2 | `integer` | read-only |
| soundWhoa | `integer` | read-only |
| soundYahWahHoo | `integer` | read-only |
| soundYahoo | `integer` | read-only |
| soundYahooWahaYippee | `integer` | read-only |
| soundYawning | `integer` | read-only |
| torsoRotMult | `number` | read-only |
| type | [enum CharacterType](constants.md#enum-CharacterType) | read-only |

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
| buttonDown | `integer` |  |
| buttonPressed | `integer` |  |
| buttonReleased | `integer` |  |
| extStickX | `integer` |  |
| extStickY | `integer` |  |
| port | `integer` |  |
| rawStickX | `integer` |  |
| rawStickY | `integer` |  |
| stickMag | `number` |  |
| stickX | `number` |  |
| stickY | `number` |  |

[:arrow_up_small:](#)

<br />

## [CustomLevelInfo](#CustomLevelInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| acousticReach | `integer` |  |
| courseNum | `integer` |  |
| echoLevel1 | `integer` |  |
| echoLevel2 | `integer` |  |
| echoLevel3 | `integer` |  |
| fullName | `string` | read-only |
| levelNum | `integer` |  |
| modIndex | `integer` |  |
| next | [CustomLevelInfo](structs.md#CustomLevelInfo) | read-only |
| script | `Pointer` <`LevelScript`> | read-only |
| scriptEntryName | `string` | read-only |
| shortName | `string` | read-only |

[:arrow_up_small:](#)

<br />

## [Cutscene](#Cutscene)

| Field | Type | Access |
| ----- | ---- | ------ |
| duration | `integer` |  |

[:arrow_up_small:](#)

<br />

## [CutsceneSplinePoint](#CutsceneSplinePoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| index | `integer` |  |
| point | [Vec3s](structs.md#Vec3s) | read-only |
| speed | `integer` |  |

[:arrow_up_small:](#)

<br />

## [CutsceneVariable](#CutsceneVariable)

| Field | Type | Access |
| ----- | ---- | ------ |
| angle | [Vec3s](structs.md#Vec3s) | read-only |
| point | [Vec3f](structs.md#Vec3f) | read-only |
| unused1 | `integer` |  |
| unused2 | `integer` |  |
| unusedPoint | [Vec3f](structs.md#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [DateTime](#DateTime)

| Field | Type | Access |
| ----- | ---- | ------ |
| day | `integer` |  |
| hour | `integer` |  |
| minute | `integer` |  |
| month | `integer` |  |
| second | `integer` |  |
| year | `integer` |  |

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
| a | `integer` |  |
| b | `integer` |  |
| g | `integer` |  |
| r | `integer` |  |

[:arrow_up_small:](#)

<br />

## [DjuiInteractableTheme](#DjuiInteractableTheme)

| Field | Type | Access |
| ----- | ---- | ------ |
| cursorDownBorderColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| cursorDownRectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| defaultBorderColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| defaultRectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| hoveredBorderColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| hoveredRectColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| textColor | [DjuiColor](structs.md#DjuiColor) | read-only |

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
| interactables | [DjuiInteractableTheme](structs.md#DjuiInteractableTheme) | read-only |
| name | `string` | read-only |
| panels | [DjuiPanelTheme](structs.md#DjuiPanelTheme) | read-only |
| threePanels | [DjuiThreePanelTheme](structs.md#DjuiThreePanelTheme) | read-only |

[:arrow_up_small:](#)

<br />

## [DjuiThreePanelTheme](#DjuiThreePanelTheme)

| Field | Type | Access |
| ----- | ---- | ------ |
| borderColor | [DjuiColor](structs.md#DjuiColor) | read-only |
| rectColor | [DjuiColor](structs.md#DjuiColor) | read-only |

[:arrow_up_small:](#)

<br />

## [ExclamationBoxContent](#ExclamationBoxContent)

| Field | Type | Access |
| ----- | ---- | ------ |
| behavior | [enum BehaviorId](constants.md#enum-BehaviorId) |  |
| firstByte | `integer` |  |
| id | `integer` |  |
| model | [enum ModelExtendedId](constants.md#enum-ModelExtendedId) |  |
| unused | `integer` |  |

[:arrow_up_small:](#)

<br />

## [FirstPersonCamera](#FirstPersonCamera)

| Field | Type | Access |
| ----- | ---- | ------ |
| centerL | `boolean` |  |
| crouch | `number` |  |
| enabled | `boolean` | read-only |
| forcePitch | `boolean` |  |
| forceRoll | `boolean` |  |
| forceYaw | `boolean` |  |
| fov | `number` |  |
| offset | [Vec3f](structs.md#Vec3f) | read-only |
| pitch | `integer` |  |
| yaw | `integer` |  |

[:arrow_up_small:](#)

<br />

## [FloorGeometry](#FloorGeometry)

| Field | Type | Access |
| ----- | ---- | ------ |
| normalX | `number` |  |
| normalY | `number` |  |
| normalZ | `number` |  |
| originOffset | `number` |  |
| unused | `Array` <`number`> |  |

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
| spiny_egg_seg5_anims_050157E4 | `Pointer` <`ObjectAnimPointer`> | read-only |
| spiny_seg5_anims_05016EAC | `Pointer` <`ObjectAnimPointer`> | read-only |
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
| apostrophe | [TextureInfo](structs.md#TextureInfo) | read-only |
| arrow_down | [TextureInfo](structs.md#TextureInfo) | read-only |
| arrow_up | [TextureInfo](structs.md#TextureInfo) | read-only |
| camera | [TextureInfo](structs.md#TextureInfo) | read-only |
| coin | [TextureInfo](structs.md#TextureInfo) | read-only |
| double_quote | [TextureInfo](structs.md#TextureInfo) | read-only |
| lakitu | [TextureInfo](structs.md#TextureInfo) | read-only |
| luigi_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| mario_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| no_camera | [TextureInfo](structs.md#TextureInfo) | read-only |
| star | [TextureInfo](structs.md#TextureInfo) | read-only |
| toad_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| waluigi_head | [TextureInfo](structs.md#TextureInfo) | read-only |
| wario_head | [TextureInfo](structs.md#TextureInfo) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNode](#GraphNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| children | [GraphNode](structs.md#GraphNode) | read-only |
| extraFlags | `integer` |  |
| flags | `integer` |  |
| hookProcess | `integer` |  |
| next | [GraphNode](structs.md#GraphNode) | read-only |
| parent | [GraphNode](structs.md#GraphNode) | read-only |
| prev | [GraphNode](structs.md#GraphNode) | read-only |
| type | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeAnimatedPart](#GraphNodeAnimatedPart)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeBackground](#GraphNodeBackground)

| Field | Type | Access |
| ----- | ---- | ------ |
| background | `integer` |  |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| prevCameraFocus | [Vec3f](structs.md#Vec3f) | read-only |
| prevCameraPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevCameraTimestamp | `integer` | read-only |
| unused | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeBillboard](#GraphNodeBillboard)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeCamera](#GraphNodeCamera)

| Field | Type | Access |
| ----- | ---- | ------ |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| matrixPtr | `Pointer` <`Mat4`> |  |
| matrixPtrPrev | `Pointer` <`Mat4`> | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| prevFocus | [Vec3f](structs.md#Vec3f) | read-only |
| prevPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevTimestamp | `integer` | read-only |
| roll | `integer` |  |
| rollScreen | `integer` |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeCullingRadius](#GraphNodeCullingRadius)

| Field | Type | Access |
| ----- | ---- | ------ |
| cullingRadius | `integer` |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| pad1E | `Array` <`integer`> |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeDisplayList](#GraphNodeDisplayList)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |

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
| objNode | [Object](structs.md#Object) |  |
| playerIndex | `integer` |  |
| prevShadowPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevShadowPosTimestamp | `integer` | read-only |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeLevelOfDetail](#GraphNodeLevelOfDetail)

| Field | Type | Access |
| ----- | ---- | ------ |
| maxDistance | `integer` |  |
| minDistance | `integer` |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |

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
| activeAreaIndex | `integer` |  |
| angle | [Vec3s](structs.md#Vec3s) | read-only |
| animInfo | [AnimInfo](structs.md#AnimInfo) | read-only |
| areaIndex | `integer` |  |
| cameraToObject | [Vec3f](structs.md#Vec3f) | read-only |
| disableAutomaticShadowPos | `boolean` |  |
| inited | `boolean` |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| prevAngle | [Vec3s](structs.md#Vec3s) | read-only |
| prevPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevScale | [Vec3f](structs.md#Vec3f) | read-only |
| prevScaleTimestamp | `integer` | read-only |
| prevShadowPos | [Vec3f](structs.md#Vec3f) | read-only |
| prevShadowPosTimestamp | `integer` | read-only |
| prevThrowMatrix | `Mat4` | read-only |
| prevThrowMatrixTimestamp | `integer` | read-only |
| prevTimestamp | `integer` | read-only |
| scale | [Vec3f](structs.md#Vec3f) | read-only |
| shadowInvisible | `boolean` |  |
| shadowPos | [Vec3f](structs.md#Vec3f) | read-only |
| sharedChild | [GraphNode](structs.md#GraphNode) | read-only |
| skipInViewCheck | `boolean` |  |
| skipInterpolationTimestamp | `integer` | read-only |
| throwMatrix | `Pointer` <`Mat4`> |  |
| throwMatrixPrev | `Pointer` <`Mat4`> | read-only |
| unk4C | [SpawnInfo](structs.md#SpawnInfo) | read-only |

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
| far | `integer` |  |
| fnNode | [FnGraphNode](structs.md#FnGraphNode) | read-only |
| fov | `number` |  |
| near | `integer` |  |
| prevFov | `number` |  |
| prevTimestamp | `number` |  |
| unused | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeRotation](#GraphNodeRotation)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| prevRotation | [Vec3s](structs.md#Vec3s) | read-only |
| prevTimestamp | `integer` |  |
| rotation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeScale](#GraphNodeScale)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| prevScale | `number` |  |
| scale | `number` |  |

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
| numCases | `integer` | read-only |
| selectedCase | `integer` |  |
| unused | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeTranslation](#GraphNodeTranslation)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| pad1E | `Array` <`integer`> |  |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeTranslationRotation](#GraphNodeTranslationRotation)

| Field | Type | Access |
| ----- | ---- | ------ |
| displayList | `Pointer` <`Gfx`> |  |
| node | [GraphNode](structs.md#GraphNode) | read-only |
| rotation | [Vec3s](structs.md#Vec3s) | read-only |
| translation | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNode_802A45E4](#GraphNode_802A45E4)

| Field | Type | Access |
| ----- | ---- | ------ |
| unk18 | `integer` |  |
| unk1A | `integer` |  |
| unk1C | `integer` |  |
| unk1E | `integer` |  |
| unk20 | `integer` |  |
| unk22 | `integer` |  |

[:arrow_up_small:](#)

<br />

## [HandheldShakePoint](#HandheldShakePoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| index | `integer` |  |
| pad | `integer` |  |
| point | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [HudUtilsRotation](#HudUtilsRotation)

| Field | Type | Access |
| ----- | ---- | ------ |
| pivotX | `number` |  |
| pivotY | `number` |  |
| prevPivotX | `number` |  |
| prevPivotY | `number` |  |
| rotation | `number` |  |
| rotationDiff | `number` |  |

[:arrow_up_small:](#)

<br />

## [InstantWarp](#InstantWarp)

| Field | Type | Access |
| ----- | ---- | ------ |
| area | `integer` |  |
| displacement | [Vec3s](structs.md#Vec3s) | read-only |
| id | `integer` |  |

[:arrow_up_small:](#)

<br />

## [LakituState](#LakituState)

| Field | Type | Access |
| ----- | ---- | ------ |
| curFocus | [Vec3f](structs.md#Vec3f) | read-only |
| curPos | [Vec3f](structs.md#Vec3f) | read-only |
| defMode | `integer` |  |
| filler30 | `Array` <`integer`> |  |
| filler3E | `Array` <`integer`> |  |
| filler72 | `Array` <`integer`> |  |
| focHSpeed | `number` |  |
| focVSpeed | `number` |  |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| focusDistance | `number` |  |
| goalFocus | [Vec3f](structs.md#Vec3f) | read-only |
| goalPos | [Vec3f](structs.md#Vec3f) | read-only |
| keyDanceRoll | `integer` |  |
| lastFrameAction | `integer` |  |
| mode | `integer` |  |
| nextYaw | `integer` |  |
| oldPitch | `integer` |  |
| oldRoll | `integer` |  |
| oldYaw | `integer` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| posHSpeed | `number` |  |
| posVSpeed | `number` |  |
| roll | `integer` |  |
| shakeMagnitude | [Vec3s](structs.md#Vec3s) | read-only |
| shakePitchDecay | `integer` |  |
| shakePitchPhase | `integer` |  |
| shakePitchVel | `integer` |  |
| shakeRollDecay | `integer` |  |
| shakeRollPhase | `integer` |  |
| shakeRollVel | `integer` |  |
| shakeYawDecay | `integer` |  |
| shakeYawPhase | `integer` |  |
| shakeYawVel | `integer` |  |
| skipCameraInterpolationTimestamp | `integer` |  |
| unused | `integer` |  |
| unusedVec1 | [Vec3f](structs.md#Vec3f) | read-only |
| unusedVec2 | [Vec3s](structs.md#Vec3s) | read-only |
| yaw | `integer` |  |

[:arrow_up_small:](#)

<br />

## [LevelValues](#LevelValues)

| Field | Type | Access |
| ----- | ---- | ------ |
| bubbleOnDeathBarrierInCapStages | `integer` |  |
| cellHeightLimit | `integer` |  |
| coinsRequiredForCoinStar | `integer` |  |
| disableActs | `integer` |  |
| entryLevel | [enum LevelNum](constants.md#enum-LevelNum) |  |
| exitCastleArea | `integer` |  |
| exitCastleLevel | [enum LevelNum](constants.md#enum-LevelNum) |  |
| exitCastleWarpNode | `integer` |  |
| extendedPauseDisplay | `integer` |  |
| fixCollisionBugs | `integer` |  |
| fixCollisionBugsFalseLedgeGrab | `integer` |  |
| fixCollisionBugsGroundPoundBonks | `integer` |  |
| fixCollisionBugsPickBestWall | `integer` |  |
| fixCollisionBugsRoundedCorners | `integer` |  |
| fixVanishFloors | `integer` |  |
| floatingStarDance | `integer` |  |
| floorLowerLimit | `integer` |  |
| floorLowerLimitMisc | `integer` |  |
| floorLowerLimitShadow | `integer` |  |
| hudCapTimer | `integer` |  |
| hudRedCoinsRadar | `integer` |  |
| hudSecretsRadar | `integer` |  |
| infiniteStairsRequirement | `integer` |  |
| jrbDarkenSkybox | `integer` |  |
| maxCoins | `integer` |  |
| maxLives | `integer` |  |
| metalCapDuration | `integer` |  |
| metalCapDurationCotmc | `integer` |  |
| metalCapSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| mushroom1UpHeal | `integer` |  |
| numCoinsToLife | `integer` |  |
| pauseExitAnywhere | `integer` |  |
| previewBlueCoins | `integer` |  |
| pssSlideStarIndex | `integer` |  |
| pssSlideStarTime | `integer` |  |
| respawnBlueCoinsSwitch | `integer` |  |
| showStarNumber | `integer` |  |
| skipCreditsAt | [enum LevelNum](constants.md#enum-LevelNum) |  |
| starHeal | `integer` |  |
| starPositions | [StarPositions](structs.md#StarPositions) | read-only |
| useGlobalStarIds | `integer` |  |
| vanishCapDuration | `integer` |  |
| vanishCapDurationVcutm | `integer` |  |
| vanishCapSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| visibleSecrets | `integer` |  |
| wdwWaterLevelSpeed | `number` |  |
| wingCapDuration | `integer` |  |
| wingCapDurationTotwc | `integer` |  |
| wingCapLookUpReq | `integer` |  |
| wingCapSequence | [enum SeqId](constants.md#enum-SeqId) |  |
| zoomOutCameraOnPause | `integer` |  |

[:arrow_up_small:](#)

<br />

## [LinearTransitionPoint](#LinearTransitionPoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| dist | `number` |  |
| focus | [Vec3f](structs.md#Vec3f) | read-only |
| pitch | `integer` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| yaw | `integer` |  |

[:arrow_up_small:](#)

<br />

## [MarioAnimation](#MarioAnimation)

| Field | Type | Access |
| ----- | ---- | ------ |
| currentAnimAddr | `Pointer` <`integer`> | read-only |
| padding | `Array` <`integer`> |  |
| targetAnim | [Animation](structs.md#Animation) |  |

[:arrow_up_small:](#)

<br />

## [MarioBodyState](#MarioBodyState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | `integer` |  |
| allowPartRotation | `integer` |  |
| capState | `integer` |  |
| eyeState | `integer` |  |
| grabPos | `integer` |  |
| handFootPos | `Array` <`Vec3f`> | read-only |
| handState | `integer` |  |
| headAngle | [Vec3s](structs.md#Vec3s) | read-only |
| headPos | [Vec3f](structs.md#Vec3f) | read-only |
| heldObjLastPosition | [Vec3f](structs.md#Vec3f) | read-only |
| lightB | `integer` |  |
| lightG | `integer` |  |
| lightR | `integer` |  |
| lightingDirX | `number` |  |
| lightingDirY | `number` |  |
| lightingDirZ | `number` |  |
| mirrorMario | `boolean` |  |
| modelState | `integer` |  |
| punchState | `integer` |  |
| shadeB | `integer` |  |
| shadeG | `integer` |  |
| shadeR | `integer` |  |
| torsoAngle | [Vec3s](structs.md#Vec3s) | read-only |
| torsoPos | [Vec3f](structs.md#Vec3f) | read-only |
| updateHeadPosTime | `integer` |  |
| updateTorsoTime | `integer` | read-only |
| wingFlutter | `integer` |  |

[:arrow_up_small:](#)

<br />

## [MarioState](#MarioState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | `integer` |  |
| actionArg | `integer` |  |
| actionState | `integer` |  |
| actionTimer | `integer` |  |
| angleVel | [Vec3s](structs.md#Vec3s) | read-only |
| animation | [MarioAnimation](structs.md#MarioAnimation) |  |
| area | [Area](structs.md#Area) | read-only |
| bounceSquishTimer | `integer` |  |
| bubbleObj | [Object](structs.md#Object) |  |
| cap | `integer` |  |
| capTimer | `integer` |  |
| ceil | [Surface](structs.md#Surface) |  |
| ceilHeight | `number` |  |
| character | [Character](structs.md#Character) |  |
| collidedObjInteractTypes | `integer` |  |
| controller | [Controller](structs.md#Controller) | read-only |
| curAnimOffset | `number` |  |
| currentRoom | `integer` |  |
| dialogId | `integer` | read-only |
| doubleJumpTimer | `integer` |  |
| faceAngle | [Vec3s](structs.md#Vec3s) | read-only |
| fadeWarpOpacity | `integer` |  |
| flags | `integer` |  |
| floor | [Surface](structs.md#Surface) |  |
| floorAngle | `integer` |  |
| floorHeight | `number` |  |
| forwardVel | `number` |  |
| framesSinceA | `integer` |  |
| framesSinceB | `integer` |  |
| freeze | `integer` |  |
| healCounter | `integer` |  |
| health | `integer` |  |
| heldByObj | [Object](structs.md#Object) |  |
| heldObj | [Object](structs.md#Object) |  |
| hurtCounter | `integer` |  |
| input | `integer` |  |
| intendedMag | `number` |  |
| intendedYaw | `integer` |  |
| interactObj | [Object](structs.md#Object) |  |
| invincTimer | `integer` |  |
| isSnoring | `integer` |  |
| knockbackTimer | `integer` |  |
| marioBodyState | [MarioBodyState](structs.md#MarioBodyState) | read-only |
| marioObj | [Object](structs.md#Object) | read-only |
| minimumBoneY | `number` |  |
| nonInstantWarpPos | [Vec3f](structs.md#Vec3f) | read-only |
| numCoins | `integer` |  |
| numKeys | `integer` |  |
| numLives | `integer` |  |
| numStars | `integer` |  |
| particleFlags | `integer` |  |
| peakHeight | `number` |  |
| playerIndex | `integer` | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| prevAction | `integer` |  |
| prevNumStarsForDialog | `integer` |  |
| quicksandDepth | `number` |  |
| riddenObj | [Object](structs.md#Object) |  |
| skipWarpInteractionsTimer | `integer` |  |
| slideVelX | `number` |  |
| slideVelZ | `number` |  |
| slideYaw | `integer` |  |
| spawnInfo | [SpawnInfo](structs.md#SpawnInfo) |  |
| specialTripleJump | `integer` |  |
| splineKeyframe | `Pointer` <`Vec4s`> |  |
| splineKeyframeFraction | `number` |  |
| splineState | `integer` |  |
| squishTimer | `integer` |  |
| statusForCamera | [PlayerCameraState](structs.md#PlayerCameraState) | read-only |
| terrainSoundAddend | `integer` |  |
| twirlYaw | `integer` |  |
| unkB0 | `integer` |  |
| unkC4 | `number` |  |
| usedObj | [Object](structs.md#Object) |  |
| vel | [Vec3f](structs.md#Vec3f) | read-only |
| wall | [Surface](structs.md#Surface) |  |
| wallKickTimer | `integer` |  |
| wallNormal | [Vec3f](structs.md#Vec3f) | read-only |
| wasNetworkVisible | `integer` |  |
| waterLevel | `integer` |  |

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
| basePath | `string` | read-only |
| category | `string` | read-only |
| customBehaviorIndex | `integer` | read-only |
| description | `string` | read-only |
| enabled | `boolean` | read-only |
| fileCapacity | `integer` | read-only |
| fileCount | `integer` | read-only |
| ignoreScriptWarnings | `boolean` | read-only |
| incompatible | `string` | read-only |
| index | `integer` | read-only |
| isDirectory | `boolean` | read-only |
| name | `string` | read-only |
| pausable | `boolean` | read-only |
| relativePath | `string` | read-only |
| renderBehindHud | `boolean` | read-only |
| selectable | `boolean` | read-only |

[:arrow_up_small:](#)

<br />

## [ModAudio](#ModAudio)

| Field | Type | Access |
| ----- | ---- | ------ |
| baseVolume | `number` |  |
| file | [ModFile](structs.md#ModFile) |  |
| isStream | `boolean` | read-only |
| loaded | `boolean` | read-only |

[:arrow_up_small:](#)

<br />

## [ModAudioSampleCopies](#ModAudioSampleCopies)

| Field | Type | Access |
| ----- | ---- | ------ |
| next | [ModAudioSampleCopies](structs.md#ModAudioSampleCopies) |  |
| parent | [ModAudio](structs.md#ModAudio) |  |
| prev | [ModAudioSampleCopies](structs.md#ModAudioSampleCopies) |  |

[:arrow_up_small:](#)

<br />

## [ModFile](#ModFile)

| Field | Type | Access |
| ----- | ---- | ------ |
| cachedPath | `string` | read-only |
| dataHash | `Array` <`integer`> | read-only |
| relativePath | `string` | read-only |
| wroteBytes | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [ModeTransitionInfo](#ModeTransitionInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| frame | `integer` |  |
| lastMode | `integer` |  |
| max | `integer` |  |
| newMode | `integer` |  |
| transitionEnd | [LinearTransitionPoint](structs.md#LinearTransitionPoint) | read-only |
| transitionStart | [LinearTransitionPoint](structs.md#LinearTransitionPoint) | read-only |

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
| currActNum | `integer` | read-only |
| currAreaIndex | `integer` | read-only |
| currAreaSyncValid | `boolean` | read-only |
| currCourseNum | `integer` | read-only |
| currLevelAreaSeqId | `integer` | read-only |
| currLevelNum | `integer` | read-only |
| currLevelSyncValid | `boolean` | read-only |
| currPositionValid | `boolean` | read-only |
| description | `string` | read-only |
| descriptionA | `integer` | read-only |
| descriptionB | `integer` | read-only |
| descriptionG | `integer` | read-only |
| descriptionR | `integer` | read-only |
| fadeOpacity | `integer` | read-only |
| globalIndex | `integer` | read-only |
| lastPingSent | `number` | read-only |
| lastReceived | `number` | read-only |
| lastSent | `number` | read-only |
| localIndex | `integer` | read-only |
| modelIndex | `integer` | read-only |
| name | `string` | read-only |
| onRxSeqId | `integer` | read-only |
| overrideLocation | `string` | read-only |
| overrideModelIndex | `integer` |  |
| overridePalette | [PlayerPalette](structs.md#PlayerPalette) |  |
| palette | [PlayerPalette](structs.md#PlayerPalette) | read-only |
| ping | `integer` | read-only |
| type | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [Object](#Object)

| Field | Type | Access |
| ----- | ---- | ------ |
| activeFlags | `integer` |  |
| allowRemoteInteractions | `integer` |  |
| areaTimer | `integer` |  |
| areaTimerDuration | `integer` |  |
| areaTimerType | [enum AreaTimerType](constants.md#enum-AreaTimerType) |  |
| behavior | `Pointer` <`BehaviorScript`> | read-only |
| bhvDelayTimer | `integer` |  |
| bhvStackIndex | `integer` | read-only |
| collidedObjInteractTypes | `integer` |  |
| collidedObjs | `Array` <`Object`> |  |
| collisionData | `Pointer` <`Collision`> |  |
| coopFlags | `integer` | read-only |
| ctx | `integer` |  |
| curBhvCommand | `Pointer` <`BehaviorScript`> | read-only |
| globalPlayerIndex | `integer` |  |
| header | [ObjectNode](structs.md#ObjectNode) | read-only |
| heldByPlayerIndex | `integer` |  |
| hitboxDownOffset | `number` |  |
| hitboxHeight | `number` |  |
| hitboxRadius | `number` |  |
| hookRender | `integer` |  |
| hurtboxHeight | `number` |  |
| hurtboxRadius | `number` |  |
| numCollidedObjs | `integer` |  |
| numSurfaces | `integer` | read-only |
| parentObj | [Object](structs.md#Object) |  |
| platform | [Object](structs.md#Object) |  |
| prevObj | [Object](structs.md#Object) |  |
| respawnInfoType | `integer` | read-only |
| setHome | `integer` |  |
| transform | `Mat4` | read-only |
| unused1 | `integer` |  |
| usingObj | [Object](structs.md#Object) |  |

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
| oLightRadius | `number` |  |

[:arrow_up_small:](#)

<br />

## [ObjectHitbox](#ObjectHitbox)

| Field | Type | Access |
| ----- | ---- | ------ |
| damageOrCoinValue | `integer` |  |
| downOffset | `integer` |  |
| health | `integer` |  |
| height | `integer` |  |
| hurtboxHeight | `integer` |  |
| hurtboxRadius | `integer` |  |
| interactType | `integer` |  |
| numLootCoins | `integer` |  |
| radius | `integer` |  |

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
| next | [ObjectWarpNode](structs.md#ObjectWarpNode) |  |
| node | [WarpNode](structs.md#WarpNode) | read-only |
| object | [Object](structs.md#Object) |  |

[:arrow_up_small:](#)

<br />

## [OffsetSizePair](#OffsetSizePair)

| Field | Type | Access |
| ----- | ---- | ------ |
| offset | `integer` |  |
| size | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Painting](#Painting)

| Field | Type | Access |
| ----- | ---- | ------ |
| alpha | `integer` |  |
| currFloor | `integer` |  |
| currRippleMag | `number` |  |
| currRippleRate | `number` |  |
| dispersionFactor | `number` |  |
| entryDispersionFactor | `number` |  |
| entryRippleDecay | `number` |  |
| entryRippleMag | `number` |  |
| entryRippleRate | `number` |  |
| floorEntered | `integer` |  |
| id | `integer` | read-only |
| imageCount | `integer` | read-only |
| lastFloor | `integer` |  |
| marioIsUnder | `integer` |  |
| marioWasUnder | `integer` |  |
| marioWentUnder | `integer` |  |
| normalDisplayList | `Pointer` <`Gfx`> | read-only |
| passiveDispersionFactor | `number` |  |
| passiveRippleDecay | `number` |  |
| passiveRippleMag | `number` |  |
| passiveRippleRate | `number` |  |
| pitch | `number` |  |
| posX | `number` |  |
| posY | `number` |  |
| posZ | `number` |  |
| rippleDecay | `number` |  |
| rippleDisplayList | `Pointer` <`Gfx`> | read-only |
| rippleTimer | `number` |  |
| rippleTrigger | `integer` |  |
| rippleX | `number` |  |
| rippleY | `number` |  |
| size | `number` |  |
| state | `integer` |  |
| textureHeight | `integer` | read-only |
| textureType | `integer` | read-only |
| textureWidth | `integer` | read-only |
| yaw | `number` |  |

[:arrow_up_small:](#)

<br />

## [PaintingMeshVertex](#PaintingMeshVertex)

| Field | Type | Access |
| ----- | ---- | ------ |
| norm | `Array` <`integer`> |  |
| pos | `Array` <`integer`> |  |

[:arrow_up_small:](#)

<br />

## [PaintingValues](#PaintingValues)

| Field | Type | Access |
| ----- | ---- | ------ |
| bob_painting | [Painting](structs.md#Painting) |  |
| ccm_painting | [Painting](structs.md#Painting) |  |
| cotmc_painting | [Painting](structs.md#Painting) |  |
| ddd_painting | [Painting](structs.md#Painting) |  |
| hmc_painting | [Painting](structs.md#Painting) |  |
| jrb_painting | [Painting](structs.md#Painting) |  |
| lll_painting | [Painting](structs.md#Painting) |  |
| sl_painting | [Painting](structs.md#Painting) |  |
| ssl_painting | [Painting](structs.md#Painting) |  |
| thi_huge_painting | [Painting](structs.md#Painting) |  |
| thi_tiny_painting | [Painting](structs.md#Painting) |  |
| ttc_painting | [Painting](structs.md#Painting) |  |
| ttm_painting | [Painting](structs.md#Painting) |  |
| ttm_slide_painting | [Painting](structs.md#Painting) |  |
| wdw_painting | [Painting](structs.md#Painting) |  |
| wf_painting | [Painting](structs.md#Painting) |  |

[:arrow_up_small:](#)

<br />

## [ParallelTrackingPoint](#ParallelTrackingPoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| distThresh | `number` |  |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| startOfPath | `integer` |  |
| zoom | `number` |  |

[:arrow_up_small:](#)

<br />

## [PlayerCameraState](#PlayerCameraState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | `integer` |  |
| cameraEvent | `integer` |  |
| faceAngle | [Vec3s](structs.md#Vec3s) | read-only |
| headRotation | [Vec3s](structs.md#Vec3s) | read-only |
| pos | [Vec3f](structs.md#Vec3f) | read-only |
| unused | `integer` |  |
| usedObj | [Object](structs.md#Object) |  |

[:arrow_up_small:](#)

<br />

## [PlayerGeometry](#PlayerGeometry)

| Field | Type | Access |
| ----- | ---- | ------ |
| currCeil | [Surface](structs.md#Surface) |  |
| currCeilHeight | `number` |  |
| currCeilType | `integer` |  |
| currFloor | [Surface](structs.md#Surface) |  |
| currFloorHeight | `number` |  |
| currFloorType | `integer` |  |
| prevCeil | [Surface](structs.md#Surface) |  |
| prevCeilHeight | `number` |  |
| prevCeilType | `integer` |  |
| prevFloor | [Surface](structs.md#Surface) |  |
| prevFloorHeight | `number` |  |
| prevFloorType | `integer` |  |
| waterHeight | `number` |  |

[:arrow_up_small:](#)

<br />

## [PlayerPalette](#PlayerPalette)

| Field | Type | Access |
| ----- | ---- | ------ |

[:arrow_up_small:](#)

<br />

## [RayIntersectionInfo](#RayIntersectionInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| hitPos | [Vec3f](structs.md#Vec3f) | read-only |
| surface | [Surface](structs.md#Surface) |  |

[:arrow_up_small:](#)

<br />

## [RomhackCameraSettings](#RomhackCameraSettings)

| Field | Type | Access |
| ----- | ---- | ------ |
| centering | `integer` |  |
| collisions | `integer` |  |
| dpad | `integer` |  |
| enable | [enum RomhackCameraOverride](constants.md#enum-RomhackCameraOverride) |  |
| modsOnly | `integer` |  |
| slowFall | `integer` |  |
| zoomedInDist | `integer` |  |
| zoomedInHeight | `integer` |  |
| zoomedOutDist | `integer` |  |
| zoomedOutHeight | `integer` |  |

[:arrow_up_small:](#)

<br />

## [ServerSettings](#ServerSettings)

| Field | Type | Access |
| ----- | ---- | ------ |
| bouncyLevelBounds | [enum BouncyLevelBounds](constants.md#enum-BouncyLevelBounds) |  |
| bubbleDeath | `integer` |  |
| enablePlayerList | `integer` |  |
| enablePlayersInLevelDisplay | `integer` |  |
| headlessServer | `integer` |  |
| maxPlayers | `integer` |  |
| nametags | `integer` |  |
| pauseAnywhere | `integer` |  |
| playerInteractions | [enum PlayerInteractions](constants.md#enum-PlayerInteractions) |  |
| playerKnockbackStrength | `integer` |  |
| pvpType | [enum PvpType](constants.md#enum-PvpType) |  |
| skipIntro | `integer` |  |
| stayInLevelAfterStar | `integer` |  |

[:arrow_up_small:](#)

<br />

## [SoundState](#SoundState)

| Field | Type | Access |
| ----- | ---- | ------ |
| animFrame1 | `integer` |  |
| animFrame2 | `integer` |  |
| playSound | `integer` |  |
| soundMagic | `integer` |  |

[:arrow_up_small:](#)

<br />

## [SpawnInfo](#SpawnInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| activeAreaIndex | `integer` |  |
| areaIndex | `integer` |  |
| behaviorArg | `integer` |  |
| next | [SpawnInfo](structs.md#SpawnInfo) | read-only |
| startAngle | [Vec3s](structs.md#Vec3s) | read-only |
| startPos | [Vec3s](structs.md#Vec3s) | read-only |
| syncID | `integer` | read-only |
| unk18 | [GraphNode](structs.md#GraphNode) | read-only |

[:arrow_up_small:](#)

<br />

## [SpawnParticlesInfo](#SpawnParticlesInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| behParam | `integer` |  |
| count | `integer` |  |
| dragStrength | `integer` |  |
| forwardVelBase | `integer` |  |
| forwardVelRange | `integer` |  |
| gravity | `integer` |  |
| model | `integer` | read-only |
| offsetY | `integer` |  |
| sizeBase | `number` |  |
| sizeRange | `number` |  |
| velYBase | `integer` |  |
| velYRange | `integer` |  |

[:arrow_up_small:](#)

<br />

## [StarPositions](#StarPositions)

| Field | Type | Access |
| ----- | ---- | ------ |
| BalconyBooStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BigBullyStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BigBullyTrioStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| BigPiranhasStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| CcmSlideStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| ChillBullyStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| EyerockStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| GhostHuntBooStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| JetstreamRingStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KingBobombStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KingWhompStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KleptoStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KoopaBobStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| KoopaThiStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| MantaRayStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| MerryGoRoundStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| MrIStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| PssSlideStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| RacingPenguinStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| SnowmanHeadStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| TreasureChestStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| TreasureJrbStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| TuxieMotherStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| UkikiCageStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| UnagiStarPos | [Vec3f](structs.md#Vec3f) | read-only |
| WigglerStarPos | [Vec3f](structs.md#Vec3f) | read-only |

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

## [Struct802A272C](#Struct802A272C)

| Field | Type | Access |
| ----- | ---- | ------ |
| vecF | [Vec3f](structs.md#Vec3f) | read-only |
| vecS | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [Surface](#Surface)

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | `integer` |  |
| force | `integer` |  |
| lowerY | `integer` |  |
| modifiedTimestamp | `integer` |  |
| normal | [Vec3f](structs.md#Vec3f) | read-only |
| object | [Object](structs.md#Object) |  |
| originOffset | `number` |  |
| prevVertex1 | [Vec3s](structs.md#Vec3s) | read-only |
| prevVertex2 | [Vec3s](structs.md#Vec3s) | read-only |
| prevVertex3 | [Vec3s](structs.md#Vec3s) | read-only |
| room | `integer` |  |
| type | `integer` |  |
| upperY | `integer` |  |
| vertex1 | [Vec3s](structs.md#Vec3s) | read-only |
| vertex2 | [Vec3s](structs.md#Vec3s) | read-only |
| vertex3 | [Vec3s](structs.md#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [TextureInfo](#TextureInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| bitSize | `integer` | read-only |
| height | `integer` | read-only |
| name | `string` | read-only |
| texture | `Pointer` <`integer`> | read-only |
| width | `integer` | read-only |

[:arrow_up_small:](#)

<br />

## [TransitionInfo](#TransitionInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| focDist | `number` |  |
| focPitch | `integer` |  |
| focYaw | `integer` |  |
| framesLeft | `integer` |  |
| marioPos | [Vec3f](structs.md#Vec3f) | read-only |
| pad | `integer` |  |
| posDist | `number` |  |
| posPitch | `integer` |  |
| posYaw | `integer` |  |

[:arrow_up_small:](#)

<br />

## [Vec2f](#Vec2f)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | `number` |  |
| y | `number` |  |

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
| cn | `Array` <`integer`> |  |
| flag | `integer` |  |
| ob | `Array` <`number`> |  |
| tc | `Array` <`integer`> |  |

[:arrow_up_small:](#)

<br />

## [Vtx_Interp](#Vtx_Interp)

| Field | Type | Access |
| ----- | ---- | ------ |
| n | `string` |  |
| ob | `Array` <`number`> |  |

[:arrow_up_small:](#)

<br />

## [WallCollisionData](#WallCollisionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| normalAddition | [Vec3f](structs.md#Vec3f) | read-only |
| normalCount | `integer` |  |
| numWalls | `integer` |  |
| offsetY | `number` |  |
| radius | `number` |  |
| unused | `integer` |  |
| walls | `Array` <`Surface`> |  |
| x | `number` |  |
| y | `number` |  |
| z | `number` |  |

[:arrow_up_small:](#)

<br />

## [WarpNode](#WarpNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| destArea | `integer` |  |
| destLevel | `integer` |  |
| destNode | `integer` |  |
| id | `integer` |  |

[:arrow_up_small:](#)

<br />

## [WarpTransition](#WarpTransition)

| Field | Type | Access |
| ----- | ---- | ------ |
| data | [WarpTransitionData](structs.md#WarpTransitionData) | read-only |
| isActive | `integer` |  |
| pauseRendering | `integer` |  |
| time | `integer` |  |
| type | `integer` |  |

[:arrow_up_small:](#)

<br />

## [WarpTransitionData](#WarpTransitionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| blue | `integer` |  |
| endTexRadius | `integer` |  |
| endTexX | `integer` |  |
| endTexY | `integer` |  |
| green | `integer` |  |
| red | `integer` |  |
| startTexRadius | `integer` |  |
| startTexX | `integer` |  |
| startTexY | `integer` |  |
| texTimer | `integer` |  |

[:arrow_up_small:](#)

<br />

## [WaterDropletParams](#WaterDropletParams)

| Field | Type | Access |
| ----- | ---- | ------ |
| behavior | `Pointer` <`BehaviorScript`> | read-only |
| flags | `integer` |  |
| model | `integer` |  |
| moveAngleRange | `integer` |  |
| moveRange | `integer` |  |
| randForwardVelOffset | `number` |  |
| randForwardVelScale | `number` |  |
| randSizeOffset | `number` |  |
| randSizeScale | `number` |  |
| randYVelOffset | `number` |  |
| randYVelScale | `number` |  |

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

## [struct802A1230](#struct802A1230)

| Field | Type | Access |
| ----- | ---- | ------ |
| unk00 | `integer` |  |
| unk02 | `integer` |  |

[:arrow_up_small:](#)

<br />

