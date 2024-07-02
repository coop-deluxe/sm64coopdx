#include "pc/rom_assets.h"
static const struct Animation anim_AB[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_AB_indices),
    anim_AB_values,
    anim_AB_indices,
    0,
    ANIM_FIELD_LENGTH(anim_AB_values),
    ANIM_FIELD_LENGTH(anim_AB_indices),
};


ROM_ASSET_LOAD_ANIM(anim_AB_indices, 0x00565224, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_AB_values, 0x00565320, 750, 0x00000000, 750);

