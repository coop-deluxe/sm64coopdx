#include "pc/rom_assets.h"
static const struct Animation anim_40[] = {
    1,
    189,
    0,
    0,
    0x13,
    ANIMINDEX_NUMPARTS(anim_40_indices),
    anim_40_values,
    anim_40_indices,
    0,
    ANIM_FIELD_LENGTH(anim_40_values),
    ANIM_FIELD_LENGTH(anim_40_indices),
};


ROM_ASSET_LOAD_ANIM(anim_40_indices, 0x005240d0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_40_values, 0x005241cc, 1094, 0x00000000, 1094);

