#include "pc/rom_assets.h"
// 0x0500F408
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500F408, 0x00145e90, 48337, 0x0000f408, 1728);

// 0x0500FAC8
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_0500FAC8, 0x00145e90, 48337, 0x0000fac8, 516);

// 0x0500FCCC
static const struct Animation eyerok_seg5_anim_0500FCCC = {
    32,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_0500FAC8),
    eyerok_seg5_animvalue_0500F408,
    eyerok_seg5_animindex_0500FAC8,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500F408),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_0500FAC8),
};
