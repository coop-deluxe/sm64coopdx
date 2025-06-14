#include "dynos.cpp.h"
#include <map>
extern "C" {
#include <assert.h>
#include "sm64.h"
#include "include/textures.h"
#include "src/pc/lua/smlua.h"
#include "src/pc/lua/utils/smlua_gfx_utils.h"
#include "include/macros.h"
}

static std::map<std::string, std::pair<Gfx *, u32>> sGfxCommandCache;
static char *sGfxCommandErrorMsg = NULL;
static u32 sGfxCommandErrorSize = 0;

#define PrintDataErrorGfx(...) { \
    if (sGfxCommandErrorMsg) { \
        snprintf(sGfxCommandErrorMsg, sGfxCommandErrorSize, __VA_ARGS__); \
        aGfxData->mErrorCount++; \
    } else { \
        PrintDataError(__VA_ARGS__); \
    } \
}

#define CHECK_TOKEN_INDEX(tokenIndex, returnValue) { \
    if (tokenIndex >= aNode->mTokens.Count()) { \
        PrintDataErrorGfx("  ERROR: Invalid token index: %llu, tokens count is: %d", tokenIndex, aNode->mTokens.Count()); \
        return returnValue; \
    } \
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
    gfx_constant(LIGHT_1);
    gfx_constant(LIGHT_2);
    gfx_constant(LIGHT_3);
    gfx_constant(LIGHT_4);
    gfx_constant(LIGHT_5);
    gfx_constant(LIGHT_6);
    gfx_constant(LIGHT_7);
    gfx_constant(LIGHT_8);

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
    gfx_constant(G_LIGHTING_ENGINE_EXT);
    gfx_constant(G_PACKED_NORMALS_EXT);

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
    gfx_constant(CALC_DXT_4b(4));
    gfx_constant(CALC_DXT_4b(8));
    gfx_constant(CALC_DXT_4b(16));
    gfx_constant(CALC_DXT_4b(32));
    gfx_constant(CALC_DXT_4b(64));
    gfx_constant(CALC_DXT_4b(128));
    gfx_constant(CALC_DXT_4b(256));

    *found = false;
    return 0;
}

static s64 ParseGfxSymbolArg(GfxData* aGfxData, DataNode<Gfx>* aNode, u64* pTokenIndex, const char *aPrefix) {
    assert(aPrefix != NULL);
    if (pTokenIndex != NULL) { CHECK_TOKEN_INDEX(*pTokenIndex, 0); }
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

    // Pointers
    for (auto& _Node : aGfxData->mRawPointers) {
        if (_Arg == _Node->mName) {
            return (s64) _Node->mData;
        }
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
        return rdValue;
    }

    // Unknown
    PrintDataErrorGfx("  ERROR: Unknown gfx arg: %s", _Arg.begin());
    return 0;
}

#define gfx_arg_with_suffix(argname, suffix)                                                        \
    CHECK_TOKEN_INDEX(aTokenIndex,);                                                                \
    const String& argname##_token = aNode->mTokens[aTokenIndex];                                    \
    String _Token##suffix = String("%s%s", argname##_token.begin(), #suffix);                       \
    s64 argname = ParseGfxSymbolArg(aGfxData, aNode, NULL, _Token##suffix.begin());                 \

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
    PrintDataErrorGfx("  ERROR: Unknown gfx gsDPSetCombineMode arg: %s", _Arg.begin());
    return "";
}

static Array<s64> ParseGfxSetCombineMode(GfxData* aGfxData, DataNode<Gfx>* aNode, u64* pTokenIndex) {
    CHECK_TOKEN_INDEX(*pTokenIndex, Array<s64>());
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
        PrintDataErrorGfx("  ERROR: gsDPSetCombineMode %s: Not enough arguments", _Buffer.begin());
    }
    return _Args;
}

static void UpdateTextureInfo(GfxData* aGfxData, s64 *aTexPtr, s32 aFormat, s32 aSize, s32 aWidth, s32 aHeight) {
    // Update current texture pointers
    if (aTexPtr && (*aTexPtr)) {
        if (DynOS_Builtin_Tex_GetFromData(*(const Texture**)aTexPtr)) {
            return;
        }

        // Skip raw pointers
        for (const auto &ptrNode : aGfxData->mRawPointers) {
            if ((void *) *aTexPtr == ptrNode->mData) {
                return;
            }
        }

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

static void SetCurrentTextureAsPalette(GfxData* aGfxData) {
    if (aGfxData->mGfxContext.mCurrentTexture) {
        aGfxData->mGfxContext.mCurrentPalette = aGfxData->mGfxContext.mCurrentTexture;
    }
}

static void ParseGfxSymbol(GfxData* aGfxData, DataNode<Gfx>* aNode, Gfx*& aHead, u64& aTokenIndex) {
    CHECK_TOKEN_INDEX(aTokenIndex,);
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    // Simple symbols
    // Uses macro iterators to dynamically handle the correct number of parameters
#define HANDLE_PARAM(paramNum) s64 _Arg##paramNum = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
#define GET_ARG(paramNum) _Arg##paramNum
#define CALL_SYMB(symb, ...) symb(__VA_ARGS__)
#define define_gfx_symbol(symb, params, addPtr, ...)                                                 \
if (_Symbol == #symb) {                                                                              \
    REPEAT(HANDLE_PARAM, params);                                                                    \
    if (addPtr) { aGfxData->mPointerList.Add(aHead); }                                               \
    Gfx _Gfx[] = { CALL_SYMB(symb, LIST_ARGS(GET_ARG, params)) };                                    \
    memcpy(aHead, _Gfx, sizeof(_Gfx));                                                               \
    aHead += (sizeof(_Gfx) / sizeof(_Gfx[0]));                                                       \
    return;                                                                                          \
}
#include "gfx_symbols.h"
#undef HANDLE_PARAM
#undef GET_ARG
#undef CALL_SYMB
#undef define_gfx_symbol

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
    if (_Symbol == "gsDPLoadTLUTCmd") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        SetCurrentTextureAsPalette(aGfxData);

        gDPLoadTLUTCmd(aHead++, _Arg0, _Arg1);
        return;
    }
    if (_Symbol == "gsDPLoadTLUT_pal16") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, &_Arg1, G_IM_FMT_RGBA, G_IM_SIZ_16b, -1, -1);
        SetCurrentTextureAsPalette(aGfxData);

        aGfxData->mPointerList.Add(aHead);
        gDPSetTextureImage(aHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, _Arg1);
        gDPTileSync(aHead++);
        gDPSetTile(aHead++, 0, 0, 0, (256+(((_Arg0)&0xf)*16)), G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPLoadSync(aHead++);
        gDPLoadTLUTCmd(aHead++, G_TX_LOADTILE, 15);
        gDPPipeSync(aHead++);
        return;
    }
    if (_Symbol == "gsDPLoadTLUT_pal256") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        UpdateTextureInfo(aGfxData, &_Arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, -1, -1);
        SetCurrentTextureAsPalette(aGfxData);

        aGfxData->mPointerList.Add(aHead);
        gDPSetTextureImage(aHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, _Arg0);
        gDPTileSync(aHead++);
        gDPSetTile(aHead++, 0, 0, 0, 256, G_TX_LOADTILE, 0 , 0, 0, 0, 0, 0, 0);
        gDPLoadSync(aHead++);
        gDPLoadTLUTCmd(aHead++, G_TX_LOADTILE, 255);
        gDPPipeSync(aHead++);
        return;
    }
    if (_Symbol == "gsDPLoadTextureBlock_4b") {
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
        UpdateTextureInfo(aGfxData, &_Arg0, (s32) _Arg1, G_IM_SIZ_4b, (s32) _Arg2, (s32) _Arg3);

        aGfxData->mPointerList.Add(aHead);
        gDPSetTextureImage(aHead++, _Arg1, G_IM_SIZ_4b, 1, _Arg0);
        gDPSetTile(aHead++, _Arg1, G_IM_SIZ_4b, 0, 0, G_TX_LOADTILE, 0, _Arg6, _Arg8, _ArgA, _Arg5, _Arg7, _Arg9);
        gDPLoadSync(aHead++);
        gDPLoadBlock(aHead++, G_TX_LOADTILE, 0, 0, (((_Arg2) * (_Arg3) + 3) >> 2) - 1, CALC_DXT_4b(_Arg2));
        gDPPipeSync(aHead++);
        gDPSetTile(aHead++, _Arg1, G_IM_SIZ_4b, ((((_Arg2) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, _Arg4, _Arg6, _Arg8, _ArgA, _Arg5, _Arg7, _Arg9);
        gDPSetTileSize(aHead++, G_TX_RENDERTILE, 0, 0, (((u64)_Arg2) - 1) << G_TEXTURE_IMAGE_FRAC, (((u64)_Arg3) - 1) << G_TEXTURE_IMAGE_FRAC);
        return;
    }
    if (_Symbol == "gsSPLightColor") {
        s64 _Arg0 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        s64 _Arg1 = ParseGfxSymbolArg(aGfxData, aNode, &aTokenIndex, "");
        // due to the function taking in the variable name instead of the actual value
        // as a parameter, we need to do this. LIGHT_1 to LIGHT_8 go from actual 1-8
        // where as G_MWO_a*/G_MWO_b* are hex numbers without a linear pattern of
        // progression, meaning there isn't a simple one line solution for this afaik
        switch(_Arg0) {
            case LIGHT_1:
                gSPLightColor(aHead++, LIGHT_1, _Arg1);
                break;
            case LIGHT_2:
                gSPLightColor(aHead++, LIGHT_2, _Arg1);
                break;
            case LIGHT_3:
                gSPLightColor(aHead++, LIGHT_3, _Arg1);
                break;
            case LIGHT_4:
                gSPLightColor(aHead++, LIGHT_4, _Arg1);
                break;
            case LIGHT_5:
                gSPLightColor(aHead++, LIGHT_5, _Arg1);
                break;
            case LIGHT_6:
                gSPLightColor(aHead++, LIGHT_6, _Arg1);
                break;
            case LIGHT_7:
                gSPLightColor(aHead++, LIGHT_7, _Arg1);
                break;
            case LIGHT_8:
                gSPLightColor(aHead++, LIGHT_8, _Arg1);
                break;
        }
        return;
    }

    // Unknown
    PrintDataErrorGfx("  ERROR: Unknown gfx symbol: %s", _Symbol.begin());
}

DataNode<Gfx>* DynOS_Gfx_Parse(GfxData* aGfxData, DataNode<Gfx>* aNode) {
    if (aNode->mData) return aNode;

    // Display list data
    u32 _Length = aNode->mTokens.Count() * DISPLAY_LIST_SIZE_PER_TOKEN;
    aNode->mData = gfx_allocate_internal(NULL, _Length);
    Gfx* _Head = aNode->mData;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseGfxSymbol(aGfxData, aNode, _Head, _TokenIndex);
    }
    aNode->mSize = (u32) (_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    memmove(aNode->mData + aNode->mSize, aNode->mData + _Length, sizeof(Gfx)); // Move the sentinel to the true end of the display list
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
    _Node->mData = gfx_allocate_internal(NULL, _Node->mSize);
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

  /////////
 // Lua //
/////////

//
// Parameter specifiers for gfx_set_command:
//
// %i -> integer
// %s -> string
// %v -> Vtx pointer
// %t -> Texture pointer
// %g -> Gfx pointer
//

static String CreateRawPointerDataNode(GfxData *aGfxData, void *pointer) {
    String ptrNodeName = String("PTR_%016llX", (u64) pointer);
    DataNode<void> *ptrNode = New<DataNode<void>>();
    ptrNode->mName = ptrNodeName;
    ptrNode->mData = pointer;
    aGfxData->mRawPointers.Add(ptrNode);
    return ptrNodeName;
}

template <typename T, typename SmluaToFunc, typename ReturnFunc>
static String ConvertParam(lua_State *L, GfxData *aGfxData, u32 paramIndex, const char *typeName, const SmluaToFunc &smluaToFunc, const ReturnFunc &returnFunc) {
    T value = smluaToFunc(L, paramIndex);
    if (!gSmLuaConvertSuccess) {
        PrintDataErrorGfx("  ERROR: Failed to convert parameter %u to %s", paramIndex, typeName);
        return "";
    }
    return returnFunc(value);
}

static String ResolveParam(lua_State *L, GfxData *aGfxData, u32 paramIndex, char paramType) {
    switch (paramType) {

        // Integer
        case 'i': return ConvertParam<s64>(
            L, aGfxData, paramIndex,
            "integer",
            [] (lua_State *L, u32 paramIndex) { return smlua_to_integer(L, paramIndex); },
            [] (s64 integer) { return String("%lld", integer); }
        );

        // String
        case 's': return ConvertParam<const char *>(
            L, aGfxData, paramIndex,
            "string",
            [] (lua_State *L, u32 paramIndex) { return smlua_to_string(L, paramIndex); },
            [] (const char *string) { return String(string); }
        );

        // Vtx pointer
        case 'v': return ConvertParam<Vtx *>(
            L, aGfxData, paramIndex,
            "Vtx pointer",
            [] (lua_State *L, u32 paramIndex) { return (Vtx *) smlua_to_cobject(L, paramIndex, LOT_VTX); },
            [&aGfxData] (Vtx *vtx) { return CreateRawPointerDataNode(aGfxData, vtx); }
        );

        // Texture pointer
        case 't': return ConvertParam<Texture *>(
            L, aGfxData, paramIndex,
            "Texture pointer",
            [] (lua_State *L, u32 paramIndex) { return (Texture *) smlua_to_cpointer(L, paramIndex, LVT_U8_P); },
            [&aGfxData] (Texture *texture) { return CreateRawPointerDataNode(aGfxData, texture); }
        );

        // Gfx pointer
        case 'g': return ConvertParam<Gfx *>(
            L, aGfxData, paramIndex,
            "Gfx pointer",
            [] (lua_State *L, u32 paramIndex) { return (Gfx *) smlua_to_cobject(L, paramIndex, LOT_GFX); },
            [&aGfxData] (Gfx *gfx) { return CreateRawPointerDataNode(aGfxData, gfx); }
        );
    }
    PrintDataErrorGfx("  ERROR: Unknown parameter type: '%c'", paramType);
    return "";
}

static std::string ResolveGfxCommand(lua_State *L, GfxData *aGfxData, const char *command) {
    std::string output;
    for (u32 paramIndex = 3; *command; command++) {
        char c = *command;
        if (c == '%') {
            char paramType = *(++command);
            String value = ResolveParam(L, aGfxData, paramIndex++, paramType);
            if (aGfxData->mErrorCount > 0) {
                return "";
            }
            output.append(value.begin());
        } else {
            output += c;
        }
    }
    return output;
}

static Array<String> TokenizeGfxCommand(const std::string &command) {
    Array<String> tokens;
    String token;
    for (u32 i = 0, scope = 0; i < command.length(); ++i) {
        char c = command[i];

        // Remove whitespaces
        if (c <= ' ') {
            continue;
        }

        if (c == '(') {

            // End of the command name, beginning of the arguments
            if (scope == 0) {
                if (!token.Empty()) {
                    tokens.Add(token);
                    token.Clear();
                }
            }

            // That's an argument
            else {
                token.Add(c);
            }

            scope++;
        }

        else if (c == ')') {
            scope--;

            // End of the command
            if (scope == 0) {
                break;
            }

            // That's an argument
            else {
                token.Add(c);
            }
        }

        // End of an argument
        else if (c == ',') {
            if (!token.Empty()) {
                tokens.Add(token);
                token.Clear();
            }
        }

        else {
            token.Add(c);
        }
    }
    if (!token.Empty()) {
        tokens.Add(token);
    }
    return tokens;
}

static bool CheckGfxLength(GfxData *aGfxData, Gfx *gfx, u32 lengthToWrite) {
    if (lengthToWrite > 1) {
        u32 gfxLength = gfx_get_length(gfx);
        if (gfxLength < lengthToWrite) {
            PrintDataErrorGfx("  ERROR: Cannot write %u commands to display list of length: %u", lengthToWrite, gfxLength);
            return false;
        }
    }
    return true;
}

static bool ParseGfxCommand(lua_State *L, GfxData *aGfxData, Gfx *gfx, const char *command, bool hasSpecifiers) {

    // Resolve command
    std::string resolved = hasSpecifiers ? ResolveGfxCommand(L, aGfxData, command) : command;
    if (aGfxData->mErrorCount > 0) {
        return false;
    }

    // Check cache
    const auto &it = sGfxCommandCache.find(resolved);
    if (it != sGfxCommandCache.end()) {
        const Gfx *src = it->second.first;
        u32 length = it->second.second;
        if (!CheckGfxLength(aGfxData, gfx, length)) {
            return false;
        }
        memcpy(gfx, src, length * sizeof(Gfx));
        return true;
    }

    // Tokenize command
    DataNode<Gfx> aNode;
    aNode.mTokens = TokenizeGfxCommand(resolved);
    if (aGfxData->mErrorCount > 0) {
        return false;
    }

    // Parse tokenized command
    u64 aTokenIndex = 0;
    Gfx gfxBuffer[16] = {0};
    Gfx *gfxHead = gfxBuffer;
    ParseGfxSymbol(aGfxData, &aNode, gfxHead, aTokenIndex);
    if (aGfxData->mErrorCount > 0) {
        return false;
    }

    // Cache parsed command
    u32 commandLength = (u32) (gfxHead - gfxBuffer);
    size_t commandSize = commandLength * sizeof(Gfx);
    Gfx *cached = (Gfx *) malloc(commandSize);
    memcpy(cached, gfxBuffer, commandSize);
    sGfxCommandCache[resolved] = { cached, commandLength };

    // Copy buffer to gfx
    if (!CheckGfxLength(aGfxData, gfx, commandLength)) {
        return false;
    }
    memcpy(gfx, gfxBuffer, commandLength * sizeof(Gfx));
    return true;
}

extern "C" {

bool dynos_smlua_parse_gfx_command(lua_State *L, Gfx *gfx, const char *command, bool hasSpecifiers, char *errorMsg, u32 errorSize) {

    // Parse command
    GfxData aGfxData;
    sGfxCommandErrorMsg = errorMsg;
    sGfxCommandErrorSize = errorSize;
    bool ok = ParseGfxCommand(L, &aGfxData, gfx, command, hasSpecifiers);

    // Clear stuff
    sGfxCommandErrorMsg = NULL;
    sGfxCommandErrorSize = 0;
    for (auto &ptrNode : aGfxData.mRawPointers) {
        Delete(ptrNode);
    }

    return ok;
}

void dynos_smlua_clear_gfx_command_cache() {
    for (auto &cached : sGfxCommandCache) {
        free(cached.second.first);
    }
    sGfxCommandCache.clear();
}

}
