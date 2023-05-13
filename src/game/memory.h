#ifndef MEMORY_H
#define MEMORY_H

#include <PR/ultratypes.h>

#include "types.h"

#define MEMORY_POOL_LEFT  0
#define MEMORY_POOL_RIGHT 1

#define GFX_POOL_SIZE      0x400000 //  4MB (Vanilla: 512kB)
#define DEFAULT_POOL_SIZE 0x2000000 // 32MB (Vanilla: ~11MB)

struct DynamicPool
{
    u32 usedSpace;
    struct DynamicPoolNode* tail;
};

struct DynamicPoolNode
{
    void* ptr;
    struct DynamicPoolNode* prev;
};

struct GrowingPool
{
    u32 usedSpace;
    u32 nodeSize;
    struct GrowingPoolNode* tail;
};

struct GrowingPoolNode
{
    u32 usedSpace;
    void* ptr;
    struct GrowingPoolNode* prev;
};

struct MemoryPool;
struct MarioAnimation;
struct Animation;

#ifndef INCLUDED_FROM_MEMORY_C
// Declaring this variable extern puts it in the wrong place in the bss order
// when this file is included from memory.c (first instead of last). Hence,
// ifdef hack. It was very likely subject to bss reordering originally.
extern struct MemoryPool *gEffectsMemoryPool;
#endif

uintptr_t set_segment_base_addr(s32 segment, void *addr);
void *get_segment_base_addr(s32 segment);
void *segmented_to_virtual(const void *addr);
void *virtual_to_segmented(u32 segment, const void *addr);
void move_segment_table_to_dmem(void);

void main_pool_init(void *start, void *end);
void *main_pool_alloc(u32 size, u32 side);
u32 main_pool_free(void *addr);
void *main_pool_realloc(void *addr, u32 size);
u32 main_pool_available(void);
u32 main_pool_push_state(void);
u32 main_pool_pop_state(void);

#define load_segment(...)
#define load_to_fixed_pool_addr(...)
#define load_segment_decompress(...)
#define load_segment_decompress_heap(...)
#define load_engine_code_segment(...)

struct DynamicPool* dynamic_pool_init(void);
void* dynamic_pool_alloc(struct DynamicPool *pool, u32 size);
void dynamic_pool_free_pool(struct DynamicPool *pool);

struct GrowingPool* growing_pool_init(struct GrowingPool* pool, u32 nodeSize);
void* growing_pool_alloc(struct GrowingPool *pool, u32 size);
void growing_pool_free_pool(struct GrowingPool *pool);

struct MemoryPool *mem_pool_init(u32 size, u32 side);
void *mem_pool_alloc(struct MemoryPool *pool, u32 size);
void mem_pool_free(struct MemoryPool *pool, void *addr);

void *alloc_display_list(u32 size);

void func_80278A78(struct MarioAnimation *a, void *b, struct Animation *target);
s32 load_patchable_table(struct MarioAnimation *a, u32 b);

#endif // MEMORY_H
