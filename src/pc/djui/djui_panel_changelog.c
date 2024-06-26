#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"

#define PAGE_COUNT 1

static char sChangelog[PAGE_COUNT][1024];

void djui_panel_changelog_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHANGELOG, CHANGELOG_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 1);
        struct DjuiBase* layoutBase = &paginated->layout->base;

        snprintf(sChangelog[0], 1024, "Hi! This is Gabe Newell, welcome to sm64coopdx %s. If you have downloaded this build and do not come from the sm64coopdx v1.0 Testing Thread, please delete it and inform agentxlp.", SM64COOPDX_VERSION);

        for (int i = 0; i < PAGE_COUNT; i++) {
            struct DjuiText* text = djui_text_create(layoutBase, sChangelog[i]);
            djui_base_set_location(&text->base, 0, 0);
            djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 360);
            djui_base_set_color(&text->base, 220, 220, 220, 255);
            djui_text_set_drop_shadow(text, 64, 64, 64, 100);
            djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        }

        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}