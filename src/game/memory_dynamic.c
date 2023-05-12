#include <PR/ultratypes.h>
#include "memory.h"
#include "rendering_graph_node.h"

struct AllocOnlyPool* alloc_only_pool_init(void) {
    struct AllocOnlyPool* pool = calloc(1, sizeof(struct AllocOnlyPool));
    pool->usedSpace = 0;
    pool->tail = NULL;
    return pool;
}

void* alloc_only_pool_alloc(struct AllocOnlyPool *pool, u32 size) {
    if (!pool) { return NULL; }

    struct AllocOnlyNode* node = calloc(1, sizeof(struct AllocOnlyNode));
    node->ptr = calloc(1, size);
    node->prev = pool->tail;

    pool->tail = node;
    pool->usedSpace += size;

    return node->ptr;
}

void alloc_only_pool_free(struct AllocOnlyPool *pool) {
    if (!pool) { return; }
    struct AllocOnlyNode* node = pool->tail;
    while (node) {
        struct AllocOnlyNode* prev = node->prev;
        free(node->ptr);
        free(node);
        node = prev;
    }
    free(pool);
}

void *alloc_display_list(u32 size) {
    return alloc_only_pool_alloc(gDisplayListHeap, size);
}
