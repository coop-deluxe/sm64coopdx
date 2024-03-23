#include "pc/rom_assets.h"
// 0x060453E0
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_060453E0, 0x00188440, 199722, 0x00045530, 1836);

// 0x06045B0C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06045B0C, 0x00188440, 199722, 0x00045c5c, 540);

// 0x06045D28
static const struct Animation bowser_seg6_anim_06045D28 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06045B0C),
    bowser_seg6_animvalue_060453E0,
    bowser_seg6_animindex_06045B0C,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_060453E0),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06045B0C),
};
