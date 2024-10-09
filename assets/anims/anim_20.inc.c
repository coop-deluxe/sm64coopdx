#include "pc/rom_assets.h"
static const struct Animation anim_20[] = {
    1,
    189,
    0,
    0,
    0x60,
    ANIMINDEX_NUMPARTS(anim_20_indices),
    anim_20_values,
    anim_20_indices,
    0,
    ANIM_FIELD_LENGTH(anim_20_values),
    ANIM_FIELD_LENGTH(anim_20_indices),
};


ROM_ASSET_LOAD_ANIM(anim_20_indices, 0x004fe40c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_20_values, 0x004fe508, 7124, 0x00000000, 7124);

