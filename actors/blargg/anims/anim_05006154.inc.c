#include "pc/rom_assets.h"
// 0x05006088
ROM_ASSET_LOAD_ANIM(blargg_seg5_animvalue_05006088, 0x00132c60, 7692, 0x00006088, 132);

// 0x0500610C
ROM_ASSET_LOAD_ANIM(blargg_seg5_animindex_0500610C, 0x00132c60, 7692, 0x0000610c, 72);

// 0x05006154
static const struct Animation blargg_seg5_anim_05006154 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(blargg_seg5_animindex_0500610C),
    blargg_seg5_animvalue_05006088,
    blargg_seg5_animindex_0500610C,
    0,
    ANIM_FIELD_LENGTH(blargg_seg5_animvalue_05006088),
    ANIM_FIELD_LENGTH(blargg_seg5_animindex_0500610C),
};
