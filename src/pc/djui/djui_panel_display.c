#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"

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
    struct DjuiThreePanel* panel = djui_panel_menu_create("DISPLAY");
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(body, "Fullscreen", &configWindow.fullscreen, djui_panel_display_apply);

    #ifdef EXTERNAL_DATA
        djui_checkbox_create(body, "Preload Textures", &configPrecacheRes, NULL);
    #endif

        djui_checkbox_create(body, "VSync", &configWindow.vsync, djui_panel_display_apply);
        djui_checkbox_create(body, "Uncapped Framerate", &configUncappedFramerate, djui_panel_display_apply);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
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
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, "Interpolation", interpChoices, 2, &configInterpolationMode, NULL);
        djui_base_set_enabled(&selectionbox1->base, (configFrameLimit > 30 || (configFrameLimit <= 30 && configUncappedFramerate)));
        sInterpolationSelectionBox = selectionbox1;

        char* filterChoices[3] = { "Nearest", "Linear", "Tripoint" };
        djui_selectionbox_create(body, "Filtering", filterChoices, 3, &configFiltering, NULL);

        char* drawDistanceChoices[6] = { "0.5x", "1x", "1.5x", "3x", "10x", "100x" };
        djui_selectionbox_create(body, "Draw Distance", drawDistanceChoices, 6, &configDrawDistance, NULL);

        djui_button_create(body, "DynOS Packs", DJUI_BUTTON_STYLE_NORMAL, djui_panel_dynos_create);

        djui_button_create(body, "Back", DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
