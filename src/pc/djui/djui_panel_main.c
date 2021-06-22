#include "djui.h"

ALIGNED8 static u8 texture_title[] = {
#include "textures/segment2/custom_title.rgba32.inc.c"
};

struct DjuiRect* gPanelMainMenu = NULL;
struct DjuiFlowLayout* sButtonContainer = NULL;
struct DjuiText* sTitleText = NULL;
struct DjuiText* sVersionText = NULL;

static void djui_panel_main_render_pre(struct DjuiBase* base, bool* skipRender) {
    sTitleText->base.height.value = sButtonContainer->base.clip.y - gPanelMainMenu->base.comp.y;
    sVersionText->base.height.value = sTitleText->base.height.value;
}

void djui_panel_main_create(void) {
    gPanelMainMenu = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_size_type(&gPanelMainMenu->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&gPanelMainMenu->base, 350.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&gPanelMainMenu->base, 0, 0, 0, 230);
    djui_base_set_border_color(&gPanelMainMenu->base, 0, 0, 0, 200);
    djui_base_set_border_width(&gPanelMainMenu->base, 8);
    djui_base_set_padding(&gPanelMainMenu->base, 16, 16, 16, 16);
    {
        sButtonContainer = djui_flow_layout_create(&gPanelMainMenu->base);
        djui_base_set_alignment(&sButtonContainer->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sButtonContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sButtonContainer->base, 1.0f, 64 * 4 + 16 * 3);
        djui_base_set_color(&sButtonContainer->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(sButtonContainer, 16);
        djui_flow_layout_set_flow_direction(sButtonContainer, DJUI_FLOW_DIR_DOWN);
        {
            struct DjuiButton* button1 = djui_button_create(&sButtonContainer->base, "Host");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 1.0f, 64);

            struct DjuiButton* button2 = djui_button_create(&sButtonContainer->base, "Join");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 1.0f, 64);

            struct DjuiButton* button3 = djui_button_create(&sButtonContainer->base, "Options");
            djui_base_set_size_type(&button3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button3->base, 1.0f, 64);

            struct DjuiButton* button4 = djui_button_create(&sButtonContainer->base, "Quit");
            djui_base_set_size_type(&button4->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button4->base, 1.0f, 64);
            button4->base.interactable->on_click = djui_panel_quit_open;
        }

        //sTitleText = djui_text_create(&gPanelMainMenu->base, "SM64EX\nCOOP");
        sTitleText = djui_text_create(&gPanelMainMenu->base, "\\#ff0800\\SM\\#1be700\\64\\#00b3ff\\EX\n\\#ffef00\\COOP");
        djui_base_set_alignment(&sTitleText->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_size_type(&sTitleText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sTitleText->base, 1.0f, 1.0f);
        djui_base_set_color(&sTitleText->base, 255, 8, 0, 255);
        djui_text_set_alignment(sTitleText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_text_set_font(sTitleText, &gDjuiFonts[1]);
        djui_text_set_font_scale(sTitleText, gDjuiFonts[1].defaultFontScale);
        sTitleText->base.on_render_pre = djui_panel_main_render_pre;

        sVersionText = djui_text_create(&gPanelMainMenu->base, "version - unst 5");
        djui_base_set_alignment(&sVersionText->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
        djui_base_set_size_type(&sVersionText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sVersionText->base, 1.0f, 1.0f);
        djui_base_set_color(&sVersionText->base, 50, 50, 50, 255);
        djui_text_set_alignment(sVersionText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    }
}
