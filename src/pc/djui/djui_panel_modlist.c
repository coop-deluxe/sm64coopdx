#include <string.h>

#include "djui.h"
#include "djui_panel_menu.h"
#include "djui_panel_misc.h"
#include "pc/mods/mods.h"
#include "pc/debuglog.h"

struct DjuiThreePanel* gDjuiModList = NULL;

void djui_panel_modlist_create(UNUSED struct DjuiBase* caller) {
    int playerListWidth = 710;
    int modListWidth = 280;

    // delete old mod list
    if (gDjuiModList != NULL) {
        djui_base_destroy(&gDjuiModList->base);
        gDjuiModList = NULL;
    }

    // only create if we have mods
    if (gActiveMods.entryCount == 0) { return; }

    f32 bodyHeight = (gActiveMods.entryCount * 32) + (gActiveMods.entryCount - 1) * 4;
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(MODLIST, MODS), false);
    djui_three_panel_set_body_size(panel, bodyHeight);
    gDjuiModList = panel;

    djui_base_set_alignment(&panel->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

    djui_base_set_location_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_location(&panel->base, (playerListWidth + modListWidth) / 2 + 8, 0);

    djui_base_set_size_type(&panel->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&panel->base, 280, bodyHeight + (32 + 16) + 32 + 32);

    djui_base_set_visible(&panel->base, false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    djui_flow_layout_set_margin((struct DjuiFlowLayout*)body, 4);

    for (int i = 0; i < gActiveMods.entryCount; i++) {
        struct Mod* mod = gActiveMods.entries[i];

        struct DjuiFlowLayout* row = djui_flow_layout_create(body);
        djui_base_set_size_type(&row->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&row->base, 1.0f, 32.0f);
        int v = (i % 2) ? 16 : 32;
        djui_base_set_color(&row->base, v, v, v, 128);
        djui_flow_layout_set_flow_direction(row, DJUI_FLOW_DIR_RIGHT);
        djui_flow_layout_set_margin(row, 8);

        int t = 220;
        struct DjuiText* t2 = djui_text_create(&row->base, mod->name);
        djui_base_set_size_type(&t2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&t2->base, 1.0f, 32.0f);
        djui_base_set_color(&t2->base, t, t, t, 255);
    }

}
