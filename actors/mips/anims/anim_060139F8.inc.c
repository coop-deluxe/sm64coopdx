#include "pc/rom_assets.h"
// 0x060136B4
ROM_ASSET_LOAD_ANIM(mips_seg6_animvalue_060136B4, 0x001d8310, 51422, 0x000137a4, 620);

// 0x06013920
ROM_ASSET_LOAD_ANIM(mips_seg6_animindex_06013920, 0x001d8310, 51422, 0x00013a10, 216);

// 0x060139F8
static const struct Animation mips_seg6_anim_060139F8 = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(mips_seg6_animindex_06013920),
    mips_seg6_animvalue_060136B4,
    mips_seg6_animindex_06013920,
    0,
    ANIM_FIELD_LENGTH(mips_seg6_animvalue_060136B4),
    ANIM_FIELD_LENGTH(mips_seg6_animindex_06013920),
};
