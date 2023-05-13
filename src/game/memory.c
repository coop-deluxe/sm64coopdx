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
            memcpy(a->targetAnim, addr, size);
            a->currentAnimAddr = addr;
            ret = TRUE;
        }
    }
    return ret;
}
