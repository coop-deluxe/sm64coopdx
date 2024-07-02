#include "pc/rom_assets.h"
// 0x06008F94
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_06008F94, 0x001d8310, 51422, 0x00009084, 640);

// 0x06009214
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_06009214, 0x001d8310, 51422, 0x00008f70, 252);

// 0x06009310
static const struct Animation toad_seg6_anim_06009310 = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_06009214),
    toad_seg6_animvalue_06008F94,
    toad_seg6_animindex_06009214,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_06008F94),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_06009214),
};
