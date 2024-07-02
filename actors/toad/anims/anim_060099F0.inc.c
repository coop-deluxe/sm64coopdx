#include "pc/rom_assets.h"
// 0x06009328
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_06009328, 0x001d8310, 51422, 0x00009418, 1484);

// 0x060098F4
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_060098F4, 0x001d8310, 51422, 0x000099e4, 252);

// 0x060099F0
static const struct Animation toad_seg6_anim_060099F0 = {
    0,
    0,
    0,
    0,
    0x3B,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_060098F4),
    toad_seg6_animvalue_06009328,
    toad_seg6_animindex_060098F4,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_06009328),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_060098F4),
};
