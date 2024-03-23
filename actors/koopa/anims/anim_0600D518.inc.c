#include "pc/rom_assets.h"
// 0x0600CFD0
ROM_ASSET_LOAD_ANIM(koopa_seg6_animvalue_0600CFD0, 0x001c4230, 80474, 0x0000cfd0, 1160);

// 0x0600D458
ROM_ASSET_LOAD_ANIM(koopa_seg6_animindex_0600D458, 0x001c4230, 80474, 0x0000d458, 192);

// 0x0600D518
static const struct Animation koopa_seg6_anim_0600D518 = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(koopa_seg6_animindex_0600D458),
    koopa_seg6_animvalue_0600CFD0,
    koopa_seg6_animindex_0600D458,
    0,
    ANIM_FIELD_LENGTH(koopa_seg6_animvalue_0600CFD0),
    ANIM_FIELD_LENGTH(koopa_seg6_animindex_0600D458),
};
