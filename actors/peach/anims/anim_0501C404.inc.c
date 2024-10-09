#include "pc/rom_assets.h"
// 0x0501B340
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0501B340, 0x0016d870, 76997, 0x0001b428, 4028);

// 0x0501C2FC
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_501C2FC, 0x0016d870, 76997, 0x0001c3e4, 264);

// 0x0501C404
static const struct Animation peach_seg5_anim_0501C404 = {
    0,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_501C2FC),
    peach_seg5_animvalue_0501B340,
    peach_seg5_animindex_501C2FC,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0501B340),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_501C2FC),
};
