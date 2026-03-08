
#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_moderator_menu.h"
#include "djui_panel_moderation_list.h"
#include "djui_panel_moderation_list_inspector.h"
#include "pc/network/network.h"
#include "pc/network/moderation.h"

static struct DjuiFlowLayout* sLayout = NULL;
static struct DjuiPaginated* sPaginated = NULL;
static unsigned int sSelectedList = MODERATION_LIST_TYPE_BAN;

static void djui_panel_moderation_list_inspect_player(struct DjuiBase* caller) {
    djui_panel_moderation_list_inspect_create(caller);
}

static void djui_panel_moderation_list_populate_list(struct DjuiBase* layoutBase) {
    struct ModerationList* list = moderation_list_get_list_by_type(sSelectedList);
    if (list->count == 0) {
        struct DjuiText* text = djui_text_create(layoutBase, DLANG(MODERATION, NO_PLAYERS_IN_LIST));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, 1, 1);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        return;
    }
    for (int i = 0; i < list->count; i++) {
        struct ModerationEntry* entry = list->list[i];
        struct DjuiRect* rectContainer = djui_rect_container_create(layoutBase, 32);
        {
            struct DjuiText* text = djui_text_create(&rectContainer->base, entry->playerName);
            djui_text_set_alignment(text, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text, 64, 64, 64, 100);
            djui_base_set_color(&text->base, entry->playerColor[0], entry->playerColor[1], entry->playerColor[2], 255);
            djui_base_set_alignment(&text->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 0.5, 32);

            struct DjuiButton* button = djui_button_create(&rectContainer->base, DLANG(MODERATION, INSPECT), DJUI_BUTTON_STYLE_NORMAL, djui_panel_moderation_list_inspect_player);
            djui_base_set_alignment(&button->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_base_set_size_type(&button->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button->base, 0.45, 32);
            button->base.tag = sSelectedList;
            button->base.uTag = i;
        }
    }
}

void djui_panel_moderation_list_reload() {
    if (!sLayout || !sPaginated) return;
    djui_base_destroy_children(&sLayout->base);
    djui_panel_moderation_list_populate_list(&sLayout->base);
    djui_paginated_calculate_height(sPaginated);
}

static void djui_panel_moderation_list_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
    sLayout = NULL;
    sPaginated = NULL;
}

static bool djui_panel_moderation_list_on_back(UNUSED struct DjuiBase* base) {
    if (!gDjuiInMainMenu) {
        djui_panel_moderator_menu_reload();
    }
    return false;
}

void djui_panel_moderation_list_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MODERATION, MODERATION_LISTS_TITLE), true);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        char* choices[MODERATION_LIST_TYPE_COUNT] = {
            DLANG(MODERATION, BAN_LIST),
            DLANG(MODERATION, MODERATOR_LIST),
        };
        djui_selectionbox_create(body, DLANG(MODERATION, LIST), choices, MODERATION_LIST_TYPE_COUNT, &sSelectedList, djui_panel_moderation_list_reload);

        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        paginated->showMaxCount = true;
        sLayout = paginated->layout;
        djui_panel_moderation_list_populate_list(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);
        sPaginated = paginated;

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    panel->on_back = djui_panel_moderation_list_on_back;
    panel->base.destroy = djui_panel_moderation_list_destroy;
    djui_panel_add(caller, panel, NULL);
}