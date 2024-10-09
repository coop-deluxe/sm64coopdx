#include "pc/rom_assets.h"
// 0x050042BC
ROM_ASSET_LOAD_ANIM(bully_seg5_animvalue_050042BC, 0x00132c60, 7692, 0x000042bc, 116);

// 0x05004330
ROM_ASSET_LOAD_ANIM(bully_seg5_animindex_05004330, 0x00132c60, 7692, 0x00004330, 168);

// 0x050043D8
static const struct Animation bully_seg5_anim_050043D8 = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(bully_seg5_animindex_05004330),
    bully_seg5_animvalue_050042BC,
    bully_seg5_animindex_05004330,
    0,
    ANIM_FIELD_LENGTH(bully_seg5_animvalue_050042BC),
    ANIM_FIELD_LENGTH(bully_seg5_animindex_05004330),
};
