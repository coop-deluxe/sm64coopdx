#include "pc/rom_assets.h"
static const struct Animation anim_BA[] = {
    0,
    189,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_BA_indices),
    anim_BA_values,
    anim_BA_indices,
    0,
    ANIM_FIELD_LENGTH(anim_BA_values),
    ANIM_FIELD_LENGTH(anim_BA_indices),
};


ROM_ASSET_LOAD_ANIM(anim_BA_indices, 0x0056cd6c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_BA_values, 0x0056ce68, 986, 0x00000000, 986);

