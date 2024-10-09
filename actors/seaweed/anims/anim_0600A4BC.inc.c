#include "pc/rom_assets.h"
// 0x0600A1F0
ROM_ASSET_LOAD_ANIM(seaweed_seg6_animvalue_0600A1F0, 0x001b9cc0, 41188, 0x0000a1f0, 644);

// 0x0600A474
ROM_ASSET_LOAD_ANIM(seaweed_seg6_animindex_0600A474, 0x001b9cc0, 41188, 0x0000a474, 72);

// 0x0600A4BC
static const struct Animation seaweed_seg6_anim_0600A4BC = {
    0,
    0,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(seaweed_seg6_animindex_0600A474),
    seaweed_seg6_animvalue_0600A1F0,
    seaweed_seg6_animindex_0600A474,
    0,
    ANIM_FIELD_LENGTH(seaweed_seg6_animvalue_0600A1F0),
    ANIM_FIELD_LENGTH(seaweed_seg6_animindex_0600A474),
};
