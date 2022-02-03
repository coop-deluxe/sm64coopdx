## [:rewind: Lua Reference](lua.md)

# Supported Structs
- [Animation](#Animation)
- [Area](#Area)
- [Camera](#Camera)
- [CameraFOVStatus](#CameraFOVStatus)
- [CameraStoredInfo](#CameraStoredInfo)
- [CameraTrigger](#CameraTrigger)
- [Character](#Character)
- [Controller](#Controller)
- [Cutscene](#Cutscene)
- [CutsceneSplinePoint](#CutsceneSplinePoint)
- [CutsceneVariable](#CutsceneVariable)
- [FloorGeometry](#FloorGeometry)
- [GraphNode](#GraphNode)
- [GraphNodeObject](#GraphNodeObject)
- [GraphNodeObject_sub](#GraphNodeObject_sub)
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
- [Surface](#Surface)
- [TransitionInfo](#TransitionInfo)
- [UnusedArea28](#UnusedArea28)
- [VblankHandler](#VblankHandler)
- [Vec3f](#Vec3f)
- [Vec3s](#Vec3s)
- [WallCollisionData](#WallCollisionData)
- [WarpNode](#WarpNode)
- [WarpTransition](#WarpTransition)
- [WarpTransitionData](#WarpTransitionData)
- [Waypoint](#Waypoint)
- [Whirlpool](#Whirlpool)

<br />

## [Animation](#Animation)

| Field | Type |
| ----- | ---- |
| flags | integer |
| length | integer |
| animYTransDivisor | integer |
| startFrame | integer |
| loopStart | integer |
| loopEnd | integer |
| unusedBoneCount | integer |

[:arrow_up_small:](#)

<br />

## [Area](#Area)

| Field | Type |
| ----- | ---- |
| camera | [Camera](#Camera) |
| flags | integer |
| index | integer |
| instantWarps | [InstantWarp](#InstantWarp) |
| musicParam | integer |
| musicParam2 | integer |
| objectSpawnInfos | [SpawnInfo](#SpawnInfo) |
| paintingWarpNodes | [WarpNode](#WarpNode) |
| terrainType | integer |
| warpNodes | [ObjectWarpNode](#ObjectWarpNode) |

[:arrow_up_small:](#)

<br />

## [Camera](#Camera)

| Field | Type |
| ----- | ---- |
| areaCenX | number |
| areaCenY | number |
| areaCenZ | number |
| cutscene | integer |
| defMode | integer |
| doorStatus | integer |
| focus | [Vec3f](#Vec3f) |
| mode | integer |
| nextYaw | integer |
| pos | [Vec3f](#Vec3f) |
| unusedVec1 | [Vec3f](#Vec3f) |
| yaw | integer |

[:arrow_up_small:](#)

<br />

## [CameraFOVStatus](#CameraFOVStatus)

| Field | Type |
| ----- | ---- |
| decay | integer |
| fov | number |
| fovFunc | integer |
| fovOffset | number |
| shakeAmplitude | number |
| shakePhase | integer |
| shakeSpeed | integer |
| unusedIsSleeping | integer |

[:arrow_up_small:](#)

<br />

## [CameraStoredInfo](#CameraStoredInfo)

| Field | Type |
| ----- | ---- |
| cannonYOffset | number |
| focus | [Vec3f](#Vec3f) |
| panDist | number |
| pos | [Vec3f](#Vec3f) |

[:arrow_up_small:](#)

<br />

## [CameraTrigger](#CameraTrigger)

| Field | Type |
| ----- | ---- |
| area | integer |
| boundsX | integer |
| boundsY | integer |
| boundsYaw | integer |
| boundsZ | integer |
| centerX | integer |
| centerY | integer |
| centerZ | integer |

[:arrow_up_small:](#)

<br />

## [Character](#Character)

| Field | Type |
| ----- | ---- |
| animOffsetEnabled | integer |
| animOffsetFeet | number |
| animOffsetHand | number |
| animOffsetLowYPoint | number |
| cameraHudHead | integer |
| capEnemyLayer | integer |
| capMetalModelId | integer |
| capMetalWingModelId | integer |
| capModelId | integer |
| capWingModelId | integer |
| modelId | integer |
| name | string |
| soundAttacked | integer |
| soundCoughing1 | integer |
| soundCoughing2 | integer |
| soundCoughing3 | integer |
| soundDoh | integer |
| soundDrowning | integer |
| soundDying | integer |
| soundEeuh | integer |
| soundFreqScale | number |
| soundGameOver | integer |
| soundGroundPoundWah | integer |
| soundHaha | integer |
| soundHaha_2 | integer |
| soundHello | integer |
| soundHereWeGo | integer |
| soundHoohoo | integer |
| soundHrmm | integer |
| soundImaTired | integer |
| soundMamaMia | integer |
| soundOnFire | integer |
| soundOoof | integer |
| soundOoof2 | integer |
| soundPanting | integer |
| soundPantingCold | integer |
| soundPressStartToPlay | integer |
| soundPunchHoo | integer |
| soundPunchWah | integer |
| soundPunchYah | integer |
| soundSnoring1 | integer |
| soundSnoring2 | integer |
| soundSnoring3 | integer |
| soundSoLongaBowser | integer |
| soundTwirlBounce | integer |
| soundUh | integer |
| soundUh2 | integer |
| soundUh2_2 | integer |
| soundWaaaooow | integer |
| soundWah2 | integer |
| soundWhoa | integer |
| soundYahWahHoo | integer |
| soundYahoo | integer |
| soundYahooWahaYippee | integer |
| soundYawning | integer |
| type | integer |

[:arrow_up_small:](#)

<br />

## [Controller](#Controller)

| Field | Type |
| ----- | ---- |
| buttonDown | integer |
| buttonPressed | integer |
| extStickX | integer |
| extStickY | integer |
| port | integer |
| rawStickX | integer |
| rawStickY | integer |
| stickMag | number |
| stickX | number |
| stickY | number |

[:arrow_up_small:](#)

<br />

## [Cutscene](#Cutscene)

| Field | Type |
| ----- | ---- |
| duration | integer |

[:arrow_up_small:](#)

<br />

## [CutsceneSplinePoint](#CutsceneSplinePoint)

| Field | Type |
| ----- | ---- |
| index | integer |
| point | [Vec3s](#Vec3s) |
| speed | integer |

[:arrow_up_small:](#)

<br />

## [CutsceneVariable](#CutsceneVariable)

| Field | Type |
| ----- | ---- |
| angle | [Vec3s](#Vec3s) |
| point | [Vec3f](#Vec3f) |
| unused1 | integer |
| unused2 | integer |
| unusedPoint | [Vec3f](#Vec3f) |

[:arrow_up_small:](#)

<br />

## [FloorGeometry](#FloorGeometry)

| Field | Type |
| ----- | ---- |
| normalX | number |
| normalY | number |
| normalZ | number |
| originOffset | number |

[:arrow_up_small:](#)

<br />

## [GraphNode](#GraphNode)

| Field | Type |
| ----- | ---- |
| children | [GraphNode](#GraphNode) |
| flags | integer |
| next | [GraphNode](#GraphNode) |
| parent | [GraphNode](#GraphNode) |
| prev | [GraphNode](#GraphNode) |
| type | integer |

[:arrow_up_small:](#)

<br />

## [GraphNodeObject](#GraphNodeObject)

| Field | Type |
| ----- | ---- |
| angle | [Vec3s](#Vec3s) |
| cameraToObject | [Vec3f](#Vec3f) |
| node | [GraphNode](#GraphNode) |
| pos | [Vec3f](#Vec3f) |
| prevAngle | [Vec3s](#Vec3s) |
| prevPos | [Vec3f](#Vec3f) |
| prevScale | [Vec3f](#Vec3f) |
| prevScaleTimestamp | integer |
| prevShadowPos | [Vec3f](#Vec3f) |
| prevShadowPosTimestamp | integer |
| prevThrowMatrixTimestamp | integer |
| prevTimestamp | integer |
| scale | [Vec3f](#Vec3f) |
| sharedChild | [GraphNode](#GraphNode) |
| skipInterpolationTimestamp | integer |
| unk18 | integer |
| unk19 | integer |
| animInfo | [GraphNodeObject_sub](#GraphNodeObject_sub) |
| unk4C | [SpawnInfo](#SpawnInfo) |

[:arrow_up_small:](#)

<br />

## [GraphNodeObject_sub](#GraphNodeObject_sub)

| Field | Type |
| ----- | ---- |
| animAccel | integer |
| animFrame | integer |
| animFrameAccelAssist | integer |
| animID | integer |
| animTimer | integer |
| animYTrans | integer |
| curAnim | [Animation](#Animation) |
| prevAnimFrame | integer |
| prevAnimFrameTimestamp | integer |
| prevAnimID | integer |
| prevAnimPtr | [Animation](#Animation) |

[:arrow_up_small:](#)

<br />

## [HandheldShakePoint](#HandheldShakePoint)

| Field | Type |
| ----- | ---- |
| index | integer |
| pad | integer |
| point | [Vec3s](#Vec3s) |

[:arrow_up_small:](#)

<br />

## [InstantWarp](#InstantWarp)

| Field | Type |
| ----- | ---- |
| area | integer |
| displacement | [Vec3s](#Vec3s) |
| id | integer |

[:arrow_up_small:](#)

<br />

## [LakituState](#LakituState)

| Field | Type |
| ----- | ---- |
| curFocus | [Vec3f](#Vec3f) |
| curPos | [Vec3f](#Vec3f) |
| defMode | integer |
| focHSpeed | number |
| focVSpeed | number |
| focus | [Vec3f](#Vec3f) |
| focusDistance | number |
| goalFocus | [Vec3f](#Vec3f) |
| goalPos | [Vec3f](#Vec3f) |
| keyDanceRoll | integer |
| lastFrameAction | integer |
| mode | integer |
| nextYaw | integer |
| oldPitch | integer |
| oldRoll | integer |
| oldYaw | integer |
| pos | [Vec3f](#Vec3f) |
| posHSpeed | number |
| posVSpeed | number |
| roll | integer |
| shakeMagnitude | [Vec3s](#Vec3s) |
| shakePitchDecay | integer |
| shakePitchPhase | integer |
| shakePitchVel | integer |
| shakeRollDecay | integer |
| shakeRollPhase | integer |
| shakeRollVel | integer |
| shakeYawDecay | integer |
| shakeYawPhase | integer |
| shakeYawVel | integer |
| skipCameraInterpolationTimestamp | integer |
| unused | integer |
| unusedVec1 | [Vec3f](#Vec3f) |
| unusedVec2 | [Vec3s](#Vec3s) |
| yaw | integer |

[:arrow_up_small:](#)

<br />

## [LinearTransitionPoint](#LinearTransitionPoint)

| Field | Type |
| ----- | ---- |
| dist | number |
| focus | [Vec3f](#Vec3f) |
| pitch | integer |
| pos | [Vec3f](#Vec3f) |
| yaw | integer |

[:arrow_up_small:](#)

<br />

## [MarioAnimation](#MarioAnimation)

| Field | Type |
| ----- | ---- |
| targetAnim | [Animation](#Animation) |

[:arrow_up_small:](#)

<br />

## [MarioBodyState](#MarioBodyState)

| Field | Type |
| ----- | ---- |
| action | integer |
| capState | integer |
| eyeState | integer |
| grabPos | integer |
| handState | integer |
| headAngle | [Vec3s](#Vec3s) |
| heldObjLastPosition | [Vec3f](#Vec3f) |
| modelState | integer |
| punchState | integer |
| torsoAngle | [Vec3s](#Vec3s) |
| torsoPos | [Vec3f](#Vec3f) |
| wingFlutter | integer |

[:arrow_up_small:](#)

<br />

## [MarioState](#MarioState)

| Field | Type |
| ----- | ---- |
| action | integer |
| actionArg | integer |
| actionState | integer |
| actionTimer | integer |
| angleVel | [Vec3s](#Vec3s) |
| animation | [MarioAnimation](#MarioAnimation) |
| area | [Area](#Area) |
| bubbleObj | [Object](#Object) |
| capTimer | integer |
| ceil | [Surface](#Surface) |
| ceilHeight | number |
| character | [Character](#Character) |
| collidedObjInteractTypes | integer |
| controller | [Controller](#Controller) |
| curAnimOffset | number |
| currentRoom | integer |
| doubleJumpTimer | integer |
| faceAngle | [Vec3s](#Vec3s) |
| fadeWarpOpacity | integer |
| flags | integer |
| floor | [Surface](#Surface) |
| floorAngle | integer |
| floorHeight | number |
| forwardVel | number |
| framesSinceA | integer |
| framesSinceB | integer |
| freeze | integer |
| healCounter | integer |
| health | integer |
| heldByObj | [Object](#Object) |
| heldObj | [Object](#Object) |
| hurtCounter | integer |
| input | integer |
| intendedMag | number |
| intendedYaw | integer |
| interactObj | [Object](#Object) |
| invincTimer | integer |
| isSnoring | integer |
| marioBodyState | [MarioBodyState](#MarioBodyState) |
| marioObj | [Object](#Object) |
| minimumBoneY | number |
| nonInstantWarpPos | [Vec3f](#Vec3f) |
| numCoins | integer |
| numKeys | integer |
| numLives | integer |
| numStars | integer |
| particleFlags | integer |
| peakHeight | number |
| playerIndex | integer |
| pos | [Vec3f](#Vec3f) |
| prevAction | integer |
| prevNumStarsForDialog | integer |
| quicksandDepth | number |
| riddenObj | [Object](#Object) |
| slideVelX | number |
| slideVelZ | number |
| slideYaw | integer |
| spawnInfo | [SpawnInfo](#SpawnInfo) |
| splineKeyframeFraction | number |
| splineState | integer |
| squishTimer | integer |
| statusForCamera | [PlayerCameraState](#PlayerCameraState) |
| terrainSoundAddend | integer |
| twirlYaw | integer |
| unkB0 | integer |
| unkC4 | number |
| usedObj | [Object](#Object) |
| vel | [Vec3f](#Vec3f) |
| wall | [Surface](#Surface) |
| wallKickTimer | integer |
| wasNetworkVisible | integer |
| waterLevel | integer |

[:arrow_up_small:](#)

<br />

## [ModeTransitionInfo](#ModeTransitionInfo)

| Field | Type |
| ----- | ---- |
| frame | integer |
| lastMode | integer |
| max | integer |
| newMode | integer |
| transitionEnd | [LinearTransitionPoint](#LinearTransitionPoint) |
| transitionStart | [LinearTransitionPoint](#LinearTransitionPoint) |

[:arrow_up_small:](#)

<br />

## [NetworkPlayer](#NetworkPlayer)

| Field | Type |
| ----- | ---- |
| connected | bool |
| currActNum | integer |
| currAreaIndex | integer |
| currAreaSyncValid | bool |
| currCourseNum | integer |
| currLevelAreaSeqId | integer |
| currLevelNum | integer |
| currLevelSyncValid | bool |
| fadeOpacity | integer |
| globalIndex | integer |
| lastReceived | number |
| lastSent | number |
| localIndex | integer |
| modelIndex | integer |
| name | string |
| onRxSeqId | integer |
| paletteIndex | integer |
| type | integer |

[:arrow_up_small:](#)

<br />

## [Object](#Object)

| Field | Type |
| ----- | ---- |
| activeFlags | integer |
| areaTimer | integer |
| areaTimerDuration | integer |
| areaTimerType | integer |
| bhvDelayTimer | integer |
| bhvStackIndex | integer |
| collidedObjInteractTypes | integer |
| createdThroughNetwork | integer |
| globalPlayerIndex | integer |
| header | [ObjectNode](#ObjectNode) |
| heldByPlayerIndex | integer |
| hitboxDownOffset | number |
| hitboxHeight | number |
| hitboxRadius | number |
| hurtboxHeight | number |
| hurtboxRadius | number |
| numCollidedObjs | integer |
| parentObj | [Object](#Object) |
| platform | [Object](#Object) |
| prevObj | [Object](#Object) |
| respawnInfoType | integer |
| unused1 | integer |

[:arrow_up_small:](#)

<br />

## [ObjectHitbox](#ObjectHitbox)

| Field | Type |
| ----- | ---- |
| damageOrCoinValue | integer |
| downOffset | integer |
| health | integer |
| height | integer |
| hurtboxHeight | integer |
| hurtboxRadius | integer |
| interactType | integer |
| numLootCoins | integer |
| radius | integer |

[:arrow_up_small:](#)

<br />

## [ObjectNode](#ObjectNode)

| Field | Type |
| ----- | ---- |
| gfx | [GraphNodeObject](#GraphNodeObject) |
| next | [ObjectNode](#ObjectNode) |
| prev | [ObjectNode](#ObjectNode) |

[:arrow_up_small:](#)

<br />

## [ObjectWarpNode](#ObjectWarpNode)

| Field | Type |
| ----- | ---- |
| next | [ObjectWarpNode](#ObjectWarpNode) |
| node | [WarpNode](#WarpNode) |
| object | [Object](#Object) |

[:arrow_up_small:](#)

<br />

## [OffsetSizePair](#OffsetSizePair)

| Field | Type |
| ----- | ---- |
| offset | integer |
| size | integer |

[:arrow_up_small:](#)

<br />

## [ParallelTrackingPoint](#ParallelTrackingPoint)

| Field | Type |
| ----- | ---- |
| distThresh | number |
| pos | [Vec3f](#Vec3f) |
| startOfPath | integer |
| zoom | number |

[:arrow_up_small:](#)

<br />

## [PlayerCameraState](#PlayerCameraState)

| Field | Type |
| ----- | ---- |
| action | integer |
| cameraEvent | integer |
| faceAngle | [Vec3s](#Vec3s) |
| headRotation | [Vec3s](#Vec3s) |
| pos | [Vec3f](#Vec3f) |
| unused | integer |
| usedObj | [Object](#Object) |

[:arrow_up_small:](#)

<br />

## [PlayerGeometry](#PlayerGeometry)

| Field | Type |
| ----- | ---- |
| currCeil | [Surface](#Surface) |
| currCeilHeight | number |
| currCeilType | integer |
| currFloor | [Surface](#Surface) |
| currFloorHeight | number |
| currFloorType | integer |
| prevCeil | [Surface](#Surface) |
| prevCeilHeight | number |
| prevCeilType | integer |
| prevFloor | [Surface](#Surface) |
| prevFloorHeight | number |
| prevFloorType | integer |
| waterHeight | number |

[:arrow_up_small:](#)

<br />

## [SpawnInfo](#SpawnInfo)

| Field | Type |
| ----- | ---- |
| activeAreaIndex | integer |
| areaIndex | integer |
| behaviorArg | integer |
| next | [SpawnInfo](#SpawnInfo) |
| startAngle | [Vec3s](#Vec3s) |
| startPos | [Vec3s](#Vec3s) |
| unk18 | [GraphNode](#GraphNode) |

[:arrow_up_small:](#)

<br />

## [Surface](#Surface)

| Field | Type |
| ----- | ---- |
| flags | integer |
| force | integer |
| lowerY | integer |
| modifiedTimestamp | integer |
| normal | [Vec3f](#Vec3f) |
| object | [Object](#Object) |
| originOffset | number |
| prevVertex1 | [Vec3s](#Vec3s) |
| prevVertex2 | [Vec3s](#Vec3s) |
| prevVertex3 | [Vec3s](#Vec3s) |
| room | integer |
| type | integer |
| upperY | integer |
| vertex1 | [Vec3s](#Vec3s) |
| vertex2 | [Vec3s](#Vec3s) |
| vertex3 | [Vec3s](#Vec3s) |

[:arrow_up_small:](#)

<br />

## [TransitionInfo](#TransitionInfo)

| Field | Type |
| ----- | ---- |
| focDist | number |
| focPitch | integer |
| focYaw | integer |
| framesLeft | integer |
| marioPos | [Vec3f](#Vec3f) |
| pad | integer |
| posDist | number |
| posPitch | integer |
| posYaw | integer |

[:arrow_up_small:](#)

<br />

## [Vec3f](#Vec3f)

| Field | Type |
| ----- | ---- |
| x | float |
| y | float |
| z | float |

[:arrow_up_small:](#)

<br />

## [Vec3s](#Vec3s)

| Field | Type |
| ----- | ---- |
| x | integer |
| y | integer |
| z | integer |

[:arrow_up_small:](#)

<br />

## [WallCollisionData](#WallCollisionData)

| Field | Type |
| ----- | ---- |
| numWalls | integer |
| offsetY | number |
| radius | number |
| unk14 | integer |

[:arrow_up_small:](#)

<br />

## [WarpNode](#WarpNode)

| Field | Type |
| ----- | ---- |
| destArea | integer |
| destLevel | integer |
| destNode | integer |
| id | integer |

[:arrow_up_small:](#)

<br />

## [WarpTransition](#WarpTransition)

| Field | Type |
| ----- | ---- |
| data | [WarpTransitionData](#WarpTransitionData) |
| isActive | integer |
| pauseRendering | integer |
| time | integer |
| type | integer |

[:arrow_up_small:](#)

<br />

## [WarpTransitionData](#WarpTransitionData)

| Field | Type |
| ----- | ---- |
| blue | integer |
| endTexRadius | integer |
| endTexX | integer |
| endTexY | integer |
| green | integer |
| red | integer |
| startTexRadius | integer |
| startTexX | integer |
| startTexY | integer |
| texTimer | integer |

[:arrow_up_small:](#)

<br />

## [Waypoint](#Waypoint)

| Field | Type |
| ----- | ---- |
| flags | integer |
| pos | [Vec3s](#Vec3s) |

[:arrow_up_small:](#)

<br />

## [Whirlpool](#Whirlpool)

| Field | Type |
| ----- | ---- |
| pos | [Vec3s](#Vec3s) |
| strength | integer |

[:arrow_up_small:](#)

<br />

