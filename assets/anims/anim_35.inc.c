#include "pc/rom_assets.h"
static const struct Animation anim_35[] = {
    1,
    189,
    0,
    0,
    0x36,
    ANIMINDEX_NUMPARTS(anim_35_indices),
    anim_35_values,
    anim_35_indices,
    0,
    ANIM_FIELD_LENGTH(anim_35_values),
    ANIM_FIELD_LENGTH(anim_35_indices),
};


ROM_ASSET_LOAD_ANIM(anim_35_indices, 0x00518858, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_35_values, 0x00518954, 3704, 0x00000000, 3704);

