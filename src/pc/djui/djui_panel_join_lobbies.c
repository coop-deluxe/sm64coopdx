#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_join_message.h"
#include "djui_lobby_entry.h"
#include "src/pc/network/network.h"
#include "src/pc/network/socket/socket.h"
#include "src/pc/network/coopnet/coopnet.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/pc/debuglog.h"
#include "macros.h"

#ifdef COOPNET

static struct DjuiFlowLayout* sLobbyLayout = NULL;

void djui_panel_join_lobby(struct DjuiBase* caller) {
    gCoopNetDesiredLobby = (uint64_t)caller->tag;
    network_reset_reconnect_and_rehost();
    network_set_system(NS_COOPNET);
    network_init(NT_CLIENT);
    djui_panel_join_message_create(caller);
}

void djui_panel_join_query(uint64_t aLobbyId, UNUSED uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, UNUSED const char* aGame, UNUSED const char* aVersion, const char* aHostName, const char* aMode) {
    char playerText[64];
    snprintf(playerText, 63, "%u/%u", aConnections, aMaxConnections);

    struct DjuiBase* layoutBase = &sLobbyLayout->base;
    struct DjuiLobbyEntry* entry = djui_lobby_entry_create(layoutBase, (char*)aHostName, (char*)aMode, playerText, djui_panel_join_lobby);
    entry->base.tag = (s64)aLobbyId;
}

void djui_panel_join_lobbies_create(struct DjuiBase* caller, const char* password) {

    bool private = (strlen(password) > 0);
    ns_coopnet_query(djui_panel_join_query, password);

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(private ? DLANG(LOBBIES, PRIVATE_LOBBIES) : DLANG(LOBBIES, PUBLIC_LOBBIES));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {

        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        sLobbyLayout = paginated->layout;
        djui_flow_layout_set_margin(sLobbyLayout, 4);

        #if 0
        struct DjuiBase* layoutBase = &sLobbyLayout->base;
        for (int i = 0; i < 1; i++) {
            djui_lobby_entry_create(layoutBase, "MysterD", "Super Mario 64", "15/16", NULL);
            djui_lobby_entry_create(layoutBase, "djoslin0", "Star Road", "1/16", NULL);
            djui_lobby_entry_create(layoutBase, "abcdefghijklmnopqrs", "Snowstorm Avalanche", "16/16", NULL);
            djui_lobby_entry_create(layoutBase, "Prince Frizzy", "Hide and Seek", "4/16", NULL);
            djui_lobby_entry_create(layoutBase, "Sunk", "Super Mario 74 (+EE)", "5/8", NULL);
        }
        djui_paginated_calculate_height(paginated);
        #endif

        struct DjuiRect* rect2 = djui_rect_container_create(body, 64);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiButton* button2 = djui_button_create(&rect2->base, DLANG(LOBBIES, REFRESH), DJUI_BUTTON_STYLE_NORMAL, NULL);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            defaultBase = &button2->base;
        }
    }

    djui_panel_add(caller, panel, defaultBase);
}

#endif