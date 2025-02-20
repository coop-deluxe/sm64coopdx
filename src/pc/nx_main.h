#ifdef __SWITCH__

#ifndef _NX_MAIN_H
#define _NX_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pc/game_main.h"

#include "gfx/gfx_pc.h"
#include "gfx/gfx_opengl.h"
#include "gfx/gfx_sdl.h"

#define WAPI gfx_sdl

#define RAPI gfx_opengl_api
#define RAPI_NAME "OpenGL"

extern struct AudioAPI *audio_api;
extern struct GfxWindowManagerAPI *wm_api;

#ifdef __cplusplus
}
#endif

#endif // _NX_MAIN_H

#endif // __SWITCH__