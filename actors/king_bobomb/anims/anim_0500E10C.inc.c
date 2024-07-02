#include "pc/rom_assets.h"
// 0x0500DDF0
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animvalue_0500DDF0, 0x00134d20, 26785, 0x0000ddf0, 424);

// 0x0500DF98
ROM_ASSET_LOAD_ANIM(king_bobomb_seg5_animindex_0500DF98, 0x00134d20, 26785, 0x0000df98, 372);

// 0x0500E10C
static const struct Animation king_bobomb_seg5_anim_0500E10C = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(king_bobomb_seg5_animindex_0500DF98),
    king_bobomb_seg5_animvalue_0500DDF0,
    king_bobomb_seg5_animindex_0500DF98,
    0,
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animvalue_0500DDF0),
    ANIM_FIELD_LENGTH(king_bobomb_seg5_animindex_0500DF98),
};
