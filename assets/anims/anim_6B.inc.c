#include "pc/rom_assets.h"
static const struct Animation anim_6B[] = {
    1,
    189,
    0,
    0,
    0x0B,
    ANIMINDEX_NUMPARTS(anim_6B_indices),
    anim_6B_values,
    anim_6B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_6B_values),
    ANIM_FIELD_LENGTH(anim_6B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_6B_indices, 0x0053d014, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_6B_values, 0x0053d110, 940, 0x00000000, 940);

