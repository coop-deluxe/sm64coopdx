#include "pc/rom_assets.h"
// 0x0605599C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0605599C, 0x00188440, 199722, 0x00055aec, 3004);

// 0x06056558
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06056558, 0x00188440, 199722, 0x000566a8, 540);

// 0x06056774
static const struct Animation bowser_seg6_anim_06056774 = {
    0,
    0,
    0,
    0,
    0x2D,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06056558),
    bowser_seg6_animvalue_0605599C,
    bowser_seg6_animindex_06056558,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0605599C),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06056558),
};
