#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_controls_n64.h"
#include "djui_panel_controls_extra.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/controller/controller_api.h"
#include "pc/controller/controller_sdl.h"

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

        djui_checkbox_create(body, DLANG(MISC, CHAT_CHAR_COUNTER), &configChatCharCounter, NULL);
        djui_checkbox_create(body, DLANG(MISC, DISABLE_CHAT_WHEN_CLOSED), &configDisableChatWhenClosed, NULL);

        static unsigned int sChatWidthIndex = 3;
        switch (configChatWidth) {
            case 500: sChatWidthIndex = 0; break;
            case 600: sChatWidthIndex = 1; break;
            case 700: sChatWidthIndex = 2; break;
            case 800: sChatWidthIndex = 3; break;
            case 900: sChatWidthIndex = 4; break;
            case 1000: sChatWidthIndex = 5; break;
            case 1100: sChatWidthIndex = 6; break;
            default: sChatWidthIndex = 3; break;
        }

        char* chatWidthChoices[] = { DLANG(MISC, CHAT_WIDTH_TINY), DLANG(MISC, CHAT_WIDTH_VERY_SMALL), DLANG(MISC, CHAT_WIDTH_SMALL), DLANG(MISC, CHAT_WIDTH_NORMAL), DLANG(MISC, CHAT_WIDTH_BIG), DLANG(MISC, CHAT_WIDTH_VERY_BIG), DLANG(MISC, CHAT_WIDTH_HUGE) };
        void on_chat_width_change(UNUSED struct DjuiBase* b) {
            unsigned int idx = sChatWidthIndex;
            unsigned int widths[] = {500,600,700,800,900,1000,1100};
            configChatWidth = widths[idx];
            if (gDjuiChatBox != NULL) {
                djui_base_set_size(&gDjuiChatBox->base, configChatWidth, gDjuiChatBox->base.height.value);
            }
        }
        djui_selectionbox_create(body, DLANG(MISC, CHAT_WIDTH), chatWidthChoices, 7, &sChatWidthIndex, on_chat_width_change);

#ifdef HAVE_SDL2
        int numJoys = SDL_NumJoysticks();
        if (numJoys == 0) { numJoys = 1; }

        char** gamepadChoices = calloc(numJoys, sizeof(char *));

        // Get the names of all connected gamepads, if none is provided, use "Unknown"
        for (int i = 0; i < numJoys; i++) {
            const char* joystickName = SDL_JoystickNameForIndex(i);
            if (joystickName == NULL) {
                joystickName = "Unknown";
            }
            gamepadChoices[i] = strdup(joystickName);
        }

        // Check for repeated names and append a number if necessary
        for (int i = 0; i < numJoys; i++) {
            int count = 1;
            for (int j = 0; j < i; j++) {
                if (strcmp(gamepadChoices[i], gamepadChoices[j]) == 0) {
                    count++;
                    char newName[256];

                    // If the name is bigger than 9 characters, we need to truncate it first
                    // Then we can append the number so it fits in the slot

                    // Should we look into making scrolling text for this?
                    if (strlen(gamepadChoices[i]) > 9) {
                        snprintf(newName, sizeof(newName), "%.9s... (%d)", gamepadChoices[i], count);
                    } else {
                        snprintf(newName, sizeof(newName), "%s (%d)", gamepadChoices[i], count);
                    }

                    // Remove the old string and replace it with the new one
                    free(gamepadChoices[i]);
                    gamepadChoices[i] = strdup(newName);
                }
            }
        }

        // Create the button
        djui_selectionbox_create(body, DLANG(CONTROLS, GAMEPAD), gamepadChoices, numJoys, &configGamepadNumber, NULL);

        // Free the memory we don't need anymore
        for (int i = 0; i < numJoys; i++) {
            free(gamepadChoices[i]);
        }

        free(gamepadChoices);
#endif

        djui_slider_create(body, DLANG(CONTROLS, DEADZONE), &configStickDeadzone, 0, 100, djui_panel_controls_value_change);
        djui_slider_create(body, DLANG(CONTROLS, RUMBLE_STRENGTH), &configRumbleStrength, 0, 100, djui_panel_controls_value_change);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
