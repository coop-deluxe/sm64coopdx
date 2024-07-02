#include "pc/rom_assets.h"
static const struct Animation anim_77[] = {
    0,
    189,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(anim_77_indices),
    anim_77_values,
    anim_77_indices,
    0,
    ANIM_FIELD_LENGTH(anim_77_values),
    ANIM_FIELD_LENGTH(anim_77_indices),
};


ROM_ASSET_LOAD_ANIM(anim_77_indices, 0x00542770, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_77_values, 0x0054286c, 2464, 0x00000000, 2464);

