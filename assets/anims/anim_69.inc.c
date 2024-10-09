#include "pc/rom_assets.h"
static const struct Animation anim_69[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_69_indices),
    anim_69_values,
    anim_69_indices,
    0,
    ANIM_FIELD_LENGTH(anim_69_values),
    ANIM_FIELD_LENGTH(anim_69_indices),
};


ROM_ASSET_LOAD_ANIM(anim_69_indices, 0x0053c6cc, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_69_values, 0x0053c7c8, 764, 0x00000000, 764);

