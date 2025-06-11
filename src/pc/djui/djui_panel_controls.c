#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_controls_n64.h"
#include "djui_panel_controls_extra.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/controller/controller_api.h"
#include "pc/controller/controller_sdl.h"
#include "pc/controller/controller_system.h"

void djui_panel_controls_value_change(UNUSED struct DjuiBase* caller) {
    controller_reconfigure();
}

void djui_panel_controls_analog_stick_options_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CONTROLS, CONTROLS), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_checkbox_create(body, DLANG(CONTROLS, ROTATE_LEFT), &configStick.rotateLeft, NULL);
        djui_checkbox_create(body, DLANG(CONTROLS, INVERT_LEFT_X), &configStick.invertLeftX, NULL);
        djui_checkbox_create(body, DLANG(CONTROLS, INVERT_LEFT_Y), &configStick.invertLeftY, NULL);
        djui_checkbox_create(body, DLANG(CONTROLS, ROTATE_RIGHT), &configStick.rotateRight, NULL);
        djui_checkbox_create(body, DLANG(CONTROLS, INVERT_RIGHT_X), &configStick.invertRightX, NULL);
        djui_checkbox_create(body, DLANG(CONTROLS, INVERT_RIGHT_Y), &configStick.invertRightY, NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}

void djui_panel_controls_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(CONTROLS, CONTROLS), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        djui_button_create(body, DLANG(CONTROLS, N64_BINDS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_n64_create);
        djui_button_create(body, DLANG(CONTROLS, EXTRA_BINDS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_extra_create);
        djui_button_create(body, DLANG(CONTROLS, ANALOG_STICK_OPTIONS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_controls_analog_stick_options_create);
        djui_checkbox_create(body, DLANG(CONTROLS, BACKGROUND_GAMEPAD), &configBackgroundGamepad, NULL);
#ifndef HANDHELD
        djui_checkbox_create(body, DLANG(CONTROLS, DISABLE_GAMEPADS), &configDisableGamepads, NULL);
#endif
        djui_checkbox_create(body, DLANG(MISC, USE_STANDARD_KEY_BINDINGS_CHAT), &configUseStandardKeyBindingsChat, NULL);

#ifdef HAVE_SDL2
        controller_update_gamepad_choices();
        djui_selectionbox_create(body, DLANG(CONTROLS, GAMEPAD), gGamepadChoices, gNumJoys, &configGamepadNumber, NULL);
#endif

        djui_slider_create(body, DLANG(CONTROLS, DEADZONE), &configStickDeadzone, 0, 100, djui_panel_controls_value_change);
        djui_slider_create(body, DLANG(CONTROLS, RUMBLE_STRENGTH), &configRumbleStrength, 0, 100, djui_panel_controls_value_change);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
