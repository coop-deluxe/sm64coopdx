#include "pc/rom_assets.h"
// 0x06054968
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06054968, 0x00188440, 199722, 0x00054ab8, 1676);

// 0x06054FF4
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06054FF4, 0x00188440, 199722, 0x00055144, 540);

// 0x06055210
static const struct Animation bowser_seg6_anim_06055210 = {
    0,
    0,
    0,
    0,
    0x1B,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06054FF4),
    bowser_seg6_animvalue_06054968,
    bowser_seg6_animindex_06054FF4,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06054968),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06054FF4),
};
