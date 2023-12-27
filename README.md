# sm64coopdx
Online multiplayer mod for the SM64 PC port that synchronizes all entities and every level for multiple players. Fork of [sm64ex-coop](https://github.com/djoslin0/sm64ex-coop). 

Feel free to report bugs and contribute, but remember, there must be **no upload of any copyrighted asset**. 
Run `./extract_assets.py --clean && make clean` or `make distclean` to clear ROM assets, however this is unnecessary for contributing because the .gitignore file already excludes ROM assets.

## How to Play

The easiest way to play is by using [coopdx-patcher](https://github.com/coop-deluxe/coopdx-patcher/releases/latest/download/coopdx-patcher.exe). Simply drag and drop your ROM into the program or run `coopdx-patcher "your_rom_name.z64"`.

However, if you need to, you can compile yourself by following the [sm64ex-coop tutorial](https://github.com/djoslin0/sm64ex-coop/wiki/How-to-Play) and replacing the sm64ex-coop links with the sm64coopdx repository.

## Goal (accomplished)
Create a mod for the PC port where multiple people can play together online.

Unlike previous multiplayer projects, this one synchronizes enemies and events. This allows players interact with the same world at the same time.

## Lua
sm64coopdx is moddable via Lua, similar to Roblox and Garry's Mod's Lua APIs. To get started, click [here](docs/lua/lua.md) to see the Lua documentation.
