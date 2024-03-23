#include "pc/rom_assets.h"
// 0x05014DD0
ROM_ASSET_LOAD_ANIM(heave_ho_seg5_animvalue_05014DD0, 0x0012a7e0, 32879, 0x00014dd0, 140);

// 0x05014E5C
ROM_ASSET_LOAD_ANIM(heave_ho_seg5_animindex_05014E5C, 0x0012a7e0, 32879, 0x00014e5c, 204);

// 0x05014F28
static const struct Animation heave_ho_seg5_anim_05014F28 = {
    0,
    0,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(heave_ho_seg5_animindex_05014E5C),
    heave_ho_seg5_animvalue_05014DD0,
    heave_ho_seg5_animindex_05014E5C,
    0,
    ANIM_FIELD_LENGTH(heave_ho_seg5_animvalue_05014DD0),
    ANIM_FIELD_LENGTH(heave_ho_seg5_animindex_05014E5C),
};
