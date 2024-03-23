#include "pc/rom_assets.h"
// 0x060542A8
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_060542A8, 0x00188440, 199722, 0x000543f8, 1164);

// 0x06054734
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06054734, 0x00188440, 199722, 0x00054884, 540);

// 0x06054950
static const struct Animation bowser_seg6_anim_06054950 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06054734),
    bowser_seg6_animvalue_060542A8,
    bowser_seg6_animindex_06054734,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_060542A8),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06054734),
};
