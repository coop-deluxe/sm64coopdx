#ifndef AUDIO_API_H
#define AUDIO_API_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef void (*AudioCaptureCallback)(const uint8_t* input, uint32_t num_bytes);

struct AudioAPI {
    bool (*init)(const char* speaker, const char* microphone);
    int (*buffered)(void);
    int (*get_desired_buffered)(void);
    void (*play)(const uint8_t *buf, size_t len);
    void (*record_start)();
    void (*record_callback)(AudioCaptureCallback callback);
    void (*record_stop)();
    char** (*get_speakers)(int* count, unsigned int* current);
    char** (*get_microphones)(int* count, unsigned int* current);
    const char* (*active_speaker)(void);
    const char* (*active_microphone)(void);
    bool (*reopen_speaker)(const char* name);
    bool (*reopen_microphone)(const char* name);
    void (*shutdown)(void);
};

#endif
