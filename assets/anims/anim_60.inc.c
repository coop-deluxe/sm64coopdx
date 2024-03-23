#include "pc/rom_assets.h"
static const struct Animation anim_60[] = {
    9,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_60_indices),
    anim_60_values,
    anim_60_indices,
    0,
    ANIM_FIELD_LENGTH(anim_60_values),
    ANIM_FIELD_LENGTH(anim_60_indices),
};


ROM_ASSET_LOAD_ANIM(anim_60_indices, 0x00535cb4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_60_values, 0x00535db0, 4020, 0x00000000, 4020);

