#include "djui.h"
#include "game/segment2.h"

struct SmCodeGlyph {
    char unicode[3];
    char base;
    f32 width;
};

struct SmCodeGlyph sSmCodeGlyphs[] = {
    { "Á", 'A', 0 },
    { "Å", 'A', 0 },
    { "Â", 'A', 0 },
    { "À", 'A', 0 },
    { "Ã", 'A', 0 },
    { "Ä", 'A', 0 },
    { "Ç", 'C', 0 },
    { "É", 'E', 0 },
    { "Ê", 'E', 0 },
    { "È", 'E', 0 },
    { "Ë", 'E', 0 },
    { "Í", 'I', 0 },
    { "Î", 'I', 0 },
    { "Ì", 'I', 0 },
    { "Ï", 'I', 0 },
    { "Ñ", 'N', 0 },
    { "Ó", 'O', 0 },
    { "Ô", 'O', 0 },
    { "Ò", 'O', 0 },
    { "Õ", 'O', 0 },
    { "Ö", 'O', 0 },
    { "Ú", 'U', 0 },
    { "Û", 'U', 0 },
    { "Ù", 'U', 0 },
    { "Ü", 'U', 0 },
    { "Ý", 'Y', 0 },
    { "Ÿ", 'Y', 0 },

    { "á", 'a', 0 },
    { "å", 'a', 0 },
    { "â", 'a', 0 },
    { "à", 'a', 0 },
    { "ã", 'a', 0 },
    { "ä", 'a', 0 },
    { "ç", 'c', 0 },
    { "é", 'e', 0 },
    { "ê", 'e', 0 },
    { "è", 'e', 0 },
    { "ë", 'e', 0 },
    { "í", 'i', 0 },
    { "î", 'i', 0 },
    { "ì", 'i', 0 },
    { "ï", 'i', 0 },
    { "ñ", 'n', 0 },
    { "ó", 'o', 0 },
    { "ô", 'o', 0 },
    { "ò", 'o', 0 },
    { "õ", 'o', 0 },
    { "ö", 'o', 0 },
    { "ú", 'u', 0 },
    { "û", 'u', 0 },
    { "ù", 'u', 0 },
    { "ü", 'u', 0 },
    { "ý", 'y', 0 },
    { "ÿ", 'y', 0 },

    { "æ", 'a', 0.5000f },
    { "Æ", 'a', 0.6000f },
    { "œ", 'o', 0.5000f },
    { "Œ", 'o', 0.5000f },
    { "ð", 'd', 0 },
    { "Ð", 'D', 0.4375f },
    { "ø", 'o', 0 },
    { "Ø", 'O', 0 },
    { "ß", 'S', 0 },

    { "¡", '!', 0 },
    { "¿", '?', 0 },
};


u8 djui_font_convert_smcode_to_base(char c) {
    if ((u8)c < 128) {
        return c;
    }
    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);
    u8 max = 128 + glyphCount;
    if ((u8)c > max) {
        return '?';
    }
    return sSmCodeGlyphs[((u8)c - 128)].base;
}

void djui_font_convert_to_unicode(char* from, char* to, int length, int maxlength) {
    int clen = 0;
    int count = 0;
    to[0] = '\0';
    while (*from != '\0' && count < length) {
        count++;
        if ((u8)*from < 128 || !djui_font_valid_smcode(*from)) {
            clen = strlen(to);
            snprintf(to + clen, maxlength - clen, "%c", *from);
            from++;
            continue;
        }

        int i = (u8)*from - 128;
        struct SmCodeGlyph* glyph = &sSmCodeGlyphs[i];
        clen = strlen(to);
        snprintf(to + clen, maxlength - clen, "%s", glyph->unicode);

        from++;
    }
}

void djui_font_convert_to_smcode(char* text) {
    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);

    //printf("....................\n");
    //printf("%s\n", text);
    char* t = text;
    while (*t != '\0') {
        //printf("%d ", *t);
        for (size_t i = 0; i < glyphCount; i++) {
            struct SmCodeGlyph* glyph = &sSmCodeGlyphs[i];
            if (t[0] == glyph->unicode[0] && t[1] == glyph->unicode[1]) {
                // consume down to one character
                char* t2 = t;
                while (*t2 != '\0') { t2[0] = t2[1]; t2++; }
                // replace
                t[0] = (s8)(128 + i);
            }
        }
        t++;
    }
    //printf("\n....................\n");
}

bool djui_font_valid_smcode(char c) {
    if (c >= '!' && (u8)c <= ((u8)'~' + 1)) {
        return true;
    } else if (c == ' ') {
        return true;
    }

    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);
    for (size_t i = 0; i < glyphCount; i++) {
        if ((u8)c == ((u8)(128 + i))) { return true; }
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

    if ((u8)c < 128) {
        return font_normal_widths[(u8)c - '!'];
    }

    size_t glyphCount = sizeof(sSmCodeGlyphs) / sizeof(sSmCodeGlyphs[0]);
    u8 max = 128 + glyphCount;
    if ((u8)c > max) {
        return font_normal_widths[(u8)'?' - '!'];
    }

    if (sSmCodeGlyphs[(u8)c - 128].width > 0) {
        return sSmCodeGlyphs[(u8)c - 128].width;
    }

    c = djui_font_convert_smcode_to_base(c);
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