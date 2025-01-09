#include "djui.h"
#include "pc/configfile.h"

static void djui_button_update_style(struct DjuiBase* base) {
    struct DjuiButton* button = (struct DjuiButton*)base;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    bool backButton = button->style == DJUI_BUTTON_STYLE_BACK;

    if (!button->base.enabled) {
        struct DjuiColor bc = djui_theme_shade_color(theme->interactables.defaultBorderColor, backButton ? 0.3f : 0.6f);
        struct DjuiColor rc = djui_theme_shade_color(theme->interactables.defaultRectColor, backButton ? 0.3f : 0.6f);

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&button->rect->base, rc.r, rc.g, rc.b, rc.a);
        djui_base_set_location(&button->text->base, 0.0f, 0.0f);
    } else if (gDjuiCursorDownOn == base) {
        struct DjuiColor bc = theme->interactables.cursorDownBorderColor;
        struct DjuiColor rc = theme->interactables.cursorDownRectColor;

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&button->rect->base, rc.r, rc.g, rc.b, rc.a);
        djui_base_set_location(&button->text->base, 1.0f, 1.0f);
    } else if (gDjuiHovered == base) {
        struct DjuiColor bc = theme->interactables.hoveredBorderColor;
        struct DjuiColor rc = theme->interactables.hoveredRectColor;

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&button->rect->base, rc.r, rc.g, rc.b, rc.a);
        djui_base_set_location(&button->text->base, -1.0f, -1.0f);
    } else {
        struct DjuiColor bc = backButton ? djui_theme_shade_color(theme->interactables.defaultBorderColor, 0.6f) : theme->interactables.defaultBorderColor;
        struct DjuiColor rc = backButton ? djui_theme_shade_color(theme->interactables.defaultRectColor, 0.6f) : theme->interactables.defaultRectColor;

        djui_base_set_border_color(base, bc.r, bc.g, bc.b, bc.a);
        djui_base_set_color(&button->rect->base, rc.r, rc.g, rc.b, rc.a);
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
    djui_base_set_size(base, 200, configDjuiThemeCenter ? 50 : 64);
    djui_base_set_border_width(base, 2);
    djui_interactable_create(base, djui_button_update_style);
    button->style = 0;

    struct DjuiRect* rect = djui_rect_create(&button->base);
    djui_base_set_size_type(&rect->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&rect->base, 1.0f, 1.0f);
    button->rect = rect;

    struct DjuiText* text = djui_text_create(&rect->base, message);
    struct DjuiColor color = gDjuiThemes[configDjuiTheme]->interactables.textColor;

    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 1.0f, 1.0f);
    djui_base_set_color(&text->base, color.r, color.g, color.b, color.a);
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