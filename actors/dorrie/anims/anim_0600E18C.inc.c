#include "pc/rom_assets.h"
// 0x0600E060
ROM_ASSET_LOAD_ANIM(dorrie_seg6_animvalue_0600E060, 0x001e7ee0, 40011, 0x0000e060, 72);

// 0x0600E0A8
ROM_ASSET_LOAD_ANIM(dorrie_seg6_animindex_0600E0A8, 0x001e7ee0, 40011, 0x0000e0a8, 228);

// 0x0600E18C
static const struct Animation dorrie_seg6_anim_0600E18C = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(dorrie_seg6_animindex_0600E0A8),
    dorrie_seg6_animvalue_0600E060,
    dorrie_seg6_animindex_0600E0A8,
    0,
    ANIM_FIELD_LENGTH(dorrie_seg6_animvalue_0600E060),
    ANIM_FIELD_LENGTH(dorrie_seg6_animindex_0600E0A8),
};
