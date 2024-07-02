#include "pc/rom_assets.h"
// 0x05005E5C
ROM_ASSET_LOAD_ANIM(klepto_seg5_animvalue_05005E5C, 0x00145e90, 48337, 0x00005e5c, 5588);

// 0x05007430
ROM_ASSET_LOAD_ANIM(klepto_seg5_animindex_05007430, 0x00145e90, 48337, 0x00007430, 324);

// 0x05007574
static const struct Animation klepto_seg5_anim_05007574 = {
    1,
    0,
    1,
    1,
    0x3A,
    ANIMINDEX_NUMPARTS(klepto_seg5_animindex_05007430),
    klepto_seg5_animvalue_05005E5C,
    klepto_seg5_animindex_05007430,
    0,
    ANIM_FIELD_LENGTH(klepto_seg5_animvalue_05005E5C),
    ANIM_FIELD_LENGTH(klepto_seg5_animindex_05007430),
};
