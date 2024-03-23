#include "pc/rom_assets.h"
static const struct Animation anim_11[] = {
    1,
    189,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_11_indices),
    anim_11_values,
    anim_11_indices,
    0,
    ANIM_FIELD_LENGTH(anim_11_values),
    ANIM_FIELD_LENGTH(anim_11_indices),
};


ROM_ASSET_LOAD_ANIM(anim_11_indices, 0x004f5704, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_11_values, 0x004f5800, 1174, 0x00000000, 1174);

