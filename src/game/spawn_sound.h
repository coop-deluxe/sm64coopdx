#ifndef SPAWN_SOUND_H
#define SPAWN_SOUND_H

#include <PR/ultratypes.h>

struct SoundState
{
    s16 playSound; // if this is 1, the info below will
                   // be used to determine the sound behavior
                   // for the object. if 0, this is skipped.
    s8 animFrame1; // the sound state provides 2 anim frames for
                   // when the provided sound can be played.
                   // these 2 variables probably coorespond to
                   // left/right foot.
    s8 animFrame2;
    s32 soundMagic;
};

void exec_anim_sound_state(struct SoundState *soundStates, u16 maxSoundStates);
/* |description|
Plays a sound if the current object is visible
|descriptionEnd| */
void cur_obj_play_sound_if_visible(s32 soundMagic);
/* |description|
Plays a sound if the current object is visible and queues rumble for the following sounds: `SOUND_OBJ_BOWSER_WALK`, `SOUND_OBJ_POUNDING_LOUD`, `SOUND_OBJ_WHOMP_LOWPRIO`
|descriptionEnd| */
void cur_obj_play_sound_and_rumble_if_visible(s32 soundMagic);
/* |description|
Create a sound spawner for objects that need a sound play once.
(Breakable walls, King Bobomb exploding, etc)
|descriptionEnd| */
void create_sound_spawner(s32 soundMagic);

s32 calc_dist_to_volume_range_1(f32 distance);
s32 calc_dist_to_volume_range_2(f32 distance);

#endif // SPAWN_SOUND_H
