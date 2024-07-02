#include "pc/rom_assets.h"
// 0x0500E1F0
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animvalue_0500E1F0, 0x00145e90, 48337, 0x0000e1f0, 1448);

// 0x0500E798
ROM_ASSET_LOAD_ANIM(eyerok_seg5_animindex_0500E798, 0x00145e90, 48337, 0x0000e798, 516);

// 0x0500E99C
static const struct Animation eyerok_seg5_anim_0500E99C = {
    32,
    0,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(eyerok_seg5_animindex_0500E798),
    eyerok_seg5_animvalue_0500E1F0,
    eyerok_seg5_animindex_0500E798,
    0,
    ANIM_FIELD_LENGTH(eyerok_seg5_animvalue_0500E1F0),
    ANIM_FIELD_LENGTH(eyerok_seg5_animindex_0500E798),
};
