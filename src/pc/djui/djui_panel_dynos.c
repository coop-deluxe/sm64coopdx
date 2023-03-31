#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "data/dynos.c.h"

static void djui_panel_dynos_apply(struct DjuiBase* caller) {
    dynos_pack_set_enabled(caller->tag, caller->bTag);
}

void djui_panel_dynos_create(struct DjuiBase* caller) {
    int packCount = dynos_pack_get_count();
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\D\\#1be700\\Y\\#00b3ff\\N\\#ffef00\\O\\#ff0800\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiPaginated* paginated = djui_paginated_create(&body->base, 8);
        struct DjuiBase* layoutBase = &paginated->layout->base;
        for (int i = 0; i < packCount; i++) {
            bool tmp = dynos_pack_get_enabled(i);
            const char* pack = dynos_pack_get_name(i);

            struct DjuiCheckbox* checkbox1 = djui_checkbox_create(layoutBase, pack, &tmp, djui_panel_dynos_apply);
            checkbox1->base.tag = i;
            checkbox1->base.bTag = tmp;
            checkbox1->value = &checkbox1->base.bTag;
        }
        djui_paginated_calculate_height(paginated);

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        panel->bodySize.value = paginated->base.height.value + 16 + 64;
    }

    djui_panel_add(caller, panel, NULL);
}
