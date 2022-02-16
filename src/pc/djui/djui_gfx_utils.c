#include <stdio.h>
#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "pc/gfx/gfx_pc.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"

#include "gfx_dimensions.h"
#include "config.h"
#include "djui.h"
#include "djui_gfx_utils.h"

static enum GfxUtilsResolution sResolution = RESOLUTION_DJUI;
static enum DjuiFontType sFont = FONT_NORMAL;

void djui_gfx_set_resolution(enum GfxUtilsResolution resolutionType) {
    if (resolutionType >= RESOLUTION_COUNT) { return; }
    sResolution = resolutionType;
}

void djui_gfx_set_font(enum DjuiFontType fontType) {
    if (fontType >= FONT_COUNT) { return; }
    sFont = fontType;
}

void djui_gfx_set_color(u8 r, u8 g, u8 b, u8 a) {
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

u32 djui_gfx_get_screen_width(void) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    return (sResolution == RESOLUTION_N64)
        ? (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT)
        : (windowWidth / djui_gfx_get_scale());
}

u32 djui_gfx_get_screen_height(void) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    return (sResolution == RESOLUTION_N64)
        ? SCREEN_HEIGHT
        : (windowHeight / djui_gfx_get_scale());
}

f32 djui_gfx_measure_text(const char* message) {
    if (message == NULL) { return 0; }
    const struct DjuiFont* font = gDjuiFonts[sFont];
    f32 width = 0;
    const char* c = message;
    while(*c != '\0') {
        width += font->char_width(*c);
        c++;
    }
    return width * font->defaultFontScale;
}

void djui_gfx_print_text(const char* message, float x, float y, float scale) {
    if (message == NULL) { return; }
    const struct DjuiFont* font = gDjuiFonts[sFont];
    f32 fontScale = font->defaultFontScale * scale;

    // setup display list
    if (font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);
    }

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    if (sResolution == RESOLUTION_DJUI) {
        djui_gfx_position_translate(&translatedX, &translatedY);
    } else if (sResolution == RESOLUTION_N64) {
        translatedX = GFX_DIMENSIONS_FROM_LEFT_EDGE(0) + x;
        translatedY = SCREEN_HEIGHT - y;
    }
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // compute font size
    f32 translatedFontSize = fontScale;
    if (sResolution == RESOLUTION_DJUI) {
        djui_gfx_size_translate(&translatedFontSize);
    }
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // render the line
    f32 addX = 0;
    size_t length = strlen(message);
    for (size_t i = 0; i < length; i++) {
        char c = message[i];
        f32 charWidth = font->char_width(c);

        if (c == '\n' && c == ' ') {
            addX += charWidth;
            continue;
        }

        // render
        font->render_char(c);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, charWidth + addX, 0, 0);
        addX = 0;
    }

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_gfx_utils_render(void) {
    //struct DjuiColor fore = { .r = 255, .g = 255, .b = 255, .a = 255 };
    //struct DjuiColor back = { .r = 0, .g = 0, .b = 0, .a = 255 };
    //const struct DjuiFont* font = gDjuiFonts[2];
    //djui_gfx_print_text(font, "abcdefghijklmnopqrstuvwxyz:1234567890", 2, 2, 2, back);
    //djui_gfx_print_text(font, "1234567890:abcdefghijklmnopqrstuvwxyz", 0, 0, 2, fore);
    //float scale = 240.0f / gfx_current_dimensions.height;

    /*{
        f32 screenWidth = djui_gfx_get_screen_width(RESOLUTION_N64);
        f32 width = djui_gfx_measure_text(font, "PAUSE", RESOLUTION_N64);

        f32 screenHeight = djui_gfx_get_screen_height(RESOLUTION_N64);
        f32 height = 16;

        djui_gfx_print_text(font, "PAUSE", screenWidth - width, screenHeight - height - 32, 1.0f, fore, RESOLUTION_N64);
        djui_gfx_print_text(font, "PAUSE", screenWidth - width * 2, screenHeight - height, 1.0f, fore, RESOLUTION_N64);
    }*/

    /*{
        f32 screenWidth = djui_gfx_get_screen_width(RESOLUTION_DJUI);
        f32 width = djui_gfx_measure_text(font, "PAUSE", RESOLUTION_DJUI);

        f32 screenHeight = djui_gfx_get_screen_height(RESOLUTION_DJUI);
        f32 height = 16;

        djui_gfx_print_text(FONT_NORMAL, "PAUSE", screenWidth - width, screenHeight - height - 32, 1.0f, fore, RESOLUTION_DJUI);
        djui_gfx_print_text(FONT_NORMAL, "PAUSE", screenWidth - width * 2, screenHeight - height, 1.0f, fore, RESOLUTION_DJUI);
    }*/
}