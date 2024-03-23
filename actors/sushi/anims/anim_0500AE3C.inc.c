#include "pc/rom_assets.h"
// 0x0500AA00
ROM_ASSET_LOAD_ANIM(sushi_seg5_animvalue_0500AA00, 0x0013b910, 41727, 0x0000aa00, 988);

// 0x0500ADDC
ROM_ASSET_LOAD_ANIM(sushi_seg5_animindex_0500ADDC, 0x0013b910, 41727, 0x0000addc, 96);

// 0x0500AE3C
static const struct Animation sushi_seg5_anim_0500AE3C = {
    0,
    0,
    0,
    0,
    0x46,
    ANIMINDEX_NUMPARTS(sushi_seg5_animindex_0500ADDC),
    sushi_seg5_animvalue_0500AA00,
    sushi_seg5_animindex_0500ADDC,
    0,
    ANIM_FIELD_LENGTH(sushi_seg5_animvalue_0500AA00),
    ANIM_FIELD_LENGTH(sushi_seg5_animindex_0500ADDC),
};
