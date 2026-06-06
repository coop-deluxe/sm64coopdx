#include <stdio.h>

#include <SDL2/SDL.h>

#include "audio_api.h"

#include "pc/voice_chat.h"

static AudioCaptureCallback sCaptureCallback;
static SDL_AudioDeviceID sSpeakerDev, sMicrophoneDev;
static char *sActiveSpeaker, *sActiveMicrophone;
static bool sCurrentlyCapturing;

enum {
    AudioDevType_Speakers,
    AudioDevType_Microphone
};

static void audio_sdl_capture_callback(UNUSED void* userdata, uint8_t* bytes, int32_t num_bytes) {
    if (sCaptureCallback) sCaptureCallback(bytes, num_bytes);
}

static SDL_AudioSpec sSpeakerSpec = {
    .freq = 32000,
    .format = AUDIO_S16SYS,
    .channels = 2,
    .samples = 640
}, sMicrophoneSpec = {
    .freq = 48000,
    .format = AUDIO_S16SYS,
    .channels = 1,
    .samples = 960,
    .callback = audio_sdl_capture_callback
};

static const char* audio_sdl_find_device(const char* name, int type) {
    if (!name) return NULL;

    int count = SDL_GetNumAudioDevices(type);
    bool found = false;
    for (int i = 0; i < count && !found; i++) {
        if (strcmp(name, SDL_GetAudioDeviceName(i, type)) == 0)
            found = true;
    }

    if (!found) name = NULL; // reset to system default
    return name;
}

static char* audio_sdl_update_name(char* current, const char* name, int type) {
    if (current) free(current);
    if (name) current = strdup(name);
    else {
        char* default_name = NULL;
        // for some reason SDL doesnt allow the audio spec to be null, so were using a dummy
        SDL_GetDefaultAudioInfo(&default_name, &(SDL_AudioSpec){}, type);
        current = strdup(default_name);
        SDL_free(default_name);
    }
    return current;
}

static bool audio_sdl_reopen_speaker(const char* name) {
    name = audio_sdl_find_device(name, AudioDevType_Speakers);

    if (sSpeakerDev != 0) SDL_CloseAudioDevice(sSpeakerDev);
    sSpeakerDev = SDL_OpenAudioDevice(name, AudioDevType_Speakers, &sSpeakerSpec, NULL, 0);
    if (sSpeakerDev == 0) {
        fprintf(stderr, "SDL_OpenAudio playback error: %s\n", SDL_GetError());
        return false;
    }
    sActiveSpeaker = audio_sdl_update_name(sActiveSpeaker, name, AudioDevType_Speakers);
    SDL_PauseAudioDevice(sSpeakerDev, 0);
    return true;
}

static bool audio_sdl_reopen_microphone(const char* name) {
    name = audio_sdl_find_device(name, AudioDevType_Microphone);

    if (sMicrophoneDev != 0) SDL_CloseAudioDevice(sMicrophoneDev);
    sMicrophoneDev = SDL_OpenAudioDevice(name, AudioDevType_Microphone, &sMicrophoneSpec, NULL, 0);
    if (sMicrophoneDev == 0) {
        gVoicePlayer->error = VOICECHAT_ERR_NO_MICROPHONE;
        fprintf(stderr, "SDL_OpenAudio capture error: %s\n", SDL_GetError());
        return false;
    }
    sActiveMicrophone = audio_sdl_update_name(sActiveMicrophone, name, AudioDevType_Microphone);
    if (sCurrentlyCapturing) SDL_PauseAudioDevice(sMicrophoneDev, 0);
    return true;
}

static bool audio_sdl_init(const char* speaker, const char* microphone) {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return false;
    }

    // dont fallback to audio_null on fail
    // perhaps the user needs to choose a different device
    audio_sdl_reopen_speaker(speaker);
    audio_sdl_reopen_microphone(microphone);
    
    return true;
}

static int audio_sdl_buffered(void) {
    if (sSpeakerDev == 0) return 0;
    return SDL_GetQueuedAudioSize(sSpeakerDev) / 4;
}

static int audio_sdl_get_desired_buffered(void) {
    if (sSpeakerDev == 0) return 0;
    return 1100;
}

static void audio_sdl_play(const uint8_t *buf, size_t len) {
    if (sSpeakerDev == 0) return;
    if (audio_sdl_buffered() < 6000) {
        // Don't fill the audio buffer too much in case this happens
        SDL_QueueAudio(sSpeakerDev, buf, len);
    }
}

static void audio_sdl_record_start() {
    if (sMicrophoneDev == 0) return;
    sCurrentlyCapturing = true;
    SDL_PauseAudioDevice(sMicrophoneDev, 0);
}

static void audio_sdl_record_callback(AudioCaptureCallback callback) {
    sCaptureCallback = callback;
}

static void audio_sdl_record_stop() {
    if (sMicrophoneDev == 0) return;
    sCurrentlyCapturing = false;
    SDL_PauseAudioDevice(sMicrophoneDev, 1);
}

static char** audio_sdl_list_devices(int* count, unsigned int* current, int type) {
    int num = SDL_GetNumAudioDevices(type);
    if (count) *count = num;

    char** strings = malloc(num * sizeof(const char*));
    for (int i = 0; i < num; i++) {
        strings[i] = strdup(SDL_GetAudioDeviceName(i, type));
        if (strcmp(strings[i], type == AudioDevType_Microphone ? sActiveMicrophone : sActiveSpeaker) == 0)
            if (current) *current = i;
    }
    return strings;
}

static char** audio_sdl_get_speakers(int* count, unsigned int* current) {
    return audio_sdl_list_devices(count, current, AudioDevType_Speakers);
}

static char** audio_sdl_get_microphones(int* count, unsigned int* current) {
    return audio_sdl_list_devices(count, current, AudioDevType_Microphone);
}

static const char* audio_sdl_active_speaker(void) {
    return sActiveSpeaker;
}

static const char* audio_sdl_active_microphone(void) {
    return sActiveMicrophone;
}

static void audio_sdl_shutdown(void)
{
    if (SDL_WasInit(SDL_INIT_AUDIO)) {
        if (sSpeakerDev != 0) {
            SDL_CloseAudioDevice(sSpeakerDev);
            sSpeakerDev = 0;
        }
        if (sMicrophoneDev != 0) {
            SDL_CloseAudioDevice(sMicrophoneDev);
            sMicrophoneDev = 0;
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
    audio_sdl_get_speakers,
    audio_sdl_get_microphones,
    audio_sdl_active_speaker,
    audio_sdl_active_microphone,
    audio_sdl_reopen_speaker,
    audio_sdl_reopen_microphone,
    audio_sdl_shutdown
};
