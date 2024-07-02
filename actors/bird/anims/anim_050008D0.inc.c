#include "pc/rom_assets.h"
// 0x050007E0
ROM_ASSET_LOAD_ANIM(birds_seg5_animvalue_050007E0, 0x0016d870, 76997, 0x000007e0, 144);

// 0x05000870
ROM_ASSET_LOAD_ANIM(birds_seg5_animindex_5000870, 0x0016d870, 76997, 0x00000870, 96);

// 0x050008D0
static const struct Animation birds_seg5_anim_050008D0 = {
    0,
    0,
    0,
    0,
    0x07,
    ANIMINDEX_NUMPARTS(birds_seg5_animindex_5000870),
    birds_seg5_animvalue_050007E0,
    birds_seg5_animindex_5000870,
    0,
    ANIM_FIELD_LENGTH(birds_seg5_animvalue_050007E0),
    ANIM_FIELD_LENGTH(birds_seg5_animindex_5000870),
};
