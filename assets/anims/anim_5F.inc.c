#include "pc/rom_assets.h"
static const struct Animation anim_5F[] = {
    9,
    189,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(anim_5F_indices),
    anim_5F_values,
    anim_5F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_5F_values),
    ANIM_FIELD_LENGTH(anim_5F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_5F_indices, 0x005347dc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_5F_values, 0x005348d8, 5058, 0x00000000, 5058);

