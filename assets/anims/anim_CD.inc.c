#include "pc/rom_assets.h"
static const struct Animation anim_CD[] = {
    1,
    189,
    0,
    0,
    0x3F,
    ANIMINDEX_NUMPARTS(anim_CD_indices),
    anim_CD_values,
    anim_CD_indices,
    0,
    ANIM_FIELD_LENGTH(anim_CD_values),
    ANIM_FIELD_LENGTH(anim_CD_indices),
};


ROM_ASSET_LOAD_ANIM(anim_CD_indices, 0x0057707c, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_CD_values, 0x00577178, 5184, 0x00000000, 5184);

