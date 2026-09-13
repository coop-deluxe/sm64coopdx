#include <stdio.h>
#include <SDL3/SDL.h>

#include "audio_api.h"

static SDL_AudioDeviceID sDevice = 0;
static SDL_AudioStream *sStream = NULL;

static bool audio_sdl_init(void) {
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        fprintf(stderr, "SDL_InitSubSystem error: %s\n", SDL_GetError());
        return false;
    }

    const SDL_AudioSpec spec = { SDL_AUDIO_S16, 2, 32000 };

    sDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    if (sDevice == 0) {
        fprintf(stderr, "SDL_OpenAudioDevice error: %s\n", SDL_GetError());
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    sStream = SDL_CreateAudioStream(&spec, &spec);
    if (sStream == NULL) {
        fprintf(stderr, "SDL_CreateAudioStream error: %s\n", SDL_GetError());
        SDL_CloseAudioDevice(sDevice);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    if (!SDL_BindAudioStream(sDevice, sStream)) {
        fprintf(stderr, "SDL_BindAudioStream error: %s\n", SDL_GetError());
        SDL_DestroyAudioStream(sStream);
        SDL_CloseAudioDevice(sDevice);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    SDL_ResumeAudioDevice(sDevice);
    return true;
}

static int audio_sdl_buffered(void) {
    return SDL_GetAudioStreamQueued(sStream) / 4;
}

static int audio_sdl_get_desired_buffered(void) {
    return 1100;
}

static void audio_sdl_play(const uint8_t *buf, size_t len) {
    SDL_PutAudioStreamData(sStream, buf, len);
}

static void audio_sdl_shutdown(void) {
    if (SDL_WasInit(SDL_INIT_AUDIO)) {
        if (sDevice != 0) {
            SDL_PauseAudioDevice(sDevice);
        }
        if (sStream != NULL) {
            SDL_ClearAudioStream(sStream);
            SDL_DestroyAudioStream(sStream);
        }
        if (sDevice != 0) {
            SDL_CloseAudioDevice(sDevice);
            sDevice = 0;
        }
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}

struct AudioAPI audio_sdl = {
    audio_sdl_init,
    audio_sdl_buffered,
    audio_sdl_get_desired_buffered,
    audio_sdl_play,
    audio_sdl_shutdown
};
