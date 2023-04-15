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
static struct DjuiButton* sRefreshButton = NULL;
static char* sPassword = NULL;

void djui_panel_join_lobby(struct DjuiBase* caller) {
    gCoopNetDesiredLobby = (uint64_t)caller->tag;
    network_reset_reconnect_and_rehost();
    network_set_system(NS_COOPNET);
    network_init(NT_CLIENT, false);
    djui_panel_join_message_create(caller);
}

void djui_panel_join_query(uint64_t aLobbyId, UNUSED uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, UNUSED const char* aGame, UNUSED const char* aVersion, const char* aHostName, const char* aMode) {
    if (!sLobbyLayout) { return; }

    char playerText[64] = "";
    snprintf(playerText, 63, "%u/%u", aConnections, aMaxConnections);


    char mode[64] = "";
    snprintf(mode, 64, "%s", aMode);

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    if (strcmp(version, aVersion) != 0) {
        snprintf(mode, 64, "\\#ff0000\\[%s]", aVersion);
    }

    struct DjuiBase* layoutBase = &sLobbyLayout->base;
    struct DjuiLobbyEntry* entry = djui_lobby_entry_create(layoutBase, (char*)aHostName, (char*)mode, playerText, djui_panel_join_lobby);
    entry->base.tag = (s64)aLobbyId;
}

void djui_panel_join_query_finish(void) {
    if (!sRefreshButton) { return; }
    djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESH));
    djui_base_set_enabled(&sRefreshButton->base, true);

    if (sLobbyLayout->base.child == NULL) {
        struct DjuiText* text = djui_text_create(&sLobbyLayout->base, DLANG(LOBBIES, NONE_FOUND));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, 1, 1);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    }
}

void djui_panel_join_lobbies_on_destroy(UNUSED struct DjuiBase* caller) {
    if (sPassword) { free(sPassword); }
    sPassword = NULL;
    sRefreshButton = NULL;
    sLobbyLayout = NULL;
}

void djui_panel_join_lobbies_refresh(UNUSED struct DjuiBase* caller) {
    djui_base_destroy_children(&sLobbyLayout->base);
    djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESHING));
    djui_base_set_enabled(&sRefreshButton->base, false);
    ns_coopnet_query(djui_panel_join_query, djui_panel_join_query_finish, sPassword);
}

void djui_panel_join_lobbies_create(struct DjuiBase* caller, const char* password) {
    if (sPassword) { free(sPassword); sPassword = NULL; }
    sPassword = strdup(password);
    bool private = (strlen(password) > 0);
    bool querying = ns_coopnet_query(djui_panel_join_query, djui_panel_join_query_finish, password);

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
        if (!querying) {
            struct DjuiText* text = djui_text_create(&sLobbyLayout->base, DLANG(NOTIF, COOPNET_CONNECTION_FAILED));
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
            djui_base_set_size(&text->base, 1, 1);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        }

        struct DjuiRect* rect2 = djui_rect_container_create(body, 64);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            sRefreshButton = djui_button_create(&rect2->base, querying ? DLANG(LOBBIES, REFRESHING) : DLANG(LOBBIES, REFRESH), DJUI_BUTTON_STYLE_NORMAL, djui_panel_join_lobbies_refresh);
            djui_base_set_size(&sRefreshButton->base, 0.485f, 64);
            djui_base_set_alignment(&sRefreshButton->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_base_set_enabled(&sRefreshButton->base, false);
            defaultBase = &sRefreshButton->base;
        }
    }

    struct DjuiPanel* p = djui_panel_add(caller, panel, defaultBase);
    p->on_panel_destroy = djui_panel_join_lobbies_on_destroy;
}

#endif