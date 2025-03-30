#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/gfx/gfx_window_manager_api.h"
#include "pc/pc_main.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

#define MSAA_ORIGINAL_UNSET ((u32)-1)

static struct DjuiInputbox* sFrameLimitInput = NULL;
static struct DjuiSelectionbox* sInterpolationSelectionBox = NULL;
static struct DjuiText* sRestartText = NULL;
static u32 sMsaaSelection = 0;
static u32 sMsaaOriginal = MSAA_ORIGINAL_UNSET;

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

static void djui_panel_display_msaa_change(UNUSED struct DjuiBase* caller) {
    switch (sMsaaSelection) {
        case 1:  configWindow.msaa = 2;  break;
        case 2:  configWindow.msaa = 4;  break;
        case 3:  configWindow.msaa = 8;  break;
        case 4:  configWindow.msaa = 16; break;
        default: configWindow.msaa = 0;  break;
    }

    if (sMsaaOriginal != configWindow.msaa) {
        djui_text_set_text(sRestartText, DLANG(DISPLAY, MUST_RESTART));
    } else {
        djui_text_set_text(sRestartText, "");
    }
}

void djui_panel_display_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(DISPLAY, DISPLAY), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    struct DjuiSelectionbox* msaa = NULL;

    // save original msaa value
    if (sMsaaOriginal == MSAA_ORIGINAL_UNSET) { sMsaaOriginal = configWindow.msaa; }

    {
        djui_checkbox_create(body, DLANG(DISPLAY, FULLSCREEN), &configWindow.fullscreen, djui_panel_display_apply);
        djui_checkbox_create(body, DLANG(DISPLAY, FORCE_4BY3), &configForce4By3, djui_panel_display_apply);
        djui_checkbox_create(body, DLANG(DISPLAY, SHOW_FPS), &configShowFPS, NULL);
        djui_checkbox_create(body, DLANG(DISPLAY, VSYNC), &configWindow.vsync, djui_panel_display_apply);
        djui_checkbox_create(body, DLANG(DISPLAY, UNCAPPED_FRAMERATE), &configUncappedFramerate, djui_panel_display_uncapped_change);

        struct DjuiRect* rect1 = djui_rect_container_create(body, 32);
        {
            if (configFrameLimit < 30) { configFrameLimit = 30; }
            if (configFrameLimit > 3000) { configFrameLimit = 3000; }
            struct DjuiText* text1 = djui_text_create(&rect1->base, DLANG(DISPLAY, FRAME_LIMIT));
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 220, 220, 220, 255);
            djui_base_set_size(&text1->base, 0.585f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_text_set_drop_shadow(text1, 64, 64, 64, 100);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.45f, 32);
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

        int maxMsaa = wm_api->get_max_msaa();
        if (maxMsaa >= 2) {
            if      (configWindow.msaa >= 16) { sMsaaSelection = 4; }
            else if (configWindow.msaa >=  8) { sMsaaSelection = 3; }
            else if (configWindow.msaa >=  4) { sMsaaSelection = 2; }
            else if (configWindow.msaa >=  2) { sMsaaSelection = 1; }
            else                              { sMsaaSelection = 0; }

            int choiceCount = 2;
            if      (maxMsaa >= 16) { choiceCount = 5; }
            else if (maxMsaa >= 8)  { choiceCount = 4; }
            else if (maxMsaa >= 4)  { choiceCount = 3; }

            char* msaaChoices[5] = { DLANG(DISPLAY, OFF), "2x", "4x", "8x", "16x" };
            msaa = djui_selectionbox_create(body, DLANG(DISPLAY, ANTIALIASING), msaaChoices, choiceCount, &sMsaaSelection, djui_panel_display_msaa_change);
        }

        char* drawDistanceChoices[6] = { DLANG(DISPLAY, D0P5X), DLANG(DISPLAY, D1X), DLANG(DISPLAY, D1P5X), DLANG(DISPLAY, D3X), DLANG(DISPLAY, D10X), DLANG(DISPLAY, D100X) };
        djui_selectionbox_create(body, DLANG(DISPLAY, DRAW_DISTANCE), drawDistanceChoices, 6, &configDrawDistance, NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        sRestartText = djui_text_create(body, "");
        djui_text_set_alignment(sRestartText, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_color(&sRestartText->base, 255, 100, 100, 255);
        djui_base_set_size_type(&sRestartText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sRestartText->base, 1.0f, 64);
    }

    // force the restart text to update
    if (msaa) {
        djui_panel_display_msaa_change(&msaa->base);
    }

    djui_panel_add(caller, panel, NULL);
}
