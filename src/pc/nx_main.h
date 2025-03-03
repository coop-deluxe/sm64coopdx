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
#ifndef WAPI_SDL2
#define WAPI_SDL2
#endif

#define RAPI gfx_opengl_api
#define RAPI_NAME "OpenGL ES"

extern struct AudioAPI *audio_api;
extern struct GfxWindowManagerAPI *wm_api;

void nx_init(void);
void nx_cleanup(void);

#ifdef GIT_HASH
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s, [%s]", WINDOW_NAME, get_version(), GIT_HASH); title; })
#else
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s", WINDOW_NAME, get_version()); title; })
#endif

#ifdef __cplusplus
}
#endif

#endif // _NX_MAIN_H

#endif // __SWITCH__