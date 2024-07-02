#include "pc/rom_assets.h"
// 0x06014BAC
ROM_ASSET_LOAD_ANIM(mips_seg6_animvalue_06014BAC, 0x001d8310, 51422, 0x00014c9c, 2456);

// 0x06015544
ROM_ASSET_LOAD_ANIM(mips_seg6_animindex_06015544, 0x001d8310, 51422, 0x00015634, 216);

// 0x0601561C
static const struct Animation mips_seg6_anim_0601561C = {
    0,
    0,
    0,
    0,
    0x6E,
    ANIMINDEX_NUMPARTS(mips_seg6_animindex_06015544),
    mips_seg6_animvalue_06014BAC,
    mips_seg6_animindex_06015544,
    0,
    ANIM_FIELD_LENGTH(mips_seg6_animvalue_06014BAC),
    ANIM_FIELD_LENGTH(mips_seg6_animindex_06015544),
};
