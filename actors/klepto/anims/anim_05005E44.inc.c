#include "pc/rom_assets.h"
// 0x050051E8
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_050051E8, 0x00145e90, 48337, 0x000051e8, 2840);

// 0x05005D00
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_05005D00, 0x00145e90, 48337, 0x00005d00, 324);

// 0x05005E44
static const struct Animation klepto_seg5_anim_05005E44 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_05005D00),
    klepto_seg5_animvalue_050051E8,
    klepto_seg5_animindex_05005D00,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_050051E8),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_05005D00),
};
