#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/configfile.h"
#include "pc/proximity_chat.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"

static struct DjuiBase* activation_threshold_slider;
static float threshold;

static void djui_panel_sound_value_change(UNUSED struct DjuiBase* caller) {
    audio_custom_update_volume();
}

static void djui_panel_mode_value_change(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(activation_threshold_slider, configProxchatActivationMode == PROXCHAT_ACTMODE_THRESHOLD);

    u32* mute_state = proxchat_player_muted(0);
    if (configProxchatActivationMode == PROXCHAT_ACTMODE_PUSH_TO_TALK) *mute_state |= PROXCHAT_MUTE_LOCAL;
    else *mute_state &= ~PROXCHAT_MUTE_LOCAL;
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
        djui_slider_create(body, DLANG(PROXCHAT, STEREO_SPREAD), &configProxchatStereoSpread, 0, 100, NULL);
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

static struct DjuiImage* djui_texture_create(struct DjuiBase* base, struct TextureInfo* info) {
    return djui_image_create(base, info->texture, info->width, info->height, info->format, info->size);
}

static struct DjuiPaginated* sPlayerPaginated;
static struct DjuiFlowLayout* sPlayerLayout;
static struct DjuiInputbox* sSearchInputbox = NULL;

static struct MicButton {
    bool global;
    s32 player_id;
    struct DjuiBase* base;
    struct DjuiButton* button;
} sMicButtons[32];

static void toggle_mute(struct DjuiBase* caller) {
    struct MicButton* mic = NULL;
    for (int i = 0; i < 32 && !mic; i++) {
        if (sMicButtons[i].base == caller) mic = &sMicButtons[i];
    }
    if (!mic) return;

    u32* mute_state = proxchat_player_muted(mic->player_id);
    if (mic->global) {
        if (*mute_state & PROXCHAT_MUTE_GLOBAL) *mute_state &= ~PROXCHAT_MUTE_GLOBAL;
        else *mute_state |= PROXCHAT_MUTE_GLOBAL;
        dynos_texture_get(*mute_state & PROXCHAT_MUTE_GLOBAL ? "texture_microphone_red_muted" : "texture_microphone_red", &mic->button->icon->textureInfo);
        network_send_proxchat_muted(gNetworkPlayers[mic->player_id].globalIndex, *mute_state & PROXCHAT_MUTE_GLOBAL);
    }
    else {
        if (*mute_state & PROXCHAT_MUTE_LOCAL) *mute_state &= ~PROXCHAT_MUTE_LOCAL;
        else *mute_state |= PROXCHAT_MUTE_LOCAL;
        dynos_texture_get(*mute_state & PROXCHAT_MUTE_LOCAL ? "texture_microphone_muted" : "texture_microphone", &mic->button->icon->textureInfo);
    }
}

#define TEXTURE_INFO(tex) (tex).texture, (tex).width, (tex).height, (tex).format, (tex).size

static void djui_panel_proximity_chat_add_players(struct DjuiBase* body) {
    s32 button_counter = 0;

    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) continue;
        if (sSearchInputbox != NULL &&
            sSearchInputbox->buffer != NULL &&
            !strstr_lowercased(djui_text_get_uncolored_string(NULL, strlen(gNetworkPlayers[i].name) + 1, gNetworkPlayers[i].name), sSearchInputbox->buffer)
        ) continue;

        struct DjuiFlowLayout* layout = djui_flow_layout_create(body);
        djui_flow_layout_set_flow_direction(layout, DJUI_FLOW_DIR_RIGHT);
        djui_base_set_size_type(&layout->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&layout->base, 1, 32);
        djui_base_set_color(&layout->base, 0, 0, 0, 0);

        struct DjuiImage* icon = djui_texture_create(&layout->base, &gMarioStates[i].character->hudHeadTexture);

        struct DjuiFlowLayout* inner_layout = djui_flow_layout_create(&layout->base);
        djui_flow_layout_set_flow_direction(inner_layout, DJUI_FLOW_DIR_LEFT);
        djui_base_set_size_type(&inner_layout->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&inner_layout->base, 1, 32);
        djui_base_set_color(&inner_layout->base, 0, 0, 0, 0);

        struct TextureInfo lmute_tex, gmute_tex;
        dynos_texture_get(*proxchat_player_muted(i) & PROXCHAT_MUTE_LOCAL  ? "texture_microphone_muted"     : "texture_microphone",     &lmute_tex);
        dynos_texture_get(*proxchat_player_muted(i) & PROXCHAT_MUTE_GLOBAL ? "texture_microphone_red_muted" : "texture_microphone_red", &gmute_tex);

        struct DjuiButton* gmute = djui_image_button_create(&inner_layout->base, TEXTURE_INFO(gmute_tex), DJUI_BUTTON_STYLE_NORMAL, toggle_mute);
        struct DjuiButton* lmute = djui_image_button_create(&inner_layout->base, TEXTURE_INFO(lmute_tex), DJUI_BUTTON_STYLE_NORMAL, toggle_mute);
        struct DjuiSlider* vol   = djui_slider_create(&inner_layout->base, gNetworkPlayers[i].name, proxchat_player_volume(i), 0, 100, NULL);

        sMicButtons[button_counter++] = (struct MicButton){ .base = &lmute->base, .button = lmute, .player_id = i, .global = false };
        sMicButtons[button_counter++] = (struct MicButton){ .base = &gmute->base, .button = gmute, .player_id = i, .global = true };

        djui_base_set_alignment(&vol->base,   DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
        djui_base_set_alignment(&lmute->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
        djui_base_set_alignment(&gmute->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);

        djui_base_set_size(&icon->base,        32, 32);
        djui_base_set_size(&lmute->text->base, 32, 32);
        djui_base_set_size(&gmute->text->base, 32, 32);

        djui_base_set_size_type(&lmute->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size_type(&gmute->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&lmute->base, 32, 32);
        djui_base_set_size(&gmute->base, 32, 32);

        djui_base_set_enabled(&gmute->base, gNetworkPlayers[0].moderator || gNetworkPlayers[0].globalIndex == 0);
    }
}

static void djui_panel_rebuild_players_list(UNUSED struct DjuiBase* caller) {
    djui_base_destroy_children(&sPlayerLayout->base);
    sPlayerLayout = sPlayerPaginated->layout;
    djui_panel_proximity_chat_add_players(&sPlayerLayout->base);
    djui_paginated_calculate_height(sPlayerPaginated);
}

void djui_panel_proximity_chat_ingame_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(PROXCHAT, PROXIMITY_CHAT), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiSearchbox* searchbox = djui_searchbox_create(body, djui_panel_rebuild_players_list);
        sSearchInputbox = searchbox->inputbox;

        sPlayerPaginated = djui_paginated_create(body, 8);
        sPlayerPaginated->showMaxCount = true;
        sPlayerLayout = sPlayerPaginated->layout;
        djui_panel_proximity_chat_add_players(&sPlayerLayout->base);
        djui_paginated_calculate_height(sPlayerPaginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_proxchat_back);
    }

    djui_panel_add(caller, panel, NULL);
}
