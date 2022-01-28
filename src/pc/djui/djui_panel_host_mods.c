#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/cheats.h"
#include "pc/mod_list.h"

static struct DjuiFlowLayout* sModPanelBody = NULL;
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
    if (base->tag >= 0 && base->tag < gModTableLocal.entryCount) {
        char* d = gModTableLocal.entries[base->tag].description;
        if (d != NULL) {
            description = gModTableLocal.entries[base->tag].description;
        }
    }
    djui_text_set_text(sTooltip, description);
}

static void djui_mod_checkbox_on_hover_end(UNUSED struct DjuiBase* base) {
    djui_text_set_text(sTooltip, "");
}

static void djui_mod_checkbox_on_value_change(UNUSED struct DjuiBase* base) {
    mod_list_update_selectable();

    u16 index = 0;
    struct DjuiBaseChild* node = sModPanelBody->base.child;
    while (node != NULL) {
        if (index >= gModTableLocal.entryCount) { break; }
        struct ModListEntry* entry = &gModTableLocal.entries[index];

        djui_base_set_enabled(node->base, entry->selectable);
 
        // iterate
        index++;
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
    f32 bodyHeight = 32 * gModTableLocal.entryCount + 64 * 1 + 16 * (gModTableLocal.entryCount + 1);

    mod_list_update_selectable();

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\M\\#1be700\\O\\#00b3ff\\D\\#ffef00\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    sModPanelBody = body;
    {
        for (int i = 0; i < gModTableLocal.entryCount; i++) {
            struct ModListEntry* entry = &gModTableLocal.entries[i];
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, entry->displayName ? entry->displayName : entry->name, &entry->enabled);
            checkbox->base.tag = i;
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
            djui_base_set_enabled(&checkbox->base, entry->selectable);
            djui_interactable_hook_hover(&checkbox->base, djui_mod_checkbox_on_hover, djui_mod_checkbox_on_hover_end);
            djui_interactable_hook_value_change(&checkbox->base, djui_mod_checkbox_on_value_change);
        }

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
        defaultBase = &button1->base;
    }

    panel->base.destroy = djui_panel_host_mods_destroy;

    djui_panel_add(caller, &panel->base, defaultBase);
    djui_panel_host_mods_description_create();
}
