#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_dynos.h"
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
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(DISPLAY, DISPLAY));
    struct DjuiBase* body = djui_three_panel_get_body(panel);

    {
        djui_checkbox_create(body, DLANG(DISPLAY, FULLSCREEN), &configWindow.fullscreen, djui_panel_display_apply);

    #ifdef EXTERNAL_DATA
        djui_checkbox_create(body, DLANG(DISPLAY, PRELOAD_TEXTURES), &configPrecacheRes, NULL);
    #endif

        djui_checkbox_create(body, DLANG(DISPLAY, VSYNC), &configWindow.vsync, djui_panel_display_apply);
        djui_checkbox_create(body, DLANG(DISPLAY, UNCAPPED_FRAMERATE), &configUncappedFramerate, djui_panel_display_apply);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            if (configFrameLimit < 30) { configFrameLimit = 30; }
            if (configFrameLimit > 3000) { configFrameLimit = 3000; }
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(DISPLAY, FRAME_LIMIT));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.4f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char frameLimitString[32] = { 0 };
            snprintf(frameLimitString, 32, "%d", configFrameLimit);
            djui_inputbox_set_text(inputbox1, frameLimitString);
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_display_frame_limit_text_change);
            djui_base_set_enabled(&inputbox1->base, !configUncappedFramerate);
            sFrameLimitInput = inputbox1;
        }

        char* interpChoices[2] = { DLANG(DISPLAY, FAST), DLANG(DISPLAY, ACCURATE) };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(body, DLANG(DISPLAY, INTERPOLATION), interpChoices, 2, &configInterpolationMode, NULL);
        djui_base_set_enabled(&selectionbox1->base, (configFrameLimit > 30 || (configFrameLimit <= 30 && configUncappedFramerate)));
        sInterpolationSelectionBox = selectionbox1;

        char* filterChoices[3] = { DLANG(DISPLAY, NEAREST), DLANG(DISPLAY, LINEAR), DLANG(DISPLAY, TRIPOINT) };
        djui_selectionbox_create(body, DLANG(DISPLAY, FILTERING), filterChoices, 3, &configFiltering, NULL);

        char* drawDistanceChoices[6] = { DLANG(DISPLAY, D0P5X), DLANG(DISPLAY, D1X), DLANG(DISPLAY, D1P5X), DLANG(DISPLAY, D3X), DLANG(DISPLAY, D10X), DLANG(DISPLAY, D100X) };
        djui_selectionbox_create(body, DLANG(DISPLAY, DRAW_DISTANCE), drawDistanceChoices, 6, &configDrawDistance, NULL);

        djui_button_create(body, DLANG(DISPLAY, DYNOS_PACKS), DJUI_BUTTON_STYLE_NORMAL, djui_panel_dynos_create);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
