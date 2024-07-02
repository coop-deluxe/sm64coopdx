#include "pc/rom_assets.h"
// 0x0500E6F0
ROM_ASSET_LOAD_ANIM(wiggler_seg5_animvalue_0500E6F0, 0x00180bb0, 29674, 0x0000e6f0, 1208);

// 0x0500EBA8
ROM_ASSET_LOAD_ANIM(wiggler_seg5_animindex_0500EBA8, 0x00180bb0, 29674, 0x0000eba8, 204);

// 0x0500EC74
static const struct Animation wiggler_seg5_anim_0500EC74 = {
    0,
    0,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(wiggler_seg5_animindex_0500EBA8),
    wiggler_seg5_animvalue_0500E6F0,
    wiggler_seg5_animindex_0500EBA8,
    0,
    ANIM_FIELD_LENGTH(wiggler_seg5_animvalue_0500E6F0),
    ANIM_FIELD_LENGTH(wiggler_seg5_animindex_0500EBA8),
};
