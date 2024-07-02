#include "pc/rom_assets.h"
static const struct Animation anim_B1[] = {
    1,
    189,
    0,
    0,
    0x1C,
    ANIMINDEX_NUMPARTS(anim_B1_indices),
    anim_B1_values,
    anim_B1_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B1_values),
    ANIM_FIELD_LENGTH(anim_B1_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B1_indices, 0x00567760, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B1_values, 0x0056785c, 2418, 0x00000000, 2418);

