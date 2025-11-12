/*
Both define_gfx_symbol and define_gfx_symbol_manual have the same parameters.
1 - Gfx command name
2 - The number of parameters the command should take
3 - Whether or not DynOS should store an internal pointer to this command.
All parameters after are representing the type that parameter should have in the gfx command, specifically for use in gfx_set_command.
Types:
GFX_PARAM_TYPE_INT - integer
GFX_PARAM_TYPE_STR - string
GFX_PARAM_TYPE_PTR - Undefined pointer type
GFX_PARAM_TYPE_VTX - Vtx pointer
GFX_PARAM_TYPE_TEX - Texture pointer
GFX_PARAM_TYPE_GFX - Gfx pointer
*/

define_gfx_symbol(gsDPFullSync, 0, false);
define_gfx_symbol(gsDPTileSync, 0, false);
define_gfx_symbol(gsDPPipeSync, 0, false);
define_gfx_symbol(gsDPLoadSync, 0, false);
define_gfx_symbol(gsDPNoOp, 0, false);
define_gfx_symbol(gsDPNoOpTag, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetCycleType, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPLight, 2, true, GFX_PARAM_TYPE_PTR, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPVertex, 3, true, GFX_PARAM_TYPE_VTX, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSP1Triangle, 4, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSP2Triangles, 8, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPNumLights, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetDepthSource, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetTextureLUT, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPLoadBlock, 5, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetRenderMode, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPGeometryMode, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPGeometryModeSetFirst, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetPrimColor, 6, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetEnvColor, 4, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetEnvRGB, 3, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetFogColor, 4, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPFogPosition, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetAlphaCompare, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetTextureFilter, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetTexturePersp, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetTextureLOD, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetTextureConvert, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPCullDisplayList, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetAlphaDither, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetCombineKey, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPPipelineMode, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPSetOtherMode, 4, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetTextureDetail, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetColorDither, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetPrimDepth, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsDPSetBlendColor, 4, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPCopyLightEXT, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPCopyLightsPlayerPart, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPFogFactor, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsMoveWd, 3, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPLoadGeometryMode, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPVertexNonGlobal, 3, true, GFX_PARAM_TYPE_VTX, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPCopyPlayerPartToColor, 3, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol(gsSPFresnel, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);

define_gfx_symbol_manual(gsSPTexture, 5, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsSPSetGeometryMode, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsSPClearGeometryMode, 1, false, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsSPDisplayList, 1, true, GFX_PARAM_TYPE_GFX);
define_gfx_symbol_manual(gsSPBranchList, 1, true, GFX_PARAM_TYPE_GFX);
define_gfx_symbol_manual(gsSPEndDisplayList, 0, false);
define_gfx_symbol_manual(gsSPSetLights0, 1, true, GFX_PARAM_TYPE_PTR);
define_gfx_symbol_manual(gsSPSetLights1, 1, true, GFX_PARAM_TYPE_PTR);
define_gfx_symbol_manual(gsDPSetCombineMode, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPSetCombineLERP, 16, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPSetTextureImage, 4, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_TEX);
define_gfx_symbol_manual(gsDPSetTile, 12, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPLoadTile, 5, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPSetTileSize, 5, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPLoadTextureBlock, 12, true, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPLoadTLUTCmd, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPLoadTLUT_pal16, 2, true, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPLoadTLUT_pal256, 1, true, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsDPLoadTextureBlock_4b, 11, true, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
define_gfx_symbol_manual(gsSPLightColor, 2, false, GFX_PARAM_TYPE_INT, GFX_PARAM_TYPE_INT);
