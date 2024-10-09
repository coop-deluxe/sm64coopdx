#include "pc/rom_assets.h"
static const struct Animation anim_A3[] = {
    1,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_A3_indices),
    anim_A3_values,
    anim_A3_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A3_values),
    ANIM_FIELD_LENGTH(anim_A3_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A3_indices, 0x0055ece4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A3_values, 0x0055ede0, 2590, 0x00000000, 2590);

