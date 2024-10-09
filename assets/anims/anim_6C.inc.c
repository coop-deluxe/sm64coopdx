#include "pc/rom_assets.h"
static const struct Animation anim_6C[] = {
    0,
    189,
    0,
    0,
    0x1B,
    ANIMINDEX_NUMPARTS(anim_6C_indices),
    anim_6C_values,
    anim_6C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6C_values),
    ANIM_FIELD_LENGTH(anim_6C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_6C_indices, 0x0053d4d4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_6C_values, 0x0053d5d0, 1284, 0x00000000, 1284);

