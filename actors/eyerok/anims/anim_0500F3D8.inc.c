#include "pc/rom_assets.h"
// 0x0500E9B4
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500E9B4, 0x00145e90, 48337, 0x0000e9b4, 2080);


// 0x0500F1D4
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_0500F1D4, 0x00145e90, 48337, 0x0000f1d4, 516);

// 0x0500F3D8
static const struct Animation eyerok_seg5_anim_0500F3D8 = {
    33,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_0500F1D4),
    eyerok_seg5_animvalue_0500E9B4,
    eyerok_seg5_animindex_0500F1D4,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500E9B4),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_0500F1D4),
};

// Same entries as above
