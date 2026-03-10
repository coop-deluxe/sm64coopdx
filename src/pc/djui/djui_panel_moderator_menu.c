
#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_moderator_menu.h"
#include "djui_panel_moderator_menu_inspect.h"
#include "djui_panel_moderation_list.h"
#include "djui_panel_moderation_confirm_action.h"
#include "pc/network/network.h"
#include "pc/network/moderation.h"

static struct DjuiFlowLayout* sLayout = NULL;
static struct DjuiPaginated* sPaginated = NULL;

static void djui_panel_moderator_menu_action_button_click(struct DjuiBase* caller) {
    djui_panel_moderation_confirm_create(caller, caller->uTag, caller->tag, caller->bTag, djui_panel_moderator_menu_reload);
}

static void djui_panel_moderator_add_players(struct DjuiBase* layoutBase) {
    bool isPlayerConnected = false;
    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) continue;
        if (gNetworkPlayerLocal->moderator && np->moderator) continue;
        if (gNetworkPlayerLocal->moderator && np->globalIndex == 0) continue;

        isPlayerConnected = true;

        struct DjuiFlowLayout* flowLayout = djui_flow_layout_create(layoutBase);
        djui_flow_layout_set_flow_direction(flowLayout, DJUI_FLOW_DIR_RIGHT);
        djui_base_set_color(&flowLayout->base, 0, 0, 0, 0);
        djui_base_set_size_type(&flowLayout->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&flowLayout->base, 1, 32);
        {
            struct DjuiButton* playerButton = djui_button_create(&flowLayout->base, np->name, DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_inspector_create);
            u8 playerColor[3];
            memcpy(playerColor, network_get_player_text_color(i), 3);
            djui_base_set_color(&playerButton->text->base, playerColor[0], playerColor[1], playerColor[2], 255);
            djui_base_set_size_type(&playerButton->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&playerButton->base, 0.4, 32);
            playerButton->base.tag = i;

            struct DjuiButton* kickButton = djui_button_create(&flowLayout->base, DLANG(MODERATION, KICK), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_action_button_click);
            djui_base_set_size_type(&kickButton->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&kickButton->base, 0.333, 32);
            kickButton->base.uTag = MODERATION_ACTION_KICK;
            kickButton->base.tag = i;

            struct DjuiButton* banButton = djui_button_create(&flowLayout->base, DLANG(MODERATION, BAN), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_action_button_click);
            djui_base_set_size_type(&banButton->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&banButton->base, 0.5, 32);
            banButton->base.uTag = MODERATION_ACTION_BAN;
            banButton->base.tag = i;

            struct DjuiButton* modButton = djui_button_create(&flowLayout->base, np->moderator ? DLANG(MODERATION, UNMOD) : DLANG(MODERATION, MOD), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_action_button_click);
            djui_base_set_size_type(&modButton->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&modButton->base, 1.0, 32);
            djui_base_set_enabled(&modButton->base, gNetworkType == NT_SERVER);
            modButton->base.uTag = np->moderator ? MODERATION_ACTION_UNMOD : MODERATION_ACTION_MOD;
            modButton->base.bTag = true;
            modButton->base.tag = i;
        }
    }

    if (!isPlayerConnected) {
        struct DjuiText* text = djui_text_create(layoutBase, DLANG(MODERATION, NO_PLAYERS_CONNECTED));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, 1, 1);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    }
}

static void djui_panel_moderator_menu_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
    sLayout = NULL;
    sPaginated = NULL;
}

void djui_panel_moderator_menu_reload(UNUSED struct DjuiBase* caller) {
    if (!sLayout || !sPaginated) return;
    djui_base_destroy_children(&sLayout->base);
    djui_panel_moderator_add_players(&sLayout->base);
    djui_paginated_calculate_height(sPaginated);
}

void djui_panel_moderator_menu_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MODERATION, MODERATOR_MENU_TITLE), true);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        paginated->showMaxCount = true;
        sLayout = paginated->layout;
        djui_panel_moderator_add_players(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);
        sPaginated = paginated;

        if (gNetworkType == NT_SERVER) djui_button_create(body, DLANG(MODERATION, MODERATION_LISTS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderation_list_create);
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    panel->base.destroy = djui_panel_moderator_menu_destroy;
    djui_panel_add(caller, panel, NULL);
}