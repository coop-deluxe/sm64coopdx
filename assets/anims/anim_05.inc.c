#include "pc/rom_assets.h"
static const struct Animation anim_05[] = {
    0,
    189,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(anim_05_indices),
    anim_05_values,
    anim_05_indices,
    0,
    ANIM_FIELD_LENGTH(anim_05_values),
    ANIM_FIELD_LENGTH(anim_05_indices),
};


ROM_ASSET_LOAD_ANIM(anim_05_indices, 0x004f08d8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_05_values, 0x004f09d4, 5796, 0x00000000, 5796);

