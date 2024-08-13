# sm64coopdx_rt64
Fork of [coop-deluxe/sm64coopdx](https://github.com/coop-deluxe/sm64coopdx) that adds support for raytracing/RTX using [RT64](https://github.com/DarioSamo/sm64rt-legacy-renderer), a hardware-accelerated real-time path tracer.

## Building
For building instructions, please refer to the [sm64ex wiki](https://github.com/sm64pc/sm64ex/wiki) and follow the process as normal with these additional build flags:
* RENDER_API=RT64 (Required to use RT64 as the renderer)

## More Infos
- https://github.com/DarioSamo/sm64rt
- https://github.com/Render96/Render96ex/tree/tester_rt64alpha


![sm64coopdx Logo](textures/segment2/custom_coopdx_logo.rgba32.png)

sm64coopdx is an online multiplayer project for the Super Mario 64 PC port that synchronizes all entities and every level for multiple players. The project was started by the Coop Deluxe Team. The purpose is to actively maintain and improve, but also continue sm64ex-coop, created by djoslin0. More features, customization, and power to the Lua API allow modders and players to enjoy Super Mario 64 more than ever!

Feel free to report bugs or contribute to the project. 

## Initial Goal (Accomplished)
Create a mod for the PC port where multiple people can play together online.

Unlike previous multiplayer projects, this one synchronizes enemies and events. This allows players to interact with the same world at the same time.

Interestingly enough though, the goal of the project has slowly evolved over time from simply just making a Super Mario 64 multiplayer mod to constantly maintaining and improving the project (notably the Lua API.)

## Lua
sm64coopdx is moddable via Lua, similar to Roblox and Garry's Mod's Lua APIs. To get started, click [here](docs/lua/lua.md) to see the Lua documentation.
