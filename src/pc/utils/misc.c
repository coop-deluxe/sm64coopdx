#include <stdio.h>
#include <stdlib.h>
#include <PR/ultratypes.h>
#include <stdbool.h>
#include <time.h>

#include "misc.h"

#include "course_table.h"
#include "game/area.h"
#include "game/level_update.h"
#include "game/save_file.h"

float smoothstep(float edge0, float edge1, float x) {
    float t = (x - edge0) / (edge1 - edge0);
    if (t < 0) { t = 0; }
    if (t > 1) { t = 1; }
    return t * t * (3.0 - 2.0 * t);
}

void update_all_mario_stars(void) {
    s32 numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        gMarioStates[i].numStars = numStars;
    }
}

static void _clock_gettime(struct timespec* clock_time) {
#if !defined _POSIX_MONOTONIC_CLOCK || _POSIX_MONOTONIC_CLOCK < 0
    clock_gettime(CLOCK_REALTIME, clock_time);
#elif _POSIX_MONOTONIC_CLOCK > 0
    clock_gettime(CLOCK_MONOTONIC, clock_time);
#else
    if (clock_gettime(CLOCK_MONOTONIC, clock_time))
        clock_gettime(CLOCK_REALTIME, clock_time));
#endif

#ifdef DEVELOPMENT
    // give each instance a random offset for testing purposed
    static int randomOffset1 = 0;
    static int randomOffset2 = 0;
    if (randomOffset1 == 0) {
        time_t t;
        srand((unsigned)time(&t));
        randomOffset1 = rand();
        randomOffset2 = rand();
    }
    clock_time->tv_sec += randomOffset1;
    clock_time->tv_nsec += randomOffset2;
#endif
}

static u64 clock_elapsed_ns(void) {
    static bool sClockInitialized = false;
    static u64 clock_start_ns;
    if (!sClockInitialized) {
        struct timespec clock_start;
        _clock_gettime(&clock_start);
        clock_start_ns = ((u64)clock_start.tv_sec) * 1000000000 + ((u64)clock_start.tv_nsec);
        sClockInitialized = true;
    }

    struct timespec clock_current;
    _clock_gettime(&clock_current);

    u64 clock_current_ns = ((u64)clock_current.tv_sec) * 1000000000 + ((u64)clock_current.tv_nsec);
    return (clock_current_ns - clock_start_ns);
}

f32 clock_elapsed(void) {
    return (clock_elapsed_ns() / 1000000000.0f);
}

f64 clock_elapsed_f64(void) {
    return (clock_elapsed_ns() / 1000000000.0);
}

u32 clock_elapsed_ticks(void) {
    return (clock_elapsed_ns() * 3 / 100000000);
}