#include "pc/rom_assets.h"
static const struct Animation anim_2A[] = {
    0,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_2A_indices),
    anim_2A_values,
    anim_2A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_2A_values),
    ANIM_FIELD_LENGTH(anim_2A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_2A_indices, 0x0050c5c8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_2A_values, 0x0050c6c4, 1252, 0x00000000, 1252);

