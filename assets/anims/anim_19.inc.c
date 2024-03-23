#include "pc/rom_assets.h"
static const struct Animation anim_19[] = {
    1,
    189,
    0,
    0,
    0x56,
    ANIMINDEX_NUMPARTS(anim_19_indices),
    anim_19_values,
    anim_19_indices,
    0,
    ANIM_FIELD_LENGTH(anim_19_values),
    ANIM_FIELD_LENGTH(anim_19_indices),
};


ROM_ASSET_LOAD_ANIM(anim_19_indices, 0x004fa630, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_19_values, 0x004fa72c, 5354, 0x00000000, 5354);

