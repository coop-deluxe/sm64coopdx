#ifndef GFX_SDL_H
#define GFX_SDL_H

#include "gfx_window_manager_api.h"

extern struct GfxWindowManagerAPI gfx_sdl;

bool gfx_sdl_check_opengl_compatibility(void);

#endif
