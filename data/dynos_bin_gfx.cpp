#include "dynos.cpp.h"
extern "C" {
#include <assert.h>
#include "sm64.h"
#include "include/textures.h"
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

#define DISPLAY_LIST_SIZE_PER_TOKEN 4

  /////////////
 // Parsing //
/////////////

#define gfx_constant(x) if (_Arg == #x) { return (s64) (x); }

s64 DynOS_Gfx_ParseGfxConstants(const String& _Arg, bool* found) {
    *found = true;

    // Constants
    gfx_constant(NULL);
    gfx_constant(G_ON);
    gfx_constant(G_OFF);

    // Combine modes
    gfx_constant(G_CCMUX_COMBINED);
    gfx_constant(G_CCMUX_TEXEL0);
    gfx_constant(G_CCMUX_TEXEL1);
    gfx_constant(G_CCMUX_PRIMITIVE);
    gfx_constant(G_CCMUX_SHADE);
    gfx_constant(G_CCMUX_ENVIRONMENT);
    gfx_constant(G_CCMUX_CENTER);
    gfx_constant(G_CCMUX_SCALE);
    gfx_constant(G_CCMUX_COMBINED_ALPHA);
    gfx_constant(G_CCMUX_TEXEL0_ALPHA);
    gfx_constant(G_CCMUX_TEXEL1_ALPHA);
    gfx_constant(G_CCMUX_PRIMITIVE_ALPHA);
    gfx_constant(G_CCMUX_SHADE_ALPHA);
    gfx_constant(G_CCMUX_ENV_ALPHA);
    gfx_constant(G_CCMUX_LOD_FRACTION);
    gfx_constant(G_CCMUX_PRIM_LOD_FRAC);
    gfx_constant(G_CCMUX_NOISE);
    gfx_constant(G_CCMUX_K4);
    gfx_constant(G_CCMUX_K5);
    gfx_constant(G_CCMUX_1);
    gfx_constant(G_CCMUX_0);
    gfx_constant(G_ACMUX_COMBINED);
    gfx_constant(G_ACMUX_TEXEL0);
    gfx_constant(G_ACMUX_TEXEL1);
    gfx_constant(G_ACMUX_PRIMITIVE);
    gfx_constant(G_ACMUX_SHADE);
    gfx_constant(G_ACMUX_ENVIRONMENT);
    gfx_constant(G_ACMUX_LOD_FRACTION);
    gfx_constant(G_ACMUX_PRIM_LOD_FRAC);
    gfx_constant(G_ACMUX_1);
    gfx_constant(G_ACMUX_0);

    // Light constants
    gfx_constant(NUMLIGHTS_0);
    gfx_constant(NUMLIGHTS_1);
    gfx_constant(NUMLIGHTS_2);
    gfx_constant(NUMLIGHTS_3);
    gfx_constant(NUMLIGHTS_4);
    gfx_constant(NUMLIGHTS_5);
    gfx_constant(NUMLIGHTS_6);
    gfx_constant(NUMLIGHTS_7);

    // Image formats
    gfx_constant(G_IM_FMT_RGBA);
    gfx_constant(G_IM_FMT_YUV);
    gfx_constant(G_IM_FMT_CI);
    gfx_constant(G_IM_FMT_IA);
    gfx_constant(G_IM_FMT_I);
    gfx_constant(G_IM_SIZ_4b);
    gfx_constant(G_IM_SIZ_8b);
    gfx_constant(G_IM_SIZ_16b);
    gfx_constant(G_IM_SIZ_32b);
    gfx_constant(G_IM_SIZ_DD);

    // Image constants
    gfx_constant(G_IM_SIZ_4b_BYTES);
    gfx_constant(G_IM_SIZ_4b_TILE_BYTES);
    gfx_constant(G_IM_SIZ_4b_LINE_BYTES);
    gfx_constant(G_IM_SIZ_8b_BYTES);
    gfx_constant(G_IM_SIZ_8b_TILE_BYTES);
    gfx_constant(G_IM_SIZ_8b_LINE_BYTES);
    gfx_constant(G_IM_SIZ_16b_BYTES);
    gfx_constant(G_IM_SIZ_16b_TILE_BYTES);
    gfx_constant(G_IM_SIZ_16b_LINE_BYTES);
    gfx_constant(G_IM_SIZ_32b_BYTES);
    gfx_constant(G_IM_SIZ_32b_TILE_BYTES);
    gfx_constant(G_IM_SIZ_32b_LINE_BYTES);
    gfx_constant(G_IM_SIZ_4b_LOAD_BLOCK);
    gfx_constant(G_IM_SIZ_8b_LOAD_BLOCK);
    gfx_constant(G_IM_SIZ_16b_LOAD_BLOCK);
    gfx_constant(G_IM_SIZ_32b_LOAD_BLOCK);
    gfx_constant(G_IM_SIZ_4b_SHIFT);
    gfx_constant(G_IM_SIZ_8b_SHIFT);
    gfx_constant(G_IM_SIZ_16b_SHIFT);
    gfx_constant(G_IM_SIZ_32b_SHIFT);
    gfx_constant(G_IM_SIZ_4b_INCR);
    gfx_constant(G_IM_SIZ_8b_INCR);
    gfx_constant(G_IM_SIZ_16b_INCR);
    gfx_constant(G_IM_SIZ_32b_INCR);

    // Tile formats
    gfx_constant(G_TX_RENDERTILE);
    gfx_constant(G_TX_LOADTILE);
    gfx_constant(G_TX_NOMIRROR);
    gfx_constant(G_TX_WRAP);
    gfx_constant(G_TX_MIRROR);
    gfx_constant(G_TX_CLAMP);
    gfx_constant(G_TX_NOMASK);
    gfx_constant(G_TX_NOLOD);

    // Render modes
    gfx_constant(G_RM_AA_ZB_OPA_SURF);
    gfx_constant(G_RM_AA_ZB_OPA_SURF2);
    gfx_constant(G_RM_AA_ZB_XLU_SURF);
    gfx_constant(G_RM_AA_ZB_XLU_SURF2);
    gfx_constant(G_RM_AA_ZB_OPA_DECAL);
    gfx_constant(G_RM_AA_ZB_OPA_DECAL2);
    gfx_constant(G_RM_AA_ZB_XLU_DECAL);
    gfx_constant(G_RM_AA_ZB_XLU_DECAL2);
    gfx_constant(G_RM_AA_ZB_OPA_INTER);
    gfx_constant(G_RM_AA_ZB_OPA_INTER2);
    gfx_constant(G_RM_AA_ZB_XLU_INTER);
    gfx_constant(G_RM_AA_ZB_XLU_INTER2);
    gfx_constant(G_RM_AA_ZB_XLU_LINE);
    gfx_constant(G_RM_AA_ZB_XLU_LINE2);
    gfx_constant(G_RM_AA_ZB_DEC_LINE);
    gfx_constant(G_RM_AA_ZB_DEC_LINE2);
    gfx_constant(G_RM_AA_ZB_TEX_EDGE);
    gfx_constant(G_RM_AA_ZB_TEX_EDGE2);
    gfx_constant(G_RM_AA_ZB_TEX_INTER);
    gfx_constant(G_RM_AA_ZB_TEX_INTER2);
    gfx_constant(G_RM_AA_ZB_SUB_SURF);
    gfx_constant(G_RM_AA_ZB_SUB_SURF2);
    gfx_constant(G_RM_AA_ZB_PCL_SURF);
    gfx_constant(G_RM_AA_ZB_PCL_SURF2);
    gfx_constant(G_RM_AA_ZB_OPA_TERR);
    gfx_constant(G_RM_AA_ZB_OPA_TERR2);
    gfx_constant(G_RM_AA_ZB_TEX_TERR);
    gfx_constant(G_RM_AA_ZB_TEX_TERR2);
    gfx_constant(G_RM_AA_ZB_SUB_TERR);
    gfx_constant(G_RM_AA_ZB_SUB_TERR2);
    gfx_constant(G_RM_RA_ZB_OPA_SURF);
    gfx_constant(G_RM_RA_ZB_OPA_SURF2);
    gfx_constant(G_RM_RA_ZB_OPA_DECAL);
    gfx_constant(G_RM_RA_ZB_OPA_DECAL2);
    gfx_constant(G_RM_RA_ZB_OPA_INTER);
    gfx_constant(G_RM_RA_ZB_OPA_INTER2);
    gfx_constant(G_RM_AA_OPA_SURF);
    gfx_constant(G_RM_AA_OPA_SURF2);
    gfx_constant(G_RM_AA_XLU_SURF);
    gfx_constant(G_RM_AA_XLU_SURF2);
    gfx_constant(G_RM_AA_XLU_LINE);
    gfx_constant(G_RM_AA_XLU_LINE2);
    gfx_constant(G_RM_AA_DEC_LINE);
    gfx_constant(G_RM_AA_DEC_LINE2);
    gfx_constant(G_RM_AA_TEX_EDGE);
    gfx_constant(G_RM_AA_TEX_EDGE2);
    gfx_constant(G_RM_AA_SUB_SURF);
    gfx_constant(G_RM_AA_SUB_SURF2);
    gfx_constant(G_RM_AA_PCL_SURF);
    gfx_constant(G_RM_AA_PCL_SURF2);
    gfx_constant(G_RM_AA_OPA_TERR);
    gfx_constant(G_RM_AA_OPA_TERR2);
    gfx_constant(G_RM_AA_TEX_TERR);
    gfx_constant(G_RM_AA_TEX_TERR2);
    gfx_constant(G_RM_AA_SUB_TERR);
    gfx_constant(G_RM_AA_SUB_TERR2);
    gfx_constant(G_RM_RA_OPA_SURF);
    gfx_constant(G_RM_RA_OPA_SURF2);
    gfx_constant(G_RM_ZB_OPA_SURF);
    gfx_constant(G_RM_ZB_OPA_SURF2);
    gfx_constant(G_RM_ZB_XLU_SURF);
    gfx_constant(G_RM_ZB_XLU_SURF2);
    gfx_constant(G_RM_ZB_OPA_DECAL);
    gfx_constant(G_RM_ZB_OPA_DECAL2);
    gfx_constant(G_RM_ZB_XLU_DECAL);
    gfx_constant(G_RM_ZB_XLU_DECAL2);
    gfx_constant(G_RM_ZB_CLD_SURF);
    gfx_constant(G_RM_ZB_CLD_SURF2);
    gfx_constant(G_RM_ZB_OVL_SURF);
    gfx_constant(G_RM_ZB_OVL_SURF2);
    gfx_constant(G_RM_ZB_PCL_SURF);
    gfx_constant(G_RM_ZB_PCL_SURF2);
    gfx_constant(G_RM_OPA_SURF);
    gfx_constant(G_RM_OPA_SURF2);
    gfx_constant(G_RM_XLU_SURF);
    gfx_constant(G_RM_XLU_SURF2);
    gfx_constant(G_RM_CLD_SURF);
    gfx_constant(G_RM_CLD_SURF2);
    gfx_constant(G_RM_TEX_EDGE);
    gfx_constant(G_RM_TEX_EDGE2);
    gfx_constant(G_RM_PCL_SURF);
    gfx_constant(G_RM_PCL_SURF2);
    gfx_constant(G_RM_ADD);
    gfx_constant(G_RM_ADD2);
    gfx_constant(G_RM_NOOP);
    gfx_constant(G_RM_NOOP2);
    gfx_constant(G_RM_VISCVG);
    gfx_constant(G_RM_VISCVG2);
    gfx_constant(G_RM_OPA_CI);
    gfx_constant(G_RM_OPA_CI2);
    gfx_constant(G_RM_CUSTOM_AA_ZB_XLU_SURF);
    gfx_constant(G_RM_CUSTOM_AA_ZB_XLU_SURF2);
    gfx_constant(G_RM_FOG_SHADE_A);
    gfx_constant(G_RM_FOG_PRIM_A);
    gfx_constant(G_RM_PASS);

    // Geometry modes
    gfx_constant(G_ZBUFFER);
    gfx_constant(G_SHADE);
    gfx_constant(G_TEXTURE_ENABLE);
    gfx_constant(G_SHADING_SMOOTH);
    gfx_constant(G_CULL_FRONT);
    gfx_constant(G_CULL_BACK);
    gfx_constant(G_CULL_BOTH);
    gfx_constant(G_FOG);
    gfx_constant(G_LIGHTING);
    gfx_constant(G_TEXTURE_GEN);
    gfx_constant(G_TEXTURE_GEN_LINEAR);
    gfx_constant(G_LOD);
    gfx_constant(G_CLIPPING);

    // Alpha modes
    gfx_constant(G_AC_NONE);
    gfx_constant(G_AC_THRESHOLD);
    gfx_constant(G_AC_DITHER);

    // Other modes
    gfx_constant(G_MDSFT_ALPHACOMPARE);
    gfx_constant(G_MDSFT_ZSRCSEL);
    gfx_constant(G_MDSFT_RENDERMODE);
    gfx_constant(G_MDSFT_BLENDER);
    gfx_constant(G_MDSFT_BLENDMASK);
    gfx_constant(G_MDSFT_ALPHADITHER);
    gfx_constant(G_MDSFT_RGBDITHER);
    gfx_constant(G_MDSFT_COMBKEY);
    gfx_constant(G_MDSFT_TEXTCONV);
    gfx_constant(G_MDSFT_TEXTFILT);
    gfx_constant(G_MDSFT_TEXTLUT);
    gfx_constant(G_MDSFT_TEXTLOD);
    gfx_constant(G_MDSFT_TEXTDETAIL);
    gfx_constant(G_MDSFT_TEXTPERSP);
    gfx_constant(G_MDSFT_CYCLETYPE);
    gfx_constant(G_MDSFT_COLORDITHER);
    gfx_constant(G_MDSFT_PIPELINE);
    gfx_constant(G_PM_1PRIMITIVE);
    gfx_constant(G_PM_NPRIMITIVE);
    gfx_constant(G_CYC_1CYCLE);
    gfx_constant(G_CYC_2CYCLE);
    gfx_constant(G_CYC_COPY);
    gfx_constant(G_CYC_FILL);
    gfx_constant(G_TP_NONE);
    gfx_constant(G_TP_PERSP);
    gfx_constant(G_TD_CLAMP);
    gfx_constant(G_TD_SHARPEN);
    gfx_constant(G_TD_DETAIL);
    gfx_constant(G_TL_TILE);
    gfx_constant(G_TL_LOD);
    gfx_constant(G_TT_NONE);
    gfx_constant(G_TT_RGBA16);
    gfx_constant(G_TT_IA16);
    gfx_constant(G_TF_POINT);
    gfx_constant(G_TF_AVERAGE);
    gfx_constant(G_TF_BILERP);
    gfx_constant(G_TC_CONV);
    gfx_constant(G_TC_FILTCONV);
    gfx_constant(G_TC_FILT);
    gfx_constant(G_CK_NONE);
    gfx_constant(G_CK_KEY);
    gfx_constant(G_CD_MAGICSQ);
    gfx_constant(G_CD_BAYER);
    gfx_constant(G_CD_NOISE);
    gfx_constant(G_CD_DISABLE);
    gfx_constant(G_CD_ENABLE);
    gfx_constant(G_AD_PATTERN);
    gfx_constant(G_AD_NOTPATTERN);
    gfx_constant(G_AD_NOISE);
    gfx_constant(G_AD_DISABLE);
    gfx_constant(G_AC_NONE);
    gfx_constant(G_AC_THRESHOLD);
    gfx_constant(G_AC_DITHER);
    gfx_constant(G_ZS_PIXEL);
    gfx_constant(G_ZS_PRIM);
    gfx_constant(G_SETOTHERMODE_H);
    gfx_constant(G_SETOTHERMODE_L);
    gfx_constant(G_BL_CLR_IN);
    gfx_constant(G_BL_CLR_MEM);
    gfx_constant(G_BL_CLR_BL);
    gfx_constant(G_BL_CLR_FOG);
    gfx_constant(G_BL_1MA);
    gfx_constant(G_BL_A_MEM);
    gfx_constant(G_BL_A_IN);
    gfx_constant(G_BL_A_FOG);
    gfx_constant(G_BL_A_SHADE);
    gfx_constant(G_BL_1);
    gfx_constant(G_BL_0);
    gfx_constant(AA_EN);
    gfx_constant(Z_CMP);
    gfx_constant(Z_UPD);
    gfx_constant(ZMODE_OPA);
    gfx_constant(ZMODE_INTER);
    gfx_constant(ZMODE_XLU);
    gfx_constant(ZMODE_DEC);
    gfx_constant(IM_RD);
    gfx_constant(CLR_ON_CVG);
    gfx_constant(CVG_DST_CLAMP);
    gfx_constant(CVG_DST_WRAP);
    gfx_constant(CVG_DST_FULL);
    gfx_constant(CVG_DST_SAVE);
    gfx_constant(CVG_X_ALPHA);
    gfx_constant(ALPHA_CVG_SEL);
    gfx_constant(FORCE_BL);
    gfx_constant(TEX_EDGE);

    // MW constants
    gfx_constant(G_MW_MATRIX);
    gfx_constant(G_MW_NUMLIGHT);
    gfx_constant(G_MW_CLIP);
    gfx_constant(G_MW_SEGMENT);
    gfx_constant(G_MW_FOG);
    gfx_constant(G_MW_LIGHTCOL);

    // PM constants
    gfx_constant(G_PM_1PRIMITIVE);
    gfx_constant(G_PM_NPRIMITIVE);

    // Texture/scale/rotate constants
    gfx_constant(G_TEXTURE_IMAGE_FRAC);
    gfx_constant(G_TEXTURE_SCALE_FRAC);
    gfx_constant(G_SCALE_FRAC);
    gfx_constant(G_ROTATE_FRAC);

    // Player parts
    gfx_constant(PANTS);
    gfx_constant(SHIRT);
    gfx_constant(GLOVES);
    gfx_constant(SHOES);
    gfx_constant(HAIR);
    gfx_constant(SKIN);
    gfx_constant(CAP);
    gfx_constant(EMBLEM);
    gfx_constant(METAL);

    // Extended
    gfx_constant(G_LIGHT_MAP_EXT);

    // Common values
    gfx_constant(CALC_DXT(4,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(8,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(16,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(32,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(64,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(128,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(256,G_IM_SIZ_4b_BYTES));
    gfx_constant(CALC_DXT(4,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(8,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(16,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(32,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(64,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(128,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(256,G_IM_SIZ_8b_BYTES));
    gfx_constant(CALC_DXT(4,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(8,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(16,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(32,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(64,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(128,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(256,G_IM_SIZ_16b_BYTES));
    gfx_constant(CALC_DXT(4,G_IM_SIZ_32b_BYTES));
    gfx_constant(CALC_DXT(8,G_IM_SIZ_32b_BYTES));
    gfx_constant(CALC_DXT(16,G_IM_SIZ_32b_BYTES));
    gfx_constant(CALC_DXT(32,G_IM_SIZ_32b_BYTES));
    gfx_constant(CALC_DXT(64,G_IM_SIZ_32b_BYTES));
    gfx_constant(CALC_DXT(128,G_IM_SIZ_32b_BYTES));
    gfx_constant(CALC_DXT(256,G_IM_SIZ_32b_BYTES));

    *found = false;
    return 0;
}

static s64 ParseGfxSymbolArg(GfxData* aGfxData, DataNode<Gfx>* aNode, u64* pTokenIndex, const char *aPrefix) {
    assert(aPrefix != NULL);
    String _Token = (pTokenIndex != NULL ? aNode->mTokens[(*pTokenIndex)++] : "");
    String _Arg("%s%s", aPrefix, _Token.begin());

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    bool constantFound = false;
    s64 constantValue = DynOS_Gfx_ParseGfxConstants(_Arg, &constantFound);
    if (constantFound) {
        return constantValue;
    }

    // Offset
    s32 _Offset = 0;
    s32 _Plus = _Arg.Find('+');
    if (_Plus != -1) {
        _Offset = _Arg.SubString(_Plus + 1).ParseInt();
        _Arg = _Arg.SubString(0, _Plus);
    }

    // Lights
    for (auto& _Node : aGfxData->mLights) {
        // Light pointer
        if (_Arg == _Node->mName) {
            return (s64) DynOS_Lights_Parse(aGfxData, _Node)->mData;
        }

        // Ambient pointer
        String _Ambient("&%s.a", _Node->mName.begin());
        if (_Arg == _Ambient) {
            return (s64) &(DynOS_Lights_Parse(aGfxData, _Node)->mData->a);
        }

        // Diffuse pointer
        String _Diffuse("&%s.l", _Node->mName.begin());
        if (_Arg == _Diffuse) {
            return (s64) &(DynOS_Lights_Parse(aGfxData, _Node)->mData->l[0]);
        }
    }

    // Textures
    for (auto& _Node : aGfxData->mTextures) {
        if (_Arg == _Node->mName) {
            return (s64) DynOS_Tex_Parse(aGfxData, _Node);
        }
    }

    // Vertex arrays
    for (auto& _Node : aGfxData->mVertices) {
        if (_Arg == _Node->mName) {
            auto base = DynOS_Vtx_Parse(aGfxData, _Node)->mData;
            auto data = (u8*)base + _Offset;
            if (_Offset != 0) {
                aGfxData->mPointerOffsetList.Add({ (const void*)data, (const void*)base });
            }
            return (s64) data;
        }
    }

    // Display lists
    for (auto& _Node : aGfxData->mDisplayLists) {
        if (_Arg == _Node->mName) {
            return (s64) DynOS_Gfx_Parse(aGfxData, _Node);
        }
    }

    for (auto& _Node : aGfxData->mLight0s) {
        // Light pointer
        if (_Arg == _Node->mName) {
            return (s64) DynOS_Light0_Parse(aGfxData, _Node)->mData;
        }
    }

    for (auto& _Node : aGfxData->mLightTs) {
        // Light pointer
        if (_Arg == _Node->mName) {
            return (s64) DynOS_LightT_Parse(aGfxData, _Node)->mData;
        }

        // Diffuse pointer
        String _Diffuse("&%s.col", _Node->mName.begin());
        if (_Arg == _Diffuse) {
            return (s64) &(DynOS_LightT_Parse(aGfxData, _Node)->mData->col[0]);
        }

        // Diffuse copy pointer
        String _DiffuseC("&%s.colc", _Node->mName.begin());
        if (_Arg == _DiffuseC) {
            return (s64) &(DynOS_LightT_Parse(aGfxData, _Node)->mData->colc[0]);
        }

        // Dir pointer
        String _Dir("&%s.dir", _Node->mName.begin());
        if (_Arg == _Dir) {
            return (s64) &(DynOS_LightT_Parse(aGfxData, _Node)->mData->dir[0]);
        }
    }

    for (auto& _Node : aGfxData->mAmbientTs) {
        // Light pointer
        if (_Arg == _Node->mName) {
            return (s64) DynOS_AmbientT_Parse(aGfxData, _Node)->mData;
        }

        // Diffuse pointer
        String _Diffuse("&%s.col", _Node->mName.begin());
        if (_Arg == _Diffuse) {
            return (s64) &(DynOS_AmbientT_Parse(aGfxData, _Node)->mData->col[0]);
        }

        // Diffuse copy pointer
        String _DiffuseC("&%s.colc", _Node->mName.begin());
        if (_Arg == _DiffuseC) {
            return (s64) &(DynOS_AmbientT_Parse(aGfxData, _Node)->mData->colc[0]);
        }
    }

    // Built-in textures
    auto builtinTex = DynOS_Builtin_Tex_GetFromName(_Arg.begin());
    if (builtinTex != NULL) {
        return (s64)builtinTex;
    }

    // Recursive descent parsing
    bool rdSuccess = false;
    s64 rdValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdSuccess, DynOS_Gfx_ParseGfxConstants);
    if (rdSuccess) {
        return (LevelScript)rdValue;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown gfx arg: %s", _Arg.begin());
    return 0;
}

#define gfx_symbol_0(symb)                                                                             \
    if (_Symbol == #symb) {                                                                       \
        Gfx _Gfx[] = { symb() };                                                                        \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_1(symb, ptr)                                                                        \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        if (ptr) { aGfxData->mPointerList.Add(aHead); }                                         \
        Gfx _Gfx[] = { symb(_Arg0) };                                                                    \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_2(symb, ptr)                                                                        \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        if (ptr) { aGfxData->mPointerList.Add(aHead); }                                         \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1) };                                                              \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_3(symb, ptr)                                                                        \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        if (ptr) { aGfxData->mPointerList.Add(aHead); }                                         \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1, _Arg2) };                                                        \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_4(symb)                                                                             \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };                                                  \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_5(symb)                                                                             \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) };                                            \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_6(symb)                                                                             \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg5 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) };                                      \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_7(symb)                                                                             \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg5 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg6 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6) };                                \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_symbol_8(symb)                                                                             \
    if (_Symbol == #symb) {                                                                       \
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg5 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg6 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        s64 _Arg7 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");                                \
        Gfx _Gfx[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7) };                          \
        memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
        aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
        return;                                                                                        \
    }

#define gfx_arg_with_suffix(argname, suffix)                                                           \
    const String& argname##_token = aNode->mTokens[aTokenIndex];                                    \
    String _Token##suffix = String("%s%s", argname##_token.begin(), #suffix);                                   \
    s64 argname = ParseGfxSymbolArg(aGfxData, aNode, NULL, _Token##suffix.begin());                         \

#define STR_VALUE_2(...) #__VA_ARGS__
#define STR_VALUE(...) STR_VALUE_2(__VA_ARGS__)
#define gfx_set_combine_mode_arg(x) if (_Arg == #x) { return String("%s", STR_VALUE(x)); }
static String ConvertSetCombineModeArgToString(GfxData *aGfxData, const String& _Arg) {
    gfx_set_combine_mode_arg(G_CC_PRIMITIVE);
    gfx_set_combine_mode_arg(G_CC_SHADE);
    gfx_set_combine_mode_arg(G_CC_MODULATEI);
    gfx_set_combine_mode_arg(G_CC_MODULATEIDECALA);
    gfx_set_combine_mode_arg(G_CC_MODULATEIFADE);
    gfx_set_combine_mode_arg(G_CC_MODULATERGB);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBDECALA);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBFADE);
    gfx_set_combine_mode_arg(G_CC_MODULATEIA);
    gfx_set_combine_mode_arg(G_CC_MODULATEIFADEA);
    gfx_set_combine_mode_arg(G_CC_MODULATEFADE);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBA);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBFADEA);
    gfx_set_combine_mode_arg(G_CC_MODULATEI_PRIM);
    gfx_set_combine_mode_arg(G_CC_MODULATEIA_PRIM);
    gfx_set_combine_mode_arg(G_CC_MODULATEIDECALA_PRIM);
    gfx_set_combine_mode_arg(G_CC_MODULATERGB_PRIM);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBA_PRIM);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBDECALA_PRIM);
    gfx_set_combine_mode_arg(G_CC_FADE);
    gfx_set_combine_mode_arg(G_CC_FADEA);
    gfx_set_combine_mode_arg(G_CC_DECALRGB);
    gfx_set_combine_mode_arg(G_CC_DECALRGBA);
    gfx_set_combine_mode_arg(G_CC_DECALFADE);
    gfx_set_combine_mode_arg(G_CC_DECALFADEA);
    gfx_set_combine_mode_arg(G_CC_BLENDI);
    gfx_set_combine_mode_arg(G_CC_BLENDIA);
    gfx_set_combine_mode_arg(G_CC_BLENDIDECALA);
    gfx_set_combine_mode_arg(G_CC_BLENDRGBA);
    gfx_set_combine_mode_arg(G_CC_BLENDRGBDECALA);
    gfx_set_combine_mode_arg(G_CC_BLENDRGBFADEA);
    gfx_set_combine_mode_arg(G_CC_ADDRGB);
    gfx_set_combine_mode_arg(G_CC_ADDRGBDECALA);
    gfx_set_combine_mode_arg(G_CC_ADDRGBFADE);
    gfx_set_combine_mode_arg(G_CC_REFLECTRGB);
    gfx_set_combine_mode_arg(G_CC_REFLECTRGBDECALA);
    gfx_set_combine_mode_arg(G_CC_HILITERGB);
    gfx_set_combine_mode_arg(G_CC_HILITERGBA);
    gfx_set_combine_mode_arg(G_CC_HILITERGBDECALA);
    gfx_set_combine_mode_arg(G_CC_SHADEDECALA);
    gfx_set_combine_mode_arg(G_CC_SHADEFADEA);
    gfx_set_combine_mode_arg(G_CC_BLENDPE);
    gfx_set_combine_mode_arg(G_CC_BLENDPEDECALA);
    gfx_set_combine_mode_arg(_G_CC_BLENDPE);
    gfx_set_combine_mode_arg(_G_CC_BLENDPEDECALA);
    gfx_set_combine_mode_arg(_G_CC_TWOCOLORTEX);
    gfx_set_combine_mode_arg(_G_CC_SPARSEST);
    gfx_set_combine_mode_arg(G_CC_TEMPLERP);
    gfx_set_combine_mode_arg(G_CC_TRILERP);
    gfx_set_combine_mode_arg(G_CC_INTERFERENCE);
    gfx_set_combine_mode_arg(G_CC_1CYUV2RGB);
    gfx_set_combine_mode_arg(G_CC_YUV2RGB);
    gfx_set_combine_mode_arg(G_CC_PASS2);
    gfx_set_combine_mode_arg(G_CC_MODULATEI2);
    gfx_set_combine_mode_arg(G_CC_MODULATEIA2);
    gfx_set_combine_mode_arg(G_CC_MODULATERGB2);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBA2);
    gfx_set_combine_mode_arg(G_CC_MODULATEI_PRIM2);
    gfx_set_combine_mode_arg(G_CC_MODULATEIA_PRIM2);
    gfx_set_combine_mode_arg(G_CC_MODULATERGB_PRIM2);
    gfx_set_combine_mode_arg(G_CC_MODULATERGBA_PRIM2);
    gfx_set_combine_mode_arg(G_CC_DECALRGB2);
    gfx_set_combine_mode_arg(G_CC_BLENDI2);
    gfx_set_combine_mode_arg(G_CC_BLENDIA2);
    gfx_set_combine_mode_arg(G_CC_CHROMA_KEY2);
    gfx_set_combine_mode_arg(G_CC_HILITERGB2);
    gfx_set_combine_mode_arg(G_CC_HILITERGBA2);
    gfx_set_combine_mode_arg(G_CC_HILITERGBDECALA2);
    gfx_set_combine_mode_arg(G_CC_HILITERGBPASSA2);
    PrintDataError("  ERROR: Unknown gfx gsDPSetCombineMode arg: %s", _Arg.begin());
    return "";
}

static Array<s64> ParseGfxSetCombineMode(GfxData* aGfxData, DataNode<Gfx>* aNode, u64* pTokenIndex) {
    String _Buffer = ConvertSetCombineModeArgToString(aGfxData, aNode->mTokens[(*pTokenIndex)++]);
    Array<s64> _Args;
    String _Token;
    for (u64 i = 0, n = _Buffer.Length(); i <= n; ++i) {
        if (i == n || _Buffer[i] == ' ' || _Buffer[i] == '\t' || _Buffer[i] == ',') {
            if (_Token.Length() != 0) {
                String _Arg("%s%s", (_Args.Count() < 4 ? "G_CCMUX_" : "G_ACMUX_"), _Token.begin());
                _Args.Add(ParseGfxSymbolArg(aGfxData, aNode, NULL, _Arg.begin()));
                _Token.Clear();
            }
        } else {
            _Token.Add(_Buffer[i]);
        }
    }
    if (_Args.Count() < 8) {
        PrintDataError("  ERROR: gsDPSetCombineMode %s: Not enough arguments", _Buffer.begin());
    }
    return _Args;
}

static void UpdateTextureInfo(GfxData* aGfxData, s64 *aTexPtr, s32 aFormat, s32 aSize, s32 aWidth, s32 aHeight) {
    // Update current texture pointers
    if (aTexPtr && (*aTexPtr)) {
        if (DynOS_Builtin_Tex_GetFromData(*(const Texture**)aTexPtr)) {
            return;
        }

        aGfxData->mGfxContext.mCurrentPalette = aGfxData->mGfxContext.mCurrentTexture;
        aGfxData->mGfxContext.mCurrentTexture = (DataNode<TexData>*) (*aTexPtr);
    }

    // Update texture info if not loaded from a file
    if (aGfxData->mGfxContext.mCurrentTexture && aGfxData->mGfxContext.mCurrentTexture->mData && aGfxData->mGfxContext.mCurrentTexture->mData->mPngData.Empty()) {
        if (aFormat != -1) aGfxData->mGfxContext.mCurrentTexture->mData->mRawFormat = aFormat;
        if (aSize   != -1) aGfxData->mGfxContext.mCurrentTexture->mData->mRawSize   = aSize;
        if (aWidth  != -1) aGfxData->mGfxContext.mCurrentTexture->mData->mRawWidth  = aWidth;
        if (aHeight != -1) aGfxData->mGfxContext.mCurrentTexture->mData->mRawHeight = aHeight;
    }
}

static void ParseGfxSymbol(GfxData* aGfxData, DataNode<Gfx>* aNode, Gfx*& aHead, u64& aTokenIndex) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    // Simple symbols
    gfx_symbol_0(gsDPFullSync);
    gfx_symbol_0(gsDPTileSync);
    gfx_symbol_0(gsDPPipeSync);
    gfx_symbol_0(gsDPLoadSync);
    gfx_symbol_0(gsDPNoOp);
    gfx_symbol_1(gsDPNoOpTag, false);
    gfx_symbol_1(gsDPSetCycleType, false);
    gfx_symbol_2(gsSPLight, true);
    gfx_symbol_3(gsSPVertex, true);
    gfx_symbol_4(gsSP1Triangle);
    gfx_symbol_8(gsSP2Triangles);
    gfx_symbol_1(gsSPNumLights, false);
    gfx_symbol_1(gsDPSetDepthSource, false);
    gfx_symbol_1(gsDPSetTextureLUT, false);
    gfx_symbol_2(gsDPLoadTLUTCmd, false);
    gfx_symbol_5(gsDPLoadBlock);
    gfx_symbol_2(gsDPSetRenderMode, false);
    gfx_symbol_2(gsSPGeometryMode, false);
    gfx_symbol_2(gsSPGeometryModeSetFirst, false);
    gfx_symbol_6(gsDPSetPrimColor);
    gfx_symbol_4(gsDPSetEnvColor);
    gfx_symbol_4(gsDPSetFogColor);
    gfx_symbol_2(gsSPFogPosition, false);
    gfx_symbol_1(gsDPSetAlphaCompare, false);
    gfx_symbol_1(gsDPSetTextureFilter, false);
    gfx_symbol_2(gsSPCullDisplayList, false);
    gfx_symbol_1(gsDPSetAlphaDither, false);
    gfx_symbol_1(gsDPSetCombineKey, false);
    gfx_symbol_1(gsDPSetTextureConvert, false);
    gfx_symbol_1(gsDPSetCombineKey, false);
    gfx_symbol_1(gsDPSetTextureConvert, false);
    gfx_symbol_1(gsDPPipelineMode, false);
    gfx_symbol_4(gsSPSetOtherMode);
    gfx_symbol_1(gsDPSetTextureDetail, false);
    gfx_symbol_1(gsDPSetColorDither, false);
    gfx_symbol_2(gsDPSetPrimDepth, false);
    gfx_symbol_4(gsDPSetBlendColor);

    gfx_symbol_2(gsSPCopyLightEXT, false);
    gfx_symbol_1(gsSPCopyLightsPlayerPart, false);
    gfx_symbol_2(gsSPFogFactor, false);
    gfx_symbol_1(gsDPSetTextureLOD, false);
    gfx_symbol_3(gsMoveWd, false);
    gfx_symbol_3(gsSPVertexNonGlobal, true);

    // Special symbols
    if (_Symbol == "gsSPTexture") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        gSPTexture(aHead++, _Arg0, _Arg1, _Arg2, _Arg3, _Arg4);
        return;
    }
    if (_Symbol == "gsSPSetGeometryMode") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        gSPSetGeometryMode(aHead++, _Arg0);
        return;
    }
    if (_Symbol == "gsSPClearGeometryMode") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        gSPClearGeometryMode(aHead++, _Arg0);
        return;
    }
    if (_Symbol == "gsSPDisplayList") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        aGfxData->mPointerList.Add(aHead);
        gSPDisplayList(aHead++, _Arg0);
        return;
    }
    if (_Symbol == "gsSPBranchList") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        aGfxData->mPointerList.Add(aHead);
        gSPBranchList(aHead++, _Arg0);
        return;
    }
    if (_Symbol == "gsSPEndDisplayList") {
        gSPEndDisplayList(aHead++);

        // Convert raw texture to PNG if all raw members are set
        if (aGfxData->mGfxContext.mCurrentTexture                    != NULL &&
            aGfxData->mGfxContext.mCurrentTexture->mData             != NULL &&
            aGfxData->mGfxContext.mCurrentTexture->mData->mPngData.Empty()   &&
            aGfxData->mGfxContext.mCurrentTexture->mData->mRawFormat != -1   &&
            aGfxData->mGfxContext.mCurrentTexture->mData->mRawSize   != -1   &&
            aGfxData->mGfxContext.mCurrentTexture->mData->mRawWidth  != -1   &&
            aGfxData->mGfxContext.mCurrentTexture->mData->mRawHeight != -1) {
            DynOS_Tex_ConvertTextureDataToPng(aGfxData, aGfxData->mGfxContext.mCurrentTexture->mData);
        }

        // End the display list parsing after hitting gsSPEndDisplayList
        aTokenIndex = 0x7FFFFFFF;
        return;
    }

    // Complex symbols
    if (_Symbol == "gsSPSetLights0") {
        Lights0 *_Light = (Lights0 *) ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        gSPNumLights(aHead++, NUMLIGHTS_0);
        aGfxData->mPointerList.Add(aHead);
        gSPLight(aHead++, &_Light->l[0], 1);
        aGfxData->mPointerList.Add(aHead);
        gSPLight(aHead++, &_Light->a, 2);
        return;
    }
    if (_Symbol == "gsSPSetLights1") {
        Lights1 *_Light = (Lights1 *) ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        gSPNumLights(aHead++, NUMLIGHTS_1);
        aGfxData->mPointerList.Add(aHead);
        gSPLight(aHead++, &_Light->l[0], 1);
        aGfxData->mPointerList.Add(aHead);
        gSPLight(aHead++, &_Light->a, 2);
        return;
    }
    if (_Symbol == "gsDPSetCombineMode") {
        Array<s64> _Args0 = ParseGfxSetCombineMode(aGfxData, aNode, &aTokenIndex);
        Array<s64> _Args1 = ParseGfxSetCombineMode(aGfxData, aNode, &aTokenIndex);
        Gfx _Gfx = {{
            _SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(GCCc0w0(_Args0[0x0], _Args0[0x2], _Args0[0x4], _Args0[0x6]) | GCCc1w0(_Args1[0x0], _Args1[0x2]), 0, 24),
            (u32) (GCCc0w1(_Args0[0x1], _Args0[0x3], _Args0[0x5], _Args0[0x7]) | GCCc1w1(_Args1[0x1], _Args1[0x4], _Args1[0x6], _Args1[0x3], _Args1[0x5], _Args1[0x7]))
        }};
        *(aHead++) = _Gfx;
        return;
    }
    if (_Symbol == "gsDPSetCombineLERP") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _Arg5 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _Arg6 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _Arg7 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _Arg8 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _Arg9 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _ArgA = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _ArgB = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_CCMUX_");
        s64 _ArgC = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _ArgD = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _ArgE = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        s64 _ArgF = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "G_ACMUX_");
        Gfx _Gfx = {{
            _SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(GCCc0w0(_Arg0, _Arg2, _Arg4, _Arg6) | GCCc1w0(_Arg8, _ArgA), 0, 24),
            (u32) (GCCc0w1(_Arg1, _Arg3, _Arg5, _Arg7) | GCCc1w1(_Arg9, _ArgC, _ArgE, _ArgB, _ArgD, _ArgF))
        }};
        *(aHead++) = _Gfx;
        return;
    }

    // TexData symbols
    if (_Symbol == "gsDPSetTextureImage") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, &_Arg3, (s32) _Arg0, (s32) _Arg1, -1, -1);
        aGfxData->mPointerList.Add(aHead);
        gDPSetTextureImage(aHead++, _Arg0, _Arg1, _Arg2, _Arg3);
        return;
    }
    if (_Symbol == "gsDPSetTile") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg5 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg6 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg7 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg8 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg9 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _ArgA = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _ArgB = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, NULL, (s32) _Arg0, (s32) _Arg1, -1, -1);
        gDPSetTile(aHead++, _Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7, _Arg8, _Arg9, _ArgA, _ArgB);
        return;
    }
    if (_Symbol == "gsDPLoadTile") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, NULL, -1, -1, (s32) (_Arg3 >> G_TEXTURE_IMAGE_FRAC) + 1, (s32) (_Arg4 >> G_TEXTURE_IMAGE_FRAC) + 1);
        gDPLoadTile(aHead++, _Arg0, _Arg1, _Arg2, _Arg3, _Arg4);
        return;
    }
    if (_Symbol == "gsDPSetTileSize") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, NULL, -1, -1, (s32) (_Arg3 >> G_TEXTURE_IMAGE_FRAC) + 1, (s32) (_Arg4 >> G_TEXTURE_IMAGE_FRAC) + 1);
        gDPSetTileSize(aHead++, _Arg0, _Arg1, _Arg2, _Arg3, _Arg4);
        return;
    }
    if (_Symbol == "gsDPLoadTextureBlock") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        gfx_arg_with_suffix(arg2_0, _LOAD_BLOCK);
        gfx_arg_with_suffix(arg2_1, _INCR);
        gfx_arg_with_suffix(arg2_2, _SHIFT);
        gfx_arg_with_suffix(arg2_3, _BYTES);
        gfx_arg_with_suffix(arg2_4, _LINE_BYTES);
        s64 _Arg2 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg3 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg4 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg5 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg6 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg7 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg8 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg9 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _ArgA = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _ArgB = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, &_Arg0, (s32) _Arg1, (s32) _Arg2, (s32) _Arg3, (s32) _Arg4);

        aGfxData->mPointerList.Add(aHead);
        gDPSetTextureImage(aHead++, _Arg1, arg2_0, 1, _Arg0);
        gDPSetTile(aHead++, _Arg1, arg2_0, 0, 0, G_TX_LOADTILE, 0, _Arg7, _Arg9, _ArgB, _Arg6, _Arg8, _ArgA);
        gDPLoadSync(aHead++);
        gDPLoadBlock(aHead++, G_TX_LOADTILE, 0, 0, (((_Arg3) * (_Arg4) + arg2_1) >> arg2_2) - 1, CALC_DXT(_Arg3, arg2_3));
        gDPPipeSync(aHead++);
        gDPSetTile(aHead++, _Arg1, _Arg2, ((((_Arg3) * arg2_4) + 7) >> 3), 0, G_TX_RENDERTILE, _Arg5, _Arg7, _Arg9, _ArgB, _Arg6, _Arg8, _ArgA);
        gDPSetTileSize(aHead++, G_TX_RENDERTILE, 0, 0, (((u64)_Arg3) - 1) << G_TEXTURE_IMAGE_FRAC, (((u64)_Arg4) - 1) << G_TEXTURE_IMAGE_FRAC);
        return;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown gfx symbol: %s", _Symbol.begin());
}

DataNode<Gfx>* DynOS_Gfx_Parse(GfxData* aGfxData, DataNode<Gfx>* aNode) {
    if (aNode->mData) return aNode;

    // Display list data
    aNode->mData = New<Gfx>(aNode->mTokens.Count() * DISPLAY_LIST_SIZE_PER_TOKEN);
    Gfx* _Head = aNode->mData;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseGfxSymbol(aGfxData, aNode, _Head, _TokenIndex);
    }
    aNode->mSize = (u32) (_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

#pragma GCC diagnostic pop

  /////////////
 // Writing //
/////////////

void DynOS_Gfx_Write(BinFile *aFile, GfxData *aGfxData, DataNode<Gfx> *aNode) {
    if (!aNode->mData) return;

    // Header
    aFile->Write<u8>(DATA_TYPE_DISPLAY_LIST);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        Gfx *_Head = &aNode->mData[i];
        if (aGfxData->mPointerList.Find((void *) _Head) != -1) {
            aFile->Write<u32>(_Head->words.w0);
            DynOS_Pointer_Write(aFile, (const void *) _Head->words.w1, aGfxData);
        } else {
            aFile->Write<u32>(_Head->words.w0);
            aFile->Write<u32>(_Head->words.w1);
        }
    }
}
  /////////////
 // Reading //
/////////////

void DynOS_Gfx_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Gfx> *_Node = New<DataNode<Gfx>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<Gfx>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        u32 _WordsW0 = aFile->Read<u32>();
        u32 _WordsW1 = aFile->Read<u32>();
        void *_Ptr = DynOS_Pointer_Load(aFile, aGfxData, _WordsW1, &_Node->mFlags);
        if (_Ptr) {
            _Node->mData[i].words.w0 = (uintptr_t) _WordsW0;
            _Node->mData[i].words.w1 = (uintptr_t) _Ptr;
        } else {
            _Node->mData[i].words.w0 = (uintptr_t) _WordsW0;
            _Node->mData[i].words.w1 = (uintptr_t) _WordsW1;
        }
    }

    // Append
    aGfxData->mDisplayLists.Add(_Node);
}
