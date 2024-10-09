#include "pc/rom_assets.h"
static const struct Animation anim_5E[] = {
    1,
    189,
    0,
    0,
    0x9B,
    ANIMINDEX_NUMPARTS(anim_5E_indices),
    anim_5E_values,
    anim_5E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_5E_values),
    ANIM_FIELD_LENGTH(anim_5E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_5E_indices, 0x00531778, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_5E_values, 0x00531874, 12110, 0x00000000, 12110);

