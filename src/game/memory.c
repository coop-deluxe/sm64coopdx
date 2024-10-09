#include <PR/ultratypes.h>
#include <string.h>

#include "memory.h"
#include "print.h"
#include "pc/debuglog.h"
#include "pc/lua/smlua.h"

#define ALIGN16(val) (((val) + 0xF) & ~0xF)

  //////////////////
 // dynamic pool //
//////////////////

struct DynamicPool *gLevelPool = NULL;

struct DynamicPool* dynamic_pool_init(void) {
    struct DynamicPool* pool = calloc(1, sizeof(struct DynamicPool));
    pool->usedSpace = 0;
    pool->tail = NULL;
    pool->nextFree = NULL;
    return pool;
}

void* dynamic_pool_alloc(struct DynamicPool *pool, u32 size) {
    if (!pool) { return NULL; }

    struct DynamicPoolNode* node = calloc(1, sizeof(struct DynamicPoolNode));
    node->ptr = calloc(1, size);
    node->prev = pool->tail;
    node->size = size;

    pool->tail = node;
    pool->usedSpace += size;

    return node->ptr;
}

void dynamic_pool_free(struct DynamicPool *pool, void* ptr) {
    if (!pool || !ptr) { return; }

    struct DynamicPoolNode* node = pool->tail;
    struct DynamicPoolNode* next = node;

    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        if (node->ptr == ptr) {
            if (pool->tail == node) {
                pool->tail = prev;
            } else {
                next->prev = prev;
            }
            pool->usedSpace -= node->size;
            free(node->ptr);
            free(node);
            return;
        }
        next = node;
        node = prev;
    }
    LOG_ERROR("Failed to find memory to free in dynamic pool: %p", ptr);
}

bool dynamic_pool_contains(struct DynamicPool *pool, void* ptr) {
    if (!pool || !ptr) { return false; }

    struct DynamicPoolNode* node = pool->tail;

    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        if (node->ptr == ptr) {
            return true;
        }
        node = prev;
    }
    return false;
}

void dynamic_pool_free_pool(struct DynamicPool *pool) {
    if (!pool) { return; }

    struct DynamicPoolNode* node = pool->nextFree;
    while (node) {
        struct DynamicPoolNode* prev = node->prev;
        free(node->ptr);
        free(node);
        node = prev;
    }

    // schedule current pool to be free'd on the next call
    pool->nextFree = pool->tail;
    pool->tail = NULL;
    pool->usedSpace = 0;
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
    struct GrowingPoolNode* node = NULL;
    if (size < pool->nodeSize) {
        node = pool->tail;
        u32 depth = 0;
        while (node && depth < 128) {
            depth++;
            s64 freeSpace = (s64)pool->nodeSize - (s64)node->usedSpace;
            if (freeSpace > size) { break; }
            node = node->prev;
        }
        if (depth >= 128) {
            node = NULL;
        }
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

  ///////////////////
 // growing array //
///////////////////

struct GrowingArray *growing_array_init(struct GrowingArray *array, u32 capacity) {
    growing_array_free(&array);
    array = calloc(1, sizeof(struct GrowingArray));
    array->buffer = calloc(capacity, sizeof(void *));
    array->capacity = capacity;
    array->count = 0;
    return array;
}

void *growing_array_alloc(struct GrowingArray *array, u32 size) {
    if (array && array->buffer) {

        // Increase capacity if needed
        while (array->count >= array->capacity) {
            u32 newCapacity = array->capacity * 2;
            void **newBuffer = calloc(newCapacity, sizeof(void *));
            memcpy(newBuffer, array->buffer, array->capacity * sizeof(void *));
            free(array->buffer);
            array->buffer = newBuffer;
            array->capacity = newCapacity;
        }

        // Alloc element if needed
        void **elem = &array->buffer[array->count++];
        if (!*elem) {
            *elem = malloc(size);
        }
        memset(*elem, 0, size);
        return *elem;
    }
    return NULL;
}

void growing_array_free(struct GrowingArray **array) {
    if (*array) {
        for (u32 i = 0; i != (*array)->capacity; ++i) {
            if ((*array)->buffer[i]) {
                smlua_free((*array)->buffer[i]);
            }
        }
        free((*array)->buffer);
        free(*array);
        *array = NULL;
    }
}

void growing_array_debug_print(struct GrowingArray *array, const char *name, s32 x, s32 y) {
    char text[256];
    u32 allocated = 0; for (u32 i = 0; i != array->capacity; ++i) { allocated += (array->buffer[i] != NULL); }
    snprintf(text, 256, "%-12s %5u/%5u/%5u", name, array->count, allocated, array->capacity);
    print_text(x, y, text);
}

  ///////////////////
 // display lists //
///////////////////

static struct GrowingPool* sDisplayListPool = NULL;

void alloc_display_list_reset(void) {
    sDisplayListPool = growing_pool_init(sDisplayListPool, 100000);
}

void *alloc_display_list(u32 size) {
    return growing_pool_alloc(sDisplayListPool, size);
}

  //////////////
 // segments //
//////////////

uintptr_t sSegmentTable[32] = { 0 };

uintptr_t set_segment_base_addr(s32 segment, void *addr) {
    sSegmentTable[segment] = (uintptr_t) addr & 0x1FFFFFFF;
    return sSegmentTable[segment];
}

void *segmented_to_virtual(const void *addr) {
    return (void *) addr;
}

void *virtual_to_segmented(UNUSED u32 segment, const void *addr) {
    return (void *) addr;
}

  /////////////////////
 // anim dma tables //
/////////////////////

static struct MarioAnimDmaRelatedThing* func_802789F0(u8* srcAddr) {
    u32 count = 0;
    memcpy(&count, srcAddr, sizeof(u32));
    u32 size = sizeof(u32) + (sizeof(u8 *) - sizeof(u32)) + sizeof(u8 *) + count * sizeof(struct OffsetSizePair);

    struct MarioAnimDmaRelatedThing *sp1C = malloc(size);
    memcpy(sp1C, srcAddr, size);
    sp1C->srcAddr = srcAddr;
    return sp1C;
}

void alloc_anim_dma_table(struct MarioAnimation* marioAnim, void* srcAddr, struct Animation* targetAnim) {
    if (srcAddr) {
        if (marioAnim->animDmaTable) {
            free(marioAnim->animDmaTable);
            marioAnim->animDmaTable = NULL;
        }
        marioAnim->animDmaTable = func_802789F0(srcAddr);
    }
    marioAnim->currentAnimAddr = NULL;
    marioAnim->targetAnim = targetAnim;
}

s32 load_patchable_table(struct MarioAnimation *a, u32 index, bool isAnim) {
    if (isAnim) {
        static struct MarioAnimDmaRelatedThing *marioAnims = (struct MarioAnimDmaRelatedThing *) gMarioAnims;
        if (index < marioAnims->count) {
            u8* addr = gMarioAnims + marioAnims->anim[index].offset;

            if (a->currentAnimAddr != addr) {
                a->targetAnim = (struct Animation *) addr;
                a->currentAnimAddr = addr;

                if ((uintptr_t) a->targetAnim->values < (uintptr_t) a->targetAnim) {
                    a->targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) a->targetAnim + (uintptr_t) a->targetAnim->values);
                }
                if ((uintptr_t) a->targetAnim->index < (uintptr_t) a->targetAnim) {
                    a->targetAnim->index = (void *) VIRTUAL_TO_PHYSICAL((u8 *) a->targetAnim + (uintptr_t) a->targetAnim->index);
                }
            }
        }
    } else {
        struct MarioAnimDmaRelatedThing *sp20 = a->animDmaTable;
        if (index < sp20->count) {
            u8* addr = sp20->srcAddr + sp20->anim[index].offset;
            u32 size = sp20->anim[index].size;

            if (a->targetAnim && a->currentAnimAddr != addr) {
                memcpy(a->targetAnim, addr, size);
                a->currentAnimAddr = addr;
                return TRUE;
            }
        }
    }

    return FALSE;
}
