# Lua Reference

The Lua scripting API is in early development.

Expect many more things to be supported in the future.

<br />

## How to install Lua mods
Lua scripts you make can be placed either the `mods` folder in the base directory, or in `<SAVE FILE LOCATION>/mods`

<br />

## Tips
- When developing Lua mods, run the game from a console. Lua errors and logs will appear there.
- You can use the `print()` command when debugging. Your logs will show up in the console.

<br />

## Sections
- [Globals](globals.md)
- [Hooks](hooks.md)
- [Constants](constants.md)
- [Functions](functions.md)
- [Structs](structs.md)

<br />

## Important notes on player indices

Something important to realize is that the `localIndex` for each player is different (unfortunately).

So the order of `gMarioStates[]`, `gNetworkPlayers[]`, and `gPlayerSyncTable[]` is different for each player.

Luckily `gPlayerSyncTable[]` will automatically translate the player indices, so setting `gPlayerSyncTable[0].example = 1` will set it for the correct player for everyone.

The `globalIndex` of each player is consistent among everyone connected. So if you absolutely need to sort things in order you will have to grab it from `gNetworkPlayers[<LOCAL INDEX HERE>].globalIndex`.

All of this is a holdover from when there were only two players. It was a reasonable idea back then.

<br />

## Example Lua mods
- [Extended Moveset](../../mods/extended-moveset.lua)
- [Character Movesets](../../mods/character-movesets.lua)
- [Low Gravity](../../mods/low-gravity.lua)
- [Faster Swimming](../../mods/faster-swimming.lua)
- [Hide and Seek](../../mods/hide-and-seek.lua)
- [HUD Rendering](examples/hud.lua)
- [Object Spawning](examples/spawn-stuff.lua)
- [Custom Ball Behavior](examples/behavior-ball.lua)
- [Replace Goomba Behavior](examples/behavior-replace-goomba.lua)
- [Add to Goomba Behavior](examples/behavior-add-to-goomba.lua)
