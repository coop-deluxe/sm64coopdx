#include "pc/rom_assets.h"
static const struct Animation anim_6E[] = {
    1,
    189,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_6E_indices),
    anim_6E_values,
    anim_6E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6E_values),
    ANIM_FIELD_LENGTH(anim_6E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_6E_indices, 0x0053e108, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_6E_values, 0x0053e204, 1136, 0x00000000, 1136);

