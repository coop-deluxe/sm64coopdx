#include "pc/rom_assets.h"
// 0x05016A58
ROM_ASSET_LOAD_ANIM(spiny_seg5_animvalue_05016A58, 0x00180bb0, 29674, 0x00016a58, 844);

// 0x05016DA4
ROM_ASSET_LOAD_ANIM(spiny_seg5_animindex_05016DA4, 0x00180bb0, 29674, 0x00016da4, 240);

// 0x05016E94
static const struct Animation spiny_seg5_anim_05016E94 = {
    0,
    0,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(spiny_seg5_animindex_05016DA4),
    spiny_seg5_animvalue_05016A58,
    spiny_seg5_animindex_05016DA4,
    0,
    ANIM_FIELD_LENGTH(spiny_seg5_animvalue_05016A58),
    ANIM_FIELD_LENGTH(spiny_seg5_animindex_05016DA4),
};
