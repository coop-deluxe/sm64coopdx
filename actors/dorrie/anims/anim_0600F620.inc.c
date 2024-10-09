#include "pc/rom_assets.h"
// 0x0600E9D4
ROM_ASSET_LOAD_ANIM(dorrie_seg6_animvalue_0600E9D4, 0x001e7ee0, 40011, 0x0000e9d4, 2920);

// 0x0600F53C
ROM_ASSET_LOAD_ANIM(dorrie_seg6_animindex_0600F53C, 0x001e7ee0, 40011, 0x0000f53c, 228);

// 0x0600F620
static const struct Animation dorrie_seg6_anim_0600F620 = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(dorrie_seg6_animindex_0600F53C),
    dorrie_seg6_animvalue_0600E9D4,
    dorrie_seg6_animindex_0600F53C,
    0,
    ANIM_FIELD_LENGTH(dorrie_seg6_animvalue_0600E9D4),
    ANIM_FIELD_LENGTH(dorrie_seg6_animindex_0600F53C),
};
