#include "pc/rom_assets.h"
static const struct Animation anim_3F[] = {
    0,
    189,
    0,
    0,
    0x3D,
    ANIMINDEX_NUMPARTS(anim_3F_indices),
    anim_3F_values,
    anim_3F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_3F_values),
    ANIM_FIELD_LENGTH(anim_3F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_3F_indices, 0x005233a4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_3F_values, 0x005234a0, 3094, 0x00000000, 3094);

