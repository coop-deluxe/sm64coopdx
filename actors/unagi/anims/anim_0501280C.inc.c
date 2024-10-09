#include "pc/rom_assets.h"
// 0x05011D58
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_05011D58, 0x0013b910, 41727, 0x00011d58, 2548);

// 0x0501274C
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_0501274C, 0x0013b910, 41727, 0x0001274c, 192);

// 0x0501280C
static const struct Animation unagi_seg5_anim_0501280C = {
    0,
    0,
    0,
    0,
    0x46,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_0501274C),
    unagi_seg5_animvalue_05011D58,
    unagi_seg5_animindex_0501274C,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_05011D58),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_0501274C),
};
