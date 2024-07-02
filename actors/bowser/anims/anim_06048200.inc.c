#include "pc/rom_assets.h"
// 0x06046774
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06046774, 0x00188440, 199722, 0x000468c4, 6256);

// 0x06047FE4
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06047FE4, 0x00188440, 199722, 0x00048134, 540);

// 0x06048200
static const struct Animation bowser_seg6_anim_06048200 = {
    0,
    0,
    0,
    0,
    0x4C,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06047FE4),
    bowser_seg6_animvalue_06046774,
    bowser_seg6_animindex_06047FE4,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06046774),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06047FE4),
};
