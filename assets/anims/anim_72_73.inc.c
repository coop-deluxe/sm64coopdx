#include "pc/rom_assets.h"
static const struct Animation anim_72[] = {
    0,
    189,
    0,
    0,
    0x48,
    ANIMINDEX_NUMPARTS(anim_72_73_indices),
    anim_72_73_values,
    anim_72_73_indices,
    0,
    ANIM_FIELD_LENGTH(anim_72_73_values),
    ANIM_FIELD_LENGTH(anim_72_73_indices),
};

static const struct Animation anim_73[] = {
    0,
    189,
    0,
    0,
    0x48,
    ANIMINDEX_NUMPARTS(anim_72_73_indices),
    anim_72_73_values,
    anim_72_73_indices,
    0,
    ANIM_FIELD_LENGTH(anim_72_73_values),
    ANIM_FIELD_LENGTH(anim_72_73_indices),
};


ROM_ASSET_LOAD_ANIM(anim_72_73_indices, 0x0053f168, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_72_73_values, 0x0053f264, 4342, 0x00000000, 4342);

