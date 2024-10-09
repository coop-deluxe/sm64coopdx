#include "pc/rom_assets.h"
static const struct Animation anim_B4[] = {
    1,
    189,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_B4_indices),
    anim_B4_values,
    anim_B4_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B4_values),
    ANIM_FIELD_LENGTH(anim_B4_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B4_indices, 0x0056a490, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B4_values, 0x0056a58c, 1846, 0x00000000, 1846);

