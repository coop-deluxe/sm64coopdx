#include "pc/rom_assets.h"
// 0x0500DF68
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500DF68, 0x00145e90, 48337, 0x0000df68, 108);

// 0x0500DFD4
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_0500DFD4, 0x00145e90, 48337, 0x0000dfd4, 516);

// 0x0500E1D8
static const struct Animation eyerok_seg5_anim_0500E1D8 = {
    32,
    0,
    0,
    0,
    0x02,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_0500DFD4),
    eyerok_seg5_animvalue_0500DF68,
    eyerok_seg5_animindex_0500DFD4,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500DF68),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_0500DFD4),
};
