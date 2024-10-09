#include "pc/rom_assets.h"
// 0x0500FCE4
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500FCE4, 0x00145e90, 48337, 0x0000fce4, 6116);

// 0x050114C8
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_050114C8, 0x00145e90, 48337, 0x000114c8, 516);

// 0x050116CC
static const struct Animation eyerok_seg5_anim_050116CC = {
    32,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_050114C8),
    eyerok_seg5_animvalue_0500FCE4,
    eyerok_seg5_animindex_050114C8,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500FCE4),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_050114C8),
};
