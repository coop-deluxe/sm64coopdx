#include "pc/rom_assets.h"
// 0x0500D288
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500D288, 0x00145e90, 48337, 0x0000d288, 2756);

// 0x0500DD4C
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_0500DD4C, 0x00145e90, 48337, 0x0000dd4c, 516);

// 0x0500DF50
static const struct Animation eyerok_seg5_anim_0500DF50 = {
    32,
    0,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_0500DD4C),
    eyerok_seg5_animvalue_0500D288,
    eyerok_seg5_animindex_0500DD4C,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500D288),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_0500DD4C),
};
