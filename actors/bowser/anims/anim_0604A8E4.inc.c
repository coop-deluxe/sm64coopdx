#include "pc/rom_assets.h"
// 0x06049898
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06049898, 0x00188440, 199722, 0x000499e8, 3632);

// 0x0604A6C8
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604A6C8, 0x00188440, 199722, 0x0004a818, 540);

// 0x0604A8E4
static const struct Animation bowser_seg6_anim_0604A8E4 = {
    0,
    0,
    0,
    0,
    0x2D,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604A6C8),
    bowser_seg6_animvalue_06049898,
    bowser_seg6_animindex_0604A6C8,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06049898),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604A6C8),
};
