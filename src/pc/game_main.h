#ifndef _GAME_MAIN_H
#define _GAME_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sm64.h"
#include "audio/audio_api.h"
#include "gfx/gfx_dummy.h"

#define AT_STARTUP __attribute__((constructor))

extern bool gGameInited;
extern bool gGfxInited;

extern f32 gMasterVolume;

extern u8 gLuaVolumeMaster;
extern u8 gLuaVolumeLevel;
extern u8 gLuaVolumeSfx;
extern u8 gLuaVolumeEnv;

void buffer_audio(void);

void produce_one_frame(void);
void produce_one_dummy_frame(void (*callback)(), u8 clearColorR, u8 clearColorG, u8 clearColorB);

void game_deinit(void);
void game_exit(void);
void *main_game_init(UNUSED void *dummy);

extern struct AudioAPI *audio_api;
extern struct GfxWindowManagerAPI *wm_api;

#ifdef __cplusplus
}
#endif

#endif // _GAME_MAIN_H