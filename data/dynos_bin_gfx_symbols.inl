/*
    Parameters are, in this order:
      1  : Symbol category (0 for manual definition and 1 for automatic).
      2  : Symbol name.
      3  : Number of arguments.
      4  : Type(s) of the pointer to store for this command.
      5+ : Type of the arguments in the order they appear in the command. Needed for `gfx_set_command`.
    Pointer types are available in `data/dynos.cpp.h`.
    Argument types are the following:
    - GFX_PARAM_INT = integer
    - GFX_PARAM_STR = string
    - GFX_PARAM_PTR = Undefined pointer type
    - GFX_PARAM_VTX = Vtx pointer
    - GFX_PARAM_TEX = Texture pointer
    - GFX_PARAM_GFX = Gfx pointer
*/

GFX_SYMBOL(1, gsDPFullSync,              0,  0)
GFX_SYMBOL(1, gsDPTileSync,              0,  0)
GFX_SYMBOL(1, gsDPPipeSync,              0,  0)
GFX_SYMBOL(1, gsDPLoadSync,              0,  0)
GFX_SYMBOL(1, gsDPNoOp,                  0,  0)
GFX_SYMBOL(1, gsDPNoOpTag,               1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetCycleType,          1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPLight,                 2,  PTYPE_PNTR_LIGHT|PTYPE_PNTR_LIGHT0|PTYPE_PNTR_LIGHTT|PTYPE_PNTR_AMBIENTT, GFX_PARAM_PTR, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPVertex,                3,  PTYPE_PNTR_VTX,    GFX_PARAM_VTX, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSP1Triangle,             4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSP2Triangles,            8,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPNumLights,             1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetDepthSource,        1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetTextureLUT,         1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPLoadBlock,             5,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetRenderMode,         2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPGeometryMode,          2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPGeometryModeSetFirst,  2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetPrimColor,          6,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetEnvColor,           4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetEnvRGB,             3,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetFogColor,           4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPFogPosition,           2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetAlphaCompare,       1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetTextureFilter,      1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetTexturePersp,       1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetTextureLOD,         1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetTextureConvert,     1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPCullDisplayList,       2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetAlphaDither,        1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetCombineKey,         1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPPipelineMode,          1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPSetOtherMode,          4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetTextureDetail,      1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetColorDither,        1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetPrimDepth,          2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetBlendColor,         4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPCopyLightEXT,          2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPCopyLightsPlayerPart,  1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPFogFactor,             2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsMoveWd,                  3,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPLoadGeometryMode,      1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPVertexNonGlobal,       3,  PTYPE_PNTR_VTX,    GFX_PARAM_VTX, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPCopyPlayerPartToColor, 3,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPFresnel,               2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsDPSetColorImage,         4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPNoOp,                  0,  0)
GFX_SYMBOL(1, gsSPMatrix,                2,  0,                 GFX_PARAM_PTR, GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPLoadState,             1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(1, gsSPSaveState,             1,  0,                 GFX_PARAM_INT)

GFX_SYMBOL(0, gsSPTexture,               5,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsSPSetGeometryMode,       1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(0, gsSPClearGeometryMode,     1,  0,                 GFX_PARAM_INT)
GFX_SYMBOL(0, gsSPDisplayList,           1,  PTYPE_PNTR_GFX,    GFX_PARAM_GFX)
GFX_SYMBOL(0, gsSPBranchList,            1,  PTYPE_PNTR_GFX,    GFX_PARAM_GFX)
GFX_SYMBOL(0, gsSPEndDisplayList,        0,  0)
GFX_SYMBOL(0, gsSPSetLights0,            1,  PTYPE_PNTR_LIGHT0, GFX_PARAM_PTR)
GFX_SYMBOL(0, gsSPSetLights1,            1,  PTYPE_PNTR_LIGHT,  GFX_PARAM_PTR)
GFX_SYMBOL(0, gsDPSetCombineMode,        2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPSetCombineLERP,        16, 0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPSetTextureImage,       4,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_TEX)
GFX_SYMBOL(0, gsDPSetTile,               12, 0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPLoadTile,              5,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPSetTileSize,           5,  0,                 GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPLoadTextureBlock,      12, PTYPE_PNTR_TEX,    GFX_PARAM_TEX, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPLoadTLUTCmd,           2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsDPLoadTLUT_pal16,        2,  PTYPE_PNTR_TEX,    GFX_PARAM_INT, GFX_PARAM_TEX)
GFX_SYMBOL(0, gsDPLoadTLUT_pal256,       1,  PTYPE_PNTR_TEX,    GFX_PARAM_TEX)
GFX_SYMBOL(0, gsDPLoadTextureBlock_4b,   11, PTYPE_PNTR_TEX,    GFX_PARAM_TEX, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT,
                                                                GFX_PARAM_INT, GFX_PARAM_INT, GFX_PARAM_INT)
GFX_SYMBOL(0, gsSPLightColor,            2,  0,                 GFX_PARAM_INT, GFX_PARAM_INT)
