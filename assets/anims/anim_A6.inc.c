#include "pc/rom_assets.h"
static const struct Animation anim_A6[] = {
    1,
    189,
    0,
    0,
    0x46,
    ANIMINDEX_NUMPARTS(anim_A6_indices),
    anim_A6_values,
    anim_A6_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A6_values),
    ANIM_FIELD_LENGTH(anim_A6_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A6_indices, 0x005614d0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A6_values, 0x005615cc, 4646, 0x00000000, 4646);

