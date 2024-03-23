#include "pc/rom_assets.h"
// 0x0600A0E8
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_0600A0E8, 0x001d8310, 51422, 0x0000a1d8, 5256);

// 0x0600B570
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_0600B570, 0x001d8310, 51422, 0x0000b660, 252);

// 0x0600B66C
static const struct Animation toad_seg6_anim_0600B66C = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_0600B570),
    toad_seg6_animvalue_0600A0E8,
    toad_seg6_animindex_0600B570,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_0600A0E8),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_0600B570),
};
