#include "pc/rom_assets.h"
// 0x0600E42C
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_0600E42C, 0x001d8310, 51422, 0x0000e51c, 5656);

// 0x0600FA44
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_0600FA44, 0x001d8310, 51422, 0x0000fb34, 252);

// 0x0600FB40
static const struct Animation toad_seg6_anim_0600FB40 = {
    1,
    0,
    0,
    0,
    0x70,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_0600FA44),
    toad_seg6_animvalue_0600E42C,
    toad_seg6_animindex_0600FA44,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_0600E42C),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_0600FA44),
};
