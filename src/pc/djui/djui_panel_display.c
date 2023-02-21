#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

// The checkbox size is determined by the base size they all have and the amount.
#define CHECKBOXES_SIZE 32 * 5
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

static struct DjuiInputbox* sFrameLimitInput = NULL;
static struct DjuiSelectionbox* sInterpolationSelectionBox = NULL;

static void djui_panel_display_apply(UNUSED struct DjuiBase* caller) {
    configWindow.settings_changed = true;
}

static void djui_panel_display_uncapped_change(UNUSED struct DjuiBase* caller) {
    djui_base_set_enabled(&sFrameLimitInput->base, !configUncappedFramerate);
    djui_base_set_enabled(&sInterpolationSelectionBox->base, (configFrameLimit > 30 || (configFrameLimit <= 30 && configUncappedFramerate)));
}

static void djui_panel_display_frame_limit_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    s32 frameLimit = atoi(inputbox1->buffer);
    if (frameLimit >= 30 && frameLimit <= 3000) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
        configFrameLimit = frameLimit;
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
    djui_base_set_enabled(&sInterpolationSelectionBox->base, (configFrameLimit > 30 || (configFrameLimit <= 30 && configUncappedFramerate)));
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

    #ifdef EXTERNAL_DATA
        struct DjuiCheckbox* checkbox7 = djui_checkbox_create(&body->base, "Preload Textures", &configPrecacheRes);
        djui_base_set_size_type(&checkbox7->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox7->base, 1.0f, 32);
    #endif

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "VSync", &configWindow.vsync);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox2->base, djui_panel_display_apply);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Uncapped Framerate", &configUncappedFramerate);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);
        djui_interactable_hook_value_change(&checkbox3->base, djui_panel_display_uncapped_change);

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 32);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            if (configFrameLimit < 30) { configFrameLimit = 30; }
            if (configFrameLimit > 3000) { configFrameLimit = 3000; }
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Frame Limit");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.5f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char frameLimitString[32] = { 0 };
            snprintf(frameLimitString, 32, "%d", configFrameLimit);
            djui_inputbox_set_text(inputbox1, frameLimitString);
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_display_frame_limit_text_change);
            djui_base_set_enabled(&inputbox1->base, !configUncappedFramerate);
            sFrameLimitInput = inputbox1;
        }

        char* interpChoices[2] = { "Fast", "Accurate" };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Interpolation", interpChoices, 2, &configInterpolationMode);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);
        djui_base_set_enabled(&selectionbox1->base, (configFrameLimit > 30 || (configFrameLimit <= 30 && configUncappedFramerate)));
        sInterpolationSelectionBox = selectionbox1;

        char* filterChoices[3] = { "Nearest", "Linear", "Tripoint" };
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(&body->base, "Filtering", filterChoices, 3, &configFiltering);
        djui_base_set_size_type(&selectionbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox2->base, 1.0f, 32);

        char* drawDistanceChoices[6] = { "0.5x", "1x", "1.5x", "3x", "10x", "100x" };
        struct DjuiSelectionbox* selectionbox3 = djui_selectionbox_create(&body->base, "Draw Distance", drawDistanceChoices, 6, &configDrawDistance);
        djui_base_set_size_type(&selectionbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox3->base, 1.0f, 32);

        struct DjuiButton* button1 = djui_button_create(&body->base, "DynOS Packs");
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
