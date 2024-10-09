#include "pc/rom_assets.h"
static const struct Animation anim_7A[] = {
    0,
    189,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(anim_7A_indices),
    anim_7A_values,
    anim_7A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_7A_values),
    ANIM_FIELD_LENGTH(anim_7A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_7A_indices, 0x00546b58, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_7A_values, 0x00546c54, 402, 0x00000000, 402);

