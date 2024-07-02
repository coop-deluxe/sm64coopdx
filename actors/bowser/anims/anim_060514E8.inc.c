#include "pc/rom_assets.h"
// 0x06050548
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06050548, 0x00188440, 199722, 0x00050698, 3460);

// 0x060512CC
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_060512CC, 0x00188440, 199722, 0x0005141c, 540);

// 0x060514E8
static const struct Animation bowser_seg6_anim_060514E8 = {
    0,
    0,
    0,
    0,
    0x2C,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_060512CC),
    bowser_seg6_animvalue_06050548,
    bowser_seg6_animindex_060512CC,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06050548),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_060512CC),
};
