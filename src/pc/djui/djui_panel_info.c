#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/pc_main.h"

static char sInfo[1024];

void djui_panel_info_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(INFORMATION, INFORMATION_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        snprintf(sInfo, 1024, "sm64coopdx is a project started by the Coop Deluxe team \
to actively maintain sm64ex-coop. The purpose of it is to \
add more features, customizability and power to the Lua \
API without having to jump through the many hoops of \
issues sm64ex-coop development has.\n\
\n\
Coop Deluxe Team:\n\
Agent X: Creator\n\
AngelicMiracles: Co-creator\n\
eros71: Testing and fixing\n\
FluffaMario: Model Designer\n\
\n\
Contributors:\n\
ArcticJaguar725: Fixing a sound engine bug\n\
Isaac: Loading screen initially on sm64coopdx\n\
iZePlayzYT: Improving chat initially on sm64coopdx\n\
\n\
It is recommended you download the sm64coopdx repository if you want to make mods or DynOS Packs.\n\
\n\
OS: %s\n\
Renderer: %s\n\
sm64coopdx Version: %s\n\
sm64ex-coop Version: %s\n\
Build Type: %s",
            get_os_name(),
            RAPI_NAME,
            SM64COOPDX_VERSION,
            get_version_local(),
#ifdef DEVELOPMENT
            "Development"
#else
            "Standard"
#endif
        );

        struct DjuiText* text = djui_text_create(body, sInfo);
        const struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
        djui_base_set_location(&text->base, 0, 0);
        djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * theme->panels.widthMultiplier) - 64, 670);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
