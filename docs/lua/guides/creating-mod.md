## [:rewind: Lua Reference](../lua.md)

# Creating a Mod

## Section 1: Navigating to the mods folder

To start, open up sm64coopdx, and navigate to Options -> Misc -> Open User/Appdata Folder.

<img width="300" height="383" alt="Screenshot 2026-07-23 at 1 19 35 PM" src="https://github.com/user-attachments/assets/65086b81-e040-43ee-9e32-2c44d720b663"/>
<img width="300" height="383" alt="Screenshot 2026-07-23 at 1 22 34 PM" src="https://github.com/user-attachments/assets/bea3c1b2-0ff8-4e2e-953f-bbe91135ad39"/>
<img width="300" height="383" alt="Screenshot 2026-07-23 at 1 22 37 PM" src="https://github.com/user-attachments/assets/3e496e88-2635-4d9d-a44c-26c51b373481"/>


Now, in your file browser, open up the `mods` folder. If the `mods` folder does not exist, create it.

<img width="327" height="104" alt="SCR-20260623-susk-2" src="https://github.com/user-attachments/assets/ebd211e6-7398-43ec-9b38-0f465dcaaa48" />

You can move on to the next section with this done.

## Section 2: Picking a file mod or a folder mod

A file mod is a mod that is a single code file. This should be used for very simple mods, for instance, let's say you want to make a mod that makes Mario die on an A button press, that should be a file mod due to the simple nature of it.

A folder mod is a mod that allows for multiple code files, actors, textures, levels, and more. If your mod is anywhere from medium-sized to large, you'll want a folder mod. It allows for greater organization, usage of assets, and a generally more expandable system.

If you are just starting out, I'd recommend learning to create a folder mod first so you won't be limited in the future.

## Section 3a: Creating a file mod

First, you need to create a `.lua` file. This is a code file where your code will go. Creating this file will differ depending on your platform. On macOS there is no easy way to do this, please consult the internet (it really does suck). On Windows, simply right click, hit New, and hit Text Document, then make the extension `.lua` and make the file name the name of the mod all lowercased with `-` as space.

<img width="613" height="349" alt="Screenshot 2026-06-23 223738" src="https://github.com/user-attachments/assets/f128b1af-5abf-4214-b29e-0f9b437af64d" />

Linux will vary depending on your file explorer, but if you're on Linux you should already know how to. In the worst-case scenario, open up your terminal and navigate to `~/.local/share/sm64coopdx/mods` and create the file with `touch modname.lua`.

## Section 3b: Creating a folder mod

Create a folder and give it your mods name all lowercased with `-` as space. Next up, create a file and name it `main.lua`. This is a requirement. Folder mods require a `main.lua` file or else sm64coopdx will not know what file to load into.

## Section 4: Configuring the mod

Before continuing, if you haven't, I would highly advise reading up on the [Visual Studio Code setup guide](vs-code-setup.md) as it will provide autocomplete and docs when writing mods.

For a file mod, simply open up the file in Visual Studio Code. For a folder mod, you can open the project in Visual Studio Code by dragging your folder into the app. Then open up `main.lua`.

There are a few fields that exist for mods. Fields can be set at the very top of a file with comments and a newline for each option. Here is a list of options, as well as an example on what multiple options look like:

| Category | Notes |
| -------- | ----- |
| `name` | The name of the mod. This name is the name used in game |
| `description` | A description of the mod. Appears when hovering over a mod to turn it on/off |
| `incompatible` | A list of tags to be marked as incompatible. This is an opt-in system. If 2 mods contain an equivalent incompatible tag, then they both won't be able to be enabled together. Tags are separated with a space character, or a whitespace. |
| `category` | The category of a mod. Leaving this empty will have the mod be in the `misc` category. The list of categories can be found in game by going to Host, Mods, then looping through the Categories select box. Note that categories are all lowercase, they are also only in English. So for category Utility, you want to put in your mod `-- category: utility` |
| `pausable` | A boolean of whether or not to allow the game to be frozen when paused in singleplayer. By default this is true, so by default you can pause in singleplayer and become frozen. To make this not the case, use `-- pausable: false`. |
| `ignore-script-warnings` | A boolean of whether or not to ignore script warnings. Don't touch this for your mods, but for documentation sake, this will suppress warnings that your script may have. This does not suppress errors, it only suppresses warnings, which are quite rare. |

An example of some of these would be:

```lua
-- name: Screaming Toad
-- description: Makes toad scream on demand!\n\n Hit X to make toad scream!\n\n Bonus Feature!!! Hit Y to make toad do something CRAZY
-- incompatible: gamemode
-- category: qol
```

When you've configured the mod the way you like, you are ready to go! Open up the game, select the mod, and you should see your mod appear!

You can read up on more documentation. Go back to the [main page](../lua.md) and go through some of the guides if you are just getting started. A good first place to look is the [hooks documentation](hooks.md). Happy modding!
