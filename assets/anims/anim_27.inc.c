#include "pc/rom_assets.h"
static const struct Animation anim_27[] = {
    1,
    189,
    0,
    0,
    0x70,
    ANIMINDEX_NUMPARTS(anim_27_indices),
    anim_27_values,
    anim_27_indices,
    0,
    ANIM_FIELD_LENGTH(anim_27_values),
    ANIM_FIELD_LENGTH(anim_27_indices),
};


ROM_ASSET_LOAD_ANIM(anim_27_indices, 0x0050993c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_27_values, 0x00509a38, 8980, 0x00000000, 8980);

