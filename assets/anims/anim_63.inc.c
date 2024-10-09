#include "pc/rom_assets.h"
static const struct Animation anim_63[] = {
    0,
    189,
    0,
    0,
    0x21,
    ANIMINDEX_NUMPARTS(anim_63_indices),
    anim_63_values,
    anim_63_indices,
    0,
    ANIM_FIELD_LENGTH(anim_63_values),
    ANIM_FIELD_LENGTH(anim_63_indices),
};


ROM_ASSET_LOAD_ANIM(anim_63_indices, 0x0053a400, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_63_values, 0x0053a4fc, 1626, 0x00000000, 1626);

