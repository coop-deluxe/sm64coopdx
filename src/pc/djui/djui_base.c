#include <string.h>
#include "djui.h"

////////////////
 // properties //
////////////////

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

void djui_base_set_size_type(struct DjuiBase* base, f32 widthType, f32 heightType) {
    base->width.type  = widthType;
    base->height.type = heightType;
}

void djui_base_set_color(struct DjuiBase* base, u8 r, u8 g, u8 b, u8 a) {
    base->color.r = r;
    base->color.g = g;
    base->color.b = b;
    base->color.a = a;
}

void djui_base_set_alignment(struct DjuiBase* base, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign) {
    base->hAlign = hAlign;
    base->vAlign = vAlign;
}

  /////////////
 // utility //
/////////////

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

void djui_base_compute(struct DjuiBase* base) {
    struct DjuiBase* parent   = base->parent;
    struct DjuiBaseRect* comp = &base->comp;

    f32 x = (base->x.type == DJUI_SVT_RELATIVE) ? parent->comp.width  * base->x.value : base->x.value;
    f32 y = (base->y.type == DJUI_SVT_RELATIVE) ? parent->comp.height * base->y.value : base->y.value;

    f32 width  = (base->width.type  == DJUI_SVT_RELATIVE) ? parent->comp.width  * base->width.value  : base->width.value;
    f32 height = (base->height.type == DJUI_SVT_RELATIVE) ? parent->comp.height * base->height.value : base->height.value;

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
    if (base->parent != NULL) {
        x += parent->comp.x;
        y += parent->comp.y;
    }

    // set computed values
    comp->x      = x;
    comp->y      = y;
    comp->width  = width;
    comp->height = height;

    djui_base_clip(base);
}

static void djui_base_add_child(struct DjuiBase* parent, struct DjuiBase* base) {
    if (parent == NULL) { return; }

    // allocate linked list node
    struct DjuiBaseChild* baseChild = malloc(sizeof(struct DjuiBaseChild));
    baseChild->base = base;
    baseChild->next = NULL;

    // add it to the head
    if (parent->child == NULL) {
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
 // events //
////////////

void djui_base_render(struct DjuiBase* base) {
    if (!base->visible) { return; }

    struct DjuiBaseRect* comp = &base->comp;
    djui_base_compute(base);
    if (comp->width  <= 0) { return; }
    if (comp->height <= 0) { return; }

    if (base->render != NULL) {
        base->render(base);
    }

    // render all children
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        djui_base_render(child->base);
        child = child->next;
    }
}

void djui_base_destroy(struct DjuiBase* base) {
    // remove myself from parent's linked list
    if (base->parent != NULL) {
        struct DjuiBaseChild* child     = base->parent->child;
        struct DjuiBaseChild* lastChild = NULL;
        while (child != NULL) {
            if (child->base == base) {
                // adjust linked list
                if (lastChild == NULL) {
                    base->parent->child = child->next;
                } else {
                    lastChild->next = child->next;
                }
                // deallocate child node
                free(child);
                base->parent = NULL;
                break;
            }

            // iterate
            lastChild = child;
            child = child->next;
        }
    }

    // destroy all children and our linked list
    struct DjuiBaseChild* child = base->child;
    while (child != NULL) {
        struct DjuiBaseChild* nextChild = child;
        child->base->parent = NULL;
        djui_base_destroy(child->base);
        free(child);
        child = nextChild->next;
    }

    // destroy this
    base->destroy(base);
}

void djui_base_init(struct DjuiBase* parent, struct DjuiBase* base, void(*render)(struct DjuiBase*), void (*destroy)(struct DjuiBase*)) {
    memset(base, 0, sizeof(struct DjuiBase));
    base->parent = parent;
    base->visible = true;
    djui_base_set_size(base, 64, 64);
    djui_base_set_color(base, 255, 255, 255, 255);
    base->render = render;
    base->destroy = destroy;
    djui_base_add_child(parent, base);
}
