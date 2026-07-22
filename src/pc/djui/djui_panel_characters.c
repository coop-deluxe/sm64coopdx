#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_unicode.h"
#include "djui_panel_main.h"
#include "djui_panel_pause.h"
#include "djui_panel_options.h"
#include "pc/network/network_player.h"
#include "pc/platform.h"
#include "pc/utils/misc.h"
#include "game/level_update.h"
#include "game/area.h"

static struct DjuiFlowLayout *sLayout = NULL;
static struct DjuiPaginated *sPaginated = NULL;
static struct DjuiInputbox *sSearchInputbox = NULL;
static struct DjuiCheckbox *sCheckboxes[MAX_CHARACTERS] = { 0 };
static unsigned int sCheckboxesCount = 0;

static void djui_panel_characters_value_changed(struct DjuiBase *caller) {
    configPlayerModel = caller->tag;
    if (configPlayerModel >= MAX_CHARACTERS) { configPlayerModel = CT_MARIO; }
    if (gNetworkPlayers[0].overrideModelIndex == gNetworkPlayers[0].modelIndex) { gNetworkPlayers[0].overrideModelIndex = configPlayerModel; }

    gNetworkPlayers[0].modelIndex = configPlayerModel;
    network_player_update_model(0);

    if (gNetworkType != NT_NONE) {
        network_send_player_settings();
    }

    // iterate through all checkboxes and set them to false UNLESS it is the caller
    for (unsigned int i = 0; i < sCheckboxesCount; i++) {
        if (!sCheckboxes[i]) { continue; }
        sCheckboxes[i]->base.bTag = (&sCheckboxes[i]->base == caller);
        djui_checkbox_update_style(&sCheckboxes[i]->base);
    }
}

static void djui_panel_characters_add_characters(struct DjuiBase *base) {
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (gCharacters[i].type == CT_UNALLOCATED) { continue; }
        bool tmp = (gMarioState->character == &gCharacters[i]);
        // filter results
        if (sSearchInputbox != NULL &&
            sSearchInputbox->buffer != NULL &&
            !strstr_lowercased(djui_text_get_uncolored_string(NULL, strlen(gCharacters[i].name) + 1, gCharacters[i].name), sSearchInputbox->buffer)
        ) {
            continue;
        }

        struct DjuiCheckbox *checkbox1 = djui_checkbox_create(base, gCharacters[i].name, &tmp, djui_panel_characters_value_changed);
        checkbox1->base.tag = i;
        checkbox1->base.bTag = tmp;
        checkbox1->value = &checkbox1->base.bTag;
        sCheckboxes[sCheckboxesCount++] = checkbox1;
    }
}

static void djui_panel_characters_refresh(UNUSED struct DjuiBase *caller) {
    memset(sCheckboxes, 0, sizeof(sCheckboxes));
    sCheckboxesCount = 0;
    djui_base_destroy_children(&sLayout->base);
    djui_panel_characters_add_characters(&sLayout->base);
    djui_paginated_calculate_height(sPaginated);
}

static void djui_panel_characters_destroy(struct DjuiBase *base) {
    struct DjuiThreePanel *threePanel = (struct DjuiThreePanel *)base;
    free(threePanel);

    sLayout = NULL;
    memset(sCheckboxes, 0, sizeof(sCheckboxes));
    sCheckboxesCount = 0;
}

void djui_panel_characters_create(struct DjuiBase *caller) {
    struct DjuiThreePanel *panel = djui_panel_menu_create(DLANG(CHARACTERS, CHARACTERS), true);

    struct DjuiBase *body = djui_three_panel_get_body(panel);
    {
        struct DjuiSearchbox *searchbox = djui_searchbox_create(body, djui_panel_characters_refresh);
        sSearchInputbox = searchbox->inputbox;

        struct DjuiPaginated *paginated = djui_paginated_create(body, 8);
        paginated->showMaxCount = true;
        sLayout = paginated->layout;
        djui_panel_characters_add_characters(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);
        sPaginated = paginated;

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
        djui_three_panel_recalculate_body_size(panel);
    }

    panel->base.destroy = djui_panel_characters_destroy;

    djui_panel_add(caller, panel, NULL);
}