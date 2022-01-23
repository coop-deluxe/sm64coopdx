#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/cheats.h"

static unsigned int sKnockbackIndex = 0;

static void djui_panel_host_settings_knockback_change(UNUSED struct DjuiBase* caller) {
    switch (sKnockbackIndex) {
        case 0:  configPlayerKnockbackStrength = 10; break;
        case 1:  configPlayerKnockbackStrength = 25; break;
        default: configPlayerKnockbackStrength = 75; break;
    }
}

void djui_panel_host_settings_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * 7 + 64 * 1 + 16 * 7;

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

        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Stay in level after star", &configStayInLevelAfterStar);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);

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

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
        defaultBase = &button1->base;
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
