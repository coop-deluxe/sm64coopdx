#include "pc/rom_assets.h"
// 0x06011FE0
ROM_ASSET_LOAD_ANIM(mips_seg6_animvalue_06011FE0, 0x001d8310, 51422, 0x000120d0, 4496);

// 0x06013170
ROM_ASSET_LOAD_ANIM(mips_seg6_animindex_06013170, 0x001d8310, 51422, 0x00013260, 216);

// 0x06013248
static const struct Animation mips_seg6_anim_06013248 = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(mips_seg6_animindex_06013170),
    mips_seg6_animvalue_06011FE0,
    mips_seg6_animindex_06013170,
    0,
    ANIM_FIELD_LENGTH(mips_seg6_animvalue_06011FE0),
    ANIM_FIELD_LENGTH(mips_seg6_animindex_06013170),
};
