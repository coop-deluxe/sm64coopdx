# Lua Reference

The Lua scripting API is in early development.

Expect many more things to be supported in the future.

<br />

## How to install Lua mods
Lua scripts you make can be placed either the `mods` folder in the base directory, or in `<SAVE FILE LOCATION>/mods`

Save file locations:
- Windows: `%appdata%/sm64ex-coop`
- Linux: `~/.local/share/sm64ex-coop`
- MacOS: `~/Library/Application Support/sm64ex-coop`

<br />

## Tips
- When developing Lua mods, run the game from a console. Lua errors and logs will appear there, but only if the game is launched with the `--console` launch parameter.
- When a function requests a time parameter, it is almost if not always in frames.
- You can use the `print()` command when debugging. Your logs will show up in the console.
- You can create a folder within the mods folder containing multiple lua scripts as long as one script is called `main.lua`. Dynos actors can be placed inside this mod folder under `<your mod folder>/actors/`.
<br />

## Sections
- [Globals](globals.md)
- [Constants](constants.md)
- [Functions](functions.md)
- [Structs](structs.md)

### Guides
- [Setting up Visual Studio Code](guides/vs-code-setup.md) 
- [Hooks](guides/hooks.md)
- [gMarioStates](guides/mario-state.md)
- [Behavior Object Lists](guides/object-lists.md)

## Important notes on player indices

Something important to realize is that the `localIndex` for each player is different (unfortunately).

So the order of `gMarioStates[]`, `gNetworkPlayers[]`, and `gPlayerSyncTable[]` is different for each player.

Luckily `gPlayerSyncTable[]` will automatically translate the player indices, so setting `gPlayerSyncTable[0].example = 1` will set it for the correct player for everyone.

The `globalIndex` of each player is consistent among everyone connected. So if you absolutely need to sort things in order you will have to grab it from `gNetworkPlayers[<LOCAL INDEX HERE>].globalIndex`.

All of this is a holdover from when there were only two players. It was a reasonable idea back then.

<br />

## Example Lua mods (small)
- [Low Gravity](examples/low-gravity.lua)
- [Faster Swimming](../../mods/faster-swimming.lua)
- [Mario Run](examples/Mario-Run.lua)
- [HUD Rendering](examples/hud.lua)
- [Object Spawning](examples/spawn-stuff.lua)
- [Custom Ball Behavior](examples/behavior-ball.lua)
- [Replace Goomba Behavior](examples/behavior-replace-goomba.lua)
- [Add to Goomba Behavior](examples/behavior-add-to-goomba.lua)
- [Behavior with Surface Collisions](examples/behavior-surface-collisions.lua)
- [Custom Surface Collisions](examples/big-paddle)
- [Custom Box Model](examples/custom-box-model)
- [Custom Player Model](examples/koopa-player-model)
- [Moonjump](examples/Moonjump.lua)
- [Instant Clip](examples/instant-clip.lua)
- [Water Height Changer](examples/water-level.lua)
- [Custom Level](examples/custom-level)
- [Custom HUD Texture](examples/custom-hud-texture)
- [Custom Audio Test](examples/audio-test)
- [Custom Texture Overriding](examples/texture-override)

## Example Lua mods (large)
- [Hide and Seek Gamemode](../../mods/hide-and-seek.lua)
