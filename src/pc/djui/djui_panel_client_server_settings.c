#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "djui_inputbox.h"

void djui_panel_client_server_settings_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_SETTINGS, SETTINGS), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        char* iChoices[3] = { DLANG(HOST_SETTINGS, NONSOLID), DLANG(HOST_SETTINGS, SOLID), DLANG(HOST_SETTINGS, FRIENDLY_FIRE) };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(HOST_SETTINGS, PLAYER_INTERACTION), iChoices, 3, &gServerSettings.playerInteractions, NULL);
        djui_base_set_enabled(&selectionbox1->base, false);

        unsigned int sKnockbackIndex = (gServerSettings.playerKnockbackStrength <= 20)
                        ? 0
                        : ((gServerSettings.playerKnockbackStrength <= 40) ? 1 : 2);
        char* kChoices[3] = { DLANG(HOST_SETTINGS, WEAK), DLANG(HOST_SETTINGS, NORMAL), DLANG(HOST_SETTINGS, TOO_MUCH) };
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(body, DLANG(HOST_SETTINGS, KNOCKBACK_STRENGTH), kChoices, 3, &sKnockbackIndex, NULL);
        djui_base_set_enabled(&selectionbox2->base, false);

        char* pChoices[2] = { DLANG(HOST_SETTINGS, CLASSIC_PVP), DLANG(HOST_SETTINGS, REVAMPED_PVP) };
        struct DjuiSelectionbox* selectionbox3 = djui_selectionbox_create(body, DLANG(HOST_SETTINGS, PVP_MODE), pChoices, 2, &gServerSettings.pvpType, NULL);
        djui_base_set_enabled(&selectionbox3->base, false);

        unsigned int sStayInLevelAfterStar = gServerSettings.stayInLevelAfterStar;
        char* lChoices[3] = { DLANG(HOST_SETTINGS, LEAVE_LEVEL), DLANG(HOST_SETTINGS, STAY_IN_LEVEL), DLANG(HOST_SETTINGS, NONSTOP) };
        struct DjuiSelectionbox* selectionbox4 = djui_selectionbox_create(body, DLANG(HOST_SETTINGS, ON_STAR_COLLECTION), lChoices, 3, &sStayInLevelAfterStar, NULL);
        djui_base_set_enabled(&selectionbox4->base, false);

        char* bChoices[3] = { DLANG(HOST_SETTINGS, BOUNCY_BOUNDS_OFF), DLANG(HOST_SETTINGS, BOUNCY_BOUNDS_ON), DLANG(HOST_SETTINGS, BOUNCY_BOUNDS_ON_CAP) };
        struct DjuiSelectionbox* selectionbox5 = djui_selectionbox_create(body, DLANG(HOST_SETTINGS, BOUNCY_LEVEL_BOUNDS), bChoices, 3, &gServerSettings.bouncyLevelBounds, NULL);
        djui_base_set_enabled(&selectionbox5->base, false);

        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(body, DLANG(HOST_SETTINGS, SKIP_INTRO_CUTSCENE), (bool*)&gServerSettings.skipIntro, NULL);
        djui_base_set_enabled(&checkbox1->base, false);
        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(body, DLANG(HOST_SETTINGS, PAUSE_ANYWHERE), (bool*)&gServerSettings.pauseAnywhere, NULL);
        djui_base_set_enabled(&checkbox2->base, false);
        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(body, DLANG(HOST_SETTINGS, BUBBLE_ON_DEATH), (bool*)&gServerSettings.bubbleDeath, NULL);
        djui_base_set_enabled(&checkbox3->base, false);
        struct DjuiCheckbox* checkbox4 = djui_checkbox_create(body, DLANG(HOST_SETTINGS, NAMETAGS), (bool*)&gServerSettings.nametags, NULL);
        djui_base_set_enabled(&checkbox4->base, false);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(HOST_SETTINGS, AMOUNT_OF_PLAYERS));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.45f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char limitString[32] = { 0 };
            snprintf(limitString, 32, "%d", gServerSettings.maxPlayers);
            djui_inputbox_set_text(inputbox1, limitString);
            djui_base_set_enabled(&inputbox1->base, false);
        }

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }
    djui_panel_add(caller, panel, NULL);
}