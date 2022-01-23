#include <stdio.h>
#include "djui.h"
#include "game/save_file.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/cheats.h"
#include "pc/mod_list.h"

void djui_panel_host_mods_create(struct DjuiBase* caller) {
    f32 bodyHeight = 32 * gModTableLocal.entryCount + 64 * 1 + 16 * (gModTableLocal.entryCount + 1);

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\M\\#1be700\\O\\#00b3ff\\D\\#ffef00\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        for (int i = 0; i < gModTableLocal.entryCount; i++) {
            struct ModListEntry* entry = &gModTableLocal.entries[i];
            struct DjuiCheckbox* checkbox = djui_checkbox_create(&body->base, entry->name, &entry->enabled);
            djui_base_set_size_type(&checkbox->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox->base, 1.0f, 32);
        }

        struct DjuiButton* button1 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_button_set_style(button1, 1);
        djui_interactable_hook_click(&button1->base, djui_panel_menu_back);
        defaultBase = &button1->base;
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
