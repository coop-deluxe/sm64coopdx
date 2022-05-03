#include "types.h"
#include "PR/gbi.h"
#include "pc/utils/stb_ds.h"
#include "pc/debuglog.h"
#ifdef HAVE_SDL2
#include <SDL2/SDL.h>
#endif

struct ProfileCounters {
    const char* key;
    f64 start;
    f64 end;
    f64 sum;
    f64 disp;
    f64 avg;
    f64 max;
    u8 newMax;
    u32 indent;
};

static u32 sProfileIndent = 0;

static struct { char *key; struct ProfileCounters* value; } *sCounters = NULL;

void profiler_reset_counters(void) {
    s32 counters = hmlen(sCounters);
    for (s32 i = 0; i < counters; ++i) {
        struct ProfileCounters* v = sCounters[i].value;
        if (v == NULL) { continue; }
        v->disp = 0;
        v->max = 0;
        v->avg = 0;
        v->sum = 0;
    }
}

void profiler_start_counter(const char* keyName) {
    u32 counters = -1;
    struct ProfileCounters* v = hmget(sCounters, (char*)keyName);
    if (v == NULL) {
        v = calloc(1, sizeof(struct ProfileCounters));
        if (v == NULL) { return; }
        //hm_new_strdup(sCounters);
        hmput(sCounters, (char*)keyName, v);
        counters = hmlenu(sCounters);
    }

    counters = counters;
    f64 freq;
    f64 curr;
#ifdef HAVE_SDL2
    freq = SDL_GetPerformanceFrequency();
    curr = SDL_GetPerformanceCounter();
#endif
    v->key = keyName;
    v->start = curr / freq;
    v->indent = sProfileIndent++;
}

void profiler_stop_counter(const char* keyName) {
    struct ProfileCounters* v = hmget(sCounters, (char*)keyName);
    if (v == NULL) {
        return;
    }

    f64 freq;
    f64 curr;
#ifdef HAVE_SDL2
    freq = SDL_GetPerformanceFrequency();
    curr = SDL_GetPerformanceCounter();
#endif
    v->end = curr / freq;
    v->sum += v->end - v->start;
    sProfileIndent--;
}

void profiler_update_counters() {
    s32 counters = hmlen(sCounters);
    bool slow = false;
    for (s32 i = 0; i < counters; ++i) {
        struct ProfileCounters* v = sCounters[i].value;
        if (v == NULL) { continue; }
        v->disp = v->sum;// / (f64) REFRESH_RATE;
        v->newMax = (v->max < v->sum);
        v->max = MAX(v->sum, v->max);
        v->avg = v->avg * 0.9 + v->sum * 0.1;

        slow = slow || v->sum > 0.034;
        v->sum = 0;
    }


    if (slow) {
        printf("-----------------------------------\n");
        char indent[64] = { 0 };
        for (s32 i = 0; i < counters; ++i) {
            struct ProfileCounters* v = sCounters[i].value;
            if (v == NULL) { continue; }

            v->indent = MIN(v->indent, 63);
            char* ind = indent;
            while (v->indent > 0) {
                *ind = ' ';
                ind++;
                v->indent--;
            }
            *ind = '\0';

            printf("PROF: %f : %f : %f : %s%s%s\n", v->disp, v->avg, v->max, indent, v->key, v->newMax ? " <<<" : "");
        }
    }
    sProfileIndent = 0;
}