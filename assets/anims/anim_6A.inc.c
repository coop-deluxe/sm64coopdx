#include "pc/rom_assets.h"
static const struct Animation anim_6A[] = {
    1,
    189,
    0,
    0,
    0x0D,
    ANIMINDEX_NUMPARTS(anim_6A_indices),
    anim_6A_values,
    anim_6A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6A_values),
    ANIM_FIELD_LENGTH(anim_6A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_6A_indices, 0x0053cadc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_6A_values, 0x0053cbd8, 1060, 0x00000000, 1060);

