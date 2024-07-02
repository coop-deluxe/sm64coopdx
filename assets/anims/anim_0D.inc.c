#include "pc/rom_assets.h"
static const struct Animation anim_0D[] = {
    0,
    189,
    0,
    0,
    0x70,
    ANIMINDEX_NUMPARTS(anim_0D_indices),
    anim_0D_values,
    anim_0D_indices,
    0,
    ANIM_FIELD_LENGTH(anim_0D_values),
    ANIM_FIELD_LENGTH(anim_0D_indices),
};


ROM_ASSET_LOAD_ANIM(anim_0D_indices, 0x004f4a7c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_0D_values, 0x004f4b78, 770, 0x00000000, 770);

