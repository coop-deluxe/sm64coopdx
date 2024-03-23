#include "pc/rom_assets.h"
// 0x06051C80
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06051C80, 0x00188440, 199722, 0x00051dd0, 2020);

// 0x06052464
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06052464, 0x00188440, 199722, 0x000525b4, 540);

// 0x06052680
static const struct Animation bowser_seg6_anim_06052680 = {
    1,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06052464),
    bowser_seg6_animvalue_06051C80,
    bowser_seg6_animindex_06052464,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06051C80),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06052464),
};
