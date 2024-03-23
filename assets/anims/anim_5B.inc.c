#include "pc/rom_assets.h"
static const struct Animation anim_5B[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_5B_indices),
    anim_5B_values,
    anim_5B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_5B_values),
    ANIM_FIELD_LENGTH(anim_5B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_5B_indices, 0x00530808, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_5B_values, 0x00530904, 720, 0x00000000, 720);

