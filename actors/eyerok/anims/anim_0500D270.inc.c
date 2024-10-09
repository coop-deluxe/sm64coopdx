#include "pc/rom_assets.h"
// 0x0500CC48
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500CC48, 0x00145e90, 48337, 0x0000cc48, 1060);

// 0x0500D06C
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_0500D06C, 0x00145e90, 48337, 0x0000d06c, 516);

// 0x0500D270
static const struct Animation eyerok_seg5_anim_0500D270 = {
    33,
    0,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_0500D06C),
    eyerok_seg5_animvalue_0500CC48,
    eyerok_seg5_animindex_0500D06C,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500CC48),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_0500D06C),
};
