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
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
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
    static s32 randomOffset1 = 0;
    static s32 randomOffset2 = 0;
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

void file_get_line(char* buffer, size_t maxLength, FILE* fp) {
    char* initial = buffer;

    char c = fgetc(fp);
    while (!feof(fp) && c != '\n') {
        // make sure it's printable
        if (c < ' ' || c > '~') { goto next_get; }

        // parse new line escape code
        if (c == '\\') {
            c = fgetc(fp);
            if (feof(fp)) { break; }
            if (c == 'n') {
                if ((size_t)(buffer - initial) < (maxLength - 1)) {
                    *buffer++ = '\n';
                }
                goto next_get;
            }
        }

        // found new line
        if (c == '\n') { break; }

        // append to buffer
        if ((size_t)(buffer - initial) < (maxLength - 1)) {
            *buffer++ = c;
        }

next_get:
        c = fgetc(fp);
    }

    *buffer = '\0';
}

/////////////////

f32 delta_interpolate_f32(f32 start, f32 end, f32 delta) {
    return start * (1.0f - delta) + end * delta;
}

void delta_interpolate_vectors_s16(Vec3s res, Vec3s a, Vec3s b, f32 delta) {
    f32 antiDelta = 1.0f - delta;
    res[0] = ((a[0] * antiDelta) + (b[0] * delta));
    res[1] = ((a[1] * antiDelta) + (b[1] * delta));
    res[2] = ((a[2] * antiDelta) + (b[2] * delta));
}

void delta_interpolate_mtx(Mtx* out, Mtx* a, Mtx* b, f32 delta) {
    f32 antiDelta = 1.0f - delta;
    for (s32 i = 0; i < 4; i++) {
        for (s32 j = 0; j < 4; j++) {
            out->m[i][j] = (a->m[i][j] * antiDelta) + (b->m[i][j] * delta);
        }
    }
}