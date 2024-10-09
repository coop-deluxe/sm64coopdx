#include "pc/rom_assets.h"
// 0x0600CE90
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_0600CE90, 0x001d8310, 51422, 0x0000cf80, 5256);

// 0x0600E318
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_0600E318, 0x001d8310, 51422, 0x0000b660, 252);

// 0x0600E414
static const struct Animation toad_seg6_anim_0600E414 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_0600E318),
    toad_seg6_animvalue_0600CE90,
    toad_seg6_animindex_0600E318,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_0600CE90),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_0600E318),
};
