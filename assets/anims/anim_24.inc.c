#include "pc/rom_assets.h"
static const struct Animation anim_24[] = {
    1,
    189,
    0,
    0,
    0x78,
    ANIMINDEX_NUMPARTS(anim_24_indices),
    anim_24_values,
    anim_24_indices,
    0,
    ANIM_FIELD_LENGTH(anim_24_values),
    ANIM_FIELD_LENGTH(anim_24_indices),
};


ROM_ASSET_LOAD_ANIM(anim_24_indices, 0x00503554, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_24_values, 0x00503650, 9376, 0x00000000, 9376);

