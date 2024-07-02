#include "pc/rom_assets.h"
// 0x0500166C
ROM_ASSET_LOAD_ANIM(clam_shell_seg5_animvalue_0500166C, 0x0013b910, 41727, 0x0000166c, 132);

// 0x050016F0
ROM_ASSET_LOAD_ANIM(clam_shell_seg5_animindex_050016F0, 0x0013b910, 41727, 0x000016f0, 60);

// 0x0500172C
static const struct Animation clam_shell_seg5_anim_0500172C = {
    1,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(clam_shell_seg5_animindex_050016F0),
    clam_shell_seg5_animvalue_0500166C,
    clam_shell_seg5_animindex_050016F0,
    0,
    ANIM_FIELD_LENGTH(clam_shell_seg5_animvalue_0500166C),
    ANIM_FIELD_LENGTH(clam_shell_seg5_animindex_050016F0),
};
