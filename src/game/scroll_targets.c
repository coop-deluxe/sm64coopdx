#include "scroll_targets.h"
#include "pc/lua/utils/smlua_math_utils.h"

static struct ScrollTarget *sScrollTargets = NULL;

/*
 * Gets the scroll targets identified by the given id
 * and returns the vertices.
 * Returns NULL if not found.
 */
struct ScrollTarget *get_scroll_targets(u32 id, u16 size, u16 offset) {
    struct ScrollTarget *scroll = sScrollTargets;

    while (scroll) {
        if (scroll->id == id) {
            break;
        }
        scroll = scroll->next;
    }

    if (scroll) {

        // If we need to, realloc the block of vertices
        if ((!scroll->hasOffset && offset > 0) || size < scroll->size) {
            if (scroll->hasOffset) { return NULL; }
            if (size > scroll->size) { size = scroll->size; } // Don't use an invalid size
            if (size + offset >= scroll->size) { return NULL; } // If the offset is invalid, Abort.
            scroll->hasOffset = true;
            Vtx* *newVtx = calloc(size, sizeof(Vtx*));
            if (!newVtx) { return NULL; }
            for (u32 i = 0; i < size; i++) {
                newVtx[i] = scroll->vertices[i + offset];
            }
            free(scroll->vertices);
            scroll->vertices = newVtx;
            scroll->size = size;
        }

        return scroll;
    }
    return NULL;
}

/*
 * Finds the scroll targets identified by the given id and
 * returns it.
 * If it doesn't find it, create one and returns an allocated
 * pointer to it.
 * Also sets up the static sScrollTargets variable if there
 * isn't any scroll targets.
 */
struct ScrollTarget* find_or_create_scroll_targets(u32 id, bool hasOffset) {
    struct ScrollTarget *scroll = sScrollTargets;
    struct ScrollTarget *lastScroll = NULL;

    while (scroll) {
        if (scroll->id == id) {
            break;
        }

        lastScroll = scroll;
        scroll = scroll->next;
    }

    if (scroll == NULL) {
        scroll = calloc(1, sizeof(struct ScrollTarget));
        scroll->id = id;
        scroll->size = 0;
        scroll->vertices = NULL;
        scroll->next = NULL;
        scroll->hasOffset = hasOffset;
        if (lastScroll) {
            lastScroll->next = scroll;
        } else {
            sScrollTargets = scroll;
        }
    }

    return scroll;
}

/*
 * Adds the given vertices to the scroll targets with the
 * given id.
 * Mods have to use the lua binding of this function to
 * make the scrolling textures work.
 */
void add_vtx_scroll_target(u32 id, Vtx *vtx, u32 size, bool hasOffset) {
    struct ScrollTarget *scroll = find_or_create_scroll_targets(id, hasOffset);
    if (!scroll) { return; }
    u32 oldSize = sizeof(Vtx*) * scroll->size;
    u32 newSize = oldSize + (sizeof(Vtx*) * size);

    Vtx* *newArray = realloc(scroll->vertices, newSize);

    if (!newArray) {
        newArray = calloc(1, newSize);
        memcpy(newArray, scroll->vertices, oldSize);
        free(scroll->vertices);
    }

    scroll->vertices = newArray;

    for (u32 i = 0; i < size; ++i) {
        scroll->vertices[scroll->size++] = &vtx[i];
    }
}

/*
 * Free the static sScrollTargets variable and
 * all its content that was allocated by
 *     find_or_create_scroll_targets(id)
 * and
 *     add_vtx_scroll_targets(id, vtx, size)
 */
void free_vtx_scroll_targets(void) {
    struct ScrollTarget* scroll = sScrollTargets;
    struct ScrollTarget* nextScroll;

    while (scroll) {
        nextScroll = scroll->next;
        free(scroll->interpF32);
        free(scroll->prevF32);
        free(scroll->interpS16);
        free(scroll->prevS16);
        free(scroll->vertices);
        free(scroll);
        scroll = nextScroll;
    }

    sScrollTargets = NULL;
}

void patch_scroll_targets_before(void) {
    struct ScrollTarget *scroll = sScrollTargets;

    while (scroll) {
        scroll->needInterp = false;
        scroll = scroll->next;
    }
}

#define SHORT_RANGE 0x7FFF

void patch_scroll_targets_interpolated(f32 delta) {
    f32 antiDelta = 1.0f - delta;
    struct ScrollTarget *scroll = sScrollTargets;

    while (scroll) {
        if (scroll->needInterp) {
            Vtx* *verts = scroll->vertices;
            if (scroll->bhv < SCROLL_UV_X) {
                u8 bhvIndex = MIN(scroll->bhv, 2);
                for (u16 k = 0; k < scroll->size; k++) {
                    verts[k]->n.ob[bhvIndex] = scroll->prevF32[k] * antiDelta + scroll->interpF32[k] * delta;
                }
            } else {
                u8 bhvIndex = MIN(scroll->bhv-SCROLL_UV_X, 1);
                for (u16 k = 0; k < scroll->size; k++) {
                    verts[k]->n.tc[bhvIndex] = clampf(scroll->prevS16[k] * antiDelta + scroll->interpS16[k] * delta, -SHORT_RANGE, SHORT_RANGE);
                }
            }
        }

        scroll = scroll->next;
    }
}
