#include "pc/rom_assets.h"
static const struct Animation anim_1B[] = {
    0,
    189,
    0,
    0,
    0x40,
    ANIMINDEX_NUMPARTS(anim_1B_indices),
    anim_1B_values,
    anim_1B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_1B_values),
    ANIM_FIELD_LENGTH(anim_1B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_1B_indices, 0x004fc1c0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_1B_values, 0x004fc2bc, 2858, 0x00000000, 2858);

