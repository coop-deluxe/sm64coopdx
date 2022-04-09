#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

// The checkbox size is determined by the base size they all have and the amount.
#define CHECKBOXES_SIZE 32 * 6
// The checkbox pad size is determined by half the base size they all have and the amount plus one.
#define CHECKBOXES_PAD_SIZE 16 * 7
// The accumulative size of both the padding size and normal size for the checkboxes.
#define CHECKBOXES_FULL_SIZE CHECKBOXES_SIZE + CHECKBOXES_PAD_SIZE

// The selection box size is determined by the base size they all have and the amount.
#define SELECTION_BOXES_SIZE 32 * 3
// The selection box pad size is determined by half the base size they all have and the amount plus one.
#define SELECTION_BOXES_PAD_SIZE 16 * 4
// The accumulative size of both the padding size and normal size for the selection boxes.
#define SELECTION_BOXES_FULL_SIZE SELECTION_BOXES_SIZE + SELECTION_BOXES_PAD_SIZE

// The button size is determined by the base size they all have and the amount.
#define BUTTON_SIZES 64 * 2

// The full height for the body.
#define BODY_HEIGHT CHECKBOXES_FULL_SIZE + SELECTION_BOXES_FULL_SIZE + BUTTON_SIZES

static void djui_panel_display_apply(UNUSED struct DjuiBase* caller) {
    configWindow.settings_changed = true;
}

void djui_panel_display_create(struct DjuiBase* caller) {
    f32 bodyHeight = BODY_HEIGHT;

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\D\\#1be700\\I\\#00b3ff\\S\\#ffef00\\P\\#ff0800\\L\\#1be700\\A\\#00b3ff\\Y");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Fullscreen", &configWindow.fullscreen);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox1->base, djui_panel_display_apply);
        defaultBase = &checkbox1->base;

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "VSync", &configWindow.vsync);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox2->base, djui_panel_display_apply);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "HUD", &configHUD);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox4 = djui_checkbox_create(&body->base, "Disable Popups", &configDisablePopups);
        djui_base_set_size_type(&checkbox4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox4->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox5 = djui_checkbox_create(&body->base, "Disable Downloaded Models", &configDisableDownloadedModels);
        djui_base_set_size_type(&checkbox5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox5->base, 1.0f, 32);
        
    #ifdef EXTERNAL_DATA
        struct DjuiCheckbox* checkbox6 = djui_checkbox_create(&body->base, "Preload Textures", &configPrecacheRes);
        djui_base_set_size_type(&checkbox6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox6->base, 1.0f, 32);
    #endif

        char* filterChoices[3] = { "Nearest", "Linear", "Tripoint" };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Filtering", filterChoices, 3, &configFiltering);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);

        char* fpsChoices[3] = { "30", "60" };
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(&body->base, "FPS", fpsChoices, 2, &config60Fps);
        djui_base_set_size_type(&selectionbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox2->base, 1.0f, 32);

        char* drawDistanceChoices[6] = { "0.5x", "1x", "1.5x", "3x", "10x", "100x" };
        struct DjuiSelectionbox* selectionbox3 = djui_selectionbox_create(&body->base, "Draw Distance", drawDistanceChoices, 6, &configDrawDistance);
        djui_base_set_size_type(&selectionbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox3->base, 1.0f, 32);

        struct DjuiButton* button1 = djui_button_create(&body->base, "DynOS Model Packs");
        djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button1->base, 1.0f, 64);
        djui_interactable_hook_click(&button1->base, djui_panel_dynos_create);

        struct DjuiButton* button2 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button2->base, 1.0f, 64);
        djui_button_set_style(button2, 1);
        djui_interactable_hook_click(&button2->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
