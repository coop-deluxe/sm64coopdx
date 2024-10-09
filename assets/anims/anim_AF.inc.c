#include "pc/rom_assets.h"
static const struct Animation anim_AF[] = {
    1,
    189,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(anim_AF_indices),
    anim_AF_values,
    anim_AF_indices,
    0,
    ANIM_FIELD_LENGTH(anim_AF_values),
    ANIM_FIELD_LENGTH(anim_AF_indices),
};


ROM_ASSET_LOAD_ANIM(anim_AF_indices, 0x00566b10, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_AF_values, 0x00566c0c, 2160, 0x00000000, 2160);

