#include "pc/rom_assets.h"
static const struct Animation anim_1E[] = {
    0,
    189,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(anim_1E_indices),
    anim_1E_values,
    anim_1E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_1E_values),
    ANIM_FIELD_LENGTH(anim_1E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_1E_indices, 0x004fd898, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_1E_values, 0x004fd994, 1530, 0x00000000, 1530);

