#include "pc/rom_assets.h"
static const struct Animation anim_9F[] = {
    1,
    189,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_9F_indices),
    anim_9F_values,
    anim_9F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_9F_values),
    ANIM_FIELD_LENGTH(anim_9F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_9F_indices, 0x0055dac4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_9F_values, 0x0055dbc0, 774, 0x00000000, 774);

