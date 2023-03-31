#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/cheats.h"

#ifdef DISCORD_SDK
#define DJUI_HOST_NS_IS_SOCKET (configNetworkSystem == 1)
#else
#define DJUI_HOST_NS_IS_SOCKET (true)
#endif

struct DjuiInputbox* sInputboxPort = NULL;

static void djui_panel_host_network_system_change(UNUSED struct DjuiBase* base) {
    djui_base_set_enabled(&sInputboxPort->base, DJUI_HOST_NS_IS_SOCKET);
}

static bool djui_panel_host_port_valid(void) {
    char* buffer = sInputboxPort->buffer;
    int port = 0;
    while (*buffer != '\0') {
        if (*buffer < '0' || *buffer > '9') { return false; }
        port *= 10;
        port += (*buffer - '0');
        buffer++;
    }
#if __linux__
    return port >= 1024 && port <= 65535;
#else
    return port <= 65535;
#endif
}

static void djui_panel_host_port_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (djui_panel_host_port_valid()) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_host_do_host(struct DjuiBase* caller) {
    if (!djui_panel_host_port_valid()) {
        djui_interactable_set_input_focus(&sInputboxPort->base);
        djui_inputbox_select_all(sInputboxPort);
        return;
    }
    
    // Doesn't let you host if the player limit is not good
    if (configAmountofPlayers < 2 || configAmountofPlayers > MAX_PLAYERS) {
        return;
    }
    
    configHostPort = atoi(sInputboxPort->buffer);

    if (gNetworkType == NT_SERVER) {
        network_rehost_begin();
    } else {
        djui_panel_host_message_create(caller);
    }
}

void djui_panel_host_create(struct DjuiBase* caller) {
    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create((gNetworkType == NT_SERVER)
            ? "\\#ff0800\\S\\#1be700\\E\\#00b3ff\\R\\#ffef00\\V\\#ff0800\\E\\#1be700\\R"
            : "\\#ff0800\\H\\#1be700\\O\\#00b3ff\\S\\#ffef00\\T");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
#ifdef DISCORD_SDK
        char* nChoices[2] = { "Discord", "Direct Connection" };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Network system", nChoices, 2, &configNetworkSystem, djui_panel_host_network_system_change);
        if (gNetworkType == NT_SERVER) {
            djui_base_set_enabled(&selectionbox1->base, false);
        }

#endif

        struct DjuiRect* rect1 = djui_rect_container_create(&body->base, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Port");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            if (gNetworkType == NT_SERVER) {
                djui_base_set_enabled(&text1->base, false);
            }

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.5f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char portString[32] = { 0 };
            snprintf(portString, 32, "%d", configHostPort);
            djui_inputbox_set_text(inputbox1, portString);
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_host_port_text_change);
            if (gNetworkType == NT_SERVER) {
                djui_base_set_enabled(&inputbox1->base, false);
#ifdef DISCORD_SDK
            } else {
                djui_base_set_enabled(&inputbox1->base, DJUI_HOST_NS_IS_SOCKET);
#endif
            }
            sInputboxPort = inputbox1;
        }
        
        struct DjuiRect* rect2 = djui_rect_container_create(&body->base, 32);
        {
            struct DjuiText* text1 = djui_text_create(&rect2->base, "Save Slot");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            char starString[32] = { 0 };
            snprintf(starString, 32, "%c x%d", '~' + 1, save_file_get_total_star_count(configHostSaveSlot - 1, 0, 24));
            struct DjuiButton* button1 = djui_button_create(&rect2->base, starString, DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_save_create);
            djui_base_set_size(&button1->base, 0.5f, 32);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
        }

        djui_button_create(&body->base, "Settings", DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_settings_create);

        struct DjuiButton* button2 = djui_button_create(&body->base, "Mods", DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_mods_create);
        button2->base.tag = 0;

        struct DjuiButton* button3 = djui_button_create(&body->base, "Rom-Hacks", DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_mods_create);
        button3->base.tag = 1;

        struct DjuiRect* rect3 = djui_rect_container_create(&body->base, 64);
        {
            struct DjuiButton* button1 = djui_button_create(&rect3->base, (gNetworkType == NT_SERVER) ? "Cancel" : "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiButton* button2 = djui_button_create(&rect3->base, (gNetworkType == NT_SERVER) ? "Apply" : "Host", DJUI_BUTTON_STYLE_NORMAL, djui_panel_host_do_host);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);

            defaultBase = (gNetworkType == NT_SERVER)
                        ? &button1->base
                        : &button2->base;
        }
    }

    djui_panel_add(caller, panel, defaultBase);
}
