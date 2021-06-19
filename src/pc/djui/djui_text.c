#include <string.h>
#include "djui.h"
#include "game/segment2.h"

  ////////////////
 // properties //
////////////////

void djui_text_set_text(struct DjuiText* text, const char* message) {
    // deallocate old message
    if (text->message != NULL) {
        free(text->message);
    }

    // allocate and set new message
    u16 messageLen = strlen(message);
    text->message = malloc(sizeof(char) * (messageLen + 1));
    memcpy(text->message, message, sizeof(char) * (messageLen + 1));
}

void djui_text_set_font_size(struct DjuiText* text, f32 fontSize) {
    text->fontSize = fontSize;
}

void djui_text_set_drop_shadow(struct DjuiText* text, f32 r, f32 g, f32 b, f32 a) {
    text->dropShadow.r = r;
    text->dropShadow.g = g;
    text->dropShadow.b = b;
    text->dropShadow.a = a;
}

void djui_text_set_alignment(struct DjuiText* text, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign) {
    text->textHAlign = hAlign;
    text->textVAlign = vAlign;
}

  ///////////////
 // rendering //
///////////////

#define DJUI_TEXT_CHAR_HEIGHT 16
#define DJUI_TEXT_CHAR_WIDTH   8

static f32 sTextRenderX = 0;
static f32 sTextRenderY = 0;
static f32 sTextRenderLastX = 0;
static f32 sTextRenderLastY = 0;

static void djui_text_translate(f32 x, f32 y) {
    sTextRenderX += x;
    sTextRenderY += y;
}

static void djui_text_render_single_char(struct DjuiText* text, u8 d) {
    struct DjuiBaseRect* comp = &text->base.comp;

    f32 dX = comp->x + sTextRenderX * text->fontSize;
    f32 dY = comp->y + sTextRenderY * text->fontSize;
    f32 dW = DJUI_TEXT_CHAR_WIDTH   * text->fontSize;
    f32 dH = DJUI_TEXT_CHAR_HEIGHT  * text->fontSize;

    if (djui_gfx_add_clipping_specific(&text->base, true, dX, dY, dW, dH)) {
        return;
    }

    create_dl_translation_matrix(DJUI_MTX_NOPUSH, sTextRenderX - sTextRenderLastX, (sTextRenderY - sTextRenderLastY) * -1.0f, 0);
    djui_gfx_render_char(d);

    sTextRenderLastX = sTextRenderX;
    sTextRenderLastY = sTextRenderY;
}

static void djui_text_render_char(struct DjuiText* text, u8 d) {
    if (text->dropShadow.a > 0) {
        // render drop shadow
        struct DjuiBase* base = &text->base;
        sTextRenderX += 0.5f;
        sTextRenderY += 0.5f;
        gDPSetEnvColor(gDisplayListHead++, text->dropShadow.r, text->dropShadow.g, text->dropShadow.b, text->dropShadow.a);
        djui_text_render_single_char(text, d);
        gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);
        sTextRenderX -= 0.5f;
        sTextRenderY -= 0.5f;
    }
    djui_text_render_single_char(text, d);
}

static f32 djui_text_measure_word_width(char* message) {
    f32 width = 0;
    while (*message != '\0') {
        u8 d = str_ascii_char_to_dialog(*message);
        if (d == DIALOG_CHAR_SPACE)      { return width; }
        if (d == DIALOG_CHAR_NEWLINE)    { return width; }
        if (d == DIALOG_CHAR_TERMINATOR) { return width; }
        width += gDialogCharWidths[d];
        message++;
    }
    return width;
}

static void djui_text_read_line(char* message, u16* index, f32* lineWidth, f32 maxLineWidth, bool onLastLine, bool* ellipses) {
    *lineWidth = 0;
    u8 lastD = DIALOG_CHAR_TERMINATOR;

    f32 ellipsesWidth = gDialogCharWidths[0x3F] * 3.0f;
    u16 lastSafeEllipsesIndex = *index;
    u16 lastSafeEllipsesLineWidth = *lineWidth + ellipsesWidth;

    while (message[*index] != '\0') {
        u8 d = str_ascii_char_to_dialog(message[*index]);

        // check for newline
        if (d == DIALOG_CHAR_NEWLINE) {
            *index = *index + 1;
            break;
        }

        // check to see if this character would exceed size
        if (*lineWidth + gDialogCharWidths[d] >= maxLineWidth) {
            break;
        }

        // check to see if this word exceeds size
        if (!onLastLine && lastD == DIALOG_CHAR_SPACE && d != DIALOG_CHAR_SPACE) {
            f32 wordWidth = djui_text_measure_word_width(&message[*index]);
            if (*lineWidth + wordWidth >= maxLineWidth) {
                return;
            }
        }

        *lineWidth += gDialogCharWidths[d];

        // check for safe ellipses index
        if (onLastLine && ((*lineWidth + ellipsesWidth) < maxLineWidth)) {
            lastSafeEllipsesIndex = *index;
            lastSafeEllipsesLineWidth = *lineWidth + ellipsesWidth;
        }

        *index = *index + 1;
        lastD = d;
    }

    // check to see if we should replace the end of the last line with ellipses
    if (onLastLine && message[*index] != '\0') {
        *index = lastSafeEllipsesIndex;
        *lineWidth = lastSafeEllipsesLineWidth;
        *ellipses = true;
    }
}

static void djui_text_render_line(struct DjuiText* text, u16 startIndex, u16 endIndex, f32 lineWidth, bool ellipses) {
    struct DjuiBase* base     = &text->base;
    struct DjuiBaseRect* comp = &base->comp;
    f32 curWidth = 0;

    // horizontal alignment
    if (text->textHAlign == DJUI_HALIGN_CENTER) {
        // center text
        f32 offset = (comp->width / text->fontSize) / 2.0f - lineWidth / 2.0f;
        djui_text_translate(offset, 0);
        curWidth = offset;
    } else if (text->textHAlign == DJUI_HALIGN_RIGHT) {
        // right align text
        f32 offset = (comp->width / text->fontSize) - lineWidth;
        djui_text_translate(offset, 0);
        curWidth = offset;
    }

    // render the line
    for (int i = startIndex; i < endIndex; i++) {
        u8 d = str_ascii_char_to_dialog(text->message[i]);
        switch (d) {
            case DIALOG_CHAR_SPACE:
                break;
            case DIALOG_CHAR_NEWLINE:
                break;
            default:
                djui_text_render_char(text, d);
                break;
        }
        djui_text_translate(gDialogCharWidths[d], 0);
        curWidth += gDialogCharWidths[d];
    }

    // render ellipses
    if (ellipses) {
        for (int i = 0; i < 3; i++) {
            u8 d = str_ascii_char_to_dialog('.');
            djui_text_render_char(text, d);
            djui_text_translate(gDialogCharWidths[d], 0);
            curWidth += gDialogCharWidths[d];
        }
    }

    // reset translation matrix
    djui_text_translate(-curWidth, DJUI_TEXT_CHAR_HEIGHT);
}

  ////////////
 // events //
////////////

static void djui_text_render(struct DjuiBase* base) {
    gSPDisplayList(gDisplayListHead++, dl_djui_ia_text_begin);

    struct DjuiText* text     = (struct DjuiText*)base;
    struct DjuiBaseRect* comp = &base->comp;

    // reset render location
    sTextRenderX = 0;
    sTextRenderY = 0;
    sTextRenderLastX = 0;
    sTextRenderLastY = 0;

    // translate position
    f32 translatedX = comp->x;
    f32 translatedY = comp->y;
    djui_gfx_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // compute size
    f32 translatedWidth  = comp->width;
    f32 translatedHeight = comp->height;
    djui_gfx_scale_translate(&translatedWidth, &translatedHeight);

    // compute font size
    f32 translatedFontSize = text->fontSize;
    djui_gfx_size_translate(&translatedFontSize);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // set color
    gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);

    // count lines
    u16 startIndex = 0;
    u16 endIndex = 0;
    f32 maxLineWidth = comp->width / text->fontSize;
    u16 lineCount = 0;
    u16 maxLines = comp->height / ((f32)DJUI_TEXT_CHAR_HEIGHT * text->fontSize);
    while (text->message[startIndex] != '\0') {
        bool onLastLine = lineCount + 1 >= maxLines;
        f32 lineWidth;
        bool ellipses;
        djui_text_read_line(text->message, &endIndex, &lineWidth, maxLineWidth, onLastLine, &ellipses);
        startIndex = endIndex;
        lineCount++;
        if (onLastLine) { break; }
    }

    // do vertical alignment
    f32 vOffset = 0;
    if (text->textVAlign == DJUI_VALIGN_CENTER) {
        vOffset += (comp->height / text->fontSize) / 2.0f;
        vOffset -= (lineCount * DJUI_TEXT_CHAR_HEIGHT) / 2.0f;
    } else if (text->textVAlign == DJUI_VALIGN_BOTTOM) {
        vOffset += (comp->height / text->fontSize);
        vOffset -= (lineCount * DJUI_TEXT_CHAR_HEIGHT);
    }
    djui_text_translate(0, vOffset);

    // render lines
    startIndex = 0;
    endIndex = 0;
    f32 lineWidth;
    u16 lineIndex = 0;
    bool ellipses = false;
    while (text->message[startIndex] != '\0') {
        bool onLastLine = lineIndex + 1 >= maxLines;
        djui_text_read_line(text->message, &endIndex, &lineWidth, maxLineWidth, onLastLine, &ellipses);
        djui_text_render_line(text, startIndex, endIndex, lineWidth, ellipses);
        startIndex = endIndex;
        lineIndex++;
        if (onLastLine) { break; }
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

static void djui_text_destroy(struct DjuiBase* base) {
    struct DjuiText* text = (struct DjuiText*)base;
    free(text->message);
    free(text);
}

struct DjuiText* djui_text_create(struct DjuiBase* parent, const char* message) {
    struct DjuiText* text = malloc(sizeof(struct DjuiText));
    struct DjuiBase* base = &text->base;

    djui_base_init(parent, base, djui_text_render, djui_text_destroy);

    text->message = NULL;
    djui_text_set_text(text, message);
    djui_text_set_font_size(text, 2.0f);
    djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

    return text;
}
