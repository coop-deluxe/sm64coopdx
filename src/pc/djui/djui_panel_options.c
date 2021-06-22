#include "djui.h"
#include "src/pc/utils/misc.h"

static struct DjuiRect* sPanelOptions = NULL;
static struct DjuiFlowLayout* sButtonContainer = NULL;
static struct DjuiText* sTitleText = NULL;
static bool sOpening = false;
static bool sClosing = false;

static void djui_panel_options_render_pre(struct DjuiBase* base, bool* skipRender) {
    sTitleText->base.height.value = sButtonContainer->base.clip.y - sPanelOptions->base.comp.y;

    float yMove = gPanelMainMenu->base.elem.height;
    static float movement = 0;
    if (sOpening) {
        movement += yMove / 10.0f;
        if (movement >= yMove) {
            movement = yMove;
            sOpening = false;
            djui_base_set_enabled(&sPanelOptions->base, true);
        }
    } else if (sClosing) {
        movement -= yMove / 10.0f;
        if (movement <= 0) {
            movement = 0;
            sClosing = false;
            djui_base_destroy(&sPanelOptions->base);
            sPanelOptions = NULL;
            *skipRender = true;
            djui_base_set_enabled(&gPanelMainMenu->base, true);
            gPanelMainMenu->base.y.value = 0;
            return;
        }
    } else {
        movement = yMove;
    }
    gPanelMainMenu->base.y.value = yMove * smoothstep(0, yMove, movement);
    sPanelOptions->base.y.value = gPanelMainMenu->base.elem.y - sPanelOptions->base.elem.height;
}

static void djui_panel_options_back(struct DjuiBase* base) {
    sClosing = true;
    djui_base_set_enabled(&sPanelOptions->base, false);
}

void djui_panel_options_create(void) {
    sOpening = true;
    sClosing = false;
    sPanelOptions = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_size_type(&sPanelOptions->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&sPanelOptions->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&sPanelOptions->base, 0, 0, 0, 240);
    djui_base_set_border_color(&sPanelOptions->base, 0, 0, 0, 200);
    djui_base_set_border_width(&sPanelOptions->base, 8);
    djui_base_set_padding(&sPanelOptions->base, 16, 16, 16, 16);
    sPanelOptions->base.on_render_pre = djui_panel_options_render_pre;
    {
        sButtonContainer = djui_flow_layout_create(&sPanelOptions->base);
        djui_base_set_alignment(&sButtonContainer->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sButtonContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sButtonContainer->base, 1.0f, 64 * 6 + 16 * 5);
        djui_base_set_color(&sButtonContainer->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(sButtonContainer, 16);
        djui_flow_layout_set_flow_direction(sButtonContainer, DJUI_FLOW_DIR_DOWN);
        {
            struct DjuiButton* button1 = djui_button_create(&sButtonContainer->base, "Player");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);

            struct DjuiButton* button2 = djui_button_create(&sButtonContainer->base, "Camera");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);

            struct DjuiButton* button3 = djui_button_create(&sButtonContainer->base, "Controls");
            djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button3->base, 1.0f, 64);

            struct DjuiButton* button4 = djui_button_create(&sButtonContainer->base, "Display");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);

            struct DjuiButton* button5 = djui_button_create(&sButtonContainer->base, "Sound");
            djui_base_set_size_type(&button5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button5->base, 1.0f, 64);

            struct DjuiButton* button6 = djui_button_create(&sButtonContainer->base, "Back");
            djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button6->base, 1.0f, 64);
            button6->base.interactable->on_click = djui_panel_options_back;
        }

        sTitleText = djui_text_create(&sPanelOptions->base, "\\#ff0800\\O\\#1be700\\P\\#00b3ff\\T\\#ffef00\\I\\#ff0800\\O\\#1be700\\N\\#00b3ff\\S");
        djui_base_set_alignment(&sTitleText->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&sTitleText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sTitleText->base, 1.0f, 1.0f);
        djui_base_set_color(&sTitleText->base, 255, 8, 0, 255);
        djui_text_set_alignment(sTitleText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_font(sTitleText, &gDjuiFonts[1]);
        djui_text_set_font_scale(sTitleText, gDjuiFonts[1].defaultFontScale);
    }
}

void djui_panel_options_open(struct DjuiBase* caller) {
    djui_base_set_enabled(&gPanelMainMenu->base, false);
    djui_panel_options_create();
}
