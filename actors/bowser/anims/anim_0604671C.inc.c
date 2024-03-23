#include "pc/rom_assets.h"
// 0x06045D40
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06045D40, 0x00188440, 199722, 0x00045e90, 1984);

// 0x06046500
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06046500, 0x00188440, 199722, 0x00046650, 540);

// 0x0604671C
static const struct Animation bowser_seg6_anim_0604671C = {
    0,
    0,
    0,
    0,
    0x24,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06046500),
    bowser_seg6_animvalue_06045D40,
    bowser_seg6_animindex_06046500,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06045D40),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06046500),
};
