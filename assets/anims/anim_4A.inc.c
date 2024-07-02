#include "pc/rom_assets.h"
static const struct Animation anim_4A[] = {
    1,
    189,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(anim_4A_indices),
    anim_4A_values,
    anim_4A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_4A_values),
    ANIM_FIELD_LENGTH(anim_4A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_4A_indices, 0x00527888, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_4A_values, 0x00527984, 616, 0x00000000, 616);

