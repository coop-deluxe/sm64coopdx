#include "pc/rom_assets.h"
static const struct Animation anim_2E[] = {
    1,
    189,
    0,
    0,
    0x2F,
    ANIMINDEX_NUMPARTS(anim_2E_indices),
    anim_2E_values,
    anim_2E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_2E_values),
    ANIM_FIELD_LENGTH(anim_2E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_2E_indices, 0x0050ea24, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_2E_values, 0x0050eb20, 3028, 0x00000000, 3028);

