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

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\P\\#1be700\\A\\#00b3ff\\U\\#ffef00\\S\\#ff0800\\E");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        
        struct DjuiRect* rect1 = djui_rect_container_create(&body->base, 64);
        {
            djui_button_left_create(&rect1->base, "Player", DJUI_BUTTON_STYLE_NORMAL, djui_panel_player_create);
            djui_button_right_create(&rect1->base, "DynOS Packs", DJUI_BUTTON_STYLE_NORMAL, djui_panel_dynos_create);
        }

        struct DjuiButton* button3 = djui_button_create(&body->base, "Options", DJUI_BUTTON_STYLE_NORMAL, djui_panel_options_create);
        defaultBase = &button3->base;

        if (gServerSettings.enableCheats) {
            djui_button_create(&body->base, "Cheats", DJUI_BUTTON_STYLE_NORMAL, djui_panel_cheats_create);
        }

        if (gNetworkType == NT_SERVER) {
            djui_button_create(&body->base, "Server Settings", DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_create);
        }

        djui_button_create(&body->base, "Resume", DJUI_BUTTON_STYLE_NORMAL, djui_panel_pause_resume);

        if (gNetworkType == NT_SERVER) {
            djui_button_create(&body->base, "Stop Hosting", DJUI_BUTTON_STYLE_BACK, djui_panel_pause_quit);
        } else {
            djui_button_create(&body->base, "Disconnect", DJUI_BUTTON_STYLE_BACK, djui_panel_pause_quit);
        }
    }
    
    djui_panel_add(caller, panel, defaultBase);
    gInteractableOverridePad = true;
    gDjuiPanelPauseCreated = true;
}
