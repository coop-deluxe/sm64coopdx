#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

void djui_panel_chat_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(OPTIONS, CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, USE_STANDARD_KEY_BINDINGS_CHAT), &configUseStandardKeyBindingsChat, NULL);

        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, CHAT_CHAR_COUNTER), &configChatCharCounter, NULL);
        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, DISABLE_CHAT_WHEN_CLOSED), &configDisableChatWhenClosed, NULL);

        static unsigned int sChatWidthIndex = 3;
        switch (configChatWidth) {
            case 500: sChatWidthIndex = 0; break;
            case 600: sChatWidthIndex = 1; break;
            case 700: sChatWidthIndex = 2; break;
            case 800: sChatWidthIndex = 3; break;
            case 900: sChatWidthIndex = 4; break;
            case 1000: sChatWidthIndex = 5; break;
            case 1100: sChatWidthIndex = 6; break;
            default: sChatWidthIndex = 3; break;
        }

        char* chatWidthChoices[] = {
            DLANG(CHAT_OPTIONS, CHAT_SIZE_TINY),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_SMALL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_SMALL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_NORMAL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_BIG),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_BIG),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_HUGE)
        };
        void on_CHAT_SIZE_change(UNUSED struct DjuiBase* b) {
            unsigned int idx = sChatWidthIndex;
            unsigned int widths[] = { 500, 600, 700, 800, 900, 1000, 1100 };
            configChatWidth = widths[idx];
            if (gDjuiChatBox != NULL) {
                djui_base_set_size(&gDjuiChatBox->base, configChatWidth, gDjuiChatBox->base.height.value);
            }
        }
        djui_selectionbox_create(body, DLANG(CHAT_OPTIONS, CHAT_WIDTH), chatWidthChoices, 7, &sChatWidthIndex, on_CHAT_SIZE_change);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}


