#include "pc/rom_assets.h"
#include <PR/ultratypes.h>

#include "macros.h"
#include "animdata.h"
#include "../gd_types.h"

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyebrows_equalizer_1, 0x00285da0, 4920, 0x00000000, 4920, 3);

struct AnimDataInfo anim_mario_eyebrows_equalizer[] = {
    { ARRAY_COUNT(animdata_mario_eyebrows_equalizer_1), GD_ANIM_ROT3S, animdata_mario_eyebrows_equalizer_1 },
    { 0, GD_ANIM_EMPTY, NULL },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyebrows_2_1, 0x002870fc, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyebrows_2_2, 0x00288434, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_eyebrows_2[] = {
    { ARRAY_COUNT(animdata_mario_eyebrows_2_1), GD_ANIM_ROT3S, animdata_mario_eyebrows_2_1 },
    { ARRAY_COUNT(animdata_mario_eyebrows_2_2), GD_ANIM_ROT3S, animdata_mario_eyebrows_2_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(anim_mario_eyebrows_3_1, 0x00285da0, 4920, 0x00000000, 4920, 3);

struct AnimDataInfo anim_mario_eyebrows_3[] = {
    { ARRAY_COUNT(anim_mario_eyebrows_3_1), GD_ANIM_ROT3S, anim_mario_eyebrows_3_1 },
    { 0, GD_ANIM_EMPTY, NULL },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyebrows_4_1, 0x00289b98, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyebrows_4_2, 0x0028aed0, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_eyebrows_4[] = {
    { ARRAY_COUNT(animdata_mario_eyebrows_4_1), GD_ANIM_ROT3S, animdata_mario_eyebrows_4_1 },
    { ARRAY_COUNT(animdata_mario_eyebrows_4_2), GD_ANIM_ROT3S, animdata_mario_eyebrows_4_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyebrows_5_1, 0x0028b2d8, 4920, 0x00000000, 4920, 3);

struct AnimDataInfo anim_mario_eyebrows_5[] = {
    { ARRAY_COUNT(animdata_mario_eyebrows_5_1), GD_ANIM_ROT3S, animdata_mario_eyebrows_5_1 },
    { 0, GD_ANIM_EMPTY, NULL },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eye_left_1, 0x0028c634, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eye_left_2, 0x0028d96c, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_eye_left[] = {
    { ARRAY_COUNT(animdata_mario_eye_left_1), GD_ANIM_ROT3S, animdata_mario_eye_left_1 },
    { ARRAY_COUNT(animdata_mario_eye_left_2), GD_ANIM_ROT3S, animdata_mario_eye_left_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eye_right_1, 0x0028dd74, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eye_right_2, 0x0028f0ac, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_eye_right[] = {
    { ARRAY_COUNT(animdata_mario_eye_right_1), GD_ANIM_ROT3S, animdata_mario_eye_right_1 },
    { ARRAY_COUNT(animdata_mario_eye_right_2), GD_ANIM_ROT3S, animdata_mario_eye_right_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_cap_1, 0x0028f4b4, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_cap_2, 0x002907ec, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_cap[] = {
    { ARRAY_COUNT(animdata_mario_cap_1), GD_ANIM_ROT3S, animdata_mario_cap_1 },
    { ARRAY_COUNT(animdata_mario_cap_2), GD_ANIM_ROT3S, animdata_mario_cap_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_3_1, 0x00290bf4, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_3_2, 0x00291f2c, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_lips_3[] = {
    { ARRAY_COUNT(animdata_mario_lips_3_1), GD_ANIM_ROT3S, animdata_mario_lips_3_1 },
    { ARRAY_COUNT(animdata_mario_lips_3_2), GD_ANIM_ROT3S, animdata_mario_lips_3_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_4_1, 0x00292334, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_4_2, 0x0029366c, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_lips_4[] = {
    { ARRAY_COUNT(animdata_mario_lips_4_1), GD_ANIM_ROT3S, animdata_mario_lips_4_1 },
    { ARRAY_COUNT(animdata_mario_lips_4_2), GD_ANIM_ROT3S, animdata_mario_lips_4_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_ear_left_1, 0x00293a74, 4920, 0x00000000, 4920, 3);

struct AnimDataInfo anim_mario_ear_left[] = {
    { ARRAY_COUNT(animdata_mario_ear_left_1), GD_ANIM_ROT3S, animdata_mario_ear_left_1 },
    { 0, GD_ANIM_EMPTY, NULL },
    END_ANIMDATA_INFO_ARR,
};
