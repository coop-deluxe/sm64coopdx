#include "pc/rom_assets.h"
// 0x050045B0
ROM_ASSET_LOAD_ANIM(bully_seg5_animvalue_050045B0, 0x00132c60, 7692, 0x000045b0, 156);

// 0x0500464C
ROM_ASSET_LOAD_ANIM(bully_seg5_animindex_0500464C, 0x00132c60, 7692, 0x0000464c, 168);

// 0x050046F4
static const struct Animation bully_seg5_anim_050046F4 = {
    0,
    0,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(bully_seg5_animindex_0500464C),
    bully_seg5_animvalue_050045B0,
    bully_seg5_animindex_0500464C,
    0,
    ANIM_FIELD_LENGTH(bully_seg5_animvalue_050045B0),
    ANIM_FIELD_LENGTH(bully_seg5_animindex_0500464C),
};
