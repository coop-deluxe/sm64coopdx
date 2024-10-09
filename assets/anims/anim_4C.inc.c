#include "pc/rom_assets.h"
static const struct Animation anim_4C[] = {
    1,
    189,
    0,
    0,
    0x09,
    ANIMINDEX_NUMPARTS(anim_4C_indices),
    anim_4C_values,
    anim_4C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_4C_values),
    ANIM_FIELD_LENGTH(anim_4C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_4C_indices, 0x00528284, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_4C_values, 0x00528380, 670, 0x00000000, 670);

