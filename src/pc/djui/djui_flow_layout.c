#include "djui.h"

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
