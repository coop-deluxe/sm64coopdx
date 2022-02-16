#include "djui.h"
#include "game/segment2.h"

  ///////////////////////////////////
 // font 0 (built-in normal font) //
///////////////////////////////////

static Vtx djui_font_normal_vertices[] = {
    {{{ 0, -1, 0}, 0, {   0, 256}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0.5f, -1, 0}, 0, {   0,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0.5f,  0, 0}, 0, { 512,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,   0, 0}, 0, { 512, 256}, { 0xff, 0xff, 0xff, 0xff }}},
};

static const Gfx djui_font_normal_text_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

static const Gfx djui_font_normal_text_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((16 * 8 + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1, CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(djui_font_normal_vertices, 4, 0),
    gsSPExecuteDjui(G_TEXCLIP_DJUI),
    gsSP2Triangles(0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

static void djui_font_normal_render_char(char c) {
    extern const u8* const font_normal_chars[];
    // replace undisplayable characters
    if (c < ' ' || (u8)c > ('~' + 1)) { c = '?'; }
    void* fontChar = (void*)font_normal_chars[c - '!'];
    if (fontChar == NULL) { fontChar = (void*)font_normal_chars[94]; }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (void*)fontChar);
    gSPDisplayList(gDisplayListHead++, djui_font_normal_text_settings);
}

static f32 djui_font_normal_char_width(char c) {
    if (c == ' ') { return 0.30f; }
    extern const f32 font_normal_widths[];
    return font_normal_widths[c - '!'];
}

static const struct DjuiFont sDjuiFontNormal = {
    .charWidth            = 0.5f,
    .charHeight           = 1.0f,
    .lineHeight           = 0.8125f,
    .defaultFontScale     = 32.0f,
    .rotatedUV            = true,
    .textBeginDisplayList = djui_font_normal_text_begin,
    .render_char          = djui_font_normal_render_char,
    .char_width           = djui_font_normal_char_width,
};

  ////////////////////////////////
 // font 1 (custom title font) //
////////////////////////////////

static void djui_font_title_render_char(char c) {
    extern const u8* const font_title_chars[];
    // replace undisplayable characters
    if (c < ' ' || (u8)c > ('~' + 1)) { c = '?'; }
    djui_gfx_render_texture(font_title_chars[c - '!'], 64, 64, 32);
}

static f32 djui_font_title_char_width(char c) {
    if (c == ' ') { return 0.30f; }
    extern const f32 font_title_widths[];
    return font_title_widths[c - '!'];
}

static const struct DjuiFont sDjuiFontTitle = {
    .charWidth            = 1.0f,
    .charHeight           = 0.9f,
    .lineHeight           = 0.7f,
    .defaultFontScale     = 64.0f,
    .rotatedUV            = false,
    .textBeginDisplayList = NULL,
    .render_char          = djui_font_title_render_char,
    .char_width           = djui_font_title_char_width,
};

  ///////////////////////
 // font 3 (hud font) //
///////////////////////

/*
    texture_hud_char_0, texture_hud_char_1, texture_hud_char_2, texture_hud_char_3,
    texture_hud_char_4, texture_hud_char_5, texture_hud_char_6, texture_hud_char_7,
    texture_hud_char_8, texture_hud_char_9, texture_hud_char_A, texture_hud_char_B,
    texture_hud_char_C, texture_hud_char_D, texture_hud_char_E, texture_hud_char_F,
    texture_hud_char_G, texture_hud_char_H, texture_hud_char_I, texture_hud_char_J,
    texture_hud_char_K, texture_hud_char_L, texture_hud_char_M, texture_hud_char_N,
    texture_hud_char_O, texture_hud_char_P,               0x0, texture_hud_char_R,
    texture_hud_char_S, texture_hud_char_T, texture_hud_char_U,               0x0,
    texture_hud_char_W,               0x0, texture_hud_char_Y, texture_hud_char_waluigi_head,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0, texture_hud_char_multiply, texture_hud_char_coin,
    texture_hud_char_mario_head, texture_hud_char_star, texture_hud_char_luigi_head, texture_hud_char_toad_head,
    texture_hud_char_apostrophe, texture_hud_char_double_quote,
*/

static u8 djui_font_hud_index(char c) {
    if (c == 'q' || c == 'Q') { return 50; }
    if (c == 'v' || c == 'V') { return 50; }
    if (c == 'x' || c == 'X') { return 50; }
    if (c == 'z' || c == 'Z') { return 50; }

    switch (c) {
        case '$':  return 51;
        case '*':  return 53;
        case '\'': return 56;
        case '"':  return 57;
    }

    if (c >= '0' && c <= '9') { return 0  + c - '0'; }
    if (c >= 'a' && c <= 'z') { return 10 + c - 'a'; }
    if (c >= 'A' && c <= 'Z') { return 10 + c - 'A'; }

    if (c >= 58) { return 50; }
    if (main_hud_lut[(int)c] == NULL) { return 50; }

    return c;
}

static void djui_font_hud_render_char(char c) {
    u8 index = djui_font_hud_index(c);
    djui_gfx_render_texture(main_hud_lut[index], 16, 16, 16);
}

static f32 djui_font_hud_char_width(UNUSED char c) {
    return 0.75f;
}

static const struct DjuiFont sDjuiFontHud = {
    .charWidth            = 1.0f,
    .charHeight           = 0.9f,
    .lineHeight           = 0.7f,
    .defaultFontScale     = 16.0f,
    .rotatedUV            = false,
    .textBeginDisplayList = NULL,
    .render_char          = djui_font_hud_render_char,
    .char_width           = djui_font_hud_char_width,
};

  ///////////////
 // font list //
///////////////

const struct DjuiFont* gDjuiFonts[] = {
    &sDjuiFontNormal,
    &sDjuiFontTitle,
    &sDjuiFontHud,
};