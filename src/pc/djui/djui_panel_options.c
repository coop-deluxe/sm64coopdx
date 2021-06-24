#include "djui.h"
#include "src/pc/utils/misc.h"

static struct DjuiThreePanel* sPanelOptions = NULL;
static struct DjuiButton* sButtonBack = NULL;
static struct DjuiBase* sCaller = NULL;
static bool sOpening = false;
static bool sClosing = false;

static void djui_panel_options_render_pre(struct DjuiBase* base, bool* skipRender) {
    float yMove = gPanelMainMenu->base.elem.height;
    static float movement = 0;
    if (sOpening) {
        movement += yMove / 10.0f;
        if (movement >= yMove) {
            movement = yMove;
            sOpening = false;
            djui_base_set_enabled(&sPanelOptions->base, true);
            djui_cursor_input_controlled_center(&sButtonBack->base);
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
            djui_cursor_input_controlled_center(sCaller);
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
    djui_cursor_input_controlled_center(NULL);
}

void djui_panel_options_create(void) {
    f32 bodyHeight = 64 * 6 + 16 * 5;
    sOpening = true;
    sClosing = false;

    sPanelOptions = djui_three_panel_create(&gDjuiRoot->base, 64, bodyHeight, 0);
    djui_base_set_size_type(&sPanelOptions->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&sPanelOptions->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&sPanelOptions->base, 0, 0, 0, 240);
    djui_base_set_border_color(&sPanelOptions->base, 0, 0, 0, 200);
    djui_base_set_border_width(&sPanelOptions->base, 8);
    djui_base_set_padding(&sPanelOptions->base, 16, 16, 16, 16);
    sPanelOptions->base.on_render_pre = djui_panel_options_render_pre;
    {
        struct DjuiText* header = djui_text_create(&sPanelOptions->base, "\\#ff0800\\O\\#1be700\\P\\#00b3ff\\T\\#ffef00\\I\\#ff0800\\O\\#1be700\\N\\#00b3ff\\S");
        djui_base_set_alignment(&header->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&header->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&header->base, 1.0f, 1.0f);
        djui_base_set_color(&header->base, 255, 8, 0, 255);
        djui_text_set_alignment(header, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_font(header, &gDjuiFonts[1]);
        djui_text_set_font_scale(header, gDjuiFonts[1].defaultFontScale);

        struct DjuiFlowLayout* body = djui_flow_layout_create(&sPanelOptions->base);
        djui_base_set_alignment(&body->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&body->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&body->base, 1.0f, bodyHeight);
        djui_base_set_color(&body->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(body, 16);
        djui_flow_layout_set_flow_direction(body, DJUI_FLOW_DIR_DOWN);
        {
            struct DjuiButton* button1 = djui_button_create(&body->base, "Player");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);

            struct DjuiButton* button2 = djui_button_create(&body->base, "Camera");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);

            struct DjuiButton* button3 = djui_button_create(&body->base, "Controls");
            djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button3->base, 1.0f, 64);

            struct DjuiButton* button4 = djui_button_create(&body->base, "Display");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);

            struct DjuiButton* button5 = djui_button_create(&body->base, "Sound");
            djui_base_set_size_type(&button5->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button5->base, 1.0f, 64);

            sButtonBack = djui_button_create(&body->base, "Back");
            djui_base_set_size_type(&sButtonBack->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sButtonBack->base, 1.0f, 64);
            sButtonBack->base.interactable->on_click = djui_panel_options_back;
        }
    }
}

void djui_panel_options_open(struct DjuiBase* caller) {
    sCaller = caller;
    djui_cursor_input_controlled_center(NULL);
    djui_base_set_enabled(&gPanelMainMenu->base, false);
    djui_panel_options_create();
}
