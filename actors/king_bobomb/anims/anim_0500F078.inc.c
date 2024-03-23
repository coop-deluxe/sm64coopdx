#include "pc/rom_assets.h"
// 0x0500E124
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500E124, 0x00134d20, 26785, 0x0000e124, 3552);

// 0x0500EF04
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500EF04, 0x00134d20, 26785, 0x0000ef04, 372);

// 0x0500F078
static const struct Animation king_bobomb_seg5_anim_0500F078 = {
    0,
    0,
    0,
    0,
    0x31,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500EF04),
    king_bobomb_seg5_animvalue_0500E124,
    king_bobomb_seg5_animindex_0500EF04,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500E124),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500EF04),
};
