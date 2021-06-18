#pragma once
#include "djui.h"

#pragma pack(1)
struct DjuiText {
    struct DjuiBase base;
    char* message;
    f32 fontSize;
    enum DjuiHAlign textHAlign;
    enum DjuiVAlign textVAlign;
};

void djui_text_set_text(struct DjuiText* text, const char* message);
void djui_text_set_font_size(struct DjuiText* text, f32 fontSize);
void djui_text_set_alignment(struct DjuiText* text, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign);

struct DjuiText* djui_text_create(struct DjuiBase* parent, const char* message);
