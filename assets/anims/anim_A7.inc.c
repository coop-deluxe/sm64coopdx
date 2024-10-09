#include "pc/rom_assets.h"
static const struct Animation anim_A7[] = {
    1,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_A7_indices),
    anim_A7_values,
    anim_A7_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A7_values),
    ANIM_FIELD_LENGTH(anim_A7_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A7_indices, 0x0056280c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A7_values, 0x00562908, 3060, 0x00000000, 3060);

