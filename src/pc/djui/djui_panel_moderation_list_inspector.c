#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_moderator_menu.h"
#include "djui_panel_moderation_list.h"
#include "djui_panel_moderation_confirm_action.h"
#include "djui_panel_confirm.h"
#include "pc/network/network.h"
#include "pc/network/moderation.h"
#include "pc/debuglog.h"

static u16 sListType = 0;
static u16 sListIndex = 0;

static void djui_panel_moderation_list_inspect_action_exit(UNUSED struct DjuiBase* caller) {
    djui_panel_back_by(2);
    djui_panel_moderation_list_reload();
}

static void djui_panel_moderation_list_action_button_click(struct DjuiBase* caller) {
    djui_panel_moderation_confirm_create_using_list(caller, caller->tag, sListType, sListIndex, djui_panel_moderation_list_inspect_action_exit);
}

static void djui_panel_moderation_list_inspect_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
}

void djui_panel_moderation_list_inspect_create(struct DjuiBase* caller) {
    struct ModerationList* list = moderation_list_get_list_by_type(caller->tag);
    if (!list) return;
    struct ModerationEntry* entry = list->list[caller->uTag];
    if (!entry) return;
    struct tm* localTime = localtime(&entry->time);

    sListType = caller->tag;
    sListIndex = caller->uTag;

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MODERATION, INSPECTOR), true);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        char playerName[MAX_CONFIG_STRING + 128];
        snprintf(playerName, MAX_CONFIG_STRING + 128, "%s \\#fff982\\- \\#82f9ff\\%s", entry->playerName, entry->address);
        struct DjuiText* playerText = djui_text_create(body, playerName);
        djui_base_set_color(&playerText->base, entry->playerColor[0], entry->playerColor[1], entry->playerColor[2], 255);
        djui_base_set_size_type(&playerText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&playerText->base, 1, 32);
        djui_text_set_alignment(playerText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        djui_text_set_drop_shadow(playerText, 64, 64, 64, 100);

        char date[128];
        strftime(date, sizeof(date), "%m/%d/%Y %I:%M:%S %p", localTime);
        char dateStr[256];
        djui_language_replace(DLANG(MODERATION, DATE), dateStr, 256, '@', date);
        struct DjuiText* dateText = djui_text_create(body, dateStr);
        djui_base_set_color(&dateText->base, 220, 220, 220, 255);
        djui_base_set_size_type(&dateText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&dateText->base, 1, 32);
        djui_text_set_alignment(dateText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
        djui_text_set_drop_shadow(dateText, 64, 64, 64, 100);

        if (entry->discordId && strcmp(entry->discordId, "") != 0 && strcmp(entry->discordId, "0") != 0) {
            char discordIdStr[128];
            djui_language_replace(DLANG(MODERATION, DISCORD_ID), discordIdStr, 128, '@', entry->discordId);
            struct DjuiText* discordIdText = djui_text_create(body, discordIdStr);
            djui_base_set_color(&discordIdText->base, 220, 220, 220, 255);
            djui_base_set_size_type(&discordIdText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&discordIdText->base, 1, 32);
            djui_text_set_alignment(discordIdText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(discordIdText, 64, 64, 64, 100);
        }

        if (entry->reason[0] != '\0') {
            int reasonStrLen = MAX_REASON_LENGTH + strlen(DLANG(MODERATION, REASON_INFO)) + 1;
            char reasonStr[reasonStrLen];
            djui_language_replace(DLANG(MODERATION, REASON_INFO), reasonStr, reasonStrLen, '@', entry->reason);
            struct DjuiText* reasonText = djui_text_create(body, reasonStr);
            djui_base_set_color(&reasonText->base, 220, 220, 220, 255);
            djui_base_set_size_type(&reasonText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&reasonText->base, 1, 32);
            djui_base_compute_tree(&reasonText->base);
            u16 reasonLines = djui_text_count_lines(reasonText, 12);
            f32 reasonHeight = 32 * reasonLines;
            djui_base_set_size(&reasonText->base, 1, reasonHeight);
            djui_text_set_alignment(reasonText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(reasonText, 64, 64, 64, 100);
        }

        djui_checkbox_create(body, DLANG(MODERATION, PERMANENT), &entry->permanent, moderation_list_save);

        for (u8 i = 0; i < MODERATION_ACTION_COUNT; i++) {
            if (!list->actions[i]) continue;
            switch (i) {
                case MODERATION_ACTION_UNBAN: {
                    struct DjuiButton* button = djui_button_create(body, DLANG(MODERATION, UNBAN), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderation_list_action_button_click);
                    button->base.tag = MODERATION_ACTION_UNBAN;
                    break;
                }
                case MODERATION_ACTION_UNMOD: {
                    struct DjuiButton* button = djui_button_create(body, DLANG(MODERATION, UNMOD), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderation_list_action_button_click);
                    button->base.tag = MODERATION_ACTION_UNMOD;
                    break;
                }
                default:
                    break;
            }
        }
    }

    djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

    panel->base.destroy = djui_panel_moderation_list_inspect_destroy;
    djui_panel_add(caller, panel, NULL);
}