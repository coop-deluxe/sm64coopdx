#include "pc/rom_assets.h"
// 0x0500EDAC
ROM_ASSET_LOAD_ANIM(peach_seg5_animvalue_0500EDAC, 0x0016d870, 76997, 0x0000ee94, 1472);

// 0x0500F36C
ROM_ASSET_LOAD_ANIM(peach_seg5_animindex_500F36C, 0x0016d870, 76997, 0x0000ed74, 264);

// 0x0500F474
static const struct Animation peach_seg5_anim_0500F474 = {
    1,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(peach_seg5_animindex_500F36C),
    peach_seg5_animvalue_0500EDAC,
    peach_seg5_animindex_500F36C,
    0,
    ANIM_FIELD_LENGTH(peach_seg5_animvalue_0500EDAC),
    ANIM_FIELD_LENGTH(peach_seg5_animindex_500F36C),
};
