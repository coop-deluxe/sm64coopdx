#include "pc/rom_assets.h"
// 0x050008E8
ROM_ASSET_LOAD_ANIM(birds_seg5_animvalue_050008E8, 0x0016d870, 76997, 0x000008e8, 136);

// 0x05000970
ROM_ASSET_LOAD_ANIM(birds_seg5_animindex_5000970, 0x0016d870, 76997, 0x00000970, 96);

// 0x050009D0
static const struct Animation birds_seg5_anim_050009D0 = {
    0,
    0,
    0,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(birds_seg5_animindex_5000970),
    birds_seg5_animvalue_050008E8,
    birds_seg5_animindex_5000970,
    0,
    ANIM_FIELD_LENGTH(birds_seg5_animvalue_050008E8),
    ANIM_FIELD_LENGTH(birds_seg5_animindex_5000970),
};
