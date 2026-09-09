#include "audio_api.h"
#include "macros.h"

static bool audio_null_init(UNUSED const char* speaker, UNUSED const char* microphone) {
    return true;
}

static int audio_null_buffered(void) {
    return 0;
}

static int audio_null_get_desired_buffered(void) {
    return 0;
}

static void audio_null_play(UNUSED const uint8_t *buf, UNUSED size_t len) {
}

static void audio_null_record_start(void) {
}

static void audio_null_record_callback(UNUSED AudioCaptureCallback callback) {
}

static void audio_null_record_stop(void) {
}

static char** audio_null_get_speakers(int* count, UNUSED unsigned int* current) {
    if (count) *count = 0;
    return NULL;
}

static char** audio_null_get_microphones(int* count, UNUSED unsigned int* current) {
    if (count) *count = 0;
    return NULL;
}

static const char* audio_null_active_speaker(void) {
    return "";
}

static const char* audio_null_active_microphone(void) {
    return "";
}

static bool audio_null_reopen_speaker(UNUSED const char* name) {
    return true;
}

static bool audio_null_reopen_microphone(UNUSED const char* name) {
    return true;
}

static void audio_null_shutdown(void) {
}

struct AudioAPI audio_null = {
    audio_null_init,
    audio_null_buffered,
    audio_null_get_desired_buffered,
    audio_null_play,
    audio_null_record_start,
    audio_null_record_callback,
    audio_null_record_stop,
    audio_null_get_speakers,
    audio_null_get_microphones,
    audio_null_active_speaker,
    audio_null_active_microphone,
    audio_null_reopen_speaker,
    audio_null_reopen_microphone,
    audio_null_shutdown
};