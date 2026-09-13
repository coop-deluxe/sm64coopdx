#ifndef _PC_MAIN_H
#define _PC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gfx/gfx_pc.h"

#include "gfx/gfx_opengl.h"
#include "gfx/gfx_direct3d11.h"

#include "gfx/gfx_window_opengl.h"
#include "gfx/gfx_window_dxgi.h"
#include "gfx/gfx_dummy.h"

#include "audio/audio_api.h"
#include "audio/audio_sdl.h"
#include "audio/audio_null.h"

#ifdef GIT_HASH
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s, [%s]", WINDOW_NAME, get_version(), GIT_HASH); title; })
#else
#define TITLE ({ char title[96] = ""; snprintf(title, 96, "%s %s", WINDOW_NAME, get_version()); title; })
#endif

#define MAX_LOADING_MESSAGE 256

#define AT_STARTUP __attribute__((constructor))

extern struct AudioAPI* gAudioApi;
extern struct GfxRenderingAPI* gRenderApi;

extern char gLoadingMessage[MAX_LOADING_MESSAGE];
extern f32 gLoadingPercent;

extern bool gGameInited;
extern bool gModsInited;
extern bool gDynosPacksInited;
extern bool gGfxInited;

extern f32 gMasterVolume;

extern u8 gLuaVolumeMaster;
extern u8 gLuaVolumeLevel;
extern u8 gLuaVolumeSfx;
extern u8 gLuaVolumeEnv;

void set_loading_message(const char *format, ...);
void set_loading_percentage(f32 percent);
void produce_one_dummy_frame(void (*callback)(), u8 clearColorR, u8 clearColorG, u8 clearColorB);
void game_deinit(void);
void game_exit(void);

#ifdef __cplusplus
}
#endif

#endif // _PC_MAIN_H
