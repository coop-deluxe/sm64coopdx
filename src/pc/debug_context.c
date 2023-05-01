#include <PR/ultratypes.h>
#include "utils/misc.h"
#include "debug_context.h"
#include "debuglog.h"
#include "game/print.h"
#include "game/hud.h"

static u32 sCtxDepth[CTX_MAX] = { 0 };

#ifdef DEVELOPMENT

static f64 sCtxTime[CTX_MAX] = { 0 };

#define MAX_TIME_STACK 16
static f64 sCtxStartTimeStack[MAX_TIME_STACK] = { 0 };
static u32 sCtxStackIndex = 0;

static char* sDebugContextNames[] = {
    "NONE",
    "FRAME",
    "NET",
    "INTERP",
    "GAME",
    "SMLUA",
    "AUDIO",
    "RENDER",
    "LEVEL",
    "HOOK",
    "MAX",
};

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
    if (ctx > CTX_MAX) { return false; }
    return sCtxDepth[ctx] > 0;
}

#ifdef DEVELOPMENT

void ctx_profiler_update_counters() {
    s32 y = SCREEN_HEIGHT - 60;
    for (s32 i = 1; i < CTX_MAX; i++) {
        const char *name = sDebugContextNames[i];
        s32 counterUs = (s32) (sCtxTime[i] * 1000000.0);
        char text[256];
        snprintf(text, 256, "             %05d", counterUs);
        memcpy(text, name, MIN(12, strlen(name)));
        for (s32 j = 0; j != 12; ++j) {
            char c = text[j];
            if (c >= 'a' && c <= 'z') c -= ('a' - 'A');
            if (c == 'J') c = 'I';
            if (c == 'Q') c = 'O';
            if (c == 'V') c = 'U';
            if (c == 'X') c = '*';
            if (c == 'Z') c = '2';
            if ((c < '0' || c > '9') && (c < 'A' || c > 'Z')) c = ' ';
            text[j] = c;
        }
        print_text(gfx_dimensions_rect_from_left_edge(4), y, text);
        y -= 18;
    }
}

#endif