#include "pc/rom_assets.h"
static const struct Animation anim_A1[] = {
    0,
    189,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_A1_indices),
    anim_A1_values,
    anim_A1_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A1_values),
    ANIM_FIELD_LENGTH(anim_A1_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A1_indices, 0x0055e17c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A1_values, 0x0055e278, 920, 0x00000000, 920);

