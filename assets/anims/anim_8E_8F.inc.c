#include "pc/rom_assets.h"
static const struct Animation anim_8E[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_8E_8F_indices),
    anim_8E_8F_values,
    anim_8E_8F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_8E_8F_values),
    ANIM_FIELD_LENGTH(anim_8E_8F_indices),
};

static const struct Animation anim_8F[] = {
    1,
    189,
    1,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_8E_8F_indices),
    anim_8E_8F_values,
    anim_8E_8F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_8E_8F_values),
    ANIM_FIELD_LENGTH(anim_8E_8F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_8E_8F_indices, 0x00554ac4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_8E_8F_values, 0x00554bc0, 1618, 0x00000000, 1618);

