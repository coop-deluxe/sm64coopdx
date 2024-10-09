#include "pc/rom_assets.h"
static const struct Animation anim_94[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_94_indices),
    anim_94_values,
    anim_94_indices,
    0,
    ANIM_FIELD_LENGTH(anim_94_values),
    ANIM_FIELD_LENGTH(anim_94_indices),
};


ROM_ASSET_LOAD_ANIM(anim_94_indices, 0x004f4e94, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_94_values, 0x005574b4, 80, 0x00000000, 80);

