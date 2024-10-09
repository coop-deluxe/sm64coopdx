#include "pc/rom_assets.h"
static const struct Animation anim_9B[] = {
    1,
    189,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(anim_9B_indices),
    anim_9B_values,
    anim_9B_indices,
    0,
    ANIM_FIELD_LENGTH(anim_9B_values),
    ANIM_FIELD_LENGTH(anim_9B_indices),
};


ROM_ASSET_LOAD_ANIM(anim_9B_indices, 0x0055a9a8, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_9B_values, 0x0055aaa4, 630, 0x00000000, 630);

