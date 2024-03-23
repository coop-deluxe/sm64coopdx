#include "pc/rom_assets.h"
static const struct Animation anim_04[] = {
    1,
    189,
    0,
    0,
    0x21,
    ANIMINDEX_NUMPARTS(anim_04_indices),
    anim_04_values,
    anim_04_indices,
    0,
    ANIM_FIELD_LENGTH(anim_04_values),
    ANIM_FIELD_LENGTH(anim_04_indices),
};


ROM_ASSET_LOAD_ANIM(anim_04_indices, 0x004efeec, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_04_values, 0x004effe8, 2264, 0x00000000, 2264);

