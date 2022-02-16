#include <stdio.h>
#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "pc/gfx/gfx_pc.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"

#include "djui_gfx.h"
#include "gfx_dimensions.h"
#include "config.h"
#include "djui.h"
#include "djui_hud_utils.h"

static enum HudUtilsResolution sResolution = RESOLUTION_DJUI;
static enum DjuiFontType sFont = FONT_NORMAL;

extern ALIGNED8 const u8 texture_hud_char_camera[];
extern ALIGNED8 const u8 texture_hud_char_lakitu[];
extern ALIGNED8 const u8 texture_hud_char_no_camera[];
extern ALIGNED8 const u8 texture_hud_char_arrow_up[];
extern ALIGNED8 const u8 texture_hud_char_arrow_down[];
extern ALIGNED8 const u8 texture_hud_char_coin[];
extern ALIGNED8 const u8 texture_hud_char_star[];

struct GlobalTextures gGlobalTextures = {
    .camera     = { .texture = texture_hud_char_camera,     .bitSize = 8, .width = 16, .height = 16 },
    .lakitu     = { .texture = texture_hud_char_lakitu,     .bitSize = 8, .width = 16, .height = 16 },
    .no_camera  = { .texture = texture_hud_char_no_camera,  .bitSize = 8, .width = 16, .height = 16 },
    .arrow_up   = { .texture = texture_hud_char_arrow_up,   .bitSize = 8, .width =  8, .height =  8 },
    .arrow_down = { .texture = texture_hud_char_arrow_down, .bitSize = 8, .width =  8, .height =  8 },
    .coin       = { .texture = texture_hud_char_coin,       .bitSize = 8, .width = 16, .height = 16 },
    .star       = { .texture = texture_hud_char_star,       .bitSize = 8, .width = 16, .height = 16 },
};

static void djui_hud_position_translate(f32* x, f32* y) {
    if (sResolution == RESOLUTION_DJUI) {
        djui_gfx_position_translate(x, y);
    } else {
        *x = GFX_DIMENSIONS_FROM_LEFT_EDGE(0) + *x;
        *y = SCREEN_HEIGHT - *y;
    }
}

static void djui_hud_size_translate(f32* size) {
    if (sResolution == RESOLUTION_DJUI) {
        djui_gfx_size_translate(size);
    }
}

void djui_hud_set_resolution(enum HudUtilsResolution resolutionType) {
    if (resolutionType >= RESOLUTION_COUNT) { return; }
    sResolution = resolutionType;
}

void djui_hud_set_font(enum DjuiFontType fontType) {
    if (fontType >= FONT_COUNT) { return; }
    sFont = fontType;
}

void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a) {
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

u32 djui_hud_get_screen_width(void) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    return (sResolution == RESOLUTION_N64)
        ? (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT)
        : (windowWidth / djui_gfx_get_scale());
}

u32 djui_hud_get_screen_height(void) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    return (sResolution == RESOLUTION_N64)
        ? SCREEN_HEIGHT
        : (windowHeight / djui_gfx_get_scale());
}

f32 djui_hud_measure_text(const char* message) {
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

void djui_hud_print_text(const char* message, float x, float y, float scale) {
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
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // compute font size
    f32 translatedFontSize = fontScale;
    djui_hud_size_translate(&translatedFontSize);
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

static void djui_hud_render_texture_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // translate scale
    f32 translatedW = scaleW;
    f32 translatedH = scaleH;
    djui_hud_size_translate(&translatedW);
    djui_hud_size_translate(&translatedH);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width * translatedW, height * translatedH, 1.0f);

    // render
    djui_gfx_render_texture(texture, width, height, bitSize);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    djui_hud_render_texture_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->width, x, y, scaleW, scaleH);
}

