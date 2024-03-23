#include "pc/rom_assets.h"
// 0x06046734
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06046734, 0x00188440, 199722, 0x00046884, 16);

// 0x06046744
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06046744, 0x00188440, 199722, 0x00046894, 24);

// 0x0604675C
static const struct Animation bowser_seg6_anim_0604675C = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06046744),
    bowser_seg6_animvalue_06046734,
    bowser_seg6_animindex_06046744,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06046734),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06046744),
};
