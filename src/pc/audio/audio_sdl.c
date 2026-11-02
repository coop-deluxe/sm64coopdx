#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#include "audio_api.h"

#include "pc/voice_chat.h"
#include "pc/djui/djui_language.h"

static AudioCaptureCallback sCaptureCallback;
static SDL_AudioDeviceID sSpeakerDev, sMicrophoneDev;
static SDL_AudioStream *sSpeakerStream, *sMicrophoneStream;
static char *sActiveSpeaker, *sActiveMicrophone;
static bool sCurrentlyCapturing;

enum {
    AudioDevType_Speakers,
    AudioDevType_Microphone
};

#define NUM_OPUS_FRAMES 960
#define NUM_OPUS_FRAMES_STRING STRING(NUM_OPUS_FRAMES)
#define STRINGG(x) #x
#define STRING(x) STRINGG(x)

static void audio_sdl_capture_callback(UNUSED void* userdata, SDL_AudioStream* stream, UNUSED int additional_amount, UNUSED int total_amount) {
    int16_t block[NUM_OPUS_FRAMES];

    while (SDL_GetAudioStreamAvailable(stream) >= (int)(sizeof(block))) {
        int got = SDL_GetAudioStreamData(stream, block, sizeof(block));
        if (got != sizeof(block)) break;
        if (sCaptureCallback) sCaptureCallback((void*)block, sizeof(block));
    }
}

static SDL_AudioSpec sSpeakerSpec = {
    .freq = 32000,
    .format = SDL_AUDIO_S16,
    .channels = 2,
}, sMicrophoneSpec = {
    .freq = 48000,
    .format = SDL_AUDIO_S16,
    .channels = 1,
};

static SDL_AudioDeviceID audio_sdl_find_device(const char* name, int type) {
    SDL_AudioDeviceID def = type == AudioDevType_Speakers ? SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK : SDL_AUDIO_DEVICE_DEFAULT_RECORDING;
    if (!name) return def;

    int count;
    SDL_AudioDeviceID* ids = (type == AudioDevType_Speakers ? SDL_GetAudioPlaybackDevices : SDL_GetAudioRecordingDevices)(&count);
    for (int i = 0; i < count; i++) {
        if (strcmp(name, SDL_GetAudioDeviceName(ids[i])) == 0)
            return ids[i];
    }

    return def;
}

static bool audio_sdl_reopen_speaker(const char* name) {
    sSpeakerDev = audio_sdl_find_device(name, AudioDevType_Speakers);

    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(sSpeakerDev, &sSpeakerSpec, NULL, NULL);
    if (!stream) {
        fprintf(stderr, "SDL_OpenAudioDeviceStream playback error: %s\n", SDL_GetError());
        return false;
    }
    if (sSpeakerStream) SDL_DestroyAudioStream(sSpeakerStream);
    sSpeakerStream = stream;

    if (sActiveSpeaker) free(sActiveSpeaker);
    sActiveSpeaker = strdup(SDL_GetAudioDeviceName(sSpeakerDev));

    SDL_ResumeAudioStreamDevice(sSpeakerStream);
    return true;
}

static bool audio_sdl_reopen_microphone(const char* name) {
    sMicrophoneDev = audio_sdl_find_device(name, AudioDevType_Microphone);

    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(sMicrophoneDev, &sMicrophoneSpec, audio_sdl_capture_callback, NULL);
    if (!stream) {
        gVoicePlayer->error = VOICECHAT_ERR_NO_MICROPHONE;
        fprintf(stderr, "SDL_OpenAudioDevice capture error: %s\n", SDL_GetError());
        return false;
    }
    if (sMicrophoneStream) SDL_DestroyAudioStream(sMicrophoneStream);
    sMicrophoneStream = stream;

    if (sActiveMicrophone) free(sActiveMicrophone);
    sActiveMicrophone = strdup(SDL_GetAudioDeviceName(sMicrophoneDev));

    if (sCurrentlyCapturing) SDL_ResumeAudioStreamDevice(sMicrophoneStream);
    return true;
}

static bool audio_sdl_init(const char* speaker, const char* microphone) {
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        fprintf(stderr, "SDL_InitSubSystem error: %s\n", SDL_GetError());
        return false;
    }

    // dont fallback to audio_null on fail
    // perhaps the user needs to choose a different device
    audio_sdl_reopen_speaker(speaker);
    audio_sdl_reopen_microphone(microphone);

    return true;
}

static int audio_sdl_buffered(void) {
    if (!sSpeakerStream) return 0;
    return SDL_GetAudioStreamQueued(sSpeakerStream) / 4;
}

static int audio_sdl_get_desired_buffered(void) {
    if (sSpeakerDev == 0) return 0;
    return 1100;
}

static void audio_sdl_play(const uint8_t *buf, size_t len) {
    if (!sSpeakerStream) return;
    SDL_PutAudioStreamData(sSpeakerStream, buf, len);
}

static void audio_sdl_record_start() {
    sCurrentlyCapturing = true;
    if (!sMicrophoneStream) return;
    SDL_ResumeAudioStreamDevice(sMicrophoneStream);
}

static void audio_sdl_record_callback(AudioCaptureCallback callback) {
    sCaptureCallback = callback;
}

static void audio_sdl_record_stop() {
    sCurrentlyCapturing = false;
    if (!sMicrophoneStream) return;
    SDL_PauseAudioStreamDevice(sMicrophoneStream);
}

static char** audio_sdl_list_devices(int* count, unsigned int* current, int type) {
    int num;
    SDL_AudioDeviceID* ids = (type == AudioDevType_Speakers ? SDL_GetAudioPlaybackDevices : SDL_GetAudioRecordingDevices)(&num);
    if (count) *count = num;
    if (current) *current = 0;

    SDL_AudioDeviceID curr_id = type == AudioDevType_Microphone ? sMicrophoneDev : sSpeakerDev;
    char** strings = malloc(num * sizeof(const char*));
    for (int i = 0; i < num; i++) {
        strings[i] = strdup(SDL_GetAudioDeviceName(ids[i]));
        if (current && curr_id == ids[i]) *current = i;
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
        if (sSpeakerStream) SDL_DestroyAudioStream(sSpeakerStream);
        if (sMicrophoneStream) SDL_DestroyAudioStream(sMicrophoneStream);
        sSpeakerStream = sMicrophoneStream = NULL;
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
