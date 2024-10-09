#include "pc/rom_assets.h"
static const struct Animation anim_52[] = {
    1,
    189,
    0,
    0,
    0x0B,
    ANIMINDEX_NUMPARTS(anim_52_indices),
    anim_52_values,
    anim_52_indices,
    0,
    ANIM_FIELD_LENGTH(anim_52_values),
    ANIM_FIELD_LENGTH(anim_52_indices),
};


ROM_ASSET_LOAD_ANIM(anim_52_indices, 0x00529ff4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_52_values, 0x0052a0f0, 878, 0x00000000, 878);

