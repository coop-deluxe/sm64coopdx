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
/* |description|Plays a sound (`soundBits`) at `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)|descriptionEnd| */
void play_sound(s32 soundBits, f32 *pos);
/* |description|Plays a sound (`soundBits`) with `freqScale` at `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)|descriptionEnd| */
void play_sound_with_freq_scale(s32 soundBits, f32* pos, f32 freqScale);
void audio_signal_game_loop_tick(void);
/* |description|Fades out `player` with `fadeDuration`|descriptionEnd| */
void seq_player_fade_out(u8 player, u16 fadeDuration);
/* |description|Fades the volume of `player` to `targetScale` (0-127) over `fadeDuration`|descriptionEnd| */
void fade_volume_scale(u8 player, u8 targetScale, u16 fadeDuration);
/* |description|Fades the volume of `player` to `percentage` over `fadeDuration`|descriptionEnd| */
void seq_player_lower_volume(u8 player, u16 fadeDuration, u8 percentage);
/* |description|Unfades the volume of `player` over `fadeDuration`|descriptionEnd| */
void seq_player_unlower_volume(u8 player, u16 fadeDuration);
/* |description|Sets the muted status of all sequence players|descriptionEnd| */
void set_audio_muted(u8 muted);
void sound_init(void);
void get_currently_playing_sound(u8 bank, u8 *numPlayingSounds, u8 *numSoundsInBank, u8 *soundId);
/* |description|Stops a sound (`soundBits`) at `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)|descriptionEnd| */
void stop_sound(u32 soundBits, f32 *pos);
/* |description|Stops sounds from `pos` (usually `gGlobalSoundSource` or `m.header.gfx.cameraToObject`)|descriptionEnd| */
void stop_sounds_from_source(f32 *pos);
/* |description|Stops sounds in sound banks moving, env, and air|descriptionEnd| */
void stop_sounds_in_continuous_banks(void);
/* |description|Enables `bankMask` soundbanks in `player`|descriptionEnd| */
void sound_banks_disable(u8 player, u16 bankMask);
/* |description|Disables `bankMask` soundbanks in `player`|descriptionEnd| */
void sound_banks_enable(u8 player, u16 bankMask);
/* |description|Sets the `speed` of moving `bank`|descriptionEnd| */
void set_sound_moving_speed(u8 bank, u8 speed);
/* |description|Plays a dialog sound corresponding to `dialogID`|descriptionEnd| */
void play_dialog_sound(u8 dialogID);
/* |description|Sets the `volume` of `player`|descriptionEnd| */
void set_sequence_player_volume(s32 player, f32 volume);
/* |description|Plays fading in music (`seqArgs`) on `player` over `fadeTimer`|descriptionEnd| */
void play_music(u8 player, u16 seqArgs, u16 fadeTimer);
/* |description|Stops background music `seqId`|descriptionEnd| */
void stop_background_music(u16 seqId);
/* |description|Fades out background music `seqId` over `fadeOut`|descriptionEnd| */
void fadeout_background_music(u16 seqId, u16 fadeOut);
/* |description|Drops any queued background music|descriptionEnd| */
void drop_queued_background_music(void);
/* |description|Gets the current background music|descriptionEnd| */
u16 get_current_background_music(void);
/* |description|Gets the current background music's default volume|descriptionEnd| */
u8 get_current_background_music_default_volume(void);
/* |description|Gets the current target volume|descriptionEnd| */
u8 get_current_background_music_target_volume(void);
/* |description|Gets the current max target volume|descriptionEnd| */
u8 get_current_background_music_max_target_volume(void);
/* |description|Checks if the current background music is lowered|descriptionEnd| */
u8 is_current_background_music_volume_lowered(void);
/* |description|Plays fading in secondary music `seqId` at `volume` over `fadeTimer` and sets the current background music's volume to `bgMusicVolume`|descriptionEnd| */
void play_secondary_music(u8 seqId, u8 bgMusicVolume, u8 volume, u16 fadeTimer);
/* |description|Fades out secondary music over `fadeTimer`|descriptionEnd| */
void stop_secondary_music(u16 fadeTimer);
/* |description|Sets the `fadeOutTime` of audio|descriptionEnd| */
void set_audio_fadeout(u16 fadeOutTime);
/* |description|Plays the star collect fanfare (this function's name was mixed up with the other)|descriptionEnd| */
void play_course_clear(void);
/* |description|Plays Peach's letter jingle|descriptionEnd| */
void play_peachs_jingle(void);
/* |description|Plays the puzzle jingle|descriptionEnd| */
void play_puzzle_jingle(void);
/* |description|Plays the course clear fanfare (this function's name was mixed up with the other)|descriptionEnd| */
void play_star_fanfare(void);
/* |description|Plays the power star jingle, set `keepBackgroundMusic` to 0 to mute background music|descriptionEnd| */
void play_power_star_jingle(u8 keepBackgroundMusic);
/* |description|Plays the race fanfare when a race is started|descriptionEnd| */
void play_race_fanfare(void);
/* |description|Plays Toad's jingle|descriptionEnd| */
void play_toads_jingle(void);
void sound_reset(u8 presetId);
void audio_set_sound_mode(u8 arg0);

void audio_init(void); // in load.c

/* |description||descriptionEnd| */
void sound_reset_background_music_default_volume(u8 seqId);
/* |description||descriptionEnd| */
void sound_set_background_music_default_volume(u8 seqId, u8 volume);

#if defined(VERSION_EU) || defined(VERSION_SH)
struct SPTask *unused_80321460();
struct SPTask *unused_80321460(void);
#endif

f32 get_sound_pan(f32 x, f32 z);
f32 sound_get_level_intensity(f32 distance);

#endif // AUDIO_EXTERNAL_H
