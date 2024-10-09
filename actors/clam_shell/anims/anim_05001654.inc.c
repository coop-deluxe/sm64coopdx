#include "pc/rom_assets.h"
// 0x050015D0
ROM_ASSET_LOAD_ANIM(clam_shell_seg5_animvalue_050015D0, 0x0013b910, 41727, 0x000015d0, 72);

// 0x05001618
ROM_ASSET_LOAD_ANIM(clam_shell_seg5_animindex_05001618, 0x0013b910, 41727, 0x00001618, 60);

// 0x05001654
static const struct Animation clam_shell_seg5_anim_05001654 = {
    1,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(clam_shell_seg5_animindex_05001618),
    clam_shell_seg5_animvalue_050015D0,
    clam_shell_seg5_animindex_05001618,
    0,
    ANIM_FIELD_LENGTH(clam_shell_seg5_animvalue_050015D0),
    ANIM_FIELD_LENGTH(clam_shell_seg5_animindex_05001618),
};
