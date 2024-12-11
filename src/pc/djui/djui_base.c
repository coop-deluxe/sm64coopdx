#include <string.h>
#include "djui.h"
#include "djui_interactable.h"

  ////////////////
 // properties //
////////////////

void djui_base_set_visible(struct DjuiBase* base, bool visible) {
    if (!base) { return; }
    base->visible = visible;
}

void djui_base_set_enabled(struct DjuiBase* base, bool enabled) {
    base->enabled = enabled;
    if (base->interactable != NULL && base->interactable->on_enabled_change != NULL) {
        base->interactable->on_enabled_change(base);
    }
    if (base->interactable != NULL && base->interactable->update_style != NULL) {
        base->interactable->update_style(base);
    }
}

void djui_base_set_location(struct DjuiBase* base, f32 x, f32 y) {
    base->x.value = x;
    base->y.value = y;
}

void djui_base_set_location_type(struct DjuiBase* base, enum DjuiScreenValueType xType, enum DjuiScreenValueType yType) {
    base->x.type = xType;
    base->y.type = yType;
}

void djui_base_set_size(struct DjuiBase* base, f32 width, f32 height) {
    base->width.value  = width;
    base->height.value = height;
}

void djui_base_set_size_type(struct DjuiBase* base, enum DjuiScreenValueType widthType, enum DjuiScreenValueType heightType) {
    base->width.type  = widthType;
    base->height.type = heightType;
}

void djui_base_set_color(struct DjuiBase* base, u8 r, u8 g, u8 b, u8 a) {
    base->color.r = r;
    base->color.g = g;
    base->color.b = b;
    base->color.a = a;
}

void djui_base_set_border_width(struct DjuiBase* base, f32 width) {
    base->borderWidth.value = width;
}

void djui_base_set_border_width_type(struct DjuiBase* base, enum DjuiScreenValueType widthType) {
    base->borderWidth.type = widthType;
}

void djui_base_set_border_color(struct DjuiBase* base, u8 r, u8 g, u8 b, u8 a) {
    base->borderColor.r = r;
    base->borderColor.g = g;
    base->borderColor.b = b;
    base->borderColor.a = a;
}

void djui_base_set_padding(struct DjuiBase* base, f32 top, f32 right, f32 bottom, f32 left) {
    base->padding.top.value    = top;
    base->padding.right.value  = right;
    base->padding.bottom.value = bottom;
    base->padding.left.value   = left;
}

void djui_base_set_padding_type(struct DjuiBase* base, enum DjuiScreenValueType topType, enum DjuiScreenValueType rightType, enum DjuiScreenValueType bottomType, enum DjuiScreenValueType leftType) {
    base->padding.top.type    = topType;
    base->padding.right.type  = rightType;
    base->padding.bottom.type = bottomType;
    base->padding.left.type   = leftType;
}

void djui_base_set_alignment(struct DjuiBase* base, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign) {
    base->hAlign = hAlign;
    base->vAlign = vAlign;
}

  /////////////
 // utility //
/////////////

static void djui_base_get_cursor_hover_location(struct DjuiBase* base, f32* x, f32* y) {
    *x = (base->elem.x + base->elem.width  * 3.0f / 4.0f);
    *y = (base->elem.y + base->elem.height * 3.0f / 4.0f);
}

static void djui_base_clip(struct DjuiBase* base) {
    struct DjuiBase* parent = base->parent;
    struct DjuiBaseRect* comp = &base->comp;
    struct DjuiBaseRect* clip = &base->clip;

    clip->x      = comp->x;
    clip->y      = comp->y;
    clip->width  = comp->width;
    clip->height = comp->height;

    if (parent == NULL) { return; }

    clip->x = fmax(clip->x, parent->clip.x);
    clip->y = fmax(clip->y, parent->clip.y);

    clip->width  = (comp->x + comp->width)  - clip->x;
    clip->height = (comp->y + comp->height) - clip->y;

    clip->width  = fmin(clip->width,  (parent->clip.x + parent->clip.width)  - clip->x);
    clip->height = fmin(clip->height, (parent->clip.y + parent->clip.height) - clip->y);
}

static void djui_base_add_padding(struct DjuiBase* base) {
    struct DjuiBaseRect* comp = &base->comp;
    struct DjuiBaseRect* parentComp = &base->comp;

    f32 tPad = (base->padding.top.type == DJUI_SVT_RELATIVE)    ? parentComp->height * base->padding.top.value    : base->padding.top.value;
    f32 rPad = (base->padding.right.type == DJUI_SVT_RELATIVE)  ? parentComp->width  * base->padding.right.value  : base->padding.right.value;
    f32 bPad = (base->padding.bottom.type == DJUI_SVT_RELATIVE) ? parentComp->height * base->padding.bottom.value : base->padding.bottom.value;
    f32 lPad = (base->padding.left.type == DJUI_SVT_RELATIVE)   ? parentComp->width  * base->padding.left.value   : base->padding.left.value;

    comp->x += lPad;
    comp->y += tPad;
    comp->height -= tPad + bPad;
    comp->width  -= lPad + rPad;
}

void djui_base_compute(struct DjuiBase* base) {
    struct DjuiBase* parent   = base->parent;
    struct DjuiBaseRect* comp = &base->comp;

    f32 x = (parent && base->x.type == DJUI_SVT_RELATIVE) ? parent->comp.width  * base->x.value : base->x.value;
    f32 y = (parent && base->y.type == DJUI_SVT_RELATIVE) ? parent->comp.height * base->y.value : base->y.value;

    f32 width  = (parent && base->width.type  == DJUI_SVT_RELATIVE) ? parent->comp.width  * base->width.value  : base->width.value;
    f32 height = (parent && base->height.type == DJUI_SVT_RELATIVE) ? parent->comp.height * base->height.value : base->height.value;

    width  = (base->width.type  == DJUI_SVT_ASPECT_RATIO) ? height * base->width.value  : width;
    height = (base->height.type == DJUI_SVT_ASPECT_RATIO) ? width  * base->height.value : height;

    if (parent != NULL) {
        // horizontal alignment
        if (base->hAlign == DJUI_HALIGN_CENTER) {
            x += (parent->comp.width - width) / 2.0f;
        } else if (base->hAlign == DJUI_HALIGN_RIGHT) {
            x = parent->comp.width - width - x;
        }

        // vertical alignment
        if (base->vAlign == DJUI_VALIGN_CENTER) {
            y += (parent->comp.height - height) / 2.0f;
        } else if (base->vAlign == DJUI_VALIGN_BOTTOM) {
            y = parent->comp.height - height - y;
        }

        // offset comp on parent's location
        x += parent->comp.x;
        y += parent->comp.y;
    }

    // set computed values
    comp->x      = x;
    comp->y      = y;
    comp->width  = width;
    comp->height = height;

    struct DjuiBaseRect* elem = &base->elem;
    elem->x      = x;
    elem->y      = y;
    elem->width  = width;
    elem->height = height;

    djui_base_clip(base);
}

void djui_base_compute_tree(struct DjuiBase* base) {
    if (!base) { return; }
    if (base->parent != NULL) {
        djui_base_compute_tree(base->parent);
    }
    djui_base_compute(base);
}

static void djui_base_add_child(struct DjuiBase* parent, struct DjuiBase* base) {
    if (parent == NULL) { return; }

    // allocate linked list node
    struct DjuiBaseChild* baseChild = calloc(1, sizeof(struct DjuiBaseChild));
    baseChild->base = base;
    baseChild->next = NULL;

    // add it to the head
    if (parent->child == NULL || parent->addChildrenToHead) {
        baseChild->next = parent->child;
        parent->child = baseChild;
        return;
    }

    // add it to the tail
    struct DjuiBaseChild* parentChild = parent->child;
    while (parentChild != NULL) {
        if (parentChild->next == NULL) {
            parentChild->next = baseChild;
            break;
        }
        parentChild = parentChild->next;
    }
}

  ////////////
 // render //
////////////

static f32 djui_base_render_border_piece(struct DjuiBase* base, f32 x1, f32 y1, f32 x2, f32 y2, bool isXBorder) {
    struct DjuiBaseRect* clip = &base->clip;

    x1 = fmax(x1, clip->x);
    y1 = fmax(y1, clip->y);
    x2 = fmin(x2, clip->x + clip->width);
    y2 = fmin(y2, clip->y + clip->height);

    if (x2 <= x1) { return 0; }
    if (y2 <= y1) { return 0; }

    // translate position
    f32 translatedX = x1;
    f32 translatedY = y1;
    djui_gfx_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // translate size
    f32 translatedWidth = x2 - x1;
    f32 translatedHeight = y2 - y1;
    djui_gfx_scale_translate(&translatedWidth, &translatedHeight);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedWidth, translatedHeight, 1.0f);

    // render
    gDPSetEnvColor(gDisplayListHead++, base->borderColor.r, base->borderColor.g, base->borderColor.b, base->borderColor.a);
    gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    return isXBorder ? fmax(x2 - x1, 0) : fmax(y2 - y1, 0);
}

static void djui_base_render_border(struct DjuiBase* base) {
    struct DjuiBaseRect* comp = &base->comp;
    struct DjuiBaseRect* clip = &base->clip;
    struct DjuiBaseRect savedComp = base->comp;

    f32 xBorderWidth = (base->borderWidth.type == DJUI_SVT_RELATIVE) ? (savedComp.width  * base->borderWidth.value) : base->borderWidth.value;
    f32 yBorderWidth = (base->borderWidth.type == DJUI_SVT_RELATIVE) ? (savedComp.height * base->borderWidth.value) : base->borderWidth.value;

    xBorderWidth = fmin(xBorderWidth, savedComp.width  / 2.0f);
    yBorderWidth = fmin(yBorderWidth, savedComp.height / 2.0f);

    comp->x      += base->borderWidth.value;
    comp->y      += base->borderWidth.value;
    comp->width  -= base->borderWidth.value * 2.0f;
    comp->height -= base->borderWidth.value * 2.0f;

    f32 addClip = 0;

    addClip = djui_base_render_border_piece(base, savedComp.x, savedComp.y, savedComp.x + savedComp.width, savedComp.y + yBorderWidth, false);
    clip->y      += addClip;
    clip->height -= addClip;

    addClip = djui_base_render_border_piece(base, savedComp.x, savedComp.y + savedComp.height - yBorderWidth, savedComp.x + savedComp.width, savedComp.y + savedComp.height, false);
    clip->height -= addClip;

    addClip = djui_base_render_border_piece(base, savedComp.x, savedComp.y, savedComp.x + xBorderWidth, savedComp.y + savedComp.height, true);
    clip->x     += addClip;
    clip->width -= addClip;

    addClip = djui_base_render_border_piece(base, savedComp.x + savedComp.width - xBorderWidth, savedComp.y, savedComp.x + savedComp.width, savedComp.y + savedComp.height, true);
    clip->width -= addClip;
}

  ////////////
 // events //
////////////

bool djui_base_render(struct DjuiBase* base) {
    if (!base->visible) { return false; }

    if (base->on_render_pre != NULL) {
        bool skipRender = false;
        base->on_render_pre(base, &skipRender);
        if (skipRender) { return false; }
    }

    struct DjuiBaseRect* comp = &base->comp;
    struct DjuiBaseRect* clip = &base->clip;

    djui_base_compute(base);
    if (comp->width  <= 0) { return false; }
    if (comp->height <= 0) { return false; }
    if (clip->width  <= 0) { return false; }
    if (clip->height <= 0) { return false; }

    if (base->borderWidth.value > 0 && base->borderColor.a > 0) {
        djui_base_render_border(base);
    }

    if (clip->width < 0 || clip->height <= 0) { return false; }

    if (base->render != NULL) {
        if (!base->render(base)) {
            return false;
        }
    }

    djui_base_add_padding(base);

    // render all children
    struct DjuiBaseChild* child = base->child;
    bool hasChildRendered = false;
    while (child != NULL) {
        struct DjuiBaseChild* nextChild = child->next;
        bool childRendered = djui_base_render(child->base);
        if (base->abandonAfterChildRenderFail && !childRendered && hasChildRendered) { break; }
        hasChildRendered = hasChildRendered || childRendered;
        if (base->on_child_render != NULL) {
            base->on_child_render(base, child->base);
        }

        child = nextChild;
    }

    return true;
}

void djui_base_destroy(struct DjuiBase* base) {
    // remove hovered status
    if (gDjuiHovered == base) {
        gDjuiHovered = NULL;
    }

    // remove focus
    if (gInteractableFocus == base) {
        gInteractableFocus = NULL;
    }

    // remove binding
    if (gInteractableBinding == base) {
        gInteractableBinding = NULL;
    }

    // remove myself from parent's linked list
    if (base->parent != NULL) {
        struct DjuiBaseChild* child     = base->parent->child;
        struct DjuiBaseChild* lastChild = NULL;
        struct DjuiBaseChild* nextChild = NULL;
        while (child != NULL) {
            nextChild = child->next;

            if (child->base == base) {
                // adjust linked list
                if (lastChild == NULL) {
                    base->parent->child = nextChild;
                } else {
                    lastChild->next = nextChild;
                }
                // deallocate child node
                free(child);
                base->parent = NULL;
                break;
            }

            // iterate
            lastChild = child;
            child = nextChild;
        }
    }

    // destroy all children and our linked list
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        struct DjuiBaseChild* nextChild = child->next;
        child->base->parent = NULL;
        djui_base_destroy(child->base);
        free(child);
        child = nextChild;
    }

    // deallocate interactable
    if (base->interactable != NULL) {
        free(base->interactable);
        base->interactable = NULL;
    }

    // remove from interactable variable
    if (base == gDjuiHovered)           { gDjuiHovered = NULL; }
    if (base == gDjuiCursorDownOn)      { gDjuiCursorDownOn = NULL; }
    if (base == gInteractableFocus)     { gInteractableFocus = NULL; }
    if (base == gInteractableBinding)   { gInteractableBinding = NULL; }
    if (base == gInteractableMouseDown) { gInteractableMouseDown = NULL; }

    // destroy this
    base->destroy(base);
}

void djui_base_destroy_children(struct DjuiBase* base) {
    // destroy all children and our linked list
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        struct DjuiBaseChild* nextChild = child->next;
        child->base->parent = NULL;
        djui_base_destroy(child->base);
        free(child);
        child = nextChild;
    }
    base->child = NULL;
}

void djui_base_destroy_one_child(struct DjuiBase* base) {
    // destroy last child in our linked list
    struct DjuiBaseChild* prev = NULL;
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        if (!child->next) { break; }
        prev = child;
        child = child->next;
    }

    if (child) {
        child->base->parent = NULL;
        djui_base_destroy(child->base);
        free(child);
        if (prev) { prev->next = NULL; }
    }
}

void djui_base_init(struct DjuiBase* parent, struct DjuiBase* base, bool (*render)(struct DjuiBase*), void (*destroy)(struct DjuiBase*)) {
    memset(base, 0, sizeof(struct DjuiBase));
    base->parent = parent;
    djui_base_set_visible(base, true);
    djui_base_set_enabled(base, true);
    djui_base_set_size(base, 64, 64);
    djui_base_set_color(base, 255, 255, 255, 255);
    base->get_cursor_hover_location = djui_base_get_cursor_hover_location;
    base->render = render;
    base->destroy = destroy;
    djui_base_add_child(parent, base);
}
