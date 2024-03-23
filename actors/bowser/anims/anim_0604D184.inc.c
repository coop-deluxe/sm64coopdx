#include "pc/rom_assets.h"
// 0x0604B8E4
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604B8E4, 0x00188440, 199722, 0x0004ba34, 5764);

// 0x0604CF68
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604CF68, 0x00188440, 199722, 0x0004d0b8, 540);

// 0x0604D184
static const struct Animation bowser_seg6_anim_0604D184 = {
    0,
    0,
    0,
    0,
    0x46,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604CF68),
    bowser_seg6_animvalue_0604B8E4,
    bowser_seg6_animindex_0604CF68,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604B8E4),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604CF68),
};
