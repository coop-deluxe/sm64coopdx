#include "pc/rom_assets.h"
static const struct Animation anim_8D[] = {
    1,
    189,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(anim_8D_indices),
    anim_8D_values,
    anim_8D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_8D_values),
    ANIM_FIELD_LENGTH(anim_8D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_8D_indices, 0x00554558, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_8D_values, 0x00554654, 1086, 0x00000000, 1086);

