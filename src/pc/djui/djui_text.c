#include <string.h>
#include "djui.h"
#include "djui_unicode.h"
#include "djui_hud_utils.h"
#include "game/segment2.h"

static u8 sSavedR = 0;
static u8 sSavedG = 0;
static u8 sSavedB = 0;
static u8 sSavedA = 0;

  ////////////////
 // properties //
////////////////

void djui_text_set_text(struct DjuiText* text, const char* message) {
    // validate that the text needs to change
    if (text->message != NULL && strcmp(text->message, message) == 0) {
        return;
    }

    // deallocate old message
    if (text->message != NULL) {
        free(text->message);
    }

    // allocate and set new message
    u16 messageLen = strlen(message);
    text->message = calloc((messageLen + 1), sizeof(char));
    memcpy(text->message, message, sizeof(char) * (messageLen + 1));
}

void djui_text_set_font(struct DjuiText* text, const struct DjuiFont* font) {
    text->font = font;
}

void djui_text_set_font_scale(struct DjuiText* text, f32 fontScale) {
    text->fontScale = fontScale;
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

static f32 sTextRenderX = 0;
static f32 sTextRenderY = 0;
static f32 sTextRenderLastX = 0;
static f32 sTextRenderLastY = 0;

static void djui_text_translate(f32 x, f32 y) {
    sTextRenderX += x;
    sTextRenderY += y;
}

static void djui_text_render_single_char(struct DjuiText* text, char* c) {
    struct DjuiBaseRect* comp = &text->base.comp;

    f32 dX = comp->x + sTextRenderX * text->fontScale;
    f32 dY = comp->y + sTextRenderY * text->fontScale;
    f32 dW = text->font->charWidth  * text->fontScale;
    f32 dH = text->font->charHeight * text->fontScale;

    if (djui_gfx_add_clipping_specific(&text->base, dX, dY, dW, dH)) {
        return;
    }

    create_dl_translation_matrix(DJUI_MTX_NOPUSH, sTextRenderX - sTextRenderLastX, (sTextRenderY - sTextRenderLastY) * -1.0f, 0);
    text->font->render_char(c);

    sTextRenderLastX = sTextRenderX;
    sTextRenderLastY = sTextRenderY;
}

static void djui_text_render_char(struct DjuiText* text, char* c) {
    if (text->dropShadow.a > 0) {
        // render drop shadow
        sTextRenderX += 1.0f / text->fontScale;
        sTextRenderY += 1.0f / text->fontScale;
        gDPSetEnvColor(gDisplayListHead++, text->dropShadow.r, text->dropShadow.g, text->dropShadow.b, text->dropShadow.a);
        djui_text_render_single_char(text, c);
        gDPSetEnvColor(gDisplayListHead++, sSavedR, sSavedG, sSavedB, sSavedA);
        sTextRenderX -= 1.0f / text->fontScale;
        sTextRenderY -= 1.0f / text->fontScale;
    }
    djui_text_render_single_char(text, c);
}

static f32 djui_text_measure_word_width(struct DjuiText* text, char* message) {
    f32 width = 0;
    bool skipping = false;
    char* c = message;
    while (*c != '\0') {
        if (*c == ' ')  { return width; }
        if (*c == '\n') { return width; }
        if (*c == '\0') { return width; }
        if (*c == '\\') { skipping = !skipping; }
        if (!skipping) {
            width += text->font->char_width(c);
        }
        c = djui_unicode_next_char(c);
    }
    return width;
}

static void djui_text_read_line(struct DjuiText* text, char** message, f32* lineWidth, f32 maxLineWidth, bool onLastLine, UNUSED bool* ellipses) {
    *lineWidth = 0;
    char* lastC = "\0";

    /*f32 ellipsesWidth = gDialogCharWidths[0x3F] * 3.0f;
    u16 lastSafeEllipsesIndex = *index;
    u16 lastSafeEllipsesLineWidth = *lineWidth + ellipsesWidth;*/

    bool skipping = false;
    char* c = *message;
    while (*c != '\0') {
        f32 charWidth = text->font->char_width(c);

        // check for special escape sequences
        if (*c == '\\') { skipping = !skipping; }
        if (skipping || *c == '\\') {
            lastC = c;
            c = djui_unicode_next_char(c);
            continue;
        }

        // check for newline
        if (*c == '\n') {
            c = djui_unicode_next_char(c);
            break;
        }

        // check to see if this character would exceed size
        if (*lineWidth + charWidth >= maxLineWidth) {
            break;
        }

        // check to see if this word exceeds size
        if (!onLastLine && *lastC == ' ' && *c != ' ') {
            f32 wordWidth = djui_text_measure_word_width(text, c);
            if (*lineWidth + wordWidth >= maxLineWidth) {
                *message = c;
                return;
            }
        }

        *lineWidth += charWidth;

        // check for safe ellipses index
        /*if (onLastLine && ((*lineWidth + ellipsesWidth) < maxLineWidth)) {
            lastSafeEllipsesIndex = *index;
            lastSafeEllipsesLineWidth = *lineWidth + ellipsesWidth;
        }*/

        lastC = c;
        c = djui_unicode_next_char(c);
    }

    // check to see if we should replace the end of the last line with ellipses
    /*if (onLastLine && message[*index] != '\0') {
        *index = lastSafeEllipsesIndex;
        *lineWidth = lastSafeEllipsesLineWidth;
        *ellipses = true;
    }*/
    *message = c;
}

int djui_text_count_lines(struct DjuiText* text, u16 maxLines) {
    struct DjuiBaseRect* comp = &text->base.comp;
    char* c = text->message;
    f32 maxLineWidth = comp->width / ((f32)text->fontScale);
    u16 lineCount = 0;
    while (*c != '\0') {
        bool onLastLine = lineCount + 1 >= maxLines;
        f32 lineWidth;
        bool ellipses;
        djui_text_read_line(text, &c, &lineWidth, maxLineWidth, onLastLine, &ellipses);
        lineCount++;
        if (onLastLine) { break; }
    }
    return lineCount;
}

f32 djui_text_find_width(struct DjuiText* text, u16 maxLines) {
    struct DjuiBaseRect* comp = &text->base.comp;
    char* c = text->message;
    f32 maxLineWidth = comp->width / ((f32)text->fontScale);
    u16 lineCount = 0;

    f32 largestWidth = 0;

    while (*c != '\0') {
        bool onLastLine = lineCount + 1 >= maxLines;
        f32 lineWidth;
        bool ellipses;
        djui_text_read_line(text, &c, &lineWidth, maxLineWidth, onLastLine, &ellipses);
        largestWidth = fmax(largestWidth, lineWidth);
        lineCount++;
        if (onLastLine) { break; }
    }
    return largestWidth * text->fontScale;
}

static char* djui_text_render_line_parse_escape(char* c1, char* c2) {
    bool parsingColor = (c1[1] == '#');
    char* c = parsingColor ? (c1 + 2) : (c1 + 1);

    u32 color = 0;
    u8 colorPieces = 0;
    while (c < c2) {
        if (*c == '\\') { break; }
        if (parsingColor) {
            u8 colorPiece = 0;
            if (*c >= '0' && *c <= '9') { colorPiece = *c - '0'; }
            else if (*c >= 'a' && *c <= 'f') { colorPiece = 10 + *c - 'a'; }
            else if (*c >= 'A' && *c <= 'F') { colorPiece = 10 + *c - 'A'; }
            color = (color << 4) | colorPiece;
            colorPieces++;
        }
        c = djui_unicode_next_char(c);
    }

    if (parsingColor) {
       if (colorPieces == 3) {
            u32 r = (color >> 8) & 0xF;
            u32 g = (color >> 4) & 0xF;
            u32 b = (color >> 0) & 0xF;
            sSavedR = (r << 4) | r;
            sSavedG = (g << 4) | g;
            sSavedB = (b << 4) | b;
        /*} else if (colorPieces == 4) {
            u32 r = (color >> 12) & 0xF;
            u32 g = (color >> 8) & 0xF;
            u32 b = (color >> 4) & 0xF;
            u32 a = (color >> 0) & 0xF;
            sSavedR = (r << 4) | r;
            sSavedG = (g << 4) | g;
            sSavedB = (b << 4) | b;
            sSavedA = (a << 4) | a;*/
        } else if (colorPieces == 6) {
            sSavedR = ((color >> 16) & 0xFF);
            sSavedG = ((color >>  8) & 0xFF);
            sSavedB = ((color >>  0) & 0xFF);
        }/*else if (colorPieces == 8) {
            sSavedR = ((color >> 24) & 0xFF);
            sSavedG = ((color >> 16) & 0xFF);
            sSavedB = ((color >>  8) & 0xFF);
            sSavedA = ((color >>  0) & 0xFF);
        }*/
        gDPSetEnvColor(gDisplayListHead++, sSavedR, sSavedG, sSavedB, sSavedA);
    }

    c = djui_unicode_next_char(c);
    return c;
}

static void djui_text_render_line(struct DjuiText* text, char* c1, char* c2, f32 lineWidth, bool ellipses) {
    struct DjuiBase* base     = &text->base;
    struct DjuiBaseRect* comp = &base->comp;
    f32 curWidth = 0;

    // horizontal alignment
    if (text->textHAlign == DJUI_HALIGN_CENTER) {
        // center text
        f32 offset = (comp->width / text->fontScale) / 2.0f - lineWidth / 2.0f;
        djui_text_translate(offset, 0);
        curWidth = offset;
    } else if (text->textHAlign == DJUI_HALIGN_RIGHT) {
        // right align text
        f32 offset = (comp->width / text->fontScale) - lineWidth;
        djui_text_translate(offset, 0);
        curWidth = offset;
    }

    // render the line
    for (char* c = c1; c < c2;) {
        if (*c == '\\') {
            c = djui_text_render_line_parse_escape(c, c2);
            continue;
        }

        f32 charWidth = text->font->char_width(c);
        if (*c != '\n' && *c != ' ') {
            djui_text_render_char(text, c);
        }

        djui_text_translate(charWidth, 0);
        curWidth += charWidth;
        c = djui_unicode_next_char(c);
    }

    // render ellipses
    if (ellipses) {
        char* c = ".";
        for (int i = 0; i < 3; i++) {
            f32 charWidth = text->font->char_width(c);
            djui_text_render_char(text, c);
            djui_text_translate(charWidth, 0);
            curWidth += charWidth;
            c = djui_unicode_next_char(c);
        }
    }

    // reset translation matrix
    djui_text_translate(-curWidth, text->font->lineHeight);
}

  ////////////
 // events //
////////////

static bool djui_text_render(struct DjuiBase* base) {
    struct DjuiText* text     = (struct DjuiText*)base;
    struct DjuiBaseRect* comp = &base->comp;

    if (text->font->textBeginDisplayList != NULL) {
        gSPDisplayList(gDisplayListHead++, text->font->textBeginDisplayList);
    }

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
    f32 translatedFontSize = text->fontScale;
    djui_gfx_size_translate(&translatedFontSize);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedFontSize, translatedFontSize, 1.0f);

    // set color
    gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);
    sSavedR = base->color.r;
    sSavedG = base->color.g;
    sSavedB = base->color.b;
    sSavedA = base->color.a;

    // count lines
    u16 maxLines = comp->height / ((f32)text->font->lineHeight * text->fontScale);
    f32 maxLineWidth = comp->width / ((f32)text->fontScale);
    u16 lineCount = djui_text_count_lines(text, maxLines);

    // do vertical alignment
    f32 vOffset = 0;
    if (text->textVAlign == DJUI_VALIGN_CENTER) {
        vOffset += (comp->height / text->fontScale) / 2.0f;
        vOffset -= (lineCount * text->font->charHeight) / 2.0f;
    } else if (text->textVAlign == DJUI_VALIGN_BOTTOM) {
        vOffset += (comp->height / text->fontScale);
        vOffset -= (lineCount * text->font->charHeight);
    }
    djui_text_translate(0, vOffset);

    // render lines
    char* c1 = text->message;
    char* c2 = c1;
    f32 lineWidth;
    u16 lineIndex = 0;
    bool ellipses = false;
    while (*c1 != '\0') {
        bool onLastLine = lineIndex + 1 >= maxLines;
        djui_text_read_line(text, &c2, &lineWidth, maxLineWidth, onLastLine, &ellipses);
        djui_text_render_line(text, c1, c2, lineWidth, ellipses);
        c1 = c2;
        lineIndex++;
        if (onLastLine) { break; }
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    return true;
}

static void djui_text_destroy(struct DjuiBase* base) {
    struct DjuiText* text = (struct DjuiText*)base;
    free(text->message);
    free(text);
}

struct DjuiText* djui_text_create(struct DjuiBase* parent, const char* message) {
    struct DjuiText* text = calloc(1, sizeof(struct DjuiText));
    struct DjuiBase* base = &text->base;

    djui_base_init(parent, base, djui_text_render, djui_text_destroy);

    text->message = NULL;
    djui_text_set_font(text, gDjuiFonts[configDjuiThemeFont == 0 ? FONT_NORMAL : FONT_ALIASED]);
    djui_text_set_font_scale(text, text->font->defaultFontScale);
    djui_text_set_text(text, message);
    djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    djui_text_set_drop_shadow(text, 0, 0, 0, 0);

    return text;
}
