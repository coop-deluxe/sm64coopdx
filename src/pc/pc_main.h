#ifndef _PC_MAIN_H
#define _PC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gfx/gfx_pc.h"

#include "gfx/gfx_opengl.h"
#include "gfx/gfx_direct3d11.h"

#include "gfx/gfx_dxgi.h"
#include "gfx/gfx_sdl.h"
#include "gfx/gfx_dummy.h"

#if defined(WAPI_SDL1) || defined(WAPI_SDL2)
# define WAPI gfx_sdl
#elif defined(WAPI_DXGI)
# define WAPI gfx_dxgi
#elif defined(WAPI_DUMMY)
# define WAPI gfx_dummy_wm_api
#else
# error No window API!
#endif

#if defined(RAPI_D3D11)
# define RAPI gfx_direct3d11_api
# define RAPI_NAME "DirectX 11"
#elif defined(RAPI_GL) || defined(RAPI_GL_LEGACY)
# define RAPI gfx_opengl_api
# ifdef USE_GLES
#  define RAPI_NAME "OpenGL ES"
# else
#  define RAPI_NAME "OpenGL"
# endif
#elif defined(RAPI_DUMMY)
# define RAPI gfx_dummy_renderer_api
# define RAPI_NAME "Dummy"
#else
# error No rendering API!
#endif

// For IDEs with syntax highlighting
#ifndef WAPI
#define WAPI gfx_dummy_wm_api
#endif
#ifndef RAPI
#define RAPI gfx_dummy_renderer_api
#endif

#ifndef RAPI_NAME
#define RAPI_NAME "Dummy"
#endif

#ifdef GIT_HASH
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s, [%s]", WINDOW_NAME, get_version(), GIT_HASH); title; })
#else
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s", WINDOW_NAME, get_version()); title; })
#endif

#define AT_STARTUP __attribute__((constructor))

extern bool gGameInited;
extern bool gGfxInited;

extern u8 gLuaVolumeMaster;
extern u8 gLuaVolumeLevel;
extern u8 gLuaVolumeSfx;
extern u8 gLuaVolumeEnv;

extern struct GfxWindowManagerAPI* wm_api;
void produce_one_dummy_frame(void (*callback)(), u8 clearColorR, u8 clearColorG, u8 clearColorB);
void game_deinit(void);
void game_exit(void);

#ifdef __cplusplus
}
#endif

#endif // _PC_MAIN_H
