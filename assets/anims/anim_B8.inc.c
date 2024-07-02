#include "pc/rom_assets.h"
static const struct Animation anim_B8[] = {
    0,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_B8_indices),
    anim_B8_values,
    anim_B8_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B8_values),
    ANIM_FIELD_LENGTH(anim_B8_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B8_indices, 0x0056c028, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B8_values, 0x0056c124, 776, 0x00000000, 776);

