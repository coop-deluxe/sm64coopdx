#include "pc/rom_assets.h"
// 0x0604FF64
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604FF64, 0x00188440, 199722, 0x000500b4, 944);

// 0x06050314
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06050314, 0x00188440, 199722, 0x00050464, 540);

// 0x06050530
static const struct Animation bowser_seg6_anim_06050530 = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06050314),
    bowser_seg6_animvalue_0604FF64,
    bowser_seg6_animindex_06050314,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604FF64),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06050314),
};
