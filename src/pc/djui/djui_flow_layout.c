#include "djui.h"

bool (*gDjuiFlowLayoutScrollRender)(struct DjuiBase*) = NULL;

  ////////////////
 // properties //
////////////////

void djui_flow_layout_set_flow_direction(struct DjuiFlowLayout* layout, enum DjuiFlowDirection flowDirection) {
    layout->flowDirection = flowDirection;
}

void djui_flow_layout_set_margin(struct DjuiFlowLayout* layout, f32 margin) {
    layout->margin.value = margin;
}

void djui_flow_layout_set_margin_type(struct DjuiFlowLayout* layout, enum DjuiScreenValueType marginType) {
    layout->margin.type = marginType;
}

  ////////////
 // events //
////////////

static void djui_flow_layout_on_child_render(struct DjuiBase* base, struct DjuiBase* child) {
    if (!child->visible) { return; }
    struct DjuiFlowLayout* layout = (struct DjuiFlowLayout*)base;
    switch (layout->flowDirection) {
        case DJUI_FLOW_DIR_DOWN:
            base->comp.y      += (child->elem.height + layout->margin.value);
            base->comp.height -= (child->elem.height + layout->margin.value);
            break;
        case DJUI_FLOW_DIR_UP:
            base->comp.height -= (child->elem.height + layout->margin.value);
            break;
        case DJUI_FLOW_DIR_RIGHT:
            base->comp.x     += (child->elem.width + layout->margin.value);
            base->comp.width -= (child->elem.width + layout->margin.value);
            break;
        case DJUI_FLOW_DIR_LEFT:
            base->comp.width -= (child->elem.width + layout->margin.value);
            break;
    }
}

  ////////////
 // scroll //
////////////

static bool djui_flow_layout_scroll_render(struct DjuiBase* base) {
    struct DjuiFlowLayout* layout = (struct DjuiFlowLayout*)base;

    // draw background
    djui_rect_render(base);

    // compute content height from visible children
    f32 contentHeight = layout->margin.value;
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        if (child->base->visible) {
            contentHeight += child->base->height.value + layout->margin.value;
        }
        child = child->next;
    }
    layout->contentHeight = contentHeight;

    // clamp scroll
    f32 maxScroll = contentHeight - base->elem.height - 32;
    if (maxScroll < 0) { maxScroll = 0; }
    if (layout->scrollY < 0) { layout->scrollY = 0; }
    if (layout->scrollY > maxScroll) { layout->scrollY = maxScroll; }

    // shift comp so children render scrolled
    base->comp.y -= layout->scrollY;

    // draw scrollbar indicator
    if (maxScroll > 0) {
        struct DjuiBaseRect* clip = &base->clip;
        f32 thumbRatio = clip->height / contentHeight;
        f32 thumbH = clip->height * thumbRatio;
        if (thumbH < 20) { thumbH = 20; }
        f32 thumbY = clip->y + (layout->scrollY / maxScroll) * (clip->height - thumbH);
        f32 thumbX = clip->x + clip->width + 6;

        f32 tX = thumbX, tY = thumbY;
        djui_gfx_position_translate(&tX, &tY);
        create_dl_translation_matrix(DJUI_MTX_PUSH, tX, tY, 0);

        f32 tW = 4, tH = thumbH;
        djui_gfx_scale_translate(&tW, &tH);
        create_dl_scale_matrix(DJUI_MTX_NOPUSH, tW, tH, 1.0f);

        gDPSetEnvColor(gDisplayListHead++, 200, 200, 200, 128);
        gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);
        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }

    return true;
}

static void djui_flow_layout_on_scroll(struct DjuiBase* base, float x, float y) {
    UNUSED f32 unused = x;
    struct DjuiFlowLayout* layout = (struct DjuiFlowLayout*)base;
    layout->scrollY -= y * 48.0f;
}

static void flow_scroll_begin(struct DjuiBase* base, UNUSED bool inputCursor) {
    struct DjuiFlowLayout* layout = (struct DjuiFlowLayout*)base;
    layout->touchStartY = gCursorY;
}

static void flow_scroll_update(struct DjuiBase* base) {
    struct DjuiFlowLayout* layout = (struct DjuiFlowLayout*)base;
    f32 delta = layout->touchStartY - gCursorY;
    layout->scrollY += delta;
    layout->touchStartY = gCursorY;
}

static void flow_scroll_end(UNUSED struct DjuiBase* base) {}

void djui_flow_layout_enable_scroll(struct DjuiFlowLayout* layout) {
    layout->scrollEnabled = true;
    layout->scrollY = 0;
    layout->base.render = djui_flow_layout_scroll_render;
    layout->base.abandonAfterChildRenderFail = false;

    if (!gDjuiFlowLayoutScrollRender) {
        gDjuiFlowLayoutScrollRender = djui_flow_layout_scroll_render;
    }

    djui_interactable_create(&layout->base, NULL);
    djui_interactable_hook_scroll(&layout->base, djui_flow_layout_on_scroll);
    djui_interactable_hook_cursor_down(&layout->base,
        flow_scroll_begin, flow_scroll_update, flow_scroll_end);
}

static void djui_flow_layout_destroy(struct DjuiBase* base) {
    struct DjuiFlowLayout* layout = (struct DjuiFlowLayout*)base;
    free(layout);
}

struct DjuiFlowLayout* djui_flow_layout_create(struct DjuiBase* parent) {
    struct DjuiFlowLayout* layout = calloc(1, sizeof(struct DjuiFlowLayout));
    struct DjuiBase* base         = &layout->base;

    djui_base_init(parent, base, djui_rect_render, djui_flow_layout_destroy);
    djui_base_set_size(base, 256, 512);

    djui_flow_layout_set_flow_direction(layout, DJUI_FLOW_DIR_DOWN);
    djui_flow_layout_set_margin(layout, 8);

    layout->base.on_child_render = djui_flow_layout_on_child_render;
    return layout;
}
