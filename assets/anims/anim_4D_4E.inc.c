#include "pc/rom_assets.h"
static const struct Animation anim_4D[] = {
    1,
    189,
    0,
    0,
    0x0C,
    ANIMINDEX_NUMPARTS(anim_4D_4E_indices),
    anim_4D_4E_values,
    anim_4D_4E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_4D_4E_values),
    ANIM_FIELD_LENGTH(anim_4D_4E_indices),
};

static const struct Animation anim_4E[] = {
    1,
    189,
    22,
    0,
    0x26,
    ANIMINDEX_NUMPARTS(anim_4D_4E_indices),
    anim_4D_4E_values,
    anim_4D_4E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_4D_4E_values),
    ANIM_FIELD_LENGTH(anim_4D_4E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_4D_4E_indices, 0x00528650, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_4D_4E_values, 0x0052874c, 2456, 0x00000000, 2456);

