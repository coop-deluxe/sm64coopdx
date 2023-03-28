#include <string.h>
#include <stdio.h>
#include "djui.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"
#include "game/segment2.h"
#include "pc/controller/controller_keyboard.h"

#define DJUI_INPUTBOX_YOFF (-2)
#define DJUI_INPUTBOX_MAX_BLINK 50
#define DJUI_INPUTBOX_MID_BLINK (DJUI_INPUTBOX_MAX_BLINK / 2)
#define DJUI_INPUTBOX_CURSOR_WIDTH (2.0f / 32.0f)

static u8 sHeldShift = 0;
static u8 sHeldControl = 0;
static u8 sCursorBlink = 0;

static void djui_inputbox_update_style(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    if (!inputbox->base.enabled) {
        djui_base_set_border_color(base, 90, 90, 90, 255);
        djui_base_set_color(&inputbox->base, 140, 140, 140, 255);
    } else if (gDjuiCursorDownOn == base) {
    } else if (gDjuiHovered == base) {
        djui_base_set_border_color(base, 0, 120, 215, 255);
        djui_base_set_color(&inputbox->base, 255, 255, 255, 255);
    } else {
        djui_base_set_border_color(base, 150, 150, 150, 255);
        djui_base_set_color(&inputbox->base, 240, 240, 240, 255);
    }
}

static void djui_inputbox_on_change(struct DjuiInputbox* inputbox) {
    struct DjuiBase* base = &inputbox->base;
    if (base != NULL && base->interactable != NULL && base->interactable->on_value_change != NULL) {
        base->interactable->on_value_change(base);
    }
}

void djui_inputbox_set_text_color(struct DjuiInputbox* inputbox, u8 r, u8 g, u8 b, u8 a) {
    inputbox->textColor.r = r;
    inputbox->textColor.g = g;
    inputbox->textColor.b = b;
    inputbox->textColor.a = a;
}

void djui_inputbox_set_text(struct DjuiInputbox* inputbox, char* text) {
    snprintf(inputbox->buffer, inputbox->bufferSize, "%s", text);
}

void djui_inputbox_select_all(struct DjuiInputbox* inputbox) {
    inputbox->selection[1] = 0;
    inputbox->selection[0] = strlen(inputbox->buffer);
}

void djui_inputbox_hook_enter_press(struct DjuiInputbox* inputbox, void (*on_enter_press)(struct DjuiInputbox*)) {
    inputbox->on_enter_press = on_enter_press;
}

void djui_inputbox_hook_escape_press(struct DjuiInputbox* inputbox, void (*on_escape_press)(struct DjuiInputbox*)) {
    inputbox->on_escape_press = on_escape_press;
}

static u16 djui_inputbox_get_cursor_index(struct DjuiInputbox* inputbox) {
    struct DjuiBaseRect*   comp = &inputbox->base.comp;
    const struct DjuiFont* font = gDjuiFonts[0];

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

static void djui_inputbox_on_cursor_down(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    u16 index = djui_inputbox_get_cursor_index(inputbox);
    inputbox->selection[0] = index;
}

static void djui_inputbox_on_cursor_down_begin(struct DjuiBase* base, UNUSED bool inputCursor) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    u16 index = djui_inputbox_get_cursor_index(inputbox);
    u16 selLength = abs(inputbox->selection[0] - inputbox->selection[1]);
    if (selLength != strlen(inputbox->buffer) || djui_interactable_is_input_focus(base)) {
        inputbox->selection[0] = index;
        inputbox->selection[1] = index;
        djui_interactable_hook_cursor_down(base, djui_inputbox_on_cursor_down_begin, djui_inputbox_on_cursor_down, NULL);
    } else {
        djui_interactable_hook_cursor_down(base, djui_inputbox_on_cursor_down_begin, NULL, NULL);
    }
    sCursorBlink = 0;
    djui_interactable_set_input_focus(base);
}

static u16 djui_inputbox_jump_word_left(char* msg, UNUSED u16 len, u16 i) {
    if (i == 0) { return i; }

    s32 lastI = i;
    bool seenNonSpace = false;
    while (true) {
        if (msg[i] == ' ' && seenNonSpace) { i = lastI; break; }
        lastI = i;
        i--;
        if (i <= 0)   { i = 0;   break; }
        if (msg[i] != ' ') { seenNonSpace = true; }
    }

    return i;
}

static u16 djui_inputbox_jump_word_right(char *msg, u16 len, u16 i) {
    if (i >= len) { return len; }

    bool seenSpace = false;
    while (true) {
        i++;
        if (i >= len) { i = len; break; }
        if (msg[i] != ' ' && seenSpace) { break; }
        if (msg[i] == ' ') { seenSpace = true; }
    };

    return i;
}

static void djui_inputbox_delete_selection(struct DjuiInputbox *inputbox) {
    u16 *sel = inputbox->selection;
    char *msg = inputbox->buffer;
    u16 len = strlen(msg);

    if (sel[0] != sel[1]) {
        u16 s1 = fmin(sel[0], sel[1]);
        u16 s2 = fmax(sel[0], sel[1]);
        memmove(&msg[s1], &msg[s2], (len + 1) - s2);
        sel[0] = s1;
        sel[1] = s1;
    }
    djui_inputbox_on_change(inputbox);
}

bool djui_inputbox_on_key_down(struct DjuiBase *base, int scancode) {
    struct DjuiInputbox *inputbox = (struct DjuiInputbox *) base;
    u16 *sel = inputbox->selection;
    char *msg = inputbox->buffer;
    u16 len = strlen(msg);
    u16 s1 = fmin(sel[0], sel[1]);
    u16 s2 = fmax(sel[0], sel[1]);

    switch (scancode) {
        case SCANCODE_CONTROL_LEFT:  sHeldControl |= (1 << 0); return true;
        case SCANCODE_CONTROL_RIGHT: sHeldControl |= (1 << 1); return true;
        case SCANCODE_SHIFT_LEFT:    sHeldShift   |= (1 << 0); return true;
        case SCANCODE_SHIFT_RIGHT:   sHeldShift   |= (1 << 1); return true;
    }

    if (scancode == SCANCODE_LEFT) {
        if (sHeldControl) {
            sel[0] = djui_inputbox_jump_word_left(msg, len, sel[0]);
        } else if (sel[0] > 0) {
            sel[0]--;
        }
        if (!sHeldShift) { sel[1] = sel[0]; }
        sCursorBlink = 0;
        return true;
    }

    if (scancode == SCANCODE_RIGHT) {
        if (sHeldControl) {
            sel[0] = djui_inputbox_jump_word_right(msg, len, sel[0]);
        } else if (sel[0] < len) {
            sel[0]++;
        }
        if (!sHeldShift) { sel[1] = sel[0]; }
        sCursorBlink = 0;
        return true;
    }

    if (scancode == SCANCODE_HOME) {
        sel[0] = 0;
        if (!sHeldShift) { sel[1] = sel[0]; }
        sCursorBlink = 0;
        return true;
    }

    if (scancode == SCANCODE_END) {
        sel[0] = len;
        if (!sHeldShift) { sel[1] = sel[0]; }
        sCursorBlink = 0;
        return true;
    }

    if (scancode == SCANCODE_BACKSPACE) {
        if (sel[0] == sel[1]) {
            if (sHeldControl) {
                sel[0] = djui_inputbox_jump_word_left(msg, len, sel[0]);
            } else if (sel[0] > 0) {
                sel[0]--;
            }
        }
        if (sel[0] != sel[1]) {
            djui_inputbox_delete_selection(inputbox);
        }
        sCursorBlink = 0;
        return true;
    }

    if (scancode == SCANCODE_DELETE) {
        if (sel[0] == sel[1]) {
            if (sHeldControl) {
                sel[1] = djui_inputbox_jump_word_right(msg, len, sel[1]);
            } else if (sel[1] < len) {
                sel[1]++;
            }
        }
        if (sel[0] != sel[1]) {
            djui_inputbox_delete_selection(inputbox);
        }
        sCursorBlink = 0;
        return true;
    }

    if ((sHeldControl && scancode == SCANCODE_V) || (sHeldShift && scancode == SCANCODE_INSERT)) {
        djui_interactable_on_text_input(wm_api->get_clipboard_text());
        sCursorBlink = 0;
        return true;
    }

    if (sHeldControl && (scancode == SCANCODE_C || scancode == SCANCODE_X)) {
        if (sel[0] != sel[1]) {
            char clipboardText[256] = { 0 };
            snprintf(clipboardText, fmin(256, 1 + s2 - s1), "%s", &msg[s1]);
            wm_api->set_clipboard_text(clipboardText);
            if (scancode == SCANCODE_X) {
                djui_inputbox_delete_selection(inputbox);
                sCursorBlink = 0;
            }
        }
        return true;
    }

    if (sHeldControl && scancode == SCANCODE_A) {
        inputbox->selection[0] = len;
        inputbox->selection[1] = 0;
        sCursorBlink = 0;
        return true;
    }

    if (scancode == SCANCODE_ESCAPE) {
        djui_interactable_set_input_focus(NULL);
        if (inputbox->on_escape_press) {
            inputbox->on_escape_press(inputbox);
        }
        return true;
    }

    if (scancode == SCANCODE_ENTER) {
        djui_interactable_set_input_focus(NULL);
        if (inputbox->on_enter_press) {
            inputbox->on_enter_press(inputbox);
        }
        return true;
    }

    return true;
}

void djui_inputbox_on_key_up(UNUSED struct DjuiBase *base, int scancode) {
    switch (scancode) {
        case SCANCODE_CONTROL_LEFT:  sHeldControl &= ~(1 << 0); break;
        case SCANCODE_CONTROL_RIGHT: sHeldControl &= ~(1 << 1); break;
        case SCANCODE_SHIFT_LEFT:    sHeldShift   &= ~(1 << 0); break;
        case SCANCODE_SHIFT_RIGHT:   sHeldShift   &= ~(1 << 1); break;
    }
}

static void djui_inputbox_on_focus_begin(UNUSED struct DjuiBase* base) {
    sHeldControl = 0;
    sHeldShift   = 0;
    wm_api->start_text_input();
}

static void djui_inputbox_on_focus_end(UNUSED struct DjuiBase* base) {
    wm_api->stop_text_input();
}

static void djui_inputbox_on_text_input(struct DjuiBase *base, char* text) {
    struct DjuiInputbox *inputbox = (struct DjuiInputbox *) base;
    char* msg = inputbox->buffer;
    int msgLen = strlen(msg);
    int textLen = strlen(text);

    djui_font_convert_to_smcode(text);

    // make sure we're not just printing garbage characters
    bool containsValidAscii = false;
    char* tinput = text;
    while (*tinput != '\0') {
        if (djui_font_valid_smcode(*tinput)) {
            containsValidAscii = true;
            break;
        }
        tinput++;
    }
    if (!containsValidAscii) {
        return;
    }

    // truncate
    if (textLen + msgLen >= inputbox->bufferSize) {
        int space = (inputbox->bufferSize - msgLen);
        if (space <= 1) { return; }
        text[space - 1] = '\0';
        textLen = space - 1;
    }

    // erase selection
    if (inputbox->selection[0] != inputbox->selection[1]) {
        djui_inputbox_delete_selection(inputbox);
    }

    // sanitize
    char *t = text;
    while (*t != '\0') {
        if (*t == '\n') { *t = ' '; }
        else if (*t == '\r') { *t = ' '; }
        else if (djui_font_valid_smcode(*t)) { ; }
        else if (*t < '!' || *t > '~') { *t = '?'; }
        t++;
    }

    // back up current message
    char* sMsg = calloc(inputbox->bufferSize, sizeof(char));
    memcpy(sMsg, msg, inputbox->bufferSize);

    // insert text
    u16 sel = inputbox->selection[0];
    snprintf(&msg[sel], (inputbox->bufferSize - sel), "%s%s", text, &sMsg[sel]);
    free(sMsg);

    // adjust cursor
    inputbox->selection[0] += strlen(text);
    inputbox->selection[1] = inputbox->selection[0];
    sCursorBlink = 0;
    djui_inputbox_on_change(inputbox);
}

static void djui_inputbox_render_char(struct DjuiInputbox* inputbox, char c, f32* drawX, f32* additionalShift) {
    struct DjuiBaseRect*   comp = &inputbox->base.comp;
    const struct DjuiFont* font = gDjuiFonts[0];
    f32 dX = comp->x + *drawX;
    f32 dY = comp->y + DJUI_INPUTBOX_YOFF;
    f32 dW = font->charWidth  * font->defaultFontScale;
    f32 dH = font->charHeight * font->defaultFontScale;

    f32 charWidth = font->char_width(c);
    *drawX += charWidth * font->defaultFontScale;

    if (c != ' ' && !djui_gfx_add_clipping_specific(&inputbox->base, font->rotatedUV, dX, dY, dW, dH)) {
        if (*additionalShift > 0) {
            create_dl_translation_matrix(DJUI_MTX_NOPUSH, *additionalShift, 0, 0);
            *additionalShift = 0;
        }
        font->render_char(c);
    }
    *additionalShift += charWidth;
}

static void djui_inputbox_render_selection(struct DjuiInputbox* inputbox) {
    const struct DjuiFont* font = gDjuiFonts[0];

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
        if (sCursorBlink < DJUI_INPUTBOX_MID_BLINK && djui_interactable_is_input_focus(&inputbox->base)) {
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
    if (sCursorBlink < DJUI_INPUTBOX_MID_BLINK && djui_interactable_is_input_focus(&inputbox->base)) {
        f32 cX = (inputbox->selection[0] < inputbox->selection[1]) ? x : (x + width);
        create_dl_translation_matrix(DJUI_MTX_PUSH, cX - DJUI_INPUTBOX_CURSOR_WIDTH / 2.0f, -0.1f, 0);
        create_dl_scale_matrix(DJUI_MTX_NOPUSH, DJUI_INPUTBOX_CURSOR_WIDTH, 0.8f, 1.0f);
        gDPSetEnvColor(gDisplayListHead++, 255, 127, 0, 255);
        gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }
}

static void djui_inputbox_keep_selection_in_view(struct DjuiInputbox* inputbox) {
    const struct DjuiFont* font = gDjuiFonts[0];

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

static bool djui_inputbox_render(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    struct DjuiBaseRect* comp     = &base->comp;
    const struct DjuiFont* font   = gDjuiFonts[0];
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
    if (font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, font->textBeginDisplayList);
    }

    // set color
    gDPSetEnvColor(gDisplayListHead++, inputbox->textColor.r, inputbox->textColor.g, inputbox->textColor.b, inputbox->textColor.a);

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
                gDPSetEnvColor(gDisplayListHead++, inputbox->textColor.r, inputbox->textColor.g, inputbox->textColor.b, inputbox->textColor.a);
            }
            wasInsideSelection = insideSelection;
        }

        // render character
        djui_inputbox_render_char(inputbox, msg[i], &drawX, &additionalShift);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    return true;
}

static void djui_inputbox_destroy(struct DjuiBase* base) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)base;
    free(inputbox->buffer);
    free(inputbox);
}

struct DjuiInputbox* djui_inputbox_create(struct DjuiBase* parent, u16 bufferSize) {
    struct DjuiInputbox* inputbox = calloc(1, sizeof(struct DjuiInputbox));
    struct DjuiBase* base         = &inputbox->base;
    inputbox->bufferSize = bufferSize;
    inputbox->buffer = calloc(bufferSize, sizeof(char));

    djui_base_init(parent, base, djui_inputbox_render, djui_inputbox_destroy);
    djui_base_set_size(base, 200, 32);
    djui_base_set_border_width(base, 2);
    djui_inputbox_set_text_color(inputbox, 0, 0, 0, 255);
    djui_interactable_create(base, djui_inputbox_update_style);
    djui_interactable_hook_cursor_down(base, djui_inputbox_on_cursor_down_begin, djui_inputbox_on_cursor_down, NULL);
    djui_interactable_hook_key(base, djui_inputbox_on_key_down, djui_inputbox_on_key_up);
    djui_interactable_hook_focus(base, djui_inputbox_on_focus_begin, NULL, djui_inputbox_on_focus_end);
    djui_interactable_hook_text_input(base, djui_inputbox_on_text_input);

    djui_inputbox_update_style(base);

    return inputbox;
}
