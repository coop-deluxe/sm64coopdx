#include "pc/rom_assets.h"
static const struct Animation anim_B2[] = {
    0,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_B2_indices),
    anim_B2_values,
    anim_B2_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B2_values),
    ANIM_FIELD_LENGTH(anim_B2_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B2_indices, 0x005681e8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B2_values, 0x005682e4, 1824, 0x00000000, 1824);

