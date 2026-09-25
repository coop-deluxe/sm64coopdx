#include "djui.h"
#include "pc/configfile.h"

void djui_button_update_style(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    bool secondaryButton = button->style == DJUI_BUTTON_STYLE_SECONDARY;

    u8 rectElement;
    u8 borderElement;
    u8 textElement;

    if (!button->base.enabled) {
        rectElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_DISABLED : DJUI_THEME_ELEMENT_PRIMARY_DISABLED;
        borderElement = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_BORDER_DISABLED : DJUI_THEME_ELEMENT_PRIMARY_BORDER_DISABLED;
        textElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_TEXT_DISABLED : DJUI_THEME_ELEMENT_PRIMARY_TEXT_DISABLED;
        djui_base_set_location(&button->text->base, 0.0f, 0.0f);
    } else if (gDjuiCursorDownOn == base) {
        rectElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_DOWN : DJUI_THEME_ELEMENT_PRIMARY_DOWN;
        borderElement = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_BORDER_DOWN : DJUI_THEME_ELEMENT_PRIMARY_BORDER_DOWN;
        textElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_TEXT : DJUI_THEME_ELEMENT_PRIMARY_TEXT;
        djui_base_set_location(&button->text->base, 1.0f, 1.0f);
    } else if (gDjuiHovered == base) {
        rectElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_HOVER : DJUI_THEME_ELEMENT_PRIMARY_HOVER;
        borderElement = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_BORDER_HOVER : DJUI_THEME_ELEMENT_PRIMARY_BORDER_HOVER;
        textElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_TEXT : DJUI_THEME_ELEMENT_PRIMARY_TEXT;
        djui_base_set_location(&button->text->base, -1.0f, -1.0f);
    } else {
        rectElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY : DJUI_THEME_ELEMENT_PRIMARY;
        borderElement = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_BORDER : DJUI_THEME_ELEMENT_PRIMARY_BORDER;
        textElement   = secondaryButton ? DJUI_THEME_ELEMENT_SECONDARY_TEXT : DJUI_THEME_ELEMENT_PRIMARY_TEXT;
        djui_base_set_location(&button->text->base, 0.0f, 0.0f);
    }

    djui_base_set_color_with_color(&button->rect->base, configDjuiTheme.elements[rectElement]);
    djui_base_set_border_color_with_color(base, configDjuiTheme.elements[borderElement]);
    djui_base_set_color_with_color(&button->text->base, configDjuiTheme.elements[textElement]);
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
    djui_base_set_size(base, 200, configDjuiThemeCenter ? 50 : 64);
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
    djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    button->text = text;

    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, configDjuiThemeCenter ? 50 : 64);
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