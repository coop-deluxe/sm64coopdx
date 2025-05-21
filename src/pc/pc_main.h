#ifndef __CONSOLE__

#ifndef _PC_MAIN_H
#define _PC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pc/game_main.h"

#include "gfx/gfx_pc.h"

#include "gfx/gfx_opengl.h"
#include "gfx/gfx_direct3d11.h"

#include "gfx/gfx_dxgi.h"
#include "gfx/gfx_sdl.h"
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

#ifdef __cplusplus
}
#endif

#endif // _PC_MAIN_H

#endif // __CONSOLE__