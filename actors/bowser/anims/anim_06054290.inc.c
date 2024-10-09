#include "pc/rom_assets.h"
// 0x06053BA4
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06053BA4, 0x00188440, 199722, 0x00053cf4, 1232);

// 0x06054074
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06054074, 0x00188440, 199722, 0x000541c4, 540);

// 0x06054290
static const struct Animation bowser_seg6_anim_06054290 = {
    0,
    0,
    0,
    0,
    0x17,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06054074),
    bowser_seg6_animvalue_06053BA4,
    bowser_seg6_animindex_06054074,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06053BA4),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06054074),
};
