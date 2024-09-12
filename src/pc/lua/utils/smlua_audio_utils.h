#ifndef SMLUA_AUDIO_UTILS_H
#define SMLUA_AUDIO_UTILS_H

#include "pc/utils/miniaudio.h"

void smlua_audio_utils_reset_all(void);
bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData);
void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name);

  ////////////////
 // mod sounds //
////////////////

struct ModAudioSampleCopies {
    ma_sound sound;
    ma_decoder decoder;
    struct ModAudioSampleCopies *next;
    struct ModAudioSampleCopies *prev;
    struct ModAudio *parent;
};

struct ModAudio {
    struct ModFile* file;
    ma_sound sound;
    ma_decoder decoder;
    void *buffer;
    u32 bufferSize;
    struct ModAudioSampleCopies* sampleCopiesTail;
    bool isStream;
    f32 baseVolume;
    bool loaded;
};

struct ModAudio* audio_stream_load(const char* filename);
void audio_stream_destroy(struct ModAudio* audio);
void audio_stream_play(struct ModAudio* audio, bool restart, f32 volume);
void audio_stream_pause(struct ModAudio* audio);
void audio_stream_stop(struct ModAudio* audio);
f32 audio_stream_get_position(struct ModAudio* audio);
void audio_stream_set_position(struct ModAudio* audio, f32 pos);
bool audio_stream_get_looping(struct ModAudio* audio);
void audio_stream_set_looping(struct ModAudio* audio, bool looping);
f32 audio_stream_get_frequency(struct ModAudio* audio);
void audio_stream_set_frequency(struct ModAudio* audio, f32 freq);
f32 audio_stream_get_volume(struct ModAudio* audio);
void audio_stream_set_volume(struct ModAudio* audio, f32 volume);

void audio_sample_destroy_pending_copies(void);
struct ModAudio* audio_sample_load(const char* filename);
void audio_sample_destroy(struct ModAudio* audio);
void audio_sample_stop(struct ModAudio* audio);
void audio_sample_play(struct ModAudio* audio, Vec3f position, f32 volume);

void audio_custom_update_volume(void);

void audio_custom_shutdown(void);

void smlua_audio_custom_deinit(void);

#endif
