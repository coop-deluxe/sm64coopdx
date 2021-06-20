#ifndef CONTROLLER_SDL_H
#define CONTROLLER_SDL_H

#include "controller_api.h"

#define VK_BASE_SDL_GAMEPAD 0x1000

extern struct ControllerAPI controller_sdl;

void controller_sdl_read_mouse_window(void);

#endif
