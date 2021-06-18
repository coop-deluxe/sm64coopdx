#include "djui.h"

struct DjuiRoot* gDjuiRoot = NULL;

ALIGNED8 static const u8 texture32x32[] = {
#include "actors/bubble/mr_i_bubble.rgba16.inc.c"
};
ALIGNED8 static const u8 texture16x16[] = {
#include "textures/segment2/custom_luigi_head.rgba16.inc.c"
};

void djui_render(void) {
    static struct DjuiRect* sDjuiRect = NULL;
    static struct DjuiRect* sDjuiRect2 = NULL;
    static struct DjuiText* sDjuiText = NULL;
    static struct DjuiImage* sDjuiImage = NULL;
    static struct DjuiButton* sDjuiButton = NULL;

    if (gDjuiRoot == NULL) {
        gDjuiRoot = djui_root_create();

        struct DjuiRect* imageContainer = djui_rect_create(&gDjuiRoot->base);
        djui_base_set_location(&imageContainer->base, 32, 32);
        djui_base_set_size(&imageContainer->base, 64, 64);

        sDjuiImage = djui_image_create(&imageContainer->base, texture16x16, 16, 16);
        djui_base_set_location(&sDjuiImage->base, 16, 16);
        djui_base_set_size(&sDjuiImage->base, 32, 32);
        djui_base_set_color(&sDjuiImage->base, 255, 255, 255, 255);

        //////////////

        sDjuiRect = djui_rect_create(&gDjuiRoot->base);
        djui_base_set_location(&sDjuiRect->base, 64, 64);
        djui_base_set_size(&sDjuiRect->base, 188, 64);
        djui_base_set_color(&sDjuiRect->base, 255, 255, 255, 200);
        djui_base_set_alignment(&sDjuiRect->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);

        sDjuiRect2 = djui_rect_create(&sDjuiRect->base);
        djui_base_set_location(&sDjuiRect2->base, 0, 0);
        djui_base_set_size(&sDjuiRect2->base, 188 - 8, 64 - 8);
        djui_base_set_alignment(&sDjuiRect2->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        sDjuiText = djui_text_create(&sDjuiRect2->base, "Host");
        djui_base_set_location(&sDjuiText->base, 0, 0);
        djui_base_set_size(&sDjuiText->base, 188 - 8, 64 - 8);
        djui_base_set_color(&sDjuiText->base, 111, 111, 111, 255);
        djui_text_set_font_size(sDjuiText, 2);
        djui_text_set_alignment(sDjuiText, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);

        sDjuiButton = djui_button_create(&gDjuiRoot->base, "button");
        djui_base_set_alignment(&sDjuiButton->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_BOTTOM);
        djui_base_set_location(&sDjuiButton->base, 64, 64);
    }

    djui_base_render(&gDjuiRoot->base);
    
    if (sDjuiRect2 != NULL) {
        static u32 sTimer = 0;
        sTimer++;
        djui_base_set_location(&sDjuiImage->base,
            16.0f + cos((sTimer) / 10.0f) * 24.0f,
            16.0f + sin((sTimer) / 31.0f) * 24.0f);

        djui_base_set_color(&sDjuiImage->base, 
            127.0f + sin((sTimer) / 13.0f) * 127.0f,
            127.0f + sin((sTimer) / 17.0f) * 127.0f,
            127.0f + sin((sTimer) / 23.0f) * 127.0f,
            255);

        djui_base_set_location(&sDjuiRect2->base,
            32.0f + cos((sTimer) / 10.0f) * 64.0f,
            32.0f + sin((sTimer) / 31.0f) * 64.0f);

        djui_base_set_size(&sDjuiButton->base,
            200.0f + cos((sTimer) / 10.0f) * 64.0f,
            64.0f + sin((sTimer) / 10.0f) * 16.0f);
    }
}