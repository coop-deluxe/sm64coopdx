#include "pc/rom_assets.h"
static const struct Animation anim_C3[] = {
    1,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_C3_indices),
    anim_C3_values,
    anim_C3_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C3_values),
    ANIM_FIELD_LENGTH(anim_C3_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C3_indices, 0x0057230c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C3_values, 0x00572408, 1942, 0x00000000, 1942);

