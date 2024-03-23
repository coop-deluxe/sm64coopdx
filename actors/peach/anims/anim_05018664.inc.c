#include "pc/rom_assets.h"
// 0x050167B0
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_050167B0, 0x0016d870, 76997, 0x00016898, 7596);

// 0x0501855C
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_501855C, 0x0016d870, 76997, 0x00018644, 264);

// 0x05018664
static const struct Animation peach_seg5_anim_05018664 = {
    1,
    0,
    0,
    0,
    0x56,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_501855C),
    peach_seg5_animvalue_050167B0,
    peach_seg5_animindex_501855C,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_050167B0),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_501855C),
};
