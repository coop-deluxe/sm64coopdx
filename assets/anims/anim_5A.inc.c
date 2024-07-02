#include "pc/rom_assets.h"
static const struct Animation anim_5A[] = {
    1,
    189,
    0,
    0,
    0x26,
    ANIMINDEX_NUMPARTS(anim_5A_indices),
    anim_5A_values,
    anim_5A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_5A_values),
    ANIM_FIELD_LENGTH(anim_5A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_5A_indices, 0x0052fa24, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_5A_values, 0x0052fb20, 3278, 0x00000000, 3278);

