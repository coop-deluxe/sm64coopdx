#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_confirm.h"
#include "djui_panel_moderation_list.h"
#include "pc/network/network.h"
#include "pc/network/moderation.h"

static char* sReason = NULL;
static bool sPermanent = false;
void (*sOnYesClick)(struct DjuiBase*) = NULL;

static void djui_panel_moderation_call_action(struct DjuiBase* caller) {
    u8 player = caller->tag;
    u8 action = caller->uTag;
    char* address = caller->cTag;

    switch(action) {
        case MODERATION_ACTION_KICK:
            network_kick_player(player, sReason);
            break;
        case MODERATION_ACTION_BAN:
            network_ban_player(player, sReason, sPermanent);
            break;
        case MODERATION_ACTION_UNBAN:
            network_unban_player(address);
            break;
        case MODERATION_ACTION_MOD:
            network_mod_player(player, sReason, sPermanent);
            break;
        case MODERATION_ACTION_UNMOD:
            network_unmod_player(address);
            break;
        default:
            break;
    }

    free(sReason);
    sReason = NULL;
    sPermanent = false;
    djui_panel_menu_back(caller);

    if (sOnYesClick) sOnYesClick(caller);
}

static void djui_panel_moderation_confirm_reason_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox = (struct DjuiInputbox*)caller;
    if (inputbox) {
        sReason = strdup(inputbox->buffer);
    }
}

static void djui_panel_moderation_confirm_set_title_and_message(u8 action, char** title, char* message, char* playerName) {
    switch (action) {
        case MODERATION_ACTION_KICK:
            *title = djui_language_get("MODERATION", "KICK_PLAYER_TITLE");
            djui_language_replace(DLANG(MODERATION, KICK_CONFIRM), message, 256, '@', playerName);
            break;
        case MODERATION_ACTION_BAN:
            *title = djui_language_get("MODERATION", "BAN_PLAYER_TITLE");
            djui_language_replace(DLANG(MODERATION, BAN_CONFIRM), message, 256, '@', playerName);
            break;
        case MODERATION_ACTION_UNBAN:
            *title = djui_language_get("MODERATION", "UNBAN_PLAYER_TITLE");
            djui_language_replace(DLANG(MODERATION, UNBAN_CONFIRM), message, 256, '@', playerName);
            break;
        case MODERATION_ACTION_MOD:
            *title = djui_language_get("MODERATION", "MOD_PLAYER_TITLE");
            djui_language_replace(DLANG(MODERATION, MOD_CONFIRM), message, 256, '@', playerName);
            break;
        case MODERATION_ACTION_UNMOD:
            *title = djui_language_get("MODERATION", "UNMOD_PLAYER_TITLE");
            djui_language_replace(DLANG(MODERATION, UNMOD_CONFIRM), message, 256, '@', playerName);
            break;
        default:
            return;
    }
}

static void djui_panel_moderation_confirm_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
    free(sReason);
    sReason = NULL;
    sPermanent = false;
    sOnYesClick = NULL;
}

void djui_panel_moderation_confirm_create_body(struct DjuiBase* caller, char* title, char* message, u8 localIndex, u8 action, bool permanent, char* address, void (*on_yes_click)(struct DjuiBase*)) {
    sPermanent = permanent;

    struct DjuiThreePanel* panel = djui_panel_menu_create(title, false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        struct DjuiText* text = djui_text_create(body, message);
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);

        if (action == MODERATION_ACTION_KICK || action == MODERATION_ACTION_BAN || action == MODERATION_ACTION_MOD) {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
            {
                struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(MODERATION, REASON));
                djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_color(&text1->base, 220, 220, 220, 255);
                djui_base_set_size(&text1->base, 0.4f, 64);
                djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
                djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

                struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 256);
                djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
                djui_base_set_size(&inputbox1->base, 0.75, 32);
                djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
                djui_interactable_hook_value_change(&inputbox1->base, djui_panel_moderation_confirm_reason_text_change);
            }

            if (action != MODERATION_ACTION_KICK) djui_checkbox_create(body, DLANG(MODERATION, PERMANENT), &sPermanent, NULL);
        }

        djui_base_set_size(&text->base, 1.0f, 64);
        djui_base_compute_tree(&text->base);
        u16 lines = djui_text_count_lines(text, 12);
        f32 textHeight = 32 * 0.8125f * lines + 8;
        djui_base_set_size(&text->base, 1.0f, textHeight);

        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

        struct DjuiRect* rect2 = djui_rect_container_create(body, 64);
        {
            djui_button_left_create(&rect2->base, DLANG(MENU, NO), DJUI_BUTTON_STYLE_NORMAL, djui_panel_menu_back);
            struct DjuiButton* yesButton = djui_button_right_create(&rect2->base, DLANG(MENU, YES), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderation_call_action);
            yesButton->base.tag = localIndex;
            yesButton->base.uTag = action;
            yesButton->base.cTag = strdup(address);
            sOnYesClick = on_yes_click;
        }
    }

    panel->base.destroy = djui_panel_moderation_confirm_destroy;
    djui_panel_add(caller, panel, NULL);
}

void djui_panel_moderation_confirm_create(struct DjuiBase* caller, u8 action, u8 localIndex, bool permanent, void (*on_yes_click)(struct DjuiBase*)) {
    if (localIndex >= MAX_PLAYERS) return;
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (!np->connected) return;
    char* title = NULL;
    char message[256] = { 0 };
    djui_panel_moderation_confirm_set_title_and_message(action, &title, message, (char*)network_get_complete_player_name(localIndex));
    djui_panel_moderation_confirm_create_body(caller, title, message, localIndex, action, permanent, gNetworkSystem->get_id_str(localIndex), on_yes_click);
}

void djui_panel_moderation_confirm_create_using_list(struct DjuiBase* caller, u8 action, u8 listType, u16 listIndex, void (*on_yes_click)(struct DjuiBase*)) {
    struct ModerationEntry* entry = moderation_list_get_list_by_type(listType)->list[listIndex];
    char* title = NULL;
    char message[256] = { 0 };
    char colorString[10] = { 0 };
    snprintf(colorString, 10, "\\#%02x%02x%02x\\", entry->playerColor[0], entry->playerColor[1], entry->playerColor[2]);
    char playerName[256] = { 0 };
    snprintf(playerName, 256, "%s%s", colorString, entry->playerName);
    djui_panel_moderation_confirm_set_title_and_message(action, &title, message, playerName);
    djui_panel_moderation_confirm_create_body(caller, title, message, 0, action, false, entry->address, on_yes_click);
}