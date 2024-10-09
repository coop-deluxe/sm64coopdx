#include "pc/rom_assets.h"
// 0x050114A0
ROM_ASSET_LOAD_ANIM(unagi_seg5_animvalue_050114A0, 0x0013b910, 41727, 0x000114a0, 816);

// 0x050117D0
ROM_ASSET_LOAD_ANIM(unagi_seg5_animindex_050117D0, 0x0013b910, 41727, 0x000117d0, 192);

// 0x05011890
static const struct Animation unagi_seg5_anim_05011890 = {
    1,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(unagi_seg5_animindex_050117D0),
    unagi_seg5_animvalue_050114A0,
    unagi_seg5_animindex_050117D0,
    0,
    ANIM_FIELD_LENGTH(unagi_seg5_animvalue_050114A0),
    ANIM_FIELD_LENGTH(unagi_seg5_animindex_050117D0),
};
