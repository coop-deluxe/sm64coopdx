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

| Field | Type | Access |
| ----- | ---- | ------ |
| flags | integer |  |
| length | integer |  |
| animYTransDivisor | integer |  |
| startFrame | integer |  |
| loopStart | integer |  |
| loopEnd | integer |  |
| unusedBoneCount | integer |  |

[:arrow_up_small:](#)

<br />

## [Area](#Area)

| Field | Type | Access |
| ----- | ---- | ------ |
| camera | [Camera](#Camera) | read-only |
| flags | integer |  |
| index | integer |  |
| instantWarps | [InstantWarp](#InstantWarp) | read-only |
| musicParam | integer |  |
| musicParam2 | integer |  |
| objectSpawnInfos | [SpawnInfo](#SpawnInfo) | read-only |
| paintingWarpNodes | [WarpNode](#WarpNode) | read-only |
| terrainType | integer |  |
| warpNodes | [ObjectWarpNode](#ObjectWarpNode) | read-only |

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

## [GraphNode](#GraphNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| children | [GraphNode](#GraphNode) | read-only |
| flags | integer |  |
| next | [GraphNode](#GraphNode) | read-only |
| parent | [GraphNode](#GraphNode) | read-only |
| prev | [GraphNode](#GraphNode) | read-only |
| type | integer |  |

[:arrow_up_small:](#)

<br />

## [GraphNodeObject](#GraphNodeObject)

| Field | Type | Access |
| ----- | ---- | ------ |
| angle | [Vec3s](#Vec3s) | read-only |
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
| sharedChild | [GraphNode](#GraphNode) | read-only |
| skipInterpolationTimestamp | integer |  |
| unk18 | integer |  |
| unk19 | integer |  |
| animInfo | [GraphNodeObject_sub](#GraphNodeObject_sub) | read-only |
| unk4C | [SpawnInfo](#SpawnInfo) | read-only |

[:arrow_up_small:](#)

<br />

## [GraphNodeObject_sub](#GraphNodeObject_sub)

| Field | Type | Access |
| ----- | ---- | ------ |
| animAccel | integer |  |
| animFrame | integer |  |
| animFrameAccelAssist | integer |  |
| animID | integer |  |
| animTimer | integer |  |
| animYTrans | integer |  |
| curAnim | [Animation](#Animation) | read-only |
| prevAnimFrame | integer |  |
| prevAnimFrameTimestamp | integer |  |
| prevAnimID | integer |  |
| prevAnimPtr | [Animation](#Animation) | read-only |

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
| targetAnim | [Animation](#Animation) | read-only |

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
| animation | [MarioAnimation](#MarioAnimation) | read-only |
| area | [Area](#Area) | read-only |
| bubbleObj | [Object](#Object) | read-only |
| capTimer | integer |  |
| ceil | [Surface](#Surface) | read-only |
| ceilHeight | number |  |
| character | [Character](#Character) | read-only |
| collidedObjInteractTypes | integer |  |
| controller | [Controller](#Controller) | read-only |
| curAnimOffset | number |  |
| currentRoom | integer |  |
| doubleJumpTimer | integer |  |
| faceAngle | [Vec3s](#Vec3s) | read-only |
| fadeWarpOpacity | integer |  |
| flags | integer |  |
| floor | [Surface](#Surface) | read-only |
| floorAngle | integer |  |
| floorHeight | number |  |
| forwardVel | number |  |
| framesSinceA | integer |  |
| framesSinceB | integer |  |
| freeze | integer |  |
| healCounter | integer |  |
| health | integer |  |
| heldByObj | [Object](#Object) | read-only |
| heldObj | [Object](#Object) | read-only |
| hurtCounter | integer |  |
| input | integer |  |
| intendedMag | number |  |
| intendedYaw | integer |  |
| interactObj | [Object](#Object) | read-only |
| invincTimer | integer |  |
| isSnoring | integer |  |
| marioBodyState | [MarioBodyState](#MarioBodyState) | read-only |
| marioObj | [Object](#Object) | read-only |
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
| riddenObj | [Object](#Object) | read-only |
| slideVelX | number |  |
| slideVelZ | number |  |
| slideYaw | integer |  |
| spawnInfo | [SpawnInfo](#SpawnInfo) | read-only |
| splineKeyframeFraction | number |  |
| splineState | integer |  |
| squishTimer | integer |  |
| statusForCamera | [PlayerCameraState](#PlayerCameraState) | read-only |
| terrainSoundAddend | integer |  |
| twirlYaw | integer |  |
| unkB0 | integer |  |
| unkC4 | number |  |
| usedObj | [Object](#Object) | read-only |
| vel | [Vec3f](#Vec3f) | read-only |
| wall | [Surface](#Surface) | read-only |
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
| bhvDelayTimer | integer |  |
| bhvStackIndex | integer |  |
| collidedObjInteractTypes | integer |  |
| createdThroughNetwork | integer |  |
| globalPlayerIndex | integer |  |
| header | [ObjectNode](#ObjectNode) | read-only |
| heldByPlayerIndex | integer |  |
| hitboxDownOffset | number |  |
| hitboxHeight | number |  |
| hitboxRadius | number |  |
| hurtboxHeight | number |  |
| hurtboxRadius | number |  |
| numCollidedObjs | integer |  |
| parentObj | [Object](#Object) | read-only |
| platform | [Object](#Object) | read-only |
| prevObj | [Object](#Object) | read-only |
| respawnInfoType | integer |  |
| unused1 | integer |  |

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
| next | [ObjectNode](#ObjectNode) | read-only |
| prev | [ObjectNode](#ObjectNode) | read-only |

[:arrow_up_small:](#)

<br />

## [ObjectWarpNode](#ObjectWarpNode)

| Field | Type | Access |
| ----- | ---- | ------ |
| next | [ObjectWarpNode](#ObjectWarpNode) | read-only |
| node | [WarpNode](#WarpNode) | read-only |
| object | [Object](#Object) | read-only |

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
| usedObj | [Object](#Object) | read-only |

[:arrow_up_small:](#)

<br />

## [PlayerGeometry](#PlayerGeometry)

| Field | Type | Access |
| ----- | ---- | ------ |
| currCeil | [Surface](#Surface) | read-only |
| currCeilHeight | number |  |
| currCeilType | integer |  |
| currFloor | [Surface](#Surface) | read-only |
| currFloorHeight | number |  |
| currFloorType | integer |  |
| prevCeil | [Surface](#Surface) | read-only |
| prevCeilHeight | number |  |
| prevCeilType | integer |  |
| prevFloor | [Surface](#Surface) | read-only |
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
| next | [SpawnInfo](#SpawnInfo) | read-only |
| startAngle | [Vec3s](#Vec3s) | read-only |
| startPos | [Vec3s](#Vec3s) | read-only |
| unk18 | [GraphNode](#GraphNode) | read-only |

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
| object | [Object](#Object) | read-only |
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

