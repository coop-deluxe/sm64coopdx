#include "pc/rom_assets.h"
static const struct Animation anim_5D[] = {
    1,
    189,
    0,
    0,
    0x13,
    ANIMINDEX_NUMPARTS(anim_5D_indices),
    anim_5D_values,
    anim_5D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_5D_values),
    ANIM_FIELD_LENGTH(anim_5D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_5D_indices, 0x005311ec, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_5D_values, 0x005312e8, 1142, 0x00000000, 1142);

