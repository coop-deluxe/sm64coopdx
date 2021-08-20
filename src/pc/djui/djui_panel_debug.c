#include "djui.h"

static struct DjuiRect* sDjuiRect = NULL;
static struct DjuiText* sDjuiText = NULL;

static struct DjuiRect* sDjuiRect2 = NULL;
static struct DjuiText* sDjuiText2 = NULL;

static void djui_panel_debug_render_pre(UNUSED struct DjuiBase* base, UNUSED bool* skipRender) {
    static u32 sTimer = 0;
    sTimer++;
    if (sDjuiText != NULL) {
        djui_base_set_location(&sDjuiText->base,
            32.0f + cos(sTimer / 20.0f) * 100.0f,
            32.0f + sin(sTimer / 62.0f) * 50.0f);
        djui_text_set_font_scale(sDjuiText, 16.0f + sin((sTimer) / 72.0f) * 4.0f);
    }

    if (sDjuiText2 != NULL) {
        djui_base_set_location(&sDjuiText2->base,
            32.0f + cos(sTimer / 20.0f) * 100.0f,
            32.0f + sin(sTimer / 62.0f) * 100.0f);
        djui_text_set_font_scale(sDjuiText2, 64.0f + sin((sTimer) / 72.0f) * 8.0f);
    }
}

void djui_panel_debug_create(void) {
    sDjuiRect = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_location(&sDjuiRect->base, 64, 64);
    djui_base_set_size(&sDjuiRect->base, 300, 100);
    djui_base_set_color(&sDjuiRect->base, 0, 0, 0, 255);
    djui_base_set_alignment(&sDjuiRect->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
    sDjuiRect->base.on_render_pre = djui_panel_debug_render_pre;

    sDjuiText = djui_text_create(&sDjuiRect->base, "hello\nworld");
    djui_base_set_location(&sDjuiText->base, 0, 0);
    djui_base_set_size(&sDjuiText->base, 300, 300);
    djui_base_set_color(&sDjuiText->base, 255, 255, 255, 255);
    djui_text_set_drop_shadow(sDjuiText, 255, 0, 0, 255);
    djui_text_set_alignment(sDjuiText, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

    sDjuiRect2 = djui_rect_create(&gDjuiRoot->base);
    djui_base_set_location(&sDjuiRect2->base, 64, 64);
    djui_base_set_size(&sDjuiRect2->base, 300, 100);
    djui_base_set_color(&sDjuiRect2->base, 100, 100, 100, 255);
    djui_base_set_alignment(&sDjuiRect2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_BOTTOM);

    sDjuiText2 = djui_text_create(&sDjuiRect2->base, "hello\nworld");
    djui_base_set_location(&sDjuiText2->base, 0, 0);
    djui_base_set_size(&sDjuiText2->base, 400, 400);
    djui_base_set_color(&sDjuiText2->base, 255, 255, 255, 255);
    djui_text_set_drop_shadow(sDjuiText2, 255, 0, 0, 255);
    djui_text_set_alignment(sDjuiText2, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    djui_text_set_font(sDjuiText2, gDjuiFonts[1]);

    struct DjuiText* alphabet = djui_text_create(&gDjuiRoot->base, "abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n01234567890\nthe quick brown fox jumps over the lazy dog\ngeqkbnfjsortelydg\nTHE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\nGEQKBNFJSORTELYDG");
    djui_base_set_location(&alphabet->base, 0, 0);
    djui_base_set_size(&alphabet->base, 400, 400);
    djui_base_set_size_type(&alphabet->base, DJUI_SVT_RELATIVE, DJUI_SVT_RELATIVE);
    djui_base_set_size(&alphabet->base, 1, 1);
    djui_base_set_color(&alphabet->base, 255, 255, 255, 255);
    djui_text_set_drop_shadow(alphabet, 255, 0, 0, 255);
    djui_text_set_alignment(alphabet, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_text_set_font(alphabet, gDjuiFonts[1]);
    djui_text_set_font_scale(alphabet, 64);
}
