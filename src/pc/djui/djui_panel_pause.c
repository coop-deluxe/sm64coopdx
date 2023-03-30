#include "djui.h"
#include "pc/cheats.h"
#include "pc/pc_main.h"
#include "pc/network/network.h"
#include "game/object_helpers.h"
#include "behavior_table.h"
#include "sm64.h"

bool gDjuiPanelPauseCreated = false;

static void djui_panel_pause_resume(UNUSED struct DjuiBase* caller) {
    djui_panel_shutdown();
}

static void djui_panel_pause_quit_yes(UNUSED struct DjuiBase* caller) {
    network_reset_reconnect_and_rehost();
    network_shutdown(true, false, false);
}

static void djui_panel_pause_quit(struct DjuiBase* caller) {
    if (find_object_with_behavior(bhvActSelector) != NULL || gMarioStates[0].action == ACT_PUSHING_DOOR || gMarioStates[0].action == ACT_PULLING_DOOR) { return; }

    if (gNetworkType == NT_SERVER) {
        djui_panel_confirm_create(caller,
                                "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T",
                                "Are you sure you want to stop hosting?",
                                djui_panel_pause_quit_yes);
    } else {
        djui_panel_confirm_create(caller,
                                "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T",
                                "Are you sure you want to disconnect?",
                                djui_panel_pause_quit_yes);
    }
}

void djui_panel_pause_create(struct DjuiBase* caller) {
    if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }

    f32 bodyHeight = 64 * 4 + 16 * 3;
    if (gServerSettings.enableCheats) { bodyHeight += 64 + 16; }
    if (gNetworkType == NT_SERVER) { bodyHeight += 64 + 16; }

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\P\\#1be700\\A\\#00b3ff\\U\\#ffef00\\S\\#ff0800\\E");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        
        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 64);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);

        struct DjuiButton* button1 = djui_button_create(&rect1->base, "Player");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 0.47f, 64);
        djui_interactable_hook_click(&button1->base, djui_panel_player_create);

        struct DjuiButton* button2 = djui_button_create(&rect1->base, "DynOS Packs");
        djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button2->base, 0.5f, 64);
        djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        djui_interactable_hook_click(&button2->base, djui_panel_dynos_create);
        
        struct DjuiButton* button3 = djui_button_create(&body->base, "Options");
        djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button3->base, 1.0f, 64);
        djui_interactable_hook_click(&button3->base, djui_panel_options_create);
        defaultBase = &button3->base;

        if (gServerSettings.enableCheats) {
            struct DjuiButton* button4 = djui_button_create(&body->base, "Cheats");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);
            djui_interactable_hook_click(&button4->base, djui_panel_cheats_create);
        }

        struct DjuiButton* button5 = djui_button_create(&body->base, "Resume");
        djui_base_set_size_type(&button5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button5->base, 1.0f, 64);
        djui_interactable_hook_click(&button5->base, djui_panel_pause_resume);

        if (gNetworkType == NT_SERVER) {
            struct DjuiButton* button6 = djui_button_create(&body->base, "Server Settings");
            djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button6->base, 1.0f, 64);
            djui_interactable_hook_click(&button6->base, djui_panel_host_create);
        }

        struct DjuiButton* button7;
        if (gNetworkType == NT_SERVER) {
            button7 = djui_button_create(&body->base, "Stop Hosting");
        } else {
            button7 = djui_button_create(&body->base, "Disconnect");
        }
        djui_base_set_size_type(&button7->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button7->base, 1.0f, 64);
        djui_interactable_hook_click(&button7->base, djui_panel_pause_quit);
        djui_button_set_style(button7, 1);
    }
    
    djui_panel_add(caller, &panel->base, defaultBase);
    gInteractableOverridePad = true;
    gDjuiPanelPauseCreated = true;
}
