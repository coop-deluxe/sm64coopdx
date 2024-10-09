#include "pc/rom_assets.h"
// 0x06052698
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06052698, 0x00188440, 199722, 0x000527e8, 1248);

// 0x06052B78
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06052B78, 0x00188440, 199722, 0x00052cc8, 540);

// 0x06052D94
static const struct Animation bowser_seg6_anim_06052D94 = {
    0,
    0,
    0,
    0,
    0x13,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06052B78),
    bowser_seg6_animvalue_06052698,
    bowser_seg6_animindex_06052B78,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06052698),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06052B78),
};
