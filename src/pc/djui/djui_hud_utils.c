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

#define INTERP_INIT(v) {v, v}
#define INTERP_SET(field, p, c) field.prev = p; field.curr = c;
#define INTERP_RESET(field, c) field.prev = field.curr = c;

typedef struct {
    f32 prev, curr;
} InterpFieldF32;

struct HudUtilsState {
    enum HudUtilsResolution resolution;
    enum HudUtilsFilter filter;
    enum DjuiFontType font;
    struct DjuiColor color;
    struct DjuiColor textColor;
    struct {
        InterpFieldF32 degrees;
        InterpFieldF32 pivotX;
        InterpFieldF32 pivotY;
    } rotation;
    struct {
        InterpFieldF32 h;
        InterpFieldF32 v;
    } textAlignment;
};

static struct HudUtilsState sHudUtilsState = {
    .resolution = RESOLUTION_DJUI,
    .filter = FILTER_NEAREST,
    .font = FONT_NORMAL,
    .color = { 255, 255, 255, 255 },
    .textColor = { 255, 255, 255, 255 },
    .rotation = {
        .degrees = INTERP_INIT(0),
        .pivotX = INTERP_INIT(ROTATION_PIVOT_X_LEFT),
        .pivotY = INTERP_INIT(ROTATION_PIVOT_Y_TOP),
    },
    .textAlignment = {
        .h = INTERP_INIT(TEXT_HALIGN_LEFT),
        .v = INTERP_INIT(TEXT_VALIGN_TOP),
    },
};

static struct DjuiColor sRefColor = { 255, 255, 255, 255 };
static struct DjuiColor sRefTextColor = { 255, 255, 255, 255 };

f32 gDjuiHudUtilsZ = 0;
bool gDjuiHudLockMouse = false;

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
    .camera       = { .texture = texture_hud_char_camera,       "texture_hud_char_camera",       .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .lakitu       = { .texture = texture_hud_char_lakitu,       "texture_hud_char_lakitu",       .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .no_camera    = { .texture = texture_hud_char_no_camera,    "texture_hud_char_no_camera",    .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .arrow_up     = { .texture = texture_hud_char_arrow_up,     "texture_hud_char_arrow_up",     .width =  8, .height =  8, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .arrow_down   = { .texture = texture_hud_char_arrow_down,   "texture_hud_char_arrow_down",   .width =  8, .height =  8, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .coin         = { .texture = texture_hud_char_coin,         "texture_hud_char_coin",         .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .star         = { .texture = texture_hud_char_star,         "texture_hud_char_star",         .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .apostrophe   = { .texture = texture_hud_char_apostrophe,   "texture_hud_char_apostrophe",   .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .double_quote = { .texture = texture_hud_char_double_quote, "texture_hud_char_double_quote", .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .mario_head   = { .texture = texture_hud_char_mario_head,   "texture_hud_char_mario_head",   .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .luigi_head   = { .texture = texture_hud_char_luigi_head,   "texture_hud_char_luigi_head",   .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .toad_head    = { .texture = texture_hud_char_toad_head,    "texture_hud_char_toad_head",    .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .waluigi_head = { .texture = texture_hud_char_waluigi_head, "texture_hud_char_waluigi_head", .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b },
    .wario_head   = { .texture = texture_hud_char_wario_head,   "texture_hud_char_wario_head",   .width = 16, .height = 16, .format = G_IM_FMT_RGBA, .size = G_IM_SIZ_16b }
};

static inline const struct DjuiFont *djui_hud_get_text_font() {
    return gDjuiFonts[sHudUtilsState.font < 0 ? FONT_NORMAL : sHudUtilsState.font];
}

static inline bool djui_hud_text_font_is_legacy() {
    return sHudUtilsState.font < 0;
}

static void djui_hud_position_translate(f32* x, f32* y) {
    if (sHudUtilsState.resolution == RESOLUTION_DJUI) {
        djui_gfx_position_translate(x, y);
    } else {
        *x = GFX_DIMENSIONS_FROM_LEFT_EDGE(0) + *x;
        *y = SCREEN_HEIGHT - *y;
    }
}

static void djui_hud_size_translate(f32* size) {
    if (sHudUtilsState.resolution == RESOLUTION_DJUI) {
        djui_gfx_size_translate(size);
    }
}

// Translates position and scale to N64 resolution
static void djui_hud_translate_positions(f32 *outX, f32 *outY, f32 *outW, f32 *outH) {
    // translate position
    djui_hud_position_translate(outX, outY);
    *outX -= GFX_DIMENSIONS_FROM_LEFT_EDGE(0);
    *outY -= SCREEN_HEIGHT;

    // translate scale
    if (sHudUtilsState.resolution == RESOLUTION_DJUI) {
        u32 windowWidth, windowHeight;
        gfx_get_dimensions(&windowWidth, &windowHeight);
        f32 screenWidth = (f32) windowWidth / djui_gfx_get_scale();
        f32 screenHeight = (f32) windowHeight / djui_gfx_get_scale();
        *outW = (*outW / screenWidth)  * SCREEN_WIDTH;
        *outH = (*outH / screenHeight) * SCREEN_HEIGHT;
    }
}

  ////////////
 // interp //
////////////

enum InterpHudType {
    INTERP_HUD_TRANSLATION,
    INTERP_HUD_ROTATION,
    INTERP_HUD_SCALE,
    INTERP_HUD_HALIGN,
    INTERP_HUD_VALIGN,
    INTERP_HUD_NEW_LINE,
    INTERP_HUD_COLOR,
};

typedef struct {
    enum InterpHudType type;
    Gfx *pos;
    f32 params[1]; // we don't need more for now
} InterpHudGfx;

struct InterpHud {
    f32 z;
    union {
        struct {
            InterpFieldF32 posX, posY;
            InterpFieldF32 scaleX, scaleY;
        };
        struct {
            InterpFieldF32 r, g, b, a;
        };
    };
    f32 width, height;
    struct HudUtilsState state;
    struct GrowingArray *gfx;
};

static struct GrowingArray *sInterpHuds = NULL;
static u32 sInterpHudCount = 0;

static void interp_hud_free(void *ptr) {
    struct InterpHud *interp = ptr;
    if (interp) {
        growing_array_free(&interp->gfx);
        free(interp);
    }
}

void patch_djui_hud_before(void) {
    sInterpHudCount = 0;
}

void patch_djui_hud(f32 delta) {
    f32 savedZ = gDjuiHudUtilsZ;
    Gfx* savedHeadPos = gDisplayListHead;
    struct HudUtilsState savedState = sHudUtilsState;

    for (u32 i = 0; i < sInterpHudCount; i++) {
        struct InterpHud *interp = sInterpHuds->buffer[i];

        f32 x = delta_interpolate_f32(interp->posX.prev, interp->posX.curr, delta);
        f32 y = delta_interpolate_f32(interp->posY.prev, interp->posY.curr, delta);
        f32 scaleW = delta_interpolate_f32(interp->scaleX.prev, interp->scaleX.curr, delta);
        f32 scaleH = delta_interpolate_f32(interp->scaleY.prev, interp->scaleY.curr, delta);
        sHudUtilsState = interp->state;
        gDjuiHudUtilsZ = interp->z;

        for (u32 j = 0; j != interp->gfx->count; ++j) {
            const InterpHudGfx *gfx = interp->gfx->buffer[j];
            gDisplayListHead = gfx->pos;

            switch (gfx->type) {
                case INTERP_HUD_TRANSLATION: {
                    djui_hud_position_translate(&x, &y);
                    create_dl_translation_matrix(DJUI_MTX_PUSH, x, y, gDjuiHudUtilsZ);
                } break;

                case INTERP_HUD_ROTATION: {
                    f32 translatedW = scaleW;
                    f32 translatedH = scaleH;
                    djui_hud_size_translate(&translatedW);
                    djui_hud_size_translate(&translatedH);
                    s16 rotPrev = degrees_to_sm64(sHudUtilsState.rotation.degrees.prev);
                    s16 rotCurr = degrees_to_sm64(sHudUtilsState.rotation.degrees.curr);
                    s32 normalizedDiff = (((s32) rotCurr - (s32) rotPrev + 0x8000) & 0xFFFF) - 0x8000; // Fix modular overflow/underflow
                    s32 rotation = delta_interpolate_s32(rotCurr - normalizedDiff, rotCurr, delta);
                    f32 pivotX = delta_interpolate_f32(sHudUtilsState.rotation.pivotX.prev, sHudUtilsState.rotation.pivotX.curr, delta);
                    f32 pivotY = delta_interpolate_f32(sHudUtilsState.rotation.pivotY.prev, sHudUtilsState.rotation.pivotY.curr, delta);
                    f32 pivotTranslationX = interp->width * translatedW * pivotX;
                    f32 pivotTranslationY = interp->height * translatedH * pivotY;
                    create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
                    create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sm64_to_degrees(rotation), 0, 0, 1);
                    create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
                } break;

                case INTERP_HUD_SCALE: {
                    f32 translatedW = scaleW;
                    f32 translatedH = scaleH;
                    djui_hud_size_translate(&translatedW);
                    djui_hud_size_translate(&translatedH);
                    create_dl_scale_matrix(DJUI_MTX_NOPUSH, interp->width * translatedW, interp->height * translatedH, 1.0f);
                } break;

                case INTERP_HUD_HALIGN: {
                    f32 textHAlign = delta_interpolate_f32(sHudUtilsState.textAlignment.h.prev, sHudUtilsState.textAlignment.h.curr, delta);
                    f32 lineWidth = gfx->params[0];
                    create_dl_translation_matrix(DJUI_MTX_NOPUSH, -lineWidth * textHAlign, 0, 0);
                } break;

                case INTERP_HUD_VALIGN: {
                    f32 textVAlign = delta_interpolate_f32(sHudUtilsState.textAlignment.v.prev, sHudUtilsState.textAlignment.v.curr, delta);
                    f32 textHeight = gfx->params[0];
                    create_dl_translation_matrix(DJUI_MTX_NOPUSH, 0, textHeight * textVAlign, 0);
                } break;

                case INTERP_HUD_NEW_LINE: {
                    const struct DjuiFont *font = djui_hud_get_text_font();
                    f32 textHAlign = delta_interpolate_f32(sHudUtilsState.textAlignment.h.prev, sHudUtilsState.textAlignment.h.curr, delta);
                    f32 lineWidth = gfx->params[0];
                    create_dl_translation_matrix(DJUI_MTX_NOPUSH, -lineWidth * (1.f - textHAlign), -font->lineHeight, 0);
                } break;

                case INTERP_HUD_COLOR: {
                    gDPSetEnvColor(gDisplayListHead++, x, y, scaleW, scaleH);
                } break;
            }
        }
    }

    sHudUtilsState = savedState;
    gDisplayListHead = savedHeadPos;
    gDjuiHudUtilsZ = savedZ;
}

static struct InterpHud *djui_hud_create_interp() {
    struct InterpHud *interp = (
        sInterpHudCount < sInterpHuds->count ?
        sInterpHuds->buffer[sInterpHudCount] :
        growing_array_alloc(sInterpHuds, sizeof(struct InterpHud))
    );

    if (interp) {
        interp->z = gDjuiHudUtilsZ;
        interp->state = sHudUtilsState;
        if (!interp->gfx) {
            interp->gfx = growing_array_init(NULL, 8, malloc, free);
        } else {
            interp->gfx->count = 0;
        }
        sInterpHudCount++;
    }

    return interp;
}

static InterpHudGfx *djui_hud_create_interp_gfx(struct InterpHud *interp, enum InterpHudType type) {
    if (!interp) { return NULL; }

    InterpHudGfx *gfx = growing_array_alloc(interp->gfx, sizeof(InterpHudGfx));
    gfx->type = type;
    gfx->pos = gDisplayListHead;
    return gfx;
}

void djui_hud_clear_interp_data() {
    sInterpHuds = growing_array_init(sInterpHuds, 16, malloc, interp_hud_free);
    sInterpHudCount = 0;
}

  ////////////
 // others //
////////////

u8 djui_hud_get_resolution(void) {
    return sHudUtilsState.resolution;
}

void djui_hud_set_resolution(enum HudUtilsResolution resolutionType) {
    if (resolutionType >= RESOLUTION_COUNT) { return; }
    sHudUtilsState.resolution = resolutionType;
}

u8 djui_hud_get_filter(void) {
    return sHudUtilsState.filter;
}

void djui_hud_set_filter(enum HudUtilsFilter filterType) {
    if (filterType >= FILTER_COUNT) { return; }
    sHudUtilsState.filter = filterType;
}

s8 djui_hud_get_font(void) {
    return sHudUtilsState.font;
}

void djui_hud_set_font(s8 fontType) {
    if (fontType >= FONT_COUNT || fontType < -1) { return; }
    sHudUtilsState.font = fontType;
}

struct DjuiColor* djui_hud_get_color(void) {
    sRefColor.r = sHudUtilsState.color.r;
    sRefColor.g = sHudUtilsState.color.g;
    sRefColor.b = sHudUtilsState.color.b;
    sRefColor.a = sHudUtilsState.color.a;
    return &sRefColor;
}

void djui_hud_set_color(u8 r, u8 g, u8 b, u8 a) {
    sHudUtilsState.color.r = r;
    sHudUtilsState.color.g = g;
    sHudUtilsState.color.b = b;
    sHudUtilsState.color.a = a;
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

void djui_hud_set_color_interpolated(u8 prevR, u8 prevG, u8 prevB, u8 prevA, u8 r, u8 g, u8 b, u8 a) {
    struct InterpHud *interp = djui_hud_create_interp();
    if (interp) {
        INTERP_SET(interp->r, prevR, r);
        INTERP_SET(interp->g, prevG, g);
        INTERP_SET(interp->b, prevB, b);
        INTERP_SET(interp->a, prevA, a);

        djui_hud_create_interp_gfx(interp, INTERP_HUD_COLOR);
    }

    djui_hud_set_color(r, g, b, a);
}


void djui_hud_reset_color(void) {
    sHudUtilsState.color.r = 255;
    sHudUtilsState.color.g = 255;
    sHudUtilsState.color.b = 255;
    sHudUtilsState.color.a = 255;
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
}

struct DjuiColor* djui_hud_get_text_color(void) {
    sRefTextColor.r = sHudUtilsState.textColor.r;
    sRefTextColor.g = sHudUtilsState.textColor.g;
    sRefTextColor.b = sHudUtilsState.textColor.b;
    sRefTextColor.a = sHudUtilsState.textColor.a;
    return &sRefTextColor;
}

void djui_hud_set_text_color(u8 r, u8 g, u8 b, u8 a) {
    sHudUtilsState.textColor.r = r;
    sHudUtilsState.textColor.g = g;
    sHudUtilsState.textColor.b = b;
    sHudUtilsState.textColor.a = a;
}

void djui_hud_reset_text_color(void) {
    sHudUtilsState.textColor.r = 255;
    sHudUtilsState.textColor.g = 255;
    sHudUtilsState.textColor.b = 255;
    sHudUtilsState.textColor.a = 255;
}

void djui_hud_set_combiner_cycles(u8 cycles) {
    gCombinerState.cycles = cycles != 2 ? 1 : 2;
}

void djui_hud_set_combiner(u8 cycle, bool alpha,
    OPTIONAL enum CombinerSource a, OPTIONAL enum CombinerSource b, OPTIONAL enum CombinerSource c, OPTIONAL enum CombinerSource d) {
    if (--cycle > 1) { return; }

    struct CombinerPart *part = (struct CombinerPart*) gCombinerState.cycle[cycle][alpha];
    if (a > CS_KEEP) { part->a = a; }
    if (b > CS_KEEP) { part->b = b; }
    if (c > CS_KEEP) { part->c = c; }
    if (d > CS_KEEP) { part->d = d; }

    gCombinerUpdated = true;
    gCombinerOverride = true;
}

void djui_hud_reset_combiner() {
    gCombinerState.cycles = 1;
    gCombinerOverride = false;
}

void djui_hud_get_rotation(RET s16 *rotation, RET f32 *pivotX, RET f32 *pivotY) {
    *rotation = degrees_to_sm64(sHudUtilsState.rotation.degrees.curr);
    *pivotX = sHudUtilsState.rotation.pivotX.curr;
    *pivotY = sHudUtilsState.rotation.pivotY.curr;
}

void djui_hud_set_rotation(s16 rotation, OPTIONAL f32 pivotX, OPTIONAL f32 pivotY) {
    INTERP_RESET(sHudUtilsState.rotation.degrees, sm64_to_degrees(rotation));
    INTERP_RESET(sHudUtilsState.rotation.pivotX, pivotX);
    INTERP_RESET(sHudUtilsState.rotation.pivotY, pivotY);
}

void djui_hud_set_rotation_interpolated(s16 prevRotation, f32 prevPivotX, f32 prevPivotY, s16 rotation, f32 pivotX, f32 pivotY) {
    INTERP_SET(sHudUtilsState.rotation.degrees, sm64_to_degrees(prevRotation), sm64_to_degrees(rotation));
    INTERP_SET(sHudUtilsState.rotation.pivotX, prevPivotX, pivotX);
    INTERP_SET(sHudUtilsState.rotation.pivotY, prevPivotY, pivotY);
}

void djui_hud_get_text_alignment(RET f32 *textHAlign, RET f32 *textVAlign) {
    *textHAlign = sHudUtilsState.textAlignment.h.curr;
    *textVAlign = sHudUtilsState.textAlignment.v.curr;
}

void djui_hud_set_text_alignment(f32 textHAlign, f32 textVAlign) {
    INTERP_RESET(sHudUtilsState.textAlignment.h, textHAlign);
    INTERP_RESET(sHudUtilsState.textAlignment.v, textVAlign);
}

void djui_hud_set_text_alignment_interpolated(f32 prevTextHAlign, f32 prevTextVAlign, f32 textHAlign, f32 textVAlign) {
    INTERP_SET(sHudUtilsState.textAlignment.h, prevTextHAlign, textHAlign);
    INTERP_SET(sHudUtilsState.textAlignment.v, prevTextVAlign, textVAlign);
}

u32 djui_hud_get_screen_width(void) {
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);

    return (sHudUtilsState.resolution == RESOLUTION_N64)
        ? GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT
        : (windowWidth / djui_gfx_get_scale());
}

u32 djui_hud_get_screen_height(void) {
    u32 windowWidth, windowHeight;
    gfx_get_dimensions(&windowWidth, &windowHeight);

    return (sHudUtilsState.resolution == RESOLUTION_N64)
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

bool djui_hud_is_mouse_locked(void) {
    return gDjuiHudLockMouse;
}

void djui_hud_set_mouse_locked(bool locked) {
    gDjuiHudLockMouse = locked;
}

u8 djui_hud_get_mouse_buttons_down(void) {
    return mouse_window_buttons;
}

u8 djui_hud_get_mouse_buttons_pressed(void) {
    return mouse_window_buttons_pressed;
}

u8 djui_hud_get_mouse_buttons_released(void) {
    return mouse_window_buttons_released;
}

f32 djui_hud_get_mouse_scroll_x(void) {
    return mouse_scroll_x;
}

f32 djui_hud_get_mouse_scroll_y(void) {
    return mouse_scroll_y;
}

void djui_hud_set_viewport(f32 x, f32 y, f32 width, f32 height) {
    // translate position and scale
    djui_hud_translate_positions(&x, &y, &width, &height);

    // convert to viewport structure
    static Vp vp = {{
        { 640, 480, 511, 0 },
        { 640, 480, 511, 0 },
    }};
    Vp_t *viewport = &vp.vp;
    viewport->vscale[0] = width * 2.0f;
    viewport->vscale[1] = height * 2.0f;
    viewport->vtrans[0] = (width + x) * 2.0f;
    viewport->vtrans[1] = (height + y) * 2.0f;

    gSPViewport(gDisplayListHead++, &vp);
}

void djui_hud_reset_viewport(void) {
    extern Vp gViewportFullscreen;
    gSPViewport(gDisplayListHead++, &gViewportFullscreen);
}

void djui_hud_set_scissor(f32 x, f32 y, f32 width, f32 height) {
    // translate position and scale
    djui_hud_translate_positions(&x, &y, &width, &height);

    // apply the scissor
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, width, height);
}

void djui_hud_reset_scissor(void) {
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, BORDER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - BORDER_HEIGHT);
}

void djui_hud_measure_text(const char* message, RET f32 *width, RET f32 *height) {
    if (message == NULL) { return; }
    const struct DjuiFont* font = djui_hud_get_text_font();

    f32 maxWidth = 0.f;
    *width = 0.f;
    *height = font->charHeight;

    char *c = (char *) message;
    const char *end = message + strlen(message);
    while (*c != '\0') {

        // check color code
        if (djui_text_parse_color(c, end, false, NULL, &c, NULL)) {
            continue;
        }

        // new line
        if (*c == '\n') {
            maxWidth = max(*width, maxWidth);
            *width = 0;
            *height += font->lineHeight;
        }

        // tab: align to the next (4 x space width)
        else if (*c == '\t') {
            f32 tabWidth = 4 * font->char_width(" ") * (djui_hud_text_font_is_legacy() ? 0.5f : 1.0f);
            *width += tabWidth - fmodf(*width, tabWidth);
        }

        // unprintable chars
        else if (!djui_text_is_printable(c)) {
            // treat them as empty
        }

        // regular chars
        else {
            *width += font->char_width(c) * (djui_hud_text_font_is_legacy() ? 0.5f : 1.0f);
        }

        c = djui_unicode_next_char(c);
    }

    *width = max(*width, maxWidth) * font->defaultFontScale;
    *height *= font->defaultFontScale * (djui_hud_text_font_is_legacy() ? 0.5f : 1.0f);
}

static Mtx *allocate_dl_translation_matrix() {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    if (matrix == NULL) { return NULL; }
    gSPMatrix(gDisplayListHead++, matrix, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    return matrix;
}

static void djui_hud_print_text_internal(const char* message, f32 x, f32 y, f32 scale, struct InterpHud *interp) {
    if (message == NULL) { return; }
    gDjuiHudUtilsZ += 0.001f;

    const struct DjuiFont* font = djui_hud_get_text_font();
    f32 fontScale = font->defaultFontScale * scale;

    // setup display list
    if (font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);
    }

    // translate
    djui_hud_create_interp_gfx(interp, INTERP_HUD_TRANSLATION);
    x += (font->xOffset * scale); y += (font->yOffset * scale);
    djui_hud_position_translate(&x, &y);
    create_dl_translation_matrix(DJUI_MTX_PUSH, x, y, gDjuiHudUtilsZ);

    // rotate
    f32 translatedFontSize = fontScale;
    djui_hud_size_translate(&translatedFontSize);
    if ((interp && sHudUtilsState.rotation.degrees.prev != 0) || sHudUtilsState.rotation.degrees.curr != 0) {
        djui_hud_create_interp_gfx(interp, INTERP_HUD_ROTATION);
        f32 pivotTranslationX = font->defaultFontScale * translatedFontSize * sHudUtilsState.rotation.pivotX.curr;
        f32 pivotTranslationY = font->defaultFontScale * translatedFontSize * sHudUtilsState.rotation.pivotY.curr;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sHudUtilsState.rotation.degrees.curr, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // compute font size
    djui_hud_create_interp_gfx(interp, INTERP_HUD_SCALE);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // allocate the translation matrix for the vertical alignment
    InterpHudGfx *valignGfx = djui_hud_create_interp_gfx(interp, INTERP_HUD_VALIGN);
    Mtx *valignMatrix = allocate_dl_translation_matrix();
    if (valignMatrix == NULL) { return; }

    // allocate the translation matrix for the horizontal alignment
    InterpHudGfx *halignGfx = djui_hud_create_interp_gfx(interp, INTERP_HUD_HALIGN);
    Mtx *halignMatrix = allocate_dl_translation_matrix();
    if (halignMatrix == NULL) { return; }

    // render the line
    char* c = (char*)message;
    const char *end = message + strlen(message);
    f32 lineWidth = 0;
    f32 textHeight = font->lineHeight;

    // apply text color
    gDPSetPrimColor(gDisplayListHead++, 0, 0,
        sHudUtilsState.textColor.r,
        sHudUtilsState.textColor.g,
        sHudUtilsState.textColor.b,
        sHudUtilsState.textColor.a
    );

    font->render_begin();
    while (*c != '\0') {

        // check color code
        struct DjuiColor parsedColor;
        if (djui_text_parse_color(c, end, false, &sHudUtilsState.textColor, &c, &parsedColor)) {
            gDPSetPrimColor(gDisplayListHead++, 0, 0,
                parsedColor.r,
                parsedColor.g,
                parsedColor.b,
                parsedColor.a
            );
            continue;
        }

        // new line
        if (*c == '\n') {

            // compute the horizontal alignment matrix for the current line
            guTranslate(halignMatrix, -lineWidth * sHudUtilsState.textAlignment.h.curr, 0, 0);
            if (halignGfx) { halignGfx->params[0] = lineWidth; }

            // allocate a new translation matrix for the next line
            halignGfx = djui_hud_create_interp_gfx(interp, INTERP_HUD_HALIGN);
            halignMatrix = allocate_dl_translation_matrix();
            if (halignMatrix == NULL) { return; }

            // cancel out the line translation and move to the next line
            // this is needed because otherwise the text would be rendered in a staircase way
            InterpHudGfx *newlineGfx = djui_hud_create_interp_gfx(interp, INTERP_HUD_NEW_LINE);
            create_dl_translation_matrix(DJUI_MTX_NOPUSH, -lineWidth * (1.f - sHudUtilsState.textAlignment.h.curr), -font->lineHeight, 0);
            if (newlineGfx) { newlineGfx->params[0] = lineWidth; }
            lineWidth = 0;
            textHeight += font->lineHeight;
            c = djui_unicode_next_char(c);
            continue;
        }

        // tab: align to the next (4 x space width)
        else if (*c == '\t') {
            f32 tabWidth = 4 * font->char_width(" ");
            f32 newLineWidth = lineWidth + tabWidth - fmodf(lineWidth, tabWidth);
            create_dl_translation_matrix(DJUI_MTX_NOPUSH, newLineWidth - lineWidth, 0, 0);
            lineWidth = newLineWidth;
            c = djui_unicode_next_char(c);
            continue;
        }

        // unprintable chars
        if (!djui_text_is_printable(c)) {
            c = djui_unicode_next_char(c);
            continue;
        }

        // render
        f32 charWidth = font->char_width(c);
        font->render_char(c);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, charWidth, 0, 0);
        lineWidth += charWidth;

        c = djui_unicode_next_char(c);
    }
    font->render_end();

    // compute the horizontal alignment matrix for the last line
    guTranslate(halignMatrix, -lineWidth * sHudUtilsState.textAlignment.h.curr, 0, 0);
    if (halignGfx) { halignGfx->params[0] = lineWidth; }

    // compute the vertical alignment matrix
    guTranslate(valignMatrix, 0, textHeight * sHudUtilsState.textAlignment.v.curr, 0);
    if (valignGfx) { valignGfx->params[0] = textHeight; }

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_print_text(const char* message, f32 x, f32 y, f32 scale) {
    if (message == NULL) { return; }

    if (djui_hud_text_font_is_legacy()) {
        scale *= 0.5f;
    }

    djui_hud_print_text_internal(message, x, y, scale, NULL);
}

void djui_hud_print_text_interpolated(const char* message, f32 prevX, f32 prevY, f32 prevScale, f32 x, f32 y, f32 scale) {
    if (message == NULL) { return; }

    if (djui_hud_text_font_is_legacy()) {
        scale *= 0.5f;
        prevScale *= 0.5f;
    }

    struct InterpHud *interp = djui_hud_create_interp();
    if (interp) {
        const struct DjuiFont* font = djui_hud_get_text_font();
        INTERP_SET(interp->posX, prevX, x);
        INTERP_SET(interp->posY, prevY, y);
        INTERP_SET(interp->scaleX, prevScale, scale);
        INTERP_SET(interp->scaleY, prevScale, scale);
        interp->width = font->defaultFontScale;
        interp->height = font->defaultFontScale;
    }

    djui_hud_print_text_internal(message, x, y, scale, interp);
}

static inline bool is_power_of_two(u32 n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

static void djui_hud_render_texture_raw(const Texture* texture, u32 width, u32 height, u8 fmt, u8 siz, f32 x, f32 y, f32 scaleW, f32 scaleH, struct InterpHud *interp) {
    if (!is_power_of_two(width) || !is_power_of_two(height)) {
        LOG_LUA_LINE("Tried to render DJUI HUD texture with NPOT width or height");
        return;
    }

    if (!texture) { return; }

    gDjuiHudUtilsZ += 0.001f;

    // translate
    djui_hud_create_interp_gfx(interp, INTERP_HUD_TRANSLATION);
    djui_hud_position_translate(&x, &y);
    create_dl_translation_matrix(DJUI_MTX_PUSH, x, y, gDjuiHudUtilsZ);

    // rotate
    djui_hud_size_translate(&scaleW);
    djui_hud_size_translate(&scaleH);
    if ((interp && sHudUtilsState.rotation.degrees.prev != 0) || sHudUtilsState.rotation.degrees.curr != 0) {
        djui_hud_create_interp_gfx(interp, INTERP_HUD_ROTATION);
        f32 pivotTranslationX = width * scaleW * sHudUtilsState.rotation.pivotX.curr;
        f32 pivotTranslationY = height * scaleH * sHudUtilsState.rotation.pivotY.curr;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sHudUtilsState.rotation.degrees.curr, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // scale
    djui_hud_create_interp_gfx(interp, INTERP_HUD_SCALE);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width * scaleW, height * scaleH, 1.0f);

    // render
    djui_gfx_render_texture(texture, width, height, fmt, siz, sHudUtilsState.filter);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

static void djui_hud_render_texture_tile_raw(const Texture* texture, u32 width, u32 height, u8 fmt, u8 siz, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH, struct InterpHud *interp) {
    if (!texture) { return; }

    gDjuiHudUtilsZ += 0.001f;
    if (width != 0) { scaleW *= (f32) tileW / (f32) width; }
    if (height != 0) { scaleH *= (f32) tileH / (f32) height; }

    // translate
    djui_hud_create_interp_gfx(interp, INTERP_HUD_TRANSLATION);
    djui_hud_position_translate(&x, &y);
    create_dl_translation_matrix(DJUI_MTX_PUSH, x, y, gDjuiHudUtilsZ);

    // rotate
    djui_hud_size_translate(&scaleW);
    djui_hud_size_translate(&scaleH);
    if ((interp && sHudUtilsState.rotation.degrees.prev != 0) || sHudUtilsState.rotation.degrees.curr != 0) {
        djui_hud_create_interp_gfx(interp, INTERP_HUD_ROTATION);
        f32 aspect = tileH ? ((f32) tileW / (f32) tileH) : 1.f;
        f32 pivotTranslationX = width * scaleW * aspect * sHudUtilsState.rotation.pivotX.curr;
        f32 pivotTranslationY = height * scaleH * sHudUtilsState.rotation.pivotY.curr;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sHudUtilsState.rotation.degrees.curr, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // scale
    djui_hud_create_interp_gfx(interp, INTERP_HUD_SCALE);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width * scaleW, height * scaleH, 1.0f);

    // render
    djui_gfx_render_texture_tile(texture, width, height, fmt, siz, tileX, tileY, tileW, tileH, sHudUtilsState.filter);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_render_texture(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    if (!texInfo) { return; }
    djui_hud_render_texture_raw(texInfo->texture, texInfo->width, texInfo->height, texInfo->format, texInfo->size, x, y, scaleW, scaleH, NULL);
}

void djui_hud_render_texture_tile(struct TextureInfo* texInfo, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH) {
    if (!texInfo) { return; }
    djui_hud_render_texture_tile_raw(texInfo->texture, texInfo->width, texInfo->height, texInfo->format, texInfo->size, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH, NULL);
}

void djui_hud_render_texture_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH) {
    if (!texInfo) { return; }

    struct InterpHud *interp = djui_hud_create_interp();
    if (interp) {
        INTERP_SET(interp->posX, prevX, x);
        INTERP_SET(interp->posY, prevY, y);
        INTERP_SET(interp->scaleX, prevScaleW, scaleW);
        INTERP_SET(interp->scaleY, prevScaleH, scaleH);
        interp->width = texInfo->width;
        interp->height = texInfo->height;
    }

    djui_hud_render_texture_raw(texInfo->texture, texInfo->width, texInfo->height, texInfo->format, texInfo->size, prevX, prevY, prevScaleW, prevScaleH, interp);
}

void djui_hud_render_texture_tile_interpolated(struct TextureInfo* texInfo, f32 prevX, f32 prevY, f32 prevScaleW, f32 prevScaleH, f32 x, f32 y, f32 scaleW, f32 scaleH, u32 tileX, u32 tileY, u32 tileW, u32 tileH) {
    if (!texInfo) { return; }

    // apply scale correction for tiles
    if (texInfo->width != 0) {
        scaleW *= ((f32)tileW / (f32)texInfo->width);
        prevScaleW *= ((f32)tileW / (f32)texInfo->width);
    }
    if (texInfo->height != 0) {
        scaleH *= ((f32)tileH / (f32)texInfo->height);
        prevScaleH *= ((f32)tileH / (f32)texInfo->height);
    }

    struct InterpHud *interp = djui_hud_create_interp();
    if (interp) {
        INTERP_SET(interp->posX, prevX, x);
        INTERP_SET(interp->posY, prevY, y);
        INTERP_SET(interp->scaleX, prevScaleW, scaleW);
        INTERP_SET(interp->scaleY, prevScaleH, scaleH);
        interp->width = texInfo->width;
        interp->height = texInfo->height;
    }

    djui_hud_render_texture_tile_raw(texInfo->texture, texInfo->width, texInfo->height, texInfo->format, texInfo->size, prevX, prevY, prevScaleW, prevScaleH, tileX, tileY, tileW, tileH, interp);
}

static void djui_hud_render_rect_internal(f32 x, f32 y, f32 width, f32 height, struct InterpHud *interp) {
    gDjuiHudUtilsZ += 0.001f;

    // translate
    djui_hud_create_interp_gfx(interp, INTERP_HUD_TRANSLATION);
    djui_hud_position_translate(&x, &y);
    create_dl_translation_matrix(DJUI_MTX_PUSH, x, y, gDjuiHudUtilsZ);

    // rotate
    djui_hud_size_translate(&width);
    djui_hud_size_translate(&height);
    if ((interp && sHudUtilsState.rotation.degrees.prev != 0) || sHudUtilsState.rotation.degrees.curr != 0) {
        djui_hud_create_interp_gfx(interp, INTERP_HUD_ROTATION);
        f32 pivotTranslationX = width * sHudUtilsState.rotation.pivotX.curr;
        f32 pivotTranslationY = height * sHudUtilsState.rotation.pivotY.curr;
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, +pivotTranslationX, -pivotTranslationY, 0);
        create_dl_rotation_matrix(DJUI_MTX_NOPUSH, sHudUtilsState.rotation.degrees.curr, 0, 0, 1);
        create_dl_translation_matrix(DJUI_MTX_NOPUSH, -pivotTranslationX, +pivotTranslationY, 0);
    }

    // scale
    djui_hud_create_interp_gfx(interp, INTERP_HUD_SCALE);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width, height, 1.0f);

    // render
    djui_gfx_update_combine_mode(CS_COLOR);
    gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);

    // pop
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void djui_hud_render_rect(f32 x, f32 y, f32 width, f32 height) {
    djui_hud_render_rect_internal(x, y, width, height, NULL);
}

void djui_hud_render_rect_interpolated(f32 prevX, f32 prevY, f32 prevWidth, f32 prevHeight, f32 x, f32 y, f32 width, f32 height) {
    struct InterpHud *interp = djui_hud_create_interp();
    if (interp) {
        INTERP_SET(interp->posX, prevX, x);
        INTERP_SET(interp->posY, prevY, y);
        INTERP_SET(interp->scaleX, prevWidth, width);
        INTERP_SET(interp->scaleY, prevHeight, height);
        interp->width = 1;
        interp->height = 1;
    }

    djui_hud_render_rect_internal(prevX, prevY, prevWidth, prevHeight, interp);
}

void djui_hud_render_line(f32 p1X, f32 p1Y, f32 p2X, f32 p2Y, f32 size) {
    f32 dx = p2X - p1X;
    f32 dy = p2Y - p1Y;
    f32 angle = atan2s(dy, dx) - 0x4000; // -90 degrees to adjust for djui rotation
    f32 hDist = sqrt(sqr(dx) + sqr(dy));
    djui_hud_set_rotation(angle, 0, 0.5);
    djui_hud_render_rect(p1X, p1Y, hDist, size);
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
    return get_first_person_enabled() ? gFirstPersonCamera.fov : replace_value_if_not_zero(gFOVState.fov, gOverrideFOV) + gFOVState.fovOffset;
}

f32 djui_hud_get_fov_coeff() {
    // fov of 45.0 is the default fov
    f32 fov = get_current_fov();
    f32 fovDefault = tanf(45.f * ((f32)M_PI / 360.0f));
    f32 fovCurrent = tanf(fov * ((f32)M_PI / 360.0f));

    return (fovDefault / fovCurrent) * 1.13f;
}

bool gDjuiHudToWorldCalcViewport = true;

bool djui_hud_world_pos_to_screen_pos(Vec3f pos, VEC_OUT Vec3f out) {
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
    if (sHudUtilsState.resolution == RESOLUTION_N64) {
        screenWidth = GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT;
        screenHeight = SCREEN_HEIGHT;
    } else {
        u32 windowWidth, windowHeight;
        gfx_get_dimensions(&windowWidth, &windowHeight);
        screenWidth = (f32) windowWidth;
        screenHeight = (f32) windowHeight;
    }

    out[0] += screenWidth  / 2.0f;
    out[1] += screenHeight / 2.0f;

    extern Vp *gViewportOverride;
    if (gViewportOverride && gDjuiHudToWorldCalcViewport) {
        Vp_t *viewport = &gViewportOverride->vp;
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
