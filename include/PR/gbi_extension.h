#pragma once

///////////////////////
// G_SETGEOMETRYMODE //
///////////////////////

#define G_LIGHT_MAP_EXT       0x00000800
#define G_LIGHTING_ENGINE_EXT 0x00004000

//////////
// DJUI //
//////////

#define G_TEXCLIP_DJUI     0xe1
#define G_TEXOVERRIDE_DJUI 0xe0
#define G_VTX_EXT          0x11
#define G_TRI2_EXT         0x12
#define G_TEXADDR_DJUI     0x13
#define G_EXECUTE_DJUI     0xdd

#define	gsSPTextureAddrDjui(c) \
{{ \
	(_SHIFTL(G_TEXADDR_DJUI,24,8)|_SHIFTL(~(u32)(c),0,24)),(u32)(0)	\
}}

#define gSetClippingDjui(pkt, cmd, x1, y1, x2, y2)         \
{                                                               \
    Gfx *_g = (Gfx *)(pkt);                                     \
    _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL( x1, 16, 8) |  \
                   _SHIFTL( y1,  8, 8) | _SHIFTL(0x00,  0, 8);   \
    _g->words.w1 = _SHIFTL(x2, 16, 8) | _SHIFTL(y2, 8, 8);      \
}

#define gSetOverrideDjui(pkt, cmd, texture, w, h, bitSize)      \
{                                                               \
    Gfx *_g = (Gfx *)(pkt);                                     \
    _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(w, 16, 8) |    \
           _SHIFTL(h, 8, 8) | _SHIFTL(bitSize, 0, 8);           \
    _g->words.w1 = (uintptr_t)(texture);                        \
}

// does not get affected by gVertexColor
#define gSPVertexNonGlobal(pkt, v, n, v0)				\
{									\
	Gfx *_g = (Gfx *)(pkt);						\
	_g->words.w0 =							\
	  _SHIFTL(G_VTX_EXT,24,8)|_SHIFTL((n),12,8)|_SHIFTL((v0)+(n),1,7);	\
	_g->words.w1 = (uintptr_t)(v);				\
}

// does not get affected by gVertexColor
#define gsSPVertexNonGlobal(v, n, v0) \
{{ \
    (_SHIFTL(G_VTX_EXT,24,8)|_SHIFTL((n),12,8)|_SHIFTL((v0)+(n),1,7)),	\
        (uintptr_t)(v)	\
}}

#define gSP2TrianglesDjui(pkt, v00, v01, v02, flag0, v10, v11, v12, flag1)	\
{									\
	Gfx *_g = (Gfx *)(pkt);						\
									\
	_g->words.w0 = (_SHIFTL(G_TRI2_EXT, 24, 8)|				\
			__gsSP1Triangle_w1f(v00, v01, v02, flag0));	\
        _g->words.w1 =  __gsSP1Triangle_w1f(v10, v11, v12, flag1); 	\
}

#define gsSPExecuteDjui(word)                                   \
{{                                                              \
    _SHIFTL(G_EXECUTE_DJUI, 24, 8), (unsigned int)(word)        \
}}

#define	gDPLoadTextureBlockWithoutTexture(pkt, timg, fmt, siz, width, height, \
        pal, cms, cmt, masks, maskt, shifts, shiftt) \
{ \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 	\
        0 , cmt, maskt, shiftt, cms, masks, shifts);		\
    gDPLoadSync(pkt);						\
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0, 				\
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT) -1,	\
        CALC_DXT(width, siz##_BYTES)); 				\
    gDPPipeSync(pkt);						\
    gDPSetTile(pkt, fmt, siz,					\
        (((width) * siz##_LINE_BYTES)+7)>>3, 0,			\
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks,	\
        shifts);						\
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,			\
        ((width)-1) << G_TEXTURE_IMAGE_FRAC,			\
        ((height)-1) << G_TEXTURE_IMAGE_FRAC)			\
}

#define gDPSetTextureClippingDjui(pkt, x1, y1, x2, y2)         gSetClippingDjui(pkt, G_TEXCLIP_DJUI, x1, y1, x2, y2)
#define gDPSetTextureOverrideDjui(pkt, texture, w, h, bitSize) gSetOverrideDjui(pkt, G_TEXOVERRIDE_DJUI, texture, w, h, bitSize)
