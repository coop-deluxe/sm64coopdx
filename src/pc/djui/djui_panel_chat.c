#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

void djui_panel_chat_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHAT_OPTIONS, CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, USE_STANDARD_KEY_BINDINGS_CHAT), &configUseStandardKeyBindingsChat, NULL);

        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, CHAT_CHAR_COUNTER), &configChatCharCounter, NULL);
        djui_checkbox_create(body, DLANG(CHAT_OPTIONS, DISABLE_CHAT_WHEN_CLOSED), &configDisableChatWhenClosed, NULL);

        static unsigned int sChatWidthIndex = 5;
        switch (configChatWidth) {
            case 300: sChatWidthIndex = 0; break;
            case 400: sChatWidthIndex = 1; break;
            case 500: sChatWidthIndex = 2; break;
            case 600: sChatWidthIndex = 3; break;
            case 700: sChatWidthIndex = 4; break;
            case 800: sChatWidthIndex = 5; break;
            case 900: sChatWidthIndex = 6; break;
            case 1000: sChatWidthIndex = 7; break;
            case 1100: sChatWidthIndex = 8; break;
            case 1200: sChatWidthIndex = 9; break;
            case 1300: sChatWidthIndex = 10; break;
            default: sChatWidthIndex = 5; break;
        }

        static unsigned int sChatHeightIndex = 5;
        switch (configChatHeight) {
            case 200: sChatHeightIndex = 0; break;
            case 250: sChatHeightIndex = 1; break;
            case 300: sChatHeightIndex = 2; break;
            case 350: sChatHeightIndex = 3; break;
            case 400: sChatHeightIndex = 4; break;
            case 450: sChatHeightIndex = 5; break;
            case 500: sChatHeightIndex = 6; break;
            case 550: sChatHeightIndex = 7; break;
            case 600: sChatHeightIndex = 8; break;
            case 650: sChatHeightIndex = 9; break;
            case 700: sChatHeightIndex = 10; break;
            default: sChatHeightIndex = 4; break;
        }

        char* chatSizeChoices[] = {
            DLANG(CHAT_OPTIONS, CHAT_SIZE_MINIMUM),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_TINY),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_TINY),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_SMALL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_SMALL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_NORMAL),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_BIG),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_BIG),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_HUGE),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_VERY_HUGE),
            DLANG(CHAT_OPTIONS, CHAT_SIZE_MAXIMUM)
        };
        void on_chat_width_change(UNUSED struct DjuiBase* b) {
            unsigned int idx = sChatWidthIndex;
            unsigned int widths[] = { 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300 };
            configChatWidth = widths[idx];
            if (gDjuiChatBox != NULL) {
                djui_base_set_size(&gDjuiChatBox->base, configChatWidth, gDjuiChatBox->base.height.value);
            }
        }
        void on_chat_height_change(UNUSED struct DjuiBase* b) {
            unsigned int idx = sChatHeightIndex;
            unsigned int heights[] = { 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700 };
            configChatHeight = heights[idx];
            if (gDjuiChatBox != NULL) {
                djui_base_set_size(&gDjuiChatBox->base, gDjuiChatBox->base.width.value, configChatHeight);
            }
        }

        djui_selectionbox_create(body, DLANG(CHAT_OPTIONS, CHAT_WIDTH),  chatSizeChoices, 11, &sChatWidthIndex,  on_chat_width_change);
        djui_selectionbox_create(body, DLANG(CHAT_OPTIONS, CHAT_HEIGHT), chatSizeChoices, 11, &sChatHeightIndex, on_chat_height_change);

        void on_chat_style_change(UNUSED struct DjuiBase* b) {
            djui_chat_messages_apply_style();
            if (gDjuiChatBox != NULL) {
                bool hasMessages = (gDjuiChatBox->chatFlow->base.height.value > 2.0f);
                u8 alpha = 0;
                if (hasMessages) {
                    int baseAlpha = (int)(configChatOpacity * 2.55f);
                    if (baseAlpha > 255) { baseAlpha = 255; }
                    if (baseAlpha < 0)   { baseAlpha = 0; }
                    alpha = gDjuiChatBoxFocus ? (u8)baseAlpha : 0;
                }
                djui_base_set_color(&gDjuiChatBox->chatFlow->base, 0, 0, 0, alpha);
            }
        }

        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_TEXT_SCALE),     &configChatTextScale,      50, 150, on_chat_style_change);
        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_OPACITY),        &configChatOpacity,         0, 100, on_chat_style_change);
        djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_LIFETIME),      &configChatMessageLifetime, 3, 60,  NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}


