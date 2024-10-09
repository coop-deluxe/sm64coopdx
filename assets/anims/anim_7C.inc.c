#include "pc/rom_assets.h"
static const struct Animation anim_7C[] = {
    1,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_7C_indices),
    anim_7C_values,
    anim_7C_indices,
    0,
    ANIM_FIELD_LENGTH(anim_7C_values),
    ANIM_FIELD_LENGTH(anim_7C_indices),
};


ROM_ASSET_LOAD_ANIM(anim_7C_indices, 0x0054784c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_7C_values, 0x00547948, 2300, 0x00000000, 2300);

