#include "pc/rom_assets.h"
static const struct Animation anim_82[] = {
    1,
    189,
    0,
    0,
    0x43,
    ANIMINDEX_NUMPARTS(anim_82_indices),
    anim_82_values,
    anim_82_indices,
    0,
    ANIM_FIELD_LENGTH(anim_82_values),
    ANIM_FIELD_LENGTH(anim_82_indices),
};


ROM_ASSET_LOAD_ANIM(anim_82_indices, 0x0054cd6c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_82_values, 0x0054ce68, 5770, 0x00000000, 5770);

