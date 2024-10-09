#include "pc/rom_assets.h"
static const struct Animation anim_C6[] = {
    0,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_C6_indices),
    anim_C6_values,
    anim_C6_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C6_values),
    ANIM_FIELD_LENGTH(anim_C6_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C6_indices, 0x00573d10, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C6_values, 0x00573e0c, 1666, 0x00000000, 1666);

