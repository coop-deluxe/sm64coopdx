#include "djui.h"

struct DjuiBase* djui_three_panel_get_header(struct DjuiThreePanel* threePanel) {
    struct DjuiBase* children[3] = { NULL };
    struct DjuiBaseChild* child = threePanel->base.child;
    for (int i = 0; i < 3; i++) {
        if (child == NULL || child->base == NULL) { break; }
        children[i] = child->base;
        child = child->next;
    }
    return children[0];
}

struct DjuiBase* djui_three_panel_get_body(struct DjuiThreePanel* threePanel) {
    struct DjuiBase* children[3] = { NULL };
    struct DjuiBaseChild* child = threePanel->base.child;
    for (int i = 0; i < 3; i++) {
        if (child == NULL || child->base == NULL) { break; }
        children[i] = child->base;
        child = child->next;
    }
    return children[1];
}

struct DjuiBase* djui_three_panel_get_footer(struct DjuiThreePanel* threePanel) {
    struct DjuiBase* children[3] = { NULL };
    struct DjuiBaseChild* child = threePanel->base.child;
    for (int i = 0; i < 3; i++) {
        if (child == NULL || child->base == NULL) { break; }
        children[i] = child->base;
        child = child->next;
    }
    return children[2];
}

void djui_three_panel_set_min_header_size_type(struct DjuiThreePanel* threePanel, enum DjuiScreenValueType minHeaderSizeType) {
    threePanel->minHeaderSize.type = minHeaderSizeType;
}

void djui_three_panel_set_min_header_size(struct DjuiThreePanel* threePanel, f32 minHeaderSize) {
    threePanel->minHeaderSize.value = minHeaderSize;
}

void djui_three_panel_set_body_size_type(struct DjuiThreePanel* threePanel, enum DjuiScreenValueType bodySizeType) {
    threePanel->bodySize.type = bodySizeType;
}

void djui_three_panel_set_body_size(struct DjuiThreePanel* threePanel, f32 bodySize) {
    threePanel->bodySize.value = bodySize;
}

void djui_three_panel_set_min_footer_size_type(struct DjuiThreePanel* threePanel, enum DjuiScreenValueType minFooterSizeType) {
    threePanel->minFooterSize.type = minFooterSizeType;
}

void djui_three_panel_set_min_footer_size(struct DjuiThreePanel* threePanel, f32 minFooterSize) {
    threePanel->minFooterSize.value = minFooterSize;
}

void djui_three_panel_recalculate_body_size(struct DjuiThreePanel* threePanel) {
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(threePanel);
    struct DjuiBaseChild* child = body->base.child;

    if (threePanel->bodySize.value != 0) { return; }

    if (body->margin.type != DJUI_SVT_ABSOLUTE) {
        return;
    }

    f32 bodyHeight = body->margin.value;
    while (child != NULL) {
        bodyHeight += body->margin.value;
        bodyHeight += child->base->height.value;
        if (child->base->height.type != DJUI_SVT_ABSOLUTE) {
            return;
        }
        child = child->next;
    }
    if (bodyHeight < 0) { bodyHeight = 0; }
    djui_three_panel_set_body_size(threePanel, bodyHeight);
}

  ////////////
 // events //
////////////

bool djui_three_panel_render(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;

    struct DjuiBase* children[3] = { NULL };
    struct DjuiBaseChild* child = base->child;
    for (int i = 0; i < 3; i++) {
        if (child == NULL || child->base == NULL) { break; }
        children[i] = child->base;
        child = child->next;
    }

    struct DjuiBase* head = children[0];
    struct DjuiBase* body = children[1];
    struct DjuiBase* foot = children[2];

    if (body == NULL) { return false; }

    struct DjuiBaseRect* parentComp = &base->comp;
    f32 tPad = (base->padding.top.type == DJUI_SVT_RELATIVE)    ? parentComp->height * base->padding.top.value    : base->padding.top.value;
    f32 bPad = (base->padding.bottom.type == DJUI_SVT_RELATIVE) ? parentComp->height * base->padding.bottom.value : base->padding.bottom.value;

    f32 myHeight = base->comp.height - tPad - bPad;
    f32 minHeaderSize = (threePanel->minHeaderSize.type == DJUI_SVT_RELATIVE) ? base->comp.height * threePanel->minHeaderSize.value : threePanel->minHeaderSize.value;
    f32 minFooterSize = (threePanel->minFooterSize.type == DJUI_SVT_RELATIVE) ? base->comp.height * threePanel->minFooterSize.value : threePanel->minFooterSize.value;
    f32 largestMinSize = fmax(minHeaderSize, minFooterSize);

    f32 headerSize = minHeaderSize;
    f32 bodySize   = (threePanel->bodySize.type == DJUI_SVT_RELATIVE) ? base->comp.height * threePanel->bodySize.value : threePanel->bodySize.value;
    f32 footerSize = minFooterSize;

    if (minHeaderSize + minFooterSize >= myHeight) {
        bodySize = 0;
        headerSize = myHeight * (minHeaderSize / (minHeaderSize + minFooterSize));
        footerSize = myHeight * (minFooterSize / (minHeaderSize + minFooterSize));
    } else if (minHeaderSize + bodySize + minFooterSize >= myHeight) {
        bodySize = myHeight - headerSize - footerSize;
    } else if (largestMinSize * 2.0f + bodySize >= myHeight) {
        if (minHeaderSize > minFooterSize) {
            footerSize = myHeight - headerSize - bodySize;
        } else {
            headerSize = myHeight - footerSize - bodySize;
        }
    } else {
        headerSize = (myHeight - bodySize) / 2.0f;
        footerSize = (myHeight - bodySize) / 2.0f;
    }

    if (head != NULL) {
        //djui_base_set_location_type(head, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        //djui_base_set_location(head, 0, 0);
        djui_base_set_size_type(head, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(head, 1.0f, headerSize);
        djui_base_set_alignment(head, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    }

    if (body != NULL) {
        djui_base_set_location_type(body, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_location(body, 0, headerSize);
        djui_base_set_size_type(body, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(body, 1.0f, bodySize);
        djui_base_set_alignment(body, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    }

    if (foot != NULL) {
        djui_base_set_location_type(foot, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
        djui_base_set_location(foot, 0, headerSize + bodySize);
        djui_base_set_size_type(foot, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(foot, 1.0f, footerSize);
        djui_base_set_alignment(foot, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
    }

    djui_rect_render(base);
    return true;
}

static void djui_three_panel_destroy(struct DjuiBase* base) {
    struct DjuiThreePanel* threePanel = (struct DjuiThreePanel*)base;
    free(threePanel);
}

struct DjuiThreePanel* djui_three_panel_create(struct DjuiBase* parent, f32 minHeaderSize, f32 bodySize, f32 minFooterSize) {
    struct DjuiThreePanel* threePanel = calloc(1, sizeof(struct DjuiThreePanel));
    struct DjuiBase* base = &threePanel->base;

    djui_base_init(parent, base, djui_three_panel_render, djui_three_panel_destroy);
    djui_three_panel_set_min_header_size(threePanel, minHeaderSize);
    djui_three_panel_set_body_size(threePanel, bodySize);
    djui_three_panel_set_min_footer_size(threePanel, minFooterSize);

    return threePanel;
}
