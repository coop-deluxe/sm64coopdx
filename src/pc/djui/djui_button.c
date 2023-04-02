#include "djui.h"

static void djui_button_update_style(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    if (!button->base.enabled) {
        u8 borderBrightness = button->style ? 50 : 75;
        u8 rectBrightness   = button->style ? 75 : 111;
        djui_base_set_border_color(base, borderBrightness, borderBrightness, borderBrightness, 255);
        djui_base_set_color(&button->rect->base, rectBrightness, rectBrightness, rectBrightness, 255);
        djui_base_set_location(&button->text->base, 0.0f, 0.0f);
    } else if (gDjuiCursorDownOn == base) {
        djui_base_set_border_color(base, 0, 84, 153, 255);
        djui_base_set_color(&button->rect->base, 204, 228, 247, 255);
        djui_base_set_location(&button->text->base, 1.0f, 1.0f);
    } else if (gDjuiHovered == base) {
        djui_base_set_border_color(base, 0, 120, 215, 255);
        djui_base_set_color(&button->rect->base, 229, 241, 251, 255);
        djui_base_set_location(&button->text->base, -1.0f, -1.0f);
    } else {
        u8 borderBrightness = button->style ? 100 : 150;
        u8 rectBrightness   = button->style ? 150 : 222;
        djui_base_set_border_color(base, borderBrightness, borderBrightness, borderBrightness, 255);
        djui_base_set_color(&button->rect->base, rectBrightness, rectBrightness, rectBrightness, 255);
        djui_base_set_location(&button->text->base, 0.0f, 0.0f);
    }
}

void djui_button_set_style(struct DjuiButton* button, enum DjuiButtonStyle style) {
    button->style = style;
    djui_button_update_style(&button->base);
}

static void djui_button_destroy(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    free(button);
}

struct DjuiButton* djui_button_create(struct DjuiBase* parent, const char* message, enum DjuiButtonStyle style, void (*on_click)(struct DjuiBase*)) {
    struct DjuiButton* button = calloc(1, sizeof(struct DjuiButton));
    struct DjuiBase* base     = &button->base;

    djui_base_init(parent, base, NULL, djui_button_destroy);
    djui_base_set_size(base, 200, 64);
    djui_base_set_border_width(base, 2);
    djui_interactable_create(base, djui_button_update_style);
    button->style = 0;

    struct DjuiRect* rect = djui_rect_create(&button->base);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 1.0f, 1.0f);
    button->rect = rect;

    struct DjuiText* text = djui_text_create(&rect->base, message);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 1.0f, 1.0f);
    djui_base_set_color(&text->base, 11, 11, 11, 255);
    djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    button->text = text;

    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, 64);
    djui_interactable_hook_click(base, on_click);
    button->style = style;
    djui_button_update_style(base);

    return button;
}

struct DjuiButton* djui_button_left_create(struct DjuiBase* parent, const char* message, enum DjuiButtonStyle style, void (*on_click)(struct DjuiBase*)) {
    struct DjuiButton* button = djui_button_create(parent, message, style, on_click);
    djui_base_set_size(&button->base, 0.485f, 64);
    djui_base_set_alignment(&button->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    return button;
}

struct DjuiButton* djui_button_right_create(struct DjuiBase* parent, const char* message, enum DjuiButtonStyle style, void (*on_click)(struct DjuiBase*)) {
    struct DjuiButton* button = djui_button_create(parent, message, style, on_click);
    djui_base_set_size(&button->base, 0.485f, 64);
    djui_base_set_alignment(&button->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
    return button;
}