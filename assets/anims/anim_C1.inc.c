#include "pc/rom_assets.h"
static const struct Animation anim_C1[] = {
    1,
    189,
    0,
    0,
    0x24,
    ANIMINDEX_NUMPARTS(anim_C1_indices),
    anim_C1_values,
    anim_C1_indices,
    0,
    ANIM_FIELD_LENGTH(anim_C1_values),
    ANIM_FIELD_LENGTH(anim_C1_indices),
};


ROM_ASSET_LOAD_ANIM(anim_C1_indices, 0x00570210, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_C1_values, 0x0057030c, 2468, 0x00000000, 2468);

