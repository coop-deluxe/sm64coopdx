#include "pc/rom_assets.h"
static const struct Animation anim_B0[] = {
    1,
    189,
    0,
    0,
    0x05,
    ANIMINDEX_NUMPARTS(anim_B0_indices),
    anim_B0_values,
    anim_B0_indices,
    0,
    ANIM_FIELD_LENGTH(anim_B0_values),
    ANIM_FIELD_LENGTH(anim_B0_indices),
};


ROM_ASSET_LOAD_ANIM(anim_B0_indices, 0x00567494, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_B0_values, 0x00567590, 440, 0x00000000, 440);

