#include <PR/ultratypes.h>
#include <string.h>

#include "sm64.h"

#define INCLUDED_FROM_MEMORY_C

#include "buffers/buffers.h"
#include "decompress.h"
#include "game_init.h"
#include "main.h"
#include "memory.h"
#include "segment_symbols.h"
#include "segments.h"
#include "pc/debuglog.h"

struct AllocOnlyPool* alloc_only_pool_init(void) {
    struct AllocOnlyPool* pool = calloc(1, sizeof(struct AllocOnlyPool));
    pool->usedSpace = 0;
    pool->tail = NULL;
    return pool;
}

void* alloc_only_pool_alloc(struct AllocOnlyPool *pool, u32 size) {
    struct AllocOnlyNode* node = calloc(1, sizeof(struct AllocOnlyNode));
    node->ptr = calloc(1, size);
    node->prev = pool->tail;

    pool->tail = node;
    pool->usedSpace += size;

    return node->ptr;
}

struct AllocOnlyPool* alloc_only_pool_resize(UNUSED struct AllocOnlyPool* pool, UNUSED u32 size) {
    return NULL;
}

void alloc_only_pool_free(struct AllocOnlyPool *pool) {
    struct AllocOnlyNode* node = pool->tail;
    while (node) {
        struct AllocOnlyNode* prev = node->prev;
        free(node->ptr);
        free(node);
        node = prev;
    }
    free(pool);
}