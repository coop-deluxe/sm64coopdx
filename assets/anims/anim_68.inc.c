#include "pc/rom_assets.h"
static const struct Animation anim_68[] = {
    1,
    189,
    0,
    0,
    0x04,
    ANIMINDEX_NUMPARTS(anim_68_indices),
    anim_68_values,
    anim_68_indices,
    0,
    ANIM_FIELD_LENGTH(anim_68_values),
    ANIM_FIELD_LENGTH(anim_68_indices),
};


ROM_ASSET_LOAD_ANIM(anim_68_indices, 0x0053c464, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_68_values, 0x0053c560, 340, 0x00000000, 340);

