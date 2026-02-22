#pragma once

//
// GFX COMMANDS FREE SLOTS
//
// The following op codes are free to use for G_ commands.
// For RSP commands, use incrementing numbers starting from 00.
// For RDP commands, use decrementing numbers starting from ff.
// Please update the following table when implementing a new command.
//
// RSP ->                     09 0a 0b 0c 0d 0e 0f
// 10          14 15 16 17 18 19 1a 1b 1c 1d 1e 1f
// 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f
// 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f
// 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f
// 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f
// 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f
// 70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f
// 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
// 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f
// a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af
// b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf
// c0 c1 c2 c3 c4 c5 c6 c7                        
// d0                                       <- RDP
//
//

///////////////////////
// G_SETGEOMETRYMODE //
///////////////////////

//
// GEOMETRY MODES FREE FLAGS
//
// The following flags are free to use for geometry modes.
// Please remove the corresponding flag from the list below when implementing a new geometry mode.
// Note: geometry mode flags have only 24 bits, the 8 upper bits cannot be used.
//
// 0x00000002
// 0x00000008
// 0x00000010
// 0x00000020
// 0x00001000
// 0x00002000
// 0x00008000
// 0x00080000 // G_TEXTURE_GEN_LINEAR, but not implemented
// 0x00100000 // G_LOD, but not implemented
// 0x00800000 // G_CLIPPING, but not implemented

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

#define gSetOverrideDjui(pkt, cmd, texture, w, h, fmt, siz)     \
{                                                               \
    Gfx *_g = (Gfx *)(pkt);                                     \
    _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(w, 16, 8) |    \
           _SHIFTL(h, 8, 8) | _SHIFTL(fmt, 4, 4) | _SHIFTL(siz, 0, 4); \
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

#define gDPSetTextureClippingDjui(pkt, x1, y1, x2, y2)          gSetClippingDjui(pkt, G_TEXCLIP_DJUI, x1, y1, x2, y2)
#define gDPSetTextureOverrideDjui(pkt, texture, w, h, fmt, siz) gSetOverrideDjui(pkt, G_TEXOVERRIDE_DJUI, texture, w, h, fmt, siz)

/////////////////
// G_SETENVRGB //
/////////////////

#define G_SETENVRGB		0xd1

#define	gDPSetEnvRGB(pkt, r, g, b)					\
            DPRGBColor(pkt, G_SETENVRGB, r,g,b,255)
#define	gsDPSetEnvRGB(r, g, b)					\
            sDPRGBColor(G_SETENVRGB, r,g,b,255)

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

////////////////
// G_MOVEWORD //
////////////////

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
