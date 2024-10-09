#include "pc/rom_assets.h"
static const struct Animation anim_66[] = {
    1,
    189,
    0,
    0,
    0x1A,
    ANIMINDEX_NUMPARTS(anim_66_indices),
    anim_66_values,
    anim_66_indices,
    0,
    ANIM_FIELD_LENGTH(anim_66_values),
    ANIM_FIELD_LENGTH(anim_66_indices),
};


ROM_ASSET_LOAD_ANIM(anim_66_indices, 0x0053b91c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_66_values, 0x0053ba18, 1948, 0x00000000, 1948);

