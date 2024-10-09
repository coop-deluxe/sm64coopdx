#include "pc/rom_assets.h"
static const struct Animation anim_36[] = {
    1,
    189,
    10,
    0,
    0x2E,
    ANIMINDEX_NUMPARTS(anim_36_indices),
    anim_36_values,
    anim_36_indices,
    0,
    ANIM_FIELD_LENGTH(anim_36_values),
    ANIM_FIELD_LENGTH(anim_36_indices),
};


ROM_ASSET_LOAD_ANIM(anim_36_indices, 0x005197e4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_36_values, 0x005198e0, 3700, 0x00000000, 3700);

