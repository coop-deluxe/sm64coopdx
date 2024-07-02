#include "pc/rom_assets.h"
// 0x0604A8FC
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604A8FC, 0x00188440, 199722, 0x0004aa4c, 1632);

// 0x0604AF5C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604AF5C, 0x00188440, 199722, 0x0004b0ac, 540);

// 0x0604B178
static const struct Animation bowser_seg6_anim_0604B178 = {
    0,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604AF5C),
    bowser_seg6_animvalue_0604A8FC,
    bowser_seg6_animindex_0604AF5C,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604A8FC),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604AF5C),
};
