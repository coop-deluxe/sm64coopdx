#include "djui.h"

  ////////////////
 // properties //
////////////////

  ////////////
 // events //
////////////

static bool lTrigDown = false;
static bool rTrigDown = false;

static struct DjuiButton* sPrevButton = NULL;
static struct DjuiButton* sNextButton = NULL;
static struct DjuiText* sPageNumText = NULL;

static s32 djui_paginated_get_count(struct DjuiPaginated* paginated) {
    s32 count = 0;
    struct DjuiBaseChild* dbc = paginated->layout->base.child;
    while (dbc != NULL) {
        count++;
        dbc = dbc->next;
    }

    return count;
}

void djui_paginated_update_page_buttons(struct DjuiPaginated* paginated) {
    s32 count = djui_paginated_get_count(paginated);
    paginated->startIndex = (MIN(paginated->startIndex, count) / paginated->showCount) * paginated->showCount;
    if (count != 0 && paginated->startIndex == count) { paginated->startIndex -= paginated->showCount; }

    char pageNumString[32] = { 0 };
    snprintf(pageNumString, 32, "%d/%d", paginated->startIndex / paginated->showCount + 1, (count - 1) / paginated->showCount + 1);
    djui_text_set_text(sPageNumText, pageNumString);
    djui_base_set_visible(&sPageNumText->base, (count > paginated->showCount));

    djui_base_set_enabled(&sPrevButton->base, (paginated->startIndex > 0));
    djui_base_set_enabled(&sNextButton->base, ((paginated->startIndex + paginated->showCount) < count));
}

static void djui_paginated_prev(struct DjuiBase* base) {
    struct DjuiPaginated* paginated = (struct DjuiPaginated*)base->parent;

    paginated->startIndex -= paginated->showCount;
    if (paginated->startIndex < 0) { paginated->startIndex = 0; }

    djui_paginated_update_page_buttons(paginated);
}

static void djui_paginated_next(struct DjuiBase* base) {
    struct DjuiPaginated* paginated = (struct DjuiPaginated*)base->parent;

    s32 count = djui_paginated_get_count(paginated);
    paginated->startIndex += paginated->showCount;
    if (paginated->startIndex >= count) { paginated->startIndex -= paginated->showCount; }

    djui_paginated_update_page_buttons(paginated);
}

void djui_paginated_calculate_height(struct DjuiPaginated* paginated) {
    struct DjuiBaseChild* dbc = paginated->layout->base.child;

    f32 height = 0;
    s32 count = 0;

    if (paginated->showMaxCount) {
        height = paginated->showCount * (32 + paginated->layout->margin.value);
        count = paginated->showCount + 1;
    } else {
        while (dbc != NULL) {
            struct DjuiBase* cbase = dbc->base;
            if (count < paginated->showCount) {
                if (height != 0) {
                    height += paginated->layout->margin.value;
                }
                height += cbase->height.value;
            }
            count++;
            dbc = dbc->next;
        }
    }

    if (count <= paginated->showCount) {
        djui_base_set_visible(&paginated->prevButton->base, false);
        djui_base_set_visible(&paginated->nextButton->base, false);
    } else {
        djui_base_set_visible(&paginated->prevButton->base, true);
        djui_base_set_visible(&paginated->nextButton->base, true);
        height += paginated->layout->margin.value;
        height += paginated->nextButton->base.height.value;
    }

    djui_base_set_size(&paginated->base, paginated->base.width.value, height);
    djui_paginated_update_page_buttons(paginated);
}

bool djui_paginated_render(struct DjuiBase* base) {
    struct DjuiPaginated* paginated = (struct DjuiPaginated*)base;
    struct DjuiBaseChild* dbc = paginated->layout->base.child;

    s32 index = 0;
    s32 shown = 0;

    while (dbc != NULL) {
        struct DjuiBase* cbase = dbc->base;
        if (index < paginated->startIndex || shown >= paginated->showCount) {
            djui_base_set_visible(cbase, false);
        } else {
            djui_base_set_visible(cbase, true);
            shown++;
        }
        index++;
        dbc = dbc->next;
    }

    djui_rect_render(base);

    OSContPad* pad = &gInteractablePad;

    if (pad->button & L_TRIG) {
        lTrigDown = true;
    } else if (pad->button & R_TRIG) {
        rTrigDown = true;
    } else if (lTrigDown) {
        djui_paginated_prev(&paginated->prevButton->base);
        lTrigDown = false;
    } else if (rTrigDown) {
        djui_paginated_next(&paginated->nextButton->base);
        rTrigDown = false;
    }

    return true;
}

static void djui_paginated_destroy(struct DjuiBase* base) {
    struct DjuiPaginated* paginated = (struct DjuiPaginated*)base;
    free(paginated);
}

struct DjuiPaginated* djui_paginated_create(struct DjuiBase* parent, u32 showCount) {
    struct DjuiPaginated* paginated = calloc(1, sizeof(struct DjuiPaginated));
    paginated->showCount = showCount;
    struct DjuiBase* base = &paginated->base;

    float bodyHeight = 416;

    djui_base_init(parent, base, djui_paginated_render, djui_paginated_destroy);
    djui_base_set_size_type(base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 1.0, bodyHeight);
    djui_base_set_color(base, 0, 64, 0, 0);
    djui_base_set_alignment(base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

    {
        struct DjuiFlowLayout* layout = djui_flow_layout_create(base);
        djui_base_set_alignment(&layout->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
        djui_base_set_location(&layout->base, 0, 0);
        djui_base_set_size_type(&layout->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&layout->base, 1.0f, bodyHeight);
        djui_base_set_color(&layout->base, 0, 0, 0, 0);
        djui_flow_layout_set_margin(layout, 16);
        djui_flow_layout_set_flow_direction(layout, DJUI_FLOW_DIR_DOWN);
        paginated->layout = layout;
    }

    sPrevButton = djui_button_create(&paginated->base, "<", DJUI_BUTTON_STYLE_NORMAL, djui_paginated_prev);
    djui_base_set_alignment(&sPrevButton->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_base_set_size_type(&sPrevButton->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&sPrevButton->base, 128, 32);
    djui_base_set_enabled(&sPrevButton->base, false);
    paginated->prevButton = sPrevButton;

    sPageNumText = djui_text_create(&paginated->base, "");
    djui_base_set_color(&sPageNumText->base, 220, 220, 220, 255);
    djui_base_set_alignment(&sPageNumText->base, DJUI_HALIGN_CENTER, DJUI_VALIGN_BOTTOM);
    djui_text_set_alignment(sPageNumText, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);
    djui_text_set_drop_shadow(sPageNumText, 64, 64, 64, 100);
    sPageNumText->base.y.value -= 30;
    sPageNumText->base.width.value += 30;

    sNextButton = djui_button_create(&paginated->base, ">", DJUI_BUTTON_STYLE_NORMAL, djui_paginated_next);
    djui_base_set_alignment(&sNextButton->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_BOTTOM);
    djui_base_set_size_type(&sNextButton->base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(&sNextButton->base, 128, 32);
    paginated->nextButton = sNextButton;

    djui_paginated_update_page_buttons(paginated);

    return paginated;
}
