#include "pc/rom_assets.h"
static const struct Animation anim_22[] = {
    1,
    189,
    0,
    0,
    0x1B,
    ANIMINDEX_NUMPARTS(anim_22_indices),
    anim_22_values,
    anim_22_indices,
    0,
    ANIM_FIELD_LENGTH(anim_22_values),
    ANIM_FIELD_LENGTH(anim_22_indices),
};


ROM_ASSET_LOAD_ANIM(anim_22_indices, 0x00500c3c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_22_values, 0x00500d38, 1750, 0x00000000, 1750);

