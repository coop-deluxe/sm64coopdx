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
    djui_gfx_render_texture_tile(texture_font_normal, 512, 256, 32, tx * 16, ty * 32, 16, 32);
}

static f32 djui_font_normal_char_width(char* c) {
    if (*c == ' ') { return 6 / 32.0f; }
    extern const f32 font_normal_widths[];
    return djui_unicode_get_sprite_width(c, font_normal_widths) / 32.0f;
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

static void djui_font_title_render_char(char* c) {
    // replace undisplayable characters
    if (*c == ' ') { return; }

    u32 index = djui_unicode_get_sprite_index(c);
    if ((u8)*c < '!' || (u8)*c > '~' + 1) {
        char tmp[2] = { 0 };
        tmp[0] = djui_unicode_get_base_char(c);
        index = djui_unicode_get_sprite_index(tmp);
    }

    u32 tx = index % 16;
    u32 ty = index / 16;

    extern ALIGNED8 const u8 texture_font_title[];
    djui_gfx_render_texture_tile(texture_font_title, 1024, 512, 32, tx * 64, ty * 64, 64, 64);
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
    if ((u8)c < ' ' || (u8)c > 127) { return 41; }

    switch (c) {
        case '!':  return 36;
        case '#':  return 37;
        case '?':  return 38;
        case '&':  return 39;
        case '%':  return 40;
        case '@':  return 41;
        case '$':  return 42;
        case ',':  return 43;
        case '*':  return 44;
        case '.':  return 45;
        case '^':  return 46;
        case '\'': return 47;
        case '"':  return 48;
        case '/':  return 49;
        case '-':  return 50;
        case '~':  return 51;
        case '+':  return 52;
    }

    if (c >= '0' && c <= '9') { return 0  + c - '0'; }
    if (c >= 'a' && c <= 'z') { return 10 + c - 'a'; }
    if (c >= 'A' && c <= 'Z') { return 10 + c - 'A'; }

    if (c >= 58) { return 41; }
    if (main_hud_lut[(int)c] == NULL) { return 41; }

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

  /////////////////////////////////
 // font 4 (built-in tiny font) //
/////////////////////////////////

static void djui_font_tiny_render_char(char* c) {
    // replace undisplayable characters
    if (*c == ' ') { return; }

    u32 index = djui_unicode_get_sprite_index(c);
    u32 tx = index % 32;
    u32 ty = index / 32;

    extern ALIGNED8 const u8 texture_font_tiny[];
    djui_gfx_render_texture_tile(texture_font_tiny, 256, 128, 32, tx * 8, ty * 16, 8, 16);
}

static f32 djui_font_tiny_char_width(char* c) {
    if (*c == ' ') { return 0.30f; }
    extern const f32 font_tiny_widths[];
    return djui_unicode_get_sprite_width(c, font_tiny_widths);
}

static const struct DjuiFont sDjuiFontTiny = {
    .charWidth            = 0.5f,
    .charHeight           = 1.0f,
    .lineHeight           = 0.8125f,
    .defaultFontScale     = 16.0f,
    .textBeginDisplayList = NULL,
    .render_char          = djui_font_tiny_render_char,
    .char_width           = djui_font_tiny_char_width,
};

  ///////////////
 // font list //
///////////////

const struct DjuiFont* gDjuiFonts[] = {
    &sDjuiFontNormal,
    &sDjuiFontTitle,
    &sDjuiFontHud,
    &sDjuiFontTiny,
};