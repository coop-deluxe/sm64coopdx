#include <stdio.h>
#include "djui.h"
#include "pc/configfile.h"
#include "pc/network/network_player.h"
#include "game/level_update.h"
#include "game/area.h"

static bool djui_panel_player_name_valid(char* buffer) {
    if (buffer[0] == '\0') { return false; }
    while (*buffer != '\0') {
        if (*buffer >= '!' && *buffer <= '~') {
            buffer++;
            continue;
        }
        return false;
    }
    return true;
}

static void djui_panel_player_name_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (djui_panel_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_player_name_on_focus_end(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (!djui_panel_player_name_valid(inputbox1->buffer)) {
        djui_inputbox_set_text(inputbox1, "Player");
    }
    snprintf(configPlayerName, 20, "%s", inputbox1->buffer);
    djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
}

void djui_panel_player_value_changed(UNUSED struct DjuiBase* caller) {
    if (configPlayerModel >= CT_MAX) { configPlayerModel = 0; }
    gNetworkPlayers[0].modelIndex = configPlayerModel;
    gNetworkPlayers[0].paletteIndex = configPlayerPalette;
    network_player_update_model(0);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }
}

void djui_panel_player_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 3 + 64 * 1 + 16 * 4;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\P\\#1be700\\L\\#00b3ff\\A\\#ffef00\\Y\\#ff0800\\E\\#1be700\\R");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 32);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Name");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 20);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.5f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            if (djui_panel_player_name_valid(configPlayerName)) {
                djui_inputbox_set_text(inputbox1, configPlayerName);
            } else {
                djui_inputbox_set_text(inputbox1, "Player");
            }
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_player_name_text_change);
            djui_interactable_hook_focus(&inputbox1->base, NULL, NULL, djui_panel_player_name_on_focus_end);
        }

        char* modelChoices[CT_MAX] = { 0 };
        for (int i = 0; i < CT_MAX; i++) {
            modelChoices[i] = gCharacters[i].name;
        }
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Model", modelChoices, CT_MAX, &configPlayerModel);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&selectionbox1->base, djui_panel_player_value_changed);

        char* paletteChoices[24] = {
            "Mario",
            "Luigi",
            "Waluigi",
            "Wario",
            "Chuckya",
            "Goomba",
            "Clover",
            "Cobalt",
            "Fury",
            "Hot Pink",
            "Nice Pink",
            "Seafoam",
            "Lilac",
            "Copper",
            "Azure",
            "Burgundy",
            "Mint",
            "Eggplant",
            "Orange",
            "Arctic",
            "Fire Mario",
            "Fire Luigi",
            "Fire Waluigi",
            "Fire Wario",
        };
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(&body->base, "Palette", paletteChoices, 24, &configPlayerPalette);
        djui_base_set_size_type(&selectionbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&selectionbox2->base, djui_panel_player_value_changed);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
