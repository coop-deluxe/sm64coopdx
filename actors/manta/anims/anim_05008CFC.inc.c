#include "pc/rom_assets.h"
// 0x05006CA0
ROM_ASSET_LOAD_ANIM(manta_seg5_animvalue_05006CA0, 0x0013b910, 41727, 0x00006ca0, 7996);

// 0x05008BDC
ROM_ASSET_LOAD_ANIM(manta_seg5_animindex_05008BDC, 0x0013b910, 41727, 0x00008bdc, 288);

// 0x05008CFC
static const struct Animation manta_seg5_anim_05008CFC = {
    0,
    0,
    0,
    0,
    0xC7,
    ANIMINDEX_NUMPARTS(manta_seg5_animindex_05008BDC),
    manta_seg5_animvalue_05006CA0,
    manta_seg5_animindex_05008BDC,
    0,
    ANIM_FIELD_LENGTH(manta_seg5_animvalue_05006CA0),
    ANIM_FIELD_LENGTH(manta_seg5_animindex_05008BDC),
};
