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

## [gCharacter](#gCharacter)
The `gCharacter[]` table is an array from `0` to `(CT_MAX - 1)` that contains a [Character](structs.md#Character) struct for each possible character.

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
