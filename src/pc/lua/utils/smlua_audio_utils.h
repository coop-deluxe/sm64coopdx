#ifndef SMLUA_AUDIO_UTILS_H
#define SMLUA_AUDIO_UTILS_H

#include "pc/lua/smlua_utils.h"

#define MA_NO_RESOURCE_MANAGER
#define MA_NO_GENERATION
#define MA_NO_ENCODING
#include "pc/utils/miniaudio.h"

/* |description|Resets all custom sequences back to vanilla|descriptionEnd| */
void smlua_audio_utils_reset_all(void);
bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData);
/* |description|Replaces the sequence corresponding to `sequenceId` with one called `m64Name`.m64 with `bankId` and `defaultVolume`|descriptionEnd| */
void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name);
/* |description|Allocates a new sequence ID|descriptionEnd| */
u8 smlua_audio_utils_allocate_sequence(void);

  ////////////////
 // mod sounds //
////////////////

// flags
// XPCCALTT
// TT - Type
// L - Loaded
// A - Alive
// CC - Channel
// P - Copy

enum ModAudioType {
    MA_TYPE_NONE,
    MA_TYPE_SAMPLE,
    MA_TYPE_STREAM
};

enum ModAudioFlags {
    MA_FLAGS_LOADED = (1 << 2),
    MA_FLAGS_COPY   = (1 << 6)
};

enum ModAudioChannel {
    MA_CHANNEL_MUSIC,
    MA_CHANNEL_SFX,
    MA_CHANNEL_ENV,
    MA_CHANNEL_MASTER
};

struct ModAudio {
    ma_sound sound;
    ma_decoder decoder;
    union {
        struct {
            u8 type    : 2;
            u8 loaded  : 1;
            u8 alive   : 1;
            u8 channel : 2;
            u8 copy    : 1;
        };
        u8 flags;
    };
    union {
        struct {
            union {
                char *filepath;
                char *relativePath; // compatibility band-aid
            };
            void *buffer;
            u32 bufferSize;
            struct ModAudio* copiesTail;
        };
        struct {
            struct ModAudio *next;
            struct ModAudio *prev;
            struct ModAudio *parent;
        };
    };

    FUNCTION(play,    audio_play);
    FUNCTION(pause,   audio_pause);
    FUNCTION(stop,    audio_stop);
    FUNCTION(destroy, audio_destroy);
    FUNCTION(reload,  audio_reload);
    FUNCTION(copy,    audio_copy);

    PROPERTY(volume,     audio_get_volume,         audio_set_volume);
    PROPERTY(pan,        audio_get_pan,            audio_set_pan);
    PROPERTY(length,     audio_get_length,         NULL);
    PROPERTY(position,   audio_get_position,       audio_set_position);
    PROPERTY(frequency,  audio_get_frequency,      audio_set_frequency);
    PROPERTY(looping,    audio_get_looping,        audio_set_looping);
    PROPERTY(playing,    audio_get_playing,        audio_set_playing);
    PROPERTY(channel,    audio_get_volume_channel, audio_set_volume_channel);
    PROPERTY(sampleRate, audio_get_sample_rate,    NULL);

    PROPERTY(file, return_self, NULL); // compatibility band-aid
};

/* |description|Loads an `audio` by `filename` (with extension)|descriptionEnd| */
struct ModAudio* audio_load(const char* filename, OPTIONAL enum ModAudioType type);

/* |description|Plays an `audio` stream with `volume`. `restart` sets the elapsed time back to 0.|descriptionEnd| */
OVERLOAD(audio_play) void audio_stream_play(struct ModAudio* audio, bool restart, f32 volume);
/* |description|Plays an `audio` sample at `position` with `volume`|descriptionEnd| */
OVERLOAD(audio_play) struct ModAudio* audio_sample_play(struct ModAudio* audio, Vec3f position, f32 volume);

/* |description|Plays an `audio`|descriptionEnd| */
OVERLOAD(audio_play) void audio_play(struct ModAudio* audio);
/* |description|Pauses an `audio`|descriptionEnd| */
void audio_pause(struct ModAudio* audio);
/* |description|Stops an `audio`|descriptionEnd| */
void audio_stop(struct ModAudio* audio);
/* |description|Destroys an `audio`|descriptionEnd| */
void audio_destroy(struct ModAudio* audio);
/* |description|Reloads a destroyed `audio`|descriptionEnd| */
void audio_reload(struct ModAudio* audio);
/* |description|Copies an `audio`|descriptionEnd| */
struct ModAudio* audio_copy(struct ModAudio* audio);

/* |description|Gets the volume of an `audio`|descriptionEnd| */
f32 audio_get_volume(struct ModAudio* audio);
/* |description|Sets the volume of an `audio`|descriptionEnd| */
void audio_set_volume(struct ModAudio* audio, f32 volume);
/* |description|Gets the pan of an `audio`|descriptionEnd| */
f32 audio_get_pan(struct ModAudio* audio);
/* |description|Sets the pan of an `audio`|descriptionEnd| */
void audio_set_pan(struct ModAudio* audio, f32 pan);
/* |description|Gets the length of an `audio` in seconds|descriptionEnd| */
void audio_get_length(struct ModAudio* audio, RET f32 *length);
/* |description|Gets the position of an `audio` in seconds|descriptionEnd| */
void audio_get_position(struct ModAudio* audio, RET f32 *position);
/* |description|Sets the position of an `audio` in seconds|descriptionEnd| */
void audio_set_position(struct ModAudio* audio, f32 pos);
/* |description|Gets if an `audio` is looping or not|descriptionEnd| */
bool audio_get_looping(struct ModAudio* audio);
/* |description|Sets if an `audio` is looping or not|descriptionEnd| */
void audio_set_looping(struct ModAudio* audio, bool looping);
/* |description|Gets if an `audio` is playing|descriptionEnd| */
bool audio_get_playing(struct ModAudio* audio);
/* |description|Sets if an `audio` is playing|descriptionEnd| */
void audio_set_playing(struct ModAudio* audio, bool playing);
/* |description|Gets an `audio`'s loop points in samples|descriptionEnd| */
void audio_get_loop_points(struct ModAudio* audio, RET u64 *loopStart, RET u64 *loopEnd);
/* |description|Sets an `audio`'s loop points in samples|descriptionEnd| */
void audio_set_loop_points(struct ModAudio* audio, s64 loopStart, OPTIONAL s64 loopEnd);
/* |description|Gets the frequency of an `audio`|descriptionEnd| */
f32 audio_get_frequency(struct ModAudio* audio);
/* |description|Sets the frequency of an `audio`|descriptionEnd| */
void audio_set_frequency(struct ModAudio* audio, f32 freq);
/* |description|Gets the volume channel of an `audio`|descriptionEnd| */
u8 audio_get_volume_channel(struct ModAudio *audio);
/* |description|Sets the volume channel of an `audio`|descriptionEnd| */
void audio_set_volume_channel(struct ModAudio *audio, u8 channel);
/* |description|Gets the sample rate of an `audio`|descriptionEnd| */
u32 audio_get_sample_rate(struct ModAudio* audio);

void audio_destroy_pending_copies(void);

void audio_custom_update_volume(void);
void audio_custom_shutdown(void);
void smlua_audio_custom_deinit(void);

#endif
