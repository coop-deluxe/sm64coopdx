#include "pc/rom_assets.h"
static const struct Animation anim_AE[] = {
    1,
    189,
    0,
    0,
    0x0B,
    ANIMINDEX_NUMPARTS(anim_AE_indices),
    anim_AE_values,
    anim_AE_indices,
    0,
    ANIM_FIELD_LENGTH(anim_AE_values),
    ANIM_FIELD_LENGTH(anim_AE_indices),
};


ROM_ASSET_LOAD_ANIM(anim_AE_indices, 0x00566640, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_AE_values, 0x0056673c, 956, 0x00000000, 956);

