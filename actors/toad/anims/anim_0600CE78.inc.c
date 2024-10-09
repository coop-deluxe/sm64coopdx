#include "pc/rom_assets.h"
// 0x0600B684
ROM_ASSET_LOAD_ANIM(toad_seg6_animvalue_0600B684, 0x001d8310, 51422, 0x0000b774, 5880);

// 0x0600CD7C
ROM_ASSET_LOAD_ANIM(toad_seg6_animindex_0600CD7C, 0x001d8310, 51422, 0x0000ce6c, 252);

// 0x0600CE78
static const struct Animation toad_seg6_anim_0600CE78 = {
    1,
    0,
    0,
    0,
    0x70,
    ANIMINDEX_NUMPARTS(toad_seg6_animindex_0600CD7C),
    toad_seg6_animvalue_0600B684,
    toad_seg6_animindex_0600CD7C,
    0,
    ANIM_FIELD_LENGTH(toad_seg6_animvalue_0600B684),
    ANIM_FIELD_LENGTH(toad_seg6_animindex_0600CD7C),
};
