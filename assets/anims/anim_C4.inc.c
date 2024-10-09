#include "pc/rom_assets.h"
static const struct Animation anim_C4[] = {
    1,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_C4_indices),
    anim_C4_values,
    anim_C4_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C4_values),
    ANIM_FIELD_LENGTH(anim_C4_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C4_indices, 0x0057230c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C4_values, 0x00572cb4, 1942, 0x00000000, 1942);

