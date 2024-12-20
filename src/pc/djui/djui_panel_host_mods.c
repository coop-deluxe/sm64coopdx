#include <stdio.h>
#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "djui_panel_main.h"
#include "djui_panel_host.h"
#include "djui_panel_host_mods.h"
#include "djui_panel_pause.h"
#include "pc/thread.h"

#define DJUI_MOD_PANEL_WIDTH (410.0f + (16 * 2.0f))
#define MOD_CATEGORY_ALL 0
#define MOD_CATEGORY_MISC 1
#define MOD_CATEGORY_START 2

static struct DjuiFlowLayout* sModLayout = NULL;
static struct DjuiThreePanel* sDescriptionPanel = NULL;
static struct DjuiText* sTooltip = NULL;
static struct DjuiPaginated* sModPaginated = NULL;
static struct DjuiButton* sBackButton = NULL;
static struct DjuiButton* sRefreshButton = NULL;
static unsigned int sSelectedCategory = MOD_CATEGORY_ALL;
static bool sWarned = false;

struct ThreadHandle gModRefreshThread = { 0 };

struct ModCategory sCategories[] = {
    // lang key, mod category
    { "ALL", NULL },
    { "MISC", NULL },
    { "ROMHACKS", "romhack" },
    { "GAMEMODES", "gamemode" },
    { "MOVESETS", "moveset" },
    { "CHARACTER_SELECT", "cs" },
};
static const int numCategories = sizeof(sCategories) / sizeof(sCategories[0]);

void djui_panel_host_mods_create(struct DjuiBase* caller);

static void djui_panel_host_mods_description_create(void) {
    f32 bodyHeight = 1000;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    struct DjuiThreePanelTheme theme = gDjuiThemes[configDjuiTheme]->threePanels;

    djui_base_set_alignment(&panel->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_MOD_PANEL_WIDTH, 1.0f);
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
        djui_text_set_drop_shadow(description, 64, 64, 64, 100);
        sTooltip = description;
    }
    sDescriptionPanel = panel;
}

static void djui_mod_checkbox_on_hover(struct DjuiBase* base) {
    char* description = "";
    if (base->tag >= 0 && base->tag < gLocalMods.entryCount) {
        struct Mod* mod = gLocalMods.entries[base->tag];
        char* d = mod->description;
        if (d != NULL) {
            description = mod->description;
        }
    }
    djui_text_set_text(sTooltip, description);
}

static void djui_mod_checkbox_on_hover_end(UNUSED struct DjuiBase* base) {
    djui_text_set_text(sTooltip, "");
}

static void djui_mod_checkbox_on_value_change(UNUSED struct DjuiBase* base) {
    mods_update_selectable();

    if (mods_get_enabled_count() - mods_get_character_select_count() >= 10) {
        if (!sWarned) {
            sWarned = true;
            djui_popup_create(DLANG(HOST_MODS, WARNING), 3);
        }
    } else {
        sWarned = false;
    }

    u16 index = 0;
    struct DjuiBaseChild* node = sModLayout->base.child;
    while (node != NULL) {
        index = node->base->tag;
        if (index >= gLocalMods.entryCount) { break; }
        struct Mod* mod = gLocalMods.entries[index];

        djui_base_set_enabled(node->base, mod->selectable);

        // iterate
        node = node->next;
    }
}

static void djui_panel_host_mods_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);

    if (sDescriptionPanel != NULL) {
        djui_base_destroy(&sDescriptionPanel->base);
        sDescriptionPanel = NULL;
    }
    sModLayout = NULL;
    sTooltip = NULL;
}

void djui_panel_host_mods_add_mods(struct DjuiBase* layoutBase) {
    bool foundAny = false;
    for (int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        char* category = mod->category != NULL ? mod->category : mod->incompatible;
        switch (sSelectedCategory) {
            case MOD_CATEGORY_ALL: { break; }
            case MOD_CATEGORY_MISC: {
                bool doContinue = false;
                if (category) {
                    for (int i = MOD_CATEGORY_START; i < numCategories; i++) {
                        if (strstr(category, sCategories[i].category)) {
                            doContinue = true;
                            break;
                        }
                    }
                }
                if (doContinue) { continue; }
                break;
            }
            default: {
                if (!category || !strstr(category, sCategories[sSelectedCategory].category)) {
                    continue;
                }
                break;
            }
        }
        struct DjuiCheckbox* checkbox = djui_checkbox_create(layoutBase, mod->name, &mod->enabled, djui_mod_checkbox_on_value_change);
        checkbox->base.tag = i;
        djui_base_set_enabled(&checkbox->base, mod->selectable);
        djui_interactable_hook_hover(&checkbox->base, djui_mod_checkbox_on_hover, djui_mod_checkbox_on_hover_end);
        foundAny = true;
    }
    if (!foundAny) {
        struct DjuiText* text = djui_text_create(layoutBase, DLANG(HOST_MODS, NO_MODS_FOUND));
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
        djui_base_set_size(&text->base, 1, 1);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
    }
}

static void djui_panel_on_categories_change(UNUSED struct DjuiBase* caller) {
    if (gModRefreshThread.state == RUNNING) { return; }
    djui_base_destroy_children(&sModLayout->base);
    djui_panel_host_mods_add_mods(&sModLayout->base);
    djui_paginated_calculate_height(sModPaginated);
}

static void* threaded_mod_refresh(void*) {
    mods_refresh_local();

    if (gModRefreshThread.state == RUNNING) { join_thread(&gModRefreshThread); }

    mods_update_selectable();
    djui_panel_host_mods_add_mods(&sModLayout->base);
    djui_paginated_calculate_height(sModPaginated);

    djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESH));
    djui_base_set_enabled(&sRefreshButton->base, true);
    djui_base_set_enabled(&sBackButton->base, true);
    gDjuiPanelDisableBack = false;

    return NULL;
}

static void djui_panel_menu_refresh(UNUSED struct DjuiBase* base) {
    djui_base_destroy_children(&sModLayout->base);
    if (init_thread_handle(&gModRefreshThread, threaded_mod_refresh, NULL, NULL, 0) == 0) {
        djui_text_set_text(sRefreshButton->text, DLANG(LOBBIES, REFRESHING));
        djui_base_set_enabled(&sRefreshButton->base, false);
        djui_base_set_enabled(&sBackButton->base, false);
        gDjuiPanelDisableBack = true;
    } else {
        threaded_mod_refresh(NULL);
    }
}

void djui_panel_host_mods_create(struct DjuiBase* caller) {

    mods_update_selectable();
    djui_panel_host_mods_description_create();

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(HOST_MODS, MODS), true);

    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        // copy category choices from sCategories
        char* categoryChoices[sizeof(sCategories)];

        // loop thru all categories names, and add those to the categoryChoices string array
        for (int i = 0; i < numCategories; i++) {
            categoryChoices[i] = djui_language_get("HOST_MOD_CATEGORIES", sCategories[i].langKey);
        }
        djui_selectionbox_create(body, DLANG(HOST_MODS, CATEGORIES), categoryChoices, numCategories, &sSelectedCategory, djui_panel_on_categories_change);
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        paginated->showMaxCount = true;
        sModLayout = paginated->layout;
        djui_panel_host_mods_add_mods(&paginated->layout->base);
        djui_paginated_calculate_height(paginated);
        sModPaginated = paginated;

        if (gNetworkType == NT_NONE) {
            struct DjuiRect* rect1 = djui_rect_container_create(body, 64);
            {
                sBackButton = djui_button_left_create(&rect1->base, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
                sRefreshButton = djui_button_right_create(&rect1->base, DLANG(LOBBIES, REFRESH), DJUI_BUTTON_STYLE_NORMAL, djui_panel_menu_refresh);
            }
        } else {
            djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
        }

        panel->bodySize.value = paginated->base.height.value + 64 + 64;
    }

    panel->base.destroy = djui_panel_host_mods_destroy;

    djui_panel_add(caller, panel, NULL);
}
