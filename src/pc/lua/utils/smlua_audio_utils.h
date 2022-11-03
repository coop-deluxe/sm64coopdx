#ifndef SMLUA_AUDIO_UTILS_H
#define SMLUA_AUDIO_UTILS_H

void smlua_audio_utils_reset_all(void);
bool smlua_audio_utils_override(u8 sequenceId, s32* bankId, void** seqData);
void smlua_audio_utils_replace_sequence(u8 sequenceId, u8 bankId, u8 defaultVolume, const char* m64Name);

  //////////
 // bass //
//////////

struct BassAudio {
    struct ModFile* file;
    char* rawData;
    bool isStream;
    bool loaded;
    u32 handle;
};

struct BassAudio* audio_stream_load(const char* filename);
struct BassAudio* audio_stream_load_url(const char* url);
void audio_stream_destroy(struct BassAudio* audio);
void audio_stream_play(struct BassAudio* audio, bool restart, f32 volume);
void audio_stream_pause(struct BassAudio* audio);
void audio_stream_stop(struct BassAudio* audio);
f32 audio_stream_get_position(struct BassAudio* audio);
void audio_stream_set_position(struct BassAudio* audio, f32 pos);
bool audio_stream_get_looping(struct BassAudio* audio);
void audio_stream_set_looping(struct BassAudio* audio, bool looping);
f32 audio_stream_get_frequency(struct BassAudio* audio);
void audio_stream_set_frequency(struct BassAudio* audio, f32 freq);
f32 audio_stream_get_tempo(struct BassAudio* audio);
void audio_stream_set_tempo(struct BassAudio* audio, f32 tempo);
f32 audio_stream_get_volume(struct BassAudio* audio);
void audio_stream_set_volume(struct BassAudio* audio, f32 volume);
void audio_stream_set_speed(struct BassAudio* audio, f32 initial_freq, f32 speed, bool pitch);

struct BassAudio* audio_sample_load(const char* filename);
void audio_sample_destroy(struct BassAudio* audio);
void audio_sample_stop(struct BassAudio* audio);
void audio_sample_play(struct BassAudio* audio, Vec3f position, f32 volume);

void audio_custom_shutdown(void);

#endif