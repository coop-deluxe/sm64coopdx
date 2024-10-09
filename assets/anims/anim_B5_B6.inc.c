#include "pc/rom_assets.h"
static const struct Animation anim_B5[] = {
    1,
    189,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_B5_B6_indices),
    anim_B5_B6_values,
    anim_B5_B6_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B5_B6_values),
    ANIM_FIELD_LENGTH(anim_B5_B6_indices),
};

static const struct Animation anim_B6[] = {
    1,
    189,
    19,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_B5_B6_indices),
    anim_B5_B6_values,
    anim_B5_B6_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B5_B6_values),
    ANIM_FIELD_LENGTH(anim_B5_B6_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B5_B6_indices, 0x0056acf4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B5_B6_values, 0x0056adf0, 1382, 0x00000000, 1382);

