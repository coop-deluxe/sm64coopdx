#include "pc/rom_assets.h"
// 0x06012000
ROM_ASSET_LOAD_ANIM(bub_seg6_animvalue_06012000, 0x001b9cc0, 41188, 0x00012000, 732);

// 0x060122DC
ROM_ASSET_LOAD_ANIM(bub_seg6_animindex_060122DC, 0x001b9cc0, 41188, 0x000122dc, 96);

// 0x0601233C
static const struct Animation bub_seg6_anim_0601233C = {
    0,
    0,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(bub_seg6_animindex_060122DC),
    bub_seg6_animvalue_06012000,
    bub_seg6_animindex_060122DC,
    0,
    ANIM_FIELD_LENGTH(bub_seg6_animvalue_06012000),
    ANIM_FIELD_LENGTH(bub_seg6_animindex_060122DC),
};
