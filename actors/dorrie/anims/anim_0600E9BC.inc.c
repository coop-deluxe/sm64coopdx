#include "pc/rom_assets.h"
// 0x0600E1A4
ROM_ASSET_LOAD_ANIM(dorrie_seg6_animvalue_0600E1A4, 0x001e7ee0, 40011, 0x0000e1a4, 1844);

// 0x0600E8D8
ROM_ASSET_LOAD_ANIM(dorrie_seg6_animindex_0600E8D8, 0x001e7ee0, 40011, 0x0000e8d8, 228);

// 0x0600E9BC
static const struct Animation dorrie_seg6_anim_0600E9BC = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(dorrie_seg6_animindex_0600E8D8),
    dorrie_seg6_animvalue_0600E1A4,
    dorrie_seg6_animindex_0600E8D8,
    0,
    ANIM_FIELD_LENGTH(dorrie_seg6_animvalue_0600E1A4),
    ANIM_FIELD_LENGTH(dorrie_seg6_animindex_0600E8D8),
};
