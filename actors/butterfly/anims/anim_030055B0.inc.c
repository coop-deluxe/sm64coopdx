#include "pc/rom_assets.h"
// 0x03005538
ROM_ASSET_LOAD_ANIM(butterfly_seg3_animvalue_03005538, 0x00201410, 96653, 0x00005538, 36);

// 0x0300555C
ROM_ASSET_LOAD_ANIM(butterfly_seg3_animindex_0300555C, 0x00201410, 96653, 0x0000555c, 84);

// 0x030055B0
static const struct Animation butterfly_seg3_anim_030055B0 = {
    0,
    0,
    7,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(butterfly_seg3_animindex_0300555C),
    butterfly_seg3_animvalue_03005538,
    butterfly_seg3_animindex_0300555C,
    0,
    ANIM_FIELD_LENGTH(butterfly_seg3_animvalue_03005538),
    ANIM_FIELD_LENGTH(butterfly_seg3_animindex_0300555C),
};
