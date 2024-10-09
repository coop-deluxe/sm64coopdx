#include "pc/rom_assets.h"
// 0x0604D19C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604D19C, 0x00188440, 199722, 0x0004d2ec, 4584);

// 0x0604E384
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604E384, 0x00188440, 199722, 0x0004e4d4, 540);

// 0x0604E5A0
static const struct Animation bowser_seg6_anim_0604E5A0 = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604E384),
    bowser_seg6_animvalue_0604D19C,
    bowser_seg6_animindex_0604E384,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604D19C),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604E384),
};
