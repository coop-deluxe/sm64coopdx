#include "pc/rom_assets.h"
// 0x06013A10
ROM_ASSET_LOAD_ANIM(mips_seg6_animvalue_06013A10, 0x001d8310, 51422, 0x00013b00, 4268);

// 0x06014ABC
ROM_ASSET_LOAD_ANIM(mips_seg6_animindex_06014ABC, 0x001d8310, 51422, 0x00014bac, 216);

// 0x06014B94
static const struct Animation mips_seg6_anim_06014B94 = {
    0,
    0,
    0,
    0,
    0x55,
    ANIMINDEX_NUMPARTS(mips_seg6_animindex_06014ABC),
    mips_seg6_animvalue_06013A10,
    mips_seg6_animindex_06014ABC,
    0,
    ANIM_FIELD_LENGTH(mips_seg6_animvalue_06013A10),
    ANIM_FIELD_LENGTH(mips_seg6_animindex_06014ABC),
};
