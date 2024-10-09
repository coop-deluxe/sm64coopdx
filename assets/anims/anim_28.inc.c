#include "pc/rom_assets.h"
static const struct Animation anim_28[] = {
    1,
    189,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(anim_28_indices),
    anim_28_values,
    anim_28_indices,
    0,
    ANIM_FIELD_LENGTH(anim_28_values),
    ANIM_FIELD_LENGTH(anim_28_indices),
};


ROM_ASSET_LOAD_ANIM(anim_28_indices, 0x0050bd64, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_28_values, 0x0050be60, 1010, 0x00000000, 1010);

