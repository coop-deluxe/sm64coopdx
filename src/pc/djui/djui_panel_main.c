#include "djui.h"

ALIGNED8 static u8 texture_title[] = {
#include "textures/segment2/custom_title.rgba32.inc.c"
};

struct DjuiRect* sTitleContainer = NULL;
struct DjuiFlowLayout* sButtonContainer = NULL;
struct DjuiText* sVersionText = NULL;

static void djui_panel_main_render_pre(struct DjuiBase* base) {
    sTitleContainer->base.height.value = sButtonContainer->base.clip.y - sTitleContainer->base.clip.y;
    sVersionText->base.height.value = sTitleContainer->base.height.value;
}

void djui_panel_main_create(void) {
    struct DjuiRect* menuContainer = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_size_type(&menuContainer->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&menuContainer->base, 512.0f + (16 * 2.0f), 1.0f);
    djui_base_set_color(&menuContainer->base, 0, 0, 0, 230);
    djui_base_set_border_color(&menuContainer->base, 0, 0, 0, 200);
    djui_base_set_border_width(&menuContainer->base, 8);
    djui_base_set_padding(&menuContainer->base, 16, 16, 16, 16);
    {
        sButtonContainer = djui_flow_layout_create(&menuContainer->base);
        djui_base_set_alignment(&sButtonContainer->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        djui_base_set_size_type(&sButtonContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sButtonContainer->base, 1.0f, 292);
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
        }

        sTitleContainer = djui_rect_create(&menuContainer->base);
        djui_base_set_size_type(&sTitleContainer->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sTitleContainer->base, 1.0f, 1.0f);
        djui_base_set_color(&sTitleContainer->base, 0, 0, 0, 0);
        sTitleContainer->base.on_render_pre = djui_panel_main_render_pre;
        {
            struct DjuiImage* title = djui_image_create(&sTitleContainer->base, texture_title, 512, 128, 32);
            djui_base_set_size(&title->base, 1.0f, 128.0f / 512.0f);
            djui_base_set_size_type(&title->base, DJUI_SVT_RELATIVE, DJUI_SVT_ASPECT_RATIO);
            djui_base_set_alignment(&title->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
        }

        sVersionText = djui_text_create(&menuContainer->base, "version - unst 5");
        djui_base_set_alignment(&sVersionText->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
        djui_base_set_size_type(&sVersionText->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&sVersionText->base, 1.0f, 1.0f);
        djui_base_set_color(&sVersionText->base, 50, 50, 50, 255);
        djui_text_set_alignment(sVersionText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    }

}
