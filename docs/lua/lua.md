# Lua Reference

The Lua scripting API is in early development.

Expect many more things to be supported in the future.

<br />

## How to install Lua mods
Lua scripts you make can be placed either the `mods` folder in the base directory, or in `<SAVE FILE LOCATION>/mods`

<br />

## Globals
| Identifier | Type | Description |
| :--------  | :--: | :---------: |
| gMarioStates[MAX_PLAYERS] | [MarioState](structs.md#MarioState) | An array of length MAX_PLAYERS containing mario states |
| gCharacter[CT_MAX] | [Character](structs.md#Character) | An array of length CT_MAX containing character information |

<br />

## Exposed from SM64
- [Constants](constants.md)
- [Functions](functions.md)
- [Structs](structs.md)

<br />

## Example Lua mods
- [Extended Moveset](../../mods/extended-moveset.lua)
- [Character Movesets](../../mods/character-movesets.lua)
- [Low Gravity](../../mods/low-gravity.lua)
- [Faster Swimming](../../mods/faster-swimming.lua)
