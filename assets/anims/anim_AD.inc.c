#include "pc/rom_assets.h"
static const struct Animation anim_AD[] = {
    1,
    189,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(anim_AD_indices),
    anim_AD_values,
    anim_AD_indices,
    0,
    ANIM_FIELD_LENGTH(anim_AD_values),
    ANIM_FIELD_LENGTH(anim_AD_indices),
};


ROM_ASSET_LOAD_ANIM(anim_AD_indices, 0x00565de8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_AD_values, 0x00565ee4, 1860, 0x00000000, 1860);

