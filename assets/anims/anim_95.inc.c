#include "pc/rom_assets.h"
static const struct Animation anim_95[] = {
    1,
    189,
    0,
    0,
    0x05,
    ANIMINDEX_NUMPARTS(anim_95_indices),
    anim_95_values,
    anim_95_indices,
    0,
    ANIM_FIELD_LENGTH(anim_95_values),
    ANIM_FIELD_LENGTH(anim_95_indices),
};


ROM_ASSET_LOAD_ANIM(anim_95_indices, 0x0055751c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_95_values, 0x00557618, 280, 0x00000000, 280);

