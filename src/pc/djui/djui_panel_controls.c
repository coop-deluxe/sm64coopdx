#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "src/pc/controller/controller_api.h"
#include "src/pc/controller/controller_sdl.h"

void djui_panel_controls_value_change(UNUSED struct DjuiBase* caller) {
    controller_reconfigure();
}

void djui_panel_controls_create(struct DjuiBase* caller) {
    f32 bodyHeight = 16 * 6 + 32 * 2 + 64 * 4;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\C\\#1be700\\O\\#00b3ff\\N\\#ffef00\\T\\#ff0800\\R\\#1be700\\O\\#00b3ff\\L\\#ffef00\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
        struct DjuiButton* button1 = djui_button_create(&body->base, "N64 Binds");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_interactable_hook_click(&button1->base, djui_panel_controls_n64_create);
        defaultBase = &button1->base;

        struct DjuiButton* button2 = djui_button_create(&body->base, "Extra Binds");
        djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button2->base, 1.0f, 64);
        djui_interactable_hook_click(&button2->base, djui_panel_controls_extra_create);

        struct DjuiCheckbox* checkboxGB = djui_checkbox_create(&body->base, "Background Gamepad (must restart)", &configBackgroundGamepad);
        djui_base_set_size_type(&checkboxGB->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkboxGB->base, 1.0f, 32);

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
        struct DjuiSelectionbox* selectionboxGamepad = djui_selectionbox_create(&body->base, "Gamepad", gamepadChoices, numJoys, &configGamepadNumber);
        djui_base_set_size_type(&selectionboxGamepad->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionboxGamepad->base, 1.0f, 32);
#endif

        struct DjuiSlider* slider1 = djui_slider_create(&body->base, "Deadzone", &configStickDeadzone, 0, 100);
        djui_base_set_size_type(&slider1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&slider1->base, djui_panel_controls_value_change);

        struct DjuiSlider* slider2 = djui_slider_create(&body->base, "Rumble Strength", &configRumbleStrength, 0, 100);
        djui_base_set_size_type(&slider2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&slider2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&slider2->base, djui_panel_controls_value_change);

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
