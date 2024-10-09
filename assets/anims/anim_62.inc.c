#include "pc/rom_assets.h"
static const struct Animation anim_62[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_62_indices),
    anim_62_values,
    anim_62_indices,
    0,
    ANIM_FIELD_LENGTH(anim_62_values),
    ANIM_FIELD_LENGTH(anim_62_indices),
};


ROM_ASSET_LOAD_ANIM(anim_62_indices, 0x0053a004, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_62_values, 0x0053a100, 742, 0x00000000, 742);

