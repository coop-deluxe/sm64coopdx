# Mod Manifest

A mod manifest is a json file containing configuration options for a mod. It serves as a replacement for the standard fields typically found at the top of `main.lua` (e.g. `-- name: Hello World!`).

To use a mod manifest, in the root of the mod create a `manifest.json` file. It must be named this or else the manifest will not be found.

## Configuration Options

| Key | Type | Notes |
| --- | ---- | ----- |
| `name` | `string` | The name of the mod shown in-game |
| `id` | `string` | A unique identifier for the mod. Useful if other mods need to find/communicate with your mod |
| `entryFile` | `string` | The Lua file to load as the mod entry point, relative to the mod root. If omitted, `main.lua` is used. If used, only that file is loaded, all other files must be loaded with `require` |
| `description` | `string` | The description of the mod shown in-game |
| `incompatible` | `string` or `string[]` | A list of tags to be marked as incompatible. This is an opt-in system. If 2 mods contain an equivalent incompatible tag, then they both won't be able to be enabled together. If you are using a single string, tags are separated with a space character, or a whitespace, if you are using an array, each element is a separate tag. |
| `category` | `string` | The category of a mod. Leaving this empty will have the mod be in the `misc` category. The list of categories can be found in game by going to Host, Mods, then looping through the Categories select box. Note that categories are all lowercase, they are also only in English. So for category Utility, you want to put in your mod manifest `"category": "utility"` |
| `pausable` | `bool` | A bool of whether or not to allow the game to be frozen when paused in singleplayer. By default this is true, so by default you can pause in singleplayer and become frozen. To make this not the case, add `"pausable": false`. |
| `ignoreScriptWarnings` | `bool` | A bool of whether or not to ignore script warnings. Don't touch this for your mods, but for documentation sake, this will suppress warnings that your script may have. This does not suppress errors, it only suppresses warnings, which are quite rare. |

Here is an example configuration file:

```json
{
  "name": "Hello World",
  "id": "50fad22e-20b0-475e-b1bb-08de8943e841",
  "description": "Hope you're doing well!",
  "category": "qol",
  "incompatible": [
    "romhack",
    "gamemode"
  ],
  "pausable": false
}
```
