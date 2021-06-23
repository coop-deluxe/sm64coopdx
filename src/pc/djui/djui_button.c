#include "djui.h"

static void djui_button_set_default_style(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    djui_base_set_border_color(base, 173, 173, 173, 255);
    djui_base_set_color(&button->rect->base, 200, 200, 200, 255);
    djui_base_set_location(&button->text->base, 0.0f, 0.0f);
}

static void djui_button_on_hover_begin(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    djui_base_set_border_color(base, 0, 120, 215, 255);
    djui_base_set_color(&button->rect->base, 229, 241, 251, 255);
    djui_base_set_location(&button->text->base, -0.5f, -0.5f);
}

static void djui_button_on_hover_end(struct DjuiBase* base) {
    djui_button_set_default_style(base);
}

static void djui_button_on_cursor_down_begin(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    djui_base_set_border_color(base, 0, 84, 153, 255);
    djui_base_set_color(&button->rect->base, 204, 228, 247, 255);
    djui_base_set_location(&button->text->base, 0.5f, 0.5f);
}

static void djui_button_on_cursor_down_end(struct DjuiBase* base) {
    djui_button_set_default_style(base);
}

static void djui_button_destroy(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    free(button);
}

struct DjuiButton* djui_button_create(struct DjuiBase* parent, const char* message) {
    struct DjuiButton* button = malloc(sizeof(struct DjuiButton));
    struct DjuiBase* base     = &button->base;

    djui_base_init(parent, base, NULL, djui_button_destroy);
    djui_base_set_size(base, 200, 64);
    djui_base_set_border_width(base, 2);
    djui_interactable_create(base,
        djui_button_on_hover_begin,
        djui_button_on_hover_end,
        djui_button_on_cursor_down_begin,
        djui_button_on_cursor_down_end);

    struct DjuiRect* rect = djui_rect_create(&button->base);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 1.0f, 1.0f);
    button->rect = rect;

    struct DjuiText* text = djui_text_create(&rect->base, message);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 1.0f, 1.0f);
    djui_base_set_color(&text->base, 11, 11, 11, 255);
    djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_text_set_drop_shadow(text, 0, 0, 0, 64);
    button->text = text;

    djui_button_set_default_style(base);

    return button;
}
