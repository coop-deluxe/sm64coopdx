#include "pc/rom_assets.h"
static const struct Animation anim_91[] = {
    0,
    189,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(anim_91_indices),
    anim_91_values,
    anim_91_indices,
    0,
    ANIM_FIELD_LENGTH(anim_91_values),
    ANIM_FIELD_LENGTH(anim_91_indices),
};


ROM_ASSET_LOAD_ANIM(anim_91_indices, 0x00555734, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_91_values, 0x00555830, 266, 0x00000000, 266);

