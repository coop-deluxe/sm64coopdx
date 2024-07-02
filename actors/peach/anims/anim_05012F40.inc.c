#include "pc/rom_assets.h"
// 0x05011068
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_05011068, 0x0016d870, 76997, 0x00011150, 7632);

// 0x05012E38
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_5012E38, 0x0016d870, 76997, 0x00012f20, 264);

// 0x05012F40
static const struct Animation peach_seg5_anim_05012F40 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_5012E38),
    peach_seg5_animvalue_05011068,
    peach_seg5_animindex_5012E38,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_05011068),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_5012E38),
};
