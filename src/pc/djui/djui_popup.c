#include "djui.h"
#include "sounds.h"
#include "audio/external.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "djui_hud_utils.h"

#define DJUI_POPUP_WIDTH 400.0f
#define DJUI_POPUP_LIFETIME 6.0f

struct DjuiPopupList {
    struct DjuiPopup* popup;
    f32 createTime;
    struct DjuiPopupList* next;
};

static struct DjuiPopupList* sPopupListHead = NULL;
static f32 sPopupListY = 0;

static void djui_popup_add_to_list(struct DjuiPopup* popup) {
    struct DjuiPopupList* node = calloc(1, sizeof(struct DjuiPopupList));
    node->popup = popup;
    node->createTime = clock_elapsed();
    node->next = sPopupListHead;
    sPopupListHead = node;
}

static bool djui_popup_render(struct DjuiBase* base) {
    djui_rect_render(base);
    return true;
}

static void djui_popup_destroy(struct DjuiBase* base) {
    struct DjuiPopup* popup = (struct DjuiPopup*)base;
    free(popup);
}

static void djui_popup_create_internal(const char* message, int lines, int paddingLines) {
    if (djui_is_popup_disabled()) { return; }
    if (paddingLines < 0) paddingLines = 0;
    struct DjuiPopup* popup = calloc(1, sizeof(struct DjuiPopup));
    struct DjuiBase* base = &popup->base;

    f32 height = (lines + paddingLines) * 32 + 32;
    djui_base_init(&gDjuiRoot->base, base, djui_popup_render, djui_popup_destroy);
    djui_base_set_alignment(base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
    djui_base_set_location(base, 8, -height);
    djui_base_set_size(base, DJUI_POPUP_WIDTH, height);
    djui_base_set_border_width(base, 4);
    djui_base_set_color(base, 0, 0, 0, 220);
    djui_base_set_border_color(base, 0, 0, 0, 180);

    struct DjuiText* text = djui_text_create(base, message);
    djui_base_set_alignment(&text->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
    djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&text->base, 1.0f, lines * 32.0f);
    djui_base_set_color(&text->base, 220, 220, 220, 255);
    djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
    djui_text_set_drop_shadow(text, 0, 0, 0, 64);
    popup->text = text;

    sPopupListY -= height + 4;
    djui_popup_add_to_list(popup);
    play_sound(SOUND_MENU_PINCH_MARIO_FACE, gGlobalSoundSource);
}

void djui_popup_create(const char* message, int lines) {
    int linesReq = (int)ceilf(djui_hud_measure_text(str_remove_color_codes(message)) / DJUI_POPUP_WIDTH);
    if (linesReq < 1) linesReq = 1;
    if (linesReq > lines) linesReq = lines;
    djui_popup_create_internal(message, linesReq, lines - linesReq);
}

void djui_popup_create_auto_scaling(const char* message, int paddingLines) {
    int linesReq = (int)ceilf(djui_hud_measure_text(str_remove_color_codes(message)) / DJUI_POPUP_WIDTH);
    if (linesReq < 1) linesReq = 1;
    djui_popup_create_internal(message, linesReq, paddingLines);
}

void djui_popup_update(void) {
    struct DjuiPopupList* node = sPopupListHead;
    struct DjuiPopupList* last = NULL;
    f32 y = sPopupListY;

    while (node != NULL) {
        struct DjuiPopupList* next = node->next;
        djui_base_set_location(&node->popup->base, 4, y);
        y += node->popup->base.height.value + 4;
        f32 elapsed = (clock_elapsed() - node->createTime);

        // fade out
        f32 alpha = fmin(DJUI_POPUP_LIFETIME - elapsed, 1.0f);
        alpha *= alpha;
        if (elapsed > DJUI_POPUP_LIFETIME) { alpha = 0; }
        djui_base_set_color(&node->popup->base, 0, 0, 0, 220 * alpha);
        djui_base_set_border_color(&node->popup->base, 0, 0, 0, 180 * alpha);
        djui_base_set_color(&node->popup->text->base, 220, 220, 220, 255 * alpha);
        djui_text_set_drop_shadow(node->popup->text, 0, 0, 0, 64 * alpha);

        // remove/deallocate popup
        if (alpha == 0) {
            if (last != NULL) { last->next = next; }
            if (node == sPopupListHead) { sPopupListHead = next; }
            djui_base_destroy(&node->popup->base);
            free(node);
            node = next;
            continue;
        }

        // iterate
        last = node;
        node = next;
    }

    // move entire popup list
    sPopupListY = sPopupListY * 0.75f + 1;
    if (sPopupListY > 4) { sPopupListY = 4; }
}