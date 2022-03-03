## [:rewind: Lua Reference](lua.md)

# Supported Structs
- [AnimInfo](#AnimInfo)
- [Animation](#Animation)
- [Area](#Area)
- [BullyCollisionData](#BullyCollisionData)
- [Camera](#Camera)
- [CameraFOVStatus](#CameraFOVStatus)
- [CameraStoredInfo](#CameraStoredInfo)
- [CameraTrigger](#CameraTrigger)
- [ChainSegment](#ChainSegment)
- [Character](#Character)
- [Controller](#Controller)
- [Cutscene](#Cutscene)
- [CutsceneSplinePoint](#CutsceneSplinePoint)
- [CutsceneVariable](#CutsceneVariable)
- [FloorGeometry](#FloorGeometry)
- [GlobalTextures](#GlobalTextures)
- [GraphNode](#GraphNode)
- [GraphNodeObject](#GraphNodeObject)
- [GraphNode_802A45E4](#GraphNode_802A45E4)
- [HandheldShakePoint](#HandheldShakePoint)
- [InstantWarp](#InstantWarp)
- [LakituState](#LakituState)
- [LinearTransitionPoint](#LinearTransitionPoint)
- [MarioAnimDmaRelatedThing](#MarioAnimDmaRelatedThing)
- [MarioAnimation](#MarioAnimation)
- [MarioBodyState](#MarioBodyState)
- [MarioState](#MarioState)
- [ModeTransitionInfo](#ModeTransitionInfo)
- [NetworkPlayer](#NetworkPlayer)
- [Object](#Object)
- [ObjectHitbox](#ObjectHitbox)
- [ObjectNode](#ObjectNode)
- [ObjectWarpNode](#ObjectWarpNode)
- [OffsetSizePair](#OffsetSizePair)
- [ParallelTrackingPoint](#ParallelTrackingPoint)
- [PlayerCameraState](#PlayerCameraState)
- [PlayerGeometry](#PlayerGeometry)
- [SPTask](#SPTask)
- [SpawnInfo](#SpawnInfo)
- [SpawnParticlesInfo](#SpawnParticlesInfo)
- [Struct802A272C](#Struct802A272C)
- [Surface](#Surface)
- [TextureInfo](#TextureInfo)
- [TransitionInfo](#TransitionInfo)
- [UnusedArea28](#UnusedArea28)
- [VblankHandler](#VblankHandler)
- [Vec3f](#Vec3f)
- [Vec3s](#Vec3s)
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
| animAccel | integer |  |
| animFrame | integer |  |
| animFrameAccelAssist | integer |  |
| animID | integer |  |
| animTimer | integer |  |
| animYTrans | integer |  |
| curAnim | [Animation](#Animation) |  |
| prevAnimFrame | integer |  |
| prevAnimFrameTimestamp | integer |  |
| prevAnimID | integer |  |
| prevAnimPtr | [Animation](#Animation) |  |

[:arrow_up_small:](#)

<br />

## [Animation](#Animation)

| Field | Type | Access |
| ----- | ---- | ------ |
| animYTransDivisor | integer |  |
| flags | integer |  |
| index | Pointer <integer> | read-only |
| length | integer |  |
| loopEnd | integer |  |
| loopStart | integer |  |
| startFrame | integer |  |
| unusedBoneCount | integer |  |
| values | Pointer <integer> | read-only |

[:arrow_up_small:](#)

<br />

## [Area](#Area)

| Field | Type | Access |
| ----- | ---- | ------ |
| camera | [Camera](#Camera) |  |
| flags | integer |  |
| index | integer |  |
| instantWarps | [InstantWarp](#InstantWarp) |  |
| macroObjects | Pointer <integer> | read-only |
| musicParam | integer |  |
| musicParam2 | integer |  |
| objectSpawnInfos | [SpawnInfo](#SpawnInfo) |  |
| paintingWarpNodes | [WarpNode](#WarpNode) |  |
| surfaceRooms | Pointer <integer> | read-only |
| terrainData | Pointer <integer> | read-only |
| terrainType | integer |  |
| warpNodes | [ObjectWarpNode](#ObjectWarpNode) |  |

[:arrow_up_small:](#)

<br />

## [BullyCollisionData](#BullyCollisionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| conversionRatio | number |  |
| posX | number |  |
| posZ | number |  |
| radius | number |  |
| velX | number |  |
| velZ | number |  |

[:arrow_up_small:](#)

<br />

## [Camera](#Camera)

| Field | Type | Access |
| ----- | ---- | ------ |
| areaCenX | number |  |
| areaCenY | number |  |
| areaCenZ | number |  |
| cutscene | integer |  |
| defMode | integer |  |
| doorStatus | integer |  |
| focus | [Vec3f](#Vec3f) | read-only |
| mode | integer |  |
| nextYaw | integer |  |
| pos | [Vec3f](#Vec3f) | read-only |
| unusedVec1 | [Vec3f](#Vec3f) | read-only |
| yaw | integer |  |

[:arrow_up_small:](#)

<br />

## [CameraFOVStatus](#CameraFOVStatus)

| Field | Type | Access |
| ----- | ---- | ------ |
| decay | integer |  |
| fov | number |  |
| fovFunc | integer |  |
| fovOffset | number |  |
| shakeAmplitude | number |  |
| shakePhase | integer |  |
| shakeSpeed | integer |  |
| unusedIsSleeping | integer |  |

[:arrow_up_small:](#)

<br />

## [CameraStoredInfo](#CameraStoredInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| cannonYOffset | number |  |
| focus | [Vec3f](#Vec3f) | read-only |
| panDist | number |  |
| pos | [Vec3f](#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [CameraTrigger](#CameraTrigger)

| Field | Type | Access |
| ----- | ---- | ------ |
| area | integer |  |
| boundsX | integer |  |
| boundsY | integer |  |
| boundsYaw | integer |  |
| boundsZ | integer |  |
| centerX | integer |  |
| centerY | integer |  |
| centerZ | integer |  |

[:arrow_up_small:](#)

<br />

## [ChainSegment](#ChainSegment)

| Field | Type | Access |
| ----- | ---- | ------ |
| pitch | integer |  |
| posX | number |  |
| posY | number |  |
| posZ | number |  |
| roll | integer |  |
| yaw | integer |  |

[:arrow_up_small:](#)

<br />

## [Character](#Character)

| Field | Type | Access |
| ----- | ---- | ------ |
| animOffsetEnabled | integer | read-only |
| animOffsetFeet | number | read-only |
| animOffsetHand | number | read-only |
| animOffsetLowYPoint | number | read-only |
| cameraHudHead | integer | read-only |
| capEnemyLayer | integer | read-only |
| capMetalModelId | integer | read-only |
| capMetalWingModelId | integer | read-only |
| capModelId | integer | read-only |
| capWingModelId | integer | read-only |
| hudHead | char | read-only |
| hudHeadTexture | [TextureInfo](#TextureInfo) | read-only |
| modelId | integer | read-only |
| name | string | read-only |
| soundAttacked | integer | read-only |
| soundCoughing1 | integer | read-only |
| soundCoughing2 | integer | read-only |
| soundCoughing3 | integer | read-only |
| soundDoh | integer | read-only |
| soundDrowning | integer | read-only |
| soundDying | integer | read-only |
| soundEeuh | integer | read-only |
| soundFreqScale | number | read-only |
| soundGameOver | integer | read-only |
| soundGroundPoundWah | integer | read-only |
| soundHaha | integer | read-only |
| soundHaha_2 | integer | read-only |
| soundHello | integer | read-only |
| soundHereWeGo | integer | read-only |
| soundHoohoo | integer | read-only |
| soundHrmm | integer | read-only |
| soundImaTired | integer | read-only |
| soundMamaMia | integer | read-only |
| soundOnFire | integer | read-only |
| soundOoof | integer | read-only |
| soundOoof2 | integer | read-only |
| soundPanting | integer | read-only |
| soundPantingCold | integer | read-only |
| soundPressStartToPlay | integer | read-only |
| soundPunchHoo | integer | read-only |
| soundPunchWah | integer | read-only |
| soundPunchYah | integer | read-only |
| soundSnoring1 | integer | read-only |
| soundSnoring2 | integer | read-only |
| soundSnoring3 | integer | read-only |
| soundSoLongaBowser | integer | read-only |
| soundTwirlBounce | integer | read-only |
| soundUh | integer | read-only |
| soundUh2 | integer | read-only |
| soundUh2_2 | integer | read-only |
| soundWaaaooow | integer | read-only |
| soundWah2 | integer | read-only |
| soundWhoa | integer | read-only |
| soundYahWahHoo | integer | read-only |
| soundYahoo | integer | read-only |
| soundYahooWahaYippee | integer | read-only |
| soundYawning | integer | read-only |
| torsoRotMult | number | read-only |
| type | integer | read-only |

[:arrow_up_small:](#)

<br />

## [Controller](#Controller)

| Field | Type | Access |
| ----- | ---- | ------ |
| buttonDown | integer |  |
| buttonPressed | integer |  |
| extStickX | integer |  |
| extStickY | integer |  |
| port | integer |  |
| rawStickX | integer |  |
| rawStickY | integer |  |
| stickMag | number |  |
| stickX | number |  |
| stickY | number |  |

[:arrow_up_small:](#)

<br />

## [Cutscene](#Cutscene)

| Field | Type | Access |
| ----- | ---- | ------ |
| duration | integer |  |

[:arrow_up_small:](#)

<br />

## [CutsceneSplinePoint](#CutsceneSplinePoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| index | integer |  |
| point | [Vec3s](#Vec3s) | read-only |
| speed | integer |  |

[:arrow_up_small:](#)

<br />

## [CutsceneVariable](#CutsceneVariable)

| Field | Type | Access |
| ----- | ---- | ------ |
| angle | [Vec3s](#Vec3s) | read-only |
| point | [Vec3f](#Vec3f) | read-only |
| unused1 | integer |  |
| unused2 | integer |  |
| unusedPoint | [Vec3f](#Vec3f) | read-only |

[:arrow_up_small:](#)

<br />

## [FloorGeometry](#FloorGeometry)

| Field | Type | Access |
| ----- | ---- | ------ |
| normalX | number |  |
| normalY | number |  |
| normalZ | number |  |
| originOffset | number |  |

[:arrow_up_small:](#)

<br />

## [GlobalTextures](#GlobalTextures)

| Field | Type | Access |
| ----- | ---- | ------ |
| arrow_down | [TextureInfo](#TextureInfo) | read-only |
| arrow_up | [TextureInfo](#TextureInfo) | read-only |
| camera | [TextureInfo](#TextureInfo) | read-only |
| coin | [TextureInfo](#TextureInfo) | read-only |
| lakitu | [TextureInfo](#TextureInfo) | read-only |
| no_camera | [TextureInfo](#TextureInfo) | read-only |
| star | [TextureInfo](#TextureInfo) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNode](#GraphNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| children | [GraphNode](#GraphNode) |  |
| flags | integer |  |
| next | [GraphNode](#GraphNode) |  |
| parent | [GraphNode](#GraphNode) |  |
| prev | [GraphNode](#GraphNode) |  |
| type | integer |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeObject](#GraphNodeObject)

| Field | Type | Access |
| ----- | ---- | ------ |
| activeAreaIndex | integer |  |
| angle | [Vec3s](#Vec3s) | read-only |
| animInfo | [AnimInfo](#AnimInfo) | read-only |
| areaIndex | integer |  |
| cameraToObject | [Vec3f](#Vec3f) | read-only |
| node | [GraphNode](#GraphNode) | read-only |
| pos | [Vec3f](#Vec3f) | read-only |
| prevAngle | [Vec3s](#Vec3s) | read-only |
| prevPos | [Vec3f](#Vec3f) | read-only |
| prevScale | [Vec3f](#Vec3f) | read-only |
| prevScaleTimestamp | integer |  |
| prevShadowPos | [Vec3f](#Vec3f) | read-only |
| prevShadowPosTimestamp | integer |  |
| prevThrowMatrixTimestamp | integer |  |
| prevTimestamp | integer |  |
| scale | [Vec3f](#Vec3f) | read-only |
| sharedChild | [GraphNode](#GraphNode) |  |
| skipInterpolationTimestamp | integer |  |
| unk4C | [SpawnInfo](#SpawnInfo) |  |

[:arrow_up_small:](#)

<br />

## [GraphNode_802A45E4](#GraphNode_802A45E4)

| Field | Type | Access |
| ----- | ---- | ------ |
| unk18 | integer |  |
| unk1A | integer |  |
| unk1C | integer |  |
| unk1E | integer |  |
| unk20 | integer |  |
| unk22 | integer |  |

[:arrow_up_small:](#)

<br />

## [HandheldShakePoint](#HandheldShakePoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| index | integer |  |
| pad | integer |  |
| point | [Vec3s](#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [InstantWarp](#InstantWarp)

| Field | Type | Access |
| ----- | ---- | ------ |
| area | integer |  |
| displacement | [Vec3s](#Vec3s) | read-only |
| id | integer |  |

[:arrow_up_small:](#)

<br />

## [LakituState](#LakituState)

| Field | Type | Access |
| ----- | ---- | ------ |
| curFocus | [Vec3f](#Vec3f) | read-only |
| curPos | [Vec3f](#Vec3f) | read-only |
| defMode | integer |  |
| focHSpeed | number |  |
| focVSpeed | number |  |
| focus | [Vec3f](#Vec3f) | read-only |
| focusDistance | number |  |
| goalFocus | [Vec3f](#Vec3f) | read-only |
| goalPos | [Vec3f](#Vec3f) | read-only |
| keyDanceRoll | integer |  |
| lastFrameAction | integer |  |
| mode | integer |  |
| nextYaw | integer |  |
| oldPitch | integer |  |
| oldRoll | integer |  |
| oldYaw | integer |  |
| pos | [Vec3f](#Vec3f) | read-only |
| posHSpeed | number |  |
| posVSpeed | number |  |
| roll | integer |  |
| shakeMagnitude | [Vec3s](#Vec3s) | read-only |
| shakePitchDecay | integer |  |
| shakePitchPhase | integer |  |
| shakePitchVel | integer |  |
| shakeRollDecay | integer |  |
| shakeRollPhase | integer |  |
| shakeRollVel | integer |  |
| shakeYawDecay | integer |  |
| shakeYawPhase | integer |  |
| shakeYawVel | integer |  |
| skipCameraInterpolationTimestamp | integer |  |
| unused | integer |  |
| unusedVec1 | [Vec3f](#Vec3f) | read-only |
| unusedVec2 | [Vec3s](#Vec3s) | read-only |
| yaw | integer |  |

[:arrow_up_small:](#)

<br />

## [LinearTransitionPoint](#LinearTransitionPoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| dist | number |  |
| focus | [Vec3f](#Vec3f) | read-only |
| pitch | integer |  |
| pos | [Vec3f](#Vec3f) | read-only |
| yaw | integer |  |

[:arrow_up_small:](#)

<br />

## [MarioAnimation](#MarioAnimation)

| Field | Type | Access |
| ----- | ---- | ------ |
| currentAnimAddr | Pointer <integer> | read-only |
| targetAnim | [Animation](#Animation) |  |

[:arrow_up_small:](#)

<br />

## [MarioBodyState](#MarioBodyState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | integer |  |
| capState | integer |  |
| eyeState | integer |  |
| grabPos | integer |  |
| handState | integer |  |
| headAngle | [Vec3s](#Vec3s) | read-only |
| heldObjLastPosition | [Vec3f](#Vec3f) | read-only |
| modelState | integer |  |
| punchState | integer |  |
| torsoAngle | [Vec3s](#Vec3s) | read-only |
| torsoPos | [Vec3f](#Vec3f) | read-only |
| wingFlutter | integer |  |

[:arrow_up_small:](#)

<br />

## [MarioState](#MarioState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | integer |  |
| actionArg | integer |  |
| actionState | integer |  |
| actionTimer | integer |  |
| angleVel | [Vec3s](#Vec3s) | read-only |
| animation | [MarioAnimation](#MarioAnimation) |  |
| area | [Area](#Area) |  |
| bubbleObj | [Object](#Object) |  |
| capTimer | integer |  |
| ceil | [Surface](#Surface) |  |
| ceilHeight | number |  |
| character | [Character](#Character) |  |
| collidedObjInteractTypes | integer |  |
| controller | [Controller](#Controller) |  |
| curAnimOffset | number |  |
| currentRoom | integer |  |
| doubleJumpTimer | integer |  |
| faceAngle | [Vec3s](#Vec3s) | read-only |
| fadeWarpOpacity | integer |  |
| flags | integer |  |
| floor | [Surface](#Surface) |  |
| floorAngle | integer |  |
| floorHeight | number |  |
| forwardVel | number |  |
| framesSinceA | integer |  |
| framesSinceB | integer |  |
| freeze | integer |  |
| healCounter | integer |  |
| health | integer |  |
| heldByObj | [Object](#Object) |  |
| heldObj | [Object](#Object) |  |
| hurtCounter | integer |  |
| input | integer |  |
| intendedMag | number |  |
| intendedYaw | integer |  |
| interactObj | [Object](#Object) |  |
| invincTimer | integer |  |
| isSnoring | integer |  |
| marioBodyState | [MarioBodyState](#MarioBodyState) |  |
| marioObj | [Object](#Object) |  |
| minimumBoneY | number |  |
| nonInstantWarpPos | [Vec3f](#Vec3f) | read-only |
| numCoins | integer |  |
| numKeys | integer |  |
| numLives | integer |  |
| numStars | integer |  |
| particleFlags | integer |  |
| peakHeight | number |  |
| playerIndex | integer | read-only |
| pos | [Vec3f](#Vec3f) | read-only |
| prevAction | integer |  |
| prevNumStarsForDialog | integer |  |
| quicksandDepth | number |  |
| riddenObj | [Object](#Object) |  |
| slideVelX | number |  |
| slideVelZ | number |  |
| slideYaw | integer |  |
| spawnInfo | [SpawnInfo](#SpawnInfo) |  |
| splineKeyframeFraction | number |  |
| splineState | integer |  |
| squishTimer | integer |  |
| statusForCamera | [PlayerCameraState](#PlayerCameraState) |  |
| terrainSoundAddend | integer |  |
| twirlYaw | integer |  |
| unkB0 | integer |  |
| unkC4 | number |  |
| usedObj | [Object](#Object) |  |
| vel | [Vec3f](#Vec3f) | read-only |
| wall | [Surface](#Surface) |  |
| wallKickTimer | integer |  |
| wasNetworkVisible | integer |  |
| waterLevel | integer |  |

[:arrow_up_small:](#)

<br />

## [ModeTransitionInfo](#ModeTransitionInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| frame | integer |  |
| lastMode | integer |  |
| max | integer |  |
| newMode | integer |  |
| transitionEnd | [LinearTransitionPoint](#LinearTransitionPoint) | read-only |
| transitionStart | [LinearTransitionPoint](#LinearTransitionPoint) | read-only |

[:arrow_up_small:](#)

<br />

## [NetworkPlayer](#NetworkPlayer)

| Field | Type | Access |
| ----- | ---- | ------ |
| connected | bool | read-only |
| currActNum | integer | read-only |
| currAreaIndex | integer | read-only |
| currAreaSyncValid | bool | read-only |
| currCourseNum | integer | read-only |
| currLevelAreaSeqId | integer | read-only |
| currLevelNum | integer | read-only |
| currLevelSyncValid | bool | read-only |
| description | string | read-only |
| descriptionA | integer | read-only |
| descriptionB | integer | read-only |
| descriptionG | integer | read-only |
| descriptionR | integer | read-only |
| fadeOpacity | integer | read-only |
| globalIndex | integer | read-only |
| lastReceived | number | read-only |
| lastSent | number | read-only |
| localIndex | integer | read-only |
| modelIndex | integer | read-only |
| name | string | read-only |
| onRxSeqId | integer | read-only |
| paletteIndex | integer | read-only |
| type | integer | read-only |

[:arrow_up_small:](#)

<br />

## [Object](#Object)

| Field | Type | Access |
| ----- | ---- | ------ |
| activeFlags | integer |  |
| areaTimer | integer |  |
| areaTimerDuration | integer |  |
| areaTimerType | integer |  |
| behavior | Pointer <BehaviorScript> | read-only |
| bhvDelayTimer | integer |  |
| bhvStackIndex | integer |  |
| collidedObjInteractTypes | integer |  |
| createdThroughNetwork | integer | read-only |
| curBhvCommand | Pointer <BehaviorScript> | read-only |
| globalPlayerIndex | integer |  |
| header | [ObjectNode](#ObjectNode) | read-only |
| heldByPlayerIndex | integer |  |
| hitboxDownOffset | number |  |
| hitboxHeight | number |  |
| hitboxRadius | number |  |
| hurtboxHeight | number |  |
| hurtboxRadius | number |  |
| numCollidedObjs | integer |  |
| parentObj | [Object](#Object) |  |
| platform | [Object](#Object) |  |
| prevObj | [Object](#Object) |  |
| respawnInfoType | integer |  |
| unused1 | integer |  |

### Object-Independent Data Fields
| Field | Type | Access |
| ----- | ---- | ------ |
| oFlags | integer |  |
| oDialogResponse | integer |  |
| oDialogState | integer |  |
| oUnk94 | integer |  |
| oSyncID | integer | read-only |
| oIntangibleTimer | integer |  |
| oPosX | number |  |
| oPosY | number |  |
| oPosZ | number |  |
| oVelX | number |  |
| oVelY | number |  |
| oVelZ | number |  |
| oForwardVel | number |  |
| oForwardVelS32 | integer |  |
| oUnkBC | number |  |
| oUnkC0 | number |  |
| oMoveAnglePitch | integer |  |
| oMoveAngleYaw | integer |  |
| oMoveAngleRoll | integer |  |
| oFaceAnglePitch | integer |  |
| oFaceAngleYaw | integer |  |
| oFaceAngleRoll | integer |  |
| oGraphYOffset | number |  |
| oActiveParticleFlags | integer |  |
| oGravity | number |  |
| oFloorHeight | number |  |
| oMoveFlags | integer |  |
| oAnimState | integer |  |
| oAngleVelPitch | integer |  |
| oAngleVelYaw | integer |  |
| oAngleVelRoll | integer |  |
| oHeldState | integer |  |
| oWallHitboxRadius | number |  |
| oDragStrength | number |  |
| oInteractType | integer |  |
| oInteractStatus | integer |  |
| oParentRelativePosX | number |  |
| oParentRelativePosY | number |  |
| oParentRelativePosZ | number |  |
| oBehParams2ndByte | integer |  |
| oAction | integer |  |
| oSubAction | integer |  |
| oTimer | integer |  |
| oBounciness | number |  |
| oDistanceToMario | number |  |
| oAngleToMario | integer |  |
| oHomeX | number |  |
| oHomeY | number |  |
| oHomeZ | number |  |
| oFriction | number |  |
| oBuoyancy | number |  |
| oSoundStateID | integer |  |
| oOpacity | integer |  |
| oDamageOrCoinValue | integer |  |
| oHealth | integer |  |
| oBehParams | integer |  |
| oPrevAction | integer |  |
| oInteractionSubtype | integer |  |
| oCollisionDistance | number |  |
| oNumLootCoins | integer |  |
| oDrawingDistance | number |  |
| oRoom | integer |  |
| oSyncDeath | integer |  |
| oUnk1A8 | integer |  |
| oWallAngle | integer |  |
| oFloorType | integer |  |
| oFloorRoom | integer |  |
| oAngleToHome | integer |  |
| oFloor | [Surface](#Surface) |  |
| oDeathSound | integer |  |

### Object-Dependent Data Fields
| Field | Type | Access |
| ----- | ---- | ------ |
| oPathedStartWaypoint | [Waypoint](#Waypoint) |  |
| oPathedPrevWaypoint | [Waypoint](#Waypoint) |  |
| oPathedPrevWaypointFlags | integer |  |
| oPathedTargetPitch | integer |  |
| oPathedTargetYaw | integer |  |
| oMacroUnk108 | number |  |
| oMacroUnk10C | number |  |
| oMacroUnk110 | number |  |
| oMarioParticleFlags | integer |  |
| oMarioPoleUnk108 | integer |  |
| oMarioReadingSignDYaw | integer |  |
| oMarioPoleYawVel | integer |  |
| oMarioCannonObjectYaw | integer |  |
| oMarioTornadoYawVel | integer |  |
| oMarioReadingSignDPosX | number |  |
| oMarioPolePos | number |  |
| oMarioCannonInputYaw | integer |  |
| oMarioTornadoPosY | number |  |
| oMarioReadingSignDPosZ | number |  |
| oMarioWhirlpoolPosY | number |  |
| oMarioBurnTimer | integer |  |
| oMarioLongJumpIsSlow | integer |  |
| oMarioSteepJumpYaw | integer |  |
| oMarioWalkingPitch | integer |  |
| o1UpHiddenUnkF4 | integer |  |
| o1UpForceSpawn | integer |  |
| oActivatedBackAndForthPlatformMaxOffset | number |  |
| oActivatedBackAndForthPlatformOffset | number |  |
| oActivatedBackAndForthPlatformVel | number |  |
| oActivatedBackAndForthPlatformCountdown | integer |  |
| oActivatedBackAndForthPlatformStartYaw | integer |  |
| oActivatedBackAndForthPlatformVertical | integer |  |
| oActivatedBackAndForthPlatformFlipRotation | integer |  |
| oAmpRadiusOfRotation | number |  |
| oAmpYPhase | integer |  |
| oHomingAmpLockedOn | integer |  |
| oHomingAmpAvgY | number |  |
| oArrowLiftDisplacement | number |  |
| oArrowLiftUnk100 | integer |  |
| oBackAndForthPlatformUnkF4 | number |  |
| oBackAndForthPlatformUnkF8 | number |  |
| oBackAndForthPlatformUnkFC | number |  |
| oBackAndForthPlatformUnk100 | number |  |
| oBirdSpeed | number |  |
| oBirdTargetPitch | integer |  |
| oBirdTargetYaw | integer |  |
| oBirdChirpChirpUnkF4 | integer |  |
| oEndBirdUnk104 | number |  |
| oHiddenBlueCoinSwitch | [Object](#Object) |  |
| oBobombBlinkTimer | integer |  |
| oBobombFuseLit | integer |  |
| oBobombFuseTimer | integer |  |
| oBobombBuddyBlinkTimer | integer |  |
| oBobombBuddyHasTalkedToMario | integer |  |
| oBobombBuddyRole | integer |  |
| oBobombBuddyCannonStatus | integer |  |
| oBobombBuddyPosXCopy | number |  |
| oBobombBuddyPosYCopy | number |  |
| oBobombBuddyPosZCopy | number |  |
| oBobombExpBubGfxScaleFacX | integer |  |
| oBobombExpBubGfxScaleFacY | integer |  |
| oBobombExpBubGfxExpRateX | integer |  |
| oBobombExpBubGfxExpRateY | integer |  |
| oSmallBompInitX | number |  |
| oBooDeathStatus | integer |  |
| oBooTargetOpacity | integer |  |
| oBooBaseScale | number |  |
| oBooOscillationTimer | integer |  |
| oBooMoveYawDuringHit | integer |  |
| oBooMoveYawBeforeHit | number |  |
| oBooParentBigBoo | [Object](#Object) |  |
| oBooNegatedAggressiveness | number |  |
| oBooInitialMoveYaw | integer |  |
| oBooTurningSpeed | integer |  |
| oBigBooNumMinionBoosKilled | integer |  |
| oBookendUnkF4 | integer |  |
| oBookendUnkF8 | integer |  |
| oBookSwitchUnkF4 | number |  |
| oBookSwitchManagerUnkF4 | integer |  |
| oBookSwitchManagerUnkF8 | integer |  |
| oHauntedBookshelfShouldOpen | integer |  |
| oBouncingFireBallUnkF4 | integer |  |
| oBowlingBallTargetYaw | integer |  |
| oBBallSpawnerMaxSpawnDist | number |  |
| oBBallSpawnerSpawnOdds | number |  |
| oBBallSpawnerPeriodMinus1 | integer |  |
| oBowserUnk88 | integer |  |
| oBowserUnkF4 | integer |  |
| oBowserUnkF8 | integer |  |
| oBowserDistToCentre | number |  |
| oBowserUnk106 | integer |  |
| oBowserUnk108 | integer |  |
| oBowserHeldAnglePitch | integer |  |
| oBowserHeldAngleVelYaw | integer |  |
| oBowserUnk10E | integer |  |
| oBowserUnk110 | integer |  |
| oBowserAngleToCentre | integer |  |
| oBowserUnk1AC | integer |  |
| oBowserUnk1AE | integer |  |
| oBowserEyesShut | integer |  |
| oBowserUnk1B2 | integer |  |
| oBowserShockWaveUnkF4 | number |  |
| oBlackSmokeBowserUnkF4 | number |  |
| oBowserKeyScale | number |  |
| oBowserPuzzleCompletionFlags | integer |  |
| oBowserPuzzlePieceOffsetX | number |  |
| oBowserPuzzlePieceOffsetY | number |  |
| oBowserPuzzlePieceOffsetZ | number |  |
| oBowserPuzzlePieceContinuePerformingAction | integer |  |
| oBubbaUnkF4 | number |  |
| oBubbaUnkF8 | integer |  |
| oBubbaUnkFC | integer |  |
| oBubbaUnk100 | integer |  |
| oBubbaUnk104 | integer |  |
| oBubbaUnk108 | number |  |
| oBubbaUnk10C | number |  |
| oBubbaUnk1AC | integer |  |
| oBubbaUnk1AE | integer |  |
| oBubbaUnk1B0 | integer |  |
| oBubbaUnk1B2 | integer |  |
| oBulletBillInitialMoveYaw | integer |  |
| oBullySubtype | integer |  |
| oBullyPrevX | number |  |
| oBullyPrevY | number |  |
| oBullyPrevZ | number |  |
| oBullyKBTimerAndMinionKOCounter | integer |  |
| oBullyMarioCollisionAngle | integer |  |
| oButterflyYPhase | integer |  |
| oTripletButterflyScale | number |  |
| oTripletButterflySpeed | number |  |
| oTripletButterflyBaseYaw | number |  |
| oTripletButterflyTargetPitch | integer |  |
| oTripletButterflyTargetYaw | integer |  |
| oTripletButterflyType | integer |  |
| oTripletButterflyModel | integer |  |
| oTripletButterflySelectedButterfly | integer |  |
| oTripletButterflyScalePhase | integer |  |
| oCannonUnkF4 | integer |  |
| oCannonUnkF8 | integer |  |
| oCannonUnk10C | integer |  |
| oCannonPlayerIndex | integer |  |
| oCapUnkF4 | integer |  |
| oCapUnkF8 | integer |  |
| oChainChompSegments | [ChainSegment](#ChainSegment) |  |
| oChainChompMaxDistFromPivotPerChainPart | number |  |
| oChainChompMaxDistBetweenChainParts | number |  |
| oChainChompDistToPivot | number |  |
| oChainChompUnk104 | number |  |
| oChainChompRestrictedByChain | integer |  |
| oChainChompTargetPitch | integer |  |
| oChainChompNumLunges | integer |  |
| oChainChompReleaseStatus | integer |  |
| oChainChompHitGate | integer |  |
| oCheckerBoardPlatformUnkF8 | integer |  |
| oCheckerBoardPlatformUnkFC | integer |  |
| oCheckerBoardPlatformUnk1AC | number |  |
| oCheepCheepUnkF4 | number |  |
| oCheepCheepUnkF8 | number |  |
| oCheepCheepUnkFC | number |  |
| oCheepCheepUnk104 | number |  |
| oCheepCheepUnk108 | number |  |
| oChuckyaUnk88 | integer |  |
| oChuckyaUnkF8 | integer |  |
| oChuckyaUnkFC | integer |  |
| oChuckyaUnk100 | integer |  |
| oClamUnkF4 | integer |  |
| oCloudCenterX | number |  |
| oCloudCenterY | number |  |
| oCloudBlowing | integer |  |
| oCloudGrowSpeed | number |  |
| oCloudFwooshMovementRadius | integer |  |
| oCoinUnkF4 | integer |  |
| oCoinUnkF8 | integer |  |
| oCoinUnk110 | number |  |
| oCoinUnk1B0 | integer |  |
| oCollisionParticleUnkF4 | number |  |
| oControllablePlatformUnkF8 | integer |  |
| oControllablePlatformUnkFC | number |  |
| oControllablePlatformUnk100 | integer |  |
| oBreakableBoxSmallReleased | integer |  |
| oBreakableBoxSmallFramesSinceReleased | integer |  |
| oJumpingBoxUnkF4 | integer |  |
| oJumpingBoxUnkF8 | integer |  |
| oRRCruiserWingUnkF4 | integer |  |
| oRRCruiserWingUnkF8 | integer |  |
| oDonutPlatformSpawnerSpawnedPlatforms | integer |  |
| oDoorUnk88 | integer |  |
| oDoorUnkF8 | integer |  |
| oDoorUnkFC | integer |  |
| oDoorUnk100 | integer |  |
| oDorrieDistToHome | number |  |
| oDorrieOffsetY | number |  |
| oDorrieVelY | number |  |
| oDorrieForwardDistToMario | number |  |
| oDorrieYawVel | integer |  |
| oDorrieLiftingMario | integer |  |
| oDorrieGroundPounded | integer |  |
| oDorrieAngleToHome | integer |  |
| oDorrieNeckAngle | integer |  |
| oDorrieHeadRaiseSpeed | integer |  |
| oElevatorUnkF4 | number |  |
| oElevatorUnkF8 | number |  |
| oElevatorUnkFC | number |  |
| oElevatorUnk100 | integer |  |
| oExclamationBoxUnkF4 | number |  |
| oExclamationBoxUnkF8 | number |  |
| oExclamationBoxUnkFC | integer |  |
| oExclamationBoxForce | integer |  |
| oEyerokBossNumHands | integer |  |
| oEyerokBossUnkFC | integer |  |
| oEyerokBossActiveHand | integer |  |
| oEyerokBossUnk104 | integer |  |
| oEyerokBossUnk108 | number |  |
| oEyerokBossUnk10C | number |  |
| oEyerokBossUnk110 | number |  |
| oEyerokBossUnk1AC | integer |  |
| oEyerokHandWakeUpTimer | integer |  |
| oEyerokReceivedAttack | integer |  |
| oEyerokHandUnkFC | integer |  |
| oEyerokHandUnk100 | integer |  |
| oEyerokHandDead | integer |  |
| oFallingPillarPitchAcceleration | number |  |
| oFireSpitterScaleVel | number |  |
| oFireSpitterLastWaterY | number |  |
| oBlueFishRandomVel | number |  |
| oBlueFishRandomTime | integer |  |
| oBlueFishRandomAngle | number |  |
| oFishWaterLevel | number |  |
| oFishPosY | number |  |
| oFishRandomOffset | number |  |
| oFishRandomSpeed | integer |  |
| oFishRespawnDistance | number |  |
| oFishRandomVel | number |  |
| oFishDepthDistance | number |  |
| oFishActiveDistance | number |  |
| oFlameUnkF4 | number |  |
| oFlameUnkF8 | integer |  |
| oFlameUnkFC | number |  |
| oFlameUnk100 | [Object](#Object) |  |
| oBlueFlameUnkF8 | number |  |
| oSmallPiranhaFlameStartSpeed | number |  |
| oSmallPiranhaFlameEndSpeed | number |  |
| oSmallPiranhaFlameModel | integer |  |
| oSmallPiranhaFlameUnk100 | integer |  |
| oSmallPiranhaFlameUnk104 | number |  |
| oMovingFlameTimer | integer |  |
| oFlameThowerFlameUnk110 | integer |  |
| oFlameThowerUnk110 | integer |  |
| oFloatingPlatformUnkF4 | integer |  |
| oFloatingPlatformUnkF8 | number |  |
| oFloatingPlatformUnkFC | number |  |
| oFloatingPlatformUnk100 | integer |  |
| oFloorSwitchPressAnimationUnkF4 | integer |  |
| oFloorSwitchPressAnimationUnkF8 | integer |  |
| oFloorSwitchPressAnimationUnkFC | integer |  |
| oFloorSwitchPressAnimationUnk100 | integer |  |
| oFlyGuyIdleTimer | integer |  |
| oFlyGuyOscTimer | integer |  |
| oFlyGuyUnusedJitter | integer |  |
| oFlyGuyLungeYDecel | number |  |
| oFlyGuyLungeTargetPitch | integer |  |
| oFlyGuyTargetRoll | integer |  |
| oFlyGuyScaleVel | number |  |
| oGrandStarUnk108 | integer |  |
| oHorizontalGrindelTargetYaw | integer |  |
| oHorizontalGrindelDistToHome | number |  |
| oHorizontalGrindelOnGround | integer |  |
| oGoombaSize | integer |  |
| oGoombaScale | number |  |
| oGoombaWalkTimer | integer |  |
| oGoombaTargetYaw | integer |  |
| oGoombaBlinkTimer | integer |  |
| oGoombaTurningAwayFromWall | integer |  |
| oGoombaRelativeSpeed | number |  |
| oGoombaJumpCooldown | integer |  |
| oHauntedChairUnkF4 | integer |  |
| oHauntedChairUnkF8 | number |  |
| oHauntedChairUnkFC | number |  |
| oHauntedChairUnk100 | Pointer <integer> | read-only |
| oHauntedChairUnk104 | integer |  |
| oHeaveHoUnk88 | integer |  |
| oHeaveHoUnkF4 | number |  |
| oHiddenObjectUnkF4 | [Object](#Object) |  |
| oHootAvailability | integer |  |
| oHootMarioReleaseTime | integer |  |
| oHorizontalMovementUnkF4 | integer |  |
| oHorizontalMovementUnkF8 | integer |  |
| oHorizontalMovementUnk100 | number |  |
| oHorizontalMovementUnk104 | integer |  |
| oHorizontalMovementUnk108 | number |  |
| oKickableBoardF4 | integer |  |
| oKickableBoardF8 | integer |  |
| oKingBobombUnk88 | integer |  |
| oKingBobombUnkF8 | integer |  |
| oKingBobombUnkFC | integer |  |
| oKingBobombUnk100 | integer |  |
| oKingBobombUnk104 | integer |  |
| oKingBobombUnk108 | integer |  |
| oKleptoDistanceToTarget | number |  |
| oKleptoUnkF8 | number |  |
| oKleptoUnkFC | number |  |
| oKleptoSpeed | number |  |
| oKleptoStartPosX | number |  |
| oKleptoStartPosY | number |  |
| oKleptoStartPosZ | number |  |
| oKleptoTimeUntilTargetChange | integer |  |
| oKleptoTargetNumber | integer |  |
| oKleptoUnk1AE | integer |  |
| oKleptoUnk1B0 | integer |  |
| oKleptoYawToTarget | integer |  |
| oKoopaAgility | number |  |
| oKoopaMovementType | integer |  |
| oKoopaTargetYaw | integer |  |
| oKoopaUnshelledTimeUntilTurn | integer |  |
| oKoopaTurningAwayFromWall | integer |  |
| oKoopaDistanceToMario | number |  |
| oKoopaAngleToMario | integer |  |
| oKoopaBlinkTimer | integer |  |
| oKoopaCountdown | integer |  |
| oKoopaTheQuickRaceIndex | integer |  |
| oKoopaTheQuickInitTextboxCooldown | integer |  |
| oKoopaRaceEndpointRaceBegun | integer |  |
| oKoopaRaceEndpointKoopaFinished | integer |  |
| oKoopaRaceEndpointRaceStatus | integer |  |
| oKoopaRaceEndpointUnk100 | integer |  |
| oKoopaRaceEndpointRaceEnded | integer |  |
| oKoopaShellFlameUnkF4 | number |  |
| oKoopaShellFlameUnkF8 | number |  |
| oCameraLakituBlinkTimer | integer |  |
| oCameraLakituSpeed | number |  |
| oCameraLakituCircleRadius | number |  |
| oCameraLakituFinishedDialog | integer |  |
| oCameraLakituUnk104 | integer |  |
| oCameraLakituPitchVel | integer |  |
| oCameraLakituYawVel | integer |  |
| oEnemyLakituNumSpinies | integer |  |
| oEnemyLakituBlinkTimer | integer |  |
| oEnemyLakituSpinyCooldown | integer |  |
| oEnemyLakituFaceForwardCountdown | integer |  |
| oIntroLakituSplineSegmentProgress | number |  |
| oIntroLakituSplineSegment | number |  |
| oIntroLakituUnk100 | number |  |
| oIntroLakituUnk104 | number |  |
| oIntroLakituUnk108 | number |  |
| oIntroLakituUnk10C | number |  |
| oIntroLakituUnk110 | number |  |
| oIntroLakituCloud | [Object](#Object) |  |
| oMenuButtonState | integer |  |
| oMenuButtonTimer | integer |  |
| oMenuButtonOrigPosX | number |  |
| oMenuButtonOrigPosY | number |  |
| oMenuButtonOrigPosZ | number |  |
| oMenuButtonScale | number |  |
| oMenuButtonActionPhase | integer |  |
| oMenuButtonIsCustom | integer |  |
| oMantaUnkF4 | integer |  |
| oMantaUnkF8 | integer |  |
| oMantaUnk1AC | integer |  |
| oMerryGoRoundStopped | integer |  |
| oMerryGoRoundMusicShouldPlay | integer |  |
| oMerryGoRoundMarioIsOutside | integer |  |
| oMerryGoRoundBooManagerNumBoosKilled | integer |  |
| oMerryGoRoundBooManagerNumBoosSpawned | integer |  |
| oMipsStarStatus | integer |  |
| oMipsStartWaypointIndex | integer |  |
| oMipsForwardVelocity | number |  |
| oMoneybagJumpState | integer |  |
| oMontyMoleCurrentHole | [Object](#Object) |  |
| oMontyMoleHeightRelativeToFloor | number |  |
| oMontyMoleHoleX | number |  |
| oMontyMoleHoleY | number |  |
| oMontyMoleHoleZ | number |  |
| oMontyMoleHoleCooldown | integer |  |
| oMrBlizzardScale | number |  |
| oMrBlizzardHeldObj | [Object](#Object) |  |
| oMrBlizzardGraphYVel | number |  |
| oMrBlizzardTimer | integer |  |
| oMrBlizzardDizziness | number |  |
| oMrBlizzardChangeInDizziness | number |  |
| oMrBlizzardGraphYOffset | number |  |
| oMrBlizzardDistFromHome | integer |  |
| oMrBlizzardTargetMoveYaw | integer |  |
| oMrIUnkF4 | integer |  |
| oMrIUnkFC | integer |  |
| oMrIUnk100 | integer |  |
| oMrIUnk104 | integer |  |
| oMrIUnk108 | integer |  |
| oMrISize | number |  |
| oMrIUnk110 | integer |  |
| oRespawnerModelToRespawn | integer |  |
| oRespawnerMinSpawnDist | number |  |
| oOpenableGrillUnk88 | integer |  |
| oOpenableGrillUnkF4 | [Object](#Object) |  |
| oIntroPeachYawFromFocus | number |  |
| oIntroPeachPitchFromFocus | number |  |
| oIntroPeachDistToCamera | number |  |
| oRacingPenguinInitTextCooldown | integer |  |
| oRacingPenguinWeightedNewTargetSpeed | number |  |
| oRacingPenguinFinalTextbox | integer |  |
| oRacingPenguinMarioWon | integer |  |
| oRacingPenguinReachedBottom | integer |  |
| oRacingPenguinMarioCheated | integer |  |
| oSmallPenguinUnk88 | integer |  |
| oSmallPenguinUnk100 | integer |  |
| oSmallPenguinUnk104 | number |  |
| oSmallPenguinUnk108 | number |  |
| oSmallPenguinUnk110 | integer |  |
| oSLWalkingPenguinWindCollisionXPos | number |  |
| oSLWalkingPenguinWindCollisionZPos | number |  |
| oSLWalkingPenguinCurStep | integer |  |
| oSLWalkingPenguinCurStepTimer | integer |  |
| oPiranhaPlantSleepMusicState | integer |  |
| oPiranhaPlantScale | number |  |
| oFirePiranhaPlantNeutralScale | number |  |
| oFirePiranhaPlantScale | number |  |
| oFirePiranhaPlantActive | integer |  |
| oFirePiranhaPlantDeathSpinTimer | integer |  |
| oFirePiranhaPlantDeathSpinVel | number |  |
| oPitouneUnkF4 | number |  |
| oPitouneUnkF8 | number |  |
| oPitouneUnkFC | number |  |
| oPlatformTimer | integer |  |
| oPlatformUnkF8 | [Object](#Object) |  |
| oPlatformUnkFC | integer |  |
| oPlatformUnk10C | number |  |
| oPlatformUnk110 | number |  |
| oPlatformOnTrackBaseBallIndex | integer |  |
| oPlatformOnTrackDistMovedSinceLastBall | number |  |
| oPlatformOnTrackSkiLiftRollVel | number |  |
| oPlatformOnTrackStartWaypoint | [Waypoint](#Waypoint) |  |
| oPlatformOnTrackPrevWaypoint | [Waypoint](#Waypoint) |  |
| oPlatformOnTrackPrevWaypointFlags | integer |  |
| oPlatformOnTrackPitch | integer |  |
| oPlatformOnTrackYaw | integer |  |
| oPlatformOnTrackOffsetY | number |  |
| oPlatformOnTrackIsNotSkiLift | integer |  |
| oPlatformOnTrackIsNotHMC | integer |  |
| oPlatformOnTrackType | integer |  |
| oPlatformOnTrackWasStoodOn | integer |  |
| oPlatformSpawnerUnkF4 | integer |  |
| oPlatformSpawnerUnkF8 | integer |  |
| oPlatformSpawnerUnkFC | integer |  |
| oPlatformSpawnerUnk100 | number |  |
| oPlatformSpawnerUnk104 | number |  |
| oPlatformSpawnerUnk108 | number |  |
| oPokeyAliveBodyPartFlags | integer |  |
| oPokeyNumAliveBodyParts | integer |  |
| oPokeyBottomBodyPartSize | number |  |
| oPokeyHeadWasKilled | integer |  |
| oPokeyTargetYaw | integer |  |
| oPokeyChangeTargetTimer | integer |  |
| oPokeyTurningAwayFromWall | integer |  |
| oPokeyBodyPartDeathDelayAfterHeadKilled | integer |  |
| oPokeyBodyPartBlinkTimer | integer |  |
| oDDDPoleVel | number |  |
| oDDDPoleMaxOffset | number |  |
| oDDDPoleOffset | number |  |
| oPyramidTopPillarsTouched | integer |  |
| oPyramidTopFragmentsScale | number |  |
| oRollingLogUnkF4 | number |  |
| oLllRotatingHexFlameUnkF4 | number |  |
| oLllRotatingHexFlameUnkF8 | number |  |
| oLllRotatingHexFlameUnkFC | number |  |
| oScuttlebugUnkF4 | integer |  |
| oScuttlebugUnkF8 | integer |  |
| oScuttlebugUnkFC | integer |  |
| oScuttlebugSpawnerUnk88 | integer |  |
| oScuttlebugSpawnerUnkF4 | integer |  |
| oSeesawPlatformPitchVel | number |  |
| oShipPart3UnkF4 | integer |  |
| oShipPart3UnkF8 | integer |  |
| oSinkWhenSteppedOnUnk104 | integer |  |
| oSinkWhenSteppedOnUnk108 | number |  |
| oSkeeterTargetAngle | integer |  |
| oSkeeterUnkF8 | integer |  |
| oSkeeterUnkFC | number |  |
| oSkeeterWaitTime | integer |  |
| oSkeeterLastWaterY | number |  |
| oSkeeterUnk1AC | integer |  |
| oJrbSlidingBoxUnkF4 | [Object](#Object) |  |
| oJrbSlidingBoxUnkF8 | integer |  |
| oJrbSlidingBoxUnkFC | number |  |
| oWFSlidBrickPtfmMovVel | number |  |
| oSmokeTimer | integer |  |
| oSnowmansBottomUnkF4 | number |  |
| oSnowmansBottomUnkF8 | integer |  |
| oSnowmansBottomUnk1AC | integer |  |
| oSnowmansHeadUnkF4 | integer |  |
| oSLSnowmanWindOriginalYaw | integer |  |
| oSnufitRecoil | integer |  |
| oSnufitScale | number |  |
| oSnufitCircularPeriod | integer |  |
| oSnufitBodyScalePeriod | integer |  |
| oSnufitBodyBaseScale | integer |  |
| oSnufitBullets | integer |  |
| oSnufitXOffset | integer |  |
| oSnufitYOffset | integer |  |
| oSnufitZOffset | integer |  |
| oSnufitBodyScale | integer |  |
| oSpindelUnkF4 | integer |  |
| oSpindelUnkF8 | integer |  |
| oSpinningHeartTotalSpin | integer |  |
| oSpinningHeartPlayedSound | integer |  |
| oSpinyTimeUntilTurn | integer |  |
| oSpinyTargetYaw | integer |  |
| oSpinyTurningAwayFromWall | integer |  |
| oSoundEffectUnkF4 | integer |  |
| oStarSpawnDisFromHome | number |  |
| oStarSpawnUnkFC | number |  |
| oHiddenStarTriggerCounter | integer |  |
| oSparkleSpawnUnk1B0 | integer |  |
| oUnlockDoorStarState | integer |  |
| oUnlockDoorStarTimer | integer |  |
| oUnlockDoorStarYawVel | integer |  |
| oCelebStarUnkF4 | integer |  |
| oCelebStarDiameterOfRotation | integer |  |
| oStarSelectorType | integer |  |
| oStarSelectorTimer | integer |  |
| oStarSelectorSize | number |  |
| oSushiSharkUnkF4 | integer |  |
| oSwingPlatformAngle | number |  |
| oSwingPlatformSpeed | number |  |
| oSwoopBonkCountdown | integer |  |
| oSwoopTargetPitch | integer |  |
| oSwoopTargetYaw | integer |  |
| oThwompRandomTimer | integer |  |
| oTiltingPyramidNormalX | number |  |
| oTiltingPyramidNormalY | number |  |
| oTiltingPyramidNormalZ | number |  |
| oTiltingPyramidMarioOnPlatform | integer |  |
| oToadMessageDialogId | integer |  |
| oToadMessageRecentlyTalked | integer |  |
| oToadMessageState | integer |  |
| oToxBoxMovementStep | integer |  |
| oTTCRotatingSolidNumTurns | integer |  |
| oTTCRotatingSolidNumSides | integer |  |
| oTTCRotatingSolidRotationDelay | integer |  |
| oTTCRotatingSolidVelY | number |  |
| oTTCRotatingSolidSoundTimer | integer |  |
| oTTCPendulumAccelDir | number |  |
| oTTCPendulumAngle | number |  |
| oTTCPendulumAngleVel | number |  |
| oTTCPendulumAngleAccel | number |  |
| oTTCPendulumDelay | integer |  |
| oTTCPendulumSoundTimer | integer |  |
| oTTCTreadmillBigSurface | Pointer <integer> | read-only |
| oTTCTreadmillSmallSurface | Pointer <integer> | read-only |
| oTTCTreadmillSpeed | number |  |
| oTTCTreadmillTargetSpeed | number |  |
| oTTCTreadmillTimeUntilSwitch | integer |  |
| oTTCMovingBarDelay | integer |  |
| oTTCMovingBarStoppedTimer | integer |  |
| oTTCMovingBarOffset | number |  |
| oTTCMovingBarSpeed | number |  |
| oTTCMovingBarStartOffset | number |  |
| oTTCCogDir | number |  |
| oTTCCogSpeed | number |  |
| oTTCCogTargetVel | number |  |
| oTTCPitBlockPeakY | number |  |
| oTTCPitBlockDir | integer |  |
| oTTCPitBlockWaitTime | integer |  |
| oTTCElevatorDir | number |  |
| oTTCElevatorPeakY | number |  |
| oTTCElevatorMoveTime | integer |  |
| oTTC2DRotatorMinTimeUntilNextTurn | integer |  |
| oTTC2DRotatorTargetYaw | integer |  |
| oTTC2DRotatorIncrement | integer |  |
| oTTC2DRotatorRandomDirTimer | integer |  |
| oTTC2DRotatorSpeed | integer |  |
| oTTCSpinnerDir | integer |  |
| oTTCChangeDirTimer | integer |  |
| oBetaTrampolineMarioOnTrampoline | integer |  |
| oTreasureChestUnkF4 | integer |  |
| oTreasureChestUnkF8 | integer |  |
| oTreasureChestUnkFC | integer |  |
| oTreasureChestSound | integer |  |
| oTreeSnowOrLeafUnkF4 | integer |  |
| oTreeSnowOrLeafUnkF8 | integer |  |
| oTreeSnowOrLeafUnkFC | integer |  |
| oTumblingBridgeUnkF4 | integer |  |
| oTweesterScaleTimer | integer |  |
| oTweesterUnused | integer |  |
| oUkikiTauntCounter | integer |  |
| oUkikiTauntsToBeDone | integer |  |
| oUkikiChaseFleeRange | number |  |
| oUkikiTextState | integer |  |
| oUkikiTextboxTimer | integer |  |
| oUkikiCageSpinTimer | integer |  |
| oUkikiHasCap | integer |  |
| oUkikiCageNextAction | integer |  |
| oUnagiUnkF4 | number |  |
| oUnagiUnkF8 | number |  |
| oUnagiUnk110 | number |  |
| oUnagiUnk1AC | number |  |
| oUnagiUnk1B0 | integer |  |
| oUnagiUnk1B2 | integer |  |
| oWaterBombVerticalStretch | number |  |
| oWaterBombStretchSpeed | number |  |
| oWaterBombOnGround | integer |  |
| oWaterBombNumBounces | number |  |
| oWaterBombSpawnerBombActive | integer |  |
| oWaterBombSpawnerTimeToSpawn | integer |  |
| oWaterCannonUnkF4 | integer |  |
| oWaterCannonUnkF8 | integer |  |
| oWaterCannonUnkFC | integer |  |
| oWaterCannonUnk100 | integer |  |
| oCannonBarrelBubblesUnkF4 | number |  |
| oWaterLevelPillarDrained | integer |  |
| oWaterLevelTriggerUnkF4 | integer |  |
| oWaterLevelTriggerTargetWaterLevel | integer |  |
| oWaterObjUnkF4 | integer |  |
| oWaterObjUnkF8 | integer |  |
| oWaterObjUnkFC | integer |  |
| oWaterObjUnk100 | integer |  |
| oWaterRingScalePhaseX | integer |  |
| oWaterRingScalePhaseY | integer |  |
| oWaterRingScalePhaseZ | integer |  |
| oWaterRingNormalX | number |  |
| oWaterRingNormalY | number |  |
| oWaterRingNormalZ | number |  |
| oWaterRingMarioDistInFront | number |  |
| oWaterRingIndex | integer |  |
| oWaterRingAvgScale | number |  |
| oWaterRingSpawnerRingsCollected | integer |  |
| oWaterRingMgrNextRingIndex | integer |  |
| oWaterRingMgrLastRingCollected | integer |  |
| oWaveTrailSize | number |  |
| oWhirlpoolInitFacePitch | integer |  |
| oWhirlpoolInitFaceRoll | integer |  |
| oWhirlpoolTimeout | integer |  |
| oWhitePuffUnkF4 | number |  |
| oWhitePuffUnkF8 | integer |  |
| oWhitePuffUnkFC | integer |  |
| oStrongWindParticlePenguinObj | [Object](#Object) |  |
| oWhompShakeVal | integer |  |
| oWigglerFallThroughFloorsHeight | number |  |
| oWigglerSegments | [ChainSegment](#ChainSegment) |  |
| oWigglerWalkAnimSpeed | number |  |
| oWigglerSquishSpeed | number |  |
| oWigglerTimeUntilRandomTurn | integer |  |
| oWigglerTargetYaw | integer |  |
| oWigglerWalkAwayFromWallTimer | integer |  |
| oWigglerUnused | integer |  |
| oWigglerTextStatus | integer |  |
| oLllWoodPieceOscillationTimer | integer |  |
| oWoodenPostTotalMarioAngle | integer |  |
| oWoodenPostPrevAngleToMario | integer |  |
| oWoodenPostSpeedY | number |  |
| oWoodenPostMarioPounding | integer |  |
| oWoodenPostOffsetY | number |  |
| oYoshiBlinkTimer | integer |  |
| oYoshiChosenHome | integer |  |
| oYoshiTargetYaw | integer |  |
| oBreakableWallForce | integer |  |

[:arrow_up_small:](#)

<br />

## [ObjectHitbox](#ObjectHitbox)

| Field | Type | Access |
| ----- | ---- | ------ |
| damageOrCoinValue | integer |  |
| downOffset | integer |  |
| health | integer |  |
| height | integer |  |
| hurtboxHeight | integer |  |
| hurtboxRadius | integer |  |
| interactType | integer |  |
| numLootCoins | integer |  |
| radius | integer |  |

[:arrow_up_small:](#)

<br />

## [ObjectNode](#ObjectNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| gfx | [GraphNodeObject](#GraphNodeObject) | read-only |
| next | [ObjectNode](#ObjectNode) |  |
| prev | [ObjectNode](#ObjectNode) |  |

[:arrow_up_small:](#)

<br />

## [ObjectWarpNode](#ObjectWarpNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| next | [ObjectWarpNode](#ObjectWarpNode) |  |
| node | [WarpNode](#WarpNode) | read-only |
| object | [Object](#Object) |  |

[:arrow_up_small:](#)

<br />

## [OffsetSizePair](#OffsetSizePair)

| Field | Type | Access |
| ----- | ---- | ------ |
| offset | integer |  |
| size | integer |  |

[:arrow_up_small:](#)

<br />

## [ParallelTrackingPoint](#ParallelTrackingPoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| distThresh | number |  |
| pos | [Vec3f](#Vec3f) | read-only |
| startOfPath | integer |  |
| zoom | number |  |

[:arrow_up_small:](#)

<br />

## [PlayerCameraState](#PlayerCameraState)

| Field | Type | Access |
| ----- | ---- | ------ |
| action | integer |  |
| cameraEvent | integer |  |
| faceAngle | [Vec3s](#Vec3s) | read-only |
| headRotation | [Vec3s](#Vec3s) | read-only |
| pos | [Vec3f](#Vec3f) | read-only |
| unused | integer |  |
| usedObj | [Object](#Object) |  |

[:arrow_up_small:](#)

<br />

## [PlayerGeometry](#PlayerGeometry)

| Field | Type | Access |
| ----- | ---- | ------ |
| currCeil | [Surface](#Surface) |  |
| currCeilHeight | number |  |
| currCeilType | integer |  |
| currFloor | [Surface](#Surface) |  |
| currFloorHeight | number |  |
| currFloorType | integer |  |
| prevCeil | [Surface](#Surface) |  |
| prevCeilHeight | number |  |
| prevCeilType | integer |  |
| prevFloor | [Surface](#Surface) |  |
| prevFloorHeight | number |  |
| prevFloorType | integer |  |
| waterHeight | number |  |

[:arrow_up_small:](#)

<br />

## [SpawnInfo](#SpawnInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| activeAreaIndex | integer |  |
| areaIndex | integer |  |
| behaviorArg | integer |  |
| next | [SpawnInfo](#SpawnInfo) |  |
| startAngle | [Vec3s](#Vec3s) | read-only |
| startPos | [Vec3s](#Vec3s) | read-only |
| unk18 | [GraphNode](#GraphNode) |  |

[:arrow_up_small:](#)

<br />

## [SpawnParticlesInfo](#SpawnParticlesInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| behParam | integer |  |
| count | integer |  |
| dragStrength | integer |  |
| forwardVelBase | integer |  |
| forwardVelRange | integer |  |
| gravity | integer |  |
| model | integer |  |
| offsetY | integer |  |
| sizeBase | number |  |
| sizeRange | number |  |
| velYBase | integer |  |
| velYRange | integer |  |

[:arrow_up_small:](#)

<br />

## [Struct802A272C](#Struct802A272C)

| Field | Type | Access |
| ----- | ---- | ------ |
| vecF | [Vec3f](#Vec3f) | read-only |
| vecS | [Vec3s](#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [Surface](#Surface)

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | integer |  |
| force | integer |  |
| lowerY | integer |  |
| modifiedTimestamp | integer |  |
| normal | [Vec3f](#Vec3f) | read-only |
| object | [Object](#Object) |  |
| originOffset | number |  |
| prevVertex1 | [Vec3s](#Vec3s) | read-only |
| prevVertex2 | [Vec3s](#Vec3s) | read-only |
| prevVertex3 | [Vec3s](#Vec3s) | read-only |
| room | integer |  |
| type | integer |  |
| upperY | integer |  |
| vertex1 | [Vec3s](#Vec3s) | read-only |
| vertex2 | [Vec3s](#Vec3s) | read-only |
| vertex3 | [Vec3s](#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [TextureInfo](#TextureInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| bitSize | const u8 | read-only |
| height | const u32 | read-only |
| texture | Pointer <integer> | read-only |
| width | const u32 | read-only |

[:arrow_up_small:](#)

<br />

## [TransitionInfo](#TransitionInfo)

| Field | Type | Access |
| ----- | ---- | ------ |
| focDist | number |  |
| focPitch | integer |  |
| focYaw | integer |  |
| framesLeft | integer |  |
| marioPos | [Vec3f](#Vec3f) | read-only |
| pad | integer |  |
| posDist | number |  |
| posPitch | integer |  |
| posYaw | integer |  |

[:arrow_up_small:](#)

<br />

## [Vec3f](#Vec3f)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | float |  |
| y | float |  |
| z | float |  |

[:arrow_up_small:](#)

<br />

## [Vec3s](#Vec3s)

| Field | Type | Access |
| ----- | ---- | ------ |
| x | integer |  |
| y | integer |  |
| z | integer |  |

[:arrow_up_small:](#)

<br />

## [WallCollisionData](#WallCollisionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| numWalls | integer |  |
| offsetY | number |  |
| radius | number |  |
| unk14 | integer |  |

[:arrow_up_small:](#)

<br />

## [WarpNode](#WarpNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| destArea | integer |  |
| destLevel | integer |  |
| destNode | integer |  |
| id | integer |  |

[:arrow_up_small:](#)

<br />

## [WarpTransition](#WarpTransition)

| Field | Type | Access |
| ----- | ---- | ------ |
| data | [WarpTransitionData](#WarpTransitionData) | read-only |
| isActive | integer |  |
| pauseRendering | integer |  |
| time | integer |  |
| type | integer |  |

[:arrow_up_small:](#)

<br />

## [WarpTransitionData](#WarpTransitionData)

| Field | Type | Access |
| ----- | ---- | ------ |
| blue | integer |  |
| endTexRadius | integer |  |
| endTexX | integer |  |
| endTexY | integer |  |
| green | integer |  |
| red | integer |  |
| startTexRadius | integer |  |
| startTexX | integer |  |
| startTexY | integer |  |
| texTimer | integer |  |

[:arrow_up_small:](#)

<br />

## [WaterDropletParams](#WaterDropletParams)

| Field | Type | Access |
| ----- | ---- | ------ |
| behavior | Pointer <BehaviorScript> | read-only |
| flags | integer |  |
| model | integer |  |
| moveAngleRange | integer |  |
| moveRange | integer |  |
| randForwardVelOffset | number |  |
| randForwardVelScale | number |  |
| randSizeOffset | number |  |
| randSizeScale | number |  |
| randYVelOffset | number |  |
| randYVelScale | number |  |

[:arrow_up_small:](#)

<br />

## [Waypoint](#Waypoint)

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | integer |  |
| pos | [Vec3s](#Vec3s) | read-only |

[:arrow_up_small:](#)

<br />

## [Whirlpool](#Whirlpool)

| Field | Type | Access |
| ----- | ---- | ------ |
| pos | [Vec3s](#Vec3s) | read-only |
| strength | integer |  |

[:arrow_up_small:](#)

<br />

## [struct802A1230](#struct802A1230)

| Field | Type | Access |
| ----- | ---- | ------ |
| unk00 | integer |  |
| unk02 | integer |  |

[:arrow_up_small:](#)

<br />

