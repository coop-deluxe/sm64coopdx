// The template display list.
// Some values are placeholders that will be filled during the custom GEO ASM function.
Gfx shape_template_dl[] = {
/* [00] */ gsSPGeometryMode(0, 0),
/* [01] */ gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
/* [02] */ gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
/* [03] */ gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, NULL),
/* [04] */ gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 0 , G_TX_CLAMP, 0, G_TX_NOLOD, G_TX_CLAMP, 0, G_TX_NOLOD),
/* [05] */ gsDPLoadSync(),
/* [06] */ gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, 0),
/* [07] */ gsDPPipeSync(),
/* [08] */ gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 128, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, G_TX_NOLOD, G_TX_CLAMP, 0, G_TX_NOLOD),
/* [09] */ gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 511 << G_TEXTURE_IMAGE_FRAC, 511 << G_TEXTURE_IMAGE_FRAC),
/* [10] */ gsSPVertex(NULL, 0, 0),
/* [11] */ gsSPDisplayList(NULL),
/* [12] */ gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
/* [13] */ gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
/* [14] */ gsSPEndDisplayList(),
};
