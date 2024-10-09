#include "pc/rom_assets.h"
static const struct Animation anim_8A[] = {
    1,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_8A_indices),
    anim_8A_values,
    anim_8A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_8A_values),
    ANIM_FIELD_LENGTH(anim_8A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_8A_indices, 0x00552854, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_8A_values, 0x00552950, 2980, 0x00000000, 2980);

