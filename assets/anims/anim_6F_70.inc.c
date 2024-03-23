#include "pc/rom_assets.h"
static const struct Animation anim_6F[] = {
    0,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_6F_70_indices),
    anim_6F_70_values,
    anim_6F_70_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6F_70_values),
    ANIM_FIELD_LENGTH(anim_6F_70_indices),
};

static const struct Animation anim_70[] = {
    2,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_6F_70_indices),
    anim_6F_70_values,
    anim_6F_70_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6F_70_values),
    ANIM_FIELD_LENGTH(anim_6F_70_indices),
};


ROM_ASSET_LOAD_ANIM(anim_6F_70_indices, 0x0053e6a4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_6F_70_values, 0x0053e7a0, 98, 0x00000000, 98);

