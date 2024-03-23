#include "pc/rom_assets.h"
static const struct Animation anim_96[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_96_indices),
    anim_96_values,
    anim_96_indices,
    0,
    ANIM_FIELD_LENGTH(anim_96_values),
    ANIM_FIELD_LENGTH(anim_96_indices),
};


ROM_ASSET_LOAD_ANIM(anim_96_indices, 0x00557748, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_96_values, 0x00557844, 680, 0x00000000, 680);

