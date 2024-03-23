#include "pc/rom_assets.h"
static const struct Animation anim_31[] = {
    1,
    189,
    0,
    0,
    0x8C,
    ANIMINDEX_NUMPARTS(anim_31_indices),
    anim_31_values,
    anim_31_indices,
    0,
    ANIM_FIELD_LENGTH(anim_31_values),
    ANIM_FIELD_LENGTH(anim_31_indices),
};


ROM_ASSET_LOAD_ANIM(anim_31_indices, 0x00512b64, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_31_values, 0x00512c60, 10660, 0x00000000, 10660);

