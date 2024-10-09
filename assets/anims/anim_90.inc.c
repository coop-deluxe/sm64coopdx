#include "pc/rom_assets.h"
static const struct Animation anim_90[] = {
    1,
    189,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(anim_90_indices),
    anim_90_values,
    anim_90_indices,
    0,
    ANIM_FIELD_LENGTH(anim_90_values),
    ANIM_FIELD_LENGTH(anim_90_indices),
};


ROM_ASSET_LOAD_ANIM(anim_90_indices, 0x0055522c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_90_values, 0x00555328, 1012, 0x00000000, 1012);

