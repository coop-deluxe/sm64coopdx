#include "pc/rom_assets.h"
static const struct Animation anim_12[] = {
    1,
    189,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_12_indices),
    anim_12_values,
    anim_12_indices,
    0,
    ANIM_FIELD_LENGTH(anim_12_values),
    ANIM_FIELD_LENGTH(anim_12_indices),
};


ROM_ASSET_LOAD_ANIM(anim_12_indices, 0x004f5cb0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_12_values, 0x004f5dac, 1318, 0x00000000, 1318);

