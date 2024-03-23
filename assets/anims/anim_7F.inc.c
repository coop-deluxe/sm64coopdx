#include "pc/rom_assets.h"
static const struct Animation anim_7F[] = {
    0,
    189,
    0,
    0,
    0x40,
    ANIMINDEX_NUMPARTS(anim_7F_indices),
    anim_7F_values,
    anim_7F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_7F_values),
    ANIM_FIELD_LENGTH(anim_7F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_7F_indices, 0x00549a9c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_7F_values, 0x00549b98, 3622, 0x00000000, 3622);

