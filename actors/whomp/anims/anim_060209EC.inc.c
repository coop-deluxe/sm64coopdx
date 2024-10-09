#include "pc/rom_assets.h"
// 0x060202F4
ROM_ASSET_LOAD_ANIM(whomp_seg6_animvalue_060202F4, 0x001c4230, 80474, 0x000202f4, 1628);

// 0x06020950
ROM_ASSET_LOAD_ANIM(whomp_seg6_animindex_06020950, 0x001c4230, 80474, 0x00020950, 156);

// 0x060209EC
static const struct Animation whomp_seg6_anim_060209EC = {
    0,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(whomp_seg6_animindex_06020950),
    whomp_seg6_animvalue_060202F4,
    whomp_seg6_animindex_06020950,
    0,
    ANIM_FIELD_LENGTH(whomp_seg6_animvalue_060202F4),
    ANIM_FIELD_LENGTH(whomp_seg6_animindex_06020950),
};
