#ifndef DJUI_GFX_UTILS_H
#define DJUI_GFX_UTILS_H

enum GfxUtilsResolution {
    RESOLUTION_DJUI,
    RESOLUTION_N64,
    RESOLUTION_COUNT,
};

enum DjuiFontType {
    FONT_NORMAL,
    FONT_MENU,
    FONT_HUD,
    FONT_COUNT,
};

void djui_gfx_set_resolution(enum GfxUtilsResolution resolutionType);
void djui_gfx_set_font(enum DjuiFontType fontType);
void djui_gfx_set_color(u8 r, u8 g, u8 b, u8 a);

u32 djui_gfx_get_screen_width(void);
u32 djui_gfx_get_screen_height(void);

f32 djui_gfx_measure_text(const char* message);
void djui_gfx_print_text(const char* message, float x, float y, float scale);

#endif