#include "pc/rom_assets.h"
// 0x0801D770
ROM_ASSET_LOAD_ANIM(goomba_seg8_animvalue_0801D770, 0x001f2200, 59076, 0x0001d770, 612);

// 0x0801D9D4
ROM_ASSET_LOAD_ANIM(goomba_seg8_animindex_0801D9D4, 0x001f2200, 59076, 0x0001d9d4, 96);

// 0x0801DA34
static const struct Animation goomba_seg8_anim_0801DA34 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(goomba_seg8_animindex_0801D9D4),
    goomba_seg8_animvalue_0801D770,
    goomba_seg8_animindex_0801D9D4,
    0,
    ANIM_FIELD_LENGTH(goomba_seg8_animvalue_0801D770),
    ANIM_FIELD_LENGTH(goomba_seg8_animindex_0801D9D4),
};
