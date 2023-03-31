#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/pc/controller/controller_api.h"
#include "src/pc/controller/controller_sdl.h"

void djui_panel_controls_value_change(UNUSED struct DjuiBase* caller) {
    controller_reconfigure();
}

void djui_panel_controls_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create("\\#ff0800\\C\\#1be700\\O\\#00b3ff\\N\\#ffef00\\T\\#ff0800\\R\\#1be700\\O\\#00b3ff\\L\\#ffef00\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        djui_button_create(&body->base, "N64 Binds", DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_n64_create);
        djui_button_create(&body->base, "Extra Binds", DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_extra_create);
        djui_checkbox_create(&body->base, "Background Gamepad (must restart)", &configBackgroundGamepad, NULL);

#ifdef HAVE_SDL2
        int numJoys = SDL_NumJoysticks();
        if (numJoys == 0) { numJoys = 1; }
        if (numJoys > 10) { numJoys = 10; }
        int strSize = numJoys * 2;
        char* gamepadChoices[numJoys];
        char gamepadChoicesLong[strSize];
        for (int i = 0; i < numJoys; i++) {
            int index = i * 2;
            if (i > 9) {
                index += (i - 9);
            }
            sprintf(&gamepadChoicesLong[index], "%d", i);
            gamepadChoices[i] = &gamepadChoicesLong[index];
        }
        djui_selectionbox_create(&body->base, "Gamepad", gamepadChoices, numJoys, &configGamepadNumber, NULL);
#endif

        djui_slider_create(&body->base, "Deadzone", &configStickDeadzone, 0, 100, djui_panel_controls_value_change);
        djui_slider_create(&body->base, "Rumble Strength", &configRumbleStrength, 0, 100, djui_panel_controls_value_change);

        djui_button_create(&body->base, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
