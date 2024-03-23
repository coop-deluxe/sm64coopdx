#include "pc/rom_assets.h"
// 0x05005EB8
ROM_ASSET_LOAD_ANIM(blargg_seg5_animvalue_05005EB8, 0x00132c60, 7692, 0x00005eb8, 368);

// 0x05006028
ROM_ASSET_LOAD_ANIM(blargg_seg5_animindex_05006028, 0x00132c60, 7692, 0x00006028, 72);

// 0x05006070
static const struct Animation blargg_seg5_anim_05006070 = {
    0,
    0,
    0,
    0,
    0x2D,
    ANIMINDEX_NUMPARTS(blargg_seg5_animindex_05006028),
    blargg_seg5_animvalue_05005EB8,
    blargg_seg5_animindex_05006028,
    0,
    ANIM_FIELD_LENGTH(blargg_seg5_animvalue_05005EB8),
    ANIM_FIELD_LENGTH(blargg_seg5_animindex_05006028),
};
