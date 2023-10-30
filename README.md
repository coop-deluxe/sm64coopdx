# sm64coopdx
Online multiplayer mod for SM64 that synchronizes all entities and every level for multiple players. Fork of [sm64ex-coop](https://github.com/djoslin0/sm64ex-coop). 

Feel free to report bugs and contribute, but remember, there must be **no upload of any copyrighted asset**. 
Run `./extract_assets.py --clean && make clean` or `make distclean` to clear ROM assets, however this is unnecessary for contributing because the .gitignore file already excludes ROM assets.

## How to Play

[Instructions on how to play are available on the wiki.](https://github.com/coop-deluxe/sm64coopdx/wiki/How-to-Play)

- The easiest way is to download [coop-compiler](https://github.com/coop-compiler/coop-compiler/releases/latest/download/coop-compiler.exe)

## Goal (accomplished)
Create a mod for the PC port where multiple people can play together online.

Unlike previous multiplayer projects, this one synchronizes enemies and events. This allows players interact with the same world at the same time.

## Lua
sm64coopdx is moddable via Lua, similar to Roblox and Garry's Mod's Lua APIs. To get started, click [here](docs/lua/lua.md) to see the Lua documentation.
