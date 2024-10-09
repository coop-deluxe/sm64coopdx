#include "pc/rom_assets.h"
// 0x06043700
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_06043700, 0x00188440, 199722, 0x00043850, 3280);

// 0x060443D0
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_060443D0, 0x00188440, 199722, 0x00044520, 540);

// 0x060445EC
static const struct Animation bowser_seg6_anim_060445EC = {
    0,
    0,
    0,
    0,
    0x2C,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_060443D0),
    bowser_seg6_animvalue_06043700,
    bowser_seg6_animindex_060443D0,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_06043700),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_060443D0),
};
