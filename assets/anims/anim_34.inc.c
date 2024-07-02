#include "pc/rom_assets.h"
static const struct Animation anim_34[] = {
    1,
    189,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(anim_34_indices),
    anim_34_values,
    anim_34_indices,
    0,
    ANIM_FIELD_LENGTH(anim_34_values),
    ANIM_FIELD_LENGTH(anim_34_indices),
};


ROM_ASSET_LOAD_ANIM(anim_34_indices, 0x00518230, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_34_values, 0x0051832c, 1300, 0x00000000, 1300);

