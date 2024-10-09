#include "pc/rom_assets.h"
// 0x05012F58
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_05012F58, 0x0016d870, 76997, 0x00013040, 9224);

// 0x05015360
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_5015360, 0x0016d870, 76997, 0x00015448, 264);

// 0x05015468
static const struct Animation peach_seg5_anim_05015468 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_5015360),
    peach_seg5_animvalue_05012F58,
    peach_seg5_animindex_5015360,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_05012F58),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_5015360),
};
