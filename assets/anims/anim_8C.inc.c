#include "pc/rom_assets.h"
static const struct Animation anim_8C[] = {
    1,
    189,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(anim_8C_indices),
    anim_8C_values,
    anim_8C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_8C_values),
    ANIM_FIELD_LENGTH(anim_8C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_8C_indices, 0x005541bc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_8C_values, 0x005542b8, 646, 0x00000000, 646);

