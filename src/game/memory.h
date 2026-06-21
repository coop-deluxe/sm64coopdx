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
    struct DynamicPoolNode* nextFree;
    struct DynamicPoolNode* tail;
};

struct DynamicPoolNode
{
    void* ptr;
    u32 size;
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

// The function signature for the allocator function used by `growing_array_alloc`.
// It matches `malloc`'s.
typedef void *(*GrowingArrayAllocFunc)(size_t);

// The function signature for the deallocator function used by `growing_array_free`.
// It matches `free`'s.
typedef void (*GrowingArrayFreeFunc)(void *);

// The function signature for the compare function used by `growing_array_sort` (and `qsort`), `growing_array_bsearch`.
// It is important to note that the parameters of such functions are POINTERS to `GrowingArray` items, not the items themselves, because that's how `qsort` works!
// The return value should be an `int`:
// - negative if `l` is evaluated as "lower" than `r`,
// - positive if `l` is evaluated as "greater" than `r`,
// - zero if `l` and `r` are evaluated as equal.
//
// For example, if the growing array items are `const char *`, this function should be implemented like this:
// ```c
// int my_sort_cmp_func(const void *l, const void *r) {
//     const char *lstr = *((const char **) l);
//     const char *rstr = *((const char **) r);
//     return strcmp(lstr, rstr);
// }
// ```
typedef int (*GrowingArrayCmpFunc)(const void *, const void *);

struct GrowingArray
{
    void **buffer;
    u32 count;
    u32 capacity;
    GrowingArrayAllocFunc alloc;
    GrowingArrayFreeFunc free;
};

struct MarioAnimation;
struct Animation;

extern struct DynamicPool *gLevelPool;

uintptr_t set_segment_base_addr(s32 segment, void *addr);
void *segmented_to_virtual(const void *addr);
void *virtual_to_segmented(u32 segment, const void *addr);

#define load_segment(...)
#define load_to_fixed_pool_addr(...)
#define load_segment_decompress(...)
#define load_segment_decompress_heap(...)
#define load_engine_code_segment(...)

struct DynamicPool* dynamic_pool_init(void);
void* dynamic_pool_alloc(struct DynamicPool *pool, u32 size);
void dynamic_pool_free(struct DynamicPool *pool, void* ptr);
void dynamic_pool_free_pool(struct DynamicPool *pool);

struct GrowingPool* growing_pool_init(struct GrowingPool* pool, u32 nodeSize);
void* growing_pool_alloc(struct GrowingPool *pool, u32 size);
void growing_pool_free_pool(struct GrowingPool *pool);

struct GrowingArray *growing_array_init(struct GrowingArray *array, u32 capacity, GrowingArrayAllocFunc alloc, GrowingArrayFreeFunc free);
void *growing_array_alloc(struct GrowingArray *array, u32 size);
void growing_array_move(struct GrowingArray *array, u32 from, u32 to, u32 count);
bool growing_array_swap_and_pop_index(struct GrowingArray *array, u32 index);
bool growing_array_swap_and_pop(struct GrowingArray *array, void *ptr);
void growing_array_free(struct GrowingArray **array);
void growing_array_sort(struct GrowingArray *array, GrowingArrayCmpFunc cmpFunc);
void *growing_array_bsearch(struct GrowingArray *array, const void *elem, GrowingArrayCmpFunc cmpFunc);
void growing_array_debug_print(struct GrowingArray *array, const char *name, s32 x, s32 y);

#define growing_array_for_each_(array, type, item) \
    for (type **_head_ = (type **)((array) != NULL ? (array)->buffer : NULL), \
              **_tail_ = _head_ + ((array) != NULL ? (array)->count : 0), \
               * item  = NULL; \
        _head_ != NULL && _head_ != _tail_ && (item = *_head_, TRUE); \
        _head_++)

void alloc_display_list_reset(void);
void *alloc_display_list(u32 size);

void alloc_anim_dma_table(struct MarioAnimation* marioAnim, void *b, struct Animation *targetAnim);
s32 load_patchable_table(struct MarioAnimation *a, u32 b, bool isAnim);

#endif // MEMORY_H
