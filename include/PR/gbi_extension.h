#pragma once

///////////////////////
// G_SETGEOMETRYMODE //
///////////////////////

#define G_LIGHT_MAP_EXT       0x00000800
#define G_LIGHTING_ENGINE_EXT 0x00004000
#define G_PACKED_NORMALS_EXT  0x00000080
#define G_CULL_INVERT_EXT     0x00000100
#define G_FRESNEL_COLOR_EXT   0x00000040
#define G_FRESNEL_ALPHA_EXT   0x00400000

//////////
// DJUI //
//////////

#define G_TEXCLIP_DJUI     0xe1
#define G_TEXOVERRIDE_DJUI 0xe0
#define G_VTX_EXT          0x11
#define G_TRI2_EXT         0x12
#define G_TEXADDR_DJUI     0x13
#define G_EXECUTE_DJUI     0xdd

#define G_MTX_INVERSE_CAMERA_EXT   0x08

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

////////////////////
// G_PPARTTOCOLOR //
////////////////////

#define G_PPARTTOCOLOR 0xd3

#define G_COL_PRIM   0x0
#define G_COL_ENV    0x1

#define G_CP_LIGHT   0x0
#define G_CP_AMBIENT 0x1

#define gSPCopyPlayerPartToColor(pkt, color, part, offset)             \
{                                                                \
    Gfx *_g = (Gfx *)(pkt);                                      \
    _g->words.w0 = (_SHIFTL(G_PPARTTOCOLOR, 24, 8)) | (_SHIFTL(color, 16, 8)); \
    _g->words.w1 = ((2 * ((part) + 1)) + 1 + offset);            \
}

#define gsSPCopyPlayerPartToColor(color, part, offset)                     \
{{                                                                   \
    (_SHIFTL(G_PPARTTOCOLOR, 24, 8)) | (_SHIFTL(color, 16, 8)),        \
    ((2 * ((part) + 1)) + 1 + offset)                                \
}}

////////////////////
//// G_MOVEWORD ////
////////////////////

#define G_MW_FX                  0x00 /* replaces G_MW_MATRIX which is no longer supported */
#define G_MWO_FRESNEL            0x0C

/**
 * Fresnel - Feature suggested by thecozies
 * Enabled with the G_FRESNEL bit in geometry mode.
 * The dot product between a vertex normal and the vector from the vertex to the
 * camera is computed. The offset and scale here convert this to a shade alpha
 * value. This is useful for making surfaces fade between transparent when
 * viewed straight-on and opaque when viewed at a large angle, or for applying a
 * fake "outline" around the border of meshes.
 * 
 * If using Fresnel, you need to set the camera world position whenever you set
 * the VP matrix, viewport, etc. See SPCameraWorld.
 * 
 * The RSP does:
 * s16 dotProduct = dot(vertex normal, camera pos - vertex pos);
 * dotProduct = abs(dotProduct); // 0 = points to side, 7FFF = points at or away
 * s32 factor = ((scale * dotProduct) >> 15) + offset;
 * s16 result = clamp(factor << 8, 0, 7FFF);
 * color_or_alpha = result >> 7;
 * 
 * At dotMax, color_or_alpha = FF, result = 7F80, factor = 7F
 * At dotMin, color_or_alpha = 00, result = 0, factor = 0
 * 7F = ((scale * dotMax) >> 15) + offset
 * 00 = ((scale * dotMin) >> 15) + offset
 * Subtract: 7F = (scale * (dotMax - dotMin)) >> 15
 *           3F8000 = scale * (dotMax - dotMin)
 *           scale = 3F8000 / (dotMax - dotMin)                <--
 * offset = -(((3F8000 / (dotMax - dotMin)) * dotMin) >> 15)
 * offset = -((7F * dotMin) / (dotMax - dotMin))               <--
 * 
 * To convert in the opposite direction:
 * ((7F - offset) << 15) / scale = dotMax
 * ((00 - offset) << 15) / scale = dotMin
 */
#define gSPFresnel(pkt, scale, offset) \
    gMoveWd(pkt, G_MW_FX, G_MWO_FRESNEL, \
        (_SHIFTL((scale), 16, 16) | _SHIFTL((offset), 0, 16)))
#define gsSPFresnel(scale, offset) \
    gsMoveWd(G_MW_FX, G_MWO_FRESNEL, \
        (_SHIFTL((scale), 16, 16) | _SHIFTL((offset), 0, 16)))
