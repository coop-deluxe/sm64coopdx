#include "pc/rom_assets.h"
static const struct Animation anim_2F[] = {
    1,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_2F_indices),
    anim_2F_values,
    anim_2F_indices,
    0,
    ANIM_FIELD_LENGTH(anim_2F_values),
    ANIM_FIELD_LENGTH(anim_2F_indices),
};


ROM_ASSET_LOAD_ANIM(anim_2F_indices, 0x0050f70c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_2F_values, 0x0050f808, 7420, 0x00000000, 7420);

