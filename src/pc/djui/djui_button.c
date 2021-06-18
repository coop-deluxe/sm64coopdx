#include "djui.h"

static void djui_button_destroy(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    free(button);
}

struct DjuiButton* djui_button_create(struct DjuiBase* parent, const char* message) {
    struct DjuiButton* button = malloc(sizeof(struct DjuiButton));
    struct DjuiBase* base     = &button->base;

    djui_base_init(parent, base, NULL, djui_button_destroy);
    djui_base_set_size(base, 200, 64);

    struct DjuiRect* rect = djui_rect_create(&button->base);
    djui_base_set_size_fill(&rect->base, 1.0f, 1.0f);
    djui_base_set_color(&rect->base, 225, 225, 225, 255);
    button->rect = rect;

    struct DjuiText* text = djui_text_create(&rect->base, message);
    djui_base_set_size_fill(&text->base, 1.0f, 1.0f);
    djui_base_set_color(&text->base, 11, 11, 11, 255);
    djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    button->text = text;

    return button;
}
