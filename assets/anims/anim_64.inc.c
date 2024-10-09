#include "pc/rom_assets.h"
static const struct Animation anim_64[] = {
    0,
    189,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_64_indices),
    anim_64_values,
    anim_64_indices,
    0,
    ANIM_FIELD_LENGTH(anim_64_values),
    ANIM_FIELD_LENGTH(anim_64_indices),
};


ROM_ASSET_LOAD_ANIM(anim_64_indices, 0x0053ab70, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_64_values, 0x0053ac6c, 1246, 0x00000000, 1246);

