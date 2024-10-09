#pragma once
#include "djui.h"

struct DjuiThreePanel {
    struct DjuiBase base;
    struct DjuiScreenValue minHeaderSize;
    struct DjuiScreenValue bodySize;
    struct DjuiScreenValue minFooterSize;
    bool temporary;
    bool (*on_back)(struct DjuiBase*);
};

struct DjuiBase* djui_three_panel_get_header(struct DjuiThreePanel* threePanel);
struct DjuiBase* djui_three_panel_get_body(struct DjuiThreePanel* threePanel);
struct DjuiBase* djui_three_panel_get_footer(struct DjuiThreePanel* threePanel);

void djui_three_panel_set_min_header_size_type(struct DjuiThreePanel* threePanel, enum DjuiScreenValueType minHeaderSizeType);
void djui_three_panel_set_min_header_size(struct DjuiThreePanel* threePanel, f32 minHeaderSize);
void djui_three_panel_set_body_size_type(struct DjuiThreePanel* threePanel, enum DjuiScreenValueType bodySizeType);
void djui_three_panel_set_body_size(struct DjuiThreePanel* threePanel, f32 bodySize);
void djui_three_panel_set_min_footer_size_type(struct DjuiThreePanel* threePanel, enum DjuiScreenValueType minFooterSizeType);
void djui_three_panel_set_min_footer_size(struct DjuiThreePanel* threePanel, f32 minFooterSize);
void djui_three_panel_recalculate_body_size(struct DjuiThreePanel* threePanel);

struct DjuiThreePanel* djui_three_panel_create(struct DjuiBase* parent, f32 minHeaderSize, f32 bodySize, f32 minFooterSize);
