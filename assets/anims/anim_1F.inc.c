#include "pc/rom_assets.h"
static const struct Animation anim_1F[] = {
    1,
    189,
    0,
    0,
    0x15,
    ANIMINDEX_NUMPARTS(anim_1F_indices),
    anim_1F_values,
    anim_1F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_1F_values),
    ANIM_FIELD_LENGTH(anim_1F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_1F_indices, 0x004fdfa8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_1F_values, 0x004fe0a4, 846, 0x00000000, 846);

