#include "pc/rom_assets.h"
// 0x06013260
ROM_ASSET_LOAD_ANIM(mips_seg6_animvalue_06013260, 0x001d8310, 51422, 0x00013350, 868);

// 0x060135C4
ROM_ASSET_LOAD_ANIM(mips_seg6_animindex_060135C4, 0x001d8310, 51422, 0x000136b4, 216);

// 0x0601369C
static const struct Animation mips_seg6_anim_0601369C = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(mips_seg6_animindex_060135C4),
    mips_seg6_animvalue_06013260,
    mips_seg6_animindex_060135C4,
    0,
    ANIM_FIELD_LENGTH(mips_seg6_animvalue_06013260),
    ANIM_FIELD_LENGTH(mips_seg6_animindex_060135C4),
};
