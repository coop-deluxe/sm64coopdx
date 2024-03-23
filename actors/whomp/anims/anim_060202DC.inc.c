#include "pc/rom_assets.h"
// 0x06020098
ROM_ASSET_LOAD_ANIM(whomp_seg6_animvalue_06020098, 0x001c4230, 80474, 0x00020098, 424);

// 0x06020240
ROM_ASSET_LOAD_ANIM(whomp_seg6_animindex_06020240, 0x001c4230, 80474, 0x00020240, 156);

// 0x060202DC
static const struct Animation whomp_seg6_anim_060202DC = {
    1,
    0,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(whomp_seg6_animindex_06020240),
    whomp_seg6_animvalue_06020098,
    whomp_seg6_animindex_06020240,
    0,
    ANIM_FIELD_LENGTH(whomp_seg6_animvalue_06020098),
    ANIM_FIELD_LENGTH(whomp_seg6_animindex_06020240),
};
