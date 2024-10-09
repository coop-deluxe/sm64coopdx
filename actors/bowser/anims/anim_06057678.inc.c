#include "pc/rom_assets.h"
// 0x0605678C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0605678C, 0x00188440, 199722, 0x000568dc, 3280);

// 0x0605745C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0605745C, 0x00188440, 199722, 0x00044520, 540);

// 0x06057678
static const struct Animation bowser_seg6_anim_06057678 = {
    0,
    0,
    0,
    0,
    0x2C,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0605745C),
    bowser_seg6_animvalue_0605678C,
    bowser_seg6_animindex_0605745C,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0605678C),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0605745C),
};
