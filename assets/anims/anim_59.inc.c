#include "pc/rom_assets.h"
static const struct Animation anim_59[] = {
    1,
    189,
    0,
    0,
    0x25,
    ANIMINDEX_NUMPARTS(anim_59_indices),
    anim_59_values,
    anim_59_indices,
    0,
    ANIM_FIELD_LENGTH(anim_59_values),
    ANIM_FIELD_LENGTH(anim_59_indices),
};


ROM_ASSET_LOAD_ANIM(anim_59_indices, 0x0052ed24, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_59_values, 0x0052ee20, 3052, 0x00000000, 3052);

