#pragma once
#include "djui.h"

struct DjuiFlowLayout {
    struct DjuiBase base;
    enum DjuiFlowDirection flowDirection;
    struct DjuiScreenValue margin;
    // Scroll
    bool scrollEnabled;
    f32  scrollY;
    f32  contentHeight;
    f32  touchStartY;
};

extern bool (*gDjuiFlowLayoutScrollRender)(struct DjuiBase*);

void djui_flow_layout_set_flow_direction(struct DjuiFlowLayout* layout, enum DjuiFlowDirection flowDirection);
void djui_flow_layout_set_margin(struct DjuiFlowLayout* layout, f32 margin);
void djui_flow_layout_set_margin_type(struct DjuiFlowLayout* layout, enum DjuiScreenValueType marginType);
void djui_flow_layout_enable_scroll(struct DjuiFlowLayout* layout);

struct DjuiFlowLayout* djui_flow_layout_create(struct DjuiBase* parent);
