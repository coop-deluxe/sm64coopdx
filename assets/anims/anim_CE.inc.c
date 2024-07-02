#include "pc/rom_assets.h"
static const struct Animation anim_CE[] = {
    1,
    189,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_CE_indices),
    anim_CE_values,
    anim_CE_indices,
    0,
    ANIM_FIELD_LENGTH(anim_CE_values),
    ANIM_FIELD_LENGTH(anim_CE_indices),
};


ROM_ASSET_LOAD_ANIM(anim_CE_indices, 0x005785d0, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_CE_values, 0x005786cc, 1460, 0x00000000, 1460);

