#include "pc/rom_assets.h"
static const struct Animation anim_A4[] = {
    0,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_A4_indices),
    anim_A4_values,
    anim_A4_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A4_values),
    ANIM_FIELD_LENGTH(anim_A4_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A4_indices, 0x0055f818, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A4_values, 0x0055f914, 1650, 0x00000000, 1650);

