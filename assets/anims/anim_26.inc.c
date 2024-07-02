#include "pc/rom_assets.h"
static const struct Animation anim_26[] = {
    65,
    189,
    0,
    0,
    0x5E,
    ANIMINDEX_NUMPARTS(anim_26_indices),
    anim_26_values,
    anim_26_indices,
    0,
    ANIM_FIELD_LENGTH(anim_26_values),
    ANIM_FIELD_LENGTH(anim_26_indices),
};


ROM_ASSET_LOAD_ANIM(anim_26_indices, 0x00507b70, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_26_values, 0x00507c6c, 7352, 0x00000000, 7352);

