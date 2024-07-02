#include "pc/rom_assets.h"
static const struct Animation anim_9E[] = {
    1,
    189,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(anim_9E_indices),
    anim_9E_values,
    anim_9E_indices,
    0,
    ANIM_FIELD_LENGTH(anim_9E_values),
    ANIM_FIELD_LENGTH(anim_9E_indices),
};


ROM_ASSET_LOAD_ANIM(anim_9E_indices, 0x0055ca08, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_9E_values, 0x0055cb04, 4008, 0x00000000, 4008);

