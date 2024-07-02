#include "pc/rom_assets.h"
static const struct Animation anim_78[] = {
    0,
    189,
    0,
    0,
    0x95,
    ANIMINDEX_NUMPARTS(anim_78_indices),
    anim_78_values,
    anim_78_indices,
    0,
    ANIM_FIELD_LENGTH(anim_78_values),
    ANIM_FIELD_LENGTH(anim_78_indices),
};


ROM_ASSET_LOAD_ANIM(anim_78_indices, 0x00543224, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_78_values, 0x00543320, 10454, 0x00000000, 10454);

