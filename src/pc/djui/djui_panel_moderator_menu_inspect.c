
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

struct DjuiButton* sModButton = NULL;
static u8 sSelectedIndex = 0;

static void djui_panel_moderator_inspector_validate_and_reload();

static void djui_panel_moderator_menu_action_button_click(struct DjuiBase* caller) {
    djui_panel_moderation_confirm_create(caller, caller->uTag, caller->tag, caller->bTag, djui_panel_moderator_inspector_validate_and_reload);
}

static void djui_panel_moderator_menu_inspector_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
    sModButton = NULL;
}

static void djui_panel_moderator_inspector_validate_and_reload() {
    djui_panel_moderator_menu_reload();
    if (sSelectedIndex >= MAX_PLAYERS) djui_panel_back_by(2);
    struct NetworkPlayer* np = &gNetworkPlayers[sSelectedIndex];
    if (!np->connected) djui_panel_back_by(2);
    djui_panel_moderator_inspector_reload();
}

void djui_panel_moderator_inspector_reload() {
    if (!sModButton) return;
    if (sSelectedIndex >= MAX_PLAYERS) return;
    struct NetworkPlayer* np = &gNetworkPlayers[sSelectedIndex];

    djui_text_set_text(sModButton->text, np->moderator ? DLANG(MODERATION, UNMOD) : DLANG(MODERATION, MOD));
    sModButton->base.uTag = np->moderator ? MODERATION_ACTION_UNMOD : MODERATION_ACTION_MOD;
}

void djui_panel_moderator_menu_inspector_create(struct DjuiBase* caller) {
    if (caller->tag <= 0 || caller->tag >= MAX_PLAYERS) return;
    struct NetworkPlayer* np = &gNetworkPlayers[caller->tag];
    if (!np->connected) return;
    sSelectedIndex = caller->tag;
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MODERATION, MODERATOR_MENU_TITLE), true);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        char playerName[MAX_CONFIG_STRING + 128];
        snprintf(playerName, MAX_CONFIG_STRING + 128, "%s \\#fff982\\- \\#82f9ff\\%s \\#fff982\\- \\#82f9ff\\%u", network_get_complete_player_name(np->localIndex), gNetworkSystem->get_id_str(np->localIndex), np->localIndex);
        struct DjuiText* playerText = djui_text_create(body, playerName);
        djui_base_set_size_type(&playerText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&playerText->base, 1, 32);
        djui_text_set_alignment(playerText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        djui_text_set_drop_shadow(playerText, 64, 64, 64, 100);

        struct DjuiButton* kickButton = djui_button_create(body, DLANG(MODERATION, KICK), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_action_button_click);
        kickButton->base.uTag = MODERATION_ACTION_KICK;
        kickButton->base.tag = np->localIndex;

        struct DjuiButton* banButton = djui_button_create(body, DLANG(MODERATION, BAN), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_action_button_click);
        banButton->base.uTag = MODERATION_ACTION_BAN;
        banButton->base.tag = np->localIndex;

        sModButton = djui_button_create(body, np->moderator ? DLANG(MODERATION, UNMOD) : DLANG(MODERATION, MOD), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderator_menu_action_button_click);
        sModButton->base.uTag = np->moderator ? MODERATION_ACTION_UNMOD : MODERATION_ACTION_MOD;
        sModButton->base.bTag = true;
        sModButton->base.tag = np->localIndex;

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    panel->base.destroy = djui_panel_moderator_menu_inspector_destroy;
    djui_panel_add(caller, panel, NULL);
}