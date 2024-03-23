#include "pc/rom_assets.h"
// 0x06051500
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06051500, 0x00188440, 199722, 0x00051650, 1356);

// 0x06051A4C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06051A4C, 0x00188440, 199722, 0x00051b9c, 540);

// 0x06051C68
static const struct Animation bowser_seg6_anim_06051C68 = {
    1,
    0,
    0,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06051A4C),
    bowser_seg6_animvalue_06051500,
    bowser_seg6_animindex_06051A4C,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06051500),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06051A4C),
};
