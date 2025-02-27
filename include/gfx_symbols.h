// To use this macro, define `define_gfx_symbol` before including this file.

#define GFX_SYMBOLS()                                   \
define_gfx_symbol(gsDPFullSync, 0);                     \
define_gfx_symbol(gsDPTileSync, 0);                     \
define_gfx_symbol(gsDPPipeSync, 0);                     \
define_gfx_symbol(gsDPLoadSync, 0);                     \
define_gfx_symbol(gsDPNoOp, 0);                         \
define_gfx_symbol(gsDPNoOpTag, 1, false);               \
define_gfx_symbol(gsDPSetCycleType, 1, false);          \
define_gfx_symbol(gsSPLight, 2, true);                  \
define_gfx_symbol(gsSPVertex, 3, true);                 \
define_gfx_symbol(gsSP1Triangle, 4);                    \
define_gfx_symbol(gsSP2Triangles, 8);                   \
define_gfx_symbol(gsSPNumLights, 1, false);             \
define_gfx_symbol(gsDPSetDepthSource, 1, false);        \
define_gfx_symbol(gsDPSetTextureLUT, 1, false);         \
define_gfx_symbol(gsDPLoadBlock, 5);                    \
define_gfx_symbol(gsDPSetRenderMode, 2, false);         \
define_gfx_symbol(gsSPGeometryMode, 2, false);          \
define_gfx_symbol(gsSPGeometryModeSetFirst, 2, false);  \
define_gfx_symbol(gsDPSetPrimColor, 6);                 \
define_gfx_symbol(gsDPSetEnvColor, 4);                  \
define_gfx_symbol(gsDPSetFogColor, 4);                  \
define_gfx_symbol(gsSPFogPosition, 2, false);           \
define_gfx_symbol(gsDPSetAlphaCompare, 1, false);       \
define_gfx_symbol(gsDPSetTextureFilter, 1, false);      \
define_gfx_symbol(gsSPCullDisplayList, 2, false);       \
define_gfx_symbol(gsDPSetAlphaDither, 1, false);        \
define_gfx_symbol(gsDPSetCombineKey, 1, false);         \
define_gfx_symbol(gsDPSetTextureConvert, 1, false);     \
define_gfx_symbol(gsDPSetCombineKey, 1, false);         \
define_gfx_symbol(gsDPSetTextureConvert, 1, false);     \
define_gfx_symbol(gsDPPipelineMode, 1, false);          \
define_gfx_symbol(gsSPSetOtherMode, 4);                 \
define_gfx_symbol(gsDPSetTextureDetail, 1, false);      \
define_gfx_symbol(gsDPSetColorDither, 1, false);        \
define_gfx_symbol(gsDPSetPrimDepth, 2, false);          \
define_gfx_symbol(gsDPSetBlendColor, 4);                \
                                                        \
define_gfx_symbol(gsSPCopyLightEXT, 2, false);          \
define_gfx_symbol(gsSPCopyLightsPlayerPart, 1, false);  \
define_gfx_symbol(gsSPFogFactor, 2, false);             \
define_gfx_symbol(gsDPSetTextureLOD, 1, false);         \
define_gfx_symbol(gsMoveWd, 3, false);                  \
define_gfx_symbol(gsSPVertexNonGlobal, 3, true);
