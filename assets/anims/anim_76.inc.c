#include "pc/rom_assets.h"
static const struct Animation anim_76[] = {
    1,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_76_indices),
    anim_76_values,
    anim_76_indices,
    0,
    ANIM_FIELD_LENGTH(anim_76_values),
    ANIM_FIELD_LENGTH(anim_76_indices),
};


ROM_ASSET_LOAD_ANIM(anim_76_indices, 0x00541434, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_76_values, 0x00541530, 4648, 0x00000000, 4648);

