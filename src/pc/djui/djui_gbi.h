#pragma once

#define G_TEXCLIP_DJUI     0xe1
#define G_TEXOVERRIDE_DJUI 0xe0
#define G_EXECUTE_DJUI     0xdd

#define gSetClippingDjui(pkt, cmd, rot, x1, y1, x2, y2)         \
{                                                               \
    Gfx *_g = (Gfx *)(pkt);                                     \
    _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL( x1, 16, 8) |  \
                   _SHIFTL( y1,  8, 8) | _SHIFTL(rot,  0, 8);   \
    _g->words.w1 = _SHIFTL(x2, 16, 8) | _SHIFTL(y2, 8, 8);      \
}

#define gSetOverrideDjui(pkt, cmd, texture, w, h, bitSize)      \
{                                                               \
    Gfx *_g = (Gfx *)(pkt);                                     \
    _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(w, 16, 8) |    \
           _SHIFTL(h, 8, 8) | _SHIFTL(bitSize, 0, 8);           \
    _g->words.w1 = (uintptr_t)(texture);                        \
}

#define gsSPExecuteDjui(word)                                   \
{{                                                              \
    _SHIFTL(G_EXECUTE_DJUI, 24, 8), (unsigned int)(word)        \
}}

#define gDPSetTextureClippingDjui(pkt, rot, x1, y1, x2, y2)    gSetClippingDjui(pkt, G_TEXCLIP_DJUI, rot, x1, y1, x2, y2)
#define gDPSetTextureOverrideDjui(pkt, texture, w, h, bitSize) gSetOverrideDjui(pkt, G_TEXOVERRIDE_DJUI, texture, w, h, bitSize)
