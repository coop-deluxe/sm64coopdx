#pragma once
#include "djui.h"

struct DjuiText {
    struct DjuiBase base;
    char* message;
    const struct DjuiFont* font;
    f32 fontScale;
    struct DjuiColor dropShadow;
    enum DjuiHAlign textHAlign;
    enum DjuiVAlign textVAlign;
};

void djui_text_set_text(struct DjuiText* text, const char* message);
void djui_text_set_font(struct DjuiText* text, const struct DjuiFont* font);
void djui_text_set_font_scale(struct DjuiText* text, f32 fontScale);
void djui_text_set_drop_shadow(struct DjuiText* text, f32 r, f32 g, f32 b, f32 a);
void djui_text_set_alignment(struct DjuiText* text, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign);

int djui_text_count_lines(struct DjuiText* text, u16 maxLines);
f32 djui_text_find_width(struct DjuiText* text, u16 maxLines);

struct DjuiText* djui_text_create(struct DjuiBase* parent, const char* message);
