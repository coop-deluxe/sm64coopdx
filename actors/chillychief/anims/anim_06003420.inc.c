#include "pc/rom_assets.h"
// 0x06003304
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animvalue_06003304, 0x00132c60, 7692, 0x000042bc, 116);

// 0x06003378
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animindex_06003378, 0x00132c60, 7692, 0x00004330, 168);

// 0x06003420
static const struct Animation chilly_chief_seg6_anim_06003420 = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(chilly_chief_seg6_animindex_06003378),
    chilly_chief_seg6_animvalue_06003304,
    chilly_chief_seg6_animindex_06003378,
    0,
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animvalue_06003304),
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animindex_06003378),
};
