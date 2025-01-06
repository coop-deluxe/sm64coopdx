## [:rewind: Lua Reference](lua.md)

# Globals
Globals are variables that are always exposed to the Lua API.

<br />

## [gMarioStates](#gMarioStates)
The `gMarioStates[]` table is an array from `0` to `(MAX_PLAYERS - 1)` that contains a [MarioState](structs.md#MarioState) struct for each possible player.

It is indexed by the local `playerIndex`, so `gMarioStates[0]` is always the local player.

[:arrow_up_small:](#)

<br />

## [gNetworkPlayers](#gNetworkPlayers)
The `gNetworkPlayers[]` table is an array from `0` to `(MAX_PLAYERS - 1)` that contains a [NetworkPlayer](structs.md#NetworkPlayer) struct for each possible player.

It is indexed by the local `playerIndex`, so `gNetworkPlayers[0]` is always the local player.

[:arrow_up_small:](#)

<br />

## [gActiveMods](#gNetworkPlayers)
The `gActiveMods[]` table is an array that starts at `0`, and contains a [Mod](structs.md#Mod) struct for each active mod.

[:arrow_up_small:](#)

<br />

## [gCharacters](#gCharacter)
The `gCharacters[]` table is an array from `0` to `(CT_MAX - 1)` that contains a [Character](structs.md#Character) struct for each possible character.

[:arrow_up_small:](#)

<br />

## [gControllers](#gControllers)
The `gControllers[]` table is an array from `0` to `(MAX_PLAYERS - 1)` that contains a [Controller](structs.md#Controller) struct for each possible player.

[:arrow_up_small:](#)

<br />

## [gMatStack](#gMatStack)
The `gMatStack[]` table is an array from `0` to `(MATRIX_STACK_SIZE - 1)` that contains `Mat4`s used by geo process.

[:arrow_up_small:](#)

<br />

## [gMatStackPrev](#gMatStackPrev)
The `gMatStackPrev[]` table is similar to [gMatStack](#gMatStack) for interpolation.

[:arrow_up_small:](#)

<br />

## [gTextures](#gTextures)
The `gTextures` table contains references to textures. Listed in [GlobalTextures](structs.md#GlobalTextures).

[:arrow_up_small:](#)

<br />

## [gObjectAnimations](#gObjectAnimations)
The `gObjectAnimations` table contains references to object animations. Listed in [GlobalObjectAnimations](structs.md#GlobalObjectAnimations).

[:arrow_up_small:](#)

<br />

## [gGlobalObjectCollisionData](#gGlobalObjectCollisionData)
The `gGlobalObjectCollisionData` table contains references to object collision data. Listed in [GlobalObjectCollisionData](structs.md#GlobalObjectCollisionData).

[:arrow_up_small:](#)

<br />

## [gLakituState](#gLakituState)
`gLakituState`'s fields are listed in [LakituState](structs.md#LakituState).

[:arrow_up_small:](#)

<br />

## [gServerSettings](#gServerSettings)
`gServerSettings`'s fields are listed in [ServerSettings](structs.md#ServerSettings).

__**NOTE**__: The fields in this struct do not sync well and changing them outside of init in if statements or functions can cause desyncs. Make sure the field gets changed on every player's end if you change it after init.

[:arrow_up_small:](#)

## [gNametagsSettings](#gNametagsSettings)
`gNametagsSettings`'s fields are listed in [NametagsSettings](structs.md#NametagsSettings).

__**NOTE**__: The fields in this struct are not synced and are meant to be changed from Lua. If you want a change to sync for everyone, call it during init outside of any if statements and functions or make sure the field gets changed on every player's end.

[:arrow_up_small:](#)

<br />

## [gLevelValues](#gLevelValues)
`gLevelValues`'s fields are listed in [LevelValues](structs.md#LevelValues).

[:arrow_up_small:](#)

<br />

## [gBehaviorValues](#gBehaviorValues)
`gBehaviorValues`'s fields are listed in [BehaviorValues](structs.md#BehaviorValues).

[:arrow_up_small:](#)

<br />

## [gPaintingValues](#gPaintingValues)
`gPaintingValues`'s fields are listed in [PaintingValues](structs.md#PaintingValues).

[:arrow_up_small:](#)

<br />

## [gFirstPersonCamera](#gFirstPersonCamera)
`gFirstPersonCamera`'s fields are listed in [FirstPersonCamera](structs.md#FirstPersonCamera).

__**NOTE**__: `gFirstPersonCamera.enabled` returns whether or not first person is enabled at all. `get_first_person_enabled()` also accounts for certain conditions that make the camera exit first person mode and will return `false` if so.

[:arrow_up_small:](#)

<br />

## [gGlobalSyncTable](#gGlobalSyncTable)
The `gGlobalSyncTable` is a table used for networking. Any field set inside of this table is automatically synchronized with all other clients. Do not use this table for player-specific variables, keep those in [gPlayerSyncTable](#gPlayerSyncTable). Player-specific variable will desynchronize within this table since it doesn't automatically translate `playerIndex`.

[:arrow_up_small:](#)

<br />

## [gPlayerSyncTable](#gPlayerSyncTable)
The `gPlayerSyncTable[]` is an array from 0 to `(MAX_PLAYERS - 1)` that is used for networking. Any field set inside of this table is automatically synchronized with all other clients.

It is indexed by the local `playerIndex`, so `gPlayerSyncTable[0]` is always for the local player.

The underlying networking system will automatically translate the local `playerIndex` so that the field is set for the correct player.

[:arrow_up_small:](#)
