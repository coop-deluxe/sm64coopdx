#include "pc/rom_assets.h"
static const struct Animation anim_98[] = {
    0,
    189,
    0,
    0,
    0x5A,
    ANIMINDEX_NUMPARTS(anim_98_indices),
    anim_98_values,
    anim_98_indices,
    0,
    ANIM_FIELD_LENGTH(anim_98_values),
    ANIM_FIELD_LENGTH(anim_98_indices),
};


ROM_ASSET_LOAD_ANIM(anim_98_indices, 0x00557db8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_98_values, 0x00557eb4, 2758, 0x00000000, 2758);

