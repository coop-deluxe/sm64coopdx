#include "pc/rom_assets.h"
static const struct Animation anim_A0[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_A0_indices),
    anim_A0_values,
    anim_A0_indices,
    0,
    ANIM_FIELD_LENGTH(anim_A0_values),
    ANIM_FIELD_LENGTH(anim_A0_indices),
};


ROM_ASSET_LOAD_ANIM(anim_A0_indices, 0x0055dee0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_A0_values, 0x0055dfdc, 390, 0x00000000, 390);

