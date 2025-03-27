#pragma once

#include <PR/ultratypes.h>
#include <stdbool.h>

#define CTX_BEGIN(_ctx) debug_context_begin(_ctx)
#define CTX_END(_ctx) debug_context_end(_ctx)
#define CTX_WITHIN(_ctx) debug_context_within(_ctx)
#define CTX_TIME(_ctx, time) debug_context_set_time(_ctx, time)
#define CTX_EXTENT(_ctx, _f) { CTX_BEGIN(_ctx); _f(); CTX_END(_ctx); }

enum DebugContext {
    CTX_NONE,
    CTX_TOTAL,
    CTX_NETWORK,
    CTX_INTERP,
    CTX_GAME_LOOP,
    CTX_SMLUA,
    CTX_AUDIO,
    CTX_RENDER,
    CTX_LEVEL_SCRIPT,
    CTX_HOOK,
    CTX_LIGHTING,
    CTX_MAX,
    // MUST BE KEPT IN SYNC WITH sDebugContextNames
};

void debug_context_begin(enum DebugContext ctx);
void debug_context_end(enum DebugContext ctx);
void debug_context_reset(void);
bool debug_context_within(enum DebugContext ctx);
void debug_context_set_time(enum DebugContext ctx, f64 time);
f64 debug_context_get_time(enum DebugContext ctx);