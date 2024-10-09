#include "pc/rom_assets.h"
static const struct Animation anim_84[] = {
    1,
    189,
    0,
    0,
    0x40,
    ANIMINDEX_NUMPARTS(anim_84_indices),
    anim_84_values,
    anim_84_indices,
    0,
    ANIM_FIELD_LENGTH(anim_84_values),
    ANIM_FIELD_LENGTH(anim_84_indices),
};


ROM_ASSET_LOAD_ANIM(anim_84_indices, 0x0054f8a0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_84_values, 0x0054f99c, 4756, 0x00000000, 4756);

