#include "pc/rom_assets.h"
static const struct Animation anim_A8[] = {
    1,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_A8_indices),
    anim_A8_values,
    anim_A8_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A8_values),
    ANIM_FIELD_LENGTH(anim_A8_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A8_indices, 0x00563514, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A8_values, 0x00563610, 3910, 0x00000000, 3910);

