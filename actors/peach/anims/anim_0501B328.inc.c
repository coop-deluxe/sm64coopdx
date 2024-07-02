#include "pc/rom_assets.h"
// 0x0501867C
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0501867C, 0x0016d870, 76997, 0x00018764, 11172);

// 0x0501B220
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_501B220, 0x0016d870, 76997, 0x0001b308, 264);

// 0x0501B328
static const struct Animation peach_seg5_anim_0501B328 = {
    1,
    0,
    0,
    0,
    0x88,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_501B220),
    peach_seg5_animvalue_0501867C,
    peach_seg5_animindex_501B220,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0501867C),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_501B220),
};
