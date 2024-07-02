#include "pc/rom_assets.h"
static const struct Animation anim_99[] = {
    0,
    189,
    0,
    0,
    0x5C,
    ANIMINDEX_NUMPARTS(anim_99_indices),
    anim_99_values,
    anim_99_indices,
    0,
    ANIM_FIELD_LENGTH(anim_99_values),
    ANIM_FIELD_LENGTH(anim_99_indices),
};


ROM_ASSET_LOAD_ANIM(anim_99_indices, 0x00558994, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_99_values, 0x00558a90, 7014, 0x00000000, 7014);

