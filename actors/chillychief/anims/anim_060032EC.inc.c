#include "pc/rom_assets.h"
// 0x06003080
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animvalue_06003080, 0x00132c60, 7692, 0x00004038, 452);

// 0x06003244
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animindex_06003244, 0x00132c60, 7692, 0x000041fc, 168);

// 0x060032EC
static const struct Animation chilly_chief_seg6_anim_060032EC = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(chilly_chief_seg6_animindex_06003244),
    chilly_chief_seg6_animvalue_06003080,
    chilly_chief_seg6_animindex_06003244,
    0,
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animvalue_06003080),
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animindex_06003244),
};
