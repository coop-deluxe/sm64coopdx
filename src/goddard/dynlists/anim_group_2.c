#include "pc/rom_assets.h"
#include <PR/ultratypes.h>

#include "macros.h"
#include "animdata.h"
#include "../gd_types.h"

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_ear_right_1, 0x00294dd0, 4920, 0x00000000, 4920, 3);

struct AnimDataInfo anim_mario_ear_right[] = {
    { ARRAY_COUNT(animdata_mario_ear_right_1), GD_ANIM_ROT3S, animdata_mario_ear_right_1 },
    { 0, GD_ANIM_EMPTY, NULL },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_nose_1, 0x0029612c, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_nose_2, 0x00297464, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_nose[] = {
    { ARRAY_COUNT(animdata_mario_nose_1), GD_ANIM_ROT3S, animdata_mario_nose_1 },
    { ARRAY_COUNT(animdata_mario_nose_2), GD_ANIM_ROT3S, animdata_mario_nose_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_5_1, 0x0029786c, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lips_5_2, 0x00298ba4, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_lips_5[] = {
    { ARRAY_COUNT(animdata_mario_lips_5_1), GD_ANIM_ROT3S, animdata_mario_lips_5_1 },
    { ARRAY_COUNT(animdata_mario_lips_5_2), GD_ANIM_ROT3S, animdata_mario_lips_5_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lip_6_1, 0x00298fac, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_lip_6_2, 0x0029a2e4, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_lips_6[] = {
    { ARRAY_COUNT(animdata_mario_lip_6_1), GD_ANIM_ROT3S, animdata_mario_lip_6_1 },
    { ARRAY_COUNT(animdata_mario_lip_6_2), GD_ANIM_ROT3S, animdata_mario_lip_6_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyelid_left_1, 0x0029a6ec, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyelid_left_2, 0x0029ba24, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_eyelid_left[] = {
    { ARRAY_COUNT(animdata_mario_eyelid_left_1), GD_ANIM_ROT3S, animdata_mario_eyelid_left_1 },
    { ARRAY_COUNT(animdata_mario_eyelid_left_2), GD_ANIM_ROT3S, animdata_mario_eyelid_left_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyelid_right_1, 0x0029be2c, 4920, 0x00000000, 4920, 3);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_eyelid_right_2, 0x0029d164, 996, 0x00000000, 996, 3);

struct AnimDataInfo anim_mario_eyelid_right[] = {
    { ARRAY_COUNT(animdata_mario_eyelid_right_1), GD_ANIM_ROT3S, animdata_mario_eyelid_right_1 },
    { ARRAY_COUNT(animdata_mario_eyelid_right_2), GD_ANIM_ROT3S, animdata_mario_eyelid_right_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_intro_1, 0x0029d56c, 9840, 0x00000000, 9840, 6);

ROM_ASSET_LOAD_ANIM_2D(animdata_mario_intro_2, 0x0029fbdc, 1992, 0x00000000, 1992, 6);

struct AnimDataInfo anim_mario_intro[] = {
    { ARRAY_COUNT(animdata_mario_intro_1), GD_ANIM_ROT3S_POS3S, animdata_mario_intro_1 },
    { ARRAY_COUNT(animdata_mario_intro_2), GD_ANIM_ROT3S_POS3S, animdata_mario_intro_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_silver_star_1, 0x002a03c8, 9840, 0x00000000, 9840, 6);

ROM_ASSET_LOAD_ANIM_2D(animdata_silver_star_2, 0x002a2a38, 1992, 0x00000000, 1992, 6);

struct AnimDataInfo anim_silver_star[] = {
    { ARRAY_COUNT(animdata_silver_star_1), GD_ANIM_ROT3S_POS3S, animdata_silver_star_1 },
    { ARRAY_COUNT(animdata_silver_star_2), GD_ANIM_ROT3S_POS3S, animdata_silver_star_2 },
    END_ANIMDATA_INFO_ARR,
};

ROM_ASSET_LOAD_ANIM_2D(animdata_red_star_1, 0x002a3224, 9840, 0x00000000, 9840, 6);

ROM_ASSET_LOAD_ANIM_2D(animdata_red_star_2, 0x002a5894, 1992, 0x00000000, 1992, 6);

struct AnimDataInfo anim_red_star[] = {
    { ARRAY_COUNT(animdata_red_star_1), GD_ANIM_ROT3S_POS3S, animdata_red_star_1 },
    { ARRAY_COUNT(animdata_red_star_2), GD_ANIM_ROT3S_POS3S, animdata_red_star_2 },
    END_ANIMDATA_INFO_ARR,
};
