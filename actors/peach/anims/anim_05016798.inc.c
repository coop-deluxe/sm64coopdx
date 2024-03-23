#include "pc/rom_assets.h"
// 0x05015480
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_05015480, 0x0016d870, 76997, 0x00015568, 4624);

// 0x05016690
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_5016690, 0x0016d870, 76997, 0x00016778, 264);

// 0x05016798
static const struct Animation peach_seg5_anim_05016798 = {
    1,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_5016690),
    peach_seg5_animvalue_05015480,
    peach_seg5_animindex_5016690,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_05015480),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_5016690),
};
