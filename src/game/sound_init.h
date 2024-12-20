#ifndef SOUND_INIT_H
#define SOUND_INIT_H

#include <PR/ultratypes.h>

#include "macros.h"

#define SOUND_MENU_FLAG_HANDAPPEAR              0x01
#define SOUND_MENU_FLAG_HANDISAPPEAR            0x02
#define SOUND_MENU_FLAG_UNKNOWN1                0x04
#define SOUND_MENU_FLAG_PINCHMARIOFACE          0x08
#define SOUND_MENU_FLAG_PINCHMARIOFACE2         0x10
#define SOUND_MENU_FLAG_LETGOMARIOFACE          0x20
#define SOUND_MENU_FLAG_CAMERAZOOMIN            0x40
#define SOUND_MENU_FLAG_CAMERAZOOMOUT           0x80

#define SOUND_MENU_MODE_STEREO       0
#define SOUND_MENU_MODE_MONO         1
#define SOUND_MENU_MODE_HEADSET      2

/* |description|Resets if music volume has been lowered|descriptionEnd| */
void reset_volume(void);
/* |description|Raises music volume back up to normal levels|descriptionEnd| */
void raise_background_noise(s32 a);
/* |description|Lowers the volume of music by 40%|descriptionEnd| */
void lower_background_noise(s32 a);
/* |description|Disables background soundbanks|descriptionEnd| */
void disable_background_sound(void);
/* |description|Enables background soundbanks|descriptionEnd| */
void enable_background_sound(void);
void set_sound_mode(u16 soundMode);
/* |description|Play menu sounds from `SOUND_MENU_FLAG_*` constants and queues rumble if `SOUND_MENU_FLAG_LETGOMARIOFACE` is one of the flags|descriptionEnd| */
void play_menu_sounds(s16 soundMenuFlags);
/* |description|Plays the painting eject sound effect if it has not already been played|descriptionEnd| */
void play_painting_eject_sound(void);
/* |description|Plays the infinite stairs music if you're in the endless stairs room and have less than `gLevelValues.infiniteStairsRequirement` stars|descriptionEnd| */
void play_infinite_stairs_music(void);
/* |description|Sets the background music to `seqArgs` on sequence player `a` with a fade in time of `fadeTimer`|descriptionEnd| */
void set_background_music(u16 a, u16 seqArgs, s16 fadeTimer);
/* |description|Fades out level, shell, and cap music|descriptionEnd| */
void fadeout_music(s16 fadeOutTime);
/* |description|Fades out the level sequence player|descriptionEnd| */
void fadeout_level_music(s16 fadeTimer);
/* |description|Plays and sets the current music to `seqArgs`|descriptionEnd| */
void play_cutscene_music(u16 seqArgs);
/* |description|Plays shell music|descriptionEnd| */
void play_shell_music(void);
/* |description|Stops shell music completely|descriptionEnd| */
void stop_shell_music(void);
/* |description|Plays `seqArgs` as cap music|descriptionEnd| */
void play_cap_music(u16 seqArgs);
/* |description|Fades out cap music|descriptionEnd| */
void fadeout_cap_music(void);
/* |description|Stops cap music completely|descriptionEnd| */
void stop_cap_music(void);
void audio_game_loop_tick(void);
void thread4_sound(UNUSED void *arg);

#endif // SOUND_INIT_H
