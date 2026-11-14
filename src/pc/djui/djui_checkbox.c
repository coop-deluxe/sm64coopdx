#include "djui.h"

void djui_checkbox_update_style(struct DjuiBase* base) {
    struct DjuiCheckbox* checkbox = (struct DjuiCheckbox*)base;
    if (!checkbox) { return; }

    enum DjuiThemeElements borderElement;
    enum DjuiThemeElements textElement;
    enum DjuiThemeElements rectValueElement;

    if (!checkbox->base.enabled) {
        borderElement = DJUI_THEME_ELEMENT_CHECKBOX_BORDER_DISABLED;
        textElement = DJUI_THEME_ELEMENT_TEXT_DISABLED;
        rectValueElement = DJUI_THEME_ELEMENT_CHECKBOX_DISABLED;
    } else if (gDjuiCursorDownOn == base) {
        borderElement = DJUI_THEME_ELEMENT_CHECKBOX_BORDER_DOWN;
        textElement = DJUI_THEME_ELEMENT_TEXT;
        rectValueElement = DJUI_THEME_ELEMENT_CHECKBOX_DOWN;
    } else if (gDjuiHovered == base) {
        borderElement = DJUI_THEME_ELEMENT_CHECKBOX_BORDER_HOVER;
        textElement = DJUI_THEME_ELEMENT_TEXT;
        rectValueElement = DJUI_THEME_ELEMENT_CHECKBOX_HOVER;
    } else {
        borderElement = DJUI_THEME_ELEMENT_CHECKBOX_BORDER;
        textElement = DJUI_THEME_ELEMENT_TEXT;
        rectValueElement = DJUI_THEME_ELEMENT_CHECKBOX;
    }
    djui_base_set_border_color_with_color(&checkbox->rect->base, configDjuiTheme.elements[borderElement]);
    djui_base_set_color_with_color(&checkbox->text->base, configDjuiTheme.elements[textElement]);
    djui_base_set_color_with_color(&checkbox->rectValue->base, configDjuiTheme.elements[rectValueElement]);
    djui_base_set_visible(&checkbox->rectValue->base, *checkbox->value);
}

static void djui_checkbox_get_cursor_hover_location(struct DjuiBase* base, f32* x, f32* y) {
    struct DjuiCheckbox* checkbox = (struct DjuiCheckbox*)base;
    struct DjuiBase* rectBase = &checkbox->rect->base;
    *x = (rectBase->elem.x + rectBase->elem.width  * 3.0f / 4.0f);
    *y = (rectBase->elem.y + rectBase->elem.height * 3.0f / 4.0f);
}

static void djui_checkbox_on_cursor_down_begin(struct DjuiBase* base, UNUSED bool inputCursor) {
    struct DjuiCheckbox* checkbox = (struct DjuiCheckbox*)base;
    if (checkbox == NULL) { return; }

    *checkbox->value = !(*checkbox->value);
    djui_base_set_visible(&checkbox->rectValue->base, *checkbox->value);
    if (base->interactable != NULL && base->interactable->on_value_change != NULL) {
        base->interactable->on_value_change(base);
    }
}

static void djui_checkbox_destroy(struct DjuiBase* base) {
    struct DjuiCheckbox* checkbox = (struct DjuiCheckbox*)base;
    free(checkbox);
}

struct DjuiCheckbox* djui_checkbox_create(struct DjuiBase* parent, const char* message, bool* value, void (*on_value_change)(struct DjuiBase*)) {
    struct DjuiCheckbox* checkbox = calloc(1, sizeof(struct DjuiCheckbox));
    struct DjuiBase* base = &checkbox->base;

    checkbox->value = value;

    djui_base_init(parent, base, NULL, djui_checkbox_destroy);
    djui_interactable_create(base, djui_checkbox_update_style);
    djui_interactable_hook_cursor_down(base, djui_checkbox_on_cursor_down_begin, NULL, NULL);

    struct DjuiText* text = djui_text_create(&checkbox->base, message);
    djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 1.0f, 1.0f);
    djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    checkbox->text = text;

    struct DjuiRect* rect = djui_rect_create(&checkbox->base);
    djui_base_set_alignment(&rect->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&rect->base, DJUI_SVT_ASPECT_RATIO, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 1.0f, 1.0f);
    djui_base_set_color(&rect->base, 0, 0, 0, 0);
    djui_base_set_border_width(&rect->base, 2);
    checkbox->rect = rect;

    struct DjuiRect* rectValue = djui_rect_create(&rect->base);
    djui_base_set_size_type(&rectValue->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&rectValue->base, 16, 16);
    djui_base_set_alignment(&rectValue->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_visible(&rectValue->base, *value);
    checkbox->rectValue = rectValue;

    base->get_cursor_hover_location = djui_checkbox_get_cursor_hover_location;

    djui_checkbox_update_style(base);
    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, 32);
    djui_interactable_hook_value_change(base, on_value_change);

    return checkbox;
}
