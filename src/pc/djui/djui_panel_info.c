#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/lua/utils/smlua_misc_utils.h"

static char sInfo[512];

static const char* get_renderer_name(void) {
#if defined(RAPI_GL)
    return "OpenGL Renderer";
#elif defined(RAPI_GL_LEGACY)
    return "OpenGL ES Renderer";
#elif defined(RAPI_D3D11)
    return "DirectX 11 Renderer";
#elif defined(RAPI_D3D12)
    return "DirectX 12 Renderer"
#endif
    return "No Renderer";
}

static const char* get_development_build(void) {
#ifdef DEVELOPMENT
    return "TRUE";
#else
    return "FALSE";
#endif
}

void djui_panel_info_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(INFORMATION, INFORMATION_TITLE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        snprintf(sInfo, 512, "sm64coopdx is a project started by the Coop Deluxe team \
to actively maintain sm64ex-coop. The purpose of it is to \
add more features, customizability and power to the Lua \
API without having to jump through the many hoops of \
issues sm64ex-coop has.\n\
\n\
OS: %s\n\
Renderer: %s\n\
sm64coopdx: Initial Release\n\
sm64ex-coop: %s\n\
Development Build: %s",
            get_os_name(),
            get_renderer_name(),
            get_version_local(),
            get_development_build()
        );

        struct DjuiText* text = djui_text_create(body, sInfo);
        const struct DjuiTheme* theme = gDjuiThemes[configDjuiTheme];
        djui_base_set_location(&text->base, 0, 0);
        djui_base_set_size(&text->base, (DJUI_DEFAULT_PANEL_WIDTH * theme->panels.widthMultiplier) - 64, 300);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_drop_shadow(text, 64, 64, 64, 100);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
