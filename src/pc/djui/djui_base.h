#pragma once
#include "djui.h"

struct DjuiBaseRect {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
};

struct DjuiBaseChild {
    struct DjuiBase* base;
    struct DjuiBaseChild* next;
};

struct DjuiBasePadding {
    struct DjuiScreenValue top;
    struct DjuiScreenValue right;
    struct DjuiScreenValue bottom;
    struct DjuiScreenValue left;
};

struct DjuiBase {
    struct DjuiBase* parent;
    struct DjuiBaseChild* child;
    bool visible;
    bool enabled;
    struct DjuiScreenValue x;
    struct DjuiScreenValue y;
    struct DjuiScreenValue width;
    struct DjuiScreenValue height;
    struct DjuiColor color;
    struct DjuiScreenValue borderWidth;
    struct DjuiColor borderColor;
    struct DjuiBasePadding padding;
    enum DjuiHAlign hAlign;
    enum DjuiVAlign vAlign;
    struct DjuiBaseRect elem;
    struct DjuiBaseRect comp;
    struct DjuiBaseRect clip;
    struct DjuiInteractable* interactable;
    bool addChildrenToHead;
    bool abandonAfterChildRenderFail;
    bool gradient;
    s64 tag;
    bool bTag;
    void (*get_cursor_hover_location)(struct DjuiBase*, f32* x, f32* y);
    void (*on_child_render)(struct DjuiBase*, struct DjuiBase*);
    void (*on_render_pre)(struct DjuiBase*, bool*);
    bool (*render)(struct DjuiBase*);
    void (*destroy)(struct DjuiBase*);
};

void djui_base_set_visible(struct DjuiBase* base, bool visible);
void djui_base_set_enabled(struct DjuiBase* base, bool enabled);
void djui_base_set_location(struct DjuiBase* base, f32 x, f32 y);
void djui_base_set_location_type(struct DjuiBase* base, enum DjuiScreenValueType xType, enum DjuiScreenValueType yType);
void djui_base_set_size(struct DjuiBase* base, f32 width, f32 height);
void djui_base_set_size_type(struct DjuiBase* base, enum DjuiScreenValueType widthType, enum DjuiScreenValueType heightType);
void djui_base_set_color(struct DjuiBase* base, u8 r, u8 g, u8 b, u8 a);
void djui_base_set_border_width(struct DjuiBase* base, f32 width);
void djui_base_set_border_width_type(struct DjuiBase* base, enum DjuiScreenValueType widthType);
void djui_base_set_border_color(struct DjuiBase* base, u8 r, u8 g, u8 b, u8 a);
void djui_base_set_padding(struct DjuiBase* base, f32 top, f32 right, f32 bottom, f32 left);
void djui_base_set_padding_type(struct DjuiBase* base, enum DjuiScreenValueType topType, enum DjuiScreenValueType rightType, enum DjuiScreenValueType bottomType, enum DjuiScreenValueType leftType);
void djui_base_set_alignment(struct DjuiBase* base, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign);
void djui_base_set_gradient(struct DjuiBase* base, bool gradient);

void djui_base_compute(struct DjuiBase* base);
void djui_base_compute_tree(struct DjuiBase* base);

bool djui_base_render(struct DjuiBase* base);
void djui_base_destroy(struct DjuiBase* base);
void djui_base_destroy_children(struct DjuiBase* base);
void djui_base_destroy_one_child(struct DjuiBase* base);
void djui_base_init(struct DjuiBase* parent, struct DjuiBase* base, bool (*render)(struct DjuiBase*), void (*destroy)(struct DjuiBase*));
