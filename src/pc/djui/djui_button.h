#pragma once
#include "djui.h"

struct DjuiButton {
    struct DjuiBase base;
    struct DjuiRect* rect;
    struct DjuiText* text;
    u8 style;
};

enum DjuiButtonStyle {
    DJUI_BUTTON_STYLE_NORMAL,
    DJUI_BUTTON_STYLE_BACK,
};

void djui_button_set_style(struct DjuiButton* button, enum DjuiButtonStyle style);

struct DjuiButton* djui_button_create(struct DjuiBase* parent, const char* message, enum DjuiButtonStyle style, void (*on_click)(struct DjuiBase*));
struct DjuiButton* djui_button_left_create(struct DjuiBase* parent, const char* message, enum DjuiButtonStyle style, void (*on_click)(struct DjuiBase*));
struct DjuiButton* djui_button_right_create(struct DjuiBase* parent, const char* message, enum DjuiButtonStyle style, void (*on_click)(struct DjuiBase*));
