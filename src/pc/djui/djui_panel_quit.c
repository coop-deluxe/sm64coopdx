#include "djui.h"
#include "src/pc/utils/misc.h"

struct DjuiRect* sPanelQuit = NULL;
bool sOpening = false;
bool sClosing = false;

static void djui_panel_quit_render_pre(struct DjuiBase* base, bool* skipRender) {
    float yMove = gPanelMainMenu->base.elem.height;
    static float movement = 0;
    if (sOpening) {
        movement += yMove / 10.0f;
        if (movement >= yMove) {
            movement = yMove;
            sOpening = false;
            djui_base_set_enabled(&sPanelQuit->base, true);
        }
    } else if (sClosing) {
        movement -= yMove / 10.0f;
        if (movement <= 0) {
            movement = 0;
            sClosing = false;
            djui_base_destroy(&sPanelQuit->base);
            sPanelQuit = NULL;
            *skipRender = true;
            djui_base_set_enabled(&gPanelMainMenu->base, true);
            gPanelMainMenu->base.y.value = 0;
            return;
        }
    } else {
        movement = yMove;
    }
    gPanelMainMenu->base.y.value = -yMove * smoothstep(0, yMove, movement);
    sPanelQuit->base.y.value = gPanelMainMenu->base.elem.y + gPanelMainMenu->base.elem.height;
}

static void djui_panel_quit_yes(struct DjuiBase* base) {
    exit(0);
}

static void djui_panel_quit_no(struct DjuiBase* base) {
    sClosing = true;
    djui_base_set_enabled(&sPanelQuit->base, false);
}

static void djui_panel_quit_create(void) {
    sOpening = true;
    sClosing = false;
    sPanelQuit = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_size_type(&sPanelQuit->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&sPanelQuit->base, 512.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&sPanelQuit->base, 0, 0, 0, 230);
    djui_base_set_border_color(&sPanelQuit->base, 0, 0, 0, 200);
    djui_base_set_border_width(&sPanelQuit->base, 8);
    djui_base_set_padding(&sPanelQuit->base, 16, 16, 16, 16);
    djui_base_set_enabled(&sPanelQuit->base, false);
    sPanelQuit->base.on_render_pre = djui_panel_quit_render_pre;
    {
        struct DjuiFlowLayout* quitContainer = djui_flow_layout_create(&sPanelQuit->base);
        djui_base_set_alignment(&quitContainer->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&quitContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&quitContainer->base, 1.0f, 64 * 3 + 16 * 2);
        djui_base_set_color(&quitContainer->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(quitContainer, 16);
        djui_flow_layout_set_flow_direction(quitContainer, DJUI_FLOW_DIR_DOWN);
        {
            struct DjuiText* text = djui_text_create(&quitContainer->base, "Are you sure you want to quit?");
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 1.0f, 64);
            djui_base_set_color(&text->base, 200, 200, 200, 255);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

            struct DjuiButton* button1 = djui_button_create(&quitContainer->base, "Yes");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);
            button1->base.interactable->on_click = djui_panel_quit_yes;

            struct DjuiButton* button2 = djui_button_create(&quitContainer->base, "No");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);
            button2->base.interactable->on_click = djui_panel_quit_no;
        }
    }
}

void djui_panel_quit_open(struct DjuiBase* caller) {
    djui_base_set_enabled(&gPanelMainMenu->base, false);
    djui_panel_quit_create();
}