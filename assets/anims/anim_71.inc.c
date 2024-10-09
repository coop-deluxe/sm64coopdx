#include "pc/rom_assets.h"
static const struct Animation anim_71[] = {
    1,
    189,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_71_indices),
    anim_71_values,
    anim_71_indices,
    0,
    ANIM_FIELD_LENGTH(anim_71_values),
    ANIM_FIELD_LENGTH(anim_71_indices),
};


ROM_ASSET_LOAD_ANIM(anim_71_indices, 0x0053e81c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_71_values, 0x0053e918, 2078, 0x00000000, 2078);

