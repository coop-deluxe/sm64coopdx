#include <string.h>
#include <stdio.h>
#include "djui.h"
#include "game/segment2.h"

#define DJUI_INPUTBOX_YOFF (-2)
#define DJUI_INPUTBOX_MAX_BLINK 50
#define DJUI_INPUTBOX_MID_BLINK (DJUI_INPUTBOX_MAX_BLINK / 2)
#define DJUI_INPUTBOX_CURSOR_WIDTH (2.0f / 32.0f)

static u8 sCursorBlink = 0;

static void djui_inputbox_set_default_style(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    djui_base_set_border_color(base, 150, 150, 150, 255);
    djui_base_set_color(&inputbox->base, 240, 240, 240, 255);
}

static void djui_inputbox_on_hover(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    djui_base_set_border_color(base, 0, 120, 215, 255);
    djui_base_set_color(&inputbox->base, 255, 255, 255, 255);
}

static void djui_inputbox_on_hover_end(struct DjuiBase* base) {
    djui_inputbox_set_default_style(base);
}

static u16 djui_inputbox_get_cursor_index(struct DjuiInputbox* inputbox) {
    struct DjuiBaseRect* comp = &inputbox->base.comp;
    struct DjuiFont* font     = &gDjuiFonts[0];

    f32 cX = (gCursorX - (comp->x + inputbox->viewX)) / font->defaultFontScale;
    f32 x = 0;
    u16 index = 0;
    for (u16 i = 0; i < inputbox->bufferSize; i++) {
        char c = inputbox->buffer[i];
        if (x < cX) {
            index = i;
        }
        if (c == '\0') { break; }
        x += font->char_width(c);
    }

    return index;
}

static void djui_inputbox_on_cursor_down_begin(struct DjuiBase* base, bool inputCursor) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    u16 index = djui_inputbox_get_cursor_index(inputbox);
    inputbox->selection[0] = index;
    inputbox->selection[1] = index;
    sCursorBlink = 0;
}

static void djui_inputbox_on_cursor_down(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    u16 index = djui_inputbox_get_cursor_index(inputbox);
    inputbox->selection[0] = index;
}

static void djui_inputbox_on_cursor_down_end(struct DjuiBase* base) {
    djui_inputbox_set_default_style(base);
}

static void djui_inputbox_render_char(struct DjuiInputbox* inputbox, char c, f32* drawX, f32* additionalShift) {
    struct DjuiBaseRect* comp = &inputbox->base.comp;
    struct DjuiFont*     font = &gDjuiFonts[0];
    f32 dX = comp->x + *drawX;
    f32 dY = comp->y + DJUI_INPUTBOX_YOFF;
    f32 dW = font->charWidth  * font->defaultFontScale;
    f32 dH = font->charHeight * font->defaultFontScale;

    f32 charWidth = font->char_width(c);
    *drawX += charWidth * font->defaultFontScale;

    if (c != ' ') {
        if (djui_gfx_add_clipping_specific(&inputbox->base, font->rotatedUV, dX, dY, dW, dH)) {
            *additionalShift += charWidth;
            return;
        }
        font->render_char(c);
    }

    create_dl_translation_matrix(DJUI_MTX_NOPUSH, charWidth + *additionalShift, 0, 0);
    *additionalShift = 0;
}

static void djui_inputbox_render_selection(struct DjuiInputbox* inputbox) {
    struct DjuiFont* font = &gDjuiFonts[0];

    // make selection well formed
    u16 selection[2] = { 0 };
    selection[0] = fmin(inputbox->selection[0], inputbox->selection[1]);
    selection[1] = fmax(inputbox->selection[0], inputbox->selection[1]);

    char* msg = inputbox->buffer;
    f32 x = 0;
    f32 width = 0;
    for (u16 i = 0; i < selection[1]; i++) {
        if (i < selection[0]) {
            x += font->char_width(msg[i]);
        } else {
            width += font->char_width(msg[i]);
        }
    }
    
    sCursorBlink = (sCursorBlink + 1) % DJUI_INPUTBOX_MAX_BLINK;

    // render only cursor when there is no selection width
    if (selection[0] == selection[1]) {
        if (sCursorBlink < DJUI_INPUTBOX_MID_BLINK) {
            create_dl_translation_matrix(DJUI_MTX_PUSH, x - DJUI_INPUTBOX_CURSOR_WIDTH / 2.0f, -0.1f, 0);
            create_dl_scale_matrix(DJUI_MTX_NOPUSH, DJUI_INPUTBOX_CURSOR_WIDTH, 0.8f, 1.0f);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
        }
        return;
    }

    // clip selection box
    // note: this is incredibly confusing due to being in font-space instead of screen-space
    f32 clipLow = -inputbox->viewX / font->defaultFontScale;
    if (x < clipLow) {
        width -= clipLow - x;
        x = clipLow;
    }
    f32 clipHigh = (inputbox->base.clip.width / font->defaultFontScale) - x + clipLow;
    if (width > clipHigh) {
        width = clipHigh;
    }

    // render selection box
    create_dl_translation_matrix(DJUI_MTX_PUSH, x, -0.1f, 0);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, width, 0.8f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 120, 215, 255);
    gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    // render selection cursor
    if (sCursorBlink < DJUI_INPUTBOX_MID_BLINK) {
        f32 cX = (inputbox->selection[0] < inputbox->selection[1]) ? x : (x + width);
        create_dl_translation_matrix(DJUI_MTX_PUSH, cX - DJUI_INPUTBOX_CURSOR_WIDTH / 2.0f, -0.1f, 0);
        create_dl_scale_matrix(DJUI_MTX_NOPUSH, DJUI_INPUTBOX_CURSOR_WIDTH, 0.8f, 1.0f);
        gDPSetEnvColor(gDisplayListHead++, 255, 127, 0, 255);
        gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }
}

static void djui_inputbox_keep_selection_in_view(struct DjuiInputbox* inputbox) {
    struct DjuiFont* font = &gDjuiFonts[0];

    // calculate where our cursor is
    f32 cursorX = inputbox->viewX;
    char* msg = inputbox->buffer;
    for (u16 i = 0; i < inputbox->selection[0]; i++) {
        cursorX += font->char_width(msg[i]) * font->defaultFontScale;
    }

    // shift viewing window
    if (cursorX > inputbox->base.comp.width) {
        inputbox->viewX -= cursorX - inputbox->base.comp.width;
    } else if (cursorX < 0) {
        inputbox->viewX -= cursorX;
    }
}

static void djui_inputbox_render(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    struct DjuiBaseRect* comp     = &base->comp;
    struct DjuiFont*     font     = &gDjuiFonts[0];
    djui_rect_render(base);

    // shift the viewing window to keep the selection in view
    djui_inputbox_keep_selection_in_view(inputbox);

    // translate position
    f32 translatedX = comp->x + inputbox->viewX;
    f32 translatedY = comp->y + DJUI_INPUTBOX_YOFF;
    djui_gfx_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // compute font size
    f32 translatedFontSize = font->defaultFontScale;
    djui_gfx_size_translate(&translatedFontSize);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // render selection
    djui_inputbox_render_selection(inputbox);

    // begin font
    gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);

    // set color
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);

    // make selection well formed
    u16 selection[2] = { 0 };
    selection[0] = fmin(inputbox->selection[0], inputbox->selection[1]);
    selection[1] = fmax(inputbox->selection[0], inputbox->selection[1]);

    // render text
    char* msg = inputbox->buffer;
    f32 drawX = inputbox->viewX;
    f32 additionalShift = 0;
    bool wasInsideSelection = false;
    for (u16 i = 0; i < inputbox->bufferSize; i++) {
        if (msg[i] == '\0') { break; }

        // deal with seleciton color
        if (selection[0] != selection[1]) {
            bool insideSelection = (i >= selection[0]) && (i < selection[1]);
            if (insideSelection && !wasInsideSelection) {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            } else if (!insideSelection && wasInsideSelection) {
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            }
            wasInsideSelection = insideSelection;
        }

        // render character
        djui_inputbox_render_char(inputbox, msg[i], &drawX, &additionalShift);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

static void djui_inputbox_destroy(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    free(inputbox->buffer);
    free(inputbox);
}

struct DjuiInputbox* djui_inputbox_create(struct DjuiBase* parent, u16 bufferSize) {
    struct DjuiInputbox* inputbox = malloc(sizeof(struct DjuiInputbox));
    struct DjuiBase* base         = &inputbox->base;
    inputbox->viewX = 0;
    inputbox->selection[0] = 0;
    inputbox->selection[1] = 0;
    inputbox->bufferSize = bufferSize;
    inputbox->buffer = malloc(sizeof(char) * bufferSize);
    memset(inputbox->buffer, 0, sizeof(char) * bufferSize);
    sprintf(inputbox->buffer, "testing string hello world there it is");

    djui_base_init(parent, base, djui_inputbox_render, djui_inputbox_destroy);
    djui_base_set_size(base, 200, 32);
    djui_base_set_border_width(base, 2);
    djui_interactable_create(base);
    djui_interactable_hook_hover(base, djui_inputbox_on_hover, djui_inputbox_on_hover_end);
    djui_interactable_hook_cursor_down(base, djui_inputbox_on_cursor_down_begin, djui_inputbox_on_cursor_down, djui_inputbox_on_cursor_down_end);

    djui_inputbox_set_default_style(base);

    return inputbox;
}
