#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_chat.h"
#include "pc/configfile.h"
#include "audio/external.h"

static struct DjuiCheckbox* sClassicControlsCheckbox = NULL;
static struct DjuiCheckbox* sCharCounterCheckbox = NULL;
static struct DjuiSelectionbox* sClosedModeSelection = NULL;
static struct DjuiSlider* sLifetimeSlider = NULL;
static struct DjuiSlider* sWidthSlider = NULL;
static struct DjuiSlider* sHeightSlider = NULL;
static struct DjuiSlider* sTextScaleSlider = NULL;
static struct DjuiSlider* sBackgroundOpacitySlider = NULL;
static struct DjuiSlider* sTextOpacitySlider = NULL;

static void djui_panel_chat_apply_layout(UNUSED struct DjuiBase* caller) {
    djui_chat_box_apply_layout();
}

static void djui_panel_chat_refresh_checkbox(struct DjuiCheckbox* checkbox) {
    if (checkbox == NULL) { return; }
    djui_base_set_visible(&checkbox->rectValue->base, *checkbox->value);
}

static void djui_panel_chat_closed_mode_change(UNUSED struct DjuiBase* caller) {
    if (sLifetimeSlider != NULL) {
        djui_base_set_enabled(&sLifetimeSlider->base, configChatClosedMode == 1);
    }
    djui_chat_box_apply_layout();
}

static void djui_panel_chat_reset(UNUSED struct DjuiBase* caller) {
    configUseStandardKeyBindingsChat = true;
    configChatCharCounter = true;
    configChatClosedMode = 1;
    configChatMessageLifetime = 10;
    configChatWidth = 800;
    configChatHeight = 400;
    configChatTextScale = 100;
    configChatBackgroundOpacity = 70;
    configChatTextOpacity = 100;

    djui_panel_chat_refresh_checkbox(sClassicControlsCheckbox);
    djui_panel_chat_refresh_checkbox(sCharCounterCheckbox);

    if (sClosedModeSelection != NULL) {
        djui_selectionbox_update_value(&sClosedModeSelection->base);
    }

    if (sLifetimeSlider != NULL) {
        djui_base_set_enabled(&sLifetimeSlider->base, configChatClosedMode == 1);
        djui_slider_update_value(&sLifetimeSlider->base);
    }
    if (sWidthSlider != NULL) { djui_slider_update_value(&sWidthSlider->base); }
    if (sHeightSlider != NULL) { djui_slider_update_value(&sHeightSlider->base); }
    if (sTextScaleSlider != NULL) { djui_slider_update_value(&sTextScaleSlider->base); }
    if (sBackgroundOpacitySlider != NULL) { djui_slider_update_value(&sBackgroundOpacitySlider->base); }
    if (sTextOpacitySlider != NULL) { djui_slider_update_value(&sTextOpacitySlider->base); }

    djui_chat_box_apply_layout();
    play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
}

void djui_panel_chat_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CHAT_OPTIONS, CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        sClassicControlsCheckbox = djui_checkbox_create(body, DLANG(MISC, USE_STANDARD_KEY_BINDINGS_CHAT), &configUseStandardKeyBindingsChat, NULL);
        sCharCounterCheckbox = djui_checkbox_create(body, DLANG(CHAT_OPTIONS, CHAT_CHAR_COUNTER), &configChatCharCounter, NULL);

        char* closedModeChoices[3] = {
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_DISABLED),
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_FADE),
            DLANG(CHAT_OPTIONS, CHAT_CLOSED_ALWAYS)
        };
        sClosedModeSelection = djui_selectionbox_create(body, DLANG(CHAT_OPTIONS, CHAT_CLOSED_MODE), closedModeChoices, 3, &configChatClosedMode, djui_panel_chat_closed_mode_change);

        sLifetimeSlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_LIFETIME), &configChatMessageLifetime, 1, 120, NULL);
        djui_slider_set_value_suffix(sLifetimeSlider, "s");
        djui_base_set_enabled(&sLifetimeSlider->base, configChatClosedMode == 1);

        sWidthSlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_WIDTH), &configChatWidth, 200, 2000, djui_panel_chat_apply_layout);
        sHeightSlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_HEIGHT), &configChatHeight, 100, 1000, djui_panel_chat_apply_layout);
        sTextScaleSlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_TEXT_SCALE), &configChatTextScale, 50, 200, djui_panel_chat_apply_layout);

        sBackgroundOpacitySlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_BACKGROUND_OPACITY), &configChatBackgroundOpacity, 0, 100, djui_panel_chat_apply_layout);
        djui_slider_set_value_suffix(sBackgroundOpacitySlider, "%");

        sTextOpacitySlider = djui_slider_create(body, DLANG(CHAT_OPTIONS, CHAT_TEXT_OPACITY), &configChatTextOpacity, 0, 100, djui_panel_chat_apply_layout);
        djui_slider_set_value_suffix(sTextOpacitySlider, "%");

        djui_button_create(body, DLANG(CHAT_OPTIONS, RESET), DJUI_BUTTON_STYLE_NORMAL, djui_panel_chat_reset);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
