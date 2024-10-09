#include "pc/rom_assets.h"
static const struct Animation anim_51[] = {
    1,
    189,
    0,
    0,
    0x0E,
    ANIMINDEX_NUMPARTS(anim_51_indices),
    anim_51_values,
    anim_51_indices,
    0,
    ANIM_FIELD_LENGTH(anim_51_values),
    ANIM_FIELD_LENGTH(anim_51_indices),
};


ROM_ASSET_LOAD_ANIM(anim_51_indices, 0x00529af4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_51_values, 0x00529bf0, 1002, 0x00000000, 1002);

