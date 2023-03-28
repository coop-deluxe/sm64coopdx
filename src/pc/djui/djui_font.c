#include "djui.h"
#include "game/segment2.h"

struct SmCodeGlyph {
    s8 unicode1;
    s8 unicode2;
    u8 smcode;
};

struct SmCodeGlyph sSmCodeGlyphs[] = {
    { -61, -95,  128 }, // á
    { -61, -87,  129 }, // é
    { -61, -83,  130 }, // í
    { -61, -77,  131 }, // ó
    { -61, -70,  132 }, // ú
    { -61, -68,  133 }, // ü
    { -61, -79,  134 }, // ñ
    { -61, -127, 135 }, // Á
    { -61, -119, 136 }, // É
    { -61, -115, 137 }, // Í
    { -61, -109, 138 }, // Ó
    { -61, -102, 139 }, // Ú
    { -61, -100, 140 }, // Ü
    { -61, -111, 141 }, // Ñ
    { -62, -95,  142 }, // ¡
    { -62, -65,  143 }, // ¿

    { -61, -96,  144 }, // à
    { -61, -94,  145 }, // â
    { -61, -93,  146 }, // ã
    { -61, -86,  147 }, // ê
    { -61, -76,  148 }, // ô
    { -61, -75,  149 }, // õ
    { -61, -89,  150 }, // ç
    { -61, -128, 151 }, // À
    { -61, -126, 152 }, // Â
    { -61, -125, 153 }, // Ã
    { -61, -118, 154 }, // Ê
    { -61, -108, 155 }, // Ô
    { -61, -107, 156 }, // Õ
    { -61, -121, 157 }, // Ç
};

void djui_font_convert_to_smcode(char* text) {
    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);

    //printf("....................\n");
    //printf("%s\n", text);
    char* t = text;
    while (*t != '\0') {
        //printf("%d ", *t);
        for (size_t i = 0; i < glyphCount; i++) {
            struct SmCodeGlyph* glyph = &sSmCodeGlyphs[i];
            if (t[0] == glyph->unicode1 && t[1] == glyph->unicode2) {
                // consume down to one character
                char* t2 = t;
                while (*t2 != '\0') { t2[0] = t2[1]; t2++; }
                // replace
                t[0] = (s8)glyph->smcode;
            }
        }
        t++;
    }
    //printf("\n....................\n");
}

bool djui_font_valid_smcode(char c) {
    if (c >= '!' && c <= '~') {
        return true;
    } else if (c == ' ') {
        return true;
    }

    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);
    for (size_t i = 0; i < glyphCount; i++) {
        struct SmCodeGlyph* glyph = &sSmCodeGlyphs[i];
        if ((u8)c == glyph->smcode) { return true; }
    }

    return false;
}

  ///////////////////////////////////
 // font 0 (built-in normal font) //
///////////////////////////////////

static Vtx djui_font_normal_vertices[] = {
    {{{ 0, -1, 0}, 0, {   0, 256}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0.5f, -1, 0}, 0, {   0,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0.5f,  0, 0}, 0, { 512,   0}, { 0xff, 0xff, 0xff, 0xff }}},
    {{{ 0,   0, 0}, 0, { 512, 256}, { 0xff, 0xff, 0xff, 0xff }}},
};

const Gfx dl_font_normal_display_list_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

const Gfx dl_font_normal_display_list[] = {
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((16 * 8 + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1, CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsSPVertex(djui_font_normal_vertices, 4, 0),
    gsSPExecuteDjui(G_TEXCLIP_DJUI),
    gsSP2Triangles(0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

static void djui_font_normal_render_char(char c) {
    extern const u8* const font_normal_chars[];
    // replace undisplayable characters
    //if ((u8)c < ' ' || (u8)c > ('~' + 3)) { c = '?'; }
    if (!djui_font_valid_smcode(c)) { c = '?'; }
    if (c == ' ') { return; }
    void* fontChar = (void*)font_normal_chars[(u8)c - '!'];
    if (fontChar == NULL) { fontChar = (void*)font_normal_chars[94]; }

    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (void*)fontChar);
    gSPDisplayList(gDisplayListHead++, dl_font_normal_display_list);
}

static f32 djui_font_normal_char_width(char c) {
    if (c == ' ') { return 0.30f; }
    extern const f32 font_normal_widths[];
    return font_normal_widths[(u8)c - '!'];
}

static const struct DjuiFont sDjuiFontNormal = {
    .charWidth            = 0.5f,
    .charHeight           = 1.0f,
    .lineHeight           = 0.8125f,
    .defaultFontScale     = 32.0f,
    .rotatedUV            = true,
    .textBeginDisplayList = dl_font_normal_display_list_begin,
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
    if (c == ' ') { return; }
    djui_gfx_render_texture(font_title_chars[c - '!'], 64, 64, 32);
}

static f32 djui_font_title_char_width(char c) {
    if (c == ' ') { return 0.30f; }
    extern const f32 font_title_widths[];
    return font_title_widths[(u8)c - '!'];
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
    if (c == ' ') { return; }
    u8 index = djui_font_hud_index(c);
    djui_gfx_render_texture(main_hud_lut[index], 16, 16, 16);
}

static f32 djui_font_hud_char_width(char c) {
    if (c == ' ') { return 0.5; }
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