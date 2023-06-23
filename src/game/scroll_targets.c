#include "scroll_targets.h"

/*
 * A scroll target is basically just a bunch of Vtx to
 * apply a movement to. Each scroll targets have an id.
 * The id is what the behavior is using to know which
 * vertices to move.
 */
struct ScrollTarget {
    u32 id;
    u32 size;
    Vtx* *vertices;
    struct ScrollTarget *next;
};

static struct ScrollTarget *sScrollTargets = NULL;

/*
 * Gets the scroll targets identified by the given id
 * and returns the vertices.
 * Returns NULL if not found.
 */
Vtx* *get_scroll_targets(u32 id) {
    struct ScrollTarget *scroll = sScrollTargets;

    while (scroll) {
        if (scroll->id == id) {
            break;
        }
        scroll = scroll->next;
    }

    if (scroll) {
        return scroll->vertices;
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
struct ScrollTarget* find_or_create_scroll_targets(u32 id) {
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
        scroll = malloc(sizeof(struct ScrollTarget));
        scroll->id = id;
        scroll->size = 0;
        scroll->vertices = NULL;
        scroll->next = NULL;
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
void add_vtx_scroll_target(u32 id, Vtx *vtx, u32 size) {
    struct ScrollTarget *scroll = find_or_create_scroll_targets(id);
    if (!scroll) { return; }
    Vtx* *newArray;
    u32 oldSize = sizeof(void*) * scroll->size;
    u32 newSize = oldSize + (sizeof(void*) * size);

    newArray = realloc(scroll->vertices, newSize);

    if (!newArray) {
        newArray = malloc(newSize);
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
void free_vtx_scroll_targets() {
    struct ScrollTarget* scroll = sScrollTargets;
    struct ScrollTarget* nextScroll;

    while (scroll) {
        nextScroll = scroll->next;
        free(scroll->vertices);
        free(scroll);
        scroll = nextScroll;
    }

    sScrollTargets = NULL;
}
