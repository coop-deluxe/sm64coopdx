#include "pc/rom_assets.h"
static const struct Animation anim_75[] = {
    1,
    189,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_75_indices),
    anim_75_values,
    anim_75_indices,
    0,
    ANIM_FIELD_LENGTH(anim_75_values),
    ANIM_FIELD_LENGTH(anim_75_indices),
};


ROM_ASSET_LOAD_ANIM(anim_75_indices, 0x00540bbc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_75_values, 0x00540cb8, 1892, 0x00000000, 1892);

