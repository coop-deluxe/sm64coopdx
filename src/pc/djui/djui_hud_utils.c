#include <stdio.h>
#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <string.h>

#include "pc/controller/controller_mouse.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"
#include "pc/utils/misc.h"

#include "djui_gfx.h"
#include "gfx_dimensions.h"
#include "config.h"
#include "djui.h"
#include "djui_unicode.h"
#include "djui_hud_utils.h"
#include "djui_panel_pause.h"
#include "game/camera.h"
#include "game/hud.h"
#include "game/rendering_graph_node.h"
#include "game/first_person_cam.h"
#include "pc/lua/smlua.h"

#include "engine/math_util.h"

static enum HudUtilsResolution sResolution = RESOLUTION_DJUI;
static enum HudUtilsFilter sFilter = FILTER_NEAREST;
static enum DjuiFontType sFont = FONT_NORMAL;
static struct HudUtilsRotation sRotation = { 0, 0, 0, 0, 0, 0 };
static struct DjuiColor sColor = { 255, 255, 255, 255 };
static struct DjuiColor sRefColor = { 255, 255, 255, 255 };
static bool sLegacy = false;

f32 gDjuiHudUtilsZ = 0;
u8 gDjuiHudLockMouse = false;

extern ALIGNED8 const u8 texture_hud_char_camera[];
extern ALIGNED8 const u8 texture_hud_char_lakitu[];
extern ALIGNED8 const u8 texture_hud_char_no_camera[];
extern ALIGNED8 const u8 texture_hud_char_arrow_up[];
extern ALIGNED8 const u8 texture_hud_char_arrow_down[];
extern ALIGNED8 const u8 texture_hud_char_coin[];
extern ALIGNED8 const u8 texture_hud_char_star[];
extern ALIGNED8 const u8 texture_hud_char_mario_head[];
extern ALIGNED8 const u8 texture_hud_char_luigi_head[];
extern ALIGNED8 const u8 texture_hud_char_toad_head[];
extern ALIGNED8 const u8 texture_hud_char_waluigi_head[];
extern ALIGNED8 const u8 texture_hud_char_wario_head[];
extern ALIGNED8 const u8 texture_hud_char_apostrophe[];
extern ALIGNED8 const u8 texture_hud_char_double_quote[];

struct GlobalTextures gGlobalTextures = {
    .camera       = { .texture = (u8*)texture_hud_char_camera,       .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_camera"       },
    .lakitu       = { .texture = (u8*)texture_hud_char_lakitu,       .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_lakitu"       },
    .no_camera    = { .texture = (u8*)texture_hud_char_no_camera,    .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_no_camera"    },
    .arrow_up     = { .texture = (u8*)texture_hud_char_arrow_up,     .bitSize = 8, .width =  8, .height =  8, "texture_hud_char_arrow_up"     },
    .arrow_down   = { .texture = (u8*)texture_hud_char_arrow_down,   .bitSize = 8, .width =  8, .height =  8, "texture_hud_char_arrow_down"   },
    .coin         = { .texture = (u8*)texture_hud_char_coin,         .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_coin"         },
    .star         = { .texture = (u8*)texture_hud_char_star,         .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_star"         },
    .apostrophe   = { .texture = (u8*)texture_hud_char_apostrophe,   .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_apostrophe"   },
    .double_quote = { .texture = (u8*)texture_hud_char_double_quote, .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_double_quote" },
    .mario_head   = { .texture = (u8*)texture_hud_char_mario_head,   .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_mario_head"   },
    .luigi_head   = { .texture = (u8*)texture_hud_char_luigi_head,   .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_luigi_head"   },
    .toad_head    = { .texture = (u8*)texture_hud_char_toad_head,    .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_toad_head"    },
    .waluigi_head = { .texture = (u8*)texture_hud_char_waluigi_head, .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_waluigi_head" },
    .wario_head   = { .texture = (u8*)texture_hud_char_wario_head,   .bitSize = 8, .width = 16, .height = 16, "texture_hud_char_wario_head"   }
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

  ////////////
 // interp //
////////////

#define MAX_INTERP_HUD 512
struct InterpHud {
    Gfx* headPos;
    f32 z;
    f32 prevX;
    f32 prevY;
    f32 x;
    f32 y;
    f32 prevScaleW;
    f32 prevScaleH;
    f32 scaleW;
    f32 scaleH;
    f32 width;
    f32 height;
    enum HudUtilsResolution resolution;
    struct HudUtilsRotation rotation;
};
static struct InterpHud sInterpHuds[MAX_INTERP_HUD] = { 0 };
static u16 sInterpHudCount = 0;
static u8 sColorAltered = FALSE;

void patch_djui_hud_before(void) {
    sInterpHudCount = 0;
}

void patch_djui_hud(f32 delta) {
    f32 savedZ = gDjuiHudUtilsZ;
    Gfx* savedHeadPos = gDisplayListHead;
    enum HudUtilsResolution savedResolution = sResolution;
    struct HudUtilsRotation savedRotation = sRotation;
    for (u16 i = 0; i < sInterpHudCount; i++) {
        struct InterpHud* interp = &sInterpHuds[i];
        f32 x = delta_interpolate_f32(interp->prevX, interp->x, delta);
        f32 y = delta_interpolate_f32(interp->prevY, interp->y, delta);
        f32 scaleW = delta_interpolate_f32(interp->prevScaleW, interp->scaleW, delta);
        f32 scaleH = delta_interpolate_f32(interp->prevScaleH, interp->scaleH, delta);
        sResolution = interp->resolution;
        sRotation = interp->rotation;

        gDjuiHudUtilsZ = interp->z;
        gDisplayListHead = interp->headPos;

        // translate position
        f32 translatedX = x;
        f32 translatedY = y;
        djui_hud_position_translate(&translatedX, &translatedY);
        create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

        // rotate
        f32 translatedW = scaleW;
        f32 translatedH = scaleH;
        djui_hud_size_translate(&translatedW);
        djui_hud_size_translate(&translatedH);
        if (sRotation.rotationDiff != 0 || sRotation.rotation != 0) {
            s32 rotation = delta_interpolate_s32(sRotation.rotation - sRotation.rotationDiff, sRotation.rotation, delta);
            f32 pivotX = delta_interpolate_f32(sRotation.prevPivotX, sRotation.pivotX, delta);
            f32 pivotY = delta_interpolate_f32(sRotation.prevPivotY, sRotation.pivotY, delta);
            f32 pivotTranslationX = interp->width * translatedW * pivotX;
            f32 pivotTranslationY = interp->height * translatedH * pivotY;
            create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
            create_dl_rotation_matrix(DJUI_MTX_NOPUSH, rotation, 0, 0, 1);
            create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
        }

        // scale
        create_dl_scale_matrix(DJUI_MTX_NOPUSH, interp->width * translatedW, interp->height * translatedH, 1.0f);
    }
    sResolution = savedResolution;
    sRotation = savedRotation;
    gDisplayListHead = savedHeadPos;
    gDjuiHudUtilsZ = savedZ;
}

  ////////////
 // others //
////////////

u8 djui_hud_get_resolution(void) {
    return sResolution;
}

void djui_hud_set_resolution(enum HudUtilsResolution resolutionType) {
    if (resolutionType >= RESOLUTION_COUNT) { return; }
    sResolution = resolutionType;
}

u8 djui_hud_get_filter(void) {
    return sFilter;
}

void djui_hud_set_filter(enum HudUtilsFilter filterType) {
    if (filterType >= FILTER_COUNT) { return; }
    sFilter = filterType;
}

u8 djui_hud_get_font(void) {
    return sFont;
}

void djui_hud_set_font(s8 fontType) {
    if (fontType >= FONT_COUNT || fontType < -1) { return; }
    sLegacy = fontType == -1;
    if (sLegacy) { fontType = 0; }
    sFont = fontType;
}

struct DjuiColor* djui_hud_get_color(void) {
    sRefColor.r = sColor.r;
    sRefColor.g = sColor.g;
    sRefColor.b = sColor.b;
    sRefColor.a = sColor.a;
    return &sRefColor;
}

void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a) {
    sColor.r = r;
    sColor.g = g;
    sColor.b = b;
    sColor.a = a;
    sColorAltered = TRUE;
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

void djui_hud_reset_color(void) {
    if (sColorAltered) {
        sColor.r = 255;
        sColor.g = 255;
        sColor.b = 255;
        sColor.a = 255;
        sColorAltered = FALSE;
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    }
}

struct HudUtilsRotation* djui_hud_get_rotation(void) {
    return &sRotation;
}

void djui_hud_set_rotation(s16 rotation, f32 pivotX, f32 pivotY) {
    sRotation.rotationDiff = 0;
    sRotation.prevPivotX = pivotX;
    sRotation.prevPivotY = pivotY;
    sRotation.rotation = (rotation * 180.f) / 0x8000;
    sRotation.pivotX = pivotX;
    sRotation.pivotY = pivotY;
}

void djui_hud_set_rotation_interpolated(s32 prevRotation, f32 prevPivotX, f32 prevPivotY, s32 rotation, f32 pivotX, f32 pivotY) {
    f32 normalizedDiff = ((rotation - prevRotation + 0x8000) & 0xFFFF) - 0x8000; // Fix modular overflow/underflow
    sRotation.rotationDiff = (normalizedDiff * 180.f) / 0x8000;
    sRotation.prevPivotX = prevPivotX;
    sRotation.prevPivotY = prevPivotY;
    sRotation.rotation = (rotation * 180.f) / 0x8000;
    sRotation.pivotX = pivotX;
    sRotation.pivotY = pivotY;
}

u32 djui_hud_get_screen_width(void) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    if (sResolution == RESOLUTION_N64) {
        return (GFX_DIMENSIONS_ASPECT_RATIO) * SCREEN_HEIGHT;
    } else {
        return (windowWidth / djui_gfx_get_scale());
    }
}

u32 djui_hud_get_screen_height(void) {
    u32 windowWidth, windowHeight;
    wm_api->get_dimensions(&windowWidth, &windowHeight);

    return (sResolution == RESOLUTION_N64)
        ? SCREEN_HEIGHT
        : (windowHeight / djui_gfx_get_scale());
}

f32 djui_hud_get_mouse_x(void) {
    controller_mouse_read_window();
    return mouse_window_x / djui_gfx_get_scale();
}

f32 djui_hud_get_mouse_y(void) {
    controller_mouse_read_window();
    return mouse_window_y / djui_gfx_get_scale();
}

f32 djui_hud_get_raw_mouse_x(void) {
    return mouse_x;
}

f32 djui_hud_get_raw_mouse_y(void) {
    return mouse_y;
}

void djui_hud_set_mouse_locked(bool locked) {
    gDjuiHudLockMouse = locked;
}

f32 djui_hud_measure_text(const char* message) {
    if (message == NULL) { return 0; }
    const struct DjuiFont* font = gDjuiFonts[sFont];
    f32 width = 0;
    const char* c = message;
    while(*c != '\0') {
        width += font->char_width((char*)c) * (sLegacy ? 0.5f : 1.0f);
        c = djui_unicode_next_char((char*)c);
    }
    return width * font->defaultFontScale;
}

void djui_hud_print_text(const char* message, f32 x, f32 y, f32 scale) {
    if (message == NULL) { return; }
    gDjuiHudUtilsZ += 0.01f;

    if (sLegacy) { scale *= 0.5f; }

    const struct DjuiFont* font = gDjuiFonts[sFont];
    f32 fontScale = font->defaultFontScale * scale;

    // setup display list
    if (font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);
    }

    // translate position
    f32 translatedX = x + (font->xOffset * scale);
    f32 translatedY = y + (font->yOffset * scale);
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // compute font size
    f32 translatedFontSize = fontScale;
    djui_hud_size_translate(&translatedFontSize);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // render the line
    f32 addX = 0;
    char* c = (char*)message;
    while (*c != '\0') {
        f32 charWidth = font->char_width(c);

        if (*c == '\n' && *c == ' ') {
            addX += charWidth;
            c++;
            continue;
        }

        // render
        font->render_char(c);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, charWidth + addX, 0, 0);
        addX = 0;

        c = djui_unicode_next_char(c);
    }

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_print_text_interpolated(const char* message, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale) {
    if (message == NULL) { return; }
    f32 savedZ = gDjuiHudUtilsZ;
    gDjuiHudUtilsZ += 0.01f;

    if (sLegacy) {
        prevScale *= 0.5f;
        scale *= 0.5f;
    }

    const struct DjuiFont* font = gDjuiFonts[sFont];
    f32 fontScale = font->defaultFontScale * scale;

    // setup display list
    if (font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);
    }

    Gfx* savedHeadPos = gDisplayListHead;

    // translate position
    f32 translatedX = x + (font->xOffset * scale);
    f32 translatedY = y + (font->yOffset * scale);
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // compute font size
    f32 translatedFontSize = fontScale;
    djui_hud_size_translate(&translatedFontSize);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // render the line
    f32 addX = 0;
    char* c = (char*)message;
    while (*c != '\0') {
        f32 charWidth = font->char_width(c);

        if (*c == '\n' && *c == ' ') {
            addX += charWidth;
            c++;
            continue;
        }

        // render
        font->render_char(c);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, charWidth + addX, 0, 0);
        addX = 0;

        c = djui_unicode_next_char(c);
    }

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    if (sInterpHudCount >= MAX_INTERP_HUD) { return; }
    struct InterpHud* interp = &sInterpHuds[sInterpHudCount++];
    interp->headPos = savedHeadPos;
    interp->prevX = prevX + (font->xOffset * prevScale);
    interp->prevY = prevY + (font->yOffset * prevScale);
    interp->prevScaleW = prevScale;
    interp->prevScaleH = prevScale;
    interp->x = x;
    interp->y = y;
    interp->scaleW = scale;
    interp->scaleH = scale;
    interp->width = font->defaultFontScale;
    interp->height = font->defaultFontScale;
    interp->z = savedZ;
    interp->resolution = sResolution;
    interp->rotation = sRotation;
}

static inline bool is_power_of_two(u32 n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

void djui_hud_render_texture_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    if (!is_power_of_two(width) || !is_power_of_two(height)) {
        LOG_LUA_LINE("Tried to render DJUI HUD texture with NPOT width or height");
        return;
    }

    gDjuiHudUtilsZ += 0.01f;

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // rotate
    f32 translatedW = scaleW;
    f32 translatedH = scaleH;
    djui_hud_size_translate(&translatedW);
    djui_hud_size_translate(&translatedH);
    if (sRotation.rotation != 0) {
        f32 pivotTranslationX = width * translatedW * sRotation.pivotX;
        f32 pivotTranslationY = height * translatedH * sRotation.pivotY;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sRotation.rotation, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // translate scale
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width * translatedW, height * translatedH, 1.0f);

    // render
    djui_gfx_render_texture(texture, width, height, bitSize, sFilter);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_render_texture_tile_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH) {
    gDjuiHudUtilsZ += 0.01f;
    scaleW *= (f32) tileW / (f32) width;
    scaleH *= (f32) tileH / (f32) height;

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // rotate
    f32 translatedW = scaleW;
    f32 translatedH = scaleH;
    djui_hud_size_translate(&translatedW);
    djui_hud_size_translate(&translatedH);
    if (sRotation.rotation != 0) {
        f32 aspect = tileH ? ((f32) tileW / (f32) tileH) : 1.f;
        f32 pivotTranslationX = width * translatedW * aspect * sRotation.pivotX;
        f32 pivotTranslationY = height * translatedH * sRotation.pivotY;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sRotation.rotation, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // translate scale
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width * translatedW, height * translatedH, 1.0f);

    // render
    djui_gfx_render_texture_tile(texture, width, height, bitSize, tileX, tileY, tileW, tileH, sFilter, false);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    djui_hud_render_texture_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->height, x, y, scaleW, scaleH);
}

void djui_hud_render_texture_tile(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH) {
    djui_hud_render_texture_tile_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->height, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH);
}

void djui_hud_render_texture_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    Gfx* savedHeadPos = gDisplayListHead;
    f32 savedZ = gDjuiHudUtilsZ;

    djui_hud_render_texture_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->height, prevX, prevY, prevScaleW, prevScaleH);

    if (sInterpHudCount >= MAX_INTERP_HUD) { return; }
    struct InterpHud* interp = &sInterpHuds[sInterpHudCount++];
    interp->headPos = savedHeadPos;
    interp->prevX = prevX;
    interp->prevY = prevY;
    interp->prevScaleW = prevScaleW;
    interp->prevScaleH = prevScaleH;
    interp->x = x;
    interp->y = y;
    interp->scaleW = scaleW;
    interp->scaleH = scaleH;
    interp->width = texInfo->width;
    interp->height = texInfo->height;
    interp->z = savedZ;
    interp->resolution = sResolution;
    interp->rotation = sRotation;
}

void djui_hud_render_texture_tile_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH) {
    Gfx* savedHeadPos = gDisplayListHead;
    f32 savedZ = gDjuiHudUtilsZ;

    djui_hud_render_texture_tile_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->height, prevX, prevY, prevScaleW, prevScaleH, tileX, tileY, tileW, tileH);

    if (sInterpHudCount >= MAX_INTERP_HUD) { return; }
    struct InterpHud* interp = &sInterpHuds[sInterpHudCount++];
    interp->headPos = savedHeadPos;
    interp->prevX = prevX;
    interp->prevY = prevY;
    interp->prevScaleW = prevScaleW;
    interp->prevScaleH = prevScaleH;
    interp->x = x;
    interp->y = y;
    interp->scaleW = scaleW;
    interp->scaleH = scaleH;
    interp->width = texInfo->width;
    interp->height = texInfo->height;
    interp->z = savedZ;
    interp->resolution = sResolution;
    interp->rotation = sRotation;
}

void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height) {
    gDjuiHudUtilsZ += 0.01f;

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // rotate
    f32 translatedW = width;
    f32 translatedH = height;
    djui_hud_size_translate(&translatedW);
    djui_hud_size_translate(&translatedH);
    if (sRotation.rotation != 0) {
        f32 pivotTranslationX = translatedW * sRotation.pivotX;
        f32 pivotTranslationY = translatedH * sRotation.pivotY;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sRotation.rotation, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // translate scale
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedW, translatedH, 1.0f);

    // render
    gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_render_rect_interpolated(f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height) {
    Gfx* savedHeadPos = gDisplayListHead;
    f32 savedZ = gDjuiHudUtilsZ;

    djui_hud_render_rect(prevX, prevY, prevWidth, prevHeight);

    if (sInterpHudCount >= MAX_INTERP_HUD) { return; }
    struct InterpHud* interp = &sInterpHuds[sInterpHudCount++];
    interp->headPos = savedHeadPos;
    interp->prevX = prevX;
    interp->prevY = prevY;
    interp->prevScaleW = prevWidth;
    interp->prevScaleH = prevHeight;
    interp->x = x;
    interp->y = y;
    interp->scaleW = width;
    interp->scaleH = height;
    interp->width = 1;
    interp->height = 1;
    interp->z = savedZ;
    interp->resolution = sResolution;
    interp->rotation = sRotation;
}

static void hud_rotate_and_translate_vec3f(Vec3f vec, Mat4* mtx, Vec3f out) {
    out[0] = (*mtx)[0][0] * vec[0] + (*mtx)[1][0] * vec[1] + (*mtx)[2][0] * vec[2];
    out[1] = (*mtx)[0][1] * vec[0] + (*mtx)[1][1] * vec[1] + (*mtx)[2][1] * vec[2];
    out[2] = (*mtx)[0][2] * vec[0] + (*mtx)[1][2] * vec[1] + (*mtx)[2][2] * vec[2];
    out[0] += (*mtx)[3][0];
    out[1] += (*mtx)[3][1];
    out[2] += (*mtx)[3][2];
}

f32 get_current_fov() {
    return get_first_person_enabled() ? gFirstPersonCamera.fov : not_zero(gFOVState.fov, gOverrideFOV) + gFOVState.fovOffset;
}

f32 djui_hud_get_fov_coeff() {
    // fov of 45.0 is the default fov
    f32 fov = get_current_fov();
    f32 fovDefault = tanf(45.f * ((f32)M_PI / 360.0f));
    f32 fovCurrent = tanf(fov * ((f32)M_PI / 360.0f));

    return (fovDefault / fovCurrent) * 1.13f;
}

bool djui_hud_world_pos_to_screen_pos(Vec3f pos, Vec3f out) {
    if (!gCamera) { return false; }
    hud_rotate_and_translate_vec3f(pos, &gCamera->mtx, out);
    if (out[2] >= 0.0f) {
        return false;
    }

    out[0] *= 256.0f / -out[2];
    out[1] *= 256.0f / out[2];

    f32 fovCoeff = djui_hud_get_fov_coeff();

    out[0] *= fovCoeff;
    out[1] *= fovCoeff;

    f32 screenWidth, screenHeight;
    if (sResolution == RESOLUTION_N64) {
        screenWidth = GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT;
        screenHeight = SCREEN_HEIGHT;
    } else {
        u32 windowWidth, windowHeight;
        WAPI.get_dimensions(&windowWidth, &windowHeight);
        screenWidth = (f32) windowWidth;
        screenHeight = (f32) windowHeight;
    }

    out[0] += screenWidth  / 2.0f;
    out[1] += screenHeight / 2.0f;

    extern Vp *D_8032CE74;
    if (D_8032CE74) {
        Vp_t *viewport = &D_8032CE74->vp;
        f32 width  = viewport->vscale[0] / 2.0f;
        f32 height = viewport->vscale[1] / 2.0f;
        f32 x = (viewport->vtrans[0] / 4.0f) - width / 2.0f;
        f32 y = SCREEN_HEIGHT - ((viewport->vtrans[1] / 4.0f) + height / 2.0f);

        f32 xDiff = screenWidth / SCREEN_WIDTH;
        f32 yDiff = screenHeight / SCREEN_HEIGHT;
        width *= xDiff;
        height *= yDiff;
        x = x * xDiff - 1;
        y = (screenHeight - y * yDiff) - height;

        out[0] = x + (out[0] * (width / screenWidth));
        out[1] = y + (out[1] * (height / screenHeight));
    }

    return true;
}

bool djui_hud_is_pause_menu_created(void) {
    return gDjuiPanelPauseCreated;
}

void djui_open_pause_menu(void) {
    if (!gDjuiPanelPauseCreated) {
        djui_panel_pause_create(NULL);
    }
}
