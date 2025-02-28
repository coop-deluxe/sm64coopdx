#include "scroll_targets.h"
#include "pc/lua/utils/smlua_math_utils.h"
#include "data/dynos_cmap.cpp.h"

static void *sScrollTargets = NULL;

/*
 * Gets the scroll targets identified by the given id
 * and returns the vertices.
 * Returns NULL if not found.
 */
struct ScrollTarget *get_scroll_targets(u32 id, u16 size, u16 offset) {
    struct ScrollTarget *scroll = hmap_get(sScrollTargets, id);
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
    struct ScrollTarget *scroll = NULL;

    if (sScrollTargets == NULL) {
        sScrollTargets = hmap_create(true);
    } else {
        scroll = hmap_get(sScrollTargets, id);
    }

    if (scroll == NULL) {
        scroll = calloc(1, sizeof(struct ScrollTarget));
        scroll->id = id;
        scroll->size = 0;
        scroll->vertices = NULL;
        scroll->hasOffset = hasOffset;
        hmap_put(sScrollTargets, id, scroll);
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
    for (struct ScrollTarget* scroll = hmap_begin(sScrollTargets); scroll != NULL; scroll = hmap_next(sScrollTargets)) {
        free(scroll->interpF32);
        free(scroll->prevF32);
        free(scroll->interpS16);
        free(scroll->prevS16);
        free(scroll->vertices);
        free(scroll);
    }
    hmap_destroy(sScrollTargets);
    sScrollTargets = NULL;
}

void patch_scroll_targets_before(void) {
    for (struct ScrollTarget* scroll = hmap_begin(sScrollTargets); scroll != NULL; scroll = hmap_next(sScrollTargets)) {
        scroll->needInterp = false;
    }
}

static inline f32 wrap_f32(f32 val) {
    if (val >=  0x8000) { val -= 0x10000; }
    if (val <= -0x8000) { val += 0x10000; }
    return val;
}

static inline s32 wrap_s32(s32 val) {
    if (val >=  0x8000) { val -= 0x10000; }
    if (val <= -0x8000) { val += 0x10000; }
    return val;
}

void patch_scroll_targets_interpolated(f32 delta) {
    for (struct ScrollTarget* scroll = hmap_begin(sScrollTargets); scroll != NULL; scroll = hmap_next(sScrollTargets)) {
        if (scroll->needInterp) {
            Vtx* *verts = scroll->vertices;
            if (scroll->bhv < SCROLL_UV_X) {
                u8 bhvIndex = MIN(scroll->bhv, 2);
                for (u16 k = 0; k < scroll->size; k++) {
                    f32 diff = wrap_f32(scroll->interpF32[k] - scroll->prevF32[k]);
                    verts[k]->n.ob[bhvIndex] = wrap_f32(scroll->prevF32[k] + diff * delta);
                }
            } else {
                u8 bhvIndex = MIN(scroll->bhv-SCROLL_UV_X, 1);
                for (u16 k = 0; k < scroll->size; k++) {
                    s32 diff = wrap_s32(scroll->interpS16[k] - scroll->prevS16[k]);
                    verts[k]->n.tc[bhvIndex] = wrap_s32(scroll->prevS16[k] + diff * delta);
                }
            }
        }
    }
}
