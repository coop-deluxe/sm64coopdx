#include "pc/rom_assets.h"
static const struct Animation anim_A5[] = {
    1,
    189,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(anim_A5_indices),
    anim_A5_values,
    anim_A5_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A5_values),
    ANIM_FIELD_LENGTH(anim_A5_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A5_indices, 0x0055ffa0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A5_values, 0x0056009c, 5148, 0x00000000, 5148);

