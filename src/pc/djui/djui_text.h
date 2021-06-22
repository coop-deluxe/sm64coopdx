#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiText {
    struct DjuiBase base;
    char* message;
    struct DjuiFont* font;
    f32 fontScale;
    struct DjuiColor dropShadow;
    enum DjuiHAlign textHAlign;
    enum DjuiVAlign textVAlign;
};

void djui_text_set_text(struct DjuiText* text, const char* message);
void djui_text_set_font(struct DjuiText* text, struct DjuiFont* font);
void djui_text_set_font_scale(struct DjuiText* text, f32 fontScale);
void djui_text_set_drop_shadow(struct DjuiText* text, f32 r, f32 g, f32 b, f32 a);
void djui_text_set_alignment(struct DjuiText* text, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign);

struct DjuiText* djui_text_create(struct DjuiBase* parent, const char* message);
