#ifndef CONTROLLER_SDL_H
#define CONTROLLER_SDL_H

#include "controller_api.h"

#define VK_BASE_SDL_GAMEPAD 0x1000

// mouse buttons are also in the controller namespace, just offset 0x100
#define VK_OFS_SDL_MOUSE 0x0100
#define VK_BASE_SDL_MOUSE (VK_BASE_SDL_GAMEPAD + VK_OFS_SDL_MOUSE)

extern struct ControllerAPI controller_sdl;

#endif
