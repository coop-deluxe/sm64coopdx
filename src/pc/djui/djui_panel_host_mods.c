#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/cheats.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"

static struct DjuiFlowLayout* sModLayout = NULL;
static struct DjuiThreePanel* sDescriptionPanel = NULL;
static struct DjuiText* sTooltip = NULL;

static void djui_panel_host_mods_description_create() {
    f32 bodyHeight = 600;

    struct DjuiThreePanel* panel = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_alignment(&panel->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&panel->base, DJUI_DEFAULT_PANEL_WIDTH, 1.0f);
    djui_base_set_color(&panel->base, 0, 0, 0, 240);
    djui_base_set_border_color(&panel->base, 0, 0, 0, 200);
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
}

void djui_panel_host_mods_create(struct DjuiBase* caller) {
    bool isRomHacks = (caller->tag == 1);

    mods_update_selectable();

    struct DjuiThreePanel* panel = djui_panel_menu_create(isRomHacks ?
        "\\#ff0800\\R\\#1be700\\O\\#00b3ff\\M \\#ffef00\\H\\#ff0800\\A\\#1be700\\C\\#00b3ff\\K\\#ffef00\\S" :
        "\\#ff0800\\M\\#1be700\\O\\#00b3ff\\D\\#ffef00\\S"
    );
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiPaginated* paginated = djui_paginated_create(&body->base, 8);
        sModLayout = paginated->layout;
        struct DjuiBase* layoutBase = &paginated->layout->base;
        for (int i = 0; i < gLocalMods.entryCount; i++) {
            struct Mod* mod = gLocalMods.entries[i];
            if (isRomHacks != (mod->incompatible && strstr(mod->incompatible, "romhack"))) {
                continue;
            }
            struct DjuiCheckbox* checkbox = djui_checkbox_create(layoutBase, mod->name, &mod->enabled, djui_mod_checkbox_on_value_change);
            checkbox->base.tag = i;
            djui_base_set_enabled(&checkbox->base, mod->selectable);
            djui_interactable_hook_hover(&checkbox->base, djui_mod_checkbox_on_hover, djui_mod_checkbox_on_hover_end);
        }
        djui_paginated_calculate_height(paginated);

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        panel->bodySize.value = paginated->base.height.value + 16 + 64;
    }

    panel->base.destroy = djui_panel_host_mods_destroy;

    djui_panel_add(caller, panel, NULL);
    djui_panel_host_mods_description_create();
}
