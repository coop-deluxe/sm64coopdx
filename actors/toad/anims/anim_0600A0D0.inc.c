#include "pc/rom_assets.h"
// 0x06009A08
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_06009A08, 0x001d8310, 51422, 0x00009af8, 1484);

// 0x06009FD4
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_06009FD4, 0x001d8310, 51422, 0x000099e4, 252);

// 0x0600A0D0
static const struct Animation toad_seg6_anim_0600A0D0 = {
    0,
    0,
    0,
    0,
    0x3B,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_06009FD4),
    toad_seg6_animvalue_06009A08,
    toad_seg6_animindex_06009FD4,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_06009A08),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_06009FD4),
};
