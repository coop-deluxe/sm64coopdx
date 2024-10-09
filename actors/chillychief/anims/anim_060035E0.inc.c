#include "pc/rom_assets.h"
// 0x06003438
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animvalue_06003438, 0x00132c60, 7692, 0x000043f0, 256);

// 0x06003538
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animindex_06003538, 0x00132c60, 7692, 0x000044f0, 168);

// 0x060035E0
static const struct Animation chilly_chief_seg6_anim_060035E0 = {
    0,
    0,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(chilly_chief_seg6_animindex_06003538),
    chilly_chief_seg6_animvalue_06003438,
    chilly_chief_seg6_animindex_06003538,
    0,
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animvalue_06003438),
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animindex_06003538),
};
