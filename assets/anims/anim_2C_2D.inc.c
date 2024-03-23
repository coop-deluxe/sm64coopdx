#include "pc/rom_assets.h"
static const struct Animation anim_2C[] = {
    1,
    189,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(anim_2C_2D_indices),
    anim_2C_2D_values,
    anim_2C_2D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_2C_2D_values),
    ANIM_FIELD_LENGTH(anim_2C_2D_indices),
};

static const struct Animation anim_2D[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_2C_2D_indices),
    anim_2C_2D_values,
    anim_2C_2D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_2C_2D_values),
    ANIM_FIELD_LENGTH(anim_2C_2D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_2C_2D_indices, 0x0050d31c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_2C_2D_values, 0x0050d418, 5620, 0x00000000, 5620);

