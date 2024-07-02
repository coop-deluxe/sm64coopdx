#include "pc/rom_assets.h"
static const struct Animation anim_4F[] = {
    1,
    189,
    0,
    0,
    0x15,
    ANIMINDEX_NUMPARTS(anim_4F_indices),
    anim_4F_values,
    anim_4F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_4F_values),
    ANIM_FIELD_LENGTH(anim_4F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_4F_indices, 0x005290fc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_4F_values, 0x005291f8, 1578, 0x00000000, 1578);

