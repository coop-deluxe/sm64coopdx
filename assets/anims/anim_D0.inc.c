#include "pc/rom_assets.h"
static const struct Animation anim_D0[] = {
    1,
    189,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(anim_D0_indices),
    anim_D0_values,
    anim_D0_indices,
    0,
    ANIM_FIELD_LENGTH(anim_D0_values),
    ANIM_FIELD_LENGTH(anim_D0_indices),
};


ROM_ASSET_LOAD_ANIM(anim_D0_indices, 0x00579840, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_D0_values, 0x0057993c, 730, 0x00000000, 730);

