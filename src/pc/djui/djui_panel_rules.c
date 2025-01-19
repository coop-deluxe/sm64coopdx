#include <string.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_rules.h"
#include "djui_panel_join_lobbies.h"

#ifdef COOPNET
static char sRules[1024];

static void djui_panel_rules_deny(struct DjuiBase* caller) {
    djui_panel_menu_back(caller);
}

static void djui_panel_rules_accept(struct DjuiBase* caller) {
    configRulesVersion = RULES_VERSION;
    djui_panel_join_lobbies_create(caller, "");
}

void djui_panel_rules_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(RULES, RULES_TITLE), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        snprintf(
            sRules,
            1024,
            "%s\n%s\n%s\n%s\n%s\n%s",
            DLANG(RULES, RULE_1),
            DLANG(RULES, RULE_2),
            DLANG(RULES, RULE_3),
            DLANG(RULES, RULE_4),
            DLANG(RULES, RULE_5),
            DLANG(RULES, RULE_6)
        );

        struct DjuiText* text1 = djui_text_create(body, sRules);
        djui_base_set_location(&text1->base, 0, 0);
        djui_base_set_size(&text1->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 11 * 30);
        djui_base_set_color(&text1->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text1, 64, 64, 64, 100);
        djui_text_set_alignment(text1, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

        struct DjuiText* text2 = djui_text_create(body, DLANG(RULES, SUBJECT_TO_CHANGE));
        djui_base_set_location(&text2->base, 0, 0);
        djui_base_set_size(&text2->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 2 * 30);
        djui_base_set_color(&text2->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text2, 64, 64, 64, 100);
        djui_text_set_alignment(text2, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        if (configRulesVersion != RULES_VERSION) {
            struct DjuiText* text3 = djui_text_create(body, DLANG(RULES, NOTICE));
            djui_base_set_location(&text3->base, 0, 0);
            djui_base_set_size(&text3->base, (DJUI_DEFAULT_PANEL_WIDTH * (configDjuiThemeCenter ? DJUI_THEME_CENTERED_WIDTH : 1)) - 64, 3 * 30);
            djui_base_set_color(&text3->base, 220, 220, 220, 255);
            djui_text_set_drop_shadow(text3, 64, 64, 64, 100);
            djui_text_set_alignment(text3, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

            struct DjuiRect* rect = djui_rect_container_create(body, 64);
            {
                djui_button_left_create(&rect->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_rules_deny);
                djui_button_right_create(&rect->base, DLANG(MENU, YES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_rules_accept);
            }
        } else {
            djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
        }

    }

    panel->temporary = true;
    djui_panel_add(caller, panel, NULL);
}
#endif
