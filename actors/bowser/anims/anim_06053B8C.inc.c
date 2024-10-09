#include "pc/rom_assets.h"
// 0x0605350C
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0605350C, 0x00188440, 199722, 0x0005365c, 1124);

// 0x06053970
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_06053970, 0x00188440, 199722, 0x00053ac0, 540);

// 0x06053B8C
static const struct Animation bowser_seg6_anim_06053B8C = {
    0,
    0,
    0,
    0,
    0x11,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_06053970),
    bowser_seg6_animvalue_0605350C,
    bowser_seg6_animindex_06053970,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0605350C),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_06053970),
};
