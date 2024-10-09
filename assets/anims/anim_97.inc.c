#include "pc/rom_assets.h"
static const struct Animation anim_97[] = {
    1,
    189,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(anim_97_indices),
    anim_97_values,
    anim_97_indices,
    0,
    ANIM_FIELD_LENGTH(anim_97_values),
    ANIM_FIELD_LENGTH(anim_97_indices),
};


ROM_ASSET_LOAD_ANIM(anim_97_indices, 0x00557b04, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_97_values, 0x00557c00, 416, 0x00000000, 416);

