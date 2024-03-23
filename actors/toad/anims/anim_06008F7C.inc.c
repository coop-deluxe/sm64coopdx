#include "pc/rom_assets.h"
// 0x06008C00
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_06008C00, 0x001d8310, 51422, 0x00008cf0, 640);

// 0x06008E80
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_06008E80, 0x001d8310, 51422, 0x00008f70, 252);

// 0x06008F7C
static const struct Animation toad_seg6_anim_06008F7C = {
    0,
    0,
    10,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_06008E80),
    toad_seg6_animvalue_06008C00,
    toad_seg6_animindex_06008E80,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_06008C00),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_06008E80),
};
