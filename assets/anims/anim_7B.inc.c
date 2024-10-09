#include "pc/rom_assets.h"
static const struct Animation anim_7B[] = {
    1,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_7B_indices),
    anim_7B_values,
    anim_7B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_7B_values),
    ANIM_FIELD_LENGTH(anim_7B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_7B_indices, 0x00546e00, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_7B_values, 0x00546efc, 2360, 0x00000000, 2360);

