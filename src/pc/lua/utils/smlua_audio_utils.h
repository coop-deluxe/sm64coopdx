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

/* |description|Loads an `audio` stream by `filename` (with extension)|descriptionEnd| */
struct ModAudio* audio_stream_load(const char* filename);
/* |description|Destroys an `audio` stream|descriptionEnd| */
void audio_stream_destroy(struct ModAudio* audio);
/* |description|Plays an `audio` stream with `volume`. `restart` sets the elapsed time back to 0.|descriptionEnd| */
void audio_stream_play(struct ModAudio* audio, bool restart, f32 volume);
/* |description|Pauses an `audio` stream|descriptionEnd| */
void audio_stream_pause(struct ModAudio* audio);
/* |description|Stops an `audio` stream|descriptionEnd| */
void audio_stream_stop(struct ModAudio* audio);
/* |description|Gets the position of an `audio` stream|descriptionEnd| */
f32 audio_stream_get_position(struct ModAudio* audio);
/* |description|Sets the position of an `audio` stream|descriptionEnd| */
void audio_stream_set_position(struct ModAudio* audio, f32 pos);
/* |description|Gets if an `audio` stream is looping or not|descriptionEnd| */
bool audio_stream_get_looping(struct ModAudio* audio);
/* |description|Sets if an `audio` stream is looping or not|descriptionEnd| */
void audio_stream_set_looping(struct ModAudio* audio, bool looping);
/* |description|Sets an `audio` stream's loop points (samples)|descriptionEnd| */
void audio_stream_set_loop_points(struct ModAudio* audio, s64 loopStart, s64 loopEnd);
/* |description|Gets the frequency of an `audio` stream|descriptionEnd| */
f32 audio_stream_get_frequency(struct ModAudio* audio);
/* |description|Sets the frequency of an `audio` stream|descriptionEnd| */
void audio_stream_set_frequency(struct ModAudio* audio, f32 freq);
/* |description|Gets the volume of an `audio` stream|descriptionEnd| */
f32 audio_stream_get_volume(struct ModAudio* audio);
/* |description|Sets the volume of an `audio` stream|descriptionEnd| */
void audio_stream_set_volume(struct ModAudio* audio, f32 volume);

void audio_sample_destroy_pending_copies(void);
/* |description|Loads an `audio` sample|descriptionEnd| */
struct ModAudio* audio_sample_load(const char* filename);
/* |description|Destroys an `audio` sample|descriptionEnd| */
void audio_sample_destroy(struct ModAudio* audio);
/* |description|Stops an `audio` sample|descriptionEnd| */
void audio_sample_stop(struct ModAudio* audio);
/* |description|Plays an `audio` sample at `position` with `volume`|descriptionEnd| */
void audio_sample_play(struct ModAudio* audio, Vec3f position, f32 volume);

void audio_custom_update_volume(void);

void audio_custom_shutdown(void);

void smlua_audio_custom_deinit(void);

#endif
