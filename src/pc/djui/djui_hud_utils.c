#include <stdio.h>
#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <string.h>

#include "pc/controller/controller_sdl.h"
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


static enum HudUtilsResolution sResolution = RESOLUTION_DJUI;
static enum DjuiFontType sFont = FONT_NORMAL;

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
    .camera     =   { .texture = (u8*)texture_hud_char_camera,       .bitSize = 8, .width = 16, .height = 16 },
    .lakitu     =   { .texture = (u8*)texture_hud_char_lakitu,       .bitSize = 8, .width = 16, .height = 16 },
    .no_camera  =   { .texture = (u8*)texture_hud_char_no_camera,    .bitSize = 8, .width = 16, .height = 16 },
    .arrow_up   =   { .texture = (u8*)texture_hud_char_arrow_up,     .bitSize = 8, .width =  8, .height =  8 },
    .arrow_down =   { .texture = (u8*)texture_hud_char_arrow_down,   .bitSize = 8, .width =  8, .height =  8 },
    .coin       =   { .texture = (u8*)texture_hud_char_coin,         .bitSize = 8, .width = 16, .height = 16 },
    .star       =   { .texture = (u8*)texture_hud_char_star,         .bitSize = 8, .width = 16, .height = 16 },
    .apostrophe =   { .texture = (u8*)texture_hud_char_apostrophe,   .bitSize = 8, .width = 16, .height = 16 },
    .double_quote = { .texture = (u8*)texture_hud_char_double_quote, .bitSize = 8, .width = 16, .height = 16 },
    .mario_head =   { .texture = (u8*)texture_hud_char_mario_head,   .bitSize = 8, .width = 16, .height = 16 },
    .luigi_head =   { .texture = (u8*)texture_hud_char_luigi_head,   .bitSize = 8, .width = 16, .height = 16 },
    .toad_head =    { .texture = (u8*)texture_hud_char_toad_head,    .bitSize = 8, .width = 16, .height = 16 },
    .waluigi_head = { .texture = (u8*)texture_hud_char_waluigi_head, .bitSize = 8, .width = 16, .height = 16 },
    .wario_head =   { .texture = (u8*)texture_hud_char_wario_head,   .bitSize = 8, .width = 16, .height = 16 }
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

#define MAX_INTERP_HUD 128
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
};
static struct InterpHud sInterpHuds[MAX_INTERP_HUD] = { 0 };
static u16 sInterpHudCount = 0;

void patch_djui_hud_before(void) {
    sInterpHudCount = 0;
}

void patch_djui_hud(f32 delta) {
    f32 savedZ = gDjuiHudUtilsZ;
    Gfx* savedHeadPos = gDisplayListHead;
    enum HudUtilsResolution savedResolution = sResolution;
    for (u16 i = 0; i < sInterpHudCount; i++) {
        struct InterpHud* interp = &sInterpHuds[i];
        f32 x = delta_interpolate_f32(interp->prevX, interp->x, delta);
        f32 y = delta_interpolate_f32(interp->prevY, interp->y, delta);
        f32 scaleW = delta_interpolate_f32(interp->prevScaleW, interp->scaleW, delta);
        f32 scaleH = delta_interpolate_f32(interp->prevScaleH, interp->scaleH, delta);
        sResolution = interp->resolution;

        gDjuiHudUtilsZ = interp->z;
        gDisplayListHead = interp->headPos;

        // translate position
        f32 translatedX = x;
        f32 translatedY = y;
        djui_hud_position_translate(&translatedX, &translatedY);
        create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

        // translate scale
        f32 translatedW = scaleW;
        f32 translatedH = scaleH;
        djui_hud_size_translate(&translatedW);
        djui_hud_size_translate(&translatedH);
        create_dl_scale_matrix(DJUI_MTX_NOPUSH, interp->width * translatedW, interp->height * translatedH, 1.0f);
    }
    sResolution = savedResolution;
    gDisplayListHead = savedHeadPos;
    gDjuiHudUtilsZ = savedZ;
}

  ////////////
 // others //
////////////

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

f32 djui_hud_get_mouse_x(void) {
#ifdef HAVE_SDL2
    controller_sdl_read_mouse_window();
#endif
    return mouse_window_x / djui_gfx_get_scale();
}

f32 djui_hud_get_mouse_y(void) {
#ifdef HAVE_SDL2
    controller_sdl_read_mouse_window();
#endif
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
        width += font->char_width((char*)c);
        c = djui_unicode_next_char((char*)c);
    }
    return width * font->defaultFontScale;
}

void djui_hud_print_text(const char* message, float x, float y, float scale) {
    if (message == NULL) { return; }
    gDjuiHudUtilsZ += 0.01f;

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

void djui_hud_render_texture_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    gDjuiHudUtilsZ += 0.01f;

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

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

void djui_hud_render_texture_tile_raw(const u8* texture, u32 bitSize, u32 width, u32 height, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH) {
    gDjuiHudUtilsZ += 0.01f;
    scaleW *= (f32) tileW / (f32) width;
    scaleH *= (f32) tileH / (f32) height;

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // translate scale
    f32 translatedW = scaleW;
    f32 translatedH = scaleH;
    djui_hud_size_translate(&translatedW);
    djui_hud_size_translate(&translatedH);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width * translatedW, height * translatedH, 1.0f);

    // render
    djui_gfx_render_texture_tile(texture, width, height, bitSize, tileX, tileY, tileW, tileH);

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
}

void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height) {
    gDjuiHudUtilsZ += 0.01f;

    // translate position
    f32 translatedX = x;
    f32 translatedY = y;
    djui_hud_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, gDjuiHudUtilsZ);

    // translate scale
    f32 translatedW = width;
    f32 translatedH = height;
    djui_hud_size_translate(&translatedW);
    djui_hud_size_translate(&translatedH);
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
}

static void hud_rotate_and_translate_vec3f(Vec3f vec, Mat4* mtx, Vec3f out) {
    out[0] = (*mtx)[0][0] * vec[0] + (*mtx)[1][0] * vec[1] + (*mtx)[2][0] * vec[2];
    out[1] = (*mtx)[0][1] * vec[0] + (*mtx)[1][1] * vec[1] + (*mtx)[2][1] * vec[2];
    out[2] = (*mtx)[0][2] * vec[0] + (*mtx)[1][2] * vec[1] + (*mtx)[2][2] * vec[2];
    out[0] += (*mtx)[3][0];
    out[1] += (*mtx)[3][1];
    out[2] += (*mtx)[3][2];
}

void djui_hud_world_pos_to_screen_pos(Vec3f pos, Vec3f out) {
    hud_rotate_and_translate_vec3f(pos, &gCamera->mtx, out);
    if (out[2] > -256.0f) {
        return;
    }

    out[0] *= 256.0 / -out[2];
    out[1] *= 256.0 / out[2];
    
    // TODO: this is a hack to correct for the FOV. It only sort of works for the default fov
    out[0] *= 1.135;
    out[1] *= 1.135;

    out[0] += djui_hud_get_screen_width()  / 2.0f;
    out[1] += djui_hud_get_screen_height() / 2.0f;
}

void djui_hud_set_render_behind_hud(bool enable) {
    gDjuiRenderBehindHud = enable;
}

bool djui_hud_is_pause_menu_created(void) {
    return gDjuiPanelPauseCreated;
}
