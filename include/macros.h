#ifndef MACROS_H
#define MACROS_H

#include "platform_info.h"

#ifndef __sgi
#define GLOBAL_ASM(...)
#endif

#if !defined(__sgi) && (!defined(NON_MATCHING) || !defined(AVOID_UB))
// asm-process isn't supported outside of IDO, and undefined behavior causes
// crashes.
#error Matching build is only possible on IDO; please build with NON_MATCHING=1.
#endif

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define GLUE(a, b) a ## b
#define GLUE2(a, b) GLUE(a, b)

// Avoid compiler warnings for unused variables
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

// Avoid undefined behaviour for non-returning functions
#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#else
#define NORETURN
#endif

// Static assertions
#ifndef __cplusplus
#ifdef __GNUC__
#define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
#define STATIC_ASSERT(cond, msg) typedef char GLUE2(static_assertion_failed, __LINE__)[(cond) ? 1 : -1]
#endif
#endif

// Align to 8-byte boundary for DMA requirements
#ifdef __GNUC__
#define ALIGNED8 __attribute__((aligned(8)))
#else
#define ALIGNED8
#endif

// Align to 16-byte boundary for audio lib requirements
#ifdef __GNUC__
#define ALIGNED16 __attribute__((aligned(16)))
#else
#define ALIGNED16
#endif

// no conversion for pc port other than cast
#define VIRTUAL_TO_PHYSICAL(addr)   ((uintptr_t)(addr))
#define PHYSICAL_TO_VIRTUAL(addr)   ((uintptr_t)(addr))
#define VIRTUAL_TO_PHYSICAL2(addr)  ((void *)(addr))

// Byteswap macros
#define BSWAP16(x) (((x) & 0xFF) << 8 | (((x) >> 8) & 0xFF))
#define BSWAP32(x) \
    ( (((x) >> 24) & 0x000000FF) | (((x) >>  8) & 0x0000FF00) | \
      (((x) <<  8) & 0x00FF0000) | (((x) << 24) & 0xFF000000) )

// Convenience macros for endian conversions
#if IS_BIG_ENDIAN
# define BE_TO_HOST16(x) (x)
# define BE_TO_HOST32(x) (x)
# define LE_TO_HOST16(x) BSWAP16(x)
# define LE_TO_HOST32(x) BSWAP32(x)
#else
# define BE_TO_HOST16(x) BSWAP16(x)
# define BE_TO_HOST32(x) BSWAP32(x)
# define LE_TO_HOST16(x) (x)
# define LE_TO_HOST32(x) (x)
#endif

// Optimize
#ifdef __clang__
#define OPTIMIZE_O3
#elif __GNUC__
#define OPTIMIZE_O3 __attribute__((optimize("O3")))
#else
#define OPTIMIZE_O3
#endif

#ifdef __clang__
#define INLINE __attribute__((always_inline)) inline
#define NOINLINE __attribute__((noinline))
#elif __GNUC__
#define INLINE __attribute__((always_inline)) inline
#define NOINLINE __attribute__((noinline))
#elif _MSC_VER
#define INLINE __forceinline
#define NOINLINE __noinline
#else
#define INLINE inline
#define NOINLINE noinline
#endif

// Repeats the macro `ACTION(N)` `N` times (one per line)
#define REPEAT_0(ACTION)
#define REPEAT_1(ACTION) ACTION(1)
#define REPEAT_2(ACTION) REPEAT_1(ACTION) ACTION(2)
#define REPEAT_3(ACTION) REPEAT_2(ACTION) ACTION(3)
#define REPEAT_4(ACTION) REPEAT_3(ACTION) ACTION(4)
#define REPEAT_5(ACTION) REPEAT_4(ACTION) ACTION(5)
#define REPEAT_6(ACTION) REPEAT_5(ACTION) ACTION(6)
#define REPEAT_7(ACTION) REPEAT_6(ACTION) ACTION(7)
#define REPEAT_8(ACTION) REPEAT_7(ACTION) ACTION(8)
#define REPEAT_9(ACTION) REPEAT_8(ACTION) ACTION(9)
#define REPEAT(ACTION, N) REPEAT_##N(ACTION)

// Expands to a comma-separated list of arguments
#define LIST_ARGS_0(ACTION)
#define LIST_ARGS_1(ACTION) ACTION(1)
#define LIST_ARGS_2(ACTION) LIST_ARGS_1(ACTION), ACTION(2)
#define LIST_ARGS_3(ACTION) LIST_ARGS_2(ACTION), ACTION(3)
#define LIST_ARGS_4(ACTION) LIST_ARGS_3(ACTION), ACTION(4)
#define LIST_ARGS_5(ACTION) LIST_ARGS_4(ACTION), ACTION(5)
#define LIST_ARGS_6(ACTION) LIST_ARGS_5(ACTION), ACTION(6)
#define LIST_ARGS_7(ACTION) LIST_ARGS_6(ACTION), ACTION(7)
#define LIST_ARGS_8(ACTION) LIST_ARGS_7(ACTION), ACTION(8)
#define LIST_ARGS_9(ACTION) LIST_ARGS_8(ACTION), ACTION(9)
#define LIST_ARGS(ACTION, N) LIST_ARGS_##N(ACTION)

#endif // MACROS_H
