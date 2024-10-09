#include "pc/rom_assets.h"
static const struct Animation anim_9A[] = {
    1,
    189,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(anim_9A_indices),
    anim_9A_values,
    anim_9A_indices,
    0,
    ANIM_FIELD_LENGTH(anim_9A_values),
    ANIM_FIELD_LENGTH(anim_9A_indices),
};


ROM_ASSET_LOAD_ANIM(anim_9A_indices, 0x0055a610, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_9A_values, 0x0055a70c, 644, 0x00000000, 644);

