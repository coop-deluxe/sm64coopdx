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
        imageContainer->base.x      = 32;
        imageContainer->base.y      = 32;
        imageContainer->base.width  = 64;
        imageContainer->base.height = 64;

        sDjuiImage = djui_image_create(&imageContainer->base, texture16x16, 16, 16);
        sDjuiImage->base.x = 16;
        sDjuiImage->base.y = 16;
        sDjuiImage->base.width  = 32;
        sDjuiImage->base.height = 32;
        sDjuiImage->base.color.r = 255;

        //////////////

        sDjuiRect = djui_rect_create(&gDjuiRoot->base);
        sDjuiRect->base.x = 64;
        sDjuiRect->base.y = 64;
        sDjuiRect->base.width = 188;
        sDjuiRect->base.height = 64;
        sDjuiRect->base.color.a = 200;
        sDjuiRect->base.hAlign = DJUI_HALIGN_LEFT;
        sDjuiRect->base.vAlign = DJUI_VALIGN_BOTTOM;

        sDjuiRect2 = djui_rect_create(&sDjuiRect->base);
        sDjuiRect2->base.x = 0;
        sDjuiRect2->base.y = 0;
        //sDjuiRect2->base.color.r = 0;
        sDjuiRect2->base.hAlign = DJUI_HALIGN_CENTER;
        sDjuiRect2->base.vAlign = DJUI_VALIGN_CENTER;
        sDjuiRect2->base.color.a = 255;
        sDjuiRect2->base.width = 188 - 8;
        sDjuiRect2->base.height = 64 - 8;

        sDjuiText = djui_text_create(&sDjuiRect2->base, "Host");
        sDjuiText->base.color.r = 111;
        sDjuiText->base.color.g = 111;
        sDjuiText->base.color.b = 111;
        sDjuiText->fontSize = 2;
        sDjuiText->base.color.a = 255;
        sDjuiText->base.width = 188 - 8;
        sDjuiText->base.height = 64 - 8;
        sDjuiText->base.x = 0;
        sDjuiText->base.y = 0;
        sDjuiText->textHAlign = DJUI_HALIGN_CENTER;
        sDjuiText->textVAlign = DJUI_VALIGN_CENTER;

        sDjuiButton = djui_button_create(&gDjuiRoot->base, "button");
    }

    djui_base_render(&gDjuiRoot->base);
    
    if (sDjuiRect2 != NULL) {
        static u32 sTimer = 0;
        sTimer++;
        sDjuiImage->base.x = 16.0f + cos((sTimer) / 10.0f) * 24.0f;
        sDjuiImage->base.y = 16.0f + sin((sTimer) / 31.0f) * 24.0f;
        sDjuiImage->base.color.r = 127.0 + sin((sTimer) / 13.0f) * 127.0f;
        sDjuiImage->base.color.g = 127.0 + sin((sTimer) / 17.0f) * 127.0f;
        sDjuiImage->base.color.b = 127.0 + sin((sTimer) / 23.0f) * 127.0f;

        sDjuiRect2->base.x = 32.0f + cos((sTimer) / 10.0f) * 64.0f;
        sDjuiRect2->base.y = 32.0f + sin((sTimer) / 31.0f) * 64.0f;

        sDjuiButton->base.width = 200 + cos((sTimer) / 10.0f) * 64.0f;
        sDjuiButton->base.height = 64 + sin((sTimer) / 10.0f) * 16.0f;
    }
}