#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/pc/controller/controller_api.h"
#include "src/pc/controller/controller_sdl.h"

void djui_panel_controls_value_change(UNUSED struct DjuiBase* caller) {
    controller_reconfigure();
}

void djui_panel_controls_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CONTROLS, CONTROLS));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_button_create(body, DLANG(CONTROLS, N64_BINDS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_n64_create);
        djui_button_create(body, DLANG(CONTROLS, EXTRA_BINDS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_extra_create);
        djui_checkbox_create(body, DLANG(CONTROLS, BACKGROUND_GAMEPAD), &configBackgroundGamepad, NULL);

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
        djui_selectionbox_create(body, DLANG(CONTROLS, GAMEPAD), gamepadChoices, numJoys, &configGamepadNumber, NULL);
#endif

        djui_slider_create(body, DLANG(CONTROLS, DEADZONE), &configStickDeadzone, 0, 100, djui_panel_controls_value_change);
        djui_slider_create(body, DLANG(CONTROLS, RUMBLE_STRENGTH), &configRumbleStrength, 0, 100, djui_panel_controls_value_change);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
