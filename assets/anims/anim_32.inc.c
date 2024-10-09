#include "pc/rom_assets.h"
static const struct Animation anim_32[] = {
    1,
    189,
    0,
    0,
    0x60,
    ANIMINDEX_NUMPARTS(anim_32_indices),
    anim_32_values,
    anim_32_indices,
    0,
    ANIM_FIELD_LENGTH(anim_32_values),
    ANIM_FIELD_LENGTH(anim_32_indices),
};


ROM_ASSET_LOAD_ANIM(anim_32_indices, 0x0051561c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_32_values, 0x00515718, 7890, 0x00000000, 7890);

