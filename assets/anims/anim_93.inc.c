#include "pc/rom_assets.h"
static const struct Animation anim_93[] = {
    1,
    189,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(anim_93_indices),
    anim_93_values,
    anim_93_indices,
    0,
    ANIM_FIELD_LENGTH(anim_93_values),
    ANIM_FIELD_LENGTH(anim_93_indices),
};


ROM_ASSET_LOAD_ANIM(anim_93_indices, 0x00557048, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_93_values, 0x00557144, 602, 0x00000000, 602);

