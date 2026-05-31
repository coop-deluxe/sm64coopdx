#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/configfile.h"
#include "pc/proximity_chat.h"
#include "pc/lua/utils/smlua_audio_utils.h"

static struct DjuiBase* activation_threshold_slider;
static float threshold;

static void djui_panel_sound_value_change(UNUSED struct DjuiBase* caller) {
    audio_custom_update_volume();
}

static void djui_panel_mode_value_change(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(activation_threshold_slider, configProxchatActivationMode == PROXCHAT_ACTMODE_THRESHOLD);
    proxchat_muted = configProxchatActivationMode == PROXCHAT_ACTMODE_PUSH_TO_TALK;
}

static void djui_panel_threshold_value_change(UNUSED struct DjuiBase* caller) {
    threshold = configProxchatActivationThreshold / 100.f;
}

static void djui_panel_proxchat_back(struct DjuiBase* caller) {
    proxchat_loopback = false;
    djui_panel_menu_back(caller);
}

void djui_panel_proximity_chat_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PROXCHAT, PROXIMITY_CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_selectionbox_create(body, DLANG(PROXCHAT, ACTIVATION_MODE), (char*[]){
            DLANG(PROXCHAT, DISABLED), DLANG(PROXCHAT, PUSH_TO_TALK), DLANG(PROXCHAT, THRESHOLD)
        }, 3, &configProxchatActivationMode, djui_panel_mode_value_change);
        djui_bind_create(body,   DLANG(CONTROLS, MUTE_MIC),     configKeyMuteMic);
        djui_bind_create(body,   DLANG(CONTROLS, PUSH_TO_TALK), configKeyPushToTalk);
        djui_slider_create(body, DLANG(SOUND, PROXCHAT_VOLUME), &configProxchatVolume, 0, 127, djui_panel_sound_value_change);
        djui_slider_create(body, DLANG(PROXCHAT, MICROPHONE_GAIN), &configProxchatMicrophoneGain, 0, 400, NULL);
        activation_threshold_slider = &djui_slider_create(body, DLANG(PROXCHAT, ACTIVATION_THRESHOLD), &configProxchatActivationThreshold, 0, 100, djui_panel_threshold_value_change)->base;

        djui_progress_bar_create(body, &threshold, 0, 1, false);
        djui_progress_bar_create(body, &proxchat_mic_level, 0, 1, false);
        djui_checkbox_create(body, DLANG(PROXCHAT, LOOPBACK), &proxchat_loopback, NULL);

        djui_panel_mode_value_change(NULL);
        djui_panel_threshold_value_change(NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_proxchat_back);
    }

    djui_panel_add(caller, panel, NULL);
}
