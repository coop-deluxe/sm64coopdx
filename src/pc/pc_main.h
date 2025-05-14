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

extern struct GfxWindowManagerAPI gfx_dxgi;
extern struct GfxWindowManagerAPI gfx_sdl;
extern struct GfxWindowManagerAPI gfx_dummy_wm_api;

extern struct GfxRenderingAPI gfx_opengl_api;
extern struct GfxRenderingAPI gfx_direct3d11_api;
extern struct GfxRenderingAPI gfx_dummy_renderer_api;

extern struct GfxWindowManagerAPI* gWindowApi;
extern struct GfxRenderingAPI* gRenderApi;
extern const char* renderApiName;

#ifdef GIT_HASH
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s, [%s]", WINDOW_NAME, get_version(), GIT_HASH); title; })
#else
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s", WINDOW_NAME, get_version()); title; })
#endif

#define AT_STARTUP __attribute__((constructor))

extern bool gGameInited;
extern bool gGfxInited;

extern f32 gMasterVolume;

extern u8 gLuaVolumeMaster;
extern u8 gLuaVolumeLevel;
extern u8 gLuaVolumeSfx;
extern u8 gLuaVolumeEnv;

void produce_one_dummy_frame(void (*callback)(), u8 clearColorR, u8 clearColorG, u8 clearColorB);
void game_deinit(void);
void game_exit(void);

#ifdef __cplusplus
}
#endif

#endif // _PC_MAIN_H
