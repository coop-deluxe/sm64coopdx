#include "pc/rom_assets.h"
// 0x060035F8
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animvalue_060035F8, 0x00132c60, 7692, 0x000045b0, 156);

// 0x06003694
ROM_ASSET_LOAD_ANIM(chilly_chief_seg6_animindex_06003694, 0x00132c60, 7692, 0x0000464c, 168);

// 0x0600373C
static const struct Animation chilly_chief_seg6_anim_0600373C = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(chilly_chief_seg6_animindex_06003694),
    chilly_chief_seg6_animvalue_060035F8,
    chilly_chief_seg6_animindex_06003694,
    0,
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animvalue_060035F8),
    ANIM_FIELD_LENGTH(chilly_chief_seg6_animindex_06003694),
};
