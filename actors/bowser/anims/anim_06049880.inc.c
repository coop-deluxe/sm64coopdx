#include "pc/rom_assets.h"
// 0x06048218
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06048218, 0x00188440, 199722, 0x00048368, 5196);

// 0x06049664
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06049664, 0x00188440, 199722, 0x000497b4, 540);

// 0x06049880
static const struct Animation bowser_seg6_anim_06049880 = {
    0,
    0,
    0,
    0,
    0x5C,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06049664),
    bowser_seg6_animvalue_06048218,
    bowser_seg6_animindex_06049664,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06048218),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06049664),
};
