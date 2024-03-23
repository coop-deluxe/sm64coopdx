#include "pc/rom_assets.h"
// 0x0604E5B8
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604E5B8, 0x00188440, 199722, 0x0004e708, 2140);

// 0x0604EE14
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604EE14, 0x00188440, 199722, 0x0004ef64, 540);

// 0x0604F030
static const struct Animation bowser_seg6_anim_0604F030 = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604EE14),
    bowser_seg6_animvalue_0604E5B8,
    bowser_seg6_animindex_0604EE14,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604E5B8),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604EE14),
};
