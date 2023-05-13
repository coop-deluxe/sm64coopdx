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

// round up to the next multiple
#define ALIGN4(val) (((val) + 0x3) & ~0x3)
#define ALIGN8(val) (((val) + 0x7) & ~0x7)
#define ALIGN16(val) (((val) + 0xF) & ~0xF)

struct MainPoolState {
    u32 freeSpace;
    struct MainPoolBlock *listHeadL;
    struct MainPoolBlock *listHeadR;
    struct MainPoolState *prev;
};

struct MainPoolBlock {
    struct MainPoolBlock *prev;
    struct MainPoolBlock *next;
};

struct MemoryBlock {
    struct MemoryBlock *next;
    u32 size;
};

struct MemoryPool {
    u32 totalSpace;
    struct MemoryBlock *firstBlock;
    struct MemoryBlock freeList;
};

extern uintptr_t sSegmentTable[32];
extern u32 sPoolFreeSpace;
extern u8 *sPoolStart;
extern u8 *sPoolEnd;
extern struct MainPoolBlock *sPoolListHeadL;
extern struct MainPoolBlock *sPoolListHeadR;


/**
 * Memory pool for small graphical effects that aren't connected to Objects.
 * Used for colored text, paintings, and environmental snow and bubbles.
 */
struct MemoryPool *gEffectsMemoryPool = NULL;

uintptr_t sSegmentTable[32];
u32 sPoolFreeSpace;
u8 *sPoolStart;
u8 *sPoolEnd;
struct MainPoolBlock *sPoolListHeadL;
struct MainPoolBlock *sPoolListHeadR;


static struct MainPoolState *gMainPoolState = NULL;

uintptr_t set_segment_base_addr(s32 segment, void *addr) {
    sSegmentTable[segment] = (uintptr_t) addr & 0x1FFFFFFF;
    return sSegmentTable[segment];
}

void *get_segment_base_addr(s32 segment) {
    return (void *) (sSegmentTable[segment] | 0x80000000);
}

void *segmented_to_virtual(const void *addr) {
    return (void *) addr;
}

void *virtual_to_segmented(UNUSED u32 segment, const void *addr) {
    return (void *) addr;
}

void move_segment_table_to_dmem(void) {
}


/**
 * Initialize the main memory pool. This pool is conceptually a pair of stacks
 * that grow inward from the left and right. It therefore only supports
 * freeing the object that was most recently allocated from a side.
 */
void main_pool_init(void *start, void *end) {
    sPoolStart = (u8 *) ALIGN16((uintptr_t) start) + 16;
    sPoolEnd = (u8 *) ALIGN16((uintptr_t) end - 15) - 16;
    sPoolFreeSpace = sPoolEnd - sPoolStart;

    sPoolListHeadL = (struct MainPoolBlock *) (sPoolStart - 16);
    sPoolListHeadR = (struct MainPoolBlock *) sPoolEnd;
    sPoolListHeadL->prev = NULL;
    sPoolListHeadL->next = NULL;
    sPoolListHeadR->prev = NULL;
    sPoolListHeadR->next = NULL;
}

/**
 * Allocate a block of memory from the pool of given size, and from the
 * specified side of the pool (MEMORY_POOL_LEFT or MEMORY_POOL_RIGHT).
 * If there is not enough space, return NULL.
 */
void *main_pool_alloc(u32 size, u32 side) {
    struct MainPoolBlock *newListHead;
    void *addr = NULL;

    size = ALIGN16(size) + 16;
    if (size != 0 && sPoolFreeSpace >= size) {
        sPoolFreeSpace -= size;
        if (side == MEMORY_POOL_LEFT) {
            newListHead = (struct MainPoolBlock *) ((u8 *) sPoolListHeadL + size);
            sPoolListHeadL->next = newListHead;
            newListHead->prev = sPoolListHeadL;
            newListHead->next = NULL;
            addr = (u8 *) sPoolListHeadL + 16;
            sPoolListHeadL = newListHead;
        } else {
            newListHead = (struct MainPoolBlock *) ((u8 *) sPoolListHeadR - size);
            sPoolListHeadR->prev = newListHead;
            newListHead->next = sPoolListHeadR;
            newListHead->prev = NULL;
            sPoolListHeadR = newListHead;
            addr = (u8 *) sPoolListHeadR + 16;
        }
    }
    if (addr == NULL) {
        LOG_ERROR("Main pool failed to allocate memory of size 0x%X on side %d.", size, side);
    }
    return addr;
}

/**
 * Free a block of memory that was allocated from the pool. The block must be
 * the most recently allocated block from its end of the pool, otherwise all
 * newer blocks are freed as well.
 * Return the amount of free space left in the pool.
 */
u32 main_pool_free(void *addr) {
    struct MainPoolBlock *block = (struct MainPoolBlock *) ((u8 *) addr - 16);
    struct MainPoolBlock *oldListHead = (struct MainPoolBlock *) ((u8 *) addr - 16);

    if (oldListHead < sPoolListHeadL) {
        while (oldListHead->next != NULL) {
            oldListHead = oldListHead->next;
        }
        sPoolListHeadL = block;
        sPoolListHeadL->next = NULL;
        sPoolFreeSpace += (uintptr_t) oldListHead - (uintptr_t) sPoolListHeadL;
    } else {
        while (oldListHead->prev != NULL) {
            oldListHead = oldListHead->prev;
        }
        sPoolListHeadR = block->next;
        sPoolListHeadR->prev = NULL;
        sPoolFreeSpace += (uintptr_t) sPoolListHeadR - (uintptr_t) oldListHead;
    }
    return sPoolFreeSpace;
}

/**
 * Resize a block of memory that was allocated from the left side of the pool.
 * If the block is increasing in size, it must be the most recently allocated
 * block from the left side.
 * The block does not move.
 */
void *main_pool_realloc(void *addr, u32 size) {
    void *newAddr = NULL;
    struct MainPoolBlock *block = (struct MainPoolBlock *) ((u8 *) addr - 16);

    if (block->next == sPoolListHeadL) {
        main_pool_free(addr);
        newAddr = main_pool_alloc(size, MEMORY_POOL_LEFT);
    }
    if (addr == NULL) {
        LOG_ERROR("Main pool failed to reallocate memory of size 0x%X at %p!", size, addr);
    }
    return newAddr;
}

/**
 * Return the size of the largest block that can currently be allocated from the
 * pool.
 */
u32 main_pool_available(void) {
    return sPoolFreeSpace - 16;
}

/**
 * Push pool state, to be restored later. Return the amount of free space left
 * in the pool.
 */
u32 main_pool_push_state(void) {
    struct MainPoolState *prevState = gMainPoolState;
    u32 freeSpace = sPoolFreeSpace;
    struct MainPoolBlock *lhead = sPoolListHeadL;
    struct MainPoolBlock *rhead = sPoolListHeadR;

    gMainPoolState = main_pool_alloc(sizeof(*gMainPoolState), MEMORY_POOL_LEFT);
    gMainPoolState->freeSpace = freeSpace;
    gMainPoolState->listHeadL = lhead;
    gMainPoolState->listHeadR = rhead;
    gMainPoolState->prev = prevState;
    return sPoolFreeSpace;
}

/**
 * Restore pool state from a previous call to main_pool_push_state. Return the
 * amount of free space left in the pool.
 */
u32 main_pool_pop_state(void) {
    if (!gMainPoolState) { return sPoolFreeSpace; }
    sPoolFreeSpace = gMainPoolState->freeSpace;
    sPoolListHeadL = gMainPoolState->listHeadL;
    sPoolListHeadR = gMainPoolState->listHeadR;
    gMainPoolState = gMainPoolState->prev;
    return sPoolFreeSpace;
}

/**
 * Perform a DMA read from ROM. The transfer is split into 4KB blocks, and this
 * function blocks until completion.
 */
static void dma_read(u8 *dest, u8 *srcStart, u8 *srcEnd) {
    memcpy(dest, srcStart, srcEnd - srcStart);
}

/**
 * Perform a DMA read from ROM, allocating space in the memory pool to write to.
 * Return the destination address.
 */
static void *dynamic_dma_read(u8 *srcStart, u8 *srcEnd, u32 side) {
    void *dest;
    u32 size = ALIGN16(srcEnd - srcStart);

    dest = main_pool_alloc(size, side);
    if (dest != NULL) {
        dma_read(dest, srcStart, srcEnd);
    }
    return dest;
}

/**
 * Allocate a memory pool from the main pool. This pool supports arbitrary
 * order for allocation/freeing.
 * Return NULL if there is not enough space in the main pool.
 */
struct MemoryPool *mem_pool_init(u32 size, u32 side) {
    void *addr;
    struct MemoryBlock *block;
    struct MemoryPool *pool = NULL;

    size = ALIGN4(size);
    addr = main_pool_alloc(size + sizeof(struct MemoryPool), side);
    if (addr != NULL) {
        pool = (struct MemoryPool *) addr;

        pool->totalSpace = size;
        pool->firstBlock = (struct MemoryBlock *) ((u8 *) addr + sizeof(struct MemoryPool));
        pool->freeList.next = (struct MemoryBlock *) ((u8 *) addr + sizeof(struct MemoryPool));

        block = pool->firstBlock;
        block->next = NULL;
        block->size = pool->totalSpace;
    }
    if (addr == NULL) {
        LOG_ERROR("Memory pool failed to initalize memory of size 0x%X on side %d.", size, side);
    }
    return pool;
}

/**
 * Allocate from a memory pool. Return NULL if there is not enough space.
 */
void *mem_pool_alloc(struct MemoryPool *pool, u32 size) {
    struct MemoryBlock *freeBlock = &pool->freeList;
    void *addr = NULL;

    size = ALIGN4(size) + sizeof(struct MemoryBlock);
    while (freeBlock->next != NULL) {
        if (freeBlock->next->size >= size) {
            addr = (u8 *) freeBlock->next + sizeof(struct MemoryBlock);
            if (freeBlock->next->size - size <= sizeof(struct MemoryBlock)) {
                freeBlock->next = freeBlock->next->next;
            } else {
                struct MemoryBlock *newBlock = (struct MemoryBlock *) ((u8 *) freeBlock->next + size);
                newBlock->size = freeBlock->next->size - size;
                newBlock->next = freeBlock->next->next;
                freeBlock->next->size = size;
                freeBlock->next = newBlock;
            }
            break;
        }
        freeBlock = freeBlock->next;
    }
    if (addr == NULL) {
        LOG_ERROR("Memory pool failed to allocate memory of size 0x%X on at pool %p.", size, pool);
    }
    return addr;
}

/**
 * Free a block that was allocated using mem_pool_alloc.
 */
void mem_pool_free(struct MemoryPool *pool, void *addr) {
    if (!addr) { return; }
    struct MemoryBlock *block = (struct MemoryBlock *) ((u8 *) addr - sizeof(struct MemoryBlock));
    struct MemoryBlock *freeList = pool->freeList.next;

    if (pool->freeList.next == NULL) {
        pool->freeList.next = block;
        block->next = NULL;
    } else {
        if (block < pool->freeList.next) {
            if ((u8 *) pool->freeList.next == (u8 *) block + block->size) {
                block->size += freeList->size;
                block->next = freeList->next;
                pool->freeList.next = block;
            } else {
                block->next = pool->freeList.next;
                pool->freeList.next = block;
            }
        } else {
            while (freeList->next != NULL) {
                if (freeList < block && block < freeList->next) {
                    break;
                }
                freeList = freeList->next;
            }
            if ((u8 *) freeList + freeList->size == (u8 *) block) {
                freeList->size += block->size;
                block = freeList;
            } else {
                block->next = freeList->next;
                freeList->next = block;
            }
            if (block->next != NULL && (u8 *) block->next == (u8 *) block + block->size) {
                block->size = block->size + block->next->size;
                block->next = block->next->next;
            }
        }
    }
}

static struct MarioAnimDmaRelatedThing *func_802789F0(u8 *srcAddr) {
    struct MarioAnimDmaRelatedThing *sp1C = dynamic_dma_read(srcAddr, srcAddr + sizeof(u32),
                                                             MEMORY_POOL_LEFT);
    u32 size = sizeof(u32) + (sizeof(u8 *) - sizeof(u32)) + sizeof(u8 *) +
               sp1C->count * sizeof(struct OffsetSizePair);
    main_pool_free(sp1C);

    sp1C = dynamic_dma_read(srcAddr, srcAddr + size, MEMORY_POOL_LEFT);
    sp1C->srcAddr = srcAddr;
    return sp1C;
}

void func_80278A78(struct MarioAnimation *a, void *b, struct Animation *target) {
    if (b != NULL) {
        a->animDmaTable = func_802789F0(b);
    }
    a->currentAnimAddr = NULL;
    a->targetAnim = target;
}

// TODO: (Scrub C)
s32 load_patchable_table(struct MarioAnimation *a, u32 index) {
    s32 ret = FALSE;
    struct MarioAnimDmaRelatedThing *sp20 = a->animDmaTable;
    u8 *addr;
    u32 size;

    if (index < sp20->count) {
        do {
            addr = sp20->srcAddr + sp20->anim[index].offset;
            size = sp20->anim[index].size;
        } while (0);
        if (a->currentAnimAddr != addr) {
            dma_read((u8 *) a->targetAnim, addr, addr + size);
            a->currentAnimAddr = addr;
            ret = TRUE;
        }
    }
    return ret;
}
