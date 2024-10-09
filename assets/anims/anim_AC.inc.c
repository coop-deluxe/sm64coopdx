#include "pc/rom_assets.h"
static const struct Animation anim_AC[] = {
    0,
    189,
    8,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(anim_AC_indices),
    anim_AC_values,
    anim_AC_indices,
    0,
    ANIM_FIELD_LENGTH(anim_AC_values),
    ANIM_FIELD_LENGTH(anim_AC_indices),
};


ROM_ASSET_LOAD_ANIM(anim_AC_indices, 0x00565628, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_AC_values, 0x00565724, 1706, 0x00000000, 1706);

