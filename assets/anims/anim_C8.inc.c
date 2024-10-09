#include "pc/rom_assets.h"
static const struct Animation anim_C8[] = {
    1,
    189,
    6,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_C8_indices),
    anim_C8_values,
    anim_C8_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C8_values),
    ANIM_FIELD_LENGTH(anim_C8_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C8_indices, 0x005750d8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C8_values, 0x005751d4, 1648, 0x00000000, 1648);

