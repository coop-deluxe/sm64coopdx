#include "djui.h"
#include "src/pc/utils/misc.h"

static struct DjuiRect* sPanelQuit = NULL;
static struct DjuiFlowLayout* sButtonContainer = NULL;
static struct DjuiText* sTitleText = NULL;
static struct DjuiButton* sButtonNo = NULL;
static struct DjuiBase* sCaller = NULL;
static bool sOpening = false;
static bool sClosing = false;

static void djui_panel_quit_render_pre(struct DjuiBase* base, bool* skipRender) {
    sTitleText->base.height.value = sButtonContainer->base.clip.y - sPanelQuit->base.comp.y;

    float yMove = gPanelMainMenu->base.elem.height;
    static float movement = 0;
    if (sOpening) {
        movement += yMove / 10.0f;
        if (movement >= yMove) {
            movement = yMove;
            sOpening = false;
            djui_base_set_enabled(&sPanelQuit->base, true);
            djui_cursor_input_controlled_center(&sButtonNo->base);
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
            djui_cursor_input_controlled_center(sCaller);
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
    djui_cursor_input_controlled_center(NULL);
}

static void djui_panel_quit_create(void) {
    sOpening = true;
    sClosing = false;
    sPanelQuit = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_size_type(&sPanelQuit->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&sPanelQuit->base, 340.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&sPanelQuit->base, 0, 0, 0, 230);
    djui_base_set_border_color(&sPanelQuit->base, 0, 0, 0, 200);
    djui_base_set_border_width(&sPanelQuit->base, 8);
    djui_base_set_padding(&sPanelQuit->base, 16, 16, 16, 16);
    djui_base_set_enabled(&sPanelQuit->base, false);
    sPanelQuit->base.on_render_pre = djui_panel_quit_render_pre;
    {
        sButtonContainer = djui_flow_layout_create(&sPanelQuit->base);
        djui_base_set_alignment(&sButtonContainer->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sButtonContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sButtonContainer->base, 1.0f, 64 * 3 + 16 * 2);
        djui_base_set_color(&sButtonContainer->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(sButtonContainer, 16);
        djui_flow_layout_set_flow_direction(sButtonContainer, DJUI_FLOW_DIR_DOWN);
        {
            struct DjuiText* text = djui_text_create(&sButtonContainer->base, "Are you sure you want to quit?");
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 1.0f, 64);
            djui_base_set_color(&text->base, 200, 200, 200, 255);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

            struct DjuiButton* button1 = djui_button_create(&sButtonContainer->base, "Yes");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);
            button1->base.interactable->on_click = djui_panel_quit_yes;

            sButtonNo = djui_button_create(&sButtonContainer->base, "No");
            djui_base_set_size_type(&sButtonNo->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&sButtonNo->base, 1.0f, 64);
            sButtonNo->base.interactable->on_click = djui_panel_quit_no;
        }

        sTitleText = djui_text_create(&sPanelQuit->base, "\\#ff0800\\Q\\#1be700\\U\\#00b3ff\\I\\#ffef00\\T");
        djui_base_set_alignment(&sTitleText->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&sTitleText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sTitleText->base, 1.0f, 1.0f);
        djui_base_set_color(&sTitleText->base, 255, 8, 0, 255);
        djui_text_set_alignment(sTitleText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_font(sTitleText, &gDjuiFonts[1]);
        djui_text_set_font_scale(sTitleText, gDjuiFonts[1].defaultFontScale);
    }
}

void djui_panel_quit_open(struct DjuiBase* caller) {
    sCaller = caller;
    djui_cursor_input_controlled_center(NULL);
    djui_base_set_enabled(&gPanelMainMenu->base, false);
    djui_panel_quit_create();
}
