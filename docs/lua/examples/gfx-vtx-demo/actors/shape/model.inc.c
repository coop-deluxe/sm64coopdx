// The template display list.
// Some values are placeholders that will be filled during the custom GEO ASM function.
Gfx shape_template_dl[] = {
    gsSPGeometryMode(0, 0),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(NULL, G_IM_FMT_RGBA, G_IM_SIZ_32b, 512, 512, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(NULL, 0, 0),
    gsSPDisplayList(NULL),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
