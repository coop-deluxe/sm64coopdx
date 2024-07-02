#include "pc/rom_assets.h"
static const struct Animation anim_BE[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_BE_indices),
    anim_BE_values,
    anim_BE_indices,
    0,
    ANIM_FIELD_LENGTH(anim_BE_values),
    ANIM_FIELD_LENGTH(anim_BE_indices),
};


ROM_ASSET_LOAD_ANIM(anim_BE_indices, 0x0056eab8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_BE_values, 0x0056ebb4, 760, 0x00000000, 760);

