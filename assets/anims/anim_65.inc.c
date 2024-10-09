#include "pc/rom_assets.h"
static const struct Animation anim_65[] = {
    1,
    189,
    0,
    0,
    0x15,
    ANIMINDEX_NUMPARTS(anim_65_indices),
    anim_65_values,
    anim_65_indices,
    0,
    ANIM_FIELD_LENGTH(anim_65_values),
    ANIM_FIELD_LENGTH(anim_65_indices),
};


ROM_ASSET_LOAD_ANIM(anim_65_indices, 0x0053b164, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_65_values, 0x0053b260, 1700, 0x00000000, 1700);

