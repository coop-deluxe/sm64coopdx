#include <stdio.h>

#include <SDL2/SDL.h>

#include "audio_api.h"

#include "pc/proximity_chat.h"

static SDL_AudioDeviceID dev;
static SDL_AudioDeviceID capture_dev;
static AudioCaptureCallback capture_callback;

enum {
    AudioDevType_Speakers,
    AudioDevType_Microphone
};

static void audio_sdl_capture_callback(void* userdata, uint8_t* bytes, int32_t num_bytes) {
    (void)userdata;
    if (capture_callback) capture_callback(bytes, num_bytes);
}

static bool audio_sdl_init(void) {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return false;
    }

    dev = SDL_OpenAudioDevice(NULL, AudioDevType_Speakers, &(SDL_AudioSpec){
        .freq = 32000,
        .format = AUDIO_S16SYS,
        .channels = 2,
        .samples = 640
    }, NULL, 0);
    if (dev == 0) {
        fprintf(stderr, "SDL_OpenAudio playback error: %s\n", SDL_GetError());
        return false;
    }

    capture_dev = SDL_OpenAudioDevice(NULL, AudioDevType_Microphone, &(SDL_AudioSpec){
        .freq = 48000,
        .format = AUDIO_S16SYS,
        .channels = 1,
        .samples = 960,
        .callback = audio_sdl_capture_callback
    }, NULL, 0);
    if (capture_dev == 0) {
        proxchat_error[0] = PROXCHAT_ERR_NO_MICROPHONE;
        fprintf(stderr, "SDL_OpenAudio capture error: %s\n", SDL_GetError());
        return false;
    }

    SDL_PauseAudioDevice(dev, 0);
    return true;
}

static int audio_sdl_buffered(void) {
    return SDL_GetQueuedAudioSize(dev) / 4;
}

static int audio_sdl_get_desired_buffered(void) {
    return 1100;
}

static void audio_sdl_play(const uint8_t *buf, size_t len) {
    if (audio_sdl_buffered() < 6000) {
        // Don't fill the audio buffer too much in case this happens
        SDL_QueueAudio(dev, buf, len);
    }
}

static void audio_sdl_record_start() {
    SDL_PauseAudioDevice(capture_dev, 0);
}

static void audio_sdl_record_callback(AudioCaptureCallback callback) {
    capture_callback = callback;
}

static void audio_sdl_record_stop() {
    SDL_PauseAudioDevice(capture_dev, 1);
}

static void audio_sdl_shutdown(void)
{
    if (SDL_WasInit(SDL_INIT_AUDIO)) {
        if (dev != 0) {
            SDL_CloseAudioDevice(dev);
            dev = 0;
        }
        if (capture_dev != 0) {
            SDL_CloseAudioDevice(capture_dev);
            capture_dev = 0;
        }
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}

struct AudioAPI audio_sdl = {
    audio_sdl_init,
    audio_sdl_buffered,
    audio_sdl_get_desired_buffered,
    audio_sdl_play,
    audio_sdl_record_start,
    audio_sdl_record_callback,
    audio_sdl_record_stop,
    audio_sdl_shutdown
};
