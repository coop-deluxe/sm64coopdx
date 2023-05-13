#include <PR/ultratypes.h>
#include "memory.h"
#include "rendering_graph_node.h"

#define ALIGN16(val) (((val) + 0xF) & ~0xF)

  //////////////////
 // dynamic pool //
//////////////////

struct DynamicPool* dynamic_pool_init(void) {
    struct DynamicPool* pool = calloc(1, sizeof(struct DynamicPool));
    pool->usedSpace = 0;
    pool->tail = NULL;
    return pool;
}

void* dynamic_pool_alloc(struct DynamicPool *pool, u32 size) {
    if (!pool) { return NULL; }

    struct DynamicPoolNode* node = calloc(1, sizeof(struct DynamicPoolNode));
    node->ptr = calloc(1, size);
    node->prev = pool->tail;

    pool->tail = node;
    pool->usedSpace += size;

    return node->ptr;
}

void dynamic_pool_free_pool(struct DynamicPool *pool) {
    if (!pool) { return; }
    struct DynamicPoolNode* node = pool->tail;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        free(node->ptr);
        free(node);
        node = prev;
    }
    free(pool);
}

  //////////////////
 // growing pool //
//////////////////

struct GrowingPool* growing_pool_init(struct GrowingPool* pool, u32 nodeSize) {
    if (pool) {
        // clear existing pool
        struct GrowingPoolNode* node = pool->tail;
        while (node) {
            node->usedSpace = 0;
            node = node->prev;
        }
        pool->usedSpace = 0;
    } else {
        // allocate a new pool
        pool = calloc(1, sizeof(struct GrowingPool));
        pool->usedSpace = 0;
        pool->nodeSize = nodeSize;
        pool->tail = NULL;
    }
    return pool;
}

void* growing_pool_alloc(struct GrowingPool *pool, u32 size) {
    if (!pool) { return NULL; }

    // maintain alignment
    size = ALIGN16(size);

    // check if it's too big for a node
    if (size >= pool->nodeSize) {
        // create a node just for this
        struct GrowingPoolNode* node = calloc(1, sizeof(struct GrowingPoolNode));
        node->ptr = calloc(1, size);
        node->prev = pool->tail;
        node->usedSpace = size;

        pool->tail = node;
        pool->usedSpace += size;

        return node->ptr;
    }

    // search for space in nodes
    struct GrowingPoolNode* node = pool->tail;
    u32 depth = 0;
    while (node) {
        depth++;
        s64 freeSpace = (s64)pool->nodeSize - (s64)node->usedSpace;
        if (freeSpace > size) { break; }
        node = node->prev;
    }

    // allocate new node
    if (!node) {
        node = calloc(1, sizeof(struct GrowingPoolNode));
        node->usedSpace = 0;
        node->ptr = calloc(1, pool->nodeSize);
        node->prev = pool->tail;
        pool->tail = node;
    }

    // retrieve pointer
    void* ptr = ((u8*)node->ptr + node->usedSpace);
    memset(ptr, 0, size);
    node->usedSpace += size;
    pool->usedSpace += size;

    return ptr;
}

void growing_pool_free_pool(struct GrowingPool *pool) {
    if (!pool) { return; }
    struct GrowingPoolNode* node = pool->tail;
    while (node) {
        struct GrowingPoolNode* prev = node->prev;
        free(node->ptr);
        free(node);
        node = prev;
    }
    free(pool);
}
