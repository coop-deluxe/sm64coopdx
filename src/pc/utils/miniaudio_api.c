#define MINIAUDIO_IMPLEMENTATION // required by miniaudio
#define MA_NO_SDL // We don't use this because it conflicts with audio_sdl2.

#include "types.h"
#include "pc/utils/miniaudio_api.h"
#include "pc/utils/miniaudio_nx.inl"
#include "pc/utils/miniaudio_sdl2.inl"

typedef struct {
    union {
        ma_context context;
        ma_context_sdl sdl_context;
    };
} ma_context_ex;

typedef struct {
  union {
      ma_device device;
      ma_device_sdl sdl_device;
  };
} ma_device_ex;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    if (pDevice->type == ma_device_type_playback)  {
        ma_waveform_read_pcm_frames((ma_waveform*)pDevice->pUserData, pOutput, frameCount, NULL);
    }

    if (pDevice->type == ma_device_type_duplex) {
        ma_copy_pcm_frames(pOutput, pInput, frameCount, pDevice->playback.format, pDevice->playback.channels);
    }
}

/*
This is our custom backend "loader". All this does is attempts to initialize our custom backends in the order they are listed. The first
one to successfully initialize is the one that's chosen. In this example we're just listing them statically, but you can use whatever logic
you want to handle backend selection.

This is used as the onContextInit() callback in the context config.
*/
static ma_result ma_context_init__custom_loader(ma_context *pContext, const ma_context_config *pConfig, ma_backend_callbacks *pCallbacks) {
    ma_result result = MA_NO_BACKEND;

    /* Silence some unused parameter warnings just in case no custom backends are enabled. */
    (void)pContext;
    (void)pCallbacks;
    
    /* NX. */
#if !defined(MA_NO_NX)
    if (result != MA_SUCCESS) {
        result = ma_context_init__nx(pContext, pConfig, pCallbacks);
    }
#endif

    /* SDL. */
#if !defined(MA_NO_SDL)
    if (result != MA_SUCCESS) {
        result = ma_context_init__sdl(pContext, pConfig, pCallbacks);
    }
#endif

    /* If we have a success result we have initialized a backend. Otherwise we need to tell miniaudio about the error so it can skip over our custom backends. */
    return result;
}

ma_context_ex global_context = { 0 };
ma_backend global_backends[] = {
    ma_backend_wasapi,
    ma_backend_dsound,
    ma_backend_winmm,
    ma_backend_coreaudio,
    ma_backend_sndio,
    ma_backend_audio4,
    ma_backend_oss,
    ma_backend_pulseaudio,
    ma_backend_alsa,
    ma_backend_jack,
    ma_backend_aaudio,
    ma_backend_opensl,
    ma_backend_webaudio,
    ma_backend_custom,
    ma_backend_null
};

ma_result ma_initalize(const ma_engine_config *pConfig, ma_engine *pEngine) {
    ma_result result = MA_SUCCESS;
    ma_engine_config engineConfig;

    /* The config is allowed to be NULL in which case we use defaults for everything. */
    if (pConfig != NULL) {
        engineConfig = *pConfig;
    } else {
        engineConfig = ma_engine_config_init();
    }
    engineConfig.pContext = (ma_context *)&global_context;
    
    ma_context_config contextConfig = ma_context_config_init();
    contextConfig.custom.onContextInit = ma_context_init__custom_loader;
    
    result = ma_context_init(global_backends, sizeof(global_backends) / sizeof(global_backends[0]), &contextConfig, (ma_context *)&global_context);
    if (result != MA_SUCCESS) { return result; }
    
    result = ma_engine_init(&engineConfig, pEngine);
    return result;
}

ma_result ma_uninitalize(ma_engine *pEngine) {
    ma_engine_uninit(pEngine);
    ma_context_uninit((ma_context *)&global_context);
}

ma_result ma_sound_from_buffer(ma_engine *engine, ma_sound *sound, ma_decoder *decoder, void *buffer, u32 size, bool stream) {
    // Decode the audio buffer.
    ma_result result = ma_decoder_init_memory(buffer, size, NULL, decoder);
    if (result != MA_SUCCESS) { return result; }
    
    result = ma_sound_init_from_data_source(engine, decoder, stream ? MA_SOUND_STREAM_FLAGS : MA_SOUND_SAMPLE_FLAGS, NULL, sound);
    return result;
}