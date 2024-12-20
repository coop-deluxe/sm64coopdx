#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_join_message.h"
#include "djui_lobby_entry.h"
#include "djui_panel_rules.h"
#include "pc/network/network.h"
#include "pc/network/socket/socket.h"
#include "pc/network/coopnet/coopnet.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"
#include "macros.h"

#ifdef COOPNET

#define DJUI_DESC_PANEL_WIDTH (410.0f + (16 * 2.0f))

static struct DjuiPaginated* sLobbyPaginated = NULL;
static struct DjuiFlowLayout* sLobbyLayout = NULL;
static struct DjuiButton* sRefreshButton = NULL;
static struct DjuiThreePanel* sDescriptionPanel = NULL;
static struct DjuiText* sTooltip = NULL;
static char* sPassword = NULL;

static void djui_panel_join_lobby_description_create(void) {
    f32 bodyHeight = 600;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    struct DjuiThreePanelTheme theme = gDjuiThemes[configDjuiTheme]->threePanels;

    djui_base_set_alignment(&panel->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_DESC_PANEL_WIDTH, 1.0f);
    djui_base_set_color(&panel->base, theme.rectColor.r, theme.rectColor.g, theme.rectColor.b, theme.rectColor.a);
    djui_base_set_border_color(&panel->base, theme.borderColor.r, theme.borderColor.g, theme.borderColor.b, theme.borderColor.a);
    djui_base_set_border_width(&panel->base, 8);
    djui_base_set_padding(&panel->base, 16, 16, 16, 16);
    {
        struct DjuiFlowLayout* body = djui_flow_layout_create(&panel->base);
        djui_base_set_alignment(&body->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&body->base, 1.0f, 1.0f);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);

        struct DjuiText* description = djui_text_create(&panel->base, "");
        djui_base_set_size_type(&description->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&description->base, 1.0f, 1.0f);
        djui_base_set_color(&description->base, 222, 222, 222, 255);
        djui_text_set_alignment(description, DJUI_HALIGN_LEFT, DJUI_VALIGN_CENTER);
        sTooltip = description;
    }
    sDescriptionPanel = panel;
}

static void djui_lobby_on_hover(struct DjuiBase* base) {
    struct DjuiLobbyEntry* entry = (struct DjuiLobbyEntry*)base;
    djui_text_set_text(sTooltip, entry->description);
}

static void djui_lobby_on_hover_end(UNUSED struct DjuiBase* base) {
    djui_text_set_text(sTooltip, "");
}

void djui_panel_join_lobby(struct DjuiBase* caller) {
    gCoopNetDesiredLobby = (uint64_t)caller->tag;
    snprintf(gCoopNetPassword, 64, "%s", sPassword);
    network_reset_reconnect_and_rehost();
    network_set_system(NS_COOPNET);
    network_init(NT_CLIENT, false);
    djui_panel_join_message_create(caller);
}

void djui_panel_join_query(uint64_t aLobbyId, UNUSED uint64_t aOwnerId, uint16_t aConnections, uint16_t aMaxConnections, UNUSED const char* aGame, const char* aVersion, const char* aHostName, const char* aMode, const char* aDescription) {
    if (!sLobbyLayout) { return; }
    if (!sLobbyPaginated) { return; }
    if (aMaxConnections > MAX_PLAYERS) { return; }

    char playerText[64] = "";
    snprintf(playerText, 63, "%u/%u", aConnections, aMaxConnections);


    char mode[64] = "";
    snprintf(mode, 64, "%s", aMode);

    char version[MAX_VERSION_LENGTH] = { 0 };
    snprintf(version, MAX_VERSION_LENGTH, "%s", get_version());
    bool disabled = strcmp(version, aVersion) != 0;
    if (disabled) {
        snprintf(mode, 64, "\\#ff0000\\[%s]", aVersion);
    }

    struct DjuiBase* layoutBase = &sLobbyLayout->base;
    struct DjuiLobbyEntry* entry = djui_lobby_entry_create(layoutBase, (char*)aHostName, (char*)mode, playerText, (char*)aDescription, disabled, djui_panel_join_lobby, djui_lobby_on_hover, djui_lobby_on_hover_end);
    entry->base.tag = (s64)aLobbyId;
    djui_paginated_update_page_buttons(sLobbyPaginated);
}

void djui_panel_join_query_finish(void) {
    if (!sLobbyLayout) { return; }
    if (!sLobbyPaginated) { return; }
    if (!sRefreshButton) { return; }
    djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESH));
    djui_base_set_enabled(&sRefreshButton->base, true);

    if (sLobbyLayout->base.child == NULL) {
        struct DjuiText* text = djui_text_create(&sLobbyLayout->base, DLANG(LOBBIES, NO_LOBBIES_FOUND));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, 1, 1);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    }
    djui_paginated_update_page_buttons(sLobbyPaginated);
}

void djui_panel_join_lobbies_on_destroy(UNUSED struct DjuiBase* caller) {
    if (sPassword) { free(sPassword); }
    sPassword = NULL;
    sRefreshButton = NULL;
    sLobbyLayout = NULL;
    sLobbyPaginated = NULL;

    if (sDescriptionPanel != NULL) {
        djui_base_destroy(&sDescriptionPanel->base);
        sDescriptionPanel = NULL;
    }
}

void djui_panel_join_lobbies_refresh(UNUSED struct DjuiBase* caller) {
    djui_base_destroy_children(&sLobbyLayout->base);
    djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESHING));
    djui_base_set_enabled(&sRefreshButton->base, false);
    djui_paginated_update_page_buttons(sLobbyPaginated);
    ns_coopnet_query(djui_panel_join_query, djui_panel_join_query_finish, sPassword);
}

void djui_panel_join_lobbies_value_changed(UNUSED struct DjuiBase* caller) {
    djui_panel_join_lobbies_refresh(NULL);
}

void djui_panel_join_lobbies_create(struct DjuiBase* caller, const char* password) {
    if (sPassword) { free(sPassword); sPassword = NULL; }
    sPassword = strdup(password);
    bool private = (strlen(password) > 0);
    if (!private && configRulesVersion != RULES_VERSION) {
        djui_panel_rules_create(caller);
        return;
    }

    djui_panel_join_lobby_description_create();

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(
        private ? DLANG(LOBBIES, PRIVATE_LOBBIES) : DLANG(LOBBIES, PUBLIC_LOBBIES),
        true);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        sLobbyPaginated = djui_paginated_create(body, 10);
        sLobbyLayout = sLobbyPaginated->layout;
        djui_flow_layout_set_margin(sLobbyLayout, 4);

        bool querying = ns_coopnet_query(djui_panel_join_query, djui_panel_join_query_finish, password);
        if (!querying) {
            struct DjuiText* text = djui_text_create(&sLobbyLayout->base, DLANG(NOTIF, COOPNET_CONNECTION_FAILED));
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
            djui_base_set_size(&text->base, 1, 1);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        }

        if (!private) { djui_button_create(body, DLANG(RULES, RULES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_rules_create); }

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
    if (!p) { return; }
    p->on_panel_destroy = djui_panel_join_lobbies_on_destroy;
}

#endif