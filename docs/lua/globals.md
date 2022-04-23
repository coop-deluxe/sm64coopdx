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

## [gCharacter](#gCharacter)
The `gCharacter[]` table is an array from `0` to `(CT_MAX - 1)` that contains a [Character](structs.md#Character) struct for each possible character.

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

## [gLevelValues](#gLevelValues)
`gLevelValues`'s fields are listed in [LevelValues](structs.md#LevelValues).

[:arrow_up_small:](#)

<br />

## [gBehaviorValues](#gBehaviorValues)
`gBehaviorValues`'s fields are listed in [BehaviorValues](structs.md#BehaviorValues).

[:arrow_up_small:](#)

<br />

## [gServerSettings](#gServerSettings)
`gServerSettings`'s fields are listed in [ServerSettings](structs.md#ServerSettings).

__**NOTE**__: You should only change the fields in this struct on init, and it shouldn't be done inside of if statements or functions. Failing to follow this advice can result in desyncs.

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
