#include "pc/rom_assets.h"
static const struct Animation anim_B7[] = {
    1,
    189,
    0,
    0,
    0x28,
    ANIMINDEX_NUMPARTS(anim_B7_indices),
    anim_B7_values,
    anim_B7_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B7_values),
    ANIM_FIELD_LENGTH(anim_B7_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B7_indices, 0x0056b370, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B7_values, 0x0056b46c, 2980, 0x00000000, 2980);

