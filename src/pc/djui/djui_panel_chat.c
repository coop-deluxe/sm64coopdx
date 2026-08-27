#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_chat.h"
#include "pc/configfile.h"

static struct DjuiSlider* sLifetimeSlider = NULL;

static void djui_panel_chat_apply_layout(UNUSED struct DjuiBase* caller) {
    djui_chat_box_apply_layout();
}

static void djui_panel_chat_closed_mode_change(UNUSED struct DjuiBase* caller) {
    if (sLifetimeSlider != NULL) {
        djui_base_set_enabled(&sLifetimeSlider->base, configChatClosedMode == 1);
    }
    djui_chat_box_apply_layout();
}

void djui_panel_chat_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHAT_OPTIONS, CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(MISC, USE_STANDARD_KEY_BINDINGS_CHAT), &configUseStandardKeyBindingsChat, NULL);
        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, CHAT_CHAR_COUNTER), &configChatCharCounter, NULL);

        char* closedModeChoices[3] = {
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_DISABLED),
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_FADE),
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_ALWAYS)
        };
        djui_selectionbox_create(body, DLANG(CHAT_OPTIONS, CHAT_CLOSED_MODE), closedModeChoices, 3, &configChatClosedMode, djui_panel_chat_closed_mode_change);

        sLifetimeSlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_LIFETIME), &configChatMessageLifetime, 1, 120, NULL);
        djui_base_set_enabled(&sLifetimeSlider->base, configChatClosedMode == 1);

        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_WIDTH), &configChatWidth, 200, 2000, djui_panel_chat_apply_layout);
        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_HEIGHT), &configChatHeight, 100, 1000, djui_panel_chat_apply_layout);
        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_TEXT_SCALE), &configChatTextScale, 50, 200, djui_panel_chat_apply_layout);
        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_BACKGROUND_OPACITY), &configChatBackgroundOpacity, 0, 100, djui_panel_chat_apply_layout);
        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_TEXT_OPACITY), &configChatTextOpacity, 0, 100, djui_panel_chat_apply_layout);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
