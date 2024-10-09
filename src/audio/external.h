#ifndef AUDIO_EXTERNAL_H
#define AUDIO_EXTERNAL_H

#include <PR/ultratypes.h>

#include "types.h"

#define MAX_AUDIO_OVERRIDE 128

// Sequence arguments, passed to seq_player_play_sequence. seqId may be bit-OR'ed with
// SEQ_VARIATION; this will load the same sequence, but set a variation
// bit which may be read by the sequence script.
#define SEQUENCE_ARGS(priority, seqId) ((priority << 8) | seqId)

#define SOUND_MODE_STEREO           0
#define SOUND_MODE_MONO             3
#define SOUND_MODE_HEADSET          1

#define SEQ_PLAYER_LEVEL            0  // Level background music
#define SEQ_PLAYER_ENV              1  // Misc music like the puzzle jingle
#define SEQ_PLAYER_SFX              2  // Sound effects

enum DialogSound {
    DS_UKIKI,
    DS_TUXIE,
    DS_BOWS1, // Bowser Intro / Doors Laugh
    DS_KOOPA,
    DS_KBOMB,
    DS_BOO,
    DS_BOMB,
    DS_BOWS2, // Bowser Battle Laugh
    DS_GRUNT,
    DS_WIGLR,
    DS_YOSHI,
    DS_MAX,
    DS_NONE = 0xff
};

#ifdef VERSION_JP
#define DS_DIFF DS_KOOPA
#else
#define DS_DIFF DS_TUXIE
#endif

extern s32 gAudioErrorFlags;
extern f32 gGlobalSoundSource[3];

extern const u8 sBackgroundMusicDefaultVolumeDefault[35];
extern u8 sBackgroundMusicDefaultVolume[MAX_AUDIO_OVERRIDE];

// defined in data.c, used by the game
extern u32 gAudioRandom;

extern u8 gAudioSPTaskYieldBuffer[]; // ucode yield data ptr; only used in JP

struct SPTask *create_next_audio_frame_task(void);
#ifdef VERSION_SH
struct SPTask *func_sh_802f5a80(void);
#endif
void play_sound(s32 soundBits, f32 *pos);
void play_sound_with_freq_scale(s32 soundBits, f32* pos, f32 freqScale);
void audio_signal_game_loop_tick(void);
void seq_player_fade_out(u8 player, u16 fadeDuration);
void fade_volume_scale(u8 player, u8 targetScale, u16 fadeDuration);
void seq_player_lower_volume(u8 player, u16 fadeDuration, u8 percentage);
void seq_player_unlower_volume(u8 player, u16 fadeDuration);
void set_audio_muted(u8 muted);
void sound_init(void);
void get_currently_playing_sound(u8 bank, u8 *numPlayingSounds, u8 *numSoundsInBank, u8 *soundId);
void stop_sound(u32 soundBits, f32 *pos);
void stop_sounds_from_source(f32 *pos);
void stop_sounds_in_continuous_banks(void);
void sound_banks_disable(u8 player, u16 bankMask);
void sound_banks_enable(u8 player, u16 bankMask);
void set_sound_moving_speed(u8 bank, u8 speed);
void play_dialog_sound(u8 dialogID);
void set_sequence_player_volume(s32 player, f32 volume);
void play_music(u8 player, u16 seqArgs, u16 fadeTimer);
void stop_background_music(u16 seqId);
void fadeout_background_music(u16 arg0, u16 fadeOut);
void drop_queued_background_music(void);
u16 get_current_background_music(void);
u8 get_current_background_music_default_volume(void);
u8 get_current_background_music_target_volume(void);
u8 get_current_background_music_max_target_volume(void);
u8 is_current_background_music_volume_lowered(void);
void play_secondary_music(u8 seqId, u8 bgMusicVolume, u8 volume, u16 fadeTimer);
void stop_secondary_music(u16 fadeTimer);
void set_audio_fadeout(u16 fadeOutTime);
void play_course_clear(void);
void play_peachs_jingle(void);
void play_puzzle_jingle(void);
void play_star_fanfare(void);
void play_power_star_jingle(u8 arg0);
void play_race_fanfare(void);
void play_toads_jingle(void);
void sound_reset(u8 presetId);
void audio_set_sound_mode(u8 arg0);

void audio_init(void); // in load.c

void sound_reset_background_music_default_volume(u8 seqId);
void sound_set_background_music_default_volume(u8 seqId, u8 volume);

#if defined(VERSION_EU) || defined(VERSION_SH)
struct SPTask *unused_80321460();
struct SPTask *unused_80321460(void);
#endif

f32 get_sound_pan(f32 x, f32 z);
f32 sound_get_level_intensity(f32 distance);

#endif // AUDIO_EXTERNAL_H
