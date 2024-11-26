#include <PR/ultratypes.h>
#include "utils/misc.h"
#include "debug_context.h"
#include "debuglog.h"
#include "gfx_dimensions.h"

static u32 sCtxDepth[CTX_MAX] = { 0 };

#ifdef DEVELOPMENT

static f64 sCtxTime[CTX_MAX] = { 0 };

#define MAX_TIME_STACK 16
static f64 sCtxStartTimeStack[MAX_TIME_STACK] = { 0 };
static u32 sCtxStackIndex = 0;

#endif

void debug_context_begin(enum DebugContext ctx) {
    sCtxDepth[ctx]++;

#ifdef DEVELOPMENT
    if (sCtxStackIndex < MAX_TIME_STACK) {
        sCtxStartTimeStack[sCtxStackIndex] = clock_elapsed_f64();
    } else {
        LOG_ERROR("Exceeded time stack!");
    }
    sCtxStackIndex++;
#endif

}

void debug_context_end(enum DebugContext ctx) {
    sCtxDepth[ctx]--;

#ifdef DEVELOPMENT
    sCtxStackIndex--;
    if (sCtxStackIndex < MAX_TIME_STACK) {
        sCtxTime[ctx] += clock_elapsed_f64() - sCtxStartTimeStack[sCtxStackIndex];
    }
#endif

}

void debug_context_reset(void) {
    for (int i = 0; i < CTX_MAX; i++) {
        if (sCtxDepth[i]) { LOG_ERROR("Context was not zero on reset: %u", i); }
        sCtxDepth[i] = 0;

#ifdef DEVELOPMENT
        sCtxTime[i] = 0;
#endif

    }
}

bool debug_context_within(enum DebugContext ctx) {
    if (ctx >= CTX_MAX) { return false; }
    return sCtxDepth[ctx] > 0;
}

#ifdef DEVELOPMENT
void debug_context_set_time(enum DebugContext ctx, f64 time) {
    if (ctx >= CTX_MAX) { return; }
    sCtxTime[ctx] = time;
}

f64 debug_context_get_time(enum DebugContext ctx) {
    if (ctx >= CTX_MAX) { return 0.0; }
    return sCtxTime[ctx];
}
#endif
