#include "pc/rom_assets.h"
// 0x08023814
ROM_ASSET_LOAD_ANIM(bobomb_seg8_animvalue_08023814, 0x001f2200, 59076, 0x00023814, 152);

// 0x080238AC
ROM_ASSET_LOAD_ANIM(bobomb_seg8_animindex_080238AC, 0x001f2200, 59076, 0x000238ac, 168);

// 0x08023954
static const struct Animation bobomb_seg8_anim_08023954 = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(bobomb_seg8_animindex_080238AC),
    bobomb_seg8_animvalue_08023814,
    bobomb_seg8_animindex_080238AC,
    0,
    ANIM_FIELD_LENGTH(bobomb_seg8_animvalue_08023814),
    ANIM_FIELD_LENGTH(bobomb_seg8_animindex_080238AC),
};
