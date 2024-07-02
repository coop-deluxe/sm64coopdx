#include "pc/rom_assets.h"
// 0x0500758C
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_0500758C, 0x00145e90, 48337, 0x0000758c, 736);

// 0x0500786C
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_0500786C, 0x00145e90, 48337, 0x0000786c, 324);

// 0x050079B0
static const struct Animation klepto_seg5_anim_050079B0 = {
    0,
    0,
    0,
    0,
    0x07,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_0500786C),
    klepto_seg5_animvalue_0500758C,
    klepto_seg5_animindex_0500786C,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_0500758C),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_0500786C),
};
