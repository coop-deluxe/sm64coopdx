#include "pc/rom_assets.h"
static const struct Animation anim_44[] = {
    1,
    189,
    0,
    0,
    0x0F,
    ANIMINDEX_NUMPARTS(anim_44_indices),
    anim_44_values,
    anim_44_indices,
    0,
    ANIM_FIELD_LENGTH(anim_44_values),
    ANIM_FIELD_LENGTH(anim_44_indices),
};


ROM_ASSET_LOAD_ANIM(anim_44_indices, 0x00524f90, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_44_values, 0x0052508c, 650, 0x00000000, 650);

