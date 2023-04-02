#include "djui.h"
#include "djui_unicode.h"
#include "game/segment2.h"

  ///////////////////////////////////
 // font 0 (built-in normal font) //
///////////////////////////////////

static void djui_font_normal_render_char(char* c) {
    // replace undisplayable characters
    if (*c == ' ') { return; }

    u32 index = djui_unicode_get_sprite_index(c);
    u32 tx = index % 32;
    u32 ty = index / 32;

    extern ALIGNED8 const u8 texture_font_normal[];
    djui_gfx_render_texture_tile(texture_font_normal, 512, 256, 32, tx * 16 + 1, ty * 32, 16, 32);
}

static f32 djui_font_normal_char_width(char* c) {
    if (*c == ' ') { return 0.30f; }
    extern const f32 font_normal_widths[];
    return djui_unicode_get_sprite_width(c, font_normal_widths);
}

static const struct DjuiFont sDjuiFontNormal = {
    .charWidth            = 0.5f,
    .charHeight           = 1.0f,
    .lineHeight           = 0.8125f,
    .defaultFontScale     = 32.0f,
    .textBeginDisplayList = NULL,
    .render_char          = djui_font_normal_render_char,
    .char_width           = djui_font_normal_char_width,
};

  ////////////////////////////////
 // font 1 (custom title font) //
////////////////////////////////

static void djui_font_title_render_char(char* text) {
    char c = *text;
    extern const u8* const font_title_chars[];
    // replace undisplayable characters
    if (c == ' ') { return; }
    c = djui_unicode_get_base_char(text);
    djui_gfx_render_texture(font_title_chars[c - '!'], 64, 64, 32);
}

static f32 djui_font_title_char_width(char* text) {
    char c = *text;
    if (c == ' ') { return 0.30f; }
    c = djui_unicode_get_base_char(text);
    extern const f32 font_title_widths[];
    return font_title_widths[(u8)c - '!'];
}

static const struct DjuiFont sDjuiFontTitle = {
    .charWidth            = 1.0f,
    .charHeight           = 0.9f,
    .lineHeight           = 0.7f,
    .defaultFontScale     = 64.0f,
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
    if ((u8)c < ' ' || (u8)c > 127) { return 50; }

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

static void djui_font_hud_render_char(char* text) {
    char c = *text;
    if (c == ' ') { return; }
    c = djui_unicode_get_base_char(text);
    u8 index = djui_font_hud_index(c);
    djui_gfx_render_texture(main_hud_lut[index], 16, 16, 16);
}

static f32 djui_font_hud_char_width(char* text) {
    char c = *text;
    if (c == ' ') { return 0.5; }
    return 0.75f;
}

static const struct DjuiFont sDjuiFontHud = {
    .charWidth            = 1.0f,
    .charHeight           = 0.9f,
    .lineHeight           = 0.7f,
    .defaultFontScale     = 16.0f,
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