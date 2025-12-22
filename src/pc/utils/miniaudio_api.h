#ifndef miniaudio_api_h
#define miniaudio_api_h

#ifdef __SWITCH__
#define MA_NO_RUNTIME_LINKING 1
#define MA_DEBUG_OUTPUT 1
#endif

#include "pc/utils/miniaudio.h"

// Optimization: disable spatialization for everything as it's not used
#define MA_SOUND_STREAM_FLAGS (MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_STREAM)
#define MA_SOUND_SAMPLE_FLAGS (MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_DECODE) // No pitch, pre-decode audio samples

ma_result ma_initalize(const ma_engine_config *pConfig, ma_engine *pEngine);
ma_result ma_uninitalize(ma_engine *pEngine);

ma_result ma_sound_from_buffer(ma_engine *engine, ma_sound *sound, ma_decoder *decoder, void *buffer, u32 size, bool stream);

#endif // miniaudio_api_h