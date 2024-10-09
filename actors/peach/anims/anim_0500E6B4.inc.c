#include "pc/rom_assets.h"
// 0x0500C650
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0500C650, 0x0016d870, 76997, 0x0000c738, 8028);

// 0x0500E5AC
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_500E5AC, 0x0016d870, 76997, 0x0000e694, 264);

// 0x0500E6B4
static const struct Animation peach_seg5_anim_0500E6B4 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_500E5AC),
    peach_seg5_animvalue_0500C650,
    peach_seg5_animindex_500E5AC,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0500C650),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_500E5AC),
};
