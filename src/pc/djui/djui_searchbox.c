#include <stdio.h>
#include <string.h>
#include "djui.h"

static void djui_searchbox_destroy(struct DjuiBase* base) {
    struct DjuiSearchbox* searchbox = (struct DjuiSearchbox*)base;
    free(searchbox);
}

static void djui_searchbox_on_value_change(struct DjuiBase* base) {
    struct DjuiInputbox* input = (struct DjuiInputbox*)base;
    struct DjuiSearchbox* searchbox = (struct DjuiSearchbox*)input->base.parent->parent;

    if (input->buffer[0] != '\0') {
        djui_base_set_visible(&searchbox->text->base, false);
    } else {
        djui_base_set_visible(&searchbox->text->base, true);
    }

    if (searchbox->on_value_change) {
        searchbox->on_value_change(base);
    }
}

struct DjuiSearchbox* djui_searchbox_create(struct DjuiBase* parent, void (*on_value_change)(struct DjuiBase*)) {
    struct DjuiSearchbox* searchbox = calloc(1, sizeof(struct DjuiSearchbox));
    struct DjuiBase* base = &searchbox->base;
    struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
    struct DjuiColor disabledTextColor = theme->interactables.disabledTextColor;

    djui_base_init(parent, base, NULL, djui_searchbox_destroy);

    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0f, 35.0f);

    struct DjuiFlowLayout* searchFlow = djui_flow_layout_create(base);
    djui_base_set_color(&searchFlow->base, 0, 0, 0, 0);
    djui_base_set_size_type(&searchFlow->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&searchFlow->base, 1.0f, 35.0f);
    djui_flow_layout_set_margin(searchFlow, 0);
    djui_flow_layout_set_flow_direction(searchFlow, DJUI_FLOW_DIR_RIGHT);

    struct DjuiInputbox* searchInputBox = djui_inputbox_create(&searchFlow->base, 64);
    djui_base_set_alignment(&searchInputBox->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&searchInputBox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&searchInputBox->base, 1.0f, 35.0f);
    djui_interactable_hook_value_change(&searchInputBox->base, djui_searchbox_on_value_change);
    searchInputBox->yOffset = 0;
    searchbox->inputbox = searchInputBox;

    struct DjuiText* text = djui_text_create(&searchInputBox->base, "Search...");
    djui_base_set_color(&text->base, disabledTextColor.r, disabledTextColor.g, disabledTextColor.b, disabledTextColor.a);
    djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&text->base, 1.0f, 1.0f);
    djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    searchbox->text = text;

    searchbox->on_value_change = on_value_change;

    return searchbox;
}