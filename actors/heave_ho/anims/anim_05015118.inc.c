#include "pc/rom_assets.h"
// 0x05014F40
ROM_ASSET_LOAD_ANIM(heave_ho_seg5_animvalue_05014F40, 0x0012a7e0, 32879, 0x00014f40, 268);

// 0x0501504C
ROM_ASSET_LOAD_ANIM(heave_ho_seg5_animindex_0501504C, 0x0012a7e0, 32879, 0x0001504c, 204);

// 0x05015118
static const struct Animation heave_ho_seg5_anim_05015118 = {
    0,
    0,
    0,
    0,
    0x26,
    ANIMINDEX_NUMPARTS(heave_ho_seg5_animindex_0501504C),
    heave_ho_seg5_animvalue_05014F40,
    heave_ho_seg5_animindex_0501504C,
    0,
    ANIM_FIELD_LENGTH(heave_ho_seg5_animvalue_05014F40),
    ANIM_FIELD_LENGTH(heave_ho_seg5_animindex_0501504C),
};
