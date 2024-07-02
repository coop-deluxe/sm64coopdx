#include "pc/rom_assets.h"
// 0x0604B190
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604B190, 0x00188440, 199722, 0x0004b2e0, 1312);

// 0x0604B6B0
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604B6B0, 0x00188440, 199722, 0x0004b800, 540);

// 0x0604B8CC
static const struct Animation bowser_seg6_anim_0604B8CC = {
    1,
    0,
    0,
    0,
    0x10,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604B6B0),
    bowser_seg6_animvalue_0604B190,
    bowser_seg6_animindex_0604B6B0,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604B190),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604B6B0),
};
