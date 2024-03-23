#include "pc/rom_assets.h"
// 0x050227D8
ROM_ASSET_LOAD_ANIM(yoshi_seg5_animvalue_050227D8, 0x0016d870, 76997, 0x000228c0, 2720);

// 0x05023278
ROM_ASSET_LOAD_ANIM(yoshi_seg5_animindex_5023278, 0x0016d870, 76997, 0x00023360, 300);

// 0x050233A4
static const struct Animation yoshi_seg5_anim_050233A4 = {
    0,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(yoshi_seg5_animindex_5023278),
    yoshi_seg5_animvalue_050227D8,
    yoshi_seg5_animindex_5023278,
    0,
    ANIM_FIELD_LENGTH(yoshi_seg5_animvalue_050227D8),
    ANIM_FIELD_LENGTH(yoshi_seg5_animindex_5023278),
};
