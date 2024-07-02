#include "pc/rom_assets.h"
// 0x06052DAC
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06052DAC, 0x00188440, 199722, 0x00052efc, 1324);

// 0x060532D8
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_060532D8, 0x00188440, 199722, 0x00053428, 540);

// 0x060534F4
static const struct Animation bowser_seg6_anim_060534F4 = {
    0,
    0,
    0,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_060532D8),
    bowser_seg6_animvalue_06052DAC,
    bowser_seg6_animindex_060532D8,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06052DAC),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_060532D8),
};
