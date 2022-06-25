#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/cheats.h"
#include "pc/network/discord/lobby.h"
#include "djui_inputbox.h"

static unsigned int sKnockbackIndex = 0;
struct DjuiInputbox* sPlayerAmount = NULL;

static void djui_panel_host_settings_knockback_change(UNUSED struct DjuiBase* caller) {
    switch (sKnockbackIndex) {
        case 0:  configPlayerKnockbackStrength = 10; break;
        case 1:  configPlayerKnockbackStrength = 25; break;
        default: configPlayerKnockbackStrength = 60; break;
    }
}

static bool djui_panel_host_limit_valid(void) {
    char* buffer = sPlayerAmount->buffer;
    int limit = 0;
    while (*buffer != '\0') {
        if (*buffer < '0' || *buffer > '9') { return false; }
        limit *= 10;
        limit += (*buffer - '0');
        buffer++;
    }
    return limit >= 2 && limit <= MAX_PLAYERS;
}

static void djui_panel_host_player_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (djui_panel_host_limit_valid()) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
        return;
    }
	configAmountofPlayers = atoi(sPlayerAmount->buffer);
}

void djui_panel_host_settings_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 8 + 64 * 1 + 16 * 8;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\S\\#1be700\\E\\#00b3ff\\T\\#ffef00\\T\\#ff0800\\I\\#1be700\\N\\#00b3ff\\G\\#ffef00\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        char* iChoices[3] = { "Non-solid", "Solid", "Friendly Fire" };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Player interaction", iChoices, 3, &configPlayerInteraction);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);

        char* kChoices[3] = { "Weak", "Normal", "Too much" };
        sKnockbackIndex = (configPlayerKnockbackStrength <= 20)
                        ? 0
                        : ((configPlayerKnockbackStrength <= 40) ? 1 : 2);
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(&body->base, "Knockback strength", kChoices, 3, &sKnockbackIndex);
        djui_base_set_size_type(&selectionbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&selectionbox2->base, djui_panel_host_settings_knockback_change);

        char* lChoices[3] = { "Leave level", "Stay in level", "Non-stop" };
        struct DjuiSelectionbox* selectionbox3 = djui_selectionbox_create(&body->base, "On star collection", lChoices, 3, &configStayInLevelAfterStar);
        djui_base_set_size_type(&selectionbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox3->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Skip intro cutscene", &configSkipIntro);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Share lives", &configShareLives);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox4 = djui_checkbox_create(&body->base, "Enable cheats", &configEnableCheats);
        djui_base_set_size_type(&checkbox4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox4->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox5 = djui_checkbox_create(&body->base, "Bubble on death", &configBubbleDeath);
        djui_base_set_size_type(&checkbox5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox5->base, 1.0f, 32);

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 32);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Amount of players");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.5f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char limitString[32] = { 0 };
            snprintf(limitString, 32, "%d", configAmountofPlayers);
            djui_inputbox_set_text(inputbox1, limitString);
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_host_player_text_change);
            sPlayerAmount = inputbox1;
        }
        
        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
    }
    djui_panel_add(caller, &panel->base, defaultBase);
}
