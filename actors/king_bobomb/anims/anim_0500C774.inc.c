#include "pc/rom_assets.h"
// 0x0500C538
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500C538, 0x00134d20, 26785, 0x0000c538, 200);

// 0x0500C600
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500C600, 0x00134d20, 26785, 0x0000c600, 372);

// 0x0500C774
static const struct Animation king_bobomb_seg5_anim_0500C774 = {
    0,
    0,
    0,
    0,
    0x04,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500C600),
    king_bobomb_seg5_animvalue_0500C538,
    king_bobomb_seg5_animindex_0500C600,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500C538),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500C600),
};
